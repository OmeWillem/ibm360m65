/* HERCULES.H   (c) Copyright Roger Bowler, 1999-2009                */
/*              Hercules Header Files                                */

/* Interpretive Execution - (c) Copyright Jan Jaeger, 1999-2009      */
/* z/Architecture support - (c) Copyright Jan Jaeger, 1999-2009      */

// $Id: hercules.h 5125 2009-01-23 12:01:44Z bernard $
//
// $Log$
// Revision 1.303  2009/01/02 19:21:51  jj
// DVD-RAM IPL
// RAMSAVE
// SYSG Integrated 3270 console fixes
//
// Revision 1.302  2008/05/22 21:34:22  fish
// Attempt to fix my *nix SCSI tape BSR over tapemark bug identified by Bob Schneider [bschneider@pingdata.net]
//
// Revision 1.301  2007/12/11 15:01:06  rbowler
// Fix undefined gettimeofday in clock.h rev 1.27 (MSVC)
//
// Revision 1.300  2007/06/23 00:04:10  ivan
// Update copyright notices to include current year (2007)
//
// Revision 1.299  2006/12/08 09:43:25  jj
// Add CVS message log
//

#ifdef HAVE_CONFIG_H
  #include <config.h> // Hercules build configuration options/settings
#endif

/*-------------------------------------------------------------------*/
/* Performance attribute: use registers to pass function parameters  */
/*     (must be #defined BEFORE "feature,h" since it uses it)        */
/*-------------------------------------------------------------------*/

#if defined(HAVE_ATTR_REGPARM)
  #ifdef _MSVC_
    #define  ATTR_REGPARM(n)   __fastcall
  #else /* GCC presumed */
    #define  ATTR_REGPARM(n)   __attribute__  (( regparm(n) ))
  #endif
#else
  #define  ATTR_REGPARM(n)   /* nothing */
#endif

// -------------------------------------------------------------------
//
//                      PROGRAMMING NOTE
//
//  The "feature.h" header MUST be #included AFTER <config.h> *AND*
//  BEFORE the _HERCULES_H pre-processor variable gets #defined. This
//  is to enure that it is ALWAYS #included regardless of whether the
//  "hercules.h" header has already been #included or not. This is so
//  the various architecture dependent source modules compile properly
//  since they #include themselves several times so as to cause them
//  to be compiled multiple times, each time with a new architecture
//  mode #defined (e.g. 370/390/900). See the very end of the source
//  member "general2.c" for a typical example of this very technique.
//
// -------------------------------------------------------------------
//

//
// Include standard system headers (if not already done)
//

#include "feature.h"      // Hercules [manually maintained] features;
                          // auto-includes featall.h and hostopts.h

                          // ALWAYS include cpuint.h after feature.h
                          // and also assure it is re-included for
                          // each archs.
#include "cpuint.h"

#ifndef _HERCULES_H       // MUST come AFTER "feature.h" is #included
#define _HERCULES_H       // MUST come AFTER "feature.h" is #included

#include "hstdinc.h"      // Precompilation-eligible header files

#ifdef _MSVC_
  #include "getopt.h"
#else
  #if defined(HAVE_GETOPT_LONG) && !defined(__GETOPT_H__)
    #include <getopt.h>
  #endif
#endif

#ifdef OPTION_DYNAMIC_LOAD
  #ifdef HDL_USE_LIBTOOL
    #include <ltdl.h>
  #else
    #if defined(__MINGW__) || defined(_MSVC_)
      #include "w32dl.h"
    #else
      #include <dlfcn.h>
    #endif
  #endif
#endif


///////////////////////////////////////////////////////////////////////
// Private Hercules-specific headers.....
///////////////////////////////////////////////////////////////////////

#include "linklist.h"     // (Hercules-wide linked-list macros)
#include "hconsts.h"      // (Hercules-wide #define constants)
#include "hthreads.h"     // (Hercules-wide threading macros)
#include "hmacros.h"      // (Hercules-wide #define macros)

#if !defined(HAVE_BYTESWAP_H) || defined(NO_ASM_BYTESWAP)
 #include "hbyteswp.h"    // (Hercules equivalent of <byteswap.h>)
#endif

#if !defined(HAVE_MEMRCHR)
  #include "memrchr.h"
#endif

#if defined(HAVE_ASSERT_H)
 #include <assert.h>
#endif

#include "hostinfo.h"
#include "version.h"

#include "esa390.h"       // (ESA/390 structure definitions)
#include "hscutl.h"       // (utility functions)
#include "w32util.h"      // (win32 porting functions)
#include "clock.h"        // (TOD definitions)

#include "codepage.h"
#include "logger.h"       // (logmsg, etc)
#include "hdl.h"          // (Hercules Dynamic Loader)

#include "cache.h"

#include "devtype.h"
#include "dasdtab.h"
#include "shared.h"
#include "hetlib.h"
#include "sockdev.h"
#include "w32ctca.h"

#include "service.h"

#include "hsocket.h"
#ifdef _MSVC_
  #include "w32mtio.h"    // 'mtio.h' needed by hstructs.h
#endif // _MSVC_
#include "hstructs.h"     // (Hercules-wide structures)
#include "hexterns.h"     // (Hercules-wide extern function prototypes)

#if defined(COMPARE_M65) || defined(SOFTWARE_M65) || defined(HARDWARE_M65)
#define M65_REG_ID 0
#define M65_REG_VER 0x1ff
#define M65_REG_CFG 1
#define M65_REG_EXT 2
#define M65_REG_IO_CMD 3
#define M65_REG_IO_RESP 4
#define M65_REG_IO_INT 5
#define M65_REG_SE_CMD 6
#define M65_REG_SE_ADDR 7
#define M65_REG_SE_RESP 8
#define M65_REG_SE_RDATA_HI 9
#define M65_REG_SE_RDATA_LO 10
#define M65_REG_SE_WDATA_HI 11
#define M65_REG_SE_WDATA_LO 12

