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

#ifndef ARXDBGUIDLGTESTCURVE_H
#define ARXDBGUIDLGTESTCURVE_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**	CLASS ArxDbgUiDlgTestCurve:
**
**	**jma
**
*************************************/

class ArxDbgUiDlgTestCurve : public CAcUiDialog {

public:
                ArxDbgUiDlgTestCurve(CWnd* pParent);

    //{{AFX_DATA(ArxDbgUiDlgTestCurve)
    enum { IDD = ARXDBG_DLG_TESTCURVES };
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiDlgTestCurve)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiDlgTestCurve)
    afx_msg void    testGetPlane();
    afx_msg void    testGetStartParamEndParam();
    afx_msg void    testGetStartPtEndPt();
    afx_msg void    testGetPtAtParam();
    afx_msg void    testGetParamAtPt();
    afx_msg void    testGetDistAtParam();
    afx_msg void    testGetParamAtDist();
    afx_msg void    testGetDistAtPt();
    afx_msg void    testGetPtAtDist();
    afx_msg void    testGetDerivs();
    afx_msg void    testGetDerivs2();
    afx_msg void    testGetClosestPtTo();
    afx_msg void    testGetClosestPtTo2();
    afx_msg void    testGetOrthoProjectedCurve();
    afx_msg void    testGetProjectedCurve();
    afx_msg void    testGetOffsetCurves();
    afx_msg void    testGetSpline();
    afx_msg void    testGetSplitCurves();
    afx_msg void    testGetSplitCurves2();
    afx_msg void    testExtend();
    afx_msg void    testExtend2();
    afx_msg void    testGetArea();
    afx_msg void    testIsClosedPeriodicPlanar();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // helper functions
    AcDbCurve*  selectCurve();
    void        printInfo(LPCTSTR tagStr, LPCTSTR valStr);
    void        makeRay(const AcGePoint3d& origin, const AcGeVector3d& dir, int color);
    void        makePt(const AcGePoint3d& pt, int color);
    BOOL        getCurvePts(AcGePoint3dArray& pts);
    BOOL        getCurveParams(AcGeDoubleArray& params);
    BOOL        getCurveParam(double& param);
    void        printParamInterval(AcDbCurve* curve);
};

#endif    // ARXDBGUIDLGTESTCURVE_H
