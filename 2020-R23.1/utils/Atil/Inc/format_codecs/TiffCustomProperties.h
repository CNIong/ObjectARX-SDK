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

#ifndef FORMATCODECPROPERTYINTERFACE_H
#include <FormatCodecPropertyInterface.h>
#endif
#ifndef FORMATCODECPROPERTYSETITERATOR_H
#include <FormatCodecPropertySetIterator.h>
#endif
#ifndef FORMATCODECSTRINGPROPERTY_H
#include <FormatCodecStringProperty.h>
#endif
#ifndef FORMATCODECDENSITY_H
#include <FormatCodecDensity.h>
#endif
#ifndef FORMATCODECASSOCIATION_H
#include <FormatCodecAssociation.h>
#endif
#ifndef STRINGBUFFER_H
#include <StringBuffer.h>
#endif
#ifndef FORMATCODECEXCLUSIVEPROPERTYSETINTERFACE_H
#include <FormatCodecExclusivePropertySetInterface.h>
#endif
#ifndef FORMATCODECTRANSPARENCY_H
#include <FormatCodecTransparency.h>
#endif
#ifndef TIFFFORMATCODEC_H
#include <TiffFormatCodec.h>
#endif

#ifndef TIFFCUSTOMPROPERTIES_H
#define TIFFCUSTOMPROPERTIES_H

struct tiff;

/// <summary>
/// This class serves as the base class for all non-ATIL TIFF Format codec
/// specific properties.
/// </summary>
///
class TiffProperty 
{
public:
    /// <summary>
    /// The virtual destructor and simple inline implementation.
    /// </summary>
    ///
    virtual ~TiffProperty () {}; // TODO: remove inline implementation

    /// <summary>
    /// This method returns the <c>TiffFormatCodec::TiffId</c> of the property class.
    /// </summary>
    ///
    /// <returns>A definition from the <c>TiffFormatCodec::TiffId</c>
    /// that indicates the property.
    /// </returns>
    ///
    virtual TiffFormatCodec::TiffId getTiffId () const { return mTiffId; }

protected:
    /// <summary>
    /// (Protected) The id of the property.
    /// </summary>  
    ///
    TiffFormatCodec::TiffId	mTiffId;

public:
    /// <summary>
    /// (Private) This method is not meant for use by applications.
    /// </summary>
    ///
    /// <param name="pTIFF">
    /// Internally used.
    /// </param>
    ///
    /// <returns>
    /// Internally used.
    /// </returns>
    ///
    virtual bool write( struct tiff* pTIFF ) const = 0;
};

/// <summary>
/// This class is the TIFF compression type. Through it an application can
/// query the configuration of an existing file and set the configuration of a file
/// to be written.
/// </summary>
///
class TiffCompressionType : public Atil::FormatCodecPropertyInterface, public TiffProperty
{
public:
    /// <summary>
    /// This enum describes the different models of compression that are
    /// available within the TIFF format depending on the image data.
    /// </summary>
    ///
    enum Compression { 
        /// <summary>
        /// This indicates that the data is not compressed.
        /// </summary>
        kNone = 0, 

        /// <summary>
        /// This indicates a Run Length Encoding scheme that is commonly used for
        /// indexed, grayscale, or bitonal images.
        /// </summary>
        kCCITT_RLE, 

        /// <summary>
        /// This indicates a Run Length Encoding scheme that is commonly used for
        /// indexed, grayscale, or bitonal images.
        /// </summary>
        kCCITT_RLEW, 

        /// <summary>
        /// This indicates a CCITT 1 dimensional fax transmission format used
        /// only with bitonal images.
        /// </summary>
        kCCITT_FAX3, 

        /// <summary>
        /// This indicates a CCITT 2 dimensional fax transmission format used
        /// only with bitonal images. This encoding is likely to offer the best compression
        /// with no loss of data.
        /// </summary>
        kCCITT_FAX4,

        /// <summary>
        /// The LZW compression scheme is patented by UniSYS. That patent has expired making
        /// LZW available as a good lossless compression for bitonal, indexed, and gray-scale imagery.
        /// </summary>
        kLZW, 

        /// <summary>
        /// This is a different run length compression scheme for paletted and gray-scale imagery.
        /// </summary>
        kPackbits, 

