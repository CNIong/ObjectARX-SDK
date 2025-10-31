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
#define DATAMODELATTRIBUTES_H

namespace Atil
{
/// <summary>
/// An abstract base class that declares attributes of data models and exposes methods
/// that describe those attributes.
/// </summary>
///
/// <remarks>
/// This class, in combination with DataModel and ColorModelInterface, allows developers 
/// to create custom data models that have limited interoperability with ATIL operations.
/// </remarks>
///
class DataModelAttributes
{
public:
    /// <summary>
    /// This enum defines entries for each of the number of bits per pixel supported by ATIL.
    /// </summary>
    ///
    enum BitsPerPixel { k1, k8, k16, k32, k64, k128 };

    /// <summary>
    /// This enum defines entries for each of the color model that ATIL supports.
    /// </summary>
    ///
    enum DataModelType { 
        /// <summary>
        /// This entry indicates that there is no color model associated with the image pixels.
        /// Therefore each pixel is considered to be un-typed data and not directly "displayable".
        /// kDataModel images enjoy partial support from ATIL defined filters.
        /// </summary>
        ///
        kDataModel, 

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbModel</c> derivation of
        /// DataModel and that the images pixels are of a red, green, blue and possibly alpha
        /// configuration.
        /// </summary>
        ///
        kRgbModel, 

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbPaletteModel</c> derivation
        /// of DataModel and that the images pixels colors reside in a table of red, green, blue
        /// and possibly alpha values that the image pixels are eight bit indexes into that table.
        /// </summary>
        ///
        /// <remarks>
        /// A paletted image is considered to be a compressed form of a RGB(A) image.
        /// </remarks>
        ///
        kPalettedRgbModel,

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbGrayModel</c> derivation
        /// of DataModel and that the images pixels are eight bit intensities where 0 is no light and 255
        /// is full light.
        /// </summary>
        ///
        kGrayModel,

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>BitonalModel</c> derivation
        /// of DataModel and that the images pixels are one bit off and on values.
        /// </summary>
        ///
        kBitonalModel,

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbModel</c> derivation of
        /// DataModel and that the images pixels are of a red, green, blue and possibly alpha that
        /// has either 5 or 6 bits of information per field.
        /// </summary>
        ///
        kRgbModel5b, 

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbModel</c> derivation of
        /// DataModel and that the images pixels are of a red, green, blue and possibly alpha that
        /// has 10 bits of information per field accept alpha which as only 2 bits.
        /// </summary>
        ///
        kRgbModel10, 

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbModel</c> derivation of
        /// DataModel and that the images pixels are of a red, green, blue and possibly alpha that
        /// has 16 bits of information per field.
        /// </summary>
        ///
        kRgbModel16i, 

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbModel</c> derivation of
        /// DataModel and that the images pixels are of a red, green, blue and possibly alpha that
        /// has 16 bits float of information per field.
        /// </summary>
        ///
        kRgbModel16f, 

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbModel</c> derivation of
        /// DataModel and that the images pixels are of a red, green, blue and possibly alpha that
        /// has 32 bits float of information per field.
        /// </summary>
        ///
        kRgbModel32f,

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbGrayModel16i</c> derivation
        /// of DataModel and that the images pixels are sixteen bit intensities where 0 is no light and 65535
        /// is full light.
        /// </summary>
        ///
        kGrayModel16i,

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbGrayModel16f</c> derivation
        /// of DataModel and that the images pixels are sixteen bit intensities of float where 0 is no light and 1.0
        /// is full light.
        /// </summary>
        ///
        kGrayModel16f,

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbGrayModel32f</c> derivation
        /// of DataModel and that the images pixels are floats where 0 is no light and 1.0
        /// is full light.
        /// </summary>
        ///
        kGrayModel32f,

        /// <summary>
        /// This entry indicates that the DataModel is an instance of the <c>RgbGrayModel32i</c> derivation
        /// of DataModel and that the images pixels are floats where 0 is no light and DATA32_MAX
        /// is full light.
        /// </summary>
        ///
        kGrayModel32i
    };

