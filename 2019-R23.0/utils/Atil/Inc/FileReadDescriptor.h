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
#ifndef DATASTREAMINTERFACE_H
#include "DataStreamInterface.h"
#endif
#ifndef TRANSFORMS_H
#include "Transforms.h"
#endif

#ifndef SIZE_H
namespace Atil { class Size; }
#endif
#ifndef FILEREADDESCRIPTORREP_H
namespace Atil { class FileReadDescriptorRep; }
#endif
#ifndef FILESPECIFIER_H
namespace Atil { class FileSpecifier; }
#endif
#ifndef IMAGEFORMATCODEC_H
namespace Atil { class ImageFormatCodec; }
#endif
#ifndef ROWPROVIDERINTERFACE_H
namespace Atil { class RowProviderInterface; }
#endif
#ifndef FORMATCODECPROPERTYSETITERATOR_H
namespace Atil { class FormatCodecPropertySetIterator; }
#endif
#ifndef DATAMODEL_H
namespace Atil { class DataModel; }
#endif
#ifndef INTERNAL_H
namespace Atil { class Internal; }
#endif
#ifndef FINDFILEINTERFACE_H
namespace Atil { class FindFileInterface; }
#endif

#ifndef IMAGEFORMATCODEC_H
#include "ImageFormatCodec.h"
#endif

#ifndef FILEREADDESCRIPTOR_H
#define FILEREADDESCRIPTOR_H

namespace Atil
{

// FileReadDescriptor is constructed by specifying the name of a file containing an image. 
// The file passed in to the FileReadDescriptor constructor should point to a valid file that contains 
// a readable image.
//
// The FileReadDescriptor class includes a static method, isDecodableFile(), which should be used 
// to determine whether a given file contains a readable image.
//
// Some image files can contain multiple images. In ATIL, we refer to each image within a single 
// file as a "frame". FileReadDescriptor can only refer to one frame at any one time. FileReadDescriptor 
// will return the number of frames contained in an open file, and will allow the user to select which 
// frame the FileReadDescriptor will refer to. 
//

/// <summary>
/// This is the ATIL class for reading data sources, mainly image files, to construct
/// and populate an <c>Atil::Image</c> with data.
/// </summary>
///
/// <remarks>
/// Once constructed, FileReadDesriptor provides access to the image data through
/// it's API. This class provides access to the image attributes as well as any 
/// custom properties that are exported by the format handler that is decoding the file. 
/// </remarks>
///
class FileReadDescriptor 
{
public:
    /// <summary>
    /// Describes the how the data from the referenced image was loaded.
    /// </summary>
    ///
    enum MethodType {
        /// <summary>
        /// This indicates that the data in the referenced image will be 
        /// copied into the internal store of ATIL.
        /// </summary>
        ///
        /// <remarks>
        /// An image can be "fully loaded" many different reasons. It is 
        /// the default mode for loading image data into an Atil::Image.
        /// </remarks>
        ///
        kFullRead, 

        /// <summary>
        /// This indicates that a constructed Atil::Image will directly
        /// reference the data in the referenced image pointed to by the 
        /// FileSpecifier.
        /// </summary>
        ///
        /// <remarks>
        /// Direct read can offer faster load times as the data in the file
        /// is not copied into ATIL. The requirements for direct loading 
        /// are strict however and the organization and type of data being
        /// loaded must match the organization and type of ATIL internal 
        /// <c>Atil::Image</c> data.
        /// </remarks>
        ///
        kDirectRead, 
        
        /// <summary>
        /// This indicates that the image file includes or can generate
        /// down scaled (smaller) copies of the image.
        /// </summary>
        ///
        /// <remarks>
        /// This indicates that the decoding codec offers an API that ATIL
        /// can use to request down scaled versions of the image when they
        /// are called for. In some cases this can speed scaling of the image.
        ///
        /// Codecs which offer this API most generally will also support
        /// <c>kDirectRead</c> as well as the files encoded in multiple 
        /// resolution formats can be large and prohibitive to copy at the
        /// full resolution as <c>kFullRead</c> would.
        /// </remarks>
        ///
        kMultipleResolution,

        /// <summary>
        /// This indicates that the codec can offer data from the image file
        /// in rectangular random access. 
        /// </summary>
        ///
        /// <remarks>
        /// Similar to <c>kDirectRead</c> partial loading will speed initial
        /// loading of the data into the <c>Atil::Image</c>. Rather than loading
        /// all the data in at one time, the <c>Atil::Image</c> will request
        /// regions of image data as they are required for operations until 
        /// all of the image data has been loaded. 
        /// </remarks>
        ///
        kPartialLoad, 

