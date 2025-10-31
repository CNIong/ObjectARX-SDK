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

#ifndef IMAGECONTEXT_H
#include "ImageContext.h"
#endif

#ifndef DATAMODEL_H
#include "DataModel.h"
#endif

#ifndef ATILEXCEPTION_H
#include "ATILException.h"
#endif

#ifndef SIZE_H
namespace Atil { class Size; }
#endif
#ifndef OFFSET_H
namespace Atil { class Offset; }
#endif
#ifndef STRINGBUFFER_H
namespace Atil { class StringBuffer; }
#endif
#ifndef IMAGEPIXEL_H
namespace Atil { struct ImagePixel; }
#endif
#ifndef ROWPROVIDERINTERFACE_H
namespace Atil { class RowProviderInterface; }
#endif
#ifndef FILEREADDESCRIPTOR_H
namespace Atil { class FileReadDescriptor; }
#endif
#ifndef FILEWRITEDESCRIPTOR_H
namespace Atil { class FileWriteDescriptor; }
#endif
#ifndef IMAGEREP_H
namespace Atil { class ImageRep; }
#endif
#ifndef INTERNAL_H
namespace Atil { class Internal; }
#endif

#ifndef IMAGE_H
#define IMAGE_H

namespace Atil
{
class ImageReactorInterface;

/// <summary>
/// The Image class is the core class of ATIL. All imagery handled by ATIL is represented 
/// by this class. It exposes methods to access the pixel values of the image through the
/// <c>ImageContext</c> class and through the return of a <c>RowProviderInterface</c> instance.
/// Each instance of the Image class has an instance of a <c>DataModel</c> based class 
/// that dictates the type of data stored as a pixel within the image.
/// </summary>
///
/// <remarks>
/// As the Image class is the representation of images in ATIL it is at the root of all
/// filter pipelines. The source for the <c>RowProviderInterface</c> connection is usually
/// an instance of that interface returned from the <c>Image::read(...)</c> method.
/// If the Image was constructed using a FileReadDescriptor then the image will retain
/// a copy of the descriptor that may be queried to recover information about the source
/// file of the image.
/// </remarks>
///
class Image 
{
public:
    friend class Internal;

    /// <summary>
    /// The empty or "NULL" constructor for an <c>Atil::Image</c>. 
    /// </summary>
    ///
    /// <remarks>
    /// An instance of an image created through this constructor is intended only to facilitate
    /// the later assignment of a valid image. The instance created through this constructor has
    /// no internal data that can be returned. Attempting access any data from a "NULL" image will
    /// result in an exception.
    /// </remarks>
    Image ();

    /// <summary>
    /// The clone constructor of the Image class allows the construction of a new instance based
    /// on an existing instance.
    /// </summary>
    ///
    /// <param name= 'image'>
    /// A const reference to the image to be copied.
    /// </param>
    ///
    /// <exception cref="ImageConstructionException">Thrown when the image can 
    /// not be cloned <see cref="ImageConstructionException"/>.
    /// </exception>
    ///
    /// <remarks>
    /// ATIL implements the Image class with a "letter - envelope" or "Bridge" 
    /// design pattern. See "Design Patterns, ISBN 0-201-63361-2". 
    /// </remarks>
    ///
    Image (const Image & image);

    /// <summary>
    /// The blank image constructor for an <c>Image</c>.
    /// </summary>
    ///
    /// <param name='size'>The size of the image to be created.</param>
    ///
    /// <param name='colorspace'>The DataModel of the image to be created.</param>
    ///
    /// <param name='initialColor'>The clear color of the image data.</param>
    ///
    /// <param name='sz'>The tile size to use for the image.
    /// The default, <c>DataModel::TileSize::kUnspecified</c> is recommended.
    /// </param>
    ///
    /// <exception cref="ImageConstructionException">An exception will be thrown
    ///  if the image can not be constructed. <see cref="ImageConstructionException"/>.
    /// </exception>
    ///
    Image (const Size& size, const DataModel* colorspace, ImagePixel initialColor,
        DataModel::TileSize sz = DataModel::kUnspecified);

