//
// Copyright (C) 1995-1997 by Autodesk, Inc.
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
#include <string.h>

const UInt32 kMyfMagic = 0x183ac64f;

struct MyfHeader
{
    UInt32 magic;
    UInt16 width;
    UInt16 height;
    UInt16 bitsPerPixel;	//must be 8, 24, 32
    
    MyfHeader() : magic(kMyfMagic), width(0), height(0), bitsPerPixel(0) {}
    AiBoolean isValid() const 
    	{ return magic == kMyfMagic && width && height && bitsPerPixel; }
};

/*** FILE READER ***/
class MyfReader : public IeFileInterface
{
  public:
    MyfReader(IeFileAccess *pFio) : mpFio(pFio) {}
    ~MyfReader() { imageClose(); }
    
    AiBoolean imageOpen(IeOpenMode openMode);
    void imageClose() { mpFio->imageCloseFile(); }
    AiBoolean openAccess() { return mpFio->imageOpenAccess(); }
    void closeAccess() { mpFio->imageCloseAccess(); }
    
    AiBoolean imageReadRow(UInt row, void *pBuf);   
    AiBoolean getImageInfo(UInt tag, void *pBuf);

  private:
    IeFileAccess *mpFio;
    MyfHeader mHeader;
    Int mImageStartPos;
    UInt mBytesPerRow;
};

AiBoolean MyfReader::imageOpen(IeOpenMode openMode)
{
    if (openMode != IE_OM_READONLY ||
        !mpFio->imageOpenFile(openMode) || 
        mpFio->imageReadFile(&mHeader, sizeof(mHeader)) != sizeof(mHeader) || 
        !mHeader.isValid())
        return FALSE;
    mImageStartPos = mpFio->imageTell();
    mBytesPerRow = mHeader.bitsPerPixel / 8 * mHeader.width;
    return TRUE;
}

AiBoolean MyfReader::imageReadRow(UInt row, void *pDest)
{
    if (row == 0 && mpFio->imageSeekFile(mImageStartPos, IE_SEEK_SET) 
    		    != mImageStartPos)		//restart read
        return FALSE;
    return mpFio->imageReadFile(pDest, mBytesPerRow) == mBytesPerRow;
}

AiBoolean MyfReader::getImageInfo(UInt tag, void *pReturn)
{
    UInt val;
    switch (tag) 
    {
      case TAG_BITSPERSAMPLE:
        val = 8;
        break;
        
      case TAG_SAMPLESPERPIXEL:
        val = mHeader.bitsPerPixel / 8;
        break;
        
      case TAG_EXTRASAMPLES:
        if (mHeader.bitsPerPixel != 32)
            return FALSE;
        val = EXTRASAMPLES_UNKNOWN;
        break;
        
      case TAG_PHOTOMETRIC:
        val = mHeader.bitsPerPixel == 8 ? PHOTOMETRIC_MINISBLACK : PHOTOMETRIC_RGB;
        break;
        
      case TAG_IMAGEWIDTH:
        val = mHeader.width;
        break;
        
      case TAG_IMAGELENGTH:
        val = mHeader.height;
        break;
      case TAG_COMPRESSION:
        *(char **)pReturn = "UNCOMPRESSED";
        return TRUE;
        break;

    default:
        return FALSE;
    }

    *(UInt*) pReturn = val;
    return TRUE;
}


/*** FILE ANALYZER ***/
static const char kFileType[] = "MYF";
static const char kVendor[] = "Autodesk";
static const char kFormatName[] = "My Simple File Reader";
static char * const kpFileSuffixes[] = { "myf", 0 };
static const char kCopyrightNotice[] = "Copyright (c) 1995-1997 Autodesk, Inc.";

class MyfReadAnalyzer : public IeFileAnalyzer
{
  public:
    MyfReadAnalyzer() {}
    ~MyfReadAnalyzer() {}
    
    IeFileMatch isItMine(IeFileAccess *pAccess, char const *pId);
    IeFileInterface *makeReader(IeFileAccess *pFio) 
    	{ return new MyfReader(pFio); }

    const char *fileType() const { return kFileType; }
    const char *fileVendor() const { return kVendor; }
    const char *fileFormatName() const { return kFormatName; }
    char * const *fileSuffixes() const { return kpFileSuffixes; }
    const char *copyRightNotice() const { return kCopyrightNotice; }
};

IeFileMatch MyfReadAnalyzer::isItMine(IeFileAccess *pFio, char const *pId) 
{
    UInt buf;

    if ((!pId || 0 == strcmp(pId, kFileType)) 
        && pFio->imageReadFile(&buf, sizeof(buf)) == sizeof(buf)
        && buf == kMyfMagic)
        return IE_FM_IS_MY_TYPE;
    else
        return IE_FM_NOT_MY_TYPE;
}

IeFileAnalyzer *newIeFileAnalyzer() 
{
    return new MyfReadAnalyzer;
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
