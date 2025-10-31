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
// TRANSACT.CPP 
//
// DESCRIPTION:
//
// This file contains sample code exercising the transaction
// model.


#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#ifdef _ADESK_WINDOWS_
#include <wtypes.h>
#endif

#include <Windows.h>
#include <assert.h>

#include "actrans.h"

#include "adslib.h"
#include "dbents.h"
#include "dbregion.h"
#include "dbsol3d.h"

#include "gepnt3d.h"

#include "poly.h"
#include "util.h"
#include "dbxutil.h"
#include "dbapserv.h"
#include "tchar.h"




// static functions used in this file.

static Acad::ErrorStatus createAndPostPoly();
static Acad::ErrorStatus
extrudePoly(AsdkPoly* pPoly, double height, AcDbObjectId& savedExtrusionId);
static Acad::ErrorStatus getASolid(TCHAR* prompt, 
    AcTransaction* pTransaction, 
    AcDb::OpenMode mode,
    AcDbObjectId checkWithThisId,
    AcDb3dSolid*& pSolid);



// External functions from command.cc
//
Acad::ErrorStatus getYOrN(TCHAR*, Adesk::Boolean, Adesk::Boolean&,Adesk::Boolean& interrupted);

// Invoked by the command - TRANSACT
//

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
transactCommand()
{
    Adesk::Boolean interrupted;
    Acad::ErrorStatus es = Acad::eOk;
    AcDbObjectId savedCylinderId,savedExtrusionId;
    // Create a poly and post it to the database.
    //
    acutPrintf(_T("\nCreating a poly...Please supply the")
        _T(" required input."));
    if ((es = createAndPostPoly()) != Acad::eOk)
        return;

    // Start a transaction
    //
    AcTransaction *pTrans
        = actrTransactionManager->startTransaction();
    assert(pTrans != NULL);
    acutPrintf(_T("\n\n######  Started transaction one.")
        _T(" ######\n"));

    // Select the poly and extrude it.
    //
    AcDbObject   *pObj = NULL;
    AsdkPoly     *pPoly = NULL;
    AcDb3dSolid  *pSolid = NULL;
    AcDbObjectId  objId;

    ads_name      ename;
    ads_point     pickpt;

    for (;;) {

        switch (acedEntSel(_T("\nSelect a polygon: "),
            ename, pickpt))
        {

        case RTNORM:
            acdbGetObjectId(objId, ename);
            if ((es = pTrans->getObject(pObj, objId,
                AcDb::kForRead)) != Acad::eOk)
            {
                acutPrintf(_T("\nFailed to obtain an object")
                    _T(" through transaction."));
                actrTransactionManager->abortTransaction();
                return;
            }
            assert(pObj != NULL);

            pPoly = AsdkPoly::cast(pObj);
            if (pPoly == NULL) {
                acutPrintf(_T("\nNot a polygon. Try again"));
                continue;
            }
            break;

        case RTNONE:
        case RTCAN:
            actrTransactionManager->abortTransaction();
            return;
        default:
            continue;
        }
        break;
    }

    // Now that we have a poly, convert it to a region
    // and extrude it.
    //
    acutPrintf(_T("\nWe will be extruding the poly."));
    AcGePoint2d c2d = pPoly->center();
    ads_point pt;
    pt[0] = c2d[0]; pt[1] = c2d[1]; pt[2] = pPoly->elevation();
    acdbEcs2Ucs(pt,pt,asDblArray(pPoly->normal()),Adesk::kFalse);
    double height;
    if (acedGetDist(pt, _T("\nEnter Extrusion height: "),
        &height) != RTNORM)
    {
        actrTransactionManager->abortTransaction();
        return;
    }

    if ((es = extrudePoly(pPoly, height,savedExtrusionId)) != Acad::eOk) {
        actrTransactionManager->abortTransaction();
        return;
    }

    // Create a cylinder at the center of the polygon of
    // the same height as the extruded poly.
    //
    double radius = (pPoly->startPoint()
        - pPoly->center()).length() * 0.5;

    pSolid = new AcDb3dSolid;
    assert(pSolid != NULL);
    pSolid->createFrustum(height, radius, radius, radius);

    AcGeMatrix3d mat(AcGeMatrix3d::translation(pPoly->elevation()*pPoly->normal())*
        AcGeMatrix3d::planeToWorld(pPoly->normal()));
    pSolid->transformBy(mat);

    // Move it up again by half the height along
    // the normal.
    //
    AcGeVector3d x(1, 0, 0), y(0, 1, 0), z(0, 0, 1);
    AcGePoint3d  moveBy(pPoly->normal()[0] * height * 0.5, 
                        pPoly->normal()[1] * height * 0.5, 
                        pPoly->normal()[2] * height * 0.5);
    mat.setCoordSystem(moveBy, x, y, z);
    pSolid->transformBy(mat);

    // Move it, so center of cylinder will equal center of poly
    AcGePoint3d pt1 ;
    pPoly->getCenter (pt1) ;
    AcGeMatrix3d mat1(AcGeMatrix3d::translation(pt1 - AcGePoint3d ())) ;
    pSolid->transformBy(mat1);

    addToDb(pSolid, savedCylinderId);
    actrTransactionManager
        ->addNewlyCreatedDBRObject(pSolid);
    pSolid->draw();
    acutPrintf(_T("\nCreated a cylinder at the center of")
        _T(" the poly."));

    // Start another transaction. Ask the user to select
    // the extruded solid followed by selecting the
    // cylinder. Make a hole in the extruded solid by
    // subtracting the cylinder from it.
    //
    pTrans = actrTransactionManager->startTransaction();
    assert(pTrans != NULL);
    acutPrintf(_T("\n\n######  Started transaction two.")
        _T(" ######\n"));

    AcDb3dSolid *pExtrusion, *pCylinder;
    if ((es = getASolid(_T("\nSelect the extrusion: "), pTrans, 
        AcDb::kForWrite, savedExtrusionId, pExtrusion))
        != Acad::eOk)
    {
        actrTransactionManager->abortTransaction();
        actrTransactionManager->abortTransaction();
        return;
    }
    assert(pExtrusion != NULL);

    if ((es = getASolid(_T("\nSelect the cylinder: "), pTrans, 
        AcDb::kForWrite, savedCylinderId, pCylinder))
        != Acad::eOk)
    {
        actrTransactionManager->abortTransaction();
        actrTransactionManager->abortTransaction();
        return;
    }
    assert(pCylinder != NULL);

    pExtrusion->booleanOper(AcDb::kBoolSubtract, pCylinder);
    pExtrusion->draw();
    acutPrintf(_T("\nSubtracted the cylinder from the")
        _T(" extrusion."));

    // At this point, cylinder is a NULL solid. We might
    // as well erase it.
    //
    assert(pCylinder->isNull());
    pCylinder->erase();

    // Start another transaction and slice the resulting
    // solid into two halves. 
    //
    pTrans = actrTransactionManager->startTransaction();
    assert(pTrans != NULL);
    acutPrintf(_T("\n\n#####  Started transaction three.")
        _T(" ######\n"));

    AcGeVector3d vec, normal;
    AcGePoint3d sp,center;
    pPoly->getStartPoint(sp);
    pPoly->getCenter(center);
    vec = sp - center;
    normal = pPoly->normal().crossProduct(vec);
    normal.normalize();
    AcGePlane sectionPlane(center, normal);

    AcDb3dSolid *pOtherHalf = NULL;
    pExtrusion->getSlice(sectionPlane, Adesk::kTrue,
        pOtherHalf);
    assert(pOtherHalf != NULL);

    // Move the other half three times the vector length
    // along the vector.
    //
    moveBy.set(vec[0] * 3.0, vec[1] * 3.0, vec[2] * 3.0);
    mat.setCoordSystem(moveBy, x, y, z);
    pOtherHalf->transformBy(mat);
    AcDbObjectId otherHalfId;
    addToDb(pOtherHalf, otherHalfId);
    actrTransactionManager
        ->addNewlyCreatedDBRObject(pOtherHalf);
    pOtherHalf->draw();
    pExtrusion->draw();
    acutPrintf(_T("\nSliced the resulting solid into half")
        _T(" and moved one piece."));

    // After all this work, let's abort transaction three,
    // so that we are back to the hole in the extrusion.
    //
    Adesk::Boolean yes = Adesk::kTrue;
    if (getYOrN(_T("\nLet's abort transaction three, yes?")
        _T(" [Y] : "), Adesk::kTrue, yes,interrupted) == Acad::eOk 
        && yes == Adesk::kTrue)
    {
        acutPrintf(_T("\n\n$$$$$$  Aborting transaction")
            _T(" three. $$$$$$\n"));
        actrTransactionManager->abortTransaction();
        acutPrintf(_T("\nBack to the un-sliced solid."));
        pExtrusion->draw();
        TCHAR option[256];
        acedGetKword(_T("\nHit any key to continue."), option);
    } else {
        acutPrintf(_T("\n\n>>>>>>  Ending transaction three.")
            _T(" <<<<<<\n"));
        actrTransactionManager->endTransaction();
    }

    // Start another transaction (three again). This time
    // slice the solid along a plane that is perpendicular
    // to the plane we used last time. That's the slice
    // we really wanted.
    //
    pTrans = actrTransactionManager->startTransaction();
    assert(pTrans != NULL);
    acutPrintf(_T("\n\n#####  Started transaction three.")
        _T(" ######\n"));

    moveBy.set(normal[0] * 3.0, normal[1] * 3.0,
        normal[2] * 3.0);
    normal = vec;
    normal.normalize();
    sectionPlane.set(center, normal);

    pOtherHalf = NULL;
    pExtrusion->getSlice(sectionPlane, Adesk::kTrue,
        pOtherHalf);
    assert(pOtherHalf != NULL);

    mat.setCoordSystem(moveBy, x, y, z);
    pOtherHalf->transformBy(mat);
    addToDb(pOtherHalf, otherHalfId);
    actrTransactionManager
        ->addNewlyCreatedDBRObject(pOtherHalf);
    pOtherHalf->draw();
    pExtrusion->draw();
    acutPrintf(_T("\nSliced the resulting solid into half")
        _T(" along a plane"));
    acutPrintf(_T("\nperpendicular to the old one and moved")
        _T(" one piece."));

    // Now, optionally, let's end all the transactions.
    //
    yes = Adesk::kFalse;
    if (getYOrN(_T("\nAbort transaction three? <No> : "),
        Adesk::kFalse, yes,interrupted) == Acad::eOk 
        && yes == Adesk::kTrue)
    {
        acutPrintf(_T("\n\n$$$$$$  Aborting transaction")
            _T(" three. $$$$$$\n"));
        actrTransactionManager->abortTransaction();
        acutPrintf(_T("\nBack to the un-sliced solid."));
    } else {
        acutPrintf(_T("\n\n>>>>>>  Ending transaction three.")
            _T(" <<<<<<\n"));
        actrTransactionManager->endTransaction();
    }

    yes = Adesk::kFalse;
    if (getYOrN(_T("\nAbort transaction two? <No> : "),
        Adesk::kFalse, yes,interrupted) == Acad::eOk 
        && yes == Adesk::kTrue)
    {
        acutPrintf(_T("\n\n$$$$$$  Aborting transaction two.")
            _T(" $$$$$$\n"));
        actrTransactionManager->abortTransaction();
        acutPrintf(_T("\nBack to separate extrusion and")
            _T(" cylinder."));
    } else {
        acutPrintf(_T("\n\n>>>>>>  Ending transaction two.")
            _T(" <<<<<<\n"));
        actrTransactionManager->endTransaction();
    }

    yes = Adesk::kFalse;
    if (getYOrN(_T("\nAbort transaction one? <No> : "),
        Adesk::kFalse, yes,interrupted) == Acad::eOk 
        && yes == Adesk::kTrue)
    {
        acutPrintf(_T("\n\n$$$$$$  Aborting transaction one.")
            _T(" $$$$$$\n"));
        actrTransactionManager->abortTransaction();
        acutPrintf(_T("\nBack to just the Poly."));
    } else {
        actrTransactionManager->endTransaction();
        acutPrintf(_T("\n\n>>>>>>  Ending transaction one.")
            _T(" <<<<<<\n"));
    }
}


