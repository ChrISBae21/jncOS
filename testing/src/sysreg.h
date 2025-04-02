#ifndef _SYSREGS_H
#define _SYSREGS_H

// *********************************************************************************
// SCTLR_EL1, System Control Register (EL1), Page 2654 of AArch64-Reference-Manual
// *********************************************************************************

#define SCTLR_RESERVED (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11) /* reserved bits, must be set */
#define SCTLR_EE_LITTLE_ENDIAN (0 << 25)                             /* little endian for EL1 explicit data access */
#define SCTLR_EOE_LITTLE_ENDIAN (0 << 24)                            /* little endian for EL0 explicit data access */
#define SCTLR_I_CACHE_DISABLED (0 << 12)                             /* disable instruction cache */
#define SCTLR_D_CACHE_DISABLED (0 << 2)                              /* disable data cache */
#define SCTLR_MMU_DISABLED (0 << 0)                                  /* disable MMU */
#define SCTLR_MMU_ENABLED (1 << 0)                                   /* enable MMU */

#define SCTLR_VALUE_MMU_DISABLED (SCTLR_RESERVED | SCTLR_EE_LITTLE_ENDIAN | SCTLR_I_CACHE_DISABLED | SCTLR_D_CACHE_DISABLED | SCTLR_MMU_DISABLED)

// ******************************************************************************************
// HCR_EL2, Hypervisor Configuration Register (EL2), Page 2487 of AArch64-Reference-Manual
// ******************************************************************************************

#define HCR_RW (1 << 31) /* executation state for EL1 AArch64 */
#define HCR_VALUE HCR_RW

// *************************************************************************************
// SPSR_EL2, Saved Program Status Register (EL3) Page 389 of AArch64-Reference-Manual
// *************************************************************************************

#define SPSR_MASK_ALL (7 << 6) /* disables interrupts for EL1 */
#define SPSR_EL1h (5 << 0)     /* artifically sets the "taken" exception level to return to */
#define SPSR_VALUE (SPSR_MASK_ALL | SPSR_EL1h)

#endif