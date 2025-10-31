//
// Copyright (C) 1993-1998 by Autodesk, Inc.
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

// Classes for file access

#ifndef	_iefileio_h
#define	_iefileio_h

#ifndef _csdefs_h
#include <csdefs.h>
#endif

enum IeOpenMode {
    IE_OM_READONLY,
    IE_OM_READWRITE,
    IE_OM_APPEND,
    IE_OM_CREATE
};

enum IeSeekMode {
    IE_SEEK_SET,            // offset is from beginning of file (+)
    IE_SEEK_CUR,            // offset is from current position (+,-)
    IE_SEEK_END             // offset is from end of file (+,-)
};

class IeFileAccess {
  public:
    virtual ~IeFileAccess() {}
    virtual UInt& rc() const = 0;

    virtual void appSetFileName(const char *pName) = 0;
    virtual void appSetHandle(const void *pHandle) = 0;
    virtual void appSetPosition(Int pos) = 0;
    virtual void appSetOpenMode(IeOpenMode openMode,
                                AiBoolean keepOpen=FALSE) = 0;

    virtual AiBoolean imageOpenFile(IeOpenMode openMode ) = 0;
    virtual AiBoolean imageOpenAccess() = 0;
    virtual UInt imageReadFile(void IE_HUGE *buf, Int size ) = 0;
    virtual UInt imageWriteFile(const void IE_HUGE *buf, Int size ) = 0;
    virtual Int imageSeekFile(Int dist, IeSeekMode mode ) = 0;
    virtual void imageCloseAccess() = 0;
    virtual void imageCloseFile() = 0;

    virtual Int imageTell() = 0;
    virtual Int imageGetFileSize() = 0;
    virtual Int imageGetChar() = 0;
    virtual const char *imageGetFileName() const = 0;
    virtual IeOpenMode imageGetMode() const = 0;
};

IEDLLEXPORT IeFileAccess * newIeFileAccess(const char *pAccessID);

#endif	/* ifndef _iefileio_h */
