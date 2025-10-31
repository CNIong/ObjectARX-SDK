//   partopen.cpp
//   Copyright (C) 1998 by Autodesk, Inc.
//
//     Permission to use, copy, modify, and distribute this software
//     for any purpose is restricted by the VIP Subscription program
//     license agreement.  This application was developed exclusively
//     for distribution by the VIP subscription program and may not
//     be posted pubicly, modified, copied, or distributed by any other
//     methods. 
//
//     AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.  
//     AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF 
//     MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
//     DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE 
//     UNINTERRUPTED OR ERROR FREE.
//
//     Use, duplication, or disclosure by the U.S. Government is subject to 
//     restrictions set forth in FAR 52.227-19 (Commercial Computer 
//     Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) 
//     (Rights in Technical Data and Computer Software), as applicable. 
//
//   Author:  Joshua Harris
//   Created: August, 1998
//

#include "adesk.h"
#include "rxdefs.h"
#include "adslib.h"
#include "adscodes.h"
#include "ads.h"
#include "rxregsvc.h"   // acrxProductKey()
#include "aced.h"       // acedRegCmds
#include "dbsymtb.h"
#include "dbapserv.h"   // acdbHostApplicationServices
#include "gept2dar.h"   // AcGePoint2dArray
#include "acestext.h"   // acadErrorStatusText
#include "dblyfilt.h"   // AcDbLayerFilter
#include "dbspfilt.h"   // AcDbSpatialFilter
#include "dbents.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" HINSTANCE _hdllInstance;

void partialOpenCommand();

#define PARTOPEN_COMMANDS   /*MSG0*/"PARTOPEN_COMMANDS"

// ... Rx Module Interface Functions
extern "C" 
{ 	__declspec(dllexport)	AcRx::AppRetCode  acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);	}

//////////////////////////////////////////////////////////////

// EditorReactor class
//     This class responds to notification about partial open
//     attempts.
//
class EditorReactor : public AcEditorReactor
{
public:
    EditorReactor();
    virtual void partialOpenNotice(AcDbDatabase* pDb);
    void setVetoPartialOpen(Adesk::Boolean bMode) { mVetoPartialOpen = bMode; }
    Adesk::Boolean getVetoPartialOpen() const { return mVetoPartialOpen; }
private:
    Adesk::Boolean mVetoPartialOpen;
} editorReactor;

EditorReactor::EditorReactor()
 :  mVetoPartialOpen(Adesk::kFalse)
{
}

void
EditorReactor::partialOpenNotice(AcDbDatabase* pDb)
{
    ads_printf("Received partial open notice!\n");
    if (mVetoPartialOpen) {
        pDb->disablePartialOpen();
        ads_printf("Vetoing partial open!\n");
    }
}

//////////////////////////////////////////////////////////////

AcDbDatabase*
selectDatabase()
{
    AcDbDatabase* pDb = NULL;
    struct resbuf* result;
    result = ads_newrb(RTSTR);
    result->resval.rstring = NULL;

    if (ads_getfiled("Partial Open", NULL, "dwg", 32, result) == RTNORM) {
        pDb = ::new AcDbDatabase(Adesk::kFalse);
        if (pDb->readDwgFile(result->resval.rstring) != Acad::eOk)
            ::delete pDb;
    }
    ads_relrb(result);
    return pDb;
}

int
selectLayers(AcDbDatabase* pDb,
             AcDbLayerFilter& layerFilter)
{
    char string[133];
    const char* pName;
    AcDbObjectId id;
    AcDbObjectIdArray layerId;
    Acad::ErrorStatus es;
    int nLayerCount = 0;

    if (pDb == NULL)
        return 0;
    
    // Get a list of all of the layers
    //
    AcDbLayerTable* pLayerTable;
    if ((es = pDb->getLayerTable(pLayerTable, AcDb::kForRead)) != Acad::eOk)
        return 0;

    AcDbLayerTableIterator* pLayerIterator;
    if ((es = pLayerTable->newIterator(pLayerIterator, Adesk::kTrue, Adesk::kTrue)) != Acad::eOk)
        return 0;

    while (!pLayerIterator->done()) {
        if ((es = pLayerIterator->getRecordId(id)) == Acad::eOk) {
            layerId.append(id);
        }
        pLayerIterator->step();
    }
    delete pLayerIterator;

    int nLayers = layerId.length();
    if (nLayers) {
        AcDbLayerTableRecord* pLayer;
        while (1) {
            string[0] = 0;
            if (ads_getstring(1, "Enter layer (* for all) or [?]: ", string) != RTNORM)
                return Acad::eInvalidInput;
            if (!string[0])
                break;
            if (string[0] == '?') {
                // List all layers
                //
                ads_printf("Layers:\n");
            } else if (string[0] == '*') {
                return 0;
            }
            int n;
            Adesk::Boolean bFound = Adesk::kFalse;
            for (n = 0; n < nLayers; n++) {
                id = layerId.at(n);
                if (acdbOpenAcDbObject((AcDbObject*&)pLayer, id, AcDb::kForRead) == Acad::eOk) {
                    if (pLayer->getName(pName) == Acad::eOk) {
                        if (string[0] == '?') {
                            ads_printf("  %s\n", pName);
                        } else {
                            for (int i = 0; string[i]; i++) {
                                if (toupper(pName[i]) != toupper(string[i]))
                                    break;
                            }
                            if (!string[i] && !pName[i]) {
                                bFound = Adesk::kTrue;
                                layerFilter.add(pName);
                                nLayerCount++;
                                ads_printf("Layer %s added to filter.\n", pName);
                            }
                        }
                    }
                    pLayer->close();
                }
            }
            if (string[0] != '?' && bFound == Adesk::kFalse)
                ads_printf("Layer not found.\n");
        }
    }

    return 1;
}

