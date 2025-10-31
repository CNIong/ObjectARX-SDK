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

