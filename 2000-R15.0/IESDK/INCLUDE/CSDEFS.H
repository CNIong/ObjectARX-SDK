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

// csdefs.h Basic definitions used by CS and IE.

#ifndef _csdefs_h
#define _csdefs_h


/*** PLATFORM SPECIFICS ***/
#if defined(WIN32) || defined(_WIN32)			//Win32
 #define CS_MSWIN 1
 #define CS_WIN32 1
 #define IE_HUGE
 #define CS_NEAR
 #ifndef _stdlib_h
  #include <stdlib.h>
 #endif
#else
 #error "unknown platform or compiler"
#endif

/*** BASIC DEFINES ***/
#ifndef FALSE
 #define FALSE 0
#endif
#ifndef TRUE
 #define TRUE 1
#endif
#ifndef NIL
 #define NIL 0
#endif
#ifdef NULL
 #undef NULL
#endif
#define NULL 0
#ifndef ENDL
 #define ENDL endl
#endif

/*** BASIC DATA TYPES ***/
#ifndef _aitypes_h
 #define _aitypes_h	//temporary
 typedef unsigned int 	AiBoolean;
 typedef long 		Int;
 typedef long 		Int32;
 typedef short 		Int16;
#ifndef ACAD_INCLUDED
 typedef signed char 	Int8;
#endif
 typedef unsigned long	UInt;
 typedef unsigned long	UInt32;
 typedef unsigned short	UInt16;
 typedef unsigned char	UInt8;
 typedef double		Real;
 typedef double 	Real64;
 typedef float		Real32;
#endif

typedef int		Ints;
typedef unsigned int	UInts;
typedef unsigned int	CsHwnd;
class CsVoid {};

/*** WIN DLL SUPPORT ***/
#ifndef IEDLLEXPORT
 #if defined(CS_WIN32) && (defined(CS_USEDLL) || defined(CS_EXPORT))
  #if defined(CS_EXPORT)
   #define IEDLLEXPORT __declspec(dllexport)
  #else
   #define IEDLLEXPORT __declspec(dllimport)
  #endif
 #else
  #define IEDLLEXPORT
 #endif
#endif

/*** INLINING STUFF ***/
#define USE_INLINES	//currently must always be defined
#ifdef USE_INLINES
 #define INLINE	inline
#else
 #define INLINE
#endif

/*** INTERNAL LEGACY STUFF ***/
#ifndef CS_APP
 #if defined(DEBUG)
  extern "C" void ieAssertTrap(const char*, const char*, Int);
  #define IEASSERT(ex)  { if (!(ex)){ ieAssertTrap(#ex,__FILE__,__LINE__); }}
 #else
  #define IEASSERT(ex)
 #endif
 #define DBG(code)
#endif

#endif //_csdefs_h
