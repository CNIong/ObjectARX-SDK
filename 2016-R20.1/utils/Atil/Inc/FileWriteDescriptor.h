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
#ifndef DATASTREAMINTERFACE_H
namespace Atil { class DataStreamInterface; }
#endif
#ifndef SIZE_H
namespace Atil { class Size; }
#endif
#ifndef FILESPECIFIER_H
namespace Atil { class FileSpecifier; }
#endif
#ifndef DATAMODEL_H
namespace Atil { class DataModel; }
#endif
#ifndef ROWPROVIDERINTERFACE_H
namespace Atil { class RowProviderInterface; }
#endif
#ifndef IMAGEFORMATCODEC_H
namespace Atil { class ImageFormatCodec; }
#endif
#ifndef FORMATCODECPROPERTYSETITERATOR_H
namespace Atil { class FormatCodecPropertySetIterator; }
#endif
#ifndef FILEREADDESCRIPTOR_H
namespace Atil { class FileReadDescriptor; }
#endif
#ifndef INTERNAL_H
namespace Atil { class Internal; }
#endif
#ifndef FILEWRITEDESCRIPTORREP_H
namespace Atil { class FileWriteDescriptorRep; }
#endif

#ifndef FILEWRITEDESCRIPTOR_H
#define FILEWRITEDESCRIPTOR_H

namespace Atil
{
/// <summary>
/// This is the class that is used to encode image data into specific image file formats.
/// </summary>
///
/// <remarks>
/// FileWriteDescriptor is bound to a format when it is constructed. Once constructed, 
/// the format to be written is fixed. Therefore, it is recommended that the 
/// ImageFormatCodec derived encoder selected is compatible with the image or
/// images that are to be encoded.
///
/// The is an order to the use of the methods of the class. Using the methods and
/// supplying the needed information at each step is required for successful writing.
///
/// 1) Select a codec. There are static methods to check compatibility of images and
///    codecs <c>isCompatibleFormatCodec</c>.
///
/// 2) Construct the <c>FileWriteDescriptor</c> with the compatible codec.
///
/// 3) Select a file name and be certain that it can be written to (file does
///    not already exist, writeable destination, etc). Set this filename into
///    <c>setFileSpecifier</c>.
///
/// 4) Use the <c>createImageFrame</c> method with the data attributes of the image
///    data to be saved.
///
/// 5) Set properties (compression, dataorganization, etc) that govern the 
///    organization and other attributes of the image data and it's encoding.
///
/// 6) Check to be certain that any required properties needed by the codec
///    to properly encoded the data have been set with <c>requiredPropertiesSet</c>
///    and loop through the properties to set any that are needed.
///
/// 7) Use <c>writeImageFrame</c> providing the stream of data to be encoded into
///    the frame in the file. This closes the current frame.
/// 
/// 8) Delete the <c>FileWriteDescriptor</c>. This closes the file. Alternately,
///    loop back to step 4 and write another image into another frame in the image,
///    if the codec supports multiple images in a single file.
/// </remarks>
///
class FileWriteDescriptor 
{
public:
    /// <summary>
    /// This static method allows the developer to check if a given image
    /// can be encoded (to a file) with a given <c>ImageFormatCodec</c> instance.
    /// </summary>
    ///
    /// <param name="codec"> A const pointer to an <c>ImageFormatCodec</c> that 
    /// is the codec to test for 
    /// </param>
    ///
    /// <param name="dataModel"> A const pointer to a <c>DataModel</c> that describes the
    /// type of image data to be encoded.
    /// </param>
    ///
    /// <param name="size"> The size of the image data to be encoded.
    /// </param>
    ///
    /// <returns>
    /// This method returns true if the codec is compatible with the image data.
    /// </returns>
    ///
    static bool isCompatibleFormatCodec (const ImageFormatCodec* codec,
        const DataModel* dataModel, Size size);

    /// <summary>
    /// This static method will return an array of <c>ImageFormatCodec</c> 
    /// instances that can encode the image data.
    /// </summary>
    ///
    /// <param name="cpDataModel"> A const pointer to a <c>DataModel</c> that describes the
    /// type of image data to be encoded.
    /// </param>
    ///
    /// <param name="size"> A const reference to a <c>Size</c> instance holding
    /// the pixel size of the image data to be encoded.
    /// </param>
    ///
    /// <param name="codecs"> A reference to an array of <c>const ImageFormatCodec*</c>
    /// that will be set to the registered codecs that can encoded the data. The 
    /// array should be deallocated with "delete []" when finished. 
    /// </param>
    ///
    /// <param name="numCodecs"> A reference to an integer that will be set 
    /// to the number of codecs within the codec array.
    /// </param>
    ///
    /// <remarks>
    /// This method uses the list of <c>ImageFormatCodecs</c> that have been 
    /// registered with the <c>ATILSettingsInterface::registerFormatCodec</c>
    /// method. This is generally done when initializing ATIL 
    /// <see cref="ATILSettingsInterface"/>.
    /// </remarks>
    ///
    static void getCompatibleFormatCodecs (const DataModel* cpDataModel,
        const Size& size, const ImageFormatCodec**& codecs, int& numCodecs);

public:
    friend class Internal;