    ///<summary>
    /// This enum defines entries for the pixel types of each of the color
    /// models that ATIL supports.
    ///</summary>
    ///
    enum PixelType {
        /// <summary>
        /// This entry indicates that the pixel is only one bit.
        /// </summary>
        ///
        kData1,

        /// <summary>
        /// This entry indicates that the pixel is an eight value.
        /// </summary>
        ///
        kData8,

        /// <summary>
        /// This entry indicates that the pixel is a sixteen bit value.
        /// </summary>
        ///
        kData16,

        /// <summary>
        /// This entry indicates that the pixel is a thirty two bit value.
        /// </summary>
        ///
        kData32,

        /// <summary>
        /// This entry indicates that the pixel is a sixty four bit value.
        /// </summary>
        ///
        kData64,

        /// <summary>
        /// This entry indicates that the pixel is a 128 bit value but is either
        /// two 64 bit values, four unsigned integers, or four float values.
        /// </summary>
        ///
        kData128,

        /// <summary>
        /// This entry indicates that the pixel is only one bit.
        /// </summary>
        ///
        kBitonal,

        /// <summary>
        /// This entry indicates that the pixel is an eight bit intensity.
        /// </summary>
        ///
        kGray,

        /// <summary>
        /// This entry indicates that the pixel is an eight bit index into a palette of colors.
        /// </summary>
        ///
        kPalettedRgb,

        /// <summary>
        /// This entry indicates that the pixel has four eight bit values of 
        /// intensity of red, green, blue, and possibly alpha.
        /// </summary>
        ///
        kRgba,

        /// <summary>
        /// This entry indicates that the pixel has four eight bit values of 
        /// intensity of blue, green, red, and possibly alpha.
        /// </summary>
        ///
        kBgra,

        /// <summary>
        /// This entry indicates that the pixel is a sixteen bit intensity.
        /// </summary>
        ///
        kGray16i,

        /// <summary>
        /// This entry indicates that the pixel is a sixteen bit of float.
        /// </summary>
        ///
        kGray16f,

        /// <summary>
        /// This entry indicates that the pixel is a thirty two bit float.
        /// </summary>
        ///
        kGray32f,
    
        /// <summary>
        /// This entry indicates that the pixel has three channels of 5 bits each
        /// intensity of red, green, blue, and possibly alpha.
        /// </summary>
        ///
        kRgba5b,

        /// <summary>
        /// This entry indicates that the pixel has three channels of 5 bits each
        /// intensity of blue, green, red, and possibly alpha.
        /// </summary>
        ///
        kBgra5b,

        /// <summary>
        /// This entry indicates that the pixel has four channels of 10 bits each
        /// intensity of red, green, blue, and possibly alpha.
        /// </summary>
        ///
        kRgba10i,

        /// <summary>
        /// This entry indicates that the pixel has four channels of 10 bits each
        /// intensity of blue, green, red, and possibly alpha.
        /// </summary>
        ///
        kBgra10i,

        /// <summary>
        /// This entry indicates that the pixel has four channels of 16 bits each
        /// intensity of red, green, blue, and possibly alpha.
        /// </summary>
        ///
        kRgba16i,

        /// <summary>
        /// This entry indicates that the pixel has four channels of 16 bits each
        /// intensity of blue, green, red, and possibly alpha.
        /// </summary>
        ///
        kBgra16i,

        /// <summary>
        /// This entry indicates that the pixel has four channels of 16 bits each
        /// intensity of red, green, blue, and possibly alpha.
        /// </summary>
        ///
        kRgba16f,

        /// <summary>
        /// This entry indicates that the pixel has four channels of 16 bits each
        /// intensity of blue, green, red, and possibly alpha.
        /// </summary>
        ///
        kBgra16f,

        /// <summary>
        /// This entry indicates that the pixel has four channels of 32 bits each
        /// intensity of red, green, blue, and possibly alpha.
        /// </summary>
        ///
        kRgba32f,

