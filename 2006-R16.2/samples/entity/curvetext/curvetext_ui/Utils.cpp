// (C) Copyright 1993-2003 by Autodesk, Inc.
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
#include "..\CurveText_DB\CurveText.h"

#include "utils.h"
#include "resource.h"

#include "appinfo.h"

#define _prec 3

AsdkDataManager<GLOBALS> DocVars;

// returns the current UCS Z normalize vector
//
AcGeVector3d 
getCurZdir(){
	AcGeVector3d xdir = acdbHostApplicationServices()->workingDatabase()->ucsxdir();
	AcGeVector3d ydir = acdbHostApplicationServices()->workingDatabase()->ucsydir();
	AcGeVector3d zdir = xdir.crossProduct(ydir);
	zdir.normalize();
	return zdir;
}

// retruns a default character size defined as being equal to
// 1/40th of the currrent view size (system variable)
//
double
getDefaultCharacterSize()
{
	struct resbuf ViewSize;
	acedGetVar("VIEWSIZE", &ViewSize);
	return ViewSize.resval.rreal / 40.0;
}

// selectEntity - utility functions to select entity
//
// Select entity, retrieve object Id and open it,
// creating and returning a valid object pointer.
//
AcDbObjectId
selectEntity()
{
	AcDbObjectId eId;
    ads_name en;
    ads_point pt;
    int rc = acedEntSel(NULL, en, pt);

    if (rc != RTNORM) {
        acutPrintf("Nothing selected.\n", rc);
        return AcDbObjectId::kNull;
    }

    AOK(acdbGetObjectId(eId, en));

	return eId;
}

AcDbEntity*
selectEntity(char * msg, AcDb::OpenMode openMode)
{
    AcDbObjectId eId;
    return selectEntity(eId, msg, openMode);
}

AcDbEntity*
selectEntity(AcDbObjectId& eId, char * msg, AcDb::OpenMode openMode)
{
    ads_name en;
    ads_point pt;

    int rc = acedEntSel(msg, en, pt);
    if (rc != RTNORM) {
        acutPrintf("Nothing selected.\n", rc);
        return NULL;
    }

    AOK(acdbGetObjectId(eId, en));
    AcDbEntity * ent;
    AOK(acdbOpenObject(ent, eId, openMode));
    return ent;
}

// Asks the user to select curves on the screen,
// then filers out from the selection set entities that
// are not curves or old style polylines.
// Populates the array of Ids passed by the caller
//
Acad::ErrorStatus
selectCurves(AcDbObjectIdArray& idArray)
{
	ads_name selection;
	int rc = acedSSGet(NULL, NULL, NULL, NULL, selection);
	if(rc != RTNORM)
		return Acad::eInvalidInput;

	return selectCurves(idArray, selection);
}

// filters out from the selection set passed
// entities that are not curve or are old style
// polylines.
//
Acad::ErrorStatus
selectCurves(AcDbObjectIdArray& idArray, ads_name selection)
{
	long length;
	acedSSLength(selection, &length);
	if(length == 0)
	{
		acedSSFree(selection);
		return Acad::eInvalidInput;
	}
	ads_name entName;
	AcDbObjectId oId;
	AcDbEntity* pEnt;
	Acad::ErrorStatus es;
	long rejected = 0;
	for(long i=0; i<length; i++)
	{
		acedSSName(selection, i, entName);
		acdbGetObjectId(oId, entName);
		es = acdbOpenAcDbEntity(pEnt, oId, AcDb::kForRead);
		if(es != Acad::eOk)
		{
			acedSSFree(selection);
			return es;
		}
		if(pEnt->isKindOf(AcDbCurve::desc()))
		{
			// does not work with old style polyline
			// ray and infinite lines
			//
			if(!pEnt->isKindOf(AcDb2dPolyline::desc()) &&
				!pEnt->isKindOf(AcDb3dPolyline::desc()) &&
				!pEnt->isKindOf(AcDbRay::desc()) &&
				!pEnt->isKindOf(AcDbXline::desc()))
			{
				idArray.append(oId);
			}
			else
				rejected++;

		}
		else
			rejected++;

		pEnt->close();
	}

	if(rejected > 0)
		acutPrintf("%d entities filtered out.\n", rejected);

	acedSSFree(selection);
	if(idArray.length() == 0)
		return Acad::eInvalidInput;

	return Acad::eOk;
}