    /// <summary> The constructor of <c>FileWriteDescriptor</c> is bound to 
    /// and encoding <c>ImageFormatCodec</c>. 
    /// </summary>
    ///
    /// <param name='pCodec'>the FormatCodec that will be used to create the file.
    /// </param>
    ///
    /// <remarks>
    /// As the constructor requires the <c>ImageFormatCodec</c> that will be
    /// used to encode the data, it is recommended to check compatibility of the
    /// image data and the codec before selecting the codec to construct this
    /// object. <see cref="isCompatibleFormatCodec"/>. 
    /// </remarks>
    ///
    FileWriteDescriptor (const ImageFormatCodec* pCodec);

    /// <summary>
    /// The destructor.
    /// </summary>
    ///
    virtual ~FileWriteDescriptor ();

    /// <summary>
    /// This method will return the <c>ImageFormatCodec</c> that was selected
    /// to encode the image data.
    /// </summary>
    ///
    ///
    /// <returns> Returns a pointer to ImageFormatCodec type object after formatCodec. </returns>
    ///
    const ImageFormatCodec* formatCodec () const;    

    /// <summary>
    /// This method will return the <c>FileSpecifier</c> naming the location
    /// to write the encoded data to. This is most often a file name.
    /// </summary>
    /// 
    /// <param name="fs"> A reference to a <c>FileSpecifier</c> that will be set
    /// to the path information for saving the image data.
    /// </param>
    ///
    /// <remarks>
    /// If a <c>FileSpecifier</c> has not been set by <see cref="setFileSpecifier"/>
    /// then the method will set the <c>FileSpecifier</c> to NULL.
    /// </remarks>
    ///
    void getFileSpecifier (FileSpecifier& fs) const;

    /// <summary>
    /// This method is used to set the <c>FileSpecifier</c> that holds the path
    /// and filename that the encoded image data will be written.
    /// </summary>
    /// 
    /// <param name='fs'> A const reference to a <c>FileSpecifier</c> instance.
    /// </param>
    /// 
    /// 
    /// <returns> Return true on success. </returns>
    ///
    /// <remarks>
    /// The file specified in the <c>FileSpecifier</c> should not exist and
    /// the path must be write able. The method will return false if the file
    /// can not be created at the specified location.
    /// </remarks>
    ///
    bool setFileSpecifier (const FileSpecifier& fs);

    /// <summary> 
    /// An alternate method of outputting codec data. Passing a 
    /// <c>DataStreamInterface</c> <see cref="DataStreamInterface"/> derived class instance. 
    /// </summary>
    ///
    /// <param name='pdsStream'> DataStreamInterface implementation to receive the
    /// encoded image data.
    /// </param> 
    ///
    /// <remarks>
    /// This method allows the developer (through a callback) to store the encoded data. 
    /// The interface class will be called with "chunks" of data to be "written". Not all 
    /// <c>ImageFormatCodec</c> implementations support streaming. The <c>ImageFormatCodec</c>
    /// base class includes methods for testing support for select features in
    /// <c>ImageFormatCodec</c> instances.
    /// </remarks>
    ///
    void setOutputStream (DataStreamInterface* pdsStream);

    /// <summary>
    /// This method is used to establish a frame in the encoded image file.
    /// To ensure success call the static method <c>isCompatibleFormatCodec</c>
    /// before attempting to create the image frame.
    /// </summary>
    ///
    /// <param name="dataModel">A const reference to the <c>DataModel</c> of the
    /// image data to be encoded.
    /// </param>
    ///
    /// <param name="size">An instance of the <c>Size</c> object that holds the
    /// pixel dimensions of the image data to be encoded.
    /// </param>
    ///
    /// <exception cref="FormatCodecException">Thrown if the parameters describe
    /// an image type that can not be written or is not supported for writing.
    /// <see cref="FormatCodecException"/>.
    /// </exception>
    ///
    /// <remarks>
    /// Some image formats can encoded multiple images into a single file. ATIL
    /// represents each image in a file as a "frame". This method is used to
    /// create a frame within the image file. Although most formats can encode
    /// only a single image this multi-image "frame" based API is still used.
    /// By requiring the datamodel and size to be encoded into the frame, the
    /// basic information about what is being encoded will be used by the codec
    /// to create the "properties" that can be set. 
    /// </remarks>
    /// 
    void createImageFrame (const DataModel& dataModel, Size size);

    /// <summary>
    /// This query will return the status of image frame being encoded with respect
    /// to the properties that need to be set into the frame before writing data into
    /// it.
    /// </summary>
    /// 
    /// 
    /// <returns> Return true on success. </returns>
    ///
    /// <remarks>
    /// Calling this method before <c>writeImageFrame</c> is recommended. Codecs 
    /// may require some <c>FormatCodecPropertyInterface</c> derived "properties"
    /// to be set before the data can be encoded. All "properties" have some form
    /// of default value, using a <c>FormatCodecPropertySetIterator</c> to loop
    /// through the available properties and test each to determine the required
    /// properties and set them into the frame is relatively straightforward.
    /// </remarks>
    ///
    bool requiredPropertiesSet () const;

