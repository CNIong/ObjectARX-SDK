//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
