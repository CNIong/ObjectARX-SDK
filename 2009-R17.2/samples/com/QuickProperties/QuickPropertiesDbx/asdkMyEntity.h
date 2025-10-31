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

//-----------------------------------------------------------------------------
//----- asdkMyEntity.h : Declaration of the asdkMyEntity
//-----------------------------------------------------------------------------
#pragma once

#ifdef QUICKPROPERTIESDBX_MODULE
#define DLLIMPEXP __declspec(dllexport)
#else
//----- Note: we don't use __declspec(dllimport) here, because of the
//----- "local vtable" problem with msvc. If you use __declspec(dllimport),
//----- then, when a client dll does a new on the class, the object's
//----- vtable pointer points to a vtable allocated in that client
//----- dll. If the client dll then passes the object to another dll,
//----- and the client dll is then unloaded, the vtable becomes invalid
//----- and any virtual calls on the object will access invalid memory.
//-----
//----- By not using __declspec(dllimport), we guarantee that the
//----- vtable is allocated in the server dll during the ctor and the
//----- client dll does not overwrite the vtable pointer after calling
//----- the ctor. And, since we expect the server dll to remain in
//----- memory indefinitely, there is no problem with vtables unexpectedly
//----- going away.
#define DLLIMPEXP
#endif

//////////////////////////////////////////////////////////////////////////
#include "dbents.h"

//////////////////////////////////////////////////////////////////////////
#define DECLARE_MEMBER_VARIABLE(_dtypeX,_varNameY) \
public:\
  virtual _dtypeX mGet##_varNameY() {assertReadEnabled();return _varNameY;};	\
  virtual _dtypeX mSet##_varNameY(_dtypeX newValue){assertWriteEnabled();_varNameY = newValue; return _varNameY;} \
private: \
  _dtypeX _varNameY; \
public:
//////////////////////////////////////////////////////////////////////////
#define DECLARE_STRING_MEMBER_VARIABLE(_dtypeX,_varNameY) \
public:\
  virtual _dtypeX mGet##_varNameY() {assertReadEnabled();return _varNameY;};	\
  virtual _dtypeX mSet##_varNameY(_dtypeX newValue){assertWriteEnabled();delete _varNameY; _varNameY=_tcsdup(newValue); return _varNameY;} \
private: \
  _dtypeX _varNameY; \
public:
//////////////////////////////////////////////////////////////////////////
class DLLIMPEXP asdkMyEntity : public AcDbLine 
{

public:
	ACRX_DECLARE_MEMBERS(asdkMyEntity) ;

protected:
	static Adesk::UInt32 kCurrentVersionNumber ;

public:
	asdkMyEntity () ;
	virtual ~asdkMyEntity () ;

	//----- AcDbObject protocols
	//- Dwg Filing protocol
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

	//----- AcDbEntity protocols
	//- Graphics protocol
	virtual Adesk::Boolean worldDraw (AcGiWorldDraw *mode) ;

  // -----------------------------------------------------------------------------
  virtual Acad::ErrorStatus getClassID(CLSID * pClsid) const;

private:

  // some member variables
  DECLARE_MEMBER_VARIABLE(Adesk::Int16, MyType);
  DECLARE_MEMBER_VARIABLE(AcGePoint3d, MyPointValue);
  
  // for box, just made up properties
  DECLARE_STRING_MEMBER_VARIABLE(TCHAR *, MyTextString);
  DECLARE_MEMBER_VARIABLE(double, MyRotation);
  DECLARE_MEMBER_VARIABLE(double, MyLength);

  // for sphere, just made up properties
  DECLARE_MEMBER_VARIABLE(Adesk::Int16, MyDropDown);
  DECLARE_MEMBER_VARIABLE(double, MySurfaceArea);

  // for cylinder, just made up properties
  DECLARE_MEMBER_VARIABLE(double, MyRadius);
  DECLARE_MEMBER_VARIABLE(double, MyHeight);
  DECLARE_MEMBER_VARIABLE(double, MyWidth);
} ;

//////////////////////////////////////////////////////////////////////////
ACDB_REGISTER_OBJECT_ENTRY_AUTO(asdkMyEntity)
