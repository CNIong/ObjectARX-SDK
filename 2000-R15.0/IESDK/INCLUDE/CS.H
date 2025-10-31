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

//    cs.h - CS/API (color system) interface header


/*
* --------	---	-----------------------------------------------------
* Date			Who	Description
* --------	---	-----------------------------------------------------
* 9805.06		ea  forwarded "class Ief; class IePalGenInfo; for IePalGenInfo api.
*               added a CsSpace constructor header for palette generation.
*               added a ieGeneratePalette() extern api for calling the palette 
*               generation after the default construction takes place.
*               added a CsSpace constructor body for palette generation.
*               appended the IePalGenInfo class api.
*
*/


#ifndef _cs_h
#define _cs_h

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#ifndef _csdefs_h
#include <csdefs.h>
#endif


class CsSpaceRep;

extern IEDLLEXPORT const UInt csShiftTable[];

/*** 32-BIT RGB(A) DATA TYPE ***/
class CsRgb8
{
private:

#ifdef CS_BIG_ENDIAN
    enum CompIndex { kAlpha = 0, kBlue, kGreen, kRed };
#else
    enum CompIndex { kRed = 0, kGreen, kBlue, kAlpha };
#endif

  public:
    union {
        UInt val;
        UInt8 aComp[4];    // Allow byte addressing of components
    };
    
    CsRgb8() {}        //remains uninitialized
    CsRgb8(const CsRgb8& v) : val(v.val) {}
    CsRgb8(UInt v) : val(v) {}

    CsRgb8(UInt r, UInt g, UInt b, UInt a = 0xff);
    UInt red() const    { return aComp[kRed]; }
    UInt green() const    { return aComp[kGreen]; }
    UInt blue() const    { return aComp[kBlue]; }
    UInt alpha() const    { return aComp[kAlpha]; }
    UInt gray() const;
    void setRed(UInt v)        { aComp[kRed] = (UInt8)v; }
    void setGreen(UInt v)    { aComp[kGreen] = (UInt8)v; }
    void setBlue(UInt v)    { aComp[kBlue] = (UInt8)v; }
    void setAlpha(UInt v)    { aComp[kAlpha] = (UInt8)v; }
    void setGray(UInt v);

    CsRgb8& operator=(const CsRgb8& v) { val = v.val; return *this; }
    CsRgb8& operator=(const UInt& v) { val = v; return *this; }
    operator UInt() const { return val; }

    UInt8 operator[](UInt i) const;
};

INLINE
CsRgb8::CsRgb8(UInt r, UInt g, UInt b, UInt a) 
{
    aComp[kRed] = (UInt8)r; 
    aComp[kGreen] = (UInt8)g; 
    aComp[kBlue] = (UInt8)b; 
    aComp[kAlpha] = (UInt8)a;
}

INLINE void
CsRgb8::setGray(UInt v) 
{ 
    aComp[kRed] = aComp[kGreen] = aComp[kBlue] = (UInt8)v; 
    aComp[kAlpha] = 0xff; 
}

INLINE UInt
CsRgb8::gray() const
{
    UInt grayValue = 19595 * aComp[kRed] + 38470 * aComp[kGreen] + 7471 * aComp[kBlue];
    return (UInt8)((grayValue + (1 << 15)) >> 16);
}

INLINE UInt8 
CsRgb8::operator[](UInt i) const 
{
#ifdef CS_BIG_ENDIAN
    return aComp[3-i]; 
#else
    return aComp[i]; 
#endif
}


extern IEDLLEXPORT const CsRgb8 csBlack;        //default black
extern IEDLLEXPORT const CsRgb8 csWhite;        //default white


// Multithreading declarations
// We declare two classes for locking thread access to the image engine.
// CsCriticalSection is a critical section that can be locked using
// CsThreadLock. We define some macros to help with compiling for
// Multithreaded or no. CSMT_ONLY only compiles when CS_MT is defined.
// CSMT_LOCK creates a lock when CS_MT is defined, or it creates
// a null reference if CS_MT is not defined.

