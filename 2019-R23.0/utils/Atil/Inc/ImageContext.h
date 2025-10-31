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
#ifndef DATAMODELATTRIBUTES_H
#include "DataModelAttributes.h"
#endif

#ifndef SIZE_H
namespace Atil { class Size; }
#endif
#ifndef OFFSET_H
namespace Atil { class Offset; }
#endif
#ifndef IMAGEPIXEL_H
namespace Atil { struct ImagePixel; }
#endif
#ifndef PIXELSELECTORINTERFACE_H
namespace Atil { class PixelSelectorInterface; }
#endif
#ifndef IMAGECONTEXTREP_H
#include "ImageContextRep.h"
#endif
#ifndef INTERNAL_H
namespace Atil { class Internal; }
#endif
#ifndef IMAGE_H
namespace Atil { class Image; }
#endif

#ifndef IMAGECONTEXT_H
#define IMAGECONTEXT_H

namespace Atil
{

/// <summary>
/// This class provides pixel level access to the data within an image. It is
/// constructed through the <c>createContext(...)</c> member of the <c>Image</c>
/// <see cref="Image"/> class.
/// </summary>
///
class ImageContext 
{
public:
    /// <summary>
    /// The enum defines modes of access to the image data.
    /// </summary>
    enum Access { 
        /// <summary>
        /// The entry indicating a request for read access.
        /// </summary>
        kRead, 
        /// <summary>
        /// The entry indicating a request for write access.
        /// </summary>
        kWrite 
    };

    /// <summary>
    /// Out of bounds requests, where the pixel to access lies outside of the
    /// image or set region, can be treated through different methods. Those 
    /// methods are defined in this enum.
    /// </summary>
    enum Behavior {
        /// <summary>
        /// This entry indicates that out of bounds request should succeed and
        /// return a default color.
        /// </summary>
        kDefaultColor,
        /// <summary>
        /// This entry indicates that out of bounds request should fail and
        /// throw an exception.
        /// </summary>
        kException,
        /// <summary> This mode will expand the image to include any tile request.
        /// It can result in a change in the size of the image (obviously) if pixels
        /// outside the current extents are requested.</summary>
        kAutoExpand
    };

public:
    /// <summary>
    /// The destructor.
    /// </summary>
    ///
    ~ImageContext ();

    /// <summary>
    /// A query that can be used to determine the pixel type of the image to which this 
    /// ImageContext is bound.
    /// </summary>
    ///
    /// <returns>
    /// This returns a member of the <c>PixelType</c> enum.
    /// </returns>
    ///
    DataModelAttributes::PixelType getPixelType () const;

    /// <summary>
    /// This method sets how out of bounds requests for pixels are handled.
    /// </summary>
    ///
    /// <param name="likeThis">A value from the <c>Behavior</c> enum dictating the
    /// action that will occur if a pixel outside of the bounds is requested.
    /// </param>
    ///
    void setOutOfBoundsBehavior ( Behavior likeThis ); 

    /// <summary>
    /// This will set the color that is returned for an out of bounds request
    /// if kDefaultColor is selected. The type of the color should match that of the image.
    /// </summary>
    ///
    /// <param name="color">The color that will be returned if the <c>Behavior</c> 
    /// action is set to <c>kDefaultColor</c> and a pixel outside of the bounds is requested.
    /// </param>
    ///
    void setOutOfBoundsColor ( ImagePixel color );

    /// <summary>
    /// This method will return a pixel from the image. 
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the pixel to return.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the pixel to return.
    /// </param>
    /// 
    /// <returns>
    /// The return is an <c>ImagePixel</c> <see cref="ImagePixel"/> which can encode
    /// any type of pixel supported within ATIL.
    /// </returns>
    ImagePixel getPixel (Int32 x, Int32 y);

    /// <summary>
    /// This method set the pixel in value into the image. 
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the pixel to set.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the pixel to set.
    /// </param>
    /// 
    /// <param name="value">A <c>ImagePixel</c> containing the value to be set.
    /// </param>
    ///
    void putPixel (Int32 x, Int32 y, ImagePixel value);

