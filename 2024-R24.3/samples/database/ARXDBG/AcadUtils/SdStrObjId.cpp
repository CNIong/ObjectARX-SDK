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

#include "SdStrObjId.h"




/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// SdStrObjIdNode //////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**    SdStrObjIdNode::SdStrObjIdNode (constructor)
**
**    **jma
**
*************************************/

SdStrObjIdNode::SdStrObjIdNode(LPCTSTR name, const AcDbObjectId& objId)
:    m_name(name),
    m_objid(objId)
{
}


/////////////////////////////////////////////////////////////////////////////
///////////////////////////// SdStrObjIdList ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**    SdStrObjIdList::SdStrObjIdList(constructor)
**
**    **jma
**
*************************************/

SdStrObjIdList::SdStrObjIdList(BOOL caseSensitive)
:    m_caseSensitive(caseSensitive)
{
}

/****************************************************************************
**
**    SdStrObjIdList::~SdStrObjIdList (destructor)
**
**    **jma
**
*************************************/

SdStrObjIdList::~SdStrObjIdList()
{
    RemoveAll();
}

/****************************************************************************
**
**    SdStrObjIdList::AddAlpha
**
**    **jma
**
*************************************/

void
SdStrObjIdList::RemoveAll()
{
    SdStrObjIdNode* nodePtr;

    POSITION pos = m_list.GetHeadPosition();
    while(pos != NULL){
        nodePtr = static_cast<SdStrObjIdNode*>(m_list.GetNext(pos));
        delete nodePtr;
    }
    m_list.RemoveAll();
}

/****************************************************************************
**
**    SdStrObjIdList::AddAlpha
**
**    **jma
**
*************************************/

POSITION
SdStrObjIdList::AddAlpha(LPCTSTR name, const AcDbObjectId& objId)
{
    SdStrObjIdNode* newNode = new SdStrObjIdNode(name, objId);
    SdStrObjIdNode* tmpNode;

    POSITION pos = m_list.GetHeadPosition();

    if (!m_caseSensitive) {
        while (pos != NULL) {
            tmpNode = static_cast<SdStrObjIdNode*>(m_list.GetAt(pos));
            if (tmpNode && (tmpNode->m_name.CompareNoCase(name) > 0))
                return(m_list.InsertBefore(pos, static_cast<void*>(newNode)));
            m_list.GetNext(pos);
        }
    }
    else {
        while (pos != NULL) {
            tmpNode = static_cast<SdStrObjIdNode*>(m_list.GetAt(pos));
            if (tmpNode && (tmpNode->m_name.Compare(name) > 0))
                return(m_list.InsertBefore(pos, static_cast<void*>(newNode)));
            m_list.GetNext(pos);
        }
    }
    return(m_list.AddTail(static_cast<void*>(newNode)));
}

/****************************************************************************
**
**    SdStrObjIdList::AddHead
**
**    **jma
**
*************************************/

POSITION
SdStrObjIdList::AddHead(LPCTSTR name, const AcDbObjectId& objId)
{
    SdStrObjIdNode* newNode = new SdStrObjIdNode(name, objId);
    return(m_list.AddHead(static_cast<void*>(newNode)));
}

/****************************************************************************
**
**    SdStrObjIdList::AddTail
**
**    **jma
**
*************************************/

POSITION
SdStrObjIdList::AddTail(LPCTSTR name, const AcDbObjectId& objId)
{
    SdStrObjIdNode* newNode = new SdStrObjIdNode(name, objId);
    return(m_list.AddTail(static_cast<void*>(newNode)));
}

/****************************************************************************
**
**    SdStrObjIdList::GetAtIndex
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::GetAtIndex(int index, CString& str, AcDbObjectId& objId) const
{
    POSITION pos = m_list.FindIndex(index);
    if (pos) {
        SdStrObjIdNode* node;
        node = (SdStrObjIdNode*)(m_list.GetAt(pos));
        str = node->m_name;
        objId = node->m_objid;
        return(TRUE);
    }
    else
        return(FALSE);
}

/****************************************************************************
**
**    SdStrObjIdList::GetIndexFor
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::GetIndexFor(const CString& str, int& index) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    SdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (str.CompareNoCase(tmpStr) == 0) {
            index = i;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    SdStrObjIdList::GetIndexFor
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::GetIndexFor(const AcDbObjectId& objId, int& index) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    SdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (tmpId == objId) {
            index = i;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    SdStrObjIdList::GetMatchFor
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::GetMatchFor(const CString& str, AcDbObjectId& objId) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    SdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (str.CompareNoCase(tmpStr) == 0) {
            objId = tmpId;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    SdStrObjIdList::GetMatchFor
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::GetMatchFor(const AcDbObjectId& objId, CString& str) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    SdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (tmpId == objId) {
            str = tmpStr;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    SdStrObjIdList::Rename
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::Rename(const CString& oldName, const CString& newName)
{
    SdStrObjIdNode* nodePtr;

    POSITION pos = m_list.GetHeadPosition();
    while (pos != NULL) {
        nodePtr = static_cast<SdStrObjIdNode*>(m_list.GetNext(pos));
        if (nodePtr->m_name == oldName) {
            nodePtr->m_name = newName;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**	SdStrObjIdList::RemoveAt
**
**	**jma
**
*************************************/

void
SdStrObjIdList::RemoveAt(int index)
{
    POSITION pos = m_list.FindIndex(index);
    if (pos) {
        SdStrObjIdNode* node;
        node = static_cast<SdStrObjIdNode*>(m_list.GetAt(pos));
        delete node;
        m_list.RemoveAt(pos);
    }
}

/****************************************************************************
**
**    SdStrObjIdListIterator::SdStrObjIdListIterator
**
**    **jma
**
*************************************/

SdStrObjIdListIterator::SdStrObjIdListIterator(const SdStrObjIdList& list)
:    m_list(list.m_list)
{
    m_pos = m_list.GetHeadPosition();
}

/****************************************************************************
**
**    SdStrObjIdListIterator::item
**
**    **jma
**
*************************************/

void
SdStrObjIdListIterator::item(CString& name, AcDbObjectId& objId) const
{
    SdStrObjIdNode* node;

    node = (SdStrObjIdNode*)(m_list.GetAt(m_pos));
    name = node->m_name;
    objId = node->m_objid;
}






