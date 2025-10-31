//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

//
#ifndef   _IDVER_H
#define   _IDVER_H

#include "idrelver.h"

#if defined(_ADESK_CROSS_PLATFORM_)
#error Fabric code should not include idver.h
#endif

#if defined(AC_BLDENV)
    #include "_idver.h"
#else
    //
    // Fabric follows a different version scheme, don't expect _idver.h to be there for fabric.
    // also this should prevent incremental desktop builds breakage.
    //
    #define ACADV_BLDMAJOR  0   /*BuildMajor*/
    #define ACADV_BLDMINOR  0   /*BuildMinor*/
    #define ACADV_BLDBRANCH 0   /*BuildBranch*/
    #define ACADV_BLDSTREAM DevelopmentBranch   /*BuildStream*/
#endif
//
// Calculate the numbers for the FILEVERSION resources.
//
// The four parts of the file version resources,
// each of which evaluates to an integer constant.
//      ACADV_{RCFILEVER1, RCFILEVER2, RCFILEVER3, RCFILEVER4}.
//
// We keep the FILEVERSION and PRODUCTVERSION numbers the same.
// So these are also used for setting the ProductVersion in rc files.
#define ACADV_RCFILEVER3 ACADV_BLDMAJOR
#define ACADV_RCFILEVER4 ACADV_BLDMINOR
#define ACADV_RCFILEVER5 ACADV_BLDBRANCH


// The following utility macros build the stringized form of the
// version numbers.
//
#define ACADV_RCFILEVERSTR ID2STR(ACADV_RCFILEVER1) "." \
                ID2STR(ACADV_RCFILEVER2) "." \
                ID2STR(ACADV_RCFILEVER3) "." \
                ID2STR(ACADV_RCFILEVER5) "." \
                ID2STR(ACADV_RCFILEVER4)

// Moved here from acadmfc.rc2
#define ACADV_PRODVERSION "R" ACADV_RCFILEVERSTR

//
// Build ACADV_VERNUM.
//
// Create a string form of the build numbers, e.g.,
// "N.20.0", "N.255.9999".
//
#if defined(_MSC_VER) || defined(UNICODE)
// This definition is used when included by source files
#define ACADV_VERNUM  ACRX_T(ID2STR(ACADV_BLDSTREAM)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_BLDMAJOR)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_BLDBRANCH)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_BLDMINOR))
#else // !_MSC_VER
// This definition is used when included by resource files
#define ACADV_VERNUM ID2STR(ACADV_BLDSTREAM) "." \
                     ID2STR(ACADV_BLDMAJOR) "." \
                     ID2STR(ACADV_BLDBRANCH) "." \
                     ID2STR(ACADV_BLDMINOR)
#endif // !_MSC_VER

//
// ACADV_VERFULL varies with production and nonproduction builds.
//
#if defined(PRODUCTION)
#define ACADV_VERFULL     ACADV_VERNAME
#else
#define ACADV_VERFULL     ACADV_VERNUM
#endif

// The following macros exist to simplify usage in RC files.

#define ACADV_BLDVERSTR   ACADV_VERNUM


#endif
