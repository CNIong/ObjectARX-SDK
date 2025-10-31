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
#ifndef IMAGEPIXEL_H
#include "ImagePixel.h"
#endif
#ifndef DATAMODEL_H
#define DATAMODEL_H

namespace Atil
{
/// <summary>
/// This is the base class for all data models in ATIL.
/// A DataModel holds the number of bits per pixel and
/// the number of those bits used within each pixel. 
/// </summary>
///
/// <remarks>
/// The DataModel holds the description of the data in an image. Every
/// image holds an instance DataModel to describe the image pixel 
/// data that resides in the image. 
/// DataModel makes no assumption about the data that is in the image, 
/// it only dictates the size of the pixels. Classes that derive from
/// DataModel extend it to cover the class of data in the datamodel. 
/// </remarks>
///
class DataModel : public DataModelAttributes
{
public:
    /// <summary>
    /// The enum declares the allowable tile sizes within ATIL.
    /// </summary>
    ///
    /// <remarks>
    /// Although each dimension of the tiles are declared, tiles in 
    /// ATIL are always square.
    /// </remarks>
    ///
    enum TileSize {
        /// <summary>
        /// The identifier for a 64 by 64 pixel tile.
        /// </summary>
        ///
        k64x64, 
        /// <summary>
        /// The identifier for a 128 by 128 pixel tile.
        /// </summary>
        ///
        k128x128, 
        /// <summary>
        /// The identifier for a 256 by 256 pixel tile.
        /// </summary>
        ///
        k256x256,
        /// <summary>
        /// The identifier for a 512 by 512 pixel tile.
        /// </summary>
        ///
        k512x512,
        /// <summary>
        /// The identifier for a 1024 by 1024 pixel tile.
        /// </summary>
        ///
        k1024x1024,
        /// <summary>
        /// This enum is a special purpose enum that allows ATIL to choose an
        /// appropriate tile size during construction of an Image.
        /// </summary>
        ///
        kUnspecified,
        /// <summary>
        /// This enum is a special purpose enum that tells ATIL to use the
        /// DataModel default tile size during construction of an Image.
        /// </summary>
        ///
        kDefault 
    };

    /// <summary>
    /// This static method will convert a count of pixels and the bits per pixel of 
    /// those pixels into an 8 byte aligned count of bytes to allocate for a row
    /// of pixel data.
    /// </summary>
    ///
    /// <param name="nPixels">
    /// The number of pixels that will be in the row.
    /// </param>
    ///
    /// <param name="bpp">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the number of bits used in a pixel.
    /// </param>
    /// 
    /// <returns>
    /// The count of bytes to allocate for the row of nPixels pixels.
    /// </returns>
    /// 
    /// <remarks>
    /// This method is useful for calculating the size of a row of pixels expected
    /// by ATIL. ATIL expects all row sizes to be 8 byte aligned.
    /// </remarks>
    ///
    static int bytesPerRow ( Int32 nPixels, DataModelAttributes::BitsPerPixel bpp );

    /// <summary>
    /// This static method will convert the <c>DataModelAttributes</c> enum entry
    /// bpp bits per pixel into an integer count of bits in the pixel.
    /// </summary>
    ///
    /// <param name="bpp">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the number of bits used in a pixel.
    /// </param>
    /// 
    /// <returns>
    /// Returns the number of bits used in a pixel described by bpp.
    /// </returns>
    ///
    static int bitsPerPixel ( DataModelAttributes::BitsPerPixel bpp );

    /// <summary>
    /// This static method will convert the <c>TileSize</c> enum entry into
    /// integer counts of pixels per column and pixels per row of a tile.
    /// </summary>
    /// 
    /// <param name="size">
    /// An enum constant describing the size of an ATIL tile.
    /// </param>
    ///
    /// <param name="nRows">
    /// A reference to an integer into which the number of rows of a tile
    /// will be stored.
    /// </param>
    ///
    /// <param name="nColumns">
    /// A reference to an integer into which the number of columns of a tile
    /// will be stored.
    /// </param>
    ///
    static void tileSize ( TileSize size, int& nRows, int& nColumns );

public:
    /// <summary>
    /// Constructor for a DataModel.
    /// </summary>
    ///
    /// <param name="format">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the format of a pixel.
    /// </param>
    ///
    /// <param name="bpp">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the number of bits used in a pixel.
    /// </param>
    ///
    /// <param name="dataBits">
    /// The number of bits used for a pixel. The number of bits used must be 
    /// less than or equal to the number of bits per pixel as declared in bpp.
    /// </param>
    ///
    /// <remarks>
    /// This method is a specialized constructor that is used to construct
    /// sub-class models that specialize the data type and provide appropriate
    /// conversion filters to the standard types. If you are not developing a
    /// custom-derivation of the DataModel to provide support for conversion
    /// from non-supported data types, then this is not the class you are 
    /// looking for.
    /// </remarks>
    ///
    DataModel (DataModelAttributes::DataType format,
        DataModelAttributes::BitsPerPixel bpp, int dataBits);

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~DataModel ();

