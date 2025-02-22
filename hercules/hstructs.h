/* HSTRUCTS.H   (c) Copyright Roger Bowler, 1999-2009                */
/*              Hercules Structure Definitions                       */

//      This header auto-#included by 'hercules.h'...
//
//      The <config.h> header and other required headers are
//      presumed to have already been #included ahead of it...

// $Id: hstructs.h 5622 2010-02-09 00:32:03Z fish $

#ifndef _HSTRUCTS_H
#define _HSTRUCTS_H

#include "hercules.h"
#include "opcode.h"

/*-------------------------------------------------------------------*/
/* Typedefs for CPU bitmap fields                                    */
/*                                                                   */
/* A CPU bitmap contains one bit for each processing engine.         */
/* The width of the bitmap depends on the maximum number of          */
/* processing engines which was selected at build time.              */
/*-------------------------------------------------------------------*/
#if MAX_CPU_ENGINES <= 32
    typedef U32                 CPU_BITMAP;
    #define F_CPU_BITMAP        "%8.8"I32_FMT"X"
#elif MAX_CPU_ENGINES <= 64
    typedef U64                 CPU_BITMAP;
    #define F_CPU_BITMAP        "%16.16"I64_FMT"X"
#else
 #error MAX_CPU_ENGINES cannot exceed 64
#endif

/*-------------------------------------------------------------------*/
/* Structure definition for CPU register context                     */
/*-------------------------------------------------------------------*/
struct REGS {                           /* Processor registers       */
#define HDL_VERS_REGS   "3.03"          /* Internal Version Number   */
#define HDL_SIZE_REGS   sizeof(REGS)

        int     arch_mode;              /* Architectural mode        */

        PSW     psw;                    /* Program status word       */
        BYTE   *ip;                     /* Mainstor inst address     */

     /* AIA - Instruction fetch accelerator                          */
        BYTE   *aip;                    /* Mainstor page address     */
        uintptr_t aim;                  /* Mainstor xor address      */
        BYTE   *aie;                    /* Mainstor page end address */
        DW      aiv;                    /* Virtual page address      */

        U64     bear;                   /* Breaking event address reg*/
        BYTE   *bear_ip;                /* Breaking event inst ptr   */

        DW      gr[16];                 /* General registers         */

        DW      cr[16+16+1];            /* 16 Control registers      */
#define CR_ALB_OFFSET   16              /* 16 Accesslist lookaside   */
#define CR_ASD_REAL     32              /*  1 Real asd register      */

        U32     ar[16];                 /* Access registers          */
        U32     fpr[32];                /* Floating point registers  */
        U32     fpc;                    /* IEEE Floating Point
                                                    Control Register */
        U32     dxc;                    /* Data exception code       */
        DW      mc;                     /* Monitor Code              */
        DW      ea;                     /* Exception address         */
        DW      et;                     /* Execute Target address    */

        unsigned int                    /* Flags (cpu thread only)   */
                execflag:1,             /* 1=EXecuted instruction    */
                exrl:1,                 /* 1=EXRL, 0=EX instruction  */
                permode:1,              /* 1=PER active              */
                instinvalid:1,          /* 1=Inst field is invalid   */
                opinterv:1,             /* 1=Operator intervening    */
                checkstop:1,            /* 1=CPU is checkstop-ed     */
                hostint:1,              /* 1=Host generated interrupt*/
                host:1,                 /* REGS are hostregs         */
                guest:1;                /* REGS are guestregs        */
        unsigned int                    /* Flags (intlock serialized)*/
                dummy:1,                /* 1=Dummy regs structure    */
                configured:1,           /* 1=CPU is online           */
                loadstate:1,            /* 1=CPU is in load state    */
                ghostregs:1,            /* 1=Ghost registers (panel) */
                invalidate:1,           /* 1=Do AIA/AEA invalidation */
                tracing:1,              /* 1=Trace is active         */
                stepwait:1,             /* 1=Wait in inst stepping   */
                sigpreset:1,            /* 1=SIGP cpu reset received */
                sigpireset:1;           /* 1=SIGP initial cpu reset  */

        S64     cpu_timer;              /* CPU timer epoch           */
        S64     int_timer;              /* S/370 Interval timer      */
        S32     old_timer;              /* S/370 Interval timer int  */
        U64     clkc;                   /* 0-7=Clock comparator epoch,
                                           8-63=Comparator bits 0-55 */
        S64     tod_epoch;              /* TOD epoch for this CPU    */
        S64     ecps_vtimer;            /* ECPS Virtual Int. timer   */
        S32     ecps_oldtmr;            /* ECPS Virtual Int. tmr int */
        BYTE   *ecps_vtmrpt;            /* Pointer to VTMR or zero   */
        U32     instcount;              /* Instruction counter       */
        U64     prevcount;              /* Previous instruction count*/
        U32     mipsrate;               /* Instructions per second   */
        U32     siocount;               /* SIO/SSCH counter          */
        U32     siosrate;               /* IOs per second            */
        U64     siototal;               /* Total SIO/SSCH count      */
        int     cpupct;                 /* Percent CPU busy          */
        U64     waittod;                /* Time of day last wait (us)*/
        U64     waittime;               /* Wait time (us) in interval*/
        DAT     dat;                    /* Fields for DAT use        */

#define GR_G(_r) gr[(_r)].D
#define GR_H(_r) gr[(_r)].F.H.F          /* Fullword bits 0-31       */
#define GR_HHH(_r) gr[(_r)].F.H.H.H.H    /* Halfword bits 0-15       */
#define GR_HHL(_r) gr[(_r)].F.H.H.L.H    /* Halfword low, bits 16-31 */
#define GR_L(_r) gr[(_r)].F.L.F          /* Fullword low, bits 32-63 */
#define GR_LHH(_r) gr[(_r)].F.L.H.H.H    /* Halfword bits 32-47      */
#define GR_LHL(_r) gr[(_r)].F.L.H.L.H    /* Halfword low, bits 48-63 */
#define GR_LHHCH(_r) gr[(_r)].F.L.H.H.B.H   /* Character, bits 32-39 */
#define GR_LA24(_r) gr[(_r)].F.L.A.A     /* 24 bit addr, bits 40-63  */
#define GR_LA8(_r) gr[(_r)].F.L.A.B      /* 24 bit addr, unused bits */
#define GR_LHLCL(_r) gr[(_r)].F.L.H.L.B.L   /* Character, bits 56-63 */
#define GR_LHLCH(_r) gr[(_r)].F.L.H.L.B.H   /* Character, bits 48-55 */
#define CR_G(_r)   cr[(_r)].D            /* Bits 0-63                */
#define CR_H(_r)   cr[(_r)].F.H.F        /* Fullword bits 0-31       */
#define CR_HHH(_r) cr[(_r)].F.H.H.H.H    /* Halfword bits 0-15       */
#define CR_HHL(_r) cr[(_r)].F.H.H.L.H    /* Halfword low, bits 16-31 */
#define CR_L(_r)   cr[(_r)].F.L.F        /* Fullword low, bits 32-63 */
#define CR_LHH(_r) cr[(_r)].F.L.H.H.H    /* Halfword bits 32-47      */
#define CR_LHHCH(_r) cr[(_r)].F.L.H.H.B.H   /* Character, bits 32-39 */
#define CR_LHL(_r) cr[(_r)].F.L.H.L.H    /* Halfword low, bits 48-63 */
#define MC_G      mc.D
#define MC_L      mc.F.L.F
#define EA_G      ea.D
#define EA_L      ea.F.L.F
#define ET_G      et.D
#define ET_L      et.F.L.F
#define AIV_G     aiv.D
#define AIV_L     aiv.F.L.F
#define AR_(_r)    ar[(_r)]

        U16     chanset;                /* Connected channel set     */
        U32     todpr;                  /* TOD programmable register */
        U16     monclass;               /* Monitor event class       */
        U16     cpuad;                  /* CPU address for STAP      */
        BYTE    excarid;                /* Exception access register */
        BYTE    opndrid;                /* Operand access register   */
        BYTE    exinst[8];              /* Target of Execute (EX)    */
        BYTE   *mainstor;               /* -> Main storage           */
        BYTE   *storkeys;               /* -> Main storage key array */
        RADR    mainlim;                /* Central Storage limit or  */
                                        /* guest storage limit (SIE) */
        PSA_3XX *psa;                   /* -> PSA for this CPU       */

