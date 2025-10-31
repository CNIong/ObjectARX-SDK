//////////////////////////////////////////////////////////////////////////////
//
//  (C) Copyright 2009-2010 by Autodesk, Inc.
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

#ifndef  ACCOREDEFS_H
#define ACCOREDEFS_H

#ifndef _ADESK_MAC_
#ifndef ACCORE_PORT
#ifdef ACCORE_API
    #define ACCORE_PORT _declspec(dllexport)
#else
    #define ACCORE_PORT
#endif
#endif
#else
// On OS X, we will export all symbols by default and will use GCC
// attributes to exclude symbols we don't want to export.
#define ACCORE_PORT
#endif // _ADESK_MAC_


#endif //ACCOREDEFS_H
