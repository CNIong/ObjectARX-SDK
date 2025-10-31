///////////////////////////////////////////////////////////////////////////////
//
//
//  (C) Copyright 2005-2006 by Autodesk, Inc.  All rights reserved.
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

#ifndef RGBCOLOR_INL
#define RGBCOLOR_INL

namespace Atil
{
// The methods of the RgbColor struct have been inlined for performance.
// Refer to the RgbColor.h header file for documentation of the methods.
//
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor::RgbColor( )
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor::RgbColor( Data32 color ) : packed( color )
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor::RgbColor (int red, int green, int blue)
{
    packed = (red | green<<8 | blue<<16 | 0xFF000000);
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor::RgbColor (int red, int green, int blue, int alpha)
{
    packed = ( red | green<<8 | blue<<16 | alpha<<24 );
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor::operator Data32() const
{
    return packed;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor& RgbColor::set (int red, int green, int blue)
{
    packed = (red | green<<8 | blue<<16 | 0xFF000000);
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor& RgbColor::set (int red, int green, int blue, int alpha)
{
    packed = ( red | green<<8 | blue<<16 | alpha<<24 );
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline Data8 RgbColor::asGray () const
{
    return static_cast<Data8>
        ( rgba.red   * RgbColorFactors::kLuminanceRedFactor
        + rgba.green * RgbColorFactors::kLuminanceGreenFactor
        + rgba.blue  * RgbColorFactors::kLuminanceBlueFactor + 0.5);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor& RgbColor::operator=( const RgbColor& rhs )
{
    packed = rhs.packed;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor& RgbColor::operator=( Data32 rhs )
{
    packed = rhs;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor::operator==( const RgbColor& rhs ) const
{
    return packed == rhs.packed;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor::operator==( Data32 rhs ) const
{
    return packed == rhs;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor::operator!=( const RgbColor& rhs ) const
{
    return packed != rhs.packed;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor::operator!=( Data32 rhs )  const
{
    return packed != rhs;
}

} //end of namespace
#endif
