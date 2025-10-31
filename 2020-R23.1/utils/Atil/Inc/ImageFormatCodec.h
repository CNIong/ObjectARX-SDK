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
#ifndef ATILEXCEPTION_H
#include "ATILException.h"
#endif
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif

#ifndef SIZE_H
namespace Atil { class Size; }
#endif
#ifndef STRINGBUFFER_H
namespace Atil { class StringBuffer; }
#endif
#ifndef FILESPECIFIER_H
namespace Atil { class FileSpecifier; }
#endif
#ifndef DATAMODELATTRIBUTES_H
namespace Atil { class DataModelAttributes; }
#endif
#ifndef FINDFILEINTERFACE_H
namespace Atil { class FindFileInterface; }
#endif
#ifndef READIMAGEFILEINTERFACE_H
namespace Atil { class ReadImageFileInterface; }
#endif
#ifndef WRITEIMAGEFILEINTERFACE_H
namespace Atil { class WriteImageFileInterface; }
#endif
#ifndef DATASTREAMINTERFACE_H
namespace Atil { class DataStreamInterface; }
#endif

#ifndef IMAGEFORMATCODEC_H
#define IMAGEFORMATCODEC_H

namespace Atil
{

/// <summary>
/// The <c>ImageFormatCodec</c> class serves as the base class for all image format
/// codecs. Reading and writing any format for encoding data is started through the
/// format specific derivation of this class. 
/// </summary>
///
/// <remarks>
/// While the discussion of image formats uses the terminology of files an image 
/// encoding is separate from it's storage. A image encoded in PNG is not necessarily
/// stored as an operating file stored on a local disk. It could be an in memory 
/// stream, a blob within a database, or the result of an http request. ATIL includes
/// some support for non-file based images.
/// </remarks>
///
class ImageFormatCodec 
{
public:
    /// <summary>
    /// Defines flags to indicate the read and write capability of the format handler.
    /// </summary>
    enum CodecCapability { 
        /// <summary>
        /// The <c>ImageFormatCodec</c> can read images encoded in a given format.
        /// </summary>
        ///
        kCanRead = 0x0001, 

        /// <summary>
        /// The <c>ImageFormatCodec</c> can encode images into a given format.
        /// </summary>
        /// 
        kCanWrite = 0x002, 

        /// <summary>
        /// The <c>ImageFormatCodec</c> can encode and decode images of a given format.
        /// </summary>
        /// 
        kCanReadAndWrite = 0x003
    };

    /// <summary>
    /// Image Formats vary in the uniqueness of file signatures that are defined
    /// for the purpose of identifying a given stream of data as being encoded in
    /// a given format.  This enum defines a method for the Image Format codec to
    /// indicate it's ability to determine that a stream of data is in it's 
    /// encoding or not. ATIL will use this information to test <c>kStronglyTyped</c>
    /// codecs for the ability to decode a stream to eliminate them before the 
    /// weaker checks used by <c>kLooselyTyped</c> formats.
    /// </summary>
    ///
    enum FormatType { 
        /// <summary>
        /// The format has a strong, easily recognized key that allows definitive
        /// identification with a relatively simple and straightforward test.
        /// </summary>
        ///
        kStronglyTyped,
        /// <summary>
        /// The format does not have a strong key and either must be completely or
        /// largely decoded in order to determine if the file is an image encoded
        /// in the format.
        /// </summary>
        ///
        kLooselyTyped
    };

    /// <summary>
    /// The <c>FormatOrganization</c> enum declares key values that are used
    /// by codecs to indicate whether the image format that they handle is 
    /// organized within a single file or if multiple separate files are needed
    /// to decode the image.
    /// </summary>
    enum FormatOrganization { 
        /// <summary>
        /// A single file carries all the information needed to correctly decode
        /// the image. Most formats are single file. Examples include TIFF, PNG, 
        /// and JPEG.
        /// </summary>
        ///
        kSingleFile, 
        /// <summary>
        /// A minority of image formats use multiple files to encode an image. 
        /// Examples include most Multi-spectral formats and Geo-Spot.
        /// </summary>
        ///
        kMultipleFiles 
    };

