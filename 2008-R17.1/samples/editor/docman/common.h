// (C) Copyright 1998-2006 by Autodesk, Inc.
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
// common.h : common definitions and functions for this project.
//            Used by docman.cpp and MDITestDialog.cpp files.
//


#ifndef _COMMON_H_
#define _COMMON_H_

#include "acdocman.h" 
#include "rxmfcapi.h"

//  Definitions and functions common to this project


const TCHAR* modeStr(AcAp::DocLockMode mode);
// Returns: a string representation of the lock mode given.

bool getLockModeFromStr(CString csLockMode, AcAp::DocLockMode &lockMode);
// Results: translates string into lock mode
// Returns: true if able to translate string into lock mode.

//	When AutoCAD asks your modeless dialog if it is willing to give up input
//	focus, return true to keep the focus and false to give it up.
//
#ifndef WM_ACAD_MFC_BASE
#define WM_ACAD_MFC_BASE        (1000)
#endif

// These are used by the document reactor to post messages to the dialog
#ifndef WM_ACAD_UPDATEDIALOG
#define WM_ACAD_UPDATEDIALOG       (WM_ACAD_MFC_BASE + 2)
#endif

#ifndef WM_ACAD_CREATEDOC
#define WM_ACAD_CREATEDOC	       (WM_ACAD_MFC_BASE + 3)
#endif

#ifndef WM_ACAD_DESTROYDOC
#define WM_ACAD_DESTROYDOC	       (WM_ACAD_MFC_BASE + 4)
#endif

#ifndef WM_ACAD_LOCKMODCHANGED
#define WM_ACAD_LOCKMODCHANGED     (WM_ACAD_MFC_BASE + 5)
#endif

#ifndef WM_ACAD_LOCKMODWILLCHANGE
#define WM_ACAD_LOCKMODWILLCHANGE  (WM_ACAD_MFC_BASE + 6)
#endif

#ifndef WM_ACAD_CURRENTDOC
#define WM_ACAD_CURRENTDOC	       (WM_ACAD_MFC_BASE + 7)
#endif

#ifndef WM_ACAD_ACTIVATEDOC
#define WM_ACAD_ACTIVATEDOC	       (WM_ACAD_MFC_BASE + 8)
#endif

#ifndef WM_ACAD_DEACTIVATEDOC
#define WM_ACAD_DEACTIVATEDOC	   (WM_ACAD_MFC_BASE + 9)
#endif

#ifndef WM_ACAD_ACTMODIFIED
#define WM_ACAD_ACTMODIFIED	       (WM_ACAD_MFC_BASE + 10)
#endif


#endif