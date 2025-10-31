#ifndef AC_GEGBL_H
#define AC_GEGBL_H
//
// (C) Copyright 1993-2006 by Autodesk, Inc.
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
//
// This file contains the struct "AcGe" containing run time identificators,
// as well as some other enums. This file contains a strusture
// AcGeContext that contains all global variables needed by the 2d
// and 3d Geometry Library.


#include <stdlib.h>
#include "gedll.h"
#include "adesk.h"
#include "getol.h"

#include "gegblge.h"
#pragma pack (push, 8)

class AcGeVector3d;

struct
GE_DLLEXPIMPORT
AcGeContext
{
    // System wide default tolerance.
    //
    static AcGeTol      gTol;

    static void (*gErrorFunc)();

#ifndef GELIB2D
    // Function to calculate a vector which is orthogonal to the given vector.
    //
    static void (*gOrthoVector)(const AcGeVector3d&,AcGeVector3d&);
#endif

#ifndef unix
    static void* (*gAllocMem)(size_t);
#ifdef MEM_DEBUG
    // Unicode: leave as char for now
    static void* (*gAllocMemLeak)(size_t, const char *, int);
#endif
    static void  (*gFreeMem)(void*);
#endif
#ifdef GE_LOCATED_NEW
    static void* (*gAllocMemNear) (size_t, AcGe::metaTypeIndex, const void* );
    static void* (*gAllocMemNearVector) (size_t, AcGe::metaTypeIndex, unsigned int, const void* );
    static void (*gSetExternalStore) (const void* );
#endif
#ifndef NDEBUG
    static void (*gAssertFunc)(const ACHAR *condition, const ACHAR *filename,
                                    int lineNumber, const ACHAR *status);
#endif
};


#pragma pack (pop)
#endif // AC_GEGBL_H
