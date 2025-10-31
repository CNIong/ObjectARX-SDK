#ifndef AMODELER_INC_VERTDATA_H
#define AMODELER_INC_VERTDATA_H


///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1996 by Autodesk, Inc.
//
// The information contained herein is confidential, proprietary
// to Autodesk,  Inc.,  and considered a trade secret as defined
// in section 499C of the penal code of the State of California.
// Use of  this information  by  anyone  other  than  authorized
// employees of Autodesk, Inc.  is granted  only under a written
// non-disclosure agreement,  expressly  prescribing  the  scope
// and manner of such use.
//
// CREATED BY:  Jiri Kripac                     January-1-1996
//
// DESCRIPTION:
//
// Polygons are used as input to sweep operations.
//
// Each polygon may have PolygonVertexData attributes attached to its vertices. 
// We call such polygons "augmented polygons." The type of the attached 
// PolygonVertexData object may be:
// 
//    kArc3d         ...  There is an arc between this polygon vertex and the 
//                        next one. The Circle3d object and the approximation
//                        are given as parameters to the constructor when 
//                        creating the PolygonVertexData object.
//                        
//                        To represent a full circle, use an augmented polygon  
//                        containing just a single vertex with a kArc3d 
//                        PolygonVertexData object. 
//
//    kArcByRadius   ...  There is an arc between this polygon vertex and the
//                        next one. The radius or the arc and the approximation
//                        are given as parameters to the constructor when creating
//                        the PolygonVertexData object. Radius > 0 means CCW, < 0 
//                        means CW orientation of the arc with reference to the
//                        polygon normal. The isCenLeft argument tells whether the
//                        center of the arc lies to the left from the edge of the
//                        polygon (in other words, it is inside the polygon). The 
//                        default is "true."
//
//    kArcByBulge    ...  There is an arc between this polygon vertex and the
//                        next one. The bulge and the approximation are given 
//                        as parameters to the constructor when creating the
//                        PolygonVertexData object.
//
//    kFilletByRadius ... The polygon vertex is filleted. The filleting radius 
//                        and the approximation are given as parameters to the
//                        constructor when creating the PolygonVertexData object.
//
// Any operation which accepts polygons first expands the augmented polygon
// to a simple polygon by generating additional vertices approximating the
// arcs, as defined by the PolygonVertexData objects.
//
// Note: The kArcByRadius and kArcByBulge options cannot be used when the 
//       polygon is used as a path for the extrusion along the path because  
//       the path may be non-planar and the polygon normal may not be defined.
//
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// NOTE: In the previous version of AModeler, the PolygonVertexData was 
//       related to the segment coming TO the current vertex. 
//
//       This has changed: Now the PolygonVertexData relates to the segment 
//       coming FROM the current vertex.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//
///////////////////////////////////////////////////////////////////////////////

#include "circle3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp PolygonVertexData
{
public:

    enum Type { kArc3d, kArcByRadius, kArcByBulge, kFilletByRadius };

    PolygonVertexData(Type, const Circle3d&, int apprx);             // kArc3d
    PolygonVertexData(Type, double rad, bool isCenLeft, int apprx);  // kArcByRadius
    PolygonVertexData(Type, double bulgeOrRadius, int apprx);        // kArcByBulge or kFilletByRadius

    Type     type;
    Circle3d circle;
    int      approx;
    bool     isCenterLeft;
    double   bulge;
    Curve*   curve;
    Surface* surface;

}; // class PolygonVertexData


AMODELER_NAMESPACE_END
#endif
