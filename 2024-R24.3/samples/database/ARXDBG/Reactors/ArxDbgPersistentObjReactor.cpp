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

#include "ArxDbgPersistentObjReactor.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdcPersistentReactors.h"



Adesk::Int16     ArxDbgPersistentObjReactor::m_version = 0;     // MDI safe

ACRX_DXF_DEFINE_MEMBERS(ArxDbgPersistentObjReactor, AcDbObject,
                        AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
                        0, ARXDBG_PERSISTENT_OBJ_REACTOR, ArxDbg);

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::getAttachedToObjs
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::getAttachedToObjs(AcDbObjectIdArray& objIds) const
{
    assertReadEnabled();

    objIds = m_attachedToObjs;
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::attachTo
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgPersistentObjReactor::attachTo(const AcDbObjectId& objId)
{
    if (m_attachedToObjs.contains(objId) == false) {
        assertWriteEnabled();
        m_attachedToObjs.append(objId);
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::detachFrom
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgPersistentObjReactor::detachFrom(const AcDbObjectId& objId)
{
    if (m_attachedToObjs.contains(objId) == false)
        return Acad::eKeyNotFound;

    assertWriteEnabled();
    m_attachedToObjs.remove(objId);

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::dwgInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgPersistentObjReactor::dwgInFields(AcDbDwgFiler* filer)
{
    Acad::ErrorStatus es;
    if ((es = AcDbObject::dwgInFields(filer)) != Acad::eOk)
        return es;

    Adesk::Int16 version;
    filer->readItem(&version);
    if (version > m_version)
        return Acad::eMakeMeProxy;

    AcDbSoftPointerId tmpId;
    Adesk::Int32 count;
    filer->readItem(&count);
    
    m_attachedToObjs.setLogicalLength(0);
    for (int i=0; i<count; i++) {
        filer->readItem(&tmpId);
        if (tmpId.isNull() == false)
            m_attachedToObjs.append(tmpId);
    }

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::dwgOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgPersistentObjReactor::dwgOutFields(AcDbDwgFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = AcDbObject::dwgOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(m_version);

    int len = m_attachedToObjs.length();
    filer->writeInt32(len);	// count of ids

    for (int i=0; i<len; i++)
        filer->writeSoftPointerId(m_attachedToObjs[i]);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::dxfInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgPersistentObjReactor::dxfInFields(AcDbDxfFiler* filer)
{
    Acad::ErrorStatus es;
    if (((es = AcDbObject::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

    resbuf rb;
    m_attachedToObjs.setLogicalLength(0);

    while ((es == Acad::eOk) && ((es = filer->readResBuf(&rb)) == Acad::eOk)) {
        if (rb.restype == AcDb::kDxfSoftPointerId) {
            AcDbObjectId tmpId;
            tmpId.setFromOldId(rb.resval.mnLongPtr);
            if (tmpId.isNull() == false)
                m_attachedToObjs.append(tmpId);
        }
        else {
            filer->pushBackItem();
            es = Acad::eEndOfFile;
        }
    }

    if (es != Acad::eEndOfFile)
        return Acad::eInvalidResBuf;

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::dxfOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgPersistentObjReactor::dxfOutFields(AcDbDxfFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = AcDbObject::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());

        // write out all the Ids
    int len = m_attachedToObjs.length();
    for (int i=0; i<len; i++) {
        if (m_attachedToObjs[i].isNull() == false)
            filer->writeItem(AcDb::kDxfSoftPointerId, m_attachedToObjs[i]);
    }

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::cancelled
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::cancelled(const AcDbObject* obj)
{
    printReactorMessage(_T("Cancelled"), obj);
    ArxDbgUiTdcPersistentReactors::doStateDboxCacelled(obj);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::copied
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::copied(const AcDbObject* obj, const AcDbObject* newObj)
{
    CString str;

    printReactorMessage(_T("Copied"), obj);
    acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T(""), _T("New Object"),
            ArxDbgUtils::objToClassStr(newObj), ArxDbgUtils::objToHandleStr(newObj, str));

    ArxDbgUiTdcPersistentReactors::doStateDboxCopied(obj, newObj);

    if (newObj->database() != NULL) {
        Adesk::Boolean wasWritable;
        Acad::ErrorStatus es = upgradeFromNotify(wasWritable);
        if (es == Acad::eOk) {
            attachTo(newObj->objectId());
            downgradeToNotify(wasWritable);
        }
    }
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::erased
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::erased(const AcDbObject* obj, Adesk::Boolean pErasing)
{
    if (pErasing)
        printReactorMessage(_T("Erase"), obj);
    else
        printReactorMessage(_T("Un-erase"), obj);

    ArxDbgUiTdcPersistentReactors::doStateDboxErased(obj, pErasing);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::goodbye
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::goodbye(const AcDbObject* obj)
{
    printReactorMessage(_T("Goodbye"), obj);
    ArxDbgUiTdcPersistentReactors::doStateDboxGoodbye(obj);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::openedForModify
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::openedForModify(const AcDbObject* obj)
{
    printReactorMessage(_T("Open For Modify"), obj);
    ArxDbgUiTdcPersistentReactors::doStateDboxOpenedModify(obj);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::modified
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::modified(const AcDbObject* obj)
{
    printReactorMessage(_T("Modified"), obj);
    ArxDbgUiTdcPersistentReactors::doStateDboxModified(obj);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::subObjModified
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::subObjModified(const AcDbObject* obj, const AcDbObject* subObj)
{
    CString str;

    printReactorMessage(_T("Sub-Obj Modified"), obj);
    acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T(""), _T("Sub Object"),
            ArxDbgUtils::objToClassStr(subObj), ArxDbgUtils::objToHandleStr(subObj, str));

    ArxDbgUiTdcPersistentReactors::doStateDboxSubObjModified(obj, subObj);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::modifyUndone
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::modifyUndone(const AcDbObject* obj)
{
    printReactorMessage(_T("Modify Undone"), obj);
    ArxDbgUiTdcPersistentReactors::doStateDboxModifyUndone(obj);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::modifiedXData
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::modifiedXData(const AcDbObject* obj)
{
    printReactorMessage(_T("Modified Xdata"), obj);
    ArxDbgUiTdcPersistentReactors::doStateDboxModifiedXdata(obj);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::unappended
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::unappended(const AcDbObject* obj)
{
    printReactorMessage(_T("Un-appended"), obj);
    ArxDbgUiTdcPersistentReactors::doStateDboxUnappended(obj);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::reappended
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::reappended(const AcDbObject* obj)
{
    printReactorMessage(_T("Re-appended"), obj);
    ArxDbgUiTdcPersistentReactors::doStateDboxReappended(obj);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::objectClosed
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::objectClosed(const AcDbObjectId objId)
{
    printReactorMessage(_T("Object Closed"), NULL);
    ArxDbgUiTdcPersistentReactors::doStateDboxClosed(objId);
}

/****************************************************************************
**
**  ArxDbgPersistentObjReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgPersistentObjReactor::printReactorMessage(LPCTSTR event, const AcDbObject* obj) const
{
    CString str;

    if (obj != NULL) {
        acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T("{OBJ P-REACTOR}"), event,
                ArxDbgUtils::objToClassStr(obj), ArxDbgUtils::objToHandleStr(obj, str));
    }
    else {
        acutPrintf(_T("\n%-15s : {%-18s: } "), _T("{OBJ P-REACTOR}"), event);
    }
}

