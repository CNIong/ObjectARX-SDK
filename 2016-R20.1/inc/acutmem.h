//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//  acutmem.h - General memory allocation functions.
//
//  DESCRIPTION:
//
//  The following functions are used to handle string values and memory
//  returned to or from (or passed into) the ObjectARX API.  Function
//  acutNewString() makes a copy of a string and returns an error status.
//  Function acutUpdString() performs the same job as acutNewString(),
//  except that it first frees any string already pointed to by the
//  output argument.  acutDelString() frees up a string allocated by
//  acutNewString() or acutUpdString() if the input pointer is non
//  NULL and then sets the pointer to NULL.
//

#ifndef _ACUTMEM_H
#define _ACUTMEM_H

#include "acadstrc.h"   // Acad::ErrorStatus
#include "AdAChar.h"    // ACHAR

#pragma pack (push, 8)

Acad::ErrorStatus acutNewBuffer(void *&pOutput, size_t size);
Acad::ErrorStatus acutNewString(ACHAR *&pOutput, int nNumChars);
Acad::ErrorStatus acutNewString(const ACHAR* pInput, ACHAR*& pOutput);
Acad::ErrorStatus acutUpdString(const ACHAR* pInput, ACHAR*& pOutput);
void acutDelBuffer(void *& pBuffer);

inline Acad::ErrorStatus acutNewBuffer(char *&pOutput, size_t size)
{
    return ::acutNewBuffer((void * &)pOutput, size);
}

inline void acutDelBuffer(char *& pString)
{
    ::acutDelBuffer((void * &)pString);
}

inline void acutDelString(char *& pString)
{
    ::acutDelBuffer((void * &)pString);
}

inline void acutDelString(wchar_t *& pString)
{
    ::acutDelBuffer((void * &)pString);
}

#pragma pack (pop)
#endif // _ACUTMEM_H
