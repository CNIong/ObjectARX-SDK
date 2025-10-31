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

#ifndef ARXDBGUIDLGSPLASH_H
#define ARXDBGUIDLGSPLASH_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgSplash:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgSplash : public CAcUiDialog {

public:
                    ArxDbgUiDlgSplash(LPCTSTR bmpFileName);        // modeless version
    virtual			~ArxDbgUiDlgSplash()    {}

    void            setTextStrings(LPCTSTR str1, LPCTSTR str2, LPCTSTR str3, LPCTSTR str4);

    //{{AFX_DATA(ArxDbgUiDlgSplash)
    enum { IDD = ARXDBG_DLG_SPLASH };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgSplash)
    public:
    virtual BOOL Create(CWnd* parent);
    virtual BOOL DestroyWindow();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgSplash)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    LPCTSTR		m_bmpFileName;
    CWnd*       m_parentWnd;
    CString     m_str1;
    CString     m_str2;
    CString     m_str3;
    CString     m_str4;

        // low level file reading vars    (ask wth for details!)
    HANDLE				m_fh;
    BITMAPFILEHEADER    m_bmfh;
    BITMAPINFO          m_bmi;
    ULONG               m_nBytesRead;
    LONG                m_picWidth;
    LONG                m_picHeight;

    static const int kBorderX;
    static const int kBorderY;

    void    displayTextLines();
    void    processTextLine(CString& str, UINT dlgItemId, int& numLines, int ht);
};

#endif    // ARXDBGUIDLGSPLASH_H
