/* DYNINST.C    (c) Copyright Jan Jaeger, 2003-2009                  */
/*              Hercules Dynamic Loader                              */

// $Id: dyninst.c 5125 2009-01-23 12:01:44Z bernard $

/* This module dynamically loads instructions.  Instruction routine  */
/* names must be registered under the name of s370_opcode_B220 for   */
/* example, where s370 may also be s390 or z900 for ESA/390 or ESAME */
/* mode respectively.  B220 is the opcode, and is depending on the   */
/* instruction 2 3 or 4 digits.                                      */

// $Log$
// Revision 1.24  2008/02/29 15:53:10  rbowler
// Instruction decoder for C4xx and C6xx instructions
//
// Revision 1.23  2008/02/29 12:05:06  rbowler
// dyninst.c incorrect restore of C8xx opcodes
//
// Revision 1.22  2007/06/23 00:04:09  ivan
// Update copyright notices to include current year (2007)
//
// Revision 1.21  2006/12/08 09:43:20  jj
// Add CVS message log
//

#include "hstdinc.h"
#include "hercules.h"


#if defined(OPTION_DYNAMIC_LOAD)


#if defined(WIN32) && !defined(HDL_USE_LIBTOOL) && !defined(_MSVC_)
/* We need to do some special tricks for windows here, since windows */
/* does not support backlink and we need to resolve symbols during   */
/* dll initialisation (REGISTER/RESOLVER). Opcode tables are renamed */
/* such that no naming conflicts occur.                              */
 #define copy_opcode_tables copy_opcode_tables_r
 #define opcode_table opcode_table_r
#endif

#include "opcode.h"

#if defined(WIN32) && !defined(HDL_USE_LIBTOOL) && !defined(_MSVC_)
 #undef copy_opcode_tables
 #undef opcode_table
#endif

#include "inline.h"


#if !defined(_GEN_ARCH)

#if defined(_ARCHMODE2)
 #define  _GEN_ARCH _ARCHMODE2
 #include "dyninst.c"
#endif 

#if defined(_ARCHMODE3)
 #undef   _GEN_ARCH
 #define  _GEN_ARCH _ARCHMODE3
 #include "dyninst.c"
#endif 


static zz_func save_table[256][GEN_MAXARCH];
static zz_func save_01xx[256][GEN_MAXARCH];
static zz_func save_a5xx[16][GEN_MAXARCH];
static zz_func save_a7xx[16][GEN_MAXARCH];
static zz_func save_b2xx[256][GEN_MAXARCH];
static zz_func save_b3xx[256][GEN_MAXARCH];
static zz_func save_b9xx[256][GEN_MAXARCH];
static zz_func save_c0xx[16][GEN_MAXARCH];
static zz_func save_c2xx[16][GEN_MAXARCH];                      /*@Z9*/
static zz_func save_c4xx[16][GEN_MAXARCH];                      /*208*/
static zz_func save_c6xx[16][GEN_MAXARCH];                      /*208*/
static zz_func save_c8xx[16][GEN_MAXARCH];
static zz_func save_e3xx[256][GEN_MAXARCH];
static zz_func save_e5xx[256][GEN_MAXARCH];
static zz_func save_e6xx[256][GEN_MAXARCH];
static zz_func save_ebxx[256][GEN_MAXARCH];
static zz_func save_ecxx[256][GEN_MAXARCH];
static zz_func save_edxx[256][GEN_MAXARCH];

#if defined(WIN32) && !defined(HDL_USE_LIBTOOL) && !defined(_MSVC_)
  static int opcodes_saved;
  static void copy_opcode_tables ();
  static void * opcode_table;
#endif

static char *prefix[] = {
    "s370_dyninst_opcode_",
    };


static void opcode_save()    
{
    memcpy(save_table,opcode_table,sizeof(save_table));
}


static void opcode_restore()
{
    memcpy(opcode_table,save_table,sizeof(save_table));
}


static void assign_extop1(int opcode, int extop, zz_func table[256][GEN_MAXARCH],
                                                 zz_func saved[256][GEN_MAXARCH])
{
int arch;
void *tmp;

    for(arch = 0; arch < GEN_MAXARCH - 2; arch++)
    {
    char name[32];

        sprintf(name,"%s%02X%1X",prefix[arch],opcode,extop);

        if((tmp = HDL_FINDSYM(name)))
            table[extop][arch] = tmp;
        else
            table[extop][arch] = saved[extop][arch];

    }


}


static void assign_extop(int opcode, int extop, zz_func table[256][GEN_MAXARCH],
                                                zz_func saved[256][GEN_MAXARCH])
{
int arch;
void *tmp;

    for(arch = 0; arch < GEN_MAXARCH - 2; arch++)
    {
    char name[32];

        sprintf(name,"%s%02X%02X",prefix[arch],opcode,extop);

        if((tmp = HDL_FINDSYM(name)))
            table[extop][arch] = tmp;
        else
            table[extop][arch] = saved[extop][arch];

    }


}


static void assign_opcode(int opcode, zz_func table[256][GEN_MAXARCH],
                                      zz_func saved[256][GEN_MAXARCH])
{
int arch;
void *tmp;

    for(arch = 0; arch < GEN_MAXARCH -  2; arch++)
    {
    char name[32];

        sprintf(name,"%s%02X",prefix[arch],opcode);

        if((tmp = HDL_FINDSYM(name)))
            table[opcode][arch] = tmp;
        else
            table[opcode][arch] = saved[opcode][arch];

    }


}


static inline void copy_opcode(zz_func to_table[256], zz_func from_table[256][GEN_MAXARCH], int opcode, int arch_mode)
{
    to_table[opcode] = from_table[opcode][arch_mode];
}

/* Libtool static name colision resolution */
/* note : lt_dlopen will look for symbol & modulename_LTX_symbol */
#if !defined(HDL_BUILD_SHARED) && defined(HDL_USE_LIBTOOL)
#define hdl_ddev dyninst_LTX_hdl_ddev
#define hdl_depc dyninst_LTX_hdl_depc
#define hdl_reso dyninst_LTX_hdl_reso
#define hdl_init dyninst_LTX_hdl_init
#define hdl_fini dyninst_LTX_hdl_fini
#endif


HDL_DEPENDENCY_SECTION;
{
     HDL_DEPENDENCY (HERCULES);
     HDL_DEPENDENCY (REGS);
     HDL_DEPENDENCY (DEVBLK);
     HDL_DEPENDENCY (SYSBLK);

} END_DEPENDENCY_SECTION


HDL_REGISTER_SECTION;
{
#if defined(WIN32) && !defined(HDL_USE_LIBTOOL) && !defined(_MSVC_)
    opcodes_saved = 0;
#else
    opcode_save();
#endif
}
END_REGISTER_SECTION


HDL_RESOLVER_SECTION;
{
int opcode, extop;

#if 0
#if defined(WIN32) && !defined(HDL_USE_LIBTOOL) && !defined(_MSVC_)
    if(!opcodes_saved)
    {
        HDL_RESOLVE(copy_opcode_tables);
        HDL_RESOLVE(opcode_table);

        opcode_save();

        opcodes_saved = 1;
    }
#endif 
#endif

    for(opcode = 0; opcode < 256; opcode++)
    {
                assign_opcode(opcode, opcode_table, save_table);

    }

    /* Copy opcodes to performance shadow tables */
    copy_opcode_tables();

} END_RESOLVER_SECTION


HDL_FINAL_SECTION;
{

    opcode_restore();

} END_FINAL_SECTION


#endif /*!defined(_GEN_ARCH)*/

#endif /*defined(OPTION_DYNAMIC_LOAD)*/
