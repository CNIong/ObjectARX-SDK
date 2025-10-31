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
#ifndef DATABUFFER_H
namespace Atil { class DataBuffer; }
#endif

#ifndef ROWITERATORINTERFACE_H
#define ROWITERATORINTERFACE_H

namespace Atil
{

/// <summary>
/// This is the base class for rows as returned from ImageFormatCodecs. 
/// </summary>
///
/// <remarks>
/// This class is similar to the RowProviderInterface in its use. It differs in
/// that extra begin and end calls are implemented to facilitate decoding Image Files.
/// The bracketed begin/done calls offer a way to initialize and free cached objects or buffers.
/// </remarks>
///
class RowIteratorInterface 
{
public:
    /// <summary> 
    /// The trivial destructor.
    /// </summary>
    ///
    virtual ~RowIteratorInterface ();

    /// <summary>
    /// This returns the integer number of bytes needed to hold one row of data.
    /// </summary>
    ///
    /// <returns>
    /// The integer number of bytes.
    /// </returns>
    ///
    virtual int rowBytes () = 0;

    /// <summary>
    /// Get one row of data.
    /// </summary>
    ///
    /// <param name="pRowBuffer"> A reference to a <c>DataBuffer</c> instance to 
    /// receive the row data.
    /// </param>
    ///
    /// <remarks>
    /// Unlike getNextRow, getRow does not increment the row pointer. It may be called
    /// multiple times returning the same data each time.
    /// </remarks>
    ///
    virtual void getRow (DataBuffer* pRowBuffer) = 0;

    /// <summary>
    /// Steps the row pointer ahead one row. 
    /// </summary>
    ///
    /// <returns>
    /// This will return true if there is a valid row at the new position.
    /// </returns>
    ///
    virtual bool incrementRowPointer () = 0;

    /// <summary>
    /// This will return the number of rows that can be read.
    /// </summary>
    ///
    /// <returns>
    /// This returns the integer number of rows that can be read.
    /// </returns>
    ///
    virtual int numRows () = 0;

    /// <summary>
    /// This will return the number of columns in a row.
    /// </summary>
    ///
    /// <returns>
    /// This returns the integer number of columns (pixels) in a row.
    /// </returns>
    ///
    virtual int numColumns () = 0;

    /// <summary>
    /// This begins a read session. It will be called before the first call
    /// to <c>getRow</c>.
    /// <summary>
    ///
    virtual void beginReadingRows () = 0;

    /// <summary>
    /// This ends a read session. It will be called after <c>beginReadingRows</c> and
    /// after any calls to <c>getRow</c> and <c>incrementRowPointer</c>.
    /// </summary>
    ///
    virtual void doneReadingRows () = 0;
};

} //end of namespace

#endif



