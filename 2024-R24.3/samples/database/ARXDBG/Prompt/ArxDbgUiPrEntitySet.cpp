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

#include "AecUiPrEntitySet.h"
#include "AecBaseEditorReactor.h"
#include "AecUiBaseServices.h"
#include "AecUiBaseApp.h"
#include "Res_AecUiBase.h"



// A class static to get back to the object that provided the function pointer
// to ssget(). I can't figure out how to get the compiler to accept a function
// pointer to a non-static class member, so this is the only way I could think
// of to deal with it. This is set in go() immediately before the call to ssget,
// and reset to NULL immediately after, so there shouldn't be any re-entrancy
// or sharing problems. (jma - 5/6/98)
AecUiPrEntitySet*    AecUiPrEntitySet::m_currentPromptObj = NULL;

/****************************************************************************
**
**  AecUiPrEntitySet::AecUiPrEntitySet
**
**  **jma
**
*************************************/

AecUiPrEntitySet::AecUiPrEntitySet()
:   AecUiPrBase(_DNT(_T("")), NULL),
    m_filterLockedLayers(Adesk::kFalse),
    m_disallowPickfirstSet(Adesk::kFalse)
{
}

/****************************************************************************
**
**  AecUiPrEntitySet::AecUiPrEntitySet
**
**  **jma
**
*************************************/

AecUiPrEntitySet::AecUiPrEntitySet(LPCTSTR msg)
:   AecUiPrBase(msg, NULL),
    m_filterLockedLayers(Adesk::kFalse),
    m_disallowPickfirstSet(Adesk::kFalse)
{
}

/****************************************************************************
**
**  AecUiPrEntitySet::~AecUiPrEntitySet
**
**  **jma
**
*************************************/

AecUiPrEntitySet::~AecUiPrEntitySet()
{
}

/****************************************************************************
**
**  AecUiPrEntitySet::addAllowedClass
**
**  **jma
**
*************************************/

Acad::ErrorStatus
AecUiPrEntitySet::addAllowedClass(AcRxClass* classType, Adesk::Boolean doIsATest)
{
    AEC_ASSERT(classType != NULL);

    if (m_allowedClassTypes.contains(classType))
        return Acad::eDuplicateKey;

    m_allowedClassTypes.append(classType);
    m_doIsATest.append(static_cast<int>(doIsATest));

    return Acad::eOk;
}

/****************************************************************************
**
**  AecUiPrEntitySet::filterLockedLayers
**
**  **jma
**
*************************************/

Adesk::Boolean
AecUiPrEntitySet::filterLockedLayers() const
{
    return m_filterLockedLayers;
}

/****************************************************************************
**
**  AecUiPrEntitySet::setFilterLockedLayers
**
**  **jma
**
*************************************/

Acad::ErrorStatus
AecUiPrEntitySet::setFilterLockedLayers(Adesk::Boolean filterThem)
{
    m_filterLockedLayers = filterThem;

    return Acad::eOk;
}

/****************************************************************************
**
**  AecUiPrEntitySet::disallowPickfirstSet
**
**  **jma
**
*************************************/

Adesk::Boolean
AecUiPrEntitySet::disallowPickfirstSet() const
{
    return m_disallowPickfirstSet;
}

/****************************************************************************
**
**  AecUiPrEntitySet::setDisallowPickfirstSet
**
**  **jma
**
*************************************/

Acad::ErrorStatus
AecUiPrEntitySet::setDisallowPickfirstSet(Adesk::Boolean disallowIt)
{
    m_disallowPickfirstSet = disallowIt;

    return Acad::eOk;
}

/****************************************************************************
**
**  AecUiPrEntitySet::cleanPickfirstSet
**
**  **jma
**
*************************************/

void
AecUiPrEntitySet::cleanPickfirstSet()
{
        // hack to wipe out the pickfirst set.
    ads_name junk1, junk2;
    junk1[0] = junk1[1] = junk2[0] = junk2[1] = 0L;
    ads_sssetfirst(junk1, junk2);
}

/****************************************************************************
**
**  AecUiPrEntitySet::verifyPickfirstSet
**
**  **jma
**
*************************************/

