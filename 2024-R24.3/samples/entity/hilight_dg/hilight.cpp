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
// This program demonstrates how to use ARX API functions to
// highlight and unhighlight subentities of complex entities
// such as ACIS solids.
//
// One command is defined called "RUN" which calls the function
// highlightTest.  highlightTest uses acedSSGet to allow the
// user to select a complex entity.  It then passes the
// selection set to acedSSNameX to get the graphics system
// marker for the subentity actually selected with the
// pointing device.  This graphics system marker is then
// used to get the appropriate AcDbFullSubentIdPath object
// which can be used with the highlight and unhighlight
// functions of AcDbObject.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <stdlib.h>
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include <adslib.h>
#include <gemat3d.h>
#include "tchar.h"



void highlightTest();
Acad::ErrorStatus getObjectAndGsMarker(AcDbObjectId&,
    int&);
void highlightEdge(const AcDbObjectId&, const int);
void highlightFaces(const AcDbObjectId&, const int);
void highlightAll(const AcDbObjectId&);
void initApp();
void unloadApp();
Acad::ErrorStatus
addToModelSpace(AcDbObjectId&, AcDbEntity*);
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

// This function calls getObjectAndGsMarker to get the
// object ID of a solid and its gsmarker.  It then calls
// highlightEdge, highlightFaces, and highlightAll to
// highlight the selected edge, all faces surrounding that
// edge, and then the whole solid.
//
void
highlightTest()
{
    AcDbObjectId objId;
    int marker;

    if (getObjectAndGsMarker(objId, marker) != Acad::eOk)
        return;
    highlightEdge(objId, marker);
    highlightFaces(objId, marker);
    highlightAll(objId);
}

// This function uses acedSSGet() to let the user select a
// single entity.  It then passes this selection set to
// acedSSNameX to get the gsmarker.  Finally, the entity name
// in the selection set is used to obtain the object ID of
// the selected entity.
//
Acad::ErrorStatus
getObjectAndGsMarker(AcDbObjectId& objId, int& marker)
{
    ads_name sset;

    if (acedSSGet(_T("_:S"), NULL, NULL, NULL, sset) != RTNORM) {
        acutPrintf(_T("\nacedSSGet has failed"));
        return Acad::eInvalidAdsName;
    }

    // Get the entity from the selection set and its
    // subentity ID.  This code assumes that the user
    // selected only one item, a solid.
    //
    struct resbuf *pRb;
    if (acedSSNameX(&pRb, sset, 0) != RTNORM) {
        acedSSFree(sset);
        return Acad::eAmbiguousOutput;
    }
    acedSSFree(sset);

    // Walk the list to the third item, which is the selected
    // entity's entity name.
    //
    struct resbuf *pTemp;
    int i;
    for (i=1, pTemp = pRb;i<3;i++, pTemp = pTemp->rbnext)
        { ; }

    ads_name ename;
    ads_name_set(pTemp->resval.rlname, ename);

    // Move on to the fourth list element, which is the gsmarker.
    //
    pTemp = pTemp->rbnext;
    marker = pTemp->resval.rint;

    acutRelRb(pRb);
    acdbGetObjectId(objId, ename);

    return Acad::eOk;
}

// This function accepts an object ID and a gsmarker.
// The object is opened, the gsmarker is used to get the
// AcDbFullSubentIdPath, which is then used to highlight
// and unhighlight the edge used to select the object.
// Next, the object's subentPtr() function is used to get
// a copy of the edge.  This copy is then added to the
// database.  Finally, the object is closed.
//
// Since the copy of the subentity was added to the database
// as a new AcDbLine entity, it remains visible in the drawing 
// editor after the command exits and will be reported by the 
// AutoCAD LIST command.
//
void
highlightEdge(const AcDbObjectId& objId, const int marker)
{
    TCHAR dummy[133]; // space for acedGetStringB pauses below

    AcDbEntity *pEnt;
    acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead);

    // Get the subentity ID for the edge that is picked
    //
    AcGePoint3d pickpnt;
    AcGeMatrix3d xform;
    int numIds;
    AcDbFullSubentPath *subentIds;
    pEnt->getSubentPathsAtGsMarker(AcDb::kEdgeSubentType,
        marker, pickpnt, xform, numIds, subentIds);

    // At this point the subentId's variable contains the
    // address of an array of AcDbFullSubentPath objects.
    // The array should be one element long, so the picked
    // edge's AcDbFullSubentPath is in subentIds[0].
    //
    // For objects with no edges (such as a sphere), the
    // code to highlight an edge is meaningless and must
    // be skipped.
    //
    if (numIds > 0) {
        // Highlight the edge.
        //
        pEnt->highlight(subentIds[0]);

        // Pause to let user see the effect.
        //
        acedGetString(0, _T("\npress <RETURN> to continue..."),
            dummy);

        // Unhighlight the picked edge.
        //
        pEnt->unhighlight(subentIds[0]);

        // Get a copy of the edge, and add it to the database.
        //
        AcDbEntity *pEntCpy = pEnt->subentPtr(subentIds[0]);
        AcDbObjectId objId;
        addToModelSpace(objId, pEntCpy);

    }
    delete []subentIds;

    pEnt->close();
}

