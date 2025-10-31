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

#ifndef ARXDBGUITDCDBOBJECTBASE_H
#define ARXDBGUITDCDBOBJECTBASE_H

#include "Res_ArxDbg.h"
#include "ArxDbgUiTdcRxObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcDbObjectBase:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcDbObjectBase : public ArxDbgUiTdcRxObjectBase {

public:
    virtual    ~ArxDbgUiTdcDbObjectBase()    {}

    //{{AFX_DATA(ArxDbgUiTdcDbObjectBase)
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcDbObjectBase)
    public:
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
            ArxDbgUiTdcDbObjectBase();    // can only be constructed by derived classes

    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcDbObjectBase)
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg virtual void OnDxf();
    afx_msg virtual void OnExtdict();
    afx_msg virtual void OnReactors();
    afx_msg virtual void OnXdata();
    afx_msg virtual void OnDatabase();
    afx_msg virtual void OnDocument();
    afx_msg virtual void OnReferencedObjects();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

        // data members
    AcDbObjectId        m_currentObjId;

        // helper functions
    AcDbObject*			openCurrentItem();

    void			addToSet();
    void			delFromSet();
	void			showObjIdDetails();
    void			setExtensionButtons(AcDbObject* obj);
	virtual bool	getReferencedObjects(AcDbObjectIdArray& hardPointerIds,
										 AcDbObjectIdArray& softPointerIds,
										 AcDbObjectIdArray& hardOwnershipIds,
										 AcDbObjectIdArray& softOwnershipIds);


		// derived from AcDbObject
	void		display(AcDbObject* obj);
	void		display(AcDbDictionary* obj);
	void		display(AcDbEntity* obj);
	void		display(AcDbFilter* obj);
	void		display(AcDbGroup* obj);
	void		display(AcDbIndex* obj);
	void		display(AcDbLongTransaction* obj);
	void		display(AcDbMlineStyle* obj);
	void		display(AcDbPlaceHolder* obj);
	void		display(AcDbPlotSettings* obj);
	void		display(AcDbProxyObject* obj);
	void		display(AcDbSymbolTable* obj);
	void		display(AcDbSymbolTableRecord* obj);
	void		display(AcDbXrecord* obj);

		// derived from AcDbDictionary
	void		display(AcDbDictionaryWithDefault* obj);

		// derived form AcDbEntity
    void        display(AcDb3dSolid* obj);
    void        display(AcDbBlockBegin* obj);
    void        display(AcDbBlockEnd* obj);
    void        display(AcDbBlockReference* obj);
    void        display(AcDbBody* obj);
    void        display(AcDbCurve* obj);
    void        display(AcDbDimension* obj);
    void        display(AcDbFace* obj);
    void        display(AcDbFaceRecord* obj);
    void        display(AcDbFcf* obj);
    void        display(AcDbFrame* obj);
    void        display(AcDbHatch* obj);
    void        display(AcDbImage* obj);
    void        display(AcDbMline* obj);
    void        display(AcDbMText* obj);
    void        display(AcDbPoint* obj);
    void        display(AcDbPolyFaceMesh* obj);
    void        display(AcDbPolygonMesh* obj);
    void        display(AcDbProxyEntity* obj);
    void        display(AcDbRegion* obj);
    void        display(AcDbSequenceEnd* obj);
    void        display(AcDbShape* obj);
    void        display(AcDbSolid* obj);
    void        display(AcDbText* obj);
    void        display(AcDbTrace* obj);
    void        display(AcDbVertex* obj);
    void        display(AcDbViewport* obj);

		// derived from AcDbBlockReference
	void		display(AcDbMInsertBlock* obj);

		// derived from AcDbCurve
    void        display(AcDb2dPolyline* obj);
    void        display(AcDb3dPolyline* obj);
    void        display(AcDbArc* obj);
    void        display(AcDbCircle* obj);
    void        display(AcDbEllipse* obj);
    void        display(AcDbLeader* obj);
    void        display(AcDbLine* obj);
    void        display(AcDbPolyline* obj);
    void        display(AcDbRay* obj);
    void        display(AcDbSpline* obj);
    void        display(AcDbXline* obj);

		// derived from AcDbDimension
    void        display(AcDb2LineAngularDimension* obj);
    void        display(AcDb3PointAngularDimension* obj);
    void        display(AcDbAlignedDimension* obj);
    void        display(AcDbDiametricDimension* obj);
    void        display(AcDbOrdinateDimension* obj);
    void        display(AcDbRadialDimension* obj);
    void        display(AcDbRotatedDimension* obj);

		// derived from AcDbFrame
	void		display(AcDbOleFrame* obj);
	void		display(AcDbOle2Frame* obj);

		// derived from AcDbText
    void        display(AcDbAttribute* obj);
    void        display(AcDbAttributeDefinition* obj);

		// derived from AcDbVertex
    void        display(AcDb2dVertex* obj);
    void        display(AcDb3dPolylineVertex* obj);
    void        display(AcDbPolyFaceMeshVertex* obj);
    void        display(AcDbPolygonMeshVertex* obj);

		// derived from AcDbFilter
	void		display(AcDbLayerFilter* obj);
	void		display(AcDbSpatialFilter* obj);

		// derived from AcDbIndex
	void		display(AcDbLayerIndex* obj);
	void		display(AcDbSpatialIndex* obj);

		// derived from AcDbPlotSettings
	void		display(AcDbLayout* obj);

        // derived from AcDbSymbolTableRecord
    void        display(AcDbAbstractViewTableRecord* tbl);
    void        display(AcDbBlockTableRecord* tbl);
    void        display(AcDbDimStyleTableRecord* tbl);
    void        display(AcDbLayerTableRecord* tbl);
    void        display(AcDbLinetypeTableRecord* tbl);
    void        display(AcDbRegAppTableRecord* tbl);
    void        display(AcDbTextStyleTableRecord* tbl);
    void        display(AcDbUCSTableRecord* tbl);

		// derived from AcDbAbstractViewTableRecord
    void        display(AcDbViewTableRecord* tbl);
    void        display(AcDbViewportTableRecord* tbl);

		// helpers
    void        displayGeCurve2d(const AcGeCurve2d* curve, int edgeType);

};

#endif    // ARXDBGUITDCDBOBJECTBASE_H