// Populates the array if Ids passed by the caller
// with curves coming from the implied selection set
// or, in its absence, from a new selection set.
//
Acad::ErrorStatus
getCurvesSelection(AcDbObjectIdArray& curvesArray)
{
	ads_name ss;
	// check if there is an implied selectoin set
	//
	int ret = acedSSGet("_I", NULL, NULL, NULL, ss); 
	Acad::ErrorStatus es;
	if(ret != RTNORM)
	{
		// if not, create one
		//
		es = selectCurves(curvesArray);
		if(es == Acad::eInvalidInput)
		{
			acutPrintf("No valid curves selected.\n");
			return es;
		}
		if(es != Acad::eOk)
			return es;
	}
	else 
	{
		// if there is a selection set, "clean" it
		// to retain only curves.
		// selectCurves frees the selection set
		//
		es = selectCurves(curvesArray, ss);
		if(es == Acad::eInvalidInput)
		{
			acutPrintf("No valid curves selected.\n");
			return es;
		}
			
		if(es != Acad::eOk)
			return es;
	}
	return Acad::eOk;
}

// print a formated point
void printPoint(AcGePoint3d pt)
{
	acutPrintf("X=%.*lf Y=%.*lf Z=%.*lf", _prec, pt.x,
								 		  _prec, pt.y,
										  _prec, pt.z);
}

// print a formated point
void printPoint(AcGeVector3d pt)
{
	acutPrintf("X=%.*lf Y=%.*lf Z=%.*lf", _prec, pt.x,
								 		  _prec, pt.y,
										  _prec, pt.z);
}

void refreshDisplay()
{
	actrTransactionManager->queueForGraphicsFlush();
	actrTransactionManager->flushGraphics();
	acedUpdateDisplay();
}

Adesk::Boolean
append(AcDbEntity* pEntity)
{
    AcDbObjectId objId;
    return append(pEntity, objId);
}

Adesk::Boolean
append(AcDbEntity* pEntity, AcDbObjectId& objId)
{

    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    ASSERT(pDb != NULL);

    AcDbBlockTable *pBlockTable;
    AOK(pDb->getBlockTable(pBlockTable, AcDb::kForRead));
    
	AcDbBlockTableRecord *pBlockRec;
    AOK(pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite));
    
	AOK(pBlockRec->appendAcDbEntity(objId, pEntity));
    pBlockRec->close();
    pBlockTable->close();
    return Adesk::kTrue;
}

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

AcDbObjectId
getTextStyleId(const CString styleName)
{
	AcDbDatabase * pDb = NULL;
	pDb = acdbHostApplicationServices()->workingDatabase();
	if(pDb == NULL)
		acrx_abort("!%s@%d: %s", __FILE__, __LINE__, "No database!");
	AcDbTextStyleTable *pTsTable;
	AOK(pDb->getTextStyleTable(pTsTable, AcDb::kForRead));
	AcDbObjectId styleId;
	AOK(pTsTable->getAt(styleName, styleId));
	pTsTable->close();
	return styleId;
}

GLOBALS::GLOBALS () {
	// dialog is dynmically updating
	// the graphic screen
	isDynamic = TRUE;
	// default string is empty
	string = "";
	// default text style is "STANDARD"
	styleId = getTextStyleId("STANDARD");
	// curve is shown
	showCurve = TRUE;
	// text is shown
	showText = TRUE;
	// text does not fit the curve
	fit = FALSE;
	reverse = FALSE;
	// The text willo not be repeated along the curve
	repeat = FALSE;
	// default text size is undefined
	// 1/20 of the screeen size will be used.
	size = getDefaultCharacterSize();
	// default space between charaters
	// is default
	space = 1.0;
	// The text starts at the beginning of the curve
	// and can cover the entire curve.
	length = startDist = 0.0;
	// test position is above the curve
	position = ABOVE;
	normal = getCurZdir();
	isStringVarying = false;
	isStyleIdVarying = false;
	isShowCurveVarying = false;
	isShowTextVarying = false;
	isFitVarying = false;
	isReverseVarying = false;
	isRepeatVarying = false;
	isSizeVarying = false;
	isSpaceVarying = false;
	isPositionVarying = false;
}

