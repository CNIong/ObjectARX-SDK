#ifndef AC_GEDLL_H
#define AC_GEDLL_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// This module controls the exporting of symbols for the AcGe Dll.
// 

#pragma warning(disable:4251)
#pragma warning(disable:4273)
#pragma warning(disable:4275)
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

#ifdef ACGE_INTERNAL
#ifndef GELIB_REGRESS
#include "acmemdebug.h"
#endif
#endif

#endif // AC_GEDLL_H
