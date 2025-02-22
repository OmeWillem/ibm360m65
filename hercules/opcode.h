/* OPCODE.H     (c) Copyright Jan Jaeger, 2000-2009                  */
/*              Instruction decoding macros and prototypes           */

/* Interpretive Execution - (c) Copyright Jan Jaeger, 1999-2009      */
/* z/Architecture support - (c) Copyright Jan Jaeger, 1999-2009      */

// $Id: opcode.h 5573 2009-12-29 13:13:29Z bernard $

#ifndef _OPCODE_H
#define _OPCODE_H

#include "hercules.h"

#ifndef _CPU_C_
 #ifndef _HENGINE_DLL_
  #define CPU_DLL_IMPORT DLL_IMPORT
 #else   /* _HENGINE_DLL_ */
  #define CPU_DLL_IMPORT extern
 #endif  /* _HENGINE_DLL_ */
#else   /* _CPU_C_ */
 #define CPU_DLL_IMPORT DLL_EXPORT
#endif /* _CPU_C_ */

#ifndef _OPCODE_C_
 #ifndef _HENGINE_DLL_
  #define OPC_DLL_IMPORT DLL_IMPORT
 #else   /* _HENGINE_DLL_ */
  #define OPC_DLL_IMPORT extern
 #endif  /* _HENGINE_DLL_ */
#else   /* _OPCODE_C_ */
 #define OPC_DLL_IMPORT DLL_EXPORT
#endif /* _OPCODE_C_ */

 #define _GEN370(_name) &s370_ ## _name,
 #define _GEN390(_name)
 #define _GEN900(_name)


#define GENx___x___x___ \
    { \
    _GEN370(operation_exception) \
        (void*)&disasm_none, \
        (void*)&"?????" "\0" "?" \
    }

#define GENx370x___x___(_name,_format,_mnemonic) \
    { \
    _GEN370(_name) \
        (void*)&disasm_ ## _format, \
        (void*)& _mnemonic "\0" #_name \
    }

#define GENx___x390x___(_name,_format,_mnemonic) \
    { \
    _GEN370(operation_exception) \
        (void*)&disasm_ ## _format, \
        (void*)& _mnemonic "\0" #_name \
    }

#define GENx370x390x___(_name,_format,_mnemonic) \
    { \
    _GEN370(_name) \
        (void*)&disasm_ ## _format, \
        (void*)& _mnemonic "\0" #_name \
    }

#define GENx___x___x900(_name,_format,_mnemonic) \
    { \
    _GEN370(operation_exception) \
        (void*)&disasm_ ## _format, \
        (void*)& _mnemonic "\0" #_name \
    }

#define GENx370x___x900(_name,_format,_mnemonic) \
    { \
    _GEN370(_name) \
        (void*)&disasm_ ## _format, \
        (void*)& _mnemonic "\0" #_name \
    }

#define GENx___x390x900(_name,_format,_mnemonic) \
    { \
    _GEN370(operation_exception) \
        (void*)&disasm_ ## _format, \
        (void*)& _mnemonic "\0" #_name \
    }

#define GENx370x390x900(_name,_format,_mnemonic) \
    { \
    _GEN370(_name) \
        (void*)&disasm_ ## _format, \
        (void*)& _mnemonic "\0" #_name \
    }

/* The following variants of the opcode table definition macros
   specify 37X (370 EXTENSIONS) instead of 370 to indicate that
   they are ESA/390 and ESAME instructions back-ported to S/370 */
#define GENx37Xx390x___ GENx370x390x___
#define GENx37Xx___x900 GENx370x___x900
#define GENx37Xx390x900 GENx370x390x900


typedef void (ATTR_REGPARM(2) *zz_func) (BYTE inst[], REGS *regs);

#define ILC(_b) ((_b) < 0x40 ? 2 : (_b) < 0xc0 ? 4 : 6)

#define REAL_ILC(_regs) \
 (likely(!(_regs)->execflag) ? (_regs)->psw.ilc : (_regs)->exrl ? 6 : 4)

/* Gabor Hoffer (performance option) */
OPC_DLL_IMPORT zz_func s370_opcode_table[];

OPC_DLL_IMPORT zz_func opcode_table[][GEN_MAXARCH];

#if !defined(SOFTWARE_M65) && !defined(HARDWARE_M65)
#define DISASM_INSTRUCTION(_inst) \
    disasm_table((_inst), 0)
#endif

typedef void (*func) ();

#if !defined(SOFTWARE_M65) && !defined(HARDWARE_M65)
extern void disasm_table (BYTE inst[], char mnemonic[]);
#endif

#if defined(OPTION_INSTRUCTION_COUNTING)

#define COUNT_INST(_inst, _regs) \
do { \
int used; \
    switch((_inst)[0]) { \
    case 0x01: \
        used = sysblk.imap01[(_inst)[1]]++; \
        break; \
    case 0xA4: \
        used = sysblk.imapa4[(_inst)[1]]++; \
        break; \
    case 0xA5: \
        used = sysblk.imapa5[(_inst)[1] & 0x0F]++; \
        break; \
    case 0xA6: \
        used = sysblk.imapa6[(_inst)[1]]++; \
        break; \
    case 0xA7: \
        used = sysblk.imapa7[(_inst)[1] & 0x0F]++; \
        break; \
    case 0xB2: \
        used = sysblk.imapb2[(_inst)[1]]++; \
        break; \
    case 0xB3: \
        used = sysblk.imapb3[(_inst)[1]]++; \
        break; \
    case 0xB9: \
        used = sysblk.imapb9[(_inst)[1]]++; \
        break; \
    case 0xC0: \
        used = sysblk.imapc0[(_inst)[1] & 0x0F]++; \
        break; \
    case 0xC2:                                     /*@Z9*/ \
        used = sysblk.imapc2[(_inst)[1] & 0x0F]++; /*@Z9*/ \
        break;                                     /*@Z9*/ \
    case 0xC4:                                     /*208*/ \
        used = sysblk.imapc4[(_inst)[1] & 0x0F]++; /*208*/ \
        break;                                     /*208*/ \
    case 0xC6:                                     /*208*/ \
        used = sysblk.imapc6[(_inst)[1] & 0x0F]++; /*208*/ \
        break;                                     /*208*/ \
    case 0xC8: \
        used = sysblk.imapc8[(_inst)[1] & 0x0F]++; \
        break; \
    case 0xE3: \
        used = sysblk.imape3[(_inst)[5]]++; \
        break; \
    case 0xE4: \
        used = sysblk.imape4[(_inst)[1]]++; \
        break; \
    case 0xE5: \
        used = sysblk.imape5[(_inst)[1]]++; \
        break; \
    case 0xEB: \
        used = sysblk.imapeb[(_inst)[5]]++; \
        break; \
    case 0xEC: \
        used = sysblk.imapec[(_inst)[5]]++; \
        break; \
    case 0xED: \
        used = sysblk.imaped[(_inst)[5]]++; \
        break; \
    default: \
        used = sysblk.imapxx[(_inst)[0]]++; \
    } \
    if(!used) \
    { \
    obtain_lock( &sysblk.icount_lock ); \
    logmsg("First use: "); \
    ARCH_DEP(display_inst) ((_regs), (_inst)); \
    release_lock( &sysblk.icount_lock ); \
    } \
} while(0)

#else

#define COUNT_INST(_inst, _regs)

#endif

/* The footprint_buffer option saves a copy of the register context
   every time an instruction is executed.  This is for problem
   determination only, as it severely impacts performance.       *JJ */

#if defined(OPTION_FOOTPRINT_BUFFER)
#define FOOTPRINT(_regs) \
do { \
    sysblk.footprregs[(_regs)->cpuad][sysblk.footprptr[(_regs)->cpuad]] = *(_regs); \
    memcpy(&sysblk.footprregs[(_regs)->cpuad][sysblk.footprptr[(_regs)->cpuad]++].inst,(_inst),6); \
    sysblk.footprptr[(_regs)->cpuad] &= OPTION_FOOTPRINT_BUFFER - 1; \
} while(0)
#endif

#if !defined(FOOTPRINT)
#define FOOTPRINT(_regs)
#endif

/* PSW Instruction Address manipulation */

#define _PSW_IA(_regs, _n) \
 (VADR)((_regs)->AIV + ((intptr_t)(_regs)->ip - (intptr_t)(_regs)->aip) + (_n))

#define PSW_IA(_regs, _n) \
 (_PSW_IA((_regs), (_n)) & ADDRESS_MAXWRAP((_regs)))

#define SET_PSW_IA(_regs) \
do { \
  if ((_regs)->aie) (_regs)->psw.IA = PSW_IA((_regs), 0); \
} while (0)

#define UPD_PSW_IA(_regs, _addr) \
do { \
  (_regs)->psw.IA = (_addr) & ADDRESS_MAXWRAP(_regs); \
  if (likely((_regs)->aie != NULL)) { \
    if (likely((_regs)->AIV == ((_regs)->psw.IA & (PAGEFRAME_PAGEMASK|1)))) \
      (_regs)->ip = _PSW_IA_MAIN((_regs), (_regs)->psw.IA); \
    else \
      (_regs)->aie = NULL; \
  } \
} while (0)

/*
 * The next three macros are used by branch-and-link type instructions
 * where the addressing mode is known.
 * Note that wrap is not performed for PSW_IA64 and for PSW_IA31.
 * For the latter, we expect branch-and-link code to `or' the hi bit
 * on so there is no need to `and' it off.
 */
#define PSW_IA64(_regs, _n) \
  ((_regs)->AIV \
   + (((uintptr_t)(_regs)->ip + (unsigned int)(_n)) - (uintptr_t)(_regs)->aip))
#define PSW_IA31(_regs, _n) \
  ((_regs)->AIV_L + ((uintptr_t)(_regs)->ip + (unsigned int)(_n)) \
   - (uintptr_t)(_regs)->aip)
#define PSW_IA24(_regs, _n) \
 (((_regs)->AIV_L + ((uintptr_t)(_regs)->ip + (unsigned int)(_n)) \
   - (uintptr_t)(_regs)->aip) & AMASK24)

/* Accelerator for instruction addresses */

#define INVALIDATE_AIA(_regs) \
do { \
  if ((_regs)->aie) { \
    (_regs)->psw.IA = PSW_IA((_regs), 0); \
    (_regs)->aie = NULL; \
  } \
} while (0)

#define INVALIDATE_AIA_MAIN(_regs, _main) \
do { \
  if ((_main) == (_regs)->aip && (_regs)->aie) { \
    (_regs)->psw.IA = PSW_IA((_regs), 0); \
    (_regs)->aie = NULL; \
  } \
} while (0)

#if 1
#define _PSW_IA_MAIN(_regs, _addr) \
 ((BYTE *)((uintptr_t)(_regs)->aip | (uintptr_t)((_addr) & PAGEFRAME_BYTEMASK)))
#else
#define _PSW_IA_MAIN(_regs, _addr) \
 ((BYTE *)((_regs)->aim ^ (uintptr_t)(_addr)))
#endif

#define _VALID_IP(_regs, _exec) \
( \
    ( !(_exec) && (_regs)->ip <  (_regs)->aie ) \
 || \
    ( (_exec) && ((_regs)->ET & (PAGEFRAME_PAGEMASK|0x01)) == (_regs)->AIV \
   && _PSW_IA_MAIN((_regs), (_regs)->ET) < (_regs)->aie \
    ) \
)

/* Instruction fetching */

#define INSTRUCTION_FETCH(_regs, _exec) \
  likely(_VALID_IP((_regs),(_exec))) \
  ? ((_exec) ? _PSW_IA_MAIN((_regs), (_regs)->ET) : (_regs)->ip) \
  : ARCH_DEP(instfetch) ((_regs), (_exec))

/* Instruction execution */

#define EXECUTE_INSTRUCTION(_ip, _regs) \
do { \
    FOOTPRINT ((_regs)); \
    COUNT_INST ((_ip), (_regs)); \
    (_regs)->ARCH_DEP(opcode_table)[_ip[0]]((_ip), (_regs)); \
} while(0)

#define UNROLLED_EXECUTE(_regs) \
 if ((_regs)->ip >= (_regs)->aie) break; \
 EXECUTE_INSTRUCTION((_regs)->ip, (_regs))

/* Branching */

#define SUCCESSFUL_BRANCH(_regs, _addr, _len) \
do { \
  VADR _newia; \
  UPDATE_BEAR((_regs), 0); \
  _newia = (_addr) & ADDRESS_MAXWRAP((_regs)); \
  if (likely(!(_regs)->permode && !(_regs)->execflag) \
   && likely((_newia & (PAGEFRAME_PAGEMASK|0x01)) == (_regs)->AIV)) { \
    (_regs)->ip = (BYTE *)((uintptr_t)(_regs)->aim ^ (uintptr_t)_newia); \
    return; \
  } else { \
    if (unlikely((_regs)->execflag)) \
      UPDATE_BEAR((_regs), (_len) - ((_regs)->exrl ? 6 : 4)); \
    (_regs)->psw.IA = _newia; \
    (_regs)->aie = NULL; \
    PER_SB((_regs), (_regs)->psw.IA); \
  } \
} while (0)

#define SUCCESSFUL_RELATIVE_BRANCH(_regs, _offset, _len) \
do { \
  UPDATE_BEAR((_regs), 0); \
  if (likely(!(_regs)->permode && !(_regs)->execflag) \
   && likely((_regs)->ip + (_offset) >= (_regs)->aip) \
   && likely((_regs)->ip + (_offset) <  (_regs)->aie)) { \
    (_regs)->ip += (_offset); \
    return; \
  } else { \
    if (likely(!(_regs)->execflag)) \
      (_regs)->psw.IA = PSW_IA((_regs), (_offset)); \
    else { \
      UPDATE_BEAR((_regs), (_len) - ((_regs)->exrl ? 6 : 4)); \
      (_regs)->psw.IA = (_regs)->ET + (_offset); \
      (_regs)->psw.IA &= ADDRESS_MAXWRAP((_regs)); \
    } \
    (_regs)->aie = NULL; \
    PER_SB((_regs), (_regs)->psw.IA); \
  } \
} while (0)

/* BRCL, BRASL can branch +/- 4G.  This is problematic on a 32 bit host */
#define SUCCESSFUL_RELATIVE_BRANCH_LONG(_regs, _offset) \
do { \
  UPDATE_BEAR((_regs), 0); \
  if (likely(!(_regs)->permode && !(_regs)->execflag) \
   && likely((_offset) > -4096) \
   && likely((_offset) <  4096) \
   && likely((_regs)->ip + (_offset) >= (_regs)->aip) \
   && likely((_regs)->ip + (_offset) <  (_regs)->aie)) { \
    (_regs)->ip += (_offset); \
    return; \
  } else { \
    if (likely(!(_regs)->execflag)) \
      (_regs)->psw.IA = PSW_IA((_regs), (_offset)); \
    else { \
      UPDATE_BEAR((_regs), 6 - ((_regs)->exrl ? 6 : 4)); \
      (_regs)->psw.IA = (_regs)->ET + (_offset); \
      (_regs)->psw.IA &= ADDRESS_MAXWRAP((_regs)); \
    } \
    (_regs)->aie = NULL; \
    PER_SB((_regs), (_regs)->psw.IA); \
  } \
} while (0)

/* CPU Stepping or Tracing */

#define CPU_STEPPING(_regs, _ilc) \
  ( \
      sysblk.inststep \
   && ( \
        (sysblk.stepaddr[0] == 0 && sysblk.stepaddr[1] == 0) \
     || (sysblk.stepaddr[0] <= sysblk.stepaddr[1] \
         && PSW_IA((_regs), -(_ilc)) >= sysblk.stepaddr[0] \
         && PSW_IA((_regs), -(_ilc)) <= sysblk.stepaddr[1] \
        ) \
     || (sysblk.stepaddr[0] > sysblk.stepaddr[1] \
         && PSW_IA((_regs), -(_ilc)) >= sysblk.stepaddr[1] \
         && PSW_IA((_regs), -(_ilc)) <= sysblk.stepaddr[0] \
        ) \
      ) \
  )

