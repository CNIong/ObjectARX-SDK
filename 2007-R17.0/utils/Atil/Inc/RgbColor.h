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

#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif

#ifndef  RGBCOLOR_H
#define  RGBCOLOR_H

namespace Atil
{

/// <summary>
/// A structure containing a union that holds the eight-bit red, green, blue and alpha
/// values as a thirty-two-bit integer value. The <c>RgbColor</c> is the data member of
/// RGBA images. Each pixel can be represented as an instance of the RgbColor structure.
/// </summary>
///
struct RgbColor 
{
public:
    /// <summary>
    /// Default (empty) constructor.
    /// </summary>
    RgbColor ( );

    /// <summary>
    /// An initializing constructor it accepts an <c>RgbColor</c> instance as an integer.
    /// </summary>
    ///
    /// <param name='color'>A 32 bit value that will be treated as 8 bit red, green,
    /// blue, and alpha values.
    /// </param>
    ///
    RgbColor ( Data32 color );

    /// <summary>
    /// An initializing constructor that sets the Red, Green, and Blue members.
    /// </summary>
    ///
    /// <param name='red'>The value to set into the red member.
    /// </param>
    ///
    /// <param name='green'>The value to set into the green member.
    /// </param>
    ///
    /// <param name='blue'>The value to set into the blue member.
    /// </param>
    ///
    RgbColor (int red, int green, int blue);

    /// <summary>
    /// An initializing constructor that sets the Red, Green, Blue, and Alpha members.
    /// </summary>
    ///
    /// <param name='red'>The value to set into the red member.
    /// </param>
    ///
    /// <param name='green'>The value to set into the green member.
    /// </param>
    ///
    /// <param name='blue'>The value to set into the blue member.
    /// </param>
    ///
    /// <param name='alpha'>The value to set into the alpha member.
    /// </param>
    ///
    RgbColor (int red, int green, int blue, int alpha);

    /// <summary>
    /// This method sets the Red, Green, and Blue members.
    /// </summary>
    ///
    /// <param name='red'>The value to set into the red member.
    /// </param>
    ///
    /// <param name='green'>The value to set into the green member.
    /// </param>
    ///
    /// <param name='blue'>The value to set into the blue member.
    /// </param>
    ///
    const RgbColor& set (int red, int green, int blue);

    /// <summary>
    /// This method sets the Red, Green, Blue, and Alpha members.
    /// </summary>
    ///
    /// <param name='red'>The value to set into the red member.
    /// </param>
    ///
    /// <param name='green'>The value to set into the green member.
    /// </param>
    ///
    /// <param name='blue'>The value to set into the blue member.
    /// </param>
    ///
    /// <param name='alpha'>The value to set into the alpha member.
    /// </param>
    ///
    const RgbColor& set (int red, int green, int blue, int alpha);

    /// <summary>
    /// This method will return the gray intensity level of the members
    /// using the constant members of <c>RgbColorFactors</c><see cref="RgbColorFactors"/>.
    /// </summary>
    ///
    Data8 asGray () const;

	union {
        /// <summary>union member</summary>
		struct { 
            /// <summary>red member</summary>
            Data8 red; 
            /// <summary>green member</summary>
            Data8 green; 
            /// <summary>blue member</summary>
            Data8 blue; 
            /// <summary>alpha member</summary>
            Data8 alpha;
        } rgba;
        /// <summary>union member</summary>
		Data32 packed;
	};

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    const RgbColor& operator=( const RgbColor& rhs );

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    const RgbColor& operator=( Data32 rhs );

    /// <summary>
    /// The cast operator allows the structure to be accessed as a 32bit data value.
    /// </summary>
    ///
    operator Data32() const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    bool operator==( const RgbColor& rhs ) const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    bool operator==( Data32 rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    bool operator!=( const RgbColor& rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    bool operator!=( Data32 rhs ) const;
};

/// <summary>
/// Constants declared for converting RGB values into Intensity or Grayscale values.
/// </summary>
///
namespace RgbColorFactors
{
const double kLuminanceRedFactor = 0.299;
const double kLuminanceGreenFactor = 0.587;
const double kLuminanceBlueFactor = 0.114;
}
} //end of namespace

#ifndef RGBCOLOR_INL
#include <RgbColor.inl>
#endif

#endif

//#ifndef IMAGEPIXEL_H
//#include <ImagePixel.h>
//#endif
