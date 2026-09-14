/*
    Copyright (C) <2012> <Syracuse System Security (Sycure) Lab>

    DECAF is based on QEMU, a whole-system emulator. You can redistribute
    and modify it under the terms of the GNU GPL, version 3 or later,
    but it is made available WITHOUT ANY WARRANTY. See the top-level
    README file for more details.

    For more information about DECAF and other softwares, see our
    web site at:
    http://sycurelab.ecs.syr.edu/

    If you have any questions about DECAF,please post it on
    http://code.google.com/p/decaf-platform/
*/
/*
* linux_vmi_new.cpp
*
*  Created on: June 26, 2015
* 	Author : Abhishek V B
*/

#include "qemu/osdep.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "cpu.h"
#include "config.h"
#include "hw/hw.h" // AWH
#include "qemu/timer.h"
#include "monitor/monitor.h"
#ifdef __cplusplus
};
#endif /* __cplusplus */

#include <inttypes.h>
#include <string>
#include <list>
#include <set>
#include <algorithm>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <queue>
#include <sys/time.h>
#include <math.h>
#include <glib.h>
#include <mcheck.h>


#include "DECAF_cmds.h"
#include "DECAF_main.h"
#include "DECAF_target.h"
#include "vmi.h"
#include "vmi_c_wrapper.h"
#include "linux_vmi_new.h"
#include "linux_procinfo.h"
#include "linux_readelf.h"
#include "hookapi.h"
#include "function_map.h"
#include "shared/utils/SimpleCallback.h"
#include "linux_readelf.h"

//zyw
#include "shared/utils/Output.h"

using namespace std;
using namespace std::tr1;

#define BREAK_IF(x) if(x) break
#define MAX_PARAM_PREFIX_LEN (64 - sizeof(target_ptr))

//Global variable used to read values from the stack
uint32_t call_stack[12];
int monitored = 0;
static int first = 1;

// current linux profile
static ProcInfo OFFSET_PROFILE = {"VMI"};

static int qrr_vmi_layout_error(char *error, size_t error_size,
                                const char *message)
{
    if (error && error_size) {
        snprintf(error, error_size, "%s", message);
    }
    return -1;
}

static bool qrr_vmi_profile_field_valid(target_ulong value)
{
    return value != (target_ulong)-1;
}

extern "C" int VMI_qrr_load_linux_profile_c(
    const char *procinfo_path, target_ulong init_task_addr,
    target_ulong proc_exec_connector, char *error, size_t error_size)
{
    ProcInfo profile = {"QRR"};

    if (load_proc_info_exact(procinfo_path, init_task_addr, &profile,
                             error, error_size) != 0) {
        return -1;
    }
    if (profile.init_task_addr != init_task_addr) {
        return qrr_vmi_layout_error(error, error_size,
                                    "procinfo-init-task-mismatch");
    }
    if (profile.proc_exec_connector != proc_exec_connector) {
        return qrr_vmi_layout_error(error, error_size,
                                    "procinfo-exec-symbol-mismatch");
    }
    if (!qrr_vmi_profile_field_valid(profile.ts_pid) ||
        !qrr_vmi_profile_field_valid(profile.ts_tgid) ||
        !qrr_vmi_profile_field_valid(profile.ts_mm) ||
        !qrr_vmi_profile_field_valid(profile.ts_fs) ||
        !qrr_vmi_profile_field_valid(profile.ts_comm) ||
        !qrr_vmi_profile_field_valid(profile.mm_pgd) ||
        !qrr_vmi_profile_field_valid(profile.mm_mmap) ||
        !qrr_vmi_profile_field_valid(profile.mm_start_brk) ||
        !qrr_vmi_profile_field_valid(profile.mm_brk) ||
        !qrr_vmi_profile_field_valid(profile.mm_start_stack) ||
        !qrr_vmi_profile_field_valid(profile.vma_vm_start) ||
        !qrr_vmi_profile_field_valid(profile.vma_vm_end) ||
        !qrr_vmi_profile_field_valid(profile.vma_vm_next) ||
        !qrr_vmi_profile_field_valid(profile.vma_vm_file) ||
        !qrr_vmi_profile_field_valid(profile.vma_vm_flags) ||
        !qrr_vmi_profile_field_valid(profile.vma_vm_pgoff) ||
        !qrr_vmi_profile_field_valid(profile.file_dentry) ||
        !qrr_vmi_profile_field_valid(profile.dentry_d_iname) ||
        !qrr_vmi_profile_field_valid(profile.dentry_d_parent) ||
        !qrr_vmi_profile_field_valid(profile.dentry_d_name) ||
        !qrr_vmi_profile_field_valid(profile.qstr_len) ||
        !qrr_vmi_profile_field_valid(profile.qstr_name) ||
        !qrr_vmi_profile_field_valid(profile.fs_seq) ||
        !qrr_vmi_profile_field_valid(profile.fs_root) ||
        !qrr_vmi_profile_field_valid(profile.fs_pwd) ||
        !qrr_vmi_profile_field_valid(profile.path_mnt) ||
        !qrr_vmi_profile_field_valid(profile.path_dentry) ||
        !qrr_vmi_profile_field_valid(profile.vfsmount_mnt_parent) ||
        !qrr_vmi_profile_field_valid(profile.vfsmount_mnt_mountpoint) ||
        !qrr_vmi_profile_field_valid(profile.vfsmount_mnt_root) ||
        !qrr_vmi_profile_field_valid(profile.ti_task)) {
        return qrr_vmi_layout_error(error, error_size,
                                    "procinfo-required-offset-missing");
    }
    OFFSET_PROFILE = profile;
    if (error && error_size) {
        error[0] = '\0';
    }
    fprintf(stderr,
            "qrr-full: exact procinfo profile=%s init_task=%08" PRIx64
            " proc_exec_connector=%08" PRIx64 " source=%s\n",
            OFFSET_PROFILE.strName, (uint64_t)init_task_addr,
            (uint64_t)proc_exec_connector, procinfo_path);
    return 0;
}