#define CPU_TRACING(_regs, _ilc) \
  ( \
      sysblk.insttrace \
   && ( \
        (sysblk.traceaddr[0] == 0 && sysblk.traceaddr[1] == 0) \
     || (sysblk.traceaddr[0] <= sysblk.traceaddr[1] \
         && PSW_IA((_regs), -(_ilc)) >= sysblk.traceaddr[0] \
         && PSW_IA((_regs), -(_ilc)) <= sysblk.traceaddr[1] \
        ) \
     || (sysblk.traceaddr[0] > sysblk.traceaddr[1] \
         && PSW_IA((_regs), -(_ilc)) >= sysblk.traceaddr[1] \
         && PSW_IA((_regs), -(_ilc)) <= sysblk.traceaddr[0] \
        ) \
      ) \
  )

#define CPU_STEPPING_OR_TRACING(_regs, _ilc) \
  ( unlikely((_regs)->tracing) && \
    (CPU_STEPPING((_regs), (_ilc)) || CPU_TRACING((_regs), (_ilc))) \
  )

#define CPU_TRACING_ALL \
  (sysblk.insttrace && sysblk.traceaddr[0] == 0 && sysblk.traceaddr[1] == 0)

#define CPU_STEPPING_ALL \
  (sysblk.inststep && sysblk.stepaddr[0] == 0 && sysblk.stepaddr[1] == 0)

#define CPU_STEPPING_OR_TRACING_ALL \
  ( CPU_TRACING_ALL || CPU_STEPPING_ALL )


#define RETURN_INTCHECK(_regs) \
        longjmp((_regs)->progjmp, SIE_NO_INTERCEPT)

