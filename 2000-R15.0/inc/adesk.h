#ifndef   _ADESK_H
#define   _ADESK_H
//
//  (C) Copyright 1993-1999 by Autodesk, Inc.  All rights reserved.
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
    // 8, 16 and 32 bits respectively.	These are to be used only when
    // the EXACT size of the integer is critical.
    //
    typedef char	   Int8;
    typedef short	   Int16;
    typedef long	   Int32;
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
    typedef int 	   Boolean;
    enum		   { kFalse = 0, kTrue = 1 };
#else
    typedef bool	   Boolean;
    enum		   { kFalse = false, kTrue = true };
#endif
};

#ifndef NULL
#define NULL 0
#endif

#pragma pack (pop)
#endif
