/* SERVICE.H    (c) Copyright Jan Jaeger, 1999-2009                  */
/*              Service Processor Architectured fields               */

// $Id: service.h 5452 2009-08-12 09:53:50Z rbowler $

#if !defined(_SERVICE_H)

#define _SERVICE_H

/*-------------------------------------------------------------------*/
/* Service Call Logical Processor command word definitions           */
/*-------------------------------------------------------------------*/
#define SCLP_READ_SCP_INFO      0x00020001
#define SCLP_READ_IFL_INFO      0x00120001
#define SCLP_READ_CHP_INFO      0x00030001
#define SCLP_READ_CSI_INFO      0x001C0001

#define SCLP_READ_XST_MAP       0x00250001

#define SCLP_WRITE_EVENT_DATA   0x00760005
#define SCLP_READ_EVENT_DATA    0x00770005
#define SCLP_WRITE_EVENT_MASK   0x00780005

#define SCLP_DECONFIGURE_CPU    0x00100001
#define SCLP_CONFIGURE_CPU      0x00110001

#define SCLP_DISCONNECT_VF      0x001A0001
#define SCLP_CONNECT_VF         0x001B0001

#define SCLP_COMMAND_MASK       0xFFFF00FF
#define SCLP_COMMAND_CLASS      0x000000FF
#define SCLP_RESOURCE_MASK      0x0000FF00
#define SCLP_RESOURCE_SHIFT     8

/*-------------------------------------------------------------------*/
/* Service Call Control Block structure definitions                  */
/*-------------------------------------------------------------------*/
typedef struct _SCCB_HEADER {
        HWORD   length;                 /* Total length of SCCB      */
        BYTE    flag;                   /* Flag byte                 */
        BYTE    resv1[2];               /* Reserved                  */
        BYTE    type;                   /* Request type              */
        BYTE    reas;                   /* Reason code               */
        BYTE    resp;                   /* Response class code       */
    } SCCB_HEADER;

/* Bit definitions for SCCB header flag byte */
#define SCCB_FLAG_SYNC          0x80    /* Synchronous request       */

/* Bit definitions for SCCB header request type */
#define SCCB_TYPE_VARIABLE      0x80    /* Variable request          */

/* Bit definitions for SCCB header reason code */
#define SCCB_REAS_NONE          0x00    /* No reason                 */
#define SCCB_REAS_NOT_PGBNDRY   0x01    /* SCCB crosses page boundary*/
#define SCCB_REAS_ODD_LENGTH    0x02    /* Length not multiple of 8  */
#define SCCB_REAS_TOO_SHORT     0x03    /* Length is inadequate      */
#define SCCB_REAS_NOACTION      0x02    /* Resource in req. state    */
#define SCCB_REAS_STANDBY       0x04    /* Resource in standby state */
#define SCCB_REAS_INVALID_CMD   0x01    /* Invalid SCLP command code */
#define SCCB_REAS_INVALID_RSCP  0x03    /* Invalid resource in parm  */
#define SCCB_REAS_IMPROPER_RSC  0x05    /* Resource in improper state*/
#define SCCB_REAS_INVALID_RSC   0x09    /* Invalid resource          */

/* Bit definitions for SCCB header response class code */
#define SCCB_RESP_BLOCK_ERROR   0x00    /* Data block error          */
#define SCCB_RESP_INFO          0x10    /* Information returned      */
#define SCCB_RESP_COMPLETE      0x20    /* Command complete          */
#define SCCB_RESP_BACKOUT       0x40    /* Command backed out        */
#define SCCB_RESP_REJECT        0xF0    /* Command reject            */

/* SCP information data area */
typedef struct _SCCB_SCP_INFO {
        HWORD   realinum;               /* Number of real storage
                                           increments installed      */
        BYTE    realiszm;               /* Size of each real storage
                                           increment in MB           */
        BYTE    realbszk;               /* Size of each real storage
                                           block in KB               */
        HWORD   realiint;               /* Real storage increment
                                           block interleave interval */
        HWORD   resv2;                  /* Reserved                  */
        HWORD   numcpu;                 /* Number of CPUs installed  */
        HWORD   offcpu;                 /* Offset from start of SCCB
                                           to CPU information array  */
        HWORD   numhsa;                 /* Number of HSAs            */
        HWORD   offhsa;                 /* Offset from start of SCCB
                                           to HSA information array  */
        BYTE    loadparm[8];            /* Load parameter            */
        FWORD   xpndinum;               /* Number of expanded storage
                                           increments installed      */
        FWORD   xpndsz4K;               /* Number of 4KB blocks in an
                                           expanded storage increment*/
        HWORD   xpndenum;               /* Number of expanded storage
                                           elements installed        */
        HWORD   resv3;                  /* Reserved                  */
        HWORD   vectssiz;               /* Vector section size       */
        HWORD   vectpsum;               /* Vector partial sum number */
        BYTE    ifm[8];                 /* Installed facilities      */
        BYTE    resv4[8];               /* Reserved                  */
        HWORD   maxresgp;               /* Maximum resource group    */
        BYTE    resv5[6];               /* Reserved                  */
        HWORD   nummpf;                 /* Number of entries in MPF
                                           information array         */
        HWORD   offmpf;                 /* Offset from start of SCCB
                                           to MPF information array  */
        BYTE    resv6[4];               /* Reserved                  */
        BYTE    cfg[6];                 /* Config characteristics    */
        FWORD   rcci;                   /* Capacity                  */
        BYTE    cfg11;                  /* Config char. byte 11      */
        BYTE    numcrl;                 /* Max #of copy and reassign
                                           list elements allowed     */
        FWORD   etrtol;                 /* ETR sync check tolerance  */
        BYTE    resv60[3];
        BYTE    maxvm;                  /* Max guest storage size
                                           >= 31 and <= 64 (2**pow)-1
                                           is the max supported
                                           guest real size. 0 means
                                           not constrained.          */
        FWORD   grzm;                   /* Addess increment size in
                                           units of 1M, valid only
                                           if realiszm is zero       */
        DBLWRD  grnmx;                  /* Maximum increment number
                                           when it is larger then
                                           64K or when ESAME is on   */
        BYTE    resv8[16];              /* Reserved                  */
    } SCCB_SCP_INFO;

