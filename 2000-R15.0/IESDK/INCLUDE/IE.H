//
// Copyright (C) 1993-1997 by Autodesk, Inc.
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

// ie.h - Image Engine/API main header

#ifndef    _ie_h
#define    _ie_h

//static const char sccsid[] = "@(#)ie.h	2.4 (95/10/17 14:56:58)";

#pragma pack (push, 8)

#include "csdefs.h"
#include "cs.h"
#include "ieaux.h"
#include "ief.h"
#include "iefdesc.h"
#if defined(CS_WIN32)
#include "iedib.h"
#endif
#include "ieimage.h"
#include "iecxt.h"

#pragma pack (pop)

#endif /* _ie_h */