    /// <summary>
    /// This method creates a full copy of the datamodel.
    /// </summary>
    ///
    /// <returns>     
    /// This returns a new <c>DataModel</c> as a copy of <c>*this</c>. 
    /// </returns>
    ///
    virtual DataModel* clone () const;

    /// <summary>
    /// Queries the default tile size of the data described by this datamodel.
    /// </summary>
    /// 
    /// <returns>
    /// The size of the tile encoded as an entry of the TileSize enum.
    /// </returns>
    ///
    virtual DataModel::TileSize defaultTileSize () const;

    /// <summary>
    /// Test a TileSize for compatibility with the data represented by the datamodel.
    /// </summary>
    ///
    /// <param name="size">
    /// An entry of the TileSize enum indicating a tile size.
    /// </param>
    ///
    /// <returns>
    /// This method returns true if the input <c>TileSize</c> is supported.
    /// </returns>
    ///
    virtual bool isCompatibleTileSize (DataModel::TileSize size) const;

    /// <summary>
    /// Test for compatibility of a data type with the data represented by the datamodel.
    /// </summary>
    ///
    /// <param name="dataSize">
    /// An entry of the BitsPerPixel indicating the desired bits per pixel to test.
    /// </param>
    ///
    /// <returns>
    /// This method returns true if the input <c>BitsPerPixel</c> is supported.
    /// </returns>
    ///
    /// <remarks>
    /// This test can be used to determine if the data of one image is size compatible
    /// with a different image. This does not determine if the type of the data is the
    /// same or compatible, it only checks the bit size of the pixels in the image.
    /// </remarks>
    ///
    virtual bool isCompatibleDataSize ( DataModelAttributes::BitsPerPixel dataSize ) const;

    /// <summary>
    /// Query for the number of bits per pixel of the data represented by the datamodel.
    /// </summary>
    /// 
    /// <returns>
    /// An entry of the BitsPerPixel indicating the bits per pixel of the data 
    /// represented by the datamodel.
    /// </returns>
    ///
    virtual DataModelAttributes::BitsPerPixel bitsPerPixel () const;

    /// <summary>
    /// Returns the number of bits that are valid within the <c>BitsPerPixel</c>.
    /// </summary>
    ///
    /// <returns>
    /// This returns the integer number of bits used to represent the pixel values in each pixel.
    /// </returns>
    ///
    /// <remarks>
    /// The bit packing size in ATIL is 8. This means that a 4 bit per pixel image
    /// will be stored using 8 bits for each pixel. This method will return the 4
    /// bits per pixel of the data as the true bits of valid data within each pixel.
    /// </remarks>
    ///
    virtual int bitsUsedPerPixel () const;

    /// <summary>
    /// This query returns an entry of the DataModelType enum that indicates
    /// which of the ATIL defined color type DataModel derived types this
    /// data model is.
    /// </summary>
    ///
    /// <returns>
    /// An entry of the DataModelType enum that indicates the derived DataModel.
    /// </returns>
    ///
    /// <remarks>
    /// In addition to defining RTTI to identify classes and their derivatives
    /// ATIL exposes this enum to help in identifying the DataModel derivatives that
    /// ATIL defines. The current ATIL defined datamodels are based on RgbModel 
    /// which defines a color space based on the R,G,B color cube.
    /// </remarks>
    ///
    virtual DataModelAttributes::DataModelType dataModelType () const;

    /// <summary>
    /// Query the pixel type of the data represented by this datamodel.
    /// </summary>
    ///
    /// <returns>
    /// This method returns an entry of the PixelType enum declaring the 
    /// type of the data in the image.
    /// </returns>
    ///
    /// <remarks>
    /// Similar this is to the DataModelType. This enum encodes the type
    /// of pixel and is used to label data as coming from or belonging to
    /// a given color model such as data, rgb, gray intensity, etc.
    /// </remarks>
    ///
    virtual DataModelAttributes::PixelType pixelType () const;

    /// <summary>
    /// Query for the type of the data i.e. signed/unsigned, float/integeral.
    /// </summary>
    /// 
    /// <returns>
    /// An entry of the DataType enum indicating the type of data in the image 
    /// represented by this datamodel.
    /// </returns>
    ///
    /// <remarks>
    /// This query can help to characterize images that do not have a color model 
    /// based DataModel derivation (RgbModel). This is also important for the <c>RgbModel5b</c>
    /// which can have multiple layouts of bits within each sample.
    /// </remarks>
    ///
    virtual DataModelAttributes::DataType dataType () const;

