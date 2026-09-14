#ifndef QRR_FULL_TCG_H
#define QRR_FULL_TCG_H

#include <elf.h>

#ifdef __linux__
#include <sys/syscall.h>
typedef struct QrrFullOpenHow {
    uint64_t flags;
    uint64_t mode;
    uint64_t resolve;
} QrrFullOpenHow;
#define QRR_FULL_RESOLVE_NO_MAGICLINKS UINT64_C(0x02)
#define QRR_FULL_RESOLVE_IN_ROOT UINT64_C(0x10)
#if defined(SYS_openat2)
#define QRR_FULL_HOST_NR_OPENAT2 SYS_openat2
#elif defined(__x86_64__) || defined(__aarch64__)
#define QRR_FULL_HOST_NR_OPENAT2 437
#endif
#endif
#define QRR_FULL_RESULT_MAGIC "QEMU_RESULT_REPLAY\t1\tqemu-result-replay-v15"
#define QRR_FULL_RESULT_MAGIC_V14 "QEMU_RESULT_REPLAY\t1\tqemu-result-replay-v14"
#define QRR_FULL_RESULT_COLUMNS \
    "key\tpath_hash\tdep_hash\tsyscall_nr\tsequence\tret\tout_arg\tout_hex\tprocess_token\tthread_token"
#define QRR_FULL_RESULT_COLUMNS_V14 \
    "key\tpath_hash\tdep_hash\tsyscall_nr\tsequence\tret\tout_arg\tout_hex\tprocess_token"
#define QRR_FULL_SCHEDULE_MAGIC \
    "QEMU_RESULT_SCHEDULE\t1\tqemu-result-schedule-v2"
#define QRR_FULL_SCHEDULE_MAGIC_V1 \
    "QEMU_RESULT_SCHEDULE\t1\tqemu-result-schedule-v1"
#define QRR_FULL_SCHEDULE_COLUMNS \
    "global_sequence\tprocess_token\tthread_token\tsyscall_sequence\tsyscall_nr\tkey\tpath_hash\tdep_hash"
#define QRR_FULL_SCHEDULE_COLUMNS_V1 \
    "global_sequence\tprocess_token\tsyscall_sequence\tsyscall_nr\tkey\tpath_hash\tdep_hash"
#define QRR_FULL_EVENT_MAGIC \
    "QEMU_FULL_TCG_SYSCALL\t1\tqemu-full-tcg-syscall-v1"
#define QRR_FULL_EVENT_COLUMNS \
    "sequence\tkey\tpath_hash\tdep_hash\tsyscall_nr\tret\tout_arg\toutput_bytes\tpgd\tentry_pc\treturn_pc\tstack\ta1\ta2\ta3\ta4\tstatus\treason"
#define QRR_FULL_EXEC_MAGIC \
    "QEMU_FULL_TCG_EXEC\t1\tqemu-full-tcg-exec-v2"
#define QRR_FULL_EXEC_COLUMNS \
    "sequence\tpgd\tentry_pc\tsyscall_nr\targc\tfilename_hex\targv_nul_hex\tcwd_hex\tstatus\treason"
#define QRR_FULL_SIGNAL_MAGIC \
    "QEMU_RESULT_SIGNAL\t4\tqemu-result-signal-v4"
#define QRR_FULL_SIGNAL_COLUMNS \
    "process_token\tevent_sequence\tanchor_kind\tsyscall_key\tsyscall_sequence\tsyscall_nr\tpath_hash\tdep_hash\tedge_from_pc\tedge_to_pc\tedge_occurrence\tdelivery_pc\tinterrupted_pc\tinterrupted_sp\tdelay_slot\tsigno\tsi_code\tsi_errno\tsi_pid\tsi_uid\tsi_status\tsi_value\tfault_addr"
#define QRR_FULL_LAYOUT_MAGIC \
    "QEMU_RESULT_LAYOUT\t1\tqemu-result-layout-v3"
#define QRR_FULL_LAYOUT_COLUMNS \
    "process_token\trecord_sequence\trecord_kind\tstart\tend\tflags\tpgoff\tstart_brk\tinitial_brk\tstart_stack\tentry_pc\tinitial_sp\tauxv_hex\tstack_hex\tfile_hex\tcontent_hex"
#define QRR_FULL_MMAP_MAGIC \
    "QEMU_RESULT_MMAP\t1\tqemu-result-mmap-v7"
#define QRR_FULL_MMAP_COLUMNS \
    "process_token\tevent_sequence\trecord_kind\tmapping_id\tmmap_sequence\tmmap_key\tstart\tlength\tprot\tflags\tfd\tfile_offset\tpage_offset\tanchor_kind\tsyscall_key\tsyscall_sequence\tsyscall_nr\tfault_pc\tedge_from_pc\tedge_to_pc\tedge_occurrence\tdelivered_signal_sequence\tpath_hash\tdep_hash\taccess_kind\tdev\tinode\tpath_hex\tpage_hex\tdelay_slot"
#define QRR_FULL_FNV64_OFFSET UINT64_C(1469598103934665603)
#define QRR_FULL_FNV64_PRIME UINT64_C(1099511628211)
#define QRR_FULL_ROOT_PROCESS_PREFIX UINT64_C(0x8000000000000000)
#define QRR_FULL_CHILD_PROCESS_TAG UINT64_C(0x4348494c445f5152)
#define QRR_FULL_SIGNAL_DEP_TAG UINT64_C(0x5349474e414c5f51)
#define QRR_FULL_MMAP_DEP_TAG UINT64_C(0x4d4d41505f504147)
#define QRR_FULL_PATH_TAIL_LENGTH 16
#define QRR_FULL_DEFAULT_MAX_BLOB (64 * 1024 * 1024)
#define QRR_FULL_RESULT_OUT_ARG_BUNDLE 7
#define QRR_FULL_RESULT_OUT_ARG_MMAP 8
#define QRR_FULL_RESULT_OUT_ARG_EXEC_UNBIND 9
#define QRR_FULL_RESULT_OUT_ARG_EXEC_REBIND 10
#define QRR_FULL_RESULT_OUT_ARG_SHMAT 11
#define QRR_FULL_RESULT_OUT_ARG_EXEC_TERMINATE 12
#define QRR_FULL_SHMAT_VERSION 1
#define QRR_FULL_SHMAT_HEADER_SIZE 32
#define QRR_FULL_BUNDLE_VERSION 3
#define QRR_FULL_OUTPUT_DIRECT_ARG 1
#define QRR_FULL_OUTPUT_RECVMSG_IOV 2
#define QRR_FULL_OUTPUT_RECVMSG_NAME_DATA 6
#define QRR_FULL_OUTPUT_RECVMSG_CONTROL_DATA 7
#define QRR_FULL_OUTPUT_RECVMSG_FIELD 8
#define QRR_FULL_OUTPUT_INDIRECT_ARG 9
#define QRR_FULL_OUTPUT_SEMAPHORE_STATE 10
#define QRR_FULL_OUTPUT_MREMAP_EFFECT 11
#define QRR_FULL_OUTPUT_SECONDARY_RETURN 12
#define QRR_FULL_MREMAP_EFFECT_SNAPSHOT_VERSION 1
#define QRR_FULL_MIPS_NR_PIPE 4042
#define QRR_FULL_MIPS_NR_IPC 4117
#define QRR_FULL_IPCOP_SEMOP 1
#define QRR_FULL_IPCOP_SEMTIMEDOP 4
#define QRR_FULL_IPCOP_SEMCTL 3
#define QRR_FULL_SEMCTL_IPC_STAT 2
#define QRR_FULL_SEMCTL_IPC_INFO 3
#define QRR_FULL_SEMCTL_SEM_STAT 18
#define QRR_FULL_SEMCTL_SEM_INFO 19
#define QRR_FULL_SEMCTL_IPC_RMID 0
#define QRR_FULL_TARGET_SEMBUF_SIZE 6
#define QRR_FULL_MIPS_SEMID64_DS_SIZE (14 * TARGET_LONG_SIZE)
#define QRR_FULL_TARGET_SEMINFO_SIZE (10 * QRR_FULL_ABI_INT_SIZE)
#define QRR_FULL_TARGET_WAIT_STATUS_SIZE QRR_FULL_ABI_INT_SIZE
#define QRR_FULL_TARGET_RUSAGE_SIZE (18 * TARGET_LONG_SIZE)
/* Linux UAPI struct sysinfo is 64 bytes for the MIPS/ARM 32-bit ABIs used
 * by the firmware corpus.  Keep the expression ABI-sized so a future
 * 64-bit collector gets the corresponding 104-byte layout. */
#define QRR_FULL_TARGET_SYSINFO_SIZE (10 * TARGET_LONG_SIZE + 24)
#define QRR_FULL_TARGET_IFREQ_SIZE (TARGET_LONG_SIZE == 8 ? 40 : 32)
#define QRR_FULL_QEMU_ESIGRETURN 513
#define QRR_FULL_ABI_LONG_SIZE ((size_t)TARGET_LONG_SIZE)
#define QRR_FULL_ABI_INT_SIZE 4
#define QRR_FULL_MIPS_THREAD_SIZE 8192
#define QRR_FULL_MIPS_PT_REGS_SP_OFFSET 0x8c
#define QRR_FULL_MIPS_PT_REGS_CAUSE_OFFSET 0xa8
#define QRR_FULL_MIPS_PT_REGS_EPC_OFFSET 0xac
#define QRR_FULL_MIPS_CAUSE_BD 0x80000000U
#define QRR_FULL_MIPS_SIGINFO_CODE_OFFSET 4
#define QRR_FULL_MIPS_SIGINFO_ERRNO_OFFSET 8
#define QRR_FULL_MIPS_SIGINFO_UNION_OFFSET 12
#define QRR_FULL_VM_FAULT_ERROR 0x33
#define QRR_FULL_MIPS_SIGIO 22
#define QRR_FULL_LINUX_CLONE_THREAD UINT32_C(0x00010000)
#define QRR_FULL_ALIGN_UP(value, align) \
    (((value) + (align) - 1) & ~((align) - 1))
#define QRR_FULL_MSG_NAME_OFF 0
#define QRR_FULL_MSG_NAMELEN_OFF \
    (QRR_FULL_MSG_NAME_OFF + QRR_FULL_ABI_LONG_SIZE)
#define QRR_FULL_MSG_IOV_OFF \
    QRR_FULL_ALIGN_UP(QRR_FULL_MSG_NAMELEN_OFF + QRR_FULL_ABI_INT_SIZE, \
                      QRR_FULL_ABI_LONG_SIZE)
#define QRR_FULL_MSG_IOVLEN_OFF \
    (QRR_FULL_MSG_IOV_OFF + QRR_FULL_ABI_LONG_SIZE)
#define QRR_FULL_MSG_CONTROL_OFF \
    (QRR_FULL_MSG_IOVLEN_OFF + QRR_FULL_ABI_LONG_SIZE)
#define QRR_FULL_MSG_CONTROLLEN_OFF \
    (QRR_FULL_MSG_CONTROL_OFF + QRR_FULL_ABI_LONG_SIZE)
#define QRR_FULL_MSG_FLAGS_OFF \
    (QRR_FULL_MSG_CONTROLLEN_OFF + QRR_FULL_ABI_LONG_SIZE)
#define QRR_FULL_IOV_BASE_OFF 0
#define QRR_FULL_IOV_LEN_OFF QRR_FULL_ABI_LONG_SIZE
#define QRR_FULL_IOV_SIZE (2 * QRR_FULL_ABI_LONG_SIZE)

typedef struct QrrFullPathState {
    target_ulong pgd;
    target_ulong task;
    uint64_t thread_token;
    uint64_t process_token;
    uint64_t next_fork_ordinal;
    uint64_t path_tail[QRR_FULL_PATH_TAIL_LENGTH];
    unsigned int path_tail_count;
    unsigned int path_tail_next;
    uint64_t previous_tb;
    bool have_previous_tb;
    target_ulong previous_user_edge_pc;
    bool have_previous_user_edge_pc;
    bool have_interrupted_user_edge;
    target_ulong interrupted_edge_from_pc;
    target_ulong interrupted_tb_pc;
    target_ulong interrupted_next_pc;
    uint64_t syscall_site_tail[QRR_FULL_PATH_TAIL_LENGTH];
    unsigned int syscall_site_tail_count;
    unsigned int syscall_site_tail_next;
    uint64_t last_syscall;
    uint64_t syscall_seq;
    uint64_t signal_seq;
    uint64_t mmap_event_seq;
    struct QrrFullPathState *next;
} QrrFullPathState;

typedef struct QrrFullUserEdgeCount {
    target_ulong pgd;
    target_ulong task;
    target_ulong from_pc;
    target_ulong to_pc;
    uint64_t occurrence;
    struct QrrFullUserEdgeCount *next;
} QrrFullUserEdgeCount;

typedef struct QrrFullUserPrecisionWatch {
    target_ulong pgd;
    target_ulong task;
    target_ulong edge_from_pc;
    target_ulong pc;
    uint64_t baseline_syscall_sequence;
    uint64_t baseline_occurrence;
    bool delay_slot;
    struct QrrFullUserPrecisionWatch *next;
} QrrFullUserPrecisionWatch;

typedef struct QrrFullTbPending {
    CPUState *cpu;
    target_ulong pgd;
    target_ulong task;
    target_ulong tb_pc;
    uint32_t tb_size;
    target_ulong edge_from_pc;
    uint64_t edge_occurrence;
    bool have_delay_edge;
    target_ulong delay_edge_from_pc;
    target_ulong delay_edge_to_pc;
    uint64_t delay_edge_occurrence;
    struct QrrFullTbPending *next;
} QrrFullTbPending;

typedef struct QrrFullCpuThread {
    CPUState *cpu;
    target_ulong pgd;
    target_ulong task;
    struct QrrFullCpuThread *next;
} QrrFullCpuThread;

typedef struct QrrFullTargetPgd {
    target_ulong pgd;
    uint64_t process_token;
    target_ulong task;
    uint32_t tgid;
    bool have_task;
    bool exec_transitioning;
    uint64_t next_thread_ordinal;
    struct QrrFullTargetPgd *next;
} QrrFullTargetPgd;

typedef struct QrrFullThreadIdentity {
    target_ulong pgd;
    target_ulong task;
    uint32_t tgid;
    uint64_t process_token;
    uint64_t ordinal;
    uint64_t thread_token;
    struct QrrFullThreadIdentity *next;
} QrrFullThreadIdentity;

typedef struct QrrFullScheduleEvent {
    uint64_t process_token;
    uint64_t thread_token;
    uint64_t syscall_sequence;
    int syscall_nr;
    uint64_t key;
    uint64_t path_hash;
    uint64_t dep_hash;
    bool committed;
    struct QrrFullScheduleEvent *next;
} QrrFullScheduleEvent;

typedef struct QrrFullPending {
    target_ulong pgd;
    target_ulong task;
    uint64_t thread_token;
    target_ulong entry_pc;
    target_ulong stack;
    uint32_t tgid;
    int syscall_nr;
    uint64_t key;
    uint64_t path_hash;
    uint64_t dep_hash;
    uint64_t sequence;
    /* One QRR row describes one logical syscall.  A signal may make Linux
     * execute the same user syscall instruction again before this pending
     * operation returns.  Those entries are attempts of this identity, not
     * new syscalls, and therefore must not advance the path/sequence state. */
    uint64_t logical_syscall_id;
    uint64_t attempt_count;
    uint64_t process_token;
    target_ulong args[6];
    char *open_path;
    target_ulong semaphore_array;
    uint32_t *semaphore_values;
    size_t semaphore_nsems;
    QrrFullScheduleEvent *schedule_event;
    struct QrrFullPending *next;
} QrrFullPending;

typedef struct QrrFullFdPath {
    target_ulong pgd;
    int fd;
    char *path;
    struct QrrFullFdPath *next;
} QrrFullFdPath;

struct QrrFullMmapMapping;

typedef struct QrrFullForkPending {
    CPUState *cpu;
    target_ulong source_pgd;
    target_ulong source_task;
    target_ulong entry_pc;
    target_ulong stack;
    uint64_t child_process_token;
    bool have_path_state;
    QrrFullPathState path_state;
    QrrFullFdPath *fd_paths;
    struct QrrFullMmapMapping *mmap_mappings;
    struct QrrFullForkPending *next;
} QrrFullForkPending;

typedef struct QrrFullProcessIdentity {
    target_ulong pgd;
    uint32_t pid;
    uint32_t parent_pid;
    struct QrrFullProcessIdentity *next;
} QrrFullProcessIdentity;

typedef struct QrrFullBuffer {
    unsigned char *data;
    size_t len;
    size_t cap;
    uint16_t outputs;
    size_t payload_bytes;
} QrrFullBuffer;

typedef struct QrrFullExecPending {
    CPUState *cpu;
    target_ulong pgd;
    target_ulong entry_pc;
    target_ulong stack;
    uint32_t pid;
    bool have_pid;
    target_ulong thread_info;
    bool have_thread_info;
    target_ulong task;
    uint64_t process_token;
    uint64_t thread_token;
    bool have_task;
    int syscall_nr;
    uint32_t argc;
    char *filename_hex;
    char *argv_hex;
    char capture_error[128];
    bool target_match;
    bool source_was_target;
    struct QrrFullExecPending *next;
} QrrFullExecPending;

typedef struct QrrFullSignalCall {
    CPUState *cpu;
    target_ulong pgd;
    target_ulong info_ptr;
    target_ulong regs_ptr;
    target_ulong return_pc;
    struct QrrFullSignalCall *next;
} QrrFullSignalCall;

typedef struct QrrFullSemaphoreLockCall {
    CPUState *cpu;
    target_ulong pgd;
    target_ulong return_pc;
    QrrFullPending *pending;
    struct QrrFullSemaphoreLockCall *next;
} QrrFullSemaphoreLockCall;

typedef struct QrrFullLayoutCaptured {
    uint64_t process_token;
    bool captured;
    struct QrrFullLayoutCaptured *next;
} QrrFullLayoutCaptured;

typedef struct QrrFullMmapPage {
    target_ulong page_offset;
    bool present_at_mmap;
    bool present_at_mremap;
    bool materialized_by_fault;
    struct QrrFullMmapPage *next;
} QrrFullMmapPage;

#define QRR_FULL_MMAP_SNAPSHOT_ACCESS "snapshot"

typedef struct QrrFullMmapMapping {
    target_ulong pgd;
    uint64_t process_token;
    uint64_t mapping_id;
    uint64_t mmap_sequence;
    uint64_t mmap_key;
    target_ulong start;
    target_ulong length;
    target_ulong prot;
    target_ulong flags;
    int fd;
    uint64_t file_offset;
    char *path;
    QrrFullMmapPage *pages;
    struct QrrFullMmapMapping *next;
} QrrFullMmapMapping;

typedef struct QrrFullPageFaultCall {
    CPUState *cpu;
    target_ulong pgd;
    target_ulong task;
    uint64_t process_token;
    QrrFullMmapMapping *mapping;
    target_ulong address;
    target_ulong regs_ptr;
    target_ulong fault_epc;
    target_ulong fault_pc;
    uint32_t fault_cause;
    uint64_t syscall_key;
    uint64_t syscall_sequence;
    int syscall_nr;
    target_ulong edge_from_pc;
    target_ulong edge_to_pc;
    uint64_t edge_occurrence;
    uint64_t delivered_signal_sequence;
    uint64_t path_hash;
    uint64_t dep_hash;
    target_ulong do_page_fault_return_pc;
    target_ulong handle_mm_fault_return_pc;
    const char *access_kind;
    bool syscall_anchor;
    bool handle_mm_fault_active;
    struct QrrFullPageFaultCall *next;
} QrrFullPageFaultCall;

static int qrr_full_initialized;
static bool qrr_full_enabled;
static bool qrr_full_all_pgds;
static bool qrr_full_follow_fork_descendants;
static const char *qrr_full_target_name;
static size_t qrr_full_max_blob = QRR_FULL_DEFAULT_MAX_BLOB;
static FILE *qrr_full_table_fp;
static FILE *qrr_full_schedule_fp;
static FILE *qrr_full_event_fp;
static FILE *qrr_full_exec_fp;
static FILE *qrr_full_signal_fp;
static FILE *qrr_full_layout_fp;
static FILE *qrr_full_mmap_fp;
static uint64_t qrr_full_exec_sequence;
static QrrFullScheduleEvent *qrr_full_schedule_head;
static QrrFullScheduleEvent *qrr_full_schedule_tail;
static QrrFullPathState *qrr_full_paths;
static QrrFullTargetPgd *qrr_full_target_pgds;
static QrrFullThreadIdentity *qrr_full_threads;
static bool qrr_full_thread_context;
static QrrFullPending *qrr_full_pending_head;
static QrrFullFdPath *qrr_full_fd_paths;
static QrrFullProcessIdentity *qrr_full_process_identities;
static QrrFullExecPending *qrr_full_exec_pending;
static QrrFullForkPending *qrr_full_fork_pending;
static QrrFullSignalCall *qrr_full_signal_calls;
static QrrFullSemaphoreLockCall *qrr_full_semaphore_lock_calls;
static QrrFullLayoutCaptured *qrr_full_layout_captured;
static QrrFullMmapMapping *qrr_full_mmap_mappings;
static QrrFullPageFaultCall *qrr_full_page_fault_calls;
static QrrFullUserEdgeCount *qrr_full_user_edge_counts;
static QrrFullUserPrecisionWatch *qrr_full_user_precision_watches;
static bool qrr_full_user_precision_flush_pending;
static bool qrr_full_debug_precision_edges;
static QrrFullTbPending *qrr_full_tb_pending;
static QrrFullCpuThread *qrr_full_cpu_threads;
static target_ulong qrr_full_last_kernel_thread_info;
static bool qrr_full_have_last_kernel_thread_info;
static const char *qrr_full_rootfs_path;
static uint64_t qrr_full_next_root_process_ordinal;
static uint64_t qrr_full_next_mapping_id;
static target_ulong qrr_full_get_signal_to_deliver;
static target_ulong qrr_full_do_signal;
static target_ulong qrr_full_do_notify_resume;
static target_ulong qrr_full_proc_exec_connector;
static target_ulong qrr_full_proc_exit_connector;
static target_ulong qrr_full_proc_fork_connector;
static target_ulong qrr_full_init_task;
static target_ulong qrr_full_pgd_current;
static target_ulong qrr_full_ipc_lock_check;
static target_ulong qrr_full_do_page_fault;
static target_ulong qrr_full_handle_mm_fault;

static char *qrr_full_hex_from_bytes(const unsigned char *bytes,
                                     size_t length);
static QrrFullExecPending *qrr_full_exec_pending_for_task(
    target_ulong task);
static void qrr_full_remove_exec_pending(QrrFullExecPending *pending);
static bool qrr_full_record_terminal_exec(target_ulong source_pgd,
                                          target_ulong task);
static void qrr_full_complete_exec_transition(CPUState *cpu,
                                              QrrFullExecPending *pending,
                                              target_ulong pgd,
                                              const char *completion);
static void qrr_full_note_current_target_task(CPUState *cpu,
                                              target_ulong pgd);
static target_ulong qrr_full_current_pgd(CPUState *cpu);
static target_ulong qrr_full_sem_array_base_offset;
static target_ulong qrr_full_sem_array_nsems_offset;
static target_ulong qrr_full_sem_size;
static target_ulong qrr_full_sem_value_offset;
static target_ulong qrr_full_selected_pgd;

static target_ulong qrr_full_selected_task;
static bool qrr_full_target_locked;
static bool qrr_full_target_active;

static void qrr_full_clone_process_state(target_ulong source_pgd,
                                         target_ulong source_task,
                                         target_ulong target_pgd);
static void qrr_full_fd_remove_all(target_ulong pgd);
static void qrr_full_unbind_process(target_ulong pgd,
                                    const char *process_name);
static void qrr_full_unbind_process_token(uint64_t process_token,
                                          const char *reason);
static void qrr_full_note_signal_delivery(CPUState *cpu, target_ulong pc);
static void qrr_full_note_semaphore_lock(CPUState *cpu, target_ulong pc);
static void qrr_full_note_page_fault(CPUState *cpu, target_ulong pc);
static QrrFullPending *qrr_full_pending_find_task(target_ulong pgd,
                                                  target_ulong task);
static bool qrr_full_read_target_u32(CPUState *cpu, target_ulong address,
                                     uint32_t *value);
static void qrr_full_capture_initial_layout(CPUState *cpu, target_ulong pgd,
                                            target_ulong entry_pc,
                                            target_ulong initial_sp);

static uint64_t qrr_full_hash_mix_u64(uint64_t hash, uint64_t value)
{
    int i;

    for (i = 0; i < 8; i++) {
        hash ^= (value >> (i * 8)) & 0xff;
        hash *= QRR_FULL_FNV64_PRIME;
    }
    return hash;
}

static uint64_t qrr_full_result_key(uint64_t path_hash, uint64_t dep_hash,
                                    uint64_t syscall_nr)
{
    uint64_t key = QRR_FULL_FNV64_OFFSET;

    key = qrr_full_hash_mix_u64(key, path_hash);
    key = qrr_full_hash_mix_u64(key, dep_hash);
    return qrr_full_hash_mix_u64(key, syscall_nr);
}

static uint16_t qrr_full_elf16(uint16_t value, bool swap)
{
    return swap ? ((value >> 8) | (value << 8)) : value;
}

static uint32_t qrr_full_elf32(uint32_t value, bool swap)
{
    if (!swap) {
        return value;
    }
    return ((value & UINT32_C(0x000000ff)) << 24) |
           ((value & UINT32_C(0x0000ff00)) << 8) |
           ((value & UINT32_C(0x00ff0000)) >> 8) |
           ((value & UINT32_C(0xff000000)) >> 24);
}

static bool qrr_full_read_at(FILE *fp, long offset, void *buffer,
                             size_t length)
{
    return offset >= 0 && fseek(fp, offset, SEEK_SET) == 0 &&
           fread(buffer, 1, length, fp) == length;
}

static bool qrr_full_resolve_kernel_symbols(const char *path,
                                            bool need_signals)
{
    static const char *names[] = {
        "get_signal_to_deliver", "do_signal", "do_notify_resume",
        "proc_exec_connector", "proc_exit_connector", "init_task",
        "pgd_current", "ipc_lock_check", "do_page_fault",
        "handle_mm_fault", "proc_fork_connector"
    };
    target_ulong values[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Elf32_Ehdr ehdr;
    FILE *fp = NULL;
    bool swap;
    uint32_t shoff;
    uint16_t shentsize;
    uint16_t shnum;
    unsigned int section_index;
    bool ok = false;

    fp = fopen(path, "rb");
    if (!fp) {
        fprintf(stderr, "qrr-full: cannot open signal vmlinux %s: %s\n",
                path, strerror(errno));
        return false;
    }
    if (fread(&ehdr, 1, sizeof(ehdr), fp) != sizeof(ehdr) ||
        memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0 ||
        ehdr.e_ident[EI_CLASS] != ELFCLASS32 ||
        (ehdr.e_ident[EI_DATA] != ELFDATA2LSB &&
         ehdr.e_ident[EI_DATA] != ELFDATA2MSB)) {
        fprintf(stderr, "qrr-full: signal vmlinux is not a valid ELF32 file: %s\n",
                path);
        goto out;
    }
#ifdef HOST_WORDS_BIGENDIAN
    swap = ehdr.e_ident[EI_DATA] == ELFDATA2LSB;
#else
    swap = ehdr.e_ident[EI_DATA] == ELFDATA2MSB;
#endif
    if (qrr_full_elf16(ehdr.e_machine, swap) != EM_MIPS) {
        fprintf(stderr, "qrr-full: signal vmlinux is not MIPS: %s\n", path);
        goto out;
    }
    shoff = qrr_full_elf32(ehdr.e_shoff, swap);
    shentsize = qrr_full_elf16(ehdr.e_shentsize, swap);
    shnum = qrr_full_elf16(ehdr.e_shnum, swap);
    if (!shoff || shentsize != sizeof(Elf32_Shdr) || !shnum) {
        fprintf(stderr, "qrr-full: signal vmlinux has no usable section table: %s\n",
                path);
        goto out;
    }
    for (section_index = 0; section_index < shnum; section_index++) {
        Elf32_Shdr sym_section;
        Elf32_Shdr str_section;
        uint32_t sym_offset;
        uint32_t sym_size;
        uint32_t sym_entsize;
        uint32_t str_offset;
        uint32_t str_size;
        uint32_t str_index;
        char *strings = NULL;
        unsigned int symbol_index;

        if (!qrr_full_read_at(fp, shoff + section_index * shentsize,
                              &sym_section, sizeof(sym_section)) ||
            qrr_full_elf32(sym_section.sh_type, swap) != SHT_SYMTAB) {
            continue;
        }
        str_index = qrr_full_elf32(sym_section.sh_link, swap);
        if (str_index >= shnum ||
            !qrr_full_read_at(fp, shoff + str_index * shentsize,
                              &str_section, sizeof(str_section))) {
            fprintf(stderr, "qrr-full: corrupt symbol string table in %s\n",
                    path);
            goto out;
        }
        sym_offset = qrr_full_elf32(sym_section.sh_offset, swap);
        sym_size = qrr_full_elf32(sym_section.sh_size, swap);
        sym_entsize = qrr_full_elf32(sym_section.sh_entsize, swap);
        str_offset = qrr_full_elf32(str_section.sh_offset, swap);
        str_size = qrr_full_elf32(str_section.sh_size, swap);
        if (sym_entsize != sizeof(Elf32_Sym) || !str_size) {
            fprintf(stderr, "qrr-full: invalid symbol table in %s\n", path);
            goto out;
        }
        strings = malloc(str_size);
        if (!strings || !qrr_full_read_at(fp, str_offset, strings, str_size)) {
            fprintf(stderr, "qrr-full: cannot read symbol strings from %s\n",
                    path);
            free(strings);
            goto out;
        }
        for (symbol_index = 0;
             symbol_index < sym_size / sym_entsize; symbol_index++) {
            Elf32_Sym symbol;
            uint32_t name_offset;
            uint32_t value;
            unsigned int wanted;

            if (!qrr_full_read_at(fp, sym_offset + symbol_index * sym_entsize,
                                  &symbol, sizeof(symbol))) {
                fprintf(stderr, "qrr-full: cannot read symbols from %s\n",
                        path);
                free(strings);
                goto out;
            }
            name_offset = qrr_full_elf32(symbol.st_name, swap);
            value = qrr_full_elf32(symbol.st_value, swap);
            if (!name_offset || name_offset >= str_size ||
                !memchr(strings + name_offset, '\0', str_size - name_offset) ||
                qrr_full_elf16(symbol.st_shndx, swap) == SHN_UNDEF) {
                continue;
            }
            for (wanted = 0; wanted < ARRAY_SIZE(names); wanted++) {
                if (strcmp(strings + name_offset, names[wanted]) == 0) {
                    if (values[wanted] && values[wanted] != value) {
                        fprintf(stderr,
                                "qrr-full: conflicting symbol %s in %s\n",
                                names[wanted], path);
                        free(strings);
                        goto out;
                    }
                    values[wanted] = value;
                }
            }
        }
        free(strings);
    }
    if (!values[3] || !values[4] || !values[5] || !values[6] ||
        !values[7] || !values[8] || !values[9] ||
        (qrr_full_follow_fork_descendants && !values[10]) ||
        (need_signals && (!values[0] || !values[1] || !values[2]))) {
        fprintf(stderr,
                "qrr-full: required kernel symbols missing in %s"
                " (get_signal_to_deliver=%" PRIx64
                " do_signal=%" PRIx64 " do_notify_resume=%" PRIx64
                " proc_exec_connector=%" PRIx64
                " proc_exit_connector=%" PRIx64 " init_task=%" PRIx64
                " pgd_current=%" PRIx64 " ipc_lock_check=%" PRIx64
                " do_page_fault=%" PRIx64 " handle_mm_fault=%" PRIx64
                " proc_fork_connector=%" PRIx64
                ")\n",
                path, (uint64_t)values[0], (uint64_t)values[1],
                (uint64_t)values[2], (uint64_t)values[3],
                (uint64_t)values[4], (uint64_t)values[5],
                (uint64_t)values[6], (uint64_t)values[7],
                (uint64_t)values[8], (uint64_t)values[9],
                (uint64_t)values[10]);
        goto out;
    }
    if (need_signals) {
        qrr_full_get_signal_to_deliver = values[0];
        qrr_full_do_signal = values[1];
        qrr_full_do_notify_resume = values[2];
    }
    qrr_full_proc_exec_connector = values[3];
    qrr_full_proc_exit_connector = values[4];
    qrr_full_init_task = values[5];
    qrr_full_pgd_current = values[6];
    qrr_full_ipc_lock_check = values[7];
    qrr_full_do_page_fault = values[8];
    qrr_full_handle_mm_fault = values[9];
    qrr_full_proc_fork_connector = values[10];
    fprintf(stderr,
            "qrr-full: kernel symbols proc_exec_connector=" TARGET_FMT_lx
            " proc_exit_connector=" TARGET_FMT_lx
            " init_task=" TARGET_FMT_lx " pgd_current=" TARGET_FMT_lx
            " get_signal_to_deliver=" TARGET_FMT_lx
            " do_signal=" TARGET_FMT_lx " do_notify_resume=" TARGET_FMT_lx
            " ipc_lock_check=" TARGET_FMT_lx
            " do_page_fault=" TARGET_FMT_lx
            " handle_mm_fault=" TARGET_FMT_lx
            " proc_fork_connector=" TARGET_FMT_lx
            " source=%s\n",
            qrr_full_proc_exec_connector, qrr_full_proc_exit_connector,
            qrr_full_init_task,
            qrr_full_pgd_current,
            qrr_full_get_signal_to_deliver, qrr_full_do_signal,
            qrr_full_do_notify_resume, qrr_full_ipc_lock_check,
            qrr_full_do_page_fault, qrr_full_handle_mm_fault,
            qrr_full_proc_fork_connector, path);
    ok = true;
out:
    fclose(fp);
    return ok;
}

typedef struct QrrFullSemaphoreProfile {
    uint64_t init_task;
    uint64_t sem_array_base;
    uint64_t sem_array_nsems;
    uint64_t sem_size;
    uint64_t sem_value;
    bool have_init_task;
    bool have_sem_array_base;
    bool have_sem_array_nsems;
    bool have_sem_size;
    bool have_sem_value;
} QrrFullSemaphoreProfile;

static int qrr_full_procinfo_value(const char *line, const char *key,
                                   uint64_t *value)
{
    const char *cursor = line;
    char *end;
    unsigned long long parsed;
    size_t key_length = strlen(key);

    while (*cursor && isspace((unsigned char)*cursor)) {
        cursor++;
    }
    if (strncmp(cursor, key, key_length) != 0 ||
        (cursor[key_length] &&
         !isspace((unsigned char)cursor[key_length]) &&
         cursor[key_length] != '=')) {
        return 0;
    }
    cursor += key_length;
    while (*cursor && isspace((unsigned char)*cursor)) {
        cursor++;
    }
    if (*cursor++ != '=') {
        return -1;
    }
    while (*cursor && isspace((unsigned char)*cursor)) {
        cursor++;
    }
    errno = 0;
    parsed = strtoull(cursor, &end, 0);
    if (errno || end == cursor) {
        return -1;
    }
    while (*end && isspace((unsigned char)*end)) {
        end++;
    }
    if (*end && *end != ';' && *end != '#') {
        return -1;
    }
    *value = parsed;
    return 1;
}

static bool qrr_full_finish_semaphore_profile(
    const QrrFullSemaphoreProfile *current, target_ulong init_task,
    unsigned int *matches, QrrFullSemaphoreProfile *selected)
{
    if (!current->have_init_task || current->init_task != init_task) {
        return true;
    }
    (*matches)++;
    if (!current->have_sem_array_base ||
        !current->have_sem_array_nsems || !current->have_sem_size ||
        !current->have_sem_value) {
        fprintf(stderr,
                "qrr-full: matching procinfo section lacks exact SysV"
                " semaphore layout\n");
        return false;
    }
    *selected = *current;
    return true;
}

/* The kernel data-layout offsets are explicit configuration in the same
 * uniquely init_task-matched procinfo section already used by QRR.  Missing,
 * duplicate, or malformed values are fatal; no instruction/memory scan is
 * used to infer them. */
static bool qrr_full_load_semaphore_profile(const char *path,
                                            target_ulong init_task)
{
    QrrFullSemaphoreProfile current = { 0 };
    QrrFullSemaphoreProfile selected = { 0 };
    FILE *fp;
    char line[512];
    unsigned int matches = 0;

    fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "qrr-full: cannot open semaphore procinfo %s: %s\n",
                path, strerror(errno));
        return false;
    }
    while (fgets(line, sizeof(line), fp)) {
        const char *cursor = line;
        uint64_t value;
        int parsed;

        while (*cursor && isspace((unsigned char)*cursor)) {
            cursor++;
        }
        if (*cursor == '[') {
            if (!qrr_full_finish_semaphore_profile(
                    &current, init_task, &matches, &selected)) {
                fclose(fp);
                return false;
            }
            memset(&current, 0, sizeof(current));
            continue;
        }
#define QRR_FULL_PROFILE_VALUE(name, field, flag)                         \
        do {                                                              \
            parsed = qrr_full_procinfo_value(cursor, name, &value);       \
            if (parsed < 0) {                                             \
                fprintf(stderr,                                           \
                        "qrr-full: malformed procinfo key %s in %s\n",    \
                        name, path);                                      \
                fclose(fp);                                               \
                return false;                                             \
            }                                                             \
            if (parsed > 0) {                                             \
                if (current.flag && current.field != value) {             \
                    fprintf(stderr,                                       \
                            "qrr-full: conflicting procinfo key %s\n",   \
                            name);                                        \
                    fclose(fp);                                           \
                    return false;                                         \
                }                                                         \
                current.field = value;                                    \
                current.flag = true;                                      \
                continue;                                                 \
            }                                                             \
        } while (0)
        QRR_FULL_PROFILE_VALUE("init_task_addr", init_task,
                               have_init_task);
        QRR_FULL_PROFILE_VALUE("sem_array_sem_base", sem_array_base,
                               have_sem_array_base);
        QRR_FULL_PROFILE_VALUE("sem_array_sem_nsems", sem_array_nsems,
                               have_sem_array_nsems);
        QRR_FULL_PROFILE_VALUE("sem_size", sem_size, have_sem_size);
        QRR_FULL_PROFILE_VALUE("sem_semval", sem_value, have_sem_value);
#undef QRR_FULL_PROFILE_VALUE
    }
    if (ferror(fp) || !qrr_full_finish_semaphore_profile(
            &current, init_task, &matches, &selected)) {
        fclose(fp);
        return false;
    }
    fclose(fp);
    if (matches != 1 || selected.sem_array_base > (target_ulong)-1 ||
        selected.sem_array_nsems > (target_ulong)-1 ||
        selected.sem_size > (target_ulong)-1 ||
        selected.sem_value > (target_ulong)-1 ||
        selected.sem_size < sizeof(uint32_t) ||
        selected.sem_value > selected.sem_size - sizeof(uint32_t)) {
        fprintf(stderr,
                "qrr-full: exact semaphore procinfo selection failed"
                " matches=%u source=%s\n", matches, path);
        return false;
    }
    qrr_full_sem_array_base_offset = selected.sem_array_base;
    qrr_full_sem_array_nsems_offset = selected.sem_array_nsems;
    qrr_full_sem_size = selected.sem_size;
    qrr_full_sem_value_offset = selected.sem_value;
    fprintf(stderr,
            "qrr-full: exact semaphore profile sem_base=%" PRIu64
            " sem_nsems=%" PRIu64 " sem_size=%" PRIu64
            " semval=%" PRIu64 " source=%s\n",
            selected.sem_array_base, selected.sem_array_nsems,
            selected.sem_size, selected.sem_value, path);
    return true;
}

