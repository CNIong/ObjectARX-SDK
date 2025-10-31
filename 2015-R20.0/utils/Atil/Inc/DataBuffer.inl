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


#ifndef DATABUFFER_INL
#define DATABUFFER_INL
#if  __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif

namespace Atil
{

/// <summary>
/// Inlined query for the number of bytes in the buffer.
/// </summary>
///
/// <returns>
/// Returns the integer count of bytes allocated in the internal buffer.
/// </returns>
inline int DataBuffer::numBytes () const
{
    return mnBufferBytes;
}

/// <summary>
/// Inlined query for modifiable access to the enclosed buffer.
/// </summary>
///
/// <returns>
/// Returns a pointer that may be used to write into the enclosed buffer.
/// </returns>
inline unsigned char* DataBuffer::dataPtr ()
{
    return mpBuffer;
}

/// <summary>
/// Inlined query for read-only access to the enclosed buffer.
/// </summary>
///
/// <returns>
/// Returns a pointer that may be used to read from the enclosed buffer.
/// </returns>
inline const unsigned char* DataBuffer::dataPtr () const
{
    return mpBuffer;
}    

}
#if  __GNUC__ >= 4
#pragma GCC visibility pop
#endif

#endif