        /// <summary>
        /// This is the JPEG DCT based lossy compression for gray-scale and r,g,b images.
        /// </summary>
        kJPEG, 

        /// <summary>
        /// This compression mode is based on the LZ compression variant implemented in zLib.
        /// </summary>
        kDeflate 
    };
public:
    /// <summary>
    /// The constructor.
    /// </summary>
    /// 
    /// <param name="type">A definition from the <c>Compression</c> enum
    /// that indicates the compression method.
    /// </param>
    ///
    TiffCompressionType ( Compression type );

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    ~TiffCompressionType ( );

    /// <summary>
    /// This method is an artificial copy constructor. All properties
    /// that are not trivial (no additional methods or data) derivations or 
    /// instances of ATIL defined property classes should implement this method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecPropertyInterface</c> instance.
    /// </returns>
    ///
    virtual Atil::FormatCodecPropertyInterface* clone () const;
    
    /// <summary>
    /// This method will return the <c>Compression</c> model.
    /// </summary>
    ///
    /// <returns>
    /// The <c>Compression</c> model represented by the class instance.
    /// </returns>
    ///
    Compression type ();

    /// <summary>
    /// (Private) This method is not meant for use by applications.
    /// </summary>
    ///
    /// <param name="pTIFF">
    /// Internally used.
    /// </param>
    ///
    /// <returns>
    /// Internally used.
    /// </returns>
    ///
    bool write ( struct tiff* pTIFF ) const;
private:
    Compression mCompressionType;
};

class TiffCompression : public Atil::FormatCodecExclusivePropertySetInterface, public TiffProperty
{
public:
    /// <summary>
    /// This class is a set of compression types where only one compression model may be 
    /// selected.
    /// </summary>
    ///
    /// <param name="nBitsPerPixel"> The number of bits in a pixel of the image.
    /// </param>
    ///
    /// <param name="usPhotometric"> The color type of the image to be compressed.
    /// </param>
    ///
    /// <param name="usSamplesPerPixel"> The number of samples (r,g,b is three) in the image.
    /// </param>
    ///
    /// <param name="selected"> The <c>TiffCompressionType::Compression</c> to be marked as the 
    /// selected compression scheme.
    /// </param>
    ///
    /// <param name="bWriting"> This will be true if the property is created in response to a 
    /// image file write request.
    /// </param>
    ///
    /// <param name="bPatentedEncoding"> This enables and disables LZW encoding.
    /// </param>
    ///
    TiffCompression (int nBitsPerPixel, unsigned short usPhotometric, unsigned short usSamplesPerPixel
        , TiffCompressionType::Compression selected = TiffCompressionType::kNone
        , bool bWriting = false, bool bPatentedEncoding = false );

    /// <summary>
    /// The destructor.
    /// </summary>
    ///
    ~TiffCompression ();

    /// <summary>
    /// This method is an artificial copy constructor. All properties
    /// that are not trivial (no additional methods or data) derivations or 
    /// instances of ATIL defined property classes should implement this method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecPropertyInterface</c> instance.
    /// </returns>
    ///
    virtual Atil::FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// This queries the <c>Compression</c> type at a specific index in the set of compression types.
    /// </summary>
    ///
    /// <param name="nIndex"> The index to of the compression to return.
    /// </param>
    ///
    /// <returns>
    /// The <c>Compression</c> model represented by the instance at the index.
    /// </returns>
    ///
    TiffCompressionType::Compression getCompressionType (int nIndex) const;

    /// <summary>
    /// This method will select a property in the set by through the <c>Compression</c> id.
    /// </summary>
    /// 
    /// <param name="use"> The <c>Compression</c> id to select.
    /// </param>
    ///
    /// <returns>
    /// This will return true on success.
    /// </returns>
    ///
    bool selectCompression (TiffCompressionType::Compression use);

    /// <summary>
    /// (Private) This method is not meant for use by applications.
    /// </summary>
    ///
    /// <param name="pTIFF">
    /// Internal use only.
    /// </param>
    ///
    /// <returns>
    /// Internal use only.
    /// </returns>
    ///
    bool write ( struct tiff* pTIFF ) const;
};