     /*
      *   sysblk.regs[i] always points to the host regs
      *   flag `host' is always 1 for the host regs
      *   flag `guest' is always 1 for the guest regs
      *   `hostregs' is always equal to sysblk.regs[i] (in both
      *       hostregs and guestregs)
      *   `guestregs' is always equal to sysblk.regs[i]->guestregs
      *       (in both hostregs and guestregs).
      *       sysblk.regs[i]->guestregs is NULL until the first SIE
      *       instruction is executed on that CPU.
      *   `sie_active' is 1 in hostregs if SIE is executing
      *       and the current register context is `guestregs'
      *   `sie_mode' is 1 in guestregs always
      *   `sie_state' has the real address of the SIEBK
      *   `siebk' has the mainstor address of the SIEBK
      */
        REGS   *hostregs;               /* Pointer to the hypervisor
                                           register context          */
        REGS   *guestregs;              /* Pointer to the guest
                                           register context          */
        SYSBLK *sysblk;                 /* Pointer to sysblk         */

        unsigned int
                sie_active:1,           /* SIE active (host only)    */
                sie_mode:1,             /* Running under SIE (guest) */
                sie_pref:1;             /* Preferred-storage mode    */

        CPU_BITMAP cpubit;              /* Only this CPU's bit is 1  */
        U32     ints_state;             /* CPU Interrupts Status     */
        U32     ints_mask;              /* Respective Interrupts Mask*/
     /*
      * Making the following flags 'stand-alone' (instead of bit-
      * flags like they were) addresses a compiler bit-flag serial-
      * ization issue that occurs with the 'SYNCHRONIZE_CPUS' macro
      * used during synchronize broadcast (cpu<->cpu communication)
      */
        int     intwait;                /* 1=Waiting on intlock      */
        int     syncio;                 /* 1=Synchronous i/o active  */

        BYTE    cpustate;               /* CPU stopped/started state */
        BYTE    malfcpu                 /* Malfuction alert flags    */
                    [MAX_CPU_ENGINES];  /* for each CPU (1=pending)  */
        BYTE    emercpu                 /* Emergency signal flags    */
                    [MAX_CPU_ENGINES];  /* for each CPU (1=pending)  */
        U16     extccpu;                /* CPU causing external call */
        BYTE    inst[8];                /* Fetched instruction when
                                           instruction crosses a page
                                           boundary                  */
        BYTE    *invalidate_main;       /* Mainstor addr to invalidat*/
        PSW     captured_zpsw;          /* Captured-z/Arch PSW reg   */

        jmp_buf progjmp;                /* longjmp destination for
                                           program check return      */
        jmp_buf exitjmp;                /* longjmp destination for
                                           CPU thread exit           */
        COND    intcond;                /* CPU interrupt condition   */
        LOCK    *cpulock;               /* CPU lock for this CPU     */

     /* Function pointers */
        pi_func program_interrupt;
        func    trace_br;

     /* ------------------------------------------------------------ */
        U64     regs_copy_end;          /* Copy regs to here         */
     /* ------------------------------------------------------------ */

     /* Opcode table pointers                                        */

        FUNC    s370_opcode_table[256];

     /* TLB - Translation lookaside buffer                           */

//        unsigned int tlbID;             /* Validation identifier     */
//        TLB     tlb;                    /* Translation lookaside buf */

};

/*-------------------------------------------------------------------*/
/* System configuration block                                        */
/*-------------------------------------------------------------------*/
struct SYSBLK {
#define HDL_VERS_SYSBLK   "3.06"        /* Internal Version Number   */
#define HDL_SIZE_SYSBLK   sizeof(SYSBLK)
        time_t  impltime;               /* TOD system was IMPL'ed    */
        int     arch_mode;              /* Architecturual mode       */
                                        /* 0 == S/370   (ARCH_370)   */
        int     arch_z900;              /* 1 == ESAME supported      */
        RADR    mainsize;               /* Main storage size (bytes) */
        BYTE   *mainstor;               /* -> Main storage           */
        BYTE   *storkeys;               /* -> Main storage key array */
        U32     xpndsize;               /* Expanded size (4K pages)  */
        BYTE   *xpndstor;               /* -> Expanded storage       */
        U64     todstart;               /* Time of initialisation    */
        U64     cpuid;                  /* CPU identifier for STIDP  */
        TID     wdtid;                  /* Thread-id for watchdog    */
        U16     lparnuml;               /* #digits (0-2) in lparnum  */
        U16     lparnum;                /* LPAR identification number*/
        U16     ipldev;                 /* IPL device                */
        int     iplcpu;                 /* IPL cpu                   */
        int     ipllcss;                /* IPL lcss                  */
        int     numcpu;                 /* Number of CPUs installed  */
        int     numvec;                 /* Number vector processors  */
        int     maxcpu;                 /* Max number of CPUs        */
        int     cpus;                   /* Number CPUs configured    */
        int     hicpu;                  /* Hi cpu + 1 configured     */
        int     sysepoch;               /* TOD clk epoch (1900/1960) */
        int     topchnge;               /* 1 = Topology Change Report
                                           pending (CPU cfg on/off)  */
        COND    cpucond;                /* CPU config/deconfig cond  */
        LOCK    cpulock[MAX_CPU_ENGINES];  /* CPU lock               */
        TID     cputid[MAX_CPU_ENGINES];   /* CPU thread identifiers */
        BYTE    ptyp[MAX_CPU_ENGINES];  /* SCCB ptyp for each engine */
        LOCK    todlock;                /* TOD clock update lock     */
        TID     todtid;                 /* Thread-id for TOD update  */
        REGS   *regs[MAX_CPU_ENGINES+1];   /* Registers for each CPU */
#if defined(OPTION_FOOTPRINT_BUFFER)
        REGS    footprregs[MAX_CPU_ENGINES][OPTION_FOOTPRINT_BUFFER];
        U32     footprptr[MAX_CPU_ENGINES];
#endif

#define LOCK_OWNER_NONE  0xFFFF
#define LOCK_OWNER_OTHER 0xFFFE
        U16     mainowner;              /* Mainlock owner            */
        U16     intowner;               /* Intlock owner             */

