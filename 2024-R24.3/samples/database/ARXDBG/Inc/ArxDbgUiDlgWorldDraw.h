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

#ifndef ARXDBGUIDLGWORLDDRAW_H
#define ARXDBGUIDLGWORLDDRAW_H

#include "Res_ArxDbg.h"
#include "ArxDbgWorldDraw.h"

/****************************************************************************
**
**	CLASS WorldDrawDbox:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgWorldDraw : public CAcUiDialog {

public:
    ArxDbgUiDlgWorldDraw(ArxDbgGiWorldDraw& wd, CWnd* pParent);

    AcGiRegenType    regenType() const;

    //{{AFX_DATA(ArxDbgUiDlgWorldDraw)
    enum { IDD = ARXDBG_DLG_WORLD_DRAW };
    BOOL    m_cbDragging;
    double	m_ebDeviation;
    int     m_ebIsolines;
    int     m_rgRegenType;
    BOOL    m_cbShowGeom;
    BOOL    m_cbShowDetail;
    BOOL    m_cbShowSubents;
    BOOL    m_cbShowWorldDraw;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgWorldDraw)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgWorldDraw)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ArxDbgGiWorldDraw&    m_wd;
};

#endif    // ARXDBGUIDLGWORLDDRAW_H
