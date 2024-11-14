/* FEATURE.H    (c) Copyright Jan Jaeger, 2000-2009                  */
/*              Architecture-dependent macro definitions             */

// $Id: feature.h 5531 2009-12-11 18:23:29Z bernard $

#ifdef HAVE_CONFIG_H
  #include <config.h> // Hercules build configuration options/settings
#endif

#if !defined(FEATCHK_CHECK_DONE)
  #include  "featall.h"
  #include  "feat370.h"
  #include  "feat390.h"
  #include  "feat900.h"
  #define   FEATCHK_CHECK_ALL
  #include  "featchk.h"
  #undef    FEATCHK_CHECK_ALL
  #define   FEATCHK_CHECK_DONE
#endif /*!defined(FEATCHK_CHECK_DONE)*/

#undef __GEN_ARCH
#if defined(_GEN_ARCH)
 #define __GEN_ARCH _GEN_ARCH
#else
 #define __GEN_ARCH _ARCHMODE1
#endif

#include  "featall.h"

#if   __GEN_ARCH == 370
 #include "feat370.h"
#elif     __GEN_ARCH == 390
 #include "feat390.h"
#elif     __GEN_ARCH == 900
 #include "feat900.h"
#else
 #error Unable to determine Architecture Mode
#endif

#include  "featchk.h"

#undef ARCH_MODE
#undef APPLY_PREFIXING
#undef AMASK
#undef ADDRESS_MAXWRAP
#undef ADDRESS_MAXWRAP_E
#undef ASF_ENABLED
#undef ASTE_AS_DESIGNATOR
#undef ASTE_LT_DESIGNATOR
#undef SAEVENT_BIT
#undef SSEVENT_BIT
#undef SSGROUP_BIT
#undef LSED_UET_HDR
#undef LSED_UET_TLR
#undef LSED_UET_BAKR
#undef LSED_UET_PC
#undef CR12_BRTRACE
#undef CR12_TRACEEA
#undef CHM_GPR2_RESV
#undef DEF_INST
#undef ARCH_DEP
#undef PSA
#undef PSA_SIZE
#undef IA
#undef PX
#undef CR
#undef GR
#undef GR_A
#undef SET_GR_A
#undef MONCODE
#undef TEA
#undef DXC
#undef ET
#undef PX_MASK
#undef RSTOLD
#undef RSTNEW
#undef RADR
#undef F_RADR
#undef VADR
#undef VADR_L
#undef F_VADR
#undef GREG
#undef F_GREG
#undef CREG
#undef F_CREG
#undef AREG
#undef F_AREG
#undef STORE_W
#undef FETCH_W
#undef AIV
#undef AIE
#undef VIE
#undef SIEBK
#undef ZPB
#undef TLB_REAL_ASD
#undef TLB_ASD
#undef TLB_VADDR
#undef TLB_PTE
#undef TLB_PAGEMASK
#undef TLB_BYTEMASK
#undef TLB_PAGESHIFT
#undef TLBID_PAGEMASK
#undef TLBID_BYTEMASK
#undef ASD_PRIVATE
#undef PER_SB

#define ARCH_MODE   ARCH_370

