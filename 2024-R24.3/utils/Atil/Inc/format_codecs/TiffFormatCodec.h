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

#ifndef IMAGEFORMATCODEC_H
#include "ImageFormatCodec.h"
#endif
#ifndef DATASTREAMINTERFACE_H
#include "DataStreamInterface.h"
#endif

#ifndef FORMATCODECAPIVERSIONINTERFACE_H
namespace Atil { class FormatCodecApiVersionInterface; }
#endif

#ifndef TIFFFORMATCODEC_H
#define TIFFFORMATCODEC_H

extern "C"
{
    /// <summary>
    /// This method is required to be exported as part of the ATIL format codec interface.
    /// It is used for checking the version of the library the format codec API the 
    /// implementation is based.
    /// </summary>
    ///
    /// <returns>
    /// An instance of the <c>FormatCodecApiVersionInterface</c> class.
    /// </returns>
    ///
    const Atil::FormatCodecApiVersionInterface* ATIL_EXPORT tiffApiVersion ();
}

/// <summary>
/// The implementation of the <c>Atil::ImageFormatCodec</c> API for the purpose of reading
/// Tag Image File Format (TIFF) files.
/// </summary>
///
class TiffFormatCodec : public Atil::ImageFormatCodec, public Atil::ImageFormatCodecStreamingInterface
{
public:
    enum TiffId { 
        /// <summary>
        /// This entry is the id a place holder for components of set based properties.
        /// </summary>
        kMember, 
        /// <summary>
        /// This entry is the id for the description of the byte order property.
        /// </summary>
        kByteOrder, 
        /// <summary>
        /// This entry is the id for the TIFF photometric interpretation property.
        /// </summary>
        kPhotometricInterpretation, 
        /// <summary>
        /// This entry is the id for the TIFF ASCII field recording the image's artist.
        /// </summary>
        kArtist, 
        /// <summary>
        /// This entry is the id for the TIFF ASCII field recording the image's copyright.
        /// </summary>
        kCopyright, 
        /// <summary>
        /// This entry is the id for the TIFF ASCII field recording a data and time.
        /// </summary>
        kDateTime, 
        /// <summary>
        /// This entry is the id for the TIFF recording of the bit order.
        /// </summary>
        kFillOrder, 
        /// <summary>
        /// This entry is the id for the TIFF gray response curve.
        /// </summary>
        kGrayResponse, 
        /// <summary>
        /// This entry is the id for the TIFF ASCII field recording the name of the generating system.
        /// </summary>
        kHostComputer, 
        /// <summary>
        /// This entry is the id for the TIFF ASCII field recording a set description of the image.
        /// </summary>
        kImageDescription,
        /// <summary>
        /// This entry is the id for the TIFF ASCII field recording a description of the scanner used for the image.
        /// </summary>
        kScannerMake,
        /// <summary>
        /// This entry is the id for the TIFF ASCII field recording a description of the scanner model used for the image.
        /// </summary>
        kScannerModel,
        /// <summary>
        /// This entry is the id for the TIFF ASCII field recording a description software used to create the image.
        /// </summary>
        kSoftware,
        /// <summary>
        /// This entry is the id for an individual type of compression.
        /// </summary>
        kCompressionType,
        /// <summary>
        /// This entry is the id for that describes a property representing a private TIFF tag.
        /// </summary>
        kPrivateTag,
        /// <summary>
        /// This entry is the id for the property holding the TIFF sample range information.
        /// </summary>
        kSampleRange,
        /// <summary>
        /// This entry is the id for the property holding the TIFF page information.
        /// </summary>
        kPageInformation
    };
public:
    /// <summary>
    /// The simple constructor.
    /// </summary>
    /// 
    /// <param name="enabledPatentedEncoding">An integer with two flags 0x01 and 0x02
    /// where 0x01 enables reading and 0x02 enables writing of LZW patented compression in
    /// TIFF files. As UniSYS patent has expired the default is to now enable both reading and writing.
    /// </param>
    ///
    TiffFormatCodec (int enabledPatentedEncoding = 3);

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~TiffFormatCodec ();

