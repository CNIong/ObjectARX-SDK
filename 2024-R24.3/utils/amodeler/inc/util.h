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
// General utilities.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_UTIL_H
#define AMODELER_INC_UTIL_H


#include "global.h"

AMODELER_NAMESPACE_BEGIN


DllImpExp void appendDxfExtension(const wchar_t inFileName[], wchar_t outFileName[]);


DllImpExp double  arcToBulge   (const Point2d& p1, const Point2d& p2, const Point2d& pointOnArc, const Point2d& center);
DllImpExp void    bulgeToCircle(const Point2d& p1, const Point2d& p2, double bulge, Point2d& center, double& radius);

DllImpExp void getAllConnectedEdgesSharingVertex(const Edge* oneEdge, Darray& allEdges);

DllImpExp bool    profilesOrdered(const Body&, const Body&);

DllImpExp Edge*   breakEdge     (Body&, const Point3d&);
DllImpExp Edge*   breakEdge     (Body&, const Point3d& p1, const Point3d& p2);

DllImpExp Vertex* findVertex    (const Body&, const Point3d&);
DllImpExp Edge*   findEdge      (const Body&, const Point3d&, const Point3d&);
DllImpExp void    findFace      (const Body&, const Plane&, Darray& facesFound);

DllImpExp void    printFace     (Face*  );
DllImpExp void    printEdge     (Edge*  );
DllImpExp void    printVertex   (Vertex*);

DllImpExp void extremeVertices  (const Body&, const Vector3d& dir, Vertex*& vMin, Vertex*& vMax);

AMODELER_NAMESPACE_END
#endif

