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

#include "ArxDbgUiDlgClassDict.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  cmdSnoopClasses
**
**  **jma
**
*************************************/

void
cmdSnoopClasses()
{
    ArxDbgUiDlgClassDict dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxDbgUiDlgClassDict::ArxDbgUiDlgClassDict
**
**  **jma
**
*************************************/

ArxDbgUiDlgClassDict::ArxDbgUiDlgClassDict(CWnd* parent)
:	CAcUiDialog(ArxDbgUiDlgClassDict::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgClassDict)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

	SetDialogName(_T("ArxDbg-ClassDict"));
}

/****************************************************************************
**
**  ArxDbgUiDlgClassDict::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgClassDict::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgClassDict)
    DDX_Control(pDX, ARXDBG_LC_CLASSES, m_classList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgClassDict message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgClassDict, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgClassDict)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgClassDict message handlers

/****************************************************************************
**
**  ArxDbgUiDlgClassDict::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgClassDict::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();

    buildColumns();
    buildClassList();
    display();
    
    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiDlgClassDict::buildColumns
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgClassDict::buildColumns()
{
    int col1_width, col2_width, col3_width, col4_width, col5_width, col6_width;

    col1_width = 200;
    col2_width = 200;
    col3_width = 200;
    col4_width = 100;
    col5_width = 200;
    col6_width = 200;

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_TEXT;
    lvc.cx = col1_width;
    lvc.pszText = _T("Class Name");
    m_classList.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.pszText = _T("DXF Name");
    m_classList.InsertColumn(1, &lvc);

    lvc.cx = col3_width;
    lvc.pszText = _T("App Name");
    m_classList.InsertColumn(2, &lvc);

    lvc.cx = col4_width;
    lvc.pszText = _T("Proxy Flags");
    m_classList.InsertColumn(3, &lvc);

    lvc.cx = col5_width;
    lvc.pszText = _T("Birth DWG Version");
    m_classList.InsertColumn(4, &lvc);

    lvc.cx = col6_width;
    lvc.pszText = _T("Birth Maint. Version");
    m_classList.InsertColumn(5, &lvc);

	GetColumnSizes(&m_classList);
}

/****************************************************************************
**
**  ArxDbgUiDlgClassDict::buildClassList
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgClassDict::buildClassList()
{
        // get an interator over the class dictionary
    AcRxDictionary* classDict = acrxClassDictionary;
    AcRxDictionaryIterator* iter;
    if ((classDict == NULL) || ((iter = classDict->newIterator()) == NULL)) {
        ArxDbgUtils::stopAlertBox(_T("ERROR: Couldn't get class dictionary."));
        return;
    }
        // iterate over each item and get its info
    AcRxObject* classDictItem;
    AcRxClass* classObj;
    const TCHAR* text;
    CString str, className, dxfName, appName;

    for (; !iter->done(); iter->next()) {
        classDictItem = iter->object();
        if ((classObj = AcRxClass::cast(classDictItem)) != NULL) {
            if ((text = classObj->appName()) != NULL)
                appName = text;
            else
                appName = _T("");

            if ((text = classObj->name()) != NULL)
                className = text;
            else
                className = _T("");

            if ((text = classObj->dxfName()) != NULL)
                dxfName = text;
            else
                dxfName = _T("");

            m_classNameStrList.AddTail(className);
            m_dxfNameStrList.AddTail(dxfName);
            m_appNameStrList.AddTail(appName);
			
			if (dxfName.IsEmpty()) {
				m_proxyStrList.AddTail(_T(""));
				m_birthDwgVerList.AddTail(_T(""));
				m_birthMntVerList.AddTail(_T(""));
			}
			else {
				int dwgVer = 0;
				int maintVer = 0;
				classObj->getClassVersion(dwgVer, maintVer);

				m_proxyStrList.AddTail(ArxDbgUtils::intToStr(classObj->proxyFlags(), str));
				m_birthDwgVerList.AddTail(ArxDbgUtils::dwgVersionToStr(static_cast<AcDb::AcDbDwgVersion>(dwgVer), str));
				m_birthMntVerList.AddTail(ArxDbgUtils::intToStr(maintVer, str));
			}
        }
        else {
            ArxDbgUtils::stopAlertBox(_T("ERROR: found non AcRxClass in class dictionary!"));
        }
    }
    delete iter;
}

/****************************************************************************
**
**  ArxDbgUiDlgClassDict::display
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgClassDict::display()
{
        // build up the list view control
    LV_ITEM lvi;
    lvi.mask = 0;
    int row = 0;

    POSITION pos1 = m_classNameStrList.GetHeadPosition();
    POSITION pos2 = m_dxfNameStrList.GetHeadPosition();
    POSITION pos3 = m_appNameStrList.GetHeadPosition();
    POSITION pos4 = m_proxyStrList.GetHeadPosition();
    POSITION pos5 = m_birthDwgVerList.GetHeadPosition();
    POSITION pos6 = m_birthMntVerList.GetHeadPosition();

    while ((pos1 != NULL) && (pos2 != NULL)) {
        lvi.iItem = row;
        lvi.iSubItem = 0;
        m_classList.InsertItem(&lvi);
        m_classList.SetItemText(row, 0, m_classNameStrList.GetNext(pos1));
        m_classList.SetItemText(row, 1, m_dxfNameStrList.GetNext(pos2));
        m_classList.SetItemText(row, 2, m_appNameStrList.GetNext(pos3));
        m_classList.SetItemText(row, 3, m_proxyStrList.GetNext(pos4));
        m_classList.SetItemText(row, 4, m_birthDwgVerList.GetNext(pos5));
        m_classList.SetItemText(row, 5, m_birthMntVerList.GetNext(pos6));
        row++;
    }
}

/****************************************************************************
**
**  ArxDbgUiDlgClassDict::OnOK
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgClassDict::OnOK() 
{
	SaveColumnSizes(&m_classList);
	
	CAcUiDialog::OnOK();
}