    /// <summary>
    /// Gets a row of data on row y of the image, starting at offset x.
    /// </summary>
    ///
    /// <param name="y">The vertical index, starting at zero, of the pixels to return.
    /// </param>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the pixels to return.
    /// </param>
    /// 
    /// <param name="nCount">The number of pixels to be copied into the buffer.
    /// </param>
    ///
    /// <param name="pBuffer">The buffer into which the data will be copied. It
    /// must be large enough to hold the requested number of pixels.
    /// </param>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request results in
    /// pixels being referenced from "out of bounds". <see cref="ImageContextException"/>
    /// </exception>
    ///
    /// <remarks>
    /// It is more efficient to use <c>Image::read(...)</c> to retrieve rows of data.
    /// This method of retrieving rows should be reserved for special applications where
    /// the data being fetched is small and an <c>ImageContext</c> already exists.
    /// </remarks>
    ///
    void getRow (Int32 y, Int32 x, int nCount, void* pBuffer );

    /// <summary>
    /// Copies data into a row of data on row y of the image, starting at offset x.
    /// </summary>
    ///
    /// <param name="y">The vertical index, starting at zero, of the pixels to set.
    /// </param>
    /// 
    /// <param name="x">The horizontal index, starting at zero, of the pixels to set.
    /// </param>
    /// 
    /// <param name="nCount">The number of pixels to be copied into the image.
    /// </param>
    ///
    /// <param name="pBuffer">The buffer from which the data will be copied.
    /// </param>
    ///
    /// <exception cref="ImageContextException">Thrown if a set request would result in
    /// pixels being set "out of bounds". <see cref="ImageContextException"/>
    /// </exception>
    ///
    /// <remarks>
    /// It is more efficient to use <c>Image::paste(...)</c> to set rows of data.
    /// This method of setting rows should be reserved for special applications where
    /// the data being set is small and an <c>ImageContext</c> already exists.
    /// </remarks>
    ///
    void putRow (Int32 y, Int32 x, int nCount, void* pBuffer );

    /// <summary>
    /// Sets the pixels in the row to the passed in color starting at row y of 
    /// the image and at offset x.
    /// </summary>
    ///
    /// <param name="y">The vertical index, starting at zero, of the pixels to set.
    /// </param>
    /// 
    /// <param name="x">The horizontal index, starting at zero, of the pixels to set.
    /// </param>
    /// 
    /// <param name="nCount">The number of pixels to be copied into the image.
    /// </param>
    ///
    /// <param name="value">The buffer from which the data will be copied.
    /// </param>
    ///
    /// <exception cref="ImageContextException">Thrown if a set request would result in
    /// pixels being set "out of bounds". <see cref="ImageContextException"/>
    /// </exception>
    ///
    /// <remarks>
    /// For large areas to be set to a single value use of the <c>BlankSource</c>
    /// or similar filter is a better choice. <see cref="BlankSource"/>
    /// </remarks>
    ///
    void setRow (Int32 y, Int32 x, int nCount, ImagePixel value );

    /// <summary>
    /// This will return the state of the bit at the desired bit location.
    /// For example, get1(2,3) will get the 2rd bit of the first byte of the 3rd row; 
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to get.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to get.
    /// </param>
    ///
    /// <returns>
    /// This will return the state of the bit at the desired bit location.
    /// </returns>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though it is organized as bits per pixel.
    /// </remarks>
    ///
    int get1 (Int32 x, Int32 y);

    /// <summary>
    /// This will return the byte at the desired location.
    /// For example, get8(2,3) will get the 2nd byte of the 3rd row.
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to get.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to get.
    /// </param>
    ///
    /// <returns>
    /// This will return the state of the byte at the desired location.
    /// </returns>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though it is organized as 8 bits per pixel.
    /// </remarks>
    ///  
    UInt8 get8 (Int32 x, Int32 y);

    /// <summary>
    /// This will return the short integer value from the X,Y location.
    /// For example, get16(1,0) would get you the second short (from bit 16 to bit 31) of row 0.
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to get.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to get.
    /// </param>
    ///
    /// <returns>
    /// This will return the state of the short integer at the desired location.
    /// </returns>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though is is organized as 16 bits per pixel.
    /// </remarks>
    ///  
    UInt16 get16 (Int32 x, Int32 y);

