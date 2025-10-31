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

#include "StdAfx.h"
#include "AsdkSimpleSquare.h"
#include <gcroot.h>
#include "mgdinterop.h"

namespace Autodesk
{
	namespace SimpleSquare
	{
		//////////////////////////////////////////////////////////////////////////
		// constructor for the managed wrapper.  This form creates the underlying unmanaged (square) object.
		Autodesk::SimpleSquare::MgSimpleSquare::MgSimpleSquare()
		:Autodesk::AutoCAD::DatabaseServices::Entity(new AsdkSimpleSquare(), true)
		{
			GetImpObj()->set_ManagedWrapper(this);
			m_pSquareModifiedHandler = NULL;
		}

		//////////////////////////////////////////////////////////////////////////
		// constructor for the managed wrapper  This form takes an already established unmanaged object
		// and simply attaches this wrapper to it.
		Autodesk::SimpleSquare::MgSimpleSquare::MgSimpleSquare(System::IntPtr unmanagedPointer, bool autoDelete)
		: Autodesk::AutoCAD::DatabaseServices::Entity(unmanagedPointer,autoDelete)
		{
			m_pSquareModifiedHandler = NULL;
		}

		//////////////////////////////////////////////////////////////////////////
		// Property to set the centre of the square
		void Autodesk::SimpleSquare::MgSimpleSquare::set_Center(Point3d point)
		{
		  Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->set_Center(GETPOINT3D(point)));
		}
		//////////////////////////////////////////////////////////////////////////
		// Property to get the center point
		Autodesk::AutoCAD::Geometry::Point3d Autodesk::SimpleSquare::MgSimpleSquare::get_Center()
		{
			return ToPoint3d (GetImpObj()->get_Center());
		}

		//////////////////////////////////////////////////////////////////////////
		// Property to set the rotation angle
		void Autodesk::SimpleSquare::MgSimpleSquare::set_Rotation(double rotation)
		{
			Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->set_Rotation(rotation));
		}

		//////////////////////////////////////////////////////////////////////////
		// Property to get the rotation angle
		double Autodesk::SimpleSquare::MgSimpleSquare::get_Rotation()
		{
			return GetImpObj()->get_Rotation();
		}

		//////////////////////////////////////////////////////////////////////////
		// Property to set the side length
		void Autodesk::SimpleSquare::MgSimpleSquare::set_SideLength(double sidelength)
		{
			Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->set_SideLength(sidelength));
		}

		//////////////////////////////////////////////////////////////////////////
		// Property to get the side length
		double Autodesk::SimpleSquare::MgSimpleSquare::get_SideLength()
		{
			return GetImpObj()->get_SideLength();
		}

		//////////////////////////////////////////////////////////////////////////
		// Property to set the normal
		void Autodesk::SimpleSquare::MgSimpleSquare::set_Normal(Vector3d normal)
		{
			Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->set_Normal(GETVECTOR3D(normal)));
		}

		//////////////////////////////////////////////////////////////////////////
		// Property to get the normal
		Vector3d Autodesk::SimpleSquare::MgSimpleSquare::get_Normal()
		{
			return ToVector3d(GetImpObj()->get_Normal());
		}

		//////////////////////////////////////////////////////////////////////////
		// Method to add a listener to the SquareModified event
		void Autodesk::SimpleSquare::MgSimpleSquare::add_SquareModified ( SquareModifiedHandler* pSquareModified )
		{
			m_pSquareModifiedHandler = static_cast< SquareModifiedHandler* >
						(Delegate::Combine( m_pSquareModifiedHandler, pSquareModified ));
		}
		//////////////////////////////////////////////////////////////////////////
		// Method to remove a listener to the SquareModified event
		void Autodesk::SimpleSquare::MgSimpleSquare::remove_SquareModified ( SquareModifiedHandler* pSquareModified )
		{
			m_pSquareModifiedHandler = static_cast< SquareModifiedHandler* >
				(Delegate::Remove( m_pSquareModifiedHandler, pSquareModified ));
		}
		//////////////////////////////////////////////////////////////////////////
		// Method to send the SquareModified event to all attached listeners.
		void Autodesk::SimpleSquare::MgSimpleSquare::raise_SquareModified( Autodesk::AutoCAD::DatabaseServices::ObjectId pObjectId )
		{
			if( m_pSquareModifiedHandler != NULL )
				m_pSquareModifiedHandler->Invoke(pObjectId);
		}
	}
}