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
// common.cpp: common definitions and functions for this project.
//             Used by docman.cpp and MDITestDialog.cpp files.
//
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "common.h"
#include "acdocman.h"




const TCHAR* modeStr(AcAp::DocLockMode mode)
{
    switch (mode) {
    case AcAp::kNotLocked:
        return _T(/*NOXLATE*/"AcAp::kNotLocked");
    case AcAp::kRead:
        return _T(/*NOXLATE*/"AcAp::kRead");
    case AcAp::kWrite:
        return _T(/*NOXLATE*/"AcAp::kWrite");
    case AcAp::kAutoWrite:
        return _T(/*NOXLATE*/"AcAp::kAutoWrite");
    case AcAp::kProtectedAutoWrite:
        return _T(/*NOXLATE*/"AcAp::kProtectedAutoWrite");
    case AcAp::kXWrite:
        return _T(/*NOXLATE*/"AcAp::kXWrite");
    }
    return _T("ERROR");
}



bool getLockModeFromStr(CString csLockMode, AcAp::DocLockMode &lockMode)
{
    if( csLockMode == _T(/*NOXLATE*/"kNone") ) {
		lockMode = AcAp::kNone;
		return true;
	}
    if( csLockMode == _T(/*NOXLATE*/"kNotLocked") ) {
		lockMode = AcAp::kNotLocked;
		return true;
	}
    if( csLockMode == _T(/*NOXLATE*/"kRead") ) {
		lockMode = AcAp::kRead;
		return true;
	}
    if( csLockMode == _T(/*NOXLATE*/"kWrite") ) {
		lockMode = AcAp::kWrite;
		return true;
	}
    if( csLockMode == _T(/*NOXLATE*/"kAutoWrite") ) {
		lockMode = AcAp::kAutoWrite;
		return true;
	}
    if( csLockMode == _T(/*NOXLATE*/"kProtectedAutoWrite") ) {
		lockMode = AcAp::kProtectedAutoWrite;
		return true;
	}
    if( csLockMode == _T(/*NOXLATE*/"kXWrite") ) {
		lockMode = AcAp::kXWrite;
		return true;
	}

    return false;
}