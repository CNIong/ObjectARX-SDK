#ifndef _ACMEM_H
#define _ACMEM_H
//
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
//  This header file contains general-purpose memory allocation
//  functions.  They are deprecated in favor of newBuffer, freeBuffer,
//  etc. declared in acutmem.h.

#include <stddef.h>
#include "AdAChar.h"

#pragma pack (push, 8)

#ifdef __cplusplus
extern "C" {
#endif

void  *acad_malloc  (size_t size);
void   acad_free    (void *p);
size_t acad__msize  (void *p);
void  *acad_realloc (void *p, size_t size);
void  *acad_calloc  (size_t num, size_t size);
ACHAR *acad__strdup (const ACHAR *p);

#ifdef __cplusplus
} // "C"
#endif

#pragma pack (pop)
#endif // _ACMEM_H
