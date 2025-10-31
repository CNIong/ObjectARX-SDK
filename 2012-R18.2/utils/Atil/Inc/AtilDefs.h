///////////////////////////////////////////////////////////////////////////////
//
// (C) Autodesk, Inc. 2007-2008. All rights reserved.
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
///////////////////////////////////////////////////////////////////////////////


#ifndef ATILDEFS_H
#define ATILDEFS_H

// Export this information in this header
#define ATIL_EXPORT

/// <summary> Force inclusion of "half" float globally.
#ifndef _HALF_H
#include "Half.h"
#endif

/// <summary>
/// ATIL namespace definitions and constants.
/// </summary>
///
/// <remarks>
/// This is the namespace enclosed global definitions for ATIL. Type
/// size constants are declared here as well as some ATIL specific 
/// orientation and limits. This file also contains macro activated 
/// platform specific information that lets ATIL be more easily ported
/// to additional platforms.
/// </remarks>
///
namespace Atil
{

/// <summary>
/// Orientation of images or coordinate systems in ATIL.
/// </summary>
///
/// <remarks>
/// When applied to images the order of application is:
///     row progression/columnprogression
/// </remarks>
///
enum Orientation 
{ 
    /// <summary>
    /// Rows progress from top to bottom, columns progress from left to right
    /// </summary>
    ///
    kTopDownLeftRight,

    /// <summary>
    /// Rows progress from top to bottom, columns progress from left to right
    /// </summary>
    ///
    kTopDownRightLeft,

    /// <summary>
    /// Rows progress from bottom to top, columns progress from left to right
    /// </summary>
    ///
    kBottomUpLeftRight,

    /// <summary>
    /// Rows progress from bottom to top, columns progress from right to left
    /// </summary>
    ///
    kBottomUpRightLeft,

    /// <summary>
    /// Rows progress from left to right, columns progress from top to bottom
    /// </summary>
    ///
    kLeftRightTopDown,

    /// <summary>
    /// Rows progress from right to left, columns progress from top to bottom
    /// </summary>
    ///
    kRightLeftTopDown,

    /// <summary>
    /// Rows progress from left to right, columns progress from bottom to top
    /// </summary>
    ///
    kLeftRightBottomUp,

    /// <summary>
    /// Rows progress from right to left, columns progress from bottom to top
    /// </summary>
    ///
    kRightLeftBottomUp 
};

/// <summary>
/// ATIL constant value for PI
/// </summary>
///
const double kPi = 3.14159265358979323846;

/// <summary>
/// ATIL constant value for PI * 2
/// </summary>
///
const double kTwoPi = 6.28318530717958647692;

/// <summary>
/// ATIL constant value for PI / 2
/// </summary>
///
const double kHalfPi = 1.57079632679489661923;

/// <summary>
/// ATIL constant value for floating point equivalence testing
/// </summary>
///
const double kTolerance = 1.0e-10;

/// <summary>
/// ATIL constant value for testing angle floating point equivalence testing
/// </summary>
///
const double kEpsilon = 1.0e-10;

#ifdef _WIN32
    typedef unsigned char Data8;
    typedef unsigned short Data16;
    typedef unsigned int Data32;
    typedef unsigned __int64 Data64;
    typedef struct _ATIL_DATA128 { \
        union { \
            struct { unsigned int a; unsigned int b; unsigned int c; unsigned int d; } ui; \
            struct { float a; float b; float c; float d; } fl; \
            struct { Data64 high64; Data64 low64; } db; \
        } value; \
        bool operator== (const struct _ATIL_DATA128& rhs) const { return (value.ui.a == rhs.value.ui.a && value.ui.b == rhs.value.ui.b && value.ui.c == rhs.value.ui.c && value.ui.d == rhs.value.ui.d); } \
        bool operator!= (const struct _ATIL_DATA128& rhs) const { return (value.ui.a != rhs.value.ui.a || value.ui.b != rhs.value.ui.b || value.ui.c != rhs.value.ui.c || value.ui.d != rhs.value.ui.d); } \
        void setToZero() {value.db.high64 = 0; value.db.low64 = 0;} \
    } Data128;

    typedef unsigned char Byte;

    typedef signed char Int8;
    typedef unsigned char UInt8;

    typedef signed short Int16;
    typedef unsigned short UInt16;

