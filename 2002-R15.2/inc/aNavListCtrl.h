/////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-1999 by Autodesk, Inc.
//
// The information contained herein is confidential, proprietary to Autodesk,
// Inc., and considered a trade secret as defined in section 499C of the
// penal code of the State of California.  Use of this information by anyone
// other than authorized employees of Autodesk, Inc. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
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

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


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
    afx_msg LONG OnHandleDrag(UINT pDataSource, LONG nSelectedItem);        
    DECLARE_MESSAGE_MAP()

    CImageList* m_pDragImage;
    CNavDropSource m_dropSource;

};

#endif // _ANavListCtrl_h