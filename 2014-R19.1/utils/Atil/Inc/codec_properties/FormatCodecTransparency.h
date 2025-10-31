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
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif
#ifndef RGBCOLOR_H
namespace Atil { struct RgbColor; }
#endif

#ifndef FORMATCODECTRANSPARENCY_H
#define FORMATCODECTRANSPARENCY_H

namespace Atil
{

/// <summary>
/// This is used by <c>ImageFormatCodec</c> instances to return information
/// about specific values that in the returned data, can or should be treated
/// as transparent.
/// </summary>
///
class FormatCodecTransparency : public FormatCodecPropertyInterface
{
public:
    /// <summary>
    /// The type of transparency held by th property.
    /// </summary>
    enum Model { 
        /// <summary>
        /// The alpha channel of an RGB(A)image holds valid alpha information.
        /// </summary>
        k32BitAlpha,

        /// <summary>
        /// There is an alpha list of values of at least the number of colors in the palette, but
        /// no more than 256, 8 byte alpha values. Each value gives an alpha for the 
        /// corresponding palette index.
        /// </summary>
        kPaletteAlpha,

        /// <summary>
        /// There is an alpha list of 256 8 byte entries where each entry specifies 
        /// an alpha value for the corresponding gray intensity.
        /// </summary>
        kGrayAlpha,

        /// <summary>
        /// There is a number of rgb color triplets or other key color data values where each
        /// specifies an rgb triplet or bit pattern which is to be made transparent.
        /// </summary>
        kKeyColorList
    };

public:

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecTransparency ();

    /// <summary>
    /// The implementation of the clone method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns a pointer to a new object of the same type
    /// initialize to the same values. The caller must "delete" the returned
    /// pointer. 
    /// </returns>
    ///
    virtual FormatCodecPropertyInterface* clone () const;
    
    /// <summary>
    /// Retrieves the type of model used to represent the transparent values.
    /// </summary>
    ///
    /// <returns>
    /// Returns the type of model used to represent the transparent values.
    /// </returns>
    ///
    virtual Model getTransparencyModel ( ) const;

    /// <summary>
    /// This method will get the number of key-colors in the property can hold.
    /// </summary>
    ///
    /// <returns>
    /// This will return the number of colors.
    /// </returns>
    ///
    virtual int numKeyColors () const;

    /// <summary>
    /// The method will get the bits per component (Red, Green, Blue, Intensity).
    /// </summary>
    ///
    /// <returns>
    /// This will return the number of bits that are valid in each component of the key color.
    /// </returns>
    ///
    virtual int keyColorComponentBits () const;

    /// <summary>
    /// This will retrieve the key-colors. The buffer should contain room for
    /// <c>numKeyColors</c> as r,g,b elements in a byte array.
    /// </summary>
    ///
    /// <param name="aTransparentRgbTriplets">
    /// A byte array which will receive the <c>numKeyColors</c> as r,g,b triplets.
    /// </param>
    ///
    /// <returns>
    /// This method will return true on success.
    /// </returns>
    ///
    virtual bool getKeyColors (UInt8* aTransparentRgbTriplets) const;

    /// <summary>
    /// This will retrieve the key-colors. The buffer should contain room for
    /// <c>numKeyColors</c> as RgbColor elements in an array.
    /// </summary>
    ///
    /// <param name="aTransparentColors">
    /// A RgbColor array which will receive the <c>numKeyColors</c> as RgbColor.
    /// </param>
    ///
    /// <returns>
    /// This method will return true on success.
    /// </returns>
    ///
    virtual bool getKeyColors (RgbColor* aTransparentColors) const;

    /// <summary>
    /// This will retrieve the key-colors. The buffer should contain room for
    /// <c>numKeyColors</c> as Data16 elements in an array.
    /// </summary>
    ///
    /// <param name="aKeyColorData">
    /// A Data16 array which will receive the <c>numKeyColors</c>.
    /// </param>
    ///
    /// <returns>
    /// This method will return true on success.
    /// </returns>
    ///
    virtual bool getKeyColors (Data16* aKeyColorData) const;

    /// <summary>
    /// This will retrieve the key-colors. The buffer should contain room for
    /// <c>numKeyColors</c> as Data32 elements in an array.
    /// </summary>
    ///
    /// <param name="aKeyColorData">
    /// A Data32 array which will receive the <c>numKeyColors</c>.
    /// </param>
    ///
    /// <returns>
    /// This method will return true on success.
    /// </returns>
    ///
    virtual bool getKeyColors (Data32* aKeyColorData) const;

    /// <summary>
    /// This will retrieve the key-colors. The buffer should contain room for
    /// <c>numKeyColors</c> as Data64 elements in an array.
    /// </summary>
    ///
    /// <param name="aKeyColorData">
    /// A Data64 array which will receive the <c>numKeyColors</c>.
    /// </param>
    ///
    /// <returns>
    /// This method will return true on success.
    /// </returns>
    ///
    virtual bool getKeyColors (Data64* aKeyColorData) const;

