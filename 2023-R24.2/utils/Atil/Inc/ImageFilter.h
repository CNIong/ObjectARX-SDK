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
#ifndef ATILEXCEPTION_H
#include "ATILException.h"
#endif
#ifndef ROWPROVIDERINTERFACE_H
#include "RowProviderInterface.h"
#endif
#ifndef SIZE_H
#include "Size.h"
#endif
#ifndef IMAGEPIXEL_H
#include "ImagePixel.h"
#endif

#ifndef DATAMODEL_H
namespace Atil { class DataModel; }
#endif
#ifndef DATABUFFER_H
namespace Atil { class DataBuffer; }
#endif
#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

namespace Atil
{

/// <summary>
/// The <c>ImageFilter</c> class derives from <c>RowProviderInterface</c> and extends
/// it with services that provide for the layering of filters into a chain. This makes
/// this the choice class as a parent for developers to derive custom filters.
/// </summary>
class ImageFilter : public RowProviderInterface
{
public:

    /// <summary>
    /// This method will return the pixel size of the output of the filter.
    /// </summary>
    ///
    /// <returns>
    /// Returns a <c>Size</c> instance that is the size in pixels of the data from this filter.
    /// </returns>
    ///
    virtual Size size () const;

    /// <summary>
    /// This method will return the datamodel of the data that will be
    /// the output of the filter.
    /// </summary>
    ///
    /// <returns>
    /// Returns a const reference to the <c>DataModel</c> of the data in this filter.
    /// </returns>
    ///
    virtual const DataModel& dataModel () const;

    /// <summary>
    /// This method will return the number of bytes needed to hold one row 
    /// of the output of the filter. This size will have sufficient padding to
    /// allocate a buffer that conforms to the ATIL packing.
    /// </summary>
    ///
    /// <returns>
    /// Returns the integer number of bytes need to hold one row of data from this filter.
    /// </returns>
    ///
    virtual int bytesPerRow () const;

    /// <summary>
    /// This method will return the status of the filter. It the filter is 
    /// functioning correctly and has the ability to provide output it will return true.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the filter can return valid data.
    /// </returns>
    ///
    virtual bool isValid () const;

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
    /// This method will return the number of rows of data that are remaining to be output.
    /// </summary>
    ///
    /// <returns>
    /// Returns the integer number of rows of data that have not yet been returned.
    /// </returns>
    ///
    virtual int rowsRemaining () = 0;

    /// <summary>
    /// This method will return the one row of data of the output and prepare to return
    /// the next row. 
    /// </summary>
    ///
    /// <param name="oneRow"> A reference to a <c>DataBuffer</c> instance to 
    /// receive the row data.
    /// </param>
    ///
    virtual void getNextRow (DataBuffer &oneRow) = 0;

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
    /// This method should be overridden if the derived filter alters the color
    /// of the pixels in the row. This allows source color such as transparency to 
    /// be converted into the proper output color.
    /// </summary>
    ///
    /// <param name="color">An <c>ImagePixel</c> reference that will be passed to 
    /// the parent for conversion and that result will have the derived conversion
    /// applied.
    /// </param>
    ///
    virtual void convertColor ( ImagePixel& color ) const;

protected:
    /// <summary>
    /// (Protected) Default constructor.
    /// </summary>
    ///
    ImageFilter ( );

    /// <summary>
    /// (Protected) Virtual destructor.
    /// </summary>
    ///
    virtual ~ImageFilter ();

    /// <summary>
    /// This method connects the derived filter to an input. If a DataModel is
    /// specified when init() is called this method will attempt to convert the 
    /// input to that of the input DataModel. 
    /// </summary>
    ///
    /// <param name="input">A <c>RowProviderInterface</c> pointer reference that
    /// will be connect as input to the filter that may have an additional 
    /// data type conversion attached ahead of the filter.
    /// </param>
    ///
    /// <returns>
    /// If the connection fails it will return false. A failure most often occurs
    /// due to a DataModel mismatch that has no available conversion.
    /// This method can be called multiple times to setup multiple input filters.
    /// </returns>
    ///
    bool connectInput ( RowProviderInterface*& input );

    /// <summary>
    /// This method connects the derived filter to an input. This method will 
    /// attempt to convert the input to that of the requested DataModel. 
    /// </summary>
    ///
    /// <param name="input">A <c>RowProviderInterface</c> pointer reference that
    /// will be connect as input to the filter that may have an additional 
    /// data type conversion attached ahead of the filter.
    /// </param>
    ///
    /// <param name="dmConvertTo"> The <c>DataModel</c> that the input should be converted
    /// to if the input is not already in that form.
    /// </param>
    ///
    /// <returns>
    /// If the connection fails it will return false. A failure most often occurs
    /// due to a DataModel mismatch that has no available conversion.
    /// </returns>
    ///
    /// <remarks>
    /// Using this method can be a way to force the input data into a single 
    /// datamodel type that your filter can handle.
    /// This method can be called multiple times to setup multiple input filters.
    /// </remarks>
    ///
    bool connectInput ( RowProviderInterface*& input,
        const DataModel& dmConvertTo );

