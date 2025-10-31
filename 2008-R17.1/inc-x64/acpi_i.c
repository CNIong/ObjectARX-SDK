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


/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0365 */
/* at Sun Feb 11 19:51:07 2007
 */
/* Compiler settings for U:\develop\global\src\coreapps\opm\Acpi\acpi.idl:
    Oicf, W1, Zp8, env=Win64 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyInspector,0x22A2DE3F,0x1F1E,0x4F04,0xBD,0x55,0xD0,0xF1,0x70,0x32,0x81,0xF9);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyEditControl,0x6371C569,0x72C0,0x43a0,0xA4,0x57,0x1E,0x9D,0x2E,0xB9,0x20,0x1E);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyEditEventsSink,0x5D6FA1C4,0x61B7,0x43C6,0x90,0x50,0xDC,0x24,0xB9,0x2F,0x47,0x45);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyUnspecified,0x63ECCF04,0x51B1,0x4fe1,0x97,0x2C,0x9E,0xFD,0x42,0x0A,0xDE,0xF4);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyDisplay,0x6a0d7861,0x8773,0x4d56,0xac,0x16,0x95,0xaf,0xf3,0x05,0x1e,0xbd);


MIDL_DEFINE_GUID(IID, IID_IAcPiCategorizeProperties,0x8590b992,0xd9a1,0x48d1,0x89,0x9a,0x35,0x8d,0x77,0xe1,0x51,0x2a);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropCommandButtons,0xA6CD83FA,0x32A5,0x4c1e,0x9F,0x2E,0x48,0x7A,0x61,0x2F,0x4A,0x77);


MIDL_DEFINE_GUID(IID, IID_IAcPiCommandButton,0xA5EAB6FD,0xEB1A,0x43d5,0xBC,0xE0,0x2D,0xA8,0xC4,0x0F,0x21,0xBA);


MIDL_DEFINE_GUID(IID, IID_IAcPiCommandButton2,0xAF4178BF,0x3E04,0x477e,0x80,0xB3,0x33,0xFC,0x2D,0xAE,0x49,0x4E);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyInspectorEventsSink,0x3EAF5E3F,0x5D7B,0x4873,0xB8,0xF4,0xA6,0xD9,0xB2,0xD1,0xEB,0x33);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyInspectorInputEventSink,0xB6E9DB08,0x8B45,0x4ad2,0xB3,0x3C,0x98,0x5B,0xBE,0x4F,0x37,0x56);


MIDL_DEFINE_GUID(IID, LIBID_ACPILib,0xC8CAF5A0,0xB473,0x453B,0xB5,0xF0,0xF0,0xBC,0x7A,0x96,0x1C,0x8B);


MIDL_DEFINE_GUID(CLSID, CLSID_AcPiPropertyInspector,0x31DBB451,0x9109,0x41EA,0x85,0x4C,0xB2,0x59,0x05,0x22,0x5A,0xEA);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



