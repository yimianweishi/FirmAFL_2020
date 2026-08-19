/*
Copyright (C) <2012> <Syracuse System Security (Sycure) Lab>

DECAF is based on QEMU, a whole-system emulator. You can redistribute
and modify it under the terms of the GNU LGPL, version 2.1 or later,
but it is made available WITHOUT ANY WARRANTY. See the top-level
README file for more details.

For more information about DECAF and other softwares, see our
web site at:
http://sycurelab.ecs.syr.edu/

If you have any questions about DECAF,please post it on
http://code.google.com/p/decaf-platform/
*/
#include "qemu/osdep.h" // zyw
#include "cpu.h" // zyw

#include <assert.h>
#include <sys/queue.h>
#include "sysemu/sysemu.h" // zyw
#include "qemu/timer.h" // zyw
#include "hw/hw.h"
#include "hw/isa/isa.h"	// zyw	/* for register_ioport_write */
#include "sysemu/blockdev.h" // zyw
#include "shared/DECAF_main.h" // AWH
#include "shared/DECAF_callback.h"
#include "shared/hookapi.h" // AWH
#include "DECAF_target.h"
#include "shared/linux_vmi_new.h"

static bool mips_kseg_to_phys(target_ulong address, gpa_t *physical)
{
  if (address >= 0x80000000 && address < 0xa0000000) {
    *physical = address - 0x80000000;
    return true;
  }
  if (address >= 0xa0000000 && address < 0xc0000000) {
    *physical = address - 0xa0000000;
    return true;
  }
  return false;
}

DECAF_GVATranslationStatus DECAF_get_phys_addr_with_pgd_status(
    CPUState *env, gpa_t pgd, gva_t addr, gpa_t *physical)
{
  CPUArchState *env_ptr;
  target_ulong pgd_entry;
  target_ulong pte;
  target_ulong entrylo;
  gpa_t pgd_phys;
  gpa_t pte_table_phys;
  gpa_t phys_page;
  int softshift;

  if (env == NULL) {
#ifdef DECAF_NO_FAIL_SAFE
    return DECAF_GVA_WALK_ERROR;
#else
    env = current_cpu ? current_cpu : first_cpu;
#endif
  }
  if (env == NULL) {
    return DECAF_GVA_WALK_ERROR;
  }

  /* KSEG0 and KSEG1 are direct mapped and never require a TLB entry. */
  if (mips_kseg_to_phys(addr, &phys_page)) {
    *physical = phys_page;
    return DECAF_GVA_TRANSLATED;
  }

  if (mips_kseg_to_phys(pgd, &pgd_phys)) {
    pgd = pgd_phys;
  }
  if (pgd == 0 || pgd == INV_ADDR) {
    return DECAF_GVA_WALK_ERROR;
  }

  /* Linux/MIPS32 uses a two-level table: 10 PGD and 10 PTE index bits. */
  pgd_entry = ldl_phys(env->as, pgd + (((target_ulong)addr >> 22) * 4));
  if (pgd_entry == 0) {
    return DECAF_GVA_NOT_PRESENT;
  }
  if (!mips_kseg_to_phys(pgd_entry, &pte_table_phys)) {
    return DECAF_GVA_WALK_ERROR;
  }

  pte = ldl_phys(env->as, pte_table_phys +
                 ((((target_ulong)addr >> 12) & 0x3ff) * 4));
  /* Bit zero is Linux _PAGE_PRESENT; a nonzero swap PTE is not mapped RAM. */
  if (!(pte & 1)) {
    return DECAF_GVA_NOT_PRESENT;
  }

  /* The kernel refill handler defines how its software PTE becomes EntryLo. */
  softshift = mips_get_pte_softshift(env);
  if (softshift <= 0 || softshift > 25) {
    return DECAF_GVA_WALK_ERROR;
  }
  entrylo = pte >> softshift;
  phys_page = ((gpa_t)((entrylo >> 6) & 0x00ffffff)) << TARGET_PAGE_BITS;
  env_ptr = (CPUArchState *)env->env_ptr;
  if ((phys_page & ~env_ptr->PAMask) != 0) {
    return DECAF_GVA_WALK_ERROR;
  }
  *physical = phys_page | ((target_ulong)addr & ~TARGET_PAGE_MASK);
  return DECAF_GVA_TRANSLATED;
}

gpa_t DECAF_get_phys_addr_with_pgd(CPUState* env, gpa_t pgd, gva_t addr)
{
  gpa_t physical;

  if (DECAF_get_phys_addr_with_pgd_status(env, pgd, addr, &physical) !=
      DECAF_GVA_TRANSLATED) {
    return INV_ADDR;
  }
  return physical;
}


// FIXME: assume only one processor
gpa_t DECAF_getPGD(CPUState* env)
{
  return mips_get_cur_pgd(env);
}
