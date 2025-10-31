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
// Polygons are used as input to sweep operations.
//
// Each polygon may have PolygonVertexData attributes attached to its vertices. 
// We call such polygons "augmented polygons." The PolygonVertexData object 
// relates to the polygon segment between the current polygon vertex and the
// next one.
//
// The type of the PolygonVertexData object may be:
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
//    kUnspecifiedCurve ... The segment between this polygon vertex and the next 
//                        one belongs to an unspecified curve. When the same
//                        PolygonVertexData object of type kUnspecifiedCurve is
//                        used several times in a PolygonVertexData array, all
//                        the segments that refer to the same PolygonVertexData
//                        object will belong to the same unspecified curve, thus
//                        grouping these segments together. 
//
//                        This grouping of segments is then taken into account 
//                        when the augmented polygon is extruded and surfaces
//                        generated. A single unspecified surface is generated 
//                        for all polygon segments that refer to the same 
//                        PolygonVertexData of kUnspecifiedCurve type. This way
//                        the corresponding faces in the extrusion solid are
//                        grouped together by a single unspecified surface. This
//                        also allows, among others, the vertex normal averaging, 
//                        producing smooth renderings of the faces belonging to
//                        the same unspecified surface.
// 
// Any operation which accepts polygons first expands the augmented polygon
// to a simple polygon by generating additional vertices approximating the
// arcs, as defined by the PolygonVertexData objects.
//
// Note: The kArcByRadius and kArcByBulge options cannot be used when the 
//       polygon is used as a path for the extrusion along the path because  
//       the path may be non-planar and the polygon normal may not be defined.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_VERTDATA_H
#define AMODELER_INC_VERTDATA_H


#include "circle3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp PolygonVertexData
{
public:

    enum Type { kArc3d, kArcByRadius, kArcByBulge, kFilletByRadius, kUnspecifiedCurve };

    PolygonVertexData(Type);                                         // kUnspecifiedCurve
    PolygonVertexData(Type, const Circle3d&, int apprx);             // kArc3d
    PolygonVertexData(Type, double rad, bool isCenLeft, int apprx);  // kArcByRadius
    PolygonVertexData(Type, double bulgeOrRadius, int apprx);        // kArcByBulge or kFilletByRadius

    bool isArc() const 
    { 
        return type == kArc3d || type == kArcByRadius || type == kArcByBulge || type == kFilletByRadius; 
    }

public: // data

    Type     type;
    Circle3d circle;
    int      approx;
    bool     isCenterLeft;
    double   bulge;
    Curve*   curve;
    Surface* surface;

}; // class PolygonVertexData



// Deletes the VertexData objects the vertexDataArray points to and sets the
// pointers to NULL. If alsoDeleteArray is true, it also deletes the array,
// otherwise it does not
//
DllImpExp void deleteVertexData(PolygonVertexData* vertexDataArray[], int arrayLength, bool alsoDeleteArray);


AMODELER_NAMESPACE_END
#endif