    typedef signed int Int32;
    typedef unsigned int UInt32;
    
    typedef signed __int64 Int64;
    typedef unsigned __int64 UInt64;

    #define INT32_MAX 2147483647
    #define INT32_MIN -2147483647-1
    #define UINT32_MAX 4294967295
#ifndef NULL
#define NULL 0
#endif

#ifdef UNICODE
    typedef wchar_t char_t;
#else
    typedef char char_t;
#endif

#else

#ifdef __INTEL_COMPILER  
    typedef unsigned char Data8;
    typedef unsigned short Data16;
    typedef unsigned int Data32;
    typedef unsigned __int64 Data64;
    typedef struct _ATIL_DATA128 { \
        union { \
            struct { unsigned int a; unsigned int b; unsigned int c; unsigned int d; } ui; \
            struct { float a; float b; float c; float d; } fl; \
            struct { Data64 high64; Data64 low64; } db; \
        } value; \
        bool operator== (const struct _ATIL_DATA128& rhs) const { return (value.ui.a == rhs.value.ui.a && value.ui.b == rhs.value.ui.b && value.ui.c == rhs.value.ui.c && value.ui.d == rhs.value.ui.d); } \
        bool operator!= (const struct _ATIL_DATA128& rhs) const { return (value.ui.a != rhs.value.ui.a || value.ui.b != rhs.value.ui.b || value.ui.c != rhs.value.ui.c || value.ui.d != rhs.value.ui.d); } \
        void setToZero() {value.db.high64 = 0; value.db.low64 = 0;} \
    } Data128;

    typedef unsigned char Byte;

    typedef signed char Int8;
    typedef unsigned char UInt8;

    typedef signed short Int16;
    typedef unsigned short UInt16;

    typedef signed int Int32;
    typedef unsigned int UInt32;
    
    typedef signed __int64 Int64;
    typedef unsigned __int64 UInt64;

    #define INT32_MAX   2147483647
    #define INT32_MIN  -2147483647-1
    #define UINT32_MAX  4294967295
    
#ifndef NULL
#define NULL    0
#endif

#ifdef UNICODE
    typedef wchar_t char_t;
#else
    typedef char char_t;
#endif

#else // Gnu

typedef unsigned char Data8;
typedef unsigned short Data16;
typedef unsigned int Data32;
typedef unsigned long long Data64;
    typedef struct _ATIL_DATA128 { \
        union { \
            struct { unsigned int a; unsigned int b; unsigned int c; unsigned int d; } ui; \
            struct { float a; float b; float c; float d; } fl; \
            struct { Data64 high64; Data64 low64; } db; \
        } value; \
        bool operator== (const struct _ATIL_DATA128& rhs) const { return (value.ui.a == rhs.value.ui.a && value.ui.b == rhs.value.ui.b && value.ui.c == rhs.value.ui.c && value.ui.d == rhs.value.ui.d); } \
        bool operator!= (const struct _ATIL_DATA128& rhs) const { return (value.ui.a != rhs.value.ui.a || value.ui.b != rhs.value.ui.b || value.ui.c != rhs.value.ui.c || value.ui.d != rhs.value.ui.d); } \
        void setToZero() {value.db.high64 = 0; value.db.low64 = 0;} \
    } Data128;


typedef unsigned char Byte;

typedef signed char Int8;
typedef unsigned char UInt8;

typedef signed short Int16;
typedef unsigned short UInt16;

typedef signed int Int32;
typedef unsigned int UInt32;

typedef signed long long Int64;
typedef unsigned long long UInt64;

#define INT32_MAX   2147483647
#define INT32_MIN  -2147483647-1
#define UINT32_MAX  4294967295

#ifndef NULL
#define NULL    0
#endif

#ifdef UNICODE
typedef wchar_t char_t;
#else
typedef char char_t;
#endif

#endif
#endif

/// <summary> Mimics the WinNt definition to allow the composition of integer values
/// into a packed 64 bit value.
/// </summary>
typedef union _ATIL_LARGE_INTEGER {
    struct {
        UInt32 LowPart;
        int HighPart;
    } s;
    struct {
        UInt32 LowPart;
        int HighPart;
    } u;
    UInt64 QuadPart;
} ATIL_LARGE_INTEGER;

} // end of namespace 

#ifndef ATILVERSIONS_H
#include "AtilVersions.h"
#endif

#endif


