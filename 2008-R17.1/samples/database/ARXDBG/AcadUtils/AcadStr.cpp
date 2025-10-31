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
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "AcadStr.h"



    // AutoCAD system variables
const TCHAR* AcadVar::adserr		= _T("errno");
const TCHAR* AcadVar::cmdecho	    = _T("cmdecho");
const TCHAR* AcadVar::cvport		= _T("cvport");
const TCHAR* AcadVar::filedia	    = _T("filedia");
const TCHAR* AcadVar::snapang	    = _T("snapang");
const TCHAR* AcadVar::viewdir	    = _T("viewdir");
const TCHAR* AcadVar::viewsize	    = _T("viewsize");


    // AutoCAD common strings
const TCHAR* AcadString::continuous	= _T("Continuous");		// needs to be translated
const TCHAR* AcadString::bylayer	= _T("ByLayer");        // needs to be translated
const TCHAR* AcadString::byblock	= _T("ByBlock");        // needs to be translated
const TCHAR* AcadString::zero       = _T("0");				// default layer
const TCHAR* AcadString::wcAll		= _T("*");				// wild card for all
const TCHAR* AcadString::nullStr	= _T("");				// ""
const TCHAR* AcadString::openBrace  = _T("{");
const TCHAR* AcadString::endBrace   = _T("}");
const TCHAR* AcadString::standard   = _T("Standard");
const TCHAR* AcadString::none       = _T("*NONE*");
const TCHAR* AcadString::varies1    = _T("*VARIES*");
const TCHAR* AcadString::varies2    = _T("VARIES");

static const TCHAR* ltypesStandardName()
{
    static TCHAR buf[_MAX_FNAME+_MAX_EXT];
    _tcscpy(buf,acdbHostApplicationServices()->program());
    _tcscat(buf,_T(".lin"));
    return buf;
}
    // AutoCAD files
const TCHAR* AcadFile::ltypesStandard	= ltypesStandardName();
const TCHAR* AcadFile::ltypesComplex	= _T("ltypeshp.lin");

