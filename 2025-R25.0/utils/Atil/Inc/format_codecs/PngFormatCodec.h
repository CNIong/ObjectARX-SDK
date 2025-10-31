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

#ifndef  IMAGEFORMATCODEC_H
#include <ImageFormatCodec.h>
#endif

#ifndef FORMATCODECAPIVERSIONINTERFACE_H
namespace Atil { class FormatCodecApiVersionInterface; }
#endif

#ifndef PNGFORMATCODEC_H
#define PNGFORMATCODEC_H

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
    const Atil::FormatCodecApiVersionInterface* ATIL_EXPORT pngApiVersion ();
}

/// <summary>
/// The implementation of the <c>Atil::ImageFormatCodec</c> API for the purpose of reading
/// PNG (Portable Network Graphics) files.
/// </summary>
///
class PngFormatCodec : public Atil::ImageFormatCodec, public Atil::ImageFormatCodecStreamingInterface
{
public:
    /// <summary>
    /// This enum lists the properties or meta-data type information
    /// that can be encoded in a PNG file and can be returned by this implementation.
    /// </summary>
    ///
    enum PngIdentifier { 
        /// <summary>
        /// This is the id for the PNG property that describes the gamma for the image.
        /// </summary>
        kGamma, 
        /// <summary>
        /// This is the id for the PNG property that describes the scale for the image.
        /// </summary>        
        kScale, 
        /// <summary>
        /// This is the id for the PNG property that describes the offset for the image.
        /// </summary>        
        kOffset,
        /// <summary>
        /// This is the id for the PNG property that describes the SRGB color system for the image.
        /// </summary>        
        kSRGB, 
        /// <summary>
        /// This is the id for the PNG property that describes a histogram of the data in the image.
        /// </summary>        
        kHistogram,
        /// <summary>
        /// This is the id for the PNG property that describes the number of bits used in grayscale data.
        /// </summary>        
        kGraySignificantBits, 
        /// <summary>
        /// This is the id for the PNG property that describes the title for the image.
        /// </summary>        
        kTitle, 
        /// <summary>
        /// This is the id for the PNG property that lists the author of the image.
        /// </summary>        
        kAuthor, 
        /// <summary>
        /// This is the id for the PNG property that encodes a description of the image.
        /// </summary>        
        kDescription,
        /// <summary>
        /// This is the id for the PNG property that contains the copyright information for the image.
        /// </summary>        
        kCopyright, 
        /// <summary>
        /// This is the id for the PNG property that encodes the data and time of creation of the image.
        /// </summary>        
        kCreationTime, 
        /// <summary>
        /// This is the id for the PNG property that encodes a description software used to create the image.
        /// </summary>        
        kSoftware, 
        /// <summary>
        /// This is the id for the PNG property that encodes a disclaimer regarding the image.
        /// </summary>        
        kDisclaimer,
        /// <summary>
        /// This is the id for the PNG property that encodes a warning about the image.
        /// </summary>        
        kWarning, 
        /// <summary>
        /// This is the id for the PNG property that encodes the source of the image.
        /// </summary>        
        kSource, 
        /// <summary>
        /// This is the id for the PNG property that encodes a generic textual comment into image.
        /// </summary>        
        kComment, 
        /// <summary>
        /// This is the id for the PNG property that encodes the optional interlacing of the image data.
        /// </summary>        
        kInterlace
    };

public:
    /// <summary>
    /// The simple constructor.
    /// </summary>
    /// 
    PngFormatCodec ();

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~PngFormatCodec ();

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
	/// This query returns an entry from the <c>CodecCapability</c> enum.
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
	/// </param>
    /// instance that holds the "file" that will be potentially written to.
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
    virtual Atil::ImageFormatCodec::FormatType getFormatDecodabilityType () const;

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
    /// <param name="pCustomPropertyName">A <c>String buffer</c> pointer (or NULL) that
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
    /// This method allows the application to test for the ability
    /// to read or write a property to or from a file.
    /// </summary>
    ///
    /// <param name="propId">A definition from the <c>PngFormatCodec::PngIdentifier</c>
    /// that indicates the property that is of interest.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the property is supported by the codec.
    /// </returns>
    ///
    virtual bool isSupportedProperty ( PngFormatCodec::PngIdentifier propId ) const;

    /// <summary>
    /// This method allows the application to retrieve the name of a property
    /// that is specific to this format codec.
    /// </summary>
    ///
    /// <param name="id">A definition from the <c>PngIdentifier</c>
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
    virtual bool getPngPropertyName ( PngIdentifier id, Atil::StringBuffer& sbName  ) const;

    /// <summary>
    /// If a format as one or more extensions (ie .png, etc.) then it
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
    virtual int getNumExtensions () const;

    /// <summary>
    /// This method provides a description of each extension that is supported for use
    /// by the application and maybe displayed to the user. Such descriptions are common
    /// elements of Windows(tm) file browsing dialogs. (ie .png, etc.)
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
    virtual Atil::ImageFormatCodec::FormatDecodability isDecodableFile (
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
    virtual Atil::WriteImageFileInterface* writeImage ( ) const;

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
    virtual Atil::ReadImageFileInterface* openImage (Atil::DataStreamInterface* pdsStream) const;

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
    virtual Atil::WriteImageFileInterface* writeImage (Atil::DataStreamInterface* pdsStream) const;
};

#endif

