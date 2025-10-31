//
//  (C) Copyright 1996-2008 by Autodesk, Inc.  All rights reserved.
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

#pragma once

//   Macros for asserting and checking whether an Acad::ErrorStatus is eOk.
//
//   eOkVerify always checks for whether the expression is eOk and
//   returns TRUE if it is, FALSE if it isn't.
//
//   In addition, in debug builds, eOkVerify puts up a message box when
//   the expression does not equal eOk.
//
//   You might be thinking it would be nice to have an eOkAssert()
//   macro, which doesn't evaluate the expression in release builds,
//   similar to the ASSERT macro.  That would avoid the overhead of
//   computing the boolean result when it's not needed.  But this
//   seemed dangerous, in that it would be easy for someone to put
//   needed code inside eOkAssert, and that code would not get called
//   in release builds.  Also, the compiler already "optimizes out"
//   expressions whose results are not used.  So eOkVerify() doesn't
//   add overhead in release builds anyway.

#include "acadstrc.h"
#include "acestext.h"
#include "acutasrt.h"
#include <tchar.h>

#ifdef NDEBUG

#define eOkTest(x) ((x) == Acad::eOk)
#define eOkCheck(x) (x)
#define eOkVerify(x) ((x) == Acad::eOk)

#else   // else not NDEBUG

// For use by eoktest.h only!
inline Acad::ErrorStatus eOkCheck_imp(
    const ACHAR *condition,
    const ACHAR *fname,
    int         lineno,
    Acad::ErrorStatus es)
{
    if (es != Acad::eOk) {
        acutAssertMessage(condition, fname, lineno,
                          acadErrorStatusText(es));
    }
    return es;
}

/// <summary>
/// Evaluates to true if value is Acad::eOk, otherwise evaluates to false.
/// </summary>
#define eOkTest(x) ((x) == Acad::eOk)

/// <summary>
/// Asserts if value is not Acad::eOk.  Evaluates to the value.
/// </summary>
#define eOkCheck(x) eOkCheck_imp(_T(# x), _T(__FILE__), __LINE__, (x))

/// <summary>
/// Asserts if value is not Acad::eOk.  Evaluates to true if value is Acad::eOk
/// otherwise evalutes to false.
/// </summary>
#define eOkVerify(x) (eOkCheck(x) == Acad::eOk)

#endif // NDEBUG
