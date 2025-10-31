//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2014 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef SIZE_H
#include "Size.h"
#endif

#ifndef DATABUFFER_H
namespace Atil { class DataBuffer; }
#endif
#ifndef DATAMODEL_H
namespace Atil { class DataModel; }
#endif
#ifndef IMAGEPIXEL_H
namespace Atil { struct ImagePixel; }
#endif

#ifndef ROWPROVIDERINTERFACE_H
#define ROWPROVIDERINTERFACE_H

namespace Atil
{
/// <summary>
/// This class is the abstract connection class that is the parent of ImageFilter and
/// all ATIL filters. <c>RowProviderInterface</c> defines abstract methods that allow
/// rows of data to be passed from instance to instance, as well as methods that facilitate
/// passing along span clipping values.
/// </summary>
/// 
/// <remarks>
/// This class defines the interface for the connection between filter instances in 
/// filter pipeline (a chain of filters). This class is not the appropriate base for 
/// application defined filters however. The <c>ImageFilter</c> implements the connection
/// logic that allows the filters to properly initialize. The <c>ImageFilter</c> <see cref="ImageFilter"/>
/// is the proper base class for application defined filters.
/// </remarks>
///
class RowProviderInterface 
{
public:
    /// <summary>
    /// Virtual destructor.
    /// </summary>
    ///
    virtual ~RowProviderInterface () ;

    /// <summary>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </summary>
    ///
    ///
    /// <param name= "oneRow">
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </param>
    ///
    virtual void getNextRow (DataBuffer& oneRow) = 0;

    /// <summary>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </summary>
    ///
    /// <returns>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </returns>
    ///
    virtual int rowsRemaining () = 0;

    /// <summary>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </summary>
    ///
    /// <returns>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </returns>
    ///
    virtual Size size () const = 0;

    /// <summary>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </summary>
    ///
    /// <returns>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </returns>
    ///
    virtual const DataModel& dataModel () const = 0;

    /// <summary>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </summary>
    ///
    /// <returns>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </returns>
    ///
    virtual bool hasSpanInfo () const = 0;

    /// <summary>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </summary>
    ///
    /// <param name="nStart">
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </param>
    ///
    /// <param name="nCount">
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </param>
    ///
    /// <returns>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </returns>
    ///
    virtual bool getNextSpan (int& nStart, int& nCount) = 0;

    /// <summary>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </summary>
    ///
    virtual void restartSpans () = 0;

    /// <summary>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </summary>
    ///
    /// <returns>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </returns>
    ///
    virtual int numSpans () = 0;

    /// <summary>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </summary>
    ///
    /// <returns>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </returns>
    ///
    virtual int bytesPerRow () const = 0;

    /// <summary>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </summary>
    ///
    /// <returns>
    /// See <c>ImageFilter</c> <see cref="ImageFilter"/> for method documentation.
    /// </returns>
    ///
    virtual bool isValid () const = 0;
};

} //end of namespace

#endif