void
copyEntities(AcDbDatabase* pFromDb, AcDbDatabase* pToDb)
{
    if (pFromDb == NULL || pToDb == NULL)
        return;

    // Open the model space of the "from" database for reading...
    //
    AcDbBlockTable* pFromTable;
    if (pFromDb->getBlockTable(pFromTable, AcDb::kForRead) == Acad::eOk) {
        AcDbBlockTableRecord* pFromModel;
        if (pFromTable->getAt(ACDB_MODEL_SPACE, pFromModel, AcDb::kForRead)
            == Acad::eOk)
        {
            // Open the model space of the "to" database for writing...
            //
            AcDbBlockTable* pToTable;
            if (pToDb->getBlockTable(pToTable, AcDb::kForRead) == Acad::eOk) {
                AcDbBlockTableRecord* pToModel;
                if (pToTable->getAt(ACDB_MODEL_SPACE, pToModel, AcDb::kForWrite)
                    == Acad::eOk)
                {
                    AcDbBlockTableRecordIterator* pIter;
                    if (pFromModel->newIterator(pIter) == Acad::eOk) {
                        AcDbEntity* pEnt;
                        AcDbEntity* pClone;
                        AcDbObjectId newId;
                        for (pIter->start(); !pIter->done(); pIter->step()) {
                            if (pIter->getEntity(pEnt, AcDb::kForRead)
                                == Acad::eOk)
                            {
                                pClone = NULL;
                                if (pEnt->isA() == AcDbLine::desc()) {
                                    AcDbLine* pLine = (AcDbLine*)pEnt;
                                    pClone = new AcDbLine(pLine->startPoint(),
                                        pLine->endPoint());
                                }
                                if (pClone != NULL) {
                                    pClone->setDatabaseDefaults(pToDb);
                                    pToModel->appendAcDbEntity(newId, pClone);
                                    pClone->close();
                                }
                            }
                        }
                        delete pIter;
                    }
                    pToModel->close();
                }
                pToTable->close();
            }
            pFromModel->close();
        }
        pFromTable->close();
    }
}

void
filterDatabase(AcDbDatabase* pDb)
{
    if (pDb == NULL)
        return;
    
    // Get window corners
    //
    ads_point pt1, pt2;
    int result = ads_getpoint(NULL, "Select window: ", pt1);
    if (result == RTERROR || result == RTCAN)
        return;

    result = ads_getcorner(pt1, NULL, pt2);
    if (result == RTERROR || result == RTCAN)
        return;

    // Get view direction
    //
    AcGeVector3d normal;
    struct resbuf rb;
    ads_getvar("VIEWDIR", &rb);
    normal[0] = rb.resval.rpoint[0];
    normal[1] = rb.resval.rpoint[1];
    normal[2] = rb.resval.rpoint[2];
    normal.normalize();

    // Convert points from UCS to ECS
    //
    struct resbuf rbFrom, rbTo;
    rbFrom.restype = RTSHORT;
    rbFrom.resval.rint = 1;     // UCS
    rbTo.restype = RT3DPOINT;
    rbTo.resval.rpoint[0] = normal[0];
    rbTo.resval.rpoint[1] = normal[1];
    rbTo.resval.rpoint[2] = normal[2];
    ads_trans(pt1, &rbFrom, &rbTo, FALSE, pt1);
    ads_trans(pt2, &rbFrom, &rbTo, FALSE, pt2);

    // Create the spatial filter
    //
    AcGePoint2dArray array;
    array.append(AcGePoint2d(pt1[0], pt1[1]));
    array.append(AcGePoint2d(pt2[0], pt2[1]));
    AcDbSpatialFilter filter;
    filter.setDefinition(
        array,
        normal,
        pt1[Z],
        ACDB_INFINITE_XCLIP_DEPTH,
        -ACDB_INFINITE_XCLIP_DEPTH,
        Adesk::kTrue);

    AcDbLayerFilter layerFilter;
    AcDbLayerFilter* pLayerFilter = NULL;
    if (selectLayers(pDb, layerFilter) > 0)
        pLayerFilter = &layerFilter;


    Adesk::Boolean bPartialLoad = pDb->isPartiallyOpened();
    Acad::ErrorStatus es =
        pDb->applyPartialOpenFilters(&filter, pLayerFilter);
    if (es != Acad::eOk) {
        ads_printf("Error occurred in call to applyPartialOpenFilters()\n");
        ads_printf("Error code = %s\n", acadErrorStatusText(es));
    }

    // If this is a partial open, be sure to finish opening the drawing
    //
    if (!bPartialLoad)
        pDb->closeInput();
}

