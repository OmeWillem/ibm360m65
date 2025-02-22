/* EXTERNAL.C   (c) Copyright Roger Bowler, 1999-2009                */
/*              ESA/390 External Interrupt and Timer                 */

// $Id: external.c 5469 2009-10-03 19:11:05Z hsg001 $

/* Interpretive Execution - (c) Copyright Jan Jaeger, 1999-2009      */
/* z/Architecture support - (c) Copyright Jan Jaeger, 1999-2009      */

/*-------------------------------------------------------------------*/
/* This module implements external interrupt, timer, and signalling  */
/* functions for the Hercules ESA/390 emulator.                      */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* Additional credits:                                               */
/*      TOD clock offset contributed by Jay Maynard                  */
/*      Correction to timer interrupt by Valery Pogonchenko          */
/*      TOD clock drag factor contributed by Jan Jaeger              */
/*      CPU timer and clock comparator interrupt improvements by     */
/*          Jan Jaeger, after a suggestion by Willem Koynenberg      */
/*      Prevent TOD clock and CPU timer from going back - Jan Jaeger */
/*      Use longjmp on all interrupt types - Jan Jaeger              */
/*      Fix todclock - Jay Maynard                                   */
/*      Modifications for Interpretive Execution (SIE) by Jan Jaeger */
/*-------------------------------------------------------------------*/

// $Log$
// Revision 1.72  2008/12/28 22:00:57  rbowler
// Issue message if service signal interrupt occurs while stepping or tracing
//
// Revision 1.71  2007/06/23 00:04:09  ivan
// Update copyright notices to include current year (2007)
//
// Revision 1.70  2007/02/26 00:54:22  gsmith
// Display timer interrupts only if tracing/stepping all
//
// Revision 1.69  2007/01/16 01:45:33  gsmith
// Tweaks to instruction stepping/tracing
//
// Revision 1.68  2006/12/08 09:43:20  jj
// Add CVS message log
//

#include "hstdinc.h"

#if !defined(_HENGINE_DLL_)
#define _HENGINE_DLL_
#endif

#if !defined(_EXTERNAL_C_)
#define _EXTERNAL_C_
#endif

#include "hercules.h"
#include "opcode.h"
#include "inline.h"

#if !defined(SOFTWARE_M65) && !defined(HARDWARE_M65)

/*-------------------------------------------------------------------*/
/* Load external interrupt new PSW                                   */
/*-------------------------------------------------------------------*/
static void ARCH_DEP(external_interrupt) (int code, REGS *regs)
{
PSA     *psa;
int     rc;

    PTT(PTT_CL_SIG,"*EXTINT",code,regs->cpuad,regs->psw.IA_L);

    {
        /* Point to PSA in main storage */
        psa = (void*)(regs->mainstor);
        STORAGE_KEY(0, regs) |= (STORKEY_REF | STORKEY_CHANGE);
    }

    /* Store the interrupt code in the PSW */
    regs->psw.intcode = code;


    /* Zero extcpuad field unless extcall or ems signal or blockio */
    if(code != EXT_EXTERNAL_CALL_INTERRUPT
    && code != EXT_EMERGENCY_SIGNAL_INTERRUPT)
        STORE_HW(psa->extcpad,0);

    {
        /* Store current PSW at PSA+X'18' */
        ARCH_DEP(store_psw) (regs, psa->extold);

        /* Load new PSW from PSA+X'58' */
        rc = ARCH_DEP(load_psw) (regs, psa->extnew);

        if ( rc )
        {
            RELEASE_INTLOCK(regs);
            ARCH_DEP(program_interrupt)(regs, rc);
        }
    }

#if defined(FEATURE_INTERVAL_TIMER)
    /* Ensure the interval timer is uptodate */
    ARCH_DEP(store_int_timer_nolock) (regs);
#endif
    RELEASE_INTLOCK(regs);


    longjmp (regs->progjmp, SIE_NO_INTERCEPT);

} /* end function external_interrupt */