static void qrr_full_flush_schedule(void)
{
    QrrFullScheduleEvent *event = qrr_full_schedule_head;
    uint64_t output_sequence = 0;

    while (event) {
        QrrFullScheduleEvent *next = event->next;

        if (event->committed && qrr_full_schedule_fp) {
            output_sequence++;
            if ((qrr_full_thread_context ?
                 fprintf(qrr_full_schedule_fp,
                        "%" PRIu64 "\t%016" PRIx64 "\t%016" PRIx64
                        "\t%" PRIu64 "\t%d\t%016" PRIx64
                        "\t%016" PRIx64 "\t%016" PRIx64 "\n",
                        output_sequence, event->process_token,
                        event->thread_token, event->syscall_sequence,
                        event->syscall_nr, event->key, event->path_hash,
                        event->dep_hash) :
                 fprintf(qrr_full_schedule_fp,
                        "%" PRIu64 "\t%016" PRIx64 "\t%" PRIu64
                        "\t%d\t%016" PRIx64 "\t%016" PRIx64
                        "\t%016" PRIx64 "\n",
                        output_sequence, event->process_token,
                        event->syscall_sequence, event->syscall_nr,
                        event->key, event->path_hash, event->dep_hash)) < 0) {
                fprintf(stderr,
                        "qrr-full: cannot write committed syscall schedule: %s\n",
                        strerror(errno));
                exit(2);
            }
        }
        free(event);
        event = next;
    }
    qrr_full_schedule_head = NULL;
    qrr_full_schedule_tail = NULL;
    if (qrr_full_schedule_fp && fflush(qrr_full_schedule_fp) != 0) {
        fprintf(stderr,
                "qrr-full: cannot flush committed syscall schedule: %s\n",
                strerror(errno));
        exit(2);
    }
}

static void qrr_full_schedule_entry(QrrFullPending *pending)
{
    QrrFullScheduleEvent *event;

    if (!qrr_full_schedule_fp) {
        return;
    }
    event = calloc(1, sizeof(*event));
    if (!event) {
        fprintf(stderr, "qrr-full: cannot allocate syscall schedule event\n");
        exit(2);
    }
    event->process_token = pending->process_token;
    event->thread_token = pending->thread_token;
    event->syscall_sequence = pending->sequence;
    event->syscall_nr = pending->syscall_nr;
    event->key = pending->key;
    event->path_hash = pending->path_hash;
    event->dep_hash = pending->dep_hash;
    if (qrr_full_schedule_tail) {
        qrr_full_schedule_tail->next = event;
    } else {
        qrr_full_schedule_head = event;
    }
    qrr_full_schedule_tail = event;
    pending->schedule_event = event;
}

static void qrr_full_schedule_commit(QrrFullPending *pending)
{
    if (pending && pending->schedule_event) {
        pending->schedule_event->committed = true;
    }
}

static void qrr_full_close(void)
{
    while (qrr_full_tb_pending) {
        QrrFullTbPending *pending = qrr_full_tb_pending;

        qrr_full_tb_pending = pending->next;
        free(pending);
    }
    if (qrr_full_table_fp) {
        fclose(qrr_full_table_fp);
        qrr_full_table_fp = NULL;
    }
    if (qrr_full_schedule_fp) {
        qrr_full_flush_schedule();
        fclose(qrr_full_schedule_fp);
        qrr_full_schedule_fp = NULL;
    } else {
        qrr_full_flush_schedule();
    }
    if (qrr_full_event_fp) {
        fclose(qrr_full_event_fp);
        qrr_full_event_fp = NULL;
    }
    if (qrr_full_exec_fp) {
        fclose(qrr_full_exec_fp);
        qrr_full_exec_fp = NULL;
    }
    if (qrr_full_signal_fp) {
        fclose(qrr_full_signal_fp);
        qrr_full_signal_fp = NULL;
    }
    if (qrr_full_layout_fp) {
        fclose(qrr_full_layout_fp);
        qrr_full_layout_fp = NULL;
    }
    if (qrr_full_mmap_fp) {
        fclose(qrr_full_mmap_fp);
        qrr_full_mmap_fp = NULL;
    }
}

static bool qrr_full_init(void)
{
    const char *table_path;
    const char *schedule_path;
    const char *event_path;
    const char *exec_path;
    const char *max_blob;
    const char *all_pgds;
    const char *target_name;
    const char *rootfs;
    const char *signal_path;
    const char *vmlinux_path;
    const char *layout_path;
    const char *mmap_path;
    const char *procinfo_path;
    const char *fork_descendants;
    const char *thread_context;
    const char *debug_precision_edges;
    bool collection_requested;
    char profile_error[128];

    if (qrr_full_initialized) {
        return qrr_full_enabled;
    }
    qrr_full_initialized = 1;
    table_path = getenv("QRR_FULL_TCG_QRR");
    schedule_path = getenv("QRR_FULL_TCG_SCHEDULE");
    event_path = getenv("QRR_FULL_TCG_EVENTS");
    exec_path = getenv("QRR_FULL_TCG_EXECS");
    max_blob = getenv("QRR_FULL_TCG_MAX_BLOB");
    all_pgds = getenv("QRR_FULL_TCG_ALL_PGDS");
    target_name = getenv("QRR_FULL_TCG_TARGET_NAME");
    rootfs = getenv("QRR_FULL_TCG_ROOTFS");
    signal_path = getenv("QRR_FULL_TCG_SIGNALS");
    vmlinux_path = getenv("QRR_FULL_TCG_VMLINUX");
    layout_path = getenv("QRR_FULL_TCG_LAYOUT");
    mmap_path = getenv("QRR_FULL_TCG_MMAPS");
    procinfo_path = getenv("QRR_FULL_TCG_PROCINFO");
    fork_descendants = getenv("QRR_FULL_TCG_FORK_DESCENDANTS");
    thread_context = getenv("QRR_FULL_TCG_THREAD_CONTEXT");
    qrr_full_thread_context = thread_context &&
        strcmp(thread_context, "1") == 0;
    debug_precision_edges = getenv("QRR_FULL_TCG_DEBUG_EDGES");
    collection_requested =
        (table_path && table_path[0]) ||
        (schedule_path && schedule_path[0]) ||
        (event_path && event_path[0]) ||
        (exec_path && exec_path[0]) || (signal_path && signal_path[0]) ||
        (layout_path && layout_path[0]) || (mmap_path && mmap_path[0]);
    /* cpu_tb_exec() is the only exact per-TB observation boundary in this
     * QEMU 2.10 collector.  Its generated direct and indirect exits can
     * otherwise enter another TB without returning through that boundary.
     * Enabling nochain only after the first page-fault watch is learned is
     * too late: the currently executing kernel chain can return to user mode
     * and execute repeated anchor edges before tb_find() gets control again.
     * Select nochain at QRR initialization, before subsequent guest code is
     * translated.  qrr_full_tb_before() still rejects every non-target PGD,
     * so this changes translation policy, not collection scope. */
    if (collection_requested &&
        !qemu_loglevel_mask(CPU_LOG_TB_NOCHAIN)) {
        qemu_set_log(qemu_loglevel | CPU_LOG_TB_NOCHAIN);
        fprintf(stderr,
                "qrr-full: exact TB observation enabled with nochain\n");
    }
    if (max_blob && max_blob[0]) {
        qrr_full_max_blob = strtoull(max_blob, NULL, 0);
    }
    qrr_full_all_pgds = all_pgds && strcmp(all_pgds, "1") == 0;
    if (fork_descendants && strcmp(fork_descendants, "0") != 0 &&
        strcmp(fork_descendants, "1") != 0) {
        fprintf(stderr,
                "qrr-full: QRR_FULL_TCG_FORK_DESCENDANTS must be 0 or 1\n");
        exit(2);
    }
    qrr_full_follow_fork_descendants =
        fork_descendants && strcmp(fork_descendants, "1") == 0;
    qrr_full_debug_precision_edges =
        debug_precision_edges && strcmp(debug_precision_edges, "1") == 0;
    qrr_full_target_name = target_name && target_name[0] ? target_name : NULL;
    if (collection_requested) {
        if (!qrr_full_target_name) {
            fprintf(stderr,
                    "qrr-full: collection requires QRR_FULL_TCG_TARGET_NAME\n");
            exit(2);
        }
        if (strlen(qrr_full_target_name) >=
            sizeof(((qrr_vmi_exec_identity_t *)0)->name)) {
            fprintf(stderr,
                    "qrr-full: target name %s cannot be represented exactly"
                    " by task_struct::comm\n", qrr_full_target_name);
            exit(2);
        }
        if (qrr_full_all_pgds) {
            fprintf(stderr,
                    "qrr-full: QRR_FULL_TCG_ALL_PGDS is incompatible with"
                    " single-target PGD collection\n");
            exit(2);
        }
        if (!vmlinux_path || !vmlinux_path[0]) {
            fprintf(stderr,
                    "qrr-full: collection requires QRR_FULL_TCG_VMLINUX\n");
            exit(2);
        }
        if (!procinfo_path || !procinfo_path[0]) {
            fprintf(stderr,
                    "qrr-full: collection requires QRR_FULL_TCG_PROCINFO\n");
            exit(2);
        }
        if (!qrr_full_resolve_kernel_symbols(
                vmlinux_path, signal_path && signal_path[0])) {
            fprintf(stderr, "qrr-full: kernel symbol resolution failed\n");
            exit(2);
        }
        if (!qrr_full_load_semaphore_profile(procinfo_path,
                                             qrr_full_init_task)) {
            fprintf(stderr,
                    "qrr-full: exact semaphore profile load failed\n");
            exit(2);
        }
        if (VMI_qrr_load_linux_profile_c(
                procinfo_path, qrr_full_init_task,
                qrr_full_proc_exec_connector, profile_error,
                sizeof(profile_error)) != 0) {
            fprintf(stderr, "qrr-full: exact procinfo load failed: %s\n",
                    profile_error[0] ? profile_error : "unknown");
            exit(2);
        }
    }
    if (rootfs && rootfs[0]) {
        int rootfs_fd;

        qrr_full_rootfs_path = rootfs;
        rootfs_fd = open(rootfs, O_PATH | O_DIRECTORY | O_CLOEXEC);
        if (rootfs_fd < 0) {
            fprintf(stderr, "qrr-full: cannot open rootfs %s: %s\n",
                    rootfs, strerror(errno));
        } else {
            fprintf(stderr, "qrr-full: rootfs %s validated\n", rootfs);
            close(rootfs_fd);
        }
    }

    if (table_path && table_path[0]) {
        qrr_full_table_fp = fopen(table_path, "a+");
        if (!qrr_full_table_fp) {
            fprintf(stderr, "qrr-full: cannot create %s: %s\n",
                    table_path, strerror(errno));
        } else {
            fseek(qrr_full_table_fp, 0, SEEK_END);
            if (ftell(qrr_full_table_fp) == 0) {
                fprintf(qrr_full_table_fp, "%s\n",
                        qrr_full_thread_context ? QRR_FULL_RESULT_MAGIC :
                        QRR_FULL_RESULT_MAGIC_V14);
                fprintf(qrr_full_table_fp, "%s\n",
                        qrr_full_thread_context ? QRR_FULL_RESULT_COLUMNS :
                        QRR_FULL_RESULT_COLUMNS_V14);
            }
            setvbuf(qrr_full_table_fp, NULL, _IOLBF, 0);
            qrr_full_enabled = true;
        }
    }
    if (schedule_path && schedule_path[0]) {
        qrr_full_schedule_fp = fopen(schedule_path, "a+");
        if (!qrr_full_schedule_fp) {
            fprintf(stderr, "qrr-full: cannot create schedule table %s: %s\n",
                    schedule_path, strerror(errno));
            exit(2);
        }
        if (setvbuf(qrr_full_schedule_fp, NULL, _IOLBF, 0) != 0) {
            fprintf(stderr,
                    "qrr-full: cannot set schedule table buffering: %s\n",
                    strerror(errno));
            exit(2);
        }
        fseek(qrr_full_schedule_fp, 0, SEEK_END);
        if (ftell(qrr_full_schedule_fp) == 0) {
            fprintf(qrr_full_schedule_fp, "%s\n",
                    qrr_full_thread_context ? QRR_FULL_SCHEDULE_MAGIC :
                    QRR_FULL_SCHEDULE_MAGIC_V1);
            fprintf(qrr_full_schedule_fp, "%s\n",
                    qrr_full_thread_context ? QRR_FULL_SCHEDULE_COLUMNS :
                    QRR_FULL_SCHEDULE_COLUMNS_V1);
        } else {
            fprintf(stderr,
                    "qrr-full: schedule output must be a fresh file: %s\n",
                    schedule_path);
            exit(2);
        }
        if (fflush(qrr_full_schedule_fp) != 0) {
            fprintf(stderr,
                    "qrr-full: cannot flush schedule table header: %s\n",
                    strerror(errno));
            exit(2);
        }
        qrr_full_enabled = true;
    }
    if (event_path && event_path[0]) {
        qrr_full_event_fp = fopen(event_path, "a+");
        if (!qrr_full_event_fp) {
            fprintf(stderr, "qrr-full: cannot create %s: %s\n",
                    event_path, strerror(errno));
        } else {
            fseek(qrr_full_event_fp, 0, SEEK_END);
            if (ftell(qrr_full_event_fp) == 0) {
                fprintf(qrr_full_event_fp, "%s\n", QRR_FULL_EVENT_MAGIC);
                fprintf(qrr_full_event_fp, "%s\n", QRR_FULL_EVENT_COLUMNS);
            }
            setvbuf(qrr_full_event_fp, NULL, _IOLBF, 0);
            qrr_full_enabled = true;
        }
    }
    if (exec_path && exec_path[0]) {
        qrr_full_exec_fp = fopen(exec_path, "a+");
        if (!qrr_full_exec_fp) {
            fprintf(stderr, "qrr-full: cannot create %s: %s\n",
                    exec_path, strerror(errno));
        } else {
            long exec_size;

            fseek(qrr_full_exec_fp, 0, SEEK_END);
            exec_size = ftell(qrr_full_exec_fp);
            if (exec_size == 0) {
                fprintf(qrr_full_exec_fp, "%s\n", QRR_FULL_EXEC_MAGIC);
                fprintf(qrr_full_exec_fp, "%s\n", QRR_FULL_EXEC_COLUMNS);
            } else {
                char magic[128];
                char columns[256];

                rewind(qrr_full_exec_fp);
                if (!fgets(magic, sizeof(magic), qrr_full_exec_fp) ||
                    !fgets(columns, sizeof(columns), qrr_full_exec_fp)) {
                    fprintf(stderr,
                            "qrr-full: existing exec table header unreadable"
                            " path=%s\n", exec_path);
                    exit(2);
                }
                magic[strcspn(magic, "\r\n")] = '\0';
                columns[strcspn(columns, "\r\n")] = '\0';
                if (strcmp(magic, QRR_FULL_EXEC_MAGIC) != 0 ||
                    strcmp(columns, QRR_FULL_EXEC_COLUMNS) != 0) {
                    fprintf(stderr,
                            "qrr-full: existing exec table is not cwd-aware"
                            " v2 path=%s magic=%s\n", exec_path, magic);
                    exit(2);
                }
                fseek(qrr_full_exec_fp, 0, SEEK_END);
            }
            setvbuf(qrr_full_exec_fp, NULL, _IOLBF, 0);
            qrr_full_enabled = true;
        }
    }
    if (signal_path && signal_path[0]) {
        qrr_full_signal_fp = fopen(signal_path, "a+");
        if (!qrr_full_signal_fp) {
            fprintf(stderr, "qrr-full: cannot create %s: %s\n",
                    signal_path, strerror(errno));
            exit(2);
        }
        if (setvbuf(qrr_full_signal_fp, NULL, _IOLBF, 0) != 0) {
            fprintf(stderr, "qrr-full: cannot set signal table buffering: %s\n",
                    strerror(errno));
            exit(2);
        }
        fseek(qrr_full_signal_fp, 0, SEEK_END);
        if (ftell(qrr_full_signal_fp) == 0) {
            fprintf(qrr_full_signal_fp, "%s\n", QRR_FULL_SIGNAL_MAGIC);
            fprintf(qrr_full_signal_fp, "%s\n", QRR_FULL_SIGNAL_COLUMNS);
        }
        if (fflush(qrr_full_signal_fp) != 0) {
            fprintf(stderr, "qrr-full: cannot flush signal table header: %s\n",
                    strerror(errno));
            exit(2);
        }
        qrr_full_enabled = true;
    }
    if (layout_path && layout_path[0]) {
        qrr_full_layout_fp = fopen(layout_path, "a+");
        if (!qrr_full_layout_fp) {
            fprintf(stderr, "qrr-full: cannot create layout table %s: %s\n",
                    layout_path, strerror(errno));
            exit(2);
        }
        if (setvbuf(qrr_full_layout_fp, NULL, _IOLBF, 0) != 0) {
            fprintf(stderr, "qrr-full: cannot set layout table buffering: %s\n",
                    strerror(errno));
            exit(2);
        }
        fseek(qrr_full_layout_fp, 0, SEEK_END);
        if (ftell(qrr_full_layout_fp) == 0) {
            fprintf(qrr_full_layout_fp, "%s\n", QRR_FULL_LAYOUT_MAGIC);
            fprintf(qrr_full_layout_fp, "%s\n", QRR_FULL_LAYOUT_COLUMNS);
        }
        if (fflush(qrr_full_layout_fp) != 0) {
            fprintf(stderr, "qrr-full: cannot flush layout table header: %s\n",
                    strerror(errno));
            exit(2);
        }
        qrr_full_enabled = true;
    }
    if (mmap_path && mmap_path[0]) {
        qrr_full_mmap_fp = fopen(mmap_path, "a+");
        if (!qrr_full_mmap_fp) {
            fprintf(stderr, "qrr-full: cannot create mmap table %s: %s\n",
                    mmap_path, strerror(errno));
            exit(2);
        }
        if (setvbuf(qrr_full_mmap_fp, NULL, _IOLBF, 0) != 0) {
            fprintf(stderr, "qrr-full: cannot set mmap table buffering: %s\n",
                    strerror(errno));
            exit(2);
        }
        fseek(qrr_full_mmap_fp, 0, SEEK_END);
        if (ftell(qrr_full_mmap_fp) == 0) {
            fprintf(qrr_full_mmap_fp, "%s\n", QRR_FULL_MMAP_MAGIC);
            fprintf(qrr_full_mmap_fp, "%s\n", QRR_FULL_MMAP_COLUMNS);
        }
        if (fflush(qrr_full_mmap_fp) != 0) {
            fprintf(stderr, "qrr-full: cannot flush mmap table header: %s\n",
                    strerror(errno));
            exit(2);
        }
        qrr_full_enabled = true;
    }
    if (qrr_full_enabled) {
        atexit(qrr_full_close);
    }
    return qrr_full_enabled;
}

static bool qrr_full_user_pc(target_ulong pc)
{
#ifdef TARGET_MIPS
    return pc < 0x80000000;
#elif defined(TARGET_ARM)
    return pc < 0xc0000000;
#else
    (void)pc;
    return false;
#endif
}

static bool qrr_full_trace_pgd(target_ulong pgd)
{
    QrrFullTargetPgd *target;

    if (!qrr_full_target_active) {
        return false;
    }
    if (!qrr_full_follow_fork_descendants) {
        if (pgd != qrr_full_selected_pgd) {
            return false;
        }
        for (target = qrr_full_target_pgds; target; target = target->next) {
            if (target->pgd == pgd) {
                return !target->exec_transitioning;
            }
        }
        return false;
    }
    /* Descendant discovery happens only at the exact fork return anchor.
     * The hot TB path therefore checks this small bound-target list and does
     * not invoke WMI or scan the guest process table. */
    for (target = qrr_full_target_pgds; target; target = target->next) {
        if (target->pgd == pgd && !target->exec_transitioning) {
            return true;
        }
    }
    return false;
}

static QrrFullTargetPgd *qrr_full_target_process(target_ulong pgd)
{
    QrrFullTargetPgd *target;

    for (target = qrr_full_target_pgds; target; target = target->next) {
        if (target->pgd == pgd) {
            return target;
        }
    }
    return NULL;
}

static QrrFullTargetPgd *qrr_full_target_process_for_token(
    uint64_t process_token)
{
    QrrFullTargetPgd *target;

    for (target = qrr_full_target_pgds; target; target = target->next) {
        if (target->process_token == process_token) {
            return target;
        }
    }
    return NULL;
}

static QrrFullThreadIdentity *qrr_full_thread_identity_find(
    target_ulong pgd, target_ulong task)
{
    QrrFullThreadIdentity *thread;

    for (thread = qrr_full_threads; thread; thread = thread->next) {
        if (thread->pgd == pgd && thread->task == task) {
            return thread;
        }
    }
    return NULL;
}

static QrrFullTargetPgd *qrr_full_target_process_for_task(
    target_ulong pgd, target_ulong task)
{
    QrrFullTargetPgd *target;
    QrrFullThreadIdentity *thread;

    for (target = qrr_full_target_pgds; target; target = target->next) {
        if (target->pgd == pgd && target->have_task &&
            target->task == task) {
            return target;
        }
    }
    thread = qrr_full_thread_identity_find(pgd, task);
    return thread ?
        qrr_full_target_process_for_token(thread->process_token) : NULL;
}

static QrrFullTargetPgd *qrr_full_target_process_for_tgid(
    target_ulong pgd, uint32_t tgid)
{
    QrrFullTargetPgd *target;

    for (target = qrr_full_target_pgds; target; target = target->next) {
        if (target->pgd == pgd && target->have_task &&
            target->tgid == tgid) {
            return target;
        }
    }
    return NULL;
}

static uint64_t qrr_full_thread_token(uint64_t process_token,
                                      uint64_t ordinal)
{
    uint64_t token = QRR_FULL_FNV64_OFFSET;

    token = qrr_full_hash_mix_u64(token, UINT64_C(0x5448524541445f51));
    token = qrr_full_hash_mix_u64(token, process_token);
    return qrr_full_hash_mix_u64(token, ordinal);
}

static QrrFullThreadIdentity *qrr_full_thread_identity(target_ulong pgd,
                                                       target_ulong task,
                                                       uint32_t tgid,
                                                       bool create)
{
    QrrFullThreadIdentity *thread;
    QrrFullTargetPgd *target;

    thread = qrr_full_thread_identity_find(pgd, task);
    if (thread) {
        if (thread->tgid != tgid) {
            fprintf(stderr,
                    "qrr-full: exact task changed thread group pgd="
                    TARGET_FMT_lx " task=" TARGET_FMT_lx
                    " old_tgid=%u new_tgid=%u\n",
                    pgd, task, thread->tgid, tgid);
            exit(2);
        }
        return thread;
    }
    target = qrr_full_target_process_for_tgid(pgd, tgid);
    if (!create || !target || !target->process_token || !task) {
        return NULL;
    }
    thread = calloc(1, sizeof(*thread));
    if (!thread) {
        return NULL;
    }
    thread->pgd = pgd;
    thread->task = task;
    thread->tgid = tgid;
    target->next_thread_ordinal++;
    thread->process_token = target->process_token;
    thread->ordinal = target->next_thread_ordinal;
    thread->thread_token = qrr_full_thread_token(
        target->process_token, target->next_thread_ordinal);
    thread->next = qrr_full_threads;
    qrr_full_threads = thread;
    fprintf(stderr,
            "qrr-full: thread-context bind process=%016" PRIx64
            " thread=%016" PRIx64 " pgd=" TARGET_FMT_lx
            " task=" TARGET_FMT_lx " tgid=%u ordinal=%" PRIu64 "\n",
            target->process_token, thread->thread_token, pgd, task,
            tgid, target->next_thread_ordinal);
    return thread;
}

static void qrr_full_set_cpu_thread(CPUState *cpu, target_ulong pgd,
                                    target_ulong task)
{
    QrrFullCpuThread *current;

    for (current = qrr_full_cpu_threads; current; current = current->next) {
        if (current->cpu == cpu) {
            current->pgd = pgd;
            current->task = task;
            return;
        }
    }
    current = calloc(1, sizeof(*current));
    if (!current) {
        fprintf(stderr, "qrr-full: cannot allocate CPU thread context\n");
        exit(2);
    }
    current->cpu = cpu;
    current->pgd = pgd;
    current->task = task;
    current->next = qrr_full_cpu_threads;
    qrr_full_cpu_threads = current;
}

static target_ulong qrr_full_cpu_thread(CPUState *cpu, target_ulong pgd)
{
    QrrFullCpuThread *current;

    for (current = qrr_full_cpu_threads; current; current = current->next) {
        if (current->cpu == cpu && current->pgd == pgd) {
            return current->task;
        }
    }
    return 0;
}

static uint64_t qrr_full_new_root_process_token(void)
{
    qrr_full_next_root_process_ordinal++;
    return QRR_FULL_ROOT_PROCESS_PREFIX |
           qrr_full_next_root_process_ordinal;
}

static uint64_t qrr_full_child_process_token(uint64_t parent_token,
                                             uint64_t fork_ordinal)
{
    uint64_t token = QRR_FULL_FNV64_OFFSET;

    token = qrr_full_hash_mix_u64(token, QRR_FULL_CHILD_PROCESS_TAG);
    token = qrr_full_hash_mix_u64(token, parent_token);
    return qrr_full_hash_mix_u64(token, fork_ordinal);
}

static void qrr_full_user_edge_remove_all(target_ulong pgd)
{
    QrrFullUserEdgeCount **link = &qrr_full_user_edge_counts;

    while (*link) {
        QrrFullUserEdgeCount *entry = *link;

        if (entry->pgd == pgd) {
            *link = entry->next;
            free(entry);
            continue;
        }
        link = &entry->next;
    }
}

static void qrr_full_user_edge_remove_task(target_ulong pgd,
                                           target_ulong task)
{
    QrrFullUserEdgeCount **link = &qrr_full_user_edge_counts;

    while (*link) {
        QrrFullUserEdgeCount *entry = *link;

        if (entry->pgd == pgd && entry->task == task) {
            *link = entry->next;
            free(entry);
            continue;
        }
        link = &entry->next;
    }
}

static void qrr_full_user_precision_remove_all(target_ulong pgd)
{
    QrrFullUserPrecisionWatch **link = &qrr_full_user_precision_watches;

    while (*link) {
        QrrFullUserPrecisionWatch *watch = *link;

        if (watch->pgd == pgd) {
            *link = watch->next;
            free(watch);
            continue;
        }
        link = &watch->next;
    }
}

static void qrr_full_user_precision_remove_task(target_ulong pgd,
                                                 target_ulong task)
{
    QrrFullUserPrecisionWatch **link = &qrr_full_user_precision_watches;

    while (*link) {
        QrrFullUserPrecisionWatch *watch = *link;

        if (watch->pgd == pgd && watch->task == task) {
            *link = watch->next;
            free(watch);
            continue;
        }
        link = &watch->next;
    }
}

static bool qrr_full_user_precision_watched(target_ulong pgd,
                                            target_ulong task,
                                            target_ulong pc,
                                            bool delay_slot)
{
    QrrFullUserPrecisionWatch *watch;

    for (watch = qrr_full_user_precision_watches; watch;
         watch = watch->next) {
        if (watch->pgd == pgd && watch->task == task && watch->pc == pc &&
            watch->delay_slot == delay_slot) {
            return true;
        }
    }
    return false;
}

static QrrFullUserPrecisionWatch *qrr_full_user_precision_find(
    target_ulong pgd, target_ulong task, target_ulong edge_from_pc,
    target_ulong edge_to_pc, bool delay_slot)
{
    QrrFullUserPrecisionWatch *watch;

    for (watch = qrr_full_user_precision_watches; watch;
         watch = watch->next) {
        if (watch->pgd == pgd && watch->task == task &&
            watch->edge_from_pc == edge_from_pc &&
            watch->pc == edge_to_pc && watch->delay_slot == delay_slot) {
            return watch;
        }
    }
    return NULL;
}

static void qrr_full_user_precision_add(
    target_ulong pgd, target_ulong task, target_ulong edge_from_pc,
    target_ulong edge_to_pc, bool delay_slot, uint64_t syscall_sequence,
    uint64_t baseline_occurrence)
{
    QrrFullUserPrecisionWatch *watch;

    if (!edge_to_pc || (delay_slot && edge_to_pc < 4) ||
        qrr_full_user_precision_find(pgd, task, edge_from_pc, edge_to_pc,
                                     delay_slot)) {
        return;
    }
    watch = calloc(1, sizeof(*watch));
    if (!watch) {
        fprintf(stderr,
                "qrr-full: cannot allocate exact user-edge watch\n");
        exit(2);
    }
    watch->pgd = pgd;
    watch->task = task;
    watch->edge_from_pc = edge_from_pc;
    watch->pc = edge_to_pc;
    watch->baseline_syscall_sequence = syscall_sequence;
    watch->baseline_occurrence = baseline_occurrence;
    watch->delay_slot = delay_slot;
    watch->next = qrr_full_user_precision_watches;
    qrr_full_user_precision_watches = watch;
    qrr_full_user_precision_flush_pending = true;
}

/* A learned anchor can lie inside an already cached or indirectly chained
 * TB.  QEMU 2.10 has no per-TB CF_NO_GOTO_PTR flag: clearing last_tb only
 * prevents tb_add_jump(), while tcg_gen_lookup_and_goto_ptr() can still skip
 * the outer cpu_tb_exec() callback.  Enable CPU_LOG_TB_NOCHAIN when the first
 * exact watch is learned and flush translated code so both direct and
 * indirect chaining stop.  QRR callbacks remain target-PGD filtered; this
 * global translation policy is required only because 2.10 cannot express it
 * per target TB. */
static bool qrr_full_user_precision_prepare(CPUState *cpu)
{
    QrrFullUserPrecisionWatch *watch;
    target_ulong pgd;
    target_ulong task;
    bool active = false;

    if (!qrr_full_enabled || !qrr_full_user_precision_watches) {
        return false;
    }
    if (qrr_full_user_precision_flush_pending) {
        if (!qemu_loglevel_mask(CPU_LOG_TB_NOCHAIN)) {
            qemu_set_log(qemu_loglevel | CPU_LOG_TB_NOCHAIN);
        }
        tb_flush(cpu);
        qrr_full_user_precision_flush_pending = false;
    }
    pgd = qrr_full_current_pgd(cpu);
    task = qrr_full_cpu_thread(cpu, pgd);
    for (watch = qrr_full_user_precision_watches; watch;
         watch = watch->next) {
        if (watch->pgd == pgd && watch->task == task) {
            active = true;
            break;
        }
    }
    return active;
}

/* Once a user-mode mmap fault or signal has exposed an exact instruction
 * edge, make all later executions of that PC visible as their own TB edge.
 * This gives occurrence a QEMU-version-independent meaning without imposing
 * global single stepping. */
static uint32_t qrr_full_user_precision_limit(CPUState *cpu,
                                              TranslationBlock *tb)
{
#ifdef TARGET_MIPS
    QrrFullUserPrecisionWatch *watch;
    target_ulong pgd;
    target_ulong task;
    uint32_t limit = 0;

    if (!qrr_full_enabled || !tb || !qrr_full_user_pc(tb->pc)) {
        return 0;
    }
    pgd = qrr_full_current_pgd(cpu);
    if (!qrr_full_trace_pgd(pgd)) {
        return 0;
    }
    task = qrr_full_cpu_thread(cpu, pgd);
    for (watch = qrr_full_user_precision_watches; watch;
         watch = watch->next) {
        uint64_t distance;
        uint32_t candidate;
        target_ulong anchor_pc;

        if (watch->pgd != pgd || watch->task != task) {
            continue;
        }
        anchor_pc = watch->delay_slot ? watch->pc - 4 : watch->pc;
        if (anchor_pc < tb->pc || anchor_pc >= tb->pc + tb->size ||
            (anchor_pc & 3) != 0 ||
            (tb->pc & 3) != 0) {
            continue;
        }
        distance = anchor_pc - tb->pc;
        /* A delay-slot anchor must execute its branch and delay instruction
         * in one normal MIPS TB.  Splitting at the delay instruction would
         * discard the branch target state and change guest control flow. */
        if (!distance && watch->delay_slot) {
            continue;
        }
        candidate = distance ? distance / 4 : 1;
        if (candidate && candidate <= tb->icount &&
            (!limit || candidate < limit)) {
            limit = candidate;
        }
    }
    return limit;
#else
    (void)cpu;
    (void)tb;
    return 0;
#endif
}

static QrrFullUserEdgeCount *qrr_full_user_edge_find(target_ulong pgd,
                                                      target_ulong task,
                                                      target_ulong from_pc,
                                                      target_ulong to_pc)
{
    QrrFullUserEdgeCount *entry;

    for (entry = qrr_full_user_edge_counts; entry; entry = entry->next) {
        if (entry->pgd == pgd && entry->task == task &&
            entry->from_pc == from_pc &&
            entry->to_pc == to_pc) {
            return entry;
        }
    }
    return NULL;
}

static uint64_t qrr_full_user_edge_next_occurrence(target_ulong pgd,
                                                    target_ulong task,
                                                    target_ulong from_pc,
                                                    target_ulong to_pc)
{
    QrrFullUserEdgeCount *entry = qrr_full_user_edge_find(
        pgd, task, from_pc, to_pc);

    if (entry && entry->occurrence == UINT64_MAX) {
        fprintf(stderr,
                "qrr-full: user edge occurrence overflow pgd=" TARGET_FMT_lx
                " from=" TARGET_FMT_lx " to=" TARGET_FMT_lx "\n",
                pgd, from_pc, to_pc);
        exit(2);
    }
    return entry ? entry->occurrence + 1 : 1;
}

/* Exact event occurrences start when the first real signal delivery or Linux
 * VM fault teaches QRR to watch that edge.  TB boundaries which happened to
 * expose the same from/to pair before that point are an implementation detail
 * of the collector and must not leak into a cross-version replay anchor. */
static uint64_t qrr_full_user_precision_next_occurrence(
    target_ulong pgd, target_ulong task, uint64_t syscall_sequence,
    target_ulong from_pc, target_ulong to_pc, bool delay_slot)
{
    QrrFullUserPrecisionWatch *watch = qrr_full_user_precision_find(
        pgd, task, from_pc, to_pc, delay_slot);
    uint64_t next = qrr_full_user_edge_next_occurrence(
        pgd, task, from_pc, to_pc);
    uint64_t baseline = 0;

    if (!watch) {
        return 1;
    }
    if (watch->baseline_syscall_sequence == syscall_sequence) {
        baseline = watch->baseline_occurrence;
    }
    if (next <= baseline) {
        fprintf(stderr,
                "qrr-full: precision edge baseline invalid pgd="
                TARGET_FMT_lx " edge=" TARGET_FMT_lx "->" TARGET_FMT_lx
                " syscall_sequence=%" PRIu64 " next=%" PRIu64
                " baseline=%" PRIu64 "\n",
                pgd, from_pc, to_pc, syscall_sequence, next, baseline);
        exit(2);
    }
    return next - baseline;
}

static uint64_t qrr_full_user_edge_current_occurrence(target_ulong pgd,
                                                       target_ulong task,
                                                       target_ulong from_pc,
                                                       target_ulong to_pc)
{
    QrrFullUserEdgeCount *entry = qrr_full_user_edge_find(
        pgd, task, from_pc, to_pc);

    return entry ? entry->occurrence : 0;
}

static uint64_t qrr_full_user_edge_note(target_ulong pgd,
                                        target_ulong task,
                                        target_ulong from_pc,
                                        target_ulong to_pc)
{
    QrrFullUserEdgeCount *entry = qrr_full_user_edge_find(
        pgd, task, from_pc, to_pc);

    if (!entry) {
        entry = calloc(1, sizeof(*entry));
        if (!entry) {
            fprintf(stderr, "qrr-full: cannot allocate user edge counter\n");
            exit(2);
        }
        entry->pgd = pgd;
        entry->task = task;
        entry->from_pc = from_pc;
        entry->to_pc = to_pc;
        entry->next = qrr_full_user_edge_counts;
        qrr_full_user_edge_counts = entry;
    }
    if (entry->occurrence == UINT64_MAX) {
        fprintf(stderr,
                "qrr-full: user edge occurrence overflow pgd=" TARGET_FMT_lx
                " from=" TARGET_FMT_lx " to=" TARGET_FMT_lx "\n",
                pgd, from_pc, to_pc);
        exit(2);
    }
    return ++entry->occurrence;
}

/* TB boundaries are a QEMU implementation detail.  A signal anchor may be a
 * linear guest edge inside one QEMU version's TB and a TB-entry edge in the
 * other version.  Count every completed MIPS32 instruction edge for the
 * target task, while keeping the persisted fuzz edge log TB-granular. */
static void qrr_full_user_edge_note_linear(target_ulong pgd,
                                           target_ulong task,
                                           target_ulong first_pc,
                                           target_ulong last_completed_pc,
                                           bool skip_edge,
                                           target_ulong skip_from_pc,
                                           target_ulong skip_to_pc)
{
    target_ulong pc;

    if (last_completed_pc < first_pc || (first_pc & 3) != 0 ||
        (last_completed_pc & 3) != 0) {
        fprintf(stderr,
                "qrr-full: invalid completed MIPS32 instruction range pgd="
                TARGET_FMT_lx " first=" TARGET_FMT_lx " last="
                TARGET_FMT_lx "\n", pgd, first_pc, last_completed_pc);
        exit(2);
    }
    for (pc = first_pc; pc < last_completed_pc; pc += 4) {
        if (skip_edge && pc == skip_from_pc && pc + 4 == skip_to_pc) {
            continue;
        }
        qrr_full_user_edge_note(pgd, task, pc, pc + 4);
    }
}

static QrrFullTbPending *qrr_full_tb_pending_find(CPUState *cpu)
{
    QrrFullTbPending *pending;

    for (pending = qrr_full_tb_pending; pending; pending = pending->next) {
        if (pending->cpu == cpu) {
            return pending;
        }
    }
    return NULL;
}

static void qrr_full_tb_pending_remove(QrrFullTbPending *pending)
{
    QrrFullTbPending **link = &qrr_full_tb_pending;

    while (*link && *link != pending) {
        link = &(*link)->next;
    }
    if (*link) {
        *link = pending->next;
        free(pending);
    }
}

static void qrr_full_tb_pending_remove_pgd(target_ulong pgd)
{
    QrrFullTbPending **link = &qrr_full_tb_pending;

    while (*link) {
        QrrFullTbPending *pending = *link;

        if (pending->pgd == pgd) {
            *link = pending->next;
            free(pending);
            continue;
        }
        link = &pending->next;
    }
}

static void qrr_full_tb_pending_remove_task(target_ulong pgd,
                                             target_ulong task)
{
    QrrFullTbPending **link = &qrr_full_tb_pending;

    while (*link) {
        QrrFullTbPending *pending = *link;

        if (pending->pgd == pgd && pending->task == task) {
            *link = pending->next;
            free(pending);
            continue;
        }
        link = &pending->next;
    }
}