    /// <summary>
    /// The <c>FormatDecodability</c> enum defines keys for the codec to return
    /// the readability of the file. 
    /// </summary>
    ///
    enum FormatDecodability { 
        /// <summary>
        /// The file contains data that is an encoded image that the <c>ImageFormatCodec</c>
        /// can decode into an image.
        /// </summary>
        ///
        kReadable, 
        /// <summary>
        /// The file contains data that is an encoded image that the <c>ImageFormatCodec</c>
        /// can uniquely identify as the encoding it supports, however it is encoded in such
        /// a way that the <c>ImageFormatCodec</c> can not decode it. 
        /// </summary>
        ///
        /// <remarks>
        /// ATIL will pass the file reference to be checked to all of the codecs that have
        /// been registered with it until one of the codecs claim it. If a codec can claim
        /// a file as being encoded with the codec's format, but can not decode this 
        /// file, then returning this value will keep ATIL from trying other codecs.
        /// </remarks>
        ///
        kNonSupported,
        /// <summary>
        /// The file contains data that is an encoded image that the <c>ImageFormatCodec</c>
        /// can uniquely identify not being in the encoding it supports.
        /// </summary>
        ///
        kNonReadable, 
        /// <summary>
        /// The file contains data that is an encoded image that the <c>ImageFormatCodec</c>
        /// can uniquely identify as the encoding it supports, however the file is not
        /// complete or has been corrupted in some way that makes it unreadable.
        /// </summary>
        ///
        kCorrupted 
    };

    /// <summary>
    /// The <c>FormatFeature</c> enum defines keys for the codec to return
    /// information about the type of encoding the that the codec and format supports. 
    /// </summary>
    ///
    enum FormatFeature { 
        /// <summary>
        /// The image format supports a compression algorithm that when decompressed 
        /// returns the identical data. None of the original information or accuracy
        /// of the data is compromised to achieve the compression.
        /// </summary>
        ///
        kLosslessCompression,
        /// <summary>
        /// The image format supports a compression algorithm that when decompressed
        /// will not return identical data. The high compression rates offered by
        /// lossy algorithm are achieved through sophisticated mathematical methods
        /// of generalizing areas of the image. They often preserve the look of the image
        /// but do alter the pixel values. Many algorithms can also introduce artifacts or
        /// distortions in the image data as a side effect of the compression process.
        /// </summary>
        ///
        kLossyCompression,
        /// <summary>
        /// If the layout of the data within the image file can be decoded in a
        /// top down, left right manner in an efficient manner, ATIL can directly
        /// read data from the file instead of storing it internally. This can 
        /// speed the loading of data and reduce the consumption of system swap space.
        /// </summary>
        ///
        kDirectLoadable,
        /// <summary>
        /// If the layout of the data within the image file can be decoded in a
        /// top down, left right manner in a some what efficient manner, ATIL can directly
        /// read data from the file and store it internally. This can 
        /// speed the loading of data however it will take longer to load the 
        /// entirety of the image into the ATIL swap system.
        /// </summary>
        ///
        kDelayLoadable, 
        /// <summary>
        /// Some formats can encode multiple images into a single file. This entry
        /// will indicate that this format supports encoding multiple images in
        /// such a way as TIFF.
        /// </summary>
        ///
        kMultipleFrames,
        /// <summary>Many formats support a special purpose reduced resolution copy of the
        /// encoded image for quick small views of the image. This flag indicates support
        /// for creating such small views. This is typically used for the single low 
        /// resolution copy of a full resolution frame akin to what is available in TIFF</summary>
        ///
        kThumbnailFrames,
        /// <summary>
        /// Some formats can be identified in the first few bytes of the file and are
        /// laid out in such a manner that they may be read in a sequential manner from
        /// beginning to end. Examples include JPEG and PNG. Such formats may be loaded
        /// from memory directly.
        /// </summary>
        ///
        kStreamable
    };  

