//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2014 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef SIZE_INL
#define SIZE_INL
// The following are methods of the Size class that have been inlined
// for performance reasons and locality.
#if  __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif


namespace Atil
{

/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline Size::Size (Int32 nWidth, Int32 nHeight) : width(nWidth), height(nHeight)
{
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline Size::Size () : width(0), height(0)
{
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline Size::Size (const Size& rhs) : width(rhs.width), height(rhs.height)
{
}
inline Size::~Size ()
{
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline bool Size::operator <= (const Size& rhs) const
{
    return width <= rhs.width && height <= rhs.height;
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline bool Size::operator >= (const Size& rhs) const
{
    return width >= rhs.width && height >= rhs.height;
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline bool Size::operator == (const Size& rhs) const
{
    return width == rhs.width && height == rhs.height;
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline bool Size::operator != (const Size& rhs) const
{
    return width != rhs.width || height != rhs.height;
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline const Size& Size::operator = (const Size& rhs)
{
    width = rhs.width; height = rhs.height;
    return *this;
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline const Size& Size::set( Int32 nWidth, Int32 nHeight )
{
    width = nWidth; height = nHeight;
    return *this;
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline const Size& Size::grow (Int32 nWidth, Int32 nHeight)
{
    width += nWidth;
    height += nHeight;
    return *this;
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline const Size& Size::grow (Int32 toEach)
{
    width += toEach;
    height += toEach;
   
    return *this;
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline const Size& Size::shrink (Int32 byWidth, Int32 byHeight)
{
    width -= byWidth;
    height -= byHeight;
    return *this;
}
/// <summary>
/// This method is the inlined implementation of a method in <c>Size</c> <see cref="Size"/>.
/// </summary>
///
inline const Size& Size::shrink (Int32 eachBy)
{
    width -= eachBy;
    height -= eachBy;
    return *this;
}

} //end of namespace
#if  __GNUC__ >= 4
#pragma GCC visibility pop
#endif

#endif
