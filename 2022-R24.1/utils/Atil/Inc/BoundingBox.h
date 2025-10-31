///////////////////////////////////////////////////////////////////////////////
//
// (C) Autodesk, Inc. 2007-2011. All rights reserved.
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

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

namespace Atil
{
//
/// <summary>
/// This class implements a simple bounding box and provides methods to get 
/// intersections and unions with other BoundingBox objects. The box uses an
/// integer coordinate system.
/// </summary>
///
class BoundingBox 
{
public:
    /// <summary>
    /// Basic constructor.
    /// </summary>
    ///
    BoundingBox ();

    /// <summary>
    /// Initializing constructor.
    /// </summary>
    ///
    /// <param name='origin'> The <c>Offset</c> giving the coordinate to 
    /// begin the region of the box.
    /// </param>
    ///
    /// <param name='size'> The <c>Size</c> in pixels of the box.</param>
    ///
    BoundingBox (Offset origin, Size size);

    /// <summary>
    /// Initializing constructor.
    /// </summary>
    ///
    /// <param name='origin'> The <c>Offset</c> giving the coordinate to 
    /// begin the region of the box.
    /// </param>
    ///
    /// <param name='extent'> The <c>Offset</c> giving the coordinate to 
    /// of the diagonal corner declaring the region of the box. The pixel
    /// indicated by the <c>Offset</c> is included inside the region.
    /// </param>
    ///
    BoundingBox (Offset origin, Offset extent);

    /// <summary>
    /// Initializing constructor.
    /// </summary>
    ///
    /// <param name='nPoints'> The number of <c>Offset</c> in the following
    /// array.
    /// </param>
    ///
    /// <param name='aOffsets'> A const array of<c>Offset</c> objects each
    /// specifying a coordinate to be included the region of the box.
    /// </param>
    ///
    /// <remarks>
    /// This method calculates the minimum bounding box defined by the array of
    /// offsets and constructs a BoundingBox object to enclose that set.
    /// </remarks>
    ///
    BoundingBox (int nPoints, const Offset* aOffsets);

    /// <summary>
    /// The destructor.
    /// </summary>
    ///
    ~BoundingBox ();

    /// <summary>
    /// This method will reset the region of the rectangle.
    /// </summary>
    ///
    /// <param name='offset'> The <c>Offset</c> giving the coordinate to 
    /// begin the region of the box.
    /// </param>
    ///
    /// <param name='size'> The <c>Size</c> in pixels of the box.</param>
    ///
    void set (Offset offset, Size size);

    /// <summary>
    /// This method will reset the region of the rectangle.
    /// </summary>
    ///
    /// <param name='origin'> The <c>Offset</c> giving the coordinate to 
    /// begin the region of the box.
    /// </param>
    ///
    /// <param name='extent'> The <c>Offset</c> giving the coordinate to 
    /// of the diagonal corner declaring the region of the box. The pixel
    /// indicated by the <c>Offset</c> is included inside the region.
    /// </param>
    ///
    void set (Offset origin, Offset extent);

    /// <summary>
    /// This method will reset the region of the rectangle.
    /// </summary>
    ///
    /// <param name='nPoints'> The number of <c>Offset</c> in the following
    /// array.
    /// </param>
    ///
    /// <param name='aOffsets'> A const array of<c>Offset</c> objects each
    /// specifying a coordinate to be included the region of the box.
    /// </param>
    ///
    /// <remarks>
    /// This method calculates the minimum bounding box defined by the array of
    /// offsets and constructs a BoundingBox object to enclose that set.
    /// </remarks>
    ///
    void set (int nPoints, const Offset* aOffsets);

    /// <summary>
    /// This method will expand the region to included the given point.
    /// </summary>
    ///
    /// <param name='offset'> The <c>Offset</c> to be included in the region.
    /// </param>
    ///
    void expandToInclude (Offset offset);

    /// <summary>
    /// This method will use the supplied <c>Offsets</c> and expand the region
    /// to included them.
    /// </summary>
    ///
    /// <param name='nPoints'> The number of <c>Offset</c> in the following
    /// array.
    /// </param>
    ///
    /// <param name='aOffsets'> A const array of<c>Offset</c> objects each
    /// specifying a coordinate to be included the region of the box.
    /// </param>
    ///
    void expandToInclude (int nPoints, const Offset* aOffsets);

