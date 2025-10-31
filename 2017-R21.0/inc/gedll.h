//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2016 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
// This module controls the exporting of symbols for the AcGe Dll.
// 

#ifndef AC_GEDLL_H
#define AC_GEDLL_H

#include "adesk.h"
#if defined(_MSC_VER)
#pragma warning(disable:4251)
#pragma warning(disable:4273)
#pragma warning(disable:4275)
#endif

#ifdef _ADESK_STATIC_LINKING_
#define GE_DLLEXPIMPORT
#define GX_DLLEXPIMPORT
#else
#ifdef  ACGE_INTERNAL
#define GE_DLLEXPIMPORT __declspec(dllexport)
#else
#define GE_DLLEXPIMPORT __declspec(dllimport)
#endif

#ifdef  ACGX_INTERNAL
#define GX_DLLEXPIMPORT __declspec(dllexport)
#else
#define GX_DLLEXPIMPORT __declspec(dllimport)
#endif
#endif

#endif // AC_GEDLL_H
