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

