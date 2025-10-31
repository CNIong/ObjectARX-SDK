//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//  ArxDbgUiDlgReactors.cpp
//
//////////////////////////////////////////////////////////////////////////////
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

    const AcDbVoidPtrArray* reactors = m_objPtr->reactors();
    if (reactors != nullptr) {
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
