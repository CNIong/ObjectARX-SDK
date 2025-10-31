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

