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

#include "AecUiPrEntity.h"
#include "AecUiPrSubEntity.h"
#include "AecUiPrEntitySetSingle.h"
#include "AecuUtils.h"
#include "AecUiBaseApp.h"
#include "Res_AecUiBase.h"



/****************************************************************************
**
**  AecUiPrSubentity::AecUiPrSubentity
**
**  **jma
**
*************************************/

AecUiPrSubentity::AecUiPrSubentity(LPCTSTR msg)
:   m_filterType(0),
    m_isValidssnamexData(Adesk::kFalse),
    m_allowNone(Adesk::kFalse),
    m_mainEnt(AcDbObjectId::kNull),
    m_allowMultipleSelect(Adesk::kFalse)
{
    setMessage(msg);
}

/****************************************************************************
**
**  AecUiPrSubentity::~AecUiPrSubentity
**
**  **jma
**
*************************************/

AecUiPrSubentity::~AecUiPrSubentity()
{
}

/****************************************************************************
**
**  AecUiPrSubentity::setAllowNone
**
**  **jma
**
*************************************/

Acad::ErrorStatus
AecUiPrSubentity::setAllowNone(Adesk::Boolean allowIt)
{
    m_allowNone = allowIt;
    return Acad::eOk;
}

/****************************************************************************
**
**  AecUiPrSubentity::setAllowMultipleSelect
**
**  **jma
**
*************************************/

Acad::ErrorStatus
AecUiPrSubentity::setAllowMultipleSelect(Adesk::Boolean allowIt)
{
    m_allowMultipleSelect = allowIt;
    return Acad::eOk;
}

/****************************************************************************
**
**  AecUiPrSubentity::setFilterType
**
**  **jma
**
*************************************/

Acad::ErrorStatus
AecUiPrSubentity::setFilterType(int type)
{
    m_filterType = type;

    return Acad::eOk;
}

/****************************************************************************
**
**  AecUiPrSubentity::setMainEntity
**
**  **jma
**
*************************************/

Acad::ErrorStatus
AecUiPrSubentity::setMainEntity(const AcDbObjectId& objId)
{
        // only allowed to do this before goPrompt issued
    if (m_mainEnt != AcDbObjectId::kNull) {
        AEC_ASSERT(0);
        return Acad::eInvalidInput;
    }

    m_mainEnt = objId;  // TBD: should open up and make sure it passes validity tests
    return Acad::eOk;
}

/****************************************************************************
**
**  AecUiPrSubentity::objectId
**
**  **jma
**
*************************************/

AcDbObjectId
AecUiPrSubentity::objectId() const
{
    if (m_selSet.isEmpty()) {
        AEC_ASSERT(0);
        return AcDbObjectId::kNull;
    }

    return m_selSet.first();
}

/****************************************************************************
**
**  AecUiPrSubentity::isValidSubEntData
**
**  **jma
**
*************************************/

Adesk::Boolean
AecUiPrSubentity::isValidSubEntData() const
{
    return m_isValidssnamexData;
}

/****************************************************************************
**
**  AecUiPrSubentity::pickCount
**
**  **jma
**
*************************************/

int
AecUiPrSubentity::pickCount() const
{
    AEC_ASSERT(m_isValidssnamexData);
    return m_gsMarkers.length();
}

/****************************************************************************
**
**  AecUiPrSubentity::pickPoint
**
**  **jma
**
*************************************/

AcGePoint3d
AecUiPrSubentity::pickPointAt(int index) const
{
    AEC_ASSERT(m_isValidssnamexData);
    return m_pickPts[index];
}

/****************************************************************************
**
**  AecUiPrSubentity::pickVector
**
**  **jma
**
*************************************/

AcGeVector3d
AecUiPrSubentity::pickVectorAt(int index) const
{
    AEC_ASSERT(m_isValidssnamexData);
    return m_pickVecs[index];
}

/****************************************************************************
**
**  AecUiPrSubentity::gsMarkerAt
**
**  **jma
**
*************************************/

Adesk::Int32
AecUiPrSubentity::gsMarkerAt(int index) const
{
    AEC_ASSERT(m_isValidssnamexData);
    return m_gsMarkers[index];
}

/****************************************************************************
**
**  AecUiPrSubentity::gsMarkers
**
**  **jma
**
*************************************/

const AcDbIntArray&
AecUiPrSubentity::gsMarkers() const
{
    AEC_ASSERT(m_isValidssnamexData);
    return m_gsMarkers;
}

/****************************************************************************
**
**  AecUiPrSubentity::go
**
**  **jma
**
*************************************/

