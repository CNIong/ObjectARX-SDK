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

// Definition of the raster file reader/writer API for the 
// Image Engine.

/*
* Begin multiple inclusion protection...
*/
#ifndef	_ieapiif_h
#define	_ieapiif_h

#pragma pack (push, 8)

/*
* Forward declarations.
*/

class IeCodecInterface;

/*
* Required header files.
*/

#ifndef _csdefs_h
#include <csdefs.h>             // required for typedefs
#endif                

#ifndef _ieapimod_h
#include <ieapimod.h>           // required for module id definitions
#endif

#ifndef _iefileio_h
#include <iefileio.h>           // required for file/stream access
#endif

#ifndef _ieapidef_h
#include <ieapidef.h>           // required for ImageInfo tags
#endif


struct IeErrorCode {
public:
    IeErrorCode(Int i, const char *t) : errorIndex(i), errorText(t) {}
    Int errorIndex;
    const char *errorText;
};

enum IeDialogStatus {
    IE_DIALOG_NOTSUPPORTED,
    IE_DIALOG_OK,
    IE_DIALOG_CANCEL
};

class IeFileInterface {
  public:
    virtual ~IeFileInterface() {}

// Open/Close of the image

    virtual AiBoolean imageOpen(IeOpenMode openMode) = 0;
    
    virtual void imageClose() = 0;

// Access control of the file

    virtual AiBoolean openAccess() { return TRUE; }

    virtual void closeAccess() {}

// Codec making functions

    virtual IeCodecInterface *makeEncoder() {
        return (IeCodecInterface *)0;
    }

    virtual IeCodecInterface *makeDecoder() {
        return (IeCodecInterface *)0;
    }

// virtual functions called when reading a file

    virtual UInt imageAdvanceFrame(Int /*numSteps*/) {
        return 0;
    }

    virtual AiBoolean imageReadRow(UInt /*row*/, void * /*pDest*/) {
        return FALSE;
    }

    virtual AiBoolean imageReadEncChunk(Int /*fileAddr*/, 
                                            void IE_HUGE * /*pDest*/) {
        return FALSE;
    }

    virtual AiBoolean getImageInfo(UInt /*tag*/, void * /*pInfo*/) {
        return FALSE;
    }

// virtual functions called when writing a file

    virtual AiBoolean imageWriteRow(UInt /*row*/, const void * /*pSrc*/) {
        return FALSE;
    }

    virtual AiBoolean imageWriteEncChunk(Int /*fileAddr*/,
                                        const void * /*pSrc*/, Int /*byteCount*/) {
        return FALSE;
    }

    virtual AiBoolean putImageInfo(UInt /*tag*/, const void * /*pInfo*/) {
        return FALSE;
    }

    virtual IeDialogStatus doOptionsDialog(CsHwnd hWnd=0) {
        return IE_DIALOG_NOTSUPPORTED;
    }
    
//  Error Reporting

    virtual IeErrorCode getErrorCode() const {
        return IeErrorCode(0,0);
    }
};

enum IeFileMatch {
    IE_FM_NOT_MY_TYPE,
    IE_FM_MAYBE_MY_TYPE,
    IE_FM_IS_MY_TYPE
};

class IeFileAnalyzer {
  public:
    virtual ~IeFileAnalyzer() {}

// Reader analyzer/constructor functions
    virtual IeFileMatch isItMine(IeFileAccess *pFio, const char *pId = 0) = 0;
    virtual IeFileInterface *makeReader(IeFileAccess *pFio) {
        return (IeFileInterface *)0;
    }

// Writer constructor function 
    virtual IeFileInterface *makeWriter(IeFileAccess *pFio) {
        return (IeFileInterface *)0;
    }

// Reader/Writer information functions
    virtual const char *fileType() const = 0;
    virtual const char *fileVendor() const { return 0; }
    virtual const char *fileFormatName() const { return 0; }
    virtual char * const *fileSuffixes() const { return 0; }
    virtual const char *copyRightNotice() const { return 0; }

    virtual AiBoolean getFileCaps(UInt /*tag*/, void * /*pInfo*/) const {
        return FALSE;
    }

    virtual AiBoolean putOptionsVal(UInt /*tag*/, const void * /*pInfo*/) {
        return FALSE;
    }

    virtual AiBoolean getOptionsVal(UInt /*tag*/, void * /*pInfo*/) const {
        return FALSE;
    }

    virtual IeDialogStatus doOptionsDialog(CsHwnd hWnd=0) {
        return IE_DIALOG_NOTSUPPORTED;
    }
    
    virtual IeDialogStatus doAboutDialog(CsHwnd hWnd=0) {
        return IE_DIALOG_NOTSUPPORTED;
    }

};

// module supplied pseudo constructor

extern "C" IeFileAnalyzer *newIeFileAnalyzer();

#pragma pack (pop)

#endif /* _ieapiif_h */
