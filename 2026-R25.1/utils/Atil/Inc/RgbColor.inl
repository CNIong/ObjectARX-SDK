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

#ifndef RGBCOLOR_INL
#define RGBCOLOR_INL
#if __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif

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
inline RgbColor::RgbColor( Data32 color ) : packed(color)
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor::RgbColor (Data8 red, Data8 green, Data8 blue)
{
    packed = (red | green<<8 | blue<<16 | 0xFF000000);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor::RgbColor (Data8 first, Data8 second, Data8 third, Data8 alpha)
{
    packed = ( first | second<<8 | third<<16 | alpha<<24 );
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
inline const RgbColor& RgbColor::set (Data8 red, Data8 green, Data8 blue)
{
    packed = (red | green<<8 | blue<<16 | 0xFF000000);
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor& RgbColor::set (Data8 red, Data8 green, Data8 blue, Data8 alpha
    , DataModelAttributes::ChannelOrder fmt)
{
    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        packed = ( red | green<<8 | blue<<16 | alpha<<24 );
    }
    else {
        packed = ( blue | green<<8 | red<<16 | alpha<<24 );
    }
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline Data8 RgbColor::asGray (DataModelAttributes::ChannelOrder format) const
{
    Data8 gray;
    if (format == DataModelAttributes::kRedGreenBlueAlpha) {
        gray = static_cast<Data8> ( rgba.red * RgbColorFactors::kLuminanceRedFactor
            + rgba.green * RgbColorFactors::kLuminanceGreenFactor
            + rgba.blue  * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    }
    else {
        gray = static_cast<Data8> ( bgra.red * RgbColorFactors::kLuminanceRedFactor
            + bgra.green * RgbColorFactors::kLuminanceGreenFactor
            + bgra.blue  * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    }
    return gray;
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
    return (packed == rhs.packed);
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
    return (packed != rhs.packed);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor::operator!=( Data32 rhs )  const
{
    return packed != rhs;
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor5b::RgbColor5b( )
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor5b::RgbColor5b( Data16 color ) : packed(color)
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor5b::RgbColor5b (Data8 red, Data8 green, Data8 blue)
{
    packed = (Data16) ((blue & RgbModelAttributes::kLowMask)
        | ((green << 5) & RgbModelAttributes::kMidMask565)
        | ((red & RgbModelAttributes::kLowMask) << 11));
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor5b::RgbColor5b (Data8 first, Data8 second, Data8 third, Data8 alpha
    , DataModelAttributes::BitFields fields)
{
    if (fields == DataModelAttributes::k5551) {
        // Using the kLowMask effectively cuts the values into range.
        packed = (Data16) ((first & RgbModelAttributes::kLowMask)
            | ((second & RgbModelAttributes::kLowMask) << 5)
            | ((third & RgbModelAttributes::kLowMask)<<10)
            | ((alpha != 0) ? RgbModelAttributes::kAlphaMask : 0));
    }
    else if (fields == DataModelAttributes::k565) {
        // Using the kLowMask effectively cuts the values into range.
        packed = (Data16) ((first & RgbModelAttributes::kLowMask)
            | ((second << 5) & RgbModelAttributes::kMidMask565)
            | ((third & RgbModelAttributes::kLowMask)<<11));
    }
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor5b::operator Data16() const
{
    return packed;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor5b& RgbColor5b::set (Data8 red, Data8 green, Data8 blue)
{
    // Using the kLowMask effectively cuts the values into range.
    packed = (Data16) ((blue & RgbModelAttributes::kLowMask)
        | ((green << 5) & RgbModelAttributes::kMidMask565)
        | ((red & RgbModelAttributes::kLowMask) << 11));
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor5b& RgbColor5b::set (Data8 red, Data8 green, Data8 blue, Data8 alpha
    , DataModelAttributes::BitFields fields, DataModelAttributes::ChannelOrder fmt)
{
    if (fields == DataModelAttributes::k5551) {
        if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
            // Using the kLowMask effectively cuts the values into range.
            packed = (Data16) ((red & RgbModelAttributes::kLowMask)
                | ((green & RgbModelAttributes::kLowMask) << 5)
                | ((blue & RgbModelAttributes::kLowMask)<<10)
                | ((alpha != 0) ? RgbModelAttributes::kAlphaMask : 0));
        }
        else  {
            // Using the kLowMask effectively cuts the values into range.
            packed = (Data16) ((blue & RgbModelAttributes::kLowMask)
                | ((green & RgbModelAttributes::kLowMask) << 5)
                | ((red & RgbModelAttributes::kLowMask) << 10)
                | ((alpha != 0) ? RgbModelAttributes::kAlphaMask : 0));
        }
    }
    else if (fields == DataModelAttributes::k565) {
        if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
            // Using the kLowMask effectively cuts the values into range.
            packed = (Data16) ((red & RgbModelAttributes::kLowMask)
                | ((green << 5) & RgbModelAttributes::kMidMask565)
                | ((blue & RgbModelAttributes::kLowMask)<<11));
        }
        else  {
            // Using the kLowMask effectively cuts the values into range.
            packed = (Data16) ((blue & RgbModelAttributes::kLowMask)
                | ((green << 5) & RgbModelAttributes::kMidMask565)
                | ((red & RgbModelAttributes::kLowMask) << 11));
        }
    }
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline void RgbColor5b::getChannelData (Data8& red, Data8& green, Data8& blue, Data8& alpha
    , DataModelAttributes::BitFields fields, DataModelAttributes::ChannelOrder fmt) const
{
    if (fields == DataModelAttributes::k5551) {
        green = (Data8) ((packed >> 5) & RgbModelAttributes::kLowMask);
        alpha = (Data8) ((packed & RgbModelAttributes::kAlphaMask) >> 15);
        if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
            red = (Data8) (packed & RgbModelAttributes::kLowMask);
            blue = (Data8) ((packed >> 10) & RgbModelAttributes::kLowMask);
        }
        else  {
            blue = (Data8) (packed & RgbModelAttributes::kLowMask);
            red = ((Data8) (packed >> 10) & RgbModelAttributes::kLowMask);
        }
    }
    else if (fields == DataModelAttributes::k565) {
        green = (Data8) ((packed & RgbModelAttributes::kMidMask565) >> 5);
        if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
            red = (Data8) (packed & RgbModelAttributes::kLowMask);
            blue = (Data8) ((packed >> 11) & RgbModelAttributes::kLowMask);
        }
        else  {
            blue = (Data8) (packed & RgbModelAttributes::kLowMask);
            red = (Data8) ((packed >> 11) & RgbModelAttributes::kLowMask);
        }
    }
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor5b::asRgbColor (DataModelAttributes::BitFields fields
    , DataModelAttributes::ChannelOrder fmt) const
{
    Data8 red = 0, green = 0, blue = 0, alpha = 255;
    if (fields == DataModelAttributes::k5551) {
        green = (Data8) ((packed >> 5) & RgbModelAttributes::kLowMask);
        alpha = (Data8) ((packed & RgbModelAttributes::kAlphaMask) >> 15);
        if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
            red = (Data8) (packed & RgbModelAttributes::kLowMask);
            blue = (Data8) ((packed >> 10) & RgbModelAttributes::kLowMask);
        }
        else  {
            blue = (Data8) (packed & RgbModelAttributes::kLowMask);
            red = (Data8) ((packed >> 10) & RgbModelAttributes::kLowMask);
        }
        red = (Data8) (red * 255 / 31);
        green = (Data8) (green * 255 / 31);
        blue = (Data8) (blue * 255 / 31);
        alpha = (Data8) (alpha * 255);  // Just one bit
    }
    else if (fields == DataModelAttributes::k565) {
        green = (Data8) ((packed & RgbModelAttributes::kMidMask565) >> 5);
        if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
            red = (Data8) (packed & RgbModelAttributes::kLowMask);
            blue = (Data8) ((packed >> 11) & RgbModelAttributes::kLowMask);
        }
        else  {
            blue = (Data8) (packed & RgbModelAttributes::kLowMask);
            red = (Data8) ((packed >> 11) & RgbModelAttributes::kLowMask);
        }
        red = (Data8) (red * 255 / 31);
        green = (Data8) (green * 255 / 63);
        blue = (Data8) (blue * 255 / 31);
        alpha = 255;
    }
    RgbColor colorRgb(red,green,blue,alpha);
    return colorRgb;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor5b::asBgrColor (DataModelAttributes::BitFields fields
    , DataModelAttributes::ChannelOrder fmt) const
{
    Data8 red = 0, green = 0, blue = 0, alpha = 0;
    if (fields == DataModelAttributes::k5551) {
        green = (Data8) ((packed >> 5) & RgbModelAttributes::kLowMask);
        alpha = (Data8) ((packed & RgbModelAttributes::kAlphaMask) >> 15);
        if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
            red = (Data8) (packed & RgbModelAttributes::kLowMask);
            blue = (Data8) ((packed >> 10) & RgbModelAttributes::kLowMask);
        }
        else  {
            blue = (Data8) (packed & RgbModelAttributes::kLowMask);
            red = (Data8) ((packed >> 10) & RgbModelAttributes::kLowMask);
        }
        red = (Data8) (red * 255 / 31);
        green = (Data8) (green * 255 / 31);
        blue = (Data8) (blue * 255 / 31);
        alpha = (Data8) (alpha * 255);  // Just one bit
    }
    else if (fields == DataModelAttributes::k565) {
        green = (Data8) ((packed & RgbModelAttributes::kMidMask565) >> 5);
        if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
            red = (Data8) (packed & RgbModelAttributes::kLowMask);
            blue = (Data8) ((packed >> 11) & RgbModelAttributes::kLowMask);
        }
        else  {
            blue = (Data8) (packed & RgbModelAttributes::kLowMask);
            red = (Data8) ((packed >> 11) & RgbModelAttributes::kLowMask);
        }
        red = (Data8) (red * 255 / 31);
        green = (Data8) (green * 255 / 63);
        blue = (Data8) (blue * 255 / 31);
        alpha = 255;
    }
    RgbColor colorRgb(blue,green,red,alpha);
    return colorRgb;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline Data8 RgbColor5b::asGray (DataModelAttributes::BitFields fields
    , DataModelAttributes::ChannelOrder format) const
{
    Data8 red = 0, green = 0, blue = 0;
    if (fields == DataModelAttributes::k5551) {
        green = (Data8) ((packed >> 5) & RgbModelAttributes::kLowMask);
        if (format == DataModelAttributes::kRedGreenBlueAlpha) {
            red = (Data8) (packed & RgbModelAttributes::kLowMask);
            blue = (Data8) ((packed >> 10) & RgbModelAttributes::kLowMask);
        }
        else  {
            blue = (Data8) (packed & RgbModelAttributes::kLowMask);
            red = (Data8) ((packed >> 10) & RgbModelAttributes::kLowMask);
        }
        red = (Data8) (red * 255 / 31);
        green = (Data8) (green * 255 / 31);
        blue = (Data8) (blue * 255 / 31);
    }
    else if (fields == DataModelAttributes::k565) {
        green = (Data8) ((packed & RgbModelAttributes::kMidMask565) >> 5);
        if (format == DataModelAttributes::kRedGreenBlueAlpha) {
            red = (Data8) (packed & RgbModelAttributes::kLowMask);
            blue = (Data8) ((packed >> 11) & RgbModelAttributes::kLowMask);
        }
        else  {
            blue = (Data8) (packed & RgbModelAttributes::kLowMask);
            red = (Data8) ((packed >> 11) & RgbModelAttributes::kLowMask);
        }
        red = (Data8) (red * 255 / 31);
        green = (Data8) (green * 255 / 63);
        blue = (Data8) (blue * 255 / 31);
    }
    Data8 gray = static_cast<Data8> ( red * RgbColorFactors::kLuminanceRedFactor
        + green * RgbColorFactors::kLuminanceGreenFactor
        + blue  * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    return gray;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor5b& RgbColor5b::operator=( const RgbColor5b& rhs )
{
    packed = rhs.packed;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor5b& RgbColor5b::operator=( Data16 rhs )
{
    packed = rhs;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor5b::operator==( const RgbColor5b& rhs ) const
{
    return (packed == rhs.packed);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor5b::operator==( Data16 rhs ) const
{
    return packed == rhs;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor5b::operator!=( const RgbColor5b& rhs ) const
{
    return (packed != rhs.packed);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor5b::operator!=( Data16 rhs )  const
{
    return packed != rhs;
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor10::RgbColor10( )
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor10::RgbColor10( Data32 color ) : packed(color)
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor10::RgbColor10 (Data16 red, Data16 green, Data16 blue)
{
    packed = ((red & 0x03FF) | ((green & 0x03FF) << 10) | ((blue & 0x03FF) << 20));
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor10::RgbColor10 (Data16 first, Data16 second, Data16 third, Data16 alpha)
{
    packed = ((first & 0x03ff) | ((second & 0x03FF) << 10)
        | ((third & 0x03FF) << 20) | ((alpha & 0x03) << 30));
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor10::operator Data32() const
{
    return packed;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor10& RgbColor10::set (Data16 red, Data16 green, Data16 blue)
{
    packed = ((red & 0x03FF) | ((green & 0x03FF) << 10) | ((blue & 0x03FF) << 20));
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor10& RgbColor10::set (Data16 red, Data16 green
    , Data16 blue, Data16 alpha, DataModelAttributes::ChannelOrder fmt)
{
    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        packed = ((red & 0x03FF) | ((green & 0x03FF) << 10)
            | ((blue & 0x03FF) << 20) | ((alpha & 0x03) << 30));
    }
    else {
        packed = ((blue & 0x03FF) | ((green & 0x03FF) << 10)
            | ((red & 0x03FF) << 20) | ((alpha & 0x03) << 30));
    }
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline void RgbColor10::getChannelData (Data16& red, Data16& green
    , Data16& blue, Data16& alpha, DataModelAttributes::ChannelOrder fmt) const
{
    green = (Data16) ((packed >> 10) & 0x03FF);
    alpha = (Data16) ((packed >> 30) & 0x03);
    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        red = (Data16) (packed & 0x03FF);
        blue = (Data16) ((packed >> 20) & 0x03FF);
    }
    else {
        blue = (Data16) (packed & 0x03FF);
        red = (Data16) ((packed >> 20) & 0x03FF);
    }
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor10::asRgbColor (DataModelAttributes::ChannelOrder fmt) const
{
    Data16 red, green, blue, alpha;
    green = (Data16) ((packed >> 10) & 0x03FF);
    alpha = (Data16) ((packed >> 30) & 0x03);
    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        red = (Data16) (packed & 0x03FF);
        blue = (Data16) ((packed >> 20) & 0x03FF);
    }
    else {
        blue = (Data16) (packed & 0x03FF);
        red = (Data16) ((packed >> 20) & 0x03FF);
    }
#define CVTC(x) ((Data8) (((x) / 1023.0) * 255))
#define CVTA(x) ((Data8) (((x) / 3.0) * 255))
    RgbColor colorRgb(CVTC(red), CVTC(green), CVTC(blue), CVTA(alpha));
    return colorRgb;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor10::asBgrColor (DataModelAttributes::ChannelOrder fmt) const
{
    Data16 red, green, blue, alpha;
    green = (Data16) ((packed >> 10) & 0x03FF);
    alpha = (Data16) ((packed >> 30) & 0x03);
    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        red = (Data16) (packed & 0x03FF);
        blue = (Data16) ((packed >> 20) & 0x03FF);
    }
    else {
        blue = (Data16) (packed & 0x03FF);
        red = (Data16) ((packed >> 20) & 0x03FF);
    }
    RgbColor colorRgb(CVTC(blue), CVTC(green), CVTC(red), CVTA(alpha));
#undef CVTC
#undef CVTA
    return colorRgb;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline Data16 RgbColor10::asGray (DataModelAttributes::ChannelOrder format) const
{
    Data16 red,green,blue,gray;
    green = (Data16) ((packed >> 10) & 0x03FF);
    if (format == DataModelAttributes::kRedGreenBlueAlpha) {
        red = (Data16) (packed & 0x03FF);
        blue = (Data16) ((packed >> 20) & 0x03FF);
        gray = static_cast<Data16> ( red * RgbColorFactors::kLuminanceRedFactor
            + green * RgbColorFactors::kLuminanceGreenFactor
            + blue  * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    }
    else {
        blue = (Data16) (packed & 0x03FF);
        red = (Data16) ((packed >> 20) & 0x03FF);
        gray = static_cast<Data16> ( red * RgbColorFactors::kLuminanceRedFactor
            + green * RgbColorFactors::kLuminanceGreenFactor
            + blue  * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    }
    return gray;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor10& RgbColor10::operator=( const RgbColor10& rhs )
{
    packed = rhs.packed;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor10& RgbColor10::operator=( Data32 rhs )
{
    packed = rhs;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor10::operator==( const RgbColor10& rhs ) const
{
    return (packed == rhs.packed);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor10::operator==( Data32 rhs ) const
{
    return packed == rhs;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor10::operator!=( const RgbColor10& rhs ) const
{
    return (packed != rhs.packed);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor10::operator!=( Data32 rhs )  const
{
    return packed != rhs;
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16i::RgbColor16i( )
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16i::RgbColor16i( Data64 color ) : packed(color)
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16i::RgbColor16i (Data16 red, Data16 green, Data16 blue)
{
    bgra.red = red;
    bgra.green = green;
    bgra.blue = blue;
    bgra.alpha = (Data16)65535;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16i::RgbColor16i (Data16 first, Data16 second, Data16 third, Data16 alpha)
{
    bgra.red = third;
    bgra.green = second;
    bgra.blue = first;
    bgra.alpha = alpha;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16i::operator Data64() const
{
    return packed;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor16i& RgbColor16i::set (Data16 red, Data16 green, Data16 blue)
{
    bgra.red = red;
    bgra.green = green;
    bgra.blue = blue;
    bgra.alpha = (Data16) 65535;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor16i& RgbColor16i::set (Data16 red, Data16 green
    , Data16 blue, Data16 alpha, DataModelAttributes::ChannelOrder fmt)
{
    bgra.alpha = alpha;
    bgra.green = green;
    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        bgra.red = red;
        bgra.blue = blue;
    }
    else {
        bgra.red = blue;
        bgra.blue = red;
    }
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor16i::asRgbColor (DataModelAttributes::ChannelOrder fmt) const
{
#define CVTC(x) ((Data8)(((x) / 65535.0) * 255.0))
#define CVTS(x) ((Data8) ((x) == 65535 ? 255 : ((int) (((x) / 65535.0) * 255.0))))
    RgbColor color;
    if (DataModelAttributes::kRedGreenBlueAlpha == fmt) {
        color = RgbColor(CVTC(rgba.red),CVTC(rgba.green),CVTC(rgba.blue),CVTS(rgba.alpha));
    }
    else {
        color = RgbColor(CVTC(bgra.red),CVTC(bgra.green),CVTC(bgra.blue),CVTS(bgra.alpha));
    }
    return color;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor16i::asBgrColor (DataModelAttributes::ChannelOrder fmt) const
{
    RgbColor color;
    if (DataModelAttributes::kRedGreenBlueAlpha == fmt) {
        color = RgbColor(CVTC(rgba.blue),CVTC(rgba.green),CVTC(rgba.red),CVTS(rgba.alpha));
    }
    else {
        color = RgbColor(CVTC(bgra.blue),CVTC(bgra.green),CVTC(bgra.red),CVTS(bgra.alpha));
    }
    return color;
#undef CVTS
#undef CVTC
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline Data16 RgbColor16i::asGray (DataModelAttributes::ChannelOrder format) const
{
    Data16 gray;

    if (format == DataModelAttributes::kRedGreenBlueAlpha) {
        gray = static_cast<Data16> ( rgba.red * RgbColorFactors::kLuminanceRedFactor
            + rgba.green * RgbColorFactors::kLuminanceGreenFactor
            + rgba.blue  * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    }
    else {
        gray = static_cast<Data16> ( bgra.red * RgbColorFactors::kLuminanceRedFactor
            + bgra.green * RgbColorFactors::kLuminanceGreenFactor
            + bgra.blue  * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    }
    return gray;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor16i& RgbColor16i::operator=( const RgbColor16i& rhs )
{
    packed = rhs.packed;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor16i& RgbColor16i::operator=( Data64 rhs )
{
    packed = rhs;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor16i::operator==( const RgbColor16i& rhs ) const
{
    return (packed == rhs.packed);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor16i::operator==( Data64 rhs ) const
{
    return packed == rhs;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor16i::operator!=( const RgbColor16i& rhs ) const
{
    return (packed != rhs.packed);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor16i::operator!=( Data64 rhs )  const
{
    return packed != rhs;
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16f::RgbColor16f( )
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16f::RgbColor16f( Data64 color ) : packed(color)
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16f::RgbColor16f (half red, half green, half blue)
{
    bgra.red = red.bits();
    bgra.green = green.bits();
    bgra.blue = blue.bits();
    bgra.alpha = (Data16) 65504;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16f::RgbColor16f (half first, half second, half third, half alpha)
{
    bgra.blue = first.bits();
    bgra.green = second.bits();
    bgra.red = third.bits();
    bgra.alpha = alpha.bits();
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16f::operator Data64() const
{
    return packed;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor16f& RgbColor16f::set (half red, half green, half blue)
{
    bgra.red = red.bits();
    bgra.green = green.bits();
    bgra.blue = blue.bits();
    bgra.alpha = (Data16) 65504;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor16f& RgbColor16f::set (half red, half green
    , half blue, half alpha, DataModelAttributes::ChannelOrder fmt)
{
    bgra.green = green.bits();
    bgra.alpha = alpha.bits();
    // Default is bgra configuration so convert rgb to bgr.
    // The naming of the parameters can be confusing, but if
    // kBlueGreenReadAlpha is sent in, the red parameter is
    // assumed to hold blue.
    if (DataModelAttributes::kRedGreenBlueAlpha == fmt) {
        bgra.blue = red.bits();
        bgra.red = blue.bits();
    }
    else {
        bgra.blue = blue.bits();
        bgra.red = red.bits();
    }
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor16f::asRgbColor (DataModelAttributes::ChannelOrder fmt) const
{
#define CVTC(x) ((Data8)((x)*255))
    RgbColor color;
    const Channels* channels = (const Channels*) &packed;
    if (DataModelAttributes::kRedGreenBlueAlpha == fmt) {
        color = RgbColor(CVTC(channels->red), CVTC(channels->green)
            , CVTC(channels->blue), CVTC(channels->alpha));
    }
    else {
        color = RgbColor(CVTC(channels->blue), CVTC(channels->green)
            , CVTC(channels->red), CVTC(channels->alpha));
    }
    return color;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor16f::asBgrColor (DataModelAttributes::ChannelOrder fmt) const
{
    RgbColor color;
    const Channels* channels = (const Channels*) &packed;
    if (DataModelAttributes::kRedGreenBlueAlpha == fmt) {
        color = RgbColor(CVTC(channels->blue), CVTC(channels->green)
            , CVTC(channels->red), CVTC(channels->alpha));
    }
    else {
        color = RgbColor(CVTC(channels->blue), CVTC(channels->green)
            , CVTC(channels->red), CVTC(channels->alpha));
    }
    return color;
#undef CVTC
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline half RgbColor16f::asGray (DataModelAttributes::ChannelOrder format) const
{
    half gray;
    const Channels* channels = (const Channels*) &packed;
    if (format == DataModelAttributes::kRedGreenBlueAlpha) {
        gray = static_cast<half> ((float) (channels->blue * RgbColorFactors::kLuminanceRedFactor
            + channels->green * RgbColorFactors::kLuminanceGreenFactor
            + channels->red * RgbColorFactors::kLuminanceBlueFactor + half(0.5)));
    }
    else {
        gray = static_cast<half> ((float) (channels->red * RgbColorFactors::kLuminanceRedFactor
            + channels->green * RgbColorFactors::kLuminanceGreenFactor
            + channels->blue  * RgbColorFactors::kLuminanceBlueFactor + half(0.5)));
    }
    return gray;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor16f::Channels RgbColor16f::getChannelData() const
{
    Channels channels = *((const Channels*) &packed);
    return channels;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor16f& RgbColor16f::operator=( const RgbColor16f& rhs )
{
    packed = rhs.packed;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor16f& RgbColor16f::operator=( Data64 rhs )
{
    packed = rhs;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor16f::operator==( const RgbColor16f& rhs ) const
{
    return (packed == rhs.packed);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor16f::operator==( Data64 rhs ) const
{
    return packed == rhs;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor16f::operator!=( const RgbColor16f& rhs ) const
{
    return (packed != rhs.packed);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor16f::operator!=( Data64 rhs )  const
{
    return packed != rhs;
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor32f::RgbColor32f( )
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor32f::RgbColor32f( Data128 color ) : pixel(color)
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor32f::RgbColor32f (float red, float green, float blue)
{
    pixel.value.fl.a = red;
    pixel.value.fl.b = green;
    pixel.value.fl.c = blue;
    pixel.value.fl.d = (float) MAX_ALPHA;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor32f::RgbColor32f (float first, float second, float third
    , float alpha)
{
    pixel.value.fl.a = first;
    pixel.value.fl.b = second;
    pixel.value.fl.c = third;
    pixel.value.fl.d = alpha;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor32f::operator Data128() const
{
    return pixel;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor32f& RgbColor32f::set (float red, float green, float blue)
{
    pixel.value.fl.a = red;
    pixel.value.fl.b = green;
    pixel.value.fl.c = blue;
    pixel.value.fl.d = (float)MAX_ALPHA;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor32f& RgbColor32f::set (float red, float green
    , float blue, float alpha, DataModelAttributes::ChannelOrder fmt)
{
    pixel.value.fl.b = green;
    pixel.value.fl.d = alpha;

    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        pixel.value.fl.a = red;
        pixel.value.fl.c = blue;
    }
    else {
        pixel.value.fl.a = blue;
        pixel.value.fl.c = red;
    }
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor32f::asRgbColor (DataModelAttributes::ChannelOrder fmt) const
{
#define CVTC(x) ((Data8)((x)*255))
    RgbColor color;
    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        color = RgbColor(CVTC(pixel.value.fl.a), CVTC(pixel.value.fl.b)
            , CVTC(pixel.value.fl.c), CVTC(pixel.value.fl.d));
    }
    else {
        color = RgbColor(CVTC(pixel.value.fl.c), CVTC(pixel.value.fl.b)
            , CVTC(pixel.value.fl.a), CVTC(pixel.value.fl.d));
    }
    return color;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor32f::asBgrColor (DataModelAttributes::ChannelOrder fmt) const
{
    RgbColor color;
    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        color = RgbColor(CVTC(pixel.value.fl.c), CVTC(pixel.value.fl.b)
            , CVTC(pixel.value.fl.a), CVTC(pixel.value.fl.d));
    }
    else {
        color = RgbColor(CVTC(pixel.value.fl.a), CVTC(pixel.value.fl.b)
            , CVTC(pixel.value.fl.c), CVTC(pixel.value.fl.d));
    }
    return color;
#undef CVTC
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline float RgbColor32f::asGray (DataModelAttributes::ChannelOrder format) const
{
    float gray;

    if (format == DataModelAttributes::kRedGreenBlueAlpha) {
        gray = static_cast<float> ( pixel.value.fl.a * RgbColorFactors::kLuminanceRedFactor
            + pixel.value.fl.b * RgbColorFactors::kLuminanceGreenFactor
            + pixel.value.fl.c * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    }
    else {
        gray = static_cast<float> ( pixel.value.fl.c * RgbColorFactors::kLuminanceRedFactor
            + pixel.value.fl.b * RgbColorFactors::kLuminanceGreenFactor
            + pixel.value.fl.a * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    }
    return gray;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor32f& RgbColor32f::operator=( const RgbColor32f& rhs )
{
    pixel = rhs.pixel;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor32f& RgbColor32f::operator=( Data128 rhs )
{
    pixel = rhs;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor32f::operator==( const RgbColor32f& rhs ) const
{
    return (pixel == rhs.pixel);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor32f::operator==( Data128 rhs ) const
{
    return pixel == rhs;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor32f::operator!=( const RgbColor32f& rhs ) const
{
    return (pixel != rhs.pixel);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor32f::operator!=( Data128 rhs )  const
{
    return pixel != rhs;
}

/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor32i::RgbColor32i( )
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor32i::RgbColor32i( Data128 color ) : pixel(color)
{
}
/// <summary>
/// This inlined constructor is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor32i::RgbColor32i (Data32 red, Data32 green, Data32 blue)
{
    pixel.value.ui.a = red;
    pixel.value.ui.b = green;
    pixel.value.ui.c = blue;
    pixel.value.ui.d = DATA32_MAX;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor32i::RgbColor32i (Data32 first, Data32 second, Data32 third, Data32 alpha)
{
    pixel.value.ui.a = first;
    pixel.value.ui.b = second;
    pixel.value.ui.c = third;
    pixel.value.ui.d = alpha;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor32i::operator Data128() const
{
    return pixel;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor32i& RgbColor32i::set (Data32 red, Data32 green, Data32 blue)
{
    pixel.value.ui.a = red;
    pixel.value.ui.b = green;
    pixel.value.ui.c = blue;
    pixel.value.ui.d = DATA32_MAX;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor32i& RgbColor32i::set (Data32 red, Data32 green
    , Data32 blue, Data32 alpha, DataModelAttributes::ChannelOrder fmt)
{
    pixel.value.ui.b = green;
    pixel.value.ui.d = alpha;

    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        pixel.value.ui.a = red;
        pixel.value.ui.c = blue;
    }
    else {
        pixel.value.ui.a = blue;
        pixel.value.ui.c = red;
    }
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor32i::asRgbColor (DataModelAttributes::ChannelOrder fmt) const
{
#define CVTC(x) ((Data8)(((x) / DATA32_MAX) * 255))
    RgbColor color;
    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        color = RgbColor(CVTC(pixel.value.ui.a), CVTC(pixel.value.ui.b)
            , CVTC(pixel.value.ui.c), CVTC(pixel.value.ui.d));
    }
    else {
        color = RgbColor(CVTC(pixel.value.ui.c), CVTC(pixel.value.ui.b)
            , CVTC(pixel.value.ui.a), CVTC(pixel.value.ui.d));
    }
    return color;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline RgbColor RgbColor32i::asBgrColor (DataModelAttributes::ChannelOrder fmt) const
{
    RgbColor color;
    if (fmt == DataModelAttributes::kRedGreenBlueAlpha) {
        color = RgbColor(CVTC(pixel.value.ui.c), CVTC(pixel.value.ui.b)
            , CVTC(pixel.value.ui.a), CVTC(pixel.value.ui.d));
    }
    else {
        color = RgbColor(CVTC(pixel.value.ui.a), CVTC(pixel.value.ui.b)
            , CVTC(pixel.value.ui.c), CVTC(pixel.value.ui.d));
    }
    return color;
#undef CVTC
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline Data32 RgbColor32i::asGray (DataModelAttributes::ChannelOrder format) const
{
    Data32 gray;

    if (format == DataModelAttributes::kRedGreenBlueAlpha) {
        gray = static_cast<Data32> ( pixel.value.ui.a * RgbColorFactors::kLuminanceRedFactor
            + pixel.value.ui.b * RgbColorFactors::kLuminanceGreenFactor
            + pixel.value.ui.c * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    }
    else {
        gray = static_cast<Data32> ( pixel.value.ui.c * RgbColorFactors::kLuminanceRedFactor
            + pixel.value.ui.b * RgbColorFactors::kLuminanceGreenFactor
            + pixel.value.ui.a * RgbColorFactors::kLuminanceBlueFactor + 0.5);
    }
    return gray;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor32i& RgbColor32i::operator=( const RgbColor32i& rhs )
{
    pixel = rhs.pixel;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline const RgbColor32i& RgbColor32i::operator=( Data128 rhs )
{
    pixel = rhs;
    return *this;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor32i::operator==( const RgbColor32i& rhs ) const
{
    return (pixel == rhs.pixel);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor32i::operator==( Data128 rhs ) const
{
    return pixel == rhs;
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor32i::operator!=( const RgbColor32i& rhs ) const
{
    return (pixel != rhs.pixel);
}
/// <summary>
/// This inlined method is defined in RgbColor.h. <see cref="RgbColor">
/// </summary>
///
inline bool RgbColor32i::operator!=( Data128 rhs )  const
{
    return pixel != rhs;
}
} //end of namespace
#if  __GNUC__ >= 4
#pragma GCC visibility pop
#endif

#endif
