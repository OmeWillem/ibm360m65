/* PLO.C        (c) Copyright Jan Jaeger, 2000-2009                  */
/*              Perform Locked Operation functions codes             */

/* Interpretive Execution - (c) Copyright Jan Jaeger, 1999-2009      */
/* z/Architecture support - (c) Copyright Jan Jaeger, 1999-2009      */

// $Id: plo.c 5126 2009-01-23 13:05:56Z bernard $
//
// $Log$
// Revision 1.24  2008/03/05 23:15:13  ptl00
// Fix fc=3 fc=19 and qword chks
//
// Revision 1.23  2007/06/23 00:04:15  ivan
// Update copyright notices to include current year (2007)
//
// Revision 1.22  2006/12/08 09:43:29  jj
// Add CVS message log
//

#include "hstdinc.h"

#if !defined(_HENGINE_DLL_)
#define _HENGINE_DLL_
#endif

#if !defined(_PLO_C_)
#define _PLO_C_
#endif

#include "hercules.h"

#include "opcode.h"

#include "inline.h"


#if !defined(_GEN_ARCH)

#if defined(_ARCHMODE2)
 #define  _GEN_ARCH _ARCHMODE2
 #include "plo.c"
#endif

#if defined(_ARCHMODE3)
#undef   _GEN_ARCH
#define  _GEN_ARCH _ARCHMODE3
#include "plo.c"
#endif

#endif /*!defined(_GEN_ARCH)*/
