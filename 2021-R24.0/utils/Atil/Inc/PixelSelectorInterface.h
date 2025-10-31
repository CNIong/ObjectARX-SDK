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

#ifndef PIXELSELECTORINTERFACE_H
#define PIXELSELECTORINTERFACE_H

/// <summary>
/// The namespace for the AtilFilters.lib exported classes.
/// </summary>
///
namespace AtilFilters
{

/// <summary>
/// This abstract base class is to be derived and implemented by the developer.
/// This interface is used by the <c>ExplodeSelect</c> class to determine whether
/// a given pixel is a member of a selected set. This allows the developer to 
/// determine and implement the selection criteria.
/// </summary>
///
class PixelSelectorInterface 
{
public:
    /// <summary>
    /// Trivial virtual destructor.
    /// </summary>
    virtual ~PixelSelectorInterface () {};

    /// <summary>
    /// Abstract selection method called by the <c>ExplodeSelect</c> class
    /// to determine if a pixel in an image could be included in the set of 
    /// selected pixels.
    /// </summary>
    ///
    /// <param name='x'>The index of the pixel along the x-axis to be tested
    /// for selection.
    /// </param>
    ///
    /// <param name='y'>The index of the pixel along the y-axis to be tested
    /// for selection.
    /// </param>
    ///
    /// <returns>
    /// A return of 'true' indicates that the pixel in question meets the
    /// selection criteria.
    /// </returns>
    ///
    virtual bool isSelected (Atil::Int32 x, Atil::Int32 y) = 0;

    /// <summary>
    /// Abstract selection method called by the <c>ExplodeSelect</c> class
    /// to set a pixel in an image as included in the set of selected pixels.
    /// </summary>
    ///
    /// <param name='y'>The index of the pixel along the y-axis to be selected.
    /// </param>
    ///
    /// <param name='x'>The index of the pixel along the x-axis that is the
    /// start of the selected pixels.
    /// </param>
    ///
    /// <param name='nCount'>The count of pixels along the x-axis from the 
    /// start to be selected.
    /// </param>
    ///
    virtual void setSelected (Atil::Int32 y, Atil::Int32 x, int nCount ) = 0;

    /// <summary>
    /// This method is called as a service to allow the selector class to 
    /// reset and write out any data it may be caching. What is needed to be 
    /// done is up to the developer.
    /// </summary>
    ///
    virtual void flush () = 0;
};

} //end of namespace

#endif
