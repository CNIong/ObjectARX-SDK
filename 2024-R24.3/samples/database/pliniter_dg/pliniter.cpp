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
// This program demonstrates iterating over the vertices of
// a polyline

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <stdlib.h>
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbents.h>
#include <adslib.h>
#include <geassign.h>
#include "tchar.h"



void listPline();
void iterate(AcDbObjectId id);
void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// This is the main function of this app.  It allows the
// user to select an entity.  It then checks to see if the
// entity is a 2d-polyline.  If so, then it calls iterate
// passing in the objectId of the pline.
// 
void
listPline()
{
    int rc;
    ads_name en;
    AcGePoint3d pt;
    rc = acedEntSel(_T("\nSelect a polyline: "), en,
        asDblArray(pt));

    if (rc != RTNORM) {
        acutPrintf(_T("\nError during object selection"));
        return;
    }

    AcDbObjectId eId;
    acdbGetObjectId(eId, en);

    AcDbObject *pObj;
    acdbOpenObject(pObj, eId, AcDb::kForRead);
    if (pObj->isKindOf(AcDb2dPolyline::desc())) {
        pObj->close();
        iterate(eId);
    } else {
        pObj->close();
        acutPrintf(_T("\nSelected entity is not an AcDb2dPolyline. \nMake sure the setvar PLINETYPE is set to 0 before createing a polyline"));
    }
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

// Accepts the object ID of an AcDb2dPolyline, opens it, and gets
// a vertex iterator. It then iterates through the vertices,
// printing out the vertex location.
// 
void
iterate(AcDbObjectId plineId)
{
    AcDb2dPolyline *pPline;
    acdbOpenObject(pPline, plineId, AcDb::kForRead);

    AcDbObjectIterator *pVertIter= pPline->vertexIterator();
    pPline->close();  // Finished with the pline header.

    AcDb2dVertex *pVertex;
    AcGePoint3d location;
    AcDbObjectId vertexObjId;
    for (int vertexNumber = 0; !pVertIter->done();
        vertexNumber++, pVertIter->step())
    {
        vertexObjId = pVertIter->objectId();
        acdbOpenObject(pVertex, vertexObjId,
            AcDb::kForRead);
        location = pVertex->position();
        pVertex->close();

        acutPrintf(_T("\nVertex #%d's location is")
            _T(" : %0.3f, %0.3f, %0.3f"), vertexNumber,
            location[X], location[Y], location[Z]);
    }
    delete pVertIter;
}

// END CODE APPEARING IN SDK DOCUMENT.

// Initialization function called from acrxEntryPoint during
// kInitAppMsg case.  This function is used to add commands
// to the command stack.
// 
void
initApp()
{
    acedRegCmds->addCommand(_T("ASDK_PLINETEST_COMMANDS"),
        _T("ASDK_ITERATE"), _T("ITERATE"), ACRX_CMD_MODAL,
        listPline);
}

// Clean up function called from acrxEntryPoint during the
// kUnloadAppMsg case.  This function removes this apps
// command set from the command stack.
// 
void
unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_PLINETEST_COMMANDS"));
}

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