    /// <summary>
    /// Use this method to retrieve a <c>FormatCodecPropertySetIterator</c> that
    /// will contain all valid "properties" for the current frame to be written.
    /// </summary>
    /// 
    /// <returns>
    /// This method returns a pointer to a <c>FormatCodecPropertySetIterator</c>
    /// that should be released with [delete] when finished with it. The iterator
    /// iterates over the set of usable properties for the image frame being
    /// encoded.
    /// </returns>
    ///
    FormatCodecPropertySetIterator* newPropertySetIterator ();

    /// <summary>
    /// This method retrieves a pointer to a <c>FormatCodecPropertyInterface</c>
    /// instance requested by an enum entry declared in <c>FormatCodecPropertyInterface</c>.
    /// </summary>
    ///
    /// <param name="id"> An entry from the <c>FormatCodecPropertyInterface::PropertyIdentifier</c>
    /// enum.
    /// </param>
    ///
    /// <returns>
    /// This method returns a pointer to an instance of a <c>FormatCodecPropertyInterface</c>
    /// derived class. The method will return NULL (0) if the codec does not support
    /// the property indicated by the parameter. If the method returns a valid pointer
    /// then the object should be released with the "delete" operator when finished.
    /// </returns>
    ///
    FormatCodecPropertyInterface* getProperty (FormatCodecPropertyInterface::PropertyIdentifier id) const;

    /// <summary>
    /// This method retrieves a pointer to a <c>FormatCodecPropertyInterface</c>
    /// instance requested by string used as a "name".
    /// </summary>
    ///
    /// <param name="sbPropertyName"> An instance of the <c>StringBuffer</c> class
    /// that holds the name of the property specific to the codec in use to return.
    /// </param>
    ///
    /// <returns>
    /// This method returns a pointer to an instance of a <c>FormatCodecPropertyInterface</c>
    /// derived class. The method will return NULL (0) if the codec does not support
    /// the property indicated by the name. If the method returns a valid pointer
    /// then the object should be released with the "delete" operator when finished.
    /// </returns>
    ///
    /// <remarks>
    /// Using a string "name" is a method to retrieve codec defined properties
    /// that can not be identified with <c>FormatCodecPropertyInterface::PropertyIdentifier</c>.
    /// The use of this method requires knowledge specific to the codec in use
    /// and the names of the properties it exports. 
    /// </remarks>
    ///
    FormatCodecPropertyInterface* getProperty (StringBuffer sbPropertyName) const;

    /// <summary>
    /// This method sets a <c>FormatCodecPropertyInterface</c> instance into the
    /// current Image Frame being encoded.
    /// </summary>
    /// 
    /// <param name="pProperty"> A const instance of a <c>FormatCodecPropertyInterface</c>
    /// derived class.
    /// </param>
    /// 
    /// <returns>
    /// This method returns true if the property is set for inclusion in the frame
    /// being written.
    /// </returns>
    ///
    /// <remarks>
    /// Setting properties can change the defaults of other properties. The
    /// <c>FormatCodecPropertyInterface::isContextSensitive()</c> method indicates
    /// whether a given properties values can change based on other properties that
    /// are set into the frame being written.
    /// </remarks>
    ///
    bool setProperty (const FormatCodecPropertyInterface* pProperty);

    /// <summary>
    /// This method will set all the properties from a source <c>FileReadDescriptor</c>.
    /// </summary>
    ///
    /// <param name="fd"> A constant pointer to a <c>FileReadDescriptor</c> instance.
    /// </param>
    ///
    /// <returns>
    /// The method will return true if any property from the <c>FileReadDescriptor</c>
    /// can be successfully set into the current frame being encoded.
    /// </returns>
    ///
    /// <remarks>
    /// This method is not recommend except for the special case of making a copy
    /// of a file. The properties valid for one image are not necessarily valid
    /// for the image being encoded.
    /// </remarks>
    ///
    bool setProperties (const FileReadDescriptor* fd);

    /// <summary>
    /// This method set the image data to be encoded in the frame. It is the final
    /// step in encoding an image frame into the image file.
    /// </summary>
    ///
    /// <param name="pPipe"> An instance of a <c>RowProviderInterface</c> derived
    /// class that will supply the image data described in <c>createImageFrame</c>.
    /// </param>
    ///
    /// <returns>
    /// This method will return the integer index of the frame that has been 
    /// written.
    /// </returns>
    ///
    /// <remarks>
    /// This method closes the frame created when <c>createImageFrame</c> by
    /// sending in the data to be encoded. It is not possible to <c>setProperties</c>
    /// into the frame after the data has been set into it.
    /// </remarks>
    ///
    int writeImageFrame (RowProviderInterface* pPipe);

    /// <summary>Commits any pending writes and closes the written file </summary>
    /// <remarks>This is also called at class destruction.</remarks>
    virtual void closeFile();

private:
    FileWriteDescriptorRep* mpImplementation;
};

} // end of namespace Atil

#endif

