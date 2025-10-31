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

#include "AecUiPrEntitySetSingle.h"



/****************************************************************************
**
**  AecUiPrEntitySetSingle::AecUiPrEntitySetSingle
**
**  **jma
**
*************************************/

AecUiPrEntitySetSingle::AecUiPrEntitySetSingle(LPCTSTR msg)
:   m_allowNone(Adesk::kFalse)
{
    setMessage(msg);
}

/****************************************************************************
**
**  AecUiPrEntitySetSingle::~AecUiPrEntitySetSingle
**
**  **jma
**
*************************************/

AecUiPrEntitySetSingle::~AecUiPrEntitySetSingle()
{
}

/****************************************************************************
**
**  AecUiPrEntitySetSingle::setAllowNone
**
**  **jma
**
*************************************/

void
AecUiPrEntitySetSingle::setAllowNone(Adesk::Boolean allowIt)
{
    m_allowNone = allowIt;
}

/****************************************************************************
**
**  AecUiPrEntitySetSingle::objectId
**
**  **jma
**
*************************************/

AcDbObjectId
AecUiPrEntitySetSingle::objectId() const
{
    if (m_selSet.isEmpty()) {
        AEC_ASSERT(0);
        return AcDbObjectId::kNull;
    }

    return m_selSet.first();
}

/****************************************************************************
**
**  AecUiPrEntitySetSingle::go
**
**  **jma
**
*************************************/

AecUiPrBase::Status
AecUiPrEntitySetSingle::go()
{
    m_selSet.setLogicalLength(0);   // reset to null set

    getLockedLayers();
    getAllowableClassTypes();

    if (verifyPickfirstSet(Adesk::kTrue))
        return AecUiPrBase::kOk;

    resbuf* filter = buildSelSetFilter();

    m_ss.setKeywordCallback(_DNT(_T("FIlter _ FIlter")), AecUiPrEntitySetSingle::keywordCallback);
    m_currentPromptObj = this;  // hack way to get back from keyword callback

    m_ss.setAllowSingleOnly(Adesk::kTrue, Adesk::kTrue);
    m_ss.setAllAtPickBox(Adesk::kTrue);     // enable selection of more than 1.  Filter will do the rest.  If not, it will work
                                            // like normal anyway by taking the first one and they can turn on object cycling
                                            // if they want to be exact.
    AecRmCString promptStr(message());
    AecAcadSelSet::SelSetStatus stat = AecAcadSelSet::kNone;
    while (1) {
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

        if (stat == AecAcadSelSet::kNone) {
            if (m_allowNone)
                break;
            else
                continue;
        }
        else
            break;
    }

    m_currentPromptObj = NULL;

    if (filter)
        ads_relrb(filter);

    if (stat != AecAcadSelSet::kSelected) {
        if (stat == AecAcadSelSet::kNone)
            return AecUiPrBase::kNone;
        else
            return AecUiPrBase::kCancel;
    }

    m_ss.asArray(m_selSet);

    if (m_selSet.isEmpty()) {
        AEC_ASSERT(0);      // should have return kNone already
        return AecUiPrBase::kCancel;
    }
    else
        return AecUiPrBase::kOk;
}

