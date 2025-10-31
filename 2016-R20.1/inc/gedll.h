//
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
// This module controls the exporting of symbols for the AcGe Dll.
// 

#ifndef AC_GEDLL_H
#define AC_GEDLL_H

#include "adesk.h"
#if defined(_ADESK_WINDOWS_)
#pragma warning(disable:4251)
#pragma warning(disable:4273)
#pragma warning(disable:4275)
#endif

#ifdef  ACGE_INTERNAL
#ifdef _ADESK_IOS_
#define GE_DLLEXPIMPORT 
#else
#define GE_DLLEXPIMPORT __declspec(dllexport)
#endif
#else
#define GE_DLLEXPIMPORT __declspec(dllimport)
#endif

#ifdef  ACGX_INTERNAL
#define GX_DLLEXPIMPORT __declspec(dllexport)
#else
#define GX_DLLEXPIMPORT __declspec(dllimport)
#endif

#if defined(_ADESK_WINDOWS_)
#ifdef ACGE_INTERNAL
#ifndef GELIB_REGRESS
#include "acmemdebug.h"
#endif
#endif
#endif  // _ADESK_WINDOWS_

#endif // AC_GEDLL_H
