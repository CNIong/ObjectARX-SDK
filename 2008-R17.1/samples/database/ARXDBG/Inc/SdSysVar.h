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

#ifndef ARXDBG_SDSYSVAR_H
#define ARXDBG_SDSYSVAR_H


/****************************************************************************
**
**    CLASS SdSysVarNode:
**        a simple object that stores the name and previous value of
**    an AutoCAD system variable.  It is not intended to be used by anyone
**    but the SdSysVarStack class.
**
**    **jma
**
*************************************/


class SdSysVarNode {

friend class SdSysVarStack;

private:
        // constructors/destructors
                SdSysVarNode(LPCTSTR varName, const resbuf* newVal);
    virtual        ~SdSysVarNode();

        // helper functions
#ifdef _DEBUG
    void        printVal(LPCTSTR msg, const resbuf* rb);  // pretty print a resbuf value
#endif

        // data members
    CString        m_varName;
    resbuf*        m_prevValue;

    // outlawed functions
    SdSysVarNode(const SdSysVarNode& copy);
    SdSysVarNode& operator=(const SdSysVarNode& copy);
};


/****************************************************************************
**
**    CLASS SdSysVarStack:
**        used to keep track of values of AutoCAD system variables so
**    that they are always returned to the values that the user had set.
**    This is not a true stack because it pops the top-most element with
**    the given varname, not just the top element.  Otherwise, it behaves
**    as a regular stack.
**
**        it is envisioned that it could be modified to keep track of
**    Sdsk system variables as well.  It just needs to keep track of one
**    extra flag so it knows which var functions to call.
**
**    **jma
**
*************************************/

class SdSysVarStack {

public:
        // constructors/destructors
                SdSysVarStack();
    virtual        ~SdSysVarStack();

        // operations
    void        pop(LPCTSTR varName);

    void        push(LPCTSTR varName, int);
    void        push(LPCTSTR varName, double);
    void        push(LPCTSTR varName, const TCHAR*);
    void        push(LPCTSTR varName, const AcGePoint3d&);
    void        push(LPCTSTR varName, const AcGePoint2d&);
    void        push(LPCTSTR varName, const AcGeVector3d&);

    void        push(LPCTSTR varName);    // use if you want to save the state of a var
                            // for restoration, but want to use the manual
                            // method for setting: pDb->setCecolor(ColorID);

    static Acad::ErrorStatus    setVar(LPCTSTR varName, const resbuf* newVal);

private:
        // data members
    CPtrList    m_varStack;

        // helper functions
    void        addNewNode(LPCTSTR varName, const resbuf* newVal);

    // outlawed functions
    SdSysVarStack(const SdSysVarStack &copy);
    SdSysVarStack&    operator=(const SdSysVarStack &copy);
};


///    These functions used to get a system variable which is
///    not available through the current database pointer.
Acad::ErrorStatus    getSysVar(LPCTSTR varName, int&);
Acad::ErrorStatus    getSysVar(LPCTSTR varName, double&);
Acad::ErrorStatus    getSysVar(LPCTSTR varName, CString&);
Acad::ErrorStatus    getSysVar(LPCTSTR varName, AcGePoint3d&);
Acad::ErrorStatus    getSysVar(LPCTSTR varName, AcGePoint2d&);

///    These functions used to set a system variable which is
///    not available through the current database pointer.
Acad::ErrorStatus    setSysVar(LPCTSTR varName, int);
Acad::ErrorStatus    setSysVar(LPCTSTR varName, double);
Acad::ErrorStatus    setSysVar(LPCTSTR varName, LPCTSTR);
Acad::ErrorStatus    setSysVar(LPCTSTR varName, const AcGePoint3d&);
Acad::ErrorStatus    setSysVar(LPCTSTR varName, const AcGePoint2d&);


#endif    // ARXDBG_SDSYSVAR_H
