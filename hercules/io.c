/* IO.C         (c) Copyright Roger Bowler, 1994-2009                */
/*              ESA/390 CPU Emulator                                 */

/* Interpretive Execution - (c) Copyright Jan Jaeger, 1999-2009      */
/* z/Architecture support - (c) Copyright Jan Jaeger, 1999-2009      */

// $Id: io.c 5242 2009-03-05 21:33:26Z jj $

/*-------------------------------------------------------------------*/
/* This module implements all I/O instructions of the                */
/* S/370 and ESA/390 architectures, as described in the manuals      */
/* GA22-7000-03 System/370 Principles of Operation                   */
/* SA22-7201-06 ESA/390 Principles of Operation                      */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* Additional credits:                                               */
/*      STCPS and SCHM instructions by Jan Jaeger                    */
/*      STCRW instruction by Jan Jaeger                              */
/*      Instruction decode by macros - Jan Jaeger                    */
/*      Instruction decode rework - Jan Jaeger                       */
/*      Correct nullification of TIO and TSCH - Jan Jaeger           */
/*      Lock device during MSCH update - Jan Jaeger                  */
/*      SIE support - Jan Jaeger                                     */
/*      SAL instruction added - Jan Jaeger                           */
/*      RCHP instruction added - Jan Jaeger                          */
/*      CONCS instruction added - Jan Jaeger                         */
/*      DISCS instruction added - Jan Jaeger                         */
/*      TPI fix - Jay Maynard, found by Greg Smith                   */
/*      STCRW instruction nullification correction - Jan Jaeger      */
/*      I/O rate counter - Valery Pogonchenko                        */
/*      64-bit IDAW support - Roger Bowler v209                  @IWZ*/
/*-------------------------------------------------------------------*/

// $Log$
// Revision 1.61  2007/06/23 00:04:14  ivan
// Update copyright notices to include current year (2007)
//
// Revision 1.60  2007/01/13 07:23:42  bernard
// backout ccmask
//
// Revision 1.59  2007/01/12 15:24:21  bernard
// ccmask phase 1
//
// Revision 1.58  2006/12/08 09:43:28  jj
// Add CVS message log
//

#include "hstdinc.h"

#if !defined(_HENGINE_DLL_)
#define _HENGINE_DLL_
#endif

#if !defined(_IO_C_)
#define _IO_C_
#endif

#include "hercules.h"

#include "opcode.h"

#include "inline.h"

