//
//
//  acutil.h - General-purpose AcUtil functions
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
//
//  DESCRIPTION:
//
//  This header file contains declarations of general-purpose utility
//  functions provided with the AcUtil library and DLL.
//
#ifndef _ACUTIL_H
#define _ACUTIL_H

#include <stddef.h>
#include "acadstrc.h"

#pragma pack (push, 8)

bool              acutSplitString(
                      size_t &      numLeftBytes,
                      const ACHAR *& pRight,
                      const ACHAR  * source,
                      unsigned int  delimiter);

void              acutTrimWhiteSpace(ACHAR * pStr);

bool              acutWcMatchEx(
                      const ACHAR * string,
                      const ACHAR * pattern,
                      bool         ignoreCase);

size_t            acutXStrLength(const ACHAR * str);

Acad::ErrorStatus acutXStrNormalize(
                      ACHAR *& pStr,
                      bool preserveCase);

inline Acad::ErrorStatus
acutXStrUppercase(ACHAR *& pStr)
{ return acutXStrNormalize(pStr, false); }

#pragma pack (pop)
#endif // _ACUTIL_H