/// <summary>
/// This describes the encoding of data in monochromatic images (bitonal and gray-scale). These
/// images are described in an abstract intensity level that can be interpreted as increasing or decreasing.
/// </summary>
///
class TiffPhotometricInterpretation : public Atil::FormatCodecExclusivePropertySetInterface, public TiffProperty
{
public:
    /// <summary>
    /// This enum describes the methods of that data can be interpreted.
    /// </summary>
    enum Interpretation { 
        /// <summary>
        /// The minimum numeric value is considered to be 'white'.
        /// </summary>
        kMinIsWhite,

        /// <summary>
        /// The minimum numeric value is considered to be 'black'.
        /// </summary>
        kMinIsBlack
    };

public:

    /// <summary>
    /// The constructor.
    /// </summary>
    ///
    /// <param name="interp"> The <c>Interpretation</c> description to select.
    /// </param>
    ///
    TiffPhotometricInterpretation ( 
        TiffPhotometricInterpretation::Interpretation interp =
        TiffPhotometricInterpretation::kMinIsWhite );

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    ~TiffPhotometricInterpretation ();

    /// <summary>
    /// This method is an artificial copy constructor. All properties
    /// that are not trivial (no additional methods or data) derivations or 
    /// instances of ATIL defined property classes should implement this method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecPropertyInterface</c> instance.
    /// </returns>
    ///
    virtual Atil::FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// This queries the <c>Interpretation</c> of the data.
    /// </summary>
    ///
    /// <returns>
    /// The <c>Interpretation</c> model represented by the instance.
    /// </returns>
    ///
    Interpretation photometricInterpretation () const;

    /// <summary>
    /// (Private) This method is not meant for use by applications.
    /// </summary>
    ///
    /// <param name="pTIFF">
    /// Internal use only.
    /// </param>
    ///
    /// <returns>
    /// Internal use only.
    /// </returns>
    ///
    bool write ( struct tiff* pTIFF ) const;
};

/// <summary>
/// The TIFF format can use two bit orderings, Least Significant to Most Significant or 
/// Most Significant to Least Significant. This properties indicates which is used.
/// </summary>
///
class TiffFillOrder : public Atil::FormatCodecExclusivePropertySetInterface, public TiffProperty
{
public:

    /// <summary>
    /// This enum describes the bit ordering of the data.
    /// </summary>
    enum Order {
        /// <summary>
        /// Most Significant to Least Significant
        /// </summary>
        kMSBtoLSB, 
        /// <summary>
        /// Least Significant to Most Significant
        /// </summary>
        kLSBtoMSB
    };

public:

    /// <summary>
    /// The constructor.
    /// </summary>
    ///
    /// <param name="order"> The <c>TiffFillOrder::Order</c> description to select.
    /// </param>
    ///
    TiffFillOrder ( TiffFillOrder::Order order = TiffFillOrder::kMSBtoLSB );

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    ~TiffFillOrder ();

    /// <summary>
    /// This method is an artificial copy constructor. All properties
    /// that are not trivial (no additional methods or data) derivations or 
    /// instances of ATIL defined property classes should implement this method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecPropertyInterface</c> instance.
    /// </returns>
    ///
    virtual Atil::FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// This queries the bit order of the data in the image.
    /// </summary>
    ///
    /// <returns> The <c>TiffFillOrder::Order</c> description that is selected.
    /// </returns>
    ///
    Order fillOrder () const;

    /// <summary>
    /// (Private) This method is not meant for use by applications.
    /// </summary>
    ///
    /// <param name="pTIFF">
    /// Internal use only.
    /// </param>
    ///
    /// <returns>
    /// Internal use only.
    /// </returns>
    ///
    bool write ( struct tiff* pTIFF ) const;

private:
    Order mOrder;
};

/// <summary>
/// This property returns the TIFF property which states "For grayscale data, the optical
/// density of each possible pixel value."
/// </summary>
class TiffGrayResponseCurve : public Atil::FormatCodecPropertyInterface, public TiffProperty
{
public:
    /// <summary>
    /// The constructor.
    /// </summary>
    ///
    TiffGrayResponseCurve ( );

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~TiffGrayResponseCurve ();

