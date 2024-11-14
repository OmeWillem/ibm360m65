/* INLINE.H     (c) Copyright Jan Jaeger, 2000-2009                  */
/*              Inline function definitions                          */

// $Id: inline.h 5126 2009-01-23 13:05:56Z bernard $

/* Original author Roger Bowler, 1999                                */
/* Interpretive Execution - (c) Copyright Jan Jaeger, 1999-2009      */
/* z/Architecture support - (c) Copyright Jan Jaeger, 1999-2009      */

/* Storage protection override fix               Jan Jaeger 31/08/00 */
/* ESAME low-address protection          v208d Roger Bowler 20/01/01 */
/* ESAME subspace replacement            v208e Roger Bowler 27/01/01 */
/* Multiply/Divide Logical instructions         Vic Cross 13/02/2001 */

// $Log$
// Revision 1.49  2007/06/23 00:04:14  ivan
// Update copyright notices to include current year (2007)
//
// Revision 1.48  2007/03/20 22:28:52  gsmith
// Use non-concurrent load for fetch_doubleword_absolute on 32bit hosts
//
// Revision 1.47  2007/03/07 15:36:56  ivan
// Fix explicit store protection check for SIE'd guests
//
// Revision 1.46  2007/01/04 23:12:04  gsmith
// remove thunk calls for program_interrupt
//
// Revision 1.45  2006/12/08 09:43:28  jj
// Add CVS message log
//

// #define INLINE_STORE_FETCH_ADDR_CHECK

_LOGICAL_C_STATIC BYTE *ARCH_DEP(logical_to_main) (VADR addr, int arn,
        REGS *regs, int acctype, BYTE akey);

_VSTORE_C_STATIC void ARCH_DEP(vstorec) (void *src, BYTE len,
        VADR addr, int arn, REGS *regs);
_VSTORE_C_STATIC void ARCH_DEP(vstoreb) (BYTE value, VADR addr,
        int arn, REGS *regs);
_VSTORE_C_STATIC void ARCH_DEP(vstore2) (U16 value, VADR addr, int arn,
        REGS *regs);
_VSTORE_C_STATIC void ARCH_DEP(vstore4) (U32 value, VADR addr, int arn,
        REGS *regs);
_VSTORE_C_STATIC void ARCH_DEP(vstore8) (U64 value, VADR addr, int arn,
        REGS *regs);
_VSTORE_C_STATIC void ARCH_DEP(vfetchc) (void *dest, BYTE len,
        VADR addr, int arn, REGS *regs);
_VSTORE_C_STATIC BYTE ARCH_DEP(vfetchb) (VADR addr, int arn,
        REGS *regs);
_VSTORE_C_STATIC U16 ARCH_DEP(vfetch2) (VADR addr, int arn,
        REGS *regs);
_VSTORE_C_STATIC U32 ARCH_DEP(vfetch4) (VADR addr, int arn,
        REGS *regs);
_VSTORE_C_STATIC U64 ARCH_DEP(vfetch8) (VADR addr, int arn,
        REGS *regs);
_VSTORE_C_STATIC void ARCH_DEP(move_chars) (VADR addr1, int arn1,
      BYTE key1, VADR addr2, int arn2, BYTE key2, int len, REGS *regs);
_VSTORE_C_STATIC void ARCH_DEP(validate_operand) (VADR addr, int arn,
        int len, int acctype, REGS *regs);
_VFETCH_C_STATIC BYTE * ARCH_DEP(instfetch) (REGS *regs, int exec);

#if !defined(_INLINE_H)

#define _INLINE_H


/*-------------------------------------------------------------------*/
/* Add two unsigned fullwords giving an unsigned fullword result     */
/* and return the condition code for the AL or ALR instruction       */
/*-------------------------------------------------------------------*/
static inline int add_logical(U32 *result, U32 op1, U32 op2)
{
    *result = op1 + op2;
    return (*result == 0 ? 0 : 1) | (op1 > *result ? 2 : 0);
} /* end function add_logical */