    /// <summary>
    /// Query for the layout of channel data within each sample. 
    /// </summary>
    /// 
    /// <returns>
    /// Returns the fields widths for channels within the pixel.
    /// </returns>
    ///
    /// <remarks>
    /// Some image formats use bit fields to describe multiple channels within each sample.
    /// </remarks>
    ///
    virtual DataModelAttributes::BitFields bitFields () const;

    /// <summary>
    /// Query the order of channels in the pixel.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the order in the <c>DataModelAttributes</c> enum.
    /// </returns>
    ///
    virtual DataModelAttributes::ChannelOrder channelOrder() const;

    /// <summary>
    /// The equals operator.
    /// </summary>
    ///
    /// <param name= 'dm'>
    /// A const reference to the <c>DataModel</c> to be tested.
    /// </param>
    ///
    /// <returns>
    /// This method returns true if two DataModel objects are equivalent.
    /// </returns>
    ///
    /// <remarks>
    /// Each internal ATIL derived <c>DataModel</c> will implement its own operators to 
    /// implement the correct and meaningful comparison.
    /// </remarks>
    ///
    virtual bool operator==(const DataModel& dm) const;

    /// <summary>
    /// The not equals operator.
    /// </summary>
    ///
    /// <param name= 'dm'>
    /// A const reference to the <c>DataModel</c> to be tested.
    /// </param>
    ///
    /// <returns>
    /// This method returns true if two DataModel objects are not equivalent.
    /// </returns>
    ///
    /// <remarks>
    /// Each internal ATIL derived <c>DataModel</c> will implement its own operators to 
    /// implement the correct and meaningful comparison.
    /// </remarks>
    ///
    virtual bool operator!=(const DataModel& dm) const;

protected:
    /// <summary>
    /// A protected initializing constructor for the use of deriving classes.
    /// </summary>
    ///
    /// <param name="dmt">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the type of the datamodel to be constructed.
    /// </param>
    ///
    /// <param name="format">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the format of a pixel.
    /// </param>
    ///
    /// <param name="bpp">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the number of bits used in a pixel.
    /// </param>
    ///
    /// <remarks>
    /// The number of bits used is assumed to be equal to the number of bits 
    /// specified by the <c>DataModelAttributes::BitsPerPixel</c> entry.
    /// </remarks>
    ///
    DataModel (DataModelAttributes::DataModelType dmt, DataModelAttributes::DataType format,
        DataModelAttributes::BitsPerPixel bpp );

    /// <summary>
    /// A protected initializing constructor for the use of deriving classes.
    /// </summary>
    ///
    /// <param name="dmt">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the type of the datamodel to be constructed.
    /// </param>
    ///
    /// <param name="format">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the format of a pixel.
    /// </param>
    ///
    /// <param name="bpp">
    /// A constant enum described in <c>DataModelAttributes</c> that declares
    /// the number of bits used in a pixel.
    /// </param>
    ///
    /// <param name="dataBits">
    /// The number of bits used for a pixel. The number of bits used must be 
    /// less than or equal to the number of bits per pixel as declared in bpp.
    /// </param>
    ///
    DataModel (DataModelAttributes::DataModelType dmt, DataModelAttributes::DataType format,
        DataModelAttributes::BitsPerPixel bpp, int dataBits);

    /// <summary> 
    /// Unimplemented copy constructor. The compiler may allow this to be used
    /// but it will not work and it will cause errors if you attempt to construct
    /// a <c>DataModel</c> through assignment.
    /// </summary>
    ///
    /// <param name="rhs">
    /// The datamodel to take values from.
    /// </param>
    ///
    /// <returns>
    /// This method returns a reference of *this.
    /// </returns>
    ///
    DataModel& operator=(const DataModel& rhs); 

    /// <summary> 
    /// The <c>DataModel</c> class can not be directly constructed. It is 
    /// used as a base class only.
    /// </summary>
    ///
    DataModel (); 

    /// <summary> 
    /// The (Protected) <c>DataModelAttributes::DataModelType</c> of the data model.
    /// </summary>
    ///
    DataModelAttributes::DataModelType mDMType;

    /// <summary> 
    /// The (Protected) <c>DataModelAttributes::BitsPerPixel</c> of the data model.
    /// </summary>
    ///
    DataModelAttributes::BitsPerPixel mPackedBits;

    /// <summary> 
    /// The (Protected) <c>DataModelAttributes::DataType</c> of the data model.
    /// </summary>
    ///
    DataModelAttributes::DataType mDataType;

    /// <summary>
    ///  The number of bits declared in <c>mPackedBits</c>.
    /// </summary>
    ///
    int mnBitsPerPixel;

    /// <summary>
    ///  The number of bits used in the pixel always equal to or less than those declared in <c>mPackedBits</c>.
    /// </summary>
    ///
    int mnDataBits;

    /// <summary>
    /// The default tile size for images that use this datamodel.
    /// </summary>
    ///
    TileSize mDefaultTileSize;
};

} // end of namespace Atil
#endif