    /// <summary>
    /// The user supplied buffer constructor for <c>Atil::Image</c>. This method of construction
    /// will wrap a user supplied buffer with the Image object allowing ATIL and the using
    /// application mutual access to the image data. Images created in this way are not memory managed.
    /// </summary>
    ///
    /// <param name='pData'>A pointer to the buffer that the image should use for its image 
    /// data storage. 
    /// </param>
    ///
    /// <param name='nBytesInBuffer'>An integer that describes the number of bytes
    /// that have been allocated in the <c>pData</c> parameter.
    /// </param>
    ///
    /// <param name='nBytesPerRow'>An integer that describes the number of bytes in 
    /// one row of the data. This sometimes referred to as the stride of the data. 
    /// The number of bytes from the beginning of one row to the beginning of the next row.
    /// </param>
    ///
    /// <param name='size'>The horizontal and vertical dimensions of the image. 
    /// The buffer in pData must be large enough to hold these dimensions.
    /// </param>
    ///
    /// <param name='pDm'>A constant pointer to a <c>DataModel</c> instance that 
    /// represents the data that will be contained in the image.
    /// </param>
    ///
    /// <exception cref="ImageConstructionException">An exception will be thrown
    ///  if the image can not be constructed. <see cref="ImageConstructionException"/>.
    /// </exception>
    ///
    Image (void* pData, int nBytesInBuffer, int nBytesPerRow, const Size& size, const DataModel* pDm);

    /// <summary>
    /// A <c>RowProviderInterface</c> based constructor for Image.
    /// </summary>
    ///
    /// <param name='pPipe'>A source of image data.
    /// </param>
    ///
    /// <param name='sz'>The tile size to be used for the image. 
    /// </param>
    ///
    /// <exception cref="ImageConstructionException">An exception will be thrown
    ///  if the image can not be constructed. <see cref="ImageConstructionException"/>.
    /// </exception>
    ///
    /// <remarks>
    /// This method will "consume" the <c>RowProviderInterface</c> and free the resources
    /// that it holds. The <c>RowProviderInterface</c> is no longer valid after using 
    /// it in this method.
    /// </remarks>
    ///
    Image (RowProviderInterface* pPipe,
        DataModel::TileSize sz = DataModel::kUnspecified);

    /// <summary>
    /// A <c>RowProviderInterface</c> based constructor for Image with the option.
    /// to reorient the input.
    /// </summary>
    ///
    /// <param name='pPipe'>A source of image data.
    /// </param>
    ///
    /// <param name='orient'>The orientation to apply to the image when storing
    /// the data in the image.
    /// </param>
    ///
    /// <param name='sz'>The tile size to be used for the image. 
    /// </param>
    ///
    /// <exception cref="ImageConstructionException">An exception will be thrown
    ///  if the image can not be constructed. <see cref="ImageConstructionException"/>.
    /// </exception>
    ///
    Image (RowProviderInterface* pPipe, Atil::Orientation orient,
        DataModel::TileSize sz = DataModel::kUnspecified);

    /// <summary>
    /// The <c>FileReadDescriptor</c> based constructor for Image. This is the constructor 
    /// to use when you want to load an image from a file.
    /// </summary>
    ///
    /// <param name='readDesc'>The <c>FileReadDescriptor</c> source of image data.
    /// </param>
    ///
    /// <param name='sz'>The tile size to be used for the image. 
    /// </param>
    ///
    /// <exception cref="ImageConstructionException">An exception will be thrown
    ///  if the image can not be constructed. <see cref="ImageConstructionException"/>.
    /// </exception>
    ///
    /// <remarks>
    /// The image will be constructed from the current frame set in the FileReadDescriptor. 
    /// </remarks>
    ///
    Image (FileReadDescriptor& readDesc,
        DataModel::TileSize sz = DataModel::kUnspecified);

    /// <summary>
    /// The destructor will release all image resources with the exception of
    /// user allocated buffers.
    /// </summary>
    ///
    ~Image ();