// This class is declared in all ie versions, but is only defined
// in the MT version. This allows applications to be compiled
// without CS_MT defined to work with the CS_MT dll.

#if defined(CS_MT)
 #if defined(WIN32) || defined(_WIN32)			//Win32
  #define WIN32_EXTRA_LEAN
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>

  #define CS_CRITICAL_SECTION(x)	CRITICAL_SECTION x
  #define CS_LOCK_THREAD(x)		EnterCriticalSection(const_cast<CRITICAL_SECTION*>(&(x)))
  #define CS_UNLOCK_THREAD(x)		LeaveCriticalSection(const_cast<CRITICAL_SECTION*>(&(x)))
  #define CS_INIT_CRIT(x)		InitializeCriticalSection(&(x))
  #define CS_DELETE_CRIT(x)		DeleteCriticalSection(&(x))
 #else
  #error "multithread only supported for WIN32"
 #endif


///////////////////////////////////////////////////////////////////////
// CsCriticalSection - Critical section object for Image Engine
class CsCriticalSection {
public:
    CsCriticalSection();
    ~CsCriticalSection();

    void lock() const;			// Lock the object
    void unlock() const;		// Unlock the object

private:
    // Prevent copy constructr and assignment from being used
    CsCriticalSection(const CsCriticalSection&);	// Not implemented
    CsCriticalSection& operator=(const CsCriticalSection&);	// Not implemented
    CS_CRITICAL_SECTION(mCriticalSection);
};

///////////////////////////////////////////////////////////////////////
// CsThreadLock - Critical section lock object for Image Engine
// NOTE: the lock, unlock and isLocked methods all check this for
// NULL. This allows an app compiled with CS_MT off, to use the
// dll compiled with CS_MT on.
class CsThreadLock {
public:
    CsThreadLock(const CsCriticalSection& sect, BOOL lock = TRUE);
    ~CsThreadLock();

    void lock();			// Lock the object
    void unlock();			// Unlock the object
    AiBoolean isLocked() const;

private:
    // Prevent copy constructr and assignment from being used
    CsThreadLock(const CsThreadLock&);	// Not implemented
    CsThreadLock& operator=(const CsThreadLock&);	// Not implemented
    const CsCriticalSection&	mSect;
    AiBoolean			mIsLocked;
};

///////////////////////////////////////////////////////////////////////
// CsUnlockStatic - Switches lock from a static critcial section to an
// object critical section. There are several static critical sections
// that are used to lock IeImg, IeDIB, IeFileDesc and IeChunkPtr so we
// can safely access the implementation pointer. Some impelementation
// methods unlock the static critical section and lock a critical
// section that only safeguards access for the inidividual object.
// This object will safely and correctly make that switch.
class CsUnlockStatic : public CsThreadLock {
public:
    CsUnlockStatic(const CsCriticalSection& section, CsThreadLock& staticLock);
    ~CsUnlockStatic();
private:
    CsThreadLock&	mStaticLock;
};

#define CSMT_ONLY(x)	x
#define CSMT_LOCK(name, crit)	CsThreadLock name(crit, TRUE)
#else
class CsCriticalSection;
class CsThreadLock;
#define CSMT_ONLY(x)
#define CSMT_LOCK(name, crit)	CsThreadLock& name = *(CsThreadLock*)NULL
#endif


/*** COLOR SPACE DESCRIPTOR/PALETTE CLASS ***/
class Ief;
class IePalGenInfo;
class CsSpace
{
  public:
    enum Type { NONE, BITONAL, INDEXED, GRAY, RGB,
                none=0, bitonal, indexed, gray, rgb };
    
    //OBJECT MAINTENANCE
    CsSpace();
    CsSpace(const CsSpace& s);
    ~CsSpace();
    const CsSpace& operator=(const CsSpace& s); 
    AiBoolean operator==(const CsSpace& s) const; 
    AiBoolean operator!=(const CsSpace& s) const; 
    AiBoolean operator==(Type t) const;
    AiBoolean operator!=(Type t) const;
    friend AiBoolean operator==(Type t, const CsSpace& s);
    friend AiBoolean operator!=(Type t, const CsSpace& s);
    
