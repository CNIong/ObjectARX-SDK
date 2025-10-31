#ifndef AMODELER_INC_UTIL_H
#define AMODELER_INC_UTIL_H


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
// Some internal utility stuff which I didn't know where else to put.
//
///////////////////////////////////////////////////////////////////////////////

#include "global.h"

AMODELER_NAMESPACE_BEGIN


DllImpExp void appendDxfExtension(const char inFileName[], char outFileName[]);


DllImpExp double  arcToBulge   (const Point2d& p1, const Point2d& p2, const Point2d& center);
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