    /// <summary>
    /// The assignment operator will destroy the existing image data and make a reference
    /// to the assigned image data.
    /// </summary>
    ///
    /// <param name= 'image'>
    /// A const reference to the image to be assigned to <c>*this</c>.
    /// </param>
    ///
    /// <returns>
    /// This returns a reference to <c>*this</c>.
    /// </returns>
    ///
    const Image& operator= (const Image& image);

    /// <summary>
    /// The assignment operator will destroy the existing image data and construct a new
    /// image from the result of the <c>RowProviderInterface</c>.
    /// </summary>
    ///
    /// <param name="pPipe">An instance of a <c>RowProviderInterface</c> that will supply
    /// the pixel data to be drawn. The <c>RowProviderInterface</c> is consumed and freed.
    /// </param>
    ///
    /// <returns>
    /// This returns a reference to <c>*this</c>.
    /// </returns>
    ///
    /// <remarks>
    /// This method will "consume" the <c>RowProviderInterface</c> and free the resources
    /// that it holds. The <c>RowProviderInterface</c> is no longer valid after using 
    /// it in this method.
    /// </remarks>
    ///
  
    const Image& operator= (RowProviderInterface* pPipe);

    /// <summary>
    /// The equals operator.
    /// </summary>
    ///
    /// <param name= 'image'>
    /// A const reference to the image to be compared.
    /// </param>
    ///
    /// <returns>
    /// This will return true of both objects refer to the same data.
    /// </returns>
    ///
    /// <remarks>
    /// While this method is provided it is not considered a reliable method for 
    /// testing equality.
    /// </remarks>
    ///
    bool operator== (const Image& image) const;

    /// <summary>
    /// The not equals operator.
    /// </summary>
    ///
    /// <param name= 'image'>
    /// A const reference to the image to be compared.
    /// </param>
    ///
    /// <returns>
    /// This will return true of both objects do not refer to the same data.
    /// </returns>
    ///
    /// <remarks>
    /// While this method is provided it is not considered a reliable method for 
    /// testing equality.
    /// </remarks>
    ///  
    bool operator!= (const Image& image) const;

    /// <summary>
    /// This returns the size of the image in pixels. 
    /// </summary>
    ///
    /// <returns>
    /// This returns a const reference to a <c>Size</c> object.
    /// </returns>
    ///
    const Size& size () const;

    /// <summary>
    /// This returns the size of a tile of the image in pixels. 
    /// </summary>
    ///
    /// <returns>
    /// This returns a <c>Size</c> object.
    /// </returns>
    ///
    Size tileSize () const;

    /// <summary>
    /// This method returns a const reference to the images dataModel. It is useful
    /// for testing the qualities of an image. All images have a dataModel.
    /// </summary>
    ///
    /// <returns>
    /// This returns a const reference to the <c>DataModel</c> for the image.
    /// </returns>
    ///
    const DataModel& dataModel () const;

    /// <summary>
    /// This method will return the <c>FileReadDescriptor</c> used to create the image
    /// if the image was created with a <c>FileReadDescriptor</c>. The return will be 
    /// NULL otherwise.
    /// </summary>
    ///
    /// <returns>
    /// This returns a const pointer to the <c>FileReadDescriptor</c> if one was used 
    /// to construct the image and NULL if not.
    /// </returns>
    ///
    const FileReadDescriptor* fileReadDescriptor () const;

    /// <summary>
    /// This method will return the number of tiles in the image. There is always
    /// at least one tile in a valid image.
    /// </summary>
    ///
    /// <param name="nRows">A integer reference which will be set to the number of
    /// tiles used to hold a row of the image.
    /// </param>
    ///
    /// <param name="nColumns">A integer reference which will be set to the number of
    /// tiles used to hold a column of the image.
    /// </param>
    ///
    /// <returns>
    /// This returns the number of tiles in the image.
    /// </returns>
    ///
    int numTiles (int& nRows, int& nColumns) const;

    /// <summary>
    /// This method returns the clear color of the image.
    /// </summary>
    ///
    /// <returns>
    /// This returns a const reference to th <c>ImagePixel</c> that holds the clear color.
    /// </returns>
    ///
    const ImagePixel& clearColor () const;

