/* FEATALL.H    (c) Copyright Jan Jaeger, 2000-2009                  */
/*              Architecture-dependent macro definitions             */

// $Id: featall.h 5454 2009-08-14 14:25:06Z rbowler $

/*-------------------------------------------------------------------*/
/* Default features                                                  */
/*   All existing features MUST be #undef-ed here.                   */
/*-------------------------------------------------------------------*/
#define OPTION_370_MODE                 /* Generate S/370 support    */
//#define OPTION_LPP_RESTRICT             /* Disable Licensed Software */
//#define OPTION_SMP                      /* Enable SMP support        */
#define VECTOR_SECTION_SIZE         128 /* Vector section size       */
#define VECTOR_PARTIAL_SUM_NUMBER     1 /* Vector partial sum number */
#define CKD_MAXFILES                  4 /* Max files per CKD volume  */
#define OPTION_MIPS_COUNTING            /* Display MIPS on ctl panel */
#define PANEL_REFRESH_RATE              /* Enable panrate feature    */
#define PANEL_REFRESH_RATE_FAST      50 /* Fast refresh rate         */
#define PANEL_REFRESH_RATE_SLOW     500 /* Slow refresh rate         */
#define DEFAULT_TIMER_REFRESH_USECS  50 /* Default timer refresh int */
#define MAX_DEVICE_THREAD_IDLE_SECS 300 /* 5 Minute thread timeout   */
#undef  OPTION_NO_INLINE_DAT            /* Performance option        */
#undef  OPTION_NO_INLINE_LOGICAL        /* Performance option        */
#undef  OPTION_NO_INLINE_VSTORE         /* Performance option        */
#undef  OPTION_NO_INLINE_IFETCH         /* Performance option        */
#define OPTION_MULTI_BYTE_ASSIST        /* Performance option        */
#define OPTION_SINGLE_CPU_DW            /* Performance option (ia32) */
#define OPTION_FAST_DEVLOOKUP           /* Fast devnum/subchan lookup*/
#define OPTION_IODELAY_KLUDGE           /* IODELAY kludge for linux  */
#undef  OPTION_FOOTPRINT_BUFFER /* 2048 ** Size must be a power of 2 */
#undef  OPTION_INSTRUCTION_COUNTING     /* First use trace and count */
#define OPTION_CKD_KEY_TRACING          /* Trace CKD search keys     */
#undef  OPTION_CMPSC_DEBUGLVL      /* 3 ** 1=Exp 2=Comp 3=Both debug */
#undef  MODEL_DEPENDENT_STCM            /* STCM, STCMH always store  */
#define OPTION_NOP_MODEL158_DIAGNOSE    /* NOP mod 158 specific diags*/
#define FEATURE_LCSS_MAX              4 /* Number of supported lcss's*/
#define OPTION_LPARNAME                 /* DIAG 204 lparname         */
#define OPTION_HTTP_SERVER              /* HTTP server support       */
#define OPTION_WAKEUP_SELECT_VIA_PIPE   /* Use communication pipes to
                                           interrupt selects instead
                                           of inter-thread signaling */
#define OPTION_TIMESTAMP_LOGFILE        /* Hardcopy logfile HH:MM:SS */
#define OPTION_IPLPARM                  /* IPL PARM a la VM          */
#ifndef FISH_HANG
#define OPTION_PTTRACE                  /* Pthreads tracing          */
#endif
//#define OPTION_DEBUG_MESSAGES         /* Prefix msgs with filename
//                                         and line# if DEBUG build  */
#define OPTION_SET_STSI_INFO            /* Set STSI info in cfg file */

#define OPTION_TAPE_AUTOMOUNT           /* "Automount" CCWs support  */
#define OPTION_MSGCLR                   /* Colored messages          */
#define OPTION_MSGHLD                   /* Sticky messages           */

#if defined(OPTION_MSGHLD) && !defined(OPTION_MSGCLR)
  #error OPTION_MSGHLD requires OPTION_MSGCLR
#endif // defined(OPTION_MSGHLD) && !defined(OPTION_MSGCLR)

/*********************************************************************\
 *********************************************************************
 **                                                                 **
 **                    ***   NOTE!   ***                            **
 **                                                                 **
 **    All HOST-operating-system-specific FEATUREs and OPTIONs      **
 **    should be #defined in the below header (and ONLY in the      **
 **    below header!) Please read the comments there!               **
 **                                                                 **
 *********************************************************************
\*********************************************************************/

#include "hostopts.h"     // (HOST-specific options/feature settings)

/* end of FEATALL.H */
