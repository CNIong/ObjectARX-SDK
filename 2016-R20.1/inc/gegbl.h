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
// DESCRIPTION:
//
// This file contains the struct "AcGe" containing run time identificators,
// as well as some other enums. This file contains a strusture
// AcGeContext that contains all global variables needed by the 2d
// and 3d Geometry Library.

#ifndef AC_GEGBL_H
#define AC_GEGBL_H

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
