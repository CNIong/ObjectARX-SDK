//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////



/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0620 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for ..\..\..\..\inc\arxsdk\AcTc.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0620 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAcadToolProperties,0xC7D10438,0x330C,0x461D,0x9D,0xC0,0xC2,0xD3,0x1F,0x74,0x6D,0x37);


MIDL_DEFINE_GUID(IID, IID_IAcadToolProperties2,0xA0E6B0E3,0x09FB,0x4E3C,0xB1,0x34,0x5E,0xDD,0x05,0xCB,0xAB,0x37);


MIDL_DEFINE_GUID(IID, IID_IAcadToolProperties3,0xF1800037,0xCB71,0x47BB,0x8C,0x06,0xC4,0xF3,0xC5,0x33,0x63,0x16);


MIDL_DEFINE_GUID(IID, IID_IAcadStockTool,0xB9A18560,0xC006,0x4F2D,0x8E,0x22,0xFF,0x55,0x38,0x9D,0xAB,0xEB);


MIDL_DEFINE_GUID(IID, IID_IAcadToolContextMenu,0xC717E8F3,0x14C7,0x4D64,0xB4,0x42,0x72,0x87,0x6D,0xE3,0x25,0x10);


MIDL_DEFINE_GUID(IID, IID_IAcadTool,0x4909ACC0,0x3574,0x4867,0xA1,0x20,0x54,0x3F,0xB2,0x88,0xE5,0xF9);


MIDL_DEFINE_GUID(IID, IID_IAcadTool2,0xCB0E3669,0x222E,0x46AB,0x9D,0xD0,0x98,0x76,0xE6,0xD0,0x52,0xAD);


MIDL_DEFINE_GUID(IID, IID_IAcadToolFlyoutShape,0x2F1A2EE9,0x32C3,0x489A,0xA2,0x9E,0x08,0x85,0x1F,0xC9,0x27,0xDA);


MIDL_DEFINE_GUID(IID, IID_IAcadToolSort,0xAF6D759E,0x0EDD,0x46DF,0x9E,0x0B,0x8D,0xC0,0x1A,0x20,0x6C,0xF7);


MIDL_DEFINE_GUID(IID, IID_IAcadToolDropTarget,0x76B9A439,0xB3BF,0x4346,0x80,0x01,0x74,0xEB,0xFA,0xD3,0x11,0x3A);


MIDL_DEFINE_GUID(IID, IID_IAcadToolDragSource,0xC8C6D2B1,0xA430,0x4949,0x8F,0x5A,0xFF,0x3C,0x35,0x33,0xCF,0x00);


MIDL_DEFINE_GUID(IID, IID_IAcadToolCopyPaste,0x5E32FE25,0x7769,0x4C8E,0x94,0x47,0xDB,0x92,0x1D,0x1D,0x24,0x9E);


MIDL_DEFINE_GUID(IID, IID_IAcadToolImage,0x74009B5D,0x217A,0x44B6,0x82,0x71,0x3A,0x43,0x98,0x51,0xEA,0xB5);


MIDL_DEFINE_GUID(IID, LIBID_AcTcLib,0x76017700,0xFD9C,0x4FB8,0xB0,0x0A,0x7A,0x51,0x35,0x9B,0xDD,0x7E);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadToolProperties,0x8C7C7AB1,0x0466,0x4FEB,0xB1,0x5A,0x5D,0xF6,0x93,0x18,0xA0,0x43);


MIDL_DEFINE_GUID(CLSID, CLSID_AcadToolImage,0x79DC18B6,0xB07B,0x4559,0xBF,0xB9,0x3D,0xD8,0x8D,0x9E,0x8A,0x5A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



