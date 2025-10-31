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
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <string.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <dbgroup.h>
#include <dbapserv.h>
#include "tchar.h"



AcDbObjectId createLine();
AcDbObjectId createCircle();
void createNewLayer();
void createGroup();
Acad::ErrorStatus changeColor(AcDbObjectId, Adesk::UInt16);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
AcDbObjectId
createLine()
{
    AcGePoint3d startPt(4.0, 2.0, 0.0);
    AcGePoint3d endPt(10.0, 7.0, 0.0);
    AcDbLine *pLine = new AcDbLine(startPt, endPt);

    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord *pBlockTableRecord;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
        AcDb::kForWrite);
    pBlockTable->close();

    AcDbObjectId lineId;
    pBlockTableRecord->appendAcDbEntity(lineId, pLine);

    pBlockTableRecord->close();
    pLine->close();

    return lineId;
}

AcDbObjectId
createCircle()
{
    AcGePoint3d center(9.0, 3.0, 0.0);
    AcGeVector3d normal(0.0, 0.0, 1.0);
    AcDbCircle *pCirc = new AcDbCircle(center, normal, 2.0);

    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord *pBlockTableRecord;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
        AcDb::kForWrite);
    pBlockTable->close();

    AcDbObjectId circleId;
    pBlockTableRecord->appendAcDbEntity(circleId, pCirc);

    pBlockTableRecord->close();
    pCirc->close();

    return circleId;
}

void
createNewLayer()
{
    AcDbLayerTable *pLayerTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pLayerTable, AcDb::kForWrite);

    AcDbLayerTableRecord *pLayerTableRecord =
        new AcDbLayerTableRecord;
    pLayerTableRecord->setName(_T("ASDK_MYLAYER"));

	// Defaults are used for other properties of 
	// the layer if they are not otherwise specified.

	pLayerTable->add(pLayerTableRecord);
    pLayerTable->close();
    pLayerTableRecord->close();
}

void
createGroup(AcDbObjectIdArray& objIds, TCHAR* pGroupName)
{
    AcDbGroup *pGroup = new AcDbGroup(pGroupName);
	
	// Put the group in the group dictionary which resides
    // in the named object dictionary.
    //
    AcDbDictionary *pGroupDict;
    acdbHostApplicationServices()->workingDatabase()
        ->getGroupDictionary(pGroupDict, AcDb::kForWrite);

    AcDbObjectId pGroupId;
    pGroupDict->setAt(pGroupName, pGroup, pGroupId);
    pGroupDict->close();

    // Now that the group has been added, it has an ObjectID.
	// This is important since the group will become a persistent
	// reactor for the added entities...
    for (int i = 0; i < objIds.length(); i++) {
        pGroup->append(objIds[i]);
    }

	pGroup->close();
}

Acad::ErrorStatus
changeColor(AcDbObjectId entId, Adesk::UInt16 newColor)
{
    AcDbEntity *pEntity;
    acdbOpenObject(pEntity, entId,
        AcDb::kForWrite);

    pEntity->setColorIndex(newColor);
    pEntity->close();

    return Acad::eOk;
}
// END CODE APPEARING IN SDK DOCUMENT.

void
runIt()
{
    createNewLayer();

    AcDbObjectIdArray idArr;

    // create a line and circle and add them to the objectId
    // array
    //
    idArr.append(createLine());
    idArr.append(createCircle());

    // change circle color to red
    //
    changeColor(idArr.last(), 1);

    // put the line and circle in a group named
    // "ASDK_TEST_GROUP"
    //
    createGroup(idArr, _T("ASDK_TEST_GROUP"));
}

void initApp()
{
    acedRegCmds->addCommand(_T("ASDK_MAKE_ENTS"),
                            _T("ASDK_MKENTS"),
                            _T("MKENTS"),
                            ACRX_CMD_MODAL,
                            runIt);
}

void unloadApp()
{
        acedRegCmds->removeGroup(_T("ASDK_MAKE_ENTS"));
}

extern "C" AcRx::AppRetCode
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
