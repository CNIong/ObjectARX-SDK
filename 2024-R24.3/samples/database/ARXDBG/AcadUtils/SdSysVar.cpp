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
#include "SdSysVar.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgUtils.h"



/****************************************************************************
**
**  SdSysVarNode::SdSysVarNode (constructor)
**      save the current value of the sysvar before setting to the
**  new value.
**
**  **jma
**
*************************************/

SdSysVarNode::SdSysVarNode(LPCTSTR varName, const resbuf* newVal)
:    m_varName(varName)
{
    CString str;

        // grab previous value and store it
    m_prevValue = acutNewRb(RTSHORT);    // allocate space for resbuf to be filled in
    if (acedGetVar(varName, m_prevValue) == RTNORM) {

#ifdef _DEBUG
        CString msg;
        msg.Format(_T("\nPUSHING SYSVAR: \"%s\" was "), varName);
        printVal(msg, m_prevValue);
#endif
            // only set new value if one was supplied, caller might want
            // to set it by hand.
        if (newVal != NULL) {
                // make this conditional on some diagnostic flag
#ifdef _DEBUG
            printVal(_T(", setting to "), newVal);
#endif
            SdSysVarStack::setVar(m_varName, newVal);
        }
    }
    else {
        acutRelRb(m_prevValue);
        m_prevValue = NULL;

        str.Format(_T("Could not save state of system variable \"%s\"."), varName);
        ArxDbgUtils::stopAlertBox(str);
    }
}

/****************************************************************************
**
**  SdSysVarNode::~SdSysVarNode (destructor)
**      restore the system var to its previous setting.
**
**  **jma
**
*************************************/

SdSysVarNode::~SdSysVarNode()
{
#ifdef _DEBUG
    CString msg;
    msg.Format(_T("\nPOPPING SYSVAR: resetting \"%s\" to "),
                static_cast<LPCTSTR>(m_varName));
    printVal(msg, m_prevValue);
#endif
    if (m_prevValue) {
        SdSysVarStack::setVar(m_varName, m_prevValue);
        acutRelRb(m_prevValue);
    }
}

#ifdef _DEBUG
/****************************************************************************
**
**  SdSysVarNode::printVal
**      print out the value of a given resbuf type.  Just use raw
**  formatting since you have no idea whether they are vectors, points,
**  scale factors, etc.
**
**  **jma
**
*************************************/

void
SdSysVarNode::printVal(LPCTSTR msg, const resbuf* rb)
{
    CString valStr;

    if (rb->restype == RTSHORT)
        valStr.Format(_T("%d"), rb->resval.rint);
    else if (rb->restype == RTSTR)
        valStr.Format(_T("\"%s\""), rb->resval.rstring);
    else if (rb->restype == RTREAL)
        valStr.Format(_T("%g"), rb->resval.rreal);
    else if (rb->restype == RT3DPOINT)
        valStr.Format(_T("(%g, %g, %g)"), rb->resval.rpoint[X], rb->resval.rpoint[Y], rb->resval.rpoint[Z]);
    else if (rb->restype == RTPOINT)
        valStr.Format(_T("(%g, %g)"), rb->resval.rpoint[X], rb->resval.rpoint[Y]);
    else {
        ASSERT(0);    // shouldn't be any other type of system var!
    }
    TRACE2("%s %s", msg, valStr);
}

#endif

///////////////////////////// SYSTEM VAR STACK //////////////////////////////

/****************************************************************************
**
**  SdSysVarStack::SdSysVarStack(constructor)
**
**  **jma
**
*************************************/

SdSysVarStack::SdSysVarStack()
{
}

/****************************************************************************
**
**  SdSysVarStack::~SdSysVarStack (destructor)
**      pop off any remaining elements and destroy the list
**
**  **jma
**
*************************************/

SdSysVarStack::~SdSysVarStack()
{
    SdSysVarNode* varPtr;

    POSITION pos = m_varStack.GetHeadPosition();
    while (pos != NULL) {
        varPtr = static_cast<SdSysVarNode*>(m_varStack.GetNext(pos));
        delete varPtr;
    }
    m_varStack.RemoveAll();
}

/****************************************************************************
**
**  SdSysVarStack::addNewNode
**
**  **jma
**
*************************************/

