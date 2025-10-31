/////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 1994-2007 by Autodesk, Inc.
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
// DESCRIPTION:
/////////////////////////////////////////////////////////////////////////////

#ifndef _ANavListCtrl_h
#define _ANavListCtrl_h

#pragma once


class  CNavListCtrl;

class CNavDropSource : public COleDropSource
{
public:
    CNavDropSource();       

    CNavListCtrl* m_pListCtrl;

    // Overrides
    SCODE GiveFeedback(DROPEFFECT dropEffect);
};


class ANAV_PORT CNavListCtrl : public CAdUiListCtrl {
public:
    CNavListCtrl ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CNavListCtrl)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CNavListCtrl)
    afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    afx_msg LRESULT OnHandleDrag(UINT_PTR pDataSource, LPARAM nSelectedItem);
    DECLARE_MESSAGE_MAP()

    CImageList* m_pDragImage;
    CNavDropSource m_dropSource;

};

#endif // _ANavListCtrl_h
