//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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

#ifndef ARXDBGKEYWORDARRAY_H
#define ARXDBGKEYWORDARRAY_H

/****************************************************************************
**
**  ArxDbgKeywordInfo::ArxDbgKeywordInfo
**
**  **jma
**
*************************************/

class ArxDbgKeywordInfo {

public:
                        ArxDbgKeywordInfo(const CString& localKword,
                                       const CString& globalKword,
                                       const CString& optionStr);
    virtual             ~ArxDbgKeywordInfo();

    const CString&	localKeyword() const;
    void            setLocalKeyword(const CString& kword);

    const CString&	globalKeyword() const;
    void            setGlobalKeyword(const CString& kword);

    const CString&	optionStr() const;
    void            setOptionStr(const CString& str);

    bool			isVisible() const;
    void            setIsVisible(bool itIs);

    bool			isEnabled() const;
    void            setIsEnabled(bool itIs);

    bool			isDefault() const;
    void            setIsDefault(bool itIs);

private:
        // data members
    CString     m_localKword;
    CString     m_globalKword;
    CString     m_optionStr;
    bool	    m_isVisible;
    bool		m_isEnabled;
    bool		m_isDefault;
};


/****************************************************************************
**
**  ArxDbgKeywordArray::ArxDbgKeywordArray
**
**  **jma
**
*************************************/

class ArxDbgKeywordArray {

public:
                    ArxDbgKeywordArray(HINSTANCE resDllInstance);
    virtual         ~ArxDbgKeywordArray();

    int             count() const;

        // standard way to append keywords as long as the keyword
        // is the same as the option you want displayed
    void            append(LPCTSTR localKword, LPCTSTR globalKword,
                                    bool isVisible = true,
                                    bool isEnabled = true);

    void            append(UINT localKwordResId, LPCTSTR globalKword,
                                    bool isVisible = true,
                                    bool isEnabled = true);

        // use this form if the option to be displayed must vary from
        // they keyword itself.  E.g., it has two words in it.
    void            append(LPCTSTR localKword, LPCTSTR globalKword,
                                    LPCTSTR optionStr,
                                    bool isVisible = true,
                                    bool isEnabled = true);
    void            append(UINT localKwordResId, LPCTSTR globalKword,
                                    UINT optionStrId,
                                    bool isVisible = true,
                                    bool isEnabled = true);

    void            deleteAll();

    ArxDbgKeywordInfo* getAt(int index);

    bool		    find(LPCTSTR kwordPicked, int& indexFoundAt);
    bool			findByJigIndex(int jigIndex, int& actualIndex);

        // pass in -1, -1 for start/end index to get all
    void            setVisible(bool isVisible, int startIndex, int endIndex);
    void            setEnabled(bool isEnabled, int startIndex, int endIndex);

    void            setAsDefault(int index);

    void            makeKeywordList(CString& str);
    void            makeOptionsList(CString& optionsStr);
    void            makeOptionsList(CString& optionsStr, CString& defaultStr, bool includeDefInOptions);

private:
        // data members
    HINSTANCE			m_resDllHandle;
    AcDbVoidPtrArray	m_keywordArray;

        // helper functions
    bool      getActualIndexRange(int& startIndex, int& endIndex);
};

#endif  // ARXDBGKEYWORDARRAY_H