    /// <summary>
    /// A new data model may be set onto an image through this method. The datamodel being
    /// set must be compatible with the number of bands and band width of the image data.
    /// </summary>
    ///
    /// <param name='dataModel'>A constant reference to a <c>DataModel</c> instance that 
    /// will be used as the representation of the data.
    /// </param>
    ///
    /// <exception cref="ImageConstructionException">An exception will be thrown
    /// if the data type of the image is incompatible with the data model instance being set
    /// <see cref="ImageConstructionException"/>.
    /// </exception>
    ///
    void setDataModel ( const DataModel& dataModel );
    
    /// <summary>
    /// This method will set the Image's clear color. 
    /// </summary>
    ///
    /// <param name="value">An <c>ImagePixel</c> that holds the color to be 
    /// used as the clear color.
    /// </param>
    ///
    /// <exception cref="ImageException">An exception will be thrown if the pixel type of the
    /// parameter is incompatible with the data model image <see cref="ImageException"/>.
    /// </exception>
    ///
    /// <remarks>
    /// The clear color is the color that will be return for any pixel which is not
    /// set with a value by the constructed image. 
    /// </remarks>
    ///
    void setClearColor ( ImagePixel value );

    /// <summary>
    /// Use this method to draw pixels from the <c>RowProviderInterface</c> into the image
    /// at the specified location.
    /// </summary>
    ///
    /// <param name="pPipe">An instance of a <c>RowProviderInterface</c> that will supply
    /// the pixel data to be drawn. The <c>RowProviderInterface</c> is consumed and freed.
    /// </param>
    ///
    /// <param name="at">The offset, in pixels, to the upper left corner at which the
    /// first pixel of the first row from the <c>RowProviderInterface</c> will be drawn.
    /// </param>
    ///
    /// <param name="bRespectTransparency">A defaulted(false) boolean that if true will
    /// cause pixels that have an alpha of 0 not to be drawn.
    /// </param>
    ///
    /// <remarks>
    /// This method will "consume" the <c>RowProviderInterface</c> and free the resources
    /// that it holds. The <c>RowProviderInterface</c> is no longer valid after using 
    /// it in this method.
    /// </remarks>
    ///
    void paste (RowProviderInterface* pPipe, const Offset& at, bool bRespectTransparency = false);
    
    /// <summary>
    /// Use this method to draw pixels into an image from the passed in <c>RowProviderInterface</c>
    /// drawing the data with the specified alpha value.
    /// </summary>
    ///
    /// <param name="pPipe">An instance of a <c>RowProviderInterface</c> that will supply
    /// the pixel data to be drawn. The <c>RowProviderInterface</c> is consumed and freed.
    /// </param>
    ///
    /// <param name="at">The offset, in pixels, to the upper left corner at which the
    /// first pixel of the first row from the <c>RowProviderInterface</c> will be drawn.
    /// </param>
    ///
    /// <param name="nAlphaValue">The input alpha range should vary between 1 and 254.
    /// </param>
    ///
    /// <param name="bRespectTransparency">A defaulted(false) boolean that if true will
    /// cause pixels that have an alpha of 0 not to be drawn.
    /// </param>
    ///
    /// <exception cref="ImageException">An exception will be thrown if the image does
    /// not have a RGB data model <see cref="ImageException"/>.
    /// </exception>
    ///
    /// <remarks>
    /// This works like the <c>paste()</c> method except that it alpha blends the
    /// input rows into the image. 
    /// Like <c>paste()</c> it will "consume" the <c>RowProviderInterface</c> and
    /// free the resources that it holds. The <c>RowProviderInterface</c> is no longer
    /// valid after using it in this method.
    /// </remarks>
    ///
    void blend (RowProviderInterface* pPipe, const Offset& at, int nAlphaValue
        , bool bRespectTransparency = false);

