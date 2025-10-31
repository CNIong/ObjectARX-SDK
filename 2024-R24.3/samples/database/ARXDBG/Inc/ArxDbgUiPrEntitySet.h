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

#ifndef AEC_AECUIPRENTITYSET_H
#define AEC_AECUIPRENTITYSET_H

#include "AecUiPrBase.h"
#include "AecAcadSelSet.h"

/****************************************************************************
**
**  CLASS AecUiPrEntitySet:
**
**  **jma
**
****************************/

class AecUiPrEntitySet : public AecUiPrBase {

public:
                                AecUiPrEntitySet();
                                AecUiPrEntitySet(LPCTSTR msg);
    virtual                     ~AecUiPrEntitySet();

    Acad::ErrorStatus           addAllowedClass(AcRxClass* classType, Adesk::Boolean doIsATest = Adesk::kFalse);

    Adesk::Boolean              filterLockedLayers() const;
    Acad::ErrorStatus           setFilterLockedLayers(Adesk::Boolean filterThem);

    Adesk::Boolean              disallowPickfirstSet() const;
    Acad::ErrorStatus           setDisallowPickfirstSet(Adesk::Boolean disallowIt);

    virtual Status              go();

    const AcDbObjectIdArray&    set();

        // overridden because this class does not support keywords
    virtual AecRmCString        keyWords() const;
    virtual Acad::ErrorStatus   setKeyWords(LPCTSTR keyWordList);

    virtual LPCTSTR             keyWordPicked();
    virtual Adesk::Boolean      isKeyWordPicked(LPCTSTR matchKeyWord);

protected:
        // data members
    AecAcadSelSet       m_ss;
    AcDbObjectIdArray   m_selSet;
    Adesk::Boolean      m_filterLockedLayers;
    AcDbVoidPtrArray    m_allowedClassTypes;
    AcDbIntArray        m_doIsATest;
    AcDbObjectIdArray   m_lockedLayerCache;
    CStringArray        m_lockedLayerNames;
    AcDbVoidPtrArray    m_classTypeCache;
    Adesk::Boolean      m_disallowPickfirstSet;

    void                getLockedLayers();
    void                getAllowableClassTypes();
    resbuf*             buildSelSetFilter();

    void                cleanPickfirstSet();
    Adesk::Boolean      verifyPickfirstSet(Adesk::Boolean singleSelect);
    Adesk::Boolean      isCorrectClassType(AcRxClass* classType);

    static struct resbuf*       keywordCallback(const TCHAR* str);
    static AecUiPrEntitySet*    m_currentPromptObj; // hack way to get back to object that set up above function pointer

private:
        // outlawed functions
                        AecUiPrEntitySet(const AecUiPrEntitySet&);
    AecUiPrEntitySet&   operator=(const AecUiPrEntitySet&);
};

#endif    // AEC_AECUIPRENTITYSET_H

