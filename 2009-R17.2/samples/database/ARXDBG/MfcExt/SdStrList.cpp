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


