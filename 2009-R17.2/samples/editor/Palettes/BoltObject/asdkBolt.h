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
//
//
//
/////////////////////////////////////////////
// asdkBolt custom object.

#if !defined(ARX__ASDKBOLT_H__20020424_164428)
#define ARX__ASDKBOLT_H__20020424_164428

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dbmain.h"
#include "gemat3d.h"

#pragma warning(disable: 4275 4251)

#ifdef _BOLTOBJECT_
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP 
#endif

#ifndef ASDKBOLTOBJECT_DBXSERVICE
#define ASDKBOLTOBJECT_DBXSERVICE _T("ASDKBOLTOBJECT_DBXSERVICE")
#endif

class DLLIMPEXP asdkBolt : public AcDbEntity
{
public:
	int headSides;
	AcGeVector3d alignment;
	AcGePoint3d position;
	TCHAR partNumber[128];
	TCHAR materialName[128];
	double threadWidth;
	double threadLength;
	double headDiameter;
	double headHeight;
	double shaftDiameter;
	double shaftLength;

	AcGePoint3d headPnts[5], 
		        shaftPnts[4], 
				thread[2];

	ACRX_DECLARE_MEMBERS(asdkBolt);

	// Constructor / Destructor
	asdkBolt();
	virtual ~asdkBolt();

	//{{AFX_ARX_METHODS(asdkBolt)
	virtual Acad::ErrorStatus getClassID(CLSID* pClsid) const;
	virtual void list() const;
	virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);
	Acad::ErrorStatus subClose();
	virtual Acad::ErrorStatus getOsnapPoints(AcDb::OsnapMode osnapMode,
	                                         Adesk::GsMarker gsSelectionMark,
	                                         const AcGePoint3d& pickPoint,
	                                         const AcGePoint3d& lastPoint,
	                                         const AcGeMatrix3d& viewXform,
	                                         AcGePoint3dArray& snapPoints,
	                                         AcDbIntArray& geomIds) const;
	virtual Acad::ErrorStatus getGripPoints(AcGePoint3dArray& gripPoints,
	                                        AcDbIntArray& osnapModes,
	                                        AcDbIntArray& geomIds) const;
	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
	//}}AFX_ARX_METHODS

	 
    //*************************************************************************
    // Get/Put Methods 
    //*************************************************************************
    
	AcGeVector3d getAlignment() const;
    double getHeadDiameter() const;
    double getHeadHeight() const;
    int getHeadSides() const;
	AcGePoint3d	getPosition()const;
	double getShaftDiameter() const;
	double getShaftLength() const;
	double getThreadLength() const;
	double getThreadWidth() const;
    void setAlignment(AcGeVector3d& align);
    void setHeadDiameter(double hD);
    void setHeadHeight(double hH);
    void setHeadSides(int hS);
	void getMaterialName(TCHAR *mN, size_t sizemN);
	void setMaterialName(TCHAR *mN);
	void setPosition(AcGePoint3d& pos);
	void setShaftDiameter(double sD);
	void setShaftLength(double sL);
	void setPartNumber(TCHAR *pN);
	void getPartNumber(TCHAR *pN, size_t sizepN);
	void setThreadLength(double tL); 
	void setThreadWidth(double tW);
	
	//*************************************************************************
    // Bolt draw methods 
    //*************************************************************************
	void drawHead(AcGiWorldDraw* wD);
	void drawShaft(AcGiWorldDraw* wD);
	void drawThread(AcGiWorldDraw* wD);
	void calculatePnts();

	//{{AFX_ARX_DATA_ACCESS(asdkBolt)
	//}}AFX_ARX_DATA_ACCESS

private:
	//{{AFX_ARX_DATA(asdkBolt)
	//}}AFX_ARX_DATA


private:

	void *operator new[](size_t nSize) { return 0; }
	void operator delete[](void *p) {};
	void *operator new[](size_t nSize, const TCHAR *file, int line) { return 0; }

};



#endif // !defined(ARX__ASDKBOLT_H__20020424_164428)