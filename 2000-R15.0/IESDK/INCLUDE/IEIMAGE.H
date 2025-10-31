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
// ieimage.h - IE Image Class Hierarchy Definition

#ifndef _ieimage_h
#define _ieimage_h

#define IE_IMAGE_SERVICES "Image_Services"

class IeImgRep;
class IeCxt;
class IePixSel;

class IeImg
{
  public:
    IeImg();
    IeImg(const IeImg&);
    IeImg(const IeSize& size, 			//general image
          IePixTyp pixTyp=IePixTyp::u8_1, 
          const CsSpace& colorSpace=csNone,
          const IeSize& tileSize=ieSizeAny);
    IeImg(void *pData,				//static contiguous raster
          const IeSize& size, 
          IePixTyp pixTyp, 
          const CsSpace& colorSpace=csNone);
    IeImg(Ief *input,				//from pipeline
          const IeSize& tileSize = ieSizeAny);
    IeImg(const IeFileDesc& fd,			//from file
    	  AiBoolean flush=FALSE,
    	  const IeSize& tileSize = ieSizeAny);
    IeImg(const char *fileName,
    	  AiBoolean flush=FALSE,
    	  const IeSize& tileSize = ieSizeAny);
    ~IeImg();
    
    const IeImg& operator=(const IeImg&);
    const IeImg& operator=(Ief*);
    AiBoolean operator==(const IeImg&) const;    
    AiBoolean operator!=(const IeImg&) const;    

    AiBoolean isValid() const;
    AiBoolean isContiguous() const;
    AiBoolean isStatic() const;
    AiBoolean isCached() const;    

    const IeSize& size() const;
    const IeSize& tileSize() const;
    const IePixTyp& pixTyp() const;
    const CsSpace& colorSpace() const;
    const IeTile& numTiles() const;
    const IeFileDesc& fileDesc() const;
    void setColorSpace(const CsSpace& colorSpace);
    void setPixTyp(const IePixTyp& pixTyp);

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
    Ief *readModify(const IeSize& size=ieSizeFull,
                    const IeOffset& offset=ieOffsetOrigin,
                    Access access=normal,
                    Int extractBand=-1);
    void write(Ief *input);
    void paste(Ief *input,
	       const IeOffset& offset,
	       Int insertBand=-1,
	       const Real *pClipPolygon=NULL,
	       Int numVertices=0,
	       const IePixel& transparentVal=iePixelNull);

    IeCxt *getReadCxt() const;
    IeCxt *getWriteCxt();
    IeCxt *makeReadCxt(const IeSize& size=ieSizeFull,
		       AiBoolean padRows=FALSE) const; 
    IeCxt *makeWriteCxt(const IeSize& size=ieSizeFull,
			AiBoolean padRows=FALSE);
    void areaFill(const IeOffset *pSeedPoints,
    		  UInt numSeedPoints,
    		  IePixSel *pSelectorFunc,
    		  UInt fillVal,
    		  IeSize& regionSize,
    		  IeOffset& regionOffset);
    void areaFill(const IeImg& mask,
    		  const IeOffset& maskOffset,
    		  IePixSel *pSelectorFunc,
    		  UInt maskVal,
    		  IeSize& regionSize,
    		  IeOffset& regionOffset);
    void clear(const IePixel& val,
	       const IeSize& size=ieSizeFull,
	       const IeOffset& offset=ieOffsetOrigin);
    void clear(UInt val=0,
	       const IeSize& size=ieSizeFull,
	       const IeOffset& offset=ieOffsetOrigin);
    
    enum MemSel { memAll, memShare, memPrivate, ckpAll, ckpShare, ckpPrivate };
    void checkpoint(MemSel=memAll) const;
    void recover(MemSel=memShare, 
    		 AiBoolean forced=FALSE) const;
    UInt memUsed(MemSel sel=memAll) const;
    UInt refCount() const;

    const void *lockToRead(const IeTile& tile=ieOffsetOrigin) const;
    void *lockToWrite(const IeTile& tile=ieOffsetOrigin, 
    		      AiBoolean willReplace=FALSE,
    		      AiBoolean makePrivate=FALSE);
    void unlock(const IeTile& tile=ieOffsetOrigin) const;
    void preserve(const IeTile& tile=ieOffsetOrigin) const;
    void unpreserve(const IeTile& tile=ieOffsetOrigin) const;
    AiBoolean tileHasData(const IeTile& tile) const;
    IeOffset tileOffset(const IeTile& tile) const;
    IeTile whichTile(const IeOffset& imageOffset,
    		     IeOffset *pTileOffset=NULL) const;
    void clearTile(const IeTile& tile, 
    		   const IePixel& val);
    void clearTile(const IeTile& tile, 
    		   UInt val);
    void clearTile(const IeTile& tile);
    void checkpointTile(const IeTile& tile) const;

    CSMT_ONLY(static IEDLLEXPORT CsCriticalSection msLock;)		// Critical section for locking images
	
  private:
    IeImgRep *mRep;

    public: IeImg(CsVoid) {}
};


class IePixSel 
{
    public:
      virtual ~IePixSel() {}
      virtual AiBoolean isSelected(UInt x, UInt y) = 0;
};


extern "C" IePixSel * newIePixSelBitonal(const IeImg& input,
                                                     UInt regVal);

extern "C" IePixSel * newIePixSelRgb(const IeImg& input, 
                                                 const CsRgb8* colorSet,
                                                 UInt numColors,
                                                 Real tolerance,
                                                 AiBoolean inclusive=TRUE);

extern "C" IePixSel * newIePixSelHue(const IeImg& input, 
                                                 const CsRgb8* colorSet,
                                                 UInt numColors,
                                                 Real tolerance,
                                                 AiBoolean inclusive=TRUE);

extern "C" IePixSel * newIePixSelGray(const IeImg& input, 
                                                  const UInt8* graySet,
                                                  UInt numGrays,
                                                  Real tolerance,
                                                  AiBoolean inclusive=TRUE);

class IeImgRep
{
  public:
    virtual ~IeImgRep() {}
    virtual UInt& rc() const = 0;
    virtual AiBoolean isValid() const = 0;
    virtual AiBoolean isContiguous() const = 0;
    virtual AiBoolean isStatic() const = 0;
    virtual AiBoolean isCached() const = 0;
    virtual const IeSize& size() const = 0;
    virtual const IeSize& tileSize() const = 0;
    virtual const IePixTyp& pixTyp() const = 0;
    virtual const CsSpace& colorSpace() const = 0;
    virtual const IeTile& numTiles() const = 0;
   virtual const IeFileDesc& fileDesc() const = 0;
    virtual void setColorSpace(const CsSpace&) = 0;
    virtual void setPixTyp(const IePixTyp&) = 0;
    virtual AiBoolean storeFile(IeFileDesc&, CsThreadLock& lock) const = 0;
    virtual Ief *read(const IeSize&,const IeOffset&, IeImg::Access, Int, AiBoolean) = 0;
    virtual void paste(Ief*, const IeOffset&, Int, const Real*, Int, 
    		       const IePixel&, CsThreadLock& lock) = 0;
    virtual IeCxt *makeReadCxt(const IeSize&, AiBoolean) = 0;
    virtual IeCxt *makeWriteCxt(const IeSize&, AiBoolean) = 0;
    virtual IeCxt *getReadCxt() = 0;
    virtual IeCxt *getWriteCxt() = 0;
    virtual void areaFill(const IeOffset*, UInt, IePixSel*,
    		          UInt, IeSize&, IeOffset&, CsThreadLock& lock) = 0;
    virtual void areaFill(const IeImg&, const IeOffset&, IePixSel*,
    		          UInt, IeSize&, IeOffset&, CsThreadLock& lock) = 0;
    virtual void clear(const IePixel&, const IeSize&, const IeOffset&, CsThreadLock& lock) = 0;
    virtual void clear(UInt, const IeSize&, const IeOffset&, CsThreadLock& lock) = 0;
    virtual void checkpoint(IeImg::MemSel, CsThreadLock& lock) = 0;
    virtual void recover(IeImg::MemSel, AiBoolean, CsThreadLock& lock) = 0;
    virtual UInt memUsed(IeImg::MemSel flags) const = 0;
    virtual UInt refCount() const = 0;
    virtual const void *lockToRead(const IeTile&, CsThreadLock& lock) = 0;
    virtual void *lockToWrite(const IeTile&, AiBoolean, AiBoolean,
                                                  CsThreadLock& lock) = 0;
    virtual void unlock(const IeTile&) = 0;
    virtual void preserve(const IeTile&) = 0;
    virtual void unpreserve(const IeTile&) = 0;
    virtual AiBoolean tileHasData(const IeTile&) const = 0;
    virtual void getTileOffset(const IeTile&, IeOffset*) const = 0;
    virtual void getWhichTile(const IeOffset&, IeOffset*, IeTile*) const = 0;
    virtual void clearTile(const IeTile&, const IePixel&, CsThreadLock& lock) = 0;
    virtual void clearTile(const IeTile&, UInt, CsThreadLock& lock) = 0;
    virtual void clearTile(const IeTile&, CsThreadLock& lock) = 0;
    virtual void checkpointTile(const IeTile&, CsThreadLock& lock) = 0;
    virtual IeImgRep *clone() const = 0;
};

extern "C" IeImgRep * ieImgRepConstructor2(const IeSize&, 
	const IePixTyp&, const CsSpace&, const IeSize&);
extern "C" IeImgRep * ieImgRepConstructor3(Ief*, const IeSize&, CsThreadLock& lock);
extern "C" IeImgRep * ieImgRepConstructor6(void*, const IeSize&, 
	const IePixTyp&, const CsSpace&);
extern "C" IeImgRep * ieImgRepConstructor7(const IeFileDesc&,
	AiBoolean, const IeSize&, CsThreadLock& lock);

extern IEDLLEXPORT const IeImg ieImgNull;

/*** INLINES ***/
INLINE IeImg::IeImg()
{
    CSMT_LOCK(lock, msLock);
    mRep = ieImgNull.mRep;
    mRep->rc()++;
}

INLINE IeImg::IeImg(const IeSize& a, IePixTyp b, const CsSpace& c,
    const IeSize& d)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieImgRepConstructor2(a, b, c, d);
}

INLINE IeImg::IeImg(void* a, const IeSize& b, IePixTyp c, const CsSpace& d)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieImgRepConstructor6(a, b, c, d);
}

INLINE IeImg::IeImg(Ief *a, const IeSize& b)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieImgRepConstructor3(a, b, lock);
}

INLINE IeImg::IeImg(const IeFileDesc& a, AiBoolean b, const IeSize& c)
{
    CSMT_LOCK(lock, msLock);
    mRep = ieImgRepConstructor7(a, b, c, lock);
}

INLINE IeImg::IeImg(const char *a, AiBoolean b, const IeSize& c)
//  : mRep(ieImgRepConstructor7(IeFileDesc(a), b, c))
//{}		//MSVC++ 2.0 internal compiler error
{
    CSMT_LOCK(lock, msLock);
    IeFileDesc desc(a);
    mRep = ieImgRepConstructor7(desc, b, c, lock);
}


INLINE IeImg::IeImg(const IeImg& i)
{
    CSMT_LOCK(lock, msLock);
    mRep = i.mRep;
    mRep->rc()++;
}

INLINE IeImg::~IeImg()
{ 
    CSMT_LOCK(lock, msLock);
    if (mRep && !--mRep->rc())
    	delete mRep;
}

INLINE const IeImg& IeImg::operator=(const IeImg& i)
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

INLINE const IeImg& IeImg::operator=(Ief *a)
{
    CSMT_LOCK(lock, msLock);
    if (!mRep->isStatic())
    {
#ifdef CS_MT
	IeImgRep* newRep = ieImgRepConstructor3(a, ieSizeAny, lock);
	if (!--mRep->rc())
	    delete mRep;
	mRep = newRep;
#else
	if (!--mRep->rc())
	    delete mRep;
	mRep = ieImgRepConstructor3(a, ieSizeAny, lock);
#endif
    }
    else
	mRep->paste(a, ieOffsetOrigin, -1, NULL, 0, iePixelNull, lock);
    return *this;
}

INLINE AiBoolean IeImg::operator==(const IeImg& i) const 
{ 
    CSMT_LOCK(lock, msLock); //?? needed?
    return mRep == i.mRep; 
}

INLINE AiBoolean IeImg::operator!=(const IeImg& i) const 
{ 
    CSMT_LOCK(lock, msLock); //?? needed?
    return mRep != i.mRep; 
}

INLINE AiBoolean IeImg::isValid() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->isValid();
}

INLINE AiBoolean IeImg::isContiguous() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->isContiguous();
}

INLINE AiBoolean IeImg::isStatic() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->isStatic();
}

INLINE AiBoolean IeImg::isCached() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->isCached();
}

INLINE const IeSize& IeImg::size() const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->size();
}

INLINE const IeSize& IeImg::tileSize() const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->tileSize();
}

INLINE const IePixTyp& IeImg::pixTyp() const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->pixTyp();
}

INLINE const CsSpace& IeImg::colorSpace() const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->colorSpace();
}

INLINE const IeTile& IeImg::numTiles() const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->numTiles();
}

INLINE const IeFileDesc& IeImg::fileDesc() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->fileDesc();
}

INLINE void IeImg::setColorSpace(const CsSpace& a)
{ 
    CSMT_LOCK(lock, msLock);
    mRep = mRep->clone();
    mRep->setColorSpace(a);
}

INLINE void IeImg::setPixTyp(const IePixTyp& a)
{ 
    CSMT_LOCK(lock, msLock);
    mRep = mRep->clone();
    mRep->setPixTyp(a);
}

INLINE AiBoolean IeImg::storeFile(IeFileDesc& a) const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->storeFile(a, lock);
}

INLINE AiBoolean IeImg::storeFile(const char *a, const char *b) const
{
    CSMT_LOCK(lock, msLock);
    IeFileDesc fd(a, b, IeFileDesc::openWrite);
    return mRep->storeFile(fd, lock);
}

INLINE Ief *IeImg::read(const IeSize& a, const IeOffset& b, IeImg::Access c, 
    Int d) const
{
    CSMT_LOCK(lock, msLock);
    const_cast<IeImg*>(this)->mRep = mRep->clone();
    return mRep->read(a, b, c, d, FALSE);
}

INLINE Ief *IeImg::readModify(const IeSize& a, const IeOffset& b, IeImg::Access c, 
    Int d)
{
    CSMT_LOCK(lock, msLock);
    mRep = mRep->clone();
    return mRep->read(a, b, c, d, TRUE);
}

INLINE void IeImg::write(Ief *a)
{ 
    CSMT_LOCK(lock, msLock);
    if (mRep->isValid())
    {
    	mRep = mRep->clone();
    	mRep->paste(a, ieOffsetOrigin, -1, NULL, 0, iePixelNull, lock);
    }
    else
    {
#ifdef CS_MT
	IeImgRep* newRep = ieImgRepConstructor3(a, ieSizeAny, lock);
	if (!--mRep->rc())
	    delete mRep;
	mRep = newRep;
#else
	if (!--mRep->rc())
	    delete mRep;
	mRep = ieImgRepConstructor3(a, ieSizeAny, lock);
#endif
    }
}

INLINE void IeImg::paste(Ief *a, const IeOffset& b, Int c, const Real *d,
    Int e, const IePixel& f)
{ 
    CSMT_LOCK(lock, msLock);
    mRep = mRep->clone();
    mRep->paste(a, b, c, d, e, f, lock);
}

INLINE IeCxt *IeImg::makeReadCxt(const IeSize& a, AiBoolean b) const
{ 
    CSMT_LOCK(lock, msLock);
    const_cast<IeImg*>(this)->mRep = mRep->clone();
    return mRep->makeReadCxt(a, b);
}

INLINE IeCxt *IeImg::makeWriteCxt(const IeSize& a, AiBoolean b)
{ 
    CSMT_LOCK(lock, msLock);
    mRep = mRep->clone();
    return mRep->makeWriteCxt(a, b);
}

INLINE IeCxt *IeImg::getReadCxt() const
{ 
    CSMT_LOCK(lock, msLock);
    const_cast<IeImg*>(this)->mRep = mRep->clone();
    return mRep->getReadCxt();
}

INLINE IeCxt *IeImg::getWriteCxt()
{ 
    CSMT_LOCK(lock, msLock);
    mRep = mRep->clone();
    return mRep->getWriteCxt();
}

INLINE void IeImg::areaFill(const IeOffset *a, UInt b, IePixSel *c,
    		     	    UInt d, IeSize& e, IeOffset& f)
{
    CSMT_LOCK(lock, msLock);
    mRep = mRep->clone();
    mRep->areaFill(a, b, c, d, e, f, lock);
}


INLINE void IeImg::areaFill(const IeImg& a, const IeOffset& b, IePixSel *c,
    		     	    UInt d, IeSize& e, IeOffset& f)
{
    CSMT_LOCK(lock, msLock);
    mRep = mRep->clone();
    mRep->areaFill(a, b, c, d, e, f, lock);
}

INLINE void IeImg::clear(const IePixel& a, const IeSize& b, const IeOffset& c)
{ 
    CSMT_LOCK(lock, msLock);
    mRep = mRep->clone();
    mRep->clear(a, b, c, lock);
}

INLINE void IeImg::clear(UInt a, const IeSize& b, const IeOffset& c)
{ 
    CSMT_LOCK(lock, msLock);
    mRep = mRep->clone();
    mRep->clear(a, b, c, lock);
}

INLINE void IeImg::checkpoint(IeImg::MemSel a) const
{ 
    CSMT_LOCK(lock, msLock);
    mRep->checkpoint(a, lock);
}

INLINE void IeImg::recover(IeImg::MemSel a, AiBoolean b) const
{ 
    CSMT_LOCK(lock, msLock);
    mRep->recover(a, b, lock);
}

INLINE UInt IeImg::memUsed(IeImg::MemSel a) const
{
    CSMT_LOCK(lock, msLock);
    return mRep->memUsed(a);
}

INLINE UInt IeImg::refCount() const
{
    CSMT_LOCK(lock, msLock);
    return mRep->refCount();
}

INLINE const void *IeImg::lockToRead(const IeTile& a) const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->lockToRead(a, lock);
}

INLINE void *IeImg::lockToWrite(const IeTile& a, AiBoolean b, AiBoolean c)
{ 
    CSMT_LOCK(lock, msLock);
    if ( c ) {
        mRep = mRep->clone();
    }
    return mRep->lockToWrite(a, b, c, lock);
}

INLINE void IeImg::unlock(const IeTile& a) const
{ 
    CSMT_LOCK(lock, msLock);
    mRep->unlock(a);
}

INLINE void IeImg::preserve(const IeTile& a) const
{ 
    CSMT_LOCK(lock, msLock);
    mRep->preserve(a);
}

INLINE void IeImg::unpreserve(const IeTile& a) const
{ 
    CSMT_LOCK(lock, msLock);
    mRep->unpreserve(a);
}

INLINE AiBoolean IeImg::tileHasData(const IeTile& a) const
{ 
    CSMT_LOCK(lock, msLock);
    return mRep->tileHasData(a);
}

INLINE IeOffset IeImg::tileOffset(const IeTile& a) const
{ 
    CSMT_LOCK(lock, msLock);
    IeOffset val;
    mRep->getTileOffset(a, &val);
    return val;
}

INLINE IeTile IeImg::whichTile(const IeOffset& a, IeOffset *b) const
{ 
    CSMT_LOCK(lock, msLock);
    IeTile val;
    mRep->getWhichTile(a, b, &val);
    return val;
}

INLINE void IeImg::clearTile(const IeTile& a, const IePixel& b)
{ 
    CSMT_LOCK(lock, msLock);
    mRep->clearTile(a, b, lock);
}

INLINE void IeImg::clearTile(const IeTile& a, UInt b)
{ 
    CSMT_LOCK(lock, msLock);
    mRep->clearTile(a, b, lock);
}

INLINE void IeImg::clearTile(const IeTile& a)
{ 
    CSMT_LOCK(lock, msLock);
    mRep->clearTile(a, lock);
}

INLINE void IeImg::checkpointTile(const IeTile& a) const
{
    CSMT_LOCK(lock, msLock);
    mRep->checkpointTile(a, lock);
}

#endif /* _ieimage_h */