    /// <summary>
    /// This method will retrieve the region of the rectangle.
    /// </summary>
    ///
    /// <param name='origin'> The <c>Offset</c> of the upper left of the region.
    /// </param>
    ///
    /// <param name='extent'> The <c>Offset</c> to receive the coordinate of 
    /// of the lower right corner of the region. 
    /// </param>
    ///
    void getExtents (Offset& origin, Offset& extent) const;

    /// <summary>
    /// This method will return the size of the region in pixels.
    /// </summary>
    /// 
    /// <returns>
    /// This returns a <c>Size</c> instance declaring the width and height
    /// in pixels of the region.
    /// </returns>
    ///
    Size size () const;


    /// <summary>
    /// This method will return the origin of the region.
    /// </summary>
    /// 
    /// <returns>
    /// This returns a <c>Offset</c> instance declaring the x and y
    /// position of the upper left pixel in the region.
    /// </returns>
    ///
    Offset origin () const;

    /// <summary>
    /// This method test to if the given point is inside the region.
    /// </summary>
    ///
    /// <param name='offset'> The <c>Offset</c> to be tested for inclusion.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the <c>Offset</c> is within the region.
    /// </returns>
    ///
    bool inBounds (const Offset& offset) const;

    /// <summary>
    /// This method test to if the given point is inside the region.
    /// </summary>
    ///
    /// <param name='x'>The index of the pixel along the x-axis to be tested
    /// for inclusion.
    /// </param>
    ///
    /// <param name='y'>The index of the pixel along the y-axis to be tested
    /// for inclusion.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the point is within the region.
    /// </returns>
    ///
    bool inBounds ( int x, int y ) const;

    /// <summary>
    /// This method tests to if the given point is inside the region and will
    /// return a modified point that is within the region if it is not.
    /// </summary>
    ///
    /// <param name='offset'> The <c>Offset</c> to be clipped.
    /// </param>
    ///
    /// <returns>
    /// This will a possibly modified <c>Offset</c> that is within the region.
    /// </returns>
    ///
    Offset clipToBounds (const Offset& offset) const;

    /// <summary>
    /// This method test the <c>BoundingBox</c> instance against another instance
    /// to determine if the instance tested is contained by this instance.
    /// </summary>
    ///
    /// <param name='box'> The <c>BoundingBox</c> to be tested.</param>
    ///
    /// <returns>
    /// This will return true if the <c>BoundingBox</c> is enclosed by the region.
    /// </returns>
    ///
    bool contains( const BoundingBox& box ) const;

    /// <summary>
    /// This method test the <c>BoundingBox</c> instance against another instance
    /// to determine if the instance tested intersects this instance.
    /// </summary>
    ///
    /// <param name='bbOther'> The <c>BoundingBox</c> to be tested.</param>
    ///
    /// <returns>
    /// This will return true if the <c>BoundingBox</c> and this region have
    /// a common area.
    /// </returns>
    ///
    bool intersects ( const BoundingBox& bbOther ) const;

    /// <summary>
    /// This method returns the intersection of this instance and another 
    /// <c>BoundingBox</c> instance against another instance.
    /// </summary>
    ///
    /// <param name='bbOther'> The <c>BoundingBox</c> to be tested.</param>
    ///
    /// <param name='bbIntersection'> The <c>BoundingBox</c> to be receive the
    /// intersection area if the regions intersect.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the <c>BoundingBox</c> and this region have
    /// a common area.
    /// </returns>
    ///
    bool getIntersection ( const BoundingBox& bbOther,
        BoundingBox& bbIntersection ) const;

    /// <summary>
    /// This method returns the intersection of this instance and an array
    /// of <c>Point2d</c> points.
    /// </summary>
    ///
    /// <param name='nPoints'> The number of <c>Offset</c> in the following
    /// array.
    /// </param>
    ///
    /// <param name='aPolygon'> A const array of<c>Point2d</c> objects each
    /// specifying a coordinate that defines a polygonal region to be intersected.
    /// </param>
    ///
    /// <param name='bbIntersection'> The <c>BoundingBox</c> to be receive the
    /// intersection area if the regions intersect.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the polygon and this region have
    /// a common area.
    /// </returns>
    ///
    bool getIntersection( int nPoints, const Point2d* aPolygon,
        BoundingBox& bbIntersection ) const;

    /// <summary>
    /// This method returns the union of this instance and another 
    /// <c>BoundingBox</c> instance.
    /// </summary>
    ///
    /// <param name='bbOther'> The <c>BoundingBox</c> to be tested.</param>
    ///
    /// <param name='bbUnion'> The <c>BoundingBox</c> to be receive the
    /// union area that will enclose both regions.
    /// </param>
    ///
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
