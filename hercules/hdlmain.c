/* HDLMAIN.C    (c) Copyright Jan Jaeger, 2003-2010                  */
/*              Hercules Dynamic Loader                              */

// $Id: hdlmain.c 5576 2009-12-29 13:17:11Z bernard $
//
// $Log$
// Revision 1.51  2008/12/24 15:42:13  jj
// Add debug entry point for sclp event masks
//
// Revision 1.50  2008/12/22 13:10:21  jj
// Add sclp debug entry points
//
// Revision 1.49  2008/02/12 08:42:15  fish
// dyngui tweaks: new def devlist fmt, new debug_cd_cmd hook
//
// Revision 1.48  2007/06/23 00:04:10  ivan
// Update copyright notices to include current year (2007)
//
// Revision 1.47  2006/12/08 09:43:25  jj
// Add CVS message log
//

#include "hstdinc.h"

#define _HDLMAIN_C_
#define _HERCULES_EXE_

#include "hercules.h"

#include "httpmisc.h"

#define CRYPTO_EXTERN extern
#include "crypto.h"


#if !defined(_GEN_ARCH)


#if defined(_ARCHMODE2)
 #define  _GEN_ARCH _ARCHMODE2
 #include "hdlmain.c"
#endif

#if defined(_ARCHMODE3)
 #undef   _GEN_ARCH
 #define  _GEN_ARCH _ARCHMODE3
 #include "hdlmain.c"
#endif


#if defined(OPTION_DYNAMIC_LOAD)

/* Following block moved to 'hdl.c' */
/* this is so that                  */
/* hdlmain.c can be moved to the executable portion */
/* hdl_main can find hdl_preload */
/*
HDLPRE hdl_preload[] = {
    { "hdteq",          HDL_LOAD_NOMSG },
    { "dyncrypt",       HDL_LOAD_NOMSG },
#if 0
    { "dyn_test1",      HDL_LOAD_DEFAULT },
    { "dyn_test2",      HDL_LOAD_NOMSG },
    { "dyn_test3",      HDL_LOAD_NOMSG | HDL_LOAD_NOUNLOAD },
#endif
    { NULL,             0  } };
*/


HDL_DEPENDENCY_SECTION;
{
     HDL_DEPENDENCY(HERCULES);
     HDL_DEPENDENCY(REGS);
     HDL_DEPENDENCY(DEVBLK);
     HDL_DEPENDENCY(SYSBLK);
     HDL_DEPENDENCY(WEBBLK);
}
END_DEPENDENCY_SECTION


HDL_REGISTER_SECTION;
{
    HDL_REGISTER( parse_args,                 parse_args      );
    HDL_REGISTER( panel_command,              panel_command_r );
    HDL_REGISTER( panel_display,              panel_display_r );
    HDL_REGISTER( config_command,             UNRESOLVED      );
    HDL_REGISTER( system_command,             UNRESOLVED      );
    HDL_REGISTER( daemon_task,                UNRESOLVED      );
    HDL_REGISTER( debug_cpu_state,            UNRESOLVED      );
    HDL_REGISTER( debug_cd_cmd,               UNRESOLVED      );
    HDL_REGISTER( debug_device_state,         UNRESOLVED      );
    HDL_REGISTER( debug_program_interrupt,    UNRESOLVED      );
    HDL_REGISTER( debug_diagnose,             UNRESOLVED      );
    HDL_REGISTER( debug_iucv,                 UNRESOLVED      );
    HDL_REGISTER( debug_sclp_unknown_command, UNRESOLVED      );
    HDL_REGISTER( debug_sclp_unknown_event,   UNRESOLVED      );
    HDL_REGISTER( debug_sclp_unknown_event_mask,   UNRESOLVED );
    HDL_REGISTER( debug_sclp_event_data,      UNRESOLVED      );
    HDL_REGISTER( debug_chsc_unknown_request, UNRESOLVED      );
    HDL_REGISTER( debug_watchdog_signal,      UNRESOLVED      );
#if defined(OPTION_W32_CTCI)
    HDL_REGISTER( debug_tt32_stats,           UNRESOLVED      );
    HDL_REGISTER( debug_tt32_tracing,         UNRESOLVED      );
#endif

    HDL_REGISTER( hdl_device_type_equates,    UNRESOLVED      );

}
END_REGISTER_SECTION


