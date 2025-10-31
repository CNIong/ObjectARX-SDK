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
#include <adslib.h>
#include <acestext.h>
#include <dbapserv.h>
#include "tchar.h"



// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Acad::ErrorStatus
createCircle(AcDbObjectId& circleId)
{
    circleId = AcDbObjectId::kNull;

    AcGePoint3d center(9.0, 3.0, 0.0);
    AcGeVector3d normal(0.0, 0.0, 1.0);
    AcDbCircle *pCirc = new AcDbCircle(center, normal, 2.0);

    if (pCirc == NULL)
        return Acad::eOutOfMemory;

    AcDbBlockTable *pBlockTable;
    Acad::ErrorStatus es = acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);
    if (es != Acad::eOk) {
        delete pCirc;
        return es;
    }

    AcDbBlockTableRecord *pBlockTableRecord;
    es = pBlockTable->getAt(ACDB_MODEL_SPACE,
        pBlockTableRecord, AcDb::kForWrite);
    if (es != Acad::eOk) {
        Acad::ErrorStatus es2 = pBlockTable->close();
        if (es2 != Acad::eOk) {
            acrx_abort(_T("\nApp X failed to close Block")
                _T(" Table. Error: %s"),
                acadErrorStatusText(es2));
        }
        delete pCirc;
        return es;
    }

    es = pBlockTable->close();
    if (es != Acad::eOk) {
        acrx_abort(_T("\nApp X failed to close Block Table.")
            _T(" Error: %s"), acadErrorStatusText(es));
    }

    es = pBlockTableRecord->appendAcDbEntity(circleId,
        pCirc);
    if (es != Acad::eOk) {
        Acad::ErrorStatus es2 = pBlockTableRecord->close();
        if (es2 != Acad::eOk) {
            acrx_abort(_T("\nApp X failed to close")
                _T(" Model Space Block Record. Error: %s"),
                acadErrorStatusText(es2));
        }
        delete pCirc;
        return es;
    }

    es = pBlockTableRecord->close();
    if (es != Acad::eOk) {
        acrx_abort(_T("\nApp X failed to close")
            _T(" Model Space Block Record. Error: %s"),
            acadErrorStatusText(es));
    }

    es = pCirc->close();
    if (es != Acad::eOk) {
        acrx_abort(_T("\nApp X failed to")
            _T(" close circle entity. Error: %s"),
            acadErrorStatusText(es));
    }
    return es;
}

Acad::ErrorStatus
createNewLayer()
{
    AcDbLayerTableRecord *pLayerTableRecord
        = new AcDbLayerTableRecord;

    if (pLayerTableRecord == NULL)
        return Acad::eOutOfMemory;

    Acad::ErrorStatus es
        = pLayerTableRecord->setName(_T("ASDK_MYLAYER"));
    if (es != Acad::eOk) {
        delete pLayerTableRecord;
        return es;
    }

    AcDbLayerTable *pLayerTable;
    es= acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pLayerTable, AcDb::kForWrite);
    if (es != Acad::eOk) {
        delete pLayerTableRecord;
        return es;
    }

    // The linetype object ID default is 0, which is
    // not a valid ID.  Therefore, it must be set to a
    // valid ID, the CONTINUOUS linetype.
    // Other data members have valid defaults, so
    // they can be left alone.
    //
    AcDbLinetypeTable *pLinetypeTbl;
    es = acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pLinetypeTbl, AcDb::kForRead);
    if (es != Acad::eOk) {
        delete pLayerTableRecord;
        es = pLayerTable->close();
        if (es != Acad::eOk) {
            acrx_abort(_T("\nApp X failed to close Layer")
                _T(" Table. Error: %s"),
                acadErrorStatusText(es));
        }
        return es;
    }

    AcDbObjectId ltypeObjId;
    es = pLinetypeTbl->getAt(_T("CONTINUOUS"), ltypeObjId);
    if (es != Acad::eOk) {
        delete pLayerTableRecord;
        es = pLayerTable->close();
        if (es != Acad::eOk) {
            acrx_abort(_T("\nApp X failed to close Layer")
                _T(" Table. Error: %s"),
                acadErrorStatusText(es));
        }
        return es;
    }

    pLayerTableRecord->setLinetypeObjectId(ltypeObjId);

    es = pLayerTable->add(pLayerTableRecord);
    if (es != Acad::eOk) {
        Acad::ErrorStatus es2 = pLayerTable->close();
        if (es2 != Acad::eOk) {
            acrx_abort(_T("\nApp X failed to close Layer")
                _T(" Table. Error: %s"),
                acadErrorStatusText(es2));
        }
        delete pLayerTableRecord;
        return es;
    }

    es = pLayerTable->close();
    if (es != Acad::eOk) {
        acrx_abort(_T("\nApp X failed to close Layer")
            _T(" Table. Error: %s"),
            acadErrorStatusText(es));
    }

    es = pLayerTableRecord->close();
    if (es != Acad::eOk) {
        acrx_abort(_T("\nApp X failed to close Layer")
            _T(" Table Record. Error: %s"),
            acadErrorStatusText(es));
    }
    return es;
}

// END CODE APPEARING IN SDK DOCUMENT.


void doit()
{
    AcDbObjectId circleId;
    Acad::ErrorStatus es = createCircle(circleId);
    if (es != Acad::eOk) {
        acutPrintf(_T("\nError creating circle: %s"),
            acadErrorStatusText(es));
    }

    es = createNewLayer();
    if (es != Acad::eOk) {
        acutPrintf(_T("\nError creating layer: %s"),
            acadErrorStatusText(es));
    }
}


void initApp()
{
    acedRegCmds->addCommand(_T("ASDK_ERROR_TEST"),
                            _T("ASDK_ERRTST"),
                            _T("ERRTST"),
                            ACRX_CMD_MODAL,
                            doit);
}

void unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_ERROR_TEST"));
}

extern "C"
AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* appId)
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
