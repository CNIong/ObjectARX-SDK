///////////////////////////////////////////////////////////////////////////////
//
//
//  (C) Copyright 2005-2007 by Autodesk, Inc.  All rights reserved.
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
#ifndef DATAMODEL_H
#include "DataModel.h"
#endif
#ifndef IMAGECONTEXT_H
#include "ImageContext.h"
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
#ifndef ROWPROVIDERINTERFACE_H
namespace Atil { class RowProviderInterface; }
#endif
#ifndef FILEREADDESCRIPTOR_H
namespace Atil { class FileReadDescriptor; }
#endif
#ifndef FILEWRITEDESCRIPTOR_H
namespace Atil { class FileWriteDescriptor; }
#endif
#ifndef IMAGECONTEXTREP_H
namespace Atil { class ImageContextRep; }
#endif
#ifndef IMAGEREACTORINTERFACE_H
namespace Atil { class ImageReactorInterface; }
#endif

#ifndef  IMAGEREP_H
#define  IMAGEREP_H

namespace Atil
{

/// <summary>
/// This class is the pure abstract definition of the internal component known as the 
/// the "letter" or the far side of the "bridge".
/// </summary>
///
/// <remarks>
/// ATIL implements the Image class with a "letter - envelope" or "Bridge" 
/// design pattern. See "Design Patterns, ISBN 0-201-63361-2". 
/// </remarks>
///
class ImageRep 
{

public:
    /// <summary>
    /// Virtual destructor.
    /// </summary>
    ///
    virtual ~ImageRep ();

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'ToClone'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual ImageRep* construct (ImageRep*  ToClone) = 0; 

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'size'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'colorspace'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'clearColor'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'sz'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual ImageRep* construct (const Size& size, const DataModel* colorspace,
        ImagePixel clearColor, DataModel::TileSize sz) = 0; 

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'pDataBuffer'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'nBytesInBuffer'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'nBytesPerRow'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'size'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'pDm'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual ImageRep* construct (void* pDataBuffer, int nBytesInBuffer, int nBytesPerRow, const Size& size,
        const DataModel* pDm) = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'pPipe'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'oriented'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'sz'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual ImageRep* construct (RowProviderInterface* pPipe, int oriented,
        DataModel::TileSize sz) = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'readDesc'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'sz'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual ImageRep* construct (FileReadDescriptor& readDesc,
        DataModel::TileSize sz) = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'imageRep'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual bool operator== (const ImageRep& imageRep) const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual const Size& size () const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'nRows'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'nCols'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual int   numTiles (int& nRows, int& nCols) const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual Size  tileSize () const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual const DataModel& dataModel () const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual const FileReadDescriptor* fileReadDescriptor () const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual const ImagePixel& clearColor () const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'clearValue'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
    virtual void setClearColor (ImagePixel clearValue)  = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual bool isValid () const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual bool isModified () const  = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual bool usesUserBuffer () const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'dataModel'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
    virtual void setDataModel ( const DataModel& dataModel ) = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'accessMethod'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'size'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'offset'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'numTilesToCache'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual ImageContextRep* createContext ( ImageContext::Access accessMethod,
        const Size& size, const Offset& offset, int numTilesToCache)  = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'size'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'offset'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual RowProviderInterface* read (const Size& size,
        const Offset& offset) const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'size'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'offset'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'oriented'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual RowProviderInterface* read (const Size& size,
        const Offset& offset, int oriented) const = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
    virtual void clear () = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'pPipe'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'at'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'bRespectTransparency'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
    virtual void paste (RowProviderInterface* pPipe, const Offset& at,
        bool bRespectTransparency ) = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'pPipe'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'at'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'nAlphaValue'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <param name= 'bRespectTransparency'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
    virtual void blend (RowProviderInterface * pPipe, const Offset& at,
        int nAlphaValue, bool bRespectTransparency ) = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'pReactor'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
    virtual void addReactor ( ImageReactorInterface* pReactor ) = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'pReactor'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
    virtual void removeReactor ( ImageReactorInterface* pReactor ) = 0;

    /// <summary>
    /// See <c>Image</c>. <see cref="Image"/>
    /// </summary>
    ///
	/// <param name= 'bDisable'>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </param>
	///
	/// <returns>
	/// See <c>ImageContext</c>. <see cref="ImageContext"/>
	/// </returns>
	///
    virtual bool disablePerTileLocking ( bool bDisable ) = 0;

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
//#ifndef ROWPROVIDERINTERFACE_H
//#include <RowProviderInterface.h>
//#endif
//#ifndef FILEREADDESCRIPTOR_H
//#include <FileReadDescriptor.h>
//#endif
//#ifndef FILEWRITEDESCRIPTOR_H
//#include <FileWriteDescriptor.h>
//#endif
