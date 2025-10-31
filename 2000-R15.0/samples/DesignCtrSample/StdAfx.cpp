// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#if defined(_DEBUG) && !defined(DEBUG_THIS_ONLY)
#undef _DEBUG
#define DEBUG_THIS_ONLY
#endif

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>

#ifdef DEBUG_THIS_ONLY
#undef DEBUG_THIS_ONLY
#define _DEBUG
#endif
