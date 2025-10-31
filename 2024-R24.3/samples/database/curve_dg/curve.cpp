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
// Description:
//
// This program demonstrates the use of some of the
// AcDbCurve protocol

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <stdlib.h>
#include <string.h>
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbelipse.h>
#include <dbsymtb.h>
#include <adslib.h>
#include <geassign.h>
#include <dbapserv.h>
#include "tchar.h"



void curves();
void projectEllipse(AcDbObjectId ellipseId);
void offsetEllipse(AcDbObjectId ellipseId);
Acad::ErrorStatus addToModelSpace(AcDbObjectId&, AcDbEntity*);
void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// This is the main function of this app.  It allows the
// user to select an entity.  It then checks to see if the
// entity is an ellipse.  If so, it calls projectCurve
// passing in the objectId of the ellipse.
//
void
curves()
{
    // Have the user select an ellipse.
    ads_name en;
    AcGePoint3d pt;
    if (acedEntSel(_T("\nSelect an Ellipse: "), en,
        asDblArray(pt)) != RTNORM)
    {
        acutPrintf(_T("\nNothing selected"));
        return;
    }

    // Now, exchange the ads_name for the object Id.
    //
    AcDbObjectId eId;
    acdbGetObjectId(eId, en);

    // If the entity is an ellipse, pass its objectId to the
    // function that will project it onto another plane.
    //
    AcDbObject *pObj;
    acdbOpenObject(pObj, eId, AcDb::kForRead);
    if (pObj->isKindOf(AcDbEllipse::desc())) {
        pObj->close();
    
        int rc;
        TCHAR kw[20];
        acedInitGet(0, _T("Offset Project"));
        rc = acedGetKword(_T("Offset/<Project>: "), kw);

        if ((rc != RTNORM) && (rc != RTNONE)) {
            acutPrintf(_T("\nNothing selected."));
            return;
        } else if (rc == RTNONE
            || _tcscmp(kw, _T("Project")) == 0)
            projectEllipse(eId);
        else
            offsetEllipse(eId);
    } else {
        pObj->close();
        acutPrintf(_T("\nSelected entity is not an ellipse"));
    }
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

// Accepts an ellipse object ID, opens the ellipse, and uses
// its getOrthoProjectedCurve member function to create a
// new ellipse that is the result of a projection onto the
// plane with normal <1,1,1>.  The resulting ellipse is
// added to the model space block Table Record.
//
void
projectEllipse(AcDbObjectId ellipseId)
{
    AcDbEllipse *pEllipse;
    acdbOpenObject(pEllipse, ellipseId, AcDb::kForRead);

    // Now project the ellipse onto a plane with a
    // normal of <1, 1, 1>.
    //
    AcDbEllipse *pProjectedCurve;
    pEllipse->getOrthoProjectedCurve(AcGePlane(
        AcGePoint3d::kOrigin, AcGeVector3d(1, 1, 1)),
        (AcDbCurve*&)pProjectedCurve);
    pEllipse->close();

    AcDbObjectId newCurveId;
    addToModelSpace(newCurveId, pProjectedCurve);
}

// Accepts an ellipse object ID, opens the ellipse, and uses
// its getOffsetCurves() member function to create a new
// ellipse that is offset 0.5 drawing units from the
// original ellipse.
//
void
offsetEllipse(AcDbObjectId ellipseId)
{
    AcDbEllipse *pEllipse;
    acdbOpenObject(pEllipse, ellipseId, AcDb::kForRead);

    // Now generate an ellipse offset by 0.5 drawing units.
    //
    AcDbVoidPtrArray curves;
    pEllipse->getOffsetCurves(0.5, curves);
    pEllipse->close();

    AcDbObjectId newCurveId;
    addToModelSpace(newCurveId, (AcDbEntity*)curves[0]);
}

// END CODE APPEARING IN SDK DOCUMENT.

// Accepts a pointer to an entity object and adds it to the
// Model Space block table record.
//
Acad::ErrorStatus
addToModelSpace(AcDbObjectId &objId, AcDbEntity* pEntity)
{
    AcDbBlockTable *pBlockTable;
    AcDbBlockTableRecord *pSpaceRecord;

    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord,
        AcDb::kForWrite);

    pBlockTable->close();

    pSpaceRecord->appendAcDbEntity(objId, pEntity);

    pEntity->close();
    pSpaceRecord->close();

    return Acad::eOk;
}


// Initialization function called from acrxEntryPoint during
// kInitAppMsg case.  This function is used to add commands
// to the command stack.
//
void
initApp()
{
    acedRegCmds->addCommand(_T("ASDK_CURVETEST"), _T("ASDK_CURVES"),
        _T("CURVES"), ACRX_CMD_MODAL, curves);
}


// Clean up function called from acrxEntryPoint during the
// kUnloadAppMsg case.  This function removes this app's
// command set from the command stack.
//
void
unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_CURVETEST"));
}


// ARX entry point
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}
