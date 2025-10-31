//
// Copyright (C) 1994-1998 by Autodesk, Inc.
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

// file i/o related declarations

#ifndef	_iefdesc_h
#define	_iefdesc_h

class IeImg;

class IeFileDesc
{
  public:
    IeFileDesc();
    IeFileDesc(const IeFileDesc& oldFD);
    ~IeFileDesc();
    const IeFileDesc& operator=(const IeFileDesc& rhs);
    AiBoolean isValid() const;

    /*** CONSTRUCTORS ***/
    enum OpenMode { openRead, openWrite };
    
    IeFileDesc(const char *fileName,
    	       const char *fileType=NULL,
    	       OpenMode openMode=openRead);
    IeFileDesc(void *fileHandle,
    	       const char *fileType=NULL,
    	       OpenMode openMode=openRead);

    IeFileDesc(const char *fileName,
    	       const IeFileDesc& alikeFD,
    	       OpenMode openMode=openWrite);
    IeFileDesc(void *fileHandle,
    	       const IeFileDesc& alikeFD,
    	       OpenMode openMode=openWrite);
    
    /*** COMMON MEMBERS ***/
    const char *fileName() const;
    const char *fileType() const;
    OpenMode openMode() const;
    const char *codecMethod() const;
    
    const char *formatName() const;
    const char **fileSuffixes() const;
    const char *vendorName() const;
    const char *copyrightNotice() const;

    AiBoolean getAttribute(UInt tag, void *pReturn) const;
    AiBoolean setAttribute(UInt tag, const void *pVal);

    const IeSize& thumbnailSize() const;

    UInt numFrames() const;
    UInt frame() const;
    UInt advanceFrame(Int numFrames=1);

    enum DialogStatus { dsNotSupported, dsOk, dsCancel };
    DialogStatus doAboutDialog(CsHwnd hWnd=0) const;
    
    /*** MEMBERS FOR READ FILE DESCRIPTORS ***/
    const IeSize& size() const;
    const IePixTyp& pixTyp() const;
    const CsSpace& colorSpace() const;
    
    Ief *read(const IeSize& size=ieSizeFull);

    /*** MEMBERS FOR WRITE FILE DESCRIPTORS ***/
    AiBoolean isCompatible(const IePixTyp& pixTyp) const;
    AiBoolean isCompatible(const CsSpace& colorSpace) const;
    AiBoolean isCompatible(const IeImg& image) const;
    AiBoolean isCompatible(Ief *input) const;
    
    AiBoolean setCodecMethod(const char *codecMethod);
    AiBoolean getCapability(UInt tag, void *pReturn) const;

    AiBoolean getOption(UInt tag, void *pReturn) const;
    AiBoolean setOption(UInt tag, const void *pVal);
    DialogStatus doOptionsDialog(CsHwnd hWnd=0);
    
    AiBoolean write(Ief *input,
    		    AiBoolean thumbnail=FALSE);
    const IeFileDesc& operator=(Ief *input);

    CSMT_ONLY(static IEDLLEXPORT CsCriticalSection msLock;)		// Critical section for locking images

  private:
    friend class IeImgImp;	
    friend class IeDIBImp;	
    void clone();
    class IeFileDescRep *mRep;
};

