//
// Copyright (C) 1995-1999 by Autodesk, Inc.
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

#include <ieapiif.h>
#include <ieapienc.h>
#include <string.h>
#include "mzf.h"

/*** DECODER ***/
class MzfRleDecoder : public IeCodecInterface
{
  public:
    MzfRleDecoder() : mpIn(NULL), mRemaining(0) {}
    ~MzfRleDecoder() {}
    void preProcessChunk(Int numPixels, Int bitsPerPixel) 
        { mBytesPerRow = numPixels * bitsPerPixel / 8; }
    AiBoolean processRow(void *pRow);
    void postProcessChunk() {};
    void setEncBuffer(void IE_HUGE *p, UInt s) { mpIn = (UInt8 IE_HUGE *) p; mRemaining = s; } 
    Int getNumBytesRemaining() const { return mRemaining; }
    const char *getCodecName() const { return codecMethodTable[2]; }
    const IeCodecType getCodecType() const { return IE_DECODER; }
    Int getMaxEncRowSize(Int bytesPerRow) const { return 2 * bytesPerRow; }
    AiBoolean isBitsPerPixelCompatible(unsigned long ulBitsPerPixel) const { return (ulBitsPerPixel == 8); }
     
    IeCodecInterface *duplicate() { return new MzfRleDecoder; }

  private:
    UInt8 IE_HUGE *mpIn;
    Int mRemaining;
    UInt mBytesPerRow;
};

AiBoolean MzfRleDecoder::processRow(void *pRow)
{
    UInt8 IE_HUGE *pSrc = mpIn;
    UInt8 *pDest = (UInt8*) pRow;
    UInt8 *pEnd = pDest + mBytesPerRow;

    while (pDest < pEnd)            //simple PCX-style RLE for palette images
    {
        UInt8 v = *pSrc++;
        if ((v & 0xc0) != 0xc0)
        {
            *pDest++ = v;
        }
        else
        {
            v &= 0x3f;
            memset(pDest, *pSrc++, v);
            pDest += v;
        }
    }
    UInt delta = pSrc - mpIn;
    mRemaining = mRemaining - delta;
    mpIn = pSrc;
    return mRemaining >= 0 && pDest == pEnd;		//bad encoding
}    


/*** FILE READER ***/
class MzfReader : public IeFileInterface
{
  public:
    MzfReader(IeFileAccess *pFio) 
      : mpFio(pFio), mpStripTable(NULL), mpSizeTable(NULL) {}
    ~MzfReader() { imageClose(); delete [] mpStripTable; delete [] mpSizeTable; }
    
    AiBoolean imageOpen(IeOpenMode openMode);
    void imageClose() { mpFio->imageCloseFile(); }
    AiBoolean openAccess() { return mpFio->imageOpenAccess(); }
    void closeAccess() { mpFio->imageCloseAccess(); }
    
    AiBoolean imageReadRow(UInt row, void *pBuf);
    AiBoolean imageReadEncChunk(Int strip, void IE_HUGE *pBuf);  
    AiBoolean getImageInfo(UInt tag, void *pBuf);
    
    IeCodecInterface *makeDecoder()
        { return mHeader.encoding == 2 ? new MzfRleDecoder : NULL; }

  private:
    IeFileAccess *mpFio;
    MzfHeader mHeader;
    Int mImageStartPos;
    UInt mNumStrips;
    MzfStrip *mpStripTable;
    UInt *mpSizeTable;         //only for getImageInfo(TAG_CHUNKBYTECOUNTS)
};

