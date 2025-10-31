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
#include <AtilDefs.h>
#endif

#ifndef OFFSET_H
#include "Offset.h"
#endif

#ifndef SIZE_H
#define SIZE_H

namespace Atil
{

/// <summary>
/// The <c>Size</c> class holds width and height members and is used to describe
/// the pixel dimensions of an image or in other methods that need to use integral
/// values for size.
/// </summary>
///
class Size 
{
public:
    /// <summary> An integer count that is the width.
    /// </summary>
    Int32 width;
    /// <summary> An integer count that is the height.
    /// </summary>
    Int32 height;

    /// <summary>
    /// The default or empty constructor.
    /// </summary>
    ///
    Size ();

    /// <summary>
    /// The initialization constructor.
    /// </summary>
    ///
    /// <param name='width'>
    /// Initial value for the width.
    /// </param>
    ///
    /// <param name='height'>
    /// Initial value for the height.
    /// </param>
    ///
    Size (Int32 width, Int32 height);

    /// <summary>
    /// The copy constructor.
    /// </summary>
    ///
    /// <param name='rhs'>
    /// A const reference to the <c>Size</c> to be copied.
    /// </param>
    ///
    Size ( const Size& rhs );

    /// <summary>
    /// The destructor.
    /// </summary>
    ///
    ~Size ();

    /// <summary>
    /// The less than or equals operator. Both the <c>width</c> and the <c>height</c> members
    /// must meet the comparison criteria.
    /// </summary>
    ///
    /// <param name='rhs'>
    /// The argument to be compared.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the condition is satisfied.
    /// </returns>
    ///
    bool operator <= (const Size& rhs) const;

    /// <summary>
    /// The greater than or equals operator. Both the <c>width</c> and the <c>height</c> members
    /// must meet the comparison criteria.
    /// </summary>
    ///
    /// <param name='rhs'>
    /// The argument to be compared.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the condition is satisfied.
    /// </returns>
    ///
    bool operator >= (const Size& rhs) const;

    /// <summary>
    /// The equals operator. True will be returned if the <c>width</c> and the 
    /// <c>height</c> members must meet the comparison criteria.
    /// </summary>
    ///
    /// <param name='rhs'>
    /// The argument to be compared.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the condition is satisfied.
    /// </returns>
    ///
    bool operator == (const Size& rhs) const;

    /// <summary>
    /// The not equals operator. False will be returned if the <c>width</c> and the 
    /// <c>height</c> members must meet the comparison criteria.
    /// </summary>
    ///
    /// <param name='rhs'>
    /// The argument to be compared.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the condition is satisfied.
    /// </returns>
    ///
    bool operator != (const Size& rhs) const;

    /// <summary>
    /// The assignment operator. 
    /// </summary>
    ///
    /// <param name='rhs'>
    /// The argument to be copied from.
    /// </param>
    ///
    /// <returns>
    /// Returns a const reference to <c>*this</c>.
    /// </returns>
    ///
    const Size& operator = (const Size& rhs);

    /// <summary>
    /// This method will set the <c>width</c> and the <c>height</c> members.
    /// </summary>
    ///
    /// <param name="nWidth">The value that the <c>width</c> should be set to.
    /// </param>
    ///
    /// <param name="nHeight">The value that the <c>height</c> should be set to.
    /// </param>
    ///
    /// <returns>
    /// Returns a const reference to <c>*this</c>.
    /// </returns>
    ///
    const Size& set( Int32 nWidth, Int32 nHeight );

    /// <summary>
    /// This method will add the parameters to the <c>width</c> and 
    /// the <c>height</c> members respectively.
    /// </summary>
    ///
    /// <param name="width">The value that should be added to the <c>width</c>.
    /// </param>
    ///
    /// <param name="height">The value that should be added to the <c>height</c>.
    /// </param>
    ///
    /// <returns>
    /// Returns a const reference to <c>*this</c>.
    /// </returns>
    ///
    const Size& grow (Int32 valueWidth, Int32 valueHeight);

