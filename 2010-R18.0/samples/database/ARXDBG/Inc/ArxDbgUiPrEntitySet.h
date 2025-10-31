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