extern int current_io_num;
#endif

#if defined(COMPARE_M65) || defined(SOFTWARE_M65)
#include "360_cstruc.h"
inline void write_m65_reg(int regno, unsigned int content) {
    switch (regno) {
    case M65_REG_CFG:
        newstate.EXTERNAL_.reg_se_size.F = content;
        break;
    case M65_REG_IO_RESP:
        newstate.EXTERNAL_.reg_io_resp.F = content;
        break;
    case M65_REG_IO_INT:
        newstate.EXTERNAL_.reg_io_int.F = content;
        break;
    case M65_REG_SE_RESP:
        newstate.EXTERNAL_.reg_se_resp.F = content;
        break;
    case M65_REG_SE_RDATA_HI:
        newstate.EXTERNAL_.reg_se_rdata_hi.F = content;
        break;
    case M65_REG_SE_RDATA_LO:
        newstate.EXTERNAL_.reg_se_rdata_lo.F = content;
        break;
    default:
        logmsg("Unknown M65 register %d\n", regno);
    }
}
inline unsigned int read_m65_reg(int regno) {
    switch (regno) {
    case M65_REG_ID:
        return 0x03602065;
    case M65_REG_VER:
        return 0x0001000; // 1.0
    case M65_REG_CFG:
        return oldstate.EXTERNAL_.reg_se_size.F;
    case M65_REG_EXT:
        return oldstate.FE.ext_reg.F;
    case M65_REG_IO_CMD:
        return oldstate.WA.reg_io_cmd.F;
    case M65_REG_IO_RESP:
        return oldstate.EXTERNAL_.reg_io_resp.F;
    case M65_REG_IO_INT:
        return oldstate.EXTERNAL_.reg_io_int.F;
    case M65_REG_SE_CMD:
        return oldstate.WA.reg_se_cmd.F;
    case M65_REG_SE_ADDR:
        return oldstate.WA.reg_se_addr.F;
    case M65_REG_SE_RESP:
        return oldstate.EXTERNAL_.reg_se_resp.F;
    case M65_REG_SE_RDATA_HI:
        return oldstate.EXTERNAL_.reg_se_rdata_hi.F;
    case M65_REG_SE_RDATA_LO:
        return oldstate.EXTERNAL_.reg_se_rdata_lo.F;
    case M65_REG_SE_WDATA_HI:
        return oldstate.WA.reg_se_wdata_hi.F;
    case M65_REG_SE_WDATA_LO:
        return oldstate.WA.reg_se_wdata_lo.F;
    default:
        logmsg("Unknown M65 register %d\n", regno);
    }
    return 0;
}
#endif
#if defined(HARDWARE_M65)
unsigned int* m65_register_map = 0;
inline void init_m65_reg();

inline void write_m65_reg(int regno, unsigned int content) {
    if (m65_register_map == 0)
        init_m65_reg();
    m65_register_map[regno] = content;
}

inline unsigned int read_m65_reg(int regno) {
    if (m65_register_map == 0)
        init_m65_reg();
    return m65_register_map[regno];
}

inline void init_m65_reg() {
    int fp;
    char line[1000];
    char devnam[1100];
    char enanam[1200];
    char resnam[1200];

    sprintf(line, "lspci -d 0360:2065 -nn");
    fp = popen(line, "r");
    if (!fp) {
        D_fprintf("Could not run command <%s>\n",line);
        exit(-1);
    }
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line,"0360:2065") && !devnam[0]) {
            D_fprintf("Found CPU: %s", line);
            *strchr(line, ' ') = 0;
            sprintf(devnam, "/sys/bus/pci/devices/0000:%s", line);
            sprintf(enanam, "%s/enable", devnam);
            sprintf(resnam, "%s/resource0", devnam);
    }
    pclose(fp);

    if (!devnam[0]) {
        D_fprintf("No CPU found.\n");
        exit(-1);
    }

    D_fprintf("Going to open %s\n", devnam);

    fp = fopen(enanam, "w");
    if (!fp) {
        D_fprintf("Can't open device <%s>\n", enanam);
        exit(-1);
    }
    fprintf(fp, "1");
    fclose(fp);

    sprintf(line, "setpci -d 0360:2065 COMMAND=402");
    fp = popen(line, "r");
    if (!fp) {
        D_fprintf("Could not run command <%s>\n", line);
        exit(-1);
    }
    while (fgets(line, sizeof(line), fp));
    pclose(fp);

    int fd = open(resnam, O_RDWR | O_SYNC);
    if (fd == -1) {
        D_fprintf("Can't open <%s>.\n",resnam);
        exit(-1);
    }
    unsigned int* mm = mmap(0, 2048, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mm == 0 || mm == -1) {
        D_fprintf("Can't map PCIe registers.\n");
        exit(-1);
    }
    if (mm[M65_REG_ID] != 0x03602065) {
        D_fprintf("Device signature is incorrect: <%08x>, expected <%08x>", mm[0], 0x03602065);
        exit(-1);
    }
    int maj = mm[M65_REG_VER] >> 16;
    int min = mm[M65_REG_VER] & 0xffff;
    if (maj != 1) {
        D_fprintf("CPU version %d.%d is incompatible with this version of Hercules. Major version 1 expected.\n",maj,min);
        exit(-1);
    }

    D_fprintf("IBM 360 model 65 CPU successfully initialized. CPU version %d.%d found.\n",maj,min)
    m65_register_map = mm;
}

#endif


#endif // _HERCULES_H
