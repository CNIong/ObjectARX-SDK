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
//
//-----------------------------------------------------------------------------
//----- AsdkSimpleSquare.h : Declaration of the AsdkSimpleSquare
//-----------------------------------------------------------------------------
#pragma once

#ifdef SIMPLESQUARE_MODULE
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

//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "dbmain.h"
#include "gepnt3d.h"

using namespace System;
using namespace Autodesk::AutoCAD::Geometry;
using namespace Autodesk::AutoCAD::DatabaseServices;

class AsdkSimpleSquare;

namespace Autodesk
{
	namespace SimpleSquare
	{
		// Declare a delegate which represents the event handler for our SquareModified event
		public __delegate void SquareModifiedHandler(ObjectId pObjectId);
		
		// Define the managed class which derives from Entity, including the Wrapper attribute indicating that this
		// class wraps the unmanaged class AsdkSimpleSquare.
		[Autodesk::AutoCAD::Runtime::Wrapper("AsdkSimpleSquare")]
		public __gc class MgSimpleSquare :  public Autodesk::AutoCAD::DatabaseServices::Entity
		{
		public:
			MgSimpleSquare(void);

        public private:
            MgSimpleSquare(System::IntPtr unmanagedPointer, bool autoDelete);
        
			// Here is the method which will consistently give us our unmanaged (AsdkSimpleSquare) object.
			inline AsdkSimpleSquare*  GetImpObj()
            {
				// UnmanagedObject() is a method of the AutoCAD managed wrappers which always
				// gives us a way to access the underlying ObjectARX objects so we can use them
				// within our C++ application freely.
				return static_cast<AsdkSimpleSquare*>(UnmanagedObject.ToPointer());
            }

        public:

			// Declaration of the properties (get and set) for what we want to expose to the managed world.

		__property void set_Center(Point3d point);
        __property Point3d get_Center();

		__property void set_Rotation(double rotation);
		__property double get_Rotation();

		__property void set_SideLength(double sidelength);
		__property double get_SideLength();
		
		__property void set_Normal(Vector3d normal);
		__property Vector3d get_Normal();

		// Here are the methods defied to support exposure of our event.

		__event void add_SquareModified // Called to add listeners
				( SquareModifiedHandler* pSquareModified );
		__event void remove_SquareModified // Called to remove listeners.
				( SquareModifiedHandler* pSquareModified );

		private public:
			// Called to send the SquareModified event to all attached managed listeners.
			__event void raise_SquareModified( Autodesk::AutoCAD::DatabaseServices::ObjectId pObjectId );

		private:
			// Here is our member delegate which represents the event for this object.
			SquareModifiedHandler* m_pSquareModifiedHandler;
		};
	}
}

// Note - a straightforward custom entity which only defines a red-square with grip points at each corner.
// Note here that AsdkSimpleSquare cannot be exported with DLLIMPEXP or __declspec(dllexport) because
// it has managed components.  This is ok for the enabler since AutoCAD receives a pointer from the 
// pseudo constructor in ACRX_DEFINE_DXF_MEMBERS.  However for UI components, this limits us to managed
// applications that can access the class.

class AsdkSimpleSquare : public AcDbEntity {

private:
	AcGePoint3d m_ptUR, m_ptLR, m_ptLL, m_ptUL; // The corner points - not persisted.
	AcGePoint3d m_CenterPoint; // center point - is persisted
	AcGeVector3d m_Normal; // normal - is persisted
	double m_Rotation; // Rotation angle - is persisted.
	double m_SideLength; // Length of each side - is persisted
	gcroot<Autodesk::SimpleSquare::MgSimpleSquare*>m_pManaged; // the managed wrapper pointer.  

public:
	ACRX_DECLARE_MEMBERS(AsdkSimpleSquare) ;

protected:
	static Adesk::UInt32 kCurrentVersionNumber ;

private:
	void CalculateCornersFromRotationAndCenter();

public:
	AsdkSimpleSquare ();

	virtual ~AsdkSimpleSquare () ;

	//----- AcDbObject protocols
	//- Dwg Filing protocol
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

	//- SubXXX() methods (self notification)
	virtual Acad::ErrorStatus subClose () ;

	//----- AcDbEntity protocols
	//- Graphics protocol
	virtual Adesk::Boolean worldDraw (AcGiWorldDraw *mode) ;

	//- Grip points protocol
	virtual Acad::ErrorStatus getGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const ;
	virtual Acad::ErrorStatus moveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) ;
	virtual Acad::ErrorStatus getGripPoints (
		AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize, 
		const AcGeVector3d &curViewDir, const int bitflags) const ;
	virtual Acad::ErrorStatus moveGripPointsAt (const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset, const int bitflags) ;

	AcGePoint3d get_Center();
	Acad::ErrorStatus set_Center(AcGePoint3d center);
	double get_Rotation();
	Acad::ErrorStatus set_Rotation(double rotation);
	double get_SideLength();
	Acad::ErrorStatus set_SideLength(double sidelength);
	AcGeVector3d get_Normal();
	Acad::ErrorStatus set_Normal(AcGeVector3d normal);

	void set_ManagedWrapper(gcroot<Autodesk::SimpleSquare::MgSimpleSquare*> p);
} ;

#ifdef SIMPLESQUARE_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(AsdkSimpleSquare)
#endif
