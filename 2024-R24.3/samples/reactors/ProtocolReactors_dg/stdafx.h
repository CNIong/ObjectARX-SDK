//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0601		// Change this to the appropriate value to target Windows 7 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0601	// Change this to the appropriate value to target Windows 7 or later.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0400	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#define WAS_DEBUG
#undef _DEBUG
#endif

#ifndef _ADESK_MAC_
#include <afxwin.h>
#endif
#ifdef _MYDEBUG
#undef _MYDEBUG
#define _DEBUG
#endif

#include "adscodes.h"
#include "rxdefs.h"
#include "rxregsvc.h"
#include "accmd.h"
#include "acedads.h"
#include "dbmain.h"
#include "dbents.h"
#include "AcString.h"
#define DYNBLKSAMP_BLOCKNAME _T("ASDK_CUSTOM_BLOCK")