    //SPACE DESCRIPTOR ATTRIBUTES
    const char *name() const;
    UInt numBands() const;
    const void *profile() const;
    Type type() const;
    AiBoolean isVisual() const;
    AiBoolean isMonochrome() const;
    AiBoolean isPalette() const;
    AiBoolean isBitonal() const;

    /*** PALETTE AND COLOR CUBE ***/
    //PALETTE CONSTRUCTORS
    CsSpace(const CsSpace &space,          //creates a palette
            UInt numColors,
            UInt offset=0, 
            const CsRgb8 *pColors=NULL, 
            const char *name = NULL);
    CsSpace(const CsSpace& space,        //creates a color cube
            const UInt *pDimensions,
            UInt offset = 0,
            CsRgb8 blackPoint = csBlack,
            CsRgb8 whitePoint = csWhite,
            const char *name = NULL);
    CsSpace(Ief* piefPipe, const IePalGenInfo* piePalGenInfo, AiBoolean& bSuccess);

    //PALETTE ATTRIBUTES
    const CsSpace& paletteColorSpace() const;
    UInt numColors() const;
    UInt offset() const;
    UInt numCubeDims() const;
    const UInt *cubeSize() const;
    UInt cubeVal(UInt dim, UInt index) const;
    AiBoolean hasAlpha() const;

    //PALETTE DATA ACCESS
    void set(UInt i, CsRgb8 val);
    CsRgb8 get(UInt i) const;
    void set(UInt count, UInt offset, const CsRgb8 *pVals); 
    void get(UInt count, UInt offset, CsRgb8 *pVals) const;
    CsRgb8 operator[](UInt i) const;
    const CsRgb8 *tablePtr() const;
    void merge(const CsSpace& s);    //merges palettes

  private:
    void clone();
    CsSpaceRep *ms;

    CSMT_ONLY(static IEDLLEXPORT CsCriticalSection msLock;)

    public: CsSpace(CsVoid) {}
};

/*** PRE-DEFINED COLOR SPACE DESCRIPTORS ***/
extern IEDLLEXPORT const CsSpace csNone;    //non-visual
extern IEDLLEXPORT const CsSpace csRgb;            //default rgb space
extern IEDLLEXPORT const CsSpace csGray;    //default monochrome space
extern IEDLLEXPORT const CsSpace csBitonal;    //default bi-tonal

class CsSpaceRep
{
  public:
    virtual ~CsSpaceRep() {}
    virtual UInt& rc() const = 0;
    virtual AiBoolean equal(const CsSpaceRep*) const = 0;
    virtual const char *name() const = 0;
    virtual UInt numBands() const = 0;
    virtual const void *profile() const = 0;
    virtual CsSpace::Type type() const = 0;
    virtual AiBoolean isVisual() const = 0;
    virtual AiBoolean isMonochrome() = 0;
    virtual AiBoolean isPalette() const = 0;
    virtual AiBoolean isBitonal() const = 0;
    virtual const CsSpace& paletteColorSpace() const = 0;
    virtual UInt numColors() const = 0;
    virtual UInt offset() const = 0;
    virtual UInt numCubeDims() const = 0;
    virtual const UInt *cubeSize() const = 0;
    virtual UInt cubeVal(UInt, UInt) const = 0;
    virtual UInt tableEntry(UInt) const = 0;
    virtual const UInt *tablePtr() const = 0;
    virtual AiBoolean hasAlpha() = 0;
    virtual UInt get(UInt) const = 0;
    virtual void set(UInt, UInt) = 0;
    virtual void get(UInt, UInt, UInt*) const = 0;
    virtual void set(UInt, UInt, const UInt*) = 0;    
    virtual void merge(const CsSpace& s) = 0;
    virtual CsSpaceRep *clone() = 0;
};

