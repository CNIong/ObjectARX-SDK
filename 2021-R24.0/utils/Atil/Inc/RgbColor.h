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
#ifndef DATAMODELATTRIBUTES_H
#include "DataModelAttributes.h"
#endif

#ifndef RGBCOLOR_H
#define RGBCOLOR_H

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
    RgbColor (Data8 red, Data8 green, Data8 blue);

    /// <summary>
    /// An initializing constructor that sets the first, second, third, and Alpha members.
    /// The arguments should be in the proper color orders. First is set low, Second higher, Third highest.
    /// </summary>
    ///
    /// <param name='first'>The value to set.
    /// </param>
    ///
    /// <param name='second'>The value to set.
    /// </param>
    ///
    /// <param name='third'>The value to set.
    /// </param>
    ///
    /// <param name='alpha'>The value to set into the alpha member.
    /// </param>
    ///
    RgbColor (Data8 first, Data8 second, Data8 third, Data8 alpha);

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
    const RgbColor& set (Data8 red, Data8 green, Data8 blue);

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
    const RgbColor& set (Data8 red, Data8 green, Data8 blue, Data8 alpha,
        DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kRedGreenBlueAlpha);

    /// <summary>
    /// This method will return the gray intensity level of the members
    /// using the constant members of <c>RgbColorFactors</c><see cref="RgbColorFactors"/>.
    /// </summary>
    /// <param name='format'>The format of the object so that the gray can be calculated.</param>
    Data8 asGray (DataModelAttributes::ChannelOrder format = DataModelAttributes::kRedGreenBlueAlpha) const;

    union {
        /// <summary>Data members union of red, green, blue, and alpha.
        /// </summary>
        struct { 
            /// <summary>red member
            /// </summary>
            Data8 red; 
            /// <summary>green member
            /// </summary>
            Data8 green; 
            /// <summary>blue member
            /// </summary>
            Data8 blue; 
            /// <summary>alpha member
            /// </summary>
            Data8 alpha;
        } rgba;

        /// <summary>Data members union of blue, green, red, and alpha.
        /// </summary>
        struct { 
            /// <summary>blue member
            /// </summary>
            Data8 blue; 
            /// <summary>green member
            /// </summary>
            Data8 green; 
            /// <summary>red member
            /// </summary>
            Data8 red; 
            /// <summary>alpha member
            /// </summary>
            Data8 alpha;
        } bgra;

        /// <summary>union member as packed 32 bit integer.
        /// </summary>
        Data32 packed;
    };

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This returns a const pointer to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor& operator=( const RgbColor& rhs );

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This will return a const reference to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor& operator=( Data32 rhs );

    /// <summary>
    /// The cast operator allows the structure to be accessed as a 32bit data value.
    /// </summary>
    ///
    /// <returns>
    /// This returns <c>*this</c> as a <c>Data32</c> instance.
    /// </returns>
    ///
    operator Data32() const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( const RgbColor& rhs ) const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( Data32 rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( const RgbColor& rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( Data32 rhs ) const;
};
/// <summary>
/// A structure containing a union that holds the eight-bit red, green, blue and alpha
/// values as a thirty-two-bit integer value. The <c>RgbColor</c> is the data member of
/// RGBA images. Each pixel can be represented as an instance of the RgbColor structure.
/// </summary>
///
struct RgbColor5b 
{
public:

    /// <summary> This describes the bit fields of the object. </summary>
    enum Fields {
        /// <summary> This describes 5 bits for each color channel and one bit as alpha. </summary>
        k5551,
        /// <summary> This describes 5 bits for red and blue with 6 for green. </summary>
        k565,
    };

public:
    /// <summary>
    /// Default (empty) constructor.
    /// </summary>
    RgbColor5b ( );

    /// <summary>
    /// An initializing constructor it accepts an <c>RgbColor5b</c> instance as an integer.
    /// </summary>
    ///
    /// <param name='color'>A 16 bit value that will be treated as 8 bit red, green,
    /// blue, and alpha values.
    /// </param>
    ///
    RgbColor5b ( Data16 color );

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
    RgbColor5b (Data8 red, Data8 green, Data8 blue);

    /// <summary>
    /// An initializing constructor that sets the first, second, third, and Alpha members.
    /// </summary>
    ///
    /// <param name='first'>The value to set.
    /// </param>
    ///
    /// <param name='second'>The value to set.
    /// </param>
    ///
    /// <param name='third'>The value to set.
    /// </param>
    ///
    /// <param name='alpha'>The value to set into the alpha member.
    /// </param>
    ///
    /// <param name='fields'>The bit layout of the channels within the pixel.</param>

    RgbColor5b (Data8 first, Data8 second, Data8 third, Data8 alpha
        , DataModelAttributes::BitFields fields = DataModelAttributes::k5551);

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
    const RgbColor5b& set (Data8 red, Data8 green, Data8 blue);

    /// <summary>This method sets the Red, Green, Blue, and Alpha members.</summary>
    /// <param name='red'>The value to set into the red member.</param>
    /// <param name='green'>The value to set into the green member.</param>
    /// <param name='blue'>The value to set into the blue member.</param>
    /// <param name='alpha'>The value to set into the alpha member.</param>
    /// <param name='fields'>The bit layout of the channels within the pixel.</param>
    /// <param name='fmt'> Describes the color order of channels within the pixel.</param>
    /// <remarks>These are the channel values 0..31 or 0..63 for green in 565.</remarks>
    const RgbColor5b& set (Data8 red, Data8 green, Data8 blue, Data8 alpha
        , DataModelAttributes::BitFields fields = DataModelAttributes::k5551
        , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);

    /// <summary>This method will return the channel values.</summary>
    /// <param name='fields'>The bit layout of the object so that the channels can be extracted.</param>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    /// <remarks>The returns are not scaled to a full eight bits. Each holds the ranged value for
    /// the appropriate channel which is either 5 or 6 bits or 1 bit for alpha. </remarks>
    void getChannelData (Data8& red, Data8& green, Data8& blue, Data8& alpha
        , DataModelAttributes::BitFields fields, DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>This method will return the color scaled to an 8 bit range in RGB form.</summary>
    /// <param name='fields'>The bit layout of the object so that the channels can be extracted.</param>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    RgbColor asRgbColor (DataModelAttributes::BitFields fields, DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>This method will return the color scaled to an 8 bit range in BGR form.</summary>
    /// <param name='fields'>The bit layout of the object so that the channels can be extracted.</param>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    RgbColor asBgrColor (DataModelAttributes::BitFields fields, DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>
    /// This method will return the gray intensity level of the members
    /// using the constant members of <c>RgbColorFactors</c><see cref="RgbColorFactors"/>.
    /// </summary>
    /// <param name='fields'>The bit layout of the channels within the pixel.</param>
    /// <param name='fmt'>The format of the object so that the gray can be calculated.</param>
    Data8 asGray (DataModelAttributes::BitFields fields
        , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;

    /// <summary> The data value for the 16bit RGB pixel.</summary>
    Data16 packed;

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This returns a const pointer to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor5b& operator=( const RgbColor5b& rhs );

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This will return a const reference to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor5b& operator=( Data16 rhs );

    /// <summary>
    /// The cast operator allows the structure to be accessed as a 64bit data value.
    /// </summary>
    ///
    /// <returns>
    /// This returns <c>*this</c> as a <c>Data32</c> instance.
    /// </returns>
    ///
    operator Data16() const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( const RgbColor5b& rhs ) const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( Data16 rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( const RgbColor5b& rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( Data16 rhs ) const;
};
/// <summary>
/// A structure containing a union that holds the ten-bit red, green, blue and alpha
/// values as a thirty-two-bit integer value. The <c>RgbColor</c> is the data member of
/// RGBA images. Each pixel can be represented as an instance of the RgbColor structure.
/// </summary>
///
struct RgbColor10 
{
public:
    /// <summary>
    /// Default (empty) constructor.
    /// </summary>
    RgbColor10 ( );

    /// <summary>
    /// An initializing constructor it accepts an <c>RgbColor10</c> instance as an integer.
    /// </summary>
    ///
    /// <param name='color'>A 32 bit value that will be treated as 10 bit red, green,
    /// blue, and 2 bits of alpha values.
    /// </param>
    ///
    RgbColor10 ( Data32 color );

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
    RgbColor10 (Data16 red, Data16 green, Data16 blue);

    /// <summary>
    /// An initializing constructor that sets the first, second, third, and Alpha members.
    /// </summary>
    ///
    /// <param name='first'>The value to set.
    /// </param>
    ///
    /// <param name='second'>The value to set.
    /// </param>
    ///
    /// <param name='third'>The value to set.
    /// </param>
    ///
    /// <param name='alpha'>The value to set into the alpha member.
    /// </param>
    RgbColor10 (Data16 first, Data16 second, Data16 third, Data16 alpha);

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
    const RgbColor10& set (Data16 red, Data16 green, Data16 blue);

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
    /// <param name='fmt'> Describes the color order of channels within the pixel.</param>
    const RgbColor10& set (Data16 red, Data16 green, Data16 blue, Data16 alpha
        , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);

    /// <summary>This method will return the channel values.</summary>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    /// <remarks>The returns are not scaled to a full eight bits. Each holds the ranged value for
    /// the appropriate channel which is 10 or 3 bits for alpha. </remarks>
    void getChannelData (Data16& red, Data16& green, Data16& blue, Data16& alpha
        , DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>This method will return the color scaled to an 8 bit range in RGB form.</summary>
    /// <param name='fields'>The bit layout of the object so that the channels can be extracted.</param>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    RgbColor asRgbColor (DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>This method will return the color scaled to an 8 bit range in BGR form.</summary>
    /// <param name='fields'>The bit layout of the object so that the channels can be extracted.</param>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    RgbColor asBgrColor (DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>
    /// This method will return the gray intensity level of the members
    /// using the constant members of <c>RgbColorFactors</c><see cref="RgbColorFactors"/>.
    /// </summary>
    /// <param name='fmt'>The format of the object so that the gray can be calculated.</param>
    Data16 asGray (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;

    /// <summary>union member as packed 32 bit integer.
    /// </summary>
    Data32 packed;

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This returns a const pointer to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor10& operator=( const RgbColor10& rhs );

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This will return a const reference to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor10& operator=( Data32 rhs );

    /// <summary>
    /// The cast operator allows the structure to be accessed as a 64bit data value.
    /// </summary>
    ///
    /// <returns>
    /// This returns <c>*this</c> as a <c>Data32</c> instance.
    /// </returns>
    ///
    operator Data32() const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( const RgbColor10& rhs ) const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( Data32 rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( const RgbColor10& rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( Data32 rhs ) const;
};


/// <summary>
/// A structure containing a union that holds the sixteen-bit red, green, blue and alpha
/// values as a sixty-four-bit integer value. The <c>RgbColor</c> is the data member of
/// RGBA images. Each pixel can be represented as an instance of the RgbColor structure.
/// </summary>
///
struct RgbColor16i 
{
public:
    /// <summary>
    /// Default (empty) constructor.
    /// </summary>
    RgbColor16i ( );

    /// <summary>
    /// An initializing constructor it accepts an <c>RgbColor16i</c> instance as an integer.
    /// </summary>
    ///
    /// <param name='color'>A 64 bit value that will be treated as 8 bit red, green,
    /// blue, and alpha values.
    /// </param>
    ///
    RgbColor16i ( Data64 color );

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
    RgbColor16i (Data16 red, Data16 green, Data16 blue);

    /// <summary>
    /// An initializing constructor that sets the first, second, third, and Alpha members.
    /// </summary>
    ///
    /// <param name='first'>The value to set.
    /// </param>
    ///
    /// <param name='second'>The value to set.
    /// </param>
    ///
    /// <param name='third'>The value to set.
    /// </param>
    ///
    /// <param name='alpha'>The value to set into the alpha member.
    /// </param>
    RgbColor16i (Data16 first, Data16 second, Data16 third, Data16 alpha);

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
    const RgbColor16i& set (Data16 red, Data16 green, Data16 blue);

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
    /// <param name='fmt'> Describes the color order of channels within the pixel.</param>
    const RgbColor16i& set (Data16 red, Data16 green, Data16 blue, Data16 alpha
        , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);

    /// <summary>This method will return the color scaled to an 8 bit range in RGB form.</summary>
    /// <param name='fmt'> Describes the color order of channels within the pixel.</param>
    RgbColor asRgbColor (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;

    /// <summary>This method will return the color scaled to an 8 bit range in BGR form.</summary>
    /// <param name='fmt'> Describes the color order of channels within the pixel.</param>    
    RgbColor asBgrColor (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;

    /// <summary>
    /// This method will return the gray intensity level of the members
    /// using the constant members of <c>RgbColorFactors</c><see cref="RgbColorFactors"/>.
    /// </summary>
    /// <param name='fmt'>The format of the object so that the gray can be calculated.</param>
    Data16 asGray (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;

    union {
        /// <summary>Data members union of red, green, blue, and alpha.
        /// </summary>
        struct { 
            /// <summary>red member
            /// </summary>
            Data16 red; 
            /// <summary>green member
            /// </summary>
            Data16 green; 
            /// <summary>blue member
            /// </summary>
            Data16 blue; 
            /// <summary>alpha member
            /// </summary>
            Data16 alpha;
        } rgba;

        /// <summary>Data members union of blue, green, red, and alpha.
        /// </summary>
        struct { 
            /// <summary>blue member
            /// </summary>
            Data16 blue; 
            /// <summary>green member
            /// </summary>
            Data16 green; 
            /// <summary>red member
            /// </summary>
            Data16 red; 
            /// <summary>alpha member
            /// </summary>
            Data16 alpha;
        } bgra;

        /// <summary>union member as packed 32 bit integer.
        /// </summary>
        Data64 packed;
    };

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This returns a const pointer to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor16i& operator=( const RgbColor16i& rhs );

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This will return a const reference to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor16i& operator=( Data64 rhs );

    /// <summary>
    /// The cast operator allows the structure to be accessed as a 64bit data value.
    /// </summary>
    ///
    /// <returns>
    /// This returns <c>*this</c> as a <c>Data32</c> instance.
    /// </returns>
    ///
    operator Data64() const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( const RgbColor16i& rhs ) const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( Data64 rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( const RgbColor16i& rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( Data64 rhs ) const;
};

/// <summary>
/// A structure containing a union that holds the sixteen-bit red, green, blue and alpha
/// values as a sixty-four-bit integer value. The <c>RgbColor</c> is the data member of
/// RGBA images. Each pixel can be represented as an instance of the RgbColor structure.
/// </summary>
///
struct RgbColor16f 
{
public:
    /// <summary>
    /// Default (empty) constructor.
    /// </summary>
    RgbColor16f ( );

    /// <summary>
    /// An initializing constructor it accepts an <c>RgbColor16f</c> instance as an integer.
    /// </summary>
    ///
    /// <param name='color'>A 64 bit value that will be treated as 8 bit red, green,
    /// blue, and alpha values.
    /// </param>
    ///
    RgbColor16f ( Data64 color );

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
    RgbColor16f (half red, half green, half blue);

    /// <summary>
    /// An initializing constructor that sets the first, second, third, and Alpha members.
    /// </summary>
    ///
    /// <param name='first'>The value to set.
    /// </param>
    ///
    /// <param name='second'>The value to set.
    /// </param>
    ///
    /// <param name='third'>The value to set.
    /// </param>
    ///
    /// <param name='alpha'>The value to set into the alpha member.
    /// </param>
    RgbColor16f (half first, half second, half third, half alpha);

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
    const RgbColor16f& set (half red, half green, half blue);

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
    /// <param name='fmt'> Describes the color order of channels within the pixel.</param>
    const RgbColor16f& set (half red, half green, half blue, half alpha
        , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);

    /// <summary>This method will return the color scaled to an 8 bit range in RGB form.</summary>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    RgbColor asRgbColor (DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>This method will return the color scaled to an 8 bit range in BGR form.</summary>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    RgbColor asBgrColor (DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>
    /// This method will return the gray intensity level of the members
    /// using the constant members of <c>RgbColorFactors</c><see cref="RgbColorFactors"/>.
    /// </summary>
    /// <param name='fmt'>The format of the object so that the gray can be calculated.</param>
    half asGray (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;

    /// <summary>Structure that describes the channel layout within the packed 64bit value
    /// </summary>
    typedef struct { 
        /// <summary>blue member
        /// </summary>
        half blue; 
        /// <summary>green member
        /// </summary>
        half green; 
        /// <summary>red member
        /// </summary>
        half red; 
        /// <summary>alpha member
        /// </summary>
        half alpha;
    } Channels;

    /// <summary>Structure that stores the channel layout within the packed 64bit value
    /// </summary>
    union {
        struct { 
            /// <summary>blue member
            /// </summary>
            Data16 blue; 
            /// <summary>green member
            /// </summary>
            Data16 green; 
            /// <summary>red member
            /// </summary>
            Data16 red; 
            /// <summary>alpha member
            /// </summary>
            Data16 alpha;
        } bgra;

        /// <summary>The pixel data as packed 64 bit integer.
        /// </summary>
        Data64 packed;
    };

    /// <summary>Get the pixel in the <c>Channels</c> structure form.</summary>
    /// <returns>This returns an instance of the <c>Channels</c> structure containing the channel data.</returns>
    Channels getChannelData() const;

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This returns a const pointer to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor16f& operator=( const RgbColor16f& rhs );

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This will return a const reference to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor16f& operator=( Data64 rhs );

    /// <summary>
    /// The cast operator allows the structure to be accessed as a 64bit data value.
    /// </summary>
    ///
    /// <returns>
    /// This returns <c>*this</c> as a <c>Data32</c> instance.
    /// </returns>
    ///
    operator Data64() const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( const RgbColor16f& rhs ) const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( Data64 rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( const RgbColor16f& rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( Data64 rhs ) const;
};

/// <summary>
/// A structure containing a union that holds the thirty two bit float red, green, blue and alpha
/// values as a 128 bit integer value. The <c>RgbColor</c> is the data member of
/// RGBA images. Each pixel can be represented as an instance of the RgbColor structure.
/// </summary>
///
struct RgbColor32f 
{
public:
    /// <summary>
    /// Default (empty) constructor.
    /// </summary>
    RgbColor32f ( );

    /// <summary>
    /// An initializing constructor it accepts an <c>RgbColor32f</c> instance as an integer.
    /// </summary>
    ///
    /// <param name='color'>A 64 bit value that will be treated as 8 bit red, green,
    /// blue, and alpha values.
    /// </param>
    ///
    RgbColor32f ( Data128 color );

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
    RgbColor32f (float red, float green, float blue);

    /// <summary>
    /// An initializing constructor that sets the first, second, third, and Alpha members.
    /// </summary>
    ///
    /// <param name='first'>The value to set.
    /// </param>
    ///
    /// <param name='second'>The value to set.
    /// </param>
    ///
    /// <param name='third'>The value to set.
    /// </param>
    ///
    /// <param name='alpha'>The value to set into the alpha member.
    /// </param>
    RgbColor32f (float first, float second, float third, float alpha);

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
    const RgbColor32f& set (float red, float green, float blue);

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
    /// <param name='fmt'> Describes the color order of channels within the pixel.</param>
    const RgbColor32f& set (float red, float green, float blue, float alpha
        , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);

    /// <summary>This method will return the color scaled to an 8 bit range in RGB form.</summary>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    RgbColor asRgbColor (DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>This method will return the color scaled to an 8 bit range in BGR form.</summary>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    RgbColor asBgrColor (DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>
    /// This method will return the gray intensity level of the members
    /// using the constant members of <c>RgbColorFactors</c><see cref="RgbColorFactors"/>.
    /// </summary>
    /// <param name='fmt'>The format of the object so that the gray can be calculated.</param>
    float asGray (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;

    /// <summary>Data member as an 128 bit integer structure <c>Data128</c>.
    /// </summary>
    Data128 pixel;

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This returns a const pointer to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor32f& operator=( const RgbColor32f& rhs );

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This will return a const reference to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor32f& operator=( Data128 rhs );

    /// <summary>
    /// The cast operator allows the structure to be accessed as a 128 bit data value.
    /// </summary>
    ///
    /// <returns>
    /// This returns <c>*this</c> as a <c>Data128</c> instance.
    /// </returns>
    ///
    operator Data128() const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( const RgbColor32f& rhs ) const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( Data128 rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( const RgbColor32f& rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( Data128 rhs ) const;
};

/// <summary>
/// A structure containing a union that holds the thirty two bit integer red, green, blue and alpha
/// values as a 128 bit integer value. The <c>RgbColor</c> is the data member of
/// RGBA images. Each pixel can be represented as an instance of the RgbColor structure.
/// </summary>
///
struct RgbColor32i 
{
public:
    /// <summary>
    /// Default (empty) constructor.
    /// </summary>
    RgbColor32i ( );

    /// <summary>
    /// An initializing constructor it accepts an <c>RgbColor32f</c> instance as an integer.
    /// </summary>
    ///
    /// <param name='color'>A 64 bit value that will be treated as 8 bit red, green,
    /// blue, and alpha values.
    /// </param>
    ///
    RgbColor32i ( Data128 color );

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
    RgbColor32i (Data32 red, Data32 green, Data32 blue);

    /// <summary>
    /// An initializing constructor that sets the first, second, third, and Alpha members.
    /// </summary>
    ///
    /// <param name='first'>The value to set.
    /// </param>
    ///
    /// <param name='second'>The value to set.
    /// </param>
    ///
    /// <param name='third'>The value to set.
    /// </param>
    ///
    /// <param name='alpha'>The value to set into the alpha member.
    /// </param>
    RgbColor32i (Data32 first, Data32 second, Data32 third, Data32 alpha);

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
    const RgbColor32i& set (Data32 red, Data32 green, Data32 blue);

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
    /// <param name='fmt'> Describes the color order of channels within the pixel.</param>
    const RgbColor32i& set (Data32 red, Data32 green, Data32 blue, Data32 alpha
        , DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha);

    /// <summary>This method will return the color scaled to an 8 bit range in RGB form.</summary>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    RgbColor asRgbColor (DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>This method will return the color scaled to an 8 bit range in BGR form.</summary>
    /// <param name='fmt'>The format of the object so that the channels can be extracted.</param>
    RgbColor asBgrColor (DataModelAttributes::ChannelOrder fmt) const;

    /// <summary>
    /// This method will return the gray intensity level of the members
    /// using the constant members of <c>RgbColorFactors</c><see cref="RgbColorFactors"/>.
    /// </summary>
    /// <param name='fmt'>The format of the object so that the gray can be calculated.</param>
    Data32 asGray (DataModelAttributes::ChannelOrder fmt = DataModelAttributes::kBlueGreenRedAlpha) const;

    /// <summary>Data member as an 128 bit integer structure <c>Data128</c>.
    /// </summary>
    Data128 pixel;

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This returns a const pointer to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor32i& operator=( const RgbColor32i& rhs );

    /// <summary>
    /// The assignment operator over writes the current values with those from the argument.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be assigned. </param>
    ///
    /// <returns>
    /// This will return a const reference to <c>*this</c>.
    /// </returns>
    ///
    const RgbColor32i& operator=( Data128 rhs );

    /// <summary>
    /// The cast operator allows the structure to be accessed as a 128 bit data value.
    /// </summary>
    ///
    /// <returns>
    /// This returns <c>*this</c> as a <c>Data128</c> instance.
    /// </returns>
    ///
    operator Data128() const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( const RgbColor32i& rhs ) const;

    /// <summary>
    /// The equals operator returns true if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are equivalent.
    /// </returns>
    ///
    bool operator==( Data128 rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( const RgbColor32i& rhs ) const;

    /// <summary>
    /// The equals operator returns false if the members of the object and the argument are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be tested against. </param>
    ///
    /// <returns>
    /// This will return true if the colors are not equivalent.
    /// </returns>
    ///
    bool operator!=( Data128 rhs ) const;
};

/*
// 5-5-5-1
mnBlueMask = 0x001F;
mnGreenMask = 0x03E0;
mnRedMask = 0x7C00;
mnAlphaMask = 0x8000

// 5-6-5
mnBlueMask = 0x001F;
mnGreenMask = 0x07E0;
mnRedMask = 0xF800;
*/

/// <summary>
/// Constants declared for converting RGB values into Intensity or Grayscale values.
/// </summary>
///
namespace RgbColorFactors
{
/// <summary>
/// Constant for conversion of RGB to Gray Luminance red multiplier.
/// </summary>
const double kLuminanceRedFactor = 0.299;

/// <summary>
/// Constant for conversion of RGB to Gray Luminance green multiplier.
/// </summary>
const double kLuminanceGreenFactor = 0.587;

/// <summary>
/// Constant for conversion of RGB to Gray Luminance blue multiplier.
/// </summary>
const double kLuminanceBlueFactor = 0.114;

} //end of namespace

} //end of namespace

#ifndef RGBCOLOR_INL
#include <RgbColor.inl>
#endif

#endif

//#ifndef IMAGEPIXEL_H
//#include <ImagePixel.h>
//#endif