    /// <summary>
    /// This method will set-up the output for the derived filter. It is required 
    /// to call this method, preferably during the constructed of the derived class.
    /// </summary>
    ///
    /// <param name="size"> The <c>Size</c> that of the data that will be returned
    /// from the filter.
    /// </param>
    ///
    /// <remarks>
    /// This method will set up the datamodel of the output to match that of the input.
    /// </remarks>
    ///
    void init ( const Size& size );

    /// <summary>
    /// This method will set-up the output for the derived filter. It is required 
    /// to call this method, preferably during the constructed of the derived class.
    /// It will setup the output datamodel to be that of the requested datamodel.
    /// </summary>
    ///
    /// <param name="size"> The <c>Size</c> that of the data that will be returned
    /// from the filter.
    /// </param>
    ///
    /// <param name="colorspace"> The <c>DataModel</c> of the data that the filter
    /// will return.
    /// </param>
    ///
    void init ( const Size& size, const DataModel& colorspace );

    /// <summary>
    /// This will return the number of inputs into this derived filter.
    /// </summary>
    ///
    /// <returns>
    /// Returns the integer number of inputs into the filter.
    /// </returns>
    ///
    int numInputs () const;

    /// <summary>
    /// This method will return the input pointer at a location in an array of inputs.
    /// </summary>
    ///
    /// <param name="nInputIndex"> The index of the inputting filters that 
    /// should be returned.
    /// </param>
    ///
    /// <returns>
    /// A pointer to an instance of the <c>RowProviderInterface</c> class that 
    /// serves as the input to the filter at the selected index of connect filter
    /// inputs.
    /// </returns>
    ///
    /// <remarks>
    /// Note that the input (parameter) pointer is not safe to use after init()
    /// and connectInput() have been called, because it might have been changed
    /// by auto-converters.
    /// Using this method to fetch the input pointer is always safe.
    /// </remarks>
    ///
    RowProviderInterface* input ( int nInputIndex ) const;

private:
    RowProviderInterface* mapDefault[5];
    RowProviderInterface** mapInputs;
    int mnElements;

    int mnInputs;
    DataModel* mpOutputDm;
    Size mOutputSize;    
};

/// <summary>
/// A specialization of the <c>ATILException</c> class used by the <c>ImageContext</c> class.
/// </summary>
/// 
/// <remarks>
/// This class is constructed and used by ATIL to indicate errors in usage of
/// ATIL APIs. The member values are intended as debugging aids and do not contain
/// information that should be displayed to the product user.
/// </remarks>
///
class ImageFilterException : public ATILException 
{
public:
    /// <summary> An enum defines for exception types.
    /// </summary>
    enum ExceptionType { 
        /// <summary> This entry indicates a specific type of error.</summary>
        kNotInitialized, 
        /// <summary> This entry indicates a specific type of error.</summary>
        kNoValidInput,
        /// <summary> This entry indicates a specific type of error.</summary>
        kInvalidClearColor, 
        /// <summary> This entry indicates a specific type of error.</summary>
        kOverConnected, 
        /// <summary> This entry indicates a specific type of error.</summary>
        kAlreadyInitialized,
        /// <summary> This entry indicates an unspecified error.</summary>
        kUnSpecified 
    };

public:

    /// <summary>
    /// The initializing constructor.
    /// </summary>
    ///
    /// <param name="sbMessage">
    /// An English ASCII debugging information message.
    /// </param>
    ///
    /// <param name="type">
    /// An enum value that indicates the reason for the exception.
    /// </param>
    ///    
    ImageFilterException (const StringBuffer& sbMessage,
        ExceptionType type = ImageFilterException::kUnSpecified);

    /// <summary>
    /// Copy constructor
    /// </summary>
    ///
    /// <param name="x">
    /// A const instance to reference for initialization of the object.
    /// </param>
    ///
    ImageFilterException (const ImageFilterException& x);

    /// <summary>
    /// Virtual destructor.
    /// </summary>
    ///
    virtual ~ImageFilterException ();

    /// <summary>
    /// This method will return a <c>ExceptionType</c> enum value indicating the
    /// the reason for the exception.
    /// </summary>
    ///
    /// <returns>
    /// This returns a member of the <c>ExceptionType</c> enum.
    /// </returns>
    ///
    virtual ExceptionType getExceptionType ();

private:
    ExceptionType eType;
};

} // end of namespace Atil

#endif

//#ifndef DATAMODEL_H
//#include <DataModel.h>
//#endif
//#ifndef DATABUFFER_H
//#include <DataBuffer.h>
//#endif