extern "C" int VMI_qrr_read_exec_identity_c(
    CPUState *env, target_ulong task, qrr_vmi_exec_identity_t *identity,
    char *error, size_t error_size)
{
    target_ulong task_pgd;
    target_ulong physical_pgd;
    target_ulong pid;
    target_ulong tgid;

    if (!env || !task || !identity) {
        return qrr_vmi_layout_error(error, error_size, "invalid-argument");
    }
    memset(identity, 0, sizeof(*identity));
    identity->task = task;
    if (!OFFSET_PROFILE.init_task_addr) {
        return qrr_vmi_layout_error(error, error_size,
                                    "procinfo-profile-not-loaded");
    }
    if (DECAF_read_ptr(env, task + OFFSET_PROFILE.ts_mm,
                       &identity->mm) < 0 || !identity->mm ||
        DECAF_read_ptr(env, identity->mm + OFFSET_PROFILE.mm_pgd,
                       &task_pgd) < 0 || !task_pgd ||
        DECAF_read_ptr(env, task + OFFSET_PROFILE.ts_pid, &pid) < 0 ||
        DECAF_read_ptr(env, task + OFFSET_PROFILE.ts_tgid, &tgid) < 0 ||
        DECAF_read_mem(env, task + OFFSET_PROFILE.ts_comm,
                       sizeof(identity->name), identity->name) < 0) {
        return qrr_vmi_layout_error(error, error_size,
                                    "exec-task-read-failed");
    }
    if (!memchr(identity->name, '\0', sizeof(identity->name)) ||
        !identity->name[0] || pid > UINT32_MAX || !pid ||
        tgid > UINT32_MAX || !tgid) {
        return qrr_vmi_layout_error(error, error_size,
                                    "exec-task-identity-invalid");
    }
#ifdef TARGET_MIPS
    if (task_pgd >= UINT32_C(0x80000000) &&
        task_pgd < UINT32_C(0xa0000000)) {
        physical_pgd = task_pgd - UINT32_C(0x80000000);
    } else if (task_pgd >= UINT32_C(0xa0000000) &&
               task_pgd < UINT32_C(0xc0000000)) {
        physical_pgd = task_pgd - UINT32_C(0xa0000000);
    } else {
        return qrr_vmi_layout_error(error, error_size,
                                    "exec-task-pgd-not-direct-mapped");
    }
#else
    physical_pgd = DECAF_get_phys_addr(env, task_pgd);
#endif
    identity->pgd = physical_pgd;
    identity->pid = (uint32_t)pid;
    identity->tgid = (uint32_t)tgid;
    if (error && error_size) {
        error[0] = '\0';
    }
    return 0;
}

extern "C" int VMI_qrr_task_from_thread_info_c(
    CPUState *env, target_ulong thread_info, target_ulong *task,
    char *error, size_t error_size)
{
    if (!env || !thread_info || !task) {
        return qrr_vmi_layout_error(error, error_size, "invalid-argument");
    }
    if (!OFFSET_PROFILE.init_task_addr) {
        return qrr_vmi_layout_error(error, error_size,
                                    "procinfo-profile-not-loaded");
    }
    if (DECAF_read_ptr(env, thread_info + OFFSET_PROFILE.ti_task,
                       task) < 0 || !*task) {
        return qrr_vmi_layout_error(error, error_size,
                                    "thread-info-task-read-failed");
    }
    if (error && error_size) {
        error[0] = '\0';
    }
    return 0;
}

#define QRR_VMI_CWD_MAX_COMPONENTS 512
#define QRR_VMI_NAME_MAX 255

typedef struct _qrr_vmi_path_pair
{
    target_ulong mnt;
    target_ulong dentry;
} qrr_vmi_path_pair_t;

static int qrr_vmi_read_path_pair(CPUState *env, target_ulong address,
                                  qrr_vmi_path_pair_t *path,
                                  char *error, size_t error_size)
{
    if (DECAF_read_ptr(env, address + OFFSET_PROFILE.path_mnt,
                       &path->mnt) < 0 || !path->mnt) {
        if (error && error_size) {
            snprintf(error, error_size,
                     "cwd-path-mnt-read-failed path=%08" PRIx64,
                     (uint64_t)address);
        }
        return -1;
    }
    if (DECAF_read_ptr(env, address + OFFSET_PROFILE.path_dentry,
                       &path->dentry) < 0 || !path->dentry) {
        if (error && error_size) {
            snprintf(error, error_size,
                     "cwd-path-dentry-read-failed path=%08" PRIx64
                     " mnt=%08" PRIx64,
                     (uint64_t)address, (uint64_t)path->mnt);
        }
        return -1;
    }
    return 0;
}

static int qrr_vmi_build_cwd(CPUState *env,
                             const qrr_vmi_path_pair_t *root,
                             const qrr_vmi_path_pair_t *pwd,
                             char *cwd, size_t cwd_size,
                             char *error, size_t error_size)
{
    qrr_vmi_path_pair_t current = *pwd;
    qrr_vmi_path_pair_t visited[QRR_VMI_CWD_MAX_COMPONENTS];
    char reversed[QRR_VMI_CWD_SIZE];
    size_t position = sizeof(reversed) - 1;
    size_t count = 0;

    if (!cwd || cwd_size < 2 || cwd_size > sizeof(reversed)) {
        return qrr_vmi_layout_error(error, error_size,
                                    "cwd-buffer-invalid");
    }
    reversed[position] = '\0';
    while (current.mnt != root->mnt || current.dentry != root->dentry) {
        target_ulong mount_root;
        size_t index;

        if (count == QRR_VMI_CWD_MAX_COMPONENTS) {
            return qrr_vmi_layout_error(error, error_size,
                                        "cwd-component-limit");
        }
        for (index = 0; index < count; index++) {
            if (visited[index].mnt == current.mnt &&
                visited[index].dentry == current.dentry) {
                return qrr_vmi_layout_error(error, error_size,
                                            "cwd-path-cycle");
            }
        }
        visited[count++] = current;
        if (DECAF_read_ptr(env,
                           current.mnt + OFFSET_PROFILE.vfsmount_mnt_root,
                           &mount_root) < 0 || !mount_root) {
            if (error && error_size) {
                snprintf(error, error_size,
                         "cwd-mount-root-read-failed mnt=%08" PRIx64,
                         (uint64_t)current.mnt);
            }
            return -1;
        }
        if (current.dentry == mount_root) {
            target_ulong parent_mnt;
            target_ulong mountpoint;

            if (current.mnt == root->mnt) {
                return qrr_vmi_layout_error(error, error_size,
                                            "cwd-outside-process-root");
            }
            if (DECAF_read_ptr(
                    env, current.mnt + OFFSET_PROFILE.vfsmount_mnt_parent,
                    &parent_mnt) < 0 || !parent_mnt) {
                if (error && error_size) {
                    snprintf(error, error_size,
                             "cwd-mount-parent-read-failed mnt=%08" PRIx64,
                             (uint64_t)current.mnt);
                }
                return -1;
            }
            if (DECAF_read_ptr(
                    env,
                    current.mnt + OFFSET_PROFILE.vfsmount_mnt_mountpoint,
                    &mountpoint) < 0 || !mountpoint) {
                if (error && error_size) {
                    snprintf(error, error_size,
                             "cwd-mountpoint-read-failed mnt=%08" PRIx64,
                             (uint64_t)current.mnt);
                }
                return -1;
            }
            if (parent_mnt == current.mnt) {
                if (error && error_size) {
                    snprintf(error, error_size,
                             "cwd-mount-parent-self mnt=%08" PRIx64,
                             (uint64_t)current.mnt);
                }
                return -1;
            }
            current.mnt = parent_mnt;
            current.dentry = mountpoint;
            continue;
        }
        {
            target_ulong parent;
            target_ulong name_pointer;
            target_ulong name_length;
            unsigned char name[QRR_VMI_NAME_MAX];

            if (DECAF_read_ptr(
                    env, current.dentry + OFFSET_PROFILE.dentry_d_parent,
                    &parent) < 0 || !parent) {
                if (error && error_size) {
                    snprintf(error, error_size,
                             "cwd-dentry-parent-read-failed dentry=%08"
                             PRIx64,
                             (uint64_t)current.dentry);
                }
                return -1;
            }
            if (parent == current.dentry) {
                if (error && error_size) {
                    snprintf(error, error_size,
                             "cwd-dentry-parent-self dentry=%08" PRIx64,
                             (uint64_t)current.dentry);
                }
                return -1;
            }
            if (DECAF_read_ptr(
                    env,
                    current.dentry + OFFSET_PROFILE.dentry_d_name +
                        OFFSET_PROFILE.qstr_len,
                    &name_length) < 0) {
                if (error && error_size) {
                    snprintf(error, error_size,
                             "cwd-dentry-name-length-read-failed dentry="
                             "%08" PRIx64,
                             (uint64_t)current.dentry);
                }
                return -1;
            }
            if (!name_length || name_length > sizeof(name)) {
                if (error && error_size) {
                    snprintf(error, error_size,
                             "cwd-dentry-name-length-invalid dentry=%08"
                             PRIx64 " length=%" PRIu64,
                             (uint64_t)current.dentry,
                             (uint64_t)name_length);
                }
                return -1;
            }
            if (DECAF_read_ptr(
                    env,
                    current.dentry + OFFSET_PROFILE.dentry_d_name +
                        OFFSET_PROFILE.qstr_name,
                    &name_pointer) < 0 || !name_pointer) {
                if (error && error_size) {
                    snprintf(error, error_size,
                             "cwd-dentry-name-pointer-read-failed dentry="
                             "%08" PRIx64,
                             (uint64_t)current.dentry);
                }
                return -1;
            }
            if (DECAF_read_mem(env, name_pointer, name_length, name) < 0) {
                if (error && error_size) {
                    snprintf(error, error_size,
                             "cwd-dentry-name-read-failed dentry=%08"
                             PRIx64 " name=%08" PRIx64 " length=%" PRIu64,
                             (uint64_t)current.dentry,
                             (uint64_t)name_pointer,
                             (uint64_t)name_length);
                }
                return -1;
            }
            if (memchr(name, '\0', name_length) ||
                memchr(name, '/', name_length)) {
                return qrr_vmi_layout_error(error, error_size,
                                            "cwd-component-invalid");
            }
            if (position < name_length + 1) {
                return qrr_vmi_layout_error(error, error_size,
                                            "cwd-path-too-long");
            }
            position -= name_length;
            memcpy(reversed + position, name, name_length);
            reversed[--position] = '/';
            current.dentry = parent;
        }
    }
    if (position == sizeof(reversed) - 1) {
        reversed[--position] = '/';
    }
    if (sizeof(reversed) - position > cwd_size) {
        return qrr_vmi_layout_error(error, error_size,
                                    "cwd-output-too-small");
    }
    memcpy(cwd, reversed + position, sizeof(reversed) - position);
    return 0;
}

