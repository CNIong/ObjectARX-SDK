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

// Definition of IE/API auxiliary classes.

#ifndef _ieaux_h
#define _ieaux_h

#include <stdio.h>
#include <stdlib.h>

#define IE_ALPHA_OPAQUE 255

enum 
{
    IE_MAX_NUM_BANDS=4 	//max number of color components per pixel
};


inline UInt ieRowStride(UInt numPixels, UInt bitsPerPixel)
{
    return (numPixels * bitsPerPixel + 31) / 8 & ~3;
}


/*** IePixTyp ***/

class IePixTyp
{
  public:
    enum Type { NONE, U1_1, U8_1, U8_3, U8_4,
		none=0, u1_1, u8_1, u8_3, u8_4 };

    IePixTyp(Type t=NONE);
    IePixTyp(const CsSpace &cs, UInts extraBands=0);
    
    operator Type() const;
    const char *name() const;
    UInts numBands() const;
    UInts bitsPerBand() const;
    UInts bitsPerPixel() const;
    Ints bytesPerBand() const;
    Ints bytesPerPixel() const;
    UInt bytesPerRow(UInts pixelsPerRow) const;
    AiBoolean isCompatible(const CsSpace &cs) const;

  private:
    Type mType;
};

struct IePixTypes { UInts a, b, c; Ints d, e; char *f; };

extern IEDLLEXPORT const IePixTypes iePixTypes[];

extern "C" IePixTyp::Type iePixTypFromCsSpace(const CsSpace&,
							  UInts);
extern "C" AiBoolean iePixTypIsCompatible(IePixTyp::Type, 
						      const CsSpace&);


/*** IeSize ***/

class IeSize
{
  public:
    IeSize() {}			//uninitialized
    IeSize(Ints x, Ints y) { mX = x; mY = y; }
    enum Init { any, full, origin };
    IeSize(Init i) : mX(i==any ? -1 : 0), mY(mX) {}

    Ints x() const { return mX; }
    Ints y() const { return mY; }
    Ints& x() { return mX; }
    Ints& y() { return mY; }
    void setX(Ints x) { mX = x; }
    void setY(Ints y) { mY = y; }

    IeSize& operator+=(const IeSize& rhs) 
    	{ mX += rhs.mX; mY += rhs.mY; return *this; }
    IeSize& operator-=(const IeSize& rhs)
	{ mX -= rhs.mX; mY -= rhs.mY; return *this; }
    IeSize& operator*=(const IeSize& rhs)
	{ mX *= rhs.mX; mY *= rhs.mY; return *this; }
    IeSize& operator/=(const IeSize& rhs)
	{ mX /= rhs.mX; mY /= rhs.mY; return *this; }
    IeSize& operator%=(const IeSize& rhs)
	{ mX %= rhs.mX; mY %= rhs.mY; return *this; }
    IeSize operator+(const IeSize& rhs) const
	{ return IeSize(mX + rhs.mX, mY + rhs.mY); }
    IeSize operator-(const IeSize& rhs) const
	{ return IeSize(mX - rhs.mX, mY - rhs.mY); }
    IeSize operator*(const IeSize& rhs) const
	{ return IeSize(mX * rhs.mX, mY * rhs.mY); }
    IeSize operator/(const IeSize& rhs) const
	{ return IeSize(mX / rhs.mX, mY / rhs.mY); }
    IeSize operator%(const IeSize& rhs) const
	{ return IeSize(mX % rhs.mX, mY % rhs.mY); }
    AiBoolean operator==(const IeSize& r) const
    	{ return mX == r.mX && mY == r.mY; }
    AiBoolean operator!=(const IeSize& r) const
    	{ return mX != r.mX || mY != r.mY; }
    AiBoolean operator<(const IeSize& r) const
    	{ return mX < r.mX && mY < r.mY; }
    AiBoolean operator<=(const IeSize& r) const
    	{ return mX <= r.mX && mY <= r.mY; }
    AiBoolean operator>(const IeSize& r) const
    	{ return mX > r.mX || mY > r.mY; }
    AiBoolean operator>=(const IeSize& r) const
    	{ return mX >= r.mX || mY >= r.mY; }

    IeSize& operator+=(const Ints r) 
    	{ mX += r; mY += r; return *this; }
    IeSize& operator-=(const Ints r)
	{ mX -= r; mY -= r; return *this; }
    IeSize& operator*=(const Ints r)
	{ mX *= r; mY *= r; return *this; }
    IeSize& operator/=(const Ints r)
	{ mX /= r; mY /= r; return *this; }
    IeSize& operator%=(const Ints r)
	{ mX %= r; mY %= r; return *this; }
    IeSize operator+(const Ints r) const
	{ return IeSize(mX + r, mY + r); }
    IeSize operator-(const Ints r) const
	{ return IeSize(mX - r, mY - r); }
    IeSize operator*(const Ints r) const
	{ return IeSize(mX * r, mY * r); }
    IeSize operator/(const Ints r) const
	{ return IeSize(mX / r, mY / r); }
    IeSize operator%(const Ints r) const
	{ return IeSize(mX % r, mY % r); }	
    AiBoolean operator==(const Ints r) const
    	{ return mX == r && mY == r; }
    AiBoolean operator!=(const Ints r) const
    	{ return mX != r || mY != r; }
    AiBoolean operator<(const Ints r) const
    	{ return mX < r && mY < r; }
    AiBoolean operator<=(const Ints r) const
    	{ return mX <= r && mY <= r; }
    AiBoolean operator>(const Ints r) const
    	{ return mX > r || mY > r; }
    AiBoolean operator>=(const Ints r) const
    	{ return mX >= r || mY >= r; }

    AiBoolean operator==(const Init i) const
    	{ IeSize r(i); return mX == r.mX && mY == r.mY; }
    AiBoolean operator!=(const Init i) const
    	{ IeSize r(i); return mX != r.mX || mY != r.mY; }
    AiBoolean operator<(const Init i) const
    	{ IeSize r(i); return mX < r.mX && mY < r.mY; }
    AiBoolean operator<=(const Init i) const
    	{ IeSize r(i); return mX <= r.mX && mY <= r.mY; }
    AiBoolean operator>(const Init i) const
    	{ IeSize r(i); return mX > r.mX || mY > r.mY; }
    AiBoolean operator>=(const Init i) const
    	{ IeSize r(i); return mX >= r.mX || mY >= r.mY; }

    friend AiBoolean operator==(const Ints l, const IeSize& r)
    	{ return r == l; }
    friend AiBoolean operator!=(const Ints l, const IeSize& r)
    	{ return r != l; }
    friend AiBoolean operator<(const Ints l, const IeSize& r)
    	{ return r > l; }
    friend AiBoolean operator<=(const Ints l, const IeSize& r)
    	{ return r >= l; }
    friend AiBoolean operator>(const Ints l, const IeSize& r)
    	{ return r < l; }
    friend AiBoolean operator>=(const Ints l, const IeSize& r)
    	{ return r <= l; }
    
    friend AiBoolean operator==(const Init i, const IeSize& r)
    	{ return r == i; }
    friend AiBoolean operator!=(const Init i, const IeSize& r)
    	{ return r != i; }
    friend AiBoolean operator<(const Init i, const IeSize& r)
    	{ return r > i; }
    friend AiBoolean operator<=(const Init i, const IeSize& r)
    	{ return r >= i; }
    friend AiBoolean operator>(const Init i, const IeSize& r)
    	{ return r < i; }
    friend AiBoolean operator>=(const Init i, const IeSize& r)
    	{ return r <= i; }
    	
  private:
    Ints mX, mY;
};

typedef IeSize IeOffset;
typedef IeSize IeTile;

extern IEDLLEXPORT const IeOffset ieOffsetOrigin;
extern IEDLLEXPORT const IeSize ieSizeFull;
extern IEDLLEXPORT const IeSize ieSizeAny;

/*** IePixel ***/

class IePixel 
{
  public:
    IePixel() : mBands(0) {}
    IePixel(Int val);
    IePixel(Int val0, Int val1);
    IePixel(Int val0, Int val1, Int val2);
    IePixel(Int val0, Int val1, Int val2, Int val3);
    IePixel(const Int *val, Int numBands);
    enum Init { null, zero };
    IePixel(Init i);
    
    Int numBands() const;
    Int &operator[](Int index);
    Int operator[](Int index) const;

  private:
    Int mBands;
    Int mVal[IE_MAX_NUM_BANDS];
};

extern IEDLLEXPORT const IePixel iePixelZero;
extern IEDLLEXPORT const IePixel iePixelNull;

/*** IeGradientFunc ***/

class IeGradientFunc
{
  public:
    virtual ~IeGradientFunc() {}
    virtual Real interp(UInt band, Real pos) const { return pos; }
};

/*** IE INITIALIZATION AND STATE ***/
#if !defined(IE_MEMORY_RECOVERY_THRESHOLD)
#define IE_MEMORY_RECOVERY_THRESHOLD (UInt) 8*1024*1024
#endif
#if !defined(IE_CHECKPOINT_BLOCK_SIZE)
#define IE_CHECKPOINT_BLOCK_SIZE 0	/*checkpointing disabled*/
#endif
#if !defined(IE_AUTO_LOAD_MODULES)
#define IE_AUTO_LOAD_MODULES TRUE
#endif

class Ie
{
  public:
    Ie();
    ~Ie();
    
    AiBoolean enableCheckpointing(UInt blockSize=16*1024,
                                  const char *tempPath=0,
                                  AiBoolean allowTruncation=FALSE);
    void checkpointAll();

    void setMemoryLimit(UInt numBytes);
    UInt recoverMemory(UInt numBytes=0, AiBoolean forced=FALSE);
    AiBoolean isMemAvailable(const class IeFileDesc& fd, UInt& memNeeded,
                             UInt& memAvail, char& tmpDrive,
                             AiBoolean includeHeap=TRUE);
    AiBoolean isMemAvailable(const IePixTyp& pixTyp, const IeSize& size,
                             UInt& memNeeded, UInt& memAvail, char& tmpDrive,
                             AiBoolean includeHeap=TRUE);
    
    enum MemSel { memInCore=16, memInFile, memCheckpointed, memTotal };
    UInt memUsed(MemSel sel=memInCore) const;
    
    typedef AiBoolean (*ProgressHandler)(Int);
    ProgressHandler setProgressHandler(ProgressHandler func);
    const char *setFileioMethod(const char *fileioMethod);
    void setKeepFilesOpen(AiBoolean keepOpen);
    void setDefaultTileSize(const IePixTyp& pixTyp, const IeSize& size, 
    			    UInt numBytesPerTile);
    const IeSize& defaultTileSize(const IePixTyp& pixTyp) const;
    
    enum ModuleClass { fileReader, fileWriter };
    const char **moduleIds(ModuleClass moduleClass) const;

    void *loadModule(const char *file, AiBoolean append=TRUE);
    void unloadModule(void *moduleHandle);
    
    const char *copyrightNotice() const;
    void doAboutDialog(CsHwnd) const;

};


class IeRep
{
  public:
    virtual ~IeRep() {}
    virtual void addRef() const = 0;
    virtual void release() const = 0;
    virtual AiBoolean enableCheckpointing(UInt, const char *, AiBoolean) = 0;
    virtual void checkpointAll() = 0;
    virtual void setMemoryLimit(UInt) = 0;
    virtual UInt recoverMemory(UInt, AiBoolean) = 0;
    virtual AiBoolean isMemAvailable(const IeFileDesc&, UInt&, UInt&, char&,
                                     AiBoolean) = 0;
    virtual AiBoolean isMemAvailable(const IePixTyp&, const IeSize&, UInt&,
                                     UInt&, char&, AiBoolean) = 0;
    virtual UInt memUsed(Ie::MemSel) const = 0;
    virtual Ie::ProgressHandler setProgressHandler(Ie::ProgressHandler) = 0;
    virtual const char *setFileioMethod(const char*) = 0;
    virtual void setKeepFilesOpen(AiBoolean) = 0;
    virtual void setDefaultTileSize(const IePixTyp&, const IeSize&, UInt) = 0;
    virtual const IeSize& defaultTileSize(const IePixTyp&) const = 0;    
    virtual const char **moduleIds(Ie::ModuleClass) const = 0;
    virtual void *loadModule(const char*, AiBoolean) = 0;
    virtual void unloadModule(void*) = 0;
    virtual const char *copyrightNotice() const = 0;
    virtual void doAboutDialog(CsHwnd) const = 0;
};

extern IEDLLEXPORT IeRep * ieRep;

extern "C" void ieEnter(UInt numBytes=IE_MEMORY_RECOVERY_THRESHOLD, 
                                    UInt ckpBlockSize=IE_CHECKPOINT_BLOCK_SIZE,
                                    AiBoolean loadModules=IE_AUTO_LOAD_MODULES);
extern "C" void ieExit();

#ifdef CS_APP			//put into each app file
static Ie CS_NEAR ie;
#endif

/*** ASSERTION AND ARGUMENT CHECKING MACROS ***/
// NOTE: due to a compiler bug these macros cannot be used in inlines 
// with the MSVC++ 2.0 compiler
#define IE_FAIL(b) csRep->doAssert("IE", NULL, 0, NULL, b)
#ifdef DEBUG
#define IE_PCHECK(a, b) if (!(a)) \
 		csRep->doAssert("IE", __FILE__, __LINE__, #a, b)
#define IE_ASSERT(a) if (!(a)) \
 		csRep->doAssert("IE", __FILE__, __LINE__, #a)
#else
#define IE_PCHECK(a, b)
#define IE_ASSERT(a)
#endif

/*** INLINES ***************************************************************/
#if defined(USE_INLINES) || defined(OUTLINE_FUNCS_HERE)

/*** IePixTyp ***/
INLINE IePixTyp::IePixTyp(Type type)
  : mType(type)
{}

INLINE IePixTyp::IePixTyp(const CsSpace& a, UInts b)
  : mType(iePixTypFromCsSpace(a, b))
{}

INLINE IePixTyp::operator IePixTyp::Type() const
{
    return mType;
}

INLINE const char *IePixTyp::name() const
{
    return iePixTypes[mType].f;
}

INLINE UInts IePixTyp::numBands() const
{
    return iePixTypes[mType].a;
}

INLINE UInts IePixTyp::bitsPerBand() const
{
    return iePixTypes[mType].b;
}

INLINE UInts IePixTyp::bitsPerPixel() const
{
    return iePixTypes[mType].c;
}

INLINE Ints IePixTyp::bytesPerBand() const
{
    return iePixTypes[mType].d;
}

INLINE Ints IePixTyp::bytesPerPixel() const
{
    return iePixTypes[mType].e;
}

INLINE UInt IePixTyp::bytesPerRow(UInts numPixels) const
{
    return ieRowStride(iePixTypes[mType].c, numPixels);
}

INLINE AiBoolean IePixTyp::isCompatible(const CsSpace &a) const
{
    return iePixTypIsCompatible(mType, a);
}


/*** IePixel ***/
INLINE IePixel::IePixel(IePixel::Init i)
  : mBands(0) 
{ 
    if (i==zero) 
    { 
        mBands = 4; 
        mVal[0] = mVal[1] = mVal[2] = mVal[3] = 0;
    }
}

INLINE IePixel::IePixel(Int val) :
    mBands(1)
{
    mVal[0] = val;
}

INLINE IePixel::IePixel(Int val0, Int val1) :
    mBands(2)
{
    mVal[0] = val0;
    mVal[1] = val1;
}

INLINE IePixel::IePixel(Int val0, Int val1, Int val2) :
    mBands(3)
{
    mVal[0] = val0;
    mVal[1] = val1;
    mVal[2] = val2;
}

INLINE IePixel::IePixel(Int val0, Int val1, Int val2, Int val3) :
    mBands(4)
{
    mVal[0] = val0;
    mVal[1] = val1;
    mVal[2] = val2;
    mVal[3] = val3;
}

INLINE IePixel::IePixel(const Int *pVal, Int numBands)
    : mBands(numBands)
{
    if (pVal == NULL)
    {
	mBands = 0;
	return;
    }
//    IE_PCHECK(mBands > 0 && mBands <= IE_MAX_NUM_BANDS,  //VC++2.0 problem
//    	"IePixel::IePixel - invalid number of bands");
    for (Int i=0; i<mBands; i++)
	mVal[i] = pVal[i];
}

INLINE Int IePixel::numBands() const
{
    return mBands;
}

INLINE Int& IePixel::operator[](Int index)
{
//    IE_PCHECK(index >=0 && index < mBands, 		//VC++ 2.0 problem
//    	"IePixel::operator[] - index out of range");
    return mVal[index];
}

INLINE Int IePixel::operator[](Int index) const
{
//    IE_PCHECK(index >=0 && index < mBands, 		//VC++ 2.0 problem
//    	"IePixel::operator[] - index out of range");
    return mVal[index];
}

INLINE Ie::Ie()
{ 
    ieEnter(IE_MEMORY_RECOVERY_THRESHOLD, IE_CHECKPOINT_BLOCK_SIZE,
    	    IE_AUTO_LOAD_MODULES);
}

INLINE Ie::~Ie()
{ 
    char csAppPath[MAX_PATH];
    HMODULE hModule = GetModuleHandle(/*MSG0*/"ie70.dll");
    if (!hModule)
        return;
    DWORD rc = GetModuleFileName(
        hModule, csAppPath, MAX_PATH);
    if (!rc)
        return;

    if (ieRep)
        ieRep->release();
}

INLINE AiBoolean Ie::enableCheckpointing(UInt a, const char *b, AiBoolean c)
{ 
    return ieRep->enableCheckpointing(a, b, c);
}

INLINE void Ie::checkpointAll()
{ 
    ieRep->checkpointAll(); 
}

INLINE void Ie::setMemoryLimit(UInt numBytes)
{ 
    ieRep->setMemoryLimit(numBytes); 
}

INLINE UInt Ie::recoverMemory(UInt a, AiBoolean b)
{
    return ieRep->recoverMemory(a, b);
}

INLINE AiBoolean Ie::isMemAvailable(const IeFileDesc& a, UInt& b, UInt& c,
                                    char& d, AiBoolean e)
{
    return ieRep->isMemAvailable(a, b, c, d, e);
}

INLINE AiBoolean Ie::isMemAvailable(const IePixTyp& a, const IeSize& b, 
                                    UInt& c, UInt& d, char& e, AiBoolean f)
{
    return ieRep->isMemAvailable(a, b, c, d, e, f);
}

INLINE UInt Ie::memUsed(Ie::MemSel a) const 
{
    return ieRep->memUsed(a);
}
    
INLINE Ie::ProgressHandler Ie::setProgressHandler(Ie::ProgressHandler a)
{
    return ieRep->setProgressHandler(a); 
}

INLINE const char *Ie::setFileioMethod(const char *a)
{
    return ieRep->setFileioMethod(a); 
}

INLINE void Ie::setKeepFilesOpen(AiBoolean a)
{
    ieRep->setKeepFilesOpen(a); 
}

INLINE void Ie::setDefaultTileSize(const IePixTyp& a, const IeSize& b, UInt c)
{ 
    ieRep->setDefaultTileSize(a, b, c); 
}

INLINE const IeSize& Ie::defaultTileSize(const IePixTyp& a) const
{
    return ieRep->defaultTileSize(a); 
}
    
INLINE const char **Ie::moduleIds(ModuleClass a) const
{
    return ieRep->moduleIds(a);
}

INLINE void *Ie::loadModule(const char *a, AiBoolean b)
{
    return ieRep->loadModule(a, b); 
}

INLINE void Ie::unloadModule(void *a) 
{
    ieRep->unloadModule(a); 
}

INLINE const char *Ie::copyrightNotice() const
{
    return ieRep->copyrightNotice();
}

INLINE void Ie::doAboutDialog(CsHwnd a) const
{
    ieRep->doAboutDialog(a);
}

#endif  /* defined(USE_INLINES) || defined(OUTLINE_FUNCS_HERE) */
#endif	/* _ieaux_h */