static void qrr_full_user_edge_clone(target_ulong source_pgd,
                                     target_ulong target_pgd)
{
    QrrFullUserEdgeCount *entry;

    qrr_full_user_edge_remove_all(target_pgd);
    for (entry = qrr_full_user_edge_counts; entry; entry = entry->next) {
        QrrFullUserEdgeCount *copy;

        if (entry->pgd != source_pgd) {
            continue;
        }
        copy = malloc(sizeof(*copy));
        if (!copy) {
            fprintf(stderr, "qrr-full: cannot clone user edge counter\n");
            exit(2);
        }
        *copy = *entry;
        copy->pgd = target_pgd;
        copy->next = qrr_full_user_edge_counts;
        qrr_full_user_edge_counts = copy;
    }
}

static void qrr_full_user_precision_clone(target_ulong source_pgd,
                                          target_ulong target_pgd)
{
    QrrFullUserPrecisionWatch *watch;

    qrr_full_user_precision_remove_all(target_pgd);
    for (watch = qrr_full_user_precision_watches; watch;
         watch = watch->next) {
        if (watch->pgd == source_pgd) {
            qrr_full_user_precision_add(
                target_pgd, watch->task, watch->edge_from_pc, watch->pc,
                watch->delay_slot, watch->baseline_syscall_sequence,
                watch->baseline_occurrence);
        }
    }
}

static void qrr_full_reset_path_context(target_ulong pgd,
                                        uint64_t process_token)
{
    QrrFullPathState *state;

    qrr_full_user_edge_remove_all(pgd);
    qrr_full_user_precision_remove_all(pgd);
    qrr_full_tb_pending_remove_pgd(pgd);
    for (state = qrr_full_paths; state; state = state->next) {
        if (state->pgd == pgd) {
            QrrFullPathState *next = state->next;

            memset(state, 0, sizeof(*state));
            state->pgd = pgd;
            state->process_token = process_token;
            state->last_syscall = UINT64_MAX;
            state->next = next;
            return;
        }
    }
}

static void qrr_full_bind_process_token(target_ulong pgd,
                                        const char *process_name,
                                        uint64_t process_token,
                                        bool reset_path)
{
    QrrFullTargetPgd *target;

    if (!qrr_full_init() || !qrr_full_target_name || !process_name ||
        strcmp(process_name, qrr_full_target_name) != 0 || !process_token) {
        return;
    }
    target = qrr_full_target_process(pgd);
    if (target) {
        target->process_token = process_token;
        target->task = 0;
        target->have_task = false;
        target->exec_transitioning = false;
        if (reset_path) {
            qrr_full_reset_path_context(pgd, process_token);
        }
        return;
    }
    target = calloc(1, sizeof(*target));
    if (!target) {
        return;
    }
    target->pgd = pgd;
    target->process_token = process_token;
    target->next = qrr_full_target_pgds;
    qrr_full_target_pgds = target;
    if (reset_path) {
        qrr_full_reset_path_context(pgd, process_token);
    }
    fprintf(stderr, "qrr-full: bound target process %s pgd=" TARGET_FMT_lx
            " process=%016" PRIx64 "\n", process_name, pgd,
            process_token);
}

/* A vfork/clone child may have a distinct TGID while temporarily sharing the
 * parent's mm and therefore the same hardware PGD.  Process ownership is an
 * exact (process_token, task, tgid) binding; PGD alone is only an address
 * space identifier and is intentionally allowed to occur more than once. */
static QrrFullTargetPgd *qrr_full_bind_shared_process_token(
    target_ulong pgd, uint64_t process_token, target_ulong task,
    uint32_t tgid)
{
    QrrFullTargetPgd *target;

    target = qrr_full_target_process_for_token(process_token);
    if (target) {
        if (target->pgd != pgd || !target->have_task ||
            target->task != task || target->tgid != tgid) {
            fprintf(stderr,
                    "qrr-full: shared-mm process token conflict"
                    " process=%016" PRIx64 " pgd=" TARGET_FMT_lx
                    " task=" TARGET_FMT_lx " tgid=%u\n",
                    process_token, pgd, task, tgid);
            exit(2);
        }
        return target;
    }
    if (qrr_full_target_process_for_task(pgd, task) ||
        qrr_full_target_process_for_tgid(pgd, tgid)) {
        fprintf(stderr,
                "qrr-full: shared-mm process identity already owned"
                " process=%016" PRIx64 " pgd=" TARGET_FMT_lx
                " task=" TARGET_FMT_lx " tgid=%u\n",
                process_token, pgd, task, tgid);
        exit(2);
    }
    target = calloc(1, sizeof(*target));
    if (!target) {
        fprintf(stderr, "qrr-full: cannot allocate shared-mm process\n");
        exit(2);
    }
    target->pgd = pgd;
    target->process_token = process_token;
    target->task = task;
    target->tgid = tgid;
    target->have_task = true;
    target->next = qrr_full_target_pgds;
    qrr_full_target_pgds = target;
    return target;
}

static uint64_t qrr_full_bind_new_target_exec(target_ulong pgd)
{
    uint64_t process_token = qrr_full_new_root_process_token();

    qrr_full_bind_process_token(pgd, qrr_full_target_name, process_token,
                                true);
    fprintf(stderr, "qrr-full: new target execution pgd=" TARGET_FMT_lx
            " process=%016" PRIx64 "\n", pgd, process_token);
    return process_token;
}

static target_ulong qrr_full_exec_connector_address(void)
{
    return qrr_full_init() ? qrr_full_proc_exec_connector : 0;
}

static target_ulong qrr_full_exit_connector_address(void)
{
    return qrr_full_init() ? qrr_full_proc_exit_connector : 0;
}

static target_ulong qrr_full_fork_connector_address(void)
{
    return qrr_full_init() && qrr_full_follow_fork_descendants ?
        qrr_full_proc_fork_connector : 0;
}

static void qrr_full_note_exit_connector(target_ulong task)
{
    QrrFullTargetPgd *target;

    if (!qrr_full_init() || !qrr_full_follow_fork_descendants || !task) {
        return;
    }
    for (target = qrr_full_target_pgds; target; target = target->next) {
        if (target->have_task && target->task == task) {
            target_ulong pgd = target->pgd;
            uint64_t process_token = target->process_token;
            QrrFullExecPending *exec_pending =
                qrr_full_exec_pending_for_task(task);
            bool terminal_exec;

            /* proc_exec_connector is the successful-exec authority and a
             * return to entry_pc+4 is the failed-but-returning authority.
             * Reaching proc_exit_connector for the exact, single-task
             * process while its logical exec syscall is still pending proves
             * the third Linux outcome: exec crossed its point of no return
             * and terminated the process in-kernel.  The QrrFullPending is
             * authoritative for syscall lifetime.  QrrFullExecPending only
             * carries entry-side filename/argv metadata and may already have
             * been discarded after an apparent old-image return-PC visit; it
             * must not gate recording the observable kernel outcome. */
            if (exec_pending && exec_pending->pgd != pgd) {
                fprintf(stderr,
                        "qrr-full: terminal exec auxiliary identity conflict"
                        " task=" TARGET_FMT_lx " pgd=" TARGET_FMT_lx
                        " pending_pgd=" TARGET_FMT_lx "\n",
                        task, pgd, exec_pending->pgd);
                exit(2);
            }
            terminal_exec = qrr_full_record_terminal_exec(pgd, task);
            if (terminal_exec && !exec_pending) {
                fprintf(stderr,
                        "qrr-full: terminal exec used authoritative syscall"
                        " pending without auxiliary exec metadata task="
                        TARGET_FMT_lx " pgd=" TARGET_FMT_lx "\n",
                        task, pgd);
            } else if (!terminal_exec && exec_pending) {
                fprintf(stderr,
                        "qrr-full: terminal exec auxiliary has no matching"
                        " syscall task=" TARGET_FMT_lx
                        " pgd=" TARGET_FMT_lx "\n",
                        task, pgd);
                exit(2);
            }

            fprintf(stderr,
                    "qrr-full: exact target process exit task="
                    TARGET_FMT_lx " pgd=" TARGET_FMT_lx
                    " process=%016" PRIx64 "\n",
                    task, pgd, process_token);
            qrr_full_unbind_process_token(process_token,
                                          "proc-exit-connector");
            return;
        }
    }
}

/* QRR resolves pgd_current from the exact configured vmlinux.  This avoids
 * both the global VMI process table and DECAF's legacy TLB-refill-handler
 * signature scan. */
static target_ulong qrr_full_current_pgd(CPUState *cpu)
{
#ifdef TARGET_MIPS
    target_ulong symbol = qrr_full_pgd_current;
    target_ulong pgd;
    gpa_t symbol_phys;

    if (symbol >= UINT32_C(0x80000000) &&
        symbol < UINT32_C(0xa0000000)) {
        symbol_phys = symbol - UINT32_C(0x80000000);
    } else if (symbol >= UINT32_C(0xa0000000) &&
               symbol < UINT32_C(0xc0000000)) {
        symbol_phys = symbol - UINT32_C(0xa0000000);
    } else {
        fprintf(stderr,
                "qrr-full: exact pgd_current symbol is not direct-mapped: "
                TARGET_FMT_lx "\n", symbol);
        exit(2);
    }
    pgd = ldl_phys(cpu->as, symbol_phys);
    if (pgd >= UINT32_C(0x80000000) && pgd < UINT32_C(0xa0000000)) {
        return pgd - UINT32_C(0x80000000);
    }
    if (pgd >= UINT32_C(0xa0000000) && pgd < UINT32_C(0xc0000000)) {
        return pgd - UINT32_C(0xa0000000);
    }
    fprintf(stderr,
            "qrr-full: pgd_current value is not direct-mapped: "
            TARGET_FMT_lx "\n", pgd);
    exit(2);
#else
    return DECAF_getPGD(cpu);
#endif
}

static void qrr_full_request_initial_layout(uint64_t process_token)
{
    QrrFullLayoutCaptured *request;

    if (!qrr_full_layout_fp) {
        return;
    }
    request = calloc(1, sizeof(*request));
    if (!request) {
        fprintf(stderr, "qrr-full: cannot allocate target layout request\n");
        exit(2);
    }
    request->process_token = process_token;
    request->next = qrr_full_layout_captured;
    qrr_full_layout_captured = request;
}

static QrrFullExecPending *qrr_full_exec_pending_for_task(
    target_ulong task)
{
    QrrFullExecPending *pending;

    for (pending = qrr_full_exec_pending; pending; pending = pending->next) {
        if (pending->have_task && pending->task == task) {
            return pending;
        }
    }
    return NULL;
}

static void qrr_full_record_exec_launch(CPUState *cpu,
                                        target_ulong task,
                                        QrrFullExecPending *pending)
{
    char cwd[QRR_VMI_CWD_SIZE];
    char error[128];
    char *cwd_hex;

    if (!pending || !pending->filename_hex || !pending->argv_hex ||
        pending->capture_error[0]) {
        fprintf(stderr,
                "qrr-full: successful target exec metadata incomplete"
                " task=" TARGET_FMT_lx " source_pgd=" TARGET_FMT_lx
                " reason=%s\n",
                task, pending ? pending->pgd : 0,
                pending && pending->capture_error[0] ?
                    pending->capture_error : "missing-exec-pending");
        exit(2);
    }
    if (VMI_qrr_read_exec_cwd_c(cpu, task, cwd, sizeof(cwd),
                                error, sizeof(error)) != 0) {
        fprintf(stderr,
                "qrr-full: successful target exec cwd capture failed"
                " task=" TARGET_FMT_lx " source_pgd=" TARGET_FMT_lx
                " reason=%s\n",
                task, pending->pgd, error[0] ? error : "unknown");
        exit(2);
    }
    cwd_hex = qrr_full_hex_from_bytes((const unsigned char *)cwd,
                                      strlen(cwd));
    if (!cwd_hex) {
        fprintf(stderr, "qrr-full: target exec cwd encoding failed\n");
        exit(2);
    }
    if (qrr_full_exec_fp) {
        fprintf(qrr_full_exec_fp,
                "%" PRIu64 "\t" TARGET_FMT_lx "\t" TARGET_FMT_lx
                "\t%d\t%u\t%s\t%s\t%s\trecord\tsuccessful_exec\n",
                ++qrr_full_exec_sequence, pending->pgd,
                pending->entry_pc, pending->syscall_nr, pending->argc,
                pending->filename_hex, pending->argv_hex, cwd_hex);
        if (fflush(qrr_full_exec_fp) != 0) {
            fprintf(stderr,
                    "qrr-full: target exec table flush failed: %s\n",
                    strerror(errno));
            exit(2);
        }
    }
    fprintf(stderr,
            "qrr-full: recorded successful target exec task="
            TARGET_FMT_lx " source_pgd=" TARGET_FMT_lx " cwd=%s argc=%u\n",
            task, pending->pgd, cwd, pending->argc);
    free(cwd_hex);
}

/* Called only from the optimized proc_exec_connector TB hook.  The first
 * successful exec whose exact task comm matches the configured target owns
 * the root process token.  Later same-name execs do not independently acquire
 * a token; fork descendants are attached only by the exact
 * proc_fork_connector lifecycle hook. */
static void qrr_full_note_exec_connector(CPUState *cpu,
                                         target_ulong task)
{
    qrr_vmi_exec_identity_t identity;
    QrrFullExecPending *exec_pending;
    QrrFullTargetPgd *bound_process;
    char error[128];
    uint64_t process_token;

    if (!qrr_full_init()) {
        return;
    }
    if (qrr_full_target_locked && !qrr_full_target_active) {
        return;
    }
    if (VMI_qrr_read_exec_identity_c(cpu, task, &identity,
                                     error, sizeof(error)) != 0) {
        fprintf(stderr,
                "qrr-full: proc_exec_connector identity read failed"
                " task=" TARGET_FMT_lx " reason=%s\n",
                task, error[0] ? error : "unknown");
        exit(2);
    }
    exec_pending = qrr_full_exec_pending_for_task(task);
    if (qrr_full_target_locked) {
        if (exec_pending && exec_pending->source_was_target) {
            QrrFullTargetPgd *source_process =
                qrr_full_target_process_for_token(
                    exec_pending->process_token);

            if (source_process && source_process->have_task &&
                source_process->task == task) {
                /* exec replaces the calling task's mm before the connector
                 * reports the committed image.  Complete this exact
                 * task-bound transition from its source binding even when
                 * Linux has already handed the old PGD to another process. */
                exec_pending->target_match =
                    strcmp(identity.name, qrr_full_target_name) == 0;
                if (exec_pending->pgd == qrr_full_selected_pgd) {
                    qrr_full_selected_pgd = exec_pending->target_match ?
                        identity.pgd : 0;
                    qrr_full_selected_task = exec_pending->target_match ?
                        identity.task : 0;
                }
                qrr_full_complete_exec_transition(
                    cpu, exec_pending, identity.pgd,
                    "proc_exec_connector-task-transition");
                return;
            }
        }
        bound_process = qrr_full_target_process_for_task(
            identity.pgd, identity.task);
        if (!bound_process) {
            bound_process = qrr_full_target_process_for_tgid(
                identity.pgd, identity.tgid);
        }
        if (bound_process) {
            if (!exec_pending) {
                if (strcmp(identity.name, qrr_full_target_name) != 0) {
                    /* Linux may reuse a dead descendant's physical PGD for
                     * an unrelated process before a userspace exit syscall
                     * was observable.  The exact connector task has no exec
                     * entry belonging to the bound execution, proving this
                     * is stale PGD ownership rather than a target exec. */
                    fprintf(stderr,
                            "qrr-full: proc_exec_connector proved stale"
                            " target PGD reuse pgd=" TARGET_FMT_lx
                            " process=%016" PRIx64 " task=" TARGET_FMT_lx
                            " new_name=%s; unbinding\n",
                            identity.pgd, bound_process->process_token,
                            identity.task, identity.name);
                    qrr_full_unbind_process(identity.pgd,
                                            "exec-pgd-reuse");
                    return;
                }
                fprintf(stderr,
                        "qrr-full: bound process successful exec has no"
                        " exact filename/argv/task association"
                        " pgd=" TARGET_FMT_lx " task=" TARGET_FMT_lx
                        " name=%s\n",
                        identity.pgd, identity.task, identity.name);
                exit(2);
            }
            /* proc_exec_connector is the authoritative successful-exec
             * event.  Its exact task identity decides whether this execution
             * remains the configured target; filename matching is used only
             * to associate the entry-side argv record. */
            exec_pending->target_match =
                strcmp(identity.name, qrr_full_target_name) == 0;
            if (exec_pending->pgd == qrr_full_selected_pgd) {
                qrr_full_selected_pgd = exec_pending->target_match ?
                    identity.pgd : 0;
                qrr_full_selected_task = exec_pending->target_match ?
                    identity.task : 0;
            }
            qrr_full_complete_exec_transition(
                cpu, exec_pending, identity.pgd, "proc_exec_connector");
            return;
        }
        if (strcmp(identity.name, qrr_full_target_name) == 0) {
            fprintf(stderr,
                    "qrr-full: ignored additional target execution"
                    " name=%s pid=%" PRIu32 " pgd=" TARGET_FMT_lx
                    " selected_pgd=" TARGET_FMT_lx "\n",
                    identity.name, identity.pid, identity.pgd,
                    qrr_full_selected_pgd);
        }
        /* The process was never in the selected fork family. */
        if (exec_pending) {
            qrr_full_remove_exec_pending(exec_pending);
        }
        return;
    }
    if (strcmp(identity.name, qrr_full_target_name) != 0) {
        if (exec_pending) {
            qrr_full_remove_exec_pending(exec_pending);
        }
        return;
    }
    if (qrr_full_exec_fp) {
        if (!exec_pending) {
            fprintf(stderr,
                    "qrr-full: successful target exec has no exact"
                    " filename/argv/task association task=" TARGET_FMT_lx
                    " name=%s\n", task, identity.name);
            exit(2);
        }
        qrr_full_record_exec_launch(cpu, task, exec_pending);
    }
    if (exec_pending) {
        qrr_full_remove_exec_pending(exec_pending);
    }
    qrr_full_target_locked = true;
    qrr_full_target_active = true;
    qrr_full_selected_pgd = identity.pgd;
    qrr_full_selected_task = identity.task;
    process_token = qrr_full_bind_new_target_exec(identity.pgd);
    bound_process = qrr_full_target_process_for_token(process_token);
    if (!bound_process) {
        fprintf(stderr, "qrr-full: selected target binding disappeared\n");
        exit(2);
    }
    bound_process->task = identity.task;
    bound_process->tgid = identity.tgid;
    bound_process->have_task = true;
    if (!qrr_full_thread_identity(identity.pgd, identity.task,
                                  identity.tgid, true)) {
        fprintf(stderr,
                "qrr-full: cannot bind selected target thread identity"
                " task=" TARGET_FMT_lx " pgd=" TARGET_FMT_lx "\n",
                identity.task, identity.pgd);
        exit(2);
    }
    /* proc_exec_connector may be the final kernel TB before returning to
     * userspace.  Cache its authoritative current task immediately instead
     * of waiting for another kernel TB that may never execute before the
     * first syscall trap. */
    qrr_full_set_cpu_thread(cpu, identity.pgd, identity.task);
    qrr_full_request_initial_layout(process_token);
    fprintf(stderr,
            "qrr-full: selected target from proc_exec_connector"
            " name=%s pid=%" PRIu32 " task=" TARGET_FMT_lx
            " mm=" TARGET_FMT_lx " pgd=" TARGET_FMT_lx
            " process=%016" PRIx64 "\n",
            identity.name, identity.pid, identity.task, identity.mm,
            identity.pgd, process_token);
}

static QrrFullProcessIdentity *qrr_full_process_identity(target_ulong pgd)
{
    QrrFullProcessIdentity *entry;

    for (entry = qrr_full_process_identities; entry; entry = entry->next) {
        if (entry->pgd == pgd) {
            return entry;
        }
    }
    return NULL;
}

static void qrr_full_note_process_identity(target_ulong pgd,
                                           const char *process_name,
                                           uint32_t pid,
                                           uint32_t parent_pid)
{
    QrrFullProcessIdentity *entry;

    if (pid == UINT32_MAX) {
        return;
    }
    entry = qrr_full_process_identity(pgd);
    if (!entry) {
        entry = calloc(1, sizeof(*entry));
        if (!entry) {
            return;
        }
        entry->pgd = pgd;
        entry->next = qrr_full_process_identities;
        qrr_full_process_identities = entry;
    }
    entry->pid = pid;
    entry->parent_pid = parent_pid;
    if (qrr_full_trace_pgd(pgd) && qrr_full_target_name && process_name &&
        strcmp(process_name, qrr_full_target_name) != 0) {
        fprintf(stderr,
                "qrr-full: process identity changed pgd=" TARGET_FMT_lx
                " name=%s; unbinding non-target execution\n",
                pgd, process_name);
        qrr_full_unbind_process(pgd, process_name);
    }
}

static void qrr_full_free_mmap_mapping(QrrFullMmapMapping *mapping)
{
    QrrFullMmapPage *page;

    if (!mapping) {
        return;
    }
    page = mapping->pages;
    while (page) {
        QrrFullMmapPage *next = page->next;

        free(page);
        page = next;
    }
    free(mapping->path);
    free(mapping);
}

static void qrr_full_mmap_remove_all(target_ulong pgd)
{
    QrrFullMmapMapping **link = &qrr_full_mmap_mappings;

    while (*link) {
        QrrFullMmapMapping *mapping = *link;

        if (mapping->pgd == pgd) {
            *link = mapping->next;
            qrr_full_free_mmap_mapping(mapping);
            continue;
        }
        link = &mapping->next;
    }
}

static void qrr_full_pending_remove_all(target_ulong pgd)
{
    QrrFullSemaphoreLockCall **semaphore_link =
        &qrr_full_semaphore_lock_calls;
    QrrFullSignalCall **signal_link = &qrr_full_signal_calls;
    QrrFullPageFaultCall **fault_link = &qrr_full_page_fault_calls;
    QrrFullPending **pending_link = &qrr_full_pending_head;

    while (*semaphore_link) {
        QrrFullSemaphoreLockCall *call = *semaphore_link;

        if (call->pgd == pgd) {
            *semaphore_link = call->next;
            free(call);
            continue;
        }
        semaphore_link = &call->next;
    }
    while (*signal_link) {
        QrrFullSignalCall *call = *signal_link;

        if (call->pgd == pgd) {
            *signal_link = call->next;
            free(call);
            continue;
        }
        signal_link = &call->next;
    }
    while (*fault_link) {
        QrrFullPageFaultCall *call = *fault_link;

        if (call->pgd == pgd) {
            *fault_link = call->next;
            free(call);
            continue;
        }
        fault_link = &call->next;
    }
    while (*pending_link) {
        QrrFullPending *pending = *pending_link;

        if (pending->pgd == pgd) {
            *pending_link = pending->next;
            free(pending->open_path);
            free(pending->semaphore_values);
            free(pending);
            continue;
        }
        pending_link = &pending->next;
    }
}

static void qrr_full_exec_pending_remove_all(target_ulong pgd)
{
    QrrFullExecPending *pending;

    do {
        pending = qrr_full_exec_pending;
        while (pending && pending->pgd != pgd) {
            pending = pending->next;
        }
        if (pending) {
            qrr_full_remove_exec_pending(pending);
        }
    } while (pending);
}

static void qrr_full_unbind_process(target_ulong pgd, const char *process_name)
{
    QrrFullTargetPgd *target = qrr_full_target_pgds;
    QrrFullTargetPgd *previous = NULL;

    while (target) {
        if (target->pgd == pgd) {
            if (previous) {
                previous->next = target->next;
            } else {
                qrr_full_target_pgds = target->next;
            }
            fprintf(stderr, "qrr-full: unbound process pgd=" TARGET_FMT_lx
                    " process=%016" PRIx64 " name=%s\n", pgd,
                    target->process_token,
                    process_name && process_name[0] ? process_name : "-");
            free(target);
            break;
        }
        previous = target;
        target = target->next;
    }
    {
        QrrFullPathState **link = &qrr_full_paths;
        QrrFullThreadIdentity **thread_link = &qrr_full_threads;

        while (*link) {
            QrrFullPathState *state = *link;
            if (state->pgd == pgd) {
                *link = state->next;
                free(state);
                continue;
            }
            link = &state->next;
        }
        while (*thread_link) {
            QrrFullThreadIdentity *thread = *thread_link;
            if (thread->pgd == pgd) {
                *thread_link = thread->next;
                free(thread);
                continue;
            }
            thread_link = &thread->next;
        }
    }
    qrr_full_pending_remove_all(pgd);
    qrr_full_exec_pending_remove_all(pgd);
    qrr_full_fd_remove_all(pgd);
    qrr_full_mmap_remove_all(pgd);
    qrr_full_user_edge_remove_all(pgd);
    qrr_full_user_precision_remove_all(pgd);
    qrr_full_tb_pending_remove_pgd(pgd);
    if (pgd == qrr_full_selected_pgd &&
        !qrr_full_follow_fork_descendants) {
        qrr_full_target_active = false;
    }
}

static void qrr_full_unbind_process_token(uint64_t process_token,
                                          const char *reason)
{
    QrrFullTargetPgd **target_link = &qrr_full_target_pgds;
    QrrFullTargetPgd *target = NULL;
    QrrFullPathState **path_link;
    QrrFullThreadIdentity **thread_link;
    QrrFullPending **pending_link;
    QrrFullMmapMapping **mapping_link;
    QrrFullPageFaultCall **fault_link;
    QrrFullSemaphoreLockCall **semaphore_link;
    QrrFullCpuThread *cpu_thread;
    target_ulong pgd;

    while (*target_link) {
        if ((*target_link)->process_token == process_token) {
            target = *target_link;
            *target_link = target->next;
            break;
        }
        target_link = &(*target_link)->next;
    }
    if (!target) {
        return;
    }
    pgd = target->pgd;
    fprintf(stderr,
            "qrr-full: unbound exact process pgd=" TARGET_FMT_lx
            " process=%016" PRIx64 " reason=%s\n",
            pgd, process_token, reason && reason[0] ? reason : "-");
    free(target);

    path_link = &qrr_full_paths;
    while (*path_link) {
        QrrFullPathState *state = *path_link;

        if (state->process_token == process_token) {
            qrr_full_user_edge_remove_task(state->pgd, state->task);
            qrr_full_user_precision_remove_task(state->pgd, state->task);
            qrr_full_tb_pending_remove_task(state->pgd, state->task);
            for (cpu_thread = qrr_full_cpu_threads; cpu_thread;
                 cpu_thread = cpu_thread->next) {
                if (cpu_thread->pgd == state->pgd &&
                    cpu_thread->task == state->task) {
                    cpu_thread->task = 0;
                }
            }
            *path_link = state->next;
            free(state);
            continue;
        }
        path_link = &(*path_link)->next;
    }
    thread_link = &qrr_full_threads;
    while (*thread_link) {
        QrrFullThreadIdentity *thread = *thread_link;

        if (thread->process_token == process_token) {
            *thread_link = thread->next;
            free(thread);
            continue;
        }
        thread_link = &(*thread_link)->next;
    }
    semaphore_link = &qrr_full_semaphore_lock_calls;
    while (*semaphore_link) {
        QrrFullSemaphoreLockCall *call = *semaphore_link;

        if (call->pending &&
            call->pending->process_token == process_token) {
            *semaphore_link = call->next;
            free(call);
            continue;
        }
        semaphore_link = &(*semaphore_link)->next;
    }
    pending_link = &qrr_full_pending_head;
    while (*pending_link) {
        QrrFullPending *pending = *pending_link;

        if (pending->process_token == process_token) {
            *pending_link = pending->next;
            free(pending->open_path);
            free(pending->semaphore_values);
            free(pending);
            continue;
        }
        pending_link = &(*pending_link)->next;
    }
    {
        QrrFullExecPending *exec_pending;

        do {
            exec_pending = qrr_full_exec_pending;
            while (exec_pending &&
                   exec_pending->process_token != process_token) {
                exec_pending = exec_pending->next;
            }
            if (exec_pending) {
                qrr_full_remove_exec_pending(exec_pending);
            }
        } while (exec_pending);
    }
    mapping_link = &qrr_full_mmap_mappings;
    while (*mapping_link) {
        QrrFullMmapMapping *mapping = *mapping_link;

        if (mapping->process_token == process_token) {
            *mapping_link = mapping->next;
            qrr_full_free_mmap_mapping(mapping);
            continue;
        }
        mapping_link = &(*mapping_link)->next;
    }
    fault_link = &qrr_full_page_fault_calls;
    while (*fault_link) {
        QrrFullPageFaultCall *call = *fault_link;

        if (call->process_token == process_token) {
            *fault_link = call->next;
            free(call);
            continue;
        }
        fault_link = &(*fault_link)->next;
    }
    /* FD path metadata is still keyed by the shared address-space identity.
     * Preserve it while another tracked owner uses that PGD; remove it only
     * when the last owner leaves. */
    if (!qrr_full_target_process(pgd)) {
        qrr_full_fd_remove_all(pgd);
    }
    if (!qrr_full_target_pgds) {
        qrr_full_target_active = false;
    }
}

static QrrFullPathState *qrr_full_path_state_for_task(target_ulong pgd,
                                                      target_ulong task,
                                                      bool create);

static QrrFullPathState *qrr_full_path_state(target_ulong pgd, bool create)
{
    return qrr_full_path_state_for_task(pgd, 0, create);
}

static QrrFullPathState *qrr_full_path_state_for_task(target_ulong pgd,
                                                      target_ulong task,
                                                      bool create)
{
    QrrFullPathState *state;

    for (state = qrr_full_paths; state; state = state->next) {
        if (state->pgd == pgd && (!task || state->task == task)) {
            return state;
        }
    }
    if (!create) {
        return NULL;
    }
    state = malloc(sizeof(*state));
    if (!state) {
        return NULL;
    }
    memset(state, 0, sizeof(*state));
    state->pgd = pgd;
    state->task = task;
    {
        QrrFullThreadIdentity *thread =
            qrr_full_thread_identity_find(pgd, task);
        QrrFullTargetPgd *target = thread ?
            qrr_full_target_process_for_token(thread->process_token) :
            qrr_full_target_process_for_task(pgd, task);

        state->process_token = target ? target->process_token : 0;
        if (target) {
            if (!thread) {
                thread = qrr_full_thread_identity(
                    pgd, task, target->tgid, true);
            }
            state->thread_token = thread ? thread->thread_token : 0;
        }
    }
    state->last_syscall = UINT64_MAX;
    state->next = qrr_full_paths;
    qrr_full_paths = state;
    return state;
}

static void qrr_full_remove_exec_pending(QrrFullExecPending *pending)
{
    QrrFullExecPending **link = &qrr_full_exec_pending;

    while (*link) {
        if (*link == pending) {
            *link = pending->next;
            free(pending->filename_hex);
            free(pending->argv_hex);
            free(pending);
            return;
        }
        link = &(*link)->next;
    }
}

static void qrr_full_record_successful_exec(target_ulong source_pgd,
                                            target_ulong task,
                                            bool target_match,
                                            uint64_t next_process_token);

static void qrr_full_write_result_row(const QrrFullPending *pending,
                                      int64_t ret, int out_arg,
                                      const char *hex)
{
    if (!qrr_full_table_fp) {
        return;
    }
    if (qrr_full_thread_context) {
        fprintf(qrr_full_table_fp,
                "%016" PRIx64 "\t%016" PRIx64 "\t%016" PRIx64
                "\t%d\t%" PRIu64 "\t%" PRId64 "\t%d\t%s\t%016" PRIx64
                "\t%016" PRIx64 "\n", pending->key, pending->path_hash,
                pending->dep_hash, pending->syscall_nr, pending->sequence,
                ret, out_arg, hex, pending->process_token,
                pending->thread_token);
    } else {
        fprintf(qrr_full_table_fp,
                "%016" PRIx64 "\t%016" PRIx64 "\t%016" PRIx64
                "\t%d\t%" PRIu64 "\t%" PRId64 "\t%d\t%s\t%016" PRIx64
                "\n", pending->key, pending->path_hash, pending->dep_hash,
                pending->syscall_nr, pending->sequence, ret, out_arg, hex,
                pending->process_token);
    }
}

static void qrr_full_track_target_exec_in_kernel(CPUState *cpu)
{
#ifdef TARGET_MIPS
    CPUArchState *env = cpu->env_ptr;
    QrrFullExecPending *pending;
    target_ulong kernel_sp;
    target_ulong thread_info;
    target_ulong task;
    target_ulong pgd;
    char error[128];

    kernel_sp = env->active_tc.gpr[29];
    if (kernel_sp < 0x80000000) {
        return;
    }
    thread_info = kernel_sp & ~(QRR_FULL_MIPS_THREAD_SIZE - 1);
    pgd = qrr_full_current_pgd(cpu);
    qrr_full_last_kernel_thread_info = thread_info;
    qrr_full_have_last_kernel_thread_info = true;
    for (pending = qrr_full_exec_pending; pending; pending = pending->next) {
        if (pending->cpu == cpu && pending->pgd == pgd &&
            pending->have_thread_info && pending->thread_info == thread_info) {
            return;
        }
    }
    for (pending = qrr_full_exec_pending; pending; pending = pending->next) {
        if (pending->cpu == cpu && pending->pgd == pgd &&
            !pending->have_thread_info) {
            if (VMI_qrr_task_from_thread_info_c(
                    cpu, thread_info, &task, error, sizeof(error)) != 0) {
                fprintf(stderr,
                        "qrr-full: target exec task lookup failed"
                        " thread_info=" TARGET_FMT_lx " reason=%s\n",
                        thread_info, error[0] ? error : "unknown");
                exit(2);
            }
            pending->thread_info = thread_info;
            pending->have_thread_info = true;
            {
                qrr_vmi_exec_identity_t identity;
                QrrFullTargetPgd *target;

                if (pending->have_task && pending->task != task) {
                    fprintf(stderr,
                            "qrr-full: exec pending task association changed"
                            " pgd=" TARGET_FMT_lx
                            " expected_task=" TARGET_FMT_lx
                            " actual_task=" TARGET_FMT_lx "\n",
                            pgd, pending->task, task);
                    exit(2);
                }
                pending->task = task;
                pending->have_task = true;
                if (VMI_qrr_read_exec_identity_c(
                        cpu, task, &identity, error,
                        sizeof(error)) != 0) {
                    fprintf(stderr,
                            "qrr-full: target exec identity lookup failed"
                            " task=" TARGET_FMT_lx " reason=%s\n", task,
                            error[0] ? error : "unknown");
                    exit(2);
                }
                target = pending->process_token ?
                    qrr_full_target_process_for_token(
                        pending->process_token) :
                    qrr_full_target_process_for_tgid(pgd, identity.tgid);

                if (target) {
                    if (target->have_task && target->task != task) {
                        fprintf(stderr,
                                "qrr-full: exec task changed within target"
                                " PGD pgd=" TARGET_FMT_lx
                                " old_task=" TARGET_FMT_lx
                                " new_task=" TARGET_FMT_lx "\n",
                                pgd, target->task, task);
                        exit(2);
                    }
                    target->task = task;
                    target->have_task = true;
                    target->tgid = identity.tgid;
                    if (!qrr_full_thread_identity(pgd, task, identity.tgid,
                                                  true)) {
                        fprintf(stderr,
                                "qrr-full: cannot bind target exec thread"
                                " task=" TARGET_FMT_lx "\n", task);
                        exit(2);
                    }
                    qrr_full_set_cpu_thread(cpu, pgd, task);
                }
            }
            fprintf(stderr,
                    "qrr-full: exec pending thread_info=" TARGET_FMT_lx
                    " task=" TARGET_FMT_lx " source_pgd=" TARGET_FMT_lx
                    "\n", thread_info, task, pending->pgd);
            return;
        }
    }
#else
    (void)cpu;
#endif
}

static void qrr_full_note_current_target_task(CPUState *cpu,
                                              target_ulong pgd)
{
#ifdef TARGET_MIPS
    CPUArchState *env = cpu->env_ptr;
    QrrFullTargetPgd *target;
    QrrFullTargetPgd *candidate;
    QrrFullThreadIdentity *thread;
    qrr_vmi_exec_identity_t identity;
    target_ulong kernel_sp = env->active_tc.gpr[29];
    target_ulong thread_info;
    target_ulong task;
    char error[128];

    if (!qrr_full_trace_pgd(pgd) ||
        kernel_sp < UINT32_C(0x80000000)) {
        return;
    }
    thread_info = kernel_sp & ~(QRR_FULL_MIPS_THREAD_SIZE - 1);
    if (VMI_qrr_task_from_thread_info_c(
            cpu, thread_info, &task, error, sizeof(error)) != 0 ||
        VMI_qrr_read_exec_identity_c(
            cpu, task, &identity, error, sizeof(error)) != 0 ||
        identity.pgd != pgd) {
        /* A kernel thread can temporarily borrow this active_mm.  It is not
         * an execution identity for the selected userspace process. */
        return;
    }
    thread = qrr_full_thread_identity_find(pgd, task);
    if (thread) {
        target = qrr_full_target_process_for_token(thread->process_token);
        if (!target || target->pgd != pgd ||
            thread->tgid != identity.tgid) {
            fprintf(stderr,
                    "qrr-full: cached exact thread identity conflict pgd="
                    TARGET_FMT_lx " task=" TARGET_FMT_lx
                    " tgid=%u process=%016" PRIx64 "\n",
                    pgd, task, identity.tgid, thread->process_token);
            exit(2);
        }
        qrr_full_set_cpu_thread(cpu, pgd, task);
        return;
    }
    target = qrr_full_target_process_for_tgid(pgd, identity.tgid);
    if (!target) {
        /* A successful exec can move the exact tracked task to a new mm
         * before proc_exec_connector commits the transition.  Detect only
         * that task-bound state; a different TGID merely borrowing the mm is
         * not classified as a target process or target thread. */
        for (candidate = qrr_full_target_pgds; candidate;
             candidate = candidate->next) {
            qrr_vmi_exec_identity_t previous;
            QrrFullExecPending *transition;

            if (candidate->pgd != pgd || !candidate->have_task) {
                continue;
            }
            memset(&previous, 0, sizeof(previous));
            transition = qrr_full_exec_pending_for_task(candidate->task);
            if (VMI_qrr_read_exec_identity_c(
                    cpu, candidate->task, &previous,
                    error, sizeof(error)) == 0 && transition &&
                transition->source_was_target &&
                transition->pgd == pgd && transition->have_task &&
                transition->task == candidate->task && previous.pgd != pgd) {
                candidate->exec_transitioning = true;
                fprintf(stderr,
                    "qrr-full: target exec left source PGD"
                    " process=%016" PRIx64
                    " source_pgd=" TARGET_FMT_lx
                    " task=" TARGET_FMT_lx
                    " old_pid=%u old_tgid=%u new_pgd=" TARGET_FMT_lx
                    " replacement_task=" TARGET_FMT_lx
                    " replacement_pid=%u replacement_tgid=%u\n",
                    candidate->process_token, pgd, candidate->task,
                    previous.pid, previous.tgid, previous.pgd, task,
                    identity.pid, identity.tgid);
                return;
            }
        }
        return;
    }
    if (!target->have_task) {
        target->task = task;
        target->tgid = identity.tgid;
        target->have_task = true;
    } else if (target->task != task) {
        if (!qrr_full_thread_identity(pgd, task, identity.tgid, true)) {
            fprintf(stderr,
                    "qrr-full: cannot allocate thread identity pgd="
                    TARGET_FMT_lx " task=" TARGET_FMT_lx "\n", pgd, task);
            exit(2);
        }
    }
    if (!qrr_full_thread_identity(pgd, task, identity.tgid, true)) {
        fprintf(stderr,
                "qrr-full: cannot allocate leader thread identity pgd="
                TARGET_FMT_lx " task=" TARGET_FMT_lx "\n", pgd, task);
        exit(2);
    }
    qrr_full_set_cpu_thread(cpu, pgd, task);
#else
    (void)cpu;
    (void)pgd;
#endif
}

