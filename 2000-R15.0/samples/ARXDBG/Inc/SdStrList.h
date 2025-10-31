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

#ifndef ARXDBG_SDSTRLIST_H
#define ARXDBG_SDSTRLIST_H


/****************************************************************************
**
**    CLASS SdStrList:
**        Abstract base class for a list of strings.  It inherits for CStringList
**    so that we can add a few useful functions and can work on Alphabetized and
**    non-alphabetized lists without functions having to know whether they are
**    supposed to insert in order or not. You can use all the striaght MFC calls
**    to CStringList, but if use SdStrList::Insert() it will either call AddTail()
**    or Insert alphabetically, depending on what the derived class is.
**
**    **jma
**
*************************************/

class SdStrList : public CStringList {

public:
        // constructors/destructors
                SdStrList()        {};
    virtual        ~SdStrList()    {};

    virtual POSITION    Insert(const CString& str)    = 0;
    virtual BOOL        GetAtIndex(int index, CString& str) const;
    virtual POSITION    FindNoCase(LPCTSTR searchValue, POSITION startAfter = NULL) const;
};


/****************************************************************************
**
**    CLASS SdUnsortedStrList:
**        Insert function does not sort alphabetically
**
**    **jma
**
*************************************/

class SdUnsortedStrList : public SdStrList {

public:
        // constructors/destructors
                SdUnsortedStrList()        {};
    virtual        ~SdUnsortedStrList()    {};

        // overridden from SdStrList
    virtual POSITION    Insert(const CString& str) { return(AddTail(str)); }
};


/****************************************************************************
**
**    CLASS SdSortedStrList:
**        Insert function does sort alphabetically
**
**    **jma
**
*************************************/

class SdSortedStrList : public SdStrList {

public:
        // constructors/destructors
                SdSortedStrList(BOOL caseSensitive = FALSE);
    virtual        ~SdSortedStrList()    {};

        // overridden from SdStrList
    virtual POSITION    Insert(const CString& str);

private:
        // data members
    BOOL    m_caseSensitive;
};

/****************************************************************************
**
**    CLASS SdStrListIterator:
**        can be used on a straight MFC CStringList or on one of our derived
**    classes.
**
**    **jma
**
*************************************/

class SdStrListIterator {

public:
        // constructors/destructor
                SdStrListIterator(const CStringList& strList);
    virtual        ~SdStrListIterator()    {};

    virtual void        toFirst()        { m_pos = m_strList.GetHeadPosition(); }
    virtual void        toLast()        { m_pos = m_strList.GetTailPosition(); }
    virtual void        previous()        { m_strList.GetPrev(m_pos); }
    virtual void        next()            { m_strList.GetNext(m_pos); }
    virtual CString        item() const    { return(m_strList.GetAt(m_pos)); }
    virtual BOOL        done() const    { return(m_pos == NULL); }

private:
        // data members
    POSITION            m_pos;
    const CStringList&    m_strList;

        // outlawed functions    (for now)
                        SdStrListIterator(const SdStrListIterator&);
    SdStrListIterator&    operator=(const SdStrListIterator&);
};


//////////////////////////////////////////////////////////////////////////////
///// GLOBAL UTILITY FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

inline LPCTSTR
asConstChar(const CString& str)
{
    return(static_cast<LPCTSTR>(str));
}



#endif    // ARXDBG_SDSTRLIST_H