/*-------------------------------------------------------------------*/
/* Perform external interrupt if pending                             */
/*                                                                   */
/* This function is called by the CPU to check whether any           */
/* external interrupt conditions are pending, and to perform         */
/* an external interrupt if so.  If multiple external interrupts     */
/* are pending, then only the highest priority interrupt is taken,   */
/* and any other interrupts remain pending.  Remaining interrupts    */
/* will be processed one-by-one during subsequent calls.             */
/*                                                                   */
/* Important notes:                                                  */
/* (i)  This function must NOT be called if the CPU is disabled      */
/*      for external interrupts (PSW bit 7 is zero).                 */
/* (ii) The caller MUST hold the interrupt lock (sysblk.intlock)     */
/*      to ensure correct serialization of interrupt pending bits.   */
/*-------------------------------------------------------------------*/
void ARCH_DEP(perform_external_interrupt) (REGS *regs)
{
PSA    *psa;                            /* -> Prefixed storage area  */
U16     cpuad;                          /* Originating CPU address   */

    /* External interrupt if console interrupt key was depressed */
    if ( OPEN_IC_INTKEY(regs) )
    {
        logmsg (_("HHCCP023I External interrupt: Interrupt key\n"));

        /* Reset interrupt key pending */
        OFF_IC_INTKEY;

        /* Generate interrupt key interrupt */
        ARCH_DEP(external_interrupt) (EXT_INTERRUPT_KEY_INTERRUPT, regs);
    }

    /* External interrupt if malfunction alert is pending */
    if (OPEN_IC_MALFALT(regs))
    {
        /* Find first CPU which generated a malfunction alert */
        for (cpuad = 0; regs->malfcpu[cpuad] == 0; cpuad++)
        {
            if (cpuad >= MAX_CPU)
            {
                OFF_IC_MALFALT(regs);
                return;
            }
        } /* end for(cpuad) */

// /*debug*/ logmsg (_("External interrupt: Malfuction Alert from CPU %d\n"),
// /*debug*/    cpuad);

        /* Reset the indicator for the CPU which was found */
        regs->malfcpu[cpuad] = 0;

        /* Store originating CPU address at PSA+X'84' */
        psa = (void*)(regs->mainstor);
        STORE_HW(psa->extcpad,cpuad);

        /* Reset emergency signal pending flag if there are
           no other CPUs which generated emergency signal */
        OFF_IC_MALFALT(regs);
        while (++cpuad < MAX_CPU)
        {
            if (regs->malfcpu[cpuad])
            {
                ON_IC_MALFALT(regs);
                break;
            }
        } /* end while */

        /* Generate emergency signal interrupt */
        ARCH_DEP(external_interrupt) (EXT_MALFUNCTION_ALERT_INTERRUPT, regs);
    }


    /* External interrupt if emergency signal is pending */
    if (OPEN_IC_EMERSIG(regs))
    {
        /* Find first CPU which generated an emergency signal */
        for (cpuad = 0; regs->emercpu[cpuad] == 0; cpuad++)
        {
            if (cpuad >= MAX_CPU)
            {
                OFF_IC_EMERSIG(regs);
                return;
            }
        } /* end for(cpuad) */

// /*debug*/ logmsg (_("External interrupt: Emergency Signal from CPU %d\n"),
// /*debug*/    cpuad);

        /* Reset the indicator for the CPU which was found */
        regs->emercpu[cpuad] = 0;

        /* Store originating CPU address at PSA+X'84' */
        psa = (void*)(regs->mainstor);
        STORE_HW(psa->extcpad,cpuad);

        /* Reset emergency signal pending flag if there are
           no other CPUs which generated emergency signal */
        OFF_IC_EMERSIG(regs);
        while (++cpuad < MAX_CPU)
        {
            if (regs->emercpu[cpuad])
            {
                ON_IC_EMERSIG(regs);
                break;
            }
        } /* end while */

        /* Generate emergency signal interrupt */
        ARCH_DEP(external_interrupt) (EXT_EMERGENCY_SIGNAL_INTERRUPT, regs);
    }

    /* External interrupt if external call is pending */
    if (OPEN_IC_EXTCALL(regs))
    {
//  /*debug*/logmsg (_("External interrupt: External Call from CPU %d\n"),
//  /*debug*/       regs->extccpu);

        /* Reset external call pending */
        OFF_IC_EXTCALL(regs);

        /* Store originating CPU address at PSA+X'84' */
        psa = (void*)(regs->mainstor);
        STORE_HW(psa->extcpad,regs->extccpu);

        /* Generate external call interrupt */
        ARCH_DEP(external_interrupt) (EXT_EXTERNAL_CALL_INTERRUPT, regs);
    }

    /* External interrupt if TOD clock exceeds clock comparator */
    if ( tod_clock(regs) > regs->clkc
        && OPEN_IC_CLKC(regs) )
    {
        if (CPU_STEPPING_OR_TRACING_ALL)
        {
            logmsg (_("HHCCP024I External interrupt: Clock comparator\n"));
        }
        ARCH_DEP(external_interrupt) (EXT_CLOCK_COMPARATOR_INTERRUPT, regs);
    }

    /* External interrupt if CPU timer is negative */
    if ( CPU_TIMER(regs) < 0
        && OPEN_IC_PTIMER(regs) )
    {
        if (CPU_STEPPING_OR_TRACING_ALL)
        {
            logmsg (_("HHCCP025I External interrupt: CPU timer=%16.16" I64_FMT "X\n"),
                    (long long)CPU_TIMER(regs) << 8);
        }
        ARCH_DEP(external_interrupt) (EXT_CPU_TIMER_INTERRUPT, regs);
    }

    /* External interrupt if interval timer interrupt is pending */
#if defined(FEATURE_INTERVAL_TIMER)
    if (OPEN_IC_ITIMER(regs)
        )
    {
        if (CPU_STEPPING_OR_TRACING_ALL)
        {
            logmsg (_("HHCCP026I External interrupt: Interval timer\n"));
        }
        OFF_IC_ITIMER(regs);
        ARCH_DEP(external_interrupt) (EXT_INTERVAL_TIMER_INTERRUPT, regs);
    }

#endif /*FEATURE_INTERVAL_TIMER*/

    /* External interrupt if service signal is pending */
    if ( OPEN_IC_SERVSIG(regs) )
    {

        /* Apply prefixing if the parameter is a storage address */
        if ( (sysblk.servparm & SERVSIG_ADDR) )

        if (CPU_STEPPING_OR_TRACING_ALL)
        {
            logmsg (_("HHCCP027I External interrupt: Service signal %8.8X\n"),
                    sysblk.servparm);
        }

        /* Store service signal parameter at PSA+X'80' */
        psa = (void*)(regs->mainstor);
        STORE_FW(psa->extparm,sysblk.servparm);

        /* Reset service parameter */
        sysblk.servparm = 0;

        /* Reset service signal pending */
        OFF_IC_SERVSIG;
        
        /* Generate service signal interrupt */
        ARCH_DEP(external_interrupt) (EXT_SERVICE_SIGNAL_INTERRUPT, regs);

    }  /* end OPEN_IC_SERVSIG(regs) */

} /* end function perform_external_interrupt */

