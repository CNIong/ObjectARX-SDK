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

#include "ArxDbgSelSet.h"
#include "ArxDbgUtils.h"
#include "ArxDbgRbList.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgSelSet::ArxDbgSelSet
**
**  **jma
**
*************************************/

ArxDbgSelSet::ArxDbgSelSet()
:   m_allowDuplicates(false),
    m_allAtPickBox(false),
    m_singleOnly(false),
    m_kwordFuncPtr(NULL),
    m_otherFuncPtr(NULL),
    m_allowLast(true),
	m_filterLockedLayers(false),
	m_rejectNonCurrentSpace(false),
	m_rejectPaperSpaceViewport(false)
{
    m_ss[0] = 0L;
    m_ss[1] = 0L;

    m_lastStatus = kCanceled;
}

/****************************************************************************
**
**  ArxDbgSelSet::~ArxDbgSelSet
**
**  **jma
**
*************************************/

ArxDbgSelSet::~ArxDbgSelSet()
{
    clear();
}

/****************************************************************************
**
**  ArxDbgSelSet::isInitialized
**
**  **jma
**
*************************************/

bool
ArxDbgSelSet::isInitialized() const
{
    if ((m_ss[0] == 0L) && (m_ss[1] == 0L))
        return false;
    else
        return true;
}

/****************************************************************************
**
**  ArxDbgSelSet::clear
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::clear()
{
    if (isInitialized()) {
        acedSSFree(m_ss);
        m_ss[0] = m_ss[1] = 0L;
    }
}

/****************************************************************************
**
**  ArxDbgSelSet::createEmptySet
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::createEmptySet()
{
    clear();

    int result = acedSSAdd(NULL, NULL, m_ss);
    ASSERT(result == RTNORM);

    if (result == RTNORM)
        m_lastStatus = ArxDbgSelSet::kSelected;
    else
        m_lastStatus = ArxDbgSelSet::kCanceled;

    return m_lastStatus;
}

/****************************************************************************
**
**  ArxDbgSelSet::handleResult
**       private helper function to process common result code action.
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::handleResult(int result)
{
    if (result == RTNORM)
        m_lastStatus = ArxDbgSelSet::kSelected;
    else if (result == RTCAN)
        m_lastStatus = ArxDbgSelSet::kCanceled;
	else if (result == RTREJ) {
		ASSERT(0);
		m_lastStatus = ArxDbgSelSet::kRejected;
	}
    else {        // doesn't return RTNONE
        createEmptySet();
        m_lastStatus = ArxDbgSelSet::kNone;
    }
    return m_lastStatus;
}

/****************************************************************************
**
**  ArxDbgSelSet::userSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::userSelect(const resbuf* filter)
{
    clear();

    setFlags(false);

        // if caller wants callback function for keywords
    if (m_kwordFuncPtr)
        acedSSSetKwordCallbackPtr(m_kwordFuncPtr);

        // if caller wants callback function for garbage input
    if (m_otherFuncPtr)
        acedSSSetOtherCallbackPtr(m_otherFuncPtr);

    int result;
    if (m_kwordFuncPtr)
        result = acedSSGet(m_flags, NULL, static_cast<LPCTSTR>(m_extraKwords), filter, m_ss);
    else
        result = acedSSGet(m_flags, NULL, NULL, filter, m_ss);

    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::userSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::userSelect(LPCTSTR selectPrompt, LPCTSTR removePrompt, const resbuf* filter)
{
    ASSERT(selectPrompt || removePrompt);   // if they wanted both to be NULL they should have used other signature!
    TCHAR* promptPtrs[2];

        // allow for one of the prompts to be NULL.  It is usually useful for the
        // Remove prompt.
    if ((selectPrompt == NULL) || (selectPrompt[0] == _T('\0')))
        promptPtrs[0] = _T("\nSelect objects: ");
    else
        promptPtrs[0] = const_cast<LPTSTR>(selectPrompt);

    if ((removePrompt == NULL) || (removePrompt[0] == _T('\0')))
        promptPtrs[1] =  _T("\nRemove objects: ");
    else
        promptPtrs[1] = const_cast<LPTSTR>(removePrompt);

        // if caller wants callback function for keywords
    if (m_kwordFuncPtr)
        acedSSSetKwordCallbackPtr(m_kwordFuncPtr);

        // if caller wants callback function for garbage input
    if (m_otherFuncPtr)
        acedSSSetOtherCallbackPtr(m_otherFuncPtr);

    setFlags(true);                     // set current state of flags

    int result;
    if (m_kwordFuncPtr)
        result = acedSSGet(m_flags, promptPtrs, static_cast<LPCTSTR>(m_extraKwords), filter, m_ss);
    else
        result = acedSSGet(m_flags, promptPtrs, NULL, filter, m_ss);

    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::impliedSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::impliedSelect(const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_I"), NULL, NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::crossingSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::crossingSelect(const AcGePoint3d& pt1, const AcGePoint3d& pt2, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_C"), asDblArray(pt1), asDblArray(pt2), filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::crossingPolygonSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::crossingPolygonSelect(const AcGePoint3dArray& ptArray, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    resbuf* ptList = ptArrayToResbuf(ptArray);
    if (ptList == NULL) {
        m_lastStatus = ArxDbgSelSet::kCanceled;
        return m_lastStatus;
    }

    int result = acedSSGet(_T("_CP"), ptList, NULL, filter, m_ss);
    acutRelRb(ptList);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::fenceSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::fenceSelect(const AcGePoint3dArray& ptArray, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    resbuf* ptList = ptArrayToResbuf(ptArray);
    if (ptList == NULL) {
        m_lastStatus = ArxDbgSelSet::kCanceled;
        return m_lastStatus;
    }

    int result = acedSSGet(_T("_F"), ptList, NULL, filter, m_ss);
    acutRelRb(ptList);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::lastSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::lastSelect(const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_L"), NULL, NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::pointSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::pointSelect(const AcGePoint3d& pt1, const resbuf* filter)
{
    clear();
	setFlags(false);

    int result = acedSSGet(m_flags, asDblArray(pt1), NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::previousSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::previousSelect(const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_P"), NULL, NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::windowSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::windowSelect(const AcGePoint3d& pt1, const AcGePoint3d& pt2, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_W"), asDblArray(pt1), asDblArray(pt2), filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::windowPolygonSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::windowPolygonSelect(const AcGePoint3dArray& ptArray, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    resbuf* ptList = ptArrayToResbuf(ptArray);
    if (ptList == NULL) {
        m_lastStatus = ArxDbgSelSet::kCanceled;
        return m_lastStatus;
    }

    int result = acedSSGet(_T("_WP"), ptList, NULL, filter, m_ss);
    acutRelRb(ptList);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::filterOnlySelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::filterOnlySelect(const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_X"), NULL, NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::allSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::allSelect(const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection
	
    int result = acedSSGet(_T("_A"), NULL, NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::boxSelect
**
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::boxSelect(const AcGePoint3d& pt1, const AcGePoint3d& pt2, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_B"), asDblArray(pt1), asDblArray(pt2), filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxDbgSelSet::length
**
**  **jma
**
*************************************/

