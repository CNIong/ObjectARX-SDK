//
// (C) Copyright 2006-2007 by Autodesk, Inc. 
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


//-----------------------------------------------------------------------------
//----- AsdkSimpleSquare.cpp : Implementation of AsdkSimpleSquare
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "AsdkSimpleSquare.h"
#include <gcroot.h>


//-----------------------------------------------------------------------------
Adesk::UInt32 AsdkSimpleSquare::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	AsdkSimpleSquare, AcDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, ASDKSIMPLESQUARE,
	ASDKSimpleSquare
	"|Product Desc:     A description for your object"
	"|Company:          Your company name"
	"|WEB Address:      Your company WEB site address"
)

// Default Constructor
AsdkSimpleSquare::AsdkSimpleSquare () : AcDbEntity () , m_CenterPoint(0,0,0)
, m_Rotation(0)
, m_SideLength(0)
, m_Normal(0,0,1)
, m_pManaged(NULL)
{
}

AsdkSimpleSquare::~AsdkSimpleSquare () {
}

// Simply calculates the corner points from the center and rotation members.
void AsdkSimpleSquare::CalculateCornersFromRotationAndCenter()
{
	// Calculate the 4 corner points.  Just use the origin point and the side length.  We'll translate and rotate below...
	double halfSide = m_SideLength / 2.0f;
	// Upper Right
	m_ptUR = AcGePoint3d(halfSide, halfSide, 0);
	//Lower Right
	m_ptLR = AcGePoint3d(halfSide, 0 - halfSide, 0);
	//Lower Left
	m_ptLL =AcGePoint3d(0 - halfSide, 0 - halfSide, 0);
	//Upper Left
	m_ptUL= AcGePoint3d(0 - halfSide, halfSide, 0);
	
	// Now, apply the rotation and center point
	AcGeMatrix3d rotMat;
	rotMat.setToRotation(m_Rotation, AcGeVector3d(0,0,1));
	
	m_ptUR = m_ptUR.transformBy(rotMat) + m_CenterPoint.asVector();
	m_ptLR = m_ptLR.transformBy(rotMat) + m_CenterPoint.asVector();
	m_ptLL = m_ptLL.transformBy(rotMat) + m_CenterPoint.asVector();
	m_ptUL = m_ptUL.transformBy(rotMat) + m_CenterPoint.asVector();
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus AsdkSimpleSquare::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (AsdkSimpleSquare::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....
	// Write the center point
	if((es = pFiler->writePoint3d(m_CenterPoint)) != Acad::eOk)
		return es;
	// Write the normal
	if((es = pFiler->writeVector3d(m_Normal)) != Acad::eOk)
		return es;
	// Write the rotation
	if((es = pFiler->writeDouble(m_Rotation)) != Acad::eOk)
		return es;
	// Write the length of each side
	if((es = pFiler->writeDouble(m_SideLength)) != Acad::eOk)
		return es;

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus AsdkSimpleSquare::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > AsdkSimpleSquare::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < AsdkSimpleSquare::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....
	
	// Read the center point
	if((es = pFiler->readPoint3d(&m_CenterPoint)) != Acad::eOk)
		return es;

	// Read the normal
	if((es = pFiler->readVector3d(&m_Normal)) != Acad::eOk)
		return es;
	
	// Read the rotation
	if((es = pFiler->readDouble(&m_Rotation)) != Acad::eOk)
		return es;

	// Read the side length
	if((es = pFiler->readDouble(&m_SideLength)) != Acad::eOk)
		return es;

	// Calculate the corner points...
	CalculateCornersFromRotationAndCenter();
	
	return (pFiler->filerStatus ()) ;
}

// This is the method that gets called when the object is closed.
// In this example, we'll use this to determine whether the object was
// modified.  This assumes that if the object was opened for Write, then
// it was indeed modified - we'll send a message to any UNMANAGED
// listeners - so we first check whether the wrapper is actually attached.

Acad::ErrorStatus AsdkSimpleSquare::subClose ()
{
	Acad::ErrorStatus es;
	if((es = AcDbEntity::subClose()) != Acad::eOk)
		return es;

	// If write-enabled, assume it was modified.  Check the managed pointer.
	if(isWriteEnabled() == Adesk::kTrue && m_pManaged != NULL)
		// Call the method on the wrapper which will propagate to all managed
		// listeners of this event...
		m_pManaged->raise_SquareModified(ToObjectId(objectId()));
	return Acad::eOk;
}

//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean AsdkSimpleSquare::worldDraw (AcGiWorldDraw *mode) {
	assertReadEnabled () ;

	// Define an array of pointers to hold the corners
	AcGePoint3d *pts[4] = {&m_ptUR, &m_ptLR, &m_ptLL, &m_ptUL};

	// set the color the red
	mode->subEntityTraits().setColor(1);
	
	// if dragging, don't fill.
	if(mode->isDragging() == Adesk::kTrue)
		mode->subEntityTraits().setFillType(kAcGiFillNever);
	else
		mode->subEntityTraits().setFillType(kAcGiFillAlways);
	
	// Draw the polygon.
	mode->geometry().polygon(4, pts[0]);

	return (AcDbEntity::worldDraw (mode)) ;
}