Adesk::Boolean
AecUiPrEntitySet::verifyPickfirstSet(Adesk::Boolean singleSelect)
{
    if (m_disallowPickfirstSet) {
        cleanPickfirstSet();
        return Adesk::kFalse;
    }

        // if the set is already selected, verify that it has
        // the right stuff in it.
    AecBaseEditorReactor* edReact = AecUiBaseServices::getEditorReactor();
    if (edReact == NULL) {
        AEC_ASSERT(0);
        cleanPickfirstSet();
        return Adesk::kFalse;
    }

    m_selSet.setLogicalLength(0);   // reset to null set

    AcDbEntity* ent;
    Acad::ErrorStatus es;
    int filteredBecauseOfClass = 0;
    int filteredBecauseOfLockedLayer = 0;

    const AcDbObjectIdArray& pickSet = edReact->pickfirstSet();
    int len = pickSet.length();

        // if only allowing single select, bail if more than 1 item
        // in the pickfirst set.
    if (singleSelect && (len > 1)) {
        ads_printf(_DNT(_T("\n"))); // make sure we get to a new line
        AecRmCString tmpStr(GetAecUiBaseAppName(), AECU_STR_VERIFYPICKFIRSTSET_AECUIPRENTITYSET_TOO_MANY_OBJECTS, TRUE);
        ads_printf(tmpStr);        //~  "Too many objects in the pickfirst set, please select again.\n"
        cleanPickfirstSet();
        return Adesk::kFalse;
    }

    for (int i=0; i<len; i++) {
        es = acdbOpenAcDbEntity(ent, pickSet[i], AcDb::kForRead);
        if (es == Acad::eOk) {
            if (isCorrectClassType(ent->isA()) == Adesk::kFalse) {
                filteredBecauseOfClass++;
                ent->close();
                continue;
            }
            if (m_filterLockedLayers && m_lockedLayerCache.contains(ent->layerId())) {
                filteredBecauseOfLockedLayer++;
                ent->close();
                continue;
            }

            ent->close();
            m_selSet.append(pickSet[i]);
        }
        else {
            Aec::ads_printf(GetAecUiBaseAppName(), AECU_STR_VERIFYPICKFIRSTSET_AECUIPRENTITYSET_COULD_NOT_OPEN_ENTITY_FOR_READ, Aec::rxErrorStr(es)); //~ "\nCould not open entity for read: %s"
        }
    }

    ads_printf(_DNT(_T("\n"))); // make sure we get to a new line

    if (filteredBecauseOfClass == 1) {
        AecRmCString tmpStr(GetAecUiBaseAppName(), AECU_STR_VERIFYPICKFIRSTSET_AECUIPRENTITYSET_OBJECT_WAS, TRUE);
        ads_printf(tmpStr);    // NOTE: leave \n's at end so you can see message before dialog comes up (jma)        //~  "1 object was of the wrong type.\n"
    }
    else if (filteredBecauseOfClass > 1) {
        Aec::ads_printf(GetAecUiBaseAppName(), AECU_STR_VERIFYPICKFIRSTSET_AECUIPRENTITYSET_OBJECTS_WERE_OF_THE_WRONG_TYPE, filteredBecauseOfClass); //~ "%ld objects were of the wrong type.\n"
    }

    if (filteredBecauseOfLockedLayer == 1) {
        AecRmCString tmpStr(GetAecUiBaseAppName(), AECU_STR_VERIFYPICKFIRSTSET_AECUIPRENTITYSET_OBJECT_WAS_0, TRUE);
        ads_printf(tmpStr);        //~  "1 object was on a locked layer.\n"
    }
    else if (filteredBecauseOfLockedLayer > 1) {
        Aec::ads_printf(GetAecUiBaseAppName(), AECU_STR_VERIFYPICKFIRSTSET_AECUIPRENTITYSET_OBJECTS_WERE_ON_LOCKED_LAYER, filteredBecauseOfLockedLayer); //~"%ld objects were on a locked layer.\n"
    }

    if ((len > 0) && m_selSet.isEmpty()) {
        AecRmCString tmpStr(GetAecUiBaseAppName(), AECU_STR_VERIFYPICKFIRSTSET_AECUIPRENTITYSET_ALL_OBJECTS_IN, TRUE);
        ads_printf(tmpStr);        //~  "All objects in the pickfirst set were filtered out, please select again.\n"
    }

    cleanPickfirstSet();

    return !m_selSet.isEmpty();
}

/****************************************************************************
**
**  AecUiPrEntitySet::go
**
**  **jma
**
*************************************/

AecUiPrBase::Status
AecUiPrEntitySet::go()
{
    m_selSet.setLogicalLength(0);   // reset to null set

    getLockedLayers();
    getAllowableClassTypes();

    if (verifyPickfirstSet(Adesk::kFalse))
        return AecUiPrBase::kOk;

    resbuf* filter = buildSelSetFilter();

    m_ss.setKeywordCallback(_DNT(_T("FIlter _ FIlter")), AecUiPrEntitySet::keywordCallback);
    m_currentPromptObj = this;  // hack way to get back from keyword callback

    AecAcadSelSet::SelSetStatus stat;

        // if supplied prompt, pass it on to selection set
    AecRmCString promptStr(message());
    if (promptStr.IsEmpty() == FALSE) {
        AecRmCString tmpPrompt;
        tmpPrompt.Format(_DNT(_T("\n%s: ")), static_cast<LPCTSTR>(promptStr));
        stat = m_ss.userSelect(tmpPrompt, NULL, filter);
    }
        // no prompt supplied, use regular ssget prompts
    else {
        stat = m_ss.userSelect(filter);
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
        return AecUiPrBase::kNone;
    }
    else
        return AecUiPrBase::kOk;
}