long
ArxDbgSelSet::length()
{
    ASSERT(isInitialized());

    Adesk::Int32 sslen;
    if (acedSSLength(m_ss, &sslen) != RTNORM) {
        acutPrintf(_T("\nInvalid selection set."));
        return 0L;
    }
    else
        return sslen;
}

/****************************************************************************
**
**  ArxDbgSelSet::add
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::add(ads_name ent)
{
    ASSERT(isInitialized());
    acedSSAdd(ent, m_ss, m_ss);
}

/****************************************************************************
**
**  ArxDbgSelSet::add
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::add(const AcDbObjectId& objId)
{
    ads_name ent;
    if (ArxDbgUtils::objIdToEname(objId, ent) == Acad::eOk)
        add(ent);
}

/****************************************************************************
**
**  ArxDbgSelSet::remove
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::remove(ads_name ent)
{
    ASSERT(isInitialized());
    acedSSDel(ent, m_ss);
}

/****************************************************************************
**
**  ArxDbgSelSet::remove
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::remove(const AcDbObjectId& objId)
{
    ads_name ent;
    if (ArxDbgUtils::objIdToEname(objId, ent) == Acad::eOk)
        remove(ent);
}

/****************************************************************************
**
**  ArxDbgSelSet::member
**
**  **jma
**
*************************************/

bool
ArxDbgSelSet::member(ads_name ent)
{
    ASSERT(isInitialized());

    if (acedSSMemb(ent, m_ss) == RTNORM)
        return true;
    else
        return false;
}

/****************************************************************************
**
**  ArxDbgSelSet::member
**
**  **jma
**
*************************************/

bool
ArxDbgSelSet::member(const AcDbObjectId& objId)
{
    ads_name ent;
    if (ArxDbgUtils::objIdToEname(objId, ent) == Acad::eOk)
        return member(ent);
    else
        return false;
}

/****************************************************************************
**
**  ArxDbgSelSet::subEntMarkerAt
**
**  **jma
**
*************************************/

