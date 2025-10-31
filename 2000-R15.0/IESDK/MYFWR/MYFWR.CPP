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


/*** FILE WRITER ***/
class MyfWriter : public IeFileInterface
{
  public:
    MyfWriter(IeFileAccess *pFio) : mpFio(pFio) {}
    ~MyfWriter() { imageClose(); }
    
    AiBoolean imageOpen(IeOpenMode openMode);
    void imageClose() { mpFio->imageCloseFile(); }
    
    AiBoolean imageWriteRow(UInt row, const void *pBuf);
    AiBoolean putImageInfo(UInt tag, const void *pVal);

  private:
    AiBoolean writeHeader();
    
    IeFileAccess *mpFio;
    MyfHeader mHeader;
    UInt mBytesPerRow;
};

AiBoolean MyfWriter::imageOpen(IeOpenMode openMode)
{
    if (openMode != IE_OM_READWRITE)
    	return FALSE;
    return mpFio->imageOpenFile(openMode);
}

AiBoolean MyfWriter::writeHeader()
{
    if (!mHeader.isValid() || 
        mpFio->imageSeekFile(0, IE_SEEK_SET) != 0 || 
        mpFio->imageWriteFile(&mHeader, sizeof(mHeader)) != sizeof(mHeader))
        return FALSE;

    mBytesPerRow = mHeader.bitsPerPixel / 8 * mHeader.width;
    return TRUE;
}

AiBoolean MyfWriter::imageWriteRow(UInt row, const void *pSrc)
{
    if (row == 0 && !writeHeader())
        return FALSE;

    return mpFio->imageWriteFile(pSrc, mBytesPerRow) == mBytesPerRow;
}

AiBoolean MyfWriter::putImageInfo(UInt tag, const void *pVal)
{
    UInt val = *(UInt*) pVal;
    switch (tag) 
    {
      case TAG_BITSPERSAMPLE:
        if (val != 8)
            return FALSE;
        break;
        
      case TAG_SAMPLESPERPIXEL:
        if (val != 1 && val != 3 && val != 4)
            return FALSE;
        mHeader.bitsPerPixel = UInt16(val * 8);
        break;
      
      case TAG_EXTRASAMPLES:   //supports alpha
        break;
          
      case TAG_PHOTOMETRIC:
        if (val != PHOTOMETRIC_MINISBLACK && val != PHOTOMETRIC_RGB)
            return FALSE;
        break;
        
      case TAG_IMAGEWIDTH:
        mHeader.width = UInt16(val);
        break;
        
      case TAG_IMAGELENGTH:
        mHeader.height = UInt16(val);
        break;

      default:
        return FALSE;
    }
    return TRUE;
}


/*** FILE ANALYZER ***/
static const char kFileType[] = "MYF";
static const char kVendor[] = "Autodesk";
static const char kFormatName[] = "My Simple File Writer";
static char * const kpFileSuffixes[] = { "myf", 0 };
static const char kCopyrightNotice[] = "Copyright (c) 1995-1997 Autodesk, Inc.";

class MyfWriteAnalyzer : public IeFileAnalyzer
{
  public:
    MyfWriteAnalyzer() {}
    ~MyfWriteAnalyzer() {}
    
    IeFileMatch isItMine(IeFileAccess *pAccess, char const *pId);
    IeFileInterface *makeWriter(IeFileAccess *pFio) 
    	{ return new MyfWriter(pFio); }

    const char *fileType() const { return kFileType; }
    const char *fileVendor() const { return kVendor; }
    const char *fileFormatName() const { return kFormatName; }
    char * const *fileSuffixes() const { return kpFileSuffixes; }
    const char *copyRightNotice() const { return kCopyrightNotice; }
};

IeFileMatch MyfWriteAnalyzer::isItMine(IeFileAccess*, char const *pId) 
{
    if (pId && 0 == strcmp(pId, kFileType))
        return IE_FM_IS_MY_TYPE;
    else
        return IE_FM_NOT_MY_TYPE;
}

IeFileAnalyzer *newIeFileAnalyzer() 
{
    return new MyfWriteAnalyzer;
}

const char *moduleIdentify(IeModuleId moduleId) 
{
    switch (moduleId) 
    {
      case IE_IMAGE_SERVICE:  return IE_IMAGE_FILE_SERVICE;
      case IE_SERVICE_TYPE:   return IE_FILE_WRITER;
      default:		      return NULL;
    }
}
