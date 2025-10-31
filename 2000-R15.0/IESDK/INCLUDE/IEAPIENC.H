//
// Copyright (C) 1992-1997 by Autodesk, Inc.
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

// Definition of image data compression and decompression filters for the 
// Image Engine.

/*
* Begin multiple inclusion protection...
*/
#ifndef    _ieapienc_h
#define    _ieapienc_h

#pragma pack (push, 8)

/*
* Required header files.
*/

#ifndef _csdefs_h
#include <csdefs.h>            // required for typedefs
#endif /* _csdefs_h */

#include "cs.h"                // for CsSpace

enum IeCodecType {
    IE_ENCODER,
    IE_DECODER
};

class IeCodecInterface {
  public:
    virtual ~IeCodecInterface() {}
 
    virtual void preProcessChunk(Int pixelWidth, Int bitsInPixel) = 0;
    virtual AiBoolean processRow(void *pDecData) = 0;
    virtual void postProcessChunk() = 0;

    virtual void setEncBuffer(void IE_HUGE *pEncData, UInt encBufSize) = 0;
    virtual Int getNumBytesRemaining() const = 0;

    virtual char const *getCodecName() const = 0;
    virtual IeCodecType const getCodecType() const = 0;
    virtual Int getMaxEncRowSize(Int bytesWide) const = 0;
    virtual AiBoolean isBitsPerPixelCompatible(unsigned long ulBitsPerPixel) const = 0;

    virtual IeCodecInterface *duplicate() = 0;
};

#pragma pack (pop)

#endif  /* _ieapienc_h */
