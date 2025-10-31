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
#ifndef STRINGBUFFER_H
#include "StringBuffer.h"
#endif
#ifndef DATAMODELATTRIBUTES_H
#include "DataModelAttributes.h"
#endif
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif
#ifndef FORMATCODECPROPERTYSETITERATOR_H
namespace Atil { class FormatCodecPropertySetIterator; }
#endif
#ifndef ROWITERATORINTERFACE_H
namespace Atil { class RowIteratorInterface; }
#endif

#ifndef READIMAGEFILEFRAMEINTERFACE_H
#define READIMAGEFILEFRAMEINTERFACE_H

namespace Atil
{

///<summary>This is the interface base class to expose reading of an image within an image file.</summary>
class ReadImageFileFrameInterface 
{
public:
    ///<summary>This enum describes the different methods ATIL accepts data in.</summary>
    enum AccessMethod { 
        ///<summary>Row by row return.</summary>
        ///<remarks>This is the most basic and all formats should implement row by row return unless it is signafactly difficult or impossible to do so.</remarks>
        kRow, 
        ///<summary>The data is return in tiles and these can be randomly accessed.</summary>
        kDirectTile, 
        ///<summary>The data can be returned within regions that are smaller than the whole image on a row by row basis.</summary>
        ///<remarks>This region request will be a random rectangle within the image. It can help performance to implement this.</remarks>
        kSubRegion, 

        ///<summary>The data can be returned in lower levels of resolution.</summary>
        ///<remarks>This signals that lower resolutions other than a thumb-nail version exist or can be provided.
        ///ATIL will call this for sub sampled data if scaled (lower) data is requested.</remarks>
        kSubSampled 
    };
public:

    ///<summary>The destructor.</summary>
    virtual ~ReadImageFileFrameInterface ();

    ///<summary>This queueries the <c>ReadImageFileFrame</c> for its data return capability.</summary>
    ///<param name='method'>An member of the <c>AccessMethod</c> enum being queuried for support.</param>
    ///<returns>This will return if the image within the file supports the passed in method.</return>
    ///<remarks>The supported return method can and will vary by image within the file.</remarks>
    virtual bool isSupportedAccessMethod ( AccessMethod method ) const = 0;

    ///<summary>This queuries the index of the image within the file.</summary>
    ///<returns>This will return the index of the image within the image file.</returns>
    ///<remarks>Some formats can encode multiple images within a single file. Other format handlers
    ///may create frames though reinterpreting data.</remarks>
    virtual int index () const = 0;

    ///<summary>This queueries the size of the image data.</summary>
    ///<param name='nRows'>A reference to an integer where the number image rows will be stored.</param>
    ///<param name='nColumn'>A reference to an integer where the number image columns will be stored.</param>
    virtual void dimensions (int& nRows, int& nColumns) const = 0;

    ///<summary>This queueries the size of the image data.</summary>
    ///<param name='nRows'>A reference to an integer where the number image rows will be stored.</param>
    ///<param name='nColumn'>A reference to an integer where the number image columns will be stored.</param>
    ///<param name='nDepths'>A reference to an integer where the number image depths will be stored.</param>
    virtual void dimensions (int& nRows, int& nColumns, int& nDepths) const {
        dimensions(nRows, nColumns);
        nDepths = 1;
    }

    ///<summary>This queuries the color format of the data being returned.</summary>
    ///<returns>This returns an instance of the <c>DataModelAttributes::DataModelType</c> descibing the color format.</returns>
    virtual DataModelAttributes::DataModelType dataModel () const = 0;

    ///<summary>This queueries the number of bits of memory occupied by each pixel sample.</summary>
    ///<returns>This returns an instance of the <c>DataModelAttributes::BitsPerPixel</c> describing the pixel footprint of each sample.</returns>
    ///<remarks>ATIL supports a discreet number of pixel sizes.</remarks>
    virtual DataModelAttributes::BitsPerPixel bitsPerPixel () const = 0;

    ///<summary>This queueries the number of bits used for each pixel sample.</summary>
    ///<returns>This returns the number of bits used with the <c>DataModelAttributes::BitsPerPixel</c> sample.</returns>
    ///<remarks>This is always less than or equal to the bits in <c>DataModelAttributes::BitsPerPixel</c>.
    ///An example is a gray scale image that uses <c>BitsPerPixel::k16</c> but has only 10 bits of actual data per sample.</remarks>
    virtual int bitsUsedPerPixel () const = 0;