    /// <summary>
    /// This will read a sub-rectangle of data from the image returning it in a
    /// <c>RowProviderInterface</c> instance.
    /// </summary>
    /// 
    /// <param name="size">The size of the sub-region of the image to be read which may
    /// be up to the full size of the image. 
    /// </param>
    ///
    /// <param name="offset">The pixel offset from the upper left corner of the image
    /// to begin reading the requested <c>size</c> region.
    /// </param>
    /// 
    /// <returns>
    /// An instance of a <c>RowProviderInterface</c> that will supply the data within
    /// the requested region.
    /// </returns>
    /// 
    /// <remarks>
    /// The requested sub-region must be within the bounds of the image.
    /// </remarks>
    ///
    RowProviderInterface* read (const Size& size, const Offset& offset) const;

    // Orientation is an enum containing the 8 different read orientations.
    /// <summary>
    /// This will read a sub-rectangle of data from the image returning it in a
    /// <c>RowProviderInterface</c> instance. The data from the image will be
    /// re-oriented from TopDownLeftRight (normal progression) to the orientation 
    /// passed in. 
    /// </summary>
    /// 
    /// <param name="size">The size of the sub-region of the image to be read which may
    /// be up to the full size of the image. 
    /// </param>
    ///
    /// <param name="offset">The pixel offset from the upper left corner of the image
    /// to begin reading the requested <c>size</c> region.
    /// </param>
    /// 
    /// <param name="orient">The orientation to be applied to the data before it is
    /// returned.
    /// </param>
    ///
    /// <returns>
    /// An instance of a <c>RowProviderInterface</c> that will supply the data within
    /// the requested region.
    /// </returns>
    /// 
    /// <remarks>
    /// The requested sub-region must be within the bounds of the image.
    /// </remarks>
    ///
    RowProviderInterface* read (const Size& size, const Offset& offset,
        Atil::Orientation orient) const;

    /// <summary>
    /// This method constructs an <c>ImageContext</c> <see cref="ImageContext"/> that
    /// maybe used to access the pixels of an image directly. 
    /// </summary>
    ///
    /// <param name="accessNeeded">An <c>ImageContext</c> can be opened for either
    /// kRead or kWrite access. ImageContexts opened with kWrite do not cache (internally) 
    /// as aggressively as those opened with kRead.  
    /// </param>
    /// 
    /// <param name="numTilesToCache">The number of tiles to cache internal to the 
    /// <c>ImageContext</c>. The default of 4 should be sufficient for most usages.
    /// </param>
    ///
    /// <returns>
    /// This will return either a pointer to a valid <c>ImageContext</c><see cref="ImageContext"/>
    /// or NULL if the method fails. The returned object must be freed when the caller
    /// is finished with it. 
    /// </returns>
    ///
    /// <remarks>
    /// An <c>ImageContext</c> holds tiles while it exists. They should be delete'd when
    /// not in use to free the resources that it holds.
    /// </remarks>
    ///
    ImageContext* createContext (ImageContext::Access accessNeeded, int numTilesToCache = 4 );

    /// <summary>
    /// This method constructs an <c>ImageContext</c> <see cref="ImageContext"/> that
    /// maybe used to access the pixels of an image directly. 
    /// </summary>
    ///
    /// <param name="accessNeeded">An <c>ImageContext</c> can be opened for either
    /// kRead or kWrite access. ImageContexts opened with kWrite do not cache (internally) 
    /// as aggressively as those opened with kRead.  
    /// </param>
    /// 
    /// <param name="size">The size of the sub-region of the image to be accessed by the
    /// context. 
    /// </param>
    ///
    /// <param name="offset">The pixel offset from the upper left corner of the image
    /// of the requested <c>size</c> region.
    /// </param>
    /// 
    /// <param name="numTilesToCache">The number of tiles to cache internal to the 
    /// <c>ImageContext</c>. The default of 4 should be sufficient for most usages.
    /// </param>
    ///
    /// <returns>
    /// This will return either a pointer to a valid <c>ImageContext</c><see cref="ImageContext"/>
    /// or NULL if the method fails. The returned object must be freed when the caller
    /// is finished with it. 
    /// </returns>
    ///
    /// <remarks>
    /// An <c>ImageContext</c> holds tiles while it exists. They should be delete'd when
    /// not in use to free the resources that it holds.
    /// </remarks>
    ///
    ImageContext* createContext (ImageContext::Access accessNeeded,
        const Size& size, const Offset& offset, int numTilesToCache = 4 );

