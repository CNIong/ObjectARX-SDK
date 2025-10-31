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

#ifndef __ACCIRCLEJIG_H__
#define __ACCIRCLEJIG_H__

# include "GripImp.h"
#include "dbjig.h"
#include "AcCircle.h"
#pragma once 
//========================================================================
//
// AcCircle class declaration
//
//========================================================================
class AcCircleJig : public AcEdJig
{
public:
	AcCircleJig(AcDbDatabase *pDb,AcCircle *pCircle);
	virtual ~AcCircleJig();
	
	void	   dragIt(void);

	//Mehthods called by AcEdJig::drag()
	virtual DragStatus	   sampler(void);
	virtual Adesk::Boolean update();
	virtual AcDbEntity*	   entity()const;

	virtual AcDbDimDataPtrArray* dimData(const double dimScale);
	bool						 updateDimension();
	DragStatus					 acquireDefPt();
	virtual Acad::ErrorStatus setDimValue(const AcDbDimData *pdimData,
										  const double dimValue);
	bool						addDimData();
	Acad::ErrorStatus			setPlane();
	void						setCircleProperties();

private:
	AcCircle		*mpCircle;
	AcDbDatabase	*mpdb;
	double			mpRadius;
	AcGePoint3d		mRadVec; 
	AcGePoint3d		mCenterPt;
	  AcGeVector3d	mNormal;
    AcGeVector3d	mHorizDir;
	//AcGePoint3d		mWcsChordPt;
    AcGeMatrix3d	mUcsToWcsMat;
    AcGeMatrix3d	mWcsToUcsMat;
    double			mElevation;
	AcDbDimDataPtrArray *mpDimDataArray;
};

__forceinline AcDbEntity* AcCircleJig::entity()const
{ return mpCircle; }

#endif //__ACCIRCLEJIG_H__
