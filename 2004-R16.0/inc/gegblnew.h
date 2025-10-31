#ifndef AC_GEGBLNEW_H
#define AC_GEGBLNEW_H
//
// (C) Copyright 1998-1999 by Autodesk, Inc.
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
// DESCRIPTION:
// Provides an interface for additional overloads to the global new.
// Implemented in gegbl.cpp
//

#ifdef GE_LOCATED_NEW

#include "gegblge.h"
#include "gegetmti.h"

GE_DLLEXPIMPORT
void* operator new ( size_t, enum AcGe::metaTypeIndex, const void* );

GE_DLLEXPIMPORT
void* operator new ( size_t, enum AcGe::metaTypeIndex, unsigned int, const void* );

#define GENEWLOC( T, ptr)  new (AcGeGetMetaTypeIndex<T >(), (ptr)) T
#define GENEWLOCVEC( T, count, ptr) new (AcGeGetMetaTypeIndex<T >(),(count),(ptr)) T [ (count) ]
#else   //#ifdef GE_LOCATED_NEW
#define GENEWLOC( T, ptr)  new T
#define GENEWLOCVEC( T, count, ptr) new T [ (count) ]
#endif


#endif  // AC_GEGBLNEW_H