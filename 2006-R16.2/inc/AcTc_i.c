/*
   (C) Copyright 1999-2004 by Autodesk, Inc. 
  
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
/* at Sat Mar 05 02:48:52 2005
 */
/* Compiler settings for ..\..\..\..\inc\arxsdk\AcTc.idl:
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

MIDL_DEFINE_GUID(IID, IID_IAcadToolProperties,0xC8498A0F,0xA997,0x454B,0xAC,0x19,0x95,0x55,0x13,0x9D,0xFB,0x10);


MIDL_DEFINE_GUID(IID, IID_IAcadToolProperties2,0x91C0D43F,0x507D,0x46f3,0x8D,0x54,0xC1,0x11,0x43,0xB2,0x70,0xFF);


MIDL_DEFINE_GUID(IID, IID_IAcadToolProperties3,0x9F3ACA08,0xA9BE,0x4ec8,0xBB,0xEB,0x1A,0x38,0xCB,0x22,0x13,0x62);


MIDL_DEFINE_GUID(IID, IID_IAcadStockTool,0xF3D70D77,0x8B79,0x4277,0x99,0xE4,0x70,0x4E,0x4C,0x17,0xDC,0x6E);


MIDL_DEFINE_GUID(IID, IID_IAcadToolContextMenu,0xBF9A27C9,0x5FB5,0x4DB9,0xB9,0x10,0x2A,0xC3,0x48,0x7C,0x95,0xB2);


MIDL_DEFINE_GUID(IID, IID_IAcadTool,0x7B064668,0xE0BE,0x4fdf,0x93,0x22,0xDC,0x48,0x40,0x24,0x87,0x8F);


MIDL_DEFINE_GUID(IID, IID_IAcadTool2,0x5ACBC770,0xAB29,0x42DA,0x91,0xA4,0x27,0x8E,0x39,0x1C,0xD4,0x18);


MIDL_DEFINE_GUID(IID, IID_IAcadToolFlyoutShape,0x167E99DB,0xE7BA,0x4bda,0x8C,0x6A,0x47,0xDC,0x06,0xCC,0x12,0xF6);


MIDL_DEFINE_GUID(IID, IID_IAcadToolSort,0x233CF99C,0x6B98,0x48df,0xB2,0x9C,0x23,0xA9,0xCC,0x88,0x2F,0x53);


MIDL_DEFINE_GUID(IID, IID_IAcadToolDropTarget,0x6FE6AD02,0xDDE9,0x4619,0xA7,0x7A,0x05,0xA1,0x83,0xD6,0x13,0xAD);


MIDL_DEFINE_GUID(IID, IID_IAcadToolDragSource,0x74A34F77,0x8C7B,0x4a43,0xB3,0xA8,0xD5,0xBB,0xFB,0xC1,0xF4,0x0C);


MIDL_DEFINE_GUID(IID, IID_IAcadToolCopyPaste,0xE1F1CB3B,0x5FC6,0x4eb8,0x86,0xDD,0xAF,0x0C,0xFA,0xFE,0x6B,0x00);


MIDL_DEFINE_GUID(IID, IID_IAcadToolImage,0xBE67D23E,0xE36A,0x11D5,0xB4,0xE5,0x00,0xB0,0xD0,0x3E,0x95,0x4A);


MIDL_DEFINE_GUID(IID, LIBID_AcTcLib,0x8C14D9E3,0x3F03,0x4F53,0x89,0x67,0x24,0x65,0x52,0xB3,0x04,0x4C);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadToolProperties,0x497C8B53,0xE920,0x4450,0x8D,0xD8,0xD7,0x3F,0x83,0xCB,0x8F,0x0F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadToolImage,0xBE67D23F,0xE36A,0x11D5,0xB4,0xE5,0x00,0xB0,0xD0,0x3E,0x95,0x4A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sat Mar 05 02:48:52 2005
 */
/* Compiler settings for ..\..\..\..\inc\arxsdk\AcTc.idl:
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

MIDL_DEFINE_GUID(IID, IID_IAcadToolProperties,0xC8498A0F,0xA997,0x454B,0xAC,0x19,0x95,0x55,0x13,0x9D,0xFB,0x10);


MIDL_DEFINE_GUID(IID, IID_IAcadToolProperties2,0x91C0D43F,0x507D,0x46f3,0x8D,0x54,0xC1,0x11,0x43,0xB2,0x70,0xFF);


MIDL_DEFINE_GUID(IID, IID_IAcadToolProperties3,0x9F3ACA08,0xA9BE,0x4ec8,0xBB,0xEB,0x1A,0x38,0xCB,0x22,0x13,0x62);


MIDL_DEFINE_GUID(IID, IID_IAcadStockTool,0xF3D70D77,0x8B79,0x4277,0x99,0xE4,0x70,0x4E,0x4C,0x17,0xDC,0x6E);


MIDL_DEFINE_GUID(IID, IID_IAcadToolContextMenu,0xBF9A27C9,0x5FB5,0x4DB9,0xB9,0x10,0x2A,0xC3,0x48,0x7C,0x95,0xB2);


MIDL_DEFINE_GUID(IID, IID_IAcadTool,0x7B064668,0xE0BE,0x4fdf,0x93,0x22,0xDC,0x48,0x40,0x24,0x87,0x8F);


MIDL_DEFINE_GUID(IID, IID_IAcadTool2,0x5ACBC770,0xAB29,0x42DA,0x91,0xA4,0x27,0x8E,0x39,0x1C,0xD4,0x18);


MIDL_DEFINE_GUID(IID, IID_IAcadToolFlyoutShape,0x167E99DB,0xE7BA,0x4bda,0x8C,0x6A,0x47,0xDC,0x06,0xCC,0x12,0xF6);


MIDL_DEFINE_GUID(IID, IID_IAcadToolSort,0x233CF99C,0x6B98,0x48df,0xB2,0x9C,0x23,0xA9,0xCC,0x88,0x2F,0x53);


MIDL_DEFINE_GUID(IID, IID_IAcadToolDropTarget,0x6FE6AD02,0xDDE9,0x4619,0xA7,0x7A,0x05,0xA1,0x83,0xD6,0x13,0xAD);


MIDL_DEFINE_GUID(IID, IID_IAcadToolDragSource,0x74A34F77,0x8C7B,0x4a43,0xB3,0xA8,0xD5,0xBB,0xFB,0xC1,0xF4,0x0C);


MIDL_DEFINE_GUID(IID, IID_IAcadToolCopyPaste,0xE1F1CB3B,0x5FC6,0x4eb8,0x86,0xDD,0xAF,0x0C,0xFA,0xFE,0x6B,0x00);


MIDL_DEFINE_GUID(IID, IID_IAcadToolImage,0xBE67D23E,0xE36A,0x11D5,0xB4,0xE5,0x00,0xB0,0xD0,0x3E,0x95,0x4A);


MIDL_DEFINE_GUID(IID, LIBID_AcTcLib,0x8C14D9E3,0x3F03,0x4F53,0x89,0x67,0x24,0x65,0x52,0xB3,0x04,0x4C);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadToolProperties,0x497C8B53,0xE920,0x4450,0x8D,0xD8,0xD7,0x3F,0x83,0xCB,0x8F,0x0F);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadToolImage,0xBE67D23F,0xE36A,0x11D5,0xB4,0xE5,0x00,0xB0,0xD0,0x3E,0x95,0x4A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

