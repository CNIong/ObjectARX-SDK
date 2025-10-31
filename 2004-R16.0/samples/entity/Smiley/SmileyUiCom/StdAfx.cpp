// StdAfx.cpp : source file that includes just the standard includes
//  StdAfx.pch will be the pre-compiled header
//  StdAfx.obj will contain the pre-compiled type information

#include "StdAfx.h"

#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#define NDEBUG
#endif

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#endif

#ifdef _DEBUG_WAS_DEFINED
#undef NDEBUG
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

