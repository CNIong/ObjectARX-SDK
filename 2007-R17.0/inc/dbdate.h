#ifndef AD_DBDATE_H
#define AD_DBDATE_H
//
// (C) Copyright 1994-1999 by Autodesk, Inc.
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
// DESCRIPTION: API for date class.

#include "acdb.h"

#pragma pack(push, 8)

class AcDbDwgFiler;

class AcDbDate
{
public:
    enum InitialValue {
        kInitZero          = 1,
        kInitLocalTime     = 2,
        kInitUniversalTime = 3
    };
    AcDbDate();
    AcDbDate(InitialValue i);
    AcDbDate(const AcDbDate&);
    virtual ~AcDbDate();

    const AcDbDate& operator= (const AcDbDate&);

    // Get and set the date.
    //
    void  getDate (short& month, short& day, short& year) const;
    void  setDate (short month, short day, short year);
    short month   () const;
    void  setMonth(short);
    short day     () const;
    void  setDay  (short);
    short year    () const;
    void  setYear (short);

#ifdef _WINBASE_
    // Get and set with win32 SYSTEMTIME struct.
    //
    void  getTime (SYSTEMTIME &st) const;
    void  setTime (const SYSTEMTIME &st);
#endif

    // Get and set the time.
    //
    void  getTime  (short& hour, short& min, short& sec, short& msec) const;
    void  setTime  (short hour, short min, short sec, short msec);
    short hour     () const;
    void  setHour  (short);
    short minute   () const;
    void  setMinute(short);
    short second   () const;
    void  setSecond(short);
    short millisecond() const;
    void  setMillisecond(short);
    void  setToZero();

    // Initialize with current time.
    //
    void  getLocalTime();
    void  getUniversalTime();

    // Convert between local and universal time
    //
    void localToUniversal();
    void universalToLocal();
 
    // Get/Set Julian representation for the date.
    //
    long   julianDay           () const;
    long   msecsPastMidnight   () const;
    void   setJulianDay        (long julianDay);
    void   setMsecsPastMidnight(long msec);
    void   setJulianDate       (long julianDay, long msec);
    double julianFraction      () const;
    void   setJulianFraction   (double);
 
    // Boolean comparison operators
    //
    bool operator== (const AcDbDate&) const;
    bool operator > (const AcDbDate&) const;
    bool operator >= (const AcDbDate&) const;
    bool operator < (const AcDbDate&) const;
    bool operator <= (const AcDbDate&) const;

    // Arithmetic operators.
    //
    const AcDbDate operator + (const AcDbDate &date) const;
    const AcDbDate operator - (const AcDbDate &date) const;
    const AcDbDate & operator += (const AcDbDate &date);
    const AcDbDate & operator -= (const AcDbDate &date);

    // Obsolete.  Please use += or -= operators.
    const AcDbDate& add      (const AcDbDate &date);
    const AcDbDate& subtract (const AcDbDate &date);

    // Dwg in and out.
    //
    Acad::ErrorStatus dwgOut(AcDbDwgFiler *outFiler) const;
    Acad::ErrorStatus dwgIn (AcDbDwgFiler *inFiler);

private:
    friend class AcDbImpDate;
    AcDbImpDate *mpImpDate;
};

inline const AcDbDate AcDbDate::operator + (const AcDbDate & d) const
{
    return AcDbDate(*this) += d;
}

inline const AcDbDate AcDbDate::operator - (const AcDbDate & d) const
{
    return AcDbDate(*this) -= d;
}

inline bool AcDbDate::operator < (const AcDbDate & d) const
{
    return ! operator >= (d);
}

inline bool AcDbDate::operator <= (const AcDbDate & d) const
{
    return ! operator > (d);
}

inline const AcDbDate & AcDbDate::add(const AcDbDate &date)
{
    return operator += (date);
}

inline const AcDbDate & AcDbDate::subtract(const AcDbDate &date)
{
    return operator -= (date);
}

#pragma pack(pop)

#endif

