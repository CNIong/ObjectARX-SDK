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
#ifndef BOUNDINGBOX_H
#include "BoundingBox.h"
#endif

#ifndef SPANPROVIDERINTERFACE_H
#define SPANPROVIDERINTERFACE_H

namespace AtilFilters 
{
/// <summary>
/// This is the interface class for span providers.
/// </summary>
///
class SpanProviderInterface
{
public:
    /// <summary>
    /// This enum dictates how to treat spans on the same row of data.
    /// </summary>
    enum Mode
    {
        /// <summary>
        /// This allows other spans to persist on the same row.
        /// </summary>
        kInclusive,
        
        /// <summary>
        /// This does not allow other spans to persist outside of the region declare within the spans.
        /// </summary>
        /// 
        kExclusive 
    };
public:
    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~SpanProviderInterface ();

    /// <summary>
    /// This allows <c>SpanProviderInterface</c> class to be "deep cloned".
    /// </summary>
    ///
    /// <returns>
    /// This returns a new <c>SpanProviderInterface</c> derived instance.
    /// </returns>
    ///
    virtual SpanProviderInterface* clone () const = 0;

    /// <summary> This returns the <c>Mode</c> of operation of the span provider. </summary>
    /// 
    /// <returns> Returns a member of the <c>Mode</c> enum. </returns>
    ///
    virtual Mode mode () = 0;

    /// <summary> This starts the return of spans with the first row. </summary>
    /// 
    virtual void begin () = 0;

    /// <summary> This ends the return of rows of spans. </summary>
    /// 
    virtual void end () = 0;

    /// <summary>
    /// This method increments the row pointer to the next row.
    /// </summary>
    ///
    /// <returns>
    /// This will return true if there is data on the row being incremented to.
    /// </returns>
    ///
    virtual bool nextRow () = 0;

    /// <summary>
    /// This method will return the number of rows of span information.
    /// </summary>
    ///
    /// <returns>
    /// Returns the integer number of rows of span information.
    /// </returns>
    ///
    virtual int numRows () = 0;

    /// <summary>
    /// This method returns the spans of data within the row returned. If no spans remain
    /// on the row, it will return false. 
    /// </summary>
    ///
    /// <param name="nStart">An integer reference that will be set to the offset of the first
    /// pixel of the current span.
    /// </param>
    /// 
    /// <param name="nCount">An integer reference that will be set to the number of pixels
    /// in the current span that are valid and should be copied.
    /// </param>
    ///
    /// <returns>
    /// This will return true if there are more spans to be returned.
    /// </returns>
    ///
    /// <remarks>
    /// The default if no clipping is present will be to return a 
    /// single span of the entire row.
    /// </remarks>
    ///
    virtual bool getNextSpan (int& nStart, int& nCount) = 0;

    /// <summary>
    /// This method will return the number of spans on the current row.
    /// </summary>
    ///
    /// <returns>
    /// Returns the integer number of spans on the current row.
    /// </returns>
    ///
    virtual int numSpans () = 0;

    /// <summary>
    /// This method will return the pixel bound box of the spans in the provider.
    /// </summary>
    ///
    /// <returns>
    /// Returns a const <c>BoundingBox</c> reference.
    /// </returns>
    ///
    virtual const Atil::BoundingBox& bounds () const = 0;
};

}

#endif