    /// <summary>
    /// This method is an artificial copy constructor. All properties
    /// that are not trivial (no additional methods or data) derivations or 
    /// instances of ATIL defined property classes should implement this method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecPropertyInterface</c> instance.
    /// </returns>
    ///
    virtual Atil::FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// This queries the number of levels.
    /// </summary>
    ///
    /// <returns>
    /// This returns the number of levels as an integer.
    /// </returns>
    ///
    virtual int responseLevels () const;

    /// <summary>
    /// This queries the levels as an array if floating point values.
    /// </summary>
    ///
    /// <param name="pValues"> The <c>TiffFillOrder::Order</c> description to select.
    /// </param>
    ///
    virtual void getResponseLevels ( float* pValues ) const;

    /// <summary>
    /// This will allow applications to store grayscale response levels.
    /// </summary>
    /// 
    /// <param name="nLevels"> The number of values in the array of levels. 
    /// </param>
    ///
    /// <param name="pValues"> An array of unsigned short values.
    /// </param>
    ///
    /// <param name="nTenthDivisor"> The divisor to convert the short values to floating point.
    /// </param>
    ///
    virtual void setResponseLevels ( int nLevels, unsigned short* pValues, int nTenthDivisor );   

    /// <summary>
    /// This will return the set tenth divisor.
    /// </summary>
    /// 
    /// <returns>
    /// This returns the divisor that has been set into the property.
    /// </returns>
    ///
    virtual unsigned short tenthDivisor () const;

    /// <summary>
    /// This will return the unscaled short data.
    /// </summary>
    /// 
    /// <returns>
    /// This returns a pointer to an unsigned short array that should be treated as const.
    /// </returns>
    ///
    virtual unsigned short* unscaledData () const;

    /// <summary>
    /// (Private) This method is not meant for use by applications.
    /// </summary>
    ///
    /// <param name="pTIFF">
    /// Internal use only.
    /// </param>
    ///
    /// <returns>
    /// Internal use only.
    /// </returns>
    ///
    bool write ( struct tiff* pTIFF ) const;
private:
    unsigned short* mpScaledLevels;
    int mnLevels;
    int mnTenthScaler;
};

/// <summary>
/// This property returns strings that can be embeded in TIFF files.
/// </summary>
///
class TiffText : public Atil::FormatCodecStringProperty, public TiffProperty
{
public:
    /// <summary>
    /// The constructor.
    /// </summary>
    ///
    /// <param name="tiffId"> The tag id of the string in TIFF that the property will hold.
    /// </param>
    ///
    TiffText (TiffFormatCodec::TiffId tiffId);

    /// <summary>
    /// The initializing constructor.
    /// </summary>
    ///
    /// <param name="tiffId"> The tag id of the string in TIFF that the property will hold.
    /// </param>
    ///
    /// <param name="psbText"> A pointer to a <c>StringBuffer</c> that holds the ASCII string.
    /// </param>
    ///
    TiffText (TiffFormatCodec::TiffId tiffId, Atil::StringBuffer* psbText);

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    ~TiffText ();

    /// <summary>
    /// This method is an artificial copy constructor. All properties
    /// that are not trivial (no additional methods or data) derivations or 
    /// instances of ATIL defined property classes should implement this method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecPropertyInterface</c> instance.
    /// </returns>
    ///
    virtual Atil::FormatCodecPropertyInterface* clone () const;
   
    /// <summary>
    /// This method can be used to set the string into the property.
    /// </summary>
    ///
    /// <param name="sbValue"> A constant pointer to a <c>StringBuffer</c> that 
    /// holds the ASCII string to be stored.
    /// </param>
    ///
    /// <returns>
    /// This method returns true on success.
    /// </returns>
    ///
    bool setValue (const Atil::StringBuffer& sbValue);

    /// <summary>
    /// (Private) This method is not meant for use by applications.
    /// </summary>
    ///
    /// <param name="pTIFF">
    /// Internal use only.
    /// </param>
    ///
    /// <returns>
    /// Internal use only.
    /// </returns>
    ///
    bool write ( struct tiff* pTIFF ) const;
};