AiBoolean MzfReader::imageOpen(IeOpenMode openMode)
{
    if (openMode != IE_OM_READONLY ||
        !mpFio->imageOpenFile(openMode) || 
        mpFio->imageReadFile(&mHeader, sizeof(mHeader)) != sizeof(mHeader) || 
        !mHeader.isValid())
        return FALSE;
        
    mNumStrips = (mHeader.height + mHeader.stripHeight - 1) / mHeader.stripHeight;
    mpStripTable = new MzfStrip[mNumStrips];
    UInt n = mNumStrips *sizeof(MzfStrip);
    if (mpFio->imageReadFile(mpStripTable, n) != n)			//load strip table
        return FALSE;
    mpSizeTable = new UInt[mNumStrips];
    for (UInt i=0; i<mNumStrips; i++)
        mpSizeTable[i] = mpStripTable[i].size;
    
    mImageStartPos = mpFio->imageTell();
    return TRUE;
}

AiBoolean MzfReader::imageReadRow(UInt row, void *pDest)
{
    if (row == 0 && mpFio->imageSeekFile(mImageStartPos, IE_SEEK_SET) 
    		    != mImageStartPos)		//restart read
        return FALSE;
    return mpFio->imageReadFile(pDest, mHeader.width) == mHeader.width;
}

AiBoolean MzfReader::imageReadEncChunk(Int strip, void IE_HUGE *pBuf)
{
    if (UInt(strip) > mNumStrips)
        return FALSE;
    UInt offset = mpStripTable[strip].offset;
    if (mpFio->imageSeekFile(offset, IE_SEEK_SET) != Int(offset))
        return FALSE;
    UInt size = mpStripTable[strip].size;
    return mpFio->imageReadFile(pBuf, size) == size;
}
        
AiBoolean MzfReader::getImageInfo(UInt tag, void *pReturn)
{
    UInt val;
    switch (tag) 
    {
      case TAG_BITSPERSAMPLE:
        val = 8;
        break;
        
      case TAG_CHUNKBYTECOUNTS:
        val = (UInt) mpSizeTable;
        break;
        
      case TAG_CHUNKLENGTH:
        val = mHeader.stripHeight;
        break;
        
      case TAG_COLORMAP:
        val = (UInt) mHeader.palette;
        break;
        
      case TAG_COMPRESSION:
        val = (UInt) codecMethodTable[mHeader.encoding];
        break;
        
      case TAG_IMAGELENGTH:
        val = mHeader.height;
        break;

      case TAG_IMAGEWIDTH:
        val = mHeader.width;
        break;
        
      case TAG_PHOTOMETRIC:
        val = PHOTOMETRIC_PALETTE;
        break;
        
      case TAG_SAMPLESPERPIXEL:
        val = 1;
        break;
        
    default:
        return FALSE;
    }

    *(UInt*) pReturn = val;
    return TRUE;
}


/*** FILE ANALYZER ***/
class MzfReadAnalyzer : public IeFileAnalyzer
{
  public:
    MzfReadAnalyzer() {}
    ~MzfReadAnalyzer() {}
    
    IeFileMatch isItMine(IeFileAccess *pAccess, char const *pId);
    IeFileInterface *makeReader(IeFileAccess *pFio) 
    	{ return new MzfReader(pFio); }

    const char *fileType() const { return kFileType; }
    const char *fileVendor() const { return kVendor; }
    const char *fileFormatName() const { return kReaderName; }
    char * const *fileSuffixes() const { return kpFileSuffixes; }
    const char *copyRightNotice() const { return kCopyrightNotice; }
};

IeFileMatch MzfReadAnalyzer::isItMine(IeFileAccess *pFio, char const *pId) 
{
    UInt buf;

    if ((!pId || 0 == strcmp(pId, kFileType)) 
        && pFio->imageReadFile(&buf, sizeof(buf)) == sizeof(buf)
        && buf == kMzfMagic)
        return IE_FM_IS_MY_TYPE;
    else
        return IE_FM_NOT_MY_TYPE;
}

IeFileAnalyzer *newIeFileAnalyzer() 
{
    return new MzfReadAnalyzer;
}

const char *moduleIdentify(IeModuleId moduleId) 
{
    switch (moduleId) 
    {
      case IE_IMAGE_SERVICE:  return IE_IMAGE_FILE_SERVICE;
      case IE_SERVICE_TYPE:   return IE_FILE_READER;
      default:		      return NULL;
    }
}