        LOCK    mainlock;               /* Main storage lock         */
        LOCK    intlock;                /* Interrupt lock            */
        LOCK    iointqlk;               /* I/O Interrupt Queue lock  */
        LOCK    sigplock;               /* Signal processor lock     */
        ATTR    detattr;                /* Detached thread attribute */
        ATTR    joinattr;               /* Joinable thread attribute */
#define  DETACHED  &sysblk.detattr      /* (helper macro)            */
#define  JOINABLE  &sysblk.joinattr     /* (helper macro)            */
        TID     cnsltid;                /* Thread-id for console     */
        TID     socktid;                /* Thread-id for sockdev     */
                                        /* 3270 Console Keep-Alive:  */
        int     kaidle;                 /* Keepalive idle seconds    */
        int     kaintv;                 /* Keepalive probe interval  */
        int     kacnt;                  /* Keepalive probe count     */
#if defined( OPTION_WAKEUP_SELECT_VIA_PIPE )
        LOCK    cnslpipe_lock;          /* signaled flag access lock */
        int     cnslpipe_flag;          /* 1 == already signaled     */
        int     cnslwpipe;              /* fd for sending signal     */
        int     cnslrpipe;              /* fd for receiving signal   */
        LOCK    sockpipe_lock;          /* signaled flag access lock */
        int     sockpipe_flag;          /* 1 == already signaled     */
        int     sockwpipe;              /* Sockdev signaling pipe Wr */
        int     sockrpipe;              /* Sockdev signaling pipe Rd */
#endif // defined( OPTION_WAKEUP_SELECT_VIA_PIPE )
        RADR    mbo;                    /* Measurement block origin  */
        BYTE    mbk;                    /* Measurement block key     */
        int     mbm;                    /* Measurement block mode    */
        int     mbd;                    /* Device connect time mode  */
        int     diag8cmd;               /* Allow diagnose 8 commands */
#define DIAG8CMD_ECHO     0x80          /* Echo command to console   */
#define DIAG8CMD_ENABLE   0x01          /* Enable DIAG8 interface    */
        BYTE    shcmdopt;               /* 'sh'ell command option    */
#define SHCMDOPT_DISABLE  0x80          /* Globally disable 'sh' cmd */
#define SHCMDOPT_NODIAG8  0x40          /* Disallow only for DIAG8   */
        int     panrate;                /* Panel refresh rate        */
        int     timerint;               /* microsecs timer interval  */
        char   *pantitle;               /* Alt console panel title   */
#if defined(OPTION_HAO)
        TID     haotid;                 /* Herc Auto-Oper thread-id  */
#endif /* defined(OPTION_HAO) */
#if defined(OPTION_SCSI_TAPE)
        int     auto_scsi_mount_secs;   /* Check for SCSI tape mount
                                           frequency; 0 == disabled  */
#define DEFAULT_AUTO_SCSI_MOUNT_SECS  (5)
#endif
        DEVBLK *firstdev;               /* -> First device block     */
        DEVBLK *sysgdev;                /* -> devblk for SYSG console*/
#if defined(OPTION_FAST_DEVLOOKUP)
        DEVBLK ***devnum_fl;            /* 1st level table for fast  */
                                        /* devnum lookup             */
        DEVBLK ***subchan_fl;           /* Subchannel table fast     */
                                        /* lookup table              */
#endif  /* FAST_DEVICE_LOOKUP */
        U16     highsubchan[FEATURE_LCSS_MAX];  /* Highest subchan+1 */
        U32     chp_reset[8];           /* Channel path reset masks  */
        IOINT  *iointq;                 /* I/O interrupt queue       */
#if !defined(OPTION_FISHIO)
        DEVBLK *ioq;                    /* I/O queue                 */
        LOCK    ioqlock;                /* I/O queue lock            */
        COND    ioqcond;                /* I/O queue condition       */
        int     devtwait;               /* Device threads waiting    */
        int     devtnbr;                /* Number of device threads  */
        int     devtmax;                /* Max device threads        */
        int     devthwm;                /* High water mark           */
        int     devtunavail;            /* Count thread unavailable  */
#endif // !defined(OPTION_FISHIO)
        RADR    addrlimval;             /* Address limit value (SAL) */
        U32     servparm;               /* Service signal parameter  */
        unsigned int                    /* Flags                     */
                daemon_mode:1,          /* Daemon mode active        */
                panel_init:1,           /* Panel display initialized */
                npquiet:1,              /* New Panel quiet indicator */
                sigintreq:1,            /* 1 = SIGINT request pending*/
                insttrace:1,            /* 1 = Instruction trace     */
                inststep:1,             /* 1 = Instruction step      */
                shutdown:1,             /* 1 = shutdown requested    */
                shutfini:1,             /* 1 = shutdown complete     */
                main_clear:1,           /* 1 = mainstor is cleared   */
                xpnd_clear:1,           /* 1 = xpndstor is cleared   */
                showregsfirst:1,        /* 1 = show regs before inst */
                showregsnone:1,         /* 1 = show no registers     */
                nomountedtapereinit:1,  /* 1 = disallow tape devinit
                                             if tape already mounted */
                legacysenseid:1,        /* ena/disa senseid on       */
                                        /*   legacy devices          */
#if defined(OPTION_IPLPARM)
                haveiplparm:1,          /* IPL PARM a la VM          */
#endif
                logoptnotime:1;         /* 1 = don't timestamp log   */
        U32     ints_state;             /* Common Interrupts Status  */
        CPU_BITMAP config_mask;         /* Configured CPUs           */
        CPU_BITMAP started_mask;        /* Started CPUs              */
        CPU_BITMAP waiting_mask;        /* Waiting CPUs              */
        U64     traceaddr[2];           /* Tracing address range     */
        U64     stepaddr[2];            /* Stepping address range    */
#if defined(OPTION_IPLPARM)
        BYTE    iplparmstring[64];      /* 64 bytes loadable at IPL  */
#endif
        U64     pgminttr;               /* Program int trace mask    */
        int     pcpu;                   /* Tgt CPU panel cmd & displ */
        int     hercprio;               /* Hercules process priority */
        int     todprio;                /* TOD Clock thread priority */
        int     cpuprio;                /* CPU thread priority       */
        int     devprio;                /* Device thread priority    */
        TID     httptid;                /* HTTP listener thread id   */
        U16     httpport;               /* HTTP port number or zero  */
        int     httpauth;               /* HTTP auth required flag   */
        char   *httpuser;               /* HTTP userid               */
        char   *httppass;               /* HTTP password             */
        char   *httproot;               /* HTTP root                 */
#if defined( OPTION_TAPE_AUTOMOUNT )
        TAMDIR *tamdir;                 /* Acc/Rej AUTOMOUNT dir ctl */
        char   *defdir;                 /* Default AUTOMOUNT dir     */
#endif
     /* Fields used by SYNCHRONIZE_CPUS */
        int     syncing;                /* 1=Sync in progress        */
        CPU_BITMAP sync_mask;           /* CPU mask for syncing CPUs */
        COND    sync_cond;              /* COND for syncing CPU      */
        COND    sync_bc_cond;           /* COND for other CPUs       */
#if defined(OPTION_SHARED_DEVICES)
        TID     shrdtid;                /* Shared device listener    */
        U16     shrdport;               /* Shared device server port */
        U32     shrdcount;              /* IO count                  */
        SHRD_TRACE  *shrdtrace;         /* Internal trace table      */
        SHRD_TRACE  *shrdtracep;        /* Current pointer           */
        SHRD_TRACE  *shrdtracex;        /* End of trace table        */
        int          shrdtracen;        /* Number of entries         */
#endif
#ifdef OPTION_IODELAY_KLUDGE
        int     iodelay;                /* I/O delay kludge for linux*/
#endif /*OPTION_IODELAY_KLUDGE*/
#if defined( HTTP_SERVER_CONNECT_KLUDGE )
        int     http_server_kludge_msecs;
#endif // defined( HTTP_SERVER_CONNECT_KLUDGE )
#if !defined(NO_SETUID)
        uid_t   ruid, euid, suid;
        gid_t   rgid, egid, sgid;
#endif /*!defined(NO_SETUID)*/

#if defined(OPTION_COUNTING)
        long long count[OPTION_COUNTING];
#define COUNT(n) sysblk.count[(n)]++
#else
#define COUNT(n)
#endif

#if defined(OPTION_INSTRUCTION_COUNTING)
        LOCK  icount_lock;
#define IMAP_FIRST sysblk.imap01
        U64 imap01[256];
        U64 imapa4[256];
        U64 imapa5[16];
        U64 imapa6[256];
        U64 imapa7[16];
        U64 imapb2[256];
        U64 imapb3[256];
        U64 imapb9[256];
        U64 imapc0[16];
        U64 imapc2[16];                                         /*@Z9*/
        U64 imapc4[16];                                         /*208*/
        U64 imapc6[16];                                         /*208*/
        U64 imapc8[16];
        U64 imape3[256];
        U64 imape4[256];
        U64 imape5[256];
        U64 imapeb[256];
        U64 imapec[256];
        U64 imaped[256];
        U64 imapxx[256];
#define IMAP_SIZE \
            ( sizeof(sysblk.imap01) \
            + sizeof(sysblk.imapa4) \
            + sizeof(sysblk.imapa5) \
            + sizeof(sysblk.imapa6) \
            + sizeof(sysblk.imapa7) \
            + sizeof(sysblk.imapb2) \
            + sizeof(sysblk.imapb3) \
            + sizeof(sysblk.imapb9) \
            + sizeof(sysblk.imapc0) \
            + sizeof(sysblk.imapc2) /*@Z9*/ \
            + sizeof(sysblk.imapc4) /*208*/ \
            + sizeof(sysblk.imapc6) /*208*/ \
            + sizeof(sysblk.imapc8) \
            + sizeof(sysblk.imape3) \
            + sizeof(sysblk.imape4) \
            + sizeof(sysblk.imape5) \
            + sizeof(sysblk.imapeb) \
            + sizeof(sysblk.imapec) \
            + sizeof(sysblk.imaped) \
            + sizeof(sysblk.imapxx) )
#endif

        char    *logofile;              /* Fancy 3270 logo box       */
        char    **herclogo;             /* 3270 Logo data            */
        size_t  logolines;              /* Number of lines in logo   */
#if defined(OPTION_MIPS_COUNTING)
        /* Merged Counters for all CPUs                              */
        U64     instcount;              /* Instruction counter       */
        U32     mipsrate;               /* Instructions per second   */
        U32     siosrate;               /* IOs per second            */
#endif /*defined(OPTION_MIPS_COUNTING)*/

        int     regs_copy_len;          /* Length to copy for REGS   */

        REGS    dummyregs;              /* Regs for unconfigured CPU */

#ifdef OPTION_MSGHLD
        int     keep_timeout_secs;      /* Message hold time         */
#endif

};

/*-------------------------------------------------------------------*/
/* I/O interrupt queue entry                                         */
/*-------------------------------------------------------------------*/

struct IOINT {                          /* I/O interrupt queue entry */
        IOINT  *next;                   /* -> next interrupt entry   */
        DEVBLK *dev;                    /* -> Device block           */
        int     priority;               /* Device priority           */
        unsigned int
                pending:1,              /* 1=Normal interrupt        */
                pcipending:1,           /* 1=PCI interrupt           */
                attnpending:1;          /* 1=ATTN interrupt          */
};