extern "C" int VMI_qrr_read_exec_cwd_c(
    CPUState *env, target_ulong task, char *cwd, size_t cwd_size,
    char *error, size_t error_size)
{
    target_ulong fs;
    unsigned int attempt;

    if (!env || !task || !cwd || cwd_size < 2) {
        return qrr_vmi_layout_error(error, error_size, "invalid-argument");
    }
    if (!OFFSET_PROFILE.init_task_addr) {
        return qrr_vmi_layout_error(error, error_size,
                                    "procinfo-profile-not-loaded");
    }
    if (DECAF_read_ptr(env, task + OFFSET_PROFILE.ts_fs, &fs) < 0 || !fs) {
        if (error && error_size) {
            snprintf(error, error_size,
                     "task-fs-read-failed task=%08" PRIx64
                     " field=%08" PRIx64,
                     (uint64_t)task,
                     (uint64_t)(task + OFFSET_PROFILE.ts_fs));
        }
        return -1;
    }
    for (attempt = 0; attempt < 4; attempt++) {
        target_ulong sequence_before;
        target_ulong sequence_after;
        qrr_vmi_path_pair_t root;
        qrr_vmi_path_pair_t pwd;
        char captured[QRR_VMI_CWD_SIZE];
        char walk_error[128] = { 0 };
        int walk_result = -1;

        if (DECAF_read_ptr(env, fs + OFFSET_PROFILE.fs_seq,
                           &sequence_before) < 0) {
            return qrr_vmi_layout_error(error, error_size,
                                        "cwd-sequence-read-failed");
        }
        if (sequence_before & 1) {
            continue;
        }
        if (qrr_vmi_read_path_pair(env, fs + OFFSET_PROFILE.fs_root,
                                   &root, walk_error,
                                   sizeof(walk_error)) == 0 &&
            qrr_vmi_read_path_pair(env, fs + OFFSET_PROFILE.fs_pwd,
                                   &pwd, walk_error,
                                   sizeof(walk_error)) == 0) {
            walk_result = qrr_vmi_build_cwd(
                env, &root, &pwd, captured, sizeof(captured), walk_error,
                sizeof(walk_error));
        }
        if (DECAF_read_ptr(env, fs + OFFSET_PROFILE.fs_seq,
                           &sequence_after) < 0) {
            return qrr_vmi_layout_error(error, error_size,
                                        "cwd-sequence-read-failed");
        }
        if (sequence_before != sequence_after || (sequence_after & 1)) {
            continue;
        }
        if (walk_result != 0) {
            if (error && error_size) {
                snprintf(error, error_size,
                         "cwd-walk-failed fs=%08" PRIx64
                         " root=%08" PRIx64 ":%08" PRIx64
                         " pwd=%08" PRIx64 ":%08" PRIx64 " cause=%s",
                         (uint64_t)fs, (uint64_t)root.mnt,
                         (uint64_t)root.dentry, (uint64_t)pwd.mnt,
                         (uint64_t)pwd.dentry,
                         walk_error[0] ? walk_error : "unknown");
            }
            return -1;
        }
        if (strlen(captured) + 1 > cwd_size) {
            return qrr_vmi_layout_error(error, error_size,
                                        "cwd-output-too-small");
        }
        memcpy(cwd, captured, strlen(captured) + 1);
        if (error && error_size) {
            error[0] = '\0';
        }
        return 0;
    }
    return qrr_vmi_layout_error(error, error_size, "cwd-sequence-unstable");
}