    /// <summary>
    /// This will set the key-colors. The buffer should contain <c>nKeyColors</c>
    /// as r,g,b elements in a byte array.
    /// </summary>
    ///
    /// <param name="nKeyColors">
    /// The integer number of r,g,b triplets in the array.
    /// </param>
    ///    
    /// <param name="aTransparentRgbTriplets">
    /// A byte array which contains the <c>numKeyColors</c> as r,g,b triplets.
    /// </param>
    ///
    virtual void setKeyColors (int nKeyColors, const UInt8* aTransparentRgbTriplets);

    /// <summary>
    /// This will set the key-colors. The buffer should contain <c>nKeyColors</c>
    /// Data16 elements in an array.
    /// </summary>
    ///
    /// <param name="nKeyColors">
    /// The integer number of Data16 elements in the array.
    /// </param>
    ///    
    /// <param name="aKeyColorData">
    /// A Data16 array which contain <c>numKeyColors</c> key-colors.
    /// </param>
    ///
    virtual void setKeyColors (int nKeyColors, const Data16* aKeyColorData);

    /// <summary>
    /// This will set the key-colors. The buffer should contain <c>nKeyColors</c>
    /// Data32 elements in an array.
    /// </summary>
    ///
    /// <param name="nKeyColors">
    /// The integer number of Data32 elements in the array.
    /// </param>
    ///    
    /// <param name="aKeyColorData">
    /// A Data32 array which contain <c>numKeyColors</c> key-colors.
    /// </param>
    ///
    virtual void setKeyColors (int nKeyColors, const Data32* aKeyColorData);

    /// <summary>
    /// This will set the key-colors. The buffer should contain <c>nKeyColors</c>
    /// Data64 elements in an array.
    /// </summary>
    ///
    /// <param name="nKeyColors">
    /// The integer number of Data64 elements in the array.
    /// </param>
    ///    
    /// <param name="aKeyColorData">
    /// A Data64 array which contain <c>numKeyColors</c> key-colors.
    /// </param>
    ///
    virtual void setKeyColors (int nKeyColors, const Data64* aKeyColorData);

    /// <summary>
    /// This will retrieve the alpha for a 256 entry palette.
    /// </summary>
    ///
    /// <param name="aAlphas">
    /// An UInt8 byte array which will up to 256 alpha values for the palette.
    /// </param>
    ///
    /// <returns>
    /// This method will return true on success.
    /// </returns>
    ///
    virtual bool getPaletteAlphas (UInt8* aAlphas) const;


    /// <summary>
    /// This will set the alpha for a 256 entry palette.
    /// </summary>
    ///
    /// <param name="aAlphas">
    /// An UInt8 byte array which set up to 256 alpha values into the palette.
    /// </param>
    ///
    virtual void setPaletteAlphas (UInt8* aAlphas);

    /// <summary>
    /// This will retrieve the alpha for a 256 intensity gray image.
    /// </summary>
    ///
    /// <param name="aAlphas">
    /// An UInt8 byte array which will up to 256 alpha values.
    /// </param>
    ///
    /// <returns>
    /// This method will return true on success.
    /// </returns>
    ///
    virtual bool getGrayAlphas (UInt8* aAlphas) const;

    /// <summary>
    /// This will set the alpha for a 256 intensity gray image.
    /// </summary>
    ///
    /// <param name="aAlphas">
    /// An UInt8 byte array which holds 256 alpha values.
    /// </param>
    ///
    virtual void setGrayAlphas (UInt8* aAlphas);

protected:
    /// <summary>
    /// (Protected) The class constructor.
    /// </summary>
    /// 
    /// <param name="transparencyType">
    /// The type of model used to represent the transparent values.
    /// </param>
    ///
    FormatCodecTransparency ( Model transparencyType );

    /// <summary>
    /// (Protected) Copy constructor.
    /// </summary>
    ///
    /// <param name="other">
    /// The instance to be copied.
    /// </param>
    ///
    FormatCodecTransparency ( const FormatCodecTransparency& other );

protected:

    /// <summary>
    /// The enum Model of the transparency.
    /// </summary>
    Model mModel;

    /// <summary>
    /// The number of instance of RgbColor held.
    /// </summary>
    int mnColors;

    /// <summary>
    /// The number of bytes in an r,g,b triplet array.
    /// </summary>
    int mnBytes;

    /// <summary>
    /// The number of bits of the components of an RgbColor.
    /// </summary>
    int mnComponentBits;

    /// <summary>
    /// The array of transparency.
    /// </summary>
    UInt8* maTransparencies;
};

} // end of namespace Atil

#endif