/// <summary>
/// The TIFF format can be extended with non-standard tag ids that are declared 
/// or allocated to companies for their applications. This property allows
/// those tags to be requested.
/// </summary>
///
class TiffPrivateTag : public Atil::FormatCodecPropertyInterface, public TiffProperty
{
public:
    /// <summary>
    /// This enum describes the forms of data that may reside in a TIFF file.
    /// </summary>
    enum TiffDataType 
    {
          /// <summary> This is an invalid entry.</summary>
          kUnknown	
          /// <summary> This is a byte (8 bit) entry.</summary>
        , kByte
          /// <summary> This is an ASCII string entry.</summary>
        , kAscii
          /// <summary> This is a short (16 bit) entry.</summary>
        , kShort
          /// <summary> This is a long (32 bit) entry.</summary>
        , kLong
          /// <summary> This is a floating point entry.</summary>
        , kRational
          /// <summary> This is a signed byte (8 bit) entry.</summary>
        , kSignedByte
          /// <summary> This is an undefined entry.</summary>
        , kUndefined
          /// <summary> This is a signed short (16 bit) entry.</summary>
        , kSignedShort
          /// <summary> This is a signed long (32 bit) entry.</summary>
        , kSignedLong
          /// <summary> This is a signed floating point entry.</summary>
        , kSignedRational
          /// <summary> This is a floating point entry.</summary>
        , kFloat
          /// <summary> This is a double floating point entry.</summary>
        , kDouble
    };

    /// <summary> Typedef the TIFF data type of byte.</summary>
    typedef unsigned char TTiffByte;
    /// <summary> Typedef the TIFF data type of ASCII.</summary>
    typedef unsigned char TTiffAscii;
    /// <summary> Typedef the TIFF data type of short.</summary>
    typedef unsigned short TTiffShort;
    /// <summary> Typedef the TIFF data type of long.</summary>
    typedef unsigned int TTiffLong;
    /// <summary> Typedef the TIFF data type of Rational.</summary>
    typedef float TTiffRational;
    /// <summary> Typedef the TIFF data type of signed byte.</summary>
    typedef char TTiffSignedByte;
    /// <summary> Typedef the TIFF data type of undefined.</summary>
    typedef unsigned char TTiffUndefined;
    /// <summary> Typedef the TIFF data type of signed short.</summary>
    typedef short TTiffSignedShort;
    /// <summary> Typedef the TIFF data type of signed long.</summary>
    typedef int TTiffSignedLong;
    /// <summary> Typedef the TIFF data type of signed Rational.</summary>
    typedef float TTiffSignedRational;
    /// <summary> Typedef the TIFF data type of float.</summary>
    typedef float TTiffFloat;
    /// <summary> Typedef the TIFF data type of double.</summary>
    typedef double TTiffDouble;

public:
    /// <summary>
    /// The constructor.
    /// </summary>
    ///
    /// <param name="tagId"> The tag id of the private data in TIFF that the property will hold.
    /// </param>
    ///
    /// <param name="dataType"> The data type of the data to be held.
    /// </param>
    ///
    TiffPrivateTag(unsigned short tagId, TiffDataType dataType);

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual	~TiffPrivateTag();

    /// <summary>
    /// This method is an artificial copy constructor. All properties
    /// that are not trivial (no additional methods or data) derivations or 
    /// instances of ATIL defined property classes should implement this method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecPropertyInterface</c> instance.
    /// </returns>
    ///
    virtual Atil::FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// (Private) This method is not meant for use by applications.
    /// </summary>
    ///
    /// <param name="pTIFF">
    /// Internal use only.
    /// </param>
    ///
    /// <returns>
    /// Internal use only.
    /// </returns>
    ///
    virtual bool write(struct tiff* pTiff) const;

    /// <summary>
    /// This will check the validity of the private tag state.
    /// </summary>
    ///
    /// <returns>
    /// The return will be true if the data is valid.
    /// </returns>
    ///
    bool isValid() const;

    /// <summary>
    /// This queries the type of the data held by the property.
    /// </summary>
    ///
    /// <returns>
    /// This returns a description entry from the <c>TiffDataType</c> enum.
    /// </returns>
    ///
    TiffDataType dataType() const;

    /// <summary>
    /// This queries the id of the TIFF tag held by the property.
    /// </summary>
    ///
    /// <returns>
    /// This returns an unsigned short which is the TIFF tag id.
    /// </returns>
    ///
    unsigned short tagId() const;