#endif

/*-------------------------------------------------------------------*/
/* Store Status                                                      */
/* Input:                                                            */
/*      sregs   Register context of CPU whose status is to be stored */
/*      aaddr   A valid absolute address of a 512-byte block into    */
/*              which status is to be stored                         */
/*              For an implicit store status, or an operator         */
/*              initiated store status the absolute address will be  */
/*              zero, for a store status at address order the        */
/*              supplied address will be nonzero                     */
/*-------------------------------------------------------------------*/
void ARCH_DEP(store_status) (REGS *ssreg, RADR aaddr)
{
int     i;                              /* Array subscript           */
PSA     *sspsa;                         /* -> Store status area      */

    /* Set reference and change bits */
    STORAGE_KEY(aaddr, ssreg) |= (STORKEY_REF | STORKEY_CHANGE);

    aaddr &= 0x7FFFFE00;

    /* Point to the PSA into which status is to be stored */
    sspsa = (void*)(ssreg->mainstor + aaddr);

    /* Store CPU timer in bytes 216-223 */
    STORE_DW(sspsa->storeptmr, cpu_timer(ssreg));

    /* Store clock comparator in bytes 224-231 */
    STORE_DW(sspsa->storeclkc, ssreg->clkc << 8);

    /* Store PSW in bytes 256-263 */
    ARCH_DEP(store_psw) (ssreg, sspsa->storepsw);

    /* Store prefix register in bytes 264-267 */
    STORE_FW(sspsa->storepfx,0);

    /* Store access registers in bytes 288-351 */
    for (i = 0; i < 16; i++)
        STORE_FW(sspsa->storear[i],ssreg->AR_(i));

    /* Store floating-point registers in bytes 352-383 */
    for (i = 0; i < 8; i++)
        STORE_FW(sspsa->storefpr[i],ssreg->fpr[i]);

    /* Store general-purpose registers in bytes 384-447 */
    for (i = 0; i < 16; i++)
        STORE_W(sspsa->storegpr[i],ssreg->GR(i));

    /* Store control registers in bytes 448-511 */
    for (i = 0; i < 16; i++)
        STORE_W(sspsa->storecr[i],ssreg->CR(i));

} /* end function store_status */


#if !defined(_GEN_ARCH)

#if defined(_ARCHMODE2)
 #define  _GEN_ARCH _ARCHMODE2
 #include "external.c"
#endif

#if defined(_ARCHMODE3)
 #undef   _GEN_ARCH
 #define  _GEN_ARCH _ARCHMODE3
 #include "external.c"
#endif


void store_status (REGS *ssreg, U64 aaddr)
{
            aaddr &= 0x7FFFFFFF;
            s370_store_status (ssreg, aaddr);
}
#endif /*!defined(_GEN_ARCH)*/
