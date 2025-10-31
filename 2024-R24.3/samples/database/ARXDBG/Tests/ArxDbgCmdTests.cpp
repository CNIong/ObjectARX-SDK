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

#include "ArxDbgCmdTests.h"
#include "ArxDbgUiTdmEntities.h"
#include "ArxDbgUiTdmEditor.h"
#include "ArxDbgUiTdmDatabase.h"
#include "ArxDbgUiDlgServiceDict.h"
#include "ArxDbgUiDlgSysRegistry.h"
#include "ArxDbgKeywordArray.h"
#include "ArxDbgUiPrompts.h"
#include "ArxDbgSelSet.h"
#include "ArxDbgApp.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiDlgObjState.h"
#include "XformTest.h"
#include "EntMakeTest.h"
#include "TblMakeTest.h"
#include "ArxDbgUiDlgXdata.h"
#include "ArxDbgUiDlgColor.h"
#include "ArxDbgUiDlgTestCurves.h"
#include "ArxDbgUiDlgWorldDraw.h"
#include "ArxDbgUiDlgFilerTest.h"
#include "ArxDbgUiDlgSelSet.h"
#include "ArxDbgDwgFiler.h"
#include "ArxDbgUtilsGe.h"
#include "ArxDbgUiTdmTransDbClones.h"
#include "SdSysVar.h"



/****************************************************************************
**
**  ArxDbgCmdTests::registerCommandLineFunctions
**
**  **jma
**
*************************************/

void
ArxDbgCmdTests::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
    cmdStack->addCommand(appname, _T("ArxDbgTestState"),              _T("TestState"),              ACRX_CMD_MODAL, &testState);
    cmdStack->addCommand(appname, _T("ArxDbgTestXform"),              _T("TestXform"),              ACRX_CMD_MODAL, &testXform);
    cmdStack->addCommand(appname, _T("ArxDbgTestEntMake"),            _T("TestEntMake"),            ACRX_CMD_MODAL, &testEntMake);
    cmdStack->addCommand(appname, _T("ArxDbgTestTblMake"),            _T("TestTblMake"),            ACRX_CMD_MODAL, &testTblMake);
    cmdStack->addCommand(appname, _T("ArxDbgTestExtents"),            _T("TestExtents"),            ACRX_CMD_MODAL, &testExtents);
    cmdStack->addCommand(appname, _T("ArxDbgTestIntersect"),          _T("TestIntersect"),          ACRX_CMD_MODAL, &testIntersect);
    cmdStack->addCommand(appname, _T("ArxDbgTestGetGripPoints"),      _T("TestGetGripPoints"),      ACRX_CMD_MODAL, &testGetGripPoints);
    cmdStack->addCommand(appname, _T("ArxDbgTestGetStretchPoints"),   _T("TestGetStretchPoints"),   ACRX_CMD_MODAL, &testGetStretchPoints);
    cmdStack->addCommand(appname, _T("ArxDbgTestGetOsnapPoints"),     _T("TestGetOsnapPoints"),     ACRX_CMD_MODAL, &testGetOsnapPoints);
    cmdStack->addCommand(appname, _T("ArxDbgTestExtDictAdd"),         _T("TestExtDictAdd"),         ACRX_CMD_MODAL, &testExtDictAdd);
    cmdStack->addCommand(appname, _T("ArxDbgTestExtDictRemove"),      _T("TextExtDictRemove"),      ACRX_CMD_MODAL, &testExtDictRemove);
    cmdStack->addCommand(appname, _T("ArxDbgTestTransDbClones"),      _T("TestTransDbClones"),      ACRX_CMD_MODAL, &testTransDatabaseClones);
    cmdStack->addCommand(appname, _T("ArxDbgTestXdata"),              _T("TestXdata"),              ACRX_CMD_MODAL, &testXdata);
    cmdStack->addCommand(appname, _T("ArxDbgTestColor"),              _T("TestColor"),              ACRX_CMD_MODAL, &testColor);
    cmdStack->addCommand(appname, _T("ArxDbgTestCurve"),              _T("TestCurve"),              ACRX_CMD_MODAL, &testCurve);
    cmdStack->addCommand(appname, _T("ArxDbgTestPruge"),              _T("TestPurge"),              ACRX_CMD_MODAL, &testPurge);
    cmdStack->addCommand(appname, _T("ArxDbgTestCountHardRefs"),      _T("TestCountHardRefs"),      ACRX_CMD_MODAL, &testCountReferences);
    cmdStack->addCommand(appname, _T("ArxDbgTestWblockCloneObjects"), _T("TestWblockCloneObjects"), ACRX_CMD_MODAL, &testWblockCloneObjects);
    cmdStack->addCommand(appname, _T("ArxDbgTestWorldDraw"),          _T("TestWorldDraw"),          ACRX_CMD_MODAL, &testWorldDraw);
    cmdStack->addCommand(appname, _T("ArxDbgTestDwgFiler"),           _T("TestDwgFiler"),           ACRX_CMD_MODAL, &testDwgFiler);
    cmdStack->addCommand(appname, _T("ArxDbgTestSelSet"),             _T("TestSelSet"),             (ACRX_CMD_MODAL  | ACRX_CMD_USEPICKSET), &testSelSet);
}

