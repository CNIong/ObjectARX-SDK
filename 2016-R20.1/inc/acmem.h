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
//  DESCRIPTION:
//
//  This header file contains general-purpose memory allocation
//  functions.  They are deprecated in favor of newBuffer, freeBuffer,
//  etc. declared in acutmem.h.

#ifndef _ACMEM_H
#define _ACMEM_H

#include <stddef.h>
#include "AdAChar.h"

#pragma pack (push, 8)

// These functions are exported from acdbxx.dll with both extern "C" and
// C++ linkage.  But we may drop support for C apps in the future.
// They forward their calls to the clib's malloc(), free(), etc

void  *acad_malloc  (size_t size);
void   acad_free    (void *p);
size_t acad__msize  (void *p);
void  *acad_realloc (void *p, size_t size);
void  *acad_calloc  (size_t num, size_t size);
ACHAR *acad__strdup (const ACHAR *p);

#pragma pack (pop)
#endif // _ACMEM_H
