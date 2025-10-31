#ifndef   _ADESK_H
#define   _ADESK_H
//
//  (C) Copyright 1993-2003 by Autodesk, Inc.  All rights reserved.
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
// DESCRIPTION:
//
// This file contains the extension to the standard set of primitive-
// type names that should be shared by all Autodesk developers, both
// in-house and third-party.  All new code and modules written in C++
// should use these type names along with those supplied by C++ itself
// (for example, int, long, float, double, etc.)
//
// See adeskabb.h for abbreviations of the following names.

// #define Adesk_Boolean_is_bool 1
#pragma pack (push, 8)

struct Adesk
{
    // The types Int8, Int16 and Int32 will be conditionally compiled
    // to guarantee that each one represents an integer type of exactly
    // 8, 16 and 32 bits respectively.    These are to be used only when
    // the EXACT size of the integer is critical.
    //
    typedef char       Int8;
    typedef short      Int16;
    typedef long       Int32;
    //
    // The unsigned versions of the above types.
    //
    typedef unsigned char  UInt8;
    typedef unsigned short UInt16;
    typedef unsigned long  UInt32;

    // Convenient abbreviations (use optionally).
    //
    typedef unsigned char  uchar;
    typedef unsigned short ushort;
    typedef unsigned int   uint;
    typedef unsigned long  ulong;

    // Logical type (Note: never use int when Boolean is intended!)
    //
#ifndef Adesk_Boolean_is_bool
    typedef int        Boolean;
    enum           { kFalse = 0, kTrue = 1 };
#else
    typedef bool       Boolean;
    enum           { kFalse = false, kTrue = true };
#endif
};

#ifndef NULL
#define NULL 0
#endif

#pragma pack (pop)


//  TODO: pre-BANFF RTM: Sanitize these comments.
//
//  Continued use of the type "char" is prohibited.  Please 
//  use only the abstract type "ACHAR" below, to contain 
//  character information.
typedef          char    ACHAR;

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
#define ADESK_NO_VTABLE __declspec(novtable)
#define ADESK_STDCALL   __stdcall
#define ADESK_DEPRECATED __declspec(deprecated)

#endif