static void qrr_full_complete_exec_transition(CPUState *cpu,
                                              QrrFullExecPending *pending,
                                              target_ulong pgd,
                                              const char *completion)
{
    target_ulong source_pgd = pending->pgd;
    target_ulong exec_task = pending->have_task ? pending->task : 0;
    uint64_t source_process_token = pending->process_token;
    bool target_match = pending->target_match;
    uint64_t next_process_token = 0;

    /* Unbind below also clears every stale exec association for the old mm.
     * Detach the exact completing record first so it cannot be freed twice. */
    qrr_full_remove_exec_pending(pending);

    if (target_match) {
        if (source_pgd != pgd) {
            qrr_full_clone_process_state(source_pgd, exec_task, pgd);
        }
        next_process_token = qrr_full_bind_new_target_exec(pgd);
        if (exec_task) {
            QrrFullTargetPgd *target =
                qrr_full_target_process_for_token(next_process_token);
            qrr_vmi_exec_identity_t identity;
            char error[128];

            if (!target) {
                fprintf(stderr,
                        "qrr-full: target exec binding disappeared\n");
                exit(2);
            }
            target->task = exec_task;
            target->have_task = true;
            if (VMI_qrr_read_exec_identity_c(cpu, exec_task, &identity,
                                             error, sizeof(error)) != 0) {
                fprintf(stderr,
                        "qrr-full: completed exec identity lookup failed"
                        " task=" TARGET_FMT_lx " reason=%s\n", exec_task,
                        error[0] ? error : "unknown");
                exit(2);
            }
            target->tgid = identity.tgid;
            if (!qrr_full_thread_identity(pgd, exec_task, identity.tgid,
                                          true)) {
                fprintf(stderr,
                        "qrr-full: completed exec thread bind failed"
                        " task=" TARGET_FMT_lx "\n", exec_task);
                exit(2);
            }
            qrr_full_set_cpu_thread(cpu, pgd, exec_task);
        }
        if (qrr_full_layout_fp) {
            QrrFullLayoutCaptured *request = calloc(1, sizeof(*request));

            if (!request) {
                fprintf(stderr,
                        "qrr-full: cannot allocate target layout request\n");
                exit(2);
            }
            request->process_token = next_process_token;
            request->next = qrr_full_layout_captured;
            qrr_full_layout_captured = request;
        }
        qrr_full_record_successful_exec(source_pgd, exec_task, true,
                                        next_process_token);
        if (source_process_token &&
            source_process_token != next_process_token) {
            qrr_full_unbind_process_token(source_process_token,
                                          "exec-source");
        }
        fprintf(stderr,
                "qrr-full: target exec completed via=%s pgd=" TARGET_FMT_lx
                "\n", completion, pgd);
    } else {
        qrr_full_record_successful_exec(source_pgd, exec_task, false, 0);
        if (source_process_token) {
            qrr_full_unbind_process_token(source_process_token,
                                          "exec-non-target");
        }
        fprintf(stderr,
                "qrr-full: non-target exec completed via=%s source_pgd="
                TARGET_FMT_lx " pgd=" TARGET_FMT_lx "\n",
                completion, source_pgd, pgd);
    }
}

static void qrr_full_bind_target_exec_transition(CPUState *cpu,
                                                 target_ulong pc)
{
#ifdef TARGET_MIPS
    QrrFullExecPending *pending;
    target_ulong pgd;

    if (!qrr_full_have_last_kernel_thread_info) {
        return;
    }
    for (pending = qrr_full_exec_pending; pending; pending = pending->next) {
        if (pending->cpu == cpu && pending->have_thread_info &&
            pending->thread_info == qrr_full_last_kernel_thread_info) {
            break;
        }
    }
    if (!pending) {
        return;
    }
    pgd = qrr_full_current_pgd(cpu);
#ifdef TARGET_MIPS
    if (pgd == pending->pgd && pc == pending->entry_pc + 4) {
        return;
    }
#elif defined(TARGET_ARM)
    if (pgd == pending->pgd && pc == pending->entry_pc) {
        return;
    }
#endif
    qrr_full_complete_exec_transition(cpu, pending, pgd,
                                      "thread-transition");
#else
    (void)cpu;
#endif
}

static void qrr_full_tb_before(CPUState *cpu, TranslationBlock *itb)
{
    QrrFullPathState *state;
    QrrFullTbPending *pending;
    target_ulong pgd;
    target_ulong task;
    target_ulong pc = itb->pc;

    if (!qrr_full_init()) {
        return;
    }
    /* Exec filename/argv are captured at the user syscall boundary.  While
     * that one exact target exec is pending, bind it to current->task from
     * the first kernel TB so proc_exec_connector can prove the successful
     * execution instance before the v2 launch row is emitted. */
    if (qrr_full_exec_pending) {
        qrr_full_track_target_exec_in_kernel(cpu);
    }
    /* Before proc_exec_connector selects the target there is no QRR TB work
     * and, in particular, no reason to inspect any current address space. */
    if (!qrr_full_target_active) {
        return;
    }
    pgd = qrr_full_current_pgd(cpu);
    if (!qrr_full_trace_pgd(pgd)) {
        return;
    }
    if (!qrr_full_user_pc(pc)) {
        qrr_full_note_current_target_task(cpu, pgd);
        if (!qrr_full_trace_pgd(pgd)) {
            return;
        }
    }
    qrr_full_note_page_fault(cpu, pc);
    qrr_full_note_signal_delivery(cpu, pc);
    qrr_full_note_semaphore_lock(cpu, pc);
    if (!qrr_full_user_pc(pc)) {
        return;
    }
    task = qrr_full_cpu_thread(cpu, pgd);
    state = qrr_full_path_state_for_task(pgd, task, true);
    if (!state) {
        return;
    }
    if (qrr_full_thread_context && (!task || !state->thread_token)) {
        fprintf(stderr,
                "qrr-full: user TB has no exact thread context pgd="
                TARGET_FMT_lx " pc=" TARGET_FMT_lx "\n", pgd, pc);
        exit(2);
    }
    /* A delivery decision is made in kernel mode before execution can return
     * here.  Reaching another user TB proves that an older interrupted-TB
     * anchor did not produce a delivered signal. */
    state->have_interrupted_user_edge = false;
#ifdef TARGET_MIPS
    qrr_full_capture_initial_layout(cpu, pgd, pc,
                                    ((CPUArchState *)cpu->env_ptr)->
                                        active_tc.gpr[29]);
#endif
    if (qrr_full_tb_pending_find(cpu)) {
        fprintf(stderr,
                "qrr-full: pending user TB before next TB cpu=%p pc="
                TARGET_FMT_lx "\n", (void *)cpu, pc);
        exit(2);
    }
    pending = calloc(1, sizeof(*pending));
    if (!pending) {
        fprintf(stderr, "qrr-full: cannot allocate pending user TB\n");
        exit(2);
    }
    pending->cpu = cpu;
    pending->pgd = pgd;
    pending->task = task;
    pending->tb_pc = pc;
    pending->tb_size = itb->size;
    pending->edge_from_pc = state->have_previous_user_edge_pc ?
        state->previous_user_edge_pc : 0;
    pending->edge_occurrence = qrr_full_user_edge_next_occurrence(
        pgd, task, pending->edge_from_pc, pc);
    if (qrr_full_debug_precision_edges &&
        qrr_full_user_precision_watched(pgd, task, pc, false)) {
        fprintf(stderr,
                "qrr-full: precision-edge pgd=" TARGET_FMT_lx
                " edge=" TARGET_FMT_lx "->" TARGET_FMT_lx
                "#%" PRIu64 " tb_size=%u tb_icount=%u\n",
                pgd, pending->edge_from_pc, pc,
                pending->edge_occurrence, itb->size, itb->icount);
    }
    {
        QrrFullUserPrecisionWatch *watch;

        for (watch = qrr_full_user_precision_watches; watch;
             watch = watch->next) {
            if (watch->pgd == pgd && watch->task == task &&
                watch->delay_slot &&
                watch->pc >= 4 && watch->pc - 4 == pc) {
                pending->have_delay_edge = true;
                pending->delay_edge_from_pc = pc;
                pending->delay_edge_to_pc = watch->pc;
                pending->delay_edge_occurrence =
                    qrr_full_user_edge_next_occurrence(
                        pgd, task, pc, watch->pc);
                break;
            }
        }
    }
    pending->next = qrr_full_tb_pending;
    qrr_full_tb_pending = pending;
}

static void qrr_full_tb_discard(CPUState *cpu, const char *reason)
{
    QrrFullTbPending *pending = qrr_full_tb_pending_find(cpu);

    (void)reason;
    if (!pending) {
        return;
    }
    qrr_full_tb_pending_remove(pending);
}

static void qrr_full_tb_commit(CPUState *cpu,
                               target_ulong last_completed_pc,
                               const char *reason)
{
    QrrFullTbPending *pending = qrr_full_tb_pending_find(cpu);
    QrrFullPathState *state;
    uint64_t occurrence;
    uint64_t tb;

    if (!pending) {
        return;
    }
    (void)reason;
    state = qrr_full_path_state_for_task(pending->pgd, pending->task, false);
    if (!state || !state->process_token) {
        fprintf(stderr,
                "qrr-full: pending user TB lost process state pgd="
                TARGET_FMT_lx " pc=" TARGET_FMT_lx "\n",
                pending->pgd, pending->tb_pc);
        exit(2);
    }
    occurrence = qrr_full_user_edge_note(
        pending->pgd, pending->task, pending->edge_from_pc,
        pending->tb_pc);
    if (occurrence != pending->edge_occurrence) {
        fprintf(stderr,
                "qrr-full: pending user edge occurrence changed pgd="
                TARGET_FMT_lx " edge=" TARGET_FMT_lx "->" TARGET_FMT_lx
                " expected=%" PRIu64 " actual=%" PRIu64 "\n",
                pending->pgd, pending->edge_from_pc, pending->tb_pc,
                pending->edge_occurrence, occurrence);
        exit(2);
    }
    if (pending->have_delay_edge &&
        last_completed_pc >= pending->delay_edge_to_pc) {
        occurrence = qrr_full_user_edge_note(
            pending->pgd, pending->task, pending->delay_edge_from_pc,
            pending->delay_edge_to_pc);
        if (occurrence != pending->delay_edge_occurrence) {
            fprintf(stderr,
                    "qrr-full: delay edge occurrence changed pgd="
                    TARGET_FMT_lx " edge=" TARGET_FMT_lx "->"
                    TARGET_FMT_lx " expected=%" PRIu64
                    " actual=%" PRIu64 "\n",
                    pending->pgd, pending->delay_edge_from_pc,
                    pending->delay_edge_to_pc,
                    pending->delay_edge_occurrence, occurrence);
            exit(2);
        }
    }
    qrr_full_user_edge_note_linear(
        pending->pgd, pending->task, pending->tb_pc, last_completed_pc,
        pending->have_delay_edge, pending->delay_edge_from_pc,
        pending->delay_edge_to_pc);
    state->previous_user_edge_pc = last_completed_pc;
    state->have_previous_user_edge_pc = true;
    tb = (uint64_t)pending->tb_pc >> 4;
    if (state->have_previous_tb) {
        state->path_tail[state->path_tail_next] = tb - state->previous_tb;
        state->path_tail_next =
            (state->path_tail_next + 1) % QRR_FULL_PATH_TAIL_LENGTH;
        if (state->path_tail_count < QRR_FULL_PATH_TAIL_LENGTH) {
            state->path_tail_count++;
        }
    }
    state->previous_tb = tb;
    state->have_previous_tb = true;
    qrr_full_tb_pending_remove(pending);
}

static void qrr_full_tb_after(CPUState *cpu, TranslationBlock *itb,
                              bool completed)
{
    QrrFullTbPending *pending = qrr_full_tb_pending_find(cpu);
    target_ulong last_completed_pc;

    if (!pending) {
        return;
    }
    if (pending->tb_pc != itb->pc || pending->tb_size != itb->size) {
        fprintf(stderr,
                "qrr-full: pending/returned TB identity mismatch"
                " pending=" TARGET_FMT_lx "/%" PRIu32
                " returned=" TARGET_FMT_lx "/%u\n",
                pending->tb_pc, pending->tb_size, itb->pc, itb->size);
        exit(2);
    }
    if (!completed) {
        qrr_full_tb_discard(cpu, "before-first-instruction");
        return;
    }
#ifdef TARGET_MIPS
    last_completed_pc = itb->size >= 4 ?
        itb->pc + itb->size - 4 : itb->pc;
#else
    last_completed_pc = itb->pc;
#endif
    qrr_full_tb_commit(cpu, last_completed_pc, "complete");
}

static void qrr_full_tb_interrupted(CPUState *cpu, bool state_restored)
{
    QrrFullTbPending *pending = qrr_full_tb_pending_find(cpu);

    if (!pending) {
        return;
    }
    if (!state_restored) {
        qrr_full_tb_discard(cpu, "unrestored-exit");
        return;
    }
#ifdef TARGET_MIPS
    {
        CPUArchState *env = cpu->env_ptr;
        QrrFullPathState *state = qrr_full_path_state_for_task(
            pending->pgd, pending->task, false);
        target_ulong fault_pc = env->active_tc.PC;
        target_ulong tb_end = pending->tb_pc + pending->tb_size;
        target_ulong last_completed_pc;
        unsigned int instruction_size = 4;
        bool delay_slot = (env->hflags & MIPS_HFLAG_BMASK) != 0;

        if (!state || !state->process_token) {
            fprintf(stderr,
                    "qrr-full: interrupted user TB lost process state pgd="
                    TARGET_FMT_lx " pc=" TARGET_FMT_lx "\n",
                    pending->pgd, fault_pc);
            exit(2);
        }
        state->interrupted_tb_pc = pending->tb_pc;
        state->interrupted_next_pc = fault_pc;

        if (fault_pc == pending->tb_pc) {
            state->have_interrupted_user_edge = true;
            state->interrupted_edge_from_pc = pending->edge_from_pc;
            qrr_full_tb_discard(
                cpu, delay_slot ? "first-instruction-delay-slot-exception" :
                                  "first-instruction-exception");
            return;
        }
        if (fault_pc < pending->tb_pc || fault_pc >= tb_end) {
            fprintf(stderr,
                    "qrr-full: exception PC outside pending user TB"
                    " pgd=" TARGET_FMT_lx " tb=" TARGET_FMT_lx
                    "-" TARGET_FMT_lx " fault=" TARGET_FMT_lx
                    " hflags=%08x\n", pending->pgd, pending->tb_pc,
                    tb_end, fault_pc, env->hflags);
            exit(2);
        }
        if (delay_slot) {
            instruction_size =
                (env->hflags & MIPS_HFLAG_B16) ? 2 : 4;
        } else if (env->hflags & MIPS_HFLAG_M16) {
            instruction_size = 2;
        }
        if (fault_pc < pending->tb_pc + instruction_size) {
            state->have_interrupted_user_edge = true;
            state->interrupted_edge_from_pc = pending->edge_from_pc;
            qrr_full_tb_discard(
                cpu, "no-completed-instruction-before-exception");
            return;
        }
        last_completed_pc = fault_pc - instruction_size;
        /* A precise exception in the middle of a TB occurs after the
         * preceding guest instruction completed.  Anchor the interrupted
         * instruction to that actual predecessor, not to the predecessor of
         * the whole TB.  In particular, repeated Linux page-fault retries of
         * one instruction must retain the same uncommitted semantic edge so
         * all materialized pages can be restored before that instruction is
         * finally executed by qemu-user. */
        state->have_interrupted_user_edge = true;
        state->interrupted_edge_from_pc = last_completed_pc;
        qrr_full_tb_commit(cpu, last_completed_pc,
                           delay_slot ? "delay-slot-exception" :
                                        "mid-tb-exception");
    }
#else
    qrr_full_tb_discard(cpu, "unsupported-architecture-exception");
#endif
}

static void qrr_full_advance_context(QrrFullPathState *state, int syscall_nr,
                                     target_ulong syscall_pc,
                                     uint64_t *key, uint64_t *path_hash,
                                     uint64_t *dep_hash, uint64_t *sequence)
{
    uint64_t next_path_hash = QRR_FULL_FNV64_OFFSET;
    unsigned int start;
    unsigned int i;

    next_path_hash = qrr_full_hash_mix_u64(next_path_hash,
                                           state->process_token);
    if (qrr_full_thread_context) {
        next_path_hash = qrr_full_hash_mix_u64(next_path_hash,
                                               state->thread_token);
    }
    state->syscall_site_tail[state->syscall_site_tail_next] =
        (uint64_t)syscall_pc & UINT64_C(0xfff);
    state->syscall_site_tail_next =
        (state->syscall_site_tail_next + 1) % QRR_FULL_PATH_TAIL_LENGTH;
    if (state->syscall_site_tail_count < QRR_FULL_PATH_TAIL_LENGTH) {
        state->syscall_site_tail_count++;
    }
    start = (state->syscall_site_tail_next + QRR_FULL_PATH_TAIL_LENGTH -
             state->syscall_site_tail_count) % QRR_FULL_PATH_TAIL_LENGTH;
    for (i = 0; i < state->syscall_site_tail_count; i++) {
        uint64_t site = state->syscall_site_tail[
            (start + i) % QRR_FULL_PATH_TAIL_LENGTH];

        next_path_hash = qrr_full_hash_mix_u64(next_path_hash, site);
    }

    *dep_hash = qrr_full_hash_mix_u64(QRR_FULL_FNV64_OFFSET,
                                      state->process_token);
    if (qrr_full_thread_context) {
        *dep_hash = qrr_full_hash_mix_u64(*dep_hash, state->thread_token);
    }
    *dep_hash = qrr_full_hash_mix_u64(*dep_hash, state->last_syscall);
    *dep_hash = qrr_full_hash_mix_u64(*dep_hash, (uint64_t)syscall_nr);
    state->last_syscall = (uint64_t)syscall_nr;
    state->syscall_seq++;
    *sequence = state->syscall_seq;
    *path_hash = next_path_hash;
    *key = qrr_full_result_key(*path_hash, *dep_hash,
                               (uint64_t)syscall_nr);

    state->path_tail_count = 0;
    state->path_tail_next = 0;
    state->have_previous_tb = false;
    state->previous_user_edge_pc = 0;
    state->have_previous_user_edge_pc = false;
    state->have_interrupted_user_edge = false;
    qrr_full_user_edge_remove_task(state->pgd, state->task);
}

static void qrr_full_current_signal_context(const QrrFullPathState *state,
                                            uint64_t *path_hash,
                                            uint64_t *dep_hash)
{
    unsigned int start;
    unsigned int i;

    *path_hash = qrr_full_hash_mix_u64(QRR_FULL_FNV64_OFFSET,
                                       state->process_token);
    if (qrr_full_thread_context) {
        *path_hash = qrr_full_hash_mix_u64(*path_hash,
                                           state->thread_token);
    }
    start = (state->syscall_site_tail_next + QRR_FULL_PATH_TAIL_LENGTH -
             state->syscall_site_tail_count) % QRR_FULL_PATH_TAIL_LENGTH;
    for (i = 0; i < state->syscall_site_tail_count; i++) {
        *path_hash = qrr_full_hash_mix_u64(
            *path_hash,
            state->syscall_site_tail[
                (start + i) % QRR_FULL_PATH_TAIL_LENGTH]);
    }
    *dep_hash = qrr_full_hash_mix_u64(QRR_FULL_FNV64_OFFSET,
                                      state->process_token);
    if (qrr_full_thread_context) {
        *dep_hash = qrr_full_hash_mix_u64(*dep_hash,
                                          state->thread_token);
    }
    *dep_hash = qrr_full_hash_mix_u64(*dep_hash, state->last_syscall);
    *dep_hash = qrr_full_hash_mix_u64(*dep_hash, QRR_FULL_SIGNAL_DEP_TAG);
}

static bool qrr_full_recordable_syscall(int syscall_nr)
{
    /* v13 includes every syscall in sequence/key state.  Output capture is
     * still validated separately below; an output that cannot be recovered
     * is emitted as an explicit skip event instead of silently narrowing the
     * replay contract. */
    return syscall_nr >= 0;
}

static bool qrr_full_is_mmap_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4090 || syscall_nr == 4210;
#elif defined(TARGET_ARM)
    return syscall_nr == 90 || syscall_nr == 192;
#else
    (void)syscall_nr;
    return false;
#endif
}

static bool qrr_full_is_mremap_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4167;
#elif defined(TARGET_ARM)
    return syscall_nr == 163;
#else
    (void)syscall_nr;
    return false;
#endif
}

static bool qrr_full_ioctl_output_length(target_ulong request,
                                         size_t *length)
{
#ifdef TARGET_MIPS
    switch (request) {
    case 0x540d: /* TCGETS: struct target_termios */
        *length = 40;
        return true;
    case 0x467f: /* FIONREAD */
    case 0x7400: /* TIOCGETD */
    case 0x741d: /* TIOCMGET */
    case 0x7472: /* TIOCOUTQ */
        *length = 4;
        return true;
    /* Legacy socket ioctls do not encode direction or size in the command.
     * These exact Linux UAPI commands all copy one complete target ifreq
     * back to userspace. */
    case 0x8910: /* SIOCGIFNAME */
    case 0x8913: /* SIOCGIFFLAGS */
    case 0x8915: /* SIOCGIFADDR */
    case 0x8917: /* SIOCGIFDSTADDR */
    case 0x8919: /* SIOCGIFBRDADDR */
    case 0x891b: /* SIOCGIFNETMASK */
    case 0x891d: /* SIOCGIFMETRIC */
    case 0x891f: /* SIOCGIFMEM */
    case 0x8921: /* SIOCGIFMTU */
    case 0x8927: /* SIOCGIFHWADDR */
    case 0x8929: /* SIOCGIFSLAVE */
    case 0x8933: /* SIOCGIFINDEX */
    case 0x8935: /* SIOCGIFPFLAGS */
    case 0x8942: /* SIOCGIFTXQLEN */
    case 0x8970: /* SIOCGIFMAP */
    case 0x8b01: /* SIOCGIWNAME */
        *length = QRR_FULL_TARGET_IFREQ_SIZE;
        return true;
    case 0x8925: /* SIOCGIFENCAP */
        *length = QRR_FULL_ABI_INT_SIZE;
        return true;
    default:
        break;
    }
    if (((request >> 29) & 2U) != 0) {
        *length = (request >> 16) & 0x1fffU;
        return *length != 0;
    }
#elif defined(TARGET_ARM)
    switch (request) {
    case 0x5401: /* TCGETS: struct target_termios */
        *length = 36;
        return true;
    case 0x5411: /* TIOCOUTQ */
    case 0x5415: /* TIOCMGET */
    case 0x5419: /* TIOCGSOFTCAR */
    case 0x541b: /* FIONREAD */
    case 0x5424: /* TIOCGETD */
    case 0x5429: /* TIOCGSID */
        *length = 4;
        return true;
    case 0x5413: /* TIOCGWINSZ */
        *length = 8;
        return true;
    case 0x8910: /* SIOCGIFNAME */
    case 0x8913: /* SIOCGIFFLAGS */
    case 0x8915: /* SIOCGIFADDR */
    case 0x8917: /* SIOCGIFDSTADDR */
    case 0x8919: /* SIOCGIFBRDADDR */
    case 0x891b: /* SIOCGIFNETMASK */
    case 0x891d: /* SIOCGIFMETRIC */
    case 0x891f: /* SIOCGIFMEM */
    case 0x8921: /* SIOCGIFMTU */
    case 0x8927: /* SIOCGIFHWADDR */
    case 0x8929: /* SIOCGIFSLAVE */
    case 0x8933: /* SIOCGIFINDEX */
    case 0x8935: /* SIOCGIFPFLAGS */
    case 0x8942: /* SIOCGIFTXQLEN */
    case 0x8970: /* SIOCGIFMAP */
    case 0x8b01: /* SIOCGIWNAME */
        *length = QRR_FULL_TARGET_IFREQ_SIZE;
        return true;
    case 0x8925: /* SIOCGIFENCAP */
        *length = QRR_FULL_ABI_INT_SIZE;
        return true;
    default:
        break;
    }
    if (((request >> 30) & 2U) != 0) {
        *length = (request >> 16) & 0x3fffU;
        return *length != 0;
    }
#else
    (void)request;
#endif
    return false;
}

static int qrr_full_open_path_arg(int syscall_nr)
{
#ifdef TARGET_MIPS
    if (syscall_nr == 4005) {
        return 0;
    }
    if (syscall_nr == 4288) {
        return 1;
    }
#elif defined(TARGET_ARM)
    if (syscall_nr == 5) {
        return 0;
    }
    if (syscall_nr == 322) {
        return 1;
    }
#else
    (void)syscall_nr;
#endif
    return -1;
}

static bool qrr_full_is_close_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4006;
#elif defined(TARGET_ARM)
    return syscall_nr == 6;
#else
    (void)syscall_nr;
    return false;
#endif
}

static bool qrr_full_mmap_file_backed(int syscall_nr,
                                      const target_ulong args[6])
{
    if (!qrr_full_is_mmap_syscall(syscall_nr)) {
        return false;
    }
#ifdef TARGET_MIPS
    return !(args[3] & 0x0800);
#elif defined(TARGET_ARM)
    return !(args[3] & 0x0020);
#else
    return false;
#endif
}

static bool qrr_full_read_mips_stack_arg(CPUState *cpu,
                                         target_ulong guest_addr,
                                         target_ulong *value)
{
    unsigned char bytes[TARGET_LONG_SIZE];
    size_t i;

    if (DECAF_read_mem(cpu, guest_addr, sizeof(bytes), bytes) < 0) {
        return false;
    }
    *value = 0;
#ifdef TARGET_WORDS_BIGENDIAN
    for (i = 0; i < sizeof(bytes); i++) {
        *value = (*value << 8) | bytes[i];
    }
#else
    for (i = 0; i < sizeof(bytes); i++) {
        *value |= (target_ulong)bytes[i] << (i * 8);
    }
#endif
    return true;
}

static void qrr_full_syscall_state(CPUState *cpu, int *syscall_nr,
                                   target_ulong args[6], target_ulong *pc,
                                   target_ulong *stack)
{
    CPUArchState *env = cpu->env_ptr;

    memset(args, 0, sizeof(target_ulong) * 6);
#ifdef TARGET_MIPS
    *syscall_nr = env->active_tc.gpr[2];
    args[0] = env->active_tc.gpr[4];
    args[1] = env->active_tc.gpr[5];
    args[2] = env->active_tc.gpr[6];
    args[3] = env->active_tc.gpr[7];
    *pc = env->active_tc.PC;
    *stack = env->active_tc.gpr[29];
    qrr_full_read_mips_stack_arg(cpu, *stack + 4 * TARGET_LONG_SIZE,
                                 &args[4]);
    qrr_full_read_mips_stack_arg(cpu, *stack + 5 * TARGET_LONG_SIZE,
                                 &args[5]);
#elif defined(TARGET_ARM)
    *syscall_nr = env->regs[7];
    args[0] = env->regs[0];
    args[1] = env->regs[1];
    args[2] = env->regs[2];
    args[3] = env->regs[3];
    args[4] = env->regs[4];
    args[5] = env->regs[5];
    *pc = env->regs[15];
    *stack = env->regs[13];
#else
    *syscall_nr = 0;
    *pc = 0;
    *stack = 0;
#endif
}

static int64_t qrr_full_syscall_ret(CPUState *cpu)
{
    CPUArchState *env = cpu->env_ptr;

#ifdef TARGET_MIPS
    if (env->active_tc.gpr[7] != 0) {
        return -(int64_t)env->active_tc.gpr[2];
    }
    return (int64_t)(target_long)env->active_tc.gpr[2];
#elif defined(TARGET_ARM)
    return (int64_t)(target_long)env->regs[0];
#else
    (void)env;
    return 0;
#endif
}

static target_ulong qrr_full_select_arg(const target_ulong args[6], int index)
{
    if (index < 1 || index > 6) {
        return 0;
    }
    return args[index - 1];
}

static bool qrr_full_direct_output_location(int syscall_nr,
                                            const target_ulong args[6],
                                            int64_t ret, int *out_arg,
                                            size_t *length)
{
    if (ret < 0) {
        return false;
    }
#ifdef TARGET_MIPS
    if (syscall_nr == 4013) {
        if (!args[0]) {
            return false;
        }
        *out_arg = 1;
        *length = TARGET_LONG_SIZE;
        return true;
    }
    if (syscall_nr == 4054 &&
        qrr_full_ioctl_output_length(args[1], length)) {
        *out_arg = 3;
        return args[2] != 0;
    }
    switch (syscall_nr) {
    case 4003:
    case 4200:
    case 4141:
    case 4219:
    case 4085:
    case 4175:
    case 4176:
        *out_arg = 2;
        *length = (size_t)ret;
        return ret > 0;
    case 4106:
    case 4107:
    case 4108:
        *out_arg = 2;
        *length = 144;
        return true;
    case 4076:
        *out_arg = 2;
        *length = 2 * TARGET_LONG_SIZE;
        return args[1] != 0;
    case 4116:
        *out_arg = 1;
        *length = QRR_FULL_TARGET_SYSINFO_SIZE;
        return args[0] != 0;
    case 4140:
        *out_arg = 4;
        *length = 8;
        return args[3] != 0;
    case 4338:
        *out_arg = 4;
        *length = 16;
        return args[3] != 0;
    case 4213:
    case 4214:
    case 4215:
        *out_arg = 2;
        *length = 104;
        return true;
    case 4293:
        *out_arg = 3;
        *length = 104;
        return true;
    case 4298:
        *out_arg = 3;
        *length = (size_t)ret;
        return ret > 0;
    case 4353:
        *out_arg = 1;
        *length = (size_t)ret;
        return ret > 0;
    case 4188:
    case 4302:
        *out_arg = 1;
        *length = (size_t)args[1] * 8;
        return args[1] > 0;
    default:
        return false;
    }
#elif defined(TARGET_ARM)
    if (syscall_nr == 13) {
        if (!args[0]) {
            return false;
        }
        *out_arg = 1;
        *length = TARGET_LONG_SIZE;
        return true;
    }
    if (syscall_nr == 54 &&
        qrr_full_ioctl_output_length(args[1], length)) {
        *out_arg = 3;
        return args[2] != 0;
    }
    switch (syscall_nr) {
    case 3:
    case 180:
    case 141:
    case 217:
    case 85:
    case 291:
    case 292:
        *out_arg = 2;
        *length = (size_t)ret;
        return ret > 0;
    case 332:
        *out_arg = 3;
        *length = (size_t)ret;
        return ret > 0;
    case 384:
        *out_arg = 1;
        *length = (size_t)ret;
        return ret > 0;
    case 168:
    case 336:
        *out_arg = 1;
        *length = (size_t)args[1] * 8;
        return args[1] > 0;
    case 76:
    case 191:
        *out_arg = 2;
        *length = 2 * TARGET_LONG_SIZE;
        return args[1] != 0;
    case 116:
        *out_arg = 1;
        *length = QRR_FULL_TARGET_SYSINFO_SIZE;
        return args[0] != 0;
    case 140:
        *out_arg = 4;
        *length = 8;
        return args[3] != 0;
    case 369:
        *out_arg = 4;
        *length = 16;
        return args[3] != 0;
    default:
        return false;
    }
#else
    (void)syscall_nr;
    (void)args;
    (void)ret;
    (void)out_arg;
    (void)length;
    return false;
#endif
}

static bool qrr_full_output_required(int syscall_nr, const target_ulong args[6],
                                     int64_t ret)
{
    if (ret < 0) {
        return false;
    }
#ifdef TARGET_MIPS
    switch (syscall_nr) {
    case QRR_FULL_MIPS_NR_PIPE:
        return ret >= 0;
    case 4116:
        return args[0] != 0;
    case 4007:
        return ret > 0 && args[1] != 0;
    case 4114:
        return ret > 0 && (args[1] || args[3]);
    case 4140:
    case 4142:
    case 4171:
    case 4172:
    case 4173:
    case 4177:
    case 4184:
        return true;
    case 4168:
    case 4334:
        return args[1] || args[2];
    case 4250:
    case 4313:
        return ret > 0;
    default:
        return false;
    }
#elif defined(TARGET_ARM)
    switch (syscall_nr) {
    case 116:
        return args[0] != 0;
    case 114:
        return ret > 0 && (args[1] || args[3]);
    case 82:
    case 106:
    case 107:
    case 108:
    case 140:
    case 142:
    case 195:
    case 196:
    case 197:
    case 327:
    case 286:
    case 287:
    case 288:
    case 295:
    case 297:
        return true;
    case 285:
    case 366:
        return args[1] || args[2];
    case 252:
    case 346:
        return ret > 0;
    default:
        return false;
    }
#else
    (void)syscall_nr;
    (void)args;
    (void)ret;
    return false;
#endif
}

static bool qrr_full_is_recvmsg_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4177;
#elif defined(TARGET_ARM)
    return syscall_nr == 297;
#else
    (void)syscall_nr;
    return false;
#endif
}

static bool qrr_full_buf_reserve(QrrFullBuffer *buf, size_t extra)
{
    size_t needed;
    size_t new_cap;
    unsigned char *new_data;

    if (extra > qrr_full_max_blob || buf->len > qrr_full_max_blob - extra) {
        return false;
    }
    needed = buf->len + extra;
    if (needed <= buf->cap) {
        return true;
    }
    new_cap = buf->cap ? buf->cap : 64;
    while (new_cap < needed) {
        if (new_cap > qrr_full_max_blob / 2) {
            new_cap = needed;
            break;
        }
        new_cap *= 2;
    }
    new_data = realloc(buf->data, new_cap);
    if (!new_data) {
        return false;
    }
    buf->data = new_data;
    buf->cap = new_cap;
    return true;
}

static bool qrr_full_buf_append(QrrFullBuffer *buf, const void *data,
                                size_t length)
{
    if (!qrr_full_buf_reserve(buf, length)) {
        return false;
    }
    if (length) {
        memcpy(buf->data + buf->len, data, length);
        buf->len += length;
    }
    return true;
}

static bool qrr_full_buf_append_u8(QrrFullBuffer *buf, uint8_t value)
{
    return qrr_full_buf_append(buf, &value, sizeof(value));
}

static bool qrr_full_buf_append_le16(QrrFullBuffer *buf, uint16_t value)
{
    uint8_t bytes[2];

    bytes[0] = value & 0xff;
    bytes[1] = (value >> 8) & 0xff;
    return qrr_full_buf_append(buf, bytes, sizeof(bytes));
}

static bool qrr_full_buf_append_le32(QrrFullBuffer *buf, uint32_t value)
{
    uint8_t bytes[4];

    bytes[0] = value & 0xff;
    bytes[1] = (value >> 8) & 0xff;
    bytes[2] = (value >> 16) & 0xff;
    bytes[3] = (value >> 24) & 0xff;
    return qrr_full_buf_append(buf, bytes, sizeof(bytes));
}

static bool qrr_full_buf_append_le64(QrrFullBuffer *buf, uint64_t value)
{
    uint8_t bytes[8];
    unsigned int i;

    for (i = 0; i < sizeof(bytes); i++) {
        bytes[i] = (value >> (i * 8)) & 0xff;
    }
    return qrr_full_buf_append(buf, bytes, sizeof(bytes));
}

static void qrr_full_buf_free(QrrFullBuffer *buf)
{
    free(buf->data);
    memset(buf, 0, sizeof(*buf));
}

static char *qrr_full_hex_from_bytes(const unsigned char *bytes,
                                     size_t length)
{
    static const char digits[] = "0123456789abcdef";
    char *hex;
    size_t i;

    if (!length) {
        return strdup("-");
    }
    if (length > qrr_full_max_blob) {
        return NULL;
    }
    hex = malloc(length * 2 + 1);
    if (!hex) {
        return NULL;
    }
    for (i = 0; i < length; i++) {
        hex[i * 2] = digits[bytes[i] >> 4];
        hex[i * 2 + 1] = digits[bytes[i] & 0xf];
    }
    hex[length * 2] = '\0';
    return hex;
}

static bool qrr_full_read_guest(CPUState *cpu, target_ulong guest_addr,
                                size_t length, void *buffer)
{
    unsigned char *bytes = buffer;
    size_t offset = 0;

    if (!length) {
        return true;
    }

    /* DECAF's bulk read may fail when a range crosses guest page boundaries. */
    while (offset < length) {
        target_ulong address = guest_addr + (target_ulong)offset;
        size_t page_offset;
        size_t chunk;

        if (offset && address < guest_addr) {
            return false;
        }
        page_offset = (size_t)(address & (TARGET_PAGE_SIZE - 1));
        chunk = TARGET_PAGE_SIZE - page_offset;
        if (chunk > length - offset) {
            chunk = length - offset;
        }
        if (DECAF_read_mem(cpu, address, chunk, bytes + offset) < 0 &&
            DECAF_read_mem_with_pgd(cpu, qrr_full_current_pgd(cpu), address,
                                    chunk,
                                    bytes + offset) < 0 &&
            cpu_memory_rw_debug(cpu, address, bytes + offset,
                                (int)chunk, 0) != 0) {
            fprintf(stderr,
                    "qrr-full: guest read failed addr=0x" TARGET_FMT_lx
                    " length=%zu range=0x" TARGET_FMT_lx "+%zu\n",
                    address, chunk, guest_addr, length);
            return false;
        }
        offset += chunk;
    }
    return true;
}

/* mmap-time coverage is a guest Linux page-table property.  Neither QEMU's
 * soft TLB nor the emulated MIPS hardware TLB says whether a lazy file page
 * has been materialized.  Walk the target PGD directly and copy exactly one
 * physical page only when _PAGE_PRESENT is set. */
static DECAF_GVATranslationStatus qrr_full_read_present_mmap_page(
    CPUState *cpu, target_ulong pgd, target_ulong guest_page, void *buffer)
{
    gpa_t physical = 0;
    DECAF_GVATranslationStatus status;

    status = DECAF_get_phys_addr_with_pgd_status(cpu, pgd, guest_page,
                                                 &physical);
    if (status != DECAF_GVA_TRANSLATED) {
        return status;
    }
    if (physical & (TARGET_PAGE_SIZE - 1)) {
        fprintf(stderr,
                "qrr-full: present mmap PTE translated to unaligned page"
                " pgd=" TARGET_FMT_lx " va=" TARGET_FMT_lx
                " pa=%" PRIx64 "\n",
                pgd, guest_page, (uint64_t)physical);
        return DECAF_GVA_WALK_ERROR;
    }
    cpu_physical_memory_rw(physical, buffer, TARGET_PAGE_SIZE, 0);
    return DECAF_GVA_TRANSLATED;
}