/*-------------------------------------------------------------------*/
/* Device configuration block                                        */
/*-------------------------------------------------------------------*/
struct DEVBLK {                         /* Device configuration block*/
#define HDL_VERS_DEVBLK   "3.05"        /* Internal Version Number   */
#define HDL_SIZE_DEVBLK   sizeof(DEVBLK)
        DEVBLK *nextdev;                /* -> next device block      */
        REGS   *regs;                   /* -> REGS if syncio         */
        LOCK    lock;                   /* Device block lock         */
        int     allocated;              /* Device block free/in use  */

        /*  device identification                                    */

        U16     ssid;                   /* Subsystem ID incl. lcssid */
        U16     subchan;                /* Subchannel number         */
        U16     devnum;                 /* Device number             */
        U16     devtype;                /* Device type               */
        U16     chanset;                /* Channel Set to which this
                                           device is connected S/370 */
        char    *typname;               /* Device type name          */

        int    member;                  /* Group member number       */
        DEVGRP *group;                  /* Device Group              */

        int     argc;                   /* Init number arguments     */
        char    **argv;                 /* Init arguments            */

        /*  Storage accessible by device                             */

        BYTE   *mainstor;               /* -> Main storage           */
        BYTE   *storkeys;               /* -> Main storage key array */
        RADR    mainlim;                /* Central Storage limit or  */
                                        /* guest storage limit (SIE) */
        char    filename[PATH_MAX+1];   /* filename (plus poss "|")  */

        /*  device i/o fields...                                     */

        int     fd;                     /* File desc / socket number */
        FILE   *fh;                     /* associated File handle    */
        bind_struct* bs;                /* -> bind_struct if socket-
                                           device, NULL otherwise    */

        /*  device buffer management fields                          */

        int     bufcur;                 /* Buffer data identifier    */
        BYTE   *buf;                    /* -> Device data buffer     */
        int     bufsize;                /* Device data buffer size   */
        int     buflen;                 /* Device buffer length used */
        int     bufoff;                 /* Offset into data buffer   */
        int     bufoffhi;               /* Highest offset allowed    */
        int     bufupdlo;               /* Lowest offset updated     */
        int     bufupdhi;               /* Highest offset updated    */
        U32     bufupd;                 /* 1=Buffer updated          */

        /*  device cache management fields                           */

        int     cache;                  /* Current cache index       */
        int     cachehits;              /* Cache hits                */
        int     cachemisses;            /* Cache misses              */
        int     cachewaits;             /* Cache waits               */

        /*  device compression support                               */

        int     comps;                  /* Acceptable compressions   */
        int     comp;                   /* Compression used          */
        int     compoff;                /* Offset to compressed data */

        /*  device i/o scheduling fields...                          */

        TID     tid;                    /* Thread-id executing CCW   */
        int     priority;               /* I/O q scehduling priority */
        DEVBLK *nextioq;                /* -> next device in I/O q   */
        IOINT   ioint;                  /* Normal i/o interrupt
                                               queue entry           */
        IOINT   pciioint;               /* PCI i/o interrupt
                                               queue entry           */
        IOINT   attnioint;              /* ATTN i/o interrupt
                                               queue entry           */
        int     cpuprio;                /* CPU thread priority       */
        int     devprio;                /* Device thread priority    */

        /*  fields used during ccw execution...                      */
        BYTE    chained;                /* Command chain and data chain
                                           bits from previous CCW    */
        BYTE    prev_chained;           /* Chaining flags from CCW
                                           preceding the data chain  */
        BYTE    code;                   /* Current CCW opcode        */
        BYTE    prevcode;               /* Previous CCW opcode       */
        int     ccwseq;                 /* CCW sequence number       */

        U32     ccwaddr;
        U16     idapmask;
        BYTE    idawfmt;
        BYTE    ccwfmt;
        BYTE    ccwkey;

        /*  device handler function pointers...                      */

        DEVHND *hnd;                    /* -> Device handlers        */
        /* Supplemental handler functions - Set by init handler @ISW */
        /* Function invoked during HDV/HIO & HSCH instructions  @ISW */
        /* processing occurs in channel.c in haltio et al.      @ISW */
        /* when the device is busy, but the channel subsystem   @ISW */
        /* does not know how to perform the halt itself but has @ISW */
        /* to rely on the handler to perform the halt           @ISW */
        void ( *halt_device)(DEVBLK *);                      /* @ISW */

        DEVIM   *immed;                 /* Model Specific IM codes   */
                                        /* (overrides devhnd immed)  */
        int     is_immed;               /* Last command is Immediate */

        /*  emulated architecture fields...   (MUST be aligned!)     */

        int     reserved1;              /* ---(ensure alignment)---- */
        ORB     orb;                    /* Operation request blk @IWZ*/
        PMCW    pmcw;                   /* Path management ctl word  */
        SCSW    scsw;                   /* Subchannel status word(XA)*/
        SCSW    pciscsw;                /* PCI subchannel status word*/
        SCSW    attnscsw;               /* ATTNsubchannel status word*/
        BYTE    csw[8];                 /* Channel status word(S/370)*/
        BYTE    pcicsw[8];              /* PCI channel status word   */
        BYTE    attncsw[8];             /* ATTN channel status word  */
        ESW     esw;                    /* Extended status word      */
        BYTE    ecw[32];                /* Extended control word     */
        U32     numsense;               /* Number of sense bytes     */
        BYTE    sense[32];              /* Sense bytes               */
        U32     numdevid;               /* Number of device id bytes */
        BYTE    devid[256];             /* Device identifier bytes   */
        U32     numdevchar;             /* Number of devchar bytes   */
        BYTE    devchar[64];            /* Device characteristics    */
        BYTE    pgstat;                 /* Path Group Status         */
        BYTE    pgid[11];               /* Path Group ID             */
        BYTE    reserved2[4];           /* (pad/align/unused/avail)  */
        COND    resumecond;             /* Resume condition          */
        COND    iocond;                 /* I/O active condition      */
        int     iowaiters;              /* Number of I/O waiters     */
        int     ioactive;               /* System Id active on device*/
#define DEV_SYS_NONE    0               /* No active system on device*/
#define DEV_SYS_LOCAL   0xffff          /* Local system active on dev*/
        BYTE    drvpwd[11];             /* Password for drive        */
        BYTE    reserved3;              /* (pad/align/unused/avail)  */

        /*  control flags...                                         */

        unsigned int                    /* Flags                     */
#ifdef OPTION_CKD_KEY_TRACING
                ckdkeytrace:1,          /* 1=Log CKD_KEY_TRACE       */
#endif /*OPTION_CKD_KEY_TRACING*/
                syncio:2,               /* 1=Synchronous I/Os allowed*/
                shared:1,               /* 1=Device is shareable     */
                console:1,              /* 1=Console device          */
                connected:1,            /* 1=Console client connected*/
                readpending:2,          /* 1=Console read pending    */
                connecting:1,           /* 1=Connecting to remote    */
                localhost:1,            /* 1=Remote is local         */
                batch:1,                /* 1=Called by dasdutil      */
                dasdcopy:1,             /* 1=Called by dasdcopy      */
                oslinux:1,              /* 1=Linux                   */
                ccwtrace:1,             /* 1=CCW trace               */
                ccwstep:1,              /* 1=CCW single step         */
                cdwmerge:1;             /* 1=Channel will merge data
                                             chained write CCWs      */

        unsigned int                    /* Device state - serialized
                                            by dev->lock             */
                busy:1,                 /* 1=Device is busy          */
                reserved:1,             /* 1=Device is reserved      */
                suspended:1,            /* 1=Channel pgm suspended   */
                pending:1,              /* 1=I/O interrupt pending   */
                pcipending:1,           /* 1=PCI interrupt pending   */
                attnpending:1,          /* 1=ATTN interrupt pending  */
                startpending:1,         /* 1=startio pending         */
                resumesuspended:1;      /* 1=Hresuming suspended dev */
#define IOPENDING(_dev) ((_dev)->pending || (_dev)->pcipending || (_dev)->attnpending)
#define INITIAL_POWERON_370() \
    ( dev->crwpending )
        int     crwpending;             /* 1=CRW pending             */
        int     syncio_active;          /* 1=Synchronous I/O active  */
        int     syncio_retry;           /* 1=Retry I/O asynchronously*/

        /*  Synchronous I/O                                          */

        U32     syncio_addr;            /* Synchronous i/o ccw addr  */
        U64     syncios;                /* Number synchronous I/Os   */
        U64     asyncios;               /* Number asynchronous I/Os  */