    /// <summary>
    /// This method will add the value to both the <c>width</c> and 
    /// the <c>height</c> members.
    /// </summary>
    ///
    /// <param name="toEach">The value that should be added to the <c>width</c>
    /// and the <c>height</c>.
    /// </param>
    ///
    /// <returns>
    /// Returns a const reference to <c>*this</c>.
    /// </returns>
    ///
    const Size& grow (Int32 toEach);

    /// <summary>
    /// This method will subtracted from parameters the <c>width</c> and 
    /// the <c>height</c> members respectively.
    /// </summary>
    ///
    /// <param name="width">The value that should be subtracted from the <c>width</c>.
    /// </param>
    ///
    /// <param name="height">The value that should be subtracted from the <c>height</c>.
    /// </param>
    ///
    /// <returns>
    /// Returns a const reference to <c>*this</c>.
    /// </returns>
    ///
    const Size& shrink (Int32 valueWidth, Int32 valueHeight);

    /// <summary>
    /// This method will subtract the value from both the <c>width</c> and 
    /// the <c>height</c> members.
    /// </summary>
    ///
    /// <param name="eachBy">The value that should be subtracted from the <c>width</c>
    /// and the <c>height</c>.
    /// </param>
    ///
    /// <returns>
    /// Returns a const reference to <c>*this</c>.
    /// </returns>
    ///
    const Size& shrink (Int32 eachBy);
};


/// <summary>
/// A grouping of methods that interact between <c>Size</c> and <c>Offset</c>.
/// The methods are inlined as they are small.
/// </summary>
///
namespace SizeOps
{
/// <summary>
/// This method will return the number of pixels that lie between the two
/// offsets.
/// </summary>
///
/// <param name="oHigh">The greater of the two offsets that specify the rectangular region.
/// </param>
///
/// <param name="oLow">The lower of the two offsets that specify the rectangular region.
/// </param>
///
/// <returns>
/// This method returns a <c>Size</c> instance that holds the width
/// and height in pixels of the region specified in the arguments.
/// </returns>
///
inline Size getSizeOf( const Offset& oHigh, const Offset& oLow )
{
    return Size(oHigh.x - oLow.x + 1, oHigh.y - oLow.y + 1);
}
/// <summary>
/// This method will return the <c>Offset</c> of the lower right pixel in the
/// the region described by the argument.
/// </summary>
///
/// <param name="extents">The <c>Size</c> region that extends from (0,0) up to
/// but not including <c>Size::width</c> and <c>Size::height</c>.
/// </param>
///
/// <returns>
/// This method returns the <c>Offset</c> set to the most extreme pixel (Lower Right)
/// within the region.
/// </returns>
///
inline Offset getHighOffset( const Size& extents )
{
    return Offset(extents.width - 1, extents.height - 1);
}

/// <summary>
/// This method will return the <c>Offset</c> of the lower right pixel in the
/// the region described by the arguments.
/// </summary>
///
/// <param name="oOrigin">The <c>Offset</c> for the region that extends up to
/// and but not including the offset plus the <c>Size::width</c> and <c>Size::height</c>.
/// </param>
///
/// <param name="extents">The <c>Size</c> region that extends from (0,0) up to
/// but not including <c>Size::width</c> and <c>Size::height</c>.
/// </param>
///
/// <returns>
/// This method returns the <c>Offset</c> set to the most extreme pixel (Lower Right)
/// within the region.
/// </returns>
///
inline Offset getHighOffset( const Offset& oOrigin, const Size& extents )
{
    return Offset( oOrigin.x + extents.width - 1, oOrigin.y + extents.height - 1 );
}

} // end of namespace SizeOps

} //end of namespace

#ifndef SIZE_INL
#include <Size.inl>
#endif

#endif