        /// <summary>
        /// This entry indicates that the pixel has four channels of 32 bits each
        /// intensity of blue, green, red, and possibly alpha.
        /// </summary>
        ///
        kBgra32f,

        /// <summary>
        /// This entry indicates that the pixel is a thirty two bit integer.
        /// </summary>
        ///
        kGray32i,

        /// <summary>
        /// This entry indicates that the pixel has four channels of 32 bits each
        /// intensity of red, green, blue, and possibly alpha.
        /// </summary>
        /// <remarks> There is currently no <c>DataModel</c> that accepts this pixetype. The enum
        /// extents support to <c>ImagePixel</c> and the <c>RgbColor32i</c> class only.</remarks>
        kRgba32i,

        /// <summary>
        /// This entry indicates that the pixel has four channels of 32 bits each
        /// intensity of blue, green, red, and possibly alpha.
        /// </summary>
        /// <remarks> There is currently no <c>DataModel</c> that accepts this pixetype. The enum
        /// extents support to <c>ImagePixel</c> and the <c>RgbColor32i</c> class only.</remarks>
        kBgra32i
    };

    /// <summary>
    /// This enum describes the type of data stored in the pixel or sample entry.
    /// </summary>
    /// 
    /// <remarks>
    /// If the DataModelType is kRgbModel, kPalettedRgbModel, kGrayModel 
    /// or kBitonalModel the datatype will always be kUnsignedInteger.
    /// For <c>DataModelType::kDataModel</c> any of the values could are allowed.
    /// kUnknown is be the default for non-color datamodels. 
    /// </remarks>
    ///
    enum DataType {
        /// <summary>
        /// The type data stored at each pixel is not known.
        /// </summary>
        ///
        kUnknown,

        /// <summary>
        /// The type data stored at each pixel is an unsigned short integer.
        /// </summary>
        ///
        kUnsignedShort, 

        /// <summary>
        /// The type data stored at each pixel is a signed short integer.
        /// </summary>
        ///
        kSignedShort,

        /// <summary>
        /// The type data stored at each pixel is an unsigned integer.
        /// </summary>
        ///
        kUnsignedInteger, 
        
        /// <summary>
        /// The type data stored at each pixel is a signed integer.
        /// </summary>
        ///
        kSignedInteger,
        
        /// <summary>
        /// The type data stored at each pixel is a 16 bit float (half) value.
        /// </summary>
        ///
        kFloat16,

        /// <summary>
        /// The type data stored at each pixel is a float value.
        /// </summary>
        ///
        kFloat,

        /// <summary>
        /// The type data stored at each pixel is a unsigned integral value holding 
        /// fields with variable bits per channel. </summary>
        kBitFields
    };

    /// <summary> This enum describes the field format for pixels described by the DataModel.</summary>
    /// <remark> This only describes the field layout. The placement of colors in the fields is
    /// determined by the <c>DataModelAttributes::PixelType</c> as either kRgba or kBgra.
    enum BitFields {
        /// <summary> The bits take the entire width of each channel within the pixel.</summary>
        kFull,
        /// <summary> This describes 5 bits for each r,g,b channel and one bit of alpha within a 16bit width.</summary>
        k5551,
        /// <summary> This describes 5 bits for red and blue and 6 bits of green within a 16bit width.</summary>
        k565
    };

    /// <summary> This enum describes the odder of channels in pixels described by the DataModel.</summary>
    enum ChannelOrder {
        ///<summary> This image has only a single channel. </summary>
        kSingleChannel,
        ///<summary> This image has multiple channels with a lead of red. </summary>
        kRedGreenBlueAlpha,
        ///<summary> This image has multiple channels with a lead of blue. </summary>
        kBlueGreenRedAlpha 
    };
public:
    /// <summary>
    /// This abstract method requires derived class to implement it. 
    /// It is intended to expose the bits per pixel of a datamodel.
    /// </summary>
    ///
    /// <returns>
    /// An entry of the <c>Atil::DataModelAttributes::BitsPerPixel</c> enum indicating the 
    /// number of bits per pixel for each pixel in an image.
    /// </returns>
    ///
    virtual BitsPerPixel bitsPerPixel () const = 0;

