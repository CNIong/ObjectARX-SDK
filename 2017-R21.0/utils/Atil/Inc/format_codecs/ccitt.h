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

#ifndef CCITT_H
#define CCITT_H

/// <summary>
/// This holds the enums used by the CCITT decoder/encoder.
/// </summary>
struct CCITT 
{
    /// <summary> Describes the fill order of the bytes in the data.</summary>
    enum FillOrder {
        /// <summary> Intel least significant first.</summary>
        kLsb2Msb, 
        /// <summary> Motorola most significant first.</summary>
        kMsb2Lsb 
    };
    /// <summary> Specifies different encoding systems within the CCITT specification.</summary>
    enum EncodeMethod { 
        /// <summary> Use the Group3 tables along the row only (one dimensional) with RLE encoding.</summary>
        kG3_RLE, 
        /// <summary> Use the Group3 tables along the row only (one dimensional).</summary>
        kG3_1D, 
        /// <summary> Use the Group3 tables with two dimensional references.</summary>
        kG3_2d, 
        /// <summary> Use the Group4 tables which are two dimensional.</summary>
        kG4 
    };

    /// <summary> This declares flags that effect the encoding of the data i.e. line terminators. </summary> 
    enum EncodeFlags {
        /// <summary> Flag indicating no directives over the CCITT specification. </summary>
        kNone = 0, 
        /// <summary> Flag indicating that bits unused in the last byte of line are filled. </summary>
        kEOLFillBits = 0x0001, 
        /// <summary> Flag indicating that each row is byte aligned. </summary>
        kFaxModeByteAlign = 0x0010,
        /// <summary> Flag indicating that each row is word aligned. </summary>
        kFaxModeWordAlign = 0x0110, 
        /// <summary> Flag used for compatibility with some fax formats. </summary>
        kFaxModeNORTC = 0x0100, 
        /// <summary> Flag used to disable the end of line flags. </summary>
        kFaxModeNoEOL = 0x1000 
    };
};

/// <summary> forward declaration of the Atil::DataStreamInterface. </summary>
namespace Atil {class DataStreamInterface;}

/// <summary>
/// CCITTDecoder is a class which is used to decode data in CCITT group 3 
/// or group 4 format.</summary>
class CCITTDecoder
{
public:
    /// <summary>
    /// A static method used to construct an instance of a CCITTTDecoder.</summary>
    static CCITTDecoder* construct();
public:
    /// <summary> The destructor. </summary>
    virtual ~CCITTDecoder();

    /// <summary>
    /// Sets up the decoder with the encoding method, the bit order, and the width of
    /// a row of decoded data.</summary> 
    /// <param name="encoding">The encoding method the data is stored in.</param>
    /// <param name="bitOrder">Whether the data is stored little-endian or big-endian</param>
    /// <param name="nEndodeFlags">Any encoding flags that are needed. (CCITT::EncodeFlags)</param>
    /// <param name="nRowWidth">Width of a row in bytes</param>
    virtual void setupDecoder( CCITT::EncodeMethod encoding, CCITT::FillOrder bitOrder,
        unsigned int nEncodeFlags, int nRowWidth ) = 0;

    /// <summary>
    /// Decodes a block of data known to contain complete rows of compressed data. </summary>
    /// <param name="pIn">Pointer to block of compressed data.</param>
    /// <param name="nInBytes">Number of bytes of compressed data.</param>
    /// <param name="pOut">Pointer to buffer to receive decoded data.</param>
    /// <param name="nOutBytes">Number of bytes to be decoded.  The output buffer must
    /// be at least that large.</param>
    virtual void decodeBlock(unsigned char* pIn, int nInBytes,
        unsigned char* pOut, int nOutBytes) = 0;

    /// <summary>
    /// Feeds the decoder the data stream from which the encoded data will be pulled. 
    /// The data stream must be open for read. </summary>
    /// <param name="pStream">Pointer to an open (for read) data stream from which 
    /// the decoder pulls encoded data. </param>
    virtual void decodeByRow(Atil::DataStreamInterface* pStream ) = 0;

    /// <summary>
    /// Decodes row(s) of data from the input stream specified in decodeByRow</summary>
    /// <param name="pRow">Pointer to a buffer to hold the decoded data.</param>
    /// <param name="nRowBytes">Number of bytes to be decoded.  The output buffer must be 
    /// at least that large.</param>
    /// <returns>Returns "true" if the requested number of bytes was decoded.</returns>
    virtual bool decodeRow(unsigned char * pRow, int nRowBytes ) = 0;

};

class CCITTEncoder
{
public:
    /// <summary>
    /// A static method used to construct an instance of a CCITTTEncoder.</summary>
    static CCITTEncoder* construct ();
public:
    /// <summary> The destructor. </summary>
    virtual ~CCITTEncoder ();


    /// <summary>
    /// Sets up the Encoder with the encoding method, the bit order, and the width of
    /// a row of data.</summary> 
    /// <param name="encoding">The encoding method the data is stored in.</param>
    /// <param name="bitOrder">Whether the data is stored little-endian or big-endian</param>
    /// <param name="options">The options from <c>EncodingFlags</c> to use in encoding.</param>
    /// <param name="nRowWidth">Width of a row in bytes</param>
    virtual void setupEncoder ( CCITT::EncodeMethod encoding, CCITT::FillOrder bitOrder,
        CCITT::EncodeFlags options, int nRowWidth ) = 0;

    /// <summary>
    /// Encodes a block of data known to contain complete rows of data. </summary>
    /// <param name="pIn">Pointer to block of data.</param>
    /// <param name="nInBytes">Number of bytes of data.</param>
    /// <param name="pOut">Pointer to buffer to receive Encoded data.</param>
    /// <param name="nEncodedBytes">A reference to the number of bytes to be used in encoding.</param>
    virtual bool encodeBlock ( unsigned char* pIn, int nInBytes,
        unsigned char* pOut, int nOutBytes, int& nEncodedBytes ) = 0;

    /// <summary>Sets the output buffer for encoded rows of data.</summary>
    /// <param name="pOut">Pointer to the buffer to receive encoded data.</param>
    /// <param name="nOutBytes">The number of bytes in the <c>pOut</c> buffer.</param>
    virtual void encodeByRow ( unsigned char* pOut, int nOutBytes ) = 0;

    /// <summary>Sets the pointer to the start of the output buffer. This states that
    /// the buffer is prepared to receive data again. </summary>
    virtual void resetOutputPointer (  ) = 0;

    /// <summary>
    /// Encodes a row of data sending encoded data to the set output buffer.</summary>
    /// <param name="pRow">Pointer to a buffer holding the data.</param>
    /// <param name="nRowBytes">Number of bytes to be encoded.</param>
    /// <param name="nEncodedBytes">A reference to the number of bytes used in the output
    /// for encoding.</param>
    /// <returns>Returns "true" if successful encoding.</returns>
    virtual bool encodeRow ( unsigned char * pRow, int nRowBytes, int& nEncodedBytes ) = 0;

    /// <summary>This signals that there are no more rows to be encoded.</summary>
    /// <param name="nEncodedBytes">A reference to the number of bytes used in the output
    /// for encoding.</param>
    virtual void endEncodingRows ( int& nEncodedBytes ) = 0;
};

#endif