    /// <summary>
    /// This queries the number of items for type <c>TIiffDataType</c> are held by the property.
    /// </summary>
    ///
    /// <returns>
    /// This returns the number of items as an unsigned long.
    /// </returns>
    ///
    unsigned int numItems() const;

    /// <summary>
    /// This queries the number of bytes of memory needed to hold the items,
    /// </summary>
    ///
    /// <returns>
    /// This returns the number of bytes required as an unsigned long.
    /// </returns>
    ///
    unsigned int numDataBytes() const;


    /// <summary>
    /// This will return the tag data.
    /// </summary>
    /// 
    /// <param name="pData"> A <c>TTiffByte</c> array to receive to the held data.
    /// </param>
    ///
    /// <param name="nItems"> The number of items that the array can hold or to retrieve.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool getValue(TTiffByte* pData, const unsigned int nItems);

    /// <summary>
    /// This will set the tag data for writing into the property.
    /// </summary>
    /// 
    /// <param name="pData"> A const <c>TTiffByte</c> array with the data to be set.
    /// </param>
    ///
    /// <param name="nItems"> The number of items to set.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool setValue(TTiffByte const* pData, const unsigned int nItems);

    /// <summary>
    /// This will return the tag data.
    /// </summary>
    /// 
    /// <param name="pData"> A <c>TTiffShort</c> array to receive to the held data.
    /// </param>
    ///
    /// <param name="nItems"> The number of items that the array can hold or to retrieve.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool getValue(TTiffShort* pData, const unsigned int nItems);

    /// <summary>
    /// This will set the tag data for writing into the property.
    /// </summary>
    /// 
    /// <param name="pData"> A const <c>TTiffShort</c> array with the data to be set.
    /// </param>
    ///
    /// <param name="nItems"> The number of items to set.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool setValue(TTiffShort const* pData, const unsigned int nItems);

    /// <summary>
    /// This will return the tag data.
    /// </summary>
    /// 
    /// <param name="pData"> A <c>TTiffLong</c> array to receive to the held data.
    /// </param>
    ///
    /// <param name="nItems"> The number of items that the array can hold or to retrieve.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool getValue(TTiffLong* pData, const unsigned int nItems);

    /// <summary>
    /// This will set the tag data for writing into the property.
    /// </summary>
    /// 
    /// <param name="pData"> A const <c>TTiffLong</c> array with the data to be set.
    /// </param>
    ///
    /// <param name="nItems"> The number of items to set.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool setValue(TTiffLong const* pData, const unsigned int nItems);

    /// <summary>
    /// This will return the tag data.
    /// </summary>
    /// 
    /// <param name="pData"> A <c>TTiffSignedByte</c> array to receive to the held data.
    /// </param>
    ///
    /// <param name="nItems"> The number of items that the array can hold or to retrieve.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool getValue(TTiffSignedByte* pData, const unsigned int nItems);

    /// <summary>
    /// This will set the tag data for writing into the property.
    /// </summary>
    /// 
    /// <param name="pData"> A const <c>TTiffSignedByte</c> array with the data to be set.
    /// </param>
    ///
    /// <param name="nItems"> The number of items to set.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool setValue(TTiffSignedByte const* pData, const unsigned int nItems);

    /// <summary>
    /// This will return the tag data.
    /// </summary>
    /// 
    /// <param name="pData"> A <c>TTiffSignedShort</c> array to receive to the held data.
    /// </param>
    ///
    /// <param name="nItems"> The number of items that the array can hold or to retrieve.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool getValue(TTiffSignedShort* pData, const unsigned int nItems);

    /// <summary>
    /// This will set the tag data for writing into the property.
    /// </summary>
    /// 
    /// <param name="pData"> A const <c>TTiffSignedShort</c> array with the data to be set.
    /// </param>
    ///
    /// <param name="nItems"> The number of items to set.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool setValue(TTiffSignedShort const* pData, const unsigned int nItems);

    /// <summary>
    /// This will return the tag data.
    /// </summary>
    /// 
    /// <param name="pData"> A <c>TTiffSignedLong</c> array to receive to the held data.
    /// </param>
    ///
    /// <param name="nItems"> The number of items that the array can hold or to retrieve.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool getValue(TTiffSignedLong* pData, const unsigned int nItems);