    /// <summary>
    /// This method allows the <c>PngFormatCodec</c> to return it's version
    /// information. 
    /// </summary>
    ///
    /// <param name="nLibMajor">An unsigned integer reference that should be 
    /// assigned the major version number for the <c>PngFormatCodec</c>.
    /// </param>
    ///
    /// <param name="nLibMinor">An unsigned integer reference that should be 
    /// assigned the minor version number for the <c>PngFormatCodec</c>.
    /// </param>
    ///
    /// <param name="nRelease">An unsigned integer reference that should be 
    /// assigned the Release number for this build of the <c>ImageFormatCodec</c>.</param>
    ///
    /// <param name="nBranch">An unsigned integer reference that should be 
    /// assigned the Branch number for this build of the <c>ImageFormatCodec</c>.</param>
    ///
    /// <param name="nBuild">An unsigned integer reference that should be 
    /// assigned the build number for the <c>ImageFormatCodec</c>.
    /// </param>
    ///
    virtual void getLibVersionInfo (unsigned int& nLibMajor, unsigned int& nLibMinor
        , unsigned int& nRelease, unsigned int& nBranch, unsigned int& nBuild) const;
    
    /// <summary>
    /// ATIL defines version numbers that are used to track the revisions to the
    /// the API defined by <c>ImageFormatCodec</c> and other classes that are used
    /// to interface between ATIL and the format codecs.  When an <c>ImageFormatCodec</c>
    /// is created it will have these version numbers encoded within it. They
    /// are then returned in this call to ATIL which can check for compatibility with
    /// the codec compiled version.
    /// </summary>
    ///
    /// <param name="nMajor">An unsigned integer reference that should be 
    /// assigned the major version number for the <c>BmpFormatCodec</c> API.
    /// </param>
    ///
    /// <param name="nMinor">An unsigned integer reference that should be 
    /// assigned the minor version number for the <c>BmpFormatCodec</c> API.
    /// </param>
    ///
    virtual void getApiVersionInfo (unsigned int& nMajor, unsigned int& nMinor) const;

    /// <summary>
    /// This query returns the appropriate value from the <c>CodecCapability</c> 
    /// <see cref="ImageFormatCodec::CodecCapability"/> 
    /// </summary>
    ///
    /// <returns>
    /// This returns a value from the <c>CodecCapability</c> enum.
    /// </returns>
    ///
    virtual Atil::ImageFormatCodec::CodecCapability codecCapability () const;

    /// <summary>
    /// This method is used to verify that a filename selected is valid and 
    /// can be written to. As the <c>FileSpecifier</c> argument can encode both 
    /// <c>kFilePath</c> and <c>kOther</c>, the implementation of this method may 
    /// do more than verify the validity of File I/O queries.
    /// </summary>
    ///
    /// <param name="fs">A const reference to a <c>FileSpecifier</c><see cref="FileSpecifier"/>
    /// instance that holds the "file" that will be potentially written to.
    /// </param>
    ///
    /// <returns>
    /// This method returns true if the file can be created.
    /// </returns>
    ///
    virtual bool isValidFileName (const Atil::FileSpecifier& fs) const;

    /// <summary>
    /// This query returns the appropriate value for the format from the 
    /// <c>FormatType</c><see cref="FormatType"/> enum.
    /// </summary>
    ///
    /// <returns>
    /// This returns an entry from the <c>FormatType</c> enum.
    /// </returns>
    ///
    virtual ImageFormatCodec::FormatType getFormatDecodabilityType () const;

    /// <summary>
    /// This method allows the application to retrieve the name of a property
    /// that is specific to this format codec.
    /// </summary>
    ///
    /// <param name="id">A definition from the <c>TiffId</c>
    /// that indicates the property.
    /// </param>
    ///
    /// <param name="sbName">A <c>String buffer</c> reference that
    /// will be set to the name of the property.
    /// </param>
    ///
    /// <returns>
    /// This will return true if successful.
    /// </returns>
    ///
    virtual bool getTiffPropertyName(TiffId id, Atil::StringBuffer& sbName) const;

    /// <summary>
    /// This query returns the appropriate value for the format from the 
    /// <c>FormatFeature</c><see cref="FormatFeature"/> enum.
    /// </summary>
    ///
    /// <param name="feature">An enum entry indicating the <c>FormatFeature</c>
    /// being queried.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the <c>FormatFeature</c> is supported.
    /// </returns>
    ///
    virtual bool isFormatFeature ( FormatFeature feature ) const;

    /// <summary>
    /// This query returns the appropriate value for the format from the 
    /// <c>FormatOrganization</c><see cref="FormatOrganization"/> enum.
    /// </summary>
    ///
    /// <returns>
    /// This query returns a value from <c>FormatOrganization</c> enum.
    /// </returns>
    ///
    virtual FormatOrganization getFormatOrganization () const;

