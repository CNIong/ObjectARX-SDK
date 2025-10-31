//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
