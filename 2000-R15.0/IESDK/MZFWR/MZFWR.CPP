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

#include <afxwin.h>
#include <ieapiif.h>
#include <ieapienc.h>
#include <string.h>

#include "mzfres.h"
#include "mzf.h"


/*** ENCODER ***/
class MzfRleEncoder : public IeCodecInterface
{
  public:
    MzfRleEncoder() : mpOut(NULL), mRemaining(0) {}
    ~MzfRleEncoder() {}
    void preProcessChunk(Int numPixels, Int bitsPerPixel) 
        { mBytesPerRow = numPixels * bitsPerPixel / 8; }
    AiBoolean processRow(void *pRow);
    void postProcessChunk() {};
    void setEncBuffer(void IE_HUGE *p, UInt s) { mpOut = (UInt8 IE_HUGE *) p; mRemaining = s; } 
    Int getNumBytesRemaining() const { return mRemaining; }
    const char *getCodecName() const { return codecMethodTable[2]; }
    const IeCodecType getCodecType() const { return IE_ENCODER; }
    Int getMaxEncRowSize(Int bytesPerRow) const { return 2 * bytesPerRow; }
    AiBoolean isBitsPerPixelCompatible(unsigned long ulBitsPerPixel) const { return (ulBitsPerPixel == 8); }
     
    IeCodecInterface *duplicate() { return new MzfRleEncoder; }

  private:
    UInt8 IE_HUGE *mpOut;
    Int mRemaining;
    UInt mBytesPerRow;
};

AiBoolean MzfRleEncoder::processRow(void *pRow)
{
    UInt8 IE_HUGE *pDest = mpOut;
    UInt8 *pSrc = (UInt8*) pRow;
    UInt8 *pEnd = pSrc + mBytesPerRow;
    UInt8 val = *pSrc++;
    UInt count = 1;
    while (pSrc < pEnd)            //simple PCX-style RLE for palette images
    {
        UInt8 v = *pSrc++;
        if (v == val && count < 63)
            count++;
        else
        {
            if (count > 1 || (val & 0xc0) == 0xc0)
                 *pDest++ = UInt8(count) | 0xc0;
            *pDest++ = val;
            val = v;
            count = 1;
        }
    }
    if (count > 1 || (val & 0xc0) == 0xc0)
        *pDest++ = UInt8(count |= 0xc0);
    *pDest++ = val;

    UInt delta = pDest - mpOut;    
    mRemaining -= delta;
    mpOut = pDest;
    return mRemaining >= 0;     //buffer overrun
}


/*** OPTIONS DIALOG ***/

class MzfDll : public CWinApp
{
  public:
    MzfDll() : CWinApp() {}
    BOOL InitInstance() { SetDialogBkColor(); return TRUE; }    
};
static MzfDll mzfDll;

class MzfDlg : public CDialog
{
  public:
    MzfDlg(CWnd* pParent) : CDialog(IDD_OPTIONSDLG, pParent) {}

    int mEnc;
    UINT mStripHeight;

  protected:
    void DoDataExchange(CDataExchange* pDX);
    BOOL OnInitDialog(); 
};

void MzfDlg::DoDataExchange(CDataExchange* pDX) 
{ 
    CDialog::DoDataExchange(pDX);
    DDX_CBIndex(pDX, IDC_ENCODING, mEnc);
    DDX_Text(pDX, IDC_ROWSPERSTRIP, mStripHeight); 
}

BOOL MzfDlg::OnInitDialog()
{ 
    CDialog::OnInitDialog(); 
    CenterWindow(); 
    return TRUE;
} 

/*** FILE ANALYZER ***/
class MzfWriteAnalyzer : public IeFileAnalyzer
{
  public:
    MzfWriteAnalyzer() : mEnc(0), mStripHeight(16) {}
    
    IeFileMatch isItMine(IeFileAccess *pAccess, char const *pId);
    IeFileInterface *makeWriter(IeFileAccess *pFio);

    AiBoolean getFileCaps(UInt tag, void *pVal) const;
    AiBoolean putOptionsVal(UInt tag, const void *pVal);
    AiBoolean getOptionsVal(UInt tag, void *pVal) const;
    IeDialogStatus doOptionsDialog(CsHwnd hWnd);

    const char *fileType() const { return kFileType; }
    const char *fileVendor() const { return kVendor; }
    const char *fileFormatName() const { return kWriterName; }
    char * const *fileSuffixes() const { return kpFileSuffixes; }
    const char *copyRightNotice() const { return kCopyrightNotice; }
    
    int mEnc;
    int mStripHeight;
};

/*** FILE WRITER ***/
class MzfWriter : public IeFileInterface
{
  public:
    MzfWriter(IeFileAccess *pFio, MzfWriteAnalyzer *pAnalyzer);
    ~MzfWriter();
    AiBoolean imageOpen(IeOpenMode openMode);
    void imageClose(){};
    
