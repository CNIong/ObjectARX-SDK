/////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-2003 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////

#ifndef _ANav_h
#define _ANav_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// ANAV_PORT is defined to export classes and functions when building the DLL.

#ifndef ANAV_PORT
#  define   ANAV_PORT  __declspec(dllimport)
#endif

/////////////////////////////////////////////////////////////////////////////
// File Navigation prototypes

#include <adui.h>
#include <afxole.h>
#include <AnavListCtrl.h>
#include <ANavData.h>
#include <ANavFilter.h>
#include <ANavArray.h>
#include <ANavDataArray.h>
#include <ANavFilterArray.h>
#include <ANavDialog.h>


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