    /// <summary>
    /// This query returns the appropriate value for the format from the 
    /// <c>FormatFrameType</c><see cref="FormatFrameType"/> enum.
    /// </summary>
    ///
    /// <returns>
    /// This query returns a value from <c>FormatFrameType</c> enum.
    /// </returns>
    ///
    virtual FormatFrameType getFormatFrameType () const;

    /// <summary>
    /// This method allows the application to test for the ability
    /// to read or write a property to or from a file.
    /// </summary>
    ///
    /// <param name="propId">A definition from the <c>FormatCodecPropertyInterface::PropertyIdentifier</c>
    /// that indicates the property that is of interest.
    /// </param>
    ///
    /// <param name="pCustomProptertyName">A <c>String buffer</c> pointer (or NULL) that
    /// holds the "name" of a property. This string match system can be used
    /// to query for non-ATIL defined properties.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the property is supported by the codec.
    /// </returns>
    ///
    virtual bool isSupportedProperty (
        Atil::FormatCodecPropertyInterface::PropertyIdentifier propId,
        Atil::StringBuffer* pCustomPropertyName = (Atil::StringBuffer*) NULL) const;

    /// <summary>
    /// If a format as one or more extensions (ie .tif, .tiff, etc.) then it
    /// should return the number of extensions that it wants to associate with this format.
    /// </summary>
    ///
    /// <remarks>
    /// ATIL does not use the extensions (letters after the . within the file name) to 
    /// identify an image file encoding. Each registered <c>ImageFormatCodec</c> instance
    /// will have a chance to claim the file as it's format until the file has been claimed.
    /// </remarks>
    ///
    /// <returns>
    /// This will return the number of extensions.
    /// </returns>
    ///
    virtual int getNumExtensions () const;

    /// <summary>
    /// This method provides a description of each extension that is supported for use
    /// by the application and maybe displayed to the user. Such descriptions are common
    /// elements of Windows(tm) file browsing dialogs. (ie .tif, .tiff, etc.)
    /// </summary>
    ///
    /// <param name="nExtensionIndex">The integer index of the extension description to
    /// retrieve. It ranges from zero to <c>getNumeExtensions() - 1</c>.
    /// </param>
    ///
    /// <param name="sbExtension">A reference to a <c>StringBuffer</c> instance that will
    /// be set to the extension text.
    /// </param>
    ///
    virtual void getExtensionText (int nExtensionIndex,
        Atil::StringBuffer& sbExtension) const;

    /// <summary>
    /// This method returns the full name of the format that the <c>ImageFormatCodec</c> handles.
    /// It may be used by the caller and displayed in the UI for the application.
    /// </summary>
    ///
    /// <param name="sbFormatName">A reference to a <c>StringBuffer</c> instance that will
    /// be set to the format name text.
    /// </param>
    ///
    virtual void getFormatName (Atil::StringBuffer& sbFormatName) const;

    /// <summary>
    /// This method returns a description of the format. 
    /// It may be used by the caller and displayed in the UI for the application.
    /// </summary>
    ///
    /// <param name="sbDescription">A reference to a <c>StringBuffer</c> instance that will
    /// be set to the format description text.
    /// </param>
    ///
    virtual void getDescriptionText (Atil::StringBuffer& sbDescription) const;

    /// <summary>
    /// This method returns any copyright information of the format or source code used
    /// in the implementation of the <c>ImageFormatCodec</c>. It may be used by the caller
    /// and displayed in the UI for the application.
    /// </summary>
    ///
    /// <param name="sbCopyright">A reference to a <c>StringBuffer</c> instance that will
    /// be set to the format copyright text.
    /// </param>
    ///
    virtual void getCopyrightText (Atil::StringBuffer& sbCopyright) const;

    /// <summary>
    /// This method allows the application to retrieve the name of a property
    /// that is specific to this format codec.
    /// </summary>
    ///
    /// <param name="tagID">An unsigned short that is the numeric ID of the desired tag.
    /// </param>
    ///
    /// <param name="sbName">A <c>String buffer</c> reference that
    /// will be set to the name of the property.
    /// </param>
    ///
    void getPrivateTagName(unsigned short tagID, Atil::StringBuffer& sbName) const;