#undef PTIO
 #define PTIO(_class, _name) \
 PTT(PTT_CL_ ## _class,_name,(U32)(effective_addr2 & 0xffffffff),0,regs->psw.IA_L)


/*-------------------------------------------------------------------*/
/* 9C00 SIO   - Start I/O                                        [S] */
/* 9C01 SIOF  - Start I/O Fast Release                           [S] */
/* 9C02 RIO   - Resume I/O   -   ZZ INCOMPLETE                   [S] */
/*-------------------------------------------------------------------*/
DEF_INST(start_io)
{
int     b2;                             /* Effective addr base       */
VADR    effective_addr2;                /* Effective address         */
PSA    *psa;                            /* -> prefixed storage area  */
DEVBLK *dev;                            /* -> device block for SIO   */
ORB     orb;                            /* Operation request blk @IZW*/
VADR    ccwaddr;                        /* CCW address for start I/O */
BYTE    ccwkey;                         /* Bits 0-3=key, 4=7=zeroes  */

    S(inst, regs, b2, effective_addr2);

#if defined(COMPARE_M65)
    record_herc_io(0x04000000 | effective_addr2);
#endif

    PRIV_CHECK(regs);

    PTIO(IO,"SIO");

    /* Locate the device block */
    if(regs->chanset == 0xFFFF
      || !(dev = find_device_by_devnum (regs->chanset,effective_addr2)) )
    {
        PTIO(ERR,"*SIO");
        regs->psw.cc = 3;
        return;
    }

    /* Fetch key and CCW address from the CAW at PSA+X'48' */
    psa = (PSA*)(regs->mainstor);
    ccwkey = psa->caw[0] & 0xF0;
    ccwaddr = (psa->caw[1] << 16) | (psa->caw[2] << 8)
                    | psa->caw[3];

    /* Build the I/O operation request block */                /*@IZW*/
    memset (&orb, 0, sizeof(ORB));                             /*@IZW*/
    orb.flag4 = ccwkey & ORB4_KEY;                             /*@IZW*/
    STORE_FW(orb.ccwaddr,ccwaddr);                             /*@IZW*/

    /* Start the channel program and set the condition code */
    regs->psw.cc = ARCH_DEP(startio) (regs, dev, &orb);        /*@IZW*/

    regs->siocount++;

}


/*-------------------------------------------------------------------*/
/* 9D00 TIO   - Test I/O                                         [S] */
/* 9D01 CLRIO - Clear I/O                                        [S] */
/*-------------------------------------------------------------------*/
DEF_INST(test_io)
{
int     b2;                             /* Base of effective addr    */
VADR    effective_addr2;                /* Effective address         */
DEVBLK *dev;                            /* -> device block for SIO   */

    S(inst, regs, b2, effective_addr2);

#if defined(COMPARE_M65)
    record_herc_io(0x5000000 | effective_addr2);
#endif

    PRIV_CHECK(regs);

    PTIO(IO,"TIO");

    /* Locate the device block */
    if(regs->chanset == 0xFFFF
      || !(dev = find_device_by_devnum (regs->chanset,effective_addr2)) )
    {
        PTIO(ERR,"*TIO");
        regs->psw.cc = 3;
        return;
    }

    /* Test the device and set the condition code */
    regs->psw.cc = testio (regs, dev, inst[1]);
    /* Yield time slice so that device handler may get some time */
    /* to possibly complete an I/O - to prevent a TIO Busy Loop  */
    if(regs->psw.cc == 2)
    {
        sched_yield();
    }

}


/*-------------------------------------------------------------------*/
/* 9E00 HIO   - Halt I/O                                         [S] */
/* 9E01 HDV   - Halt Device                                      [S] */
/*-------------------------------------------------------------------*/
DEF_INST(halt_io)
{
int     b2;                             /* Base of effective addr    */
VADR    effective_addr2;                /* Effective address         */
DEVBLK *dev;                            /* -> device block for SIO   */

    S(inst, regs, b2, effective_addr2);

    PRIV_CHECK(regs);

    PTIO(IO,"HIO");

    /* Locate the device block */
    if(regs->chanset == 0xFFFF
      || !(dev = find_device_by_devnum (regs->chanset,effective_addr2)) )
    {
        PTIO(ERR,"*HIO");
        regs->psw.cc = 3;
        return;
    }

    /* Test the device and set the condition code */
    regs->psw.cc = haltio (regs, dev, inst[1]);

}


/*-------------------------------------------------------------------*/
/* 9F00 TCH   - Test Channel                                     [S] */
/*-------------------------------------------------------------------*/
DEF_INST(test_channel)
{
int     b2;                             /* Base of effective addr    */
VADR    effective_addr2;                /* Effective address         */

    S(inst, regs, b2, effective_addr2);

#if defined(COMPARE_M65)
    record_herc_io(0x07000000 | effective_addr2);
#endif

    PRIV_CHECK(regs);

    PTIO(IO,"TCH");

        /* Test for pending interrupt and set condition code */
        regs->psw.cc = testch (regs, effective_addr2 & 0xFF00);
}


#if !defined(_GEN_ARCH)

#if defined(_ARCHMODE2)
 #define  _GEN_ARCH _ARCHMODE2
 #include "io.c"
#endif

#if defined(_ARCHMODE3)
 #undef   _GEN_ARCH
 #define  _GEN_ARCH _ARCHMODE3
 #include "io.c"
#endif

#endif /*!defined(_GEN_ARCH)*/