static int qrr_vmi_read_linux_layout_task(CPUState *env, target_ulong task,
                                          qrr_vmi_layout_t *layout,
                                          char *error, size_t error_size)
{
    target_ulong mm;
    target_ulong vma;
    target_ulong first_vma;
    size_t count = 0;

    if (!env || !layout) {
        return qrr_vmi_layout_error(error, error_size, "invalid-argument");
    }
    memset(layout, 0, sizeof(*layout));
    if (!OFFSET_PROFILE.init_task_addr) {
        return qrr_vmi_layout_error(error, error_size,
                                    "procinfo-profile-not-loaded");
    }
    if (!task) {
        return qrr_vmi_layout_error(error, error_size,
                                    "process-task-struct-not-found");
    }
    if (DECAF_read_ptr(env, task + OFFSET_PROFILE.ts_mm,
                       &mm) < 0 || !mm) {
        return qrr_vmi_layout_error(error, error_size,
                                    "task-mm-read-failed");
    }
    if (DECAF_read_ptr(env, mm + OFFSET_PROFILE.mm_start_brk,
                       &layout->start_brk) < 0 ||
        DECAF_read_ptr(env, mm + OFFSET_PROFILE.mm_brk,
                       &layout->brk) < 0 ||
        DECAF_read_ptr(env, mm + OFFSET_PROFILE.mm_start_stack,
                       &layout->start_stack) < 0 ||
        DECAF_read_ptr(env, mm + OFFSET_PROFILE.mm_mmap, &vma) < 0) {
        return qrr_vmi_layout_error(error, error_size,
                                    "mm-layout-read-failed");
    }
    if (!layout->start_brk || layout->brk < layout->start_brk ||
        !layout->start_stack) {
        return qrr_vmi_layout_error(error, error_size,
                                    "mm-layout-invalid");
    }
    first_vma = vma;
    while (vma) {
        qrr_vmi_vma_t *out;
        target_ulong next;

        if (count == QRR_VMI_MAX_VMAS) {
            return qrr_vmi_layout_error(error, error_size,
                                        "vma-limit-exceeded");
        }
        out = &layout->vmas[count];
        if (DECAF_read_ptr(env, vma + OFFSET_PROFILE.vma_vm_start,
                           &out->start) < 0 ||
            DECAF_read_ptr(env, vma + OFFSET_PROFILE.vma_vm_end,
                           &out->end) < 0 ||
            DECAF_read_ptr(env, vma + OFFSET_PROFILE.vma_vm_flags,
                           &out->flags) < 0 ||
            DECAF_read_ptr(env, vma + OFFSET_PROFILE.vma_vm_pgoff,
                           &out->pgoff) < 0 ||
            DECAF_read_ptr(env, vma + OFFSET_PROFILE.vma_vm_file,
                           &out->file) < 0) {
            return qrr_vmi_layout_error(error, error_size,
                                        "vma-field-read-failed");
        }
        if (!out->start || out->end <= out->start) {
            return qrr_vmi_layout_error(error, error_size,
                                        "vma-range-invalid");
        }
        if (out->file) {
            target_ulong dentry;

            if (DECAF_read_ptr(env,
                               out->file + OFFSET_PROFILE.file_dentry,
                               &dentry) < 0 || !dentry ||
                DECAF_read_mem(env,
                               dentry + OFFSET_PROFILE.dentry_d_iname,
                               QRR_VMI_FILE_NAME_SIZE,
                               out->file_name) < 0) {
                return qrr_vmi_layout_error(error, error_size,
                                            "vma-file-name-read-failed");
            }
            out->file_name[QRR_VMI_FILE_NAME_SIZE - 1] = '\0';
            if (!out->file_name[0]) {
                return qrr_vmi_layout_error(error, error_size,
                                            "vma-file-name-empty");
            }
        }
        count++;
        if (DECAF_read_ptr(env, vma + OFFSET_PROFILE.vma_vm_next,
                           &next) < 0) {
            return qrr_vmi_layout_error(error, error_size,
                                        "vma-next-read-failed");
        }
        if (next == first_vma || next == vma) {
            return qrr_vmi_layout_error(error, error_size,
                                        "vma-list-cycle");
        }
        vma = next;
    }
    if (!count) {
        return qrr_vmi_layout_error(error, error_size, "vma-list-empty");
    }
    layout->vma_count = count;
    if (error && error_size) {
        error[0] = '\0';
    }
    return 0;
}

extern "C" int VMI_qrr_read_linux_layout_task_c(
    CPUState *env, target_ulong task, qrr_vmi_layout_t *layout,
    char *error, size_t error_size)
{
    return qrr_vmi_read_linux_layout_task(env, task, layout,
                                          error, error_size);
}

extern "C" int VMI_read_linux_layout_c(CPUState *env, uint32_t cr3,
                                         qrr_vmi_layout_t *layout,
                                         char *error, size_t error_size)
{
    process *proc = VMI_find_process_by_pgd(cr3);

    if (!proc || !proc->EPROC_base_addr) {
        return qrr_vmi_layout_error(error, error_size,
                                    "process-task-struct-not-found");
    }
    return qrr_vmi_read_linux_layout_task(env, proc->EPROC_base_addr,
                                          layout, error, error_size);
}


void print_loaded_modules(CPUState *env)
{

    target_ulong  modules_list, module_size, first_module;

    target_ulong next_module = OFFSET_PROFILE.modules;
	next_module -= OFFSET_PROFILE.module_list;

	first_module = next_module;

	DECAF_read_ptr(env, next_module + OFFSET_PROFILE.module_list ,
                              &next_module);

  	next_module -= OFFSET_PROFILE.module_list;
	
	char module_name[MAX_PARAM_PREFIX_LEN];

    //monitor_printf(cur_mon, "%20s     %10s \n", "Module", "Size");


    while(true)
    {
        DECAF_read_mem(env, next_module + OFFSET_PROFILE.module_name,
						 MAX_PARAM_PREFIX_LEN, module_name);

        module_name[MAX_PARAM_PREFIX_LEN - 1] = '\0';

					
        DECAF_read_ptr(env, next_module + OFFSET_PROFILE.module_size,
                                &module_size);

        //monitor_printf(cur_mon, "%20s  |  %10lu\n", module_name, module_size);

		DECAF_read_ptr(env, next_module + OFFSET_PROFILE.module_list ,
                              &next_module);
			  
        next_module -= OFFSET_PROFILE.module_list;

        if(first_module == next_module)
        {
			//monitor_printf(cur_mon, "done\n");
            break;
        }

    }

}

void print_loaded_modules_old(CPUState *env)
{
	

}


static void traverse_kmod_list(CPUState *env)
{
	target_ulong  modules_list, module_size, first_module, module_base;

    target_ulong next_module = OFFSET_PROFILE.modules;
	next_module -= OFFSET_PROFILE.module_list;

	first_module = next_module;

	DECAF_read_ptr(env, next_module + OFFSET_PROFILE.module_list ,
                              &next_module);

  	next_module -= OFFSET_PROFILE.module_list;
	
	char module_name[MAX_PARAM_PREFIX_LEN];

    while(true)
    {
        DECAF_read_mem(env, next_module + OFFSET_PROFILE.module_name,
						 MAX_PARAM_PREFIX_LEN, module_name);

        //module_name[MAX_PARAM_PREFIX_LEN - 1] = '\0';
		module_name[31] = '\0';
			

		if(!VMI_find_kmod_by_name(module_name))
		{
								
	        DECAF_read_ptr(env, next_module + OFFSET_PROFILE.module_size,
	                                &module_size);

	        DECAF_read_ptr(env, next_module + OFFSET_PROFILE.module_init,
	                                &module_base);

			module *mod = new module();
            strncpy(mod->name, module_name, 31);
            mod->name[31] = '\0';
            mod->size = module_size;
            mod->inode_number = 0;
            mod->symbols_extracted = 1;

			//monitor_printf(default_mon, "kernel module %s base %x\n", module_name, module_base);
            VMI_add_module(mod, module_name);

	        VMI_insert_module(0, module_base , mod);
		}

		DECAF_read_ptr(env, next_module + OFFSET_PROFILE.module_list ,
                              &next_module);
			  
        next_module -= OFFSET_PROFILE.module_list;

        if(first_module == next_module)
        {
            break;
        }

    }
}



