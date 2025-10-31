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

#ifndef ARXDBG_ENTMAKETEST_H
#define ARXDBG_ENTMAKETEST_H

#include "Res_ArxDbg.h"

/****************************************************************************
**
**  CLASS EntMakeDbox:
**
**  **jma
**
*************************************/

class EntMakeDbox : public CAcUiDialog {

public:
                EntMakeDbox(CWnd* pParent);

    //{{AFX_DATA(EntMakeDbox)
    enum { IDD = ARXDBG_DLG_ENTMAKE };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(EntMakeDbox)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
                    AFX_CMDHANDLERINFO* pHandlerInfo);

protected:
    // Generated message map functions
    //{{AFX_MSG(EntMakeDbox)
    afx_msg void OnButtonClicked();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    int        m_buttonId;

        // functions
    void        makePolyline();
    void        make2dPolyline();
    void        make3dPolyline();
    void        makeArc();
    void        makeCircle();
    void        makeEllipse();
    void        makeLeader();
    void        makeLine();
    void        makeRay();
    void        makeSpline();
    void        makeXline();
    void        makePolyFaceMesh();
    void        makePolygonMesh();
    void        make2LineAngularDim();
    void        make3PointAngularDim();
    void        makeAlignedDim();
    void        makeDiametricDim();
    void        makeOrdinateDim();
    void        makeRadialDim();
    void        makeRotatedDim();
    void        makeBlockReference();
    void        makeMInsertBlock();
    void        makeHatch();
    void        makeFace();
    void        makeFcf();
    void        makeMline();
    void        makePoint();
    void        makeSolid();
    void        makeTrace();
    void        makeViewport();
    void        make3dSolid();
    void        makeRegion();
    void        makeText();
    void        makeMText();
    void        makeAttributeDefinition();

        // helper functions
    Acad::ErrorStatus   getPointArray(AcGePoint3dArray& vertices, int& ptCount);
    void                makeVface(AcDbPolyFaceMesh* pface,
                                const AcGePoint3d& pt1, const AcGePoint3d& pt2,
                                const AcGePoint3d& pt3, const AcGePoint3d& pt4);
    void                recordVface(AcDbPolyFaceMesh* pface, int vertex1, int vertex2, int vertex3, int vertex4);
    void                addPolygonMeshVertex(AcDbPolygonMesh* mesh, const AcGePoint3d& pt);
    void                nextNvertex(int nSize, const AcGePoint3d& pt1, const AcGePoint3d& pt2, AcDbPolygonMesh* mesh);
    AcGePoint3d         nextMvertex(int mSize, int loop, const AcGePoint3d& pt1, const AcGePoint3d& pt2);
    Acad::ErrorStatus   makeAttributes(const AcDbObjectId& blockRecordId, AcDbBlockReference* blkRef);
    Acad::ErrorStatus   getBlockSpecFromUser(AcDbObjectId& blockId, AcGePoint3d& insertPt,
                                double& scale, double& rotation);

    Acad::ErrorStatus   getArcCircleCenterRadius(AcGePoint3d& centerPt, double& radius);
    Acad::ErrorStatus   get3PointArc(AcGePoint3d& centerPt, AcGePoint3d& pt1, AcGePoint3d& pt2);
    Acad::ErrorStatus   getLineOrTwoPoints(AcGePoint3d& pt1, AcGePoint3d& pt2);
    Acad::ErrorStatus   getAngularDimLines(AcGePoint3d& pt1, AcGePoint3d& pt2, AcGePoint3d& pt3, AcGePoint3d& pt4);
    Acad::ErrorStatus   getDimRotationAngle(double& ang);
    double              getDimHorizRotation();

};


#endif    // ARXDBG_ENTMAKETEST_H
