//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
// This file contains the extension to the standard set of primitive-
// type names that should be shared by all Autodesk developers, both
// in-house and third-party.  All new code and modules written in C++
// should use these type names along with those supplied by C++ itself
// (for example, int, long, float, double, etc.)
//
// See adeskabb.h for abbreviations of the following names.

#ifndef   _ADESK_H
#define   _ADESK_H

#include "AdAChar.h"            // ACHAR typedef

#if __LP64__
// We need this defined on the 64-bit OS X builds to avoid
// method overloading conficts between Adesk::Int32 and 
// Adesk::Boolean.
//
// This is particually important with respect
// to DWG filer read/writeItem method overloads.
#define Adesk_Boolean_is_bool 1
#endif

#pragma pack (push, 8)

#if defined(_MSC_VER)
// Use _MSC_VER to detect that we are building on Windows. This
// test will need to be updated a bit when we start supporting the Intel
// compiler.
//
#define _ADESK_WINDOWS_ 1
#elif defined(__APPLE__) && defined(__MACH__)
#define _ADESK_MAC_     1
    #define __w64
    #if __LP64__
        #define _AC64
    #endif //__LP64__
#endif //defined(__APPLE__) && defined(__MACH__)

struct Adesk
{
    // The types Int8, Int16 and Int32 will be conditionally compiled
    // to guarantee that each one represents an integer type of exactly
    // 8, 16 and 32 bits respectively.    These are to be used only when
    // the EXACT size of the integer is critical.
    //
    // We also need to be sure to use the Adesk::Int32 and Adesk::UInt32
    // datatypes rather than a long now that we support OSX 64-bit builds.
    //
    // Unlike Windows-64, on OSX-64 , a long is 64-bits. Any code that
    // assumes sizeof(int) == sizeof(long) will potentially have bugs. The
    // fix is to consistently use Adesk::Int32 and Adesk::UInt32 in place
    // of longs so we can normalize this all between the two platforms.
    //
    typedef char       Int8;
    typedef short      Int16;

    //
    // The unsigned versions of the above types.
    //
    typedef unsigned char  UInt8;
    typedef unsigned short UInt16;
#ifdef __LP64__
    typedef unsigned int   UInt32;
    typedef int            Int32;
#else
    typedef unsigned long  UInt32;
    typedef long           Int32;
#endif //__LP64__

#if defined(_ADESK_MAC_)
    typedef int64_t        Int64;
    typedef uint64_t       UInt64;
#else 
    typedef __int64        Int64;
    typedef unsigned __int64 UInt64;
#endif // _ADESK_MAC_

    // Convenient abbreviations (use optionally).
    //
    typedef unsigned char  uchar;
    typedef unsigned short ushort;
    typedef unsigned int   uint;
#ifdef __LP64__
    // We have too much code that assumes sizeof(int)
    // == sizeof(long) to allow for 64-bit longs.
    // So, for the __LP64__ model we need to make
    // ulong's 32-bit.
    //
    typedef UInt32         ulong;
#else
    typedef unsigned long  ulong;
#endif //__LP64__
    // integer/unsigned integers that can hold a pointer value.
    // These change size depending on the platform and should NEVER
    // be streamed out to permanent storage.
#if !defined(_WIN64) && !defined (_AC64)

    // Using __w64 let's us catch potential errors at compile time
    // when /Wp64 is enabled.  Also, we use long, instead of int,
    // in the 32-bit build.  That's for compatibility with the Int32
    // and UInt32 types.
    //
    typedef __w64 long          LongPtr;
    typedef __w64 unsigned long ULongPtr;
    //
    typedef __w64 int           IntPtr;
    typedef __w64 unsigned int  UIntPtr;
#else   // _WIN64 || _AC64

#ifdef _ADESK_MAC_
    typedef int64_t             LongPtr;
    typedef uint64_t            ULongPtr;
    typedef int64_t             IntPtr;
    typedef uint64_t            UIntPtr;
#else
    typedef __int64             LongPtr;
    typedef unsigned __int64    ULongPtr;
    typedef __int64             IntPtr;
    typedef unsigned __int64    UIntPtr;
#endif // _ADESK_MAC_

#endif // _WIN64 || _AC64

    typedef LongPtr IntDbId;
    typedef IntPtr GsMarker;

    // Logical type (Note: never use int when Boolean is intended!)
    //
#ifndef Adesk_Boolean_is_bool
    typedef int        Boolean;
    enum           { kFalse = 0, kTrue = 1 };
#else
    typedef bool       Boolean;
    typedef enum {kFalse = false, kTrue = true} BooleanVal;
#endif

};

#undef NULL
#define NULL 0

#pragma pack (pop)