        /// <summary>
        /// This indicates that the data being loaded is a highly reduced
        /// resolution representation of the image in the image file.
        /// </summary>
        ///
        /// <remarks>
        /// This tag is useful for applications that would like to display
        /// small snapshots of an image on a dialog. Thumbnails are usually
        /// quite small and their quality varies greatly depending on the 
        /// size of the original image, it's type, and the creating application.
        /// </remarks>
        ///
        kThumbnail, 

        /// <summary>
        /// This tag indicates that the source of the image data is from
        /// a stream. 
        /// </summary>
        ///
        /// <remarks>
        /// Stream sources will always be fully loaded at <c>Atil::Image</c> 
        /// construction.
        /// </remarks>
        ///
        kStream
    };

public:
    /// <summary>
    /// This static method will use the codecs that have been registered through
    /// <c>Atil:ATILSettingsInterface::registerFormatCodec</c> and attempt to 
    /// discover the format codec that can read the source parameter.
    /// </summary>
    ///
    /// <param name="fs">
    /// The <c>FileSpecifier</c> refers to the image data file to be decoded. 
    /// </param>
    ///
    /// <param name="pIsThisCodec">
    /// This reference to an <c>ImageFormatCodec</c> pointer will be set with
    /// the codec that can decode the image data indicated by the FileSpecifier
    /// if a codec is found.
    /// </param>
    ///
    /// <returns>
    /// An entry of the <c>ImageFormatCodec::FormatDecodeability</c> enum
    /// the indicates the success of the search for a suitable codec.
    /// </returns>
    ///
    /// <remarks>
    /// This method will use the ATIL registered codecs and call each in turn
    /// in an attempt to discover which codec can decode the FileSpecifier. It
    /// uses isDecodableFile to do this and returns the decodability status. 
    /// This means that a subsequent call to isDecodable is redundant. Use the
    /// returned status for determining readability.
    /// </remarks>
    ///
    static ImageFormatCodec::FormatDecodability findImageFileCodec(const FileSpecifier& fs,
        const ImageFormatCodec*& pIsThisCodec);

    /// <summary>
    /// This static method can be used to verify that a given codec can be used to
    /// decode the given FileSpecifier specified image.
    /// </summary>
    ///
    /// <param name="fs">
    /// The <c>FileSpecifier</c> refers to the image data file to be decoded. 
    /// </param>
    ///
    /// <param name="useThisCodec">
    /// A pointer to an <c>ImageFormatCodec</c> pointer which will be used to
    /// test the decodability of the image file.
    /// </param>
    ///
    /// <returns>
    /// An entry of the <c>ImageFormatCodec::FormatDecodeability</c> enum
    /// the indicates if it is a suitable codec for decoding the image.
    /// </returns>
    ///
    /// <remarks>
    /// This is check should be used to ensure that the image data is de-codable
    /// by the codec before attempting to use them to construct the FileReadDescriptor.
    /// However, if the codec was determined with <c>findImageFileCodec</c> then
    /// using this method is redundant.
    /// </remarks>
    ///
    static ImageFormatCodec::FormatDecodability isDecodableFile (const FileSpecifier& fs,
        const ImageFormatCodec* useThisCodec);

    /// <summary>
    /// This constructor takes a minimal argument of only a FileSpecifier. If
    /// the FileSpecifier can not be decoded an exception is thrown.
    /// </summary>
    ///
    /// <param name="fs">
    /// The <c>FileSpecifier</c> refers to the image data file to be decoded. 
    /// </param>
    ///
    /// <remarks>
    /// This constructor will <c>throw</c> a <c>FileDescriptorException</c> instance
    /// if the FileSpecifier is not able to be decoded. It is recommended to either 
    /// catch the exception or pre-qualify the FileSpecifier
    /// <see cref="findImageFileCodec"/>.
    /// </remarks>
    ///
    FileReadDescriptor (const FileSpecifier& fs);

    /// <summary>
    /// This constructor takes arguments of a FileSpecifier and a FileFindInterface.
    /// The FileFindInterface may be used to aid in locating the file or supporting
    /// files for multi-file image formats. If the FileSpecifier can not be decoded
    /// an exception is thrown.
    /// </summary>
    ///
    /// <param name="fs">
    /// The <c>FileSpecifier</c> refers to the image data file to be decoded. 
    /// </param>
    ///
    /// <param name="pFindFile">
    /// The FileFindInterface is an application provided class that ATIL codecs may
    /// use to help locate additional files that may make up muti-file formats and or
    /// external correlation and meta-data.
    /// </param>
    ///
    /// <remarks>
    /// This constructor will <c>throw</c> a <c>FileDescriptorException</c> instance
    /// if the FileSpecifier is not able to be decoded. 
    /// </remarks>
    ///
    FileReadDescriptor (const FileSpecifier& fs, FindFileInterface* pFindFile );