static bool qrr_full_read_anonymous_vma(CPUState *cpu, target_ulong pgd,
                                        target_ulong guest_addr,
                                        size_t length, void *buffer)
{
    unsigned char *bytes = buffer;
    size_t offset = 0;
    size_t absent_pages = 0;

    while (offset < length) {
        target_ulong address = guest_addr + (target_ulong)offset;
        size_t page_offset = address & (TARGET_PAGE_SIZE - 1);
        size_t chunk = TARGET_PAGE_SIZE - page_offset;
        gpa_t physical = 0;
        DECAF_GVATranslationStatus status;

        if (offset && address < guest_addr) {
            return false;
        }
        if (chunk > length - offset) {
            chunk = length - offset;
        }
        status = DECAF_get_phys_addr_with_pgd_status(cpu, pgd, address,
                                                     &physical);
        if (status == DECAF_GVA_TRANSLATED) {
            cpu_physical_memory_rw(physical, bytes + offset, chunk, 0);
        } else if (status == DECAF_GVA_NOT_PRESENT) {
            /* An anonymous VMA page without a present PTE is demand-zero. */
            memset(bytes + offset, 0, chunk);
            absent_pages++;
        } else {
            fprintf(stderr,
                    "qrr-full: anonymous VMA page-table walk failed"
                    " pgd=" TARGET_FMT_lx " addr=" TARGET_FMT_lx "\n",
                    pgd, address);
            return false;
        }
        offset += chunk;
    }
    if (absent_pages) {
        fprintf(stderr,
                "qrr-full: anonymous VMA restored %zu demand-zero pages"
                " range=" TARGET_FMT_lx "+%zu\n",
                absent_pages, guest_addr, length);
    }
    return true;
}

static uint32_t qrr_full_target_u32_from_bytes(const unsigned char bytes[4])
{
#ifdef TARGET_WORDS_BIGENDIAN
    return ((uint32_t)bytes[0] << 24) |
           ((uint32_t)bytes[1] << 16) |
           ((uint32_t)bytes[2] << 8) |
           (uint32_t)bytes[3];
#else
    return (uint32_t)bytes[0] |
           ((uint32_t)bytes[1] << 8) |
           ((uint32_t)bytes[2] << 16) |
           ((uint32_t)bytes[3] << 24);
#endif
}

static uint16_t qrr_full_target_u16_from_bytes(const unsigned char bytes[2])
{
#ifdef TARGET_WORDS_BIGENDIAN
    return ((uint16_t)bytes[0] << 8) | (uint16_t)bytes[1];
#else
    return (uint16_t)bytes[0] | ((uint16_t)bytes[1] << 8);
#endif
}

static target_ulong qrr_full_target_ulong_from_bytes(
    const unsigned char bytes[TARGET_LONG_SIZE])
{
    target_ulong value = 0;
    size_t i;

#ifdef TARGET_WORDS_BIGENDIAN
    for (i = 0; i < TARGET_LONG_SIZE; i++) {
        value = (value << 8) | bytes[i];
    }
#else
    for (i = 0; i < TARGET_LONG_SIZE; i++) {
        value |= (target_ulong)bytes[i] << (i * 8);
    }
#endif
    return value;
}

static bool qrr_full_read_target_u32(CPUState *cpu, target_ulong guest_addr,
                                     uint32_t *value)
{
    unsigned char bytes[4];

    if (!qrr_full_read_guest(cpu, guest_addr, sizeof(bytes), bytes)) {
        return false;
    }
    *value = qrr_full_target_u32_from_bytes(bytes);
    return true;
}

static bool qrr_full_read_target_ulong(CPUState *cpu, target_ulong guest_addr,
                                       target_ulong *value)
{
    unsigned char bytes[TARGET_LONG_SIZE];

    if (!qrr_full_read_guest(cpu, guest_addr, sizeof(bytes), bytes)) {
        return false;
    }
    *value = qrr_full_target_ulong_from_bytes(bytes);
    return true;
}

static char *qrr_full_initial_auxv_hex(CPUState *cpu, target_ulong sp)
{
    target_ulong argc;
    target_ulong cursor;
    target_ulong value;
    target_ulong auxv_start;
    unsigned int i;
    size_t length;
    unsigned char *bytes;
    char *hex;

    if (!qrr_full_read_target_ulong(cpu, sp, &argc) || argc > 4096) {
        fprintf(stderr,
                "qrr-full: initial layout invalid argc at sp="
                TARGET_FMT_lx "\n", sp);
        return NULL;
    }
    if (argc > ((~(target_ulong)0) / TARGET_LONG_SIZE) - 2) {
        return NULL;
    }
    cursor = sp + (argc + 2) * TARGET_LONG_SIZE;
    if (cursor < sp) {
        return NULL;
    }
    for (i = 0; i < 8192; i++) {
        if (!qrr_full_read_target_ulong(cpu, cursor, &value)) {
            return NULL;
        }
        cursor += TARGET_LONG_SIZE;
        if (!value) {
            break;
        }
    }
    if (i == 8192) {
        fprintf(stderr, "qrr-full: initial layout envp has no terminator\n");
        return NULL;
    }
    auxv_start = cursor;
    for (i = 0; i < 128; i++) {
        target_ulong type;

        if (!qrr_full_read_target_ulong(cpu, cursor, &type) ||
            !qrr_full_read_target_ulong(cpu, cursor + TARGET_LONG_SIZE,
                                        &value)) {
            return NULL;
        }
        cursor += 2 * TARGET_LONG_SIZE;
        if (!type) {
            break;
        }
    }
    if (i == 128) {
        fprintf(stderr, "qrr-full: initial layout auxv has no AT_NULL\n");
        return NULL;
    }
    length = (size_t)(cursor - auxv_start);
    if (!length || length > qrr_full_max_blob) {
        fprintf(stderr, "qrr-full: initial layout auxv length=%zu invalid\n",
                length);
        return NULL;
    }
    bytes = malloc(length);
    if (!bytes) {
        return NULL;
    }
    if (!qrr_full_read_guest(cpu, auxv_start, length, bytes)) {
        free(bytes);
        return NULL;
    }
    hex = qrr_full_hex_from_bytes(bytes, length);
    free(bytes);
    return hex;
}

static void qrr_full_capture_initial_layout(CPUState *cpu, target_ulong pgd,
                                            target_ulong entry_pc,
                                            target_ulong initial_sp)
{
    QrrFullPathState *state;
    QrrFullLayoutCaptured *request;
    qrr_vmi_layout_t layout;
    char error[128];
    char *auxv_hex;
    char *stack_hex = NULL;
    unsigned char *stack_bytes = NULL;
    qrr_vmi_vma_t *stack_vma = NULL;
    size_t stack_length = 0;
    size_t i;

    if (!qrr_full_layout_fp) {
        return;
    }
    state = qrr_full_path_state_for_task(
        pgd, qrr_full_cpu_thread(cpu, pgd), false);
    if (!state || !state->process_token) {
        fprintf(stderr,
                "qrr-full: layout capture missing process token pgd="
                TARGET_FMT_lx "\n", pgd);
        exit(2);
    }
    for (request = qrr_full_layout_captured; request;
         request = request->next) {
        if (request->process_token == state->process_token) {
            break;
        }
    }
    if (!request || request->captured) {
        return;
    }
    if (!qrr_full_selected_task || pgd != qrr_full_selected_pgd) {
        fprintf(stderr,
                "qrr-full: target layout has no selected exec task"
                " pgd=" TARGET_FMT_lx "\n", pgd);
        exit(2);
    }
    if (VMI_qrr_read_linux_layout_task_c(
            cpu, qrr_full_selected_task, &layout,
            error, sizeof(error)) != 0) {
        fprintf(stderr,
                "qrr-full: target layout capture failed process=%016"
                PRIx64 " pgd=" TARGET_FMT_lx " reason=%s\n",
                state->process_token, pgd, error);
        exit(2);
    }
    if (layout.start_stack != initial_sp) {
        fprintf(stderr,
                "qrr-full: target layout initial SP mismatch process=%016"
                PRIx64 " mm_start_stack=" TARGET_FMT_lx
                " cpu_sp=" TARGET_FMT_lx "\n",
                state->process_token, layout.start_stack, initial_sp);
        exit(2);
    }
    auxv_hex = qrr_full_initial_auxv_hex(cpu, initial_sp);
    if (!auxv_hex) {
        fprintf(stderr,
                "qrr-full: target layout auxv capture failed process=%016"
                PRIx64 " sp=" TARGET_FMT_lx "\n",
                state->process_token, initial_sp);
        exit(2);
    }
    for (i = 0; i < layout.vma_count; i++) {
        qrr_vmi_vma_t *vma = &layout.vmas[i];

        if (vma->start <= initial_sp && initial_sp < vma->end) {
            if (stack_vma) {
                fprintf(stderr,
                        "qrr-full: target layout stack VMA is not unique\n");
                exit(2);
            }
            stack_vma = vma;
        }
    }
    if (!stack_vma || stack_vma->file || stack_vma->end <= stack_vma->start) {
        fprintf(stderr,
                "qrr-full: target layout anonymous stack VMA missing\n");
        exit(2);
    }
    stack_length = (size_t)(stack_vma->end - stack_vma->start);
    if ((target_ulong)stack_length != stack_vma->end - stack_vma->start ||
        !stack_length || stack_length > qrr_full_max_blob) {
        fprintf(stderr,
                "qrr-full: target layout stack length=%zu invalid\n",
                stack_length);
        exit(2);
    }
    stack_bytes = malloc(stack_length);
    if (!stack_bytes ||
        !qrr_full_read_anonymous_vma(cpu, pgd, stack_vma->start,
                                    stack_length, stack_bytes)) {
        fprintf(stderr,
                "qrr-full: target layout stack read failed range="
                TARGET_FMT_lx "-" TARGET_FMT_lx "\n",
                stack_vma->start, stack_vma->end);
        free(stack_bytes);
        exit(2);
    }
    stack_hex = qrr_full_hex_from_bytes(stack_bytes, stack_length);
    free(stack_bytes);
    if (!stack_hex) {
        fprintf(stderr, "qrr-full: target layout stack encode failed\n");
        exit(2);
    }
    fprintf(qrr_full_layout_fp,
            "%016" PRIx64 "\t1\tmeta\t%016x\t%016x\t%016x\t%016x"
            "\t%016" PRIx64 "\t%016" PRIx64 "\t%016" PRIx64
            "\t%016" PRIx64 "\t%016" PRIx64 "\t%s\t%s\t-\t-\n",
            state->process_token, 0, 0, 0, 0,
            (uint64_t)layout.start_brk, (uint64_t)layout.brk,
            (uint64_t)layout.start_stack, (uint64_t)entry_pc,
            (uint64_t)initial_sp, auxv_hex, stack_hex);
    free(auxv_hex);
    free(stack_hex);
    for (i = 0; i < layout.vma_count; i++) {
        qrr_vmi_vma_t *vma = &layout.vmas[i];
        unsigned char *content_bytes = NULL;
        char *content_hex = NULL;
        const char *content_column = "-";
        char *file_hex = NULL;
        const char *file_column = "-";
        size_t content_length;

        if (vma->file) {
            file_hex = qrr_full_hex_from_bytes(
                (const unsigned char *)vma->file_name,
                strnlen(vma->file_name, sizeof(vma->file_name)));
            if (!file_hex) {
                fprintf(stderr,
                        "qrr-full: target layout filename encode failed\n");
                exit(2);
            }
            file_column = file_hex;
        } else if (vma != stack_vma) {
            content_length = (size_t)(vma->end - vma->start);
            if ((target_ulong)content_length != vma->end - vma->start ||
                !content_length || content_length > qrr_full_max_blob) {
                fprintf(stderr,
                        "qrr-full: target layout anonymous VMA length=%zu"
                        " invalid range=" TARGET_FMT_lx "-" TARGET_FMT_lx
                        "\n", content_length, vma->start, vma->end);
                exit(2);
            }
            content_bytes = malloc(content_length);
            if (!content_bytes ||
                !qrr_full_read_anonymous_vma(cpu, pgd, vma->start,
                                            content_length, content_bytes)) {
                fprintf(stderr,
                        "qrr-full: target layout anonymous VMA read failed"
                        " range=" TARGET_FMT_lx "-" TARGET_FMT_lx "\n",
                        vma->start, vma->end);
                free(content_bytes);
                exit(2);
            }
            content_hex = qrr_full_hex_from_bytes(content_bytes,
                                                  content_length);
            free(content_bytes);
            if (!content_hex) {
                fprintf(stderr,
                        "qrr-full: target layout anonymous VMA encode failed"
                        "\n");
                exit(2);
            }
            content_column = content_hex;
        }
        fprintf(qrr_full_layout_fp,
                "%016" PRIx64 "\t%zu\tvma\t%016" PRIx64
                "\t%016" PRIx64 "\t%016" PRIx64 "\t%016" PRIx64
                "\t%016x\t%016x\t%016x\t%016x\t%016x\t-\t-\t%s\t%s\n",
                state->process_token, i + 2,
                (uint64_t)vma->start, (uint64_t)vma->end,
                (uint64_t)vma->flags, (uint64_t)vma->pgoff,
                0, 0, 0, 0, 0, file_column, content_column);
        free(file_hex);
        free(content_hex);
    }
    if (fflush(qrr_full_layout_fp) != 0) {
        fprintf(stderr,
                "qrr-full: target layout table flush failed: %s\n",
                strerror(errno));
        exit(2);
    }
    request->captured = true;
    fprintf(stderr,
            "qrr-full: captured initial layout process=%016" PRIx64
            " pgd=" TARGET_FMT_lx " vmas=%zu start_brk=" TARGET_FMT_lx
            " brk=" TARGET_FMT_lx " stack=" TARGET_FMT_lx "\n",
            state->process_token, pgd, layout.vma_count,
            layout.start_brk, layout.brk, layout.start_stack);
}

static bool qrr_full_is_shmat_syscall(int syscall_nr,
                                      const target_ulong args[6])
{
#ifdef TARGET_MIPS
    /* MIPS O32 uses ipc(call, first, second, third, ptr, fifth).  SHMAT is
     * call 21; its successful syscall return is zero and the attached guest
     * address is written through the fourth syscall argument. */
    return syscall_nr == 4117 && (args[0] & UINT32_C(0xffff)) == 21;
#else
    (void)syscall_nr;
    (void)args;
    return false;
#endif
}

static char *qrr_full_encode_shmat(CPUState *cpu,
                                   const QrrFullPending *pending,
                                   int64_t ret, size_t *payload_bytes,
                                   const char **failure)
{
    static const unsigned char magic[] = { 'Q', 'S', 'H', 'M' };
    qrr_vmi_layout_t layout;
    qrr_vmi_vma_t *match = NULL;
    QrrFullTargetPgd *target;
    QrrFullBuffer blob;
    target_ulong attached;
    target_ulong length_target;
    unsigned char *content = NULL;
    char profile_error[128];
    char *hex = NULL;
    size_t length;
    size_t i;

    *payload_bytes = 0;
    *failure = "shmat-capture-failed";
    memset(&blob, 0, sizeof(blob));
    if (ret != 0) {
        *failure = "shmat-success-return-not-zero";
        goto out;
    }
    if (!pending->args[3] ||
        !qrr_full_read_target_ulong(cpu, pending->args[3], &attached) ||
        !attached) {
        *failure = "shmat-attached-address-read-failed";
        goto out;
    }
    target = qrr_full_target_process_for_token(pending->process_token);
    if (!target || target->pgd != pending->pgd ||
        !target->have_task || !target->task) {
        *failure = "shmat-process-task-missing";
        goto out;
    }
    if (VMI_qrr_read_linux_layout_task_c(
            cpu, target->task, &layout,
            profile_error, sizeof(profile_error)) != 0) {
        fprintf(stderr,
                "qrr-full: SHMAT VMA lookup failed process=%016" PRIx64
                " pgd=" TARGET_FMT_lx " reason=%s\n",
                pending->process_token, pending->pgd,
                profile_error[0] ? profile_error : "unknown");
        *failure = "shmat-vma-layout-read-failed";
        goto out;
    }
    for (i = 0; i < layout.vma_count; i++) {
        qrr_vmi_vma_t *vma = &layout.vmas[i];

        if (vma->start <= attached && attached < vma->end) {
            if (match) {
                *failure = "shmat-vma-not-unique";
                goto out;
            }
            match = vma;
        }
    }
    if (!match || match->start != attached) {
        *failure = match ? "shmat-address-not-vma-start" :
                           "shmat-vma-not-found";
        goto out;
    }
    length_target = match->end - match->start;
    length = (size_t)length_target;
    if ((target_ulong)length != length_target || !length ||
        length > qrr_full_max_blob ||
        QRR_FULL_SHMAT_HEADER_SIZE > qrr_full_max_blob - length) {
        *failure = "shmat-vma-length-invalid";
        goto out;
    }
    content = malloc(length);
    if (!content ||
        !qrr_full_read_anonymous_vma(cpu, pending->pgd, attached,
                                    length, content)) {
        *failure = "shmat-content-read-failed";
        goto out;
    }
    if (!qrr_full_buf_append(&blob, magic, sizeof(magic)) ||
        !qrr_full_buf_append_u8(&blob, QRR_FULL_SHMAT_VERSION) ||
        !qrr_full_buf_append_u8(&blob, TARGET_LONG_SIZE) ||
        !qrr_full_buf_append_le16(&blob, 0) ||
        !qrr_full_buf_append_le64(&blob, (uint64_t)attached) ||
        !qrr_full_buf_append_le64(&blob, (uint64_t)length) ||
        !qrr_full_buf_append_le64(&blob, (uint64_t)match->flags) ||
        !qrr_full_buf_append(&blob, content, length)) {
        *failure = "shmat-blob-build-failed";
        goto out;
    }
    if (blob.len != QRR_FULL_SHMAT_HEADER_SIZE + length) {
        *failure = "shmat-blob-length-mismatch";
        goto out;
    }
    hex = qrr_full_hex_from_bytes(blob.data, blob.len);
    if (!hex) {
        *failure = "shmat-blob-encode-failed";
        goto out;
    }
    *payload_bytes = length + TARGET_LONG_SIZE;
    *failure = NULL;
    fprintf(stderr,
            "qrr-full: captured SHMAT process=%016" PRIx64
            " seq=%" PRIu64 " shmid=" TARGET_FMT_lx
            " address=" TARGET_FMT_lx " length=%zu vm_flags="
            TARGET_FMT_lx "\n",
            pending->process_token, pending->sequence, pending->args[1],
            attached, length, match->flags);

out:
    free(content);
    qrr_full_buf_free(&blob);
    return hex;
}

static bool qrr_full_append_output_from_guest(CPUState *cpu,
                                             QrrFullBuffer *bundle,
                                             uint8_t kind, uint8_t arg,
                                             uint32_t aux,
                                             target_ulong guest_addr,
                                             size_t length)
{
    unsigned char *data = NULL;

    if (bundle->outputs == UINT16_MAX || length > UINT32_MAX ||
        length > qrr_full_max_blob) {
        return false;
    }
    if (bundle->len > qrr_full_max_blob ||
        qrr_full_max_blob - bundle->len < 10 ||
        qrr_full_max_blob - bundle->len - 10 < length) {
        return false;
    }
    if (length) {
        data = malloc(length);
        if (!data) {
            return false;
        }
        if (!qrr_full_read_guest(cpu, guest_addr, length, data)) {
            free(data);
            return false;
        }
    }
    if (!qrr_full_buf_append_u8(bundle, kind) ||
        !qrr_full_buf_append_u8(bundle, arg) ||
        !qrr_full_buf_append_le32(bundle, aux) ||
        !qrr_full_buf_append_le32(bundle, (uint32_t)length) ||
        !qrr_full_buf_append(bundle, data, length)) {
        free(data);
        return false;
    }
    free(data);
    bundle->outputs++;
    bundle->payload_bytes += length;
    return true;
}

static bool qrr_full_append_output_bytes(QrrFullBuffer *bundle,
                                         uint8_t kind, uint8_t arg,
                                         uint32_t aux,
                                         const unsigned char *data,
                                         size_t length)
{
    if (bundle->outputs == UINT16_MAX || length > UINT32_MAX ||
        length > qrr_full_max_blob || bundle->len > qrr_full_max_blob ||
        qrr_full_max_blob - bundle->len < 10 ||
        qrr_full_max_blob - bundle->len - 10 < length) {
        return false;
    }
    if (!qrr_full_buf_append_u8(bundle, kind) ||
        !qrr_full_buf_append_u8(bundle, arg) ||
        !qrr_full_buf_append_le32(bundle, aux) ||
        !qrr_full_buf_append_le32(bundle, (uint32_t)length) ||
        !qrr_full_buf_append(bundle, data, length)) {
        return false;
    }
    bundle->outputs++;
    bundle->payload_bytes += length;
    return true;
}

static bool qrr_full_is_wait4_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4114;
#elif defined(TARGET_ARM)
    return syscall_nr == 114;
#else
    (void)syscall_nr;
    return false;
#endif
}

static bool qrr_full_is_waitpid_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4007;
#else
    (void)syscall_nr;
    return false;
#endif
}

static bool qrr_full_is_wait_syscall(int syscall_nr)
{
    return qrr_full_is_wait4_syscall(syscall_nr) ||
           qrr_full_is_waitpid_syscall(syscall_nr);
}

static bool qrr_full_is_secondary_return_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == QRR_FULL_MIPS_NR_PIPE;
#else
    (void)syscall_nr;
    return false;
#endif
}

/* MIPS O32 pipe returns its second descriptor in v1 rather than guest
 * memory.  Model that architectural output explicitly; replay must not
 * inherit whatever value happened to be in v1 before the syscall. */
static char *qrr_full_encode_secondary_return_bundle(CPUState *cpu,
                                                      size_t *payload_bytes)
{
#ifdef TARGET_MIPS
    static const unsigned char magic[] = { 'Q', 'R', 'R', 'B' };
    CPUArchState *env = cpu->env_ptr;
    QrrFullBuffer bundle;
    char *hex = NULL;

    *payload_bytes = 0;
    memset(&bundle, 0, sizeof(bundle));
    if (!qrr_full_buf_append(&bundle, magic, sizeof(magic)) ||
        !qrr_full_buf_append_u8(&bundle, QRR_FULL_BUNDLE_VERSION) ||
        !qrr_full_buf_append_le16(&bundle, 1) ||
        !qrr_full_buf_append_u8(&bundle,
                                QRR_FULL_OUTPUT_SECONDARY_RETURN) ||
        !qrr_full_buf_append_u8(&bundle, 3) ||
        !qrr_full_buf_append_le32(&bundle, TARGET_LONG_SIZE) ||
        !qrr_full_buf_append_le32(&bundle, TARGET_LONG_SIZE) ||
        !qrr_full_buf_append_le32(
            &bundle, (uint32_t)env->active_tc.gpr[3])) {
        goto out;
    }
    *payload_bytes = TARGET_LONG_SIZE;
    hex = qrr_full_hex_from_bytes(bundle.data, bundle.len);

out:
    qrr_full_buf_free(&bundle);
    return hex;
#else
    (void)cpu;
    *payload_bytes = 0;
    return NULL;
#endif
}

/* wait-family calls have independent output objects.  A successful reap
 * writes the target-endian status word through arg2 and wait4, when
 * requested, writes the complete target struct rusage through arg4.  Store
 * both as ordinary direct-argument bundle items so replay does not depend on
 * host wait status or accounting. */
static char *qrr_full_encode_wait_bundle(CPUState *cpu, int syscall_nr,
                                         const target_ulong args[6],
                                         int64_t ret,
                                         size_t *payload_bytes)
{
    static const unsigned char magic[] = { 'Q', 'R', 'R', 'B' };
    QrrFullBuffer bundle;
    char *hex = NULL;

    *payload_bytes = 0;
    if (ret <= 0 ||
        (!args[1] &&
         (!qrr_full_is_wait4_syscall(syscall_nr) || !args[3]))) {
        return NULL;
    }
    memset(&bundle, 0, sizeof(bundle));
    if (!qrr_full_buf_append(&bundle, magic, sizeof(magic)) ||
        !qrr_full_buf_append_u8(&bundle, QRR_FULL_BUNDLE_VERSION) ||
        !qrr_full_buf_append_le16(&bundle, 0) ||
        (args[1] && !qrr_full_append_output_from_guest(
            cpu, &bundle, QRR_FULL_OUTPUT_DIRECT_ARG, 2, 0, args[1],
            QRR_FULL_TARGET_WAIT_STATUS_SIZE)) ||
        (qrr_full_is_wait4_syscall(syscall_nr) && args[3] &&
         !qrr_full_append_output_from_guest(
            cpu, &bundle, QRR_FULL_OUTPUT_DIRECT_ARG, 4, 0, args[3],
            QRR_FULL_TARGET_RUSAGE_SIZE))) {
        goto out;
    }
    bundle.data[5] = bundle.outputs & 0xff;
    bundle.data[6] = (bundle.outputs >> 8) & 0xff;
    *payload_bytes = bundle.payload_bytes;
    hex = qrr_full_hex_from_bytes(bundle.data, bundle.len);

out:
    qrr_full_buf_free(&bundle);
    return hex;
}

static bool qrr_full_select_fdset_length(target_ulong nfds, size_t *length)
{
    size_t words;

    if (nfds > SIZE_MAX - (TARGET_LONG_SIZE * 8 - 1)) {
        return false;
    }
    words = (nfds + TARGET_LONG_SIZE * 8 - 1) /
            (TARGET_LONG_SIZE * 8);
    if (words > qrr_full_max_blob / TARGET_LONG_SIZE) {
        return false;
    }
    *length = words * TARGET_LONG_SIZE;
    return true;
}

static bool qrr_full_append_select_pointer(CPUState *cpu,
                                           QrrFullBuffer *bundle,
                                           uint8_t kind, uint32_t aux,
                                           target_ulong pointer,
                                           size_t length)
{
    if (!pointer) {
        return true;
    }
    return qrr_full_append_output_from_guest(cpu, bundle, kind, 1, aux,
                                             pointer, length);
}

static char *qrr_full_encode_select_bundle(CPUState *cpu, int syscall_nr,
                                           const target_ulong args[6],
                                           size_t *payload_bytes)
{
    static const unsigned char magic[] = { 'Q', 'R', 'R', 'B' };
    QrrFullBuffer bundle;
    target_ulong nfds;
    target_ulong readfds;
    target_ulong writefds;
    target_ulong exceptfds;
    target_ulong timeout;
    size_t fdset_length;
    bool indirect = false;
    char *hex = NULL;

    *payload_bytes = 0;
    memset(&bundle, 0, sizeof(bundle));
    if (!qrr_full_buf_append(&bundle, magic, sizeof(magic)) ||
        !qrr_full_buf_append_u8(&bundle, QRR_FULL_BUNDLE_VERSION) ||
        !qrr_full_buf_append_le16(&bundle, 0)) {
        goto out;
    }

#ifdef TARGET_ARM
    if (syscall_nr == 82) {
        target_ulong select_args = args[0];

        indirect = true;
        if (!select_args ||
            !qrr_full_read_target_ulong(cpu,
                    select_args + 0 * TARGET_LONG_SIZE, &nfds) ||
            !qrr_full_read_target_ulong(cpu,
                    select_args + 1 * TARGET_LONG_SIZE, &readfds) ||
            !qrr_full_read_target_ulong(cpu,
                    select_args + 2 * TARGET_LONG_SIZE, &writefds) ||
            !qrr_full_read_target_ulong(cpu,
                    select_args + 3 * TARGET_LONG_SIZE, &exceptfds) ||
            !qrr_full_read_target_ulong(cpu,
                    select_args + 4 * TARGET_LONG_SIZE, &timeout)) {
            goto out;
        }
    } else
#endif
    {
        nfds = args[0];
        readfds = args[1];
        writefds = args[2];
        exceptfds = args[3];
        timeout = args[4];
    }
    if (!qrr_full_select_fdset_length(nfds, &fdset_length)) {
        goto out;
    }

    if (indirect) {
        if (!qrr_full_append_select_pointer(
                cpu, &bundle, QRR_FULL_OUTPUT_INDIRECT_ARG,
                1 * TARGET_LONG_SIZE, readfds, fdset_length) ||
            !qrr_full_append_select_pointer(
                cpu, &bundle, QRR_FULL_OUTPUT_INDIRECT_ARG,
                2 * TARGET_LONG_SIZE, writefds, fdset_length) ||
            !qrr_full_append_select_pointer(
                cpu, &bundle, QRR_FULL_OUTPUT_INDIRECT_ARG,
                3 * TARGET_LONG_SIZE, exceptfds, fdset_length) ||
            !qrr_full_append_select_pointer(
                cpu, &bundle, QRR_FULL_OUTPUT_INDIRECT_ARG,
                4 * TARGET_LONG_SIZE, timeout, 2 * TARGET_LONG_SIZE)) {
            goto out;
        }
    } else {
        if ((readfds && !qrr_full_append_output_from_guest(
                cpu, &bundle, QRR_FULL_OUTPUT_DIRECT_ARG, 2, 0,
                readfds, fdset_length)) ||
            (writefds && !qrr_full_append_output_from_guest(
                cpu, &bundle, QRR_FULL_OUTPUT_DIRECT_ARG, 3, 0,
                writefds, fdset_length)) ||
            (exceptfds && !qrr_full_append_output_from_guest(
                cpu, &bundle, QRR_FULL_OUTPUT_DIRECT_ARG, 4, 0,
                exceptfds, fdset_length)) ||
            (timeout && !qrr_full_append_output_from_guest(
                cpu, &bundle, QRR_FULL_OUTPUT_DIRECT_ARG, 5, 0,
                timeout, 2 * TARGET_LONG_SIZE))) {
            goto out;
        }
    }

    bundle.data[5] = bundle.outputs & 0xff;
    bundle.data[6] = (bundle.outputs >> 8) & 0xff;
    *payload_bytes = bundle.payload_bytes;
    hex = qrr_full_hex_from_bytes(bundle.data, bundle.len);

out:
    qrr_full_buf_free(&bundle);
    return hex;
}

/* MIPS o32 passes semctl through sys_ipc.  Its fifth syscall argument points
 * at the target union semun word, which in turn points at the output object.
 * Capturing args[4] directly would save only the pointer and lose the kernel
 * write performed by IPC_STAT/SEM_STAT/IPC_INFO/SEM_INFO. */
static bool qrr_full_is_semctl_output(const QrrFullPending *pending,
                                      size_t *length)
{
#ifdef TARGET_MIPS
    target_ulong operation;
    target_ulong command;

    if (pending->syscall_nr != QRR_FULL_MIPS_NR_IPC) {
        return false;
    }
    operation = pending->args[0] & 0xffff;
    command = pending->args[3] & 0xff;
    if (operation != QRR_FULL_IPCOP_SEMCTL) {
        return false;
    }
    switch (command) {
    case QRR_FULL_SEMCTL_IPC_STAT:
    case QRR_FULL_SEMCTL_SEM_STAT:
        *length = QRR_FULL_MIPS_SEMID64_DS_SIZE;
        return true;
    case QRR_FULL_SEMCTL_IPC_INFO:
    case QRR_FULL_SEMCTL_SEM_INFO:
        *length = QRR_FULL_TARGET_SEMINFO_SIZE;
        return true;
    default:
        return false;
    }
#else
    (void)pending;
    (void)length;
    return false;
#endif
}

static bool qrr_full_semaphore_state_required(const QrrFullPending *pending)
{
#ifdef TARGET_MIPS
    target_ulong operation;
    target_ulong command;

    if (!pending || pending->syscall_nr != QRR_FULL_MIPS_NR_IPC) {
        return false;
    }
    operation = pending->args[0] & 0xffff;
    if (operation == QRR_FULL_IPCOP_SEMOP ||
        operation == QRR_FULL_IPCOP_SEMTIMEDOP) {
        return true;
    }
    if (operation != QRR_FULL_IPCOP_SEMCTL) {
        return false;
    }
    command = pending->args[3] & 0xff;
    return command != QRR_FULL_SEMCTL_IPC_RMID &&
           command != QRR_FULL_SEMCTL_IPC_INFO &&
           command != QRR_FULL_SEMCTL_SEM_INFO &&
           command != QRR_FULL_SEMCTL_SEM_STAT;
#else
    (void)pending;
    return false;
#endif
}

static char *qrr_full_encode_semctl_bundle(CPUState *cpu,
                                           const QrrFullPending *pending,
                                           size_t length,
                                           size_t *payload_bytes)
{
    static const unsigned char magic[] = { 'Q', 'R', 'R', 'B' };
    QrrFullBuffer bundle;
    QrrFullBuffer state;
    target_ulong output_addr;
    char *hex = NULL;
    size_t i;

    *payload_bytes = 0;
    memset(&bundle, 0, sizeof(bundle));
    memset(&state, 0, sizeof(state));
    if (!qrr_full_buf_append(&bundle, magic, sizeof(magic)) ||
        !qrr_full_buf_append_u8(&bundle, QRR_FULL_BUNDLE_VERSION) ||
        !qrr_full_buf_append_le16(&bundle, 0)) {
        goto out;
    }
    if (length) {
        if (!pending->args[4] ||
            !qrr_full_read_target_ulong(cpu, pending->args[4],
                                        &output_addr) ||
            !output_addr ||
            !qrr_full_append_output_from_guest(
                cpu, &bundle, QRR_FULL_OUTPUT_INDIRECT_ARG, 5, 0,
                output_addr, length)) {
            goto out;
        }
    }
    if (pending->semaphore_values) {
        if (!pending->semaphore_nsems ||
            pending->semaphore_nsems > UINT32_MAX) {
            goto out;
        }
        for (i = 0; i < pending->semaphore_nsems; i++) {
            if (!qrr_full_buf_append_le32(&state,
                                          pending->semaphore_values[i])) {
                goto out;
            }
        }
        if (!qrr_full_append_output_bytes(
                &bundle, QRR_FULL_OUTPUT_SEMAPHORE_STATE, 0,
                (uint32_t)pending->semaphore_nsems,
                state.data, state.len)) {
            goto out;
        }
    }
    if (!bundle.outputs) {
        goto out;
    }
    bundle.data[5] = bundle.outputs & 0xff;
    bundle.data[6] = (bundle.outputs >> 8) & 0xff;
    *payload_bytes = bundle.payload_bytes;
    hex = qrr_full_hex_from_bytes(bundle.data, bundle.len);

out:
    qrr_full_buf_free(&state);
    qrr_full_buf_free(&bundle);
    return hex;
}

static bool qrr_full_is_select_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4142;
#elif defined(TARGET_ARM)
    return syscall_nr == 82 || syscall_nr == 142;
#else
    (void)syscall_nr;
    return false;
#endif
}

static bool qrr_full_append_addr_and_len(CPUState *cpu,
                                         QrrFullBuffer *bundle,
                                         uint8_t addr_arg,
                                         target_ulong addr,
                                         uint8_t len_arg,
                                         target_ulong len_addr)
{
    uint32_t length;

    if (!addr || !len_addr) {
        return true;
    }
    if (!qrr_full_read_target_u32(cpu, len_addr, &length)) {
        return false;
    }
    if (length && !qrr_full_append_output_from_guest(
            cpu, bundle, QRR_FULL_OUTPUT_DIRECT_ARG, addr_arg, 0,
            addr, length)) {
        return false;
    }
    return qrr_full_append_output_from_guest(
        cpu, bundle, QRR_FULL_OUTPUT_DIRECT_ARG, len_arg, 0,
        len_addr, QRR_FULL_ABI_INT_SIZE);
}

static char *qrr_full_encode_socket_bundle(CPUState *cpu, int syscall_nr,
                                           const target_ulong args[6],
                                           int64_t ret,
                                           size_t *payload_bytes)
{
    static const unsigned char magic[] = { 'Q', 'R', 'R', 'B' };
    QrrFullBuffer bundle;
    bool handled = true;
    bool ok = true;
    char *hex = NULL;

    *payload_bytes = 0;
    memset(&bundle, 0, sizeof(bundle));
    if (!qrr_full_buf_append(&bundle, magic, sizeof(magic)) ||
        !qrr_full_buf_append_u8(&bundle, QRR_FULL_BUNDLE_VERSION) ||
        !qrr_full_buf_append_le16(&bundle, 0)) {
        goto out;
    }
#ifdef TARGET_MIPS
    switch (syscall_nr) {
    case 4168:
    case 4171:
    case 4172:
    case 4334:
        ok = qrr_full_append_addr_and_len(cpu, &bundle, 2, args[1],
                                          3, args[2]);
        break;
    case 4173:
        ok = qrr_full_append_addr_and_len(cpu, &bundle, 4, args[3],
                                          5, args[4]);
        break;
    case 4176:
        if (ret > 0) {
            size_t data_len = (uint64_t)ret < (uint64_t)args[2]
                              ? (size_t)ret : (size_t)args[2];

            ok = qrr_full_append_output_from_guest(
                cpu, &bundle, QRR_FULL_OUTPUT_DIRECT_ARG, 2, 0,
                args[1], data_len);
        }
        if (ok) {
            ok = qrr_full_append_addr_and_len(cpu, &bundle, 5, args[4],
                                              6, args[5]);
        }
        break;
    case 4184:
        ok = qrr_full_append_output_from_guest(
            cpu, &bundle, QRR_FULL_OUTPUT_DIRECT_ARG, 4, 0,
            args[3], 2 * QRR_FULL_ABI_INT_SIZE);
        break;
    default:
        handled = false;
        break;
    }
#elif defined(TARGET_ARM)
    switch (syscall_nr) {
    case 285:
    case 286:
    case 287:
    case 366:
        ok = qrr_full_append_addr_and_len(cpu, &bundle, 2, args[1],
                                          3, args[2]);
        break;
    case 295:
        ok = qrr_full_append_addr_and_len(cpu, &bundle, 4, args[3],
                                          5, args[4]);
        break;
    case 292:
        if (ret > 0) {
            size_t data_len = (uint64_t)ret < (uint64_t)args[2]
                              ? (size_t)ret : (size_t)args[2];

            ok = qrr_full_append_output_from_guest(
                cpu, &bundle, QRR_FULL_OUTPUT_DIRECT_ARG, 2, 0,
                args[1], data_len);
        }
        if (ok) {
            ok = qrr_full_append_addr_and_len(cpu, &bundle, 5, args[4],
                                              6, args[5]);
        }
        break;
    case 288:
        ok = qrr_full_append_output_from_guest(
            cpu, &bundle, QRR_FULL_OUTPUT_DIRECT_ARG, 4, 0,
            args[3], 2 * QRR_FULL_ABI_INT_SIZE);
        break;
    default:
        handled = false;
        break;
    }
#else
    (void)syscall_nr;
    (void)args;
    (void)ret;
    handled = false;
#endif
    if (!handled || !ok) {
        goto out;
    }
    bundle.data[5] = bundle.outputs & 0xff;
    bundle.data[6] = (bundle.outputs >> 8) & 0xff;
    *payload_bytes = bundle.payload_bytes;
    hex = qrr_full_hex_from_bytes(bundle.data, bundle.len);

out:
    qrr_full_buf_free(&bundle);
    return hex;
}

static bool qrr_full_is_socket_output_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4168 || syscall_nr == 4171 ||
           syscall_nr == 4172 || syscall_nr == 4173 ||
           syscall_nr == 4176 || syscall_nr == 4184 ||
           syscall_nr == 4334;
#elif defined(TARGET_ARM)
    return syscall_nr == 285 || syscall_nr == 286 ||
           syscall_nr == 287 || syscall_nr == 288 ||
           syscall_nr == 292 || syscall_nr == 295 ||
           syscall_nr == 366;
#else
    (void)syscall_nr;
    return false;
#endif
}

