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
