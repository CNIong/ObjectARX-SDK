// (C) Copyright 1993-2006 by Autodesk, Inc.
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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include "utils.h"

#include "appinfo.h"



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

	const TCHAR * pStyleName;
	pStyle->getName(pStyleName);
	styleName = pStyleName;

	pStyle->close();
	return Acad::eOk;
}


//----- Register the Application in the AutoCAD registry (demand loading)

void updateRegistry()
{
	// Fill the AppInfo structure with our demand loading details.
	AcadAppInfo appInfo;
	appInfo.setAppName(_T("AsdkCurveTextDBX")); // Application name
	HMODULE hModule=GetModuleHandle(_T("AsdkCurveText.dbx")); // Get the physical location of the DBX...
    TCHAR modulePath[512];
    DWORD pathLength = GetModuleFileName(hModule, modulePath, 512);
    if (pathLength)
		appInfo.setModuleName(modulePath);// .. and set it.
	appInfo.setAppDesc(_T("AsdkCurveTextDBX"));	 // Description
	appInfo.setLoadReason(// Specify when we want this to load...
		AcadApp::LoadReasons(
		AcadApp::kOnProxyDetection |
		AcadApp::kOnLoadRequest));
	
	appInfo.writeToRegistry(true,true);// Write appInfo to the registry.  Set also the DBX registry portion.
}


// print a formated point
void printPoint(AcGePoint3d pt){
	ads_printf(_T("X=%.*lf Y=%.*lf Z=%.*lf"), _prec, pt.x,
								 		  _prec, pt.y,
										  _prec, pt.z);
}