/*-------------------------------------------------------------------*/
/* Subtract two unsigned fullwords giving unsigned fullword result   */
/* and return the condition code for the SL or SLR instruction       */
/*-------------------------------------------------------------------*/
static inline int sub_logical(U32 *result, U32 op1, U32 op2)
{
    *result = op1 - op2;
    return (*result == 0 ? 0 : 1) | (op1 < *result ? 0 : 2);
} /* end function sub_logical */


/*-------------------------------------------------------------------*/
/* Add two signed fullwords giving a signed fullword result          */
/* and return the condition code for the A or AR instruction         */
/*-------------------------------------------------------------------*/
static inline int add_signed(U32 *result, U32 op1, U32 op2)
{
    *result = (S32)op1 + (S32)op2;

    return  ((S32)*result >  0) ?
                ((S32)op1 <  0 && (S32)op2 <  0) ? 3 : 2 :
            ((S32)*result <  0) ?
                ((S32)op1 >= 0 && (S32)op2 >= 0) ? 3 : 1 :
                ((S32)op1 <  0 && (S32)op2 <  0) ? 3 : 0;

/*    return (((S32)op1 < 0 && (S32)op2 < 0 && (S32)*result >= 0)
      || ((S32)op1 >= 0 && (S32)op2 >= 0 && (S32)*result < 0)) ? 3 :
                                              (S32)*result < 0 ? 1 :
                                              (S32)*result > 0 ? 2 : 0; */
} /* end function add_signed */


/*-------------------------------------------------------------------*/
/* Subtract two signed fullwords giving a signed fullword result     */
/* and return the condition code for the S or SR instruction         */
/*-------------------------------------------------------------------*/
static inline int sub_signed(U32 *result, U32 op1, U32 op2)
{
    *result = (S32)op1 - (S32)op2;

    return  ((S32)*result >  0) ?
                ((S32)op1 <  0 && (S32)op2 >= 0) ? 3 : 2 :
            ((S32)*result <  0) ?
                ((S32)op1 >= 0 && (S32)op2 <  0) ? 3 : 1 :
            ((S32)op1 <  0 && (S32)op2 >= 0) ? 3 : 0;

/*    return (((S32)op1 < 0 && (S32)op2 >= 0 && (S32)*result >= 0)
      || ((S32)op1 >= 0 && (S32)op2 < 0 && (S32)*result < 0)) ? 3 :
                                             (S32)*result < 0 ? 1 :
                                             (S32)*result > 0 ? 2 : 0; */
} /* end function sub_signed */


/*-------------------------------------------------------------------*/
/* Multiply two signed fullwords giving a signed doubleword result   */
/*-------------------------------------------------------------------*/
static inline void mul_signed ( U32 *resulthi, U32 *resultlo,
                             U32 op1, U32 op2 )
{
S64 r;

    r = (S64)(S32)op1 * (S32)op2;
    *resulthi = (U32)((U64)r >> 32);
    *resultlo = (U32)((U64)r & 0xFFFFFFFF);
} /* end function mul_signed */


/*-------------------------------------------------------------------*/
/* Divide a signed doubleword dividend by a signed fullword divisor  */
/* giving a signed fullword remainder and a signed fullword quotient.*/
/* Returns 0 if successful, 1 if divide overflow.                    */
/*-------------------------------------------------------------------*/
static inline int div_signed ( U32 *remainder, U32 *quotient,
              U32 dividendhi, U32 dividendlo, U32 divisor )
{
U64 dividend;
S64 quot, rem;

    if (divisor == 0) return 1;
    dividend = (U64)dividendhi << 32 | dividendlo;
    quot = (S64)dividend / (S32)divisor;
    rem = (S64)dividend % (S32)divisor;
    if (quot < -2147483648LL || quot > 2147483647LL) return 1;
    *quotient = (U32)quot;
    *remainder = (U32)rem;
    return 0;
} /* end function div_signed */

/*
 * The following routines were moved from esame.c rev 1.139 21oct2005
 */

/*-------------------------------------------------------------------*/
/* Add two unsigned doublewords giving an unsigned doubleword result */
/* and return the condition code for the ALG or ALGR instruction     */
/*-------------------------------------------------------------------*/
static inline int add_logical_long(U64 *result, U64 op1, U64 op2)
{
    *result = op1 + op2;
    return (*result == 0 ? 0 : 1) | (op1 > *result ? 2 : 0);
} /* end function add_logical_long */