    /// <summary>
    /// Image formats that encode multiple images into a single file set can 
    /// report the type of the images that are encoded. 
    /// </summary>
    ///
    enum FormatFrameType { 
        /// <summary> This entry indicates that each image within the file set
        /// is an independent image.</summary>
        ///
        kImage, 
        /// <summary> This entry indicates that each image within the file set
        /// is an a part of a single image.</summary>
        ///
        kBand,
        /// <summary> This entry indicates that each image within the file set
        /// is low resolution copy of a single full resolution image.</summary>
        ///
        kMipMap
    };

public:
    /// <summary>
    /// Virtual destructor.
    /// </summary>
    ///
    virtual ~ImageFormatCodec ();

    /// <summary>
    /// This method allows the <c>ImageFormatCodec</c> to return it's version
    /// information. 
    /// </summary>
    ///
    /// <param name="nLibMajor">An unsigned integer reference that should be 
    /// assigned the major version number for the <c>ImageFormatCodec</c>.
    /// </param>
    ///
    /// <param name="nLibMinor">An unsigned integer reference that should be 
    /// assigned the minor version number for the <c>ImageFormatCodec</c>.
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
        , unsigned int& nRelease, unsigned int& nBranch, unsigned int& nBuild) const = 0;

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
    /// assigned the major version number for the <c>ImageFormatCodec</c> API.
    /// </param>
    ///
    /// <param name="nMinor">An unsigned integer reference that should be 
    /// assigned the minor version number for the <c>ImageFormatCodec</c> API.
    /// </param>
    ///
    virtual void getApiVersionInfo (unsigned int& nMajor, unsigned int& nMinor) const = 0;

    /// <summary>
    /// This query returns the appropriate value from the <c>CodecCapability</c> 
    /// <see cref="CodecCapability"/>
    /// </summary>
    ///
    /// <returns>
    /// This returns a value from the <c>CodecCapability</c> enum.
    /// </returns>
    ///
    virtual CodecCapability codecCapability () const = 0;

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
    virtual bool isValidFileName (const FileSpecifier& fs) const = 0;

    /// <summary>
    /// This query returns the appropriate value for the format from the 
    /// <c>FormatType</c><see cref="FormatType"/> enum.
    /// </summary>
    ///
    /// <returns>
    /// This returns an entry from the <c>FormatType</c> enum.
    /// </returns>
    ///
    virtual FormatType getFormatDecodabilityType () const = 0;

    /// <summary>
    /// This query returns the appropriate value for the format from the 
    /// <c>FormatOrganization</c><see cref="FormatOrganization"/> enum.
    /// </summary>
    ///
    /// <returns>
    /// This query returns a value from <c>FormatOrganization</c> enum.
    /// </returns>
    ///
    virtual FormatOrganization getFormatOrganization () const = 0;

    /// <summary>
    /// This query returns the appropriate value for the format from the 
    /// <c>FormatFrameType</c><see cref="FormatFrameType"/> enum.
    /// </summary>
    ///
    /// <returns>
    /// This query returns a value from <c>FormatFrameType</c> enum.
    /// </returns>
    ///
    virtual FormatFrameType getFormatFrameType () const = 0;

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
    virtual bool isFormatFeature ( FormatFeature feature ) const = 0;

    /// <summary>
    /// This method allows the application to test for the ability
    /// to read or write a property to or from a file.
    /// </summary>
    ///
    /// <param name="propId">A definition from the <c>FormatCodecPropertyInterface::PropertyIdentifier</c>
    /// that indicates the property that is of interest.
    /// </param>
    ///
    /// <param name="pCustomPropertyName">A <c>String buffer pointer</c> (or NULL) that
    /// holds the "name" of a property. This string match system can be used
    /// to query for non-ATIL defined properties.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the property is supported by the codec.
    /// </returns>
    ///
    virtual bool isSupportedProperty (
        FormatCodecPropertyInterface::PropertyIdentifier propId,
        StringBuffer* pCustomPropertyName = (StringBuffer*) NULL) const = 0;

