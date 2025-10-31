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

#ifndef  DATAMODELATTRIBUTES_H
#define  DATAMODELATTRIBUTES_H

namespace Atil
{
/// <summary>
/// An abstract base class that declares attributes of data models and exposes methods
/// that describe those attributes.
/// </summary>
///
/// <remarks>
/// This class, in combination with DataModel and ColorModelInterface, allows developers 
/// to create custom data models that have limited inter-operability with ATIL operations.
/// </remarks>
///
class DataModelAttributes
{
public:
    /// <summary>
    /// This enum defines entries for each of the number of bits per pixel supported by ATIL.
    /// </summary>
    ///
    enum BitsPerPixel { k1, k8, k16, k32, k64 };

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
        /// This entry indicates that the datamodel is an instance of the <c>RgbModel</c> derivation of
        /// DataModel and that the images pixels are of a red, green, blue and possibly alpha
        /// configuration.
        /// </summary>
        ///
        kRgbModel, 

        /// <summary>
        /// This entry indicates that the datamodel is an instance of the <c>RgbPaletteModel</c> derivation
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
        /// This entry indicates that the datamodel is an instance of the <c>RgbGrayModel</c> derivation
        /// of DataModel and that the images pixels are eight bit intensities where 0 is no light and 255
        /// is full light.
        /// </summary>
        ///
        kGrayModel,

        /// <summary>
        /// This entry indicates that the datamodel is an instance of the <c>BitonalModel</c> derivation
        /// of DataModel and that the images pixels are one bit off and on values.
        /// </summary>
        ///
        kBitonalModel
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
        /// This entry indicates that the pixel is only one bit.
        /// </summary>
        ///
        kBitonal,

        /// <summary>
        /// This entry indicates that the pixel is one bit where zero is black and 1 is white.
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
        kRgba
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
        /// The type data stored at each pixel is a float value.
        /// </summary>
        ///
        kFloat
    };

public:
    /// <summary>
    /// This static method will return the bits per pixel for a given PixelType enum entry.
    /// </summary>
    ///
    /// <param name="pixType">
    /// </param>
    ///
    /// <returns>
    /// An entry of the <c>Atil::DataModelAttributes::BitsPerPixel</c> enum indicating the 
    /// number of bits per pixel for each pixel in an image.
    /// </returns>
    ///
    static DataModelAttributes::BitsPerPixel bitsPerPixel (DataModelAttributes::PixelType pixType);

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

} // end of namespace Atil
#endif
