#ifndef _ACUTMIGR_H
#define _ACUTMIGR_H
//
//
//  acutmigr.h:  Migration assistance for AcUtil
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
//  DESCRIPTION:
//
//  This header file provides inline functions, macros, etc. to
//  assist migration to the new AcUtil functions.  This header file
//  may not be available in a subsequent release of ObjectARX.

#include "acutmem.h"

#pragma pack (push, 8)

// Unicode: leaving newBuffer and delBuffer pointer args as char *.
//
inline Acad::ErrorStatus newBuffer(char *&pOutput, size_t size)
{
    return ::acutNewBuffer(pOutput, size);
}

inline Acad::ErrorStatus newString(const ACHAR* pInput, ACHAR*& pOutput)
{
    return ::acutNewString(pInput, pOutput);
}

inline Acad::ErrorStatus newString(ACHAR*& pOutput, int nNumChars)
{
    return ::acutNewString(pOutput, nNumChars);
}

inline Acad::ErrorStatus updString(const ACHAR* pInput, ACHAR*& pOutput)
{
    return ::acutUpdString(pInput, pOutput);
}

inline void delString(ACHAR*& pString)
{
    ::acutDelString(pString);
}

inline void delBuffer(char*& pString)
{
    ::acutDelString(pString);
}

#pragma pack (pop)
#endif // _ACUTMGR_H