    /// <summary>
    /// If a format as one or more extensions (ie .bmp, .png, .jpg, etc.) then it
    /// should return the number of extensions that it wants to associate with this format.
    /// </summary>
    ///
    /// <returns>
    /// This returns the integer number of extensions.
    /// </returns>
    ///
    /// <remarks>
    /// ATIL does not use the extensions (letters after the . within the file name) to 
    /// identify an image file encoding. Each registered <c>ImageFormatCodec</c> instance
    /// will have a chance to claim the file as it's format until the file has been claimed.
    /// </remarks>
    ///
    virtual int getNumExtensions () const = 0;
    
    /// <summary>
    /// This method provides a description of each extension that is supported for use
    /// by the application and maybe displayed to the user. Such descriptions are common
    /// elements of Windows(tm) file browsing dialogs. (ie .bmp, .png, .jpg, etc.)
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
        StringBuffer& sbExtension) const = 0;

    /// <summary>
    /// This method returns the full name of the format that the <c>ImageFormatCodec</c> handles.
    /// It may be used by the caller and displayed in the UI for the application.
    /// </summary>
    ///
    /// <param name="sbFormatName">A reference to a <c>StringBuffer</c> instance that will
    /// be set to the format name text.
    /// </param>
    ///
    virtual void getFormatName (StringBuffer& sbFormatName) const = 0;

    /// <summary>
    /// This method returns a description of the format. 
    /// It may be used by the caller and displayed in the UI for the application.
    /// </summary>
    ///
    /// <param name="sbDescription">A reference to a <c>StringBuffer</c> instance that will
    /// be set to the format description text.
    /// </param>
    ///
    virtual void getDescriptionText (StringBuffer& sbDescription) const = 0;

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
    virtual void getCopyrightText (StringBuffer& sbCopyright) const = 0;

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
    virtual FormatDecodability isDecodableFile (const FileSpecifier& fileSpecifier,
        FindFileInterface* ff = (FindFileInterface*) NULL) const = 0;

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
    virtual bool isEncodableImage (const DataModelAttributes& allAboutImageData,
        Size size ) const = 0;

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
    virtual ReadImageFileInterface* openImage (
        const FileSpecifier* fsThisImage) const = 0;

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
    virtual ReadImageFileInterface* openImage (
        const FileSpecifier* fsThisImage, FindFileInterface& ff) const = 0;

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
    virtual WriteImageFileInterface* writeImage ( ) const = 0;

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
    virtual ReadImageFileInterface* cloneOpenImage (
        const ReadImageFileInterface* pOpenImage, FindFileInterface& ff ) const = 0;

    /// <summary> This method passes an extension to act as a pretest for a format
    /// match. If this returns true, then an isDecodable call will follow.</summary>
    /// <param name="pExt">This is the file extension in the ASCII character
    /// format. The extension will be in ASCII to make testing quicker.</param>
    /// <returns> This should return true for an extension match. This is quick
    /// test and if true is returned a isDecodable check will follow.</returns>
    virtual bool isExtensionMatch(const char* pExt) const = 0;
};

/// <summary>
/// <c>ImageFormatCodec</c> developers may optionally add this class as a parent 
/// (Multiple derivation). Doing so exposes stream ability to the format. 
/// The class must be able to stream read and write as per the CodecCapability reported
/// in <c>ImageFormatCodec::codecCapability()</c>.
/// </summary>
///
class ImageFormatCodecStreamingInterface
{
public:
    /// <summary>
    /// Virtual Destructor.
    /// </summary>
    ///
    virtual ~ImageFormatCodecStreamingInterface();

    /// <summary>
    /// This method is used by <c>FileReadDescriptor</c> to open an image file for decoding.
    /// </summary>
    /// 
    /// <param name="pdsStream">An pointer to a <c>DataStreamInterface</c> derived class 
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
    /// </remarks>
    ///
    virtual ReadImageFileInterface* openImage (DataStreamInterface* pdsStream) const = 0;

    /// <summary>
    /// This method is used by <c>FileWriteDescriptor</c> to open a stream for image encoding.
    /// </summary>
    /// 
    /// <param name="pdsStream">An pointer to a <c>DataStreamInterface</c> derived class
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
    /// </remarks>
    ///
    virtual WriteImageFileInterface* writeImage (DataStreamInterface* pdsStream) const = 0;
};

} // end of namespace Atil

#endif