    /// <summary>
    /// This will return the 32-bit unsigned integer (DWORD) value from the X,Y location.
    /// For example, get32(1,0) would get you the second DWORD (from bit 32 to bit 61) of row 0. 
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to get.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to get.
    /// </param>
    ///
    /// <returns>
    /// This will return the state of the 32-bit unsigned integer at the desired location.
    /// </returns>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though it is organized as 32 bits per pixel.
    /// </remarks>
    ///  
    UInt32 get32 (Int32 x, Int32 y);

    /// <summary>
    /// This will return the 64-bit value from the X,Y location. 
    /// For example, get64(1,0) would get you the second 64 bit value (from bit 61 to bit 127) of row 0.
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to get.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to get.
    /// </param>
    ///
    /// <returns>
    /// This will return the state of the 64-bit value at the desired location.
    /// </returns>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though it is organized as 64 bits per pixel.
    /// </remarks>
    ///  
    UInt64 get64 (Int32 x, Int32 y);

    /// <summary>
    /// This will return the 128-bit value from the X,Y location. 
    /// For example, get128(1,0) would get you the second 128 bit value (from bit 129 to bit 255) of row 0.
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to get.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to get.
    /// </param>
    ///
    /// <returns>
    /// This will return the state of the 64-bit value at the desired location.
    /// </returns>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though it is organized as 128 bits per pixel.
    /// </remarks>
    ///  
    Data128 get128 (Int32 x, Int32 y);

    /// <summary>
    /// This will set the state of the bit at the desired bit location.
    /// For example, set1(2,3) will set the 2rd bit of the first byte of the 3rd row; 
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to set.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to set.
    /// </param>
    ///
    /// <param name="value"> The value to set the bit to.
    /// </param>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though it is organized as bits per pixel.
    /// </remarks>
    ///
    void put1 (Int32 x, Int32 y, int value);

    /// <summary>
    /// This will set the byte at the desired location.
    /// For example, set8(2,3) will set the 2nd byte of the 3rd row.
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to set.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to set.
    /// </param>
    ///
    /// <param name="value"> The value to set the byte to.
    /// </param>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though it is organized as 8 bits per pixel.
    /// </remarks>
    /// 
    void put8 (Int32 x, Int32 y, UInt8 value);

    /// <summary>
    /// This will set the short integer value at the X,Y location.
    /// For example, set16(1,0) would set the second short (from bit 16 to bit 31) of row 0.
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to set.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to set.
    /// </param>
    ///
    /// <param name="value"> The value to set the unsigned short to.
    /// </param>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though is is organized as 16 bits per pixel.
    /// </remarks>
    ///  
    void put16 (Int32 x, Int32 y, UInt16 value);

    /// <summary>
    /// This will set the 32-bit unsigned integer (DWORD) value at the X,Y location.
    /// For example, set32(1,0) would set the second DWORD (from bit 32 to bit 61) of row 0. 
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to set.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to set.
    /// </param>
    ///
    /// <param name="value"> The value to set the 32bit (DWORD) to.
    /// </param>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though it is organized as 32 bits per pixel.
    /// </remarks>
    ///    
    void put32 (Int32 x, Int32 y, UInt32 value);

    /// <summary>
    /// This will set the 64-bit value at the X,Y location. 
    /// For example, set64(1,0) would set the second 64 bit value (from bit 61 to bit 127) of row 0.
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to set.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to set.
    /// </param>
    ///
    /// <param name="value"> The value to set the 64bit value to.
    /// </param>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though it is organized as 64 bits per pixel.
    /// </remarks>
    ///  
    void put64 (Int32 x, Int32 y, UInt64 value);

    /// <summary>
    /// This will set the 128-bit value at the X,Y location. 
    /// For example, put128(1,0) would set the second 128 bit value (from bit 129 to bit 255) of row 0.
    /// </summary>
    ///
    /// <param name="x">The horizontal index, starting at zero, of the bit to set.
    /// </param>
    /// 
    /// <param name="y">The vertical index, starting at zero, of the bit to set.
    /// </param>
    ///
    /// <param name="value"> The value to set the 64bit value to.
    /// </param>
    ///
    /// <exception cref="ImageContextException">Thrown if a get request is 
    /// "out of bounds" and the out of bounds behavior is set to generate exceptions.
    /// <see cref="setOutOfBoundsBehavior"/> and <see cref="ImageContextException"/>
    /// </exception>    
    /// 
    /// <remarks>
    /// This method will treat the data as though it is organized as 64 bits per pixel.
    /// </remarks>
    ///  
    void put128 (Int32 x, Int32 y, Data128 value);

