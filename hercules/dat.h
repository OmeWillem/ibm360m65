/* DAT.H        (c) Copyright Roger Bowler, 1999-2009                */
/*              ESA/390 Dynamic Address Translation                  */

/* Interpretive Execution - (c) Copyright Jan Jaeger, 1999-2009      */
/* z/Architecture support - (c) Copyright Jan Jaeger, 1999-2009      */

// $Id: dat.h 5549 2009-12-16 16:50:50Z ivan $

/*-------------------------------------------------------------------*/
/* This module implements the DAT, ALET, and ASN translation         */
/* functions of the ESA/390 architecture, described in the manual    */
/* SA22-7201-04 ESA/390 Principles of Operation.  The numbers in     */
/* square brackets in the comments refer to sections in the manual.  */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* Additional credits:                                               */
/*      S/370 DAT support by Jay Maynard (as described in            */
/*      GA22-7000 System/370 Principles of Operation)                */
/*      Clear remainder of ASTE when ASF=0 - Jan Jaeger              */
/*      S/370 DAT support when running under SIE - Jan Jaeger        */
/*      ESAME DAT support by Roger Bowler (SA22-7832)                */
/*      ESAME ASN authorization and ALET translation - Roger Bowler  */
/*-------------------------------------------------------------------*/

// $Log$
// Revision 1.112  2008/12/08 20:38:20  ivan
// Fix SIE DAT Issue with ESA/390 Guest on z/Arch host with >2GB of storage
//
// Revision 1.111  2008/03/16 00:04:37  rbowler
// Replace ACC_ARMODE by USE_ARMODE for LPTEA
//
// Revision 1.110  2008/03/15 23:41:16  rbowler
// Correct end function comment for logical_to_main
//
// Revision 1.108  2007/08/31 10:01:01  ivan
// Throw an addressing exception when a SIE host->guest DAT points beyond
// addressable storage
//
// Revision 1.107  2007/06/23 00:04:08  ivan
// Update copyright notices to include current year (2007)
//
// Revision 1.106  2007/06/06 22:14:57  gsmith
// Fix SYNCHRONIZE_CPUS when numcpu > number of host processors - Greg
//
// Revision 1.105  2007/03/21 01:28:20  gsmith
// Fix missed (acctype != ACC...) compares
//
// Revision 1.104  2007/03/20 23:46:15  gsmith
// Don't update TLB if ACC_NOTLB
//
// Revision 1.103  2007/03/20 22:27:25  gsmith
// Simplify some code in logical_to_main
//
// Revision 1.102  2007/03/20 22:23:32  gsmith
// Redefine ACC_ and ACCTYPE_ macros
//
// Revision 1.101  2007/03/20 02:06:02  gsmith
// Rename IS_MCDS macro to MULTIPLE_CONTROLLED_DATA_SPACE
//
// Revision 1.100  2007/03/18 18:47:43  gsmith
// Simplify MULTIPLE_CONTROLLED_DATA_SPACE tests
//
// Revision 1.99  2007/03/18 00:41:53  gsmith
// Clarify load_address_space_designator code
//
// Revision 1.98  2007/01/04 23:12:03  gsmith
// remove thunk calls for program_interrupt
//
// Revision 1.97  2006/12/08 09:43:20  jj
// Add CVS message log
//

#if !defined(OPTION_NO_INLINE_LOGICAL) || defined(_DAT_C)
/*-------------------------------------------------------------------*/
/* Convert logical address to absolute address and check protection  */
/*                                                                   */
/* Input:                                                            */
/*      addr    Logical address to be translated                     */
/*      arn     Access register number (or USE_REAL_ADDR,            */
/*                      USE_PRIMARY_SPACE, USE_SECONDARY_SPACE)      */
/*      regs    CPU register context                                 */
/*      acctype Type of access requested: READ, WRITE, or instfetch  */
/*      akey    Bits 0-3=access key, 4-7=zeroes                      */
/* Returns:                                                          */
/*      Absolute storage address.                                    */
/*                                                                   */
/*      If the PSW indicates DAT-off, or if the access register      */
/*      number parameter is the special value USE_REAL_ADDR,         */
/*      then the addr parameter is treated as a real address.        */
/*      Otherwise addr is a virtual address, so dynamic address      */
/*      translation is called to convert it to a real address.       */
/*      Prefixing is then applied to convert the real address to     */
/*      an absolute address, and then low-address protection,        */
/*      access-list controlled protection, page protection, and      */
/*      key controlled protection checks are applied to the address. */
/*      If successful, the reference and change bits of the storage  */
/*      key are updated, and the absolute address is returned.       */
/*                                                                   */
/*      If the logical address causes an addressing, protection,     */
/*      or translation exception then a program check is generated   */
/*      and the function does not return.                            */
/*-------------------------------------------------------------------*/
_LOGICAL_C_STATIC BYTE *ARCH_DEP(logical_to_main) (VADR addr, int arn,
                                    REGS *regs, int acctype, BYTE akey)
{
RADR    aaddr;                          /* Absolute address          */

    /* Program check if absolute address is outside main storage */
    if (addr > regs->mainlim)
        goto vabs_addr_excp;

    /* Check protection and set reference and change bits */
    regs->dat.storkey = &(STORAGE_KEY(addr, regs));


    if (acctype & ACC_READ)
    {
        /* Program check if fetch protected location */
        if (unlikely(ARCH_DEP(is_fetch_protected) (addr, *regs->dat.storkey, akey, regs)))
        {
            goto vabs_prot_excp;
        }

        /* Set the reference bit in the storage key */
        *regs->dat.storkey |= STORKEY_REF;
    }
    else
    if (acctype & (ACC_WRITE|ACC_CHECK))
    {
        /* Program check if store protected location */
        if (unlikely(ARCH_DEP(is_store_protected) (addr, *regs->dat.storkey, akey, regs)))
        {
            goto vabs_prot_excp;
        }

        /* Set the reference and change bits in the storage key */
        if (acctype & ACC_WRITE)
            *regs->dat.storkey |= (STORKEY_REF | STORKEY_CHANGE);

    } /* acctype & ACC_WRITE|CHECK */

    /* Return mainstor address */
    return regs->mainstor + addr;

vabs_addr_excp:
    regs->program_interrupt (regs, PGM_ADDRESSING_EXCEPTION);

vabs_prot_excp:
        regs->program_interrupt (regs, PGM_PROTECTION_EXCEPTION);

    return NULL; /* prevent warning from compiler */
} /* end function ARCH_DEP(logical_to_main) */

#endif /*!defined(OPTION_NO_INLINE_LOGICAL) || defined(_DAT_C) */

/* end of DAT.H */
