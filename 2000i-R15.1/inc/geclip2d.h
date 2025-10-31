#ifndef AC_GECLIP2D_H
#define AC_GECLIP2D_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// This file contains the class AcGeClipBoundary2d - An implementation similar
// to the Sutherland-Hodgman pipeline clipping algorithm, for clipping
// arbitrary 2d polygons or polylines to 2d convex polygons or rectangles.  
//
// Detailed edge information can be generated to track the source of each clipped
// output segment. This can be used to control edge display or to efficiently stitch together
// output from multiple clip boundaries (possibly from decomposing a non-convex clip
// boundary into multiple convex boundaries.)
//


#include "adesk.h"
#include "assert.h"
#include "geent2d.h"
#include "gepnt2d.h"
#include "gept2dar.h"
#include "gegbl.h"
#include "geintarr.h"
#pragma pack (push, 8)

class AcGeImpClipBoundary2d;

class
GE_DLLEXPIMPORT
AcGeClipBoundary2d : public AcGeEntity2d
{
public:

    AcGeClipBoundary2d();

    // Initialize for ortho-aligned rectangular clip boundary.
    //
    AcGeClipBoundary2d(const AcGePoint2d& cornerA, const AcGePoint2d& cornerB);

    // Initialize for convex polyline/polygon clip boundary (1 or more edges).  
    //
    AcGeClipBoundary2d(const AcGePoint2dArray& clipBoundary);
   
	// Copy constructor.
	//
	AcGeClipBoundary2d (const AcGeClipBoundary2d& src);

    // Notes on set() methods:
    // 1) set() need be called only once after the creation of the clipper.  
    //    The clipper can then be reused by calling
    //    clipPolygon or clipPolyline repeatedly.

    // Initialize for ortho-aligned rectangular clip boundary.
    //
	AcGe::ClipError		set(const AcGePoint2d& cornerA, const AcGePoint2d& cornerB);

    // Initialize for convex polyline/polygon clip boundary (1 or more edges).  
    // 1) Counterclockwise orientation is
    //    assumed if there is only one non-colinear clipping edge in the polygon.
    // 2) If more than one non-colinear edge is supplied, the orientation of the edges
    //    is computed automagically.
    //
    AcGe::ClipError		set(const AcGePoint2dArray& clipBoundary);

    // Optional clipped segment source information (below) is interpreted as follows:
    // Let srcInx(n) := (*pClippedSegmentSourceLabel).at(n).
    //
    // Case 1: If srcInx(n) > 0, then segment number "n", connecting
    //      output vertices "n-1" and "n", is a piece of source segment "srcInx(n)", connecting
    //      input vertices "srcInx(n)-1" and "srcInx(n)".
    // Case 2: If srcInx(n) < 0, then it is a piece of clip boundary segment "srcInx(n)", connecting
    //      clip boundary vertices "srcInx(n)-1" and "srcInx(n)".
	//
	// Notes: 
    // 1)   srcInx(0), which doesn't correspond to a segment, should be ignored.
    // 2)   Degenerate clip boundary edges and polyline/polygon segments are skipped, so the
    //      srcInx() values aren't necessarily sequential.
    //
    
    // Clip a closed polygon, creating a second closed polygon.
    //
    AcGe::ClipError		clipPolygon(const AcGePoint2dArray& rawVertices, 
                                    AcGePoint2dArray& clippedVertices,
                                    AcGe::ClipCondition& clipCondition,
                                    AcGeIntArray* pClippedSegmentSourceLabel = 0) const;

    // Clip a polyline, creating a second polyline.
    //
    AcGe::ClipError		clipPolyline(const AcGePoint2dArray& rawVertices, 
                                     AcGePoint2dArray& clippedVertices,
                                     AcGe::ClipCondition& clipCondition,
                                     AcGeIntArray* pClippedSegmentSourceLabel = 0) const;

    // Assignment operator.
    //
    AcGeClipBoundary2d& operator = (const AcGeClipBoundary2d& crvInt);
};


#pragma pack (pop)
#endif
