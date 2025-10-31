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
#ifndef OFFSET_H
#include "Offset.h"
#endif
#ifndef IMAGEFILTER_H
#include "ImageFilter.h"
#endif
#ifndef DATABUFFER_H
#include "DataBuffer.h"
#endif
#ifndef SPANPROVIDERINTERFACE_H
#include "SpanProviderInterface.h"
#endif
#ifndef ATILFILTERSVERSION_H
#include "AtilFiltersVersion.h"
#endif

#ifndef SPANFILTERS_H
#define SPANFILTERS_H

namespace AtilFilters
{

/// <summary>
/// This is the base class for filters that add span information to affect clipping 
/// of data in a <c>Atill::RowProviderInterface</c> pipeline.
/// </summary>
///
class SpanFilter : public Atil::ImageFilter
{
public:
    /// <summary>
    /// This enum describes the behavior of the SpanFilter.
    /// </summary>
    enum Operation 
    { 
        /// <summary>
        /// This entry that data inside the span is not to be drawn.
        /// </summary>
        kClip, 

        /// <summary>
        /// This entry that data outside the span is not to be drawn.
        /// </summary>
        kCrop 
    };

public:
    /// <summary>
    /// The constructor.
    /// </summary>
    ///
    /// <param name='pInput'> The row input to have the spans appended to.
    /// </param>
    ///
    SpanFilter (Atil::RowProviderInterface* pInput);

    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~SpanFilter ();

    /// <summary>
    /// This method will return the one row of data of the output and prepare to return
    /// the next row. 
    /// </summary>
    ///
    /// <param name="oneRow"> A reference to a <c>DataBuffer</c> instance to 
    /// receive the row data.
    /// </param>
    ///
    virtual void getNextRow (Atil::DataBuffer& oneRow);

    /// <summary>
    /// This method will return the number of rows of data that are remaining to be output.
    /// </summary>
    ///
    /// <returns>
    /// Returns the integer number of rows of data that have not yet been returned.
    /// </returns>
    ///
    virtual int rowsRemaining ();

    /// <summary>
    /// This method will return whether there is span clipping information available
    /// for this filters output.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the filter has span information about the rows of data in the filter.
    /// </returns>
    ///
    virtual bool hasSpanInfo () const;

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
    virtual bool getNextSpan (int& nStart, int& nCount);

    /// <summary>
    /// This method may allow a caller to set the current Span pointer back to the
    /// beginning of the current row.
    /// </summary>
    ///
    virtual void restartSpans ();

    /// <summary>
    /// This method will return the number of spans on the current row.
    /// </summary>
    ///
    /// <returns>
    /// Returns the integer number of spans on the current row.
    /// </returns>
    ///
    virtual int numSpans ();

    /// <summary>
    /// This method will return the pixel size of the output of the filter.
    /// </summary>
    ///
    /// <returns>
    /// Returns a <c>Size</c> instance that is the size in pixels of the data from this filter.
    /// </returns>
    ///
    /// <remarks>
    /// Size may change as edits are appended in.
    /// </remarks>
    ///
    virtual Atil::Size size () const;

    /// <summary>
    /// This method allows a span provider to be added to the filter providing the spans
    /// for the filter data.
    /// </summary>
    /// 
    /// <param name='provider'> A const reference to a <c>SpanProviderInterface</c> based class.
    /// </param>
    /// 
    /// <param name='offsetFromPipeOrigin'> An <c>Atil::Offset</c> instance giving an x and y offset
    /// from the top left (0,0) origin of the data in the filter to the top left origin (0,0) of the
    /// data in the <c>SpanProviderInterface</c>.
    /// </param>
    ///
    /// <param name='op'> A member of the <c>Operation</c> enum dictating how to treat the spans.
    /// </param>
    ///
    void appendSpanProvider ( const SpanProviderInterface& provider,
        Atil::Offset offsetFromPipeOrigin, Operation op );

    /// <summary>
    /// Internal version tracking.
    /// </summary>
    ///
    AtilFiltersVersion version;

private:
    bool isActive ( int nIndex );

    struct SpanProvider {
        SpanProviderInterface* pProvider;
        SpanProviderInterface::Mode mode;
        SpanFilter::Operation op;
        Atil::Offset offset;
        bool bActive;
    };
    struct SpanProvider* maProviderList;

    int mnProviders;
    int mnArrayElements;

    struct Span 
    {
        int nStart;
        int nEnd;
        struct Span* next;
    };
    int mnSpans;
    int mnOnSpan;
    int collateProviderSpans( int nProvider );
    int collateProviderSpans( int nProvider, struct Span*& aSpans );
    void mergeSpan ( SpanProviderInterface::Mode mode, int nSpans, struct Span* aSpans );
    void clearToEnd ( int nEnd );

    struct Span* newSpan ();
    void deleteSpanList ();
    void appendToList ( struct Span* pAppend );
    void insertSpanIntoList (struct Span* pInsert, struct Span* pAfter);
    void removeSpanFromList (struct Span* pRemove );

    struct Span* mpSpanList;
    struct Span* mpTail;

    int mnColumns;
    int mnRows;
    int mnOnRow;
    bool mbShowInactiveRows;
    bool mbActiveProviderOnRow;
};

}

#endif
