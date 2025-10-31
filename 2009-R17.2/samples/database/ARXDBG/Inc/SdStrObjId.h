//
// (C) Copyright 1998-2007 by Autodesk, Inc. 
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

#ifndef ARXDBG_SDSTROBJID_H
#define ARXDBG_SDSTROBJID_H

/****************************************************************************
**
**    CLASS SdStrObjIdNode:
**
**    **jma
**
*************************************/

class SdStrObjIdNode {

friend class SdStrObjIdList;
friend class SdStrObjIdListIterator;

private:
    // constructors/destructors
    SdStrObjIdNode(LPCTSTR name, const AcDbObjectId& objId);

    // data members
    CString            m_name;
    AcDbObjectId    m_objid;

        // outlawed functions
    SdStrObjIdNode(const SdStrObjIdNode& copy);
    SdStrObjIdNode&  operator=(const SdStrObjIdNode& copy);
};

/****************************************************************************
**
**    CLASS SdStrObjIdList:
**
**    **jma
**
*************************************/

class SdStrObjIdList {

friend class SdStrObjIdListIterator;    // allow direct access to underlying list

public:
        // constructors/destructors
            SdStrObjIdList(BOOL caseSensitive = TRUE);
    virtual    ~SdStrObjIdList();

    // operations
    int Count() const { 
        // 64Bit: I don't think we'll ever need THAT many (2 billion) 
        // objects, especially in samples (this class isn't used any-
        // where else). Keep it as it is for now until I hear shouting.
        return AcIntPtrToInt(m_list.GetCount()); 
    }
    virtual POSITION    AddHead(LPCTSTR str, const AcDbObjectId& objId);
    virtual POSITION    AddTail(LPCTSTR str, const AcDbObjectId& objId);
    virtual POSITION    AddAlpha(LPCTSTR str, const AcDbObjectId& objId);
    virtual BOOL        GetAtIndex(int index, CString& str, AcDbObjectId& objId) const;
    virtual BOOL        GetIndexFor(const CString& str, int& index) const;
    virtual BOOL        GetIndexFor(const AcDbObjectId& objId, int& index) const;
    virtual BOOL        GetMatchFor(const AcDbObjectId& objId, CString& str) const;
    virtual BOOL        GetMatchFor(const CString& str, AcDbObjectId& objId) const;
    virtual BOOL        Rename(const CString& oldName, const CString& newName);
    virtual void        RemoveAt(int index);
    virtual void        RemoveAll();

private:
        // data members
    CPtrList    m_list;
    BOOL        m_caseSensitive;


        // outlawed functions
                    SdStrObjIdList(const SdStrObjIdList&);
    SdStrObjIdList&    operator=(const SdStrObjIdList&);
};

/****************************************************************************
**
**    CLASS SdStrObjIdListIterator:
**
**    **jma
**
*************************************/

class SdStrObjIdListIterator {

public:
    // constructors/destructor
    SdStrObjIdListIterator(const SdStrObjIdList& list);
    virtual         ~SdStrObjIdListIterator()    {};

    virtual void    toFirst()        { m_pos = m_list.GetHeadPosition(); }
    virtual void    toLast()        { m_pos = m_list.GetTailPosition(); }
    virtual void    previous()        { m_list.GetPrev(m_pos); }
    virtual void    next()            { m_list.GetNext(m_pos); }
    virtual void    item(CString& name, AcDbObjectId& objId) const;
    virtual BOOL    done() const    { return(m_pos == NULL); }

private:
        // data members
    POSITION                m_pos;
    const CPtrList&         m_list;

        // outlawed functions    (for now)
                            SdStrObjIdListIterator(const SdStrObjIdListIterator&);
    SdStrObjIdListIterator&    operator=(const SdStrObjIdListIterator&);
};




#endif    // ARXDBG_SDSTROBJID_H
