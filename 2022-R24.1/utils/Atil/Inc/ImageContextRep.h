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

#ifndef OFFSET_H
namespace Atil { class Offset; }
#endif
#ifndef SIZE_H
namespace Atil { class Size; }
#endif
#ifndef IMAGEPIXEL_H
namespace Atil { struct ImagePixel; }
#endif
#ifndef PIXELSELECTORINTERFACE_H
namespace Atil { class PixelSelectorInterface; }
#endif
#ifndef IMAGE_H
namespace Atil { class Image; }
#endif

#ifndef IMAGECONTEXTREP_H
#define IMAGECONTEXTREP_H

namespace Atil
{
/// <summary> This class serves as an abstract base class for the <c>CellRequestor</c>.</summary>
/// <remarks> It is solely allocated through the <c>ImageContext</c> class. It is meant
/// to allow access to a odd number pixel box. Used in a random offset pattern typically.</remarks>
class CellRequestor
{
public:
    ///<summary>Destructor</summary>
    virtual ~CellRequestor();

    /// <summary> See <c>ImageContext</c>. <see cref="ImageContext"/></summary>
    /// <param name= 'at'> See <c>ImageContext</c>. <see cref="ImageContext"/></param>
    /// <param name= 'pValues'> See <c>ImageContext</c>. <see cref="ImageContext"/></param>
    /// <returns> See <c>ImageContext</c>. <see cref="ImageContext"/></returns>
    virtual bool getCellAt(const Offset& at, void* pValues) = 0;

    /// <summary> See <c>ImageContext</c>. <see cref="ImageContext"/></summary>
    /// <returns> See <c>ImageContext</c>. <see cref="ImageContext"/></returns>    
    virtual Size cellSize() const = 0;

    /// <summary> See <c>ImageContext</c>. <see cref="ImageContext"/></summary>
    /// <returns> See <c>ImageContext</c>. <see cref="ImageContext"/></returns>
    virtual int cellBytes() const = 0;
};


class ImageContextRep 
{
public:
    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    virtual ~ImageContextRep ();

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual DataModelAttributes::PixelType getPixelType () const = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'likeThis'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void setOutOfBoundsBehavior ( int likeThis ) = 0; 

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'color'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void setOutOfBoundsColor ( ImagePixel color ) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual int get1 (Int32 x, Int32 y) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual UInt8 get8 (Int32 x, Int32 y) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual UInt16 get16 (Int32 x, Int32 y) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual UInt32 get32 (Int32 x, Int32 y) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual UInt64 get64 (Int32 x, Int32 y) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual Data128 get128 (Int32 x, Int32 y) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'value'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void put1 (Int32 x, Int32 y, int value) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'value'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void put8 (Int32 x, Int32 y, UInt8 value) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'value'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void put16 (Int32 x, Int32 y, UInt16 value) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'value'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void put32 (Int32 x, Int32 y, UInt32 value) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'value'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void put64 (Int32 x, Int32 y, UInt64 value) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'value'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void put128 (Int32 x, Int32 y, Data128 value) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    virtual void flush ( ) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual ImagePixel getPixel (Int32 x, Int32 y) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'value'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void putPixel (Int32 x, Int32 y, ImagePixel value) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'nCount'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'pBuffer'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void getRow (Int32 y, Int32 x, int nCount, void* pBuffer ) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'nCount'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'pBuffer'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void putRow (Int32 y, Int32 x, int nCount, void* pBuffer ) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'y'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'x'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'nCount'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'value'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    virtual void setRow (Int32 y, Int32 x, int nCount, ImagePixel value ) = 0;
    
    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    /// 
    /// <param name= 'row'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    /// 
    /// <param name= 'col'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'pTileData'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual bool getTile (int row, int col, UInt8 *& pTileData) = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    virtual void releaseTile () = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual bool putTile () = 0;

    /// <summary>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </summary>
    ///
    /// <param name= 'Row'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <param name= 'Col'>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </param>
    ///
    /// <returns>
    /// See <c>ImageContext</c>. <see cref="ImageContext"/>
    /// </returns>
    ///
    virtual bool tileHasData (int Row, int Col) = 0;

    /// <summary>See <c>ImageContext</c>. <see cref="ImageContext"/></summary>
    /// <param name= 'cellSize'>See <c>ImageContext</c>. <see cref="ImageContext"/></param>
    /// <returns>See <c>ImageContext</c>. <see cref="ImageContext"/></returns>
    virtual CellRequestor* constructCellRequestor(int cellSize) = 0;
};

} // end of namespace Atil

#endif


