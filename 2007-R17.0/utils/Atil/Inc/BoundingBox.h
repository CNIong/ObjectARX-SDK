///////////////////////////////////////////////////////////////////////////////
//
//
//  (C) Copyright 2005 by Autodesk, Inc.  All rights reserved.
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
///////////////////////////////////////////////////////////////////////////////

#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef OFFSET_H
#include "Offset.h"
#endif

#ifndef SIZE_H
namespace Atil { class Size; }
#endif

#ifndef POINT2D_H
namespace Atil { class Point2d; }
#endif

#ifndef  BOUNDINGBOX_H
#define  BOUNDINGBOX_H

namespace Atil
{
// Implements a simple bounding box; provides methods to get intersections 
// and unions with other BoundingBox objects. 
//
class BoundingBox 
{
public:
    BoundingBox ();
    BoundingBox (Offset offset, Size size);
    BoundingBox (Offset origin, Offset extent);
    // Calcualtes the minimum bounding box defined by an array of offsets and
    // constructs a BoundingBox object from those extents.
    // The arguments are:
    // <param name='nPoints'>the number of points in the array of offsets;</param>
    // <param name='aOffsets'>an array of offsets used to calculate the
    // bounding box extents.</param>
    BoundingBox (int nPoints, const Offset* aOffsets);
    ~BoundingBox ();

    void set (Offset offset, Size size);
    void set (Offset origin, Offset extent);
    void set (int nPoints, const Offset* aOffsets);

    void expandToInclude (Offset offset);
    void expandToInclude (int nPoints, const Offset* aOffsets);

    void   getExtents (Offset& origin, Offset& extent) const;
    Size   size () const;
    Offset origin () const ;
    bool   inBounds (const Offset& offset) const;
    bool   inBounds ( int x, int y ) const;
    Offset clipToBounds (const Offset& offset) const;
    bool   contains( const BoundingBox& box ) const;

    bool intersects ( const BoundingBox& bbOther ) const;
    bool getIntersection ( const BoundingBox& bbOther,
        BoundingBox& bbIntersection ) const;
    bool getIntersection( int nPoints, const Point2d* aPolygon,
        BoundingBox& bbIntersection ) const;

    void getUnion ( const BoundingBox& bbOther, BoundingBox& bbUnion ) const;
private:
    Offset mOrigin;
    Offset mExtent;
};

} // end of namespace Atil

#ifndef BOUNDINGBOX_INL
#include <BoundingBox.inl>
#endif

#endif


//#ifndef SIZE_H
//#include <Size.h>
//#endif