static char *qrr_full_encode_recvmsg_bundle(CPUState *cpu,
                                            target_ulong msg_addr,
                                            int64_t ret,
                                            size_t *payload_bytes)
{
    static const unsigned char magic[] = { 'Q', 'R', 'R', 'B' };
    QrrFullBuffer bundle;
    target_ulong name_addr;
    uint32_t name_len;
    target_ulong iov_addr;
    target_ulong iov_count;
    target_ulong control_addr;
    target_ulong control_len;
    uint64_t remaining;
    char *hex = NULL;

    *payload_bytes = 0;
    if (ret < 0 || !msg_addr) {
        return NULL;
    }
    memset(&bundle, 0, sizeof(bundle));
    if (!qrr_full_buf_append(&bundle, magic, sizeof(magic)) ||
        !qrr_full_buf_append_u8(&bundle, QRR_FULL_BUNDLE_VERSION) ||
        !qrr_full_buf_append_le16(&bundle, 0)) {
        goto out;
    }
    if (!qrr_full_read_target_ulong(cpu, msg_addr + QRR_FULL_MSG_NAME_OFF,
                                    &name_addr) ||
        !qrr_full_read_target_u32(cpu, msg_addr + QRR_FULL_MSG_NAMELEN_OFF,
                                  &name_len) ||
        !qrr_full_read_target_ulong(cpu, msg_addr + QRR_FULL_MSG_IOV_OFF,
                                    &iov_addr) ||
        !qrr_full_read_target_ulong(cpu, msg_addr + QRR_FULL_MSG_IOVLEN_OFF,
                                    &iov_count) ||
        !qrr_full_read_target_ulong(cpu, msg_addr + QRR_FULL_MSG_CONTROL_OFF,
                                    &control_addr) ||
        !qrr_full_read_target_ulong(cpu,
                                    msg_addr + QRR_FULL_MSG_CONTROLLEN_OFF,
                                    &control_len)) {
        goto out;
    }

    if (name_addr && name_len &&
        !qrr_full_append_output_from_guest(cpu, &bundle,
                                           QRR_FULL_OUTPUT_RECVMSG_NAME_DATA,
                                           2, 0, name_addr, name_len)) {
        goto out;
    }
    if (control_addr && control_len &&
        !qrr_full_append_output_from_guest(cpu, &bundle,
                                           QRR_FULL_OUTPUT_RECVMSG_CONTROL_DATA,
                                           2, 0, control_addr, control_len)) {
        goto out;
    }

    remaining = (uint64_t)ret;
    if (remaining > 0) {
        target_ulong i;

        if (iov_count > IOV_MAX) {
            goto out;
        }
        for (i = 0; i < iov_count && remaining > 0; i++) {
            target_ulong base;
            target_ulong available;
            uint64_t chunk;

            if (!qrr_full_read_target_ulong(cpu,
                    iov_addr + i * QRR_FULL_IOV_SIZE + QRR_FULL_IOV_BASE_OFF,
                    &base) ||
                !qrr_full_read_target_ulong(cpu,
                    iov_addr + i * QRR_FULL_IOV_SIZE + QRR_FULL_IOV_LEN_OFF,
                    &available)) {
                goto out;
            }
            chunk = remaining < available ? remaining : available;
            if (chunk &&
                !qrr_full_append_output_from_guest(cpu, &bundle,
                                                   QRR_FULL_OUTPUT_RECVMSG_IOV,
                                                   2, (uint32_t)i, base,
                                                   (size_t)chunk)) {
                goto out;
            }
            remaining -= chunk;
        }
        /* MSG_TRUNC may return the full datagram length, beyond iov capacity. */
    }

    if (!qrr_full_append_output_from_guest(cpu, &bundle,
            QRR_FULL_OUTPUT_RECVMSG_FIELD, 2, QRR_FULL_MSG_NAMELEN_OFF,
            msg_addr + QRR_FULL_MSG_NAMELEN_OFF, QRR_FULL_ABI_INT_SIZE) ||
        !qrr_full_append_output_from_guest(cpu, &bundle,
            QRR_FULL_OUTPUT_RECVMSG_FIELD, 2, QRR_FULL_MSG_CONTROLLEN_OFF,
            msg_addr + QRR_FULL_MSG_CONTROLLEN_OFF, QRR_FULL_ABI_LONG_SIZE) ||
        !qrr_full_append_output_from_guest(cpu, &bundle,
            QRR_FULL_OUTPUT_RECVMSG_FIELD, 2, QRR_FULL_MSG_FLAGS_OFF,
            msg_addr + QRR_FULL_MSG_FLAGS_OFF, QRR_FULL_ABI_INT_SIZE)) {
        goto out;
    }

    bundle.data[5] = bundle.outputs & 0xff;
    bundle.data[6] = (bundle.outputs >> 8) & 0xff;
    *payload_bytes = bundle.payload_bytes;
    hex = qrr_full_hex_from_bytes(bundle.data, bundle.len);

out:
    qrr_full_buf_free(&bundle);
    return hex;
}

static char *qrr_full_encode_guest_hex(CPUState *cpu, target_ulong guest_addr,
                                       size_t length)
{
    static const char digits[] = "0123456789abcdef";
    char *hex;
    unsigned char *buffer;
    size_t i;

    if (!length) {
        return strdup("-");
    }
    if (length > qrr_full_max_blob) {
        return NULL;
    }
    buffer = malloc(length);
    if (!buffer) {
        return NULL;
    }
    if (!qrr_full_read_guest(cpu, guest_addr, length, buffer)) {
        free(buffer);
        return NULL;
    }
    hex = malloc(length * 2 + 1);
    if (!hex) {
        free(buffer);
        return NULL;
    }
    for (i = 0; i < length; i++) {
        hex[i * 2] = digits[buffer[i] >> 4];
        hex[i * 2 + 1] = digits[buffer[i] & 0xf];
    }
    hex[length * 2] = '\0';
    free(buffer);
    return hex;
}

static bool qrr_full_is_execve_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4011;
#elif defined(TARGET_ARM)
    return syscall_nr == 11;
#else
    (void)syscall_nr;
    return false;
#endif
}

static bool qrr_full_is_signal_return_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4119 || syscall_nr == 4193;
#elif defined(TARGET_ARM)
    return syscall_nr == 119 || syscall_nr == 173;
#else
    (void)syscall_nr;
    return false;
#endif
}

static bool qrr_full_is_exit_syscall(int syscall_nr)
{
#ifdef TARGET_MIPS
    return syscall_nr == 4001 || syscall_nr == 4246;
#elif defined(TARGET_ARM)
    return syscall_nr == 1 || syscall_nr == 248;
#else
    (void)syscall_nr;
    return false;
#endif
}

static bool qrr_full_read_guest_string(CPUState *cpu,
                                       target_ulong guest_addr,
                                       QrrFullBuffer *buffer,
                                       bool include_nul)
{
    size_t start = buffer->len;

    if (!guest_addr) {
        return false;
    }
    while (buffer->len - start < 4096) {
        unsigned char byte;

        if (!qrr_full_read_guest(cpu, guest_addr++, 1, &byte)) {
            return false;
        }
        if (!byte) {
            return !include_nul || qrr_full_buf_append_u8(buffer, 0);
        }
        if (!qrr_full_buf_append_u8(buffer, byte)) {
            return false;
        }
    }
    return false;
}

static char *qrr_full_read_guest_path(CPUState *cpu, target_ulong guest_addr)
{
    QrrFullBuffer path = { 0 };
    char *result = NULL;

    if (qrr_full_read_guest_string(cpu, guest_addr, &path, false)) {
        result = malloc(path.len + 1);
        if (result) {
            memcpy(result, path.data, path.len);
            result[path.len] = '\0';
        }
    }
    qrr_full_buf_free(&path);
    return result;
}

static QrrFullFdPath *qrr_full_fd_path(target_ulong pgd, int fd)
{
    QrrFullFdPath *entry;

    for (entry = qrr_full_fd_paths; entry; entry = entry->next) {
        if (entry->pgd == pgd && entry->fd == fd) {
            return entry;
        }
    }
    return NULL;
}

static void qrr_full_fd_remove(target_ulong pgd, int fd)
{
    QrrFullFdPath **link = &qrr_full_fd_paths;

    while (*link) {
        QrrFullFdPath *entry = *link;

        if (entry->pgd == pgd && entry->fd == fd) {
            *link = entry->next;
            free(entry->path);
            free(entry);
            return;
        }
        link = &entry->next;
    }
}

static void qrr_full_fd_remove_all(target_ulong pgd)
{
    QrrFullFdPath **link = &qrr_full_fd_paths;

    while (*link) {
        QrrFullFdPath *entry = *link;

        if (entry->pgd == pgd) {
            *link = entry->next;
            free(entry->path);
            free(entry);
            continue;
        }
        link = &entry->next;
    }
}

static void qrr_full_fd_set(target_ulong pgd, int fd, const char *path)
{
    QrrFullFdPath *entry;

    if (fd < 0 || !path || !path[0]) {
        return;
    }
    qrr_full_fd_remove(pgd, fd);
    entry = calloc(1, sizeof(*entry));
    if (!entry) {
        return;
    }
    entry->path = strdup(path);
    if (!entry->path) {
        free(entry);
        return;
    }
    entry->pgd = pgd;
    entry->fd = fd;
    entry->next = qrr_full_fd_paths;
    qrr_full_fd_paths = entry;
}

static void qrr_full_clone_process_state(target_ulong source_pgd,
                                         target_ulong source_task,
                                         target_ulong target_pgd)
{
    QrrFullPathState *source_state;
    QrrFullPathState *target_state;
    QrrFullFdPath *fd_path;

    if (source_pgd == target_pgd) {
        return;
    }
    source_state = qrr_full_path_state_for_task(source_pgd, source_task,
                                                false);
    target_state = qrr_full_path_state_for_task(target_pgd, source_task,
                                                true);
    if (source_state && target_state) {
        QrrFullPathState *next = target_state->next;

        memcpy(target_state, source_state, sizeof(*target_state));
        target_state->pgd = target_pgd;
        target_state->next = next;
        qrr_full_user_edge_clone(source_pgd, target_pgd);
        qrr_full_user_precision_clone(source_pgd, target_pgd);
    }
    for (fd_path = qrr_full_fd_paths; fd_path; fd_path = fd_path->next) {
        if (fd_path->pgd == source_pgd) {
            qrr_full_fd_set(target_pgd, fd_path->fd, fd_path->path);
        }
    }
}

static bool qrr_full_is_process_fork_syscall(int syscall_nr,
                                             const target_ulong args[6])
{
#ifdef TARGET_MIPS
    if (syscall_nr == 4120) {
        /* CLONE_VM is an address-space relationship, not a process identity:
         * vfork-like children share the mm while retaining a distinct TGID.
         * Linux thread-group membership is explicitly CLONE_THREAD. */
        return !(args[0] & QRR_FULL_LINUX_CLONE_THREAD);
    }
    return syscall_nr == 4002 || syscall_nr == 4190;
#elif defined(TARGET_ARM)
    if (syscall_nr == 120) {
        return !(args[0] & QRR_FULL_LINUX_CLONE_THREAD);
    }
    return syscall_nr == 2 || syscall_nr == 190;
#else
    (void)syscall_nr;
    (void)args;
    return false;
#endif
}

static bool qrr_full_same_syscall_return(target_ulong entry_pc,
                                         target_ulong entry_stack,
                                         target_ulong return_pc,
                                         target_ulong return_stack)
{
#ifdef TARGET_MIPS
    return entry_pc + 4 == return_pc && entry_stack == return_stack;
#elif defined(TARGET_ARM)
    return entry_pc == return_pc && entry_stack == return_stack;
#else
    return false;
#endif
}

static void qrr_full_free_fork_pending(QrrFullForkPending *pending)
{
    QrrFullFdPath *entry;
    QrrFullMmapMapping *mapping;

    if (!pending) {
        return;
    }
    entry = pending->fd_paths;

    while (entry) {
        QrrFullFdPath *next = entry->next;

        free(entry->path);
        free(entry);
        entry = next;
    }
    mapping = pending->mmap_mappings;
    while (mapping) {
        QrrFullMmapMapping *next = mapping->next;

        qrr_full_free_mmap_mapping(mapping);
        mapping = next;
    }
    free(pending);
}

static QrrFullMmapMapping *qrr_full_clone_mmap_mapping(
    const QrrFullMmapMapping *source)
{
    QrrFullMmapMapping *copy;
    QrrFullMmapPage **page_tail;
    const QrrFullMmapPage *page;

    copy = calloc(1, sizeof(*copy));
    if (!copy) {
        fprintf(stderr, "qrr-full: cannot snapshot fork mmap mapping\n");
        exit(2);
    }
    *copy = *source;
    copy->path = source->path ? strdup(source->path) : NULL;
    copy->pages = NULL;
    copy->next = NULL;
    if (source->path && !copy->path) {
        qrr_full_free_mmap_mapping(copy);
        fprintf(stderr, "qrr-full: cannot snapshot fork mmap path\n");
        exit(2);
    }
    page_tail = &copy->pages;
    for (page = source->pages; page; page = page->next) {
        QrrFullMmapPage *page_copy = malloc(sizeof(*page_copy));

        if (!page_copy) {
            qrr_full_free_mmap_mapping(copy);
            fprintf(stderr, "qrr-full: cannot snapshot fork mmap page\n");
            exit(2);
        }
        *page_copy = *page;
        page_copy->next = NULL;
        *page_tail = page_copy;
        page_tail = &page_copy->next;
    }
    return copy;
}

static void qrr_full_emit_inherited_mmap_mapping(
    QrrFullPathState *state, const QrrFullMmapMapping *mapping)
{
    char *path_hex = NULL;
    const char *path_column = "-";

    if (!qrr_full_mmap_fp || !state || !state->process_token ||
        state->process_token != mapping->process_token) {
        fprintf(stderr,
                "qrr-full: cannot emit inherited mmap mapping"
                " process=%016" PRIx64 " mapping=%016" PRIx64 "\n",
                mapping->process_token, mapping->mapping_id);
        exit(2);
    }
    if (mapping->path) {
        path_hex = qrr_full_hex_from_bytes(
            (const unsigned char *)mapping->path, strlen(mapping->path));
        if (!path_hex) {
            fprintf(stderr,
                    "qrr-full: cannot encode inherited mmap path"
                    " process=%016" PRIx64 " mapping=%016" PRIx64 "\n",
                    mapping->process_token, mapping->mapping_id);
            exit(2);
        }
        path_column = path_hex;
    }
    if (state->mmap_event_seq == UINT64_MAX) {
        fprintf(stderr,
                "qrr-full: inherited mmap event sequence exhausted"
                " process=%016" PRIx64 "\n", state->process_token);
        free(path_hex);
        exit(2);
    }
    state->mmap_event_seq++;
    fprintf(qrr_full_mmap_fp,
            "%016" PRIx64 "\t%" PRIu64 "\tmap\t%016" PRIx64
            "\t%" PRIu64 "\t%016" PRIx64 "\t%016" PRIx64
            "\t%016" PRIx64 "\t%016" PRIx64 "\t%016" PRIx64
            "\t%d\t%016" PRIx64 "\t%016x\t-\t%016x\t%" PRIu64
            "\t%d\t%016x\t%016x\t%016x\t%" PRIu64 "\t%" PRIu64
            "\t%016" PRIx64 "\t%016" PRIx64
            "\t-\t%016x\t%016x\t%s\t-\t0\n",
            mapping->process_token, state->mmap_event_seq,
            mapping->mapping_id, mapping->mmap_sequence, mapping->mmap_key,
            (uint64_t)mapping->start, (uint64_t)mapping->length,
            (uint64_t)mapping->prot, (uint64_t)mapping->flags, mapping->fd,
            mapping->file_offset, 0, 0, (uint64_t)0, 0, 0,
            0, 0, (uint64_t)0, (uint64_t)0,
            (uint64_t)0, (uint64_t)0, 0, 0, path_column);
    if (fflush(qrr_full_mmap_fp) != 0) {
        fprintf(stderr, "qrr-full: inherited mmap table flush failed: %s\n",
                strerror(errno));
        free(path_hex);
        exit(2);
    }
    fprintf(stderr,
            "qrr-full: inherited mmap mapping process=%016" PRIx64
            " mapping=%016" PRIx64 " range=" TARGET_FMT_lx "+"
            TARGET_FMT_lx "\n",
            mapping->process_token, mapping->mapping_id,
            mapping->start, mapping->length);
    free(path_hex);
}

static void qrr_full_remove_fork_pending(QrrFullForkPending *pending)
{
    QrrFullForkPending **link = &qrr_full_fork_pending;

    while (*link) {
        if (*link == pending) {
            *link = pending->next;
            qrr_full_free_fork_pending(pending);
            return;
        }
        link = &(*link)->next;
    }
}

static void qrr_full_capture_target_fork(CPUState *cpu, target_ulong pgd,
                                         target_ulong entry_pc,
                                         target_ulong stack)
{
    QrrFullForkPending *pending;
    QrrFullTargetPgd *target;
    QrrFullPathState *path_state;
    QrrFullFdPath *fd_path;
    QrrFullMmapMapping *mapping;

    target = qrr_full_target_process_for_task(
        pgd, qrr_full_cpu_thread(cpu, pgd));
    if (!target || !target->have_task || !target->task) {
        fprintf(stderr,
                "qrr-full: process fork entry has no exact parent task"
                " pgd=" TARGET_FMT_lx "\n", pgd);
        exit(2);
    }
    pending = calloc(1, sizeof(*pending));
    if (!pending) {
        return;
    }
    pending->cpu = cpu;
    pending->source_pgd = pgd;
    pending->source_task = target->task;
    pending->entry_pc = entry_pc;
    pending->stack = stack;
    path_state = qrr_full_path_state_for_task(pgd, target->task, true);
    if (path_state) {
        path_state->next_fork_ordinal++;
        pending->child_process_token =
            qrr_full_child_process_token(path_state->process_token,
                                         path_state->next_fork_ordinal);
        memcpy(&pending->path_state, path_state, sizeof(*path_state));
        pending->path_state.next = NULL;
        pending->have_path_state = true;
    }
    for (fd_path = qrr_full_fd_paths; fd_path; fd_path = fd_path->next) {
        QrrFullFdPath *snapshot;

        if (fd_path->pgd != pgd) {
            continue;
        }
        snapshot = calloc(1, sizeof(*snapshot));
        if (!snapshot) {
            continue;
        }
        snapshot->path = strdup(fd_path->path);
        if (!snapshot->path) {
            free(snapshot);
            continue;
        }
        snapshot->fd = fd_path->fd;
        snapshot->next = pending->fd_paths;
        pending->fd_paths = snapshot;
    }
    /* fork inherits the complete address space.  Snapshot the collector's
     * mmap metadata now, before either parent or child can mutate it.  The
     * child gets its own token/PGD objects when its exact return is seen;
     * physical bytes are already inherited by the real guest fork. */
    for (mapping = qrr_full_mmap_mappings; mapping;
         mapping = mapping->next) {
        QrrFullMmapMapping *snapshot;

        if (mapping->pgd != pgd || !path_state ||
            mapping->process_token != path_state->process_token) {
            continue;
        }
        snapshot = qrr_full_clone_mmap_mapping(mapping);
        snapshot->next = pending->mmap_mappings;
        pending->mmap_mappings = snapshot;
    }
    pending->next = qrr_full_fork_pending;
    qrr_full_fork_pending = pending;
}

/* proc_fork_connector(child_task) runs only after copy_process has created a
 * real child task and mm.  It is therefore the authoritative fork identity
 * boundary.  Never infer a child from a matching userspace return PC/SP:
 * unrelated processes commonly return through the same libc clone wrapper. */
static void qrr_full_note_fork_connector(CPUState *cpu,
                                         target_ulong child_task)
{
#ifdef TARGET_MIPS
    CPUArchState *env;
    target_ulong kernel_sp;
    target_ulong thread_info;
    target_ulong parent_task;
    qrr_vmi_exec_identity_t parent_identity;
    qrr_vmi_exec_identity_t child_identity;
    QrrFullForkPending *pending = NULL;
    QrrFullForkPending *candidate;
    QrrFullPathState *target_state;
    QrrFullFdPath *fd_path;
    QrrFullMmapMapping *mapping;
    QrrFullTargetPgd *target;
    char error[128];

    if (!qrr_full_init() || !child_task) {
        return;
    }
    env = cpu->env_ptr;
    kernel_sp = env->active_tc.gpr[29];
    if (kernel_sp < UINT32_C(0x80000000)) {
        fprintf(stderr,
                "qrr-full: proc_fork_connector executed outside kernel"
                " child_task=" TARGET_FMT_lx "\n", child_task);
        exit(2);
    }
    thread_info = kernel_sp & ~(QRR_FULL_MIPS_THREAD_SIZE - 1);
    if (VMI_qrr_task_from_thread_info_c(
            cpu, thread_info, &parent_task, error, sizeof(error)) != 0) {
        fprintf(stderr,
                "qrr-full: proc_fork_connector parent task lookup failed"
                " child_task=" TARGET_FMT_lx " reason=%s\n",
                child_task, error[0] ? error : "unknown");
        exit(2);
    }

    for (candidate = qrr_full_fork_pending; candidate;
         candidate = candidate->next) {
        if (candidate->cpu == cpu &&
            candidate->source_task == parent_task) {
            if (pending) {
                fprintf(stderr,
                        "qrr-full: conflicting process forks for exact"
                        " parent task=" TARGET_FMT_lx "\n", parent_task);
                exit(2);
            }
            pending = candidate;
        }
    }
    target = qrr_full_target_process(qrr_full_current_pgd(cpu));
    if (!pending && !target) {
        return;
    }

    if (VMI_qrr_read_exec_identity_c(
            cpu, parent_task, &parent_identity,
            error, sizeof(error)) != 0) {
        if (!pending) {
            return;
        }
        fprintf(stderr,
                "qrr-full: proc_fork_connector parent identity failed"
                " task=" TARGET_FMT_lx " reason=%s\n",
                parent_task, error[0] ? error : "unknown");
        exit(2);
    }
    if (VMI_qrr_read_exec_identity_c(
            cpu, child_task, &child_identity,
            error, sizeof(error)) != 0) {
        fprintf(stderr,
                "qrr-full: proc_fork_connector child identity failed"
                " task=" TARGET_FMT_lx " reason=%s\n",
                child_task, error[0] ? error : "unknown");
        exit(2);
    }

    /* The connector is the creation-order boundary for both processes and
     * threads.  Allocate a shared-mm child's thread token here, before the
     * scheduler can choose which newly created task runs first.  This order
     * is the one qemu-user observes at clone(), so token derivation remains
     * deterministic across system collection and replay. */
    target = qrr_full_target_process_for_task(parent_identity.pgd,
                                               parent_task);
    if (target && child_identity.pgd == parent_identity.pgd) {
        QrrFullThreadIdentity *thread;
        QrrFullPathState *thread_state;

        if (parent_identity.tgid != target->tgid) {
            fprintf(stderr,
                    "qrr-full: clone parent has conflicting tgid"
                    " process=%016" PRIx64 " pgd=" TARGET_FMT_lx
                    " parent_task=" TARGET_FMT_lx " parent_tgid=%u"
                    " expected_tgid=%u\n",
                    target->process_token, parent_identity.pgd,
                    parent_task, parent_identity.tgid, target->tgid);
            exit(2);
        }
        if (child_identity.tgid != target->tgid) {
            /* A distinct TGID sharing this PGD is a process, not a thread.
             * The exact process-fork entry already allocated its child token
             * and snapshotted path/mmap state.  Bind that execution instance
             * without removing or aliasing the suspended parent. */
            QrrFullPathState *next_state;

            if (!pending || !qrr_full_follow_fork_descendants ||
                !pending->have_path_state ||
                !pending->child_process_token ||
                pending->source_pgd != parent_identity.pgd ||
                pending->source_task != parent_task) {
                fprintf(stderr,
                        "qrr-full: shared-mm process clone lacks exact"
                        " fork entry parent_task=" TARGET_FMT_lx
                        " child_task=" TARGET_FMT_lx
                        " parent_tgid=%u child_tgid=%u\n",
                        parent_task, child_task, parent_identity.tgid,
                        child_identity.tgid);
                exit(2);
            }
            target = qrr_full_bind_shared_process_token(
                child_identity.pgd, pending->child_process_token,
                child_task, child_identity.tgid);
            thread = qrr_full_thread_identity(
                child_identity.pgd, child_task, child_identity.tgid, true);
            thread_state = qrr_full_path_state_for_task(
                child_identity.pgd, child_task, true);
            if (!target || !thread || !thread_state) {
                fprintf(stderr,
                        "qrr-full: cannot bind shared-mm process context"
                        " process=%016" PRIx64
                        " child_task=" TARGET_FMT_lx "\n",
                        pending->child_process_token, child_task);
                exit(2);
            }
            next_state = thread_state->next;
            memcpy(thread_state, &pending->path_state,
                   sizeof(*thread_state));
            thread_state->pgd = child_identity.pgd;
            thread_state->task = child_task;
            thread_state->process_token = pending->child_process_token;
            thread_state->thread_token = thread->thread_token;
            thread_state->next_fork_ordinal = 0;
            thread_state->next = next_state;
            mapping = pending->mmap_mappings;
            pending->mmap_mappings = NULL;
            while (mapping) {
                QrrFullMmapMapping *next_mapping = mapping->next;

                mapping->pgd = child_identity.pgd;
                mapping->process_token = pending->child_process_token;
                mapping->next = qrr_full_mmap_mappings;
                qrr_full_mmap_mappings = mapping;
                qrr_full_emit_inherited_mmap_mapping(thread_state, mapping);
                mapping = next_mapping;
            }
            fprintf(stderr,
                    "qrr-full: inherited shared-mm target process"
                    " pgd=" TARGET_FMT_lx
                    " parent_task=" TARGET_FMT_lx
                    " child_task=" TARGET_FMT_lx
                    " parent_tgid=%u child_tgid=%u"
                    " process=%016" PRIx64
                    " source=proc_fork_connector\n",
                    child_identity.pgd, parent_task, child_task,
                    parent_identity.tgid, child_identity.tgid,
                    pending->child_process_token);
            qrr_full_remove_fork_pending(pending);
            return;
        }
        thread = qrr_full_thread_identity(
            child_identity.pgd, child_task, child_identity.tgid, true);
        thread_state = qrr_full_path_state_for_task(
            child_identity.pgd, child_task, true);
        if (!thread || !thread_state) {
            fprintf(stderr,
                    "qrr-full: cannot bind clone thread context"
                    " process=%016" PRIx64 " child_task=" TARGET_FMT_lx
                    "\n", target->process_token, child_task);
            exit(2);
        }
        thread_state->process_token = target->process_token;
        thread_state->thread_token = thread->thread_token;
        fprintf(stderr,
                "qrr-full: target thread clone process=%016" PRIx64
                " thread=%016" PRIx64 " pgd=" TARGET_FMT_lx
                " parent_task=" TARGET_FMT_lx " child_task=" TARGET_FMT_lx
                " source=proc_fork_connector\n",
                target->process_token, thread->thread_token,
                child_identity.pgd, parent_task, child_task);
        return;
    }

    /* Only a logical process-fork syscall from an already selected family
     * member has a pending record.  Unrelated system forks take this exact
     * hook too, but have no matching source_task and are ignored. */
    if (!pending || !qrr_full_follow_fork_descendants) {
        return;
    }
    if (parent_identity.task != pending->source_task ||
        parent_identity.pgd != pending->source_pgd) {
        fprintf(stderr,
                "qrr-full: proc_fork_connector parent identity conflict"
                " expected_task=" TARGET_FMT_lx
                " actual_task=" TARGET_FMT_lx
                " expected_pgd=" TARGET_FMT_lx
                " actual_pgd=" TARGET_FMT_lx "\n",
                pending->source_task, parent_identity.task,
                pending->source_pgd, parent_identity.pgd);
        exit(2);
    }
    if (!child_identity.mm || !child_identity.pgd ||
        child_identity.pgd == parent_identity.pgd) {
        fprintf(stderr,
                "qrr-full: process fork connector did not create an"
                " isolated child mm parent_task=" TARGET_FMT_lx
                " child_task=" TARGET_FMT_lx
                " parent_pgd=" TARGET_FMT_lx
                " child_pgd=" TARGET_FMT_lx "\n",
                parent_task, child_task, parent_identity.pgd,
                child_identity.pgd);
        exit(2);
    }

    /* The connector proves both child task and child PGD.  A pre-existing
     * owner of that physical PGD can only be stale reuse from a process whose
     * exit was not observable at a userspace syscall boundary. */
    target = qrr_full_target_process(child_identity.pgd);
    if (target) {
        if (target->have_task && target->task == child_task) {
            fprintf(stderr,
                    "qrr-full: duplicate proc_fork_connector child"
                    " task=" TARGET_FMT_lx " pgd=" TARGET_FMT_lx "\n",
                    child_task, child_identity.pgd);
            exit(2);
        }
        qrr_full_unbind_process(child_identity.pgd,
                                "fork-connector-pgd-reuse");
    }
    if (!pending->have_path_state || !pending->child_process_token) {
        fprintf(stderr,
                "qrr-full: inherited target fork has no parent path state"
                " parent_pgd=" TARGET_FMT_lx " child_pgd=" TARGET_FMT_lx
                "\n", pending->source_pgd, child_identity.pgd);
        exit(2);
    }
    target_state = qrr_full_path_state(child_identity.pgd, true);
    if (!target_state) {
        fprintf(stderr,
                "qrr-full: cannot allocate inherited target path state"
                " child_pgd=" TARGET_FMT_lx "\n", child_identity.pgd);
        exit(2);
    }
    {
        QrrFullPathState *next = target_state->next;

        memcpy(target_state, &pending->path_state, sizeof(*target_state));
        target_state->pgd = child_identity.pgd;
        target_state->task = child_task;
        target_state->process_token = pending->child_process_token;
        target_state->thread_token = 0;
        target_state->next_fork_ordinal = 0;
        target_state->next = next;
        /* A process token is an execution instance.  Edge occurrences begin
         * empty in the child on both collection and replay. */
        qrr_full_user_edge_remove_all(child_identity.pgd);
        qrr_full_user_precision_remove_all(child_identity.pgd);
    }
    for (fd_path = pending->fd_paths; fd_path; fd_path = fd_path->next) {
        qrr_full_fd_set(child_identity.pgd, fd_path->fd, fd_path->path);
    }
    qrr_full_bind_process_token(child_identity.pgd, qrr_full_target_name,
                                pending->child_process_token,
                                false);
    target = qrr_full_target_process(child_identity.pgd);
    if (!target) {
        fprintf(stderr,
                "qrr-full: exact fork child binding disappeared"
                " child_pgd=" TARGET_FMT_lx "\n", child_identity.pgd);
        exit(2);
    }
    target->task = child_task;
    target->tgid = child_identity.tgid;
    target->have_task = true;
    {
        QrrFullThreadIdentity *thread = qrr_full_thread_identity(
            child_identity.pgd, child_task, child_identity.tgid, true);

        if (!thread) {
            fprintf(stderr,
                    "qrr-full: cannot bind fork child thread identity"
                    " task=" TARGET_FMT_lx "\n", child_task);
            exit(2);
        }
        target_state->thread_token = thread->thread_token;
    }
    mapping = pending->mmap_mappings;
    pending->mmap_mappings = NULL;
    while (mapping) {
        QrrFullMmapMapping *next = mapping->next;

        mapping->pgd = child_identity.pgd;
        mapping->process_token = pending->child_process_token;
        mapping->next = qrr_full_mmap_mappings;
        qrr_full_mmap_mappings = mapping;
        qrr_full_emit_inherited_mmap_mapping(target_state, mapping);
        mapping = next;
    }
    fprintf(stderr,
            "qrr-full: inherited target fork pgd=" TARGET_FMT_lx
            " parent_pgd=" TARGET_FMT_lx
            " parent_task=" TARGET_FMT_lx
            " child_task=" TARGET_FMT_lx
            " process=%016" PRIx64 " source=proc_fork_connector\n",
            child_identity.pgd, pending->source_pgd, parent_task,
            child_task, pending->child_process_token);
    qrr_full_remove_fork_pending(pending);
#else
    (void)cpu;
    (void)child_task;
#endif
}

static void qrr_full_discard_failed_target_fork(CPUState *cpu,
                                                 target_ulong pgd,
                                                 target_ulong return_pc,
                                                 target_ulong stack,
                                                 int64_t ret)
{
    QrrFullForkPending *pending;

    for (pending = qrr_full_fork_pending; pending;
         pending = pending->next) {
        if (pending->cpu == cpu && pending->source_pgd == pgd &&
            qrr_full_same_syscall_return(pending->entry_pc,
                                         pending->stack,
                                         return_pc, stack)) {
            if (ret >= 0) {
                fprintf(stderr,
                        "qrr-full: successful target fork had no exact"
                        " proc_fork_connector event source_task="
                        TARGET_FMT_lx " source_pgd=" TARGET_FMT_lx
                        " ret=%" PRId64 "\n",
                        pending->source_task, pgd, ret);
                exit(2);
            }
            fprintf(stderr,
                    "qrr-full: target fork failed source_task="
                    TARGET_FMT_lx " source_pgd=" TARGET_FMT_lx
                    " ret=%" PRId64 "\n", pending->source_task, pgd, ret);
            qrr_full_remove_fork_pending(pending);
            return;
        }
    }
}

static void qrr_full_update_fd_paths(const QrrFullPending *pending,
                                     int64_t ret)
{
    if (pending->open_path && ret >= 0 && ret <= INT_MAX) {
        qrr_full_fd_set(pending->pgd, (int)ret, pending->open_path);
    } else if (qrr_full_is_close_syscall(pending->syscall_nr) && ret == 0) {
        qrr_full_fd_remove(pending->pgd, (int)pending->args[0]);
    }
}

