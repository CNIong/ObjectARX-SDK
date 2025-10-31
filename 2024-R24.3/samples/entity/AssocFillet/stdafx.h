//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Include file for standard system include files, or project specific 
// include files that are used frequently, but are changed infrequently.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#pragma warning(disable: 4100 4239 4786)

#ifndef WINVER
#define WINVER 0x601
#endif

#include <afxwin.h>
#include "aced.h"
#include "acdb.h"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

#undef VERIFY

inline bool VERIFY(int condition)
{
    ASSERT(condition);
    return condition != 0;
}