//  Wait for kernel's `init_module` to call `trim_init_extable' where we grab module data
static void new_kmod_callback(DECAF_Callback_Params* params)
{
	CPUState *env = params->bb.env;

	target_ulong pc = DECAF_getPC(env);

    if(OFFSET_PROFILE.trim_init_extable != pc)
        return;

	traverse_kmod_list(env);
}


//  Traverse the task_struct linked list and add all un-added processes
//  This function is called
static void traverse_task_struct_add(CPUState *env)
{

    target_ulong task_pid = 0; //zyw change uint32_t to target_ulong
   // uint32_t task_pid = 0;
    uint32_t kernel_count = 0; //zyw
    const int MAX_LOOP_COUNT = 10240;	// prevent infinite loop
    target_ulong next_task, mm, proc_cr3, task_pgd, ts_parent_pid, ts_real_parent;
    next_task = OFFSET_PROFILE.init_task_addr;

    for (int count = MAX_LOOP_COUNT; count > 0; --count)
    {
        BREAK_IF(DECAF_read_ptr(env, next_task + (OFFSET_PROFILE.ts_tasks + sizeof(target_ptr)),
                                &next_task) < 0);

        next_task -= OFFSET_PROFILE.ts_tasks;

        if(OFFSET_PROFILE.init_task_addr == next_task)
        {
            break;
        }



        BREAK_IF(DECAF_read_ptr(env, next_task + OFFSET_PROFILE.ts_mm, &mm) < 0);
	
        if (mm != 0)
        {
            BREAK_IF(DECAF_read_ptr(env, mm + OFFSET_PROFILE.mm_pgd,
                                    &task_pgd) < 0);

	//DECAF_read_ptr(env, mm + OFFSET_PROFILE.mm_pgd, &task_pgd);
            proc_cr3 = DECAF_get_phys_addr(env, task_pgd);
        }

        else
        {
            // We don't add kernel processed for now.
            proc_cr3 = -1;
            kernel_count++;
            continue;
        }
        if (!VMI_find_process_by_pgd(proc_cr3))
        {
            // get task_pid
            BREAK_IF(DECAF_read_ptr(env, next_task + OFFSET_PROFILE.ts_tgid,
                                    &task_pid) < 0);

            // get parent task's base address
            BREAK_IF(DECAF_read_ptr(env, next_task + OFFSET_PROFILE.ts_real_parent,
                                    &ts_real_parent) < 0
                     ||
                     DECAF_read_ptr(env, ts_real_parent + OFFSET_PROFILE.ts_tgid,
                                    &ts_parent_pid) < 0);

            process* pe = new process();
            pe->pid = task_pid;
            pe->parent_pid = ts_parent_pid;
            pe->cr3 = proc_cr3;
            pe->EPROC_base_addr = next_task; // store current task_struct's base address
            BREAK_IF(DECAF_read_mem(env, next_task + OFFSET_PROFILE.ts_comm,
                                    SIZEOF_COMM, pe->name) < 0);

            VMI_create_process(pe);
			pe->modules_extracted = false;
        }
    }
    //zyw
    //printf("\n\n\n\n kernel_count:%d,count:%d\n\n\n", kernel_count,MAX_LOOP_COUNT-count);
}

// Traverse the task_struct linked list and updates the internal DECAF process data structures on process exit
// This is called when the linux system call `proc_exit_connector` is called.
static process *traverse_task_struct_remove(CPUState *env)
{
    set<target_ulong> pids;
    target_ulong task_pid = 0; //zyw change uint32_t to target_ulong
    //uint32_t task_pid = 0;
    process *right_proc = NULL;
    uint32_t right_pid = 0;

    target_ulong next_task, mm;
    next_task = OFFSET_PROFILE.init_task_addr;

    while(true)
    {
        BREAK_IF(DECAF_read_ptr(env, next_task + (OFFSET_PROFILE.ts_tasks + sizeof(target_ptr)),
                                &next_task) < 0);

        next_task -= OFFSET_PROFILE.ts_tasks;

        if(OFFSET_PROFILE.init_task_addr == next_task)
        {
            break;
        }

        BREAK_IF(DECAF_read_ptr(env, next_task + OFFSET_PROFILE.ts_mm,
                                &mm) < 0);

        if (mm != 0)
        {
            DECAF_read_ptr(env, next_task + OFFSET_PROFILE.ts_tgid,
                           &task_pid);
            // Collect PIDs of all processes in the task linked list
            pids.insert(task_pid);
        }

    }

    // Compare the collected list with the internal list. We track the Process which is removed and call `VMI_process_remove`
    for(unordered_map < uint32_t, process * >::iterator iter = process_pid_map.begin(); iter != process_pid_map.end(); ++iter)
    {
        if(iter->first != 0 && !pids.count(iter->first))
        {
            right_pid = iter->first;
            right_proc = iter->second;
            break;
        }
    }

    if(right_pid == 0)
		return NULL;
	
	//monitor_printf(default_mon,"process with pid [%08x]  ended\n",right_pid);

    VMI_remove_process(right_pid);
    return right_proc;
}