        /*  Device dependent data (generic)                          */
        void    *dev_data;

#ifdef EXTERNALGUI
        /*  External GUI fields                                      */
        GUISTAT* pGUIStat;              /* EXTERNALGUI Dev Stat Ctl  */
#endif

        /*  Fields for remote devices                                */

        struct in_addr rmtaddr;         /* Remote address            */
        U16     rmtport;                /* Remote port number        */
        U16     rmtnum;                 /* Remote device number      */
        int     rmtid;                  /* Remote Id                 */
        int     rmtrel;                 /* Remote release level      */
        DBLWRD  rmthdr;                 /* Remote header             */
        int     rmtcomp;                /* Remote compression parm   */
        int     rmtcomps;               /* Supported compressions    */
        int     rmtpurgen;              /* Remote purge count        */
        FWORD  *rmtpurge;               /* Remote purge list         */

#ifdef OPTION_SHARED_DEVICES
        /*  Fields for device sharing                                */
        TID     shrdtid;                /* Device thread id          */
        int     shrdid;                 /* Id for next client        */
        int     shrdconn;               /* Number connected clients  */
        int     shrdwait;               /* Signal indicator          */
        SHRD   *shrd[SHARED_MAX_SYS];   /* ->SHRD block              */
#endif

        /*  Device dependent fields for console                      */

        struct in_addr ipaddr;          /* Client IP address         */
        in_addr_t  acc_ipaddr;          /* Allowable clients IP addr */
        in_addr_t  acc_ipmask;          /* Allowable clients IP mask */
        U32     rlen3270;               /* Length of data in buffer  */
        int     pos3270;                /* Current screen position   */
        int     keybdrem;               /* Number of bytes remaining
                                           in keyboard read buffer   */
        u_int   eab3270:1;              /* 1=Extended attributes     */
        u_int   ewa3270:1;              /* 1=Last erase was EWA      */
        u_int   prompt1052:1;           /* 1=Prompt for linemode i/p */
        BYTE    aid3270;                /* Current input AID value   */
        BYTE    mod3270;                /* 3270 model number         */

        /*  Device dependent fields for cardrdr                      */

        char    **more_files;           /* for more that one file in
                                           reader */
        char    **current_file;         /* counts how many additional
                                           reader files are avail    */
        int     cardpos;                /* Offset of next byte to be
                                           read from data buffer     */
        int     cardrem;                /* Number of bytes remaining
                                           in data buffer            */
        u_int   multifile:1;            /* 1=auto-open next i/p file */
        u_int   rdreof:1;               /* 1=Unit exception at EOF   */
        u_int   ebcdic:1;               /* 1=Card deck is EBCDIC     */
        u_int   ascii:1;                /* 1=Convert ASCII to EBCDIC */
        u_int   trunc:1;                /* Truncate overlength record*/
        u_int   autopad:1;              /* 1=Pad incomplete last rec
                                           to 80 bytes if EBCDIC     */

        /*  Device dependent fields for ctcadpt                      */

        DEVBLK *ctcpair;                /* -> Paired device block    */
        int     ctcpos;                 /* next byte offset          */
        int     ctcrem;                 /* bytes remaining in buffer */
        int     ctclastpos;             /* last packet read          */
        int     ctclastrem;             /* last packet read          */
        u_int   ctcxmode:1;             /* 0=Basic mode, 1=Extended  */
        BYTE    ctctype;                /* CTC_xxx device type       */
        BYTE    netdevname[IFNAMSIZ];   /* network device name       */

        /*  Device dependent fields for printer                      */

        int     printpos;               /* Number of bytes already
                                           placed in print buffer    */
        int     printrem;               /* Number of bytes remaining
                                           in print buffer           */
        pid_t   ptpcpid;                /* print-to-pipe child pid   */
        u_int   crlf:1;                 /* 1=CRLF delimiters, 0=LF   */
        u_int   diaggate:1;             /* 1=Diagnostic gate command */
        u_int   fold:1;                 /* 1=Fold to upper case      */
        u_int   ispiped:1;              /* 1=Piped device            */
        u_int   stopprt:1;              /* 1=stopped; 0=started      */
        u_int   notrunc:1;              /* 1=do not truncate at open */

        /*  Device dependent fields for tapedev                      */

        void   *omadesc;                /* -> OMA descriptor array   */
        U16     omafiles;               /* Number of OMA tape files  */
        U16     curfilen;               /* Current file number       */
        U32     blockid;                /* Current device block ID   */
        off_t   nxtblkpos;              /* Offset from start of file
                                           to next block             */
        off_t   prvblkpos;              /* Offset from start of file
                                           to previous block         */
        U16     curblkrem;              /* Number of bytes unread
                                           from current block        */
        U16     curbufoff;              /* Offset into buffer of data
                                           for next data chained CCW */
        U16     tapssdlen;              /* #of bytes of data prepared
                                           for Read Subsystem Data   */
        HETB   *hetb;                   /* HET control block         */

        struct                          /* HET device parms          */
        {
          u_int compress:1;             /* 1=Compression enabled     */
          u_int method:3;               /* Compression method        */
          u_int level:4;                /* Compression level         */
          u_int strictsize:1;           /* Strictly enforce MAXSIZE  */
          u_int displayfeat:1;          /* Device has a display      */
                                        /* feature installed         */
          u_int deonirq:1;              /* DE on IRQ on tape motion  */
                                        /* MVS 3.8j workaround       */
          u_int logical_readonly:1;     /* Tape is forced READ ONLY  */
          U16   chksize;                /* Chunk size                */
          off_t maxsize;                /* Maximum allowed TAPE file
                                           size                      */
        }       tdparms;                /* HET device parms          */

        off_t   eotmargin;              /* Amount of space left before
                                           reporting EOT (in bytes)  */
        u_int   fenced:1;               /* 1=Pos err; volume fenced  */
        u_int   readonly:1;             /* 1=Tape is write-protected */
        u_int   sns_pending:1;          /* Contingency Allegiance    */
                                        /* - means : don't build a   */
                                        /* sense on X'04' : it's     */
                                        /* aleady there              */
                                        /* NOTE : flag cleared by    */
                                        /*        sense command only */
                                        /*        or a device init   */
        u_int   SIC_supported:1;        /* 1=Spec Intcpt Cond support*/
        u_int   SIC_active:1;           /* 1=SIC active              */
        u_int   forced_logging:1;       /* 1=Forced Error Logging    */
        u_int   eotwarning:1;           /* 1=EOT warning area reached*/
#if defined( OPTION_TAPE_AUTOMOUNT )
        u_int   noautomount:1;          /* 1=AUTOMOUNT disabled      */
#endif
        U32     msgid;                  /* Message Id of async. i/o  */
#if defined(OPTION_SCSI_TAPE)
        struct mtget mtget;             /* SCSI tape status struct   */
#define sstat  mtget.mt_gstat           /* Generic SCSI tape device-
                                           independent status field;
                                           (struct mtget->mt_gstat)  */
        TID     stape_mountmon_tid;     /* Tape-mount monitor thread */
        u_int   stape_close_rewinds:1;  /* 1=Rewind at close         */
        u_int   stape_blkid_32:1;       /* 1=block-ids are 32 bits   */
        u_int   stape_no_erg:1;         /* 1=ignore Erase Gap CCWs   */
        u_int   stape_getstat_busy:1;   /* 1=Status wrkr thrd busy   */
        u_int   stape_threads_exit:1;   /* 1=Ask helpr thrds to exit */
        TID     stape_getstat_tid;      /* Tape status wrkr thrd tid */
        LOCK    stape_getstat_lock;     /* LOCK for status wrkr thrd */
        COND    stape_getstat_cond;     /* COND for status wrkr thrd */
        COND    stape_exit_cond;        /* thread wait for exit COND */
        struct mtget stape_getstat_mtget;/* status wrkr thrd status  */
#define stape_getstat_sstat stape_getstat_mtget.mt_gstat /* (gstat)  */
        struct timeval
                stape_getstat_query_tod;/* TOD of actual drive query */
#endif
        BYTE    tapedevt;               /* Hercules tape device type */
        TAPEMEDIA_HANDLER *tmh;         /* Tape Media Handling       */
                                        /* dispatcher                */

        /* ---------- Autoloader feature --------------------------- */
        TAPEAUTOLOADENTRY *als;          /* Autoloader stack         */
        int     alss;                    /* Autoloader stack size    */
        int     alsix;                   /* Current Autoloader index */
        char  **al_argv;                 /* ARGV in autoloader       */
        int     al_argc;                 /* ARGC in autoloader       */
        /* ---------- end Autoloader feature ----------------------- */

