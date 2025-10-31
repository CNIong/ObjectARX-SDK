#ifndef AD_DBHANDLE_H
#define AD_DBHANDLE_H 1
//
// (C) Copyright 1993-2007 by Autodesk, Inc.
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
//
// DESCRIPTION:
//
// This file contains the interface of the AcDbHandle class.
// Instances of this class encapsulate an 8-byte AutoCAD database
// handle value.

#include "adesk.h"

#pragma pack (push, 8)

class AcDbHandle
{
public:

    AcDbHandle();                // this ctor does not initialize the handle
    AcDbHandle(int lo, int hi);  // this one does - useful for creating null handles
    AcDbHandle(const ACHAR*);
    AcDbHandle(const Adesk::UInt64 &);

    AcDbHandle& operator=(const AcDbHandle&);

    AcDbHandle& operator=(const ACHAR*);

    // This gets the hex digits into a string buffer.
    void getIntoAsciiBuffer(ACHAR* pBuf) const;

    bool operator == (const AcDbHandle&) const;
    bool operator != (const AcDbHandle&) const;

    bool           isNull() const;
    void           setNull();

    Adesk::UInt32  low() const;
    Adesk::UInt32  high() const;
    void           setLow(Adesk::UInt32 low);
    void           setHigh(Adesk::UInt32 high);

    bool           isOne(void) const;

    /////// Implementation Class Members: Not for 3rd Party Consumption ///////
    //
    AcDbHandle& operator++();
    AcDbHandle operator++(int);
    void increment(void);
    void decrement(void);
    AcDbHandle operator + (const AcDbHandle&) const;
    AcDbHandle slowOperatorPlus(const AcDbHandle&) const;
    AcDbHandle& operator += (const AcDbHandle&);
    AcDbHandle operator - (const AcDbHandle&) const;
    AcDbHandle& operator -= (const AcDbHandle&);
    bool operator > (const AcDbHandle&) const;
    bool operator >= (const AcDbHandle&) const;
    bool operator < (const AcDbHandle&) const;
    bool operator <= (const AcDbHandle&) const;
    int compare(const AcDbHandle&) const;
    void copyToOldType(Adesk::UInt8 hand[8]) const;
    void copyFromOldType(const Adesk::UInt8 hand[8]);
    void getValueBytes(Adesk::UInt8*, Adesk::UInt8*) const;
    void setValueBytes(Adesk::UInt8, const Adesk::UInt8*);
    AcDbHandle& operator=(Adesk::UInt32);
    operator Adesk::UInt32() const;
    AcDbHandle operator + (Adesk::ULongPtr) const;
    void print() const;
    enum { kMaxValueBytes = 8 };
    int byte(Adesk::UInt32 i) const;
    int restZeros(int i) const;
private:
    Adesk::UInt64 & get64BitVal()
          { return *reinterpret_cast<Adesk::UInt64 *>(&mLow); }
    const Adesk::UInt64 & get64BitVal() const
          { return *reinterpret_cast<const Adesk::UInt64 *>(&mLow); }

    Adesk::UInt32 mLow;
    Adesk::UInt32 mHigh;
    friend class AcDbHandleTable;
    friend class HandleDataBase;
};

// This value is used to indicate cases where a conversion from
// an AcDbHandle to an Adesk::UInt32 has gone bad because the
// handle value was too great.
//
const Adesk::UInt32 kBadUInt32Handle = 0xFFFFFFFF;

inline AcDbHandle::AcDbHandle()
{
}

inline AcDbHandle::AcDbHandle(int lo, int hi) : mLow(lo), mHigh(hi)
{
}

inline
AcDbHandle::AcDbHandle(const Adesk::UInt64 &val)
{
    this->get64BitVal() = val;
}

inline AcDbHandle&
AcDbHandle::operator=(const AcDbHandle& handle)
{
    this->get64BitVal() = handle.get64BitVal();

    return *this;
}

inline AcDbHandle&
AcDbHandle::operator=(Adesk::UInt32 val)
{ mHigh = 0; mLow = val; return *this; }

inline AcDbHandle
AcDbHandle::operator+(const AcDbHandle& handle) const
{
    AcDbHandle tHandle(*this);
    tHandle.get64BitVal() += handle.get64BitVal();
    return tHandle;
}

inline AcDbHandle
AcDbHandle::operator+(Adesk::ULongPtr val) const
{
    AcDbHandle tHandle(*this);
    tHandle.get64BitVal() += val;
    return tHandle;
}


inline bool
AcDbHandle::operator > (const AcDbHandle& handle) const
{
    return this->get64BitVal() > handle.get64BitVal();
}

inline int
AcDbHandle::compare(const AcDbHandle& handle) const
{
    if (this->get64BitVal() > handle.get64BitVal())
        return -1;
    else if (this->get64BitVal() == handle.get64BitVal())
        return 0;
    else
        return 1;
}

inline bool
AcDbHandle::operator==(const AcDbHandle &handle) const
{
    return this->get64BitVal() == handle.get64BitVal();
}

inline bool
AcDbHandle::operator!=(const AcDbHandle &handle) const
{
    return this->get64BitVal() != handle.get64BitVal();
}

inline bool
AcDbHandle::isNull(void) const
{
    return this->get64BitVal() == 0;
}

inline void AcDbHandle::setNull(void)
{
    mHigh = mLow = 0;
}

inline bool
AcDbHandle::isOne(void) const
{
    return this->get64BitVal() == 1;
}

inline AcDbHandle&
AcDbHandle::operator++(void)          // ++AcDbHandle
{
    this->get64BitVal()++;

    return *this;
}

inline void
AcDbHandle::increment(void)          // AcDbHandle = AcDbHandle + 1;
{
    this->get64BitVal()++;
}

inline void
AcDbHandle::decrement(void)          // AcDbHandle = AcDbHandle - 1;
{
    this->get64BitVal()--;
}

inline AcDbHandle
AcDbHandle::operator++(int)           // AcDbHandle++
{
    AcDbHandle tempHandle = *this;
    ++(*this);
    return tempHandle;
}

inline AcDbHandle::operator Adesk::UInt32() const
{
    if (mHigh != 0)
        return kBadUInt32Handle;
    return mLow;
}

inline bool
AcDbHandle::operator < (const AcDbHandle& handle) const
{
    return this->get64BitVal() < handle.get64BitVal();
}

inline int AcDbHandle::byte(Adesk::UInt32 i) const
{
    // Unicode: leave as unsigned char *
    return *((unsigned char *)&mLow + i);
}

inline int AcDbHandle::restZeros(int i) const
{
    Adesk::UInt32 mask;
    if (i < 4) {
        mask = ~0 << (i << 3);
        return !(mHigh | (mLow & mask));
    } else {
        mask = ~0 << ((i - 4) << 3);
        return !(mHigh & mask);
    }
}

inline Adesk::UInt32  AcDbHandle::low() const
{
    return mLow;
}
inline Adesk::UInt32  AcDbHandle::high() const
{
    return mHigh;
}
 
inline void AcDbHandle::setLow(Adesk::UInt32 low)
{
    mLow = low;
    return;
}
inline void AcDbHandle::setHigh(Adesk::UInt32 high)
{
    mHigh = high;
    return;
}

#pragma pack (pop)

#endif
