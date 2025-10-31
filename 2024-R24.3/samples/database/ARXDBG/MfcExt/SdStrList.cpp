//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "SdStrList.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**    SdStrList::GetAtIndex
**
**    **jma
**
*************************************/

BOOL
SdStrList::GetAtIndex(int index, CString& str)const
{
    POSITION pos = FindIndex(index);
    if (pos) {
        str = GetAt(pos);
        return(TRUE);
    }
    else
        return(FALSE);
}

/****************************************************************************
**
**    SdStrList::FindNoCase
**        find without regard to case sesitivity.  This function was taken from
**    the MFC source and modified to call a different string compare function.
**
**    **jma
**
*************************************/

POSITION
SdStrList::FindNoCase(LPCTSTR searchValue, POSITION startAfter) const
{
    ASSERT_VALID(this);

    CNode* pNode = (CNode*) startAfter;
    if (pNode == NULL) {
        pNode = m_pNodeHead;  // start at head
    }
    else {
        ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
        pNode = pNode->pNext;  // start after the one specified
    }

    for (; pNode != NULL; pNode = pNode->pNext)
        if (pNode->data.CompareNoCase(searchValue) == 0)
            return (POSITION) pNode;
    return NULL;
}




/****************************************************************************
**
**    SdSortedStrList::SdSortedStrList
**
**    **jma
**
*************************************/

SdSortedStrList::SdSortedStrList(BOOL caseSensitive)
:    m_caseSensitive(caseSensitive)
{
}

/****************************************************************************
**
**    SdSortedStrList::Insert
**
**    **jma
**
*************************************/

POSITION
SdSortedStrList::Insert(const CString& str)
{
    CString tmpStr;
    POSITION pos = GetHeadPosition();

    if (!m_caseSensitive) {
        while (pos != NULL) {
            tmpStr = GetAt(pos);
            if (tmpStr.CompareNoCase(str) > 0)
                return(InsertBefore(pos, str));
            GetNext(pos);
        }
    }
    else {
        while (pos != NULL) {
            tmpStr = GetAt(pos);
            if (tmpStr.Compare(str) > 0)
                return(InsertBefore(pos, str));
            GetNext(pos);
        }
    }
    return(AddTail(str));
}


/****************************************************************************
**
**    SdStrListIterator::SdStrListIterator
**
**    **jma
**
*************************************/

SdStrListIterator::SdStrListIterator(const CStringList& strList)
:    m_strList(strList)
{
    m_pos = m_strList.GetHeadPosition();
}