        /* 3480/3490/3590 Message display */

        char    tapemsg1[9];            /* 1st Host Message          */
        char    tapemsg2[9];            /* 2nd Host Message          */
        char    tapesysmsg[32];         /*     Unit Message     (SYS)*/
        char   *prev_tapemsg;           /* Previously displayed msg  */

        BYTE    tapedisptype;           /* Type of message display   */
        BYTE    tapedispflags;          /* How the msg is displayed  */

#define TAPEDISPTYP_IDLE           0    /* "READY" "NT RDY" etc (SYS)*/
#define TAPEDISPTYP_LOCATING       1    /* Locate in progress   (SYS)*/
#define TAPEDISPTYP_ERASING        2    /* DSE in progress      (SYS)*/
#define TAPEDISPTYP_REWINDING      3    /* Rewind in progress   (SYS)*/
#define TAPEDISPTYP_UNLOADING      4    /* Unload in progress   (SYS)*/
#define TAPEDISPTYP_CLEAN          5    /* Clean recommended    (SYS)*/
#define TAPEDISPTYP_MOUNT          6    /* Display Until Mounted     */
#define TAPEDISPTYP_UNMOUNT        7    /* Display Until Unmounted   */
#define TAPEDISPTYP_UMOUNTMOUNT    8    /* Display #1 Until Unmounted,
                                              then #2 Until Mounted  */
#define TAPEDISPTYP_WAITACT        9    /* Display until motion      */

#define IS_TAPEDISPTYP_SYSMSG( dev ) \
    (0 \
     || TAPEDISPTYP_IDLE      == (dev)->tapedisptype \
     || TAPEDISPTYP_LOCATING  == (dev)->tapedisptype \
     || TAPEDISPTYP_ERASING   == (dev)->tapedisptype \
     || TAPEDISPTYP_REWINDING == (dev)->tapedisptype \
     || TAPEDISPTYP_UNLOADING == (dev)->tapedisptype \
     || TAPEDISPTYP_CLEAN     == (dev)->tapedisptype \
    )

#define TAPEDISPFLG_ALTERNATE   0x80    /* Alternate msgs 1 & 2      */
#define TAPEDISPFLG_BLINKING    0x40    /* Selected msg blinks       */
#define TAPEDISPFLG_MESSAGE2    0x20    /* Display msg 2 instead of 1*/
#define TAPEDISPFLG_AUTOLOADER  0x10    /* Autoloader request        */
#define TAPEDISPFLG_REQAUTOMNT  0x08    /* ReqAutoMount has work     */

       /* Device dependent fields for Comm Line                      */
        COMMADPT *commadpt;             /* Single structure pointer  */

        /*  Device dependent fields for dasd (fba and ckd)           */

        char   *dasdsfn;                /* Shadow file name          */
        char   *dasdsfx;                /* Pointer to suffix char    */


        /*  Device dependent fields for fbadasd                      */

        FBADEV *fbatab;                 /* Device table entry        */
        int     fbanumblk;              /* Number of blocks in device*/
        int     fbablksiz;              /* Physical block size       */
        off_t   fbaorigin;              /* Device origin block number*/
        off_t   fbarba;                 /* Relative byte offset      */
        off_t   fbaend;                 /* Last RBA in file          */
        /* Values from define extent */
        u_int   fbaxtdef:1;             /* 1=Extent defined          */
        BYTE    fbamask;                /* Define extent file mask   */
        U32     fbaxblkn;               /* Offset from start of device
                                           to first block of extent  */
        U32     fbaxfirst;              /* Block number within dataset
                                           of first block of extent  */
        U32     fbaxlast;               /* Block number within dataset
                                           of last block of extent   */
        /* Values from locate */
        BYTE    fbaoper;                /* Locate operation byte     */
        U16     fbalcnum;               /* Block count for locate    */
        U32     fbalcblk;               /* Block number within dataset
                                           of first block for locate */

        /*  Device dependent fields for ckddasd                      */

        int     ckdnumfd;               /* Number of CKD image files */
        int     ckdfd[CKD_MAXFILES];    /* CKD image file descriptors*/
        int     ckdhitrk[CKD_MAXFILES]; /* Highest track number
                                           in each CKD image file    */
        CKDDEV *ckdtab;                 /* Device table entry        */
        CKDCU  *ckdcu;                  /* Control unit entry        */
        off_t   ckdtrkoff;              /* Track image file offset   */
        int     ckdcyls;                /* Number of cylinders       */
        int     ckdtrks;                /* Number of tracks          */
        int     ckdheads;               /* #of heads per cylinder    */
        int     ckdtrksz;               /* Track size                */
        int     ckdcurcyl;              /* Current cylinder          */
        int     ckdcurhead;             /* Current head              */
        int     ckdcurrec;              /* Current record id         */
        int     ckdcurkl;               /* Current record key length */
        int     ckdorient;              /* Current orientation       */
        int     ckdcuroper;             /* Curr op: read=6, write=5  */
        U16     ckdcurdl;               /* Current record data length*/
        U16     ckdrem;                 /* #of bytes from current
                                           position to end of field  */
        U16     ckdpos;                 /* Offset into buffer of data
                                           for next data chained CCW */
        U16     ckdxblksz;              /* Define extent block size  */
        U16     ckdxbcyl;               /* Define extent begin cyl   */
        U16     ckdxbhead;              /* Define extent begin head  */
        U16     ckdxecyl;               /* Define extent end cyl     */
        U16     ckdxehead;              /* Define extent end head    */
        BYTE    ckdfmask;               /* Define extent file mask   */
        BYTE    ckdxgattr;              /* Define extent global attr */
        U16     ckdltranlf;             /* Locate record transfer
                                           length factor             */
        U16     ckdlmask;               /* Locate record mask        */
        BYTE    ckdloper;               /* Locate record operation   */
        BYTE    ckdlaux;                /* Locate record aux byte    */
        BYTE    ckdlcount;              /* Locate record count       */
        BYTE    ckdreserved1;           /* Alignment                 */
        void   *cckd_ext;               /* -> Compressed ckddasd
                                           extension otherwise NULL  */
        u_int   ckd3990:1;              /* 1=Control unit is 3990    */
        u_int   ckdxtdef:1;             /* 1=Define Extent processed */
        u_int   ckdsetfm:1;             /* 1=Set File Mask processed */
        u_int   ckdlocat:1;             /* 1=Locate Record processed */
        u_int   ckdspcnt:1;             /* 1=Space Count processed   */
        u_int   ckdseek:1;              /* 1=Seek command processed  */
        u_int   ckdskcyl:1;             /* 1=Seek cylinder processed */
        u_int   ckdrecal:1;             /* 1=Recalibrate processed   */
        u_int   ckdrdipl:1;             /* 1=Read IPL processed      */
        u_int   ckdxmark:1;             /* 1=End of track mark found */
        u_int   ckdhaeq:1;              /* 1=Search Home Addr Equal  */
        u_int   ckdideq:1;              /* 1=Search ID Equal         */
        u_int   ckdkyeq:1;              /* 1=Search Key Equal        */
        u_int   ckdwckd:1;              /* 1=Write R0 or Write CKD   */
        u_int   ckdtrkof:1;             /* 1=Track ovfl on this blk  */
        u_int   ckdssi:1;               /* 1=Set Special Intercept   */
        u_int   ckdnolazywr:1;          /* 1=Perform updates now     */
        u_int   ckdrdonly:1;            /* 1=Open read only          */
        u_int   ckdwrha:1;              /* 1=Write Home Address      */
                                        /* Line above ISW20030819-1  */
        u_int   ckdfakewr:1;            /* 1=Fake successful write
                                             for read only file      */
        U16     ckdssdlen;              /* #of bytes of data prepared
                                           for Read Subsystem Data   */
};


/*-------------------------------------------------------------------*/
/* Device Group Structure     (just a group of related devices)      */
/*-------------------------------------------------------------------*/
struct DEVGRP {                         /* Device Group Structure    */
        int     members;                /* #of member devices in grp */
        int     acount;                 /* #allocated members in grp */
        void   *grp_data;               /* Group dep data (generic)  */
        DEVBLK *memdev[FLEXIBLE_ARRAY]; /* Member devices            */
};


