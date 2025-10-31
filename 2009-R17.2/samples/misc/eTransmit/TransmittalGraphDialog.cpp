//
//
// (C) Copyright 2003-2008 by Autodesk, Inc. 
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
//-----------------------------------------------------------------------------
#include "StdAfx.h"
//----- TransmittalGraphDialog.cpp : implementation file
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif




//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CTransmittalGraphDialog, CAcUiDialog)

BEGIN_MESSAGE_MAP(CTransmittalGraphDialog, CAcUiDialog)
    //{{AFX_MSG_MAP(CTransmittalGraphDialog)
    ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)    // Needed for modeless dialog.
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CTransmittalGraphDialog::CTransmittalGraphDialog (ITransmittalFile *graphRoot, CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CTransmittalGraphDialog::IDD, pParent, hInstance) {
    //{{AFX_DATA_INIT(CTransmittalGraphDialog)
    //}}AFX_DATA_INIT

    // store the root graph node point for ITransmittalFile so that we can
    // setup the dialog graph
    m_graphRoot = graphRoot;
}

void CTransmittalGraphDialog::DoDataExchange (CDataExchange *pDX) {
    CAcUiDialog::DoDataExchange (pDX) ;
    //{{AFX_DATA_MAP(CTransmittalGraphDialog)
    DDX_Control(pDX, IDC_TREE1, m_treeGraph);
    //}}AFX_DATA_MAP
}

// Needed for modeless dialogs to keep focus.
// Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CTransmittalGraphDialog::OnAcadKeepFocus(WPARAM, LPARAM)
{
  return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
BOOL CTransmittalGraphDialog::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();

    // redirect the resources
    CAcModuleResourceOverride res;

    // Create image list for the tree view images
  m_imageList.Create(IDB_BITMAPS, 16, 1, RGB(255,255,255));
  // Attach image list to the tree.
  m_treeGraph.SetImageList (&m_imageList, TVSIL_NORMAL);

    // insert the treeroot item
    HTREEITEM treeRoot = m_treeGraph.InsertItem(_T("TransmittalGraph"));
    // add the tree bitmap
  m_treeGraph.SetItemImage (treeRoot, 1, 1);

    // now create the tree
    traverseTransmittalDependents(treeRoot, m_graphRoot);
    // expand the tree so we can see what's held in there
    BOOL ret = m_treeGraph.Expand(treeRoot, TVE_EXPAND);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

//-----------------------------------------------------------------------------

void CTransmittalGraphDialog::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    // TODO: Add your control notification handler code here
    
    *pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////
// recursively tranverses through the ITransmittalFile graph
HRESULT CTransmittalGraphDialog::traverseTransmittalDependents (HTREEITEM treeRoot, ITransmittalFile *graphRoot)
{
    TCHAR drive[_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];
    TCHAR fname[_MAX_FNAME];
    TCHAR ext[_MAX_EXT];		
    BSTR sourcePath; 

    // work out how many dependents we have
    int numOfNodes = 0;
    CComQIPtr<ITransmittalFile2> pIRoot2 = graphRoot;
    CHECK(pIRoot2->get_numberOfDependents(&numOfNodes));
    // ok, got the total number of dependents, loop them 
    for (int i=0; i<numOfNodes; ++i) 
    {
        CComPtr<ITransmittalFile> childFile;
        CHECK(pIRoot2->getDependent(i, &childFile));
        // now print them out
        CHECK(childFile->get_sourcePath(&sourcePath));
        // insert the item into the tree
        HTREEITEM childNode = m_treeGraph.InsertItem((TCHAR *)_bstr_t(sourcePath), treeRoot, treeRoot);

        // lets find out what type of extension it has
        _tsplitpath_s((TCHAR *)_bstr_t(sourcePath), drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
        // drawing files
        if (!_tcsicmp (ext, _T(".dwg")))
        {
            // set the bitmap for this filetype
            m_treeGraph.SetItemImage (childNode, 2, 2);
        }
        // shape fonts
        else if (!_tcsicmp (ext, _T(".shx")))
        {
            // set the bitmap for this filetype
            m_treeGraph.SetItemImage (childNode, 3, 3);
        }
        // true type fonts
        else if (!_tcsicmp (ext, _T(".ttf")))
        {
            // set the bitmap for this filetype
            m_treeGraph.SetItemImage (childNode, 4, 4);
        }
        // postscript fonts
        else if (!_tcsicmp (ext, _T(".pfb")))
        {
            // set the bitmap for this filetype
            m_treeGraph.SetItemImage (childNode, 5, 5);
        }
        // lisp
        else if (!_tcsicmp (ext, _T(".fmp")) || !_tcsicmp (ext, _T(".lsp")))
        {
            // set the bitmap for this filetype
            m_treeGraph.SetItemImage (childNode, 6, 6);
        }
        // other
        else
        {
            // set the bitmap for this filetype
            m_treeGraph.SetItemImage (childNode, 7, 7);
        }

        // now list the dependents of this file
        traverseTransmittalDependents(childNode, childFile);
    }

    return S_OK;
}