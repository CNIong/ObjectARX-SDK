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

#include "ArxDbgTransientObjReactor.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdcTransientReactors.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgTransientObjReactor, AcDbObjectReactor);

/****************************************************************************
**
**  ArxDbgTransientObjReactor::~ArxDbgTransientObjReactor
**
**  **jma
**
*************************************/

ArxDbgTransientObjReactor::~ArxDbgTransientObjReactor()
{
    delFromAll();
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::addToObject
**
**  **jma
**
*************************************/

bool
ArxDbgTransientObjReactor::addToObject(AcDbObject* obj)
{
    ASSERT(obj != NULL);
    ASSERT(obj->isWriteEnabled() == Adesk::kTrue);

    if (m_objList.contains(obj->objectId()))
        return false;
    else {
        obj->addReactor(this);
        m_objList.append(obj->objectId());
        return true;
    }
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::delFromObject
**
**  **jma
**
*************************************/

bool
ArxDbgTransientObjReactor::delFromObject(AcDbObject* obj)
{
    ASSERT(obj != NULL);
    ASSERT(obj->isWriteEnabled() == Adesk::kTrue);

    int index;
    if (m_objList.find(obj->objectId(), index)) {
        obj->removeReactor(this);
        m_objList.removeAt(index);
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::delFromAll
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::delFromAll()
{
    AcDbObject* obj;
    Acad::ErrorStatus es;

    int length = m_objList.length();
    for (int i=0; i<length; i++) {
            // must open erased entities too!
        es = acdbOpenObject(obj, m_objList[i], AcDb::kForWrite, true);
        if (es == Acad::eOk) {
            obj->removeReactor(this);
            obj->close();
        }
        else
            ArxDbgUtils::rxErrorAlert(es);
    }
    m_objList.setLogicalLength(0);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::cancelled
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::cancelled(const AcDbObject* obj)
{
    printReactorMessage(_T("Cancelled"), obj);
    ArxDbgUiTdcTransientReactors::doStateDboxCacelled(obj);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::copied
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::copied(const AcDbObject* obj, const AcDbObject* newObj)
{
    CString str;

    printReactorMessage(_T("Copied"), obj);
    acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T(""), _T("New Object"),
            ArxDbgUtils::objToClassStr(newObj), ArxDbgUtils::objToHandleStr(newObj, str));
    ArxDbgUiTdcTransientReactors::doStateDboxCopied(obj, newObj);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::erased
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::erased(const AcDbObject* obj, Adesk::Boolean pErasing)
{
    if (pErasing)
        printReactorMessage(_T("Erase"), obj);
    else
        printReactorMessage(_T("Un-erase"), obj);

    ArxDbgUiTdcTransientReactors::doStateDboxErased(obj, pErasing);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::goodbye
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::goodbye(const AcDbObject* obj)
{
    printReactorMessage(_T("Goodbye"), obj);
    ArxDbgUiTdcTransientReactors::doStateDboxGoodbye(obj);

	m_objList.remove(obj->objectId());	// remove this from the list of things we are keeping track of
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::openedForModify
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::openedForModify(const AcDbObject* obj)
{
    printReactorMessage(_T("Open For Modify"), obj);
    ArxDbgUiTdcTransientReactors::doStateDboxOpenedModify(obj);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::modified
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::modified(const AcDbObject* obj)
{
    printReactorMessage(_T("Modified"), obj);
    ArxDbgUiTdcTransientReactors::doStateDboxModified(obj);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::subObjModified
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::subObjModified(const AcDbObject* obj, const AcDbObject* subObj)
{
    CString str;

    printReactorMessage(_T("Sub-Obj Modified"), obj);
    acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T(""), _T("Sub Object"),
            ArxDbgUtils::objToClassStr(subObj), ArxDbgUtils::objToHandleStr(subObj, str));

    ArxDbgUiTdcTransientReactors::doStateDboxSubObjModified(obj, subObj);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::modifyUndone
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::modifyUndone(const AcDbObject* obj)
{
    printReactorMessage(_T("Modify Undone"), obj);
    ArxDbgUiTdcTransientReactors::doStateDboxModifyUndone(obj);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::modifiedXData
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::modifiedXData(const AcDbObject* obj)
{
    printReactorMessage(_T("Modified Xdata"), obj);
    ArxDbgUiTdcTransientReactors::doStateDboxModifiedXdata(obj);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::unappended
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::unappended(const AcDbObject* obj)
{
    printReactorMessage(_T("Un-appended"), obj);
    ArxDbgUiTdcTransientReactors::doStateDboxUnappended(obj);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::reappended
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::reappended(const AcDbObject* obj)
{
    printReactorMessage(_T("Re-appended"), obj);
    ArxDbgUiTdcTransientReactors::doStateDboxReappended(obj);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::objectClosed
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::objectClosed(const AcDbObjectId objId)
{
    printReactorMessage(_T("Object Closed"), NULL);
    ArxDbgUiTdcTransientReactors::doStateDboxClosed(objId);
}

/****************************************************************************
**
**  ArxDbgTransientObjReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgTransientObjReactor::printReactorMessage(LPCTSTR event, const AcDbObject* obj) const
{
    CString str;

    if (obj != NULL) {
        acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T("{OBJ T-REACTOR}"), event,
                ArxDbgUtils::objToClassStr(obj), ArxDbgUtils::objToHandleStr(obj, str));
    }
    else {
        acutPrintf(_T("\n%-15s : {%-18s: } "), _T("{OBJ T-REACTOR}"), event);
    }
}
