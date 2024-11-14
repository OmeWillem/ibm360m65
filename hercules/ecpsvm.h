// $Id: ecpsvm.h 4102 2006-12-08 09:43:35Z jj $
//
// $Log$

#ifndef __ECPSVM_H__
#define __ECPSVM_H__

/* CR6 Definitions (VMBLOK style) */
#define VMMFE 0x80
#define VMMPROB 0x40
#define VMMNOSK 0x20
#define VMM360 0x10
#define VMMSVC 0x08
#define VMMSHADT 0x04
#define VMMCPAST 0x02
#define VMMVTMR 0x01

/* PSA Usefull Values */
#define IOOPSW   0x038

#define QUANTUMR 0x04C  /* Usefull little unused space for MVCing NEW ITIMER */
#define INTTIMER 0x050
#define QUANTUM  0x054  /* Usefull little unused space for MVCing OLD ITIMER */

/* PSA Displacements used by ECPS:VM */
/* PSA Entries used by DISPx Instructions */
#define CPSTATUS 0x348
/* PSA + 348 : CPSTATUS */
#define CPWAIT 0x80     /* CP IN WAIT STATE */
#define CPRUN  0x40     /* RUNUSER is use running */
#define CPEX   0x20     /* CPEXBLOK RUNNING */
#define CPSUPER 0x08    /* Supervisor State */

/* PSA + 349 : SYSTEM EXTENDING FREE STORAGE BYTE */
/* Note : PSA+0X349 = 0xFF if storage extending */
#define XTENDLOCK 0x349
#define XTENDLOCKSET 0xff

/* PSA + 34A : CPSTAT2 */
#define CPSTAT2 0x34A
#define CPMICAVL 0x80
#define CPMICON  0x40
#define CPSHRLK 0x20
#define CPASTAVL 0x08
#define CPASTON 0x04

/* RUNPSW */
/* PSW used during dispatch */
#define RUNPSW 0x330

/* RUNUSER PSA+338 */
#define RUNUSER 0x338

/* RUNCR0, RUNCR1 */
/* CR0 & CR1 used during dispatch */
#define RUNCR0 0x340
#define RUNCR1 0x344

/* ASYSVM : PSA+37C */
#define ASYSVM 0x37C

/* PSA + X'3D4' - ASSISTS STUFF */
#define CPCREG0 0x3D4
#define CPCREG6 0x3D8
#define CPCREG8 0x3DC
#define TIMEDISP 0x3E0
#define ASVCLIST 0x3E4
#define AVMALIST 0x3E8
#define LASTUSER 0x3EC

/* PSA + 328 : PROBTIME */
/* Total time spent in problem state (2's complement) */
#define PROBTIME 0x328

/* PSA + 69D : APSTAT2 - Machine check recov & PTLB Required */
#define APSTAT2  0x69D
#define CPMCHLK  0x10
#define CPPTLBR  0x02

/* PSA + 6A8 : PROBSTRT */
/* TOD Clock at Proble state entry */
#define PROBSTRT 0x6A8

/* PSA + 6D0 : STACKVM - GPR11 Backup for dispatcher */
#define STACKVM 0x6D0

/* VMBLOK Displacements */
#define VMQFPNT         0x000
#define VMQBPNT         0x004
#define VMPNT           0x008
#define VMECEXT         0x00C
#define VMVCR0 VMECEXT
#define VMSEG           0x010
#define VMSIZE          0x014
#define VMCHSTRT        0x018
#define VMCUSTRT        0x01C
#define VMDVSTRT        0x020
#define VMTERM          0x024
#define VMVTERM         0x028
#define VMTRMID         0x02A
#define VMTLEND         0x02C
#define VMTLDEL         0x02D
#define VMTCDEL         0x02E
#define VMTESCP         0x02F
#define VMCHCNT         0x030
#define VMCUCNT         0x032
#define VMDVCNT         0x034
#define VMIOACTV        0x036
#define VMCHTBL         0x038
#define VMRSTAT         0x058
    /* Flags defined in VMRSTAT */
#define VMCFWAIT 0x80
#define VMPGWAIT 0x40
#define VMIOWAIT 0x20
#define VMPSWAIT 0x10
#define VMEXWAIT 0x08
#define VMLOGON  0x04
#define VMLOGOFF 0x02
#define VMIDLE   0x01
#define VMCPWAIT (VMCFWAIT|VMPGWAIT|VMIOWAIT|VMEXWAIT|VMLOGOFF|VMLOGON)
#define VMNORUN  (VMCPWAIT|VMPSWAIT)
#define VMLONGWT (VMCFWAIT|VMLOGON|VMLOGOFF|VMIDLE)