    /// <summary>
    /// This constructor takes arguments of a FileSpecifier and an ImageFormatCodec 
    /// to decode the image data with. Since the codec is known then there will not 
    /// be any testing of the input file to discover the format codec to use. This makes
    /// this constructor the most efficient for opening an image where the format of that
    /// image is known.If the FileSpecifier can not be decoded with the provided codec an
    /// exception is thrown.
    /// </summary>
    ///
    /// <param name="fs">
    /// The <c>FileSpecifier</c> refers to the image data file to be decoded. 
    /// </param>
    ///
    /// <param name="useThisCodec">
    /// A pointer to an <c>ImageFormatCodec</c> pointer which will be used to
    /// decode the image file.
    /// </param>
    ///
    /// <remarks>
    /// This constructor will <c>throw</c> a <c>FileDescriptorException</c> instance
    /// if the FileSpecifier is not able to be decoded. It is recommended to either 
    /// catch the exception or pre-qualify the FileSpecifier
    /// <see cref="isDecodableFile"/>.
    /// </remarks>
    ///
    FileReadDescriptor (const FileSpecifier& fs, const ImageFormatCodec* useThisCodec);

    /// <summary>
    /// This constructor takes arguments of a FileSpecifier, a pointer to a codec
    /// to use for decoding the image, and a FileFindInterface. Since the codec
    /// is known then there will not be any testing of the input file to discover
    /// the format codec to use. This makes this constructor the most efficient for
    /// opening an image where the format of that image is known. The FileFindInterface
    /// may be used to aid in locating the file or supporting files for multi-file
    /// image formats. If the FileSpecifier can not be decoded an exception is thrown.
    /// </summary>
    ///
    /// <param name="fs">
    /// The <c>FileSpecifier</c> refers to the image data file to be decoded. 
    /// </param>
    ///
    /// <param name="useThisCodec">
    /// This reference to an <c>ImageFormatCodec</c> pointer will the codec to use to
    /// decode the image data indicated by the FileSpecifier.
    /// </param>
    ///
    /// <param name="pFindFile">
    /// The FileFindInterface is an application provided class that ATIL codecs may
    /// use to help locate additional files that may make up muti-file formats and or
    /// external correlation and meta-data.
    /// </param>
    ///
    /// <remarks>
    /// This constructor will <c>throw</c> a <c>FileDescriptorException</c> instance
    /// if the FileSpecifier is not able to be decoded.  It is recommended to either 
    /// catch the exception or pre-qualify the FileSpecifier
    /// <see cref="isDecodableFile"/>.
    /// </remarks>
    ///
    FileReadDescriptor (const FileSpecifier& fs, const ImageFormatCodec* useThisCodec,
        FindFileInterface* pFindFile);

    /// <summary>
    /// This constructor takes arguments of a FileSpecifier and a pointer to a codec
    /// to use for decoding the image. If the FileSpecifier can not be decoded an
    /// exception is thrown.
    /// </summary>
    ///
    /// <param name="pdsStream">
    /// The stream to read the encode image data from. 
    /// </param>
    ///
    /// <param name="useThisCodec">
    /// This reference to an <c>ImageFormatCodec</c> pointer will the codec to use to
    /// decode the image data indicated by the FileSpecifier.
    /// </param>
    ///
    /// <remarks>
    /// This constructor will <c>throw</c> a <c>FileDescriptorException</c> instance
    /// if the FileSpecifier is not able to be decoded.  It is recommended to either 
    /// catch the exception or pre-qualify the FileSpecifier
    /// <see cref="isDecodableFile"/>.
    /// </remarks>
    ///
    FileReadDescriptor (DataStreamInterface* pdsStream, const ImageFormatCodec* useThisCodec);

    /// <summary>
    /// The copy constructor.
    /// </summary>
    ///
    /// <param name="copyThis">
    /// A const reference to a <c>FileReadDescriptor</c> to initialize the constructed 
    /// instance.
    /// </param>
    ///
    FileReadDescriptor (const FileReadDescriptor& copyThis);

    /// <summary>
    /// The destructor.
    /// </summary>
    ///
    ~FileReadDescriptor ();

    /// <summary>
    /// Opens the FileReadDescriptor for use. The FileReadDescriptor will be open
    /// after construction and after calling <see cref="setFrame"/> to
    /// set the desired frame. <see cref="numFrames"/>
    /// </summary>
    ///
    void open () const;