HDL_RESOLVER_SECTION;
{
    HDL_RESOLVE( panel_command              );
    HDL_RESOLVE( panel_display              );
    HDL_RESOLVE( config_command             );
    HDL_RESOLVE( system_command             );
    HDL_RESOLVE( daemon_task                );
    HDL_RESOLVE( debug_cpu_state            );
    HDL_RESOLVE( debug_cd_cmd               );
    HDL_RESOLVE( debug_device_state         );
    HDL_RESOLVE( debug_program_interrupt    );
    HDL_RESOLVE( debug_diagnose             );
    HDL_RESOLVE( debug_sclp_unknown_command );
    HDL_RESOLVE( debug_sclp_unknown_event   );
    HDL_RESOLVE( debug_sclp_unknown_event_mask );
    HDL_RESOLVE( debug_sclp_event_data      );
    HDL_RESOLVE( debug_chsc_unknown_request );
#if defined(OPTION_W32_CTCI)
    HDL_RESOLVE( debug_tt32_stats           );
    HDL_RESOLVE( debug_tt32_tracing         );
#endif

    HDL_RESOLVE( hdl_device_type_equates    );

}
END_RESOLVER_SECTION


HDL_FINAL_SECTION;
{
    system_cleanup();
}
END_FINAL_SECTION


#endif /*defined(OPTION_DYNAMIC_LOAD)*/


HDL_DEVICE_SECTION;
{
#if !defined(OPTION_DYNAMIC_LOAD)
    /* TTY consoles */
    HDL_DEVICE(1052, constty_device_hndinfo );
    HDL_DEVICE(3215, constty_device_hndinfo );

    /* 3270 consoles */
    HDL_DEVICE(3270, loc3270_device_hndinfo );
    HDL_DEVICE(3287, loc3270_device_hndinfo );

    /* Communication line devices */
    HDL_DEVICE(2703, comadpt_device_hndinfo );

    /* Card readers */
    HDL_DEVICE(1442, cardrdr_device_hndinfo );
    HDL_DEVICE(2501, cardrdr_device_hndinfo );
    HDL_DEVICE(3505, cardrdr_device_hndinfo );

    /* Card punches */
    HDL_DEVICE(3525, cardpch_device_hndinfo );

    /* Printers */
    HDL_DEVICE(1403, printer_device_hndinfo );
    HDL_DEVICE(3211, printer_device_hndinfo );

    /* Tape drives */
    HDL_DEVICE(3410, tapedev_device_hndinfo );
    HDL_DEVICE(3411, tapedev_device_hndinfo );
    HDL_DEVICE(3420, tapedev_device_hndinfo );
    HDL_DEVICE(3480, tapedev_device_hndinfo );
    HDL_DEVICE(3490, tapedev_device_hndinfo );
    HDL_DEVICE(9347, tapedev_device_hndinfo );
    HDL_DEVICE(9348, tapedev_device_hndinfo );
    HDL_DEVICE(8809, tapedev_device_hndinfo );
    HDL_DEVICE(3422, tapedev_device_hndinfo );
    HDL_DEVICE(3430, tapedev_device_hndinfo );

    /* Communications devices */
    HDL_DEVICE(3088, ctcadpt_device_hndinfo );
    HDL_DEVICE(CTCI, ctci_device_hndinfo    );
    HDL_DEVICE(CTCT, ctct_device_hndinfo    );
    HDL_DEVICE(LCS,  lcs_device_hndinfo     );
    HDL_DEVICE(VMNET,vmnet_device_hndinfo   );
#if defined(WIN32)
    HDL_DEVICE(CTCI-W32, ctci_device_hndinfo);
#endif /*defined(WIN32)*/

#endif /*!defined(OPTION_DYNAMIC_LOAD)*/

    /* Count Key Data Direct Access Storage Devices */
    HDL_DEVICE(2305, ckddasd_device_hndinfo );
    HDL_DEVICE(2311, ckddasd_device_hndinfo );
    HDL_DEVICE(2314, ckddasd_device_hndinfo );
    HDL_DEVICE(3330, ckddasd_device_hndinfo );
    HDL_DEVICE(3340, ckddasd_device_hndinfo );
    HDL_DEVICE(3350, ckddasd_device_hndinfo );
    HDL_DEVICE(3375, ckddasd_device_hndinfo );
    HDL_DEVICE(3380, ckddasd_device_hndinfo );
    HDL_DEVICE(3390, ckddasd_device_hndinfo );
    HDL_DEVICE(9345, ckddasd_device_hndinfo );

    /* Fixed Block Architecture Direct Access Storage Devices */
    HDL_DEVICE(0671, fbadasd_device_hndinfo );
    HDL_DEVICE(3310, fbadasd_device_hndinfo );
    HDL_DEVICE(3370, fbadasd_device_hndinfo );
    HDL_DEVICE(9313, fbadasd_device_hndinfo );
    HDL_DEVICE(9332, fbadasd_device_hndinfo );
    HDL_DEVICE(9335, fbadasd_device_hndinfo );
    HDL_DEVICE(9336, fbadasd_device_hndinfo );
}
END_DEVICE_SECTION


#endif /*!defined(_GEN_ARCH)*/
