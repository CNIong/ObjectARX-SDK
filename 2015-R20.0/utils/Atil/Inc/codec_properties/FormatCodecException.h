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
#ifndef ATILEXCEPTION_H
#include "ATILException.h"
#endif

#ifndef FORMATCODECEXCEPTION_H
#define FORMATCODECEXCEPTION_H
namespace Atil 
{

/// <summary>
/// This class serves as the base class for exceptions thrown from codecs.
/// </summary>
///
/// <remarks>
/// Using the base class allows calling applications to be generic in their catch phrasing.
/// </remarks>
///
class FormatCodecException : public ATILException
{
public:
    enum ExceptionType { 
        /// <summary> Something bad happened. </summary>
        kUnSpecified,
        /// <summary> A <c>FormatCodecProperty</c> derivant was not set and is needed. </summary>
        kRequiredPropertiesNotSet,
        /// <summary> A <c>ReadRowIterator</c> is not valid. <summary>
        kInvalidRowIterator,
        /// <summary> An error code. </summary>
        kRowIteratorMismatch,
        /// <summary> An error code. </summary>
        kParametersNotComplete,
        /// <summary> An error code. </summary>
        kUnableToAppendFrame,
        /// <summary> An error code. </summary>
        kUnsupportedColorModel,
        /// <summary> An error code. </summary>
        kUnsupportedBitsPerPixel,
        /// <summary> An error code specifing that the contents of the file is not readable. </summary>
        kCorruptFile,
        /// <summary> An error code. </summary>
        kUnsupportedDimensions,
        /// <summary> An error code. </summary>
        kUnsupportedFeature
    };

public:

    /// <summary> 
    /// Basic constructor.
    /// </summary>
    ///
    /// <param name="sbMessage">A constant reference to a <c>StringBuffer</c> instance that will be
    /// referenced for the member <c>msbmessage</c> to be set.
    /// </param>
    ///
    /// <param name="type"> By default <c>kUnSpecified</c> but may be set to indicate 
    /// the nature of the error.
    /// </param>
    FormatCodecException (const StringBuffer& sbMessage,
        ExceptionType type = FormatCodecException::kUnSpecified);

    /// <summary> 
    /// The copy constructor creates a new instance initialized the contents of the argument.
    /// </summary>
    ///
    /// <param name="x">A constant reference to a <c>FormatCodecException</c> instance that is to be copied.
    /// </param>
    FormatCodecException (const FormatCodecException& x);

    /// <summary> 
    /// The destructor.
    /// </summary>
    ///
    virtual ~FormatCodecException ();

    /// <summary>
    /// This gets the type <c>ExceptionType</c> that describest the reason for the exception.
    /// </summary>
    ///
    /// <returns>
    /// A member of the <c>ExceptionType</c> enum.
    /// </returns>
    virtual ExceptionType getExceptionType ();

private:
    ExceptionType eType;

};

}
#endif