//- Grip points protocol
Acad::ErrorStatus AsdkSimpleSquare::getGripPoints (
	AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds
) const {
	assertReadEnabled () ;
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new getGripPoints() method below (which is the default implementation)

	//clockwise from Upper Right...
	gripPoints.append(m_ptUR);
	gripPoints.append(m_ptLR);
	gripPoints.append(m_ptLL);
	gripPoints.append(m_ptUL);
	
	return Acad::eOk;
}

Acad::ErrorStatus AsdkSimpleSquare::moveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) {
	assertWriteEnabled () ;
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new moveGripPointsAt() method below (which is the default implementation)

	int gripUsed = indices[0]; // We're only interested in the first grip point...
	
	AcGePoint3d gripPt;

	switch (gripUsed)
	{
	case 0:
		gripPt = m_ptUR;
		break;
	case 1:
		gripPt = m_ptLR;
		break;
	case 2:
		gripPt = m_ptLL;
		break;
	case 3:
		gripPt = m_ptUL;
		break;
	}
	gripPt = gripPt + offset;

	AcGeVector3d vecToMovedGrip = gripPt - m_CenterPoint;

	// Update the side length...
	m_SideLength = vecToMovedGrip.length() * SIN45 * 2;

	// Update the rotation...subtract 45 to unbias the rotation.
	m_Rotation = vecToMovedGrip.angleOnPlane(AcGePlane(get_Center(), get_Normal())) - PI / 4;

	CalculateCornersFromRotationAndCenter();
	
	return Acad::eOk;
}

Acad::ErrorStatus AsdkSimpleSquare::getGripPoints (
	AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize, 
	const AcGeVector3d &curViewDir, const int bitflags
) const {
	assertReadEnabled () ;

	//----- If you return eNotImplemented here, that will force AutoCAD to call
	//----- the older getGripPoints() implementation. The call below may return
	//----- eNotImplemented depending of your base class.
	return eNotImplemented;
}

Acad::ErrorStatus AsdkSimpleSquare::moveGripPointsAt (
	const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset,
	const int bitflags
) {
	assertWriteEnabled () ;

	//----- If you return eNotImplemented here, that will force AutoCAD to call
	//----- the older getGripPoints() implementation. The call below may return
	//----- eNotImplemented depending of your base class.
	return eNotImplemented;
}

// Below are essentially the properties of the class.  Get and Set methods.

AcGePoint3d AsdkSimpleSquare::get_Center()
{
	return m_CenterPoint;
}

Acad::ErrorStatus AsdkSimpleSquare::set_Center(AcGePoint3d center)
{
	m_CenterPoint = center;
	CalculateCornersFromRotationAndCenter();
	return Acad::eOk;
}

double AsdkSimpleSquare::get_Rotation()
{
	return m_Rotation;
}

Acad::ErrorStatus AsdkSimpleSquare::set_Rotation(double rotation)
{
	m_Rotation = rotation;
	CalculateCornersFromRotationAndCenter();
	return Acad::eOk;
}

double AsdkSimpleSquare::get_SideLength()
{
	return m_SideLength; 
}

Acad::ErrorStatus AsdkSimpleSquare::set_SideLength(double sidelength)
{
	m_SideLength = sidelength;
	CalculateCornersFromRotationAndCenter();
	return Acad::eOk;
}

AcGeVector3d AsdkSimpleSquare::get_Normal()
{
	return m_Normal;
}

Acad::ErrorStatus AsdkSimpleSquare::set_Normal(AcGeVector3d normal)
{
	m_Normal = normal;
	CalculateCornersFromRotationAndCenter();
	return Acad::eOk;
}

void AsdkSimpleSquare::set_ManagedWrapper(gcroot<Autodesk::SimpleSquare::MgSimpleSquare*> p)
{
	m_pManaged = p;
}