    /// <summary>
    /// Adds a reactor that will call the owner whenever a tile is saved. 
    /// When a tile is saved, it is assumed to have been edited (written to). 
    /// </summary>
    /// 
    /// <param name="pReactor">An instance of a reactor to be added to the image.
    /// </param>
    ///
    /// <remarks>
    /// The <c>ImageReactorInterface</c><see cref="ImageReactorInterface"/> 
    /// can be derived from to track changes in the image.
    /// </remarks>
    ///
    void addReactor ( ImageReactorInterface* pReactor );

    /// <summary>
    /// Removes the reactor that had previously been added to the image.
    /// </summary>
    /// 
    /// <param name="pReactor">The instance of a reactor to be removed from the image.
    /// </param>
    ///
    void removeReactor ( ImageReactorInterface* pReactor );

    /// <summary>
    /// This method disables per tile locking. ATIL implements per tile locking for
    /// read and write. This option is provided as an optimization for instances in
    /// which a developer can guarantee single-threaded usage. Use it carefully.
    /// </summary>
    ///
    /// <param name= 'bDisable'>
    /// The boolean will disable per tile locking if set to true.
    /// </param>
    ///
    /// <returns>
    /// This will return true if per tile locking is disabled.
    /// </returns>
    ///
    bool disablePerTileLocking ( bool bDisable );

    /// <summary>
    /// This method will cause all pixels of the image to be set to the image's
    /// internal clear color.
    /// </summary>
    ///
    void clear ();

    /// <summary>
    /// This method will return true if there is valid data within the image.
    /// </summary>
    ///
    /// <returns>
    /// This will return true if the image is valid.
    /// </returns>
    ///
    bool isValid () const;

    /// <summary>
    /// This method will be set to true if data has been set into the image 
    /// after construction. There is no way to reset it.
    /// </summary>
    ///
    /// <returns>
    /// This will return true if the image has been written to.
    /// </returns>
    ///
    bool isModified () const;

    /// <summary>
    /// This method will return true if the "user buffer" method of construction
    /// was used to create the image.
    /// </summary>
    ///
    /// <returns>
    /// This will return true if a "user buffer" was use to construct the image.
    /// </returns>
    ///
    bool usesUserBuffer () const;

    /// <summary>
    /// This method will return a pointer to the "user buffer" used to construct
    /// the image.
    /// </summary>
    ///
    /// <returns>
    /// This will return the "user buffer" pointer used to construct the image.
    /// </returns>
    void* getUserBuffer ();

private:
    ImageRep* mImplementation;
};

/// <summary>
/// This class defines a single abstract method that acts an interface that can
/// be called by an image. It provides a way for a developer to track the changes
/// made to an image on a per tile basis.
/// </summary>
///
class ImageReactorInterface
{
public:
    /// <summary>
    /// Virtual destructor.
    /// </summary>
    virtual ~ImageReactorInterface();

    /// <summary>
    /// The abstract method that will be called when a tile is modified.
    /// </summary>
    ///
    /// <param name='row'> The row of the modified tile. </param>
    ///
    /// <param name='column'> The column of the modified tile. </param>
    ///
    virtual void onModified( int row, int column );
};


/// <summary>
/// A specialization of the <c>ATILException</c> class used during construction of images.
/// </summary>
/// 
/// <remarks>
/// This class is constructed and used by ATIL to indicate errors in usage of
/// ATIL APIs. The member values are intended as debugging aids and do not contain
/// information that should be displayed to the product user.
/// </remarks>
///
class ImageConstructionException : public ATILException 
{
public:
    /// <summary> An enum defines for exception types.
    /// </summary>
    enum ExceptionType { 
        /// <summary> This entry indicates a specific type of error.</summary>
        kIncompatibleTileSize,
        /// <summary> This entry indicates a specific type of error.</summary>
        kInvalidClearColor,
        /// <summary> This entry indicates a specific type of error.</summary>
        kInvalidSize,
        /// <summary> This entry indicates a specific type of error.</summary>
        kNonClonal,
        /// <summary> This entry indicates a specific type of error.</summary>
        kUnsafeClone,
        /// <summary> This entry indicates a specific type of error.</summary>
        kInsufficentStorage,
        /// <summary> This entry indicates a specific type of error.</summary>
        kInvalidRowAlignment,
        /// <summary> This entry indicates a specific type of error.</summary>
        kInvalidData,
        /// <summary> This entry indicates a general type of error.</summary>
        kUnSpecified
    };

public:

    /// <summary>
    /// The initializing constructor.
    /// </summary>
    ///
    /// <param name="sbMessage">
    /// An English ASCII debugging information message.
    /// </param>
    ///
    /// <param name="type">
    /// An enum value that indicates the reason for the exception.
    /// </param>
    ///
    ImageConstructionException (const StringBuffer& sbMessage,
        ExceptionType type = ImageConstructionException::kUnSpecified);

    /// <summary>
    /// Copy constructor
    /// </summary>
    ///
    /// <param name="x">
    /// A const instance to reference for initialization of the object.
    /// </param>
    ///
    ImageConstructionException (const ImageConstructionException& x);

    /// <summary>
    /// Virtual destructor.
    /// </summary>
    ///
    virtual ~ImageConstructionException ();

    /// <summary>
    /// This method will return a <c>ExceptionType</c> enum value indicating the
    /// the reason for the exception.
    /// </summary>
    ///
    /// <returns>
    /// This returns a member of the <c>ExceptionType</c> enum.
    /// </returns>
    ///
    virtual ExceptionType getExceptionType ();

private:
    ExceptionType eType;
};

/// <summary>
/// A specialization of the <c>ATILException</c> class used for errors after construction of images.
/// </summary>
///
class ImageException : public ATILException 
{
public:
    /// <summary> An enum defines for exception types.
    /// </summary>
    enum ExceptionType { 
        /// <summary> This entry indicates a specific type of error.</summary>
        kInvalidSubRegion, 
        /// <summary> This entry indicates a specific type of error.</summary>
        kIncompatibleDataModel,
        /// <summary> This entry indicates a specific type of error.</summary>
        kUnableToRegisterReactor, 
        /// <summary> This entry indicates a specific type of error.</summary>
        kInvalidBlendTarget, 
        /// <summary> This entry indicates a specific type of error.</summary>
        kInvalidPixelType,
        /// <summary> This entry indicates a specific type of error.</summary>
        kNullConstruction,
        /// <summary> This entry indicates a general type of error.</summary>
        kUnSpecified
    };
public:
    /// <summary>
    /// The initializing constructor.
    /// </summary>
    ///
    /// <param name="sbMessage">
    /// An English ASCII debugging information message.
    /// </param>
    ///
    /// <param name="type">
    /// An enum value that indicates the reason for the exception.
    /// </param>
    ///
    ImageException (const StringBuffer& sbMessage,
        ExceptionType type = ImageException::kUnSpecified);

    /// <summary>
    /// Copy constructor
    /// </summary>
    ///
    /// <param name="x">
    /// A const instance to reference for initialization of the object.
    /// </param>
    ///
    ImageException (const ImageException& x);

    /// <summary>
    /// Virtual destructor.
    /// </summary>
    ///
    virtual ~ImageException ();

    /// <summary>
    /// This method will return a <c>ExceptionType</c> enum value indicating the
    /// the reason for the exception.
    /// </summary>
    ///
    /// <returns>
    /// This returns a member of the <c>ExceptionType</c> enum.
    /// </returns>
    ///
    virtual ExceptionType getExceptionType ();

private:
    ExceptionType eType;
};

} // end of namespace Atil

#endif

#ifndef IMAGE_INL
#include "Image.inl"
#endif

