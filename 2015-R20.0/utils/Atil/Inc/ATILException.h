/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2014 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef STRINGBUFFER_H
#include "StringBuffer.h"
#endif

#ifndef ATILEXCEPTION_H
#define ATILEXCEPTION_H

namespace Atil
{
/// <summary>
/// The base class of all C++ exceptions thrown from ATIL. ATIL exceptions
/// throw instances of this exception class and the instance should be 
/// deleted if the exception is caught and handled.
/// </summary>
/// 
/// <remarks>
/// The fact that all ATIL exceptions are derived from this class makes
/// creation of a generic catch-all easier. It is recommended however,
/// that the specific exception is caught when it is thrown to facilitate
/// proper error handling.
///
/// Generally exceptions are used in ATIL for where unexpected errors 
/// occur only. Methods that have expected failure states will return them
/// with method specific return codes. For example, FileReadDescriptor 
/// assumes that the file path you send it is valid and readable and will
/// throw an exception if it is not. To test for readability, 
/// FileReadDescriptor exposes a method isDecodableFile that returns a
/// enum code regarding the readability of a file that should be called
/// prior to constructing a FileReadDescriptor.
/// </remarks>
///
class ATILException 
{
public:
    /// <summary> 
    /// Initializing constructor that initializes the internal string to that
    /// of the argument.
    /// </summary>
    ///
    /// <param name="sbMessage">A constant reference to a <c>StringBuffer</c> instance that will be
    /// referenced for the member <c>msbmessage</c> to be set.
    /// </param>
    /// 
    ATILException (const StringBuffer& sbMessage);
    /// <summary> 
    /// Basic constructor that requires post initialization of members 
    /// </summary>
    ///
    ATILException ();
    /// <summary> 
    /// The copy constructor creates a new instance initialized the contents of the argument.
    /// </summary>
    ///
    /// <param name="x">A constant reference to a <c>ATILException</c> instance that is to be copied.
    /// </param>
    ATILException (const ATILException& x);
    /// <summary> 
    /// The destructor.
    /// </summary>
    ///
    virtual ~ATILException ();

    /// <summary>
    /// Access the message, if any, carried by the exception.
    /// </summary>
    ///
    /// <returns>
    /// This method returns a constant StringBuffer pointer to the got message.
    /// </returns>
    ///
    /// <remarks>
    /// The message carried by the exception is not localized and is
    /// not intended to be displayed to the user. It is a string that
    /// describes and error condition as an aid to the developer.
    /// </remarks>
    ///
    virtual const StringBuffer* getMessage ();

protected:

    /// <summary> 
    /// The English ASCII only encoded error message to be carried by this exception
    /// for use as a debugging aid. 
    /// </summary>
    ///
    StringBuffer msbMessage;
};

}

#endif
