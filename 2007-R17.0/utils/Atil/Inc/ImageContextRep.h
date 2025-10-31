///////////////////////////////////////////////////////////////////////////////
//
//
//  (C) Copyright 2005 by Autodesk, Inc.  All rights reserved.
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

#ifndef  IMAGECONTEXTREP_H
#define  IMAGECONTEXTREP_H

namespace Atil
{
class ImageContextRep 
{

public:
    virtual ~ImageContextRep ();
    virtual DataModelAttributes::PixelType getPixelType () const = 0;
    virtual void setOutOfBoundsBehavior ( int likeThis ) = 0; 
    virtual void setOutOfBoundsColor ( ImagePixel color ) = 0;

    virtual int get1 (Int32 x, Int32 y) = 0;
    virtual UInt8 get8 (Int32 x, Int32 y) = 0;
    virtual UInt16 get16 (Int32 x, Int32 y) = 0;
    virtual UInt32 get32 (Int32 x, Int32 y) = 0;
    virtual UInt64 get64 (Int32 x, Int32 y) = 0;
    virtual void put1 (Int32 x, Int32 y, int value) = 0;
    virtual void put8 (Int32 x, Int32 y, UInt8 value) = 0;
    virtual void put16 (Int32 x, Int32 y, UInt16 value) = 0;
    virtual void put32 (Int32 x, Int32 y, UInt32 value) = 0;
    virtual void put64 (Int32 x, Int32 y, UInt64 value) = 0;
    virtual void flush ( ) = 0;

    virtual ImagePixel getPixel (Int32 x, Int32 y) = 0;
    virtual void putPixel (Int32 x, Int32 y, ImagePixel value) = 0;

    virtual void getRow (Int32 y, Int32 x, int nCount, void* pBuffer ) = 0;
    virtual void putRow (Int32 y, Int32 x, int nCount, void* pBuffer ) = 0;
    virtual void setRow (Int32 y, Int32 x, int nCount, ImagePixel value ) = 0;
    
    virtual bool getTile (int row, int col, UInt8 *& pTileData) = 0;
    virtual void releaseTile () = 0;
    virtual bool putTile () = 0;
    virtual bool tileHasData (int Row, int Col) = 0;
};

} // end of namespace Atil
#endif

//#ifndef OFFSET_H
//#include <Offset.h>
//#endif
//#ifndef SIZE_H
//#include <Size.h>
//#endif
//#ifndef IMAGEPIXEL_H
//#include <ImagePixel.h>
//#endif
//#ifndef PIXELSELECTORINTERFACE_H
//#include <PixelSelectorInterface.h>
//#endif
//#ifndef IMAGE_H
//#include <Image.h>
//#endif