//  These are constant definitions: regardless of whether the Unicode
//  or legacy character system is in use, the legacy character type
//  will always be an 8-bit character.
//
//  Note: use LEGACY_CHAR to represent *textual* information; do not
//  use it for 8-bit binary data; the AC_BYTE type, below, is intended
//  for that use.  Use legacy characters sparingly, where ACHAR is
//  inappropriate.
typedef          char         LEGACY_CHAR;
typedef          char*        LEGACY_STRING;
typedef const    char*        LEGACY_STRING_CONST;
typedef       unsigned short  WIDE_CHAR;          // UTF-16 format
typedef       unsigned short* WIDE_STRING;        // UTF-16 format
typedef const unsigned short* WIDE_STRING_CONST;  // UTF-16 format

//  One of the (ab)uses of the char type is to point to bytes of memory.
//  The (void*) isn't good for this because the sizeof a void element may
//  not be what one expects.  This type is offered as a generic pointer
//  to memory, but in which sizeof(element) == 1.  We use char instead
//  of byte only because signed/unsigned mismatches will cause a flurry
//  of warnings in the transition; eventually, the type can be anything
//  we want.
typedef          char*   MEMORY_POINTER;
typedef const    char*   MEMORY_POINTER_CONST;

//  Describes an 8-bit numerical quantity, *not* a character.
typedef unsigned char    AC_BYTE;

// Use ADESK_NO_VTABLE on base classes which:
//   1. have virtual methods
//   2. are never instantiated
//   3. have a ctor and/or a dtor
//   4. do not call any virtual methods in the ctor or dtor
// This allows the compiler to avoid assigning a vtable pointer at
// the top of the base class's ctor and dtor.  So the vtable itself
// and any methods it points to which aren't used elsewhere can be
// omitted by the linker and reduce overall space.
//
// Make sure though that the base class is never instantiated.  Making
// the ctor protected or using pure virtual methods can help with this.
//
#if defined(_MSC_VER)
    #define ADESK_NO_VTABLE           __declspec(novtable)
    #define ADESK_STDCALL             __stdcall
    #define ADESK_DEPRECATED          __declspec(deprecated)
    #define ADESK_DEPRECATED_MSG(MSG) __declspec(deprecated(MSG))
    #define ADESK_DATA_IMPORT         __declspec(dllimport)
#else 
    #define ADESK_NO_VTABLE

    // The GCC 4.0 compiler doesn't seem to support the stdcall attribute
    // for 64-bit builds. If we use it, we just get a ton of warnings
    // from the compiler mentioning that it isn't supported.
    #if defined(__LP64__) || defined(_ADESK_IOS_)
        #define ADESK_STDCALL
    #else
        #define ADESK_STDCALL         __attribute__((stdcall))   
    #endif // __LP64__
    
    #define ADESK_DEPRECATED          __attribute__((__deprecated__))
    #define ADESK_DEPRECATED_MSG(MSG) __attribute__((__deprecated__))
    #define ADESK_DATA_IMPORT         extern

    // Redefine __declspec(method) for gcc
    #define __declspec(method) __declspec_##method
    #define _declspec(method) __declspec_##method

    #define __declspec_selectany      __attribute__ ((__weak__))

    #define __declspec_dllexport      __attribute__ ((__visibility__("default")))
    #define __declspec_dllimport      

    #define __declspec_noinline       __attribute__ ((__noinline__))
    #define __declspec_noreturn       __attribute__ ((__noreturn__))
    #define __declspec_deprecated     __attribute__ ((__deprecated__))
    #define __declspec_novtable
    #define __declspec_allocate(name) __attribute__ ((section("__DATA," name)))


#endif //_MSC_VER

#ifdef _MSC_EXTENSIONS
    #define ADESK_OVERRIDE  override
    #define ADESK_SEALED sealed
#else //_MSC_EXTENSIONS
    #define ADESK_OVERRIDE
    #define ADESK_SEALED 
#endif //_MSC_EXTENSIONS

#define MIGRATION_ERRORS

#if defined(_MSC_VER) && defined (MIGRATION_ERRORS)
    #define ADESK_SEALED_VIRTUAL virtual
    #if !defined(ADESK_SEALED)
        #define ADESK_SEALED sealed
    #endif //ADESK_SEALED
#else //MIGRATION_ERRORS
    #define ADESK_SEALED_VIRTUAL 
    #define ADESK_SEALED
#endif //MIGRATION_ERRORS

//
// Compiler indentification
//
#if defined(__INTEL_COMPILER) || defined (_MSC_VER)
    #define ADESK_FORCE_INLINE __forceinline
#else //__INTEL_COMPILER || _MSC_VER
    #define ADESK_FORCE_INLINE inline
#endif //__INTEL_COMPILER || _MSC_VER

#ifdef _ADESK_WINDOWS_
#define VA_ARG_WCHAR(ap, t)      va_arg(ap, wchar_t)
#else
#define VA_ARG_WCHAR(ap, t)      va_arg(ap, int)
#endif

#endif //_ADESK_H
