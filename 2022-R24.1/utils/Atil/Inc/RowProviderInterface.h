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