    /// <summary>
    /// This method will write the data cache of the context to into the system store. 
    /// This is done automatically when the ImageContext is deleted.
    /// </summary>
    ///
    void flush ( );

    /// <summary>
    /// This method will get one tile of data. You can think of this operation as 
    /// checking out the data. Note that you can get only one tile at a time in this way.  
    /// To obtain another, the tile of data previously checked out must be released or put back. 
    /// </summary>
    ///
    /// <param name="row">The row index of the tile to retrieve.
    /// </param>
    ///
    /// <param name="col">The column index of the tile to retrieve.
    /// </param>
    ///
    /// <param name="pTileData">The buffer to copy the full tile of data into.
    /// </param>
    /// 
    /// <returns>
    /// The method will return "true" if the tile could be retrieved.
    /// </returns>
    ///
    /// <exception cref="ImageContextException"> An instance of the <c>ImageContextException</c>
    /// will be thrown if the a given tile is requested that is already checked out.
    /// </exception>
    ///

    bool getTile (int row, int col, UInt8*& pTileData);

    /// <summary>
    /// This will "unlock" the tile that was checked out via getTile() without 
    /// saving it back to the image.
    /// </summary>
    ///
    void releaseTile ( );

    /// <summary>
    /// This will "unlock" the tile that was checked out via getTile() after 
    /// saving it back to the image.
    /// </summary>
    ///
    /// <returns>
    /// This will return true if the tile was successfully committed.
    /// </returns>
    ///  
    bool putTile ( );

    /// <summary>
    /// Determine whether a given tile has data. Tiles are blank until they are written to. 
    /// Use tileHasData() to avoid processing empty tiles.
    /// </summary>
    ///
    /// <param name="Row">The row index of the tile to test.
    /// </param>
    ///
    /// <param name="Col">The column index of the tile to test.
    /// </param>
    ///
    /// <returns>
    /// The method will return "true" if the tile has data.
    /// </returns>
    ///
    bool tileHasData (int Row, int Col);

    /// <summary>Costructs a concrete version of the <c>CellRequestor</c> class.</summary>
    /// <param name= 'cellSize'>Odd sized (3x3) (5x5) square cell.</param>
    /// <returns>See <c>ImageContext</c>. <see cref="ImageContext"/></returns>
    CellRequestor* constructCellRequestor(int cellSize);

private:
    friend class Image;
    friend class Internal;
    ImageContext ( ImageContextRep* mpImplementation );
    ImageContextRep* mpImplementation;
};


/// <summary>
/// A specialization of the <c>ATILException</c> class used by the <c>ImageContext</c> class.
/// </summary>
/// 
/// <remarks>
/// This class is constructed and used by ATIL to indicate errors in usage of
/// ATIL APIs. The member values are intended as debugging aids and do not contain
/// information that should be displayed to the product user.
/// </remarks>
///
class ImageContextException : public ATILException 
{
public:
    /// <summary> An enum defines for exception types.
    /// </summary>
    enum ExceptionType {
        /// <summary> This entry indicates a specific type of error.</summary>
        kTileAlreadyAllocated,
        /// <summary> This entry indicates a specific type of error.</summary>
        kNotOpenForWrite,
        /// <summary> This entry indicates a specific type of error.</summary>
        kOutOfBounds,
        /// <summary> This entry indicates a specific type of error.</summary>
        kInvalidObject,
        /// <summary> This entry indicates an unspecified type of error.</summary>
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
    ImageContextException (const StringBuffer& sbMessage,
        ExceptionType type = ImageContextException::kUnSpecified);

    /// <summary>
    /// Copy constructor
    /// </summary>
    ///
    /// <param name="x">
    /// A const instance to reference for initialization of the object.
    /// </param>
    ///
    ImageContextException (const ImageContextException& x);

    /// <summary>
    /// Virtual destructor.
    /// </summary>
    ///
    virtual ~ImageContextException ();

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


