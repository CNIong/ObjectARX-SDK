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

#ifndef ROWITERATORINTERFACE_H
#include "RowIteratorInterface.h"
#endif

#ifndef SUBREGIONROWITERATORINTERFACE_H
#define SUBREGIONROWITERATORINTERFACE_H

namespace Atil
{

/// <summary>
/// This class extends the <c>RowIteratorInterface</c> class adding
/// the ability to specify a sub area of the total pixel area of the 
/// the image in the file. 
/// </summary>
/// 
/// <remarks>
/// Developers should not base their <c>RowIteratorInterface</c> on this
/// super class unless their codec can support reading a sub region (rectangle).
/// This is most often the case when the data in the file is not compressed.
/// </remarks>
///
class SubRegionRowIteratorInterface : public RowIteratorInterface
{
public:
    /// <summary>
    /// This is a trivial destructor.
    /// </summary>
    virtual ~SubRegionRowIteratorInterface ();

    /// <summary>
    /// This will reset equivalent sub region currently set to (0,0) (xsize, ysize).
    /// This makes it equivalent to the return of <c>RowIteratorInterface</c>.
    /// </summary>
    virtual void setRegionToExtents () = 0;

    /// <summary>
    /// This will set the upper left corner of the requested subregion.
    /// </summary>
    ///
    /// <param name="nRow">
    /// The integer index of the desired row to start on.
    /// </param>
    ///
    /// <param name="nCol">
    /// The integer index of the desired column to start with.    
    /// </param>
    ///
    virtual void setStart (int nRow, int nCol) = 0;

    /// <summary>
    /// This will get the upper left corner of the requested subregion.
    /// </summary>
    ///
    /// <param name="nRow">
    /// The reference to an integer that will be set to the index of the desired row to start on.
    /// </param>
    ///
    /// <param name="nCol">
    /// The reference to an integer that will be set to the index of the desired column to start with.    
    /// </param>
    ///
    virtual void getStart (int& nRow, int& nCol) = 0;

    /// <summary>
    /// This will set the lower right corner of the requested subregion.
    /// </summary>
    ///
    /// <param name="nRow">
    /// The integer index of the desired row to end on.
    /// </param>
    ///
    /// <param name="nCol">
    /// The integer index of the desired column to end with.    
    /// </param>
    ///
    virtual void setEnd (int nRow, int nCol) = 0;

    /// <summary>
    /// This will get the lower right corner of the requested subregion.
    /// </summary>
    ///
    /// <param name="nRow">
    /// The reference to an integer that will be set to the index of the desired row to end on.
    /// </param>
    ///
    /// <param name="nCol">
    /// The reference to an integer that will be set to the index of the desired column to end with.    
    /// </param>
    ///
    virtual void getEnd (int& nRow, int& nCol) = 0;
};

} //end of namespace

#endif
