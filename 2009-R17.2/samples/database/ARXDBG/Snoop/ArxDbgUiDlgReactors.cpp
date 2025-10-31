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

#include "ArxDbgUiDlgReactors.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiDlgReactors::ArxDbgUiDlgReactors
**
**  **jma
**
*************************************/

ArxDbgUiDlgReactors::ArxDbgUiDlgReactors(CWnd* parent, AcDbObject* obj)
:   CAcUiDialog(ArxDbgUiDlgReactors::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
    ASSERT(obj != NULL);
    m_objPtr = obj;

    //{{AFX_DATA_INIT(ArxDbgUiDlgReactors)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiDlgReactors::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgReactors::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgReactors)
    DDX_Control(pDX, ARXDBG_LB_TRANSIENT, m_transList);
    DDX_Control(pDX, ARXDBG_LB_PERSISTENT, m_persistList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgReactors message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgReactors, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgReactors)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgReactors message handlers


/****************************************************************************
**
**  ArxDbgUiDlgReactors::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgReactors::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();

    m_persistList.SetTabStops(45);
    
    CString str, str2;

    void* pSomething;
    AcDbObjectReactor* pObjReactor;
    AcDbObject* obj;
    Acad::ErrorStatus es;

    AcDbVoidPtrArray* reactors = m_objPtr->reactors();
    if (reactors != NULL) {
        for (int i = 0; i < reactors->length(); i++) {
            pSomething = reactors->at(i);
            if (acdbIsPersistentReactor(pSomething)) {
                es = acdbOpenObject(obj, acdbPersistentReactorObjectId(pSomething), AcDb::kForRead);
                if ((es == Acad::eOk) && obj) {
                    str.Format(_T("%s\t%s"), ArxDbgUtils::objToHandleStr(obj, str2),
                                ArxDbgUtils::objToClassStr(obj));
                    m_persistList.AddString(str);
                    obj->close();
                }
            }
            else {
                pObjReactor = static_cast<AcDbObjectReactor*>(reactors->at(i));
                m_transList.AddString(ArxDbgUtils::objToClassStr(pObjReactor));
            }
        }
    }
    return TRUE;
}