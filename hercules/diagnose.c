/* DIAGNOSE.C   (c) Copyright Roger Bowler, 2000-2009                */
/*              ESA/390 Diagnose Functions                           */

// $Id: diagnose.c 5548 2009-12-15 15:50:44Z rbowler $

/*-------------------------------------------------------------------*/
/* This module implements miscellaneous diagnose functions           */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* Additional credits:                                               */
/*      Hercules-specific diagnose calls by Jay Maynard.             */
/*      Set/reset bad frame indicator call by Jan Jaeger.            */
/* z/Architecture support - (c) Copyright Jan Jaeger, 1999-2009      */
/*-------------------------------------------------------------------*/

#include "hstdinc.h"

#if !defined(SOFTWARE_M65) && !defined(HARDWARE_M65)

#if !defined(_HENGINE_DLL_)
#define _HENGINE_DLL_
#endif

#if !defined(_DIAGNOSE_C_)
#define _DIAGNOSE_C_
#endif

#include "hercules.h"

#include "opcode.h"

#include "inline.h"

#if !defined(_DIAGNOSE_H)

#define _DIAGNOSE_H

#endif /*!defined(_DIAGNOSE_H)*/

/*-------------------------------------------------------------------*/
/* Diagnose instruction                                              */
/*-------------------------------------------------------------------*/
void ARCH_DEP(diagnose_call) (VADR effective_addr2, int b2,
                              int r1, int r2, REGS *regs)
{
U32   code;

    code = effective_addr2;

    /*---------------------------------------------------------------*/
    /* Diagnose xxx: Invalid function code                           */
    /*---------------------------------------------------------------*/

        if( HDC4(debug_diagnose, code, r1, r2, regs) )
            return;

        ARCH_DEP(program_interrupt)(regs, PGM_SPECIFICATION_EXCEPTION);
        return;

} /* end function diagnose_call */


#if !defined(_GEN_ARCH)

#if defined(_ARCHMODE2)
 #define  _GEN_ARCH _ARCHMODE2
 #include "diagnose.c"
#endif

#if defined(_ARCHMODE3)
 #undef   _GEN_ARCH
 #define  _GEN_ARCH _ARCHMODE3
 #include "diagnose.c"
#endif

#endif /*!defined(_GEN_ARCH)*/
#endif