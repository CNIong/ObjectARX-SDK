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
