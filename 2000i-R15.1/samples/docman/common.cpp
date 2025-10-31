// (C) Copyright 1998 by Autodesk, Inc.
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
#include "common.h"
#include "acdocman.h"


const char* modeStr(AcAp::DocLockMode mode)
{
    switch (mode) {
    case AcAp::kNotLocked:
        return /*NOXLATE*/"AcAp::kNotLocked";
    case AcAp::kRead:
        return /*NOXLATE*/"AcAp::kRead";
    case AcAp::kWrite:
        return /*NOXLATE*/"AcAp::kWrite";
    case AcAp::kAutoWrite:
        return /*NOXLATE*/"AcAp::kAutoWrite";
    case AcAp::kProtectedAutoWrite:
        return /*NOXLATE*/"AcAp::kProtectedAutoWrite";
    case AcAp::kXWrite:
        return /*NOXLATE*/"AcAp::kXWrite";
    }
    return "ERROR";
}



bool getLockModeFromStr(CString csLockMode, AcAp::DocLockMode &lockMode)
{
    if( csLockMode == /*NOXLATE*/"kNone" ) {
		lockMode = AcAp::kNone;
		return true;
	}
    if( csLockMode == /*NOXLATE*/"kNotLocked" ) {
		lockMode = AcAp::kNotLocked;
		return true;
	}
    if( csLockMode == /*NOXLATE*/"kRead" ) {
		lockMode = AcAp::kRead;
		return true;
	}
    if( csLockMode == /*NOXLATE*/"kWrite" ) {
		lockMode = AcAp::kWrite;
		return true;
	}
    if( csLockMode == /*NOXLATE*/"kAutoWrite" ) {
		lockMode = AcAp::kAutoWrite;
		return true;
	}
    if( csLockMode == /*NOXLATE*/"kProtectedAutoWrite" ) {
		lockMode = AcAp::kProtectedAutoWrite;
		return true;
	}
    if( csLockMode == /*NOXLATE*/"kXWrite" ) {
		lockMode = AcAp::kXWrite;
		return true;
	}

    return false;
}