/****************************************************************************
**
**  ArxDbgCmdTests::testState
**      display the information available for a given entity.
**
**  **jma
**
*************************************/

void
ArxDbgCmdTests::testState()
{
    AcDbObjectId objId;
    if (!ArxDbgUtils::selectEntity(_T("\nSelect an entity: "), objId))
        return;

    ArxDbgUiDlgObjState dbox(acedGetAcadDwgView(), objId);
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxDbgCmdTests::testXform
**      display the information available for a given entity (but possibly nested
**    within a block or xref).
**
**  **jma
**
*************************************/

void
ArxDbgCmdTests::testXform()
{
    XformDbox dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

/****************************************************************************
**
**    ArxDbgCmdTests::testEntMake
**
**    **jma
**
*************************************/

void
ArxDbgCmdTests::testEntMake()
{
    EntMakeDbox dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

/****************************************************************************
**
**    ArxDbgCmdTests::testTblMake
**
**    **jma
**
*************************************/

void
ArxDbgCmdTests::testTblMake()
{
    TblMakeDbox dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

/************************************************************************
**
**    ArxDbgCmdTests::makePointEnt
**        make a point entity so you can debug where stuff is
**
**    **jma
**
***********************************/

void
ArxDbgCmdTests::makePointEnt(const AcGePoint3d& pt, int colorIndex)
{
    int mode = 0;
    getSysVar(_T("pdmode"), mode);
    if (mode == 0)
        setSysVar(_T("pdmode"), 99);

    AcDbPoint* tmpPt = new AcDbPoint(pt);
    tmpPt->setColorIndex(colorIndex);
    ArxDbgUtils::addToCurrentSpaceAndClose(tmpPt);
}

/****************************************************************************
**
**    ArxDbgCmdTests::extMakeAFace
**        Used by testExtents to assist in making a AcDbFace entity.
**
**    **jma
**
*************************************/

void
ArxDbgCmdTests::extMakeAFace(AcDbBlockTableRecord* blkRec,
        const AcGePoint3d& pt1, const AcGePoint3d& pt2,
        const AcGePoint3d& pt3, const AcGePoint3d& pt4)
{
    AcDbFace* face = new AcDbFace;
    face->setVertexAt(0, pt1);
    face->setVertexAt(1, pt2);
    face->setVertexAt(2, pt3);
    face->setVertexAt(3, pt4);

    Acad::ErrorStatus es = blkRec->appendAcDbEntity(face);
    if (es != Acad::eOk)
        ArxDbgUtils::rxErrorAlert(es);

    face->close();
}

/****************************************************************************
**
**  ArxDbgCmdTests::testExtents
**
**  **jma
**
*************************************/

void
ArxDbgCmdTests::testExtents()
{
    AcDbEntity* obj;
    AcGePoint3d p1, p2, p3, p4, p5, p6, p7, p8;
    Acad::ErrorStatus es;
    CString str;
    double deltaX, deltaY, deltaZ;
    AcGePoint3d centerPt;
    AcDbBlockTableRecord* newBlkRec;
    AcDbBlockReference* blkRef;
    AcGeVector3d offset;
    AcDbObjectId newBlockId;

    while (1) {
        if ((obj = ArxDbgUtils::selectEntity(nullptr, AcDb::kForRead)) == nullptr)
            return;

        AcDbExtents* extents = new AcDbExtents;        // have to allocate fresh each time or it just grows!
        if ((es = obj->getGeomExtents(*extents)) != Acad::eOk) {
            ArxDbgUtils::rxErrorMsg(es);
            obj->close();
            delete extents;
            continue;
        }

        acutPrintf(_T("\nEXTMIN:    %s"), ArxDbgUtils::ptToStr(extents->minPoint(), str));
        acutPrintf(_T("\nEXTMAX:    %s"), ArxDbgUtils::ptToStr(extents->maxPoint(), str));
        centerPt = ArxDbgUtilsGe::midpoint(extents->minPoint(), extents->maxPoint());
        acutPrintf(_T("\nCENTER PT: %s"), ArxDbgUtils::ptToStr(centerPt, str));

        deltaX = fabs(extents->maxPoint().x - extents->minPoint().x);
        deltaY = fabs(extents->maxPoint().y - extents->minPoint().y);
        deltaZ = fabs(extents->maxPoint().z - extents->minPoint().z);

        p1 = extents->minPoint();
        p7 = extents->maxPoint();

        delete extents;

            // make bottom face
        p2.set(p1.x + deltaX, p1.y, p1.z);
        p3.set(p2.x, p2.y + deltaY, p2.z);
        p4.set(p1.x, p1.y + deltaY, p1.z);

            // project up by Z
        p5.set(p1.x, p1.y, p1.z + deltaZ);
        p6.set(p2.x, p2.y, p2.z + deltaZ);
        p8.set(p4.x, p4.y, p4.z + deltaZ);

        offset = centerPt.asVector();

            // move points so that they are centered at WCS origin
            // for block creation.  Express everything in WCS since
            // that is what AcDbEntity::geomExtents() works in.
        p1 -= offset;
        p2 -= offset;
        p3 -= offset;
        p4 -= offset;
        p5 -= offset;
        p6 -= offset;
        p7 -= offset;
        p8 -= offset;

            // make an anonymous block that envelops the entity
        if (ArxDbgUtils::defineNewAnonymousBlock(newBlkRec, newBlockId,
                    acdbHostApplicationServices()->workingDatabase()) != Acad::eOk) {
            obj->close();
            return;
        }

        extMakeAFace(newBlkRec, p1, p2, p3, p4);    // bottom face
        extMakeAFace(newBlkRec, p5, p6, p7, p8);    // top face
        extMakeAFace(newBlkRec, p1, p2, p6, p5);    // front face
        extMakeAFace(newBlkRec, p2, p3, p7, p6);    // right side face
        extMakeAFace(newBlkRec, p3, p4, p8, p7);    // back side face
        extMakeAFace(newBlkRec, p4, p1, p5, p8);    // left side face

        newBlkRec->close();

            // insert the block into the drawing
        blkRef = new AcDbBlockReference;
        if (blkRef->setBlockTableRecord(newBlockId) != Acad::eOk) {
            delete blkRef;
            obj->close();
            return;
        }

        blkRef->setPosition(centerPt);
        blkRef->setDatabaseDefaults();
        ArxDbgUtils::addToCurrentSpaceAndClose(blkRef);
        obj->close();
    }
}

/****************************************************************************
**
**  ArxDbgCmdTests::testIntersect
**
**  **jma
**
*************************************/

void
ArxDbgCmdTests::testIntersect()
{
    AcDbEntity* obj1;
    AcDbEntity* obj2;
    AcGePoint3dArray points;
    int i, len;
    CString str;
    Acad::ErrorStatus es;
    AcGePoint3d pt1, pt2;
    AcDb::Intersect intType;

        // get intersection type from user
    ArxDbgUiPrKeyWord prIntType(_T("Extend objects [None/First/Second/Both]"),
            _T("None First Second Both"));
    if (prIntType.go() != ArxDbgUiPrBase::kOk)
        return;

    if (prIntType.isKeyWordPicked(_T("None")))
        intType = AcDb::kOnBothOperands;
    else if (prIntType.isKeyWordPicked(_T("First")))
        intType = AcDb::kExtendThis;
    else if (prIntType.isKeyWordPicked(_T("Second")))
        intType = AcDb::kExtendArg;
    else
        intType = AcDb::kExtendBoth;

    while (1) {
        if ((obj1 = ArxDbgUtils::selectEntity(_T("\nSelect first entity: "), AcDb::kForRead)) == nullptr)
            return;

        if ((obj2 = ArxDbgUtils::selectEntity(_T("\nSelect intersecting entity: "), AcDb::kForRead)) == nullptr) {
            obj1->close();
            return;
        }

        es = obj1->intersectWith(obj2, intType, points);

        if (es == Acad::eOk) {
            len = points.length();
            if (len == 0)
                acutPrintf(_T("\nObjects do not intersect!"));
            else {
                for (i=0;i<len;i++) {
                    acutPrintf(_T("\nINTERSECT PT:  %s"), ArxDbgUtils::ptToStr(points[i], str));
                    makePointEnt(points[i], 3);
                }
                points.setLogicalLength(0);
            }
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        obj1->close();
        obj2->close();
    }
}

/****************************************************************************
**
**  ArxDbgCmdTests::testGetGripPoints
**
**  **jma
**
*************************************/

void
ArxDbgCmdTests::testGetGripPoints()
{
    AcDbEntity* obj;
    AcGePoint3dArray gripPoints;
    AcDbIntArray osnapModes, geomIds;
    Acad::ErrorStatus es;
    CString str;

    while (1) {
        if ((obj = ArxDbgUtils::selectEntity(nullptr, AcDb::kForRead)) == nullptr)
            return;

            // empty previous loops results
        gripPoints.setLogicalLength(0);
        osnapModes.setLogicalLength(0);
        geomIds.setLogicalLength(0);

        es = obj->getGripPoints(gripPoints, osnapModes, geomIds);
        if (es == Acad::eOk) {
            int i;

                // print out grip points
            if (gripPoints.isEmpty())
                acutPrintf(_T("\nNo grip points specified!"));

            for (i=0; i<gripPoints.length(); i++) {
                acutPrintf(_T("\nGRIP[%d]: %s"), i, ArxDbgUtils::ptToStr(gripPoints[i], str));
                makePointEnt(gripPoints[i], 2);
            }
                // print out osnap modes
            if (osnapModes.isEmpty())
                acutPrintf(_T("\nNo osnap modes specified!"));

            for (i=0; i<osnapModes.length(); i++)
                acutPrintf(_T("\nOSNAP MODE[%d]: %s"), i, ArxDbgUtils::osnapToStr(osnapModes[i], str));

                // print out geomIds
            if (geomIds.isEmpty())
                acutPrintf(_T("\nNo geomIds specified!"));

            for (i=0; i<geomIds.length(); i++)
                acutPrintf(_T("\nGEOM ID[%d]: %s"), i, ArxDbgUtils::intToStr(geomIds[i], str));
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        obj->close();
    }
}

/****************************************************************************
**
**  ArxDbgCmdTests::testGetStretchPoints
**
**  **jma
**
*************************************/

void
ArxDbgCmdTests::testGetStretchPoints()
{
    AcDbEntity* obj;
    AcGePoint3dArray stretchPoints;
    Acad::ErrorStatus es;
    CString str;

    while (1) {
        if ((obj = ArxDbgUtils::selectEntity(nullptr, AcDb::kForRead)) == nullptr)
            return;

        stretchPoints.setLogicalLength(0);    // empty previous results

        es = obj->getStretchPoints(stretchPoints);
        if (es == Acad::eOk) {
            if (stretchPoints.isEmpty())
                acutPrintf(_T("\nNo stretch points specified!"));

                // print out grip points
            for (int i=0; i<stretchPoints.length(); i++) {
                acutPrintf(_T("\nSTRETCH[%d]: %s"), i, ArxDbgUtils::ptToStr(stretchPoints[i], str));
                makePointEnt(stretchPoints[i], 1);
            }
        }
        else
            ArxDbgUtils::rxErrorMsg(es);
    }
}

/****************************************************************************
**
**    ArxDbgCmdTests::printSnapPts
**
**    **jma
**
*************************************/

void
ArxDbgCmdTests::printSnapPts(LPCTSTR typeStr, const AcGePoint3dArray& pts, Acad::ErrorStatus es)
{
    CString str;

    acutPrintf(_T("\nSnap Points for: %s"), typeStr);
    if (es == Acad::eOk) {
        if (pts.isEmpty())
            acutPrintf(_T("\nNo snap points specified!"));

            // print out snap points
        for (int i=0; i<pts.length(); i++) {
            acutPrintf(_T("\nOSNAP[%d]: %s"), i, ArxDbgUtils::ptToStr(pts[i], str));
            makePointEnt(pts[i], 1);
        }
    }
    else
        ArxDbgUtils::rxErrorMsg(es);
}

/****************************************************************************
**
**    ArxDbgCmdTests::testGetOsnapPoints
**
**	**jma
**
*************************************/

void
ArxDbgCmdTests::testGetOsnapPoints()
{
    AcDbEntity* obj;
    AcGePoint3dArray snapPoints;
    AcDbIntArray geomIds;
    Acad::ErrorStatus es;

    ArxDbgUiPrPoint prPickPt(_T("Point picked"), nullptr);
    AcGePoint3d tmpPt;

    while (1) {
        if ((obj = ArxDbgUtils::selectEntity(nullptr, AcDb::kForRead)) == nullptr)
            return;

        if (prPickPt.go() != ArxDbgUiPrBase::kOk) {
            obj->close();
            return;
        }
        tmpPt = ArxDbgUtils::ucsToWcs(prPickPt.value());

        es = obj->getOsnapPoints(AcDb::kOsModeNear, 0, tmpPt,
                        tmpPt, AcGeMatrix3d::kIdentity, snapPoints, geomIds);
        printSnapPts(_T("END"), snapPoints, es);
        snapPoints.setLogicalLength(0);    // empty previous results
        geomIds.setLogicalLength(0);

        es = obj->getOsnapPoints(AcDb::kOsModeCen, 0, tmpPt,
                    tmpPt, AcGeMatrix3d::kIdentity, snapPoints, geomIds);
        printSnapPts(_T("CEN"), snapPoints, es);
        snapPoints.setLogicalLength(0);    // empty previous results
        geomIds.setLogicalLength(0);

        obj->close();
    }
}

/****************************************************************************
**
**	ArxDbgCmdTests::testExtDictAdd
**
**	**jma
**
*************************************/

void
ArxDbgCmdTests::testExtDictAdd()
{
	AcDbObjectId objId;
    AcDbObject* obj;
    CString str;

	if (!ArxDbgUtils::selectEntityOrObject(objId))
		return;

    ArxDbgUiPrString prKey(_T("Key to store under"), false);
    ArxDbgUiPrString prTestStr(_T("Test string to store"), false);

    if ((prKey.go() != ArxDbgUiPrBase::kOk) ||
        (prTestStr.go() != ArxDbgUiPrBase::kOk))
        return;

	Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForWrite);
	if (es != Acad::eOk) {
		ArxDbgUtils::rxErrorMsg(es);
		return;
	}

	AcDbDictionary* extDict = ArxDbgUtils::openExtDictForWrite(obj, true);
    if (extDict) {
        if (extDict->has(prKey.value())) {
            acutPrintf(_T("\n\"%s\" is already in the extension dictionary."),
                                static_cast<LPCTSTR>(prKey.value()));
        }
        else {
                // make an Xrecord to stick into the dictionary
            AcDbXrecord* xRec = new AcDbXrecord;
            resbuf* rb = acutBuildList(2, static_cast<LPCTSTR>(prTestStr.value()), 0);
            xRec->setFromRbChain(*rb);

            AcDbObjectId newObjId;
            es = extDict->setAt(static_cast<LPCTSTR>(prKey.value()), xRec, newObjId);
            if (es != Acad::eOk) {
                ArxDbgUtils::rxErrorMsg(es);
                delete xRec;
            }
            else {
                acutPrintf(_T("\nAdded it to the dictionary!"));
                xRec->close();
            }
        }
        extDict->close();
    }
    else
        acutPrintf(_T("\nERROR: couldn't get extension dictionary"));

	obj->close();
}

/****************************************************************************
**
**	ArxDbgCmdTests::testExtDictRemove
**        remove an extension dictionary on an entity.
**
**    **jma
**
*************************************/

void
ArxDbgCmdTests::testExtDictRemove()
{
    AcDbObject* obj;
	AcDbObjectId objId;

	if (!ArxDbgUtils::selectEntityOrObject(objId))
		return;

	Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForWrite);
	if (es != Acad::eOk) {
		ArxDbgUtils::rxErrorMsg(es);
		return;
	}

	AcDbObjectId extDictId = obj->extensionDictionary();
    if (extDictId == AcDbObjectId::kNull) {
        acutPrintf(_T("\nThere was no extension dictionary attaced to this object!"));
    }
    else {
        AcDbDictionary* extDict;
        Acad::ErrorStatus es;
        es = acdbOpenObject(extDict, extDictId, AcDb::kForRead);
        if (es == Acad::eOk) {
            int numEntries = extDict->numEntries();
            extDict->close();
            if (numEntries != 0)
                acutPrintf(_T("\nExtension dict not empty, cannot be removed."));
            else {
                es = obj->releaseExtensionDictionary();
                if (es == Acad::eOk)
                    acutPrintf(_T("\nRemoved extension dictionary!"));
                else
                    ArxDbgUtils::rxErrorMsg(es);
            }
        }
        else
            ArxDbgUtils::rxErrorMsg(es);
    }

    obj->close();
}

/****************************************************************************
**
**	ArxDbgCmdTests::testTransDatabaseClones
**
**	**jma
**
*************************************/

void
ArxDbgCmdTests::testTransDatabaseClones()
{
    ArxDbgUiTdmTransDbClones dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

	// used for following Xdata test
#define XDT_AGE                 20000
#define XDT_RANK                20001
#define XDT_BIRTHDAY            20002
#define XDT_FAVORITE_ANIMALS    20003
#define XDT_MISC                20004

/****************************************************************************
**
**	ArxDbgCmdTests::testGetXdata
**
**    **jma
**
*************************************/

void
ArxDbgCmdTests::testGetXdata(ArxDbgAppXdata& xdata1, ArxDbgAppXdata& xdata2)
{
    CString str;
    int intVal;
    double realVal;

        // get the birthday field
    if (xdata1.getString(XDT_BIRTHDAY, str))
        acutPrintf(_T("\nBirthday is: %s"), str);
    else
        ArxDbgUtils::stopAlertBox(_T("Couldn't get birthday"));

        // try getting a bogus value
    if (xdata1.getInteger(99999, intVal))
        acutPrintf(_T("\nBOGUS VAL: %d"), intVal);
    else
        acutPrintf(_T("\nCouldn't get bogus tag 99999"));

        // get uniform Animal list, and walk it
    ArxDbgXdataList list1;
    xdata1.getList(XDT_FAVORITE_ANIMALS, list1);

    ArxDbgXdataListIterator iter1(list1);
    while (iter1.getString(str))
        acutPrintf(_T("\nANIMAL: %s"), str);

        // get non-uniform list and retrieve values
        // expecting string/int/real in order
    ArxDbgXdataList list2;
    xdata2.getList(XDT_MISC, list2);

    ArxDbgXdataListIterator iter2(list2);
    if ((iter2.getString(str)) &&
        (iter2.getInteger(intVal)) &&
        (iter2.getReal(realVal)))
        acutPrintf(_T("\nVALUES: %s, %d, %lf"), str, intVal, realVal);
    else
        acutPrintf(_T("\nERROR: values not in expected format!"));
}

/****************************************************************************
**
**	ArxDbgCmdTests::testXdata
**
**	**jma
**
*************************************/

void
ArxDbgCmdTests::testXdata()
{
	AcDbObjectId objId;
	AcDbObject* obj;

	if (!ArxDbgUtils::selectEntityOrObject(objId))
		return;

	Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForWrite);
	if (es != Acad::eOk) {
		ArxDbgUtils::rxErrorMsg(es);
		return;
	}

        // add xdata for first app
    ArxDbgUtils::infoAlertBox(_T("add Xdata for Son #1"));
    ArxDbgAppXdata connor(_T("CONNOR"), obj->database());
    connor.setDistance(XDT_AGE, 6.0);
    connor.setInteger(XDT_RANK, 1);
    connor.setString(XDT_BIRTHDAY, _T("January 14, 1993"));

        // add in a uniform list
    ArxDbgXdataList list1;
    list1.appendString(_T("Tiger"));
    list1.appendString(_T("Lion"));
    list1.appendString(_T("Wolf"));
    connor.setList(XDT_FAVORITE_ANIMALS, list1);

    connor.setXdata(obj);

    ArxDbgUiDlgXdata dbox1(acedGetAcadDwgView(), obj);
    dbox1.DoModal();

        // add xdata for second app
    ArxDbgUtils::infoAlertBox(_T("add Xdata for Son #2"));
    ArxDbgAppXdata mason(_T("MASON"), obj->database());
    mason.setDistance(XDT_AGE, 4.2);
    mason.setInteger(XDT_RANK, 2);
    mason.setString(XDT_BIRTHDAY, _T("November 22, 1994"));
        // add in a non-uniform list
    ArxDbgXdataList list2;
    list2.appendString(_T("String 1"));
    list2.appendInteger(44);
    list2.appendReal(33.33);
    mason.setList(XDT_MISC, list2);

    mason.setXdata(obj);

    ArxDbgUiDlgXdata dbox2(acedGetAcadDwgView(), obj);
    dbox2.DoModal();

        // try retrieving some values
    ArxDbgUtils::infoAlertBox(_T("Retrieve Xdata values"));
    connor.getXdata(obj);        // no real reason to get again, but what the hell
    mason.getXdata(obj);         // no real reason to get again, but what the hell
    testGetXdata(connor, mason);

        // try editing some values
    ArxDbgUtils::infoAlertBox(_T("Remove Birthday and change age."));
    connor.getXdata(obj);        // no real reason to get again, but what the hell
    connor.remove(XDT_BIRTHDAY);
    connor.setDistance(XDT_AGE, 30.11);    // change to my age

    connor.setXdata(obj);

    ArxDbgUiDlgXdata dbox3(acedGetAcadDwgView(), obj);
    dbox3.DoModal();

    obj->close();
}

/****************************************************************************
**
**	ArxDbgCmdTests::testColor
**
**	**jma
**
*************************************/

void
ArxDbgCmdTests::testColor()
{
    ArxDbgUiDlgColor dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxDbgCmdTests::testCurve
**
**  **jma
**
*************************************/

void
ArxDbgCmdTests::testCurve()
{
    ArxDbgUiDlgTestCurve dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

/****************************************************************************
**
**	ArxDbgCmdTests::testPurge
**
**	**jma
**
*************************************/

void
ArxDbgCmdTests::testPurge()
{
    AcDbObjectIdArray objIds;
    AcDbObjectId objId;

    acutPrintf(_T("\nSelect items to purge: "));

    while (ArxDbgUtils::getEntityOrObject(objId)) {
        if (objIds.contains(objId) == Adesk::kFalse)
            objIds.append(objId);
    }

    if (objIds.isEmpty()) {
        acutPrintf(_T("\nNothing selected!"));
        return;
    }

    AcDbObjectIdArray purgableIds(objIds);
    Acad::ErrorStatus es = acdbHostApplicationServices()->workingDatabase()->purge(purgableIds);
    if (es != Acad::eOk) {
        acutPrintf(_T("\nPurge operation failed: %s"), ArxDbgUtils::rxErrorStr(es));
        return;
    }

    CString str;
    AcDbObject* obj;
    for (AcDbObjectId id : objIds) {
        es = acdbOpenObject(obj, id, AcDb::kForRead, Adesk::kTrue);
        if (es == Acad::eOk) {
            ASSERT(obj->database() == acdbHostApplicationServices()->workingDatabase());    // made an assumption above that user stayed in same database

            acutPrintf(_T("\n<CLASS: %-20s HANDLE: %-4s>"), ArxDbgUtils::objToClassStr(obj),
                        ArxDbgUtils::objToHandleStr(obj, str));
            if (purgableIds.contains(id))
                acutPrintf(_T("   (Purgable)"));
            else
                acutPrintf(_T("   (UnPurgable)"));

            obj->close();
        }
        else
            ArxDbgUtils::rxErrorMsg(es);
    }
}

/****************************************************************************
**
**	ArxDbgCmdTests::testCountReferences
**
**	**jma
**
*************************************/

void
ArxDbgCmdTests::testCountReferences()
{
    AcDbObjectIdArray objIds;
    AcDbObjectId objId;

    acutPrintf(_T("\nSelect items to count references: "));

    while (ArxDbgUtils::getEntityOrObject(objId)) {
        if (objIds.contains(objId) == Adesk::kFalse)
            objIds.append(objId);
    }

    int len = objIds.length();
    if (len == 0) {
        acutPrintf(_T("\nNothing selected!"));
        return;
    }

    Adesk::UInt32* countArray = new Adesk::UInt32[len];
    int i;
    for (i=0; i<len; i++)
        countArray[i] = 0;  // init count values;

    Acad::ErrorStatus es = acdbHostApplicationServices()->workingDatabase()->countHardReferences(objIds, countArray);
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorMsg(es);
        delete [] countArray;
        return;
    }

    CString str;
    AcDbObject* obj;
    len = objIds.length();
    for (i=0; i<len; i++) {
        es = acdbOpenAcDbObject(obj, objIds[i], AcDb::kForRead);
        if (es == Acad::eOk) {
            ASSERT(obj->database() == acdbHostApplicationServices()->workingDatabase());    // made an assumption above that user stayed in same database

            acutPrintf(_T("\n<CLASS: %-20s HANDLE: %-4s>"), ArxDbgUtils::objToClassStr(obj),
                        ArxDbgUtils::objToHandleStr(obj, str));

            acutPrintf(_T("  (Count = %d)"), countArray[i]);
            obj->close();
        }
        else {
            ArxDbgUtils::rxErrorMsg(es);
        }
    }

    delete [] countArray;
}

/****************************************************************************
**
**	ArxDbgCmdTests::testWblockCloneObjects
**
**	**jma
**
*************************************/

void
ArxDbgCmdTests::testWblockCloneObjects()
{
	ArxDbgSelSet ss;
	if (ss.userSelect() != ArxDbgSelSet::kSelected)
		return;

    acutPrintf(_T("\nDuplicate Record Options:"));
	acutPrintf(_T("\n   0 = kDrcNotApplicable"));
	acutPrintf(_T("\n   1 = kDrcIgnore"));
	acutPrintf(_T("\n   2 = kDrcReplace"));
	acutPrintf(_T("\n   3 = kDrcXrefMangleName"));
	acutPrintf(_T("\n   4 = kDrcMangleName"));
	acutPrintf(_T("\n   5 = kDrcUnmangleName"));

	ArxDbgUiPrIntDef prDrc(_T("Duplicate record type"), nullptr, ArxDbgUiPrInt::kRange, AcDb::kDrcIgnore);
    prDrc.setRange(AcDb::kDrcNotApplicable, AcDb::kDrcUnmangleName);
	if (prDrc.go() != ArxDbgUiPrBase::kOk)
		return;

	AcDbObjectIdArray cloneSet;
	ss.asArray(cloneSet);

	Acad::ErrorStatus es;
	AcDbObjectId destBlkId;
	AcApDocumentIterator* iter = acDocManager->newAcApDocumentIterator();
	AcApDocument* curDoc = acDocManager->curDocument();
	AcDbDatabase* fromDb = curDoc->database();
    if (iter) {
        AcApDocument* tmpDoc;
        for (; !iter->done(); iter->step()) {
            tmpDoc = iter->document();
            if (tmpDoc) {
				if (tmpDoc != curDoc) {
					es = acDocManager->setCurDocument(tmpDoc, AcAp::kWrite);
					if (es == Acad::eOk) {
						AcDbIdMapping idMap;
						idMap.setDestDb(tmpDoc->database());
						destBlkId = tmpDoc->database()->currentSpaceId();
						es = fromDb->wblockCloneObjects(cloneSet, destBlkId, idMap,
									static_cast<AcDb::DuplicateRecordCloning>(prDrc.value()));
						acDocManager->unlockDocument(tmpDoc); // Unlock the doc when done...
						ArxDbgUtils::rxErrorMsg(es);
					}
					else {
						ArxDbgUtils::rxErrorMsg(es);
					}
			    }
            }
            else {
                ASSERT(0);
            }
        }
        delete iter;
    }
    acDocManager->setCurDocument(curDoc);
}

/****************************************************************************
**
**    ArxDbgCmdTests::testWorldDraw
**
**    **jma
**
*************************************/

void
ArxDbgCmdTests::testWorldDraw()
{
    ArxDbgGiWorldDraw wd;
    ArxDbgUiDlgWorldDraw dbox(wd, acedGetAcadDwgView());
    if (dbox.DoModal() != IDOK)
        return;

    AcDbEntity* ent;
    Adesk::Boolean didWorldDraw;

    while (1) {
        ent = ArxDbgUtils::selectEntity(_T("\nSelect entity to test worldDraw(): "), AcDb::kForRead);
        if (ent) {
                // set up initial properties to draw with
            wd.setInitialProps(ent);

            didWorldDraw = ent->worldDraw(&wd);
            if (!didWorldDraw)
                acutPrintf(_T("\nDo viewportDraw()..."));
            ent->close();
            acutPrintf(_T("\n\n********************************************************\n"));
        }
        else
            break;
    }
}

/****************************************************************************
**
**    ArxDbgCmdTests::testDwgFiler
**
**    **jma
**
*************************************/

void
ArxDbgCmdTests::testDwgFiler()
{
    ArxDbgUiDlgFilerTest dbox(acedGetAcadDwgView());
    if (dbox.DoModal() != IDOK)
        return;

    AcDbObjectId objId;
    AcDbObject* obj;
    Acad::ErrorStatus es;

    AcDb::FilerType fType = dbox.indexToFilerType(dbox.m_puFilerTypeIndex);

        // skirt around bug in R14... and now Tahoe
    if (fType == AcDb::kFileFiler) {
        ArxDbgUtils::alertBox(_T("ERROR: FileFiler currently crashes AutoCAD due to blind casting... Setting to CopyFiler instead."));
        fType = AcDb::kCopyFiler;
    }

    CString str;
    ArxDbgDwgFiler dwgFiler;
    dwgFiler.setFilerType(fType);

    while (ArxDbgUtils::selectEntityOrObject(objId)) {
        acutPrintf(_T("\n\n*******************************************************\n"));

        if (acdbOpenAcDbObject(obj, objId, AcDb::kForRead) == Acad::eOk) {
            acutPrintf(_T("\nFiler for:  %s\n"), ArxDbgUtils::objToClassAndHandleStr(obj, str));

            es = obj->dwgOut(&dwgFiler);
            if (es != Acad::eOk)
                ArxDbgUtils::rxErrorAlert(es);
    
            obj->close();
        }
        dwgFiler.resetFilerStatus();

        acutPrintf(_T("\n\n*******************************************************\n"));
    }
}

/****************************************************************************
**
**  ArxDbgCmdTests::testSelSet
**
**  **jma
**
*************************************/

void
ArxDbgCmdTests::testSelSet()
{
    ArxDbgUiDlgSelSet dbox(acedGetAcadDwgView());
    dbox.DoModal();
}
