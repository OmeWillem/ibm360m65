/* FEATCHK.H    (c) Copyright Jan Jaeger, 2000-2009                  */
/*              Feature definition consistency checks                */

// $Id: featchk.h 5454 2009-08-14 14:25:06Z rbowler $

/*-------------------------------------------------------------------*/
/*  Perform various checks on feature combinations, and set          */
/*  additional flags to percolate certain features such as           */
/*  SIE down to lower architecture levels such that these            */
/*  can include emulation support                                    */
/*-------------------------------------------------------------------*/

#if defined(FEATCHK_CHECK_ALL)

#if defined(FEATURE_INTERVAL_TIMER)
 #define _FEATURE_INTERVAL_TIMER
#endif

#undef _VSTORE_C_STATIC
#if !defined(OPTION_NO_INLINE_VSTORE)
 #define _VSTORE_C_STATIC static inline
 #define _VSTORE_FULL_C_STATIC static
#else
 #define _VSTORE_C_STATIC
 #define _VSTORE_FULL_C_STATIC
#endif

#undef _VFETCH_C_STATIC
#if !defined(OPTION_NO_INLINE_IFETCH)
 #define _VFETCH_C_STATIC static inline
#else
 #define _VFETCH_C_STATIC
#endif

#undef _DAT_C_STATIC
#if !defined(OPTION_NO_INLINE_DAT)
 #define _DAT_C_STATIC static inline
#else
 #define _DAT_C_STATIC
#endif

#undef _LOGICAL_C_STATIC
#if !defined(OPTION_NO_INLINE_LOGICAL)
 #define _LOGICAL_C_STATIC static inline
#else
 #define _LOGICAL_C_STATIC
#endif

 #define _370
 #define _ARCHMODE1 370
 #define ARCH_370 0

#if defined(_ARCHMODE3)
 #define GEN_MAXARCH    3+2
#elif defined(_ARCHMODE2)
 #define GEN_MAXARCH    2+2
#else
 #define GEN_MAXARCH    1+2
#endif

#endif /*!defined(FEATALL_CHECKALL)*/

/* end of FEATCHK.H */