/* Bit definitions for installed facilities */
#define SCCB_IFM0_CHANNEL_PATH_INFORMATION              0x80
#define SCCB_IFM0_CHANNEL_PATH_SUBSYSTEM_COMMAND        0x40
#define SCCB_IFM0_CHANNEL_PATH_RECONFIG                 0x20
#define SCCB_IFM0_CPU_INFORMATION                       0x08
#define SCCB_IFM0_CPU_RECONFIG                          0x04
#define SCCB_IFM1_SIGNAL_ALARM                          0x80
#define SCCB_IFM1_WRITE_OPERATOR_MESSAGE                0x40
#define SCCB_IFM1_STORE_STATUS_ON_LOAD                  0x20
#define SCCB_IFM1_RESTART_REASONS                       0x10
#define SCCB_IFM1_INSTRUCTION_ADDRESS_TRACE_BUFFER      0x08
#define SCCB_IFM1_LOAD_PARAMETER                        0x04
#define SCCB_IFM1_READ_AND_WRITE_DATA                   0x02
#define SCCB_IFM2_REAL_STORAGE_INCREMENT_RECONFIG       0x80
#define SCCB_IFM2_REAL_STORAGE_ELEMENT_INFO             0x40
#define SCCB_IFM2_REAL_STORAGE_ELEMENT_RECONFIG         0x20
#define SCCB_IFM2_COPY_AND_REASSIGN_STORAGE             0x10
#define SCCB_IFM2_EXTENDED_STORAGE_USABILITY_MAP        0x08
#define SCCB_IFM2_EXTENDED_STORAGE_ELEMENT_INFO         0x04
#define SCCB_IFM2_EXTENDED_STORAGE_ELEMENT_RECONFIG     0x02
#define SCCB_IFM2_COPY_AND_REASSIGN_STORAGE_LIST        0x01
#define SCCB_IFM3_READ_WRITE_EVENT_FEATURE              0x40
#define SCCB_IFM3_EXTENDED_STORAGE_USABILITY_MAP_EXT    0x20
#define SCCB_IFM3_READ_RESOURCE_GROUP_INFO              0x08
#define SCCB_IFM4_READ_STORAGE_STATUS                   0x80

/* Bit definitions for configuration characteristics */
#define SCCB_CFG0_LOGICALLY_PARTITIONED                 0x80
#define SCCB_CFG0_SUPPRESSION_ON_PROTECTION             0x20
#define SCCB_CFG0_INITIATE_RESET                        0x10
#define SCCB_CFG0_STORE_CHANNEL_SUBSYS_CHARACTERISTICS  0x08
#define SCCB_CFG0_FAST_SYNCHRONOUS_DATA_MOVER           0x01
#define SCCB_CFG0_MVPG_FOR_ALL_GUESTS                   0x04
#define SCCB_CFG0_UNKNOWN_BUT_SET_UNDER_VM              0x02
#define SCCB_CFG1_CSLO                                  0x40
#define SCCB_CFG2_DEVICE_ACTIVE_ONLY_MEASUREMENT        0x40
#define SCCB_CFG2_CALLED_SPACE_IDENTIFICATION           0x02
#define SCCB_CFG2_CHECKSUM_INSTRUCTION                  0x01
#define SCCB_CFG3_RESUME_PROGRAM                        0x80
#define SCCB_CFG3_IMMEDIATE_AND_RELATIVE                0x10
#define SCCB_CFG3_EXTENDED_FLOATING_POINT               0x02
#define SCCB_CFG3_EXTENDED_LOGICAL_COMPUTATION_FACILITY 0x01
#define SCCB_CFG4_EXTENDED_TOD_CLOCK                    0x80
#define SCCB_CFG4_EXTENDED_TRANSLATION                  0x40
#define SCCB_CFG4_LOAD_REVERSED_FACILITY                0x20
#define SCCB_CFG4_STORE_SYSTEM_INFORMATION              0x08
#define SCCB_CFG4_LPAR_CLUSTERING                       0x02
#define SCCB_CFG4_IFA_FACILITY                          0x01
#define SCCB_CFG5_SENSE_RUNNING_STATUS                  0x08
#define SCCB_CFG5_ESAME                                 0x01
#define SCCB_CFGB_PER_3                                 0x04
#define SCCB_CFGB_LOAD_WITH_DUMP                        0x02
#define SCCB_CFGB_LIST_DIRECTED_IPL                     0x01