static Acad::ErrorStatus
createAndPostPoly()
{
    int nSides = 0;

    while (nSides < 3) {

        acedInitGet(INP_NNEG, _T(""));
        switch (acedGetInt(_T("\nEnter number of sides: "),
            &nSides))
        {

        case RTNORM:
            if (nSides < 3)
               acutPrintf(_T("\nNeed at least 3 sides."));
            break;
        default:
            return Acad::eInvalidInput;
        }
    }

    ads_point center, startPt, normal;

    if (acedGetPoint(NULL, _T("\nLocate center of polygon: "),
        center) != RTNORM)
    {
        return Acad::eInvalidInput;
    }

    startPt[0] = center[0];
    startPt[1] = center[1];
    startPt[2] = center[2];
    
    while (asPnt3d(startPt) == asPnt3d(center)) {
        switch (acedGetPoint(center,
            _T("\nLocate start point of polygon: "), startPt)) {
            case RTNORM:
                if (asPnt3d(center) == asPnt3d(startPt))
                    acutPrintf(_T("\nPick a point different")
                        _T(" from the center."));
                break;
            default:
                return Acad::eInvalidInput;
        }
    }


    // Set the normal to the plane of the polygon to be
    // the same as the z direction of the current ucs,
    // i.e. (0, 0, 1) since we also got the center and
    // start point in the current UCS. (acedGetPoint()
    // returns in the current UCS.)

    normal[X] = 0.0;
    normal[Y] = 0.0;
    normal[Z] = 1.0;

    acdbUcs2Wcs(normal, normal, Adesk::kTrue);
    acdbUcs2Ecs(center, center, normal, Adesk::kFalse);
    acdbUcs2Ecs(startPt, startPt, normal, Adesk::kFalse);
    double elev = center[2];
    AcGePoint2d cen = asPnt2d(center),
                start = asPnt2d(startPt);
    AcGeVector3d norm = asVec3d(normal);

    AsdkPoly *pPoly = new AsdkPoly;

    if (pPoly==NULL)
        return Acad::eOutOfMemory;
    Acad::ErrorStatus es;
    if ((es=pPoly->set(cen, start, nSides, norm, _T("transactPoly"), elev))!=Acad::eOk)
        return es;

    pPoly->setDatabaseDefaults(acdbHostApplicationServices()->workingDatabase());
    postToDb(pPoly);

    return Acad::eOk;
}