/****************************************************************************
**
**  AecUiPrEntitySet::set
**
**  **jma
**
*************************************/

const AcDbObjectIdArray&
AecUiPrEntitySet::set()
{
    return m_selSet;
}

/****************************************************************************
**
**  AecUiPrEntitySet::getLockedLayers
**
**  **jma
**
*************************************/

void
AecUiPrEntitySet::getLockedLayers()
{
    m_lockedLayerCache.setLogicalLength(0);
    m_lockedLayerNames.RemoveAll();

    if (m_filterLockedLayers == Adesk::kFalse)
        return;

    AcDbLayerTableRecord* layer;
    const TCHAR* tmpName;

    AcDbLayerTable* layTbl;
	Acad::ErrorStatus es = acdbHostApplicationServices()->workingDatabase()->getSymbolTable(layTbl, AcDb::kForRead);
	if (es == Acad::eOk) {
        AcDbLayerTableIterator* tblIter;
        if (layTbl->newIterator(tblIter) == Acad::eOk) {
            for (; !tblIter->done(); tblIter->step()) {
                es = tblIter->getRecord(layer, AcDb::kForRead);
                if (es == Acad::eOk) {
                    if (layer->isLocked()) {
                        m_lockedLayerCache.append(layer->objectId());

                        es = layer->getName(tmpName);
                        if (es == Acad::eOk) {
                            m_lockedLayerNames.Add(tmpName);
                        }
                        else {
                            AEC_ASSERT(0);
                            m_lockedLayerNames.Add(_DNT(_T("")));   // have to keep balanced
                        }
                    }

                    layer->close();
                }
            }
            delete tblIter;
        }
        else {
            AEC_ASSERT(0);
        }

        layTbl->close();
    }
}

/****************************************************************************
**
**  AecUiPrEntitySet::getAllowableClassTypes
**
**  **jma
**
*************************************/

void
AecUiPrEntitySet::getAllowableClassTypes()
{
    ASSERT(m_allowedClassTypes.length() == m_doIsATest.length());

    m_classTypeCache = m_allowedClassTypes;     // copy over all the definite classes that are ok

    AcRxDictionaryIterator* iter;
    AcRxDictionary* classDict = acrxClassDictionary;
    if (classDict == NULL) {
        AEC_ASSERT(0);
        return;
    }

    int len = m_doIsATest.length();
    for (int i=0; i<len; i++) {
            // if not doing isA() testing, must get all classes derived from
            // this one.
        if (m_doIsATest[i] == Adesk::kFalse) {
            iter = classDict->newIterator();
            if (iter != NULL) {
                    // iterate over each item and get its info
                AcRxObject* classDictItem;
                AcRxClass* classObj;

                for (; !iter->done(); iter->next()) {
                    classDictItem = iter->object();
                    if ((classObj = AcRxClass::cast(classDictItem)) != NULL) {
                        if (classObj->isDerivedFrom(static_cast<AcRxClass*>(m_allowedClassTypes[i]))) {
                            if (m_classTypeCache.contains(classObj) == Adesk::kFalse) {
                                m_classTypeCache.append(classObj);
                            }
                        }
                    }
                    else {
                        AEC_ASSERT(0);
                    }
                }
                delete iter;
            }
            else {
                AEC_ASSERT(0);
            }
        }
    }
}

/****************************************************************************
**
**  AecUiPrEntitySet::isCorrectClassType
**
**  **jma
**
*************************************/

Adesk::Boolean
AecUiPrEntitySet::isCorrectClassType(AcRxClass* classType)
{
    if (m_classTypeCache.isEmpty() || m_classTypeCache.contains(classType))
        return Adesk::kTrue;
    else
        return Adesk::kFalse;
}

/****************************************************************************
**
**  AecUiPrEntitySet::buildSelSetFilter
**
**  **jma
**
*************************************/

