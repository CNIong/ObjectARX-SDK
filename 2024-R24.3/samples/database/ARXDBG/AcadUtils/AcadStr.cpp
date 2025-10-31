//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
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