// Traverse the memory map for a process
void traverse_mmap(CPUState *env, void *opaque)
{
    process *proc = (process *)opaque;
    target_ulong mm, vma_curr, vma_file, f_dentry, f_inode, mm_mmap, vma_next=NULL;
    set<target_ulong> module_bases;
    unsigned int inode_number;
    target_ulong vma_vm_start = 0, vma_vm_end = 0;
    target_ulong last_vm_start = 0, last_vm_end = 0, mod_vm_start = 0;
    char name[32];	// module file path
    string last_mod_name;
    module *mod = NULL;

    if (DECAF_read_ptr(env, proc->EPROC_base_addr + OFFSET_PROFILE.ts_mm, &mm) < 0)
        return;

    if (DECAF_read_ptr(env, mm + OFFSET_PROFILE.mm_mmap, &mm_mmap) < 0)
        return;
    // Mark the `modules_extracted` true. This is done because this function calls `VMI_find_module_by_base`
    // and that function calls `traverse_mmap` if `modules_extracted` is false. We don't want to get into
    // an infinite recursion.
    proc->modules_extracted = true;

    if (-1UL == proc->cr3)
        return;


    // starting from the first vm_area, read vm_file. NOTICE vm_area_struct can be null
    if (( vma_curr = mm_mmap) == 0)
        return;


    while(true)
    {
        // read start of curr vma
        if (DECAF_read_ptr(env, vma_curr + OFFSET_PROFILE.vma_vm_start, &vma_vm_start) < 0)
            goto next;

        // read end of curr vma
        if (DECAF_read_ptr(env, vma_curr + OFFSET_PROFILE.vma_vm_end, &vma_vm_end) < 0)
            goto next;

        DECAF_printf("memory %x:%x ", vma_vm_start, vma_vm_end); 

        // read the struct* file entry of the curr vma, used to then extract the dentry of the this page
        if (DECAF_read_ptr(env, vma_curr + OFFSET_PROFILE.vma_vm_file, &vma_file) < 0 || !vma_file)
            goto next;

        // dentry extraction from the struct* file
        if (DECAF_read_ptr(env, vma_file + OFFSET_PROFILE.file_dentry, &f_dentry) < 0 || !f_dentry)
            goto next;


        // read small names form the dentry
        if (DECAF_read_mem(env, f_dentry + OFFSET_PROFILE.dentry_d_iname, 32, name) < 0)
            goto next;


        // inode struct extraction from the struct* file
        if (DECAF_read_ptr(env, f_dentry + OFFSET_PROFILE.file_inode, &f_inode) < 0 || !f_inode)
            goto next;

        // inode_number extraction
        if (DECAF_read_ptr(env, f_inode + OFFSET_PROFILE.inode_ino ,&inode_number) < 0 || !inode_number)
            goto next;

        name[31] = '\0';	// truncate long string


        // name is invalid, move on the data structure
        if (strlen(name)==0)
            goto next;

        DECAF_printf("%s ", name);


        if (!strcmp(last_mod_name.c_str(), name))
        {
            // extending the module
            if(last_vm_end == vma_vm_start)
            {
                assert(mod);
                target_ulong new_size = vma_vm_end - mod_vm_start;
                if (mod->size < new_size)
                    mod->size = new_size;
            }
            // This is a special case when the data struct is BEING populated
            goto next;
        }

        char key[32+32];
        //not extending, a different module
        mod_vm_start = vma_vm_start;

        sprintf(key, "%u_%s", inode_number, name);
        mod = VMI_find_module_by_key(key);
        module_bases.insert(vma_vm_start);
        if (!mod)
        {
            mod = new module();
            strncpy(mod->name, name, 31);
            mod->name[31] = '\0';
            mod->size = vma_vm_end - vma_vm_start;
            mod->inode_number = inode_number;
            mod->symbols_extracted = 0;
            VMI_add_module(mod, key);
        }

        if(VMI_find_module_by_base(proc->cr3, vma_vm_start) != mod)
        {
            VMI_insert_module(proc->pid, mod_vm_start , mod);
        }
        

next:
        DECAF_printf("\n");
        if (DECAF_read_ptr(env, vma_curr + OFFSET_PROFILE.vma_vm_next, &vma_next) < 0)
            break;

        if (vma_next == NULL)
        {
            break;
        }

        vma_curr = vma_next;
        last_mod_name = name;
        if (mod != NULL)
        {
            last_vm_start = vma_vm_start;
            last_vm_end = vma_vm_end;
        }
    }


    unordered_map<uint32_t, module *>::iterator iter = proc->module_list.begin();
    set<target_ulong> bases_to_remove;
    for(; iter!=proc->module_list.end(); iter++)
    {
        //DEBUG-only
        //monitor_printf(default_mon,"module %s base %08x \n",iter->second->name,iter->first);
        if (module_bases.find(iter->first) == module_bases.end())
            bases_to_remove.insert(iter->first);
    }

    set<target_ulong>::iterator iter2;
    for (iter2=bases_to_remove.begin(); iter2!=bases_to_remove.end(); iter2++)
    {
        VMI_remove_module(proc->pid, *iter2);
    }
}

//New process callback function

static void new_proc_callback(DECAF_Callback_Params* params)
{
    CPUState *env = params->bb.env;
    target_ulong pc = DECAF_getPC(env);
    if(OFFSET_PROFILE.proc_exec_connector != pc &&OFFSET_PROFILE.proc_fork_connector != pc)
        return;

    traverse_task_struct_add(env);
}

//Process exit callback function
static void proc_end_callback(DECAF_Callback_Params *params)
{

    CPUState *env = params->bb.env;

    target_ulong pc = DECAF_getPC(env);

    if(OFFSET_PROFILE.proc_exit_connector != pc)
        return;
    traverse_task_struct_remove(env);
}

// Callback corresponding to `vma_link`,`vma_adjust` & `remove_vma`
// This marks the `modules_extracted` for the process `false`
void VMA_update_func_callback(DECAF_Callback_Params *params)
{
    CPUState *env = params->bb.env;

    target_ulong pc = DECAF_getPC(env);

    if(!(pc == OFFSET_PROFILE.vma_link) && !(pc == OFFSET_PROFILE.vma_adjust) && !(pc == OFFSET_PROFILE.remove_vma))
        return;

    uint32_t pgd =  DECAF_getPGD(env);
    process *proc = NULL;

    proc = VMI_find_process_by_pgd(pgd);

    if(proc)
        proc->modules_extracted = false;
}

// TLB miss callback
// This callback is only used for updating modules when users have registered for either a
// module loaded/unloaded callback.
void Linux_tlb_call_back(DECAF_Callback_Params *temp)
{
    CPUState *ourenv = temp->tx.env;
    uint32_t pgd = -1;
    process *proc = NULL;

    // Check too see if any callbacks are registered
    if(!VMI_is_MoudleExtract_Required())
    {
        return;
    }
	
    // The first time we register for some VMA related callbacks
    if(first)
    {
        monitor_printf(cur_mon,"Registered for VMA update callbacks!\n");
        DECAF_registerOptimizedBlockBeginCallback(&VMA_update_func_callback, NULL, OFFSET_PROFILE.vma_adjust, OCB_CONST);
        DECAF_registerOptimizedBlockBeginCallback(&VMA_update_func_callback, NULL, OFFSET_PROFILE.vma_link, OCB_CONST);
        DECAF_registerOptimizedBlockBeginCallback(&VMA_update_func_callback, NULL, OFFSET_PROFILE.remove_vma, OCB_CONST);
        first = 0;
    }

    pgd = DECAF_getPGD(ourenv);
    proc = VMI_find_process_by_pgd(pgd);

    // Traverse memory map for a process if required.
    if (proc && !proc->modules_extracted)
    {
        traverse_mmap(ourenv, proc);
    }
}

//zyw
target_ulong mips_get_cur_pid(CPUState *env, char *proc_name)
{
//not use tulInitTaskAddr
	ProcInfo offset_profile = {"VMI"};
	target_ulong pid = 0;
	target_ulong current_task_addr;
	target_ulong _thread_info = DECAF_getESP(env) & ~ (guestOS_THREAD_SIZE - 1);
	//target_ulong _thread_info = ((CPUMIPSState *)env->env_ptr)->active_tc.gpr[28];
	//target_ulong tulInitTaskAddr = findTaskStructFromThreadInfo(env, _thread_info, &offset_profile, 0);
	DECAF_read_ptr(env, _thread_info + OFFSET_PROFILE.ti_task, &current_task_addr);
	//printf("thread_info_addr:%x, task_addr:%x, ts_pid:%x\n",_thread_info,current_task_addr,OFFSET_PROFILE.ts_pid);
	DECAF_read_ptr(env, current_task_addr + OFFSET_PROFILE.ts_pid, &pid);
	DECAF_read_mem(env, current_task_addr + OFFSET_PROFILE.ts_comm, SIZEOF_COMM, proc_name);
	return pid;
}
	
