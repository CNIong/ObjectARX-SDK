#ifndef _ACUTASRT_H
#define _ACUTASRT_H
//
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
// DESCRIPTION:
//
// This header file contains the declaration of acutAssertMessage.
// We provide a separate header file for this function to avoid header-file
// dependencies caused by placing the declaration in our header files.
// This header file needs to be "benign" for safe usage in other header
// files that provide assert-like macros.
// 
#include "AdAChar.h"
#pragma pack (push, 8)

void acutAssertMessage(
    const ACHAR *condition,
    const ACHAR *filename,
    int         lineNumber,
    const ACHAR *status);

#pragma pack (pop)
#endif // !_ACUTASRT_H