    /// <summary>
    /// This abstract method requires derived class to implement it. 
    /// It is intended to expose the used bits per pixel of a datamodel which is a the same
    /// or less than the bits per pixel.
    /// </summary>
    ///
    /// <returns>
    /// This will return the number pixels used out of the number of bits stored for each
    /// pixel in the image. 
    /// </returns>
    ///
    virtual int bitsUsedPerPixel () const = 0;

    /// <summary>
    /// This abstract method requires derived class to implement it. 
    /// It is intended to expose the dataModelType of a datamodel. This provides
    /// pseudo RTTI support for the ATIL defined and exported datamodels.
    /// </summary>
    ///
    /// <returns>
    /// This returns and instance of the <c>Atil::DataModelAttributes::DataModelType</c>
    /// indicating one of the ATIL internal color model <c>DataModel</c> derived classes.
    /// </returns>
    ///
    virtual DataModelType dataModelType () const = 0;

    /// <summary>
    /// This abstract method requires derived class to implement it. 
    /// It is intended to expose the pixel type of a datamodel.
    /// </summary>
    ///
    /// <returns>
    /// This returns an entry of the <c>Atil::DataModelAttributes::PixelType</c>
    /// indicating the type of a pixel.
    /// </returns>
    ///
    virtual PixelType pixelType () const = 0;

    /// <summary>
    /// This abstract method requires derived class to implement it. 
    /// It is intended to expose the data type of a datamodel.
    /// </summary>
    ///
    /// <returns>
    /// This returns an entry of the <c>Atil::DataModelAttributes::DataType</c>
    /// indicating the type of data for a pixel.
    /// </returns>
    ///
    virtual DataType dataType () const = 0;

    /// <summary>
    /// This abstract method requires derived class to implement it. 
    /// It is intended to expose the data type of a datamodel.
    /// </summary>
    ///
    /// <returns>
    /// This returns an entry of the <c>Atil::DataModelAttributes::BitFields</c>
    /// indicating the order and width of bits for each channel in a pixel.
    /// </returns>
    ///
    virtual BitFields bitFields () const = 0;

    /// <summary>
    /// Query the order of channels in the pixel.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the order in the <c>DataModelAttributes</c> enum.
    /// </returns>
    ///
    virtual DataModelAttributes::ChannelOrder channelOrder() const = 0;

protected:

    /// <summary>
    /// (Protected) Internalized destructor.
    /// </summary>
    ///
    /// <remarks>
    /// This class is used as a component of the <c>DataModel</c> classes and
    /// not as independently constructible object.
    /// </remarks>
    ///
    virtual ~DataModelAttributes ();

};

namespace RgbModelAttributes 
{
    /// <summary> The number of channels that the color model holds.
    /// </summary>
    enum Channels { 
        /// <summary> Declares three channels of red, green, and blue. </summary>
        k3Channels, 

        /// <summary> Declares three channels of red, green, blue, and alpha. </summary>
        k4Channels 
    };
    /// <summary> This enum gives masks for each bit field in the pixel.</summary>
    /// <remark> This only describes the field layout. The placement of colors in the fields is
    /// determined by the <c>DataModelAttributes::PixelType</c> as either kRgba or kBgra.
    enum Masks {
        /// <summary> Mask for either Red or Blue.</summary>
        kLowMask = 0x001F,
        /// <summary> Mask for Green.<summary>
        kMidMask5551 = 0x03E0,
        /// <summary> Mask for Green.<summary>
        kMidMask565 = 0x07E0,
        /// <summary> Mask for either Blue or Red.</summary>
        kHighMask5551 = 0x7C00,
        /// <summary> Mask for either Blue or Red.</summary>
        kHighMask565= 0xF800,
        /// <summary> Mask for Alpha.<summary>
        kAlphaMask = 0x8000
    };
}

} // end of namespace Atil
#endif
