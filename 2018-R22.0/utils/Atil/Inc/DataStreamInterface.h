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

#ifndef DATASTREAMINTERFACE_H
#define DATASTREAMINTERFACE_H

namespace Atil
{
/// <summary>
/// This class describes a stream of image file data. It can be used
/// together with a <c>FileReadDescriptor</c> to read an image into ATIL or
/// a <c>FileWriteDescriptor</c> to write and image from ATIL to an 
/// external source.
/// </summary>
///
/// <remarks>
/// This class has only abstract methods and functions as an interface
/// that can be aggregated to another class through derivation. 
/// </remarks>
///
class DataStreamInterface 
{
public:
    /// <summary>
    /// An enum declaring constants that dictate the current state of a stream
    /// </summary>
    ///
    enum StreamMode	{
        /// <summary>
        /// This entry indicates that the stream is closed 
        /// </summary>
        ///
        kClosed,
        /// <summary>
        /// This entry indicates that the stream is open for reading.
        /// </summary>
        ///
        kForRead, 
        /// <summary>
        /// This entry indicates that the stream is open for writing.
        /// </summary>
        ///
        kForWrite
    };

public:
    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~DataStreamInterface ();
    
    /// <summary>
    /// Use this method to read bytes from the stream.
    /// </summary>
    /// 
    /// <param name="nBytes">
    /// The number of bytes to be read from the stream.
    /// </param>
    ///
    /// <param name="pBytes">
    /// The buffer to receive the bytes from the stream. It should be large
    /// enough to hold the requested number of bytes.
    /// </param>
    ///
    /// <param name="nRead">
    /// The number of bytes read from the string will be returned in the
    /// integer reference nRead.
    /// </param>
    ///
    virtual void read (int nBytes, unsigned char* pBytes, int& nRead) = 0;
    /// <summary>
    /// Use this method to write bytes into the stream.
    /// </summary>
    /// 
    /// <param name="nBytes">
    /// The number of bytes to be written into the stream.
    /// </param>
    ///
    /// <param name="cpBytes">
    /// The buffer containing the bytes to be written into the stream.
    /// </param>
    ///
    /// <returns>
    /// This returns a bool indicating that the number of bytes requested
    /// have been successfully written to the stream. False indicates a
    /// failure to write all the bytes.
    /// </returns>
    ///
    virtual bool write (int nBytes, const unsigned char* cpBytes) = 0;

    /// <summary>
    /// Opens the stream in the requested mode, read or write.
    /// </summary>
    ///
    /// <param name="mode">
    /// An entry from the StreamMode enum that indicates the method that the
    /// stream will be used. For reading or for writing.
    /// </param>
    /// 
    /// <returns>
    /// The return will be true for success and false for failure to open.
    /// </returns>
    ///
    virtual bool open(StreamMode mode) = 0;

    /// <summary>
    /// This allows a stream to be reset to the beginning. 
    /// </summary>
    ///
    /// <returns>
    /// Not all streams support resetting and will return false of failure.
    /// </returns>
    ///
    virtual bool reset() = 0;

    /// <summary>
    /// This will close the stream.
    /// </summary>
    ///
    /// <remarks>
    /// The entire stream does not need to be read nor written before calling close.
    /// </remarks>
    ///
    virtual void close () = 0;
};

/// <summary>
/// This subclass of the <c>DataStreamInterface</c> adds an additional method
/// that will allow a codec to have random access to points within the stream.
/// </summary>
///
class SeekableDataStreamInterface : public Atil::DataStreamInterface
{
public:

    /// <summary>
    /// This enum defines the basis of the offset supplied in a request to
    /// set the "stream" to specific location.
    /// </summary>
    ///
    enum SeekBase { 
        /// <summary>
        /// This entry dictates that the offset is biased from byte zero of 
        /// the stream.
        /// </summary>
        ///
        kFromStart, 

        /// <summary>
        /// This entry dictates that the offset is biased from the last byte of 
        /// the stream.
        /// </summary>
        ///
        kFromEnd, 

        /// <summary>
        /// This entry dictates that the offset is biased from the current position 
        /// of the pointer within the stream.
        /// </summary>
        ///
        kFromCurrent 
    };
public:
    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~SeekableDataStreamInterface();

    /// <summary>
    /// This method will rest the stream pointer within the stream to specific byte location
    /// </summary>
    ///
    /// <param name="nOffset">The byte offset to move the pointer to relative to the selected
    /// base.
    /// </param>
    ///
    /// <param name="from">An entry of the <c>SeekBase</c> enum that dictates the base byte
    /// offset that the select offset should be applied to.
    /// </param>
    ///
    /// <returns>
    /// This method returns the new offset of the pointer within the stream.
    /// </returns>
    ///
    virtual Int32 seek ( Int32 nOffset, SeekBase from ) = 0;
};

} // end of namespace Atil

#endif