//zyw
/*
target_ulong mips_get_cur_pgd(CPUState *env)
{
	ProcInfo offset_profile = {"VMI"};
	target_ulong mm, task_pgd, proc_cr3;
	target_ulong _thread_info = DECAF_getESP(env) & ~ (guestOS_THREAD_SIZE - 1);	
	target_ulong tulInitTaskAddr = findTaskStructFromThreadInfo(env, _thread_info, &offset_profile, 0);
	DECAF_read_ptr(env, tulInitTaskAddr + OFFSET_PROFILE.ts_mm,
                                &mm);
	DECAF_read_ptr(env, mm + OFFSET_PROFILE.mm_pgd,
                                    &task_pgd);
	return task_pgd;
	
}



target_ulong mips_get_cur_cr3(CPUState *env)
{
	ProcInfo offset_profile = {"VMI"};
	target_ulong mm, task_pgd, proc_cr3;
	target_ulong _thread_info = DECAF_getESP(env) & ~ (guestOS_THREAD_SIZE - 1);	
	target_ulong tulInitTaskAddr = findTaskStructFromThreadInfo(env, _thread_info, &offset_profile, 0);
	DECAF_read_ptr(env, tulInitTaskAddr + OFFSET_PROFILE.ts_mm,
                                &mm);
	DECAF_read_ptr(env, mm + OFFSET_PROFILE.mm_pgd,
                                    &task_pgd);
	proc_cr3 = DECAF_get_phys_addr(env, task_pgd);
	return proc_cr3;
	
}
*/

target_ulong kernel_fatal_signal = 0;
// to see whether this is a Linux or not,
// the trick is to check the init_thread_info, init_task
int find_linux(CPUState *env, uintptr_t insn_handle)
{
    target_ulong _thread_info = DECAF_getESP(env) & ~ (guestOS_THREAD_SIZE - 1);
    static target_ulong _last_thread_info = 0;

// if current address is tested before, save time and do not try it again
    if (_thread_info == _last_thread_info || _thread_info <= 0x80000000)
        return 0;
// first time run
    if (_last_thread_info == 0)
    {
// memset(&OFFSET_PROFILE.init_task_addr, -1, sizeof(ProcInfo) - sizeof(OFFSET_PROFILE.strName));
    }

    _last_thread_info = _thread_info;

    if(0 != load_proc_info(env, _thread_info, OFFSET_PROFILE))
    {
        return 0;
    }

    //monitor_printf(cur_mon, "swapper task @ [%08x] \n", OFFSET_PROFILE.init_task_addr);
    kernel_fatal_signal = OFFSET_PROFILE.kernel_fatal_signal;
    VMI_guest_kernel_base = 0xc0000000;

    return (1);
}



// when we know this is a linux
void linux_vmi_init()
{ 	
	DECAF_registerOptimizedBlockBeginCallback(&new_proc_callback, NULL, OFFSET_PROFILE.proc_exec_connector, OCB_CONST);
	//DECAF_registerOptimizedBlockBeginCallback(&new_kmod_callback, NULL, OFFSET_PROFILE.trim_init_extable, OCB_CONST);
	DECAF_registerOptimizedBlockBeginCallback(&proc_end_callback, NULL, OFFSET_PROFILE.proc_exit_connector, OCB_CONST);
    //DECAF_register_callback(DECAF_TLB_EXEC_CB, Linux_tlb_call_back, NULL);

	process *kernel_proc = new process();
	kernel_proc->cr3 = 0;
	strcpy(kernel_proc->name, "<kernel>");
	kernel_proc->pid = 0;
	VMI_create_process(kernel_proc);
}

/*
gpa_t mips_get_cur_pgd(CPUState *env)
{
    const target_ulong MIPS_KERNEL_BASE = 0x80000000;
    gpa_t pgd = 0;
    if(0 == OFFSET_PROFILE.mips_pgd_current)
    {
        //monitor_printf(cur_mon, "Error\nmips_get_cur_pgd: read pgd before procinfo is populated.\n");
        return 0;
    }

    DECAF_read_ptr(env,
                   OFFSET_PROFILE.mips_pgd_current,
                   &pgd);
    pgd &= ~MIPS_KERNEL_BASE;
    return pgd;
}
*/

//ldl_phys first argument need to be env->as

static struct {
    target_ulong pgd_current_p;
    int softshift;
} linux_pte_info = {0};


#if defined(TARGET_MIPS)
static void mips_init_pte_info(CPUState *env)
{
    if (unlikely(linux_pte_info.pgd_current_p == 0)) {
        int i;
        uint32_t lui_ins, lw_ins, srl_ins;
        uint32_t address;
        uint32_t ebase;

        /*
         * The exact TLB refill code varies depeing on the kernel version
         * and configuration. Examins the TLB handler to extract
         * pgd_current_p and the shift required to convert in memory PTE
         * to TLB format
         */
        static struct {
            struct {
                uint32_t off;
                uint32_t op;
                uint32_t mask;
            } lui, lw, srl;
        } handlers[] = {
            /* 2.6.29+ */
            {
                {0x00, 0x3c1b0000, 0xffff0000}, /* 0x3c1b803f : lui k1,%hi(pgd_current_p) */
                {0x08, 0x8f7b0000, 0xffff0000}, /* 0x8f7b3000 : lw  k1,%lo(k1) */
                {0x34, 0x001ad182, 0xffffffff}  /* 0x001ad182 : srl k0,k0,0x6 */
            },
            /* 3.4+ */
            {
                {0x00, 0x3c1b0000, 0xffff0000}, /* 0x3c1b803f : lui k1,%hi(pgd_current_p) */
                {0x08, 0x8f7b0000, 0xffff0000}, /* 0x8f7b3000 : lw  k1,%lo(k1) */
                {0x34, 0x001ad142, 0xffffffff}  /* 0x001ad182 : srl k0,k0,0x5 */
            }
        };

	ebase = ((CPUArchState *)env->env_ptr)->CP0_EBase - 0x80000000;

        /* Match the kernel TLB refill exception handler against known code */
        for (i = 0; i < sizeof(handlers)/sizeof(handlers[0]); i++) {
            lui_ins = ldl_phys(env->as, ebase + handlers[i].lui.off);
            lw_ins = ldl_phys(env->as, ebase + handlers[i].lw.off);
            srl_ins = ldl_phys(env->as, ebase + handlers[i].srl.off);
            if (((lui_ins & handlers[i].lui.mask) == handlers[i].lui.op) &&
                ((lw_ins & handlers[i].lw.mask) == handlers[i].lw.op) &&
                ((srl_ins & handlers[i].srl.mask) == handlers[i].srl.op))
                break;
        }
        if (i >= sizeof(handlers)/sizeof(handlers[0])) {
                printf("TLBMiss handler dump:\n");
            for (i = 0; i < 0x80; i+= 4)
                //printf("0x%08x: 0x%08x\n", ebase + i, ldl_phys(env->as, ebase + i));
            cpu_abort(env, "TLBMiss handler signature not recognised\n");
        }
        address = (lui_ins & 0xffff) << 16;
        address += (((int32_t)(lw_ins & 0xffff)) << 16) >> 16;
        if (address >= 0x80000000 && address < 0xa0000000)
            address -= 0x80000000;
        else if (address >= 0xa0000000 && address <= 0xc0000000)
            address -= 0xa0000000;
        else
            cpu_abort(env, "pgd_current_p not in KSEG0/KSEG1\n");

        linux_pte_info.pgd_current_p = address;
        linux_pte_info.softshift = (srl_ins >> 6) & 0x1f;
    }
}

