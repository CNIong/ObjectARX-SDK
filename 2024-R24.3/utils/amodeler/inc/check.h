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
// Functions checking the validity of input parameters.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_CHECK_H
#define AMODELER_INC_CHECK_H


#include "global.h"

AMODELER_NAMESPACE_BEGIN

DllImpExp void checkProfile    (const Body& profileBody);
DllImpExp void checkMorphingMap(const MorphingMap& morphingMap, int numEdges0, int numEdges1);

DllImpExp void checkFaceAgainstAxis(Face*, const Line3d& axis);

DllImpExp bool isPolygonSelfIntersecting(const Point3d plg[], int numEdges, int i1, int i2);

DllImpExp ErrorCode checkPolygon(const Point3d   plg[], 
                                 int             numEdges,
                                 const Plane&    plgPlane, 
                                 const Vector3d& plgNormal);


AMODELER_NAMESPACE_END
#endif