#define DEF_INST(_name) \
void (ATTR_REGPARM(2) s370_ ## _name) (BYTE inst[], REGS *regs)

#define ARCH_DEP(_name) \
s370_ ## _name

#define APPLY_PREFIXING(addr,pfx) \
    ( ((U32)(addr) & 0x7FFFF000) == 0 || ((U32)(addr) & 0x7FFFF000) == (pfx) \
      ? (U32)(addr) ^ (pfx) \
      : (addr) \
    )

#define AMASK   AMASK_L

#define ADDRESS_MAXWRAP(_register_context) \
    (AMASK24)

#define ADDRESS_MAXWRAP_E(_register_context) \
    (AMASK31)

#define ASF_ENABLED(_regs)  0 /* ASF is never enabled for S/370 */

#define ASTE_AS_DESIGNATOR(_aste) \
    ((_aste)[2])

#define ASTE_LT_DESIGNATOR(_aste) \
    ((_aste)[3])

#define SAEVENT_BIT STD_SAEVENT
#define SSEVENT_BIT STD_SSEVENT
#define SSGROUP_BIT STD_GROUP

#define PSA PSA_3XX
#define PSA_SIZE 4096
#define IA  IA_L
#define CR(_r)  CR_L(_r)
#define GR(_r)  GR_L(_r)
#define GR_A(_r, _regs) ((_regs)->GR_L((_r)))
#define SET_GR_A(_r, _regs,_v) ((_regs)->GR_L((_r))=(_v))
#define MONCODE MC_L
#define TEA EA_L
#define DXC     tea
#define ET  ET_L
#define PX_MASK 0x7FFFF000
#define RSTOLD  iplccw1
#define RSTNEW  iplpsw
#define RADR    U32
#define F_RADR  "%8.8"I32_FMT"X"
#define VADR    U32
#define VADR_L  VADR
#define F_VADR  "%8.8"I32_FMT"X"
#define GREG    U32
#define F_GREG  "%8.8"I32_FMT"X"
#define CREG    U32
#define F_CREG  "%8.8"I32_FMT"X"
#define AREG    U32
#define F_AREG  "%8.8"I32_FMT"X"
#define STORE_W STORE_FW
#define FETCH_W FETCH_FW
#define AIV     AIV_L
#define AIE     AIE_L
#define SIEBK                   SIE1BK
#define ZPB                     ZPB1
#define TLB_REAL_ASD  TLB_REAL_ASD_L
#define TLB_ASD(_n)   TLB_ASD_L(_n)
#define TLB_VADDR(_n) TLB_VADDR_L(_n)
#define TLB_PTE(_n)   TLB_PTE_L(_n)
#define TLB_PAGEMASK  0x00FFF800
#define TLB_BYTEMASK  0x000007FF
#define TLB_PAGESHIFT 11
#define TLBID_PAGEMASK  0x00E00000
#define TLBID_BYTEMASK  0x001FFFFF
#define ASD_PRIVATE   SEGTAB_370_CMN

#undef PAGEFRAME_PAGESIZE
#undef PAGEFRAME_PAGESHIFT
#undef PAGEFRAME_BYTEMASK
#undef PAGEFRAME_PAGEMASK
#undef MAXADDRESS
 #define PAGEFRAME_PAGESIZE 2048
 #define PAGEFRAME_PAGESHIFT    11
 #define PAGEFRAME_BYTEMASK 0x000007FF
 #define PAGEFRAME_PAGEMASK 0x7FFFF800
  #define MAXADDRESS             0x00FFFFFF


#undef ITIMER_UPDATE
#undef ITIMER_SYNC
#if defined(FEATURE_INTERVAL_TIMER)
 #define ITIMER_UPDATE(_addr, _len, _regs)       \
    do {                                         \
    if( ITIMER_ACCESS((_addr), (_len)) )     \
            ARCH_DEP(fetch_int_timer) ((_regs)); \
    } while(0) 
 #define ITIMER_SYNC(_addr, _len, _regs)         \
    do {                                         \
        if( ITIMER_ACCESS((_addr), (_len)) )     \
        ARCH_DEP(store_int_timer) ((_regs)); \
    } while (0)
#else
 #define ITIMER_UPDATE(_addr, _len, _regs)
 #define ITIMER_SYNC(_addr, _len, _regs)
#endif


 #define STORAGE_KEY_UNITSIZE 2048

 #undef STORAGE_KEY
 #undef STORAGE_KEY_PAGESHIFT
 #undef STORAGE_KEY_PAGESIZE
 #undef STORAGE_KEY_PAGEMASK
 #undef STORAGE_KEY_BYTEMASK
 #define STORAGE_KEY_PAGESHIFT  11
 #define STORAGE_KEY_PAGESIZE   2048
 #define STORAGE_KEY_PAGEMASK   0x7FFFF800
 #define STORAGE_KEY_BYTEMASK   0x000007FF

#define STORAGE_KEY(_addr, _pointer) \
   (_pointer)->storkeys[(_addr)>>STORAGE_KEY_PAGESHIFT]

 #define STORAGE_KEY1(_addr, _pointer) \
    (_pointer)->storkeys[((_addr)>>STORAGE_KEY_PAGESHIFT)&~1]
 #define STORAGE_KEY2(_addr, _pointer) \
    (_pointer)->storkeys[((_addr)>>STORAGE_KEY_PAGESHIFT)|1]

#define XSTORE_INCREMENT_SIZE   0x00100000
#define XSTORE_PAGESHIFT    12
#define XSTORE_PAGESIZE     4096
#undef   XSTORE_PAGEMASK
 #define XSTORE_PAGEMASK    0x7FFFF000


/* Macros for accelerated lookup */
#undef MADDR


 /*
  * Accelerated lookup
  */
#define MADDR(_addr, _arn, _regs, _acctype, _akey) \
 ( \
       ARCH_DEP(logical_to_main) ((_addr), (_arn), (_regs), (_acctype), (_akey)) \
 )

 #define PER_SB(_regs,_addr)

/* end of FEATURES.H */