    AiBoolean imageWriteRow(UInt row, const void *pBuf);
    AiBoolean imageWriteEncChunk(Int strip, const void *pBuf, Int numBytes);
    
    AiBoolean getImageInfo(UInt tag, void *pVal);
    AiBoolean putImageInfo(UInt tag, const void *pVal);
    IeDialogStatus doOptionsDialog(CsHwnd hWnd);    
    IeCodecInterface *makeEncoder()
        { return mHeader.encoding == 2 ? new MzfRleEncoder : NULL; }

  private:
    AiBoolean writeHeader();
    
    MzfWriteAnalyzer *mpAnalyzer;
    IeFileAccess *mpFio;
    MzfHeader mHeader;		
    UInt mNumStrips;		//total number of strips
    MzfStrip *mpStripTable;
    Int mStrip;			//current strip
    AiBoolean mDoThumbnail;     //TRUE while writing thumbnail
};

/*** DLL INTERFACE ***/
IeFileAnalyzer *newIeFileAnalyzer() 
{
    return new MzfWriteAnalyzer;
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

/*** FILE ANALYZER ***/
IeFileMatch MzfWriteAnalyzer::isItMine(IeFileAccess*, char const *pId) 
{
    return pId && 0 == strcmp(pId, kFileType) 
    	? IE_FM_IS_MY_TYPE : IE_FM_NOT_MY_TYPE;
}

IeFileInterface *MzfWriteAnalyzer::makeWriter(IeFileAccess *pFio) 
{ 
    return new MzfWriter(pFio, this);
}

AiBoolean MzfWriteAnalyzer::putOptionsVal(UInt tag, const void *pVal)
{
    UInt val = *(UInt*) pVal;
    switch (tag) 
    {
      case TAG_COMPRESSION:
        if (val >= NUM_ENCODERS)
            break;;
        mEnc = val;
        return TRUE;
      case TAG_CHUNKLENGTH:
      case TAG_ROWSPERSTRIP:
        mStripHeight = val;
        return TRUE;
      default:
        break;
    }
    return FALSE;
}

AiBoolean MzfWriteAnalyzer::getOptionsVal(UInt tag, void *pVal) const
{
    switch (tag)
    {
      case TAG_COMPRESSION:
        *(UInt*) pVal = mEnc;
        return TRUE;
      case TAG_CHUNKLENGTH:
      case TAG_ROWSPERSTRIP:
        *(UInt*) pVal = mStripHeight;
        return TRUE;
      default:
        break;
    }
    return FALSE;
}

AiBoolean MzfWriteAnalyzer::getFileCaps(UInt tag, void *pVal) const
{
    switch (tag)
    {
      case TAG_COMPRESSION:
        *(const char***) pVal = codecMethodTable;
        return TRUE;
      case TAG_MAXTHUMBWIDTH:
        *(UInt*)pVal = UInt(-1L);		//support any size
        return TRUE;
      default:
        break;
    }
    return FALSE;
}

IeDialogStatus MzfWriteAnalyzer::doOptionsDialog(CsHwnd hWnd)
{
    MzfDlg dlg(CWnd::FromHandle((HWND)hWnd));
    dlg.mEnc = mEnc;
    dlg.mStripHeight = mStripHeight;
    if (dlg.DoModal() != IDOK)
        return IE_DIALOG_CANCEL;
    mEnc = dlg.mEnc;
    mStripHeight = dlg.mStripHeight;
    return IE_DIALOG_OK;
}


/*** FILE WRITER ***/
MzfWriter::MzfWriter(IeFileAccess *pFio, MzfWriteAnalyzer *pAnalyzer) 
  : mpFio(pFio),
    mpAnalyzer(pAnalyzer),
    mpStripTable(NULL),
    mStrip(-1),
    mDoThumbnail(FALSE) 
{ 
    mHeader.encoding = pAnalyzer->mEnc; 
    mHeader.stripHeight = pAnalyzer->mStripHeight;
}

AiBoolean MzfWriter::imageOpen(IeOpenMode openMode)
{
    if (openMode != IE_OM_READWRITE)
    	return FALSE;
    return mpFio->imageOpenFile(openMode);
}

MzfWriter::~MzfWriter()
{   
    if (mpStripTable)
    {
        mpFio->imageSeekFile(sizeof(mHeader), IE_SEEK_SET);
        mpFio->imageWriteFile(mpStripTable, mNumStrips * sizeof(MzfStrip));
        delete [] mpStripTable;
        mpStripTable = NULL;
        mStrip = -1;
    }
    if (mDoThumbnail)   // write thumbwidth and thumbheight to file
    {
        mpFio->imageSeekFile(4, IE_SEEK_SET);  	    //after magic
        mpFio->imageWriteFile(&mHeader.width, 4);   //4 bytes
    }
    mpFio->imageCloseFile();
}

AiBoolean MzfWriter::writeHeader()
{
    if (!mHeader.stripHeight || mHeader.stripHeight > mHeader.height)
        mHeader.stripHeight = mHeader.height;
    if (!mHeader.isValid() || 
        mpFio->imageSeekFile(0, IE_SEEK_SET) != 0 || 
        mpFio->imageWriteFile(&mHeader, sizeof(mHeader)) != sizeof(mHeader))
        return FALSE;

    mNumStrips = (mHeader.height + mHeader.stripHeight - 1) / mHeader.stripHeight;
    delete [] mpStripTable;
    mpStripTable = new MzfStrip[mNumStrips];
    mpFio->imageSeekFile(mNumStrips * sizeof(MzfStrip), IE_SEEK_CUR);  //reserve space for strip table
    return TRUE;
}

AiBoolean MzfWriter::imageWriteRow(UInt row, const void *pSrc)
{
    //called for contiguous uncompressed data and the thumbnail
    if (row == 0 && !mDoThumbnail && !writeHeader())	//first image row
            return FALSE;
    return mpFio->imageWriteFile(pSrc, mHeader.width) == mHeader.width;
}

AiBoolean MzfWriter::imageWriteEncChunk(Int strip, const void *pSrc, Int numBytes)
{
    //called for multi-strip uncompressed and any compressed data
    if (strip != mStrip)		//new strip
    {
        if (mStrip == -1 && !writeHeader())
            return FALSE;
        if (UInt(strip) >= mNumStrips)
            return FALSE; 
        mStrip = strip;
        mpStripTable[strip].size = 0;
        mpStripTable[strip].offset = mpFio->imageTell();
    }

    mpStripTable[strip].size += UInt16(numBytes);    
    return mpFio->imageWriteFile(pSrc, numBytes) == UInt(numBytes);
}    
        
AiBoolean MzfWriter::getImageInfo(UInt tag, void *pVal)
{
    if (mDoThumbnail)
       return FALSE;	//contiguous uncompressed for thumbnails
    switch (tag)
    {
       case TAG_ROWSPERSTRIP:
       case TAG_CHUNKLENGTH:
          *(UInt*) pVal = !mHeader.stripHeight || mHeader.stripHeight >= mHeader.height 
          	? mHeader.height : mHeader.stripHeight;
          return TRUE;

       case TAG_COMPRESSION:
          *(const char**) pVal = codecMethodTable[mHeader.encoding];
          return TRUE;
         
      default: break;
    }
    return FALSE;
}

AiBoolean MzfWriter::putImageInfo(UInt tag, const void *pVal)
{
    UInt val = *(UInt*) pVal;
    switch (tag) 
    {
      case TAG_SUBFILETYPE:	//accept only one thumbnail
        return mDoThumbnail = (!mDoThumbnail && val == FILETYPE_REDUCEDIMAGE);
        
      case TAG_BITSPERSAMPLE:
        return val == 8;
      
      case TAG_ROWSPERSTRIP:
      case TAG_CHUNKLENGTH:
        mHeader.stripHeight = UInt16(val);
        return TRUE;
                
      case TAG_SAMPLESPERPIXEL:
        return val == 1;
          
      case TAG_PHOTOMETRIC:
        return val == PHOTOMETRIC_PALETTE;

      case TAG_COLORMAP:
        memcpy(mHeader.palette, (void*) val, 1024);   //8-bit data only for now
        mHeader.magic = kMzfMagic;	              //indicate that palette has been set
        return TRUE;
               
      case TAG_IMAGEWIDTH:
        mHeader.width = UInt16(val);
        return TRUE;
        
      case TAG_IMAGELENGTH:
        mHeader.height = UInt16(val);
        return TRUE;

      case TAG_COMPRESSION:
        if (val >= NUM_ENCODERS)
            return FALSE;
        mHeader.encoding = UInt16(val);
        return TRUE;
        
      default: break;
    }
    return FALSE;
}

IeDialogStatus MzfWriter::doOptionsDialog(CsHwnd hWnd)
{
    MzfDlg dlg(CWnd::FromHandle((HWND)hWnd));
    dlg.mEnc = mHeader.encoding;
    dlg.mStripHeight = mHeader.stripHeight;
    if (dlg.DoModal() != IDOK)
        return IE_DIALOG_CANCEL;

    /*** get settings and save any changes to analyzer ***/
    if (mHeader.encoding != dlg.mEnc)
        mpAnalyzer->mEnc = mHeader.encoding = dlg.mEnc;
    if (mHeader.stripHeight != dlg.mStripHeight)
        mpAnalyzer->mStripHeight = mHeader.stripHeight = dlg.mStripHeight;
    return IE_DIALOG_OK;
}
    