/*-------------------------------------------------------------------*/
/* Subtract unsigned doublewords giving unsigned doubleword result   */
/* and return the condition code for the SLG or SLGR instruction     */
/*-------------------------------------------------------------------*/
static inline int sub_logical_long(U64 *result, U64 op1, U64 op2)
{
    *result = op1 - op2;
    return (*result == 0 ? 0 : 1) | (op1 < *result ? 0 : 2);
} /* end function sub_logical_long */


/*-------------------------------------------------------------------*/
/* Add two signed doublewords giving a signed doubleword result      */
/* and return the condition code for the AG or AGR instruction       */
/*-------------------------------------------------------------------*/
static inline int add_signed_long(U64 *result, U64 op1, U64 op2)
{
    *result = (S64)op1 + (S64)op2;

    return (((S64)op1 < 0 && (S64)op2 < 0 && (S64)*result >= 0)
      || ((S64)op1 >= 0 && (S64)op2 >= 0 && (S64)*result < 0)) ? 3 :
                                              (S64)*result < 0 ? 1 :
                                              (S64)*result > 0 ? 2 : 0;
} /* end function add_signed_long */


/*-------------------------------------------------------------------*/
/* Subtract two signed doublewords giving signed doubleword result   */
/* and return the condition code for the SG or SGR instruction       */
/*-------------------------------------------------------------------*/
static inline int sub_signed_long(U64 *result, U64 op1, U64 op2)
{
    *result = (S64)op1 - (S64)op2;

    return (((S64)op1 < 0 && (S64)op2 >= 0 && (S64)*result >= 0)
      || ((S64)op1 >= 0 && (S64)op2 < 0 && (S64)*result < 0)) ? 3 :
                                             (S64)*result < 0 ? 1 :
                                             (S64)*result > 0 ? 2 : 0;
} /* end function sub_signed_long */


/*-------------------------------------------------------------------*/
/* Divide an unsigned 128-bit dividend by an unsigned 64-bit divisor */
/* giving unsigned 64-bit remainder and unsigned 64-bit quotient.    */
/* Returns 0 if successful, 1 if divide overflow.                    */
/*-------------------------------------------------------------------*/
static inline int div_logical_long
                  (U64 *rem, U64 *quot, U64 high, U64 lo, U64 d)
{
    int i;

    *quot = 0;
    if (high >= d) return 1;
    for (i = 0; i < 64; i++)
    {
    int ovf;
        ovf = high >> 63;
        high = (high << 1) | (lo >> 63);
        lo <<= 1;
        *quot <<= 1;
        if (high >= d || ovf)
        {
            *quot += 1;
            high -= d;
        }
    }
    *rem = high;
    return 0;
} /* end function div_logical_long */


/*-------------------------------------------------------------------*/
/* Multiply two unsigned doublewords giving unsigned 128-bit result  */
/*-------------------------------------------------------------------*/
static inline int mult_logical_long
                  (U64 *high, U64 *lo, U64 md, U64 mr)
{
    int i;

    *high = 0; *lo = 0;
    for (i = 0; i < 64; i++)
    {
    U64 ovf;
        ovf = *high;
        if (md & 1)
            *high += mr;
        md >>= 1;
        *lo = (*lo >> 1) | (*high << 63);
        if(ovf > *high)
            *high = (*high >> 1) | 0x8000000000000000ULL;
        else
            *high >>= 1;
    }
    return 0;
} /* end function mult_logical_long */


#endif /*!defined(_INLINE_H)*/


/*-------------------------------------------------------------------*/
/* Test for fetch protected storage location.                        */
/*                                                                   */
/* Input:                                                            */
/*      addr    Logical address of storage location                  */
/*      skey    Storage key with fetch, reference, and change bits   */
/*              and one low-order zero appended                      */
/*      akey    Access key with 4 low-order zeroes appended          */
/*      regs    Pointer to the CPU register context                  */
/*      regs->dat.private  1=Location is in a private address space  */
/* Return value:                                                     */
/*      1=Fetch protected, 0=Not fetch protected                     */
/*-------------------------------------------------------------------*/
static inline int ARCH_DEP(is_fetch_protected) (VADR addr, BYTE skey,
                    BYTE akey, REGS *regs)
{
    UNREFERENCED_370(addr);
    UNREFERENCED_370(regs);

    /* [3.4.1] Fetch is allowed if access key is zero, regardless
       of the storage key and fetch protection bit */
    /* [3.4.1] Fetch protection prohibits fetch if storage key fetch
       protect bit is on and access key does not match storage key */
    if (likely(akey == 0
    || akey == (skey & STORKEY_KEY)
    || !(skey & STORKEY_FETCH)))
    return 0;

    /* Return one if location is fetch protected */
    return 1;

} /* end function is_fetch_protected */