    /// <summary>
    /// This will set the tag data for writing into the property.
    /// </summary>
    /// 
    /// <param name="pData"> A const <c>TTiffSignedLong</c> array with the data to be set.
    /// </param>
    ///
    /// <param name="nItems"> The number of items to set.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool setValue(TTiffSignedLong const* pData, const unsigned int nItems);

    /// <summary>
    /// This will return the tag data.
    /// </summary>
    /// 
    /// <param name="pData"> A <c>TTiffFloat</c> array to receive to the held data.
    /// </param>
    ///
    /// <param name="nItems"> The number of items that the array can hold or to retrieve.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool getValue(TTiffFloat* pData, const unsigned int nItems);

    /// <summary>
    /// This will set the tag data for writing into the property.
    /// </summary>
    /// 
    /// <param name="pData"> A const <c>TTiffFloat</c> array with the data to be set.
    /// </param>
    ///
    /// <param name="nItems"> The number of items to set.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool setValue(TTiffFloat const* pData, const unsigned int nItems);

    /// <summary>
    /// This will return the tag data.
    /// </summary>
    /// 
    /// <param name="pData"> A <c>TTiffDouble</c> array to receive to the held data.
    /// </param>
    ///
    /// <param name="nItems"> The number of items that the array can hold or to retrieve.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool getValue(TTiffDouble* pData, const unsigned int nItems);

    /// <summary>
    /// This will set the tag data for writing into the property.
    /// </summary>
    /// 
    /// <param name="pData"> A const <c>TTiffDouble</c> array with the data to be set.
    /// </param>
    ///
    /// <param name="nItems"> The number of items to set.
    /// </param>
    ///
    /// <returns>
    /// The method returns true on a valid request.
    /// </returns>
    ///
    bool setValue(TTiffDouble const* pData, const unsigned int nItems);


private:
    bool storeValue(void const * pData, const unsigned int numBytes);
    bool retrieveValue(void* pData, const unsigned int numBytes);

    TiffDataType mDataType;
    unsigned int mNumItems;
    void* mpTagValue;
    unsigned short mTagId;
    bool mbValid;
};

/// <summary>
/// This class returns the numeric range of the data in the image if that information
/// is present in the TIFF file.
/// </summary>
///
/// <remarks>
/// The range placed for applications about the numeric range of the data is not
/// always accurate. So this tag data should not be considered reliable.
/// </remarks>
///
class TiffSampleRange : public Atil::FormatCodecInclusivePropertySetInterface, public TiffProperty
{
public:

    /// <summary>
    /// The constructor.
    /// </summary>
    ///
    TiffSampleRange ();

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~TiffSampleRange ();

    /// <summary>
    /// This method is an artificial copy constructor. All properties
    /// that are not trivial (no additional methods or data) derivations or 
    /// instances of ATIL defined property classes should implement this method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecPropertyInterface</c> instance.
    /// </returns>
    ///
    virtual Atil::FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// This will return the range for the image data.
    /// </summary>
    ///
    /// <param name="nMinValue"> An unsigned short reference to be set to the minimum value.
    /// </param>
    ///
    /// <param name="nMaxValue"> An unsigned short reference to be set to the maximum value.
    /// </param>
    ///
    virtual void getRange (unsigned short& nMinValue, unsigned short& nMaxValue) const;

    /// <summary>
    /// This will set the range for the image data into the TIFF file.
    /// </summary>
    ///
    /// <param name="nMinValue"> An unsigned short with the minimum value.
    /// </param>
    ///
    /// <param name="nMaxValue"> An unsigned short with the maximum value.
    /// </param>
    ///
    virtual void setRange (unsigned short nMinValue, unsigned short nMaxValue);

    /// <summary>
    /// (Private) This method is not meant for use by applications.
    /// </summary>
    ///
    /// <param name="pTIFF">
    /// Internal use only.
    /// </param>
    ///
    /// <returns>
    /// Internal use only.
    /// </returns>
    ///
    bool write ( struct tiff* pTIFF ) const;
};