    /// <summary>
    /// Closes the FileReadDescriptor.
    /// </summary>
    void close () const;
 
    /// <summary>
    /// Retrieve the FileSpecifier that specifies the image loaded by this object.
    /// </summary>
    ///
    /// <param name="fs">
    /// A reference to a <c>FileSpecifier</c> that will be set to the <c>FileSpecifier</c>
    /// of the object. 
    /// </param>
    ///
    void getFileSpecifier (FileSpecifier& fs) const;

    /// <summary>
    /// This method will return a pointer to the codec used to decode the image data.
    /// </summary>
    ///
    /// <returns>
    /// A constant pointer to the <c>ImageFormatCodec</c> that was the codec to
    /// decode the image data.
    /// </returns>
    ///
    const ImageFormatCodec* formatCodec () const;

    /// <summary>
    /// This will return the number of frames (or images) encoded within the "file".
    /// </summary>
    ///
    /// <returns>
    /// return the number of frames.
    /// </returns>
    ///
    /// <remarks>
    /// Some image formats can encode multiple images into a single file. Examples
    /// would be frames of animation, pages of a scanned book, or multiple ranges of
    /// spectra captured by satellite cameras of the same ground area.
    /// </remarks>
    ///
    int numFrames () const;

    /// <summary>
    /// This method will return the currently selected frame.<see cref="numFrames"/>
    /// </summary>
    /// 
    /// <returns>
    /// return the number of selected frames.
    /// </returns>
    ///
    int selectedFrame () const;

    /// <summary>
    /// This method will change the open frame to the frame index passed in. The 
    /// desired index must be greater than or equal to zero and less than the number
    /// of frames in the "file". <see cref="numFrames"/>
    /// </summary>
    ///
    /// <param name="frame"> 
    /// The index, starting at zero to numFrames - 1, to make the current one.
    /// </param>
    ///
    /// <returns>
    /// This returns a bool indicating if the selected frame was successfully opened.
    /// </returns>
    ///
    bool setFrame (int frame);

    /// <summary>
    /// Returns an instance of the <c>MethodType</c> enum corresponding to the method
    /// ATIL used to load the image data from the current frame.
    /// </summary>
    ///
    /// <returns>
    /// return the loaded FileReadDescriptor::MethodType.
    /// </returns>
    ///
    FileReadDescriptor::MethodType loadMethod () const;

    /// <summary>
    /// This method will return the size in pixels of the image data in the current frame.
    /// </summary>
    ///
    /// <param name="size">
    /// A reference to a <c>Atil::Size</c> object that will be set to the image size 
    /// in pixels.
    /// </param>
    ///
    /// <remarks>
    /// This is the size of the image in the pixels disregarding any format specified
    /// re-orientation of the image.
    /// </remarks>
    ///
    void getDataSize (Size& size) const;

    /// <summary>
    /// This method will return the size in pixels of the image data in the current frame.
    /// </summary>
    ///
    /// <remarks>
    /// This is the size of the 3d image in the pixels disregarding any format specified
    /// re-orientation of the image.
    /// </remarks>
    ///
    void getDataSize (int& nRows, int& nColumns, int& nDepths) const;
    
    /// <summary>
    /// This will return any format specified orientation of the image data.
    /// </summary>
    ///
    /// <returns>
    /// An entry of the <c>Atil::Orientation</c> enum describing the one of eight
    /// possible orientations that will be applied to the image as it is loaded.
    /// </returns>
    ///
    Atil::Orientation dataOrientation() const;

    /// <summary>
    /// This will return the loaded size of the image from the current frame 
    /// in pixels after the image is reoriented to Atil::Orientation::kTopDownLeftRight.
    /// </summary>
    ///
    /// <param name="size">
    /// A reference to a <c>Atil::Size</c> object that will be set to the image size 
    /// in pixels.
    /// </param>
    ///
    void getOrientedSize (Size& size) const;

    /// <summary>
    /// This will return the dataModel that represents the image.
    /// </summary>
    /// 
    /// <returns>
    /// A const reference to the datamodel utilized by the image data in the current frame.
    /// </returns>
    ///
    const DataModel& dataModel () const;

    /// <summary>
    /// This will retrieve a pointer to an instance of a property set iterator that
    /// can be used to iterate through properties for the current image frame.
    /// </summary>
    /// 
    /// <returns>
    /// This returns a pointer to an instance of a PropertySetIterator.
    /// </returns>
    ///
    FormatCodecPropertySetIterator* newPropertySetIterator () const;