#define ODD_CHECK(_r, _regs) \
    if( (_r) & 1 ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

#define ODD2_CHECK(_r1, _r2, _regs) \
    if( ((_r1) & 1) || ((_r2) & 1) ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

#define HW_CHECK(_value, _regs) \
    if( (_value) & 1 ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

#define FW_CHECK(_value, _regs) \
    if( (_value) & 3 ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

#define DW_CHECK(_value, _regs) \
    if( (_value) & 7 ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

#define QW_CHECK(_value, _regs) \
    if( (_value) & 15 ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

    /* Program check if m is not 0, 1, or 4 to 7 */
#define HFPM_CHECK(_m, _regs) \
    if (((_m) == 2) || ((_m) == 3) || ((_m) & 8)) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

#define PRIV_CHECK(_regs) \
    if( PROBSTATE(&(_regs)->psw) ) \
        (_regs)->program_interrupt( (_regs), PGM_PRIVILEGED_OPERATION_EXCEPTION)

    /* Program check if r is not 0,1,4,5,8,9,12, or 13 (designating 
       the lower-numbered register of a floating-point register pair) */
#define BFPREGPAIR_CHECK(_r, _regs) \
    if( ((_r) & 2) ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

    /* Program check if r1 and r2 are not both 0,1,4,5,8,9,12, or 13
       (lower-numbered register of a floating-point register pair) */
#define BFPREGPAIR2_CHECK(_r1, _r2, _regs) \
    if( ((_r1) & 2) || ((_r2) & 2) ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

    /* Program check if r is not 0,1,4,5,8,9,12, or 13 (designating 
       the lower-numbered register of a floating-point register pair) */
#define DFPREGPAIR_CHECK(_r, _regs) \
    if( ((_r) & 2) ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

    /* Program check if r1 and r2 are not both 0,1,4,5,8,9,12, or 13
       (lower-numbered register of a floating-point register pair) */
#define DFPREGPAIR2_CHECK(_r1, _r2, _regs) \
    if( ((_r1) & 2) || ((_r2) & 2) ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

    /* Program check if r1, r2, r3 are not all 0,1,4,5,8,9,12, or 13
       (lower-numbered register of a floating-point register pair) */
#define DFPREGPAIR3_CHECK(_r1, _r2, _r3, _regs) \
    if( ((_r1) & 2) || ((_r2) & 2) || ((_r3) & 2) ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

    /* Program check if fpc is not valid contents for FPC register */
#define FPC_CHECK(_fpc, _regs) \
    if((_fpc) & FPC_RESERVED) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

#define SSID_CHECK(_regs) \
    if((!((_regs)->GR_LHH(1) & 0x0001)) \
    || (_regs)->GR_LHH(1) > (0x0001|((FEATURE_LCSS_MAX-1) << 1))) \
        (_regs)->program_interrupt( (_regs), PGM_OPERAND_EXCEPTION)

#define IOID_TO_SSID(_ioid) \
    ((_ioid) >> 16)

#define IOID_TO_LCSS(_ioid) \
    ((_ioid) >> 17)

#define SSID_TO_LCSS(_ssid) \
    ((_ssid) >> 1)

#define LCSS_TO_SSID(_lcss) \
    (((_lcss) << 1) | 1)

#define PER_RANGE_CHECK(_addr, _low, _high) \
  ( (((_high) & MAXADDRESS) >= ((_low) & MAXADDRESS)) ? \
  (((_addr) >= ((_low) & MAXADDRESS)) && (_addr) <= ((_high) & MAXADDRESS)) : \
  (((_addr) >= ((_low) & MAXADDRESS)) || (_addr) <= ((_high) & MAXADDRESS)) )

#define PER_RANGE_CHECK2(_addr1, _addr2, _low, _high) \
  ( (((_high) & MAXADDRESS) >= ((_low) & MAXADDRESS)) ? \
  (((_addr1) >= ((_low) & MAXADDRESS)) && (_addr1) <= ((_high) & MAXADDRESS)) || \
  (((_addr2) >= ((_low) & MAXADDRESS)) && (_addr2) <= ((_high) & MAXADDRESS)) || \
  (((_addr1) <= ((_low) & MAXADDRESS)) && (_addr2) >= ((_high) & MAXADDRESS)) :  \
  (((_addr2) >= ((_low) & MAXADDRESS)) || (_addr1) <= ((_high) & MAXADDRESS)) )

#ifdef WORDS_BIGENDIAN
 #define CSWAP16(_x) (_x)
 #define CSWAP32(_x) (_x)
 #define CSWAP64(_x) (_x)
#else
 #define CSWAP16(_x) bswap_16(_x)
 #define CSWAP32(_x) bswap_32(_x)
 #define CSWAP64(_x) bswap_64(_x)
#endif

#define FETCH_HW(_value, _storage) (_value) = fetch_hw(_storage)
#define FETCH_FW(_value, _storage) (_value) = fetch_fw(_storage)
#define FETCH_DW(_value, _storage) (_value) = fetch_dw(_storage)

#define STORE_HW(_storage, _value) store_hw(_storage, _value)
#define STORE_FW(_storage, _value) store_fw(_storage, _value)
#define STORE_DW(_storage, _value) store_dw(_storage, _value)

#include "machdep.h"

#endif /*!defined(_OPCODE_H)*/

#undef SIE_ACTIVE
#define SIE_ACTIVE(_regs) (0)

#define MULTIPLE_CONTROLLED_DATA_SPACE(_regs) (0)

/* PER3 Breaking Event Address Recording (BEAR) */

#undef UPDATE_BEAR
#undef SET_BEAR_REG

 #define UPDATE_BEAR(_regs, _n)   while (0)
 #define SET_BEAR_REG(_regs, _ip) while (0)

#undef HFPREG_CHECK
#undef HFPREG2_CHECK
#undef HFPODD_CHECK
#undef HFPODD2_CHECK
#undef FPR2I
#undef FPREX


    /* Program check if r1 is not 0, 2, 4, or 6 */
#define HFPREG_CHECK(_r, _regs) \
    if( (_r) & 9 ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

    /* Program check if r1 and r2 are not 0, 2, 4, or 6 */
#define HFPREG2_CHECK(_r1, _r2, _regs) \
    if( ((_r1) & 9) || ((_r2) & 9) ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

    /* Program check if r1 is not 0 or 4 */
#define HFPODD_CHECK(_r, _regs) \
    if( (_r) & 11 ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

    /* Program check if r1 and r2 are not 0 or 4 */
#define HFPODD2_CHECK(_r1, _r2, _regs) \
    if( ((_r1) & 11) || ((_r2) & 11) ) \
        (_regs)->program_interrupt( (_regs), PGM_SPECIFICATION_EXCEPTION)

    /* Convert fpr to index */
#define FPR2I(_r) \
    (_r)

    /* Offset of extended register */
#define FPREX 2


#define TLBIX(_addr) (((VADR_L)(_addr) >> TLB_PAGESHIFT) & TLB_MASK)

#define MAINADDR(_main, _addr) \
   (BYTE*)((uintptr_t)(_main) ^ (uintptr_t)(_addr))

#define NEW_MAINADDR(_regs, _addr, _aaddr) \
   (BYTE*)((uintptr_t)((_regs)->mainstor \
         + (uintptr_t)(_aaddr)) \
         ^ (uintptr_t)((_addr) & TLB_PAGEMASK))

/* Perform invalidation after storage key update.
 * If the REF or CHANGE bit is turned off for an absolute
 * address then we need to invalidate any cached entries
 * for that address on *all* CPUs.
 * FIXME: Synchronization, esp for the CHANGE bit, should
 * be tighter than what is provided here.
 */

#define STORKEY_INVALIDATE(_regs, _n) \
 do { \
   BYTE *mn; \
   mn = (_regs)->mainstor + ((_n) & PAGEFRAME_PAGEMASK); \
   if (sysblk.cpus > 1) { \
     int i; \
     OBTAIN_INTLOCK ((_regs)); \
     for (i = 0; i < HI_CPU; i++) { \
       if (IS_CPU_ONLINE(i) && i != (_regs)->cpuad) { \
         if (!( sysblk.waiting_mask & CPU_BIT(i)) ) { \
           ON_IC_INTERRUPT(sysblk.regs[i]); \
           if (!sysblk.regs[i]->invalidate) { \
             sysblk.regs[i]->invalidate = 1; \
             sysblk.regs[i]->invalidate_main = mn; \
           } else \
             sysblk.regs[i]->invalidate_main = NULL; \
         } \
       } \
     } \
     RELEASE_INTLOCK((_regs)); \
   } \
 } while (0)

#if defined(INLINE_STORE_FETCH_ADDR_CHECK)
 #define FETCH_MAIN_ABSOLUTE(_addr, _regs, _len) \
  ARCH_DEP(fetch_main_absolute)((_addr), (_regs), (_len))
#else
 #define FETCH_MAIN_ABSOLUTE(_addr, _regs, _len) \
  ARCH_DEP(fetch_main_absolute)((_addr), (_regs))
#endif

#define INST_UPDATE_PSW(_regs, _len, _ilc) \
     do { \
            if (_len) (_regs)->ip += (_len); \
            if (_ilc) (_regs)->psw.ilc = (_ilc); \
        } while(0)

/* Instruction decoders */

/*
 * A decoder is placed at the start of each instruction. The purpose
 * of a decoder is to extract the operand fields according to the
 * instruction format; to increment the instruction address (IA) field
 * of the PSW by 2, 4, or 6 bytes; and to set the instruction length
 * code (ILC) field of the PSW in case a program check occurs.
 *
 * Certain decoders have additional forms with 0 and _B suffixes.
 * - the 0 suffix version does not update the PSW ILC.
 * - the _B suffix version updates neither the PSW ILC nor the PSW IA.
 *
 * The "0" versions of the decoders are chosen whenever we know
 * that past this point, no program interrupt will be generated
 * (like most general instructions when no storage access is needed)
 * therefore needing simpler prologue code.
 * The "_B" versions for some of the decoders are intended for
 * "branch" type operations where updating the PSW IA to IA+ILC 
 * should only be done after the branch is deemed impossible.
 */

#undef DECODER_TEST_RRE
#define DECODER_TEST_RRF_R
#define DECODER_TEST_RRF_M
#define DECODER_TEST_RRF_M4
#define DECODER_TEST_RRF_RM
#define DECODER_TEST_RRF_MM
#define DECODER_TEST_RRR
#undef DECODER_TEST_RX
#define DECODER_TEST_RXE
#define DECODER_TEST_RXF
#define DECODER_TEST_RXY
#undef DECODER_TEST_RS
#define DECODER_TEST_RSY
#undef DECODER_TEST_RSL
#undef DECODER_TEST_RSI
#undef DECODER_TEST_RI
#define DECODER_TEST_RIL
#define DECODER_TEST_RIL_A
#undef DECODER_TEST_RIS
#undef DECODER_TEST_RRS
#undef DECODER_TEST_SI
#define DECODER_TEST_SIY
#undef DECODER_TEST_SIL
#undef DECODER_TEST_S
#define DECODER_TEST_SS
#define DECODER_TEST_SS_L
#define DECODER_TEST_SSE
#define DECODER_TEST_SSF

/* E implied operands and extended op code */
#undef E
#define E(_inst,_regs) E_DECODER((_inst), (_regs), 2, 2)

#define E_DECODER(_inst, _regs, _len, _ilc) \
        { \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

/* RR register to register */
#undef RR_
#undef RR0
#undef RR_B

#define RR_(_inst, _regs, _r1, _r2)  \
        RR_DECODER(_inst, _regs, _r1, _r2, 2, 2)
#define RR0(_inst, _regs, _r1, _r2) \
        RR_DECODER(_inst, _regs, _r1, _r2, 2, 0)
#define RR_B(_inst, _regs, _r1, _r2) \
        RR_DECODER(_inst, _regs, _r1, _r2, 0, 0)

#define RR_DECODER(_inst, _regs, _r1, _r2, _len, _ilc) \
        { \
            int i = (_inst)[1]; \
            (_r1) = i >> 4; \
            (_r2) = i & 0x0F; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

/* RR special format for SVC instruction */
#undef RR_SVC

#define RR_SVC(_inst, _regs, _svc) \
        RR_SVC_DECODER(_inst, _regs, _svc, 2, 2)

#define RR_SVC_DECODER(_inst, _regs, _svc, _ilc, _len) \
        { \
            (_svc) = (_inst)[1]; \
            INST_UPDATE_PSW((_regs), (_ilc), (_len)); \
        }

/* RRE register to register with extended op code */
#undef RRE
#undef RRE0
#undef RRE_B

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RRE)
 #define RRE(_inst, _regs, _r1, _r2) \
         RRE_DECODER(_inst, _regs, _r1, _r2, 4, 4)
 #define RRE0(_inst, _regs, _r1, _r2) \
         RRE_DECODER(_inst, _regs, _r1, _r2, 4, 0)
 #define RRE_B(_inst, _regs, _r1, _r2) \
         RRE_DECODER(_inst, _regs, _r1, _r2, 0, 0)
#else
 #define RRE(_inst, _regs, _r1, _r2) \
         RRE_DECODER_TEST(_inst, _regs, _r1, _r2, 4, 4)
 #define RRE0(_inst, _regs, _r1, _r2) \
         RRE_DECODER_TEST(_inst, _regs, _r1, _r2, 4, 0)
 #define RRE_B(_inst, _regs, _r1, _r2) \
         RRE_DECODER_TEST(_inst, _regs, _r1, _r2, 0, 0)
#endif

#define RRE_DECODER(_inst, _regs, _r1, _r2, _len, _ilc) \
        { \
            int i = (_inst)[3]; \
            (_r1) = i >> 4; \
            (_r2) = i & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

#define RRE_DECODER_TEST(_inst, _regs, _r1, _r2, _len, _ilc) \
        { \
            int i = (_inst)[3]; \
            (_r2) = i & 0xf; \
            (_r1) = i >> 4; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

/* RRF register to register with additional R3 field */
#undef RRF_R

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RRF_R)
 #define RRF_R(_inst, _regs, _r1, _r2, _r3) \
         RRF_R_DECODER(_inst, _regs, _r1, _r2, _r3, 4, 4)
#else
 #define RRF_R(_inst, _regs, _r1, _r2, _r3) \
         RRF_R_DECODER_TEST(_inst, _regs, _r1, _r2, _r3, 4, 4)
#endif

#define RRF_R_DECODER(_inst, _regs, _r1, _r2, _r3, _len, _ilc) \
        { \
            int i = (_inst)[2]; \
            (_r1) = i >> 4; \
            i = (_inst)[3]; \
            (_r3) = i >> 4; \
            (_r2) = i & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

#define RRF_R_DECODER_TEST(_inst, _regs, _r1, _r2, _r3, _len, _ilc) \
      { U32 temp = fetch_fw(_inst); \
            (_r2) = (temp      ) & 0xf; \
            (_r3) = (temp >>  4) & 0xf; \
            (_r1) = (temp >> 12) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

/* RRF register to register with additional M3 field */
#undef RRF_M

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RRF_M)
 #define RRF_M(_inst, _regs, _r1, _r2, _m3) \
         RRF_M_DECODER(_inst, _regs, _r1, _r2, _m3, 4, 4)
#else
 #define RRF_M(_inst, _regs, _r1, _r2, _m3) \
         RRF_M_DECODER_TEST(_inst, _regs, _r1, _r2, _m3, 4, 4)
#endif

#define RRF_M_DECODER(_inst, _regs, _r1, _r2, _m3, _len, _ilc) \
        { \
            int i = (_inst)[2]; \
            (_m3) = i >> 4; \
            i = (_inst)[3]; \
            (_r1) = i >> 4; \
            (_r2) = i & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

#define RRF_M_DECODER_TEST(_inst, _regs, _r1, _r2, _m3, _len, _ilc) \
      { U32 temp = fetch_fw(_inst); \
            (_m3) = (temp >> 12) & 0xf; \
            (_r2) = (temp      ) & 0xf; \
            (_r1) = (temp >>  4) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }


/* RRF register to register with additional M4 field */
#undef RRF_M4

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RRF_M4)
 #define RRF_M4(_inst, _regs, _r1, _r2, _m4) \
         RRF_M4_DECODER(_inst, _regs, _r1, _r2, _m4, 4, 4)
#else
 #define RRF_M4(_inst, _regs, _r1, _r2, _m4) \
         RRF_M4_DECODER_TEST(_inst, _regs, _r1, _r2, _m4, 4, 4)
#endif

#define RRF_M4_DECODER(_inst, _regs, _r1, _r2, _m4, _len, _ilc) \
        { \
            int i = (_inst)[2]; \
            (_m4) = i & 0xf; \
            i = (_inst)[3]; \
            (_r1) = i >> 4; \
            (_r2) = i & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

#define RRF_M4_DECODER_TEST(_inst, _regs, _r1, _r2, _m4, _len, _ilc) \
      { U32 temp = fetch_fw(_inst); \
            (_m4) = (temp >>  8) & 0xf; \
            (_r2) = (temp      ) & 0xf; \
            (_r1) = (temp >>  4) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

/* RRF register to register with additional R3 and M4 fields */
#undef RRF_RM

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RRF_RM)
 #define RRF_RM(_inst, _regs, _r1, _r2, _r3, _m4) \
         RRF_RM_DECODER(_inst, _regs, _r1, _r2, _r3, _m4, 4, 4)
#else
 #define RRF_RM(_inst, _regs, _r1, _r2, _r3, _m4) \
         RRF_RM_DECODER_TEST(_inst, _regs, _r1, _r2, _r3, _m4, 4, 4)
#endif

#define RRF_RM_DECODER(_inst, _regs, _r1, _r2, _r3, _m4, _len, _ilc) \
        { \
            int i = (_inst)[2]; \
            (_r3) = i >> 4; \
            (_m4) = i & 0xf; \
            i = (_inst)[3]; \
            (_r1) = i >> 4; \
            (_r2) = i & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

#define RRF_RM_DECODER_TEST(_inst, _regs, _r1, _r2, _r3, _m4, _len, _ilc) \
      { U32 temp = fetch_fw(_inst); \
            (_r3) = (temp >> 12) & 0xf; \
            (_m4) = (temp >>  8) & 0xf; \
            (_r2) = (temp      ) & 0xf; \
            (_r1) = (temp >>  4) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
      }

/* RRF register to register with additional M3 and M4 fields */
#undef RRF_MM

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RRF_MM)
 #define RRF_MM(_inst, _regs, _r1, _r2, _m3, _m4) \
         RRF_MM_DECODER(_inst, _regs, _r1, _r2, _m3, _m4, 4, 4)
#else
 #define RRF_MM(_inst, _regs, _r1, _r2, _m3, _m4) \
         RRF_MM_DECODER_TEST(_inst, _regs, _r1, _r2, _m3, _m4, 4, 4)
#endif

#define RRF_MM_DECODER(_inst, _regs, _r1, _r2, _m3, _m4, _len, _ilc) \
        { \
            int i = (_inst)[2]; \
            (_m3) = i >> 4; \
            (_m4) = i & 0xf; \
            i = (_inst)[3]; \
            (_r1) = i >> 4; \
            (_r2) = i & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

#define RRF_MM_DECODER_TEST(_inst, _regs, _r1, _r2, _m3, _m4, _len, _ilc) \
      { U32 temp = fetch_fw(_inst); \
            (_m3) = (temp >> 12) & 0xf; \
            (_m4) = (temp >>  8) & 0xf; \
            (_r2) = (temp      ) & 0xf; \
            (_r1) = (temp >>  4) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
      }

/* RRR register to register with register */
#undef RRR

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RRR)
 #define RRR(_inst, _regs, _r1, _r2, _r3) \
         RRR_DECODER(_inst, _regs, _r1, _r2, _r3, 4, 4)
#else
 #define RRR(_inst, _regs, _r1, _r2, _r3) \
         RRR_DECODER_TEST(_inst, _regs, _r1, _r2, _r3, 4, 4)
#endif

#define RRR_DECODER(_inst, _regs, _r1, _r2, _r3, _len, _ilc) \
        { \
            int i = (_inst)[2]; \
            (_r3) = i >> 4; \
            i = (_inst)[3]; \
            (_r1) = i >> 4; \
            (_r2) = i & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

#define RRR_DECODER_TEST(_inst, _regs, _r1, _r2, _r3, _len, _ilc) \
      { U32 temp = fetch_fw(_inst); \
            (_r3) = (temp >> 12) & 0xf; \
            (_r2) = (temp      ) & 0xf; \
            (_r1) = (temp >>  4) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

/* RX register and indexed storage */
#undef RX_
#undef RX0
#undef RX_B

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RX)
 #define RX_(_inst, _regs, _r1, _b2, _effective_addr2) \
         RX_DECODER(_inst, _regs, _r1, _b2, _effective_addr2, 4, 4)
 #define RX0(_inst, _regs, _r1, _b2, _effective_addr2) \
         RX_DECODER(_inst, _regs, _r1, _b2, _effective_addr2, 4, 0)
 #define RX_B(_inst, _regs, _r1, _b2, _effective_addr2) \
         RX_DECODER(_inst, _regs, _r1, _b2, _effective_addr2, 0, 0)
#else
 #define RR_(_inst, _regs, _r1, _b2, _effective_addr2) \
         RX_DECODER_TEST(_inst, _regs, _r1, _b2, _effective_addr2, 4, 4)
 #define RX0(_inst, _regs, _r1, _b2, _effective_addr2) \
         RX_DECODER_TEST(_inst, _regs, _r1, _b2, _effective_addr2, 4, 0)
 #define RX_B(_inst, _regs, _r1, _b2, _effective_addr2) \
         RX_DECODER_TEST(_inst, _regs, _r1, _b2, _effective_addr2, 0, 0)
#endif

#define RX_DECODER(_inst, _regs, _r1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_b2) = (temp >> 16) & 0xf; \
            (_effective_addr2) = temp & 0xfff; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            (_b2) = (temp >> 12) & 0xf; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            if ((_len)) \
            (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RX_DECODER_TEST(_inst, _regs, _r1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 16) & 0xf; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            (_b2) = (temp >> 12) & 0xf; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            if ((_len)) \
            (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            (_r1) = (temp >> 20) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RX_BC register and indexed storage - optimized for BC */
#undef RX_BC

#define RX_BC(_inst, _regs, _b2, _effective_addr2) \
        RX_BC_DECODER(_inst, _regs, _b2, _effective_addr2, 0, 0)

#define RX_BC_DECODER(_inst, _regs, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 16) & 0xf; \
            if(unlikely((_b2))) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            (_b2) = (temp >> 12) & 0xf; \
            if(likely((_b2))) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
    }

/* RXE register and indexed storage with extended op code */
#undef RXE

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RXE)
 #define RXE(_inst, _regs, _r1, _b2, _effective_addr2) \
         RXE_DECODER(_inst, _regs, _r1, _b2, _effective_addr2, 6, 6)
#else
 #define RXE(_inst, _regs, _r1, _b2, _effective_addr2) \
         RXE_DECODER_TEST(_inst, _regs, _r1, _b2, _effective_addr2, 6, 6)
#endif

#define RXE_DECODER(_inst, _regs, _r1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_b2) = (temp >> 16) & 0xf; \
            (_effective_addr2) = temp & 0xfff; \
        if((_b2)) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            (_b2) = (temp >> 12) & 0xf; \
        if((_b2)) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RXE_DECODER_TEST(_inst, _regs, _r1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 16) & 0xf; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            (_b2) = (temp >> 12) & 0xf; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            (_r1) = (temp >> 20) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RXF register and indexed storage with ext.opcode and additional R3 */
#undef RXF

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RXF)
 #define RXF(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
         RXF_DECODER(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 6, 6)
#else
 #define RXF(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
         RXF_DECODER_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 6, 6)
#endif

#define RXF_DECODER(_inst, _regs, _r1, _r3, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp; \
        (_r1) = (_inst)[4] >> 4; \
            memcpy (&temp, (_inst), 4); \
            temp = CSWAP32(temp); \
            (_r3) = (temp >> 20) & 0xf; \
            (_b2) = (temp >> 16) & 0xf; \
            (_effective_addr2) = temp & 0xfff; \
        if((_b2)) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            (_b2) = (temp >> 12) & 0xf; \
        if((_b2)) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RXF_DECODER_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 16) & 0xf; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            (_b2) = (temp >> 12) & 0xf; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            (_r3) = (temp >> 20) & 0xf; \
            (_r1) = (_inst)[4] >> 4; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RXY register and indexed storage with extended op code
   and long displacement */
#undef RXY
#undef RXY0
#undef RXY_B

 #if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RXY)
  #define RXY(_inst, _regs, _r1, _b2, _effective_addr2) \
          RXY_DECODER(_inst, _regs, _r1, _b2, _effective_addr2, 6, 6)
  #define RXY0(_inst, _regs, _r1, _b2, _effective_addr2) \
          RXY_DECODER(_inst, _regs, _r1, _b2, _effective_addr2, 6, 0)
  #define RXY_B(_inst, _regs, _r1, _b2, _effective_addr2) \
          RXY_DECODER(_inst, _regs, _r1, _b2, _effective_addr2, 0, 0)
 #else
  #define RXY(_inst, _regs, _r1, _b2, _effective_addr2) \
          RXY_DECODER_TEST(_inst, _regs, _r1, _b2, _effective_addr2, 6, 6)
  #define RXY0(_inst, _regs, _r1, _b2, _effective_addr2) \
          RXY_DECODER_TEST(_inst, _regs, _r1, _b2, _effective_addr2, 6, 0)
  #define RXY_B(_inst, _regs, _r1, _b2, _effective_addr2) \
          RXY_DECODER_TEST(_inst, _regs, _r1, _b2, _effective_addr2, 0, 0)
 #endif

#define RXY_DECODER_LD(_inst, _regs, _r1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp; S32 temp2; int tempx; \
            temp  = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            tempx = (temp >> 16) & 0xf; \
            (_b2) = (temp >> 12) & 0xf; \
            temp2 = (_inst[4] << 12) | (temp & 0xfff); \
            if (temp2 & 0x80000) temp2 |= 0xfff00000; \
            (_effective_addr2) = \
                        (tempx ? (_regs)->GR(tempx) : (GREG)0) + \
                        ((_b2) ? (_regs)->GR((_b2)) : (GREG)0) + \
                        temp2; \
            if ((_len)) \
            (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RXY_DECODER_LD_TEST(_inst, _regs, _r1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp; S32 disp2; \
            temp  = fetch_fw(_inst); \
            (_effective_addr2) = 0; \
            (_b2) = (temp >> 16) & 0xf; \
            if ((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            (_b2) = (temp >> 12) & 0xf; \
            if ((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            disp2 = temp & 0xfff; \
            if (unlikely((_inst)[4])) { \
                disp2 |= (_inst[4] << 12); \
                if (disp2 & 0x80000) disp2 |= 0xfff00000; \
            } \
            (_effective_addr2) += disp2; \
            if ((_len)) \
            (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            (_r1) = (temp >> 20) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RXY_DECODER(_inst, _regs, _r1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_b2) = (temp >> 16) & 0xf; \
            (_effective_addr2) = temp & 0xfff; \
        if((_b2)) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        if ((_len)) \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            (_b2) = (temp >> 12) & 0xf; \
        if((_b2)) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        if ((_len)) \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RXY_DECODER_TEST(_inst, _regs, _r1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 16) & 0xf; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            (_b2) = (temp >> 12) & 0xf; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            if ((_len)) \
            (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            (_r1) = (temp >> 20) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RS register and storage with additional R3 or M3 field */
#undef RS
#undef RS0
#undef RS_B

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RS)
 #define RS(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
         RS_DECODER(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 4, 4)
 #define RS0(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
         RS_DECODER(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 4, 0)
 #define RS_B(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
         RS_DECODER(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 0, 0)
#else
 #define RS(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
         RS_DECODER_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 4, 4)
 #define RS0(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
         RS_DECODER_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 4, 0)
 #define RS_B(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
         RS_DECODER_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 0, 0)
#endif

#define RS_DECODER(_inst, _regs, _r1, _r3, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_r3) = (temp >> 16) & 0xf; \
            (_b2) = (temp >> 12) & 0xf; \
            (_effective_addr2) = temp & 0xfff; \
        if((_b2)) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        if ((_len)) \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RS_DECODER_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 12) & 0xf; \
            if((_b2)) \
            { \
                (_effective_addr2) += (_regs)->GR((_b2)); \
                if ((_len)) \
                (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_r3) = (temp >> 16) & 0xf; \
            (_r1) = (temp >> 20) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#if 0
/* RSE register and storage with extended op code and additional
   R3 or M3 field (note, this is NOT the ESA/390 vector RSE format) */
/* Note: Effective June 2003, RSE is retired and replaced by RSY */
#undef RSE
#define RSE(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
    {   U32 temp; \
            memcpy (&temp, (_inst), 4); \
            temp = CSWAP32(temp); \
            (_r1) = (temp >> 20) & 0xf; \
            (_r3) = (temp >> 16) & 0xf; \
            (_b2) = (temp >> 12) & 0xf; \
            (_effective_addr2) = temp & 0xfff; \
        if((_b2) != 0) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), 6, 6); \
    }
#endif

/* RSY register and storage with extended op code, long displacement,
   and additional R3 or M3 field */
#undef RSY
#undef RSY0
#undef RSY_B

 #if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RSY)
  #define RSY(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
          RSY_DECODER(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 6, 6)
  #define RSY0(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
          RSY_DECODER(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 6, 0)
  #define RSY_B(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
          RSY_DECODER(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 0, 0)
 #else
  #define RSY(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
          RSY_DECODER_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 6, 6)
  #define RSY0(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
          RSY_DECODER_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 6, 0)
  #define RSY_B(_inst, _regs, _r1, _r3, _b2, _effective_addr2) \
          RSY_DECODER_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, 0, 0)
 #endif

#define RSY_DECODER_LD(_inst, _regs, _r1, _r3, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp; S32 temp2; \
            temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_r3) = (temp >> 16) & 0xf; \
            (_b2) = (temp >> 12) & 0xf; \
            temp2 = (_inst[4] << 12) | (temp & 0xfff); \
            if (temp2 & 0x80000) temp2 |= 0xfff00000; \
            (_effective_addr2) = \
                        ((_b2) ? (_regs)->GR((_b2)) : (GREG)0) + \
                        temp2; \
            if ((_len)) \
            (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RSY_DECODER_LD_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp; S32 disp2; \
            temp = fetch_fw(_inst); \
            (_effective_addr2) = 0; \
            (_b2) = (temp >> 12) & 0xf; \
            if ((_b2)) \
                _effective_addr2 += (_regs)->GR((_b2)); \
            disp2 = temp & 0xfff; \
            if (unlikely((_inst)[4])) { \
                disp2 |= (_inst[4] << 12); \
                if (disp2 & 0x80000) disp2 |= 0xfff00000; \
            } \
            (_effective_addr2) += disp2; \
            if ((_len)) \
            (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            (_r3) = (temp >> 16) & 0xf; \
            (_r1) = (temp >> 20) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RSY_DECODER(_inst, _regs, _r1, _r3, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_r3) = (temp >> 16) & 0xf; \
            (_b2) = (temp >> 12) & 0xf; \
            (_effective_addr2) = temp & 0xfff; \
        if((_b2) != 0) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        if ((_len)) \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RSY_DECODER_TEST(_inst, _regs, _r1, _r3, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 12) & 0xf; \
            if((_b2)) \
                (_effective_addr2) += (_regs)->GR((_b2)); \
            if ((_len)) \
            (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            (_r3) = (temp >> 16) & 0xf; \
            (_r1) = (temp >> 20) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RSL storage operand with extended op code and 4-bit L field */
#undef RSL

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RSL)
 #define RSL(_inst, _regs, _l1, _b1, _effective_addr1) \
         RSL_DECODER(_inst, _regs, _l1, _b1, _effective_addr1, 6, 6)
#else
 #define RSL(_inst, _regs, _l1, _b1, _effective_addr1) \
         RSL_DECODER_TEST(_inst, _regs, _l1, _b1, _effective_addr1, 6, 6)
#endif

#define RSL_DECODER(_inst, _regs, _l1, _b1, _effective_addr1, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_l1) = (temp >> 20) & 0xf; \
            (_b1) = (temp >> 12) & 0xf; \
            (_effective_addr1) = temp & 0xfff; \
            if((_b1) != 0) \
            { \
                (_effective_addr1) += (_regs)->GR((_b1)); \
                (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

#define RSL_DECODER_TEST(_inst, _regs, _l1, _b1, _effective_addr1, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr1) = temp & 0xfff; \
            (_b1) = (temp >> 12) & 0xf; \
            if((_b1)) { \
                (_effective_addr1) += (_regs)->GR((_b1)); \
                (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_l1) = (temp >> 20) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
        }

/* RSI register and immediate with additional R3 field */
#undef RSI
#undef RSI0

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RSI)
 #define RSI(_inst, _regs, _r1, _r3, _i2) \
         RSI_DECODER(_inst, _regs, _r1, _r3, _i2, 4, 4)
 #define RSI0(_inst, _regs, _r1, _r3, _i2) \
         RSI_DECODER(_inst, _regs, _r1, _r3, _i2, 4, 0)
#else
 #define RSI(_inst, _regs, _r1, _r3, _i2) \
         RSI_DECODER_TEST(_inst, _regs, _r1, _r3, _i2, 4, 4)
 #define RSI0(_inst, _regs, _r1, _r3, _i2) \
         RSI_DECODER_TEST(_inst, _regs, _r1, _r3, _i2, 4, 0)
#endif

#define RSI_DECODER(_inst, _regs, _r1, _r3, _i2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_r3) = (temp >> 16) & 0xf; \
            (_i2) = temp & 0xffff; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RSI_DECODER_TEST(_inst, _regs, _r1, _r3, _i2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_i2) = temp & 0xffff; \
            (_r3) = (temp >> 16) & 0xf; \
            (_r1) = (temp >> 20) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RI register and immediate with extended 4-bit op code */
#undef RI
#undef RI0
#undef RI_B

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RI)
 #define RI(_inst, _regs, _r1, _op, _i2) \
         RI_DECODER(_inst, _regs, _r1, _op, _i2, 4, 4)
 #define RI0(_inst, _regs, _r1, _op, _i2) \
         RI_DECODER(_inst, _regs, _r1, _op, _i2, 4, 0)
 #define RI_B(_inst, _regs, _r1, _op, _i2) \
         RI_DECODER(_inst, _regs, _r1, _op, _i2, 0, 0)
#else
 #define RI(_inst, _regs, _r1, _op, _i2) \
         RI_DECODER_TEST(_inst, _regs, _r1, _op, _i2, 4, 4)
 #define RI0(_inst, _regs, _r1, _op, _i2) \
         RI_DECODER_TEST(_inst, _regs, _r1, _op, _i2, 4, 0)
 #define RI_B(_inst, _regs, _r1, _op, _i2) \
         RI_DECODER_TEST(_inst, _regs, _r1, _op, _i2, 0, 0)
#endif

#define RI_DECODER(_inst, _regs, _r1, _op, _i2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_op) = (temp >> 16) & 0xf; \
            (_i2) = temp & 0xffff; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RI_DECODER_TEST(_inst, _regs, _r1, _op, _i2) \
    {   U32 temp = fetch_fw(_inst); \
            (_op) = (temp >> 16) & 0xf; \
            (_i2) = temp & 0xffff; \
            (_r1) = (temp >> 20) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RIE register and immediate with ext.opcode and additional R3 */
#undef RIE
#undef RIE0
#undef RIE_B

#define RIE(_inst, _regs, _r1, _r3, _i2) \
        RIE_DECODER(_inst, _regs, _r1, _r3, _i2, 6, 6)
#define RIE0(_inst, _regs, _r1, _r3, _i2) \
        RIE_DECODER(_inst, _regs, _r1, _r3, _i2, 6, 0)
#define RIE_B(_inst, _regs, _r1, _r3, _i2) \
        RIE_DECODER(_inst, _regs, _r1, _r3, _i2, 0, 0)

#define RIE_DECODER(_inst, _regs, _r1, _r3, _i2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_r3) = (temp >> 16) & 0xf; \
            (_i2) = temp & 0xffff; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RIE register and immediate with mask */                      /*208*/
#undef RIE_RIM

#define RIE_RIM(_inst, _regs, _r1, _i2, _m3) \
        RIE_RIM_DECODER(_inst, _regs, _r1, _i2, _m3, 6, 6)

#define RIE_RIM_DECODER(_inst, _regs, _r1, _i2, _m3, _len, _ilc) \
    {   U32 temp = fetch_fw(&(_inst)[1]); \
            (_m3) = (temp >> 4) & 0xf; \
            (_i2) = (temp >> 8) & 0xffff; \
            (_r1) = (temp >> 28) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RIE register to register with immediate and mask */          /*208*/
#undef RIE_RRIM
#undef RIE_RRIM0
#undef RIE_RRIM_B

#define RIE_RRIM(_inst, _regs, _r1, _r2, _i4, _m3) \
        RIE_RRIM_DECODER(_inst, _regs, _r1, _r2, _i4, _m3, 6, 6)
#define RIE_RRIM0(_inst, _regs, _r1, _r2, _i4, _m3) \
        RIE_RRIM_DECODER(_inst, _regs, _r1, _r2, _i4, _m3, 6, 0)
#define RIE_RRIM_B(_inst, _regs, _r1, _r2, _i4, _m3) \
        RIE_RRIM_DECODER(_inst, _regs, _r1, _r2, _i4, _m3, 0, 0)

#define RIE_RRIM_DECODER(_inst, _regs, _r1, _r2, _i4, _m3, _len, _ilc) \
    {   U32 temp = fetch_fw(&(_inst)[1]); \
            (_m3) = (temp >> 4) & 0xf; \
            (_i4) = (temp >> 8) & 0xffff; \
            (_r2) = (temp >> 24) & 0xf; \
            (_r1) = (temp >> 28) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RIE register and mask with longer immediate and immediate */ /*208*/
#undef RIE_RMII
#undef RIE_RMII0
#undef RIE_RMII_B

#define RIE_RMII(_inst, _regs, _r1, _i2, _m3, _i4) \
        RIE_RMII_DECODER(_inst, _regs, _r1, _i2, _m3, _i4, 6, 6)
#define RIE_RMII0(_inst, _regs, _r1, _i2, _m3, _i4) \
        RIE_RMII_DECODER(_inst, _regs, _r1, _i2, _m3, _i4, 6, 0)
#define RIE_RMII_B(_inst, _regs, _r1, _i2, _m3, _i4) \
        RIE_RMII_DECODER(_inst, _regs, _r1, _i2, _m3, _i4, 0, 0)

#define RIE_RMII_DECODER(_inst, _regs, _r1, _i2, _m3, _i4, _len, _ilc) \
    {   U32 temp = fetch_fw(&(_inst)[1]); \
            (_i2) = temp & 0xff; \
            (_i4) = (temp >> 8) & 0xffff; \
            (_m3) = (temp >> 24) & 0xf; \
            (_r1) = (temp >> 28) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RIE register to register with three immediate fields */      /*208*/
#undef RIE_RRIII

#define RIE_RRIII(_inst, _regs, _r1, _r2, _i3, _i4, _i5) \
        RIE_RRIII_DECODER(_inst, _regs, _r1, _r2, _i3, _i4, _i5, 6, 6)

#define RIE_RRIII_DECODER(_inst, _regs, _r1, _r2, _i3, _i4, _i5, _len, _ilc) \
    {   U32 temp = fetch_fw(&(_inst)[1]); \
            (_i5) = temp & 0xff; \
            (_i4) = (temp >> 8) & 0xff; \
            (_i3) = (temp >> 16) & 0xff; \
            (_r2) = (temp >> 24) & 0xf; \
            (_r1) = (temp >> 28) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RIL register and longer immediate with extended 4 bit op code */
#undef RIL
#undef RIL0
#undef RIL_B

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RIL)
 #define RIL(_inst, _regs, _r1, _op, _i2) \
         RIL_DECODER(_inst, _regs, _r1, _op, _i2, 6, 6)
 #define RIL0(_inst, _regs, _r1, _op, _i2) \
         RIL_DECODER(_inst, _regs, _r1, _op, _i2, 6, 0)
 #define RIL_B(_inst, _regs, _r1, _op, _i2) \
         RIL_DECODER(_inst, _regs, _r1, _op, _i2, 0, 0)
#else
 #define RIL(_inst, _regs, _r1, _op, _i2) \
         RIL_DECODER_TEST(_inst, _regs, _r1, _op, _i2, 6, 6)
 #define RIL0(_inst, _regs, _r1, _op, _i2) \
         RIL_DECODER_TEST(_inst, _regs, _r1, _op, _i2, 6, 0)
 #define RIL_B(_inst, _regs, _r1, _op, _i2) \
         RIL_DECODER_TEST(_inst, _regs, _r1, _op, _i2, 0, 0)
#endif

#define RIL_DECODER(_inst, _regs, _r1, _op, _i2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_op) = (temp >> 16) & 0xf; \
            (_i2) = ((temp & 0xffff) << 16) \
          | ((_inst)[4] << 8) \
          | (_inst)[5]; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RIL_DECODER_TEST(_inst, _regs, _r1, _op, _i2, _len, _ilc) \
    { \
            (_i2) = fetch_fw(&(_inst)[2]); \
            (_op) = ((_inst)[1]     ) & 0xf; \
            (_r1) = ((_inst)[1] >> 4) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RIL register and longer immediate relative address */
#undef RIL_A

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RIL_A)
 #define RIL_A(_inst, _regs, _r1, _addr2) \
         RIL_A_DECODER(_inst, _regs, _r1, _addr2, 6, 6)
#else
 #define RIL_A(_inst, _regs, _r1, _addr2) \
         RIL_A_DECODER_TEST(_inst, _regs, _r1, _addr2, 6, 6)
#endif

#define RIL_A_DECODER(_inst, _regs, _r1, _addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
        S64 offset; \
            (_r1) = (temp >> 20) & 0xf; \
            offset = 2LL*(S32)(((temp & 0xffff) << 16) \
                    | ((_inst)[4] << 8) \
                    | (_inst)[5]); \
            (_addr2) = (likely(!(_regs)->execflag)) ? \
                    PSW_IA((_regs), offset) : \
                    ((_regs)->ET + offset) & ADDRESS_MAXWRAP((_regs)); \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RIL_A_DECODER_TEST(_inst, _regs, _r1, _addr2, _len, _ilc) \
    { \
        S64 offset = 2LL*(S32)(fetch_fw(&(_inst)[2])); \
            (_r1) = ((_inst)[1] >> 4) & 0xf; \
            (_addr2) = (likely(!(_regs)->execflag)) ? \
                    PSW_IA((_regs), offset) : \
                    ((_regs)->ET + offset) & ADDRESS_MAXWRAP((_regs)); \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RIS register, immediate, mask, and storage */                /*208*/
#undef RIS
#undef RIS0
#undef RIS_B

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RIS)
 #define RIS(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4) \
         RIS_DECODER(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4, 6, 6)
 #define RIS0(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4) \
         RIS_DECODER(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4, 6, 0)
 #define RIS_B(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4) \
         RIS_DECODER(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4, 0, 0)
#else
 #define RIS(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4) \
         RIS_DECODER_TEST(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4, 6, 6)
 #define RISO(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4) \
         RIS_DECODER_TEST(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4, 6, 0)
 #define RIS_B(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4) \
         RIS_DECODER_TEST(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4, 0, 0)
#endif

#define RIS_DECODER(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr4) = temp & 0xfff; \
            (_b4) = (temp >> 12) & 0xf; \
            if((_b4) != 0) \
            { \
                (_effective_addr4) += (_regs)->GR((_b4)); \
                (_effective_addr4) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_m3) = (temp >> 16) & 0xf; \
            (_r1) = (temp >> 20) & 0xf; \
            (_i2) = (_inst)[4]; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RIS_DECODER_TEST(_inst, _regs, _r1, _i2, _m3, _b4, _effective_addr4, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr4) = temp & 0xfff; \
            (_b4) = (temp >> 12) & 0xf; \
            if((_b4)) { \
                (_effective_addr4) += (_regs)->GR((_b4)); \
                (_effective_addr4) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_m3) = (temp >> 16) & 0xf; \
            (_r1) = (temp >> 20) & 0xf; \
            (_i2) = (_inst)[4]; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* RRS register, immediate, mask, and storage */                /*208*/
#undef RRS
#undef RRS0
#undef RRS_B

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_RRS)
 #define RRS(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4) \
         RRS_DECODER(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4, 6, 6)
 #define RRS0(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4) \
         RRS_DECODER(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4, 6, 0)
 #define RRS_B(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4) \
         RRS_DECODER(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4, 0, 0)
#else
 #define RRS(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4) \
         RRS_DECODER_TEST(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4, 6, 6)
 #define RRS0(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4) \
         RRS_DECODER_TEST(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4, 6, 0)
 #define RRS_B(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4) \
         RRS_DECODER_TEST(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4, 0, 0)
#endif

#define RRS_DECODER(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr4) = temp & 0xfff; \
            (_b4) = (temp >> 12) & 0xf; \
            if((_b4) != 0) \
            { \
                (_effective_addr4) += (_regs)->GR((_b4)); \
                (_effective_addr4) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_r2) = (temp >> 16) & 0xf; \
            (_r1) = (temp >> 20) & 0xf; \
            (_m3) = ((_inst)[4] >> 4) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define RRS_DECODER_TEST(_inst, _regs, _r1, _r2, _m3, _b4, _effective_addr4, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr4) = temp & 0xfff; \
            (_b4) = (temp >> 12) & 0xf; \
            if((_b4)) { \
                (_effective_addr4) += (_regs)->GR((_b4)); \
                (_effective_addr4) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_r2) = (temp >> 16) & 0xf; \
            (_r1) = (temp >> 20) & 0xf; \
            (_m3) = ((_inst)[4] >> 4) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* SI storage and immediate */
#undef SI

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_SI)
 #define SI(_inst, _regs, _i2, _b1, _effective_addr1) \
         SI_DECODER(_inst, _regs, _i2, _b1, _effective_addr1, 4, 4)
#else
 #define SI(_inst, _regs, _i2, _b1, _effective_addr1) \
         SI_DECODER_TEST(_inst, _regs, _i2, _b1, _effective_addr1, 4, 4)
#endif

#define SI_DECODER(_inst, _regs, _i2, _b1, _effective_addr1, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_i2) = (temp >> 16) & 0xff; \
            (_b1) = (temp >> 12) & 0xf; \
            (_effective_addr1) = temp & 0xfff; \
        if((_b1) != 0) \
        { \
        (_effective_addr1) += (_regs)->GR((_b1)); \
        (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define SI_DECODER_TEST(_inst, _regs, _i2, _b1, _effective_addr1, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr1) = temp & 0xfff; \
            (_b1) = (temp >> 12) & 0xf; \
            if((_b1)) { \
                (_effective_addr1) += (_regs)->GR((_b1)); \
                (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_i2) = (temp >> 16) & 0xff; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* SIY storage and immediate with long displacement */
#undef SIY


#define SIY_DECODER_LD(_inst, _regs, _i2, _b1, _effective_addr1, _len, _ilc) \
    {   U32 temp; S32 temp1; \
            temp = fetch_fw(_inst); \
            (_i2) = (temp >> 16) & 0xff; \
            (_b1) = (temp >> 12) & 0xf; \
            temp1 = (_inst[4] << 12) | (temp & 0xfff); \
            if (temp1 & 0x80000) temp1 |= 0xfff00000; \
            (_effective_addr1) = \
                        ((_b1) ? (_regs)->GR((_b1)) : (GREG)0) + \
                        temp1; \
            (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define SIY_DECODER_LD_TEST(_inst, _regs, _i2, _b1, _effective_addr1, _len, _ilc) \
    {   U32 temp; S32 disp; \
            temp = fetch_fw(_inst); \
            (_effective_addr1) = 0; \
            (_b1) = (temp >> 12) & 0xf; \
            if ((_b1)) \
                (_effective_addr1) += (_regs)->GR((_b1)); \
            disp = temp & 0xfff; \
            if (unlikely((_inst)[4])) { \
                disp |= (_inst[4] << 12); \
                if (disp & 0x80000) disp |= 0xfff00000; \
            } \
            (_effective_addr1) += disp; \
            (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
            (_i2) = (temp >> 16) & 0xff; \
    }

/* SIL storage and longer immediate */                          /*208*/
#undef SIL

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_SIL)
 #define SIL(_inst, _regs, _i2, _b1, _effective_addr1) \
         SIL_DECODER(_inst, _regs, _i2, _b1, _effective_addr1, 6, 6)
#else
 #define SIL(_inst, _regs, _i2, _b1, _effective_addr1) \
         SIL_DECODER_TEST(_inst, _regs, _i2, _b1, _effective_addr1, 6, 6)
#endif

#define SIL_DECODER(_inst, _regs, _i2, _b1, _effective_addr1, _len, _ilc) \
    {   U32 temp = fetch_fw(&(_inst)[2]); \
            (_i2) = temp & 0xffff; \
            (_effective_addr1) = (temp >> 16) & 0xfff; \
            (_b1) = (temp >> 28) & 0xf; \
            if((_b1) != 0) \
            { \
                (_effective_addr1) += (_regs)->GR((_b1)); \
                (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define SIL_DECODER_TEST(_inst, _regs, _i2, _b1, _effective_addr1, _len, _ilc) \
    {   U32 temp = fetch_fw(&(_inst)[2]); \
            (_i2) = temp & 0xffff; \
            (_effective_addr1) = (temp >> 16) & 0xfff; \
            (_b1) = (temp >> 28) & 0xf; \
            if((_b1) != 0) \
            { \
                (_effective_addr1) += (_regs)->GR((_b1)); \
                (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* S storage operand only */
#undef S

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_S)
 #define S(_inst, _regs, _b2, _effective_addr2) \
         S_DECODER(_inst, _regs, _b2, _effective_addr2, 4, 4)
#else
 #define S(_inst, _regs, _b2, _effective_addr2) \
         S_DECODER_TEST(_inst, _regs, _b2, _effective_addr2, 4, 4)
#endif

#define S_DECODER(_inst, _regs, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_b2) = (temp >> 12) & 0xf; \
            (_effective_addr2) = temp & 0xfff; \
        if((_b2) != 0) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define S_DECODER_TEST(_inst, _regs, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 12) & 0xf; \
            if((_b2) != 0) { \
                (_effective_addr2) += (_regs)->GR((_b2)); \
                (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* SS storage to storage with two 4-bit L or R fields */
#undef SS

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_SS)
 #define SS(_inst, _regs, _r1, _r3, \
            _b1, _effective_addr1, _b2, _effective_addr2) \
         SS_DECODER(_inst, _regs, _r1, _r3, \
            _b1, _effective_addr1, _b2, _effective_addr2, 6, 6)
#else
 #define SS(_inst, _regs, _r1, _r3, \
            _b1, _effective_addr1, _b2, _effective_addr2) \
         SS_DECODER_TEST(_inst, _regs, _r1, _r3, \
            _b1, _effective_addr1, _b2, _effective_addr2, 6, 6)
#endif

#define SS_DECODER(_inst, _regs, _r1, _r3, \
           _b1, _effective_addr1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r1) = (temp >> 20) & 0xf; \
            (_r3) = (temp >> 16) & 0xf; \
            (_b1) = (temp >> 12) & 0xf; \
            (_effective_addr1) = temp & 0xfff; \
        if((_b1) != 0) \
        { \
        (_effective_addr1) += (_regs)->GR((_b1)); \
        (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
        } \
        (_b2) = (_inst)[4] >> 4; \
        (_effective_addr2) = (((_inst)[4] & 0x0F) << 8) | (_inst)[5]; \
        if((_b2) != 0) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define SS_DECODER_TEST(_inst, _regs, _r1, _r3, \
           _b1, _effective_addr1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp; \
            temp = fetch_fw((_inst)+2); \
            (_effective_addr1) = (temp >> 16) & 0xfff; \
            (_b1) = (temp >> 28); \
            if ((_b1)) { \
                (_effective_addr1) += (_regs)->GR((_b1)); \
                (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 12) & 0xf; \
            if ((_b2)) { \
                (_effective_addr2) += (_regs)->GR((_b2)); \
                (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_r3) = ((_inst)[1]     ) & 0xf; \
            (_r1) = ((_inst)[1] >> 4) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* SS storage to storage with one 8-bit L field */
#undef SS_L

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_SS_L)
 #define SS_L(_inst, _regs, _l, \
              _b1, _effective_addr1, _b2, _effective_addr2) \
         SS_L_DECODER(_inst, _regs, _l, \
              _b1, _effective_addr1, _b2, _effective_addr2, 6, 6)
#else
 #define SS_L(_inst, _regs, _l, \
              _b1, _effective_addr1, _b2, _effective_addr2) \
         SS_L_DECODER_TEST(_inst, _regs, _l, \
              _b1, _effective_addr1, _b2, _effective_addr2, 6, 6)
#endif

#define SS_L_DECODER(_inst, _regs, _l, \
           _b1, _effective_addr1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_l) = (temp >> 16) & 0xff; \
            (_b1) = (temp >> 12) & 0xf; \
            (_effective_addr1) = temp & 0xfff; \
        if((_b1) != 0) \
        { \
        (_effective_addr1) += (_regs)->GR((_b1)); \
        (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
        } \
        (_b2) = (_inst)[4] >> 4; \
        (_effective_addr2) = (((_inst)[4] & 0x0F) << 8) | (_inst)[5]; \
        if((_b2) != 0) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define SS_L_DECODER_TEST(_inst, _regs, _l, \
           _b1, _effective_addr1, _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp; \
            temp = fetch_fw((_inst)+2); \
            (_effective_addr1) = (temp >> 16) & 0xfff; \
            (_b1) = (temp >> 28); \
            if((_b1)) { \
                (_effective_addr1) += (_regs)->GR((_b1)); \
                (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 12) & 0xf; \
            if ((_b2)) { \
                (_effective_addr2) += (_regs)->GR((_b2)); \
                (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_l) = (_inst)[1]; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* SSE storage to storage with extended op code */
#undef SSE

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_SSE)
 #define SSE(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2) \
         SSE_DECODER(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2, 6, 6)
#else
 #define SSE(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2) \
         SSE_DECODER_TEST(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2, 6, 6)
#endif

#define SSE_DECODER(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_b1) = (temp >> 12) & 0xf; \
            (_effective_addr1) = temp & 0xfff; \
        if((_b1) != 0) \
        { \
        (_effective_addr1) += (_regs)->GR((_b1)); \
        (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
        } \
        (_b2) = (_inst)[4] >> 4; \
        (_effective_addr2) = (((_inst)[4] & 0x0F) << 8) | (_inst)[5]; \
        if((_b2) != 0) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define SSE_DECODER_TEST(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2, _len, _ilc) \
    {   U32 temp = fetch_fw((_inst)+2); \
            (_effective_addr1) = (temp >> 16) & 0xfff; \
            (_b1) = (temp >> 28); \
            if((_b1)) { \
                (_effective_addr1) += (_regs)->GR((_b1)); \
                (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 12) & 0xf; \
            if ((_b2)) { \
                (_effective_addr2) += (_regs)->GR((_b2)); \
                (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

/* SSF storage to storage with additional register */
#undef SSF

#if !defined(DECODER_TEST)&&!defined(DECODER_TEST_SSF)
 #define SSF(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2, _r3) \
         SSF_DECODER(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2, _r3, 6, 6)
#else
 #define SSF(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2, _r3) \
         SSF_DECODER_TEST(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2, _r3, 6, 6)
#endif

#define SSF_DECODER(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2, _r3, _len, _ilc) \
    {   U32 temp = fetch_fw(_inst); \
            (_r3) = (temp >> 20) & 0xf; \
            (_b1) = (temp >> 12) & 0xf; \
            (_effective_addr1) = temp & 0xfff; \
        if((_b1) != 0) \
        { \
        (_effective_addr1) += (_regs)->GR((_b1)); \
        (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
        } \
        (_b2) = (_inst)[4] >> 4; \
        (_effective_addr2) = (((_inst)[4] & 0x0F) << 8) | (_inst)[5]; \
        if((_b2) != 0) \
        { \
        (_effective_addr2) += (_regs)->GR((_b2)); \
        (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
        } \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define SSF_DECODER_TEST(_inst, _regs, _b1, _effective_addr1, \
                     _b2, _effective_addr2, _r3, _len, _ilc) \
    {   U32 temp; \
            temp = fetch_fw((_inst)+2); \
            (_effective_addr1) = (temp >> 16) & 0xfff; \
            (_b1) = (temp >> 28); \
            if((_b1)) { \
                (_effective_addr1) += (_regs)->GR((_b1)); \
                (_effective_addr1) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_effective_addr2) = temp & 0xfff; \
            (_b2) = (temp >> 12) & 0xf; \
            if ((_b2)) { \
                (_effective_addr2) += (_regs)->GR((_b2)); \
                (_effective_addr2) &= ADDRESS_MAXWRAP((_regs)); \
            } \
            (_b1) = ((_inst)[1]     ) & 0xf;\
            (_r3) = ((_inst)[1] >> 4) & 0xf; \
            INST_UPDATE_PSW((_regs), (_len), (_ilc)); \
    }

#define PERFORM_SERIALIZATION(_regs) do { } while (0)
#define PERFORM_CHKPT_SYNC(_regs) do { } while (0)

/* Functions in module channel.c */
int  ARCH_DEP(startio) (REGS *regs, DEVBLK *dev, ORB *orb);
void *s370_execute_ccw_chain (DEVBLK *dev);
int  stchan_id (REGS *regs, U16 chan);
int  testch (REGS *regs, U16 chan);
int  testio (REGS *regs, DEVBLK *dev, BYTE ibyte);
int  test_subchan (REGS *regs, DEVBLK *dev, IRB *irb);
int  cancel_subchan (REGS *regs, DEVBLK *dev);
void clear_subchan (REGS *regs, DEVBLK *dev);
int  halt_subchan (REGS *regs, DEVBLK *dev);
int  haltio (REGS *regs, DEVBLK *dev, BYTE ibyte);
int  resume_subchan (REGS *regs, DEVBLK *dev);
int  ARCH_DEP(present_io_interrupt) (REGS *regs, U32 *ioid,
        U32 *ioparm, U32 *iointid, BYTE *csw);
int ARCH_DEP(present_zone_io_interrupt) (U32 *ioid, U32 *ioparm,
                                              U32 *iointid, BYTE zone);
void io_reset (void);
int  chp_reset(REGS *, BYTE chpid);
void channelset_reset(REGS *regs);
DLL_EXPORT int  device_attention (DEVBLK *dev, BYTE unitstat);
DLL_EXPORT int  ARCH_DEP(device_attention) (DEVBLK *dev, BYTE unitstat);


/* Functions in module cpu.c */
/* define all arch_load|store_psw */
/* regardless of current architecture (if any) */
void s370_store_psw (REGS *regs, BYTE *addr);
int  s370_load_psw (REGS *regs, BYTE *addr);
void s370_process_trace (REGS *regs);

int cpu_init (int cpu, REGS *regs, REGS *hostregs);
void ARCH_DEP(perform_io_interrupt) (REGS *regs);
void ARCH_DEP(checkstop_config)(void);
CPU_DLL_IMPORT void (ATTR_REGPARM(2) ARCH_DEP(program_interrupt)) (REGS *regs, int code);
void *cpu_thread (int *cpu);
DLL_EXPORT void copy_psw (REGS *regs, BYTE *addr);
void display_psw (REGS *regs);


/* Functions in module vm.c */
int  ARCH_DEP(diag_devtype) (int r1, int r2, REGS *regs);
int  ARCH_DEP(syncblk_io) (int r1, int r2, REGS *regs);
int  ARCH_DEP(syncgen_io) (int r1, int r2, REGS *regs);
void ARCH_DEP(extid_call) (int r1, int r2, REGS *regs);
int  ARCH_DEP(cpcmd_call) (int r1, int r2, REGS *regs);
void ARCH_DEP(pseudo_timer) (U32 code, int r1, int r2, REGS *regs);
void ARCH_DEP(access_reipl_data) (int r1, int r2, REGS *regs);
int  ARCH_DEP(diag_ppagerel) (int r1, int r2, REGS *regs);
void ARCH_DEP(vm_info) (int r1, int r2, REGS *regs);
int  ARCH_DEP(device_info) (int r1, int r2, REGS *regs);


/* Functions in module vmd250.c */
int  ARCH_DEP(vm_blockio) (int r1, int r2, REGS *regs);


/* Functions in module decimal.c */
void packed_to_binary (BYTE *dec, int len, U64 *result,
    int *ovf, int *dxf);
void binary_to_packed (S64 bin, BYTE *result);


/* Functions in module diagnose.c */
void ARCH_DEP(diagnose_call) (VADR effective_addr2, int b2, int r1, int r3,
    REGS *regs);


/* Functions in module diagmssf.c */
void ARCH_DEP(scpend_call) (void);
int  ARCH_DEP(mssf_call) (int r1, int r2, REGS *regs);
//void ARCH_DEP(diag204_call) (int r1, int r2, REGS *regs);
//void ARCH_DEP(diag224_call) (int r1, int r2, REGS *regs);


/* Functions in module external.c */
void ARCH_DEP(perform_external_interrupt) (REGS *regs);
void ARCH_DEP(store_status) (REGS *ssreg, RADR aaddr);
void store_status (REGS *ssreg, U64 aaddr);


/* Functions in module ipl.c */
int          load_ipl           (U16 lcss, U16  devnum, int cpu, int clear);
int ARCH_DEP(load_ipl)          (U16 lcss, U16  devnum, int cpu, int clear);
int          system_reset       (             int cpu, int clear);
int ARCH_DEP(system_reset)      (             int cpu, int clear);
int          cpu_reset          (REGS *regs);
int ARCH_DEP(cpu_reset)         (REGS *regs);
int          initial_cpu_reset  (REGS *regs);
int ARCH_DEP(initial_cpu_reset) (REGS *regs);
int ARCH_DEP(common_load_begin)  (int cpu, int clear);
int ARCH_DEP(common_load_finish) (REGS *regs);
void storage_clear(void);
void xstorage_clear(void);


/* Functions in module scedasd.c */
void         set_sce_dir        (char *path);
char        *get_sce_dir        ();
int          load_main          (char *fname, RADR startloc);
int ARCH_DEP(load_main)         (char *fname, RADR startloc);
int          load_hmc           (char *fname, int cpu, int clear);
int ARCH_DEP(load_hmc)          (char *fname, int cpu, int clear);
void ARCH_DEP(sclp_scedio_request) (SCCB_HEADER *);
void ARCH_DEP(sclp_scedio_event) (SCCB_HEADER *);


/* Functions in module machchk.c */
int  ARCH_DEP(present_mck_interrupt) (REGS *regs, U64 *mcic, U32 *xdmg,
    RADR *fsta);
U32  channel_report (REGS *);
void machine_check_crwpend (void);
void ARCH_DEP(sync_mck_interrupt) (REGS *regs);
void sigabend_handler (int signo);


/* Functions in module opcode.c */
OPC_DLL_IMPORT void copy_opcode_tables ();
void set_opcode_pointers (REGS *regs);


/* Functions in module panel.c */
void ARCH_DEP(display_inst) (REGS *regs, BYTE *inst);
void display_inst (REGS *regs, BYTE *inst);


/* Functions in module sie.c */
void ARCH_DEP(sie_exit) (REGS *regs, int code);
void ARCH_DEP(diagnose_002) (REGS *regs, int r1, int r3);


/* Functions in module stack.c */
void ARCH_DEP(trap_x) (int trap_is_trap4, REGS *regs, U32 trap_operand);
void ARCH_DEP(form_stack_entry) (BYTE etype, VADR retna, VADR calla,
    U32 csi, U32 pcnum, REGS *regs);
VADR ARCH_DEP(locate_stack_entry) (int prinst, LSED *lsedptr,
    REGS *regs);
void ARCH_DEP(stack_modify) (VADR lsea, U32 m1, U32 m2, REGS *regs);
void ARCH_DEP(stack_extract) (VADR lsea, int r1, int code, REGS *regs);
void ARCH_DEP(unstack_registers) (int gtype, VADR lsea, int r1,
    int r2, REGS *regs);
int  ARCH_DEP(program_return_unstack) (REGS *regs, RADR *lsedap, int *rc);


/* Functions in module trace.c */
CREG  ARCH_DEP(trace_br) (int amode, VADR ia, REGS *regs);
CREG  ARCH_DEP(trace_bsg) (U32 alet, VADR ia, REGS *regs);
CREG  ARCH_DEP(trace_ssar) (int ssair, U16 sasn, REGS *regs);
CREG  ARCH_DEP(trace_pc) (U32 pcea, REGS *regs);
CREG  ARCH_DEP(trace_pr) (REGS *newregs, REGS *regs);
CREG  ARCH_DEP(trace_pt) (int pti, U16 pasn, GREG gpr2, REGS *regs);
CREG  ARCH_DEP(trace_tr) (int r1, int r3, U32 op, REGS *regs);
CREG  ARCH_DEP(trace_tg) (int r1, int r3, U32 op, REGS *regs);
CREG  ARCH_DEP(trace_ms) (int br_ind, VADR ia, REGS *regs);


/* Functions in module plo.c */
int ARCH_DEP(plo_cl) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_clg) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_clgr) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_clx) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_cs) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csg) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csgr) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csx) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_dcs) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_dcsg) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_dcsgr) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_dcsx) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csst) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csstg) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csstgr) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csstx) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csdst) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csdstg) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csdstgr) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_csdstx) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_cstst) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_cststg) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_cststgr) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);
int ARCH_DEP(plo_cststx) (int r1, int r3, VADR effective_addr2, int b2,
                            VADR effective_addr4, int b4,  REGS *regs);


/* Instruction functions in opcode.c */
DEF_INST(operation_exception);
DEF_INST(dummy_instruction);


/* Instructions in control.c */
DEF_INST(diagnose);
DEF_INST(insert_storage_key);
DEF_INST(load_program_status_word);
DEF_INST(load_using_real_address);
DEF_INST(lock_page);
DEF_INST(modify_stacked_state);
DEF_INST(move_with_destination_key);
DEF_INST(move_with_optional_specifications);                    /*208*/
DEF_INST(move_with_source_key);
DEF_INST(program_call);
DEF_INST(program_return);
DEF_INST(program_transfer);
DEF_INST(program_transfer_with_instance);
DEF_INST(purge_accesslist_lookaside_buffer);
DEF_INST(purge_translation_lookaside_buffer);
DEF_INST(reset_reference_bit);
DEF_INST(reset_reference_bit_extended);
DEF_INST(set_address_space_control);
DEF_INST(set_address_space_control_fast);
DEF_INST(set_clock);
DEF_INST(set_clock_comparator);
DEF_INST(set_clock_programmable_field);
DEF_INST(set_cpu_timer);
DEF_INST(set_prefix);
DEF_INST(set_psw_key_from_address);
DEF_INST(set_secondary_asn);
DEF_INST(set_secondary_asn_with_instance);
DEF_INST(set_storage_key);
DEF_INST(set_storage_key_extended);
DEF_INST(set_system_mask);
DEF_INST(store_clock_comparator);
DEF_INST(store_control);
DEF_INST(store_cpu_address);
DEF_INST(store_cpu_id);
DEF_INST(store_cpu_timer);
DEF_INST(store_prefix);
DEF_INST(store_system_information);
DEF_INST(store_then_and_system_mask);
DEF_INST(store_then_or_system_mask);
DEF_INST(store_using_real_address);
DEF_INST(test_access);
DEF_INST(test_block);
DEF_INST(test_protection);
DEF_INST(trace);


/* Instructions in decimal.c */
DEF_INST(add_decimal);
DEF_INST(compare_decimal);
DEF_INST(divide_decimal);
DEF_INST(edit_x_edit_and_mark);
DEF_INST(multiply_decimal);
DEF_INST(subtract_decimal);
DEF_INST(zero_and_add);
DEF_INST(test_decimal);


/* Instructions in vm.c */
DEF_INST(inter_user_communication_vehicle);


/* Instructions in sie.c */
DEF_INST(start_interpretive_execution);
DEF_INST(store_zone_parameter);
DEF_INST(set_zone_parameter);
DEF_INST(test_pending_zone_interrupt);


/* Instructions in qdio.c */
DEF_INST(signal_adapter);


/* Instructions in float.c */
DEF_INST(load_positive_float_long_reg);
DEF_INST(load_negative_float_long_reg);
DEF_INST(load_and_test_float_long_reg);
DEF_INST(load_complement_float_long_reg);
DEF_INST(halve_float_long_reg);
DEF_INST(load_rounded_float_long_reg);
DEF_INST(multiply_float_ext_reg);
DEF_INST(multiply_float_long_to_ext_reg);
DEF_INST(load_float_long_reg);
DEF_INST(compare_float_long_reg);
DEF_INST(add_float_long_reg);
DEF_INST(subtract_float_long_reg);
DEF_INST(multiply_float_long_reg);
DEF_INST(divide_float_long_reg);
DEF_INST(add_unnormal_float_long_reg);
DEF_INST(subtract_unnormal_float_long_reg);
DEF_INST(load_positive_float_short_reg);
DEF_INST(load_negative_float_short_reg);
DEF_INST(load_and_test_float_short_reg);
DEF_INST(load_complement_float_short_reg);
DEF_INST(halve_float_short_reg);
DEF_INST(load_rounded_float_short_reg);
DEF_INST(add_float_ext_reg);
DEF_INST(subtract_float_ext_reg);
DEF_INST(load_float_short_reg);
DEF_INST(compare_float_short_reg);
DEF_INST(add_float_short_reg);
DEF_INST(subtract_float_short_reg);
DEF_INST(multiply_float_short_to_long_reg);
DEF_INST(divide_float_short_reg);
DEF_INST(add_unnormal_float_short_reg);
DEF_INST(subtract_unnormal_float_short_reg);
DEF_INST(store_float_long);
DEF_INST(multiply_float_long_to_ext);
DEF_INST(load_float_long);
DEF_INST(compare_float_long);
DEF_INST(add_float_long);
DEF_INST(subtract_float_long);
DEF_INST(multiply_float_long);
DEF_INST(divide_float_long);
DEF_INST(add_unnormal_float_long);
DEF_INST(subtract_unnormal_float_long);
DEF_INST(store_float_short);
DEF_INST(load_float_short);
DEF_INST(compare_float_short);
DEF_INST(add_float_short);
DEF_INST(subtract_float_short);
DEF_INST(multiply_float_short_to_long);
DEF_INST(divide_float_short);
DEF_INST(add_unnormal_float_short);
DEF_INST(subtract_unnormal_float_short);
DEF_INST(multiply_float_short_reg);
DEF_INST(load_fp_int_float_short_reg);
DEF_INST(load_fp_int_float_long_reg);
DEF_INST(convert_fixed_to_float_short_reg);
DEF_INST(convert_fixed_to_float_long_reg);
DEF_INST(convert_fixed_to_float_ext_reg);
DEF_INST(convert_fix64_to_float_short_reg);
DEF_INST(convert_fix64_to_float_long_reg);
DEF_INST(convert_fix64_to_float_ext_reg);
DEF_INST(convert_float_short_to_fixed_reg);
DEF_INST(convert_float_long_to_fixed_reg);
DEF_INST(convert_float_ext_to_fixed_reg);
DEF_INST(convert_float_short_to_fix64_reg); /* under construction! Bernard van der Helm */
DEF_INST(convert_float_long_to_fix64_reg); /* under construction! Bernard van der Helm */
DEF_INST(convert_float_ext_to_fix64_reg); /* under construction! Bernard van der Helm */
DEF_INST(load_lengthened_float_short_to_long);
DEF_INST(load_lengthened_float_long_to_ext);
DEF_INST(load_lengthened_float_short_to_ext);
DEF_INST(squareroot_float_short);
DEF_INST(squareroot_float_long);
DEF_INST(multiply_float_short);
DEF_INST(load_float_ext_reg);
DEF_INST(load_zero_float_short_reg);
DEF_INST(load_zero_float_long_reg);
DEF_INST(load_zero_float_ext_reg);
DEF_INST(multiply_add_float_short_reg);
DEF_INST(multiply_add_float_long_reg);
DEF_INST(multiply_add_float_short);
DEF_INST(multiply_add_float_long);
DEF_INST(multiply_subtract_float_short_reg);
DEF_INST(multiply_subtract_float_long_reg);
DEF_INST(multiply_subtract_float_short);
DEF_INST(multiply_subtract_float_long);
DEF_INST(multiply_unnormal_float_long_to_ext_reg);              /*@Z9*/
DEF_INST(multiply_unnormal_float_long_to_ext_low_reg);          /*@Z9*/
DEF_INST(multiply_unnormal_float_long_to_ext_high_reg);         /*@Z9*/
DEF_INST(multiply_add_unnormal_float_long_to_ext_reg);          /*@Z9*/
DEF_INST(multiply_add_unnormal_float_long_to_ext_low_reg);      /*@Z9*/
DEF_INST(multiply_add_unnormal_float_long_to_ext_high_reg);     /*@Z9*/
DEF_INST(multiply_unnormal_float_long_to_ext);                  /*@Z9*/
DEF_INST(multiply_unnormal_float_long_to_ext_low);              /*@Z9*/
DEF_INST(multiply_unnormal_float_long_to_ext_high);             /*@Z9*/
DEF_INST(multiply_add_unnormal_float_long_to_ext);              /*@Z9*/
DEF_INST(multiply_add_unnormal_float_long_to_ext_low);          /*@Z9*/
DEF_INST(multiply_add_unnormal_float_long_to_ext_high);         /*@Z9*/
DEF_INST(load_float_long_y);
DEF_INST(load_float_short_y);
DEF_INST(store_float_long_y);
DEF_INST(store_float_short_y);


/* Instructions in general1.c */
DEF_INST(add_register);
DEF_INST(add);
DEF_INST(add_halfword);
DEF_INST(add_halfword_immediate);
DEF_INST(add_logical_register);
DEF_INST(add_logical);
DEF_INST(and_register);
DEF_INST(and);
DEF_INST(and_immediate);
DEF_INST(and_character);
DEF_INST(branch_and_link_register);
DEF_INST(branch_and_link);
DEF_INST(branch_on_condition_register);
DEF_INST(branch_on_condition);
DEF_INST(branch_on_count_register);
DEF_INST(branch_on_count);
DEF_INST(branch_on_index_high);
DEF_INST(branch_on_index_low_or_equal);
DEF_INST(branch_relative_on_condition);
DEF_INST(branch_relative_and_save);
DEF_INST(branch_relative_on_count);
DEF_INST(branch_relative_on_index_high);
DEF_INST(branch_relative_on_index_low_or_equal);
DEF_INST(checksum);
DEF_INST(compare_register);
DEF_INST(compare);
DEF_INST(compare_and_form_codeword);
DEF_INST(compare_and_swap);
DEF_INST(compare_and_swap_and_store);
DEF_INST(compare_halfword);
DEF_INST(compare_halfword_immediate);
DEF_INST(compare_logical_register);
DEF_INST(compare_logical);
DEF_INST(compare_logical_immediate);
DEF_INST(compare_logical_character);
DEF_INST(compare_logical_character_long);
DEF_INST(compare_logical_long_extended);
DEF_INST(compare_logical_string);
DEF_INST(compare_until_substring_equal);
DEF_INST(convert_utf16_to_utf8);
DEF_INST(convert_utf16_to_utf32);
DEF_INST(convert_utf32_to_utf16);
DEF_INST(convert_utf32_to_utf8);
DEF_INST(convert_utf8_to_utf16);
DEF_INST(convert_utf8_to_utf32);
DEF_INST(convert_to_binary);
DEF_INST(convert_to_decimal);
DEF_INST(copy_access);
DEF_INST(divide_register);
DEF_INST(divide);
DEF_INST(exclusive_or_register);
DEF_INST(exclusive_or);
DEF_INST(exclusive_or_immediate);
DEF_INST(exclusive_or_character);
DEF_INST(execute);
DEF_INST(execute_relative_long);                                /*208*/
DEF_INST(extract_access_register);
DEF_INST(insert_character);
DEF_INST(insert_program_mask);
DEF_INST(load);
DEF_INST(load_register);
DEF_INST(load_access_multiple);
DEF_INST(load_address);
DEF_INST(load_address_extended);
DEF_INST(load_and_test_register);
DEF_INST(load_complement_register);
DEF_INST(load_halfword);
DEF_INST(load_halfword_immediate);
DEF_INST(load_multiple);
DEF_INST(load_negative_register);
DEF_INST(load_positive_register);
DEF_INST(monitor_call);
DEF_INST(move_immediate);
DEF_INST(move_character);
DEF_INST(move_inverse);
DEF_INST(move_long);
DEF_INST(move_long_extended);
DEF_INST(move_numerics);
DEF_INST(move_string);
DEF_INST(move_with_offset);
DEF_INST(move_zones);
DEF_INST(multiply_register);
DEF_INST(multiply);
DEF_INST(multiply_halfword);
DEF_INST(multiply_halfword_immediate);
DEF_INST(multiply_single_register);
DEF_INST(multiply_single);


/* Instructions in general2.c */
DEF_INST(or_register);
DEF_INST(or);
DEF_INST(or_immediate);
DEF_INST(or_character);
DEF_INST(pack);
DEF_INST(search_string);
DEF_INST(set_access_register);
DEF_INST(set_program_mask);
DEF_INST(shift_left_double);
DEF_INST(shift_left_double_logical);
DEF_INST(shift_left_single);
DEF_INST(shift_left_single_logical);
DEF_INST(shift_right_double);
DEF_INST(shift_right_double_logical);
DEF_INST(shift_right_single);
DEF_INST(shift_right_single_logical);
DEF_INST(store);
DEF_INST(store_access_multiple);
DEF_INST(store_character);
DEF_INST(store_clock);
DEF_INST(store_clock_extended);
DEF_INST(store_clock_fast);                                     /*@Z9*/
DEF_INST(store_halfword);
DEF_INST(store_multiple);
DEF_INST(subtract_register);
DEF_INST(subtract);
DEF_INST(subtract_halfword);
DEF_INST(subtract_logical_register);
DEF_INST(subtract_logical);
DEF_INST(supervisor_call);
DEF_INST(test_and_set);
DEF_INST(test_under_mask);
DEF_INST(test_under_mask_high);
DEF_INST(test_under_mask_low);
DEF_INST(translate);
DEF_INST(translate_and_test);
DEF_INST(translate_extended);
DEF_INST(unpack);
DEF_INST(update_tree);


/* Instructions in general3.c */
DEF_INST(add_immediate_long_storage);                           /*208*/
DEF_INST(add_immediate_storage);                                /*208*/
DEF_INST(add_logical_with_signed_immediate);                    /*208*/
DEF_INST(add_logical_with_signed_immediate_long);               /*208*/
DEF_INST(compare_and_branch_register);                          /*208*/
DEF_INST(compare_and_branch_long_register);                     /*208*/
DEF_INST(compare_and_branch_relative_register);                 /*208*/
DEF_INST(compare_and_branch_relative_long_register);            /*208*/
DEF_INST(compare_and_trap_long_register);                       /*208*/
DEF_INST(compare_and_trap_register);                            /*208*/
DEF_INST(compare_halfword_immediate_halfword_storage);          /*208*/
DEF_INST(compare_halfword_immediate_long_storage);              /*208*/
DEF_INST(compare_halfword_immediate_storage);                   /*208*/
DEF_INST(compare_halfword_long);                                /*208*/
DEF_INST(compare_halfword_relative_long);                       /*208*/
DEF_INST(compare_halfword_relative_long_long);                  /*208*/
DEF_INST(compare_immediate_and_branch);                         /*208*/
DEF_INST(compare_immediate_and_branch_long);                    /*208*/
DEF_INST(compare_immediate_and_branch_relative);                /*208*/
DEF_INST(compare_immediate_and_branch_relative_long);           /*208*/
DEF_INST(compare_immediate_and_trap);                           /*208*/
DEF_INST(compare_immediate_and_trap_long);                      /*208*/
DEF_INST(compare_logical_and_branch_long_register);             /*208*/
DEF_INST(compare_logical_and_branch_register);                  /*208*/
DEF_INST(compare_logical_and_branch_relative_long_register);    /*208*/
DEF_INST(compare_logical_and_branch_relative_register);         /*208*/
DEF_INST(compare_logical_and_trap_long_register);               /*208*/
DEF_INST(compare_logical_and_trap_register);                    /*208*/
DEF_INST(compare_logical_immediate_and_branch);                 /*208*/
DEF_INST(compare_logical_immediate_and_branch_long);            /*208*/
DEF_INST(compare_logical_immediate_and_branch_relative);        /*208*/
DEF_INST(compare_logical_immediate_and_branch_relative_long);   /*208*/
DEF_INST(compare_logical_immediate_and_trap_fullword);          /*208*/
DEF_INST(compare_logical_immediate_and_trap_long);              /*208*/
DEF_INST(compare_logical_immediate_fullword_storage);           /*208*/
DEF_INST(compare_logical_immediate_halfword_storage);           /*208*/
DEF_INST(compare_logical_immediate_long_storage);               /*208*/
DEF_INST(compare_logical_relative_long);                        /*208*/
DEF_INST(compare_logical_relative_long_halfword);               /*208*/
DEF_INST(compare_logical_relative_long_long);                   /*208*/
DEF_INST(compare_logical_relative_long_long_fullword);          /*208*/
DEF_INST(compare_logical_relative_long_long_halfword);          /*208*/
DEF_INST(compare_relative_long);                                /*208*/
DEF_INST(compare_relative_long_long);                           /*208*/
DEF_INST(compare_relative_long_long_fullword);                  /*208*/
DEF_INST(extract_cache_attribute);                              /*208*/
DEF_INST(load_address_extended_y);                              /*208*/
DEF_INST(load_and_test_long_fullword);                          /*208*/
DEF_INST(load_halfword_relative_long);                          /*208*/
DEF_INST(load_halfword_relative_long_long);                     /*208*/
DEF_INST(load_logical_halfword_relative_long);                  /*208*/
DEF_INST(load_logical_halfword_relative_long_long);             /*208*/
DEF_INST(load_logical_relative_long_long_fullword);             /*208*/
DEF_INST(load_relative_long);                                   /*208*/
DEF_INST(load_relative_long_long);                              /*208*/
DEF_INST(load_relative_long_long_fullword);                     /*208*/
DEF_INST(move_fullword_from_halfword_immediate);                /*208*/
DEF_INST(move_halfword_from_halfword_immediate);                /*208*/
DEF_INST(move_long_from_halfword_immediate);                    /*208*/
DEF_INST(multiply_halfword_y);                                  /*208*/
DEF_INST(multiply_single_immediate_fullword);                   /*208*/
DEF_INST(multiply_single_immediate_long_fullword);              /*208*/
DEF_INST(multiply_y);                                           /*208*/
DEF_INST(prefetch_data);                                        /*208*/
DEF_INST(prefetch_data_relative_long);                          /*208*/
DEF_INST(rotate_then_and_selected_bits_long_reg);               /*208*/
DEF_INST(rotate_then_exclusive_or_selected_bits_long_reg);      /*208*/
DEF_INST(rotate_then_insert_selected_bits_long_reg);            /*208*/
DEF_INST(rotate_then_or_selected_bits_long_reg);                /*208*/
DEF_INST(store_halfword_relative_long);                         /*208*/
DEF_INST(store_relative_long);                                  /*208*/
DEF_INST(store_relative_long_long);                             /*208*/


/* Instructions in io.c */
DEF_INST(clear_subchannel);
DEF_INST(halt_subchannel);
DEF_INST(modify_subchannel);
DEF_INST(resume_subchannel);
DEF_INST(set_address_limit);
DEF_INST(set_channel_monitor);
DEF_INST(reset_channel_path);
DEF_INST(start_subchannel);
DEF_INST(cancel_subchannel);
DEF_INST(store_channel_path_status);
DEF_INST(store_channel_report_word);
DEF_INST(store_subchannel);
DEF_INST(test_pending_interruption);
DEF_INST(test_subchannel);
DEF_INST(start_io);
DEF_INST(test_io);
DEF_INST(halt_io);
DEF_INST(test_channel);
DEF_INST(store_channel_id);
DEF_INST(connect_channel_set);
DEF_INST(disconnect_channel_set);


/* Instructions in service.c */
DEF_INST(service_call);


/* Instructions in chsc.c */
DEF_INST(channel_subsystem_call);


/* Instructions in xstore.c */
DEF_INST(page_in);
DEF_INST(page_out);
DEF_INST(move_page);
DEF_INST(invalidate_expanded_storage_block_entry);


/* Instructions in vector.c */
DEF_INST(v_test_vmr);
DEF_INST(v_complement_vmr);
DEF_INST(v_count_left_zeros_in_vmr);
DEF_INST(v_count_ones_in_vmr);
DEF_INST(v_extract_vct);
DEF_INST(v_extract_vector_modes);
DEF_INST(v_restore_vr);
DEF_INST(v_save_changed_vr);
DEF_INST(v_save_vr);
DEF_INST(v_load_vmr);
DEF_INST(v_load_vmr_complement);
DEF_INST(v_store_vmr);
DEF_INST(v_and_to_vmr);
DEF_INST(v_or_to_vmr);
DEF_INST(v_exclusive_or_to_vmr);
DEF_INST(v_save_vsr);
DEF_INST(v_save_vmr);
DEF_INST(v_restore_vsr);
DEF_INST(v_restore_vmr);
DEF_INST(v_load_vct_from_address);
DEF_INST(v_clear_vr);
DEF_INST(v_set_vector_mask_mode);
DEF_INST(v_load_vix_from_address);
DEF_INST(v_store_vector_parameters);
DEF_INST(v_save_vac);
DEF_INST(v_restore_vac);


/* Instructions in esame.c */
DEF_INST(store_fpc);
DEF_INST(load_fpc);
DEF_INST(set_fpc);
DEF_INST(extract_fpc);
DEF_INST(set_bfp_rounding_mode);
DEF_INST(trap2);
DEF_INST(trap4);
DEF_INST(resume_program);
DEF_INST(trace_long);
DEF_INST(convert_to_binary_long);
DEF_INST(convert_to_decimal_long);
DEF_INST(multiply_logical);
DEF_INST(multiply_logical_long);
DEF_INST(multiply_logical_register);
DEF_INST(multiply_logical_long_register);
DEF_INST(divide_logical);
DEF_INST(divide_logical_long);
DEF_INST(divide_logical_register);
DEF_INST(divide_logical_long_register);
DEF_INST(add_logical_carry_long_register);
DEF_INST(subtract_logical_borrow_long_register);
DEF_INST(add_logical_carry_long);
DEF_INST(subtract_logical_borrow_long);
DEF_INST(add_logical_carry_register);
DEF_INST(subtract_logical_borrow_register);
DEF_INST(add_logical_carry);
DEF_INST(subtract_logical_borrow);
DEF_INST(divide_single_long);
DEF_INST(divide_single_long_fullword);
DEF_INST(divide_single_long_register);
DEF_INST(divide_single_long_fullword_register);
DEF_INST(load_logical_long_character);
DEF_INST(load_logical_long_halfword);
DEF_INST(store_pair_to_quadword);
DEF_INST(load_pair_from_quadword);
DEF_INST(extract_stacked_registers_long);
DEF_INST(extract_psw);
DEF_INST(extract_and_set_extended_authority);
DEF_INST(load_address_relative_long);
DEF_INST(perform_frame_management_function);                    /*208*/
DEF_INST(perform_timing_facility_function);                     /*@Z9*/
DEF_INST(perform_topology_function);                            /*208*/
DEF_INST(store_facility_list);
DEF_INST(store_facility_list_extended);                         /*@Z9*/
DEF_INST(load_long_halfword_immediate);
DEF_INST(add_long_halfword_immediate);
DEF_INST(multiply_long_halfword_immediate);
DEF_INST(compare_long_halfword_immediate);
DEF_INST(and_long);
DEF_INST(or_long);
DEF_INST(exclusive_or_long);
DEF_INST(and_long_register);
DEF_INST(or_long_register);
DEF_INST(exclusive_or_long_register);
DEF_INST(load_long_register);
DEF_INST(add_logical_long_register);
DEF_INST(add_logical_long_fullword_register);
DEF_INST(subtract_logical_long_register);
DEF_INST(subtract_logical_long_fullword_register);
DEF_INST(store_control_long);
DEF_INST(load_multiple_high);
DEF_INST(load_multiple_long);
DEF_INST(store_multiple_high);
DEF_INST(store_multiple_long);
DEF_INST(load_using_real_address_long);
DEF_INST(store_using_real_address_long);
DEF_INST(test_addressing_mode);
DEF_INST(set_addressing_mode_24);
DEF_INST(set_addressing_mode_31);
DEF_INST(set_addressing_mode_64);
DEF_INST(load_program_status_word_extended);
DEF_INST(store_long);
DEF_INST(store_real_address);
DEF_INST(load_long);
DEF_INST(multiply_single_long_register);
DEF_INST(multiply_single_long_fullword_register);
DEF_INST(multiply_single_long);
DEF_INST(multiply_single_long_fullword);
DEF_INST(rotate_left_single_logical_long);
DEF_INST(rotate_left_single_logical);
DEF_INST(shift_right_single_long);
DEF_INST(shift_left_single_long);
DEF_INST(shift_right_single_logical_long);
DEF_INST(shift_left_single_logical_long);
DEF_INST(compare_logical_long);
DEF_INST(compare_logical_long_fullword);
DEF_INST(compare_logical_long_fullword_register);
DEF_INST(load_logical_long_thirtyone_register);
DEF_INST(compare_logical_long_register);
DEF_INST(test_under_mask_high_high);
DEF_INST(test_under_mask_high_low);
DEF_INST(branch_relative_on_count_long);
DEF_INST(load_positive_long_register);
DEF_INST(load_negative_long_register);
DEF_INST(load_and_test_long_register);
DEF_INST(load_complement_long_register);
DEF_INST(load_long_fullword_register);
DEF_INST(add_long_register);
DEF_INST(add_long_fullword_register);
DEF_INST(subtract_long_register);
DEF_INST(subtract_long_fullword_register);
DEF_INST(add_logical_long);
DEF_INST(add_logical_long_fullword);
DEF_INST(add_long);
DEF_INST(add_long_fullword);
DEF_INST(subtract_logical_long);
DEF_INST(subtract_logical_long_fullword);
DEF_INST(subtract_long);
DEF_INST(subtract_long_fullword);
DEF_INST(compare_long_register);
DEF_INST(compare_long);
DEF_INST(branch_on_count_long_register);
DEF_INST(branch_on_count_long);
DEF_INST(compare_and_swap_long);
DEF_INST(branch_on_index_high_long);
DEF_INST(branch_on_index_low_or_equal_long);
DEF_INST(branch_relative_on_index_high_long);
DEF_INST(branch_relative_on_index_low_or_equal_long);
DEF_INST(branch_relative_on_condition_long);
DEF_INST(branch_relative_and_save_long);
DEF_INST(compare_long_fullword_register);
DEF_INST(load_positive_long_fullword_register);
DEF_INST(load_negative_long_fullword_register);
DEF_INST(load_and_test_long_fullword_register);
DEF_INST(load_complement_long_fullword_register);
DEF_INST(load_long_fullword);
DEF_INST(load_long_halfword);
DEF_INST(compare_long_fullword);
DEF_INST(load_logical_long_fullword_register);
DEF_INST(load_logical_long_fullword);
DEF_INST(load_logical_long_thirtyone);
DEF_INST(insert_immediate_high_high);
DEF_INST(insert_immediate_high_low);
DEF_INST(insert_immediate_low_high);
DEF_INST(insert_immediate_low_low);
DEF_INST(and_immediate_high_high);
DEF_INST(and_immediate_high_low);
DEF_INST(and_immediate_low_high);
DEF_INST(and_immediate_low_low);
DEF_INST(or_immediate_high_high);
DEF_INST(or_immediate_high_low);
DEF_INST(or_immediate_low_high);
DEF_INST(or_immediate_low_low);
DEF_INST(load_logical_immediate_high_high);
DEF_INST(load_logical_immediate_high_low);
DEF_INST(load_logical_immediate_low_high);
DEF_INST(load_logical_immediate_low_low);
DEF_INST(load_reversed_long_register);
DEF_INST(load_reversed_register);
DEF_INST(load_reversed_long);
DEF_INST(load_reversed);
DEF_INST(load_reversed_half);
DEF_INST(store_reversed_long);
DEF_INST(store_reversed);
DEF_INST(store_reversed_half);
DEF_INST(translate_two_to_two);
DEF_INST(translate_two_to_one);
DEF_INST(translate_one_to_two);
DEF_INST(translate_one_to_one);
DEF_INST(add_y);
DEF_INST(add_halfword_y);
DEF_INST(add_logical_y);
DEF_INST(and_immediate_y);
DEF_INST(and_y);
DEF_INST(compare_y);
DEF_INST(compare_and_swap_y);
DEF_INST(compare_halfword_y);
DEF_INST(compare_logical_y);
DEF_INST(compare_logical_immediate_y);
DEF_INST(convert_to_binary_y);
DEF_INST(convert_to_decimal_y);
DEF_INST(exclusive_or_immediate_y);
DEF_INST(exclusive_or_y);
DEF_INST(insert_character_y);
DEF_INST(load_y);
DEF_INST(load_access_multiple_y);
DEF_INST(load_address_y);
DEF_INST(load_byte);
DEF_INST(load_byte_long);
DEF_INST(load_halfword_y);
DEF_INST(load_multiple_y);
DEF_INST(move_immediate_y);
DEF_INST(multiply_single_y);
DEF_INST(or_immediate_y);
DEF_INST(or_y);
DEF_INST(store_y);
DEF_INST(store_access_multiple_y);
DEF_INST(store_character_y);
DEF_INST(store_halfword_y);
DEF_INST(store_multiple_y);
DEF_INST(subtract_y);
DEF_INST(subtract_halfword_y);
DEF_INST(subtract_logical_y);
DEF_INST(test_under_mask_y);
DEF_INST(compare_and_swap_and_purge_long);
DEF_INST(invalidate_dat_table_entry);
DEF_INST(load_page_table_entry_address);                        /*@Z9*/
DEF_INST(add_fullword_immediate);                               /*@Z9*/
DEF_INST(add_long_fullword_immediate);                          /*@Z9*/
DEF_INST(add_logical_fullword_immediate);                       /*@Z9*/
DEF_INST(add_logical_long_fullword_immediate);                  /*@Z9*/
DEF_INST(and_immediate_high_fullword);                          /*@Z9*/
DEF_INST(and_immediate_low_fullword);                           /*@Z9*/
DEF_INST(compare_fullword_immediate);                           /*@Z9*/
DEF_INST(compare_long_fullword_immediate);                      /*@Z9*/
DEF_INST(compare_logical_fullword_immediate);                   /*@Z9*/
DEF_INST(compare_logical_long_fullword_immediate);              /*@Z9*/
DEF_INST(exclusive_or_immediate_high_fullword);                 /*@Z9*/
DEF_INST(exclusive_or_immediate_low_fullword);                  /*@Z9*/
DEF_INST(insert_immediate_high_fullword);                       /*@Z9*/
DEF_INST(insert_immediate_low_fullword);                        /*@Z9*/
DEF_INST(load_long_fullword_immediate);                         /*@Z9*/
DEF_INST(load_logical_immediate_high_fullword);                 /*@Z9*/
DEF_INST(load_logical_immediate_low_fullword);                  /*@Z9*/
DEF_INST(or_immediate_high_fullword);                           /*@Z9*/
DEF_INST(or_immediate_low_fullword);                            /*@Z9*/
DEF_INST(subtract_logical_fullword_immediate);                  /*@Z9*/
DEF_INST(subtract_logical_long_fullword_immediate);             /*@Z9*/
DEF_INST(load_and_test);                                        /*@Z9*/
DEF_INST(load_and_test_long);                                   /*@Z9*/
DEF_INST(load_byte_register);                                   /*@Z9*/
DEF_INST(load_long_byte_register);                              /*@Z9*/
DEF_INST(load_halfword_register);                               /*@Z9*/
DEF_INST(load_long_halfword_register);                          /*@Z9*/
DEF_INST(load_logical_character);                               /*@Z9*/
DEF_INST(load_logical_character_register);                      /*@Z9*/
DEF_INST(load_logical_long_character_register);                 /*@Z9*/
DEF_INST(load_logical_halfword);                                /*@Z9*/
DEF_INST(load_logical_halfword_register);                       /*@Z9*/
DEF_INST(load_logical_long_halfword_register);                  /*@Z9*/
DEF_INST(find_leftmost_one_long_register);                      /*@Z9*/
DEF_INST(extract_cpu_time);


/* Instructions in ecpsvm.c */
DEF_INST(ecpsvm_basic_freex);
DEF_INST(ecpsvm_basic_fretx);
DEF_INST(ecpsvm_lock_page);
DEF_INST(ecpsvm_unlock_page);
DEF_INST(ecpsvm_decode_next_ccw);
DEF_INST(ecpsvm_free_ccwstor);
DEF_INST(ecpsvm_locate_vblock);
DEF_INST(ecpsvm_disp1);
DEF_INST(ecpsvm_tpage);
DEF_INST(ecpsvm_tpage_lock);
DEF_INST(ecpsvm_inval_segtab);
DEF_INST(ecpsvm_inval_ptable);
DEF_INST(ecpsvm_decode_first_ccw);
DEF_INST(ecpsvm_dispatch_main);
DEF_INST(ecpsvm_locate_rblock);
DEF_INST(ecpsvm_comm_ccwproc);
DEF_INST(ecpsvm_unxlate_ccw);
DEF_INST(ecpsvm_disp2);
DEF_INST(ecpsvm_store_level);
DEF_INST(ecpsvm_loc_chgshrpg);
DEF_INST(ecpsvm_extended_freex);
DEF_INST(ecpsvm_extended_fretx);
DEF_INST(ecpsvm_prefmach_assist);


/* Instructions in ieee.c */
DEF_INST(convert_bfp_long_to_float_long_reg);
DEF_INST(convert_bfp_short_to_float_long_reg);
DEF_INST(convert_float_long_to_bfp_long_reg);
DEF_INST(convert_float_long_to_bfp_short_reg);
DEF_INST(add_bfp_ext_reg);
DEF_INST(add_bfp_long_reg);
DEF_INST(add_bfp_long);
DEF_INST(add_bfp_short_reg);
DEF_INST(add_bfp_short);
DEF_INST(compare_bfp_ext_reg);
DEF_INST(compare_bfp_long_reg);
DEF_INST(compare_bfp_long);
DEF_INST(compare_bfp_short_reg);
DEF_INST(compare_bfp_short);
DEF_INST(compare_and_signal_bfp_ext_reg);
DEF_INST(compare_and_signal_bfp_long_reg);
DEF_INST(compare_and_signal_bfp_long);
DEF_INST(compare_and_signal_bfp_short_reg);
DEF_INST(compare_and_signal_bfp_short);
DEF_INST(convert_fix32_to_bfp_ext_reg);
DEF_INST(convert_fix32_to_bfp_long_reg);
DEF_INST(convert_fix32_to_bfp_short_reg);
DEF_INST(convert_fix64_to_bfp_ext_reg);
DEF_INST(convert_fix64_to_bfp_long_reg);
DEF_INST(convert_fix64_to_bfp_short_reg);
DEF_INST(convert_bfp_ext_to_fix32_reg);
DEF_INST(convert_bfp_long_to_fix32_reg);
DEF_INST(convert_bfp_short_to_fix32_reg);
DEF_INST(convert_bfp_ext_to_fix64_reg);
DEF_INST(convert_bfp_long_to_fix64_reg);
DEF_INST(convert_bfp_short_to_fix64_reg);
DEF_INST(divide_bfp_ext_reg);
DEF_INST(divide_bfp_long_reg);
DEF_INST(divide_bfp_long);
DEF_INST(divide_bfp_short_reg);
DEF_INST(divide_bfp_short);
DEF_INST(divide_integer_bfp_long_reg);
DEF_INST(divide_integer_bfp_short_reg);
DEF_INST(load_and_test_bfp_ext_reg);
DEF_INST(load_and_test_bfp_long_reg);
DEF_INST(load_and_test_bfp_short_reg);
DEF_INST(load_fp_int_bfp_ext_reg);
DEF_INST(load_fp_int_bfp_long_reg);
DEF_INST(load_fp_int_bfp_short_reg);
DEF_INST(load_lengthened_bfp_short_to_long_reg);
DEF_INST(load_lengthened_bfp_short_to_long);
DEF_INST(load_lengthened_bfp_long_to_ext_reg);
DEF_INST(load_lengthened_bfp_long_to_ext);
DEF_INST(load_lengthened_bfp_short_to_ext_reg);
DEF_INST(load_lengthened_bfp_short_to_ext);
DEF_INST(load_negative_bfp_ext_reg);
DEF_INST(load_negative_bfp_long_reg);
DEF_INST(load_negative_bfp_short_reg);
DEF_INST(load_complement_bfp_ext_reg);
DEF_INST(load_complement_bfp_long_reg);
DEF_INST(load_complement_bfp_short_reg);
DEF_INST(load_positive_bfp_ext_reg);
DEF_INST(load_positive_bfp_long_reg);
DEF_INST(load_positive_bfp_short_reg);
DEF_INST(load_rounded_bfp_long_to_short_reg);
DEF_INST(load_rounded_bfp_ext_to_long_reg);
DEF_INST(load_rounded_bfp_ext_to_short_reg);
DEF_INST(multiply_bfp_ext_reg);
DEF_INST(multiply_bfp_long_to_ext_reg);
DEF_INST(multiply_bfp_long_to_ext);
DEF_INST(multiply_bfp_long_reg);
DEF_INST(multiply_bfp_long);
DEF_INST(multiply_bfp_short_to_long_reg);
DEF_INST(multiply_bfp_short_to_long);
DEF_INST(multiply_bfp_short_reg);
DEF_INST(multiply_bfp_short);
DEF_INST(multiply_add_bfp_long_reg);
DEF_INST(multiply_add_bfp_long);
DEF_INST(multiply_add_bfp_short_reg);
DEF_INST(multiply_add_bfp_short);
DEF_INST(multiply_subtract_bfp_long_reg);
DEF_INST(multiply_subtract_bfp_long);
DEF_INST(multiply_subtract_bfp_short_reg);
DEF_INST(multiply_subtract_bfp_short);
DEF_INST(squareroot_bfp_ext_reg);
DEF_INST(squareroot_bfp_long_reg);
DEF_INST(squareroot_bfp_long);
DEF_INST(squareroot_bfp_short_reg);
DEF_INST(squareroot_bfp_short);
DEF_INST(subtract_bfp_ext_reg);
DEF_INST(subtract_bfp_long_reg);
DEF_INST(subtract_bfp_long);
DEF_INST(subtract_bfp_short_reg);
DEF_INST(subtract_bfp_short);
DEF_INST(test_data_class_bfp_short);
DEF_INST(test_data_class_bfp_long);
DEF_INST(test_data_class_bfp_ext);

/* Instructions in dfp.c */
DEF_INST(copy_sign_fpr_long_reg);
DEF_INST(load_complement_fpr_long_reg);
DEF_INST(load_fpr_from_gr_long_reg);
DEF_INST(load_gr_from_fpr_long_reg);
DEF_INST(load_negative_fpr_long_reg);
DEF_INST(load_positive_fpr_long_reg);
DEF_INST(set_dfp_rounding_mode);
DEF_INST(load_fpc_and_signal);
DEF_INST(set_fpc_and_signal);
DEF_INST(add_dfp_ext_reg);
DEF_INST(add_dfp_long_reg);
DEF_INST(compare_dfp_ext_reg);
DEF_INST(compare_dfp_long_reg);
DEF_INST(compare_and_signal_dfp_ext_reg);
DEF_INST(compare_and_signal_dfp_long_reg);
DEF_INST(compare_exponent_dfp_ext_reg);
DEF_INST(compare_exponent_dfp_long_reg);
DEF_INST(convert_fix64_to_dfp_ext_reg);
DEF_INST(convert_fix64_to_dfp_long_reg);
DEF_INST(convert_sbcd128_to_dfp_ext_reg);
DEF_INST(convert_sbcd64_to_dfp_long_reg);
DEF_INST(convert_ubcd128_to_dfp_ext_reg);
DEF_INST(convert_ubcd64_to_dfp_long_reg);
DEF_INST(convert_dfp_ext_to_fix64_reg);
DEF_INST(convert_dfp_long_to_fix64_reg);
DEF_INST(convert_dfp_ext_to_sbcd128_reg);
DEF_INST(convert_dfp_long_to_sbcd64_reg);
DEF_INST(convert_dfp_ext_to_ubcd128_reg);
DEF_INST(convert_dfp_long_to_ubcd64_reg);
DEF_INST(divide_dfp_ext_reg);
DEF_INST(divide_dfp_long_reg);
DEF_INST(extract_biased_exponent_dfp_ext_to_fix64_reg);
DEF_INST(extract_biased_exponent_dfp_long_to_fix64_reg);
DEF_INST(extract_significance_dfp_ext_reg);
DEF_INST(extract_significance_dfp_long_reg);
DEF_INST(insert_biased_exponent_fix64_to_dfp_ext_reg);
DEF_INST(insert_biased_exponent_fix64_to_dfp_long_reg);
DEF_INST(load_and_test_dfp_ext_reg);
DEF_INST(load_and_test_dfp_long_reg);
DEF_INST(load_fp_int_dfp_ext_reg);
DEF_INST(load_fp_int_dfp_long_reg);
DEF_INST(load_lengthened_dfp_long_to_ext_reg);
DEF_INST(load_lengthened_dfp_short_to_long_reg);
DEF_INST(load_rounded_dfp_ext_to_long_reg);
DEF_INST(load_rounded_dfp_long_to_short_reg);
DEF_INST(multiply_dfp_ext_reg);
DEF_INST(multiply_dfp_long_reg);
DEF_INST(quantize_dfp_ext_reg);
DEF_INST(quantize_dfp_long_reg);
DEF_INST(reround_dfp_ext_reg);
DEF_INST(reround_dfp_long_reg);
DEF_INST(shift_coefficient_left_dfp_ext);
DEF_INST(shift_coefficient_left_dfp_long);
DEF_INST(shift_coefficient_right_dfp_ext);
DEF_INST(shift_coefficient_right_dfp_long);
DEF_INST(subtract_dfp_ext_reg);
DEF_INST(subtract_dfp_long_reg);
DEF_INST(test_data_class_dfp_ext);
DEF_INST(test_data_class_dfp_long);
DEF_INST(test_data_class_dfp_short);
DEF_INST(test_data_group_dfp_ext);
DEF_INST(test_data_group_dfp_long);
DEF_INST(test_data_group_dfp_short);

/* Instructions in pfpo.c */
DEF_INST(perform_floating_point_operation);

/* end of OPCODE.H */
