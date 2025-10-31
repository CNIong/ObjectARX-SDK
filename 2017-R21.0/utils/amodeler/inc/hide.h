///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
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
