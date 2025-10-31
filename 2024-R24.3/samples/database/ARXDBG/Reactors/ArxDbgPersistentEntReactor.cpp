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

#include "ArxDbgPersistentEntReactor.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdcPersistentReactors.h"



Adesk::Int16     ArxDbgPersistentEntReactor::m_version = 0;     // MDI safe

ACRX_DXF_DEFINE_MEMBERS(ArxDbgPersistentEntReactor, ArxDbgPersistentObjReactor,
						AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
						0, ARXDBG_PERSISTENT_ENT_REACTOR, ArxDbg);

/****************************************************************************
**
**  ArxDbgPersistentEntReactor::dwgInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgPersistentEntReactor::dwgInFields(AcDbDwgFiler* filer)
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgPersistentObjReactor::dwgInFields(filer)) != Acad::eOk)
        return es;

    Adesk::Int16 version;
    filer->readItem(&version);
    //if (version > m_version)
    //    return Acad::eMakeMeProxy;

	// we don't have any data at this level yet, but we still want to file
	// out version in case we do some day.

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgPersistentEntReactor::dwgOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgPersistentEntReactor::dwgOutFields(AcDbDwgFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgPersistentObjReactor::dwgOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(m_version);

	// we don't have any data at this level yet, but we still want to file
	// out version in case we do some day.

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgPersistentEntReactor::dxfInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgPersistentEntReactor::dxfInFields(AcDbDxfFiler* filer)
{
    Acad::ErrorStatus es;
    if (((es = ArxDbgPersistentObjReactor::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgPersistentEntReactor::dxfOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgPersistentEntReactor::dxfOutFields(AcDbDxfFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgPersistentObjReactor::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgPersistentEntReactor::modifiedGraphics
**
**  **jma
**
*************************************/

void
ArxDbgPersistentEntReactor::modifiedGraphics(const AcDbObject* obj)
{
    printReactorMessage(_T("Modified Graphics"), obj);
    ArxDbgUiTdcPersistentReactors::doStateDboxModifiedGraphics(obj);
}

/****************************************************************************
**
**  ArxDbgPersistentEntReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgPersistentEntReactor::printReactorMessage(LPCTSTR event, const AcDbObject* obj) const
{
    CString str;

    if (obj != NULL) {
        acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T("{ENT P-REACTOR}"), event,
                ArxDbgUtils::objToClassStr(obj), ArxDbgUtils::objToHandleStr(obj, str));
    }
    else {
        acutPrintf(_T("\n%-15s : {%-18s: } "), _T("{ENT P-REACTOR}"), event);
    }
}