// This function accepts an object ID and a gsmarker.
// The object is opened, the gsmarker is used to get the
// AcDbFullSubentIdPath, which is then used to highlight
// and unhighlight faces that share the edge used to
// select the object.  The object is then closed.
//
void
highlightFaces(const AcDbObjectId& objId, const int marker)
{
    TCHAR dummy[133];

    AcDbEntity *pEnt;
    acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead);

    // Get the subentIds for the faces.
    //
    AcGePoint3d pickpnt;
    AcGeMatrix3d xform;
    int numIds;
    AcDbFullSubentPath *subentIds;
    pEnt->getSubentPathsAtGsMarker(AcDb::kFaceSubentType,
        marker, pickpnt, xform, numIds, subentIds);

    // Walk the subentIds list, highlighting each face subentity.
    //
    for (int i = 0;i < numIds; i++) {
        pEnt->highlight(subentIds[i]); // Highlight face.

        // Pause to let the user see the effect.
        //
        acedGetString(0, _T("\npress <RETURN> to continue..."),
            dummy);

        pEnt->unhighlight(subentIds[i]);
    }
    delete []subentIds;
    pEnt->close();
}

// This function accepts an object ID.  The object is opened,
// and its highlight() and unhighlight() functions are
// used with no parameters, to highlight and
// unhighlight the edge used to select the object.  The
// object is then closed.
//
void
highlightAll(const AcDbObjectId& objId)
{
    TCHAR dummy[133];

    AcDbEntity *pEnt;
    acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead);

    // Highlight the whole solid.
    //
    pEnt->highlight();

    // Pause to let user see the effect.
    //
    acedGetString(0, _T("\npress <RETURN> to continue..."),
        dummy);

    pEnt->unhighlight();
    pEnt->close();
}


Acad::ErrorStatus
addToModelSpace(AcDbObjectId &objId, AcDbEntity* pEntity)
{
    AcDbBlockTable *pBlockTable;
    AcDbBlockTableRecord *pSpaceRecord;

    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord,
        AcDb::kForWrite);

    pSpaceRecord->appendAcDbEntity(objId, pEntity);

    pBlockTable->close();
    pEntity->close();
    pSpaceRecord->close();

    return Acad::eOk;
}

// END CODE APPEARING IN SDK DOCUMENT.

// Initialization function called in acrxEntryPoint during
// the kInitAppMsg case.  This is where commands are added
// to the AcEd command stack.
//
void
initApp()
{
    acedRegCmds->addCommand(_T("ASDK_HILIGHTTEST_COMMANDS"),
        _T("ASDK_RUN"), _T("RUN"), ACRX_CMD_MODAL, highlightTest);
}

// Clean up function called in acrxEntryPoint during the
// kUnloadAppMsg case.  This app's command group is removed
// from the AcEd command stack.
//
void
unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_HILIGHTTEST_COMMANDS"));
}


// ARX entry point.
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

// The following is for informational purposes only and is
// not really needed for the code above.
//
// acedSSNameX list format. The restype of each resbuf is
// shown.
//
// For pick method:
//    5016 -- start of entity
//    5003 -- selection method
//    5006 -- picked entity's name (could be subname)
//    5003 -- GS marker
//    5016 -- start of list for pick point
//    5003 -- point description, not used.
//    5009 -- pick location (WCS)
//    5009 -- (only if view is not XY) normal vec for pnt
//    5017 -- end of list for pick point
//    5009 -- xform data (X vector in rotation matrix)
//    5009 -- xform data (Y vector in rotation matrix)
//    5009 -- xform data (Z vector in rotation matrix)
//    5009 -- xform data (Translation vector)
//    5006 -- (only if applicable) first block in
//             acedNEntSelP-style containing blocks list.
//    :    -- (only if applicable) etc. for rest of
//             containing blocks.
//    5017 -- end of entity
//
// For fence method:
//    5016 -- start of entity
//    5003 -- selection method
//    5006 -- picked entity's name (could be subname)
//    5003 -- GS marker
//    5016 -- start of list for first fence intersection
//             with entity.
//    5003 -- point description, not used.
//    5009 -- pick location (WCS)
//    5009 -- (only if view is not XY) normal vec for pnt
//    5017 -- end of list for first fence intersection
//         -- with entity  etc. for rest of fence points
//    5017 -- end of entity
//
// For crossing, window, crossing polygon, and window
// polygon methods:
//    5016 -- start of entity
//    5003 -- selection method
//    5006 -- pick entity's name
//    5003 -- GS marker
//    5003 -- polygon/window ID.
//    5017 -- end of entity
//    5016 -- Start of polygon/window pick points
//    5003 -- Polygon/Window ID.
//    5016 -- Start of first point
//    5003 -- point description, not used.
//    5009 -- pick location (WCS)
//    5009 -- (only if view is not XY) normal vec for pnt
//    5017 -- end of first point.
//    :    -- etc. for rest of polygon/window pick points.
//    5017 -- end of polygon/window pick points.
//
// For all method and groups (no location or container
// information):
//    5016 -- start of entity
//    5003 -- selection method
//    5006 -- picked entity's name
//    5003 -- GS marker
//    5017 -- end of entity
//
// Note that the crossing methods currently have a bug
// that returns the the subentities in block entities
// instead of only the block entity.  Each subentity
// returned will have containing block information.
