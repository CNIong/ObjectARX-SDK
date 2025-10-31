#ifndef AMODELER_INC_POLYGON_H
#define AMODELER_INC_POLYGON_H

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
///////////////////////////////////////////////////////////////////////////////

#include "point2d.h"
#include "point3d.h"
#include "vertdata.h"

AMODELER_NAMESPACE_BEGIN


DllImpExp void expandAugmentedPolygonToSimplePolygon(
                   const Point3d        plg[],
                   PolygonVertexData*   vertexData[],
                   int                  numVertices,
                   const Vector3d&      plgNormal,
                   bool                 isPlanar,  // true==planar polygon, false==non planar polygon (3d path)
                   Point3d*&            simplePlg,                           
                   PolygonVertexData**& simplePlgVertexData,
                   int&                 simplePlgNumVertices,
                   Plane&               simplePlgPlane);


// Needed just for edge filetting, will be removed
//
void filletVertex(Point2d       p1,
                 Point2d        p2,
                 Point2d        p3,
                 double         radius,
                 Point2d&       start,
                 Point2d&       center,
                 Point2d&       end,
                 bool&          isCcw);

double polygonLength(Point3d* plg, int numVertices, bool isClosed);


// Internal functions, used for revolution and endpoint revolution
//
void transformAugmentedPlgToXYandAxisToXAndExpand
                        (const Point3d            plg[],
                         PolygonVertexData*       vertexData[],
                         int                      m, 
                         const Line3d&            axis,
                         int                      approx,
                         const Vector3d&          plgNormal,   
                         Point3d*&                simplePlg,
                         Surface**&               surfaces,
                         int&                     n,   // Simple plg # of vertices
                         Transf3d&                t);

// Used for extrusion and pyramid
//
void transformAugmentedPlgToXYAndExpand
                        (const Point3d            plg[],
                         PolygonVertexData*       vertexData[],
                         int                      m, 
                         const Vector3d&          plgNormal,   
                         bool                     extrusionOrPyramid,  // Extrusion==true, pyramid==flase
                         Vector3d&                vector,       // Will be transformed
                         Point3d&                 apex,         // Vill be transformed  
                         Point3d*&                simplePlg,
                         Surface**&               surfaces,
                         int&                     n,   // Simple plg # of vertices
                         Transf3d&                t);

// Can be called only after expandAugmentedPolygonToSimplePolygon() when the
// circles in VertexData have already been evaluated
//
Vector3d polygonStartOrEndTangent(const Point3d      plg[],
                                  PolygonVertexData* vertexData[],
                                  int                numVertices,
                                  bool               startOrEnd /*true==start, false==end*/);


AMODELER_NAMESPACE_END
#endif
