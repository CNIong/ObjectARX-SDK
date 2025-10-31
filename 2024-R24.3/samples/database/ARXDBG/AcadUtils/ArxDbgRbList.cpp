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

#include "ArxDbgRbList.h"
#include "ArxDbgUtils.h"



/******************************************************************
**
**  ArxDbgRbList::addToEmptyList
**      Helper function for other add functions to handle
**  the special case of adding to an empty list.
**
**  **jma
**
****************************/

bool
ArxDbgRbList::addToEmptyList(resbuf* newNode)
{
    ASSERT(newNode != NULL);

    if (m_head == NULL) {
        m_head = newNode;
        m_tail = newNode;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxDbgRbList::ArxDbgRbList
**
**  **jma
**
*************************************/

ArxDbgRbList::ArxDbgRbList()
:   m_head(NULL),
    m_tail(NULL)
{
}

/****************************************************************************
**
**  ArxDbgRbList::ArxDbgRbList
**
**  **jma
**
*************************************/

ArxDbgRbList::ArxDbgRbList(resbuf* adoptedList)
{
    m_head = adoptedList;
    m_tail = tailOfResbufChain(m_head);
}

/****************************************************************************
**
**  ArxDbgRbList::ArxDbgRbList
**
**  **jma
**
*************************************/

ArxDbgRbList::ArxDbgRbList(const ArxDbgRbList& copyFrom)
{
    m_head = duplicateResbufChain(copyFrom.m_head);
    m_tail = tailOfResbufChain(m_head);
}

/****************************************************************************
**
**  ArxDbgRbList::~ArxDbgRbList
**
**  **jma
**
*************************************/

ArxDbgRbList::~ArxDbgRbList()
{
    if (m_head)
        acutRelRb(m_head);
}

/****************************************************************************
**
**  ArxDbgRbList::operator=
**
**  **jma
**
*************************************/

ArxDbgRbList&
ArxDbgRbList::operator=(const ArxDbgRbList& copyFrom)
{
        // check for self-assignment
    if (m_head == copyFrom.m_head)
        return *this;

    removeAll();
    m_head = duplicateResbufChain(copyFrom.m_head);
    m_tail = tailOfResbufChain(m_head);
    return *this;
}

/******************************************************************
**
**  ArxDbgRbList::addHead
**
**  **jma
**
****************************/

void
ArxDbgRbList::addHead(resbuf* newNode)
{
    ASSERT(newNode != NULL);

    if (addToEmptyList(newNode) == false) {
        newNode->rbnext = m_head;
        m_head = newNode;
    }
}

/******************************************************************
**
**  ArxDbgRbList::addTail
**
**  **jma
**
****************************/

void
ArxDbgRbList::addTail(resbuf* newNode)
{
    ASSERT(newNode != NULL);

    if (addToEmptyList(newNode) == false) {
        m_tail->rbnext = newNode;
        m_tail = newNode;
    }
}

/******************************************************************
**
**  ArxDbgRbList::append
**      append two rblists together, destroying the handle to
**  the second list.
**
**  **jma
**
****************************/

void
ArxDbgRbList::append(ArxDbgRbList& appendList)
{
        // NULL-OP if second list is NULL
    if (appendList.m_head == NULL)
        return;

        // EASY-OP if first list is NULL, switch head ptr
    if (m_head == NULL)
        m_head = appendList.m_head;
    else
        m_tail->rbnext = appendList.m_head;

    m_tail = appendList.m_tail;

        // The list has been handed over to list 1, so
        // reset member vars in list 2 to reflect the change.
    appendList.m_head = NULL;
    appendList.m_tail = NULL;
}

/******************************************************************
**
**  ArxDbgRbList::length
**
**  **jma
**
****************************/

int
ArxDbgRbList::length()
{
    int len = 0;
    resbuf* rb = m_head;
    while (rb) {
        len++;
        rb = rb->rbnext;
    }
    return len;
}

/******************************************************************
**
**  ArxDbgRbList::adoptData
**
**  **jma
**
****************************/

void
ArxDbgRbList::adoptData(resbuf* adoptedList)
{
    removeAll();    // remove any existing list
    m_head = adoptedList;
    m_tail = tailOfResbufChain(m_head);
}

/******************************************************************
**
**  ArxDbgRbList::orphanData
**
**  **jma
**
****************************/

resbuf*
ArxDbgRbList::orphanData()
{
    resbuf* rb = m_head;
    m_head = NULL;
    m_tail = NULL;
    return rb;
}

/******************************************************************
**
**  ArxDbgRbList::detach
**
**  **jma
**
****************************/

resbuf*
ArxDbgRbList::detach(resbuf* nodeToDel)
{
    ASSERT((m_head != NULL) && (nodeToDel != NULL));

        // trap for safety
    if ((m_head == NULL) || (nodeToDel == NULL))
        return NULL;

        // see if it is first on the list
    if (m_head == nodeToDel) {
        m_head = m_head->rbnext;
        nodeToDel->rbnext = NULL;
        if (m_head == NULL)
            m_tail = NULL;    // removed only element

        return nodeToDel;
    }
        // node is somewhere in the middle or end of the list
    resbuf* rb = m_head;
    while (rb->rbnext) {
        if (rb->rbnext == nodeToDel) {
            if (m_tail == nodeToDel)    // don't lose tail ptr
                m_tail = rb;

            rb->rbnext = nodeToDel->rbnext;
            nodeToDel->rbnext = NULL;
            return(nodeToDel);
        }
        rb = rb->rbnext;
    }
    ASSERT(rb != NULL);
    return NULL;
}

/******************************************************************
**
**  ArxDbgRbList::detach
**
**  **jma
**
****************************/

resbuf*
ArxDbgRbList::detach(resbuf* startPtr, resbuf* endPtr)
{
    ASSERT(m_head != NULL);
    ASSERT(startPtr != NULL);
    ASSERT(endPtr != NULL);

        // trap safety case
    if ((m_head == NULL) || (startPtr == NULL) || (endPtr == NULL))
        return NULL;

        // see if it is first on the list
    if (m_head == startPtr) {
        m_head = endPtr->rbnext;
        endPtr->rbnext = NULL;
        if (m_head == NULL)
            m_tail = NULL;    // removed only element

        return startPtr;
    }
        // node is somewhere in the middle or end of the list
    resbuf* rb = m_head;
    while (rb->rbnext) {
        if (rb->rbnext == startPtr) {
            if (m_tail == endPtr)    // don't lose tail ptr
                m_tail = rb;

            rb->rbnext = endPtr->rbnext;
            endPtr->rbnext = NULL;
            return startPtr;
        }
        rb = rb->rbnext;
    }
    ASSERT(rb != NULL);
    return NULL;
}

/******************************************************************
**
**  ArxDbgRbList::remove
**
**  **jma
**
****************************/

void
ArxDbgRbList::remove(resbuf* nodeToDel)
{
    resbuf* rb = detach(nodeToDel);
    if (rb)
        acutRelRb(rb);
}

/******************************************************************
**
**  ArxDbgRbList::removeAll
**      delete all elements of the list and ensure that the
**  member vars are updated to reflect the new state
**
**  **jma
**
****************************/

void
ArxDbgRbList::removeAll()
{
    if (m_head)
        acutRelRb(m_head);

    m_head = NULL;
    m_tail = NULL;
}



/////////////////////////////////////////////////////////////////////////
///////////////////  GENERIC FUNCTIONS ON RAW RESBUFS  //////////////////
/////////////////////////////////////////////////////////////////////////

/************************************************************************
**
**  dxfCodeToDataType:
**
**  **jma
**
******************************************/

int
dxfCodeToDataType(int resType)
{
        // which data type is this value
    if ((resType >= 0) && (resType <= 9))
        return RTSTR;
    else if ((resType >= 10) && (resType <= 17))
        return RT3DPOINT;
    else if ((resType >= 38) && (resType <= 59))
        return RTREAL;
    else if ((resType >= 60) && (resType <= 79))
        return RTSHORT;
    else if ((resType >= 90) && (resType <= 99))
        return RTLONG;
    else if ((resType == 100) || (resType == 101) || (resType == 102) ||(resType == 105))
        return RTSTR;
	  else if ((resType >= 110) && (resType <= 119))
		    return RT3DPOINT;
    else if ((resType >= 140) && (resType <= 149))
        return RTREAL;
    else if ((resType >= 170) && (resType <= 179))
        return RTSHORT;
    else if ((resType >= 210) && (resType <= 219))
        return RT3DPOINT;
    else if ((resType >= 270) && (resType <= 299))
        return RTSHORT;
    else if ((resType >= 300) && (resType <= 309))
        return RTSTR;
    else if ((resType >= 310) && (resType <= 369))
        return RTENAME;
    else if ((resType >= 370) && (resType <= 379))
        return RTSHORT;
    else if ((resType >= 380) && (resType <= 389))
        return RTSHORT;
    else if ((resType >= 390) && (resType <= 399))
        return RTENAME;
    else if ((resType >= 400) && (resType <= 409))
        return RTSHORT;
    else if ((resType >= 410) && (resType <= 419))
        return RTSTR;
    else if (resType == 1004)
        return resType;        // binary chunk
    else if ((resType >= 999) && (resType <= 1009))
        return RTSTR;
    else if ((resType >= 1010) && (resType <= 1013))
        return RT3DPOINT;
    else if ((resType >= 1038) && (resType <= 1059))
        return RTREAL;
    else if ((resType >= 1060) && (resType <= 1070))
        return RTSHORT;
    else if ((resType == 1071))
        return RTLONG;
    else if ((resType < 0) || (resType > 4999))
        return resType;
    else
        return RTNONE;
}

/**********************************************************************
**
**  bytesToHexStr:
**
**  **jma
**
*****************************************/

// Unicode: Leaving as char type because it is a buffer
LPCTSTR
bytesToHexStr(char* buffer, int len, CString& hexStr)
{
    // Unicode: Leaving as char type because it is a byte
    unsigned char k;
    int j;
    CString tmpStr;

    hexStr.Empty();    // make sure nothing in it yet since we are concatenating it

    for (j=0;j<len;j++) {
        k = static_cast<unsigned char>(buffer[j]);
        tmpStr.Format(_T("%02hX"), k);
        hexStr += tmpStr;
    }
    return hexStr;
}

/*********************************************************************
**
**  dxfToStr:
**
**  **jma
**
******************************************/

void
dxfToStr(const resbuf* rb, CString& dxfCodeStr, CString& valueStr)
{
    int dataType = dxfCodeToDataType(rb->restype);
    dxfCodeStr.Format(_T("%d"), rb->restype);

    CString tmpStr;

    switch (dataType) {
        case RTSHORT:
            valueStr.Format(_T("%d"), rb->resval.rint);
            break;
        case RTLONG:
            valueStr.Format(_T("%ld"), rb->resval.rlong);
            break;
        case RTREAL:
            valueStr.Format(_T("%g"), rb->resval.rreal);
            break;
        case RTSTR:
            if (rb->resval.rstring == NULL)
                valueStr = _T("(NULL)");
            else
                valueStr.Format(_T("\"%s\""), rb->resval.rstring);
            break;
        case RT3DPOINT:
            valueStr.Format(_T("(%g, %g, %g)"), rb->resval.rpoint[X],
                        rb->resval.rpoint[Y], rb->resval.rpoint[Z]);
            break;
        case RTPOINT:
            valueStr.Format(_T("(%g, %g)"), rb->resval.rpoint[X], rb->resval.rpoint[Y]);
            break;
        case 1004:
            valueStr.Format(_T("Binary Chunk: \"%s\""),
                        bytesToHexStr(rb->resval.rbinary.buf,
                                rb->resval.rbinary.clen, tmpStr));
            break;
        case -6:
            valueStr = _T("Extension Dictionary");
            break;
        case -5:
            valueStr = _T("Persistent Reactors");
            break;
        case -4:
            valueStr.Format(_T("Conditional Operator: \"%s\""), rb->resval.rstring);
            break;
        case -3:
            valueStr = _T("Start of Xdata");
            break;
        case -2:
            valueStr.Format(_T("<Entity Name Reference: %8lx>"), rb->resval.rlname[0]);
            break;
        case -1:
        case RTENAME:
            if ((rb->restype >= 330 )&& (rb->restype < 340))
                valueStr.Format(_T("<Soft Pointer: %8lx>"), rb->resval.rlname[0]);
            else if((rb->restype >= 340) && (rb->restype < 350))
                valueStr.Format(_T("<Hard Pointer: %8lx>"), rb->resval.rlname[0]);
            else if((rb->restype >= 350) && (rb->restype < 360))
                valueStr.Format(_T("<Soft Ownership: %8lx>"), rb->resval.rlname[0]);
            else if((rb->restype >= 360) && (rb->restype < 370))
                valueStr.Format(_T("<Hard Ownership: %8lx>"), rb->resval.rlname[0]);
            else if((rb->restype >= 390) && (rb->restype < 399))
                valueStr.Format(_T("<Hard Pointer: %8lx>"), rb->resval.rlname[0]);
            else
                valueStr.Format(_T("<Entity Name: %8lx>"), rb->resval.rlname[0]);
            break;
        case RTPICKS:
            valueStr.Format(_T("<Selection Set: %8lx>"), rb->resval.rlname[0]);
            break;
        case RTLB:
            valueStr = _T("List Begin");
            break;
        case RTLE:
            valueStr = _T("List End");
            break;
        case RTNIL:
            valueStr = _T("NIL");
            break;
        case RTT:
            valueStr = _T("T");
            break;
        default:
            valueStr = _T("*Unknown*");
            break;
    }
}

/******************************************************************
**
**  duplicateResbufNode
**      duplicate only a single node on the list.
**
**  **jma
**
****************************/

resbuf*
duplicateResbufNode(resbuf* rb)
{
    resbuf *newNode;
    int dataType;

    newNode = acutNewRb(rb->restype);    // standard out of mem handler??
    ASSERT(newNode != NULL);
    if (newNode == NULL)
        return(NULL);

    dataType = dxfCodeToDataType(rb->restype);

    if (dataType == RTSHORT)
        newNode->resval.rint = rb->resval.rint;
    else if (dataType == RTREAL)
        newNode->resval.rreal = rb->resval.rreal;
    else if (dataType == RTLONG)
        newNode->resval.rlong = rb->resval.rlong;
    else if ((dataType == RTSTR) || (dataType == -4))
        newNode->resval.rstring = _tcsdup(rb->resval.rstring);
    else if ((dataType == RT3DPOINT) || (dataType == RTPOINT)) {
        copyAdsPt(newNode->resval.rpoint, rb->resval.rpoint);
    }
    else if ((dataType == RTENAME) || (dataType == -1) || (dataType == -2) || (dataType == RTPICKS)){
        copyEname(newNode->resval.rlname, rb->resval.rlname);
    }
    else if (dataType == -3)
        ;       // no value
    else if (dataType == 1004) {
        // Unicode: Leaving as char type because it is a buffer
        newNode->resval.rbinary.buf = static_cast<char*>(malloc(rb->resval.rbinary.clen));
        memcpy(newNode->resval.rbinary.buf, rb->resval.rbinary.buf,
                rb->resval.rbinary.clen);
    }
    else {
        ASSERT(0);    // shouldn't happen
        return NULL;
    }
    return newNode;
}

/******************************************************************
**
**  duplicateResbufChain
**      duplicate the entire chain.
**
**  **jma
**
****************************/

resbuf*
duplicateResbufChain(resbuf* rb)
{
    resbuf* newNode;             // tmp dup node
    resbuf* lastNode = NULL;            // speed ptr to end of list
    resbuf* duplicate = NULL;    // returned duplicate list

    resbuf* tmp = rb;
    while (tmp) {
        if ((newNode = duplicateResbufNode(tmp)) != NULL) {
            if (duplicate == NULL) {
                duplicate = newNode;
                lastNode = newNode;
            }
            else {
                lastNode->rbnext = newNode;
                lastNode = lastNode->rbnext;
            }
        }
        tmp = tmp->rbnext;
    }
    return duplicate;
}

/******************************************************************
**
**  duplicateResbufChain
**      duplicate an range in the chain.
**
**  **jma
**
****************************/

resbuf*
duplicateResbufChain(resbuf* startPtr, resbuf* endPtr)
{
    ASSERT(startPtr != NULL);
    ASSERT(endPtr != NULL);

        // safety bail-out
    if ((startPtr == NULL) || (endPtr == NULL))
        return NULL;

    resbuf* newNode;        // tmp dup node
    resbuf* lastNode = NULL;        // speed ptr to end of list
    resbuf* duplicate = NULL;    // returned duplicate list

    resbuf* tmp = startPtr;
    while (tmp && (tmp != endPtr->rbnext)) {
        if ((newNode = duplicateResbufNode(tmp)) != NULL) {
            if (duplicate == NULL) {
                duplicate = newNode;
                lastNode = newNode;
            }
            else {
                lastNode->rbnext = newNode;
                lastNode = lastNode->rbnext;
            }
        }
        tmp = tmp->rbnext;
    }
    return duplicate;
}

/*********************************************************************
**
**  ptArrayToResbuf:
**      convert an array of 3d points to a resbuf chain
**  of 3d points.  Used to pass to selection set functions.
**
**  **jma
**
******************************************/

resbuf*
ptArrayToResbuf(const AcGePoint3dArray& ptArray)
{
    resbuf* ptList = NULL;        // overall list
    resbuf* lastRb = NULL;        // place holder to end of list
    resbuf* rb;
    int len = ptArray.length();
    for (int i=0;i<len;i++) {
        if ((rb = acutNewRb(RT3DPOINT)) == NULL) {
            acutRelRb(ptList);
            return NULL;
        }
        copyAdsPt(rb->resval.rpoint, asDblArray(ptArray.at(i)));
        if (ptList == NULL) {
            ptList = rb;
            lastRb = rb;
        }
        else {
            lastRb->rbnext = rb;
            lastRb = rb;
        }
    }
    return ptList;
}

/*********************************************************************
**
**  tailOfResbufChain:
**      find the end of the resbuf chain.
**
**  **jma
**
******************************************/

resbuf*
tailOfResbufChain(resbuf* const rb)
{
    resbuf* tmp = rb;
    if (tmp != NULL) {
        while (tmp->rbnext != NULL)
            tmp = tmp->rbnext;
    }
    return tmp;
}

/*********************************************************************
**
**  printResbufChain:
**
**  **jma
**
******************************************/

void
printResbufChain(resbuf* const rb)
{
    CString dxfCodeStr, valueStr, tmpStr;
    resbuf* tmp = rb;
    while (tmp) {
        dxfToStr(tmp, dxfCodeStr, valueStr);
        tmpStr.Format(_T("\n(%s . %s)"), dxfCodeStr, valueStr);
        acutPrintf(static_cast<LPCTSTR>(tmpStr));
        tmp = tmp->rbnext;
    }
}