class IeFileDescRep
{
  public:
    virtual ~IeFileDescRep() {}
	virtual UInt& rc() const = 0;
    virtual AiBoolean isValid() const = 0;
    virtual const IeSize& size() const = 0;
    virtual const IeSize& thumbnailSize() const = 0;
    virtual const IePixTyp& pixTyp() const = 0;
    virtual const CsSpace& colorSpace() const = 0;
    virtual AiBoolean isCompatible(const IeImg&) = 0;
    virtual AiBoolean isCompatible(Ief*) = 0;
    virtual AiBoolean setPixTyp(const IePixTyp&) = 0;
    virtual AiBoolean setColorSpace(const CsSpace&) = 0;
    virtual const char *fileName() const = 0;
    virtual const char *fileType() const = 0;
    virtual IeFileDesc::OpenMode openMode() const = 0;
    virtual const char *codecMethod() const = 0;
    virtual AiBoolean setCodecMethod(const char*) = 0;
    virtual UInt advanceFrame(Int) = 0;
    virtual UInt frame() const = 0;
    virtual UInt numFrames() const = 0;
    virtual Ief *read(const IeSize&) = 0;
    virtual AiBoolean write(Ief*, AiBoolean, CsThreadLock&) = 0;
    virtual const char *formatName() const = 0;
    virtual const char **fileSuffixes() const = 0;
    virtual const char *vendorName() const = 0;
    virtual const char *copyrightNotice() const = 0;    
    virtual AiBoolean getAttribute(UInt, void*) const = 0;
    virtual AiBoolean setAttribute(UInt, const void*) = 0;
    virtual AiBoolean getCapability(UInt, void*) const = 0;
    virtual AiBoolean getOption(UInt, void*) const = 0;
    virtual AiBoolean setOption(UInt, const void*) = 0;
    virtual UInt doOptionsDialog(UInts, CsThreadLock&) = 0;
    virtual UInt doAboutDialog(UInts, CsThreadLock&) const = 0;
    virtual void *makeReader() const = 0;
};

extern "C" IeFileDescRep * ieFileDescConstructor1();
extern "C" IeFileDescRep * ieFileDescConstructor2(
	const char*, const char*, IeFileDesc::OpenMode);
extern "C" IeFileDescRep * ieFileDescConstructor3(
	void*, const char*, IeFileDesc::OpenMode);
extern "C" IeFileDescRep * ieFileDescConstructor4(
	const char*, const IeFileDescRep*, IeFileDesc::OpenMode);
extern "C" IeFileDescRep * ieFileDescConstructor5(
	void*, const IeFileDescRep*, IeFileDesc::OpenMode);

/*** INLINES ***************************************************************/

INLINE IeFileDesc::IeFileDesc()
  : mRep(ieFileDescConstructor1())
{}

INLINE IeFileDesc::IeFileDesc(const IeFileDesc& a)
{
    CSMT_LOCK(lock, msLock);
    mRep = a.mRep;
    mRep->rc()++;
}

INLINE IeFileDesc::IeFileDesc(const char *a, const char *b, 
			      IeFileDesc::OpenMode c)
  : mRep(ieFileDescConstructor2(a, b, c))
{}

INLINE IeFileDesc::IeFileDesc(void *a, const char *b, 
			      IeFileDesc::OpenMode c)
  : mRep(ieFileDescConstructor3(a, b, c))
{}

INLINE IeFileDesc::IeFileDesc(const char *a, const IeFileDesc& b,
			      IeFileDesc::OpenMode c)
  : mRep(ieFileDescConstructor4(a, b.mRep, c))
{}

INLINE IeFileDesc::IeFileDesc(void *a, const IeFileDesc& b,
			      IeFileDesc::OpenMode c)
  : mRep(ieFileDescConstructor5(a, b.mRep, c))
{}

INLINE IeFileDesc::~IeFileDesc()
{
    CSMT_LOCK(lock, msLock);
    if (mRep && !--mRep->rc())
    	delete mRep;
}

INLINE const IeFileDesc& IeFileDesc::operator=(const IeFileDesc& a)
{
    CSMT_LOCK(lock, msLock);
	if (mRep != a.mRep) {
		if (!--mRep->rc())
			delete mRep;
		a.mRep->rc()++;
		mRep = a.mRep;
	}
    return *this;
}

INLINE const IeFileDesc& IeFileDesc::operator=(Ief *a)
{
    CSMT_LOCK(lock, msLock);
    mRep->write(a, FALSE, lock);
    return *this;
}

INLINE AiBoolean IeFileDesc::isValid() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->isValid();
}

INLINE const IeSize& IeFileDesc::size() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->size();
}