resbuf*
AecUiPrEntitySet::buildSelSetFilter()
{
    if ((m_lockedLayerNames.GetSize() == 0) && m_classTypeCache.isEmpty())
        return NULL;

    AecResbufList rbList;

    resbuf* tmpRb;

    if (m_classTypeCache.isEmpty() == Adesk::kFalse) {
        tmpRb = acutNewRb(-4);
        newString(_DNT(_T("<or")), tmpRb->resval.rstring);
        rbList.addTail(tmpRb);

        const TCHAR* dxfStr;
        int len = m_classTypeCache.length();
        for (int i=0; i<len; i++) {
            dxfStr = static_cast<AcRxClass*>(m_classTypeCache[i])->dxfName();
            if (dxfStr) {
                tmpRb = acutNewRb(0);
                newString(dxfStr, tmpRb->resval.rstring);
                rbList.addTail(tmpRb);
            }
            //else {
                //AEC_ASSERT(0);    // can't assert because AcDbCurve has no DXF name
            //}
        }

        tmpRb = acutNewRb(-4);
        newString(_DNT(_T("or>")), tmpRb->resval.rstring);
        rbList.addTail(tmpRb);
    }

    int len = m_lockedLayerNames.GetSize();
    if (len > 0) {
        tmpRb = acutNewRb(-4);
        newString(_DNT(_T("<not")), tmpRb->resval.rstring);
        rbList.addTail(tmpRb);

        tmpRb = acutNewRb(-4);
        newString(_DNT(_T("<or")), tmpRb->resval.rstring);
        rbList.addTail(tmpRb);

        for (int i=0; i<len; i++) {
            if (m_lockedLayerNames[i].IsEmpty() == FALSE) {
                tmpRb = acutNewRb(8);
                newString(m_lockedLayerNames[i], tmpRb->resval.rstring);
                rbList.addTail(tmpRb);
            }
            else {
                AEC_ASSERT(0);
            }
        }

        tmpRb = acutNewRb(-4);
        newString(_DNT(_T("or>")), tmpRb->resval.rstring);
        rbList.addTail(tmpRb);

        tmpRb = acutNewRb(-4);
        newString(_DNT(_T("not>")), tmpRb->resval.rstring);
        rbList.addTail(tmpRb);
    }

    return rbList.orphanData();
}

/****************************************************************************
**
**  AecUiPrEntitySet::keywordCallback
**
**  **jma
**
*************************************/

struct resbuf*
AecUiPrEntitySet::keywordCallback(const TCHAR* str)
{
    if (AecUiPrEntitySet::m_currentPromptObj == NULL) {
        AEC_ASSERT(0);
        return NULL;
    }

    AecRmCString tmpStr;
    AecRmCString tmpStr2(GetAecUiBaseAppName(), AECU_STR_KEYWORDCALLBACK_AECUIPRENTITYSET_FILTERS, TRUE);
    AecRmCString tmpStr3(GetAecUiBaseAppName(), AECU_STR_KEYWORDCALLBACK_AECUIPRENTITYSET_ALLOWED_OBJECT, TRUE);

    ads_printf(tmpStr2);        //~  "\nFILTERS:"
    Aec::ads_printf(GetAecUiBaseAppName(), AECU_STR_KEYWORDCALLBACK_AECUIPRENTITYSET_LOCKED_LAYERS,       //~ "\n  Locked Layers:        %s"
            Aec::booleanToStr(AecUiPrEntitySet::m_currentPromptObj->m_filterLockedLayers, tmpStr));
    ads_printf(tmpStr3);        //~  "\n  Allowed Object Types:"

    int len = AecUiPrEntitySet::m_currentPromptObj->m_classTypeCache.length();
    if (len == 0) {
        AecRmCString tmpStr4(GetAecUiBaseAppName(), AECU_STR_KEYWORDCALLBACK_AECUIPRENTITYSET_ALL_ENTITIES, TRUE);
        ads_printf(tmpStr4);    //~  "\n    All entities allowed."
    }
    else {
        AcRxClass* classType;
        for (int i=0; i<len; i++) {
            classType = static_cast<AcRxClass*>(AecUiPrEntitySet::m_currentPromptObj->m_classTypeCache[i]);
            ads_printf(_DNT(_T("\n    %s")), classType->name());
        }
    }

    ads_printf(_DNT(_T("\n")));

    return NULL;
}

/****************************************************************************
**
**  AecUiPrEntitySet::keyWords
**
**  **jma
**
*************************************/

AecRmCString
AecUiPrEntitySet::keyWords() const
{
    return _DNT(_T(""));
}

/****************************************************************************
**
**  AecUiPrEntitySet::setKeyWords
**
**  **jma
**
*************************************/

Acad::ErrorStatus
AecUiPrEntitySet::setKeyWords(LPCTSTR keyWordList)
{
    return Acad::eNotApplicable;
}

/****************************************************************************
**
**  AecUiPrEntitySet::keyWordPicked
**
**  **jma
**
*************************************/

LPCTSTR
AecUiPrEntitySet::keyWordPicked()
{
    return NULL;
}

/****************************************************************************
**
**  AecUiPrEntitySet::isKeyWordPicked
**
**  **jma
**
*************************************/

Adesk::Boolean
AecUiPrEntitySet::isKeyWordPicked(LPCTSTR matchKeyWord)
{
    return Adesk::kFalse;
}