    /// <summary>
    /// This method is used by <c>FileReadDescriptor</c> to check the readability of a given file. 
    /// It applies only to this format handler. It is not meant to be used by application developers. 
    /// </summary>
    ///
    /// <param name="fileSpecifier">A constant <c>FileSpecifier</c> instance that holds
    /// the "path" of the encoded image is to be tested.
    /// </param>
    /// 
    /// <param name="ff">A pointer to a <c>FindFileInterface</c> derived class or NULL. 
    /// </param>
    ///
    /// <returns>
    /// This query returns a value from <c>FormatDecodability</c> enum.
    /// </returns>
    ///
    /// <remarks>
    /// The <c>FileReadDescriptor</c> exposes a static method should be used by applications
    /// to determine if a file is a 'decodable' image file.
    /// </remarks>
    ///
    virtual ImageFormatCodec::FormatDecodability isDecodableFile (
        const Atil::FileSpecifier& fileSpecifier, 
        Atil::FindFileInterface* ff = (Atil::FindFileInterface*) NULL) const;

    /// <summary>
    /// This method is used by <c>FileWriteDescriptor</c> to check the write ability of a 
    /// given image. It tests the type and size of an image's encode ability in the format.
    /// It is not meant to be used by application developers. 
    /// </summary>
    ///
    /// <param name="allAboutImageData">A const reference to a <c>DataModelAttributes</c>
    /// instance that describes the color and image type of the data to be encoded.
    /// </param>
    /// 
    /// <param name="size">The size in pixels of the data to be encoded.
    /// </param>
    ///
    /// <returns>
    /// This returns true of the codec can encode the data being queried.
    /// </returns>
    ///
    /// <remarks>
    /// The <c>FileWriteDescriptor</c> class exposes static methods should be used by 
    /// application developers to test the ability of a <c>ImageFormatCodec</c> to 
    /// encode the image type.
    /// </remarks>
    ///
    virtual bool isEncodableImage (const Atil::DataModelAttributes& allAboutImageData,
        Atil::Size size ) const;

    /// <summary>
    /// This method is used by <c>FileReadDescriptor</c> to open an image file for decoding.
    /// </summary>
    /// 
    /// <param name="fsThisImage">A constant <c>FileSpecifier</c> instance that holds
    /// the "path" of the encoded image is to be opened.
    /// </param>
    ///  
    /// <returns>
    /// This method returns an instance (pointer to) of the <c>ReadImageFileInterface</c>
    /// for use by the <c>FileReadDescriptor</c> in decoding the image data.
    /// </returns>
    /// 
    /// <remarks>
    /// This method is not for use by application developers. It is an internal ATIL method.
    /// </remarks>
    ///
    virtual Atil::ReadImageFileInterface* openImage (
        const Atil::FileSpecifier* fsThisImage) const;

    /// <summary>
    /// This method is used by <c>FileReadDescriptor</c> to open an image file for decoding.
    /// </summary>
    /// 
    /// <param name="fsThisImage">A constant <c>FileSpecifier</c> instance that holds
    /// the "path" of the encoded image is to be opened.
    /// </param>
    /// 
    /// <param name="ff">An instance of a <c>FindFileInterface</c> derived class. 
    /// </param>
    ///
    /// <returns>
    /// This method returns an instance (pointer to) of the <c>ReadImageFileInterface</c>
    /// for use by the <c>FileReadDescriptor</c> in decoding the image data.
    /// </returns>
    /// 
    /// <remarks>
    /// This method is not for use by application developers. It is an internal ATIL method.
    /// </remarks>
    ///
    virtual Atil::ReadImageFileInterface * openImage (
        const Atil::FileSpecifier* fsThisImage, Atil::FindFileInterface& ff) const;

    /// <summary>
    /// This method is used by <c>FileWriteDescriptor</c> to open a file for image encoding.
    /// </summary>
    /// 
    /// <returns>
    /// This method returns an instance (pointer to) of the <c>WriteImageFileInterface</c>
    /// for use by the <c>FileWriteDescriptor</c> in encoding the image data.
    /// </returns>
    /// 
    /// <remarks>
    /// This method is not for use by application developers. It is an internal ATIL method.
    /// </remarks>
    ///
    virtual Atil::WriteImageFileInterface* writeImage () const;

