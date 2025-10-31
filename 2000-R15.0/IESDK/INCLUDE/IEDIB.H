//
// Copyright (C) 1995-1998 by Autodesk, Inc.
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

// iedib.h - IE DIB Image Class Hierarchy Definition

#ifndef _iedib_h
#define _iedib_h

#ifndef _WINDOWS_
#include <windows.h> //TODO FIXME must undefine for autocad
#endif

class IeDIBRep;

class IeDIB
{
  public:
    enum Format { same, asIndexed, as16BGR, as24BGR, as32BGR };
    IeDIB();
    IeDIB(const IeDIB&);
    IeDIB(const IeSize& size, 	                //general image
          IePixTyp pixTyp=IePixTyp::u8_1, 
          const CsSpace& colorSpace=csNone);
    IeDIB(void *pData,				//static contiguous raster
          const IeSize& size, 
          IePixTyp pixTyp, 
          const CsSpace& colorSpace=csNone);
    IeDIB(Ief *input, Format dibType=same);     //from pipeline
    IeDIB(const IeFileDesc& fd, AiBoolean flush=TRUE,
                         Format dibType=same);  //from file
    IeDIB(const char *fileName, Format dibType=same);

    IeDIB(BITMAPINFO* pBMI, void* pBits, Format dibType=same); 
    IeDIB(BITMAPINFO* pPackedDIB, Format dibType=same);
    IeDIB(const IeSize& size, const IePixTyp& pixTyp, HPALETTE hPal);
    IeDIB(Int width, Int height, Int bitsPerPixel, HPALETTE hPal);

    ~IeDIB();

    const IeDIB& operator=(const IeDIB&);
    const IeDIB& operator=(Ief*);

    AiBoolean isValid() const;

    void *pData() const;
    void *dataPtr() const;
    BITMAPINFO *bitmapInfo() const;
    RGBQUAD *colorTable() const;
    HPALETTE palHandle() const;

    const IeSize& size() const;
    const IePixTyp& pixTyp() const;
    const CsSpace& colorSpace() const;
    const IeFileDesc& fileDesc() const;
    void setColorSpace(const CsSpace& colorSpace);

    void paint(HDC hDC, const IeOffset& srcPos, 
                            const IeOffset& destPos, const IeSize& destSize);
    void paint(HDC hDC, Int srcX, Int srcY, const RECT& destRect);

    AiBoolean storeFile(IeFileDesc& fd) const;
    AiBoolean storeFile(const char *fileName, const char *fileType) const;
    
    enum Access { leftTop, rightTop, leftBot, rightBot, 
		  topLeft, topRight, botLeft, botRight,
		  normal=0, flipHoriz, flipVert, rotate180,
		  transpose, rotate270, rotate90, transposeAnti,
		  columnMajor=0x4, yDecrement=0x2, xDecrement=0x1 };
    Ief *read(const IeSize& size=ieSizeFull,
	      const IeOffset& offset=ieOffsetOrigin,
	      Access access=normal,
	      Int extractBand=-1) const;
    void write(Ief *input);
    void paste(Ief *input,
	       const IeOffset& offset,
	       Int insertBand=-1,
	       const Real *pClipPolygon=NULL,
	       Int numVertices=0,
	       const IePixel& transparentVal=iePixelNull);

    void clear(const IePixel& val,
	       const IeSize& size=ieSizeFull,
	       const IeOffset& offset=ieOffsetOrigin);
    void clear(UInt val=0,
	       const IeSize& size=ieSizeFull,
	       const IeOffset& offset=ieOffsetOrigin);
    
    UInt refCount() const;

    CSMT_ONLY(static IEDLLEXPORT CsCriticalSection msLock;)		// Critical section for locking images

  private:
    IeDIBRep *mRep;
    public: IeDIB(CsVoid) {}
};

class IeDIBRep
{
  public:
    virtual ~IeDIBRep() {}
	virtual UInt& rc() const = 0;
    virtual AiBoolean isValid() const = 0;
    virtual void *pData() const = 0;
    virtual BITMAPINFO *bitmapInfo() const = 0;
    virtual RGBQUAD *colorTable() const = 0;
    virtual HPALETTE palHandle() const = 0;
    virtual const IeSize& size() const = 0;
    virtual const IePixTyp& pixTyp() const = 0;
    virtual const CsSpace& colorSpace() const = 0;
    virtual const IeFileDesc& fileDesc() const = 0;
    virtual void setColorSpace(const CsSpace&) = 0;
    virtual void paint(HDC,const IeOffset&,const IeOffset&,const IeSize&) = 0;
    virtual AiBoolean storeFile(IeFileDesc&, CsThreadLock&) const = 0;
    virtual Ief *read(const IeSize&,const IeOffset&, IeDIB::Access, Int) = 0;
    virtual void paste(Ief*, const IeOffset&, Int, const Real*, Int, 
    		       const IePixel&, CsThreadLock&, AiBoolean) = 0;
    virtual void clear(const IePixel&, const IeSize&, const IeOffset&, CsThreadLock&) = 0;
    virtual void clear(UInt, const IeSize&, const IeOffset&, CsThreadLock&) = 0;
    virtual UInt refCount() const = 0;
};

extern "C" {
IeDIBRep * ieDIBRepConstructor1(BITMAPINFO*, void*, IeDIB::Format );
IeDIBRep * ieDIBRepConstructor4(BITMAPINFO*, IeDIB::Format);
IeDIBRep * ieDIBRepConstructor5(const IeSize&, 
        const IePixTyp&, HPALETTE);        
IeDIBRep * ieDIBRepConstructor2(const IeSize&, 
	const IePixTyp&, const CsSpace&);
IeDIBRep * ieDIBRepConstructor3(Ief*, IeDIB::Format, CsThreadLock& lock);
IeDIBRep * ieDIBRepConstructor6(void*, const IeSize&, 
	const IePixTyp&, const CsSpace&);
IeDIBRep * ieDIBRepConstructor7(const IeFileDesc&,
        AiBoolean, IeDIB::Format, CsThreadLock&);
IeDIBRep * ieDIBRepConstructor8(const char *, IeDIB::Format, CsThreadLock&);
}

extern IEDLLEXPORT const IeDIB ieDIBNull;

/*** INLINES ***/
INLINE IeDIB::IeDIB(BITMAPINFO* a, void* b, Format c)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieDIBRepConstructor1(a, b, c);
}

INLINE IeDIB::IeDIB(BITMAPINFO* a, Format b)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieDIBRepConstructor4(a,b);
}

INLINE IeDIB::IeDIB(const IeSize& a, const IePixTyp& b, HPALETTE c)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieDIBRepConstructor5(a, b, c);
}

INLINE IeDIB::IeDIB(Int a, Int b, Int c, HPALETTE d)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieDIBRepConstructor5(IeSize(a,b), 
        c > 8 ? IePixTyp::u8_3 : (c == 1 ? IePixTyp::u1_1 : IePixTyp::u8_1), d);
}

INLINE IeDIB::IeDIB()
{
    CSMT_LOCK(lock, msLock);
	mRep = ieDIBNull.mRep;
    mRep->rc()++;
}

INLINE IeDIB::IeDIB(const IeSize& a, IePixTyp b, const CsSpace& c)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieDIBRepConstructor2(a, b, c);
}

INLINE IeDIB::IeDIB(void* a, const IeSize& b, IePixTyp c, const CsSpace& d)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieDIBRepConstructor6(a, b, c, d);
}

INLINE IeDIB::IeDIB(Ief *a, Format b)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieDIBRepConstructor3(a,b,lock);
}

INLINE IeDIB::IeDIB(const IeFileDesc& a, AiBoolean b, Format c)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieDIBRepConstructor7(a,b,c, lock);
}

INLINE IeDIB::IeDIB(const char *a, Format b)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieDIBRepConstructor8(a,b, lock);
}


INLINE IeDIB::IeDIB(const IeDIB& i)
{
    CSMT_LOCK(lock, msLock);
	mRep = i.mRep;
    mRep->rc()++;
}

INLINE IeDIB::~IeDIB()
{ 
    CSMT_LOCK(lock, msLock);
    if (mRep && !--mRep->rc())
        delete mRep;
}

INLINE const IeDIB& IeDIB::operator=(const IeDIB& i)
{
    CSMT_LOCK(lock, msLock);
    if (mRep != i.mRep) {
        i.mRep->rc()++;
        if (!--mRep->rc())
            delete mRep;
        mRep = i.mRep;
    }
    return *this;
}

INLINE const IeDIB& IeDIB::operator=(Ief *a)
{
    CSMT_LOCK(lock, msLock);
    if (!mRep->isValid())
    {
#ifdef CS_MT
        IeDIBRep* newRep = ieDIBRepConstructor3(a,same,lock);
        if (!--mRep->rc())
            delete mRep;
        mRep = newRep;
#else
        if (!--mRep->rc())
            delete mRep;
        mRep = ieDIBRepConstructor3(a,same,lock);
#endif
    }
    else
    	mRep->paste(a, ieOffsetOrigin, -1, NULL, 0, iePixelNull, lock, FALSE);
    return *this;
}

INLINE AiBoolean IeDIB::isValid() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->isValid();
}

INLINE const IeSize& IeDIB::size() const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->size();
}

INLINE const IePixTyp& IeDIB::pixTyp() const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->pixTyp();
}

INLINE const CsSpace& IeDIB::colorSpace() const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->colorSpace();
}

INLINE const IeFileDesc& IeDIB::fileDesc() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->fileDesc();
}

INLINE void IeDIB::setColorSpace(const CsSpace& a)
{ 
    CSMT_LOCK(lock, msLock);
    mRep->setColorSpace(a);
}

INLINE AiBoolean IeDIB::storeFile(IeFileDesc& a) const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->storeFile(a, lock);
}

INLINE AiBoolean IeDIB::storeFile(const char *a, const char *b) const
{
    CSMT_LOCK(lock, msLock);
    IeFileDesc fd(a, b, IeFileDesc::openWrite);
    return mRep->storeFile(fd, lock);
}

INLINE Ief *IeDIB::read(const IeSize& a, const IeOffset& b, IeDIB::Access c, 
    Int d) const
{
    CSMT_LOCK(lock, msLock);
    return mRep->read(a, b, c, d);
}

INLINE void IeDIB::write(Ief *a)
{ 
    CSMT_LOCK(lock, msLock);
    if (mRep->isValid()) {
    	mRep->paste(a, ieOffsetOrigin, -1, NULL, 0, iePixelNull, lock, FALSE);
    } else {
#ifdef CS_MT
		IeDIBRep* newRep = ieDIBRepConstructor3(a,same,lock);
		if (!--mRep->rc())
			delete mRep;
		mRep = newRep;
#else
		if (!--mRep->rc())
			delete mRep;
		mRep = ieDIBRepConstructor3(a,same,lock);
#endif
    }
}

INLINE void IeDIB::paste(Ief *a, const IeOffset& b, Int c, const Real *d,
    Int e, const IePixel& f)
{ 
    CSMT_LOCK(lock, msLock);
    mRep->paste(a, b, c, d, e, f, lock, FALSE);
}

INLINE void *IeDIB::dataPtr() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->pData();
}
INLINE void *IeDIB::pData() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->pData();
}


INLINE BITMAPINFO *IeDIB::bitmapInfo() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->bitmapInfo();
}

INLINE RGBQUAD *IeDIB::colorTable() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->colorTable();
}

INLINE HPALETTE IeDIB::palHandle() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->palHandle();
}

INLINE void IeDIB::paint(HDC a, const IeOffset& b, 
                        const IeOffset& c, const IeSize& d)
{
    CSMT_LOCK(lock, msLock);
    mRep->paint(a, b, c, d);
}
INLINE void IeDIB::paint(HDC a, Int b, Int c, const RECT& d)
{
    CSMT_LOCK(lock, msLock);
    mRep->paint(a, IeOffset(b,c), IeOffset(d.left,d.top),
                                IeSize(d.right-d.left,d.bottom-d.top));
}
INLINE void IeDIB::clear(const IePixel& a, const IeSize& b, const IeOffset& c)
{ 
    CSMT_LOCK(lock, msLock);
    mRep->clear(a, b, c, lock);
}

INLINE void IeDIB::clear(UInt a, const IeSize& b, const IeOffset& c)
{ 
    CSMT_LOCK(lock, msLock);
    mRep->clear(a, b, c, lock);
}

INLINE UInt IeDIB::refCount() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->refCount();
}

#endif /* _iedib_h */