static uint64_t qrr_full_mmap_file_offset(const QrrFullPending *pending,
                                          bool *valid)
{
    uint64_t offset = (uint64_t)pending->args[5];

    *valid = true;
#ifdef TARGET_MIPS
    if (pending->syscall_nr == 4210) {
#elif defined(TARGET_ARM)
    if (pending->syscall_nr == 192) {
#else
    if (false) {
#endif
        if (offset > UINT64_MAX / TARGET_PAGE_SIZE) {
            *valid = false;
            return 0;
        }
        offset *= TARGET_PAGE_SIZE;
    }
    return offset;
}

static void qrr_full_current_mmap_context(const QrrFullPathState *state,
                                          uint64_t *path_hash,
                                          uint64_t *dep_hash)
{
    unsigned int start;
    unsigned int i;

    *path_hash = qrr_full_hash_mix_u64(QRR_FULL_FNV64_OFFSET,
                                       state->process_token);
    if (qrr_full_thread_context) {
        *path_hash = qrr_full_hash_mix_u64(*path_hash,
                                           state->thread_token);
    }
    start = (state->syscall_site_tail_next + QRR_FULL_PATH_TAIL_LENGTH -
             state->syscall_site_tail_count) % QRR_FULL_PATH_TAIL_LENGTH;
    for (i = 0; i < state->syscall_site_tail_count; i++) {
        *path_hash = qrr_full_hash_mix_u64(
            *path_hash,
            state->syscall_site_tail[
                (start + i) % QRR_FULL_PATH_TAIL_LENGTH]);
    }
    *dep_hash = qrr_full_hash_mix_u64(QRR_FULL_FNV64_OFFSET,
                                      state->process_token);
    if (qrr_full_thread_context) {
        *dep_hash = qrr_full_hash_mix_u64(*dep_hash,
                                          state->thread_token);
    }
    *dep_hash = qrr_full_hash_mix_u64(*dep_hash, state->last_syscall);
    *dep_hash = qrr_full_hash_mix_u64(*dep_hash, QRR_FULL_MMAP_DEP_TAG);
}

static bool qrr_full_record_mmap_mapping(CPUState *cpu,
                                         const QrrFullPending *pending,
                                         int64_t ret,
                                         const char **failure_reason)
{
    QrrFullPathState *state;
    QrrFullMmapMapping *mapping;
    QrrFullMmapPage *page_record;
    QrrFullFdPath *fd_path = NULL;
    target_ulong page;
    target_ulong end;
    target_ulong page_offset;
    uint64_t file_offset;
    unsigned char *snapshot = NULL;
    char *snapshot_hex = NULL;
    DECAF_GVATranslationStatus snapshot_status;
    bool valid_offset;
    char *path_hex = NULL;
    const char *path_column = "-";

    if (!qrr_full_mmap_fp) {
        *failure_reason = "mmap_event_table_missing";
        return false;
    }
    if (!pending->args[1] || (target_ulong)ret & (TARGET_PAGE_SIZE - 1)) {
        *failure_reason = "mmap_invalid_range";
        return false;
    }
    if ((target_ulong)ret > ~(target_ulong)0 -
        (pending->args[1] - 1)) {
        *failure_reason = "mmap_range_overflow";
        return false;
    }
    file_offset = qrr_full_mmap_file_offset(pending, &valid_offset);
    if (!valid_offset) {
        *failure_reason = "mmap_offset_overflow";
        return false;
    }
    state = qrr_full_path_state_for_task(pending->pgd, pending->task, false);
    if (!state || state->process_token != pending->process_token) {
        *failure_reason = "mmap_process_state_missing";
        return false;
    }
    mapping = calloc(1, sizeof(*mapping));
    if (!mapping) {
        *failure_reason = "mmap_mapping_allocation_failed";
        return false;
    }
    qrr_full_next_mapping_id++;
    if (!qrr_full_next_mapping_id) {
        fprintf(stderr, "qrr-full: mmap mapping id exhausted\n");
        exit(2);
    }
    mapping->pgd = pending->pgd;
    mapping->process_token = pending->process_token;
    mapping->mapping_id = qrr_full_next_mapping_id;
    mapping->mmap_sequence = pending->sequence;
    mapping->mmap_key = pending->key;
    mapping->start = (target_ulong)ret;
    mapping->length = pending->args[1];
    mapping->prot = pending->args[2];
    mapping->flags = pending->args[3];
    mapping->fd = (int32_t)pending->args[4];
    mapping->file_offset = file_offset;
    if (qrr_full_mmap_file_backed(pending->syscall_nr, pending->args)) {
        fd_path = qrr_full_fd_path(pending->pgd, mapping->fd);
        if (fd_path && fd_path->path) {
            mapping->path = strdup(fd_path->path);
            path_hex = qrr_full_hex_from_bytes(
                (const unsigned char *)fd_path->path,
                strlen(fd_path->path));
            if (!mapping->path || !path_hex) {
                free(mapping->path);
                free(mapping);
                free(path_hex);
                *failure_reason = "mmap_path_allocation_failed";
                return false;
            }
            path_column = path_hex;
        }
    }
    mapping->next = qrr_full_mmap_mappings;
    qrr_full_mmap_mappings = mapping;
    state->mmap_event_seq++;
    fprintf(qrr_full_mmap_fp,
            "%016" PRIx64 "\t%" PRIu64 "\tmap\t%016" PRIx64
            "\t%" PRIu64 "\t%016" PRIx64 "\t%016" PRIx64
            "\t%016" PRIx64 "\t%016" PRIx64 "\t%016" PRIx64
            "\t%d\t%016" PRIx64 "\t%016x\t-\t%016x\t%" PRIu64
            "\t%d\t%016x\t%016x\t%016x\t%" PRIu64 "\t%" PRIu64
            "\t%016" PRIx64 "\t%016" PRIx64
            "\t-\t%016x\t%016x\t%s\t-\t0\n",
            mapping->process_token, state->mmap_event_seq,
            mapping->mapping_id, mapping->mmap_sequence, mapping->mmap_key,
            (uint64_t)mapping->start, (uint64_t)mapping->length,
            (uint64_t)mapping->prot, (uint64_t)mapping->flags, mapping->fd,
            mapping->file_offset, 0, 0, (uint64_t)0, 0, 0,
            0, 0, (uint64_t)0, (uint64_t)0,
            pending->path_hash, pending->dep_hash, 0, 0, path_column);
    free(path_hex);

    /* Establish the mmap baseline from the guest Linux page tables.  Present
     * pages are copied in full.  Absent PTEs produce no guessed bytes: their
     * contents can only be supplied by a later successful real page fault. */
    end = TARGET_PAGE_ALIGN(mapping->start + mapping->length);
    for (page = mapping->start, page_offset = 0; page < end;
         page += TARGET_PAGE_SIZE, page_offset += TARGET_PAGE_SIZE) {
        snapshot = malloc(TARGET_PAGE_SIZE);
        if (!snapshot) {
            *failure_reason = "mmap_snapshot_allocation_failed";
            return false;
        }
        snapshot_status = qrr_full_read_present_mmap_page(
            cpu, pending->pgd, page, snapshot);
        if (snapshot_status == DECAF_GVA_NOT_PRESENT) {
            fprintf(stderr,
                    "qrr-full: mmap snapshot process=%016" PRIx64
                    " mapping=%016" PRIx64 " offset=%016" PRIx64
                    " source=pte-absent\n",
                    mapping->process_token, mapping->mapping_id,
                    (uint64_t)page_offset);
            free(snapshot);
            snapshot = NULL;
            continue;
        }
        if (snapshot_status != DECAF_GVA_TRANSLATED) {
            fprintf(stderr,
                    "qrr-full: mmap baseline page-table walk failed"
                    " process=%016" PRIx64 " mapping=%016" PRIx64
                    " pgd=" TARGET_FMT_lx " page=" TARGET_FMT_lx "\n",
                    mapping->process_token, mapping->mapping_id,
                    pending->pgd, page);
            free(snapshot);
            exit(2);
        }
        snapshot_hex = qrr_full_hex_from_bytes(snapshot, TARGET_PAGE_SIZE);
        if (!snapshot_hex) {
            free(snapshot);
            *failure_reason = "mmap_snapshot_encode_failed";
            return false;
        }
        page_record = calloc(1, sizeof(*page_record));
        if (!page_record) {
            free(snapshot_hex);
            free(snapshot);
            *failure_reason = "mmap_snapshot_page_allocation_failed";
            return false;
        }
        page_record->page_offset = page_offset;
        page_record->present_at_mmap = true;
        page_record->next = mapping->pages;
        mapping->pages = page_record;
        state->mmap_event_seq++;
        fprintf(qrr_full_mmap_fp,
                "%016" PRIx64 "\t%" PRIu64 "\tsnapshot\t%016" PRIx64
                "\t%" PRIu64 "\t%016" PRIx64 "\t%016" PRIx64
                "\t%016" PRIx64 "\t%016" PRIx64 "\t%016" PRIx64
                "\t%d\t%016" PRIx64 "\t%016" PRIx64
                "\t-\t%016x\t%" PRIu64 "\t%d\t%016x"
                "\t%016x\t%016x\t%" PRIu64 "\t%" PRIu64
                "\t%016" PRIx64 "\t%016" PRIx64 "\t%s\t%016x"
                "\t%016x\t-\t%s\t0\n",
                mapping->process_token, state->mmap_event_seq,
                mapping->mapping_id, mapping->mmap_sequence, mapping->mmap_key,
                (uint64_t)mapping->start, (uint64_t)mapping->length,
                (uint64_t)mapping->prot, (uint64_t)mapping->flags, mapping->fd,
                mapping->file_offset, (uint64_t)page_offset,
                (uint64_t)0, 0, 0, 0,
                0, 0, (uint64_t)0, (uint64_t)0, 0, 0,
                QRR_FULL_MMAP_SNAPSHOT_ACCESS, 0, 0, snapshot_hex);
        fprintf(stderr,
                "qrr-full: mmap snapshot process=%016" PRIx64
                " mapping=%016" PRIx64 " event=%" PRIu64
                " offset=%016" PRIx64 " bytes=%zu source=guest\n",
                mapping->process_token, mapping->mapping_id,
                state->mmap_event_seq, (uint64_t)page_offset,
                (size_t)TARGET_PAGE_SIZE);
        free(snapshot_hex);
        snapshot_hex = NULL;
        free(snapshot);
        snapshot = NULL;
    }
    fprintf(stderr,
            "qrr-full: mmap mapping process=%016" PRIx64
            " mapping=%016" PRIx64 " seq=%" PRIu64
            " range=" TARGET_FMT_lx "+" TARGET_FMT_lx
            " fd=%d offset=%" PRIu64 " path=%s\n",
            mapping->process_token, mapping->mapping_id,
            mapping->mmap_sequence, mapping->start, mapping->length,
            mapping->fd, mapping->file_offset,
            mapping->path ? mapping->path : "-");
    return true;
}

static QrrFullMmapMapping *qrr_full_find_mmap_mapping(
    target_ulong pgd, uint64_t process_token, target_ulong addr)
{
    QrrFullMmapMapping *mapping;

    for (mapping = qrr_full_mmap_mappings; mapping;
         mapping = mapping->next) {
        target_ulong span;

        if (mapping->pgd != pgd ||
            mapping->process_token != process_token ||
            addr < mapping->start) {
            continue;
        }
        span = TARGET_PAGE_ALIGN(mapping->length);
        if (addr - mapping->start < span) {
            return mapping;
        }
    }
    return NULL;
}

/* Record the exact address-space transition selected by the guest kernel.
 * This is an internal effect record, not copied guest memory.  The mapping
 * id links the transition to the mmap-v3 object so later real page faults in
 * grown or moved pages remain part of the same deep-copy map. */
static char *qrr_full_record_mremap_effect(CPUState *cpu,
                                           const QrrFullPending *pending,
                                           int64_t ret,
                                           size_t *payload_bytes,
                                           const char **failure_reason)
{
    static const unsigned char magic[] = { 'Q', 'R', 'R', 'B' };
    QrrFullMmapMapping *mapping;
    QrrFullMmapPage *new_page_records = NULL;
    QrrFullBuffer effect;
    QrrFullBuffer snapshots;
    QrrFullBuffer bundle;
    target_ulong old_start = pending->args[0];
    target_ulong old_length = pending->args[1];
    target_ulong new_length = pending->args[2];
    target_ulong flags = pending->args[3];
    target_ulong requested_start = pending->args[4];
    target_ulong new_start = (target_ulong)ret;
    target_ulong old_span;
    target_ulong new_span;
    target_ulong page_offset;
    unsigned char *snapshot = NULL;
    DECAF_GVATranslationStatus snapshot_status;
    uint32_t snapshot_count = 0;
    char *hex = NULL;

    *payload_bytes = 0;
    memset(&effect, 0, sizeof(effect));
    memset(&snapshots, 0, sizeof(snapshots));
    memset(&bundle, 0, sizeof(bundle));
    if (!old_length || !new_length ||
        (old_start & (TARGET_PAGE_SIZE - 1)) ||
        (new_start & (TARGET_PAGE_SIZE - 1)) ||
        old_length > ~(target_ulong)0 - (TARGET_PAGE_SIZE - 1) ||
        new_length > ~(target_ulong)0 - (TARGET_PAGE_SIZE - 1) ||
        old_start > ~(target_ulong)0 - (old_length - 1) ||
        new_start > ~(target_ulong)0 - (new_length - 1)) {
        *failure_reason = "mremap-invalid-range";
        goto out;
    }
    old_span = TARGET_PAGE_ALIGN(old_length);
    new_span = TARGET_PAGE_ALIGN(new_length);
    mapping = qrr_full_find_mmap_mapping(
        pending->pgd, pending->process_token, old_start);
    if (!mapping || mapping->process_token != pending->process_token ||
        mapping->start != old_start || mapping->length != old_length) {
        *failure_reason = "mremap-mapping-not-exact";
        goto out;
    }
    /* Linux requires FIXED to imply MAYMOVE, and a successful fixed remap
     * must return the requested address.  A non-moving request cannot return
     * a different address. */
    if (((flags & 2) && (!(flags & 1) || new_start != requested_start)) ||
        (!(flags & 1) && new_start != old_start)) {
        *failure_reason = "mremap-return-contract";
        goto out;
    }

    /* mremap growth has the same lazy-page contract as mmap.  Copy only
     * extension pages whose guest Linux PTE is present when mremap returns;
     * absent pages are deliberately omitted so a later successful real
     * page fault supplies their bytes and exact execution anchor. */
    snapshot = malloc(TARGET_PAGE_SIZE);
    if (!snapshot) {
        *failure_reason = "mremap-snapshot-allocation-failed";
        goto out;
    }
    for (page_offset = old_span; page_offset < new_span;
         page_offset += TARGET_PAGE_SIZE) {
        QrrFullMmapPage *page_record;

        snapshot_status = qrr_full_read_present_mmap_page(
            cpu, pending->pgd, new_start + page_offset, snapshot);
        if (snapshot_status == DECAF_GVA_NOT_PRESENT) {
            fprintf(stderr,
                    "qrr-full: mremap snapshot process=%016" PRIx64
                    " mapping=%016" PRIx64 " offset=%016" PRIx64
                    " source=pte-absent\n",
                    mapping->process_token, mapping->mapping_id,
                    (uint64_t)page_offset);
            continue;
        }
        if (snapshot_status != DECAF_GVA_TRANSLATED) {
            fprintf(stderr,
                    "qrr-full: mremap baseline page-table walk failed"
                    " process=%016" PRIx64 " mapping=%016" PRIx64
                    " pgd=" TARGET_FMT_lx " page=" TARGET_FMT_lx "\n",
                    mapping->process_token, mapping->mapping_id,
                    pending->pgd, new_start + page_offset);
            exit(2);
        }
        if (snapshot_count == UINT32_MAX ||
            qrr_full_max_blob < 64 + sizeof(uint64_t) + TARGET_PAGE_SIZE ||
            snapshot_count >=
                (qrr_full_max_blob - 64) /
                (sizeof(uint64_t) + TARGET_PAGE_SIZE) ||
            !qrr_full_buf_append_le64(&snapshots,
                                      (uint64_t)page_offset) ||
            !qrr_full_buf_append(&snapshots, snapshot, TARGET_PAGE_SIZE)) {
            *failure_reason = "mremap-snapshot-encode-failed";
            goto out;
        }
        page_record = calloc(1, sizeof(*page_record));
        if (!page_record) {
            *failure_reason = "mremap-snapshot-page-allocation-failed";
            goto out;
        }
        page_record->page_offset = page_offset;
        page_record->present_at_mremap = true;
        page_record->next = new_page_records;
        new_page_records = page_record;
        snapshot_count++;
        fprintf(stderr,
                "qrr-full: mremap snapshot process=%016" PRIx64
                " mapping=%016" PRIx64 " offset=%016" PRIx64
                " bytes=%u source=guest\n",
                mapping->process_token, mapping->mapping_id,
                (uint64_t)page_offset, TARGET_PAGE_SIZE);
    }
    if (!qrr_full_buf_append_le64(&effect, mapping->mapping_id) ||
        !qrr_full_buf_append_le64(&effect, (uint64_t)old_start) ||
        !qrr_full_buf_append_le64(&effect, (uint64_t)old_length) ||
        !qrr_full_buf_append_le64(&effect, (uint64_t)new_start) ||
        !qrr_full_buf_append_le64(&effect, (uint64_t)new_length) ||
        !qrr_full_buf_append_le64(&effect, (uint64_t)flags) ||
        !qrr_full_buf_append_le64(&effect, (uint64_t)requested_start) ||
        !qrr_full_buf_append_le32(
            &effect, QRR_FULL_MREMAP_EFFECT_SNAPSHOT_VERSION) ||
        !qrr_full_buf_append_le32(&effect, snapshot_count) ||
        !qrr_full_buf_append(&effect, snapshots.data, snapshots.len) ||
        !qrr_full_buf_append(&bundle, magic, sizeof(magic)) ||
        !qrr_full_buf_append_u8(&bundle, QRR_FULL_BUNDLE_VERSION) ||
        !qrr_full_buf_append_le16(&bundle, 0) ||
        !qrr_full_append_output_bytes(&bundle,
                QRR_FULL_OUTPUT_MREMAP_EFFECT, 0, 0,
                effect.data, effect.len)) {
        *failure_reason = "mremap-effect-encode-failed";
        goto out;
    }
    bundle.data[5] = bundle.outputs & 0xff;
    bundle.data[6] = (bundle.outputs >> 8) & 0xff;
    *payload_bytes = bundle.payload_bytes;
    hex = qrr_full_hex_from_bytes(bundle.data, bundle.len);
    if (!hex) {
        *failure_reason = "mremap-effect-hex-failed";
        goto out;
    }

    while (new_page_records) {
        QrrFullMmapPage *page_record = new_page_records;

        new_page_records = page_record->next;
        page_record->next = mapping->pages;
        mapping->pages = page_record;
    }
    mapping->start = new_start;
    mapping->length = new_length;
    fprintf(stderr,
            "qrr-full: mremap effect process=%016" PRIx64
            " mapping=%016" PRIx64 " seq=%" PRIu64
            " old=" TARGET_FMT_lx "+" TARGET_FMT_lx
            " new=" TARGET_FMT_lx "+" TARGET_FMT_lx
            " flags=" TARGET_FMT_lx " requested=" TARGET_FMT_lx
            " extension_snapshots=%" PRIu32 "\n",
            mapping->process_token, mapping->mapping_id,
            pending->sequence, old_start, old_length,
            new_start, new_length, flags, requested_start, snapshot_count);

out:
    free(snapshot);
    while (new_page_records) {
        QrrFullMmapPage *page_record = new_page_records;

        new_page_records = page_record->next;
        free(page_record);
    }
    qrr_full_buf_free(&effect);
    qrr_full_buf_free(&snapshots);
    qrr_full_buf_free(&bundle);
    return hex;
}

static QrrFullMmapPage *qrr_full_mmap_page_record(
    const QrrFullMmapMapping *mapping, target_ulong page_offset)
{
    QrrFullMmapPage *page;

    for (page = mapping ? mapping->pages : NULL; page; page = page->next) {
        if (page->page_offset == page_offset) {
            return page;
        }
    }
    return NULL;
}

static void qrr_full_page_fault_call_remove(QrrFullPageFaultCall *call)
{
    QrrFullPageFaultCall **link = &qrr_full_page_fault_calls;

    while (*link && *link != call) {
        link = &(*link)->next;
    }
    if (*link) {
        *link = call->next;
        free(call);
    }
}

#ifdef TARGET_MIPS
static target_ulong qrr_full_mips_fault_instruction_pc(uint32_t epc,
                                                        uint32_t cause)
{
    target_ulong fault_pc = (target_ulong)epc;

    /* On MIPS, an exception raised by an instruction in a branch delay slot
     * saves the branch address in EPC and sets Cause.BD.  The instruction
     * that actually accessed the missing page is the 32-bit delay-slot
     * instruction at EPC + 4.  Non-BD exceptions are anchored at EPC itself. */
    if (cause & QRR_FULL_MIPS_CAUSE_BD) {
        fault_pc += 4;
    }
    return fault_pc;
}
#endif

static void qrr_full_record_materialized_mmap_page(
    CPUState *cpu, QrrFullPageFaultCall *call)
{
    QrrFullMmapMapping *mapping = call->mapping;
    QrrFullMmapPage *page_record;
    QrrFullPathState *state;
    target_ulong page = call->address & TARGET_PAGE_MASK;
    target_ulong page_offset = page - mapping->start;
    gpa_t physical = 0;
    DECAF_GVATranslationStatus status;
    unsigned char *bytes;
    char *hex;
    uint64_t path_hash;
    uint64_t dep_hash;

    if (qrr_full_mmap_page_record(mapping, page_offset)) {
        return;
    }
    status = DECAF_get_phys_addr_with_pgd_status(cpu, call->pgd, page,
                                                 &physical);
    if (status == DECAF_GVA_NOT_PRESENT) {
        /* VM_FAULT_RETRY and similar successful-looking returns may leave
         * the PTE absent.  The next genuine do_page_fault invocation is the
         * only place where this page may become a replay event. */
        fprintf(stderr,
                "qrr-full: page fault returned without present PTE"
                " process=%016" PRIx64 " mapping=%016" PRIx64
                " page=" TARGET_FMT_lx "\n",
                call->process_token, mapping->mapping_id, page);
        return;
    }
    if (status != DECAF_GVA_TRANSLATED ||
        (physical & (TARGET_PAGE_SIZE - 1))) {
        fprintf(stderr,
                "qrr-full: page fault PTE walk failed after success"
                " process=%016" PRIx64 " mapping=%016" PRIx64
                " pgd=" TARGET_FMT_lx " page=" TARGET_FMT_lx
                " status=%d pa=%" PRIx64 "\n",
                call->process_token, mapping->mapping_id, call->pgd, page,
                status, (uint64_t)physical);
        exit(2);
    }
    state = qrr_full_path_state_for_task(
        call->pgd, call->task, false);
    if (!state || state->process_token != call->process_token) {
        fprintf(stderr,
                "qrr-full: page fault process state missing"
                " pgd=" TARGET_FMT_lx " process=%016" PRIx64 "\n",
                call->pgd, call->process_token);
        exit(2);
    }
    bytes = malloc(TARGET_PAGE_SIZE);
    page_record = calloc(1, sizeof(*page_record));
    if (!bytes || !page_record) {
        fprintf(stderr, "qrr-full: page fault snapshot allocation failed\n");
        free(bytes);
        free(page_record);
        exit(2);
    }
    cpu_physical_memory_rw(physical, bytes, TARGET_PAGE_SIZE, 0);
    hex = qrr_full_hex_from_bytes(bytes, TARGET_PAGE_SIZE);
    free(bytes);
    if (!hex) {
        fprintf(stderr, "qrr-full: page fault snapshot encode failed\n");
        free(page_record);
        exit(2);
    }
    path_hash = call->path_hash;
    dep_hash = call->dep_hash;
    state->mmap_event_seq++;
    fprintf(qrr_full_mmap_fp,
            "%016" PRIx64 "\t%" PRIu64 "\tfault\t%016" PRIx64
            "\t%" PRIu64 "\t%016" PRIx64 "\t%016" PRIx64
            "\t%016" PRIx64 "\t%016" PRIx64 "\t%016" PRIx64
            "\t%d\t%016" PRIx64 "\t%016" PRIx64 "\t%s"
            "\t%016" PRIx64 "\t%" PRIu64 "\t%d\t%016" PRIx64
            "\t%016" PRIx64 "\t%016" PRIx64 "\t%" PRIu64
            "\t%" PRIu64 "\t%016" PRIx64 "\t%016" PRIx64
            "\t%s\t%016x\t%016x"
            "\t-\t%s\t%d\n",
            call->process_token, state->mmap_event_seq,
            mapping->mapping_id, mapping->mmap_sequence, mapping->mmap_key,
            (uint64_t)mapping->start, (uint64_t)mapping->length,
            (uint64_t)mapping->prot, (uint64_t)mapping->flags, mapping->fd,
            mapping->file_offset, (uint64_t)page_offset,
            call->syscall_anchor ? "syscall" : "user",
            call->syscall_key, call->syscall_sequence, call->syscall_nr,
            (uint64_t)call->fault_pc, (uint64_t)call->edge_from_pc,
            (uint64_t)call->edge_to_pc, call->edge_occurrence,
            call->delivered_signal_sequence, path_hash, dep_hash,
            call->access_kind, 0, 0, hex,
            !!(call->fault_cause & QRR_FULL_MIPS_CAUSE_BD));
    free(hex);
    if (fflush(qrr_full_mmap_fp) != 0) {
        fprintf(stderr, "qrr-full: cannot flush mmap fault event: %s\n",
                strerror(errno));
        free(page_record);
        exit(2);
    }
    if (!call->syscall_anchor) {
        qrr_full_user_precision_add(
            call->pgd, state->task, call->edge_from_pc, call->edge_to_pc,
            !!(call->fault_cause & QRR_FULL_MIPS_CAUSE_BD),
            state->syscall_seq,
            qrr_full_user_edge_current_occurrence(
                call->pgd, state->task, call->edge_from_pc,
                call->edge_to_pc));
    }
    page_record->page_offset = page_offset;
    page_record->materialized_by_fault = true;
    page_record->next = mapping->pages;
    mapping->pages = page_record;
    fprintf(stderr,
            "qrr-full: mmap real-fault process=%016" PRIx64
            " mapping=%016" PRIx64 " event=%" PRIu64
            " page=" TARGET_FMT_lx " offset=" TARGET_FMT_lx
            " anchor=%s syscall_sequence=%" PRIu64
            " edge=" TARGET_FMT_lx "->" TARGET_FMT_lx "#%" PRIu64
            " delivered_signal_sequence=%" PRIu64
            " fault_epc=" TARGET_FMT_lx " fault_cause=%08" PRIx32
            " delay_slot=%d fault_pc=" TARGET_FMT_lx " access=%s\n",
            call->process_token, mapping->mapping_id,
            state->mmap_event_seq, page, page_offset,
            call->syscall_anchor ? "syscall" : "user",
            call->syscall_sequence, call->edge_from_pc, call->edge_to_pc,
            call->edge_occurrence, call->delivered_signal_sequence,
            call->fault_epc, call->fault_cause,
            !!(call->fault_cause & QRR_FULL_MIPS_CAUSE_BD), call->fault_pc,
            call->access_kind);
}

/* Capture only Linux VM faults.  do_page_fault supplies saved EPC/Cause and
 * the faulting address.  Cause.BD distinguishes a fault in a branch delay
 * slot, whose actual instruction PC is EPC + 4.  handle_mm_fault returning
 * without VM_FAULT_ERROR proves that the guest kernel completed the VM
 * operation.
 * A direct PGD walk after that return proves the PTE is now present before
 * any bytes are copied.  QEMU soft-TLB and MIPS TLB activity never enters
 * this path.  A user EPC is an exact instruction anchor.  A kernel EPC is
 * accepted only while an exact target syscall is pending and is bound to that
 * syscall's recorded identity; no syscall type is inferred here. */
static void qrr_full_note_page_fault(CPUState *cpu, target_ulong pc)
{
#ifdef TARGET_MIPS
    CPUArchState *env = cpu->env_ptr;
    QrrFullPageFaultCall *call;
    QrrFullPageFaultCall *next;
    QrrFullMmapMapping *mapping;
    QrrFullMmapPage *existing;
    QrrFullPending *pending;
    QrrFullPathState *state;
    target_ulong pgd = qrr_full_current_pgd(cpu);
    target_ulong address;
    target_ulong page_offset;
    uint32_t fault_epc;
    uint32_t fault_cause;
    target_ulong fault_pc;
    DECAF_GVATranslationStatus status;
    gpa_t physical = 0;

    if (!qrr_full_mmap_fp || !qrr_full_do_page_fault ||
        !qrr_full_handle_mm_fault) {
        return;
    }
    if (pc == qrr_full_do_page_fault) {
        address = env->active_tc.gpr[6];
        state = qrr_full_path_state_for_task(
            pgd, qrr_full_cpu_thread(cpu, pgd), false);
        if (!state || !state->process_token) {
            return;
        }
        mapping = qrr_full_find_mmap_mapping(
            pgd, state->process_token, address);
        if (!mapping || mapping->process_token == 0) {
            return;
        }
        if (!qrr_full_read_target_u32(
                cpu,
                env->active_tc.gpr[4] +
                    QRR_FULL_MIPS_PT_REGS_CAUSE_OFFSET,
                &fault_cause) ||
            !qrr_full_read_target_u32(
                cpu, env->active_tc.gpr[4] + QRR_FULL_MIPS_PT_REGS_EPC_OFFSET,
                &fault_epc)) {
            fprintf(stderr,
                    "qrr-full: cannot read do_page_fault pt_regs Cause/EPC"
                    " process=%016" PRIx64 " mapping=%016" PRIx64
                    " regs=" TARGET_FMT_lx "\n",
                    mapping->process_token, mapping->mapping_id,
                    env->active_tc.gpr[4]);
            exit(2);
        }
        fault_pc = qrr_full_mips_fault_instruction_pc(fault_epc,
                                                       fault_cause);
        page_offset = (address & TARGET_PAGE_MASK) - mapping->start;
        existing = qrr_full_mmap_page_record(mapping, page_offset);
        if (existing) {
            return;
        }
        /* A user fault can recurse while handle_mm_fault() materializes the
         * same mapping page.  The nested pt_regs then contains a kernel EPC,
         * but it is not a second page event and it is not evidence of a
         * syscall.  Bind it to the exact already-active mapping/page/task
         * fault instead of trying to invent a kernel syscall anchor.  The
         * outer handle_mm_fault return remains the sole point at which the
         * now-present page is copied. */
        for (call = qrr_full_page_fault_calls; call; call = call->next) {
            target_ulong current_task = qrr_full_cpu_thread(cpu, pgd);

            if (call->cpu == cpu && call->pgd == pgd &&
                call->mapping == mapping &&
                (call->address & TARGET_PAGE_MASK) ==
                    (address & TARGET_PAGE_MASK) &&
                (!current_task || call->task == current_task)) {
                fprintf(stderr,
                        "qrr-full: nested mmap fault joined active page"
                        " process=%016" PRIx64 " mapping=%016" PRIx64
                        " page=" TARGET_FMT_lx
                        " outer_fault_pc=" TARGET_FMT_lx
                        " nested_fault_pc=" TARGET_FMT_lx "\n",
                        mapping->process_token, mapping->mapping_id,
                        address & TARGET_PAGE_MASK, call->fault_pc, fault_pc);
                return;
            }
        }
        status = DECAF_get_phys_addr_with_pgd_status(
            cpu, pgd, address & TARGET_PAGE_MASK, &physical);
        if (status == DECAF_GVA_TRANSLATED) {
            /* This is a protection/COW fault on an already materialized
             * page, not delayed file data missing from the mmap baseline. */
            return;
        }
        if (status != DECAF_GVA_NOT_PRESENT) {
            fprintf(stderr,
                    "qrr-full: page-table walk failed at do_page_fault"
                    " process=%016" PRIx64 " mapping=%016" PRIx64
                    " pgd=" TARGET_FMT_lx " address=" TARGET_FMT_lx
                    " status=%d\n",
                    mapping->process_token, mapping->mapping_id, pgd,
                    address, status);
            exit(2);
        }
        call = calloc(1, sizeof(*call));
        if (!call) {
            fprintf(stderr, "qrr-full: cannot allocate page fault call\n");
            exit(2);
        }
        call->cpu = cpu;
        call->pgd = pgd;
        call->process_token = mapping->process_token;
        call->mapping = mapping;
        call->address = address;
        call->regs_ptr = env->active_tc.gpr[4];
        call->fault_epc = (target_ulong)fault_epc;
        call->fault_pc = fault_pc;
        call->fault_cause = fault_cause;
        call->do_page_fault_return_pc = env->active_tc.gpr[31];
        state = qrr_full_path_state_for_task(
            pgd, qrr_full_cpu_thread(cpu, pgd), false);
        if (!state || state->process_token != mapping->process_token) {
            fprintf(stderr,
                    "qrr-full: page fault has no matching process state"
                    " pgd=" TARGET_FMT_lx " process=%016" PRIx64 "\n",
                    pgd, mapping->process_token);
            free(call);
            exit(2);
        }
        call->task = state->task;
        if (qrr_full_user_pc(fault_pc)) {
            call->syscall_anchor = false;
            call->syscall_sequence = state->syscall_seq;
            if (state->have_interrupted_user_edge &&
                state->interrupted_next_pc != fault_pc) {
                fprintf(stderr,
                        "qrr-full: user mmap fault contradicts saved"
                        " interrupted edge pgd=" TARGET_FMT_lx
                        " process=%016" PRIx64
                        " fault_pc=" TARGET_FMT_lx
                        " have_interrupt=%d interrupt_next=" TARGET_FMT_lx
                        "\n",
                        pgd, mapping->process_token, fault_pc,
                        state->have_interrupted_user_edge,
                        state->interrupted_next_pc);
                free(call);
                exit(2);
            }
            /* cpu_loop_exit() has no host return PC to restore for a few
             * architecturally precise MIPS exceptions.  In that case the
             * pending TB was discarded, while pt_regs still supplies the
             * exact faulting instruction.  Use the last completed user PC
             * exactly as signal delivery does at a kernel-to-user boundary;
             * this is the semantic execution edge, not a PC-only anchor. */
            call->edge_from_pc = state->have_interrupted_user_edge ?
                state->interrupted_edge_from_pc :
                (state->have_previous_user_edge_pc ?
                 state->previous_user_edge_pc : 0);
            call->edge_to_pc = fault_pc;
            call->edge_occurrence =
                qrr_full_user_precision_next_occurrence(
                    pgd, state->task, state->syscall_seq,
                    call->edge_from_pc,
                    call->edge_to_pc,
                    !!(call->fault_cause & QRR_FULL_MIPS_CAUSE_BD));
            call->delivered_signal_sequence = state->signal_seq;
            qrr_full_current_mmap_context(
                state, &call->path_hash, &call->dep_hash);
        } else {
            pending = qrr_full_pending_find_task(pgd, state->task);
            if (!pending || pending->process_token != mapping->process_token) {
                fprintf(stderr,
                        "qrr-full: kernel mmap page fault has no active"
                        " target syscall process=%016" PRIx64
                        " mapping=%016" PRIx64 " pgd=" TARGET_FMT_lx
                        " fault_pc=" TARGET_FMT_lx
                        " address=" TARGET_FMT_lx "\n",
                        mapping->process_token, mapping->mapping_id, pgd,
                        fault_pc, address);
                free(call);
                exit(2);
            }
            call->syscall_anchor = true;
            call->syscall_key = pending->key;
            call->syscall_sequence = pending->sequence;
            call->syscall_nr = pending->syscall_nr;
            call->delivered_signal_sequence = state->signal_seq;
            call->path_hash = pending->path_hash;
            call->dep_hash = pending->dep_hash;
        }
        if (env->active_tc.gpr[5]) {
            call->access_kind = "store";
        } else if (fault_pc == address) {
            /* Compare against the actual faulting instruction, including a
             * delay-slot PC selected through Cause.BD. */
            call->access_kind = "fetch";
        } else {
            call->access_kind = "load";
        }
        call->next = qrr_full_page_fault_calls;
        qrr_full_page_fault_calls = call;
        return;
    }
    if (pc == qrr_full_handle_mm_fault) {
        address = env->active_tc.gpr[6];
        for (call = qrr_full_page_fault_calls; call; call = call->next) {
            if (call->cpu == cpu && call->pgd == pgd &&
                call->address == address &&
                !call->handle_mm_fault_active) {
                call->handle_mm_fault_active = true;
                call->handle_mm_fault_return_pc = env->active_tc.gpr[31];
                break;
            }
        }
        return;
    }
    for (call = qrr_full_page_fault_calls; call; call = call->next) {
        if (call->cpu == cpu && call->handle_mm_fault_active &&
            call->handle_mm_fault_return_pc == pc) {
            call->handle_mm_fault_active = false;
            if (qrr_full_current_pgd(cpu) == call->pgd &&
                !(env->active_tc.gpr[2] & QRR_FULL_VM_FAULT_ERROR)) {
                qrr_full_record_materialized_mmap_page(cpu, call);
            }
            break;
        }
    }
    for (call = qrr_full_page_fault_calls; call; call = next) {
        next = call->next;
        if (call->cpu == cpu && call->do_page_fault_return_pc == pc) {
            qrr_full_page_fault_call_remove(call);
            return;
        }
    }
#else
    (void)cpu;
    (void)pc;
#endif
}

static bool qrr_full_exec_filename_matches_target(const QrrFullBuffer *filename)
{
    const unsigned char *basename;
    size_t basename_len;
    size_t target_len;
    size_t i;

    if (!qrr_full_target_name || !filename || !filename->data ||
        !filename->len) {
        return false;
    }
    basename = filename->data;
    basename_len = filename->len;
    for (i = 0; i < filename->len; i++) {
        if (filename->data[i] == '/') {
            basename = filename->data + i + 1;
            basename_len = filename->len - i - 1;
        }
    }
    target_len = strlen(qrr_full_target_name);
    return basename_len == target_len &&
           memcmp(basename, qrr_full_target_name, target_len) == 0;
}

static bool qrr_full_exec_event(CPUState *cpu, target_ulong pgd,
                                target_ulong entry_pc, target_ulong stack,
                                int syscall_nr,
                                const target_ulong args[6],
                                bool *matched_target)
{
    QrrFullBuffer filename;
    QrrFullBuffer argv;
    QrrFullExecPending *pending = NULL;
    target_ulong argv_addr = args[1];
    uint32_t argc = 0;
    bool target_match = false;
    target_ulong source_task = qrr_full_cpu_thread(cpu, pgd);
    QrrFullPathState *source_state = qrr_full_path_state_for_task(
        pgd, source_task, false);
    bool source_was_target = source_state && source_state->process_token;
    bool filename_captured;

    if (!qrr_full_is_execve_syscall(syscall_nr)) {
        return false;
    }
    *matched_target = false;
    memset(&filename, 0, sizeof(filename));
    memset(&argv, 0, sizeof(argv));
    filename_captured = qrr_full_read_guest_string(
        cpu, args[0], &filename, false);
    if (!filename_captured && !source_was_target) {
        goto out;
    }
    target_match = filename_captured &&
        qrr_full_exec_filename_matches_target(&filename);
    *matched_target = target_match;
    if (!target_match && !source_was_target) {
        goto out;
    }
    pending = calloc(1, sizeof(*pending));
    if (!pending) {
        fprintf(stderr, "qrr-full: cannot allocate target exec pending\n");
        exit(2);
    }
    pending->cpu = cpu;
    pending->pgd = pgd;
    pending->entry_pc = entry_pc;
    pending->stack = stack;
    pending->syscall_nr = syscall_nr;
    pending->target_match = target_match;
    pending->source_was_target = source_was_target;
    if (source_was_target) {
        pending->task = source_task;
        pending->have_task = true;
        pending->process_token = source_state->process_token;
        pending->thread_token = source_state->thread_token;
    }
    if (!filename_captured) {
        /* A valid exec filename may live in a demand-paged user VMA.  At the
         * syscall boundary the guest kernel has not run copy_from_user yet,
         * so failure of the collector's VA->PA walk does not prove an invalid
         * exec.  Keep the exact task-bound pending event and let the real
         * proc_exec_connector decide successful target/non-target identity.
         * If exec fails, the normal userspace return discards this pending
         * record without changing process ownership. */
        snprintf(pending->capture_error, sizeof(pending->capture_error),
                 "filename_not_resident_at_entry");
        fprintf(stderr,
                "qrr-full: deferred bound process exec identity to"
                " proc_exec_connector pgd=" TARGET_FMT_lx
                " entry_pc=" TARGET_FMT_lx " filename=" TARGET_FMT_lx
                "\n", pgd, entry_pc, args[0]);
        goto queue;
    }
    pending->filename_hex = qrr_full_hex_from_bytes(
        filename.data, filename.len);
    if (!pending->filename_hex) {
        snprintf(pending->capture_error, sizeof(pending->capture_error),
                 "filename_encode_failed");
        goto queue;
    }
    if (!argv_addr) {
        snprintf(pending->capture_error, sizeof(pending->capture_error),
                 "argv_missing");
        goto queue;
    }
    while (argc < 256) {
        target_ulong pointer;

        if (!qrr_full_read_target_ulong(
                cpu, argv_addr + argc * TARGET_LONG_SIZE, &pointer)) {
            snprintf(pending->capture_error, sizeof(pending->capture_error),
                     "argv_pointer_capture_failed");
            goto queue;
        }
        if (!pointer) {
            break;
        }
        if (!qrr_full_read_guest_string(cpu, pointer, &argv, true)) {
            snprintf(pending->capture_error, sizeof(pending->capture_error),
                     "argv_string_capture_failed");
            goto queue;
        }
        argc++;
    }
    if (argc == 256) {
        snprintf(pending->capture_error, sizeof(pending->capture_error),
                 "argv_limit");
        goto queue;
    }
    pending->argv_hex = qrr_full_hex_from_bytes(argv.data, argv.len);
    if (!pending->argv_hex) {
        snprintf(pending->capture_error, sizeof(pending->capture_error),
                 "argv_encode_failed");
    }

queue:
    pending->argc = argc;
    pending->next = qrr_full_exec_pending;
    qrr_full_exec_pending = pending;
    fprintf(stderr,
            "qrr-full: exec syscall pending source_pgd="
            TARGET_FMT_lx " entry_pc=" TARGET_FMT_lx " argc=%u reason=%s\n",
            pgd, entry_pc, argc,
            pending->capture_error[0] ? pending->capture_error : "-");

out:
    if (!pending && target_match) {
        fprintf(stderr, "qrr-full: target exec metadata was not queued\n");
        exit(2);
    }
    qrr_full_buf_free(&filename);
    qrr_full_buf_free(&argv);
    return true;
}

static void qrr_full_event(QrrFullPending *pending, target_ulong return_pc,
                           int64_t ret, int out_arg, size_t output_bytes,
                           const char *status, const char *reason)
{
    if (!qrr_full_event_fp || !pending) {
        return;
    }
    fprintf(qrr_full_event_fp,
            "%" PRIu64 "\t%016" PRIx64 "\t%016" PRIx64 "\t%016" PRIx64
            "\t%d\t%" PRId64 "\t%d\t%zu\t" TARGET_FMT_lx "\t"
            TARGET_FMT_lx "\t" TARGET_FMT_lx "\t" TARGET_FMT_lx "\t"
            TARGET_FMT_lx "\t" TARGET_FMT_lx "\t" TARGET_FMT_lx "\t"
            TARGET_FMT_lx "\t%s\t%s\n",
            pending->sequence, pending->key, pending->path_hash,
            pending->dep_hash, pending->syscall_nr, ret, out_arg,
            output_bytes, pending->pgd, pending->entry_pc, return_pc,
            pending->stack, pending->args[0], pending->args[1],
            pending->args[2], pending->args[3], status, reason);
}

static void qrr_full_pending_insert(QrrFullPending *pending)
{
    pending->next = qrr_full_pending_head;
    qrr_full_pending_head = pending;
}

static void qrr_full_record_successful_exec(target_ulong source_pgd,
                                            target_ulong task,
                                            bool target_match,
                                            uint64_t next_process_token)
{
    QrrFullPending *last = NULL;
    QrrFullPending *pending = qrr_full_pending_head;
    int out_arg = target_match ? QRR_FULL_RESULT_OUT_ARG_EXEC_REBIND :
                                 QRR_FULL_RESULT_OUT_ARG_EXEC_UNBIND;
    char token_hex[17] = "-";

    while (pending) {
        if (pending->pgd == source_pgd && (!task || pending->task == task) &&
            qrr_full_is_execve_syscall(pending->syscall_nr)) {
            if (last) {
                last->next = pending->next;
            } else {
                qrr_full_pending_head = pending->next;
            }
            pending->next = NULL;
            break;
        }
        last = pending;
        pending = pending->next;
    }
    /* Initial target startup is intentionally outside the prior process's
     * QRR scope and therefore has no syscall-result entry to complete. */
    if (!pending) {
        return;
    }
    if (target_match) {
        int i;

        if (!next_process_token) {
            fprintf(stderr, "qrr-full: target exec produced zero process token\n");
            exit(2);
        }
        for (i = 0; i < 8; i++) {
            static const char digits[] = "0123456789abcdef";
            unsigned int byte =
                (next_process_token >> ((7 - i) * 8)) & 0xff;

            token_hex[i * 2] = digits[byte >> 4];
            token_hex[i * 2 + 1] = digits[byte & 0xf];
        }
        token_hex[16] = '\0';
    }
    qrr_full_write_result_row(pending, 0, out_arg, token_hex);
    qrr_full_schedule_commit(pending);
    qrr_full_event(pending, 0, 0, out_arg,
                   target_match ? 8 : 0, "record",
                   target_match ? "exec_target" : "exec_non_target");
    free(pending->open_path);
    free(pending);
}

static bool qrr_full_record_terminal_exec(target_ulong source_pgd,
                                          target_ulong task)
{
    QrrFullPending *last = NULL;
    QrrFullPending *pending = qrr_full_pending_head;

    while (pending) {
        if (pending->pgd == source_pgd && (!task || pending->task == task) &&
            qrr_full_is_execve_syscall(pending->syscall_nr)) {
            if (last) {
                last->next = pending->next;
            } else {
                qrr_full_pending_head = pending->next;
            }
            pending->next = NULL;
            break;
        }
        last = pending;
        pending = pending->next;
    }
    if (!pending) {
        return false;
    }
    qrr_full_write_result_row(pending, 0,
                              QRR_FULL_RESULT_OUT_ARG_EXEC_TERMINATE, "-");
    qrr_full_schedule_commit(pending);
    qrr_full_event(pending, 0, 0,
                   QRR_FULL_RESULT_OUT_ARG_EXEC_TERMINATE, 0,
                   "record", "exec_terminal_exit");
    fprintf(stderr,
            "qrr-full: terminal exec process=%016" PRIx64
            " sequence=%" PRIu64 " task=" TARGET_FMT_lx
            " source_pgd=" TARGET_FMT_lx "\n",
            pending->process_token, pending->sequence, task, source_pgd);
    free(pending->open_path);
    free(pending);
    return true;
}

static QrrFullPending *qrr_full_pending_find_task(target_ulong pgd,
                                                  target_ulong task)
{
    QrrFullPending *pending;

    for (pending = qrr_full_pending_head; pending; pending = pending->next) {
        if (pending->pgd == pgd && (!task || pending->task == task)) {
            return pending;
        }
    }
    return NULL;
}

/* For one exact thread execution instance, a second trap at an entry PC/SP
 * whose first trap is
 * still pending is the kernel's re-entry into that same logical syscall.
 * Match the complete saved user register identity so a syscall made by a
 * signal handler remains an independent operation.  In particular, do not
 * infer restart from EINTR, a syscall number, or adjacency in the table. */
static QrrFullPending *qrr_full_pending_find_entry_anchor(
    target_ulong pgd, target_ulong task, target_ulong entry_pc,
    target_ulong stack)
{
    QrrFullPending *pending;

    for (pending = qrr_full_pending_head; pending; pending = pending->next) {
        if (pending->pgd == pgd && pending->task == task &&
            pending->entry_pc == entry_pc &&
            pending->stack == stack) {
            return pending;
        }
    }
    return NULL;
}

static bool qrr_full_pending_same_attempt(
    const QrrFullPending *pending, int syscall_nr,
    const target_ulong args[6])
{
    return pending->syscall_nr == syscall_nr &&
           memcmp(pending->args, args, sizeof(pending->args)) == 0;
}

static void qrr_full_semaphore_lock_call_remove(
    QrrFullSemaphoreLockCall *call)
{
    QrrFullSemaphoreLockCall **link = &qrr_full_semaphore_lock_calls;

    while (*link && *link != call) {
        link = &(*link)->next;
    }
    if (*link) {
        *link = call->next;
        free(call);
    }
}

/* ipc_lock_check() is resolved from the configured vmlinux.  Its successful
 * return is the exact guest-kernel decision that identifies the sem_array
 * used by this target syscall.  We retain only the pointer here; values are
 * read after the syscall has committed, then semop is reversed exactly to
 * obtain the state that must exist before replaying the operation. */
static void qrr_full_note_semaphore_lock(CPUState *cpu, target_ulong pc)
{
#ifdef TARGET_MIPS
    CPUArchState *env = cpu->env_ptr;
    QrrFullSemaphoreLockCall *call;
    QrrFullSemaphoreLockCall *next;
    QrrFullPending *pending;
    target_ulong pgd;
    target_ulong result;

    if (!qrr_full_ipc_lock_check) {
        return;
    }
    pgd = qrr_full_current_pgd(cpu);
    if (pc == qrr_full_ipc_lock_check) {
        pending = qrr_full_pending_find_task(
            pgd, qrr_full_cpu_thread(cpu, pgd));
        if (!pending || pending->semaphore_array ||
            !qrr_full_semaphore_state_required(pending)) {
            return;
        }
        for (call = qrr_full_semaphore_lock_calls; call;
             call = call->next) {
            if (call->cpu == cpu && call->pending == pending) {
                return;
            }
        }
        call = calloc(1, sizeof(*call));
        if (!call) {
            fprintf(stderr,
                    "qrr-full: cannot allocate semaphore lock call\n");
            exit(2);
        }
        call->cpu = cpu;
        call->pgd = pgd;
        call->return_pc = env->active_tc.gpr[31];
        call->pending = pending;
        call->next = qrr_full_semaphore_lock_calls;
        qrr_full_semaphore_lock_calls = call;
        return;
    }
    for (call = qrr_full_semaphore_lock_calls; call; call = next) {
        next = call->next;
        if (call->cpu != cpu || call->return_pc != pc) {
            continue;
        }
        result = env->active_tc.gpr[2];
        if (qrr_full_current_pgd(cpu) == call->pgd && result &&
            result < (target_ulong)-4095 && call->pending &&
            !call->pending->semaphore_array) {
            call->pending->semaphore_array = result;
            fprintf(stderr,
                    "qrr-full: semaphore object process=%016" PRIx64
                    " seq=%" PRIu64 " array=" TARGET_FMT_lx "\n",
                    call->pending->process_token,
                    call->pending->sequence, result);
        }
        qrr_full_semaphore_lock_call_remove(call);
        return;
    }
#else
    (void)cpu;
    (void)pc;
#endif
}

static bool qrr_full_read_semaphore_values(CPUState *cpu,
                                           target_ulong sem_array,
                                           uint32_t *values,
                                           size_t capacity,
                                           size_t *count,
                                           const char **failure)
{
#ifdef TARGET_MIPS
    target_ulong sem_base;
    target_ulong nsems;
    size_t i;

    if (!cpu || !sem_array || !count || !qrr_full_sem_size ||
        !qrr_full_read_target_ulong(
            cpu, sem_array + qrr_full_sem_array_base_offset, &sem_base) ||
        !sem_base ||
        !qrr_full_read_target_ulong(
            cpu, sem_array + qrr_full_sem_array_nsems_offset, &nsems) ||
        !nsems) {
        *failure = "semaphore-layout-read-failed";
        return false;
    }
    if ((uint64_t)nsems > SIZE_MAX ||
        (uint64_t)nsems >
            ((uint64_t)(target_ulong)-1 - sem_base) / qrr_full_sem_size) {
        *failure = "semaphore-layout-overflow";
        return false;
    }
    *count = (size_t)nsems;
    if (!values) {
        if (capacity) {
            *failure = "semaphore-values-null";
            return false;
        }
        return true;
    }
    if (capacity < *count) {
        *failure = "semaphore-values-capacity";
        return false;
    }
    for (i = 0; i < *count; i++) {
        target_ulong value;
        target_ulong address = sem_base + i * qrr_full_sem_size +
            qrr_full_sem_value_offset;

        if (!qrr_full_read_target_ulong(cpu, address, &value) ||
            value > INT_MAX) {
            *failure = "semaphore-value-read-failed";
            return false;
        }
        values[i] = value;
    }
    return true;
#else
    (void)cpu;
    (void)sem_array;
    (void)values;
    (void)capacity;
    (void)count;
    *failure = "semaphore-state-unsupported-architecture";
    return false;
#endif
}

static bool qrr_full_capture_semaphore_state(CPUState *cpu,
                                             QrrFullPending *pending,
                                             const char **failure)
{
#ifdef TARGET_MIPS
    uint32_t *values = NULL;
    size_t nsems = 0;
    size_t captured_nsems = 0;
    target_ulong operation;

    *failure = NULL;
    if (!qrr_full_semaphore_state_required(pending)) {
        return true;
    }
    if (!pending->semaphore_array) {
        *failure = "semaphore-array-not-observed";
        return false;
    }
    if (!qrr_full_read_semaphore_values(
            cpu, pending->semaphore_array, NULL, 0, &nsems, failure) ||
        !nsems ||
        nsems > qrr_full_max_blob / sizeof(*values)) {
        fprintf(stderr,
                "qrr-full: semaphore state size failed process=%016"
                PRIx64 " seq=%" PRIu64 " reason=%s nsems=%zu\n",
                pending->process_token, pending->sequence,
                *failure ? *failure : "invalid-size", nsems);
        *failure = "semaphore-state-size-failed";
        return false;
    }
    values = calloc(nsems, sizeof(*values));
    if (!values || !qrr_full_read_semaphore_values(
            cpu, pending->semaphore_array, values, nsems,
            &captured_nsems, failure) ||
        captured_nsems != nsems) {
        fprintf(stderr,
                "qrr-full: semaphore state read failed process=%016"
                PRIx64 " seq=%" PRIu64 " reason=%s\n",
                pending->process_token, pending->sequence,
                *failure ? *failure : "count-changed");
        free(values);
        *failure = "semaphore-state-read-failed";
        return false;
    }
    operation = pending->args[0] & 0xffff;
    if (operation == QRR_FULL_IPCOP_SEMOP ||
        operation == QRR_FULL_IPCOP_SEMTIMEDOP) {
        target_ulong sops = pending->args[4];
        target_ulong nsops = pending->args[2];
        target_ulong i;

        if (!sops || !nsops || nsops > qrr_full_max_blob /
                QRR_FULL_TARGET_SEMBUF_SIZE ||
            sops > (target_ulong)-1 -
                nsops * QRR_FULL_TARGET_SEMBUF_SIZE) {
            free(values);
            *failure = "semaphore-operations-invalid";
            return false;
        }
        for (i = nsops; i > 0; i--) {
            unsigned char sembuf[QRR_FULL_TARGET_SEMBUF_SIZE];
            target_ulong address = sops +
                (i - 1) * QRR_FULL_TARGET_SEMBUF_SIZE;
            uint16_t sem_num;
            int16_t sem_op;
            int64_t before;

            if (!qrr_full_read_guest(cpu, address, sizeof(sembuf), sembuf)) {
                free(values);
                *failure = "semaphore-operations-read-failed";
                return false;
            }
            sem_num = qrr_full_target_u16_from_bytes(sembuf);
            sem_op = (int16_t)qrr_full_target_u16_from_bytes(sembuf + 2);
            if (sem_num >= nsems) {
                free(values);
                *failure = "semaphore-operation-index-invalid";
                return false;
            }
            if (sem_op == 0) {
                if (values[sem_num] != 0) {
                    free(values);
                    *failure = "semaphore-zero-operation-state-invalid";
                    return false;
                }
                continue;
            }
            before = (int64_t)values[sem_num] - sem_op;
            if (before < 0 || before > INT_MAX) {
                free(values);
                *failure = "semaphore-operation-state-overflow";
                return false;
            }
            values[sem_num] = (uint32_t)before;
        }
    }
    pending->semaphore_values = values;
    pending->semaphore_nsems = nsems;
    fprintf(stderr,
            "qrr-full: semaphore pre-state process=%016" PRIx64
            " seq=%" PRIu64 " nsems=%zu first=%" PRIu32 "\n",
            pending->process_token, pending->sequence, nsems, values[0]);
    return true;
#else
    (void)cpu;
    (void)pending;
    *failure = "semaphore-state-unsupported-architecture";
    return false;
#endif
}

static void qrr_full_signal_call_remove(QrrFullSignalCall *call)
{
    QrrFullSignalCall **link = &qrr_full_signal_calls;

    while (*link && *link != call) {
        link = &(*link)->next;
    }
    if (*link) {
        *link = call->next;
        free(call);
    }
}

static void qrr_full_record_signal_delivery(CPUState *cpu,
                                            QrrFullSignalCall *call,
                                            int signo)
{
#ifdef TARGET_MIPS
    QrrFullPathState *state;
    QrrFullPending *pending;
    uint32_t info_errno;
    uint32_t info_code;
    uint32_t info_pid;
    uint32_t info_uid;
    uint32_t info_status;
    uint32_t info_value;
    uint32_t info_word0;
    uint32_t info_word1;
    uint32_t info_word2;
    uint32_t fault_addr;
    uint32_t interrupted_cause;
    uint32_t interrupted_pc;
    uint32_t delivery_pc;
    uint32_t interrupted_sp;
    uint64_t key = 0;
    uint64_t syscall_sequence = 0;
    uint64_t path_hash;
    uint64_t dep_hash;
    target_ulong edge_from_pc = 0;
    target_ulong edge_to_pc = 0;
    uint64_t edge_occurrence = 0;
    int syscall_nr = -1;
    const char *anchor_kind = "user";
    bool delay_slot;

    if (signo <= 0 || signo > 64 || !qrr_full_trace_pgd(call->pgd)) {
        return;
    }
    state = qrr_full_path_state_for_task(
        call->pgd, qrr_full_cpu_thread(cpu, call->pgd), false);
    if (!state || !state->process_token) {
        return;
    }
    if (!qrr_full_read_target_u32(
            cpu, call->info_ptr + QRR_FULL_MIPS_SIGINFO_ERRNO_OFFSET,
            &info_errno) ||
        !qrr_full_read_target_u32(
            cpu, call->info_ptr + QRR_FULL_MIPS_SIGINFO_CODE_OFFSET,
            &info_code) ||
        !qrr_full_read_target_u32(
            cpu, call->info_ptr + QRR_FULL_MIPS_SIGINFO_UNION_OFFSET,
            &info_word0) ||
        !qrr_full_read_target_u32(
            cpu, call->info_ptr + QRR_FULL_MIPS_SIGINFO_UNION_OFFSET + 4,
            &info_word1) ||
        !qrr_full_read_target_u32(
            cpu, call->info_ptr + QRR_FULL_MIPS_SIGINFO_UNION_OFFSET + 8,
            &info_word2) ||
        !qrr_full_read_target_u32(
            cpu, call->regs_ptr + QRR_FULL_MIPS_PT_REGS_CAUSE_OFFSET,
            &interrupted_cause) ||
        !qrr_full_read_target_u32(
            cpu, call->regs_ptr + QRR_FULL_MIPS_PT_REGS_EPC_OFFSET,
            &interrupted_pc) ||
        !qrr_full_read_target_u32(
            cpu, call->regs_ptr + QRR_FULL_MIPS_PT_REGS_SP_OFFSET,
            &interrupted_sp)) {
        fprintf(stderr,
                "qrr-full: cannot read delivered signal state pgd="
                TARGET_FMT_lx " signo=%d info=" TARGET_FMT_lx
                " regs=" TARGET_FMT_lx "\n",
                call->pgd, signo, call->info_ptr, call->regs_ptr);
        exit(2);
    }
    delay_slot = (interrupted_cause & QRR_FULL_MIPS_CAUSE_BD) != 0;
    if (delay_slot && interrupted_pc > UINT32_MAX - 4) {
        fprintf(stderr,
                "qrr-full: delivered signal delay-slot PC overflow pgd="
                TARGET_FMT_lx " signo=%d epc=%08" PRIx32 "\n",
                call->pgd, signo, interrupted_pc);
        exit(2);
    }
    delivery_pc = interrupted_pc + (delay_slot ? 4 : 0);
    info_pid = info_word0;
    info_uid = info_word1;
    info_status = info_word2;
    info_value = info_word2;
    fault_addr = info_word0;
    /* MIPS SIGIO uses the first two union words for si_band and si_fd. */
    if (signo == QRR_FULL_MIPS_SIGIO) {
        info_status = info_word0;
        info_value = info_word1;
    }
    pending = qrr_full_pending_find_task(call->pgd, state->task);
    if (pending) {
        anchor_kind = "syscall";
        key = pending->key;
        syscall_sequence = pending->sequence;
        syscall_nr = pending->syscall_nr;
        path_hash = pending->path_hash;
        dep_hash = pending->dep_hash;
    } else {
        qrr_full_current_signal_context(state, &path_hash, &dep_hash);
        syscall_sequence = state->syscall_seq;
        if (state->have_interrupted_user_edge &&
            state->interrupted_next_pc != delivery_pc) {
            fprintf(stderr,
                    "qrr-full: delivered user signal contradicts saved"
                    " interrupted-TB anchor pgd=" TARGET_FMT_lx
                    " signo=%d delivery_pc=%08" PRIx32
                    " have_interrupt=%d interrupt_next=" TARGET_FMT_lx
                    "\n",
                    call->pgd, signo, delivery_pc,
                    state->have_interrupted_user_edge,
                    state->interrupted_next_pc);
            exit(2);
        }
        /*
         * A signal can be selected either while returning from an interrupted
         * user TB or at a kernel-to-user resume boundary (most commonly just
         * after a completed syscall).  The latter has no interrupted TB to
         * recover: the exact execution edge is the last committed user
         * instruction to the PC supplied by the kernel in pt_regs.  Both
         * cases use the next occurrence of that exact semantic edge in this
         * syscall interval; no signal number, EINTR result, or adjacent
         * syscall is inferred.
         */
        edge_from_pc = state->have_interrupted_user_edge ?
            state->interrupted_edge_from_pc :
            (state->have_previous_user_edge_pc ?
             state->previous_user_edge_pc : 0);
        edge_to_pc = delivery_pc;
        /* Count this semantic edge, not all QEMU TBs in the interval.  QEMU
         * 2.10 system mode and QEMU 8.2 user mode may split the same linear
         * instruction range into different TBs.  The replay side therefore
         * creates a selective split at delivery_pc and counts the exact
         * edge_from_pc -> delivery_pc occurrence. */
        edge_occurrence = qrr_full_user_edge_next_occurrence(
            call->pgd, state->task, edge_from_pc, delivery_pc);
        state->have_interrupted_user_edge = false;
    }
    state->signal_seq++;
    fprintf(qrr_full_signal_fp,
            "%016" PRIx64 "\t%" PRIu64 "\t%s\t%016" PRIx64
            "\t%" PRIu64 "\t%d\t%016" PRIx64 "\t%016" PRIx64
            "\t%016" PRIx64 "\t%016" PRIx64 "\t%" PRIu64
            "\t%016" PRIx64 "\t%016" PRIx64 "\t%016" PRIx64
            "\t%d\t%d\t%" PRId32 "\t%" PRId32 "\t%" PRIu32
            "\t%" PRIu32 "\t%" PRId32 "\t%016" PRIx64
            "\t%016" PRIx64 "\n",
            state->process_token, state->signal_seq, anchor_kind, key,
            syscall_sequence, syscall_nr, path_hash, dep_hash,
            (uint64_t)edge_from_pc, (uint64_t)edge_to_pc, edge_occurrence,
            (uint64_t)delivery_pc, (uint64_t)interrupted_pc,
            (uint64_t)interrupted_sp, delay_slot, signo,
            (int32_t)info_code, (int32_t)info_errno, info_pid, info_uid,
            (int32_t)info_status, (uint64_t)info_value,
            (uint64_t)fault_addr);
    if (fflush(qrr_full_signal_fp) != 0) {
        fprintf(stderr, "qrr-full: cannot flush signal event: %s\n",
                strerror(errno));
        exit(2);
    }
    if (!pending) {
        qrr_full_user_precision_add(
            call->pgd, state->task, edge_from_pc, edge_to_pc, delay_slot,
            state->syscall_seq,
            qrr_full_user_edge_current_occurrence(
                call->pgd, state->task, edge_from_pc, edge_to_pc));
    }
    fprintf(stderr,
            "qrr-full: signal process=%016" PRIx64 " event=%" PRIu64
            " signo=%d anchor=%s syscall_sequence=%" PRIu64
            " edge=%08" PRIx64 "->%08" PRIx64 "#%" PRIu64
            " delivery_pc=%08" PRIx32 " interrupted_pc=%08" PRIx32
            " interrupted_sp=%08" PRIx32 " delay_slot=%d"
            "\n",
            state->process_token, state->signal_seq, signo, anchor_kind,
            syscall_sequence, (uint64_t)edge_from_pc,
            (uint64_t)edge_to_pc, edge_occurrence,
            delivery_pc, interrupted_pc, interrupted_sp, delay_slot);
#else
    (void)cpu;
    (void)call;
    (void)signo;
#endif
}

static void qrr_full_note_signal_delivery(CPUState *cpu, target_ulong pc)
{
#ifdef TARGET_MIPS
    CPUArchState *env;
    QrrFullSignalCall *call;
    QrrFullSignalCall *next;
    target_ulong pgd;

    if (!qrr_full_signal_fp || !qrr_full_get_signal_to_deliver) {
        return;
    }
    env = cpu->env_ptr;
    if (pc == qrr_full_get_signal_to_deliver) {
        pgd = qrr_full_current_pgd(cpu);
        if (qrr_full_trace_pgd(pgd)) {
            call = calloc(1, sizeof(*call));
            if (!call) {
                fprintf(stderr, "qrr-full: cannot allocate signal call\n");
                exit(2);
            }
            call->cpu = cpu;
            call->pgd = pgd;
            call->info_ptr = env->active_tc.gpr[4];
            call->regs_ptr = env->active_tc.gpr[6];
            call->return_pc = env->active_tc.gpr[31];
            call->next = qrr_full_signal_calls;
            qrr_full_signal_calls = call;
        }
        return;
    }
    for (call = qrr_full_signal_calls; call; call = next) {
        next = call->next;
        if (call->cpu == cpu && call->return_pc == pc) {
            pgd = qrr_full_current_pgd(cpu);
            if (pgd == call->pgd && (target_long)env->active_tc.gpr[2] > 0) {
                qrr_full_record_signal_delivery(
                    cpu, call, (int)(target_long)env->active_tc.gpr[2]);
            }
            qrr_full_signal_call_remove(call);
            return;
        }
    }
#else
    (void)cpu;
    (void)pc;
#endif
}

static QrrFullPending *qrr_full_pending_take(target_ulong pgd,
                                             target_ulong curr_pc,
                                             target_ulong curr_stack,
                                             target_ulong task)
{
    QrrFullPending *last = NULL;
    QrrFullPending *curr = qrr_full_pending_head;

    while (curr) {
        bool match;

#ifdef TARGET_MIPS
        match = curr->pgd == pgd && (!task || curr->task == task) &&
                curr->entry_pc + 4 == curr_pc &&
                curr->stack == curr_stack;
#elif defined(TARGET_ARM)
        match = curr->pgd == pgd && (!task || curr->task == task) &&
                curr->entry_pc == curr_pc &&
                curr->stack == curr_stack;
#else
        match = false;
#endif
        if (match) {
            if (last) {
                last->next = curr->next;
            } else {
                qrr_full_pending_head = curr->next;
            }
            curr->next = NULL;
            return curr;
        }
        last = curr;
        curr = curr->next;
    }
    return NULL;
}

/* A successful sigreturn resumes the interrupted PC, not syscall_pc + 4.
 * It is nevertheless a completed syscall and must occupy its v13 sequence.
 * Use the same internal sentinel returned by qemu-user's real sigreturn
 * implementation so the state transition can be executed and audited. */
static QrrFullPending *qrr_full_pending_take_signal_return(target_ulong pgd,
                                                           target_ulong task)
{
    QrrFullPending *last = NULL;
    QrrFullPending *curr = qrr_full_pending_head;

    while (curr) {
        if (curr->pgd == pgd && (!task || curr->task == task) &&
            qrr_full_is_signal_return_syscall(curr->syscall_nr)) {
            if (last) {
                last->next = curr->next;
            } else {
                qrr_full_pending_head = curr->next;
            }
            curr->next = NULL;
            return curr;
        }
        last = curr;
        curr = curr->next;
    }
    return NULL;
}

static bool qrr_full_exec_returned(const QrrFullExecPending *pending,
                                   target_ulong pgd, target_ulong curr_pc,
                                   target_ulong curr_stack)
{
    return pending->pgd == pgd &&
           qrr_full_same_syscall_return(pending->entry_pc, pending->stack,
                                        curr_pc, curr_stack);
}

static void qrr_full_discard_returned_exec(CPUState *cpu, target_ulong pgd,
                                           target_ulong curr_pc,
                                           target_ulong curr_stack)
{
    QrrFullExecPending *pending;

    for (pending = qrr_full_exec_pending; pending; pending = pending->next) {
        if (pending->cpu == cpu &&
            qrr_full_exec_returned(pending, pgd, curr_pc, curr_stack)) {
            fprintf(stderr,
                    "qrr-full: target exec syscall returned without"
                    " proc_exec_connector source_pgd=" TARGET_FMT_lx
                    " entry_pc=" TARGET_FMT_lx "\n",
                    pending->pgd, pending->entry_pc);
            qrr_full_remove_exec_pending(pending);
            return;
        }
    }
}

static void qrr_full_syscall_entry(CPUState *cpu)
{
    QrrFullPathState *state;
    QrrFullPending *pending;
    QrrFullPending *active_anchor;
    target_ulong args[6];
    target_ulong pgd;
    target_ulong pc;
    target_ulong stack;
    target_ulong task;
    int syscall_nr;
    uint64_t key;
    uint64_t path_hash;
    uint64_t dep_hash;
    uint64_t sequence;
    bool exec_target_match = false;

    if (!qrr_full_init()) {
        return;
    }
    qrr_full_syscall_state(cpu, &syscall_nr, args, &pc, &stack);
    if (!qrr_full_user_pc(pc)) {
        return;
    }
    pgd = qrr_full_current_pgd(cpu);
    /* At the architectural syscall exception boundary MIPS still exposes
     * the userspace SP, so deriving thread_info from gpr[29] yields no task.
     * The last kernel TB before this userspace run already resolved current
     * exactly and cached it for this CPU+PGD; userspace cannot switch tasks
     * without returning through the kernel path that refreshes this cache. */
    task = qrr_full_cpu_thread(cpu, pgd);
    /* A delivered signal can return to the interrupted syscall instruction
     * and trap again while its original pending record is still live.  The
     * exact entry PC/SP identifies that suspended logical syscall; handler
     * syscalls have their own entry anchor and continue through the normal
     * path below. */
    if (qrr_full_trace_pgd(pgd) &&
        qrr_full_recordable_syscall(syscall_nr)) {
        active_anchor = qrr_full_pending_find_entry_anchor(
            pgd, task, pc, stack);
        if (active_anchor) {
            if (!qrr_full_pending_same_attempt(active_anchor, syscall_nr,
                                               args)) {
                fprintf(stderr,
                        "qrr-full: conflicting syscall re-entry"
                        " process=%016" PRIx64
                        " logical=%" PRIu64 " attempt=%" PRIu64
                        " pgd=" TARGET_FMT_lx " pc=" TARGET_FMT_lx
                        " sp=" TARGET_FMT_lx " expected_nr=%d actual_nr=%d\n",
                        active_anchor->process_token,
                        active_anchor->logical_syscall_id,
                        active_anchor->attempt_count + 1, pgd, pc, stack,
                        active_anchor->syscall_nr, syscall_nr);
                fflush(NULL);
                exit(2);
            }
            if (active_anchor->attempt_count == UINT64_MAX) {
                fprintf(stderr,
                        "qrr-full: syscall attempt counter overflow"
                        " process=%016" PRIx64 " logical=%" PRIu64 "\n",
                        active_anchor->process_token,
                        active_anchor->logical_syscall_id);
                fflush(NULL);
                exit(2);
            }
            active_anchor->attempt_count++;
            fprintf(stderr,
                    "qrr-full: logical syscall restart"
                    " process=%016" PRIx64 " logical=%" PRIu64
                    " sequence=%" PRIu64 " attempt=%" PRIu64
                    " syscall=%d pc=" TARGET_FMT_lx " sp=" TARGET_FMT_lx
                    "\n",
                    active_anchor->process_token,
                    active_anchor->logical_syscall_id,
                    active_anchor->sequence, active_anchor->attempt_count,
                    active_anchor->syscall_nr, pc, stack);
            return;
        }
    }
    /* Exec launch metadata is observed at the syscall boundary so argv stays
     * exact.  It does not bind a process or enter the QRR syscall table; only
     * the successful proc_exec_connector hook may select the target PGD. */
    qrr_full_exec_event(cpu, pgd, pc, stack, syscall_nr, args,
                        &exec_target_match);
    if (!qrr_full_trace_pgd(pgd)) {
        return;
    }
    state = qrr_full_path_state_for_task(pgd, task, true);
    if (!state) {
        return;
    }
    if (qrr_full_thread_context && (!task || !state->thread_token)) {
        fprintf(stderr,
                "qrr-full: exact thread context unavailable at syscall"
                " pgd=" TARGET_FMT_lx " task=" TARGET_FMT_lx
                " syscall=%d pc=" TARGET_FMT_lx "\n",
                pgd, task, syscall_nr, pc);
        exit(2);
    }
    if (!qrr_full_recordable_syscall(syscall_nr)) {
        return;
    }
    qrr_full_advance_context(state, syscall_nr, pc, &key, &path_hash,
                             &dep_hash, &sequence);

    pending = malloc(sizeof(*pending));
    if (!pending) {
        return;
    }
    memset(pending, 0, sizeof(*pending));
    pending->pgd = pgd;
    pending->task = task;
    pending->thread_token = state->thread_token;
    pending->entry_pc = pc;
    pending->stack = stack;
    pending->syscall_nr = syscall_nr;
    pending->key = key;
    pending->path_hash = path_hash;
    pending->dep_hash = dep_hash;
    pending->sequence = sequence;
    pending->logical_syscall_id = sequence;
    pending->attempt_count = 1;
    pending->process_token = state->process_token;
    memcpy(pending->args, args, sizeof(pending->args));
    /* Record logical syscall *entry* order independently of the result
     * table.  A signal handler can complete later-sequence syscalls before
     * the interrupted syscall returns, so result-row order is not a valid
     * process schedule.  Restart attempts return above and therefore never
     * create a second schedule event. */
    qrr_full_schedule_entry(pending);
    /* A process child is bound only after its exact fork return is observed.
     * Its derived token keeps parent and child QRR streams isolated. */
    if (qrr_full_follow_fork_descendants &&
        qrr_full_is_process_fork_syscall(syscall_nr, args)) {
        qrr_full_capture_target_fork(cpu, pgd, pc, stack);
    }
    {
        int path_arg = qrr_full_open_path_arg(syscall_nr);

        if (path_arg >= 0) {
            pending->open_path = qrr_full_read_guest_path(
                cpu, args[path_arg]);
        }
    }
    if (qrr_full_is_exit_syscall(syscall_nr)) {
        qrr_full_write_result_row(pending, 0, 0, "-");
        qrr_full_schedule_commit(pending);
        qrr_full_event(pending, 0, 0, 0, 0, "record", "no_return_exit");
        /* A descendant may remain live after this member exits.  Keep the
         * family active so its separately bound PGD and process token can
         * continue collection. */
        if (qrr_full_follow_fork_descendants) {
            fprintf(stderr,
                    "qrr-full: descendant-aware target exit"
                    " pgd=" TARGET_FMT_lx " process=%016" PRIx64 "\n",
                    pgd, pending->process_token);
            /* The family remains active, but this address-space identity is
             * dead.  Remove it now so a later Linux PGD reuse cannot inherit
             * stale path/pending state or consume the old process token. */
            qrr_full_unbind_process_token(pending->process_token,
                                          "exit-syscall");
            free(pending->open_path);
            free(pending);
            return;
        }
        fprintf(stderr,
                "qrr-full: selected target exited pgd=" TARGET_FMT_lx
                " process=%016" PRIx64 "; collection stopped\n",
                pgd, pending->process_token);
        qrr_full_target_active = false;
        qrr_full_unbind_process_token(pending->process_token,
                                      "exit-syscall");
        free(pending->open_path);
        free(pending);
        return;
    }
    qrr_full_pending_insert(pending);
}

static void qrr_full_syscall_return(CPUState *cpu, target_ulong return_pc,
                                    target_ulong stack)
{
    QrrFullPending *pending;
    target_ulong pgd;
    target_ulong task;
    int64_t ret;
    int out_arg = 0;
    size_t output_bytes = 0;
    char *hex = NULL;
    const char *skip_reason = NULL;
    bool fatal_effect_capture = false;

    if (!qrr_full_init() || !qrr_full_user_pc(return_pc)) {
        return;
    }
    pgd = qrr_full_current_pgd(cpu);
    task = qrr_full_cpu_thread(cpu, pgd);
    qrr_full_discard_returned_exec(cpu, pgd, return_pc, stack);
    if (!qrr_full_trace_pgd(pgd)) {
        return;
    }
    if (qrr_full_thread_context && !task) {
        fprintf(stderr,
                "qrr-full: exact thread context unavailable at syscall"
                " return pgd=" TARGET_FMT_lx " pc=" TARGET_FMT_lx "\n",
                pgd, return_pc);
        exit(2);
    }
    ret = qrr_full_syscall_ret(cpu);
    if (qrr_full_follow_fork_descendants) {
        qrr_full_discard_failed_target_fork(cpu, pgd, return_pc, stack, ret);
    }
    pending = qrr_full_pending_take(pgd, return_pc, stack, task);
    if (!pending) {
        pending = qrr_full_pending_take_signal_return(pgd, task);
        if (pending) {
            ret = -QRR_FULL_QEMU_ESIGRETURN;
        }
    }
    if (!pending) {
        return;
    }
    if (!pending->open_path) {
        int path_arg = qrr_full_open_path_arg(pending->syscall_nr);

        if (path_arg >= 0) {
            pending->open_path = qrr_full_read_guest_path(
                cpu, pending->args[path_arg]);
        }
    }
    qrr_full_update_fd_paths(pending, ret);

    if (ret >= 0) {
        size_t direct_length = 0;
        size_t semctl_output_length = 0;
        bool semctl_output = qrr_full_is_semctl_output(
            pending, &semctl_output_length);
        bool semaphore_state = qrr_full_semaphore_state_required(pending);

        if (semaphore_state &&
            !qrr_full_capture_semaphore_state(cpu, pending,
                                              &skip_reason)) {
            fatal_effect_capture = true;
        } else if (semctl_output || semaphore_state) {
            out_arg = QRR_FULL_RESULT_OUT_ARG_BUNDLE;
            hex = qrr_full_encode_semctl_bundle(
                cpu, pending, semctl_output ? semctl_output_length : 0,
                &output_bytes);
            if (!hex) {
                skip_reason = "semaphore-bundle-capture-failed";
                fatal_effect_capture = true;
            }
        } else if (qrr_full_is_shmat_syscall(pending->syscall_nr,
                                      pending->args)) {
            out_arg = QRR_FULL_RESULT_OUT_ARG_SHMAT;
            hex = qrr_full_encode_shmat(cpu, pending, ret, &output_bytes,
                                        &skip_reason);
            fatal_effect_capture = !hex;
        } else if (qrr_full_is_mremap_syscall(pending->syscall_nr)) {
            out_arg = QRR_FULL_RESULT_OUT_ARG_BUNDLE;
            hex = qrr_full_record_mremap_effect(
                cpu, pending, ret, &output_bytes, &skip_reason);
            if (!hex) {
                if (!skip_reason) {
                    skip_reason = "mremap-effect-capture-failed";
                }
                fatal_effect_capture = true;
            }
        } else if (qrr_full_is_mmap_syscall(pending->syscall_nr)) {
            const char *mmap_failure = NULL;

            /* The syscall table carries only the return value.  Mapping
             * metadata and demand-page snapshots live in the independent
             * mmap-v1 event table. */
            if (!qrr_full_record_mmap_mapping(cpu, pending, ret,
                                              &mmap_failure)) {
                skip_reason = mmap_failure ? mmap_failure :
                              "mmap_event_capture_failed";
                fatal_effect_capture = true;
            }
        } else if (ret >= 0 && qrr_full_is_secondary_return_syscall(
                                  pending->syscall_nr)) {
            out_arg = QRR_FULL_RESULT_OUT_ARG_BUNDLE;
            hex = qrr_full_encode_secondary_return_bundle(
                cpu, &output_bytes);
            if (!hex) {
                skip_reason = "secondary-return-capture-failed";
                fatal_effect_capture = true;
            }
        } else if (qrr_full_is_wait_syscall(pending->syscall_nr) &&
                   ret > 0 &&
                   (pending->args[1] ||
                    (qrr_full_is_wait4_syscall(pending->syscall_nr) &&
                     pending->args[3]))) {
            out_arg = QRR_FULL_RESULT_OUT_ARG_BUNDLE;
            hex = qrr_full_encode_wait_bundle(cpu, pending->syscall_nr,
                                              pending->args, ret,
                                              &output_bytes);
            if (!hex) {
                skip_reason = "wait-output-capture-failed";
                fatal_effect_capture = true;
            }
        } else if (qrr_full_is_select_syscall(pending->syscall_nr)) {
            out_arg = QRR_FULL_RESULT_OUT_ARG_BUNDLE;
            hex = qrr_full_encode_select_bundle(cpu, pending->syscall_nr,
                                                pending->args,
                                                &output_bytes);
            if (!hex) {
                skip_reason = "output_capture_failed";
            }
        } else if (qrr_full_is_socket_output_syscall(
                       pending->syscall_nr)) {
            out_arg = QRR_FULL_RESULT_OUT_ARG_BUNDLE;
            hex = qrr_full_encode_socket_bundle(cpu, pending->syscall_nr,
                                                pending->args, ret,
                                                &output_bytes);
            if (!hex) {
                skip_reason = "output_capture_failed";
            }
        } else if (qrr_full_is_recvmsg_syscall(pending->syscall_nr)) {
            out_arg = QRR_FULL_RESULT_OUT_ARG_BUNDLE;
            hex = qrr_full_encode_recvmsg_bundle(cpu, pending->args[1], ret,
                                                 &output_bytes);
            if (!hex) {
                skip_reason = "output_capture_failed";
            }
        } else if (qrr_full_direct_output_location(pending->syscall_nr,
                                                   pending->args, ret,
                                                   &out_arg,
                                                   &direct_length)) {
            target_ulong output_addr =
                qrr_full_select_arg(pending->args, out_arg);

            hex = qrr_full_encode_guest_hex(cpu, output_addr, direct_length);
            if (!hex) {
                skip_reason = "output_capture_failed";
                /* Reaching this branch means the syscall has a known,
                 * target-ABI output object.  A strict all-syscall table may
                 * never silently omit that memory effect. */
                fatal_effect_capture = true;
            } else {
                output_bytes = direct_length;
            }
        } else if (qrr_full_output_required(pending->syscall_nr,
                                            pending->args, ret)) {
            skip_reason = "unsupported_output";
        }
    }
    if (!hex && !skip_reason) {
        hex = strdup("-");
    }
    if (skip_reason) {
        qrr_full_event(pending, return_pc, ret, out_arg, output_bytes,
                       "skip", skip_reason);
        if (fatal_effect_capture) {
            fprintf(stderr,
                    "qrr-full: required memory effect capture failed"
                    " process=%016" PRIx64 " seq=%" PRIu64
                    " reason=%s\n",
                    pending->process_token, pending->sequence, skip_reason);
            fflush(NULL);
            exit(2);
        }
        free(pending->open_path);
        free(pending->semaphore_values);
        free(pending);
        return;
    }
    qrr_full_write_result_row(pending, ret, out_arg, hex);
    qrr_full_schedule_commit(pending);
    qrr_full_event(pending, return_pc, ret, out_arg, output_bytes,
                   "record", "-");
    free(hex);
    free(pending->open_path);
    free(pending->semaphore_values);
    free(pending);
}

#endif
