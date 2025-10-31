//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _acutilads_h
#define _acutilads_h 1

// Ensure that C++ modules use the right linking conventions when calling
// functions contained in C.

#ifdef __cplusplus
    extern "C" {
#endif

#include "adsdef.h"
#include "AdAChar.h"
#include "AcCoreDefs.h"

#pragma pack (push, 8)

void           acad__assert(const ACHAR *, const ACHAR *, int);

int            acutCvUnit (ads_real value, const ACHAR *oldunit,
                             const ACHAR *newunit, ads_real *result);
int            acutWcMatch (const ACHAR *string, const ACHAR *pattern);

int            acutPrintf (const ACHAR *format, ...);
int            acutSPrintf (ACHAR *buffer, const ACHAR *format, ...);

struct resbuf *acutNewRb (int v);
int            acutRelRb (struct resbuf *rb);
struct resbuf *acutBuildList (int rtype, ...);

ACCORE_PORT 
int acutRbDup(const struct resbuf *source, struct resbuf **result);


ads_real       acutAngle (const ads_point pt1, const ads_point pt2);
ads_real       acutDistance (const ads_point pt1, const ads_point pt2);
void           acutPolar (const ads_point pt, ads_real angle,
                            ads_real dist, ads_point ptres);

int            acutIsAlpha (int c);
int            acutIsUpper (int c);
int            acutIsLower (int c);
int            acutIsDigit (int c);
int            acutIsXDigit (int c);
int            acutIsSpace (int c);
int            acutIsPunct (int c);
int            acutIsAlNum (int c);
int            acutIsPrint (int c);
int            acutIsGraph (int c);
int            acutIsCntrl (int c);
int            acutToUpper (int c);
int            acutToLower (int c);

#pragma pack (pop)

#ifdef __cplusplus
    }
#endif

#endif // !acutilads.h