    /// <summary>
    /// This will query for a specific property from the current frame of the image.
    /// </summary>
    ///
    /// <param name="id">
    /// An instance of the <c>FormatCodecPropertyInterface::PropertyIdentifier</c>
    /// that indicates a property type to return.
    /// </param>
    ///
    /// <returns>
    /// An instance of a <c>FormatCodecPropertyInterface</c> derived property that
    /// should be deleted by the caller. A NULL pointer will be returned if the requested
    /// property can not be found.
    /// </returns>
    ///
    FormatCodecPropertyInterface* getProperty ( FormatCodecPropertyInterface::PropertyIdentifier id ) const;

    /// <summary>
    /// This will query for a specific property from the current frame of the image.
    /// </summary>
    ///
    /// <param name="sbPropertyName">
    /// An instance of a <c>Atil::StringBuffer</c> that holds the name of the
    /// property type to return.
    /// </param>
    ///
    /// <returns>
    /// An instance of a <c>FormatCodecPropertyInterface</c> derived property that
    /// should be deleted by the caller. A NULL pointer will be returned if the requested
    /// property can not be found.
    /// </returns>
    ///
    FormatCodecPropertyInterface* getProperty ( StringBuffer sbPropertyName ) const;

    /// <summary>
    /// This will retrieve an instance of a class that implements the <c>RowProviderInterface</c>
    /// the data pipeline interface of ATIL. It will provide rows of data from the
    /// image in the file.
    /// </summary>
    ///
    /// <returns>
    /// An instance of class that implements the <c>RowProviderInterface</c> allowing
    /// access to rows of data from the image in the file.
    /// </returns>
    ///
    /// <exception cref="FormatCodecException">
    /// Individual image format readers may throw exceptions if they encounter format
    /// defined conditions of error such as corrupt files. Some encryption schemes 
    /// are extremely sensitive to corrupted data and therefore use exceptions or jumps
    /// to exit. <see cref="FormatCodecException"/>.
    /// </exception>
    ///
    /// <remarks>
    /// The rows returned from this call will not be re-oriented, but rather will reflect
    /// the rows of data as they are laid out in the image file. If the data needs to 
    /// be re-oriented that will be done by Atil::Image during image construction.
    /// </remarks>
    ///
     RowProviderInterface* read ();

    /// <summary>
    /// This method allows rows of data to be read from the image in the file at different
    /// resolutions. This method can be used to generate data for reduced resolution previews
    /// of the image often referred to as image thumbnails.
    /// </summary>
    ///
    /// <param name="dScale">
    /// A double value specifying a scaling value to be applied to the data returned 
    /// from the current selected frame.
    /// </param>
    ///
    /// <param name="filterMethod">
    /// An entry of the <c>Atil::Resample::FilterTypes</c> enum that indicates the re-sampling
    /// method to use.
    /// </param>
    ///
    /// <returns>
    /// An instance of class that implements the <c>RowProviderInterface</c> allowing
    /// access to rows of data from the image in the file.
    /// </returns>
    /// 
    /// <exception cref="FormatCodecException">
    /// Individual image format readers may throw exceptions if they encounter format
    /// defined conditions of error such as corrupt files. Some encryption schemes 
    /// are extremely sensitive to corrupted data and therefore use exceptions or jumps
    /// to exit. <see cref="FormatCodecException"/>.
    /// </exception>
    ///
    /// <remarks>
    /// The image data will be re-oriented to TopDownLeftRight orientation before it is return.
    /// </remarks>
    ///
     RowProviderInterface* scaledRead (const double& dScale, Resample::FilterTypes filterMethod);

    /// <summary>
    /// This will return the number of files in the load multi-file image set. This set will 
    /// include external correlation files as well as the files that comprise the image data.
    /// </summary>
    ///
    /// <returns>
    /// This will return the integer number of files that make up the image.
    /// </returns>
    ///
    int numClosureSetFiles () const;

    /// <summary>
    /// This will query the file names from an image that is composed or contained by within
    /// multiple files or sources.
    /// </summary>
    /// 
    /// <param name="nIndex">
    /// The integer index of the file or source name to return.
    /// <see cref="numClosureSetFiles"/>
    /// </param>
    ///
    /// <returns>
    /// This returns an <c>Atil::FileSpecifier</c> object that will hold the string
    /// that indicates the name or path of the source or file at the passed in index.
    /// </returns>
    ///
    FileSpecifier getClosureSetFilename (int nIndex) const;

private:
    FileReadDescriptorRep* mpImplementation;
    friend class Internal;
};

}

#endif