/*-------------------------------------------------------------------*/
/* Structure definitions for CKD headers                             */
/*-------------------------------------------------------------------*/
struct CKDDASD_DEVHDR {                 /* Device header             */
        BYTE    devid[8];               /* Device identifier         */
        FWORD   heads;                  /* #of heads per cylinder
                                           (bytes in reverse order)  */
        FWORD   trksize;                /* Track size (reverse order)*/
        BYTE    devtype;                /* Last 2 digits of device type
                                           (0x80=3380, 0x90=3390)    */
        BYTE    fileseq;                /* CKD image file sequence no.
                                           (0x00=only file, 0x01=first
                                           file of multiple files)   */
        HWORD   highcyl;                /* Highest cylinder number on
                                           this file, or zero if this
                                           is the last or only file
                                           (bytes in reverse order)  */
        BYTE    resv[492];              /* Reserved                  */
};

struct CKDDASD_TRKHDR {                 /* Track header              */
        BYTE    bin;                    /* Bin number                */
        HWORD   cyl;                    /* Cylinder number           */
        HWORD   head;                   /* Head number               */
};

struct CKDDASD_RECHDR {                 /* Record header             */
        HWORD   cyl;                    /* Cylinder number           */
        HWORD   head;                   /* Head number               */
        BYTE    rec;                    /* Record number             */
        BYTE    klen;                   /* Key length                */
        HWORD   dlen;                   /* Data length               */
};

#define CKDDASD_DEVHDR_SIZE     ((ssize_t)sizeof(CKDDASD_DEVHDR))
#define CKDDASD_TRKHDR_SIZE     ((ssize_t)sizeof(CKDDASD_TRKHDR))
#define CKDDASD_RECHDR_SIZE     ((ssize_t)sizeof(CKDDASD_RECHDR))

/* Null track formats */
#define CKDDASD_NULLTRK_FMT0       0    /* ha r0 r1 eot              */
#define CKDDASD_NULLTRK_FMT1       1    /* ha r0 eot                 */
#define CKDDASD_NULLTRK_FMT2       2    /* linux (3390 only)         */
#define CKDDASD_NULLTRK_FMTMAX     CKDDASD_NULLTRK_FMT2

#define CKDDASD_NULLTRK_SIZE0      (5 + 8 + 8 + 8 + 8)
#define CKDDASD_NULLTRK_SIZE1      (5 + 8 + 8 + 8)
#define CKDDASD_NULLTRK_SIZE2      (5 + 8 + 8 + (12 * (8 + 4096)) + 8)

/*-------------------------------------------------------------------*/
/* Structure definitions for Compressed CKD devices                  */
/*-------------------------------------------------------------------*/
struct CCKDDASD_DEVHDR {                /* Compress device header    */
/*  0 */BYTE             vrm[3];        /* Version Release Modifier  */
/*  3 */BYTE             options;       /* Options byte              */
/*  4 */S32              numl1tab;      /* Size of lvl 1 table       */
/*  8 */S32              numl2tab;      /* Size of lvl 2 tables      */
/* 12 */U32              size;          /* File size                 */
/* 16 */U32              used;          /* File used                 */
/* 20 */U32              free;          /* Position to free space    */
/* 24 */U32              free_total;    /* Total free space          */
/* 28 */U32              free_largest;  /* Largest free space        */
/* 32 */S32              free_number;   /* Number free spaces        */
/* 36 */U32              free_imbed;    /* Imbedded free space       */
/* 40 */FWORD            cyls;          /* Cylinders on device       */
/* 44 */BYTE             nullfmt;       /* Null track format         */
/* 45 */BYTE             compress;      /* Compression algorithm     */
/* 46 */S16              compress_parm; /* Compression parameter     */
/* 48 */BYTE             resv2[464];    /* Reserved                  */
};
#define CCKD_DEVHDR      CCKDDASD_DEVHDR

#define CCKD_VERSION           0
#define CCKD_RELEASE           3
#define CCKD_MODLVL            1

#define CCKD_NOFUDGE           1         /* [deprecated]             */
#define CCKD_BIGENDIAN         2
#define CCKD_SPERRS            32        /* Space errors detected    */
#define CCKD_ORDWR             64        /* Opened read/write since
                                            last chkdsk              */
#define CCKD_OPENED            128

#define CCKD_COMPRESS_NONE     0x00
#define CCKD_COMPRESS_ZLIB     0x01
#define CCKD_COMPRESS_BZIP2    0x02
#define CCKD_COMPRESS_MASK     0x03

#define CCKD_STRESS_MINLEN     4096
#if defined(HAVE_LIBZ)
#define CCKD_STRESS_COMP       CCKD_COMPRESS_ZLIB
#else
#define CCKD_STRESS_COMP       CCKD_COMPRESS_NONE
#endif
#define CCKD_STRESS_PARM1      4
#define CCKD_STRESS_PARM2      2

struct CCKD_L2ENT {                     /* Level 2 table entry       */
        U32              pos;           /* Track offset              */
        U16              len;           /* Track length              */
        U16              size;          /* Track size  (size >= len) */
};

struct CCKD_FREEBLK {                   /* Free block (file)         */
        U32              pos;           /* Position next free blk    */
        U32              len;           /* Length this free blk      */
};

struct CCKD_IFREEBLK {                  /* Free block (internal)     */
        U32              pos;           /* Position next free blk    */
        U32              len;           /* Length this free blk      */
        int              prev;          /* Index to prev free blk    */
        int              next;          /* Index to next free blk    */
        int              pending;       /* 1=Free pending (don't use)*/
};

struct CCKD_RA {                        /* Readahead queue entry     */
        DEVBLK          *dev;           /* Readahead device          */
        int              trk;           /* Readahead track           */
        int              prev;          /* Index to prev entry       */
        int              next;          /* Index to next entry       */
};

typedef  U32          CCKD_L1ENT;       /* Level 1 table entry       */
typedef  CCKD_L1ENT   CCKD_L1TAB[];     /* Level 1 table             */
typedef  CCKD_L2ENT   CCKD_L2TAB[256];  /* Level 2 table             */
typedef  char         CCKD_TRACE[128];  /* Trace table entry         */

#define CCKDDASD_DEVHDR_SIZE   ((ssize_t)sizeof(CCKDDASD_DEVHDR))
#define CCKD_DEVHDR_SIZE       CCKDDASD_DEVHDR_SIZE
#define CCKD_DEVHDR_POS        CKDDASD_DEVHDR_SIZE
#define CCKD_L1ENT_SIZE        ((ssize_t)sizeof(CCKD_L1ENT))
#define CCKD_L1TAB_POS         ((CCKD_DEVHDR_POS)+(CCKD_DEVHDR_SIZE))
#define CCKD_L2ENT_SIZE        ((ssize_t)sizeof(CCKD_L2ENT))
#define CCKD_L2TAB_SIZE        ((ssize_t)sizeof(CCKD_L2TAB))
#define CCKD_FREEBLK_SIZE      ((ssize_t)sizeof(CCKD_FREEBLK))
#define CCKD_FREEBLK_ISIZE     ((ssize_t)sizeof(CCKD_IFREEBLK))
#define CCKD_IFREEBLK_SIZE     (CCKD_FREEBLK_ISIZE)

/* Flag bits */
#define CCKD_SIZE_EXACT         0x01    /* Space obtained is exact   */
#define CCKD_SIZE_ANY           0x02    /* Space can be any size     */
#define CCKD_L2SPACE            0x04    /* Space for a l2 table      */

/* adjustable values */

#define CCKD_FREE_MIN_SIZE     96       /* Minimum free space size   */
#define CCKD_FREE_MIN_INCR     32       /* Added for each 1024 spaces*/
#define CCKD_COMPRESS_MIN      512      /* Track images smaller than
                                           this won't be compressed  */
#define CCKD_MAX_SF            8        /* Maximum number of shadow
                                           files: 0 to 9 [0 disables
                                           shadow file support]      */
#define CCKD_MAX_READAHEADS    16       /* Max readahead trks        */
#define CCKD_MAX_RA_SIZE       16       /* Readahead queue size      */
#define CCKD_MAX_RA            9        /* Max readahead threads     */
#define CCKD_MAX_WRITER        9        /* Max writer threads        */
#define CCKD_MAX_GCOL          1        /* Max garbage collectors    */
#define CCKD_MAX_TRACE         200000   /* Max nbr trace entries     */
#define CCKD_MAX_FREEPEND      4        /* Max free pending cycles   */

#define CCKD_MIN_READAHEADS    0        /* Min readahead trks        */
#define CCKD_MIN_RA            0        /* Min readahead threads     */
#define CCKD_MIN_WRITER        1        /* Min writer threads        */
#define CCKD_MIN_GCOL          0        /* Min garbage collectors    */

#define CCKD_DEFAULT_RA_SIZE   4        /* Readahead queue size      */
#define CCKD_DEFAULT_RA        2        /* Default number readaheads */
#define CCKD_DEFAULT_WRITER    2        /* Default number writers    */
#define CCKD_DEFAULT_GCOL      1        /* Default number garbage
                                              collectors             */
