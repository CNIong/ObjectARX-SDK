// (C) Copyright 1993-1998 by Autodesk, Inc.
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

#include "stdafx.h"

#include "utils.h"

#define _prec 3

Acad::ErrorStatus 
getTextStyleName(CString& styleName, AcDbObjectId styleId)
{
	if(AcDbObjectId::kNull == styleId)
		return Acad::eNullObjectId;

	AcDbObject *pObj;
	ISOK(acdbOpenAcDbObject(pObj, styleId, AcDb::kForRead));

	AcDbTextStyleTableRecord *pStyle;
	pStyle = AcDbTextStyleTableRecord::cast(pObj);
	if(pStyle == NULL)
	{
		pObj->close();
		return Acad::eWrongObjectType;
	}

	const char * pStyleName;
	pStyle->getName(pStyleName);
	styleName = pStyleName;

	pStyle->close();
	return Acad::eOk;
}


void
updateRegistry()
{
    // Represents your company's Registry location
    const char pAppInfoLoc[] = 
        "Software\\Autodesk\\ObjectARX\\3.0\\SampleApps\\CurveText";

    // The final argument of Adesk::kTrue means that this app will be
    // registered under the Autodesk/ObjectDBX area of the registry
    // All ObjectDBX apps can search for it there, in addition to AutoCAD
    //
    acrxRegisterApp((AcadApp::LoadReasons)(AcadApp::kOnProxyDetection), 
                     "CurveTextDBX", pAppInfoLoc  , 2, Adesk::kTrue);

    // Now to write out the application specific information
    //
    // We will install our "application specific" data in:
    // Software\Autodesk\ObjectARX\3.0\SampleApps\Curvetext

    HKEY rkey;
    DWORD result;
    LONG status = RegCreateKeyEx(HKEY_LOCAL_MACHINE, pAppInfoLoc, 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &rkey, &result);
    if (status != ERROR_SUCCESS)
        return;

    HKEY prodKey;
    status = RegCreateKeyEx(rkey, "CurveTextDBX", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &prodKey, &result);
    RegCloseKey(rkey);
    if (status != ERROR_SUCCESS)
        return;

    HKEY loaderKey;
    status = RegCreateKeyEx(prodKey, "Loader", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &loaderKey, &result);
    
    if (status == ERROR_SUCCESS) {
        HMODULE modHandle = GetModuleHandle("curvetext.dbx");
        if (modHandle) {
            // long filenames have a max length of 255.  total directory path
            // length is also 255 or less,  so a buffer of 512 bytes should be
            // fine.
            //
            char modulePath[512];
            DWORD pathLength = GetModuleFileName(modHandle, modulePath, 512);
            if (pathLength)
                RegSetValueEx(loaderKey, "MODULE", 0, REG_SZ,
                    (const unsigned char*)modulePath, pathLength + 1);
        }
        RegCloseKey(loaderKey);
    }

    HKEY nameKey;
    status = RegCreateKeyEx(prodKey, "Name", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &nameKey, &result);
    RegCloseKey(prodKey);
    if (status != ERROR_SUCCESS)
        return;

    RegSetValueEx(nameKey, "CurveTextDBX", 0, REG_SZ,
        (const unsigned char*)"CurveTextDBX", 12);
    RegCloseKey(nameKey);
}



// print a formated point
void printPoint(AcGePoint3d pt){
	ads_printf("X=%.*lf Y=%.*lf Z=%.*lf", _prec, pt.x,
								 		  _prec, pt.y,
										  _prec, pt.z);
}