extern "C" CsSpaceRep * csSpaceRepConstructor1(const CsSpace&, 
    UInt, UInt, const UInt*, const char*);
extern "C" CsSpaceRep * csSpaceRepConstructor2(const CsSpace&,
    const UInt*, UInt, UInt, UInt, const char*);
extern "C" AiBoolean    ieGeneratePalette(Ief* a,
    const IePalGenInfo* b, CsSpace& c);

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#endif

extern "C" void * csNew(size_t);
extern "C" void csDelete(void*);


/*** INITIALIZER ***/
class Cs
{
  public:
    Cs();
    ~Cs();
    
    typedef AiBoolean (*ErrorHandler)(const char*);
    ErrorHandler setErrorHandler(ErrorHandler func);
    typedef AiBoolean (*NewHandler)(UInt);
    NewHandler setNewHandler(NewHandler func);
    typedef void (*ExitHandler)();
    ExitHandler setExitHandler(ExitHandler func);
};


class CsRep
{
  public:
    virtual ~CsRep() {}
    virtual UInt& rc() const = 0;
    virtual void doAssert(const char*, const char*, Int, 
                  const char*a = NULL, const char*b = NULL) const = 0;
    virtual Cs::ErrorHandler setErrorHandler(Cs::ErrorHandler) = 0;
    virtual Cs::NewHandler setNewHandler(Cs::NewHandler) = 0;
    virtual Cs::ExitHandler setExitHandler(Cs::ExitHandler) = 0;
};

extern IEDLLEXPORT CsRep * csRep;

extern "C" void csInit();
extern "C" void csExit();

#ifdef CS_APP        //put into at each app file
static Cs CS_NEAR cs;
#endif

/*** ASSERTION AND ARGUMENT CHECKING MACROS ***/
#ifdef DEBUG
#define CS_PCHECK(a, b) { if (!(a)) \
         csRep->doAssert("CS", __FILE__, __LINE__, #a, b); }
#define CS_ASSERT(a) { if (!(a)) \
         csRep->doAssert("CS", __FILE__, __LINE__, #a); }
#else
#define CS_PCHECK(a, b)
#define CS_ASSERT(a)
#endif


/*** INLINES ***/
#if defined(USE_INLINES) || defined(OUTLINE_FUNCS_HERE)

INLINE void CsSpace::clone() 
{ 
    CSMT_LOCK(lock, msLock);
    if (ms->rc() > 1) 
    { 
        ms->rc()--;
        ms = ms->clone(); 
    }
}

INLINE CsSpace::CsSpace()
{
    CSMT_LOCK(lock, msLock);
    ms = csNone.ms;
    ms->rc()++; 
}

INLINE CsSpace::CsSpace(const CsSpace& s)
{
    CSMT_LOCK(lock, msLock);
    ms = s.ms;
    ms->rc()++; 
}

INLINE CsSpace::CsSpace(const CsSpace& a, UInt b, UInt c, const CsRgb8 *d, 
    const char *e)
{
    CSMT_LOCK(lock, msLock);
    ms = (CsSpaceRep*) csSpaceRepConstructor1(a, b, c, (const UInt*) d, e);
}

INLINE CsSpace::CsSpace(const CsSpace& a, const UInt *b, UInt c,
    CsRgb8 d, CsRgb8 e, const char *f)
{
    CSMT_LOCK(lock, msLock);
    ms = (CsSpaceRep*) csSpaceRepConstructor2(a, b, c, d, e, f);
}

INLINE CsSpace::CsSpace(Ief* a, const IePalGenInfo* b, AiBoolean& c)
{
    CSMT_LOCK(lock, msLock);
    ms = csNone.ms;
    ms->rc()++; 
    c = ieGeneratePalette(a, b, *this);	// implementation of ieGeneratePalette is in src\filter\IePaletteGenerator.cpp()
}

INLINE CsSpace::~CsSpace() 
{ 
    CSMT_LOCK(lock, msLock);
    if (ms && !--ms->rc()) 
        delete ms; 
}

INLINE const CsSpace& CsSpace::operator=(const CsSpace& s) 
{
    CSMT_LOCK(lock, msLock);
    if (!ms->equal(s.ms))
    {
    if (!--ms->rc())
        delete ms; 
    ms = s.ms;
    ms->rc()++;
    }
    return *this;
}

INLINE AiBoolean CsSpace::operator==(const CsSpace& s) const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->equal(s.ms); 
}

INLINE AiBoolean CsSpace::operator!=(const CsSpace& s) const 
{ 
    CSMT_LOCK(lock, msLock);
    return !ms->equal(s.ms); 
}

INLINE AiBoolean CsSpace::operator==(CsSpace::Type t) const 
{
    CSMT_LOCK(lock, msLock);
    return type() == t;
}

INLINE AiBoolean CsSpace::operator!=(CsSpace::Type t) const 
{ 
    CSMT_LOCK(lock, msLock);
    return type() != t; 
}

INLINE AiBoolean operator==(CsSpace::Type t, const CsSpace& s)
{ 
    CSMT_LOCK(lock, CsSpace::msLock);
    return s == t; 
}

INLINE AiBoolean operator!=(CsSpace::Type t, const CsSpace& s)
{ 
    CSMT_LOCK(lock, CsSpace::msLock);
    return s != t; 
}

INLINE const char *CsSpace::name() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->name(); 
}

