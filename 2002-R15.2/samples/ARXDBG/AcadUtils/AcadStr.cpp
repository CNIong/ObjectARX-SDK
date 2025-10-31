//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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

#include "stdafx.h"
#include "AcadStr.h"

    // AutoCAD system variables
const char* AcadVar::adserr		= "errno";
const char* AcadVar::cmdecho	= "cmdecho";
const char* AcadVar::cvport		= "cvport";
const char* AcadVar::filedia	= "filedia";
const char* AcadVar::snapang	= "snapang";
const char* AcadVar::viewdir	= "viewdir";
const char* AcadVar::viewsize	= "viewsize";


    // AutoCAD common strings
const char* AcadString::continuous	= "Continuous";		// needs to be translated
const char* AcadString::bylayer		= "ByLayer";        // needs to be translated
const char* AcadString::byblock		= "ByBlock";        // needs to be translated
const char* AcadString::zero        = "0";				// default layer
const char* AcadString::wcAll		= "*";				// wild card for all
const char* AcadString::nullStr		= "";				// ""
const char* AcadString::openBrace   = "{";
const char* AcadString::endBrace    = "}";
const char* AcadString::standard    = "Standard";
const char* AcadString::none        = "*NONE*";
const char* AcadString::varies1     = "*VARIES*";
const char* AcadString::varies2     = "VARIES";

static const char* ltypesStandardName()
{
    static char buf[_MAX_FNAME+_MAX_EXT];
    strcpy(buf,acdbHostApplicationServices()->program());
    strcat(buf,".lin");
    return buf;
}
    // AutoCAD files
const char* AcadFile::ltypesStandard	= ltypesStandardName();
const char* AcadFile::ltypesComplex		= "ltypeshp.lin";

