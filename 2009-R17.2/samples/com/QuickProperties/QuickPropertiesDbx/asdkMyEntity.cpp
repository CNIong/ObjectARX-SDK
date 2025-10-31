// (C) Copyright 2002-2008 by Autodesk, Inc. 
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

//////////////////////////////////////////////////////////////////////////
//      asdkMyEntity.cpp : Implementation of asdkMyEntity
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "asdkMyEntity.h"

//////////////////////////////////////////////////////////////////////////
Adesk::UInt32 asdkMyEntity::kCurrentVersionNumber =1 ;

//////////////////////////////////////////////////////////////////////////
ACRX_DXF_DEFINE_MEMBERS (
	asdkMyEntity, AcDbLine,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, asdkMyEntity,
	"ADSKQUICKPROPERTIESDBXAPP"
	"|Product Desc:     A description for your object"
	"|Company:          Your company name"
	"|WEB Address:      Your company WEB site address"
)

//////////////////////////////////////////////////////////////////////////
asdkMyEntity::asdkMyEntity () : AcDbLine () 
{
  mSetMyType(0);
  mSetMyPointValue(AcGePoint3d(100,200,0));

  // for box, just made up properties
  mSetMyTextString(_tcsdup(_T("Autodesk Inc"))); // always create an empty string as readItem will free it automatically
  mSetMyRotation(1.23);
  mSetMyLength(100);
  // for sphere, just made up properties
  mSetMyDropDown(1);
  mSetMySurfaceArea(10000);

  // for cylinder, just made up properties
  mSetMyRadius(50.3);
  mSetMyHeight(200);
  mSetMyWidth(255);
}
//////////////////////////////////////////////////////////////////////////
asdkMyEntity::~asdkMyEntity () 
{
}

//////////////////////////////////////////////////////////////////////////
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus asdkMyEntity::dwgOutFields (AcDbDwgFiler *pFiler) const 
{
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es = AcDbLine::dwgOutFields (pFiler) ;
	if (es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ((es =pFiler->writeUInt32 (asdkMyEntity::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

  // some member variables, these don't really do anything they are just there for OPM demonstration purposes
  pFiler->writeItem(MyType);
  pFiler->writeItem(MyPointValue);

  // for box, just made up properties
  pFiler->writeItem(MyTextString);
  pFiler->writeItem(MyRotation);
  pFiler->writeItem(MyLength);

  // for sphere, just made up properties
  pFiler->writeItem(MyDropDown);
  pFiler->writeItem(MySurfaceArea);

  // for cylinder, just made up properties
  pFiler->writeItem(MyRadius);
  pFiler->writeItem(MyHeight);
  pFiler->writeItem(MyWidth);

	return (pFiler->filerStatus ()) ;
}

//////////////////////////////////////////////////////////////////////////
Acad::ErrorStatus asdkMyEntity::dwgInFields (AcDbDwgFiler *pFiler) 
{
	assertWriteEnabled () ;

  //----- Read parent class information first.
	Acad::ErrorStatus es =AcDbLine::dwgInFields (pFiler) ;
	if (es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ((es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if (version > asdkMyEntity::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if (version < asdkMyEntity::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....
  
  // find out which version of the object we are reading
  switch (asdkMyEntity::kCurrentVersionNumber)
  {
    case 1:
    {
      // some member variables
      pFiler->readItem(&MyType);
      pFiler->readItem(&MyPointValue);

      // for box, just made up properties
      pFiler->readItem(&MyTextString);
      pFiler->readItem(&MyRotation);
      pFiler->readItem(&MyLength);

      // for sphere, just made up properties
      pFiler->readItem(&MyDropDown);
      pFiler->readItem(&MySurfaceArea);

      // for cylinder, just made up properties
      pFiler->readItem(&MyRadius);
      pFiler->readItem(&MyHeight);
      pFiler->readItem(&MyWidth);

    }break;
  }

	return (pFiler->filerStatus ()) ;
}

//////////////////////////////////////////////////////////////////////////
// draw routine
Adesk::Boolean asdkMyEntity::worldDraw (AcGiWorldDraw *mode) 
{
	assertReadEnabled ();

  // if thickness is required
  if (mGetMyType() == 2)
    mode->subEntityTraits().setLineWeight(AcDb::kLnWt211);

  // draw the line
  AcDbLine::worldDraw(mode);

  // throw down 
  mode->subEntityTraits().setSelectionMarker(1);
  // if type == line with text or thick line with text
  if (mGetMyType())
  {
    AcGePoint3d textPosition = startPoint() + ((endPoint() - startPoint()) / 2.0);
    // draw the text
    mode->geometry().text(textPosition, AcGeVector3d::kZAxis, AcGeVector3d::kXAxis, mGetMyHeight(), 1, 0, mGetMyTextString());
  }

  return (Adesk::kFalse);
}

//////////////////////////////////////////////////////////////////////////
// {4DF765BB-80F1-40ca-9506-A22BE3B857AB}
static const GUID CLSID_MyEntityWrapper = { 0xBA415977,0x05AE,0x4167, { 0x84,0x70,0x9D,0x04,0xC6,0xC1,0x52,0xE2 } };
//////////////////////////////////////////////////////////////////////////
// returns the class id of the Object Properties Class for this object
Acad::ErrorStatus asdkMyEntity::getClassID(CLSID * pClsid) const
{
  *pClsid = CLSID_MyEntityWrapper;

  return (Acad::eOk);
}