// PARTIALIMPORTCOMMAND:
//    Imports LINE entities from an external file into the current drawing
//    using partial open to filter the
//    database based upon the layers and area selected
void
partialImportCommand()
{
    AcDbDatabase* pDb = selectDatabase();
    if (pDb != NULL) {
        filterDatabase(pDb);
        // Now do something with the database to illustrate the
        // filtered model space...
        // for example, copy all of the lines and circles from the
        // partially opened database to the current active database.
        //
        AcDbDatabase* pActiveDb =
            acdbHostApplicationServices()->workingDatabase();
        if (pActiveDb != NULL)
            copyEntities(pDb, pActiveDb);
        ::delete pDb;
    }
}

// PARTIALLOADCOMMAND:
//    Simplified version of the PARTIALOAD command.  Only works if the
//    active drawing is partially opened.
//
void
partialLoadCommand()
{
    // Just call filterDatabase on the active database
    //
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if (pDb != NULL && pDb->isPartiallyOpened())
        filterDatabase(pDb);
}

// ISPARTIALOPENCOMMAND:
//     Displays whether or not the active drawing is partially opened.
//
void
isPartialOpenCommand()
{
    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if (pDb != NULL) {
        if (pDb->isPartiallyOpened())
            ads_printf("Drawing is partially opened.\n");
        else
            ads_printf("Drawing is fully opened.\n");
    }
}

// TOGGLEVETOCOMMAND:
//     Toggle the state of the editor reactor to between vetoing and
//     no vetoing partial open attempts.
//
void
toggleVetoCommand()
{
    Adesk::Boolean bState = (editorReactor.getVetoPartialOpen() == Adesk::kTrue)
        ? Adesk::kFalse : Adesk::kTrue;
    editorReactor.setVetoPartialOpen(bState);
    ads_printf("Partial open attempts %s vetoed.\n", (bState == Adesk::kTrue)
        ? "ARE" : "ARE NOT");
}


void
loadModule()
{
    // Add command to the ARX command stack.
	acedRegCmds->addCommand(PARTOPEN_COMMANDS,
							"PIMPORT",
							"PIMPORT",
							ACRX_CMD_MODAL,
							&partialImportCommand);
	acedRegCmds->addCommand(PARTOPEN_COMMANDS,
							"ISPOPEN",
							"ISPOPEN",
							ACRX_CMD_MODAL,
							&isPartialOpenCommand);
	acedRegCmds->addCommand(PARTOPEN_COMMANDS,
							"PLOAD",
							"PLOAD",
							ACRX_CMD_MODAL,
							&partialLoadCommand);
	acedRegCmds->addCommand(PARTOPEN_COMMANDS,
							"PVETO",
							"PVETO",
							ACRX_CMD_MODAL,
							&toggleVetoCommand);
    acedEditor->addReactor(&editorReactor);
}

void
unloadModule()
{
	// Removes the command group with the name cmdGroupName from the CommandStack and deletes 
	// the command group dictionary object and all the AcEdCommand objects stored within it.
	acedRegCmds->removeGroup(PARTOPEN_COMMANDS);
    acedEditor->removeReactor(&editorReactor);
}

AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
    switch(msg) {
	    case AcRx::kInitAppMsg:
	        acrxDynamicLinker->unlockApplication(pkt);
			acrxDynamicLinker->registerAppMDIAware(pkt);
			loadModule();
			break;
	    case AcRx::kUnloadAppMsg:
	        unloadModule();
			break;
	    case AcRx::kLoadDwgMsg:
            break;
	    case AcRx::kUnloadDwgMsg:
            break;
	    case AcRx::kInvkSubrMsg:
	    default:
			break;
    }
    return AcRx::kRetOK;
}
