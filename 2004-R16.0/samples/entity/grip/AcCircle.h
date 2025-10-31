//
// (C) Copyright 1998-2002 by Autodesk, Inc. 
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

# ifndef _ACCIRCLE_H
# define _ACCIRCLE_H

# include "GripImp.h"
# include "dbgrip.h"				//Custom Grip Implementation
# include <vector>
# include <string>
# define PI 3.14
#pragma once 

//========================================================================
//
// AcCircle class declaration
//
//========================================================================
class AcCircle : public AcDbEntity
{
	enum 
	{ GripCount=5};
	
public:
	ACRX_DECLARE_MEMBERS(AcCircle);
	
	AcCircle();
	AcCircle(AcGePoint3d&,AcGeVector3d&,double radius=0.5);
	virtual ~AcCircle();
	
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;
	
	virtual Acad::ErrorStatus getGripPoints(AcGePoint3dArray&,AcDbIntArray&,
							  			    AcDbIntArray&) const;
	virtual Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray&,
											   const AcGeVector3d&);
	//New overloaded grip methods that need to be implemented 
	//to use the Grip Enhancement
	virtual Acad::ErrorStatus  getGripPoints(AcDbGripDataPtrArray& grips,
                                             const double viewSize,
											 const int gripSize,
		                                     const AcGeVector3d& curViewDir, 
                                             const int bitflags) const;

	virtual Acad::ErrorStatus  moveGripPointsAt(const AcDbVoidPtrArray&,
												const AcGeVector3d&,
                                                const int bitflags);

	virtual	Adesk::Boolean    worldDraw(AcGiWorldDraw* worldDraw);

    void					  dragStatus(const AcDb::DragStat status);
    void					  gripStatus(const AcDb::GripStat status);
	void					  setRadius(double radius);
	AcGePoint3d&			  Center();
	void					  setCenter(AcGePoint3d &pt);
	double&					  radius();
	static void				setHover(bool);
	static bool				isHover();
	static AcDbObjectId&	objectId();
	static void				setObjectId(AcDbObjectId &rObjId);
	void					setNormal(AcGeVector3d& normal);
	AcGeVector3d&			normal();
	

	///////////////////////////////////////////////////////////////////
	/////////////Dynamic Dimension call back functions///////////////
	/////////////////////////////////////////////////////////////////
	static void 
	gripDimensionCbackfn(AcDbGripData* pThis,
						 const AcDbObjectId& entId,
						 double dimScale,
						AcDbDimDataPtrArray& dimData);

	static AcGeVector3d 
	setDimValueCbackFunc(AcDbDimData* pThis,
						AcDbEntity* pEnt,
						double newValue,
						const AcGeVector3d& offset);

	static void 
	hotGripDimensionfunc(AcDbGripData			   *pThis,
						const AcDbObjectId		   &entId,
						double					    dimScale,
						AcDbDimDataPtrArray		   &dimData);

	static void 
	hoverGripDimensionfunc(	AcDbGripData				*pGrip,
							const AcDbObjectId			&objId,
							double 						dimScale,
							AcDbDimDataPtrArray			&dimDataArr);
	

private:
	AcGePoint3d					   mCenter;
	AcGeVector3d				   mNormal;
	double						   mRadius;
	static bool						mbHover;
	static appDataType			   msAppData; //Stores the AppData
	static AcDbObjectId			 mentId;

	//Static method
	static appDataType::iterator	putAppData();
};

///////////////////////////////////////////////////////////////////////
///////////AcCircle Inline Functions
__forceinline void	AcCircle::setNormal(AcGeVector3d& normal)
	{ mNormal = normal; }

__forceinline AcGeVector3d& AcCircle::normal()
	{ return mNormal; }

__forceinline void AcCircle::setRadius(double radius)
{	mRadius = radius; }

__forceinline AcGePoint3d& AcCircle::Center()
	{ return 	mCenter; }

__forceinline double&		AcCircle::radius()
{ return mRadius;}

__forceinline void	AcCircle::setHover(bool bHover)
{mbHover = bHover;}

__forceinline bool	AcCircle::isHover()
{	return mbHover; }

 __forceinline void AcCircle::setObjectId(AcDbObjectId &rObjId)
	{ mentId = rObjId; }

__forceinline AcDbObjectId&  AcCircle::objectId()
		{ return mentId; }

__forceinline void AcCircle::setCenter(AcGePoint3d &pt)
		{mCenter = pt; }

#endif//_ACCIRCLE_H