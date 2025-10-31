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
#include <string.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <dbgroup.h>
#include <dbapserv.h>

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
    pLayerTableRecord->setName("ASDK_MYLAYER");

	// Defaults are used for other properties of 
	// the layer if they are not otherwise specified.

	pLayerTable->add(pLayerTableRecord);
    pLayerTable->close();
    pLayerTableRecord->close();
}

void
createGroup(AcDbObjectIdArray& objIds, char* pGroupName)
{
    AcDbGroup *pGroup = new AcDbGroup(pGroupName);

    for (int i = 0; i < objIds.length(); i++) {
        pGroup->append(objIds[i]);
    }

    // Put the group in the group dictionary which resides
    // in the named object dictionary.
    //
    AcDbDictionary *pGroupDict;
    acdbHostApplicationServices()->workingDatabase()
        ->getGroupDictionary(pGroupDict, AcDb::kForWrite);

    AcDbObjectId pGroupId;
    pGroupDict->setAt(pGroupName, pGroup, pGroupId);
    pGroupDict->close();
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
    createGroup(idArr, "ASDK_TEST_GROUP");
}

void initApp()
{
    acedRegCmds->addCommand("ASDK_MAKE_ENTS",
                            "ASDK_MKENTS",
                            "MKENTS",
                            ACRX_CMD_MODAL,
                            runIt);
}

void unloadApp()
{
        acedRegCmds->removeGroup("ASDK_MAKE_ENTS");
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