/// <summary>
/// The TIFF format can be used to store the scanned pages of documents and books. For 
/// these type of images each frame within the file has information regarding the page
/// that the image represents.
/// </summary>
///
class TiffPageInformation : public Atil::FormatCodecInclusivePropertySetInterface, public TiffProperty
{
public:

    /// <summary>
    /// The constructor.
    /// </summary>
    ///
    /// <param name="pDoc"> A pointer to a <c>StringBuffer</c> which may contain the
    /// name of the document that was the source of the image file. The pointer may be 
    /// NULL in which case no name is stored.
    /// </param>
    ///
    /// <param name="pPage"> A pointer to a <c>StringBuffer</c> which may contain the
    /// name of the page that was the source of the frame (sub-image) within the image file.
    /// The pointer may be NULL in which case no name is stored.
    /// </param>
    ///
    /// <param name="nPage"> An integer set to the page index of this frame (sub-image).
    /// </param>
    ///
    /// <param name="nPage"> An integer count of the pages in this image file.
    /// </param>
    ///
    /// <param name="pX"> A double reference to an X offset for the image. If the
    /// pointer is NULL then offset will be 0 or none.
    /// </param>
    ///
    /// <param name="pY"> A double reference to an Y offset for the image. If the
    /// pointer is NULL then offset will be 0 or none.
    /// </param>
    ///
    TiffPageInformation (Atil::StringBuffer* pDoc, Atil::StringBuffer* pPage,
        int nPage, int nPages, double* pX, double* pY );

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~TiffPageInformation ();

    /// <summary>
    /// This method is an artificial copy constructor. All properties
    /// that are not trivial (no additional methods or data) derivations or 
    /// instances of ATIL defined property classes should implement this method.
    /// </summary>
    ///
    /// <returns>
    /// This method returns the new <c>FormatCodecPropertyInterface</c> instance.
    /// </returns>
    ///
    virtual Atil::FormatCodecPropertyInterface* clone () const;

    /// <summary>
    /// This query returns the document name.
    /// </summary>
    /// 
    /// <param name="sbName"> A <c>StringBuffer</c> reference to be set to the document name.
    /// </param>
    ///
    /// <returns>
    /// A return of false indicates that the tag containing that value was not 
    /// present in the set of tags for the current frame (IFD). The return value will
    /// be the default for that member.
    /// </returns>
    ///
    virtual bool getDocumentName ( Atil::StringBuffer& sbName ) const;

    /// <summary>
    /// This query returns the page name.
    /// </summary>
    /// 
    /// <param name="sbName"> A <c>StringBuffer</c> reference to be set to the page name.
    /// </param>
    ///
    /// <returns>
    /// A return of false indicates that the tag containing that value was not 
    /// present in the set of tags for the current frame (IFD). The return value will
    /// be the default for that member.
    /// </returns>
    ///
    virtual bool getPageName ( Atil::StringBuffer& sbName ) const;

    /// <summary>
    /// This query returns the page index.
    /// </summary>
    /// 
    /// <param name="nNumber"> An integer reference that will be set to the page index.
    /// </param>
    ///
    /// <returns>
    /// A return of false indicates that the tag containing that value was not 
    /// present in the set of tags for the current frame (IFD). The return value will
    /// be the default for that member.
    /// </returns>
    ///
    virtual bool getPageNumber ( int& nNumber ) const;

    /// <summary>
    /// This query will return the offset of the page from the top left of the image.
    /// </summary>
    ///
    /// <param name="dX"> A double reference to be set to the X offset for the image. 
    /// </param>
    ///
    /// <param name="dY"> A double reference to be set to the Y offset for the image. 
    /// </param>
    ///
    /// <returns>
    /// A return of false indicates that the tag containing that value was not 
    /// present in the set of tags for the current frame (IFD). The return value will
    /// be the default for that member.
    /// </returns>
    ///
    virtual bool getPosition ( double& dX, double& dY ) const;


private:
    /// <summary>
    /// (Private) Internal use only.
    /// </summary>
    ///
    /// <param name="pTIFF">
    /// Internal use only.
    /// </param>
    ///
    /// <returns>
    /// Internal use only.
    /// </returns>
    ///
    bool write ( struct tiff* pTIFF ) const;
};

#endif