bool
ArxDbgSelSet::subEntMarkerAt(long index, AcDbObjectId& objId, int& gsMarker)
{
    resbuf* rb;

    if (acedSSNameX(&rb, m_ss, index) != RTNORM)
        return false;

        // walk to third element to retrieve ename of selected entity
    int i = 1;
    resbuf* tmp = rb;
    while (tmp && (i < 3)) {
        i++;
        tmp = tmp->rbnext;
    }
        // get the objectId of the slected entity
    ASSERT((tmp != NULL) && (i == 3));
    if (tmp == NULL)
        return false;

    if (ArxDbgUtils::enameToObjId(tmp->resval.rlname, objId) != Acad::eOk) {
        acutRelRb(rb);
        return false;
    }
        // get the gsMarker, which should be the 4th element
    tmp = tmp->rbnext;
    ASSERT(tmp != NULL);
    if (tmp == NULL) {
        acutRelRb(rb);
        return false;
    }

    gsMarker = tmp->resval.rint;
    acutRelRb(rb);
    return true;
}

/****************************************************************************
**
**  ArxDbgSelSet::asArray
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::asArray(AcDbObjectIdArray& objIds)
{
    ASSERT(isInitialized());
    long len = length();
    int ret;
    AcDbObjectId objId;
    ads_name ent;

    for (long i=0L; i<len; i++) {
        ret = acedSSName(m_ss, i, ent);
        ASSERT(ret == RTNORM);
        if (ArxDbgUtils::enameToObjId(ent, objId) == Acad::eOk)
            objIds.append(objId);
    }
}

/****************************************************************************
**
**  ArxDbgSelSet::lastStatus
**    if client wants to delay check for status to subroutine
**  **jma
**
*************************************/

ArxDbgSelSet::SelSetStatus
ArxDbgSelSet::lastStatus() const
{
    return m_lastStatus;
}

/****************************************************************************
**
**  ArxDbgSelSet::asAdsName
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::asAdsName(ads_name ss)
{
    ss[0] = m_ss[0];
    ss[1] = m_ss[1];
}

/****************************************************************************
**
**  ArxDbgSelSet::setFilterLockedLayers
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::setFilterLockedLayers(bool filterThem)
{
    m_filterLockedLayers = filterThem;
}

/****************************************************************************
**
**  ArxDbgSelSet::setAllowDuplicates
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::setAllowDuplicates(bool dups)
{
    m_allowDuplicates = dups;
}

/****************************************************************************
**
**  ArxDbgSelSet::setAllAtPickBox
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::setAllAtPickBox(bool pickBox)
{
    m_allAtPickBox = pickBox;
}

/****************************************************************************
**
**  ArxDbgSelSet::setAllowSingleOnly
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::setAllowSingleOnly(bool single, bool allowLast)
{
    m_singleOnly = single;
    m_allowLast = allowLast;
}

/****************************************************************************
**
**  ArxDbgSelSet::setRejectNonCurrentSpace
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::setRejectNonCurrentSpace(bool rejectIt)
{
	m_rejectNonCurrentSpace = rejectIt;
}

/****************************************************************************
**
**  ArxDbgSelSet::setRejectPaperSpaceViewport
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::setRejectPaperSpaceViewport(bool rejectIt)
{
	m_rejectPaperSpaceViewport = rejectIt;
}

/****************************************************************************
**
**  ArxDbgSelSet::setKeywordCallback
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::setKeywordCallback(LPCTSTR extraKwords, struct resbuf* (*pFunc) (const TCHAR*))
{
    ASSERT(pFunc != NULL);

    m_kwordFuncPtr = pFunc;
    m_extraKwords = extraKwords;
}

/****************************************************************************
**
**  ArxDbgSelSet::setOtherCallback
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::setOtherCallback(struct resbuf* (*pFunc) (const TCHAR*))
{
    ASSERT(pFunc != NULL);

    m_otherFuncPtr = pFunc;
}

/****************************************************************************
**
**  ArxDbgSelSet::setFlags
**
**  **jma
**
*************************************/

void
ArxDbgSelSet::setFlags(bool hasPrompt)
{
    m_flags = _T("_");

    if (m_singleOnly) {
        if (m_allowLast)
            m_flags += _T("+L");

        m_flags += _T("+.:S");    // put in single mode, plus allow only pick selection
    }

    if (hasPrompt)
        m_flags += _T(":$");

    if (m_allowDuplicates)
        m_flags += _T(":D");

    if (m_allAtPickBox)
        m_flags += _T(":E");

	if (m_filterLockedLayers)
		m_flags += _T(":L");

	if (m_rejectNonCurrentSpace)
		m_flags += _T(":C");

	if (m_rejectPaperSpaceViewport)
		m_flags += _T(":P");

    if (m_kwordFuncPtr != NULL)
        m_flags += _T(":K");

    if (m_otherFuncPtr != NULL)
        m_flags += _T(":?");
}