void
setInitialValues(class GLOBALS &glob)
{
	glob.isStringVarying = false;
	glob.isStyleIdVarying = false;
	glob.isShowCurveVarying = false;
	glob.isShowTextVarying = false;
	glob.isFitVarying = false;
	glob.isReverseVarying = false;
	glob.isRepeatVarying = false;
	glob.isSizeVarying = false;
	glob.isSpaceVarying = false;
	glob.isPositionVarying = false;
	glob.isDynamic = true;
}

void
setDefaultValues(AsdkCurveText* pCurveText)
{
	pCurveText->setString(global.string);
	pCurveText->setNormal(global.normal);
	pCurveText->setStyle(global.styleId);
	pCurveText->setSize(global.size);
	pCurveText->setSpace(global.space);
	pCurveText->showCurve(global.showCurve);
	pCurveText->showText(global.showText);
	pCurveText->setFit(global.fit);
	pCurveText->setRepeatText(global.repeat);
	pCurveText->setReverse(global.reverse);
	pCurveText->setStartDist(global.startDist);
	pCurveText->setLength(global.length);
	pCurveText->setPosition(global.position);
}

void
setInitialValues(AsdkCurveText* pCurveText, class GLOBALS &glob, bool isDefault)
{
	if(isDefault == true)
	{
		glob.string = pCurveText->getString();
		glob.normal = pCurveText->getNormal();
		glob.styleId = pCurveText->getStyle();
		glob.size = pCurveText->getSize();
		glob.space = pCurveText->getSpace();
		glob.showCurve = pCurveText->isCurveShown();
		glob.showText = pCurveText->isTextShown();
		glob.fit = pCurveText->isFit();
		glob.repeat = pCurveText->isRepeatText();
		glob.reverse = pCurveText->isReversed();
		glob.startDist = pCurveText->getStartDist();
		glob.length = pCurveText->getLength();
		glob.position = pCurveText->getPosition();
		return;
	}

	if(pCurveText->getString() != glob.string)
		glob.isStringVarying = true;
	if(pCurveText->getStyle() != glob.styleId)
		glob.isStyleIdVarying = true;
	if(pCurveText->getSize() != glob.size)
		glob.isSizeVarying = true;
	if(pCurveText->getSpace() != glob.space)
		glob.isSpaceVarying = true;
	if(pCurveText->isCurveShown() != glob.showCurve)
		glob.isShowCurveVarying = true;
	if(pCurveText->isTextShown() != glob.showText)
		glob.isShowTextVarying = true;
	if(pCurveText->isFit() != glob.fit)
		glob.isFitVarying = true;
	if(pCurveText->isRepeatText() != glob.repeat)
		glob.isRepeatVarying = true;
	if(pCurveText->isReversed() != glob.reverse)
		glob.isReverseVarying = true;
	if(pCurveText->getPosition() != glob.position)
		glob.isPositionVarying = true;
}

//----- Register the Application in the AutoCAD registry (demand loading)

void updateRegistry()
{
	// Fill the AppInfo structure with our demand loading details.
	AcadAppInfo appInfo;
	appInfo.setAppName("CurveTextARX"); // Application Name
	appInfo.setModuleName(acedGetAppName()); // ARX module location.
	appInfo.setAppDesc("CurveTextARX");	 // Description
	appInfo.setLoadReason(// Specify when we want this to load
		AcadApp::LoadReasons(
		AcadApp::kOnCommandInvocation |
		AcadApp::kOnLoadRequest));
	
	appInfo.writeToRegistry(false,true);// Write appInfo to the registry
	appInfo.writeGroupNameToRegistry("CURVETEXT"); // GroupName
	appInfo.writeCommandNameToRegistry("ACDG_CT","CT"); // Commands...
	appInfo.writeCommandNameToRegistry("ACDG_REVERSE","REVERSE");// --
}


