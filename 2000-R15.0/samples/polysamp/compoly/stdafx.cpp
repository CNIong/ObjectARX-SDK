// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
// (C) Copyright 1998 by Autodesk, Inc.
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#if defined(_DEBUG) && !defined(_DEBUG_AUTOCAD)
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#endif 

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>
#include "acad15_i.c"

#if defined(_DEBUG_WAS_DEFINED)
#undef _DEBUG_WAS_DEFINED
#define _DEBUG
#endif
