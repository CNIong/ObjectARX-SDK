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

#include "ArxDbgUiPrEntity.h"
#include "ArxDbgUtils.h"
#include "AcadStr.h"
#include "SdSysVar.h"



/****************************************************************************
**
**  ArxDbgUiPrEntity::ArxDbgUiPrEntity
**
**  **jma
**
*************************************/

ArxDbgUiPrEntity::ArxDbgUiPrEntity(LPCTSTR msg, LPCTSTR keyWordList)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_allowNone(false),
    m_objId(AcDbObjectId::kNull),
    m_filterLockedLayers(false)
{
}

/****************************************************************************
**
**  ArxDbgUiPrEntity::~ArxDbgUiPrEntity
**
**  **jma
**
*************************************/

ArxDbgUiPrEntity::~ArxDbgUiPrEntity()
{
}

/****************************************************************************
**
**  ArxDbgUiPrEntity::addAllowedClass
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUiPrEntity::addAllowedClass(AcRxClass* classType, bool doIsATest)
{
    ASSERT(classType != NULL);

    if (m_allowedClassTypes.contains(classType))
        return Acad::eDuplicateKey;

    m_allowedClassTypes.append(classType);
    m_doIsATest.append(static_cast<int>(doIsATest));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgUiPrEntity::filterLockedLayers
**
**  **jma
**
*************************************/

bool
ArxDbgUiPrEntity::filterLockedLayers() const
{
    return m_filterLockedLayers;
}

/****************************************************************************
**
**  ArxDbgUiPrEntity::setFilterLockedLayers
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUiPrEntity::setFilterLockedLayers(bool filterThem)
{
    m_filterLockedLayers = filterThem;

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgUiPrEntity::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrEntity::go()
{
    CString prompt;
    int result;
    int errNum;
    ads_point adsPt;
    ads_name ent;
    AcDbObjectId tmpId;
    AcDbEntity* tmpEnt;
    Acad::ErrorStatus es;

    prompt.Format(_T("\n%s: "), message());

    while (1) {
        acedInitGet(0, keyWords());
        result = acedEntSel(prompt, ent, adsPt);

        if (result == RTNORM) {
            ArxDbgUtils::enameToObjId(ent, tmpId);
            es = acdbOpenAcDbEntity(tmpEnt, tmpId, AcDb::kForRead);
            if (es == Acad::eOk) {
                    // if its correct class and we are not filtering locked layers its ok,
                    // or if we are filtering locked layers and this one isn't on a locked layer
                if (correctClass(tmpEnt)) {     // correctClass() will print error msg
                    if ((!m_filterLockedLayers) ||
                        (ArxDbgUtils::isOnLockedLayer(tmpEnt, true) == false)) {    // isOnLockedLayer() will print error msg
                        tmpEnt->close();
                        m_pickPt = asPnt3d(adsPt);
                        m_objId = tmpId;
                        return ArxDbgUiPrBase::kOk;
                    }
                }
                tmpEnt->close();    // close and loop again until they get it right!
            }
            else {
                ASSERT(0);
                ArxDbgUtils::rxErrorMsg(es);
                return ArxDbgUiPrBase::kCancel;
            }
        }
        else if (result == RTERROR) {
            getSysVar(AcadVar::adserr, errNum);
            if (errNum == OL_ENTSELPICK)            // picked but didn't get anything
                acutPrintf(_T("\nNothing selected."));
            else if (errNum == OL_ENTSELNULL) {     // hit RETURN or SPACE
                if (m_allowNone)
                    return ArxDbgUiPrBase::kNone;      // prompt specifically wants to know about None
                else
                    return ArxDbgUiPrBase::kCancel;    // prompt wants to bail on None
            }
            else
                acutPrintf(_T("\nNothing selected."));
        }
        else if (result == RTKWORD) {
            acedGetInput(m_keyWordPicked.GetBuffer(512));
            m_keyWordPicked.ReleaseBuffer();
            return ArxDbgUiPrBase::kKeyWord;
        }
        else
            return ArxDbgUiPrBase::kCancel;
    }
}

/****************************************************************************
**
**  ArxDbgUiPrEntity::correctClass
**
**  **jma
**
*************************************/

bool
ArxDbgUiPrEntity::correctClass(AcDbEntity* ent)
{
    if (m_allowedClassTypes.isEmpty())
        return Adesk::kTrue;

    AcRxClass* rxClass;
    int len = m_allowedClassTypes.length();
    bool isOk = false;
    for (int i=0; i<len; i++) {
        rxClass = static_cast<AcRxClass*>(m_allowedClassTypes[i]);
        if (m_doIsATest[i]) {
            if (ent->isA() == rxClass)
                isOk = true;
        }
        else {
            if (ent->isKindOf(rxClass))
                isOk = true;
        }
    }

    if (isOk)
        return true;

        // print out error message with allowed types
    CString types;
    CString str;
    for (int ii=0; ii<len;ii++) {
        if (ii > 0)
            types += _T(", ");

        rxClass = static_cast<AcRxClass*>(m_allowedClassTypes[ii]);
        types += rxClass->name();
    }

    acutPrintf(_T("\nSelected entity must be of type: %s"), types);

    return false;
}

/****************************************************************************
**
**  ArxDbgUiPrEntity::objectId
**
**  **jma
**
*************************************/

AcDbObjectId
ArxDbgUiPrEntity::objectId() const
{
    return m_objId;
}

/****************************************************************************
**
**  ArxDbgUiPrEntity::pickPoint
**
**  **jma
**
*************************************/

AcGePoint3d
ArxDbgUiPrEntity::pickPoint() const
{
    return m_pickPt;
}

/****************************************************************************
**
**  ArxDbgUiPrEntity::setAllowNone
**
**  **jma
**
*************************************/

void
ArxDbgUiPrEntity::setAllowNone(bool allowIt)
{
    m_allowNone = allowIt;
}