#define CCKD_DEFAULT_GCOLWAIT  10       /* Default wait (seconds)    */
#define CCKD_DEFAULT_GCOLPARM  0        /* Default adjustment parm   */
#define CCKD_DEFAULT_READAHEADS 2       /* Default nbr to read ahead */
#define CCKD_DEFAULT_FREEPEND  -1       /* Default freepend cycles   */

#define CFBA_BLOCK_NUM         120      /* Number fba blocks / group */
#define CFBA_BLOCK_SIZE        61440    /* Size of a block group 60k */
                                        /* Number of bytes in an fba
                                           block group.  Probably
                                           should be a multiple of 512
                                           but has to be < 64K       */

struct CCKDBLK {                        /* Global cckd dasd block    */
        BYTE             id[8];         /* "CCKDBLK "                */
        DEVBLK          *dev1st;        /* 1st device in cckd queue  */
        unsigned int     batch:1,       /* 1=called in batch mode    */
                         sfmerge:1,     /* 1=sf-* merge              */
                         sfforce:1;     /* 1=sf-* force              */
        int              sflevel;       /* sfk xxxx level            */

        BYTE             comps;         /* Supported compressions    */
        BYTE             comp;          /* Override compression      */
        int              compparm;      /* Override compression parm */

        LOCK             gclock;        /* Garbage collector lock    */
        COND             gccond;        /* Garbage collector cond    */
        int              gcs;           /* Number garbage collectors */
        int              gcmax;         /* Max garbage collectors    */
        int              gcwait;        /* Wait time in seconds      */
        int              gcparm;        /* Adjustment parm           */

        LOCK             wrlock;        /* I/O lock                  */
        COND             wrcond;        /* I/O condition             */
        int              wrpending;     /* Number writes pending     */
        int              wrwaiting;     /* Number writers waiting    */
        int              wrs;           /* Number writer threads     */
        int              wrmax;         /* Max writer threads        */
        int              wrprio;        /* Writer thread priority    */

        LOCK             ralock;        /* Readahead lock            */
        COND             racond;        /* Readahead condition       */
        int              ras;           /* Number readahead threads  */
        int              ramax;         /* Max readahead threads     */
        int              rawaiting;     /* Number threads waiting    */
        int              ranbr;         /* Readahead queue size      */
        int              readaheads;    /* Nbr tracks to read ahead  */
        CCKD_RA          ra[CCKD_MAX_RA_SIZE];    /* Readahead queue */
        int              ra1st;         /* First readahead entry     */
        int              ralast;        /* Last readahead entry      */
        int              rafree;        /* Free readahead entry      */

        LOCK             devlock;       /* Device chain lock         */
        COND             devcond;       /* Device chain condition    */
        int              devusers;      /* Number shared users       */
        int              devwaiters;    /* Number of waiters         */

        int              freepend;      /* Number freepend cycles    */
        int              nostress;      /* 1=No stress writes        */
        int              linuxnull;     /* 1=Always check nulltrk    */
        int              fsync;         /* 1=Perform fsync()         */
        COND             termcond;      /* Termination condition     */

        U64              stats_switches;       /* Switches           */
        U64              stats_cachehits;      /* Cache hits         */
        U64              stats_cachemisses;    /* Cache misses       */
        U64              stats_readaheads;     /* Readaheads         */
        U64              stats_readaheadmisses;/* Readahead misses   */
        U64              stats_syncios;        /* Synchronous i/os   */
        U64              stats_synciomisses;   /* Missed syncios     */
        U64              stats_iowaits;        /* Waits for i/o      */
        U64              stats_cachewaits;     /* Waits for cache    */
        U64              stats_stresswrites;   /* Writes under stress*/
        U64              stats_l2cachehits;    /* L2 cache hits      */
        U64              stats_l2cachemisses;  /* L2 cache misses    */
        U64              stats_l2reads;        /* L2 reads           */
        U64              stats_reads;          /* Number reads       */
        U64              stats_readbytes;      /* Bytes read         */
        U64              stats_writes;         /* Number writes      */
        U64              stats_writebytes;     /* Bytes written      */
        U64              stats_gcolmoves;      /* Spaces moved       */
        U64              stats_gcolbytes;      /* Bytes moved        */

        CCKD_TRACE      *itrace;        /* Internal trace table      */
        CCKD_TRACE      *itracep;       /* Current pointer           */
        CCKD_TRACE      *itracex;       /* End of trace table        */
        int              itracen;       /* Number of entries         */

        int              bytemsgs;      /* Limit for `byte 0' msgs   */
};

struct CCKDDASD_EXT {                   /* Ext for compressed ckd    */
        DEVBLK          *devnext;       /* cckd device queue         */
        unsigned int     ckddasd:1,     /* 1=CKD dasd                */
                         fbadasd:1,     /* 1=FBA dasd                */
                         ioactive:1,    /* 1=Channel program active  */
                         bufused:1,     /* 1=newbuf was used         */
                         updated:1,     /* 1=Update occurred         */
                         merging:1,     /* 1=File merge in progress  */
                         stopping:1,    /* 1=Device is closing       */
                         notnull:1,     /* 1=Device has track images */
                         l2ok:1,        /* 1=All l2s below bounds    */
                         sfmerge:1,     /* 1=sf-xxxx merge           */
                         sfforce:1;     /* 1=sf-xxxx force           */
        int              sflevel;       /* sfk xxxx level            */
        LOCK             filelock;      /* File lock                 */
        LOCK             iolock;        /* I/O lock                  */
        COND             iocond;        /* I/O condition             */
        long long        maxsize;       /* Maximum file size         */
        int              iowaiters;     /* Number I/O waiters        */
        int              wrpending;     /* Number writes pending     */
        int              ras;           /* Number readaheads active  */
        int              sfn;           /* Number active shadow files*/
        int              sfx;           /* Active level 2 file index */
        int              l1x;           /* Active level 2 table index*/
        CCKD_L2ENT      *l2;            /* Active level 2 table      */
        int              l2active;      /* Active level 2 cache entry*/
        off_t            l2bounds;      /* L2 tables boundary        */
        int              active;        /* Active cache entry        */
        BYTE            *newbuf;        /* Uncompressed buffer       */
        unsigned int     freemin;       /* Minimum free space size   */
        CCKD_IFREEBLK   *free;          /* Internal free space chain */
        int              freenbr;       /* Number free space entries */
        int              free1st;       /* Index of 1st entry        */
        int              freelast;      /* Index of last entry       */
        int              freeavail;     /* Index of available entry  */
        int              lastsync;      /* Time of last sync         */
        int              ralkup[CCKD_MAX_RA_SIZE];/* Lookup table    */
        int              ratrk;         /* Track to readahead        */
        unsigned int     totreads;      /* Total nbr trk reads       */
        unsigned int     totwrites;     /* Total nbr trk writes      */
        unsigned int     totl2reads;    /* Total nbr l2 reads        */
        unsigned int     cachehits;     /* Cache hits                */
        unsigned int     readaheads;    /* Number trks read ahead    */
        unsigned int     switches;      /* Number trk switches       */
        unsigned int     misses;        /* Number readahead misses   */
        int              fd[CCKD_MAX_SF+1];      /* File descriptors */
        BYTE             swapend[CCKD_MAX_SF+1]; /* Swap endian flag */
        BYTE             open[CCKD_MAX_SF+1];    /* Open flag        */
        int              reads[CCKD_MAX_SF+1];   /* Nbr track reads  */
        int              l2reads[CCKD_MAX_SF+1]; /* Nbr l2 reads     */
        int              writes[CCKD_MAX_SF+1];  /* Nbr track writes */
        CCKD_L1ENT      *l1[CCKD_MAX_SF+1];      /* Level 1 tables   */
        CCKDDASD_DEVHDR  cdevhdr[CCKD_MAX_SF+1]; /* cckd device hdr  */
};

#define CCKD_OPEN_NONE         0
#define CCKD_OPEN_RO           1
#define CCKD_OPEN_RD           2
#define CCKD_OPEN_RW           3

#ifdef EXTERNALGUI
struct GUISTAT
{
    char*   pszOldStatStr;
    char*   pszNewStatStr;
#define     GUI_STATSTR_BUFSIZ    256
    char    szStatStrBuff1[GUI_STATSTR_BUFSIZ];
    char    szStatStrBuff2[GUI_STATSTR_BUFSIZ];
};
#endif // EXTERNALGUI


#endif // _HSTRUCTS_H
