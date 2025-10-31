//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

#ifndef _acutilads_h
#define _acutilads_h 1

// Ensure that C++ modules use the right linking conventions when calling
// functions contained in C.

#ifdef __cplusplus
    extern "C" {
#endif

#include "adsdef.h"
#include "AdAChar.h"

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
