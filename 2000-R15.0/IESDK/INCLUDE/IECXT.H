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

//	iecxt.h - image random access contexts

#ifndef _iecxt_h
#define _iecxt_h

/* enable/disable inline argument checking here */
//#define IE_CXT_CHECK_ARGS

// constructor functions IeImage::makeReadCxt and IeImage::makeWriteCxt 
// in ieimage.h

class IeCxt
{
  public:
    
    virtual ~IeCxt() {};
    virtual void unlock() = 0;
    virtual void setMaxNumTables(UInt val) = 0;	//default = 4

    /*** pixel access ***/    
    UInts get1(UInts x, UInts y);
    UInts get8(UInts x, UInts y);
    UInt get32(UInts x, UInts y);

    void set1(UInts x, UInts y);
    void clear1(UInts x, UInts y);
    void put1(UInts x, UInts y, UInts val);
    void put8(UInts x, UInts y, UInts val);
    void put32(UInts x, UInts y, UInt val);
    
    /*** row access ***/
    virtual void getRow(UInts x, UInts y, UInts numPixels, void *pBuffer) = 0;
    virtual void setRow(UInts x, UInts y, UInts numPixels, UInt val) = 0;
    virtual void putRow(UInts x, UInts y, UInts numPixels, const void *pData) = 0;
    
    /*** region access ***/
    enum AbyssMode { abyssConst, abyssReplicate, abyssMirror, 
                     abyssWrap, abyssFail };
    virtual void setAbyss(AbyssMode modeX, AbyssMode modeY, 
    			  UInt valX = 0, UInt valY = 0) = 0;
    virtual UInt numBytes() const = 0;	//rect buffer size
    virtual AiBoolean getRect(Ints x, Ints y, void *pBuffer) = 0;
    virtual void setRect(Ints x, Ints y, UInt val) = 0;
    virtual void putRect(Ints x, Ints y, const void *pData) = 0;
    
    virtual Ief *rectStream(const Int& x, const Int& y) = 0;
    virtual void putRect(Ints x, Ints y, Ief *input) = 0;

	UInt32 threadId();
	AiBoolean isWritable();

  protected:
    virtual UInt lock(UInt, UInt) = 0;
    UInt *mpYt;
    UInts *mpBt;
    UInt *mpSt;
    UInt *mpCt;
    UInts mXmin;		//quadbyte offset
    UInts mXmax;		//quadbyte offset
    UInts mXlimit;		//quadbyte offset; for arg checking only
    UInts mYlimit;		//for arg checking only
    AiBoolean mIsTiled;
    AiBoolean mIsWritable;
	UInt32 mThreadId;
};

/*** INLINES ***************************************************************/
// cannot use IE_PCHECK macro in inlines due to MSVC++ compiler bug
inline UInts IeCxt::get1(UInts x, UInts y)
{
#ifdef IE_CXT_CHECK_ARGS
    if (!((x>>5) <= mXlimit && y <= mYlimit))
    	csRep->doAssert("IE", __FILE__, __LINE__, 0, 
    		"IeCxt::put32 - x or y out of range");
#endif
    register UInt p = mpYt[y];
    if (mIsTiled && (!p || (x>>5) < mXmin || (x>>5) > mXmax))
        p = lock(x>>5, y);
    return (UInts) ((UInt) *((UInt*) p + (x>>5)) >> mpBt[x & 31]) & 1;
}


inline UInts IeCxt::get8(UInts x, UInts y)
{
#ifdef IE_CXT_CHECK_ARGS
    if (!((x>>2) <= mXlimit && y <= mYlimit))
    	csRep->doAssert("IE", __FILE__, __LINE__, 0, 
    		"IeCxt::get8 - x or y out of range");
#endif
    register UInt p = mpYt[y];
    if (mIsTiled && (p == 0 || (x>>2) < mXmin || (x>>2) > mXmax))
        p = lock(x>>2, y);
    return *(UInt8*) (p + x);
}


inline UInt IeCxt::get32(UInts x, UInts y)
{
#ifdef IE_CXT_CHECK_ARGS
    if (!(x <= mXlimit && y <= mYlimit))
    	csRep->doAssert("IE", __FILE__, __LINE__, 0, 
    		"IeCxt::get32 - x or y out of range");
#endif
    register UInt p = mpYt[y];
    if (mIsTiled && (!p || x < mXmin || x > mXmax))
        p = lock(x, y);
    return *(UInt*) (p + (x<<2));
}

inline void IeCxt::set1(UInts x, UInts y)
{
#ifdef IE_CXT_CHECK_ARGS
    if (!(mIsWritable && (x>>5) <= mXlimit && y <= mYlimit))
    	csRep->doAssert("IE", __FILE__, __LINE__, 0, 
    		"IeCxt::set1 - x or y out of range");
#endif
    register UInt p = mpYt[y];
    if (mIsTiled && (p == 0 || (x>>5) < mXmin || (x>>5) > mXmax))
        p = lock(x>>5, y);
    *((UInt*) p + (x>>5)) |= mpSt[x & 31];
}


inline void IeCxt::clear1(UInts x, UInts y)
{
#ifdef IE_CXT_CHECK_ARGS
    if (!(mIsWritable && (x>>5) <= mXlimit && y <= mYlimit))
    	csRep->doAssert("IE", __FILE__, __LINE__, 0, 
    		"IeCxt::clear1 - x or y out of range");
#endif
    register UInt p = mpYt[y];
    if (mIsTiled && (p == 0 || (x>>5) < mXmin || (x>>5) > mXmax))
        p = lock(x>>5, y);
    *((UInt*) p + (x>>5)) &= mpCt[x & 31];
}

inline void IeCxt::put1(UInts x, UInts y, UInts val)
{
    if (val)
        set1(x, y);
    else
        clear1(x, y);
}


inline void IeCxt::put8(UInts x, UInts y, UInts val)
{
#ifdef IE_CXT_CHECK_ARGS
    if (!(mIsWritable && (x>>2) <= mXlimit && y <= mYlimit))
    	csRep->doAssert("IE", __FILE__, __LINE__, 0, 
    		"IeCxt::put8 - x or y out of range");
#endif
    register UInt p = mpYt[y];
    if (mIsTiled && (p == 0 || (x>>2) < mXmin || (x>>2) > mXmax))
        p = lock(x>>2, y);
    *(UInt8*) (p + x) = (UInt8) val;
}


inline void IeCxt::put32(UInts x, UInts y, UInt val)
{
#ifdef IE_CXT_CHECK_ARGS
    if (!(mIsWritable && x <= mXlimit && y <= mYlimit))
    	csRep->doAssert("IE", __FILE__, __LINE__, 0, 
    		"IeCxt::put32 - x or y out of range");
#endif
    register UInt p = mpYt[y];
    if (mIsTiled && (!p || x < mXmin || x > mXmax))
        p = lock(x, y);
    *(UInt*) (p + (x<<2)) = val;
}

inline UInt32 IeCxt::threadId()
{
	return mThreadId;
}

inline AiBoolean IeCxt::isWritable()
{
	return mIsWritable;
}

#endif	/* _iecxt_h */