gpa_t mips_get_cur_pgd(CPUState *env)
{
    target_ulong pgd;

    mips_init_pte_info(env);

    /* Get pgd_current */
    pgd = ldl_phys(env->as, linux_pte_info.pgd_current_p);
    if (pgd >= 0x80000000 && pgd < 0xa0000000) {
        return pgd - 0x80000000;
    }
    if (pgd >= 0xa0000000 && pgd < 0xc0000000) {
        return pgd - 0xa0000000;
    }
    cpu_abort(env, "current PGD not in KSEG0/KSEG1\n");
}

int mips_get_pte_softshift(CPUState *env)
{
    mips_init_pte_info(env);
    return linux_pte_info.softshift;
}
#endif

//zyw
extern target_ulong code_start;
extern target_ulong code_end;

void traverse_mmap_new(CPUState *env, void *opaque, FILE *fp)
{
    process *proc = (process *)opaque;
    target_ulong mm, vma_curr, vma_file, f_dentry, f_inode, mm_mmap, vma_next, vma_prot, vma_flags=NULL;
    set<target_ulong> module_bases;
    unsigned int inode_number;
    target_ulong vma_vm_start = 0, vma_vm_end = 0;
    target_ulong last_vm_start = 0, last_vm_end = 0, mod_vm_start = 0;
    char name[32];  // module file path
    string last_mod_name;
    module *mod = NULL;
    if (DECAF_read_ptr(env, proc->EPROC_base_addr + OFFSET_PROFILE.ts_mm, &mm) < 0)
        return;
   
    if (DECAF_read_ptr(env, mm + OFFSET_PROFILE.mm_mmap, &mm_mmap) < 0)
        return;

    // Mark the `modules_extracted` true. This is done because this function calls `VMI_find_module_by_base`
    // and that function calls `traverse_mmap` if `modules_extracted` is false. We don't want to get into
    // an infinite recursion.

    proc->modules_extracted = true;

    if (-1UL == proc->cr3)
        return;


    // starting from the first vm_area, read vm_file. NOTICE vm_area_struct can be null
    if (( vma_curr = mm_mmap) == 0)
        return;
    
    int count = 0;
    while(true)
    {
        count ++;
        // read start of curr vma
        if (DECAF_read_ptr(env, vma_curr + OFFSET_PROFILE.vma_vm_start,  &vma_vm_start) < 0)
            goto next;
        // read end of curr vma
        if (DECAF_read_ptr(env, vma_curr + OFFSET_PROFILE.vma_vm_end,  &vma_vm_end) < 0)
            goto next;

        DECAF_printf("memory %x:%x ", vma_vm_start, vma_vm_end);    

//zyw obtain the memory area property
        if (DECAF_read_ptr(env, vma_curr + OFFSET_PROFILE.vma_vm_flags, &vma_flags) < 0)      
            goto next;

        DECAF_printf("%x ", vma_flags);
        fprintf(fp, "%x:", vma_vm_start);
        fprintf(fp, "%x:", vma_vm_end);
        fprintf(fp, "%x:", vma_flags);
        if(count == 1)
        {
            code_start = vma_vm_start;
            code_end = vma_vm_end;
        }

//
         
        

        // read the struct* file entry of the curr vma, used to then extract the dentry of the this page
        if (DECAF_read_ptr(env, vma_curr + OFFSET_PROFILE.vma_vm_file, &vma_file) < 0 || !vma_file)
            goto next;

        // dentry extraction from the struct* file
        if (DECAF_read_ptr(env, vma_file + OFFSET_PROFILE.file_dentry, &f_dentry) < 0 || !f_dentry)
            goto next;



        // read small names form the dentry
        if (DECAF_read_mem(env, f_dentry + OFFSET_PROFILE.dentry_d_iname, 32, name) < 0)
            goto next;
            
        // inode struct extraction from the struct* file
        if (DECAF_read_ptr(env, f_dentry + OFFSET_PROFILE.file_inode, &f_inode) < 0 || !f_inode)
            goto next;

        // inode_number extraction
        if (DECAF_read_ptr(env, f_inode + OFFSET_PROFILE.inode_ino, &inode_number) < 0 || !inode_number)
            goto next;

        name[31] = '\0';    // truncate long string

        // name is invalid, move on the data structure
        if (strlen(name)==0)
            goto next;

        fprintf(fp, "%s", name);
        DECAF_printf("%s ", name);

        
        if (!strcmp(last_mod_name.c_str(), name))
        {
            // extending the module
            if(last_vm_end == vma_vm_start)
            {
                assert(mod);
                target_ulong new_size = vma_vm_end - mod_vm_start;
                if (mod->size < new_size)
                    mod->size = new_size;
            }
            // This is a special case when the data struct is BEING populated
            goto next;
        }

        char key[32+32];
        //not extending, a different module
        mod_vm_start = vma_vm_start;

        sprintf(key, "%u_%s", inode_number, name);
        mod = VMI_find_module_by_key(key);
        module_bases.insert(vma_vm_start);
        if (!mod)
        {
            mod = new module();
            strncpy(mod->name, name, 31);
            mod->name[31] = '\0';
            mod->size = vma_vm_end - vma_vm_start;
            mod->inode_number = inode_number;
            mod->symbols_extracted = 0;
            VMI_add_module(mod, key);
        }

        if(VMI_find_module_by_base(proc->cr3, vma_vm_start) != mod)
        {
            VMI_insert_module(proc->pid, mod_vm_start , mod);
        }

next:
        fprintf(fp, "\n");
        DECAF_printf("\n");
                
        if (DECAF_read_ptr(env, vma_curr + OFFSET_PROFILE.vma_vm_next, &vma_next) < 0)
            break;

        if (vma_next == NULL)
        {
            break;
        }

        vma_curr = vma_next;
        last_mod_name = name;
        if (mod != NULL)
        {
            last_vm_start = vma_vm_start;
            last_vm_end = vma_vm_end;
        }
    }
   

    unordered_map<uint32_t, module *>::iterator iter = proc->module_list.begin();
    set<target_ulong> bases_to_remove;
    for(; iter!=proc->module_list.end(); iter++)
    {
        //DEBUG-only
        //monitor_printf(default_mon,"module %s base %08x \n",iter->second->name,iter->first);
        if (module_bases.find(iter->first) == module_bases.end())
            bases_to_remove.insert(iter->first);
    }

    set<target_ulong>::iterator iter2;
    for (iter2=bases_to_remove.begin(); iter2!=bases_to_remove.end(); iter2++)
    {
        VMI_remove_module(proc->pid, *iter2);
    }
}