void
SdSysVarStack::addNewNode(LPCTSTR varName, const resbuf* newVal)
{
    SdSysVarNode* newNode = new SdSysVarNode(varName, newVal);
    m_varStack.AddHead(static_cast<void*>(newNode));
}

/****************************************************************************
**
**  SdSysVarStack::pop
**      psuedo-pop since it pops the topmost element with the
**  given system var name.
**
**  **jma
**
*************************************/

void
SdSysVarStack::pop(LPCTSTR varName)
{
    ASSERT(varName != NULL);
    ASSERT(!m_varStack.IsEmpty());

    SdSysVarNode* varPtr;

    POSITION pos = m_varStack.GetHeadPosition();
    POSITION savedPos;
    while (pos != NULL) {
        savedPos = pos;
        varPtr = static_cast<SdSysVarNode*>(m_varStack.GetNext(pos));
        if (varPtr && (varPtr->m_varName == varName)) {
            m_varStack.RemoveAt(savedPos);
            delete varPtr;
            return;
        }
    }
    ASSERT(0);    // attempt to pop var that was never pushed!!
}

/****************************************************************************
**
**  SdSysVarStack::push    INT
**
**  **jma
**
*************************************/

void
SdSysVarStack::push(LPCTSTR varName, int val)
{
    ASSERT(varName != NULL);

    resbuf rb;
    rb.restype = RTSHORT;
    rb.resval.rint = val;

    addNewNode(varName, &rb);
}

/****************************************************************************
**
**  SdSysVarStack::push    DOUBLE
**
**  **jma
**
*************************************/

void
SdSysVarStack::push(LPCTSTR varName, double val)
{
    ASSERT(varName != NULL);

    resbuf rb;
    rb.restype = RTREAL;
    rb.resval.rreal = val;

    addNewNode(varName, &rb);
}

/****************************************************************************
**
**  SdSysVarStack::push    STRING
**
**  **jma
**
*************************************/

void
SdSysVarStack::push(LPCTSTR varName, LPCTSTR val)
{
    ASSERT(varName != NULL);

    resbuf rb;
    rb.restype = RTSTR;
    rb.resval.rstring = _tcsdup(val);    // must use stdlib strdup()!

    addNewNode(varName, &rb);
}

/****************************************************************************
**
**  SdSysVarStack::push    3D POINT
**
**  **jma
**
*************************************/

void
SdSysVarStack::push(LPCTSTR varName, const AcGePoint3d& val)
{
    ASSERT(varName != NULL);

    resbuf rb;
    rb.restype = RT3DPOINT;
    copyAdsPt(rb.resval.rpoint, asDblArray(val));

    addNewNode(varName, &rb);
}

/****************************************************************************
**
**  SdSysVarStack::push    2D POINT
**
**  **jma
**
*************************************/

void
SdSysVarStack::push(LPCTSTR varName, const AcGePoint2d& val)
{
    ASSERT(varName != NULL);

    resbuf rb;
    rb.restype = RTPOINT;
    copyAdsPt(rb.resval.rpoint, asDblArray(val));

    addNewNode(varName, &rb);
}

/****************************************************************************
**
**  SdSysVarStack::push    Don't set new value
**
**  **jma
**
*************************************/

void
SdSysVarStack::push(LPCTSTR varName)
{
    ASSERT(varName != NULL);
    addNewNode(varName, NULL);
}

/****************************************************************************
**
**  SdSysVarStack::setVar
**
**  **jma
**
*************************************/

Acad::ErrorStatus
SdSysVarStack::setVar(LPCTSTR varName, const resbuf* newVal)
{
    CString str;
    if (acedSetVar(varName, newVal) != RTNORM) {
        str.Format(_T("Could not set system variable \"%s\"."), varName);
        ArxDbgUtils::stopAlertBox(str);
        return Acad::eInvalidInput;
    }
    else
        return Acad::eOk;
}


/////////////////////////////////////////////////////////////////////////////
//////////////////////////// GLOBAL GETVAR FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////////////////////


/****************************************************************************
**
**  getSysVar (INT)
**
**  **jma
**
*************************************/

