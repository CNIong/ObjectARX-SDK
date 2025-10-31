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

#ifndef BOUNDINGBOX_INL
#define BOUNDINGBOX_INL

#ifndef OFFSET_H
#include "Offset.h"
#endif
#ifndef SIZE_H
#include "Size.h"
#endif

namespace Atil {

inline BoundingBox::BoundingBox (Offset offset, Size size) 
    : mOrigin(offset)
{
    mExtent = SizeOps::getHighOffset(offset,size);
}
inline BoundingBox::BoundingBox (Offset origin, Offset extent)
    : mOrigin(origin), mExtent(extent)
{
}
inline BoundingBox::BoundingBox (int nPoints, const Offset* aOffsets)
{
    set(nPoints, aOffsets );
}
inline BoundingBox::~BoundingBox ()
{
}

// Set the bounding box origin to the given offset, and extents using the given size. 
//
inline void BoundingBox::set (Offset offset, Size size)
{

    mOrigin = offset; mExtent = SizeOps::getHighOffset(offset,size);
}

// Set the bounding box origin and extents to those given.
//
inline void BoundingBox::set (Offset origin, Offset extent)
{
    mOrigin = origin; mExtent = extent;
}

// Is the given offset within the bounding box. 
//
inline bool BoundingBox::inBounds (const Offset& offset) const
{
    return ( offset.x >= mOrigin.x && offset.y >= mOrigin.y
        && offset.x <= mExtent.x && offset.y <= mExtent.y );
}

// Is the given XY point within the bounding box. 
//
inline bool BoundingBox::inBounds ( int x, int y ) const
{
    return ( x >= mOrigin.x && y >= mOrigin.y
        && x <= mExtent.x && y <= mExtent.y );
}

// Get the bounding box extents. 
//
inline void BoundingBox::getExtents (Offset& origin, Offset& extent) const
{
    origin = mOrigin; extent = mExtent;
}

// Get the bounding box size. 
//
inline Size BoundingBox::size () const
{
    return SizeOps::getSizeOf(mExtent, mOrigin);
}

// Get the bounding box origin. 
//
inline Offset BoundingBox::origin () const
{
    return mOrigin;
}

// Return true if this bounding box contains the given bounding box, false otherwise. 
//
inline bool BoundingBox::contains( const BoundingBox& otherBox ) const
{
    return (inBounds(otherBox.mOrigin) && inBounds(otherBox.mExtent));
}

}

#endif
