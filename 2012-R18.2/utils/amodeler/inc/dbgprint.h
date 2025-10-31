#ifndef AMODELER_INC_DBGPRINT_H
#define AMODELER_INC_DBGPRINT_H

///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
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
///////////////////////////////////////////////////////////////////////////////

#include "global.h"
#include <tchar.h>

AMODELER_NAMESPACE_BEGIN


DllImpExp void  dbgOpen (const wchar_t* pFileName);
DllImpExp void  dbgClose();
DllImpExp FILE* dbgFile ();
DllImpExp void  dbgPrint(const wchar_t* format, ...);
DllImpExp void  dbgPrintFace(const Face*);
DllImpExp void  dbgPrintFaceAsLisp(const Face*, const wchar_t* lispFileName);
DllImpExp void  dbgPrintPolygonAsLisp(const Point3d plg[], int n, bool isClosed, const wchar_t* lispFileName);


AMODELER_NAMESPACE_END
#endif