/*-------------------------------------------------------------------*/
/* Test for low-address protection.                                  */
/*                                                                   */
/* Input:                                                            */
/*      addr    Logical address of storage location                  */
/*      regs    Pointer to the CPU register context                  */
/*      regs->dat.private  1=Location is in a private address space  */
/* Return value:                                                     */
/*      1=Low-address protected, 0=Not low-address protected         */
/*-------------------------------------------------------------------*/
static inline int ARCH_DEP(is_low_address_protected) (VADR addr,
                                              REGS *regs)
{
    /* For S/370 and ESA/390, low-address protection applies
       to locations 0-511 only */
    if (addr > 511)
        return 0;

    /* Low-address protection applies only if the low-address
       protection control bit in control register 0 is set */
    if ((regs->CR(0) & CR0_LOW_PROT) == 0)
        return 0;

    /* Return one if location is low-address protected */
    return 1;

} /* end function is_low_address_protected */

/*-------------------------------------------------------------------*/
/* Test for store protected storage location.                        */
/*                                                                   */
/* Input:                                                            */
/*      addr    Logical address of storage location                  */
/*      skey    Storage key with fetch, reference, and change bits   */
/*              and one low-order zero appended                      */
/*      akey    Access key with 4 low-order zeroes appended          */
/*      regs    Pointer to the CPU register context                  */
/*      regs->dat.private  1=Location is in a private address space  */
/*      regs->dat.protect  1=Access list protected or page protected */
/* Return value:                                                     */
/*      1=Store protected, 0=Not store protected                         */
/*-------------------------------------------------------------------*/
static inline int ARCH_DEP(is_store_protected) (VADR addr, BYTE skey,
               BYTE akey, REGS *regs)
{
    /* [3.4.4] Low-address protection prohibits stores into certain
       locations in the prefixed storage area of non-private address
       address spaces, if the low-address control bit in CR0 is set,
       regardless of the access key and storage key */
    if (ARCH_DEP(is_low_address_protected) (addr, regs))
        return 1;

    /* [3.4.1] Store is allowed if access key is zero, regardless
       of the storage key */
    if (akey == 0)
        return 0;

    /* [3.4.1] Store protection prohibits stores if the access
       key does not match the storage key */
    if (akey != (skey & STORKEY_KEY))
        return 1;

    /* Return zero if location is not store protected */
    return 0;

} /* end function is_store_protected */


/*-------------------------------------------------------------------*/
/* Return mainstor address of absolute address.                      */
/* The caller is assumed to have already checked that the absolute   */
/* address is within the limit of main storage.                      */
/*-------------------------------------------------------------------*/
#if defined(INLINE_STORE_FETCH_ADDR_CHECK)
static inline BYTE *ARCH_DEP(fetch_main_absolute) (RADR addr,
                                REGS *regs, int len)
#else
static inline BYTE *ARCH_DEP(fetch_main_absolute) (RADR addr,
                                REGS *regs)
#endif
{
#if defined(INLINE_STORE_FETCH_ADDR_CHECK)
    if(addr > regs->mainlim - len)
        regs->program_interrupt (regs, PGM_ADDRESSING_EXCEPTION);
#endif /*defined(INLINE_STORE_FETCH_ADDR_CHECK)*/

    /* Set the main storage reference bit */
    STORAGE_KEY(addr, regs) |= STORKEY_REF;

    /* Return absolute storage mainstor address */
    return (regs->mainstor + addr);

} /* end function fetch_main_absolute */


#include "dat.h"

#include "vstore.h"

/* end of INLINE.H */