#define VMDSTAT         0x059
    /* Flags defined in VMDSTAT */
#define VMDSP   0x80
#define VMTSEND 0x40
#define VMQSEND 0x20
#define VMTIO   0x10
#define VMRUN   0x08
#define VMINQ   0x04
#define VMELIG  0x02
#define VMDSPCH 0x01

#define VMOSTAT         0x05A
    /* Flags defined in VMOSTAT */
#define VMSYSOP 0x80
#define VMSHR   0x40
#define VMSLEEP 0x20
#define VMDISC  0x10
#define VMCFRUN 0x08
#define VMVIRCF 0x04
#define VMCF    0x02
#define VMKILL  0x01

#define VMQSTAT         0x05B
    /* Flags defined in VMQSTAT */
#define VMPRIDSP 0x80
#define VMAUTOLOG 0x40
#define VMWSERNG 0x20
#define VMDLDRP 0x10
#define VMWSCHG 0x08
#define VMINHMIG 0x04
#define VMCFREAD 0x02
#define VMPA2APL 0x01

#define VMPSTAT         0x05C
    /* Flags defined in VMPSTAT */
#define VMISAM 0x80
#define VMV370R 0x40
#define VMRPAGE 0x20
#define VMREAL 0x10
#define VMNOTRAN 0x08
#define VMNSHR 0x04
#define VMACCOUN 0x02
#define VMPAGEX 0x01

#define VMESTAT         0x05D
    /* Flags defined in VMESTAT */
#define VMSHADT 0x80
#define VMPERCM 0x40
#define VMBADCR0 0x20
#define VMMICSVC 0x10
#define VMEXTCM 0x08
#define VMNEWCR0 0x04
#define VMINVSEG 0x02
#define VMINVPAG 0x01
#define VMECZAP ~VMMICSVC

#define VMTRCTL         0x05E
    /* Bits defined in VMTRCTL */
#define VMTRPER 0x80
#define VMTRSVC 0x40
#define VMTRPRG 0x20
#define VMTRIO  0x10
#define VMTREX  0x08
#define VMTRPRV 0x04
#define VMTRSIO 0x02
#define VMTRBRIN 0x01
#define VMTRINT (VMTRSVC|VMTRPRG|VMTRIO|VMTREX)

#define VMMLEVEL        0x05F
#define VMQLEVEL        0x060
    /* Bits defined in VMQLEVEL */
#define VMQ1    0x80
#define VMCOMP  0x40
#define VMHIPRI 0x20
#define VMLOPRI 0x10
#define VMAEX   0x08
#define VMAEXP  0x04
#define VMAQ3   0x02
#define VMDROP1 0x02
#define VMFS    0x01

#define VM_RESERVED1    0x061
#define VMTLEVEL        0x062
   /* Flags defined for VMTLEVEL */
#define VMTON   0x80
#define VMRON   0x40
#define VMCPUTMR 0x20
#define VMSTMPI 0x08
#define VMSTMPT 0x04
#define VMTMRINT 0x01

#define VMPEND          0x063
   /* Flags defined in VMPEND */
#define VMDEFSTK 0x80
#define VMPERPND 0x40
#define VMPRGPND 0x20
#define VMSVCPND 0x10
#define VMPGPND  0x08
#define VMIOPND  0x02
#define VMEXTPND 0x01

#define VMLOCKER        0x064
#define VMFSTAT         0x068
#define VMMLVL2         0x069
#define VMIOINT         0x06A
#define VMTIMER         0x06C
#define VMVTIME         0x070
#define VMTMOUTQ        0x078
#define VMTTIME         0x080
#define VMTMINQ         0x088
#define VMTSOUTQ VMTMINQ
#define VMTODINQ        0x090
#define VMINST          0x098
#define VMUPRIOR        0x09E
#define VMPSWCT         0x09F
#define VMTREXT         0x0A0
#define VMADSTOP        0x0A4
#define VMPSW           0x0A8
#define VMGPRS          0x0B0
#define VMFPRS          0x0F0
#define VMUSER          0x110
#define VMACCNT         0x118
#define VMDIST          0x120


#define VMMICRO         0x17C
#define VMMCR6 VMMICRO
#define VMMADDR VMMICRO+1

#define VMPXINT         0x184

#define VMNOECPS        0x1A7

#define VMSTKCNT        0x1CC


/* ECBLOK Specifics */
#define EXTSHCR0 0x40
#define EXTSHCR1 0x44


#endif