    /// <summary>
    /// This method is used by <c>FileReadDescriptor</c> in it's copy constructor to 
    /// open a new connection to the data source.
    /// </summary>
    ///
    /// <param name="pOpenImage">An open image to be copied. 
    /// </param>
    ///
    /// <param name="ff">An instance of a <c>FindFileInterface</c> derived class. 
    /// This may be referenced during construction of the clone.
    /// </param>
    ///
    /// <returns>
    /// This method returns an instance (pointer to) of the <c>ReadImageFileInterface</c>
    /// for use by the <c>FileReadDescriptor</c> in decoding the image data.
    /// </returns>
    /// 
    /// <remarks>
    /// This method is not for use by application developers. It is an internal ATIL method.
    /// </remarks>
    ///
    virtual Atil::ReadImageFileInterface* cloneOpenImage (
        const Atil::ReadImageFileInterface* pOpenImage, Atil::FindFileInterface& ff ) const;

    /// <summary> This method passes an extension to act as a pretest for a format
    /// match. If this returns true, then an isDecodable call will follow.</summary>
    /// <param name="pExt">This is the file extension in the ASCII character
    /// format. The extension will be in ASCII to make testing quicker.</param>
    /// <returns> This should return true for an extension match. This is quick
    /// test and if true is returned a isDecodable check will follow.</returns>
    virtual bool isExtensionMatch(const char* pExt) const;

    /// <summary>
    /// This method is used by <c>FileReadDescriptor</c> to open an image file for decoding.
    /// </summary>
    /// 
    /// <param name="pdsStream">An pointer to a <c>Atil::SeekableDataStreamInterface</c> derived class 
    /// that provides a stream of data to be encoded.
    /// </param>
    /// 
    /// <returns>
    /// This method returns an instance (pointer to) of the <c>ReadImageFileInterface</c>
    /// for use by the <c>FileReadDescriptor</c> in decoding the image data.
    /// </returns>
    /// 
    /// <remarks>
    /// This method is not for use by application developers. It is an internal ATIL method.
    /// The DataStreamInterface classes must be <c>Atil::SeekableDataStreamInterface</c>  class.
    /// </remarks>
    ///
    virtual Atil::ReadImageFileInterface* openImage (
        Atil::DataStreamInterface* pdsStream) const;

    /// <summary>
    /// This method is used by <c>FileWriteDescriptor</c> to open a stream for image encoding.
    /// </summary>
    /// 
    /// <param name="pdsStream">An pointer to a <c>Atil::SeekableDataStreamInterface</c>  derived class
    /// that provides a stream of data to be encoded.
    /// </param>
    ///
    /// <returns>
    /// This method returns an instance (pointer to) of the <c>WriteImageFileInterface</c>
    /// for use by the <c>FileWriteDescriptor</c> in encoding the image data.
    /// </returns>
    /// 
    /// <remarks>
    /// This method is not for use by application developers. It is an internal ATIL method.
    /// The DataStreamInterface classes must be <c>Atil::SeekableDataStreamInterface</c> class.
    /// </remarks>
    ///
    virtual Atil::WriteImageFileInterface* writeImage (
        Atil::DataStreamInterface* pdsStream) const;

    /// <summary>
    /// This method is used to query the mode of UniSYS LZW enabling.
    /// </summary>
    /// 
    /// <returns>An integer with two flags 0x01 and 0x02
    /// where 0x01 enables reading and 0x02 enables writing of LZW patented compression in
    /// TIFF files. 
    /// </returns>
    ///
    virtual int patentedEncodingEnabled () const;

    /// <summary>
    /// Applications wishing to utilize the LibGeoTIFF CSV files for correlation need
    /// to call this method with the location of the CSV files.
    /// </summary>
    ///
    /// <param name="sbPath">A const <c>String buffer</c> reference that
    /// holds the path to the libGeoTIFF CSV code files.
    /// </param>
    ///
    void setPathToCsvFiles(const Atil::StringBuffer& sbPath);

    /// <summary>
    /// This method will return the path set for the LibGeoTIFF files.
    /// </summary>
    ///
    /// <param name="sbPath">A <c>String buffer</c> reference that
    /// will be set to the path used to read the libGeoTIFF CSV code files.
    /// </param>
    ///
    void getPathToCsvFiles(Atil::StringBuffer& sbPath) const;

private:
    bool mbPatentedReadEnabled;
    bool mbPatentedWriteEnabled;

    static Atil::StringBuffer   msbCsvPath;     // Shared by all instances of the codec
};

#endif

