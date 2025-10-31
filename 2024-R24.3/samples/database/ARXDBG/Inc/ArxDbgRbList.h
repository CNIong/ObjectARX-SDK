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

#ifndef ARXDBGRBLIST_H
#define ARXDBGRBLIST_H


/******************************************************************
**
**	CLASS ArxDbgRbList
**		Thin wrapper for resbuf chains.  This should be used
**	by other classes and wrapped "thicker" whenever possible.
**	Pay attentiob to orphan/adopt semantics since there is some
**	direct access to the underlying representation.
**
**	**jma
**
****************************/

class ArxDbgRbList {

public:
                ArxDbgRbList();                     // constructs empty list
                ArxDbgRbList(resbuf* adoptedList);  // adopts resbuf chain
                ArxDbgRbList(const ArxDbgRbList&);	// copy constructor (does deep clone)
    virtual		~ArxDbgRbList();

        // assignment
    ArxDbgRbList&        operator=(const ArxDbgRbList& list);    // assign a copy

        // operations on an ArxDbgRbList
    int			length();
    bool        isEmpty()    { return m_head == NULL; }

    void        addHead(resbuf* newNode);
    void        addTail(resbuf* newNode);
    void        append(ArxDbgRbList& appendList);    // destructive to appended list

    resbuf*		detach(resbuf* nodeToDel);    // detach but don't delete
    resbuf*     detach(resbuf* startNode, resbuf* endNode);
    resbuf*     detachHead()    { return detach(m_head); }
    resbuf*     detachTail()    { return detach(m_tail); }

    void        remove(resbuf* nodeToDel);    // detach and delete
    void        removeHead()    { remove(m_head); }
    void        removeTail()    { remove(m_tail); }
    void        removeAll();

        // direct operations on resbuf chain, use only if absolutely necessary
        // these are considered "semi-private"
    void        adoptData(resbuf* adoptedList);	// object takes resposiblity for resbuf*
    resbuf*     orphanData();                   // object gives up responsibility for resbuf*
    resbuf*     data() { return m_head; }       // return pointer to data to pass to ADS

private:
    resbuf*		m_head;        // head of resbuf chain
    resbuf*     m_tail;        // tail of resbuf chain

    bool        addToEmptyList(resbuf* newElement);    // helper function
};


//////////////////////////////////////////////////////////////////////////

    // global functions applicable to raw resbuf usage but also used as helper
    // functions for ArxDbgRbList class
int			dxfCodeToDataType(int resType);
void        dxfToStr(const resbuf* rb, CString& dxfCodeStr, CString& valueStr);
// Unicode: Leaving as char type because it is a buffer
LPCTSTR     bytesToHexStr(char* buffer, int len, CString& hexStr);
resbuf*     duplicateResbufNode(resbuf* rb);
resbuf*     duplicateResbufChain(resbuf* rb);
resbuf*     duplicateResbufChain(resbuf* startPtr, resbuf* endPtr);
resbuf*     ptArrayToResbuf(const AcGePoint3dArray& ptArray);
resbuf*     tailOfResbufChain(resbuf* const rb);
void        printResbufChain(resbuf* const rb);


#endif    // ARXDBGRBLIST_H