// Extrudes the poly to a given height.

static Acad::ErrorStatus
extrudePoly(AsdkPoly* pPoly, double height, AcDbObjectId& savedExtrusionId)
{
    Acad::ErrorStatus es = Acad::eOk;

    // Explode to a set of lines
    //
    AcDbVoidPtrArray lines;
    pPoly->explode(lines);

    // Create a region from the set of lines.
    //
    AcDbVoidPtrArray regions;
    AcDbRegion::createFromCurves(lines, regions);
    assert(regions.length() == 1);
    AcDbRegion *pRegion
        = AcDbRegion::cast((AcRxObject*)regions[0]);
    assert(pRegion != NULL);

    // Extrude the region to create a solid.
    //
    AcDb3dSolid *pSolid = new AcDb3dSolid;
    assert(pSolid != NULL);
    pSolid->extrude(pRegion, height, 0.0);

    for (int i = 0; i < lines.length(); i++) {
        delete (AcRxObject*)lines[i];
    }
    for (int ii = 0; ii < regions.length(); ii++) {
        delete (AcRxObject*)regions[ii];
    }

    // Now we have a solid. Add it to database, then
    // associate the solid with a transaction. After
    // this, transaction management is in charge of
    // maintaining it.
    //

    pSolid->setPropertiesFrom(pPoly);
    addToDb(pSolid, savedExtrusionId);
    actrTransactionManager
        ->addNewlyCreatedDBRObject(pSolid);
    pSolid->draw();

    return Acad::eOk;
}


static Acad::ErrorStatus
getASolid(TCHAR*          prompt, 
          AcTransaction* pTransaction, 
          AcDb::OpenMode mode,
          AcDbObjectId   checkWithThisId,
          AcDb3dSolid*&  pSolid)
{
    AcDbObject   *pObj = NULL;
    AcDbObjectId  objId;

    ads_name      ename;
    ads_point     pickpt;

    for (;;) {

        switch (acedEntSel(prompt, ename, pickpt)) {

        case RTNORM:

            acdbGetObjectId(objId, ename);
            if (objId != checkWithThisId) {
                acutPrintf(_T("\n Select the proper")
                    _T(" solid."));
                continue;
            }

            pTransaction->getObject(pObj, objId, mode);
            assert(pObj != NULL);

            pSolid = AcDb3dSolid::cast(pObj);
            if (pSolid == NULL) {
                acutPrintf(_T("\nNot a solid. Try again"));
                pObj->close();
                continue;
            }
            break;

        case RTNONE:
        case RTCAN:
            return Acad::eInvalidInput;
        default:
            continue;
        }
        break;
    }

    return Acad::eOk;
}

// END CODE APPEARING IN SDK DOCUMENT.