INLINE const IePixTyp& IeFileDesc::pixTyp() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->pixTyp();
}

INLINE const CsSpace& IeFileDesc::colorSpace() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->colorSpace();
}

INLINE AiBoolean IeFileDesc::isCompatible(const IeImg& a) const
{
    CSMT_LOCK(lock, msLock);
    return mRep->isCompatible(a);
}

INLINE AiBoolean IeFileDesc::isCompatible(const CsSpace& a) const
{
    CSMT_LOCK(lock, msLock);
    return mRep->setColorSpace(a);
}

INLINE AiBoolean IeFileDesc::isCompatible(const IePixTyp& a) const
{
    CSMT_LOCK(lock, msLock);
    return mRep->setPixTyp(a);
}

INLINE AiBoolean IeFileDesc::isCompatible(Ief *a) const
{
    CSMT_LOCK(lock, msLock);
    return mRep->isCompatible(a);
}

INLINE const char *IeFileDesc::fileName() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->fileName();
}

INLINE const char *IeFileDesc::fileType() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->fileType();
}

INLINE IeFileDesc::OpenMode IeFileDesc::openMode() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->openMode();
}

INLINE const char *IeFileDesc::codecMethod() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->codecMethod();
}

INLINE AiBoolean IeFileDesc::setCodecMethod(const char *a)
{
    CSMT_LOCK(lock, msLock);
    return mRep->setCodecMethod(a);
}

INLINE UInt IeFileDesc::advanceFrame(Int a)
{
    CSMT_LOCK(lock, msLock);
    return mRep->advanceFrame(a);
}

INLINE UInt IeFileDesc::frame() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->frame();
}

INLINE UInt IeFileDesc::numFrames() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->numFrames();
}

INLINE const IeSize& IeFileDesc::thumbnailSize() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->thumbnailSize();
}

INLINE Ief* IeFileDesc::read(const IeSize& a)
{
    CSMT_LOCK(lock, msLock);
    return mRep->read(a);
}

INLINE AiBoolean IeFileDesc::write(Ief *a, AiBoolean b)
{
    CSMT_LOCK(lock, msLock);
    return mRep->write(a, b, lock);
}
    
INLINE const char *IeFileDesc::formatName() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->formatName();
}

INLINE const char **IeFileDesc::fileSuffixes() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->fileSuffixes();
}

INLINE const char *IeFileDesc::vendorName() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->vendorName();
}

INLINE const char *IeFileDesc::copyrightNotice() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->copyrightNotice();
}

INLINE AiBoolean IeFileDesc::getAttribute(UInt a, void *b) const
{
    CSMT_LOCK(lock, msLock);
    return mRep->getAttribute(a, b);
}

INLINE AiBoolean IeFileDesc::setAttribute(UInt a, const void *b)
{
    CSMT_LOCK(lock, msLock);
    return mRep->setAttribute(a, b);
}

INLINE AiBoolean IeFileDesc::getCapability(UInt a, void *b) const
{
    CSMT_LOCK(lock, msLock);
    return mRep->getCapability(a, b);
}

INLINE AiBoolean IeFileDesc::getOption(UInt a, void *b) const
{
    CSMT_LOCK(lock, msLock);
    return mRep->getOption(a, b);
}

INLINE AiBoolean IeFileDesc::setOption(UInt a, const void *b)
{
    CSMT_LOCK(lock, msLock);
    return mRep->setOption(a, b);
}

INLINE IeFileDesc::DialogStatus IeFileDesc::doOptionsDialog(CsHwnd hWnd)
{
    CSMT_LOCK(lock, msLock);
    return (DialogStatus) mRep->doOptionsDialog(hWnd, lock);
}

INLINE IeFileDesc::DialogStatus IeFileDesc::doAboutDialog(CsHwnd hWnd) const
{
    CSMT_LOCK(lock, msLock);
    return (DialogStatus) mRep->doAboutDialog(hWnd, lock);
}

#endif	/* ifndef _iefdesc_h */