    ///<summary>This queuries the format of the channel data within the sample.</summary>
    ///<returns>This returns an instance of the <c>DataModelAttributes::DataType</c> 
    ///describing the color format.</returns>
    virtual DataModelAttributes::DataType dataType () const = 0;

    ///<summary>This queuries the layout of the channel data within the sample.</summary>
    ///<returns>This returns an instance of the <c>DataModelAttributes::BitFields</c> 
    ///describing the width of bit fields within single sample images.</returns>
    virtual DataModelAttributes::BitFields bitFields () const = 0;

    ///<summary>This queuries the orientation that the data will be returned in.</summary>
    ///<returns>This returns a member of the <c>Atil::Orientation</c> enum describing the direction of rows and columns for the data.</returns>
    ///<remarks> Any orientation other than <c>kTopDownLeftRight</c> will disable all
    ///"quick" loading methods such as <c>kSubRegion</c> and <c>kDirectTile</c>. 
    ///If your driver can easily reorient the data to <c>kTopDowLeftRight</c> it should do so.</remarks>
    virtual Atil::Orientation dataOrientation () = 0;

    ///<summary>This queueries the number of colors in a palette.</summary>
    ///<returns>This returns the number of entries and will be between 0 and 256.</returns>
    ///<remarks>This will return 0 if the image in the file is not paletted.</remarks>
    virtual int numPaletteEntries () = 0;

    ///<summary>This retrieves the colors of the palette to the image.</summary>
    ///<param name='nPaletteEntries'>This is the number of entries to retrieve.</param>
    ///<param name='palette'>A pointer to an array of packed r,g,b triples (as bytes) the length set by <c>nPaletteEntries</c> parameter.</param> 
    virtual void getPaletteEntries (int nPaletteEntries, UInt8* palette) = 0;

    ///<summary>This retrieves the <c>RowIteratorInterface</c> that will provide the image data.</summary>
    ///<returns>This returns a pointer to a <c>RowIteratorInterface</c> instance.</returns>
    virtual RowIteratorInterface* getRowIterator () = 0;

    ///<summary>This queuries the image for tile sizes.</summary>
    ///<param name='nSizes'>The number of entries in the <c>paSquareTileSizes</c> array.</param>
    ///<param name='paSquareTileSizes'>An array of integers where each integer holds the size of a tile.</param>
    ///<returns>While this should return true if there is a size match in the array, it is not currently used.</returns>
    ///<remarks>This API is not currently called, although it may in the future.</remarks>
    virtual bool canProvideTileSize (int nSizes, int* paSquareTileSizes) const = 0;

    ///<summary>This retrieves an instance of <c>FormatCodecPropertySetIterator</c> with <c>FormatCodecPropertyInterface</c> derivants in it.</summary>
    ///<returns>This returns an <c>FormatCodecPropertySetIterator</c> instance.</returns>
    ///<remarks>This is a convienent way to get image properties. The iterator holds all properties that apply to the image frame.</remarks>
    virtual FormatCodecPropertySetIterator* newPropertySetIterator () = 0;

    /// <summary>This will query for a specific property from the current frame of the image.</summary>
    /// <param name="id">An instance of the <c>FormatCodecPropertyInterface::PropertyIdentifier</c> that indicates a property type to return.</param>
    /// <returns>An instance of a <c>FormatCodecPropertyInterface</c> derived property that
    /// should be deleted by the caller. A NULL pointer will be returned if the requested property can not be found.</returns>
    virtual FormatCodecPropertyInterface* getProperty (FormatCodecPropertyInterface::PropertyIdentifier id) = 0;

    /// <summary>This will query for a specific property from the current frame of the image.</summary>
    /// <param name="sbPropertyName">An instance of a <c>Atil::StringBuffer</c> that holds the name of the property type to return.</param>
    /// <returns>An instance of a <c>FormatCodecPropertyInterface</c> derived property that
    /// should be deleted by the caller. A NULL pointer will be returned if the requested property can not be found.</returns>
    virtual FormatCodecPropertyInterface* getProperty (const StringBuffer& sbPropertyName) = 0;
};

} //end of namespace

#endif

