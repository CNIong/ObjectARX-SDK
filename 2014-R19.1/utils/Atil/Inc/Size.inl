///////////////////////////////////////////////////////////////////////////////
//
// (c) Autodesk, Inc. 2007-2008. All rights reserved.
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
