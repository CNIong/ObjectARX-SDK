// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// TRANSACT.CPP 
//
// DESCRIPTION:
//
// This file contains sample code exercising the transaction
// model.


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


// static functions used in this file.

static Acad::ErrorStatus createAndPostPoly();
static Acad::ErrorStatus
extrudePoly(AsdkPoly* pPoly, double height, AcDbObjectId& savedExtrusionId);
static Acad::ErrorStatus getASolid(char* prompt, 
    AcTransaction* pTransaction, 
    AcDb::OpenMode mode,
    AcDbObjectId checkWithThisId,
    AcDb3dSolid*& pSolid);



// External functions from command.cc
//
Acad::ErrorStatus getYOrN(char*, Adesk::Boolean, Adesk::Boolean&,Adesk::Boolean& interrupted);

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
    acutPrintf("\nCreating a poly...Please supply the"
        " required input.");
    if ((es = createAndPostPoly()) != Acad::eOk)
        return;

    // Start a transaction
    //
    AcTransaction *pTrans
        = actrTransactionManager->startTransaction();
    assert(pTrans != NULL);
    acutPrintf("\n\n######  Started transaction one."
        " ######\n");

    // Select the poly and extrude it.
    //
    AcDbObject   *pObj = NULL;
    AsdkPoly     *pPoly = NULL;
    AcDb3dSolid  *pSolid = NULL;
    AcDbObjectId  objId;

    ads_name      ename;
    ads_point     pickpt;

    for (;;) {

        switch (acedEntSel("\nSelect a polygon: ",
            ename, pickpt))
        {

        case RTNORM:
            acdbGetObjectId(objId, ename);
            if ((es = pTrans->getObject(pObj, objId,
                AcDb::kForRead)) != Acad::eOk)
            {
                acutPrintf("\nFailed to obtain an object"
                    " through transaction.");
                actrTransactionManager->abortTransaction();
                return;
            }
            assert(pObj != NULL);

            pPoly = AsdkPoly::cast(pObj);
            if (pPoly == NULL) {
                acutPrintf("\nNot a polygon. Try again");
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
    acutPrintf("\nWe will be extruding the poly.");
    AcGePoint2d c2d = pPoly->center();
    ads_point pt;
    pt[0] = c2d[0]; pt[1] = c2d[1]; pt[2] = pPoly->elevation();
    acdbEcs2Ucs(pt,pt,asDblArray(pPoly->normal()),Adesk::kFalse);
    double height;
    if (acedGetDist(pt, "\nEnter Extrusion height: ",
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
    acutPrintf("\nCreated a cylinder at the center of"
        " the poly.");

    // Start another transaction. Ask the user to select
    // the extruded solid followed by selecting the
    // cylinder. Make a hole in the extruded solid by
    // subtracting the cylinder from it.
    //
    pTrans = actrTransactionManager->startTransaction();
    assert(pTrans != NULL);
    acutPrintf("\n\n######  Started transaction two."
        " ######\n");

    AcDb3dSolid *pExtrusion, *pCylinder;
    if ((es = getASolid("\nSelect the extrusion: ", pTrans, 
        AcDb::kForWrite, savedExtrusionId, pExtrusion))
        != Acad::eOk)
    {
        actrTransactionManager->abortTransaction();
        actrTransactionManager->abortTransaction();
        return;
    }
    assert(pExtrusion != NULL);

    if ((es = getASolid("\nSelect the cylinder: ", pTrans, 
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
    acutPrintf("\nSubtracted the cylinder from the"
        " extrusion.");

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
    acutPrintf("\n\n#####  Started transaction three."
        " ######\n");

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
    acutPrintf("\nSliced the resulting solid into half"
        " and moved one piece.");

    // After all this work, let's abort transaction three,
    // so that we are back to the hole in the extrusion.
    //
    Adesk::Boolean yes = Adesk::kTrue;
    if (getYOrN("\nLet's abort transaction three, yes?"
        " [Y] : ", Adesk::kTrue, yes,interrupted) == Acad::eOk 
        && yes == Adesk::kTrue)
    {
        acutPrintf("\n\n$$$$$$  Aborting transaction"
            " three. $$$$$$\n");
        actrTransactionManager->abortTransaction();
        acutPrintf("\nBack to the un-sliced solid.");
        pExtrusion->draw();
        char option[256];
        acedGetKword("\nHit any key to continue.", option);
    } else {
        acutPrintf("\n\n>>>>>>  Ending transaction three."
            " <<<<<<\n");
        actrTransactionManager->endTransaction();
    }

    // Start another transaction (three again). This time
    // slice the solid along a plane that is perpendicular
    // to the plane we used last time. That's the slice
    // we really wanted.
    //
    pTrans = actrTransactionManager->startTransaction();
    assert(pTrans != NULL);
    acutPrintf("\n\n#####  Started transaction three."
        " ######\n");

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
    acutPrintf("\nSliced the resulting solid into half"
        " along a plane");
    acutPrintf("\nperpendicular to the old one and moved"
        " one piece.");

    // Now, optionally, let's end all the transactions.
    //
    yes = Adesk::kFalse;
    if (getYOrN("\nAbort transaction three? <No> : ",
        Adesk::kFalse, yes,interrupted) == Acad::eOk 
        && yes == Adesk::kTrue)
    {
        acutPrintf("\n\n$$$$$$  Aborting transaction"
            " three. $$$$$$\n");
        actrTransactionManager->abortTransaction();
        acutPrintf("\nBack to the un-sliced solid.");
    } else {
        acutPrintf("\n\n>>>>>>  Ending transaction three."
            " <<<<<<\n");
        actrTransactionManager->endTransaction();
    }

    yes = Adesk::kFalse;
    if (getYOrN("\nAbort transaction two? <No> : ",
        Adesk::kFalse, yes,interrupted) == Acad::eOk 
        && yes == Adesk::kTrue)
    {
        acutPrintf("\n\n$$$$$$  Aborting transaction two."
            " $$$$$$\n");
        actrTransactionManager->abortTransaction();
        acutPrintf("\nBack to separate extrusion and"
            " cylinder.");
    } else {
        acutPrintf("\n\n>>>>>>  Ending transaction two."
            " <<<<<<\n");
        actrTransactionManager->endTransaction();
    }

    yes = Adesk::kFalse;
    if (getYOrN("\nAbort transaction one? <No> : ",
        Adesk::kFalse, yes,interrupted) == Acad::eOk 
        && yes == Adesk::kTrue)
    {
        acutPrintf("\n\n$$$$$$  Aborting transaction one."
            " $$$$$$\n");
        actrTransactionManager->abortTransaction();
        acutPrintf("\nBack to just the Poly.");
    } else {
        actrTransactionManager->endTransaction();
        acutPrintf("\n\n>>>>>>  Ending transaction one."
            " <<<<<<\n");
    }
}


static Acad::ErrorStatus
createAndPostPoly()
{
    int nSides = 0;

    while (nSides < 3) {

        acedInitGet(INP_NNEG, "");
        switch (acedGetInt("\nEnter number of sides: ",
            &nSides))
        {

        case RTNORM:
            if (nSides < 3)
               acutPrintf("\nNeed at least 3 sides.");
            break;
        default:
            return Acad::eInvalidInput;
        }
    }

    ads_point center, startPt, normal;

    if (acedGetPoint(NULL, "\nLocate center of polygon: ",
        center) != RTNORM)
    {
        return Acad::eInvalidInput;
    }

    startPt[0] = center[0];
    startPt[1] = center[1];
    startPt[2] = center[2];
    
    while (asPnt3d(startPt) == asPnt3d(center)) {
        switch (acedGetPoint(center,
            "\nLocate start point of polygon: ", startPt)) {
            case RTNORM:
                if (asPnt3d(center) == asPnt3d(startPt))
                    acutPrintf("\nPick a point different"
                        " from the center.");
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
    if ((es=pPoly->set(cen, start, nSides, norm, "transactPoly", elev))!=Acad::eOk)
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
    for (i = 0; i < regions.length(); i++) {
        delete (AcRxObject*)regions[i];
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
getASolid(char*          prompt, 
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

            AOK(acdbGetObjectId(objId, ename));
            if (objId != checkWithThisId) {
                acutPrintf("\n Select the proper"
                    " solid.");
                continue;
            }

            AOK(pTransaction->getObject(pObj, objId, mode));
            assert(pObj != NULL);

            pSolid = AcDb3dSolid::cast(pObj);
            if (pSolid == NULL) {
                acutPrintf("\nNot a solid. Try again");
                AOK(pObj->close());
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
