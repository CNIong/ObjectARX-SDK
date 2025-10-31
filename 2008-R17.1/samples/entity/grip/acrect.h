//
// (C) Copyright 1998-2002,2004 by Autodesk, Inc. 
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
// FILE: acrect.h

# ifndef ACRECT_H
# define ACRECT_H
# pragma once


# include "GripImp.h"
# include "dbgrip.h"

//# include <afxwin.h>
//# include "dbents.h"
//# include "dbproxy.h"
//# include "gept3dar.h"
//# include "acgi.h"
//# include "dbgrip.h"
//# include "dbmain.h"


//========================================================================
//
// AcRectangle class declaration
//
//========================================================================

class AcRectangle : public AcDbEntity
{
public:
	ACRX_DECLARE_MEMBERS(AcRectangle);
	//Constructor
	AcRectangle();
	AcRectangle(AcGeVector3d&, AcGeVector3d&, AcGePoint3d&, double, double);
	virtual ~AcRectangle();

    double  width() const;
    void    setWidth(double value);
    double  height() const;
    void    setHeight(double value);
    double  elevation() const;
    void    setElevation(double value);
    AcGePoint3d  center() const;
    void setCenter(const AcGePoint3d& cenPt);
    AcGeVector3d normal() const;
    void setNormal(const AcGeVector3d& normVec);
    AcGeVector3d horizDir() const;
    void setHorizDir(const AcGeVector3d& horzVec);
    bool updateDimensions(AcDbDimDataPtrArray* pDimData);

    virtual void  list() const;
    virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);

	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;

	virtual	Adesk::Boolean    worldDraw(AcGiWorldDraw* worldDraw);

	virtual Acad::ErrorStatus getGripPoints(AcGePoint3dArray&,AcDbIntArray&,
							  			    AcDbIntArray&) const;
	virtual Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray&,const AcGeVector3d&);
	

    virtual Acad::ErrorStatus   getGripPoints(AcDbGripDataPtrArray& grips,
                                              const double curViewUnitSize, 
                                              const int gripSize, 
                                              const AcGeVector3d& curViewDir, 
                                              const int bitflags) const;
	virtual Acad::ErrorStatus  moveGripPointsAt(const AcDbVoidPtrArray&,
												const AcGeVector3d&,
                                                const int bitflags);
    virtual void gripStatus(const AcDb::GripStat status);

    static void gripDimensionCbackFuncGuts(AcDbGripData*,
		                                   const AcDbObjectId&,
                                           double dimScale,
                                           AcDbDimDataPtrArray&,
                                           bool isHover = false);

    static void hoverDimensionCbackFunc(AcDbGripData*,
                                        const AcDbObjectId&,
                                        double dimScale,
                                        AcDbDimDataPtrArray&);

    static void hotGripDimensionCbackFunc(AcDbGripData*,
		                                  const AcDbObjectId&,
                                          double dimScale,
                                          AcDbDimDataPtrArray&);

    static AcGeVector3d  setDimValueCbackFunc(AcDbDimData* pThis, 
                                     AcDbEntity* pEnt, 
                                     double value,
									 const AcGeVector3d& offset);

    static  bool gripWorldDrawFunc(AcDbGripData* pThis,
                                   AcGiWorldDraw* pWd,
                                   const AcDbObjectId& entId, 
                                   AcDbGripOperations::DrawType type, 
                                   AcGePoint3d* cursor);

	//View port draw call back functions
	
static void
GripViewportDrawfunc(			AcDbGripData				 *pThis,
								AcGiViewportDraw			 *pVd,
								const AcDbObjectId			 &entId,
								AcDbGripOperations::DrawType type,
								AcGePoint3d					 *cursor,
								int							 gripSize);

private:
   //Member variables
    AcGePoint3d					   mCenter;
	AcGeVector3d				   mNormal;
    AcGeVector3d                   mHorizDir;
    double                         mWidth;
    double                         mHeight;
    double                         mElevation;

public:
    AcDbDimDataPtrArray            *mpDimData;
};



# endif  // ACRECT_H
