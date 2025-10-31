// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
// (C) Copyright 1998-2006 by Autodesk, Inc.
//      are changed infrequently
//
#if defined(_DEBUG) && defined(ARXSAMPLE)
#undef _DEBUG
#define DEBUG_WAS_DEFINED
#define NDEBUG
#endif

#ifndef WINVER
#define WINVER 0x500
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifdef DEBUG_WAS_DEFINED
#define _DEBUG
#undef DEBUG_WAS_DEFINED
#undef NDEBUG
#endif
