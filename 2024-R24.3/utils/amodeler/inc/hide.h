///////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form. 
//
// DESCRIPTION:
//
// Variables and functions needed in hide.cpp as well as in pick.cpp and 
// drawing.cpp.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_HIDE_H
#define AMODELER_INC_HIDE_H

#include <limits.h>
#include "transf3d.h"

AMODELER_NAMESPACE_BEGIN


const int kHideIntMax = INT_MAX/4 - 4; // Integer range <-kHideIntMax;kHideIntMax>



class DllImpExp HideIntegerTransform
{
public:

    Point3d projectedIntToProjectedDouble(IntPoint3d ip) const
    {
        return Point3d(mRx*ip.x+mSx, mRy*ip.y+mSy, mRz*ip.z+mSz);
    }

    double mRx, mSx; // Back transfrom int --> double
    double mRy, mSy; // E.g.: xDouble = mRx*xInt+mSx
    double mRz, mSz;
};



enum PointInPolygonLocation
{
    kPointOutsidePolygon      =  0,  // Point not hidden by the polygon
    kPointBehindPolygonVertex =  1,
    kPointBehindPolygonEdge   =  2,
    kPointBehindPolygonFace   =  3,  // Point regularly hidden by the polygon
    kPointAtPolygonVertex     = -1,
    kPointOnPolygonEdge       = -2,
    kPointInPolygonFace       = -3
};


PointInPolygonLocation pointInPolygonTest(IntPoint3d p, Face* f, int* zPtr = NULL);


AMODELER_NAMESPACE_END
#endif