AecUiPrBase::Status
AecUiPrSubentity::go()
{
    m_selSet.setLogicalLength(0);   // reset to null set
    m_isValidssnamexData = Adesk::kFalse;

    getLockedLayers();
    getAllowableClassTypes();

    m_disallowPickfirstSet = Adesk::kTrue;  // don't allow pickfirst set because we need the gsmarkers
    cleanPickfirstSet();

    resbuf* filter = buildSelSetFilter();

    m_ss.setKeywordCallback(_DNT(_T("FIlter _ FIlter")), AecUiPrEntitySetSingle::keywordCallback);
    m_currentPromptObj = this;  // hack way to get back from keyword callback

    m_ss.setAllowSingleOnly(Adesk::kTrue, Adesk::kFalse);
    m_ss.setAllAtPickBox(Adesk::kTrue);     // enable selection of more than 1.  Filter will do the rest.  If not, it will work
                                            // like normal anyway by taking the first one and they can turn on object cycling
                                            // if they want to be exact.
    AecRmCString promptStr(message());
    AecAcadSelSet::SelSetStatus stat = AecAcadSelSet::kNone;
    int errNum = 0;
    while (1) {
        Aecu::setSysVar(AcadVar::adserr, 0);     // reset fresh

            // if supplied prompt, pass it on to selection set
        if (promptStr.IsEmpty() == FALSE) {
            AecRmCString tmpPrompt;
            tmpPrompt.Format(_DNT(_T("\n%s: ")), static_cast<LPCTSTR>(promptStr));
            stat = m_ss.userSelect(tmpPrompt, NULL, filter);
        }
            // no prompt supplied, use regular ssget prompts
        else {
            stat = m_ss.userSelect(filter);
        }

            // got some kind of response, if its a NULL response, only
            // allow it if allowNone flag is set or if they have already
            // picked some sub-entities
        if (stat == AecAcadSelSet::kNone) {
            if (Aecu::getSysVar(AcadVar::adserr, errNum) == Acad::eOk) {
                if (errNum != OL_ENTSELNULL) {   // this means they missed hitting an entity
                    Aec::ads_printf(GetAecUiBaseApp(), AECU_STR_NO_SELECTION);
                    continue;
                }
            }

            if ((m_allowNone) || (m_mainEnt != AcDbObjectId::kNull)) {
                    // if they have already picked one, final return value should
                    // be selected, not NONE
                if (m_mainEnt != AcDbObjectId::kNull)
                    stat = AecAcadSelSet::kSelected;

                break;
            }
            else
                continue;
        }
        else if (stat == AecAcadSelSet::kSelected) {
            if (retrievePickDataAt(0L)) {

                    // bail early if we only allow a single edgeId
                if (m_allowMultipleSelect == Adesk::kFalse)
                    break;
            }
        }
        else
            break;
    }

    doUnHighlight(m_mainEnt);   // leave object unhighlighted when we leave the prompt

    m_currentPromptObj = NULL;

    if (filter)
        ads_relrb(filter);

    if (stat != AecAcadSelSet::kSelected) {
        if (stat == AecAcadSelSet::kNone)
            return AecUiPrBase::kNone;
        else
            return AecUiPrBase::kCancel;
    }

    if (m_selSet.isEmpty()) {
        AEC_ASSERT(0);      // should have return kNone already
        return AecUiPrBase::kCancel;
    }
    else
        return AecUiPrBase::kOk;
}

/****************************************************************************
**
**  AecUiPrSubentity::doHighlight
**
**  **jma
**
*************************************/

Adesk::Boolean
AecUiPrSubentity::doHighlight(const AcDbObjectId& objId)
{
    if (m_gsMarkers.isEmpty())  // could happen the first time through loop
        return Adesk::kTrue;

    AecDbEntity* ent;
    Acad::ErrorStatus es = AecDbEntity::open(ent, objId, AcDb::kForRead);
    if (es == Acad::eOk) {
        ent->highlightSubents(m_gsMarkers);
        ent->close();
    }
    else {
        AEC_ASSERT(0);
        Aec::rxErrorMsg(es);
    }

    return Adesk::kTrue;
}

/****************************************************************************
**
**  AecUiPrSubentity::doUnHighlight
**
**  **jma
**
*************************************/

Adesk::Boolean
AecUiPrSubentity::doUnHighlight(const AcDbObjectId& objId)
{
    if (m_gsMarkers.isEmpty())  // could happen the first time through loop
        return Adesk::kTrue;

    AecDbEntity* ent;
    Acad::ErrorStatus es = AecDbEntity::open(ent, objId, AcDb::kForRead);
    if (es == Acad::eOk) {
        ent->unhighlightSubents(m_gsMarkers);
        ent->close();
    }
    else {
        AEC_ASSERT(0);
        Aec::rxErrorMsg(es);
    }

    return Adesk::kTrue;
}

/****************************************************************************
**
**  AecUiPrSubentity::retrievePickDataAt
**
**  **jma
**
*************************************/

Adesk::Boolean
AecUiPrSubentity::retrievePickDataAt(long index)
{
    AecRmCString hardErrMsg(GetAecUiBaseAppName(), AECU_STR_RETRIEVEPICKDATAAT_AECUIPRSUBENTITY_ERROR_COULD_NOT, TRUE);  //~  "\nERROR: could not retreive pick data!"

    resbuf* rb;
    ads_name selSet;

    m_ss.asAdsName(selSet);

    if (ads_ssnamex(&rb, selSet, index) != RTNORM)
        return Adesk::kFalse;

        // find out the objectId of the item picked
    AcDbObjectId mainId;
    ads_name ent;
    ads_ssname(selSet, index, ent);
    if (Aec::enameToObjId(ent, mainId) != Acad::eOk) {
        ads_printf(hardErrMsg);
        return Adesk::kFalse;
    }

    resbuf* tmp = rb;
    if ((tmp == NULL) || (tmp->restype != RTLB)) { // should start with this
        AEC_ASSERT(0);
        ads_relrb(rb);
        ads_printf(hardErrMsg);
        return Adesk::kFalse;
    }

        // second element is selection method, which should always be pickPt=1
    tmp = tmp->rbnext;
    if ((tmp == NULL) || (tmp->restype != RTSHORT) || (tmp->resval.rint != 1)) {
        AEC_ASSERT(0);
        ads_relrb(rb);
        ads_printf(hardErrMsg);
        return Adesk::kFalse;
    }

        // third element is entity name of object selected
    tmp = tmp->rbnext;
    if ((tmp == NULL) || (tmp->restype != RTENAME)) {
        AEC_ASSERT(0);
        ads_relrb(rb);
        ads_printf(hardErrMsg);
        return Adesk::kFalse;
    }

        // fourth element is the gsMarker
    tmp = tmp->rbnext;
    if ((tmp == NULL) || (tmp->restype != RTSHORT)) {
        AEC_ASSERT(0);
        ads_relrb(rb);
        ads_printf(hardErrMsg);
        return Adesk::kFalse;
    }
    int gsMarker = tmp->resval.rint;

        // fifth element is start of list for pickPt
    tmp = tmp->rbnext;
    if ((tmp == NULL) || (tmp->restype != RTLB)) {
        AEC_ASSERT(0);
        ads_relrb(rb);
        ads_printf(hardErrMsg);
        return Adesk::kFalse;
    }

        // sixth element is point descriptor
    tmp = tmp->rbnext;
    if ((tmp == NULL) || (tmp->restype != RTSHORT)) {
        AEC_ASSERT(0);
        ads_relrb(rb);
        ads_printf(hardErrMsg);
        return Adesk::kFalse;
    }

        // seventh element is pick point
    tmp = tmp->rbnext;
    if ((tmp == NULL) || (tmp->restype != RT3DPOINT)) {
        AEC_ASSERT(0);
        ads_relrb(rb);
        ads_printf(hardErrMsg);
        return Adesk::kFalse;
    }

    AcGePoint3d pickPt(tmp->resval.rpoint[0], tmp->resval.rpoint[1], tmp->resval.rpoint[2]);

        // eigth element is either end of list or the direction vector
    tmp = tmp->rbnext;
    if (tmp == NULL) {
        AEC_ASSERT(0);
        ads_relrb(rb);
        ads_printf(hardErrMsg);
        return Adesk::kFalse;
    }

    AcGeVector3d pickVector;
    if (tmp->restype == RT3DPOINT)
        pickVector.set(tmp->resval.rpoint[0], tmp->resval.rpoint[1], tmp->resval.rpoint[2]);
    else
        pickVector.set(0.0, 0.0, 1.0);    // WCS Z-axis

    ads_relrb(rb);

        // if this is the first time its picked, set mainId to this objectId.
        // All subsequent picks must match this id
    if (m_mainEnt == AcDbObjectId::kNull) {
        m_mainEnt = mainId;

            // add this to the "set" of objects selected (which in our case is 1 item)
        m_selSet.setLogicalLength(0);   // reset array
        m_selSet.append(mainId);
    }
    else {
            // must be from same entity!
        if (m_mainEnt != mainId) {
            AecRmCString msg;
            msg.LoadString(GetAecUiBaseAppName(), AECU_STR_SUBENT_MUST_BE_FROM_MAINENT);
            ads_printf(msg);
            return Adesk::kFalse;
        }
    }

        // unhighlight any existing edges
    doUnHighlight(m_mainEnt);

        // if the same edge is picked twice, remove it out of the set
    int atIndex;
    if (m_gsMarkers.find(gsMarker, atIndex)) {
        m_gsMarkers.removeAt(atIndex);
        m_pickPts.removeAt(atIndex);
        m_pickVecs.removeAt(atIndex);

        DEBUG_ONLY(ads_printf(_DNT(_T("\nAecUiPrSubentity:: removed gsmarker: %d")), gsMarker));
    }
    else {
        m_isValidssnamexData = Adesk::kTrue;    // this isn't really accurate Nth time thru loop
        m_gsMarkers.append(gsMarker);
        m_pickPts.append(pickPt);
        m_pickVecs.append(pickVector);

        DEBUG_ONLY(ads_printf(_DNT(_T("\nAecUiPrSubentity:: added gsmarker: %d")), gsMarker));
    }

        // re-highlight with new data
    doHighlight(m_mainEnt);

    return Adesk::kTrue;
}