Acad::ErrorStatus
getSysVar(LPCTSTR varName, int& val)
{
    resbuf rb;
    if (acedGetVar(varName, &rb)== RTNORM) {
        ASSERT(rb.restype == RTSHORT);
        val = rb.resval.rint;
        return(Acad::eOk);
    }
    else
        return(Acad::eInvalidInput);
}

/****************************************************************************
**
**  getSysVar (DOUBLE)
**
**  **jma
**
*************************************/

Acad::ErrorStatus
getSysVar(LPCTSTR varName, double& val)
{
    resbuf rb;
    if (acedGetVar(varName, &rb) == RTNORM) {
        ASSERT(rb.restype == RTREAL);
        val = rb.resval.rreal;
        return(Acad::eOk);
    }
    else
        return(Acad::eInvalidInput);
}

/****************************************************************************
**
**  getSysVar (string)
**
**  **jma
**
*************************************/

Acad::ErrorStatus
getSysVar(LPCTSTR varName, CString& val)
{
    resbuf rb;
    if (acedGetVar(varName, &rb) == RTNORM) {
        ASSERT(rb.restype == RTSTR);
        val = rb.resval.rstring;
        free(rb.resval.rstring);
        return(Acad::eOk);
    }
    else
        return(Acad::eInvalidInput);
}

/****************************************************************************
**
**  getSysVar (2D point)
**
**  **jma
**
*************************************/

Acad::ErrorStatus
getSysVar(LPCTSTR varName, AcGePoint2d& val)
{
    resbuf rb;
    if (acedGetVar(varName, &rb) == RTNORM) {
        ASSERT(rb.restype == RTPOINT);
        val.set(rb.resval.rpoint[X], rb.resval.rpoint[Y]);
        return(Acad::eOk);
    }
    else
        return(Acad::eInvalidInput);
}

/****************************************************************************
**
**  getSysVar (3D point)
**
**  **jma
**
*************************************/

Acad::ErrorStatus
getSysVar(LPCTSTR varName, AcGePoint3d& val)
{
    resbuf rb;
    if (acedGetVar(varName, &rb) == RTNORM) {
        ASSERT(rb.restype == RT3DPOINT);
        val.set(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
        return(Acad::eOk);
    }
    else
        return(Acad::eInvalidInput);
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////// GLOBAL SETVAR FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  setSysVar(INT)
**
**  **jma
**
*************************************/

Acad::ErrorStatus
setSysVar(LPCTSTR varName, int val)
{
    ASSERT(varName != NULL);

    resbuf rb;
    rb.restype = RTSHORT;
    rb.resval.rint = val;

    return(SdSysVarStack::setVar(varName, &rb));
}

/****************************************************************************
**
**  setSysVar (DOUBLE)
**
**  **jma
**
*************************************/

Acad::ErrorStatus
setSysVar(LPCTSTR varName, double val)
{
    ASSERT(varName != NULL);

    resbuf rb;
    rb.restype = RTREAL;
    rb.resval.rreal = val;

    return(SdSysVarStack::setVar(varName, &rb));
}

/****************************************************************************
**
**  setSysVar (STRING)
**
**  **jma
**
*************************************/

Acad::ErrorStatus
setSysVar(LPCTSTR varName, const TCHAR* val)
{
    ASSERT(varName != NULL);

    resbuf rb;
    rb.restype = RTSTR;
    rb.resval.rstring = const_cast<TCHAR*>(val);

    return(SdSysVarStack::setVar(varName, &rb));
}

/****************************************************************************
**
**  setSysVar (3D POINT)
**
**  **jma
**
*************************************/

Acad::ErrorStatus
setSysVar(LPCTSTR varName, const AcGePoint3d& val)
{
    ASSERT(varName != NULL);

    resbuf rb;
    rb.restype = RT3DPOINT;
    copyAdsPt(rb.resval.rpoint, asDblArray(val));

    return(SdSysVarStack::setVar(varName, &rb));
}

/****************************************************************************
**
**  setSysVar (2D POINT)
**
**  **jma
**
*************************************/

Acad::ErrorStatus
setSysVar(LPCTSTR varName, const AcGePoint2d& val)
{
    ASSERT(varName != NULL);

    resbuf rb;
    rb.restype = RTPOINT;
    copyAdsPt(rb.resval.rpoint, asDblArray(val));

    return(SdSysVarStack::setVar(varName, &rb));
}
