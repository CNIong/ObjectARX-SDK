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
#ifndef READIMAGEFILEFRAMEINTERFACE_H
#include "ReadImageFileFrameInterface.h"
#endif

#ifndef DIRECTTILEREADINTERFACE_H
#define DIRECTTILEREADINTERFACE_H

namespace Atil
{

/// <summary>
/// This class specifies an aggregate of the <c>ReadImagFileFrameInterface</c>.
/// It specifies that the <c>ReadImagFileFrameInterface</c> can return tiles of data.
/// </summary>
///
/// <remarks>
/// To be used the <c>ReadImagFileFrameInterface</c> derivant must also derive from
/// this class. This is multiple derivation however the parents are both pure abstract
/// API specification classes. RTTI will be used to identify if your class implements
/// this Interface.
/// </remarks>
///
class DirectTileReadInterface
{
public:
    /// <summary>
    /// This is a trivial destructor.
    /// </summary>
    virtual ~DirectTileReadInterface ();

    /// <summary>
    /// This returns the size of a square tile. Tiles are always square.
    /// </summary>
    ///
    /// <param name="nLookingFor">
    /// The desired number of pixels for each side of a tile.
    /// </param>
    ///
    /// <returns>
    /// The integer size of either dimension of a square tile in pixels.
    /// </returns>
    virtual int getTileSize (int nLookingFor) = 0;

    /// <summary>
    /// This will set the upper left corner of the requested subregion.
    /// </summary>
    ///
    /// <param name="nRow">
    /// The integer index of the row for the desired tile.
    /// </param>
    ///
    /// <param name="nColumn">
    /// The integer index of the column of the desired tile.    
    /// </param>
    ///
    /// <param name="pBuffer">
    /// The address (pointer to) a buffer to receive the tile data.
    /// </param>
    /// 
    /// <returns>
    /// This will return true if the <c>pBuffer</c> was filled with the tiles data.
    /// </returns>
    /// 
    /// <remarks>
    /// Every tile is complete. Partial tiles on the right or bottom should be 
    /// padded with initialized data.
    /// </remarks>
    ///
    virtual bool getTileData (UInt32 nRow, UInt32 nColumn, UInt8* pBuffer) = 0;
};

} // end of namespace Atil

#endif

