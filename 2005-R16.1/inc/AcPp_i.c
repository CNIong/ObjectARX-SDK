/*
   (C) Copyright 1999-2003 by Autodesk, Inc. 
  
   Permission to use, copy, modify, and distribute this software in
   object code form for any purpose and without fee is hereby granted, 
   provided that the above copyright notice appears in all copies and 
   that both that copyright notice and the limited warranty and
   restricted rights notice below appear in all supporting 
   documentation.
  
   AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
   AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
   MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
   DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
   UNINTERRUPTED OR ERROR FREE.
  
   Use, duplication, or disclosure by the U.S. Government is subject to 
   restrictions set forth in FAR 52.227-19 (Commercial Computer
   Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
   (Rights in Technical Data and Computer Software), as applicable.
  
  
*/

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Feb 24 23:23:12 2004
 */
/* Compiler settings for U:\global\src\coreapps\opm\AcPp.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)

#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAcPpAcadInput,0x07816A95,0x3C14,0x4236,0xB9,0xD3,0xAA,0x7F,0x4A,0x4A,0x1E,0xFB);


MIDL_DEFINE_GUID(IID, IID_IAcPpPalette,0xA20A927F,0x5508,0x4624,0x91,0x57,0xFD,0x5C,0xBE,0x5B,0x2D,0x64);


MIDL_DEFINE_GUID(IID, IID_IAcPpPaletteEvents,0xC1EA7682,0x303C,0x4173,0xBA,0x92,0x0E,0xEF,0x3D,0xD3,0x75,0x6E);


MIDL_DEFINE_GUID(IID, IID_IAcPpPaletteSet,0x0CC0CED7,0x7D69,0x490b,0xA8,0x4B,0xA7,0x50,0x06,0x74,0xA2,0x9C);


MIDL_DEFINE_GUID(IID, IID_IAcPpPaletteSetEvents,0xC3F530AF,0xE211,0x49fa,0x9E,0x02,0x28,0x29,0x0E,0x41,0x41,0xF6);


MIDL_DEFINE_GUID(IID, LIBID_AcPpLib,0x5CD1397D,0x084E,0x4020,0x80,0x22,0xB6,0x5B,0x93,0x63,0x6D,0xC9);


MIDL_DEFINE_GUID(CLSID, CLSID_AcPpAcadInput,0x9307A809,0x170D,0x4A75,0xB8,0xEC,0xD3,0xC4,0x62,0xD2,0xF4,0xDB);


MIDL_DEFINE_GUID(CLSID, CLSID_AcPpPaletteSet,0x2FAA8BEA,0xAB1B,0x479a,0x97,0xB2,0x6E,0x7A,0xAB,0x38,0x75,0x0E);


MIDL_DEFINE_GUID(CLSID, CLSID_AcPpPalette,0x83E53FB0,0xC3F9,0x44c8,0x89,0x17,0x1A,0x79,0xD8,0x9B,0x90,0xAA);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Feb 24 23:23:12 2004
 */
/* Compiler settings for U:\global\src\coreapps\opm\AcPp.idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)

#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAcPpAcadInput,0x07816A95,0x3C14,0x4236,0xB9,0xD3,0xAA,0x7F,0x4A,0x4A,0x1E,0xFB);


MIDL_DEFINE_GUID(IID, IID_IAcPpPalette,0xA20A927F,0x5508,0x4624,0x91,0x57,0xFD,0x5C,0xBE,0x5B,0x2D,0x64);


MIDL_DEFINE_GUID(IID, IID_IAcPpPaletteEvents,0xC1EA7682,0x303C,0x4173,0xBA,0x92,0x0E,0xEF,0x3D,0xD3,0x75,0x6E);


MIDL_DEFINE_GUID(IID, IID_IAcPpPaletteSet,0x0CC0CED7,0x7D69,0x490b,0xA8,0x4B,0xA7,0x50,0x06,0x74,0xA2,0x9C);


MIDL_DEFINE_GUID(IID, IID_IAcPpPaletteSetEvents,0xC3F530AF,0xE211,0x49fa,0x9E,0x02,0x28,0x29,0x0E,0x41,0x41,0xF6);


MIDL_DEFINE_GUID(IID, LIBID_AcPpLib,0x5CD1397D,0x084E,0x4020,0x80,0x22,0xB6,0x5B,0x93,0x63,0x6D,0xC9);


MIDL_DEFINE_GUID(CLSID, CLSID_AcPpAcadInput,0x9307A809,0x170D,0x4A75,0xB8,0xEC,0xD3,0xC4,0x62,0xD2,0xF4,0xDB);


MIDL_DEFINE_GUID(CLSID, CLSID_AcPpPaletteSet,0x2FAA8BEA,0xAB1B,0x479a,0x97,0xB2,0x6E,0x7A,0xAB,0x38,0x75,0x0E);


MIDL_DEFINE_GUID(CLSID, CLSID_AcPpPalette,0x83E53FB0,0xC3F9,0x44c8,0x89,0x17,0x1A,0x79,0xD8,0x9B,0x90,0xAA);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