/* CPU information array entry */
typedef struct _SCCB_CPU_INFO {
        BYTE    cpa;                    /* CPU address               */
        BYTE    tod;                    /* TOD clock number          */
        BYTE    cpf[12];                /* RCPU facility map         */
        BYTE    ptyp;                   /* Processor type            */
        BYTE    ksid;                   /* Crypto unit identifier    */
    } SCCB_CPU_INFO;

/* Bit definitions for CPU installed features */
#define SCCB_CPF0_SIE_370_MODE                          0x80
#define SCCB_CPF0_SIE_XA_MODE                           0x40
#define SCCB_CPF0_SIE_SET_II_370_MODE                   0x20
#define SCCB_CPF0_SIE_SET_II_XA_MODE                    0x10
#define SCCB_CPF0_SIE_NEW_INTERCEPT_FORMAT              0x08
#define SCCB_CPF0_STORAGE_KEY_ASSIST                    0x04
#define SCCB_CPF0_MULTIPLE_CONTROLLED_DATA_SPACE        0x02
#define SCCB_CPF1_IO_INTERPRETATION_LEVEL_2             0x40
#define SCCB_CPF1_GUEST_PER_ENHANCED                    0x20
#define SCCB_CPF1_SIGP_INTERPRETATION_ASSIST            0x08
#define SCCB_CPF1_RCP_BYPASS_FACILITY                   0x04
#define SCCB_CPF1_REGION_RELOCATE_FACILITY              0x02
#define SCCB_CPF1_EXPEDITE_TIMER_PROCESSING             0x01
#define SCCB_CPF2_EXPEDITE_RUN_PROCESSING               0x04
#define SCCB_CPF3_PRIVATE_SPACE_FEATURE                 0x80
#define SCCB_CPF3_FETCH_ONLY_BIT                        0x40
#define SCCB_CPF3_PER2_INSTALLED                        0x01
#define SCCB_CPF4_OMISION_GR_ALTERATION_370             0x80
#define SCCB_CPF5_GUEST_WAIT_STATE_ASSIST               0x40

/* Definitions for processor type code */
#define SCCB_PTYP_CP                                    0
#define SCCB_PTYP_ICF                                   1
#define SCCB_PTYP_IFA                                   2
#define SCCB_PTYP_IFL                                   3
#define SCCB_PTYP_SUP                                   5
#define SCCB_PTYP_MAX                                   5 /*(maximum value)*/

/* Definitions for crypto unit identifier */
#define SCCB_KSID_CRYPTO_UNIT_ID                        0x01

/* HSA information array entry */
typedef struct _SCCB_HSA_INFO {
        HWORD   hssz;                   /* Size of HSA in 4K blocks  */
        FWORD   ahsa;                   /* Address of HSA            */
    } SCCB_HSA_INFO;

/* MPF information array entry */
typedef struct _SCCB_MPF_INFO {
        HWORD   mpfy;                   /* MPF info array entry      */
    } SCCB_MPF_INFO;

/* Channel path information data area */
typedef struct _SCCB_CHP_INFO {
        BYTE    installed[32];          /* Channels installed bits   */
        BYTE    standby[32];            /* Channels standby bits     */
        BYTE    online[32];             /* Channels online bits      */
    } SCCB_CHP_INFO;

/* Channel path information data area */
typedef struct _SCCB_CHSET {
        BYTE    chanset0a[32];          /* 370 channel set 0A        */
        BYTE    chanset1a[32];          /* 370 channel set 1A        */
        BYTE    chanset0b[32];          /* 370 channel set 0B        */
        BYTE    chanset1b[32];          /* 370 channel set 1B        */
        BYTE    csconfig;               /* Channel set configuration */
        BYTE    resv[23];               /* Reserved, set to zero     */
    } SCCB_CHSET_INFO;

/* Read Channel Subsystem Information data area */
typedef struct _SCCB_CSI_INFO {
        BYTE    csif[8];                /* Channel Subsystem installed
                                           facility field            */
        BYTE    resv[48];
    } SCCB_CSI_INFO;

/* Bit definitions for channel subsystem installed facilities */
#define SCCB_CSI0_CANCEL_IO_REQUEST_FACILITY            0x02
#define SCCB_CSI0_CONCURRENT_SENSE_FACILITY             0x01


#endif /*!defined(_SERVICE_H)*/
