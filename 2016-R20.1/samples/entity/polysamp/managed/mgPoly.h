//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// mgPoly.h

#pragma once
#include <tchar.h>
using namespace System;
using namespace Autodesk::AutoCAD::Geometry;
using namespace Autodesk::AutoCAD::DatabaseServices;

namespace Autodesk {
    namespace ObjectDbxSample
    {
        [Autodesk::AutoCAD::Runtime::Wrapper("AsdkPoly")]
        public __gc class Poly :  public Autodesk::AutoCAD::DatabaseServices::Curve
        {

        public:
            Poly();

        public private:
            Poly(System::IntPtr unmanagedPointer, bool autoDelete);
            inline AsdkPoly*  GetImpObj()
            {
                return static_cast<AsdkPoly*>(UnmanagedObject.ToPointer());
            }

        public:
        __property void set_Center(Point2d point);
        __property Point2d get_Center();

        __property void set_StartPoint2d(Point2d point);
        __property Point2d get_StartPoint2d();

        __property void set_NumberOfSides(long value);
        __property long get_NumberOfSide();

        __property void set_Normal(Vector3d vector);
        __property Vector3d get_Normal();

        __property void set_Elevation(double value);
        __property double get_Elevation();
        
        __property void set_Name(String* value);
        __property String* get_Name();

        __property void set_TextStyle(Autodesk::AutoCAD::DatabaseServices::ObjectId value);

        __property  Point2dCollection* get_Vertices();

        //static __property bool get_UseDragData();
        //static __property void set_UseDragData(bool value);

        //__property virtual bool get_Closed();
        //__property virtual bool get_IsPeriodic();
        //__property virtual bool get_IsPlanar(); this is missing from Curve!

        //__property virtual double get_StartParam();
        //__property virtual double get_EndParam();

        //AcGeVector3d GetSideVector(int whichSide);

        };
    }

}