INLINE UInt CsSpace::numBands() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->numBands(); 
}

INLINE const void *CsSpace::profile() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->profile(); 
}

INLINE CsSpace::Type CsSpace::type() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->type(); 
}

INLINE AiBoolean CsSpace::isVisual() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->isVisual(); 
}

INLINE AiBoolean CsSpace::isMonochrome() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->isMonochrome(); 
}

INLINE AiBoolean CsSpace::isPalette() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->isPalette(); 
}

INLINE AiBoolean CsSpace::isBitonal() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->isBitonal(); 
}

INLINE const CsSpace& CsSpace::paletteColorSpace() const
{
    CSMT_LOCK(lock, msLock);
    return ms->paletteColorSpace();
}

INLINE UInt CsSpace::numColors() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->numColors(); 
}

INLINE UInt CsSpace::offset() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->offset(); 
}

INLINE UInt CsSpace::numCubeDims() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->numCubeDims(); 
}

INLINE AiBoolean CsSpace::hasAlpha() const
{ 
    CSMT_LOCK(lock, msLock);
    return ms->hasAlpha(); 
}

INLINE const UInt *CsSpace::cubeSize() const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->cubeSize(); 
}

INLINE UInt CsSpace::cubeVal(UInt d, UInt i) const 
{ 
    CSMT_LOCK(lock, msLock);
    return ms->cubeVal(d, i);
}

INLINE void CsSpace::merge(const CsSpace& s) 
{
    CSMT_LOCK(lock, msLock);
    clone();
    ms->merge(s);
}

INLINE CsRgb8 CsSpace::operator[](UInt i) const 
{
    CSMT_LOCK(lock, msLock);
    return ms->tableEntry(i); 
}

INLINE const CsRgb8 *CsSpace::tablePtr() const 
{
    CSMT_LOCK(lock, msLock);
    return (const CsRgb8*) ms->tablePtr(); 
}

INLINE void CsSpace::set(UInt i, CsRgb8 val) 
{
    CSMT_LOCK(lock, msLock);
    clone(); 
    ms->set(i, val); 
}

INLINE CsRgb8 CsSpace::get(UInt i) const 
{
    CSMT_LOCK(lock, msLock);
    return ms->get(i); 
}

INLINE void CsSpace::set(UInt count, UInt offset, const CsRgb8 *pVals) 
{
    CSMT_LOCK(lock, msLock);
    clone();
    ms->set(count, offset, (const UInt*) pVals); 
}

INLINE void CsSpace::get(UInt count, UInt offset, CsRgb8 *pVals) const
{
    CSMT_LOCK(lock, msLock);
    ms->get(count, offset, (UInt*) pVals); 
}

INLINE Cs::Cs()
{
    if (!csRep) 
        csInit();
    csRep->rc()++;
}

INLINE Cs::~Cs()
{
    char csAppPath[MAX_PATH];
    HMODULE hModule = GetModuleHandle(/*MSG0*/"ie70.dll");
    if (!hModule)
        return;
    DWORD rc = GetModuleFileName(
        hModule, csAppPath, MAX_PATH);
    if (!rc)
        return;
    if (csRep && !--csRep->rc())
        csExit();
}

INLINE Cs::ErrorHandler Cs::setErrorHandler(Cs::ErrorHandler func)
{
    return csRep->setErrorHandler(func);
}

INLINE Cs::NewHandler Cs::setNewHandler(Cs::NewHandler func)
{
    return csRep->setNewHandler(func);
}

INLINE Cs::ExitHandler Cs::setExitHandler(Cs::ExitHandler func)
{
    return csRep->setExitHandler(func);
}

#ifdef	CS_MT
/*** INLINES ***/
INLINE CsCriticalSection::CsCriticalSection()
{
	CS_INIT_CRIT(mCriticalSection);
}

INLINE CsCriticalSection::~CsCriticalSection()
{
	CS_DELETE_CRIT(mCriticalSection);
}

INLINE void CsCriticalSection::lock() const
{
	CS_LOCK_THREAD(mCriticalSection);
}

INLINE void CsCriticalSection::unlock() const
{
	CS_UNLOCK_THREAD(mCriticalSection);
}

INLINE CsThreadLock::CsThreadLock(const CsCriticalSection& sect, BOOL initialLock)
	: mSect(sect), mIsLocked(FALSE)
{
	if (initialLock)
		lock();
	else
		unlock();
}

INLINE CsThreadLock::~CsThreadLock()
{
	unlock();
}

INLINE void CsThreadLock::lock()
{
	if (this != NULL && !mIsLocked) {
		mSect.lock();
		mIsLocked = TRUE;
	}
}

INLINE void CsThreadLock::unlock()
{
	if (this != NULL && mIsLocked) {
		mSect.unlock();
		mIsLocked = FALSE;
	}
}

INLINE AiBoolean CsThreadLock::isLocked() const
{
	return this != NULL ? mIsLocked : 0;
}

INLINE CsUnlockStatic::CsUnlockStatic(const CsCriticalSection& section, CsThreadLock& staticLock)
	: CsThreadLock(const_cast<CsCriticalSection&>(section), TRUE),
	  mStaticLock(staticLock)
{
	staticLock.unlock();
}

INLINE CsUnlockStatic::~CsUnlockStatic()
{
	unlock();
	mStaticLock.lock();
}
#endif

#endif  /* defined(USE_INLINES) || defined(OUTLINE_FUNCS_HERE) */

//======================================================================================================

class IePalGenInfo
{
public:

	typedef	enum	tagEGENMETHOD
	{
		ecmOctree,
	}	EGENMETHOD;

	virtual	~IePalGenInfo(){};

	//	operations
	virtual	void								setColorSpaceType(CsSpace::Type csType) = 0;
	virtual	CsSpace::Type				getColorSpaceType() const = 0;

	virtual	void								setNumEntries(unsigned long ulNumEntries) = 0;
	virtual	unsigned	long			getNumEntries() const = 0;

	virtual	AiBoolean						isGenMethodValid(IePalGenInfo::EGENMETHOD eGenMethod) const = 0;
	virtual	AiBoolean						setGenMethodType(IePalGenInfo::EGENMETHOD eGenMethod) = 0;
	virtual	IePalGenInfo::EGENMETHOD	getGenMethodType() const = 0;

	virtual	AiBoolean						isValid() const = 0;
};


IEDLLEXPORT IePalGenInfo* newIePalGenInfoOctree(CsSpace::Type csType = CsSpace::INDEXED, unsigned long ulNumEntries = 256);


//======================================================================================================

#endif  /* _cs_h */
