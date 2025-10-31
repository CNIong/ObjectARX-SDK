// (C) Copyright 1999 by Autodesk, Inc. 
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

/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Oct 27 15:03:01 1998
 */
/* Compiler settings for E:\TEMP\square\AsdkSquareLib\AsdkSquareLib.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "AsdkSquareLib.h"

#define TYPE_FORMAT_STRING_SIZE   1195                              
#define PROC_FORMAT_STRING_SIZE   2143                              

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Standard interface: __MIDL_itf_AsdkSquareLib_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IAcadHyperlink, ver. 0.0,
   GUID={0xB2547D94,0xCA93,0x11D1,{0xB6,0x0F,0x00,0x60,0xB0,0x87,0xE2,0x35}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAcadHyperlink_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IAcadHyperlink_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    28,
    56,
    84,
    112,
    140
    };

static const MIDL_SERVER_INFO IAcadHyperlink_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAcadHyperlink_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAcadHyperlink_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAcadHyperlink_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(13) _IAcadHyperlinkProxyVtbl = 
{
    &IAcadHyperlink_ProxyInfo,
    &IID_IAcadHyperlink,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IAcadHyperlink::put_URL */ ,
    (void *)-1 /* IAcadHyperlink::get_URL */ ,
    (void *)-1 /* IAcadHyperlink::put_URLDescription */ ,
    (void *)-1 /* IAcadHyperlink::get_URLDescription */ ,
    (void *)-1 /* IAcadHyperlink::get_Application */ ,
    (void *)-1 /* IAcadHyperlink::Delete */
};


static const PRPC_STUB_FUNCTION IAcadHyperlink_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IAcadHyperlinkStubVtbl =
{
    &IID_IAcadHyperlink,
    &IAcadHyperlink_ServerInfo,
    13,
    &IAcadHyperlink_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAcadHyperlinks, ver. 0.0,
   GUID={0xB2547D92,0x056E,0x11d2,{0xB6,0x51,0x00,0x60,0xB0,0x87,0xE2,0x35}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAcadHyperlinks_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IAcadHyperlinks_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    162,
    196,
    224,
    252,
    280
    };

static const MIDL_SERVER_INFO IAcadHyperlinks_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAcadHyperlinks_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAcadHyperlinks_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAcadHyperlinks_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(12) _IAcadHyperlinksProxyVtbl = 
{
    &IAcadHyperlinks_ProxyInfo,
    &IID_IAcadHyperlinks,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IAcadHyperlinks::Item */ ,
    (void *)-1 /* IAcadHyperlinks::get_Count */ ,
    (void *)-1 /* IAcadHyperlinks::get__NewEnum */ ,
    (void *)-1 /* IAcadHyperlinks::get_Application */ ,
    (void *)-1 /* IAcadHyperlinks::Add */
};


static const PRPC_STUB_FUNCTION IAcadHyperlinks_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IAcadHyperlinksStubVtbl =
{
    &IID_IAcadHyperlinks,
    &IAcadHyperlinks_ServerInfo,
    12,
    &IAcadHyperlinks_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAcadObject, ver. 0.0,
   GUID={0x5B57EEA0,0xCA9A,0x11D1,{0xB6,0x0F,0x00,0x60,0xB0,0x87,0xE2,0x35}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAcadObject_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IAcadObject_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    320,
    28,
    348,
    388,
    422,
    444,
    472,
    500,
    528,
    556,
    584
    };

static const MIDL_SERVER_INFO IAcadObject_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAcadObject_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAcadObject_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAcadObject_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(18) _IAcadObjectProxyVtbl = 
{
    &IAcadObject_ProxyInfo,
    &IID_IAcadObject,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IAcadObject::get_Handle */ ,
    (void *)-1 /* IAcadObject::get_ObjectName */ ,
    (void *)-1 /* IAcadObject::GetXData */ ,
    (void *)-1 /* IAcadObject::SetXData */ ,
    (void *)-1 /* IAcadObject::Delete */ ,
    (void *)-1 /* IAcadObject::get_ObjectID */ ,
    (void *)-1 /* IAcadObject::get_Application */ ,
    (void *)-1 /* IAcadObject::get_Database */ ,
    (void *)-1 /* IAcadObject::get_HasExtensionDictionary */ ,
    (void *)-1 /* IAcadObject::GetExtensionDictionary */ ,
    (void *)-1 /* IAcadObject::Erase */
};


static const PRPC_STUB_FUNCTION IAcadObject_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IAcadObjectStubVtbl =
{
    &IID_IAcadObject,
    &IAcadObject_ServerInfo,
    18,
    &IAcadObject_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAcadXRecord, ver. 0.0,
   GUID={0x2928D4DD,0xCA93,0x11D1,{0xB6,0x0F,0x00,0x60,0xB0,0x87,0xE2,0x35}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAcadXRecord_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IAcadXRecord_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    320,
    28,
    348,
    388,
    422,
    444,
    472,
    500,
    528,
    556,
    584,
    606,
    634,
    662,
    696,
    730,
    758
    };

static const MIDL_SERVER_INFO IAcadXRecord_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAcadXRecord_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAcadXRecord_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAcadXRecord_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(24) _IAcadXRecordProxyVtbl = 
{
    &IAcadXRecord_ProxyInfo,
    &IID_IAcadXRecord,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IAcadObject::get_Handle */ ,
    (void *)-1 /* IAcadObject::get_ObjectName */ ,
    (void *)-1 /* IAcadObject::GetXData */ ,
    (void *)-1 /* IAcadObject::SetXData */ ,
    (void *)-1 /* IAcadObject::Delete */ ,
    (void *)-1 /* IAcadObject::get_ObjectID */ ,
    (void *)-1 /* IAcadObject::get_Application */ ,
    (void *)-1 /* IAcadObject::get_Database */ ,
    (void *)-1 /* IAcadObject::get_HasExtensionDictionary */ ,
    (void *)-1 /* IAcadObject::GetExtensionDictionary */ ,
    (void *)-1 /* IAcadObject::Erase */ ,
    (void *)-1 /* IAcadXRecord::get_Name */ ,
    (void *)-1 /* IAcadXRecord::put_Name */ ,
    (void *)-1 /* IAcadXRecord::GetXRecordData */ ,
    (void *)-1 /* IAcadXRecord::SetXRecordData */ ,
    (void *)-1 /* IAcadXRecord::get_TranslateIDs */ ,
    (void *)-1 /* IAcadXRecord::put_TranslateIDs */
};


static const PRPC_STUB_FUNCTION IAcadXRecord_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IAcadXRecordStubVtbl =
{
    &IID_IAcadXRecord,
    &IAcadXRecord_ServerInfo,
    24,
    &IAcadXRecord_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAcadDictionary, ver. 0.0,
   GUID={0xF8DD32D0,0xF7DF,0x11D1,{0xA2,0xC8,0x08,0x00,0x09,0xDC,0x63,0x9A}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAcadDictionary_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IAcadDictionary_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    320,
    28,
    348,
    388,
    422,
    444,
    472,
    500,
    528,
    556,
    584,
    606,
    634,
    786,
    826,
    860,
    894,
    928,
    962,
    996,
    1030,
    1058,
    1086
    };

static const MIDL_SERVER_INFO IAcadDictionary_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAcadDictionary_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAcadDictionary_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAcadDictionary_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(30) _IAcadDictionaryProxyVtbl = 
{
    &IAcadDictionary_ProxyInfo,
    &IID_IAcadDictionary,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IAcadObject::get_Handle */ ,
    (void *)-1 /* IAcadObject::get_ObjectName */ ,
    (void *)-1 /* IAcadObject::GetXData */ ,
    (void *)-1 /* IAcadObject::SetXData */ ,
    (void *)-1 /* IAcadObject::Delete */ ,
    (void *)-1 /* IAcadObject::get_ObjectID */ ,
    (void *)-1 /* IAcadObject::get_Application */ ,
    (void *)-1 /* IAcadObject::get_Database */ ,
    (void *)-1 /* IAcadObject::get_HasExtensionDictionary */ ,
    (void *)-1 /* IAcadObject::GetExtensionDictionary */ ,
    (void *)-1 /* IAcadObject::Erase */ ,
    (void *)-1 /* IAcadDictionary::get_Name */ ,
    (void *)-1 /* IAcadDictionary::put_Name */ ,
    (void *)-1 /* IAcadDictionary::AddObject */ ,
    (void *)-1 /* IAcadDictionary::GetName */ ,
    (void *)-1 /* IAcadDictionary::GetObject */ ,
    (void *)-1 /* IAcadDictionary::Remove */ ,
    (void *)-1 /* IAcadDictionary::Rename */ ,
    (void *)-1 /* IAcadDictionary::Replace */ ,
    (void *)-1 /* IAcadDictionary::Item */ ,
    (void *)-1 /* IAcadDictionary::get__NewEnum */ ,
    (void *)-1 /* IAcadDictionary::get_Count */ ,
    (void *)-1 /* IAcadDictionary::AddXRecord */
};


static const PRPC_STUB_FUNCTION IAcadDictionary_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IAcadDictionaryStubVtbl =
{
    &IID_IAcadDictionary,
    &IAcadDictionary_ServerInfo,
    30,
    &IAcadDictionary_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAcadObjectEvents, ver. 0.0,
   GUID={0x67F4AC32,0xC9DC,0x11d1,{0xB6,0x0F,0x00,0x60,0xB0,0x87,0xE2,0x35}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAcadObjectEvents_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IAcadObjectEvents_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1120
    };

static const MIDL_SERVER_INFO IAcadObjectEvents_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAcadObjectEvents_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAcadObjectEvents_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAcadObjectEvents_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(8) _IAcadObjectEventsProxyVtbl = 
{
    &IAcadObjectEvents_ProxyInfo,
    &IID_IAcadObjectEvents,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IAcadObjectEvents::Modified */
};


static const PRPC_STUB_FUNCTION IAcadObjectEvents_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IAcadObjectEventsStubVtbl =
{
    &IID_IAcadObjectEvents,
    &IAcadObjectEvents_ServerInfo,
    8,
    &IAcadObjectEvents_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAcadEntity, ver. 0.0,
   GUID={0x5B57EEA2,0xCA9A,0x11D1,{0xB6,0x0F,0x00,0x60,0xB0,0x87,0xE2,0x35}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAcadEntity_ServerInfo;

#pragma code_seg(".orpc")
/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_Move_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [in] */ VARIANT FromPoint,
    /* [in] */ VARIANT ToPoint)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,ToPoint);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1594],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1594],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&FromPoint,
                  ( unsigned char __RPC_FAR * )&ToPoint);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1594],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_Rotate_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [in] */ VARIANT BasePoint,
    /* [in] */ double RotationAngle)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,RotationAngle);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1628],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1628],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&BasePoint,
                  ( unsigned char __RPC_FAR * )&RotationAngle);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1628],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_Rotate3D_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [in] */ VARIANT Point1,
    /* [in] */ VARIANT Point2,
    /* [in] */ double RotationAngle)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,RotationAngle);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1662],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1662],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&Point1,
                  ( unsigned char __RPC_FAR * )&Point2,
                  ( unsigned char __RPC_FAR * )&RotationAngle);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1662],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_Mirror_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [in] */ VARIANT Point1,
    /* [in] */ VARIANT Point2,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *pMirrorObj)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pMirrorObj);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1702],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1702],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&Point1,
                  ( unsigned char __RPC_FAR * )&Point2,
                  ( unsigned char __RPC_FAR * )&pMirrorObj);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1702],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_Mirror3D_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [in] */ VARIANT point1,
    /* [in] */ VARIANT point2,
    /* [in] */ VARIANT point3,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *pMirrorObj)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pMirrorObj);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1742],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1742],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&point1,
                  ( unsigned char __RPC_FAR * )&point2,
                  ( unsigned char __RPC_FAR * )&point3,
                  ( unsigned char __RPC_FAR * )&pMirrorObj);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1742],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_ScaleEntity_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [in] */ VARIANT BasePoint,
    /* [in] */ double ScaleFactor)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,ScaleFactor);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1788],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1788],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&BasePoint,
                  ( unsigned char __RPC_FAR * )&ScaleFactor);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1788],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_TransformBy_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [in] */ VARIANT TransformationMatrix)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,TransformationMatrix);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1822],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1822],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&TransformationMatrix);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1822],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_Update_Proxy( 
    IAcadEntity __RPC_FAR * This)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,This);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1850],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1850],
                  ( unsigned char __RPC_FAR * )&This);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1850],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_GetBoundingBox_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *MinPoint,
    /* [out] */ VARIANT __RPC_FAR *MaxPoint)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,MaxPoint);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1872],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1872],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&MinPoint,
                  ( unsigned char __RPC_FAR * )&MaxPoint);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1872],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_IntersectWith_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [in] */ LPDISPATCH IntersectObject,
    /* [in] */ AcExtendOption option,
    /* [retval][out] */ VARIANT __RPC_FAR *intPoints)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,intPoints);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1906],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1906],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&IntersectObject,
                  ( unsigned char __RPC_FAR * )&option,
                  ( unsigned char __RPC_FAR * )&intPoints);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1906],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_get_PlotStyleName_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *plotStyle)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,plotStyle);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1946],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1946],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&plotStyle);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1946],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_put_PlotStyleName_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [in] */ BSTR plotStyle)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,plotStyle);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1974],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1974],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&plotStyle);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1974],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_get_Lineweight_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [retval][out] */ ACAD_LWEIGHT __RPC_FAR *lineweight)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,lineweight);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2002],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2002],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&lineweight);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2002],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_put_Lineweight_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [in] */ ACAD_LWEIGHT lineweight)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,lineweight);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2030],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2030],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&lineweight);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2030],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][helpcontext][readonly][propget][id] */ HRESULT STDMETHODCALLTYPE IAcadEntity_get_Hyperlinks_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [retval][out] */ IAcadHyperlinks __RPC_FAR *__RPC_FAR *HyperLinks)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,HyperLinks);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2058],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2058],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&HyperLinks);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2058],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][nonbrowsable][hidden][readonly][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadEntity_get_EntityName_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *EntityName)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,EntityName);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2086],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2086],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&EntityName);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2086],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][nonbrowsable][hidden][readonly][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadEntity_get_EntityType_Proxy( 
    IAcadEntity __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *entType)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,entType);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2114],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2114],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&entType);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2114],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

static const unsigned short IAcadEntity_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    320,
    28,
    348,
    388,
    422,
    444,
    472,
    500,
    528,
    556,
    584,
    1148,
    1176,
    1204,
    1232,
    1260,
    1288,
    1316,
    1344,
    1372,
    1400,
    1428,
    1474,
    1538,
    1566,
    1594,
    1628,
    1662,
    1702,
    1742,
    1788,
    1822,
    1850,
    1872,
    1906,
    1946,
    1974,
    2002,
    2030,
    2058,
    2086,
    2114
    };

static const MIDL_SERVER_INFO IAcadEntity_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAcadEntity_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAcadEntity_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAcadEntity_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(49) _IAcadEntityProxyVtbl = 
{
    &IAcadEntity_ProxyInfo,
    &IID_IAcadEntity,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IAcadObject::get_Handle */ ,
    (void *)-1 /* IAcadObject::get_ObjectName */ ,
    (void *)-1 /* IAcadObject::GetXData */ ,
    (void *)-1 /* IAcadObject::SetXData */ ,
    (void *)-1 /* IAcadObject::Delete */ ,
    (void *)-1 /* IAcadObject::get_ObjectID */ ,
    (void *)-1 /* IAcadObject::get_Application */ ,
    (void *)-1 /* IAcadObject::get_Database */ ,
    (void *)-1 /* IAcadObject::get_HasExtensionDictionary */ ,
    (void *)-1 /* IAcadObject::GetExtensionDictionary */ ,
    (void *)-1 /* IAcadObject::Erase */ ,
    (void *)-1 /* IAcadEntity::get_Color */ ,
    (void *)-1 /* IAcadEntity::put_Color */ ,
    (void *)-1 /* IAcadEntity::get_Layer */ ,
    (void *)-1 /* IAcadEntity::put_Layer */ ,
    (void *)-1 /* IAcadEntity::get_Linetype */ ,
    (void *)-1 /* IAcadEntity::put_Linetype */ ,
    (void *)-1 /* IAcadEntity::get_LinetypeScale */ ,
    (void *)-1 /* IAcadEntity::put_LinetypeScale */ ,
    (void *)-1 /* IAcadEntity::get_Visible */ ,
    (void *)-1 /* IAcadEntity::put_Visible */ ,
    (void *)-1 /* IAcadEntity::ArrayPolar */ ,
    (void *)-1 /* IAcadEntity::ArrayRectangular */ ,
    (void *)-1 /* IAcadEntity::Highlight */ ,
    (void *)-1 /* IAcadEntity::Copy */ ,
    IAcadEntity_Move_Proxy ,
    IAcadEntity_Rotate_Proxy ,
    IAcadEntity_Rotate3D_Proxy ,
    IAcadEntity_Mirror_Proxy ,
    IAcadEntity_Mirror3D_Proxy ,
    IAcadEntity_ScaleEntity_Proxy ,
    IAcadEntity_TransformBy_Proxy ,
    IAcadEntity_Update_Proxy ,
    IAcadEntity_GetBoundingBox_Proxy ,
    IAcadEntity_IntersectWith_Proxy ,
    IAcadEntity_get_PlotStyleName_Proxy ,
    IAcadEntity_put_PlotStyleName_Proxy ,
    IAcadEntity_get_Lineweight_Proxy ,
    IAcadEntity_put_Lineweight_Proxy ,
    IAcadEntity_get_Hyperlinks_Proxy ,
    IAcadEntity_get_EntityName_Proxy ,
    IAcadEntity_get_EntityType_Proxy
};


static const PRPC_STUB_FUNCTION IAcadEntity_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IAcadEntityStubVtbl =
{
    &IID_IAcadEntity,
    &IAcadEntity_ServerInfo,
    49,
    &IAcadEntity_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAsdkSquareWrapper, ver. 0.0,
   GUID={0x800F70AD,0x6DE9,0x11D2,{0xA7,0xA6,0x00,0x60,0xB0,0x87,0x24,0x57}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

CINTERFACE_PROXY_VTABLE(49) _IAsdkSquareWrapperProxyVtbl = 
{
    0,
    &IID_IAsdkSquareWrapper,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    0 /* forced delegation IAcadObject::get_Handle */ ,
    0 /* forced delegation IAcadObject::get_ObjectName */ ,
    0 /* forced delegation IAcadObject::GetXData */ ,
    0 /* forced delegation IAcadObject::SetXData */ ,
    0 /* forced delegation IAcadObject::Delete */ ,
    0 /* forced delegation IAcadObject::get_ObjectID */ ,
    0 /* forced delegation IAcadObject::get_Application */ ,
    0 /* forced delegation IAcadObject::get_Database */ ,
    0 /* forced delegation IAcadObject::get_HasExtensionDictionary */ ,
    0 /* forced delegation IAcadObject::GetExtensionDictionary */ ,
    0 /* forced delegation IAcadObject::Erase */ ,
    0 /* forced delegation IAcadEntity::get_Color */ ,
    0 /* forced delegation IAcadEntity::put_Color */ ,
    0 /* forced delegation IAcadEntity::get_Layer */ ,
    0 /* forced delegation IAcadEntity::put_Layer */ ,
    0 /* forced delegation IAcadEntity::get_Linetype */ ,
    0 /* forced delegation IAcadEntity::put_Linetype */ ,
    0 /* forced delegation IAcadEntity::get_LinetypeScale */ ,
    0 /* forced delegation IAcadEntity::put_LinetypeScale */ ,
    0 /* forced delegation IAcadEntity::get_Visible */ ,
    0 /* forced delegation IAcadEntity::put_Visible */ ,
    0 /* forced delegation IAcadEntity::ArrayPolar */ ,
    0 /* forced delegation IAcadEntity::ArrayRectangular */ ,
    0 /* forced delegation IAcadEntity::Highlight */ ,
    0 /* forced delegation IAcadEntity::Copy */ ,
    IAcadEntity_Move_Proxy ,
    IAcadEntity_Rotate_Proxy ,
    IAcadEntity_Rotate3D_Proxy ,
    IAcadEntity_Mirror_Proxy ,
    IAcadEntity_Mirror3D_Proxy ,
    IAcadEntity_ScaleEntity_Proxy ,
    IAcadEntity_TransformBy_Proxy ,
    IAcadEntity_Update_Proxy ,
    IAcadEntity_GetBoundingBox_Proxy ,
    IAcadEntity_IntersectWith_Proxy ,
    IAcadEntity_get_PlotStyleName_Proxy ,
    IAcadEntity_put_PlotStyleName_Proxy ,
    IAcadEntity_get_Lineweight_Proxy ,
    IAcadEntity_put_Lineweight_Proxy ,
    IAcadEntity_get_Hyperlinks_Proxy ,
    IAcadEntity_get_EntityName_Proxy ,
    IAcadEntity_get_EntityType_Proxy
};


static const PRPC_STUB_FUNCTION IAsdkSquareWrapper_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IAsdkSquareWrapperStubVtbl =
{
    &IID_IAsdkSquareWrapper,
    0,
    49,
    &IAsdkSquareWrapper_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, float, double or hyper in -Oif or -Oicf, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

    /* Procedure put_URL */

            0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/*  2 */    NdrFcLong( 0x0 ),   /* 0 */
/*  6 */    NdrFcShort( 0x7 ),  /* 7 */
#ifndef _ALPHA_
/*  8 */    NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 10 */    NdrFcShort( 0x0 ),  /* 0 */
/* 12 */    NdrFcShort( 0x8 ),  /* 8 */
/* 14 */    0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x2,        /* 2 */

    /* Parameter URLPath */

/* 16 */    NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 18 */    NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 20 */    NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Return value */

/* 22 */    NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 24 */    NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 26 */    0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_ObjectName */


    /* Procedure get_URL */

/* 28 */    0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 30 */    NdrFcLong( 0x0 ),   /* 0 */
/* 34 */    NdrFcShort( 0x8 ),  /* 8 */
#ifndef _ALPHA_
/* 36 */    NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 38 */    NdrFcShort( 0x0 ),  /* 0 */
/* 40 */    NdrFcShort( 0x8 ),  /* 8 */
/* 42 */    0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter ObjectName */


    /* Parameter URLPath */

/* 44 */    NdrFcShort( 0x2113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 46 */    NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 48 */    NdrFcShort( 0x2c ), /* Type Offset=44 */

    /* Return value */


    /* Return value */

/* 50 */    NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 52 */    NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 54 */    0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure put_URLDescription */

/* 56 */    0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 58 */    NdrFcLong( 0x0 ),   /* 0 */
/* 62 */    NdrFcShort( 0x9 ),  /* 9 */
#ifndef _ALPHA_
/* 64 */    NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 66 */    NdrFcShort( 0x0 ),  /* 0 */
/* 68 */    NdrFcShort( 0x8 ),  /* 8 */
/* 70 */    0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x2,        /* 2 */

    /* Parameter Description */

/* 72 */    NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 74 */    NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 76 */    NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Return value */

/* 78 */    NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 80 */    NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 82 */    0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_URLDescription */

/* 84 */    0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 86 */    NdrFcLong( 0x0 ),   /* 0 */
/* 90 */    NdrFcShort( 0xa ),  /* 10 */
#ifndef _ALPHA_
/* 92 */    NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 94 */    NdrFcShort( 0x0 ),  /* 0 */
/* 96 */    NdrFcShort( 0x8 ),  /* 8 */
/* 98 */    0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter Description */

/* 100 */   NdrFcShort( 0x2113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 102 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 104 */   NdrFcShort( 0x2c ), /* Type Offset=44 */

    /* Return value */

/* 106 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 108 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 110 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Application */

/* 112 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 114 */   NdrFcLong( 0x0 ),   /* 0 */
/* 118 */   NdrFcShort( 0xb ),  /* 11 */
#ifndef _ALPHA_
/* 120 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 122 */   NdrFcShort( 0x0 ),  /* 0 */
/* 124 */   NdrFcShort( 0x8 ),  /* 8 */
/* 126 */   0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter ApplicationObject */

/* 128 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 130 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 132 */   NdrFcShort( 0x36 ), /* Type Offset=54 */

    /* Return value */

/* 134 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 136 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 138 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Delete */

/* 140 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 142 */   NdrFcLong( 0x0 ),   /* 0 */
/* 146 */   NdrFcShort( 0xc ),  /* 12 */
#ifndef _ALPHA_
/* 148 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 150 */   NdrFcShort( 0x0 ),  /* 0 */
/* 152 */   NdrFcShort( 0x8 ),  /* 8 */
/* 154 */   0x4,        /* Oi2 Flags:  has return, */
            0x1,        /* 1 */

    /* Return value */

/* 156 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 158 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 160 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Item */

/* 162 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 164 */   NdrFcLong( 0x0 ),   /* 0 */
/* 168 */   NdrFcShort( 0x7 ),  /* 7 */
#ifndef _ALPHA_
/* 170 */   NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 172 */   NdrFcShort( 0x8 ),  /* 8 */
/* 174 */   NdrFcShort( 0x8 ),  /* 8 */
/* 176 */   0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x3,        /* 3 */

    /* Parameter Index */

/* 178 */   NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 180 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 182 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Parameter pItem */

/* 184 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 186 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 188 */   NdrFcShort( 0x4c ), /* Type Offset=76 */

    /* Return value */

/* 190 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 192 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 194 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Count */

/* 196 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 198 */   NdrFcLong( 0x0 ),   /* 0 */
/* 202 */   NdrFcShort( 0x8 ),  /* 8 */
#ifndef _ALPHA_
/* 204 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 206 */   NdrFcShort( 0x0 ),  /* 0 */
/* 208 */   NdrFcShort( 0x10 ), /* 16 */
/* 210 */   0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter pVal */

/* 212 */   NdrFcShort( 0x2150 ),   /* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 214 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 216 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Return value */

/* 218 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 220 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 222 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get__NewEnum */

/* 224 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 226 */   NdrFcLong( 0x0 ),   /* 0 */
/* 230 */   NdrFcShort( 0x9 ),  /* 9 */
#ifndef _ALPHA_
/* 232 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 234 */   NdrFcShort( 0x0 ),  /* 0 */
/* 236 */   NdrFcShort( 0x8 ),  /* 8 */
/* 238 */   0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter pVal */

/* 240 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 242 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 244 */   NdrFcShort( 0x66 ), /* Type Offset=102 */

    /* Return value */

/* 246 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 248 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 250 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Application */

/* 252 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 254 */   NdrFcLong( 0x0 ),   /* 0 */
/* 258 */   NdrFcShort( 0xa ),  /* 10 */
#ifndef _ALPHA_
/* 260 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 262 */   NdrFcShort( 0x0 ),  /* 0 */
/* 264 */   NdrFcShort( 0x8 ),  /* 8 */
/* 266 */   0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter ApplicationObject */

/* 268 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 270 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 272 */   NdrFcShort( 0x36 ), /* Type Offset=54 */

    /* Return value */

/* 274 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 276 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 278 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Add */

/* 280 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 282 */   NdrFcLong( 0x0 ),   /* 0 */
/* 286 */   NdrFcShort( 0xb ),  /* 11 */
#ifndef _ALPHA_
/* 288 */   NdrFcShort( 0x14 ), /* x86, MIPS, PPC Stack size/offset = 20 */
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 290 */   NdrFcShort( 0x0 ),  /* 0 */
/* 292 */   NdrFcShort( 0x8 ),  /* 8 */
/* 294 */   0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x4,        /* 4 */

    /* Parameter Name */

/* 296 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 298 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 300 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Parameter Description */

/* 302 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 304 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 306 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Parameter pHyperlink */

/* 308 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 310 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 312 */   NdrFcShort( 0x4c ), /* Type Offset=76 */

    /* Return value */

/* 314 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 316 */   NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 318 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Handle */

/* 320 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 322 */   NdrFcLong( 0x0 ),   /* 0 */
/* 326 */   NdrFcShort( 0x7 ),  /* 7 */
#ifndef _ALPHA_
/* 328 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 330 */   NdrFcShort( 0x0 ),  /* 0 */
/* 332 */   NdrFcShort( 0x8 ),  /* 8 */
/* 334 */   0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter Handle */

/* 336 */   NdrFcShort( 0x2113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 338 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 340 */   NdrFcShort( 0x2c ), /* Type Offset=44 */

    /* Return value */

/* 342 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 344 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 346 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure GetXData */

/* 348 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 350 */   NdrFcLong( 0x0 ),   /* 0 */
/* 354 */   NdrFcShort( 0x9 ),  /* 9 */
#ifndef _ALPHA_
/* 356 */   NdrFcShort( 0x14 ), /* x86, MIPS, PPC Stack size/offset = 20 */
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 358 */   NdrFcShort( 0x0 ),  /* 0 */
/* 360 */   NdrFcShort( 0x8 ),  /* 8 */
/* 362 */   0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x4,        /* 4 */

    /* Parameter AppName */

/* 364 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 366 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 368 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Parameter XDataType */

/* 370 */   NdrFcShort( 0x4113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 372 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 374 */   NdrFcShort( 0x402 ),    /* Type Offset=1026 */

    /* Parameter XDataValue */

/* 376 */   NdrFcShort( 0x4113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 378 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 380 */   NdrFcShort( 0x402 ),    /* Type Offset=1026 */

    /* Return value */

/* 382 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 384 */   NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 386 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure SetXData */

/* 388 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 390 */   NdrFcLong( 0x0 ),   /* 0 */
/* 394 */   NdrFcShort( 0xa ),  /* 10 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 396 */   NdrFcShort( 0x28 ), /* x86 Stack size/offset = 40 */
#else
            NdrFcShort( 0x2c ), /* MIPS & PPC Stack size/offset = 44 */
#endif
#else
            NdrFcShort( 0x30 ), /* Alpha Stack size/offset = 48 */
#endif
/* 398 */   NdrFcShort( 0x0 ),  /* 0 */
/* 400 */   NdrFcShort( 0x8 ),  /* 8 */
/* 402 */   0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter XDataType */

/* 404 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 406 */   NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 408 */   NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter XDataValue */

/* 410 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 412 */   NdrFcShort( 0x14 ), /* x86 Stack size/offset = 20 */
#else
            NdrFcShort( 0x18 ), /* MIPS & PPC Stack size/offset = 24 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 414 */   NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Return value */

/* 416 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 418 */   NdrFcShort( 0x24 ), /* x86 Stack size/offset = 36 */
#else
            NdrFcShort( 0x28 ), /* MIPS & PPC Stack size/offset = 40 */
#endif
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 420 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Delete */

/* 422 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 424 */   NdrFcLong( 0x0 ),   /* 0 */
/* 428 */   NdrFcShort( 0xb ),  /* 11 */
#ifndef _ALPHA_
/* 430 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 432 */   NdrFcShort( 0x0 ),  /* 0 */
/* 434 */   NdrFcShort( 0x8 ),  /* 8 */
/* 436 */   0x4,        /* Oi2 Flags:  has return, */
            0x1,        /* 1 */

    /* Return value */

/* 438 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 440 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 442 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_ObjectID */

/* 444 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 446 */   NdrFcLong( 0x0 ),   /* 0 */
/* 450 */   NdrFcShort( 0xc ),  /* 12 */
#ifndef _ALPHA_
/* 452 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 454 */   NdrFcShort( 0x0 ),  /* 0 */
/* 456 */   NdrFcShort( 0x10 ), /* 16 */
/* 458 */   0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter ObjectId */

/* 460 */   NdrFcShort( 0x2150 ),   /* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 462 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 464 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Return value */

/* 466 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 468 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 470 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Application */

/* 472 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 474 */   NdrFcLong( 0x0 ),   /* 0 */
/* 478 */   NdrFcShort( 0xd ),  /* 13 */
#ifndef _ALPHA_
/* 480 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 482 */   NdrFcShort( 0x0 ),  /* 0 */
/* 484 */   NdrFcShort( 0x8 ),  /* 8 */
/* 486 */   0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter ApplicationObject */

/* 488 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 490 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 492 */   NdrFcShort( 0x36 ), /* Type Offset=54 */

    /* Return value */

/* 494 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 496 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 498 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Database */

/* 500 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 502 */   NdrFcLong( 0x0 ),   /* 0 */
/* 506 */   NdrFcShort( 0xe ),  /* 14 */
#ifndef _ALPHA_
/* 508 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 510 */   NdrFcShort( 0x0 ),  /* 0 */
/* 512 */   NdrFcShort( 0x8 ),  /* 8 */
/* 514 */   0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter pDatabase */

/* 516 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 518 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 520 */   NdrFcShort( 0x36 ), /* Type Offset=54 */

    /* Return value */

/* 522 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 524 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 526 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_HasExtensionDictionary */

/* 528 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 530 */   NdrFcLong( 0x0 ),   /* 0 */
/* 534 */   NdrFcShort( 0xf ),  /* 15 */
#ifndef _ALPHA_
/* 536 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 538 */   NdrFcShort( 0x0 ),  /* 0 */
/* 540 */   NdrFcShort( 0xe ),  /* 14 */
/* 542 */   0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter bHasDictionary */

/* 544 */   NdrFcShort( 0x2150 ),   /* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 546 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 548 */   0x6,        /* FC_SHORT */
            0x0,        /* 0 */

    /* Return value */

/* 550 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 552 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 554 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure GetExtensionDictionary */

/* 556 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 558 */   NdrFcLong( 0x0 ),   /* 0 */
/* 562 */   NdrFcShort( 0x10 ), /* 16 */
#ifndef _ALPHA_
/* 564 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 566 */   NdrFcShort( 0x0 ),  /* 0 */
/* 568 */   NdrFcShort( 0x8 ),  /* 8 */
/* 570 */   0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter pExtDictionary */

/* 572 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 574 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 576 */   NdrFcShort( 0x41e ),    /* Type Offset=1054 */

    /* Return value */

/* 578 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 580 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 582 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Erase */

/* 584 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 586 */   NdrFcLong( 0x0 ),   /* 0 */
/* 590 */   NdrFcShort( 0x11 ), /* 17 */
#ifndef _ALPHA_
/* 592 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 594 */   NdrFcShort( 0x0 ),  /* 0 */
/* 596 */   NdrFcShort( 0x8 ),  /* 8 */
/* 598 */   0x4,        /* Oi2 Flags:  has return, */
            0x1,        /* 1 */

    /* Return value */

/* 600 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 602 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 604 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Name */


    /* Procedure get_Name */

/* 606 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 608 */   NdrFcLong( 0x0 ),   /* 0 */
/* 612 */   NdrFcShort( 0x12 ), /* 18 */
#ifndef _ALPHA_
/* 614 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 616 */   NdrFcShort( 0x0 ),  /* 0 */
/* 618 */   NdrFcShort( 0x8 ),  /* 8 */
/* 620 */   0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter pVal */


    /* Parameter bstrName */

/* 622 */   NdrFcShort( 0x2113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 624 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 626 */   NdrFcShort( 0x2c ), /* Type Offset=44 */

    /* Return value */


    /* Return value */

/* 628 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 630 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 632 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure put_Name */


    /* Procedure put_Name */

/* 634 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 636 */   NdrFcLong( 0x0 ),   /* 0 */
/* 640 */   NdrFcShort( 0x13 ), /* 19 */
#ifndef _ALPHA_
/* 642 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 644 */   NdrFcShort( 0x0 ),  /* 0 */
/* 646 */   NdrFcShort( 0x8 ),  /* 8 */
/* 648 */   0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x2,        /* 2 */

    /* Parameter newVal */


    /* Parameter bstrName */

/* 650 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 652 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 654 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Return value */


    /* Return value */

/* 656 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 658 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 660 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure GetXRecordData */

/* 662 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 664 */   NdrFcLong( 0x0 ),   /* 0 */
/* 668 */   NdrFcShort( 0x14 ), /* 20 */
#ifndef _ALPHA_
/* 670 */   NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 672 */   NdrFcShort( 0x0 ),  /* 0 */
/* 674 */   NdrFcShort( 0x8 ),  /* 8 */
/* 676 */   0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x3,        /* 3 */

    /* Parameter XRecordDataType */

/* 678 */   NdrFcShort( 0x4113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 680 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 682 */   NdrFcShort( 0x402 ),    /* Type Offset=1026 */

    /* Parameter XRecordDataValue */

/* 684 */   NdrFcShort( 0x4113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 686 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 688 */   NdrFcShort( 0x402 ),    /* Type Offset=1026 */

    /* Return value */

/* 690 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 692 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 694 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure SetXRecordData */

/* 696 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 698 */   NdrFcLong( 0x0 ),   /* 0 */
/* 702 */   NdrFcShort( 0x15 ), /* 21 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 704 */   NdrFcShort( 0x28 ), /* x86 Stack size/offset = 40 */
#else
            NdrFcShort( 0x2c ), /* MIPS & PPC Stack size/offset = 44 */
#endif
#else
            NdrFcShort( 0x30 ), /* Alpha Stack size/offset = 48 */
#endif
/* 706 */   NdrFcShort( 0x0 ),  /* 0 */
/* 708 */   NdrFcShort( 0x8 ),  /* 8 */
/* 710 */   0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter XRecordDataType */

/* 712 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 714 */   NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 716 */   NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter XRecordDataValue */

/* 718 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 720 */   NdrFcShort( 0x14 ), /* x86 Stack size/offset = 20 */
#else
            NdrFcShort( 0x18 ), /* MIPS & PPC Stack size/offset = 24 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 722 */   NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Return value */

/* 724 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 726 */   NdrFcShort( 0x24 ), /* x86 Stack size/offset = 36 */
#else
            NdrFcShort( 0x28 ), /* MIPS & PPC Stack size/offset = 40 */
#endif
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 728 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_TranslateIDs */

/* 730 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 732 */   NdrFcLong( 0x0 ),   /* 0 */
/* 736 */   NdrFcShort( 0x16 ), /* 22 */
#ifndef _ALPHA_
/* 738 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 740 */   NdrFcShort( 0x0 ),  /* 0 */
/* 742 */   NdrFcShort( 0xe ),  /* 14 */
/* 744 */   0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter xlateIds */

/* 746 */   NdrFcShort( 0x2150 ),   /* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 748 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 750 */   0x6,        /* FC_SHORT */
            0x0,        /* 0 */

    /* Return value */

/* 752 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 754 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 756 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure put_TranslateIDs */

/* 758 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 760 */   NdrFcLong( 0x0 ),   /* 0 */
/* 764 */   NdrFcShort( 0x17 ), /* 23 */
#ifndef _ALPHA_
/* 766 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 768 */   NdrFcShort( 0x6 ),  /* 6 */
/* 770 */   NdrFcShort( 0x8 ),  /* 8 */
/* 772 */   0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter xlateIds */

/* 774 */   NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 776 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 778 */   0x6,        /* FC_SHORT */
            0x0,        /* 0 */

    /* Return value */

/* 780 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 782 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 784 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure AddObject */

/* 786 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 788 */   NdrFcLong( 0x0 ),   /* 0 */
/* 792 */   NdrFcShort( 0x14 ), /* 20 */
#ifndef _ALPHA_
/* 794 */   NdrFcShort( 0x14 ), /* x86, MIPS, PPC Stack size/offset = 20 */
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 796 */   NdrFcShort( 0x0 ),  /* 0 */
/* 798 */   NdrFcShort( 0x8 ),  /* 8 */
/* 800 */   0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x4,        /* 4 */

    /* Parameter Keyword */

/* 802 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 804 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 806 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Parameter ObjectName */

/* 808 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 810 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 812 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Parameter pNewObj */

/* 814 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 816 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 818 */   NdrFcShort( 0x434 ),    /* Type Offset=1076 */

    /* Return value */

/* 820 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 822 */   NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 824 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure GetName */

/* 826 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 828 */   NdrFcLong( 0x0 ),   /* 0 */
/* 832 */   NdrFcShort( 0x15 ), /* 21 */
#ifndef _ALPHA_
/* 834 */   NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 836 */   NdrFcShort( 0x0 ),  /* 0 */
/* 838 */   NdrFcShort( 0x8 ),  /* 8 */
/* 840 */   0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter Object */

/* 842 */   NdrFcShort( 0xb ),  /* Flags:  must size, must free, in, */
#ifndef _ALPHA_
/* 844 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 846 */   NdrFcShort( 0x438 ),    /* Type Offset=1080 */

    /* Parameter bstrName */

/* 848 */   NdrFcShort( 0x2113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 850 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 852 */   NdrFcShort( 0x2c ), /* Type Offset=44 */

    /* Return value */

/* 854 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 856 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 858 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure GetObject */

/* 860 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 862 */   NdrFcLong( 0x0 ),   /* 0 */
/* 866 */   NdrFcShort( 0x16 ), /* 22 */
#ifndef _ALPHA_
/* 868 */   NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 870 */   NdrFcShort( 0x0 ),  /* 0 */
/* 872 */   NdrFcShort( 0x8 ),  /* 8 */
/* 874 */   0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter Name */

/* 876 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 878 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 880 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Parameter pObj */

/* 882 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 884 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 886 */   NdrFcShort( 0x434 ),    /* Type Offset=1076 */

    /* Return value */

/* 888 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 890 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 892 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Remove */

/* 894 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 896 */   NdrFcLong( 0x0 ),   /* 0 */
/* 900 */   NdrFcShort( 0x17 ), /* 23 */
#ifndef _ALPHA_
/* 902 */   NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 904 */   NdrFcShort( 0x0 ),  /* 0 */
/* 906 */   NdrFcShort( 0x8 ),  /* 8 */
/* 908 */   0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter Name */

/* 910 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 912 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 914 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Parameter pObj */

/* 916 */   NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 918 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 920 */   NdrFcShort( 0x434 ),    /* Type Offset=1076 */

    /* Return value */

/* 922 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 924 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 926 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Rename */

/* 928 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 930 */   NdrFcLong( 0x0 ),   /* 0 */
/* 934 */   NdrFcShort( 0x18 ), /* 24 */
#ifndef _ALPHA_
/* 936 */   NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 938 */   NdrFcShort( 0x0 ),  /* 0 */
/* 940 */   NdrFcShort( 0x8 ),  /* 8 */
/* 942 */   0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter OldName */

/* 944 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 946 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 948 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Parameter NewName */

/* 950 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 952 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 954 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Return value */

/* 956 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 958 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 960 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Replace */

/* 962 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 964 */   NdrFcLong( 0x0 ),   /* 0 */
/* 968 */   NdrFcShort( 0x19 ), /* 25 */
#ifndef _ALPHA_
/* 970 */   NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 972 */   NdrFcShort( 0x0 ),  /* 0 */
/* 974 */   NdrFcShort( 0x8 ),  /* 8 */
/* 976 */   0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter OldName */

/* 978 */   NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 980 */   NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 982 */   NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Parameter pObj */

/* 984 */   NdrFcShort( 0xb ),  /* Flags:  must size, must free, in, */
#ifndef _ALPHA_
/* 986 */   NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 988 */   NdrFcShort( 0x438 ),    /* Type Offset=1080 */

    /* Return value */

/* 990 */   NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 992 */   NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 994 */   0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Item */

/* 996 */   0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 998 */   NdrFcLong( 0x0 ),   /* 0 */
/* 1002 */  NdrFcShort( 0x1a ), /* 26 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1004 */  NdrFcShort( 0x1c ), /* x86 Stack size/offset = 28 */
#else
            NdrFcShort( 0x20 ), /* MIPS & PPC Stack size/offset = 32 */
#endif
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 1006 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1008 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1010 */  0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter Index */

/* 1012 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1014 */  NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1016 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter pItem */

/* 1018 */  NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1020 */  NdrFcShort( 0x14 ), /* x86 Stack size/offset = 20 */
#else
            NdrFcShort( 0x18 ), /* MIPS & PPC Stack size/offset = 24 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1022 */  NdrFcShort( 0x434 ),    /* Type Offset=1076 */

    /* Return value */

/* 1024 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1026 */  NdrFcShort( 0x18 ), /* x86 Stack size/offset = 24 */
#else
            NdrFcShort( 0x1c ), /* MIPS & PPC Stack size/offset = 28 */
#endif
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 1028 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get__NewEnum */

/* 1030 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1032 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1036 */  NdrFcShort( 0x1b ), /* 27 */
#ifndef _ALPHA_
/* 1038 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1040 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1042 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1044 */  0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter pVal */

/* 1046 */  NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 1048 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1050 */  NdrFcShort( 0x44a ),    /* Type Offset=1098 */

    /* Return value */

/* 1052 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1054 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1056 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Count */

/* 1058 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1060 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1064 */  NdrFcShort( 0x1c ), /* 28 */
#ifndef _ALPHA_
/* 1066 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1068 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1070 */  NdrFcShort( 0x10 ), /* 16 */
/* 1072 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter pVal */

/* 1074 */  NdrFcShort( 0x2150 ),   /* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1076 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1078 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Return value */

/* 1080 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1082 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1084 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure AddXRecord */

/* 1086 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1088 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1092 */  NdrFcShort( 0x1d ), /* 29 */
#ifndef _ALPHA_
/* 1094 */  NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 1096 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1098 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1100 */  0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter Keyword */

/* 1102 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1104 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1106 */  NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Parameter pNewXRecord */

/* 1108 */  NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 1110 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1112 */  NdrFcShort( 0x460 ),    /* Type Offset=1120 */

    /* Return value */

/* 1114 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1116 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1118 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Modified */

/* 1120 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1122 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1126 */  NdrFcShort( 0x7 ),  /* 7 */
#ifndef _ALPHA_
/* 1128 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1130 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1132 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1134 */  0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x2,        /* 2 */

    /* Parameter Object */

/* 1136 */  NdrFcShort( 0xb ),  /* Flags:  must size, must free, in, */
#ifndef _ALPHA_
/* 1138 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1140 */  NdrFcShort( 0x476 ),    /* Type Offset=1142 */

    /* Return value */

/* 1142 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1144 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1146 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Color */

/* 1148 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1150 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1154 */  NdrFcShort( 0x12 ), /* 18 */
#ifndef _ALPHA_
/* 1156 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1158 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1160 */  NdrFcShort( 0x10 ), /* 16 */
/* 1162 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter Color */

/* 1164 */  NdrFcShort( 0x2150 ),   /* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1166 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1168 */  0xe,        /* FC_ENUM32 */
            0x0,        /* 0 */

    /* Return value */

/* 1170 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1172 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1174 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure put_Color */

/* 1176 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1178 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1182 */  NdrFcShort( 0x13 ), /* 19 */
#ifndef _ALPHA_
/* 1184 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1186 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1188 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1190 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter Color */

/* 1192 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1194 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1196 */  0xe,        /* FC_ENUM32 */
            0x0,        /* 0 */

    /* Return value */

/* 1198 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1200 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1202 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Layer */

/* 1204 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1206 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1210 */  NdrFcShort( 0x14 ), /* 20 */
#ifndef _ALPHA_
/* 1212 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1214 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1216 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1218 */  0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter Layer */

/* 1220 */  NdrFcShort( 0x2113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1222 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1224 */  NdrFcShort( 0x2c ), /* Type Offset=44 */

    /* Return value */

/* 1226 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1228 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1230 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure put_Layer */

/* 1232 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1234 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1238 */  NdrFcShort( 0x15 ), /* 21 */
#ifndef _ALPHA_
/* 1240 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1242 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1244 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1246 */  0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x2,        /* 2 */

    /* Parameter Layer */

/* 1248 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1250 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1252 */  NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Return value */

/* 1254 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1256 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1258 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Linetype */

/* 1260 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1262 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1266 */  NdrFcShort( 0x16 ), /* 22 */
#ifndef _ALPHA_
/* 1268 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1270 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1272 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1274 */  0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter Linetype */

/* 1276 */  NdrFcShort( 0x2113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1278 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1280 */  NdrFcShort( 0x2c ), /* Type Offset=44 */

    /* Return value */

/* 1282 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1284 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1286 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure put_Linetype */

/* 1288 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1290 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1294 */  NdrFcShort( 0x17 ), /* 23 */
#ifndef _ALPHA_
/* 1296 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1298 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1300 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1302 */  0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x2,        /* 2 */

    /* Parameter Linetype */

/* 1304 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1306 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1308 */  NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Return value */

/* 1310 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1312 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1314 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_LinetypeScale */

/* 1316 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1318 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1322 */  NdrFcShort( 0x18 ), /* 24 */
#ifndef _ALPHA_
/* 1324 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1326 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1328 */  NdrFcShort( 0x18 ), /* 24 */
/* 1330 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter ltScale */

/* 1332 */  NdrFcShort( 0x2150 ),   /* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1334 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1336 */  0xc,        /* FC_DOUBLE */
            0x0,        /* 0 */

    /* Return value */

/* 1338 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1340 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1342 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure put_LinetypeScale */

/* 1344 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1346 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1350 */  NdrFcShort( 0x19 ), /* 25 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1352 */  NdrFcShort( 0x10 ), /* x86 Stack size/offset = 16 */
#else
            NdrFcShort( 0x14 ), /* MIPS & PPC Stack size/offset = 20 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1354 */  NdrFcShort( 0x10 ), /* 16 */
/* 1356 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1358 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter ltScale */

/* 1360 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1362 */  NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1364 */  0xc,        /* FC_DOUBLE */
            0x0,        /* 0 */

    /* Return value */

/* 1366 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1368 */  NdrFcShort( 0xc ),  /* x86 Stack size/offset = 12 */
#else
            NdrFcShort( 0x10 ), /* MIPS & PPC Stack size/offset = 16 */
#endif
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1370 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Visible */

/* 1372 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1374 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1378 */  NdrFcShort( 0x1a ), /* 26 */
#ifndef _ALPHA_
/* 1380 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1382 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1384 */  NdrFcShort( 0xe ),  /* 14 */
/* 1386 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter bVisible */

/* 1388 */  NdrFcShort( 0x2150 ),   /* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1390 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1392 */  0x6,        /* FC_SHORT */
            0x0,        /* 0 */

    /* Return value */

/* 1394 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1396 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1398 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure put_Visible */

/* 1400 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1402 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1406 */  NdrFcShort( 0x1b ), /* 27 */
#ifndef _ALPHA_
/* 1408 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1410 */  NdrFcShort( 0x6 ),  /* 6 */
/* 1412 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1414 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter bVisible */

/* 1416 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1418 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1420 */  0x6,        /* FC_SHORT */
            0x0,        /* 0 */

    /* Return value */

/* 1422 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1424 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1426 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure ArrayPolar */

/* 1428 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1430 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1434 */  NdrFcShort( 0x1c ), /* 28 */
#ifndef _ALPHA_
/* 1436 */  NdrFcShort( 0x28 ), /* x86, MIPS, PPC Stack size/offset = 40 */
#else
            NdrFcShort( 0x38 ), /* Alpha Stack size/offset = 56 */
#endif
/* 1438 */  NdrFcShort( 0x18 ), /* 24 */
/* 1440 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1442 */  0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x5,        /* 5 */

    /* Parameter NumberOfObjects */

/* 1444 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1446 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1448 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Parameter AngleToFill */

/* 1450 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1452 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1454 */  0xc,        /* FC_DOUBLE */
            0x0,        /* 0 */

    /* Parameter CenterPoint */

/* 1456 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1458 */  NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1460 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter pArrayObjs */

/* 1462 */  NdrFcShort( 0x4113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 1464 */  NdrFcShort( 0x20 ), /* x86, MIPS, PPC Stack size/offset = 32 */
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 1466 */  NdrFcShort( 0x402 ),    /* Type Offset=1026 */

    /* Return value */

/* 1468 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1470 */  NdrFcShort( 0x24 ), /* x86, MIPS, PPC Stack size/offset = 36 */
#else
            NdrFcShort( 0x30 ), /* Alpha Stack size/offset = 48 */
#endif
/* 1472 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure ArrayRectangular */

/* 1474 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1476 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1480 */  NdrFcShort( 0x1d ), /* 29 */
#ifndef _ALPHA_
/* 1482 */  NdrFcShort( 0x30 ), /* x86, MIPS, PPC Stack size/offset = 48 */
#else
            NdrFcShort( 0x48 ), /* Alpha Stack size/offset = 72 */
#endif
/* 1484 */  NdrFcShort( 0x48 ), /* 72 */
/* 1486 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1488 */  0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x8,        /* 8 */

    /* Parameter NumberOfRows */

/* 1490 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1492 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1494 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Parameter NumberOfColumns */

/* 1496 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1498 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1500 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Parameter NumberOfLevels */

/* 1502 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1504 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1506 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Parameter DistBetweenRows */

/* 1508 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1510 */  NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 1512 */  0xc,        /* FC_DOUBLE */
            0x0,        /* 0 */

    /* Parameter DistBetweenCols */

/* 1514 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1516 */  NdrFcShort( 0x18 ), /* x86, MIPS, PPC Stack size/offset = 24 */
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 1518 */  0xc,        /* FC_DOUBLE */
            0x0,        /* 0 */

    /* Parameter DistBetweenLevels */

/* 1520 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1522 */  NdrFcShort( 0x20 ), /* x86, MIPS, PPC Stack size/offset = 32 */
#else
            NdrFcShort( 0x30 ), /* Alpha Stack size/offset = 48 */
#endif
/* 1524 */  0xc,        /* FC_DOUBLE */
            0x0,        /* 0 */

    /* Parameter pArrayObjs */

/* 1526 */  NdrFcShort( 0x4113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 1528 */  NdrFcShort( 0x28 ), /* x86, MIPS, PPC Stack size/offset = 40 */
#else
            NdrFcShort( 0x38 ), /* Alpha Stack size/offset = 56 */
#endif
/* 1530 */  NdrFcShort( 0x402 ),    /* Type Offset=1026 */

    /* Return value */

/* 1532 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1534 */  NdrFcShort( 0x2c ), /* x86, MIPS, PPC Stack size/offset = 44 */
#else
            NdrFcShort( 0x40 ), /* Alpha Stack size/offset = 64 */
#endif
/* 1536 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Highlight */

/* 1538 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1540 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1544 */  NdrFcShort( 0x1e ), /* 30 */
#ifndef _ALPHA_
/* 1546 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1548 */  NdrFcShort( 0x6 ),  /* 6 */
/* 1550 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1552 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter HighlightFlag */

/* 1554 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1556 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1558 */  0x6,        /* FC_SHORT */
            0x0,        /* 0 */

    /* Return value */

/* 1560 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1562 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1564 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Copy */

/* 1566 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1568 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1572 */  NdrFcShort( 0x1f ), /* 31 */
#ifndef _ALPHA_
/* 1574 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1576 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1578 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1580 */  0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter pCopyObj */

/* 1582 */  NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 1584 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1586 */  NdrFcShort( 0x490 ),    /* Type Offset=1168 */

    /* Return value */

/* 1588 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1590 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1592 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Move */

/* 1594 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1596 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1600 */  NdrFcShort( 0x20 ), /* 32 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1602 */  NdrFcShort( 0x28 ), /* x86 Stack size/offset = 40 */
#else
            NdrFcShort( 0x2c ), /* MIPS & PPC Stack size/offset = 44 */
#endif
#else
            NdrFcShort( 0x30 ), /* Alpha Stack size/offset = 48 */
#endif
/* 1604 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1606 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1608 */  0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter FromPoint */

/* 1610 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1612 */  NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1614 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter ToPoint */

/* 1616 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1618 */  NdrFcShort( 0x14 ), /* x86 Stack size/offset = 20 */
#else
            NdrFcShort( 0x18 ), /* MIPS & PPC Stack size/offset = 24 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1620 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Return value */

/* 1622 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1624 */  NdrFcShort( 0x24 ), /* x86 Stack size/offset = 36 */
#else
            NdrFcShort( 0x28 ), /* MIPS & PPC Stack size/offset = 40 */
#endif
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 1626 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Rotate */

/* 1628 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1630 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1634 */  NdrFcShort( 0x21 ), /* 33 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1636 */  NdrFcShort( 0x20 ), /* x86 Stack size/offset = 32 */
#else
            NdrFcShort( 0x24 ), /* MIPS & PPC Stack size/offset = 36 */
#endif
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 1638 */  NdrFcShort( 0x10 ), /* 16 */
/* 1640 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1642 */  0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter BasePoint */

/* 1644 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1646 */  NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1648 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter RotationAngle */

/* 1650 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1652 */  NdrFcShort( 0x14 ), /* x86 Stack size/offset = 20 */
#else
            NdrFcShort( 0x18 ), /* MIPS & PPC Stack size/offset = 24 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1654 */  0xc,        /* FC_DOUBLE */
            0x0,        /* 0 */

    /* Return value */

/* 1656 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1658 */  NdrFcShort( 0x1c ), /* x86 Stack size/offset = 28 */
#else
            NdrFcShort( 0x20 ), /* MIPS & PPC Stack size/offset = 32 */
#endif
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 1660 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Rotate3D */

/* 1662 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1664 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1668 */  NdrFcShort( 0x22 ), /* 34 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1670 */  NdrFcShort( 0x30 ), /* x86 Stack size/offset = 48 */
#else
            NdrFcShort( 0x34 ), /* MIPS & PPC Stack size/offset = 52 */
#endif
#else
            NdrFcShort( 0x38 ), /* Alpha Stack size/offset = 56 */
#endif
/* 1672 */  NdrFcShort( 0x10 ), /* 16 */
/* 1674 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1676 */  0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x4,        /* 4 */

    /* Parameter Point1 */

/* 1678 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1680 */  NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1682 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter Point2 */

/* 1684 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1686 */  NdrFcShort( 0x14 ), /* x86 Stack size/offset = 20 */
#else
            NdrFcShort( 0x18 ), /* MIPS & PPC Stack size/offset = 24 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1688 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter RotationAngle */

/* 1690 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1692 */  NdrFcShort( 0x24 ), /* x86 Stack size/offset = 36 */
#else
            NdrFcShort( 0x28 ), /* MIPS & PPC Stack size/offset = 40 */
#endif
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 1694 */  0xc,        /* FC_DOUBLE */
            0x0,        /* 0 */

    /* Return value */

/* 1696 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1698 */  NdrFcShort( 0x2c ), /* x86 Stack size/offset = 44 */
#else
            NdrFcShort( 0x30 ), /* MIPS & PPC Stack size/offset = 48 */
#endif
#else
            NdrFcShort( 0x30 ), /* Alpha Stack size/offset = 48 */
#endif
/* 1700 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Mirror */

/* 1702 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1704 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1708 */  NdrFcShort( 0x23 ), /* 35 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1710 */  NdrFcShort( 0x2c ), /* x86 Stack size/offset = 44 */
#else
            NdrFcShort( 0x30 ), /* MIPS & PPC Stack size/offset = 48 */
#endif
#else
            NdrFcShort( 0x38 ), /* Alpha Stack size/offset = 56 */
#endif
/* 1712 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1714 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1716 */  0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x4,        /* 4 */

    /* Parameter Point1 */

/* 1718 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1720 */  NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1722 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter Point2 */

/* 1724 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1726 */  NdrFcShort( 0x14 ), /* x86 Stack size/offset = 20 */
#else
            NdrFcShort( 0x18 ), /* MIPS & PPC Stack size/offset = 24 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1728 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter pMirrorObj */

/* 1730 */  NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1732 */  NdrFcShort( 0x24 ), /* x86 Stack size/offset = 36 */
#else
            NdrFcShort( 0x28 ), /* MIPS & PPC Stack size/offset = 40 */
#endif
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 1734 */  NdrFcShort( 0x490 ),    /* Type Offset=1168 */

    /* Return value */

/* 1736 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1738 */  NdrFcShort( 0x28 ), /* x86 Stack size/offset = 40 */
#else
            NdrFcShort( 0x2c ), /* MIPS & PPC Stack size/offset = 44 */
#endif
#else
            NdrFcShort( 0x30 ), /* Alpha Stack size/offset = 48 */
#endif
/* 1740 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Mirror3D */

/* 1742 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1744 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1748 */  NdrFcShort( 0x24 ), /* 36 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1750 */  NdrFcShort( 0x3c ), /* x86 Stack size/offset = 60 */
#else
            NdrFcShort( 0x40 ), /* MIPS & PPC Stack size/offset = 64 */
#endif
#else
            NdrFcShort( 0x48 ), /* Alpha Stack size/offset = 72 */
#endif
/* 1752 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1754 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1756 */  0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x5,        /* 5 */

    /* Parameter point1 */

/* 1758 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1760 */  NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1762 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter point2 */

/* 1764 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1766 */  NdrFcShort( 0x14 ), /* x86 Stack size/offset = 20 */
#else
            NdrFcShort( 0x18 ), /* MIPS & PPC Stack size/offset = 24 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1768 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter point3 */

/* 1770 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1772 */  NdrFcShort( 0x24 ), /* x86 Stack size/offset = 36 */
#else
            NdrFcShort( 0x28 ), /* MIPS & PPC Stack size/offset = 40 */
#endif
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 1774 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter pMirrorObj */

/* 1776 */  NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1778 */  NdrFcShort( 0x34 ), /* x86 Stack size/offset = 52 */
#else
            NdrFcShort( 0x38 ), /* MIPS & PPC Stack size/offset = 56 */
#endif
#else
            NdrFcShort( 0x38 ), /* Alpha Stack size/offset = 56 */
#endif
/* 1780 */  NdrFcShort( 0x490 ),    /* Type Offset=1168 */

    /* Return value */

/* 1782 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1784 */  NdrFcShort( 0x38 ), /* x86 Stack size/offset = 56 */
#else
            NdrFcShort( 0x3c ), /* MIPS & PPC Stack size/offset = 60 */
#endif
#else
            NdrFcShort( 0x40 ), /* Alpha Stack size/offset = 64 */
#endif
/* 1786 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure ScaleEntity */

/* 1788 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1790 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1794 */  NdrFcShort( 0x25 ), /* 37 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1796 */  NdrFcShort( 0x20 ), /* x86 Stack size/offset = 32 */
#else
            NdrFcShort( 0x24 ), /* MIPS & PPC Stack size/offset = 36 */
#endif
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 1798 */  NdrFcShort( 0x10 ), /* 16 */
/* 1800 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1802 */  0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x3,        /* 3 */

    /* Parameter BasePoint */

/* 1804 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1806 */  NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1808 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Parameter ScaleFactor */

/* 1810 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1812 */  NdrFcShort( 0x14 ), /* x86 Stack size/offset = 20 */
#else
            NdrFcShort( 0x18 ), /* MIPS & PPC Stack size/offset = 24 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1814 */  0xc,        /* FC_DOUBLE */
            0x0,        /* 0 */

    /* Return value */

/* 1816 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1818 */  NdrFcShort( 0x1c ), /* x86 Stack size/offset = 28 */
#else
            NdrFcShort( 0x20 ), /* MIPS & PPC Stack size/offset = 32 */
#endif
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 1820 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure TransformBy */

/* 1822 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1824 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1828 */  NdrFcShort( 0x26 ), /* 38 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1830 */  NdrFcShort( 0x18 ), /* x86 Stack size/offset = 24 */
#else
            NdrFcShort( 0x1c ), /* MIPS & PPC Stack size/offset = 28 */
#endif
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 1832 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1834 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1836 */  0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x2,        /* 2 */

    /* Parameter TransformationMatrix */

/* 1838 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1840 */  NdrFcShort( 0x4 ),  /* x86 Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* MIPS & PPC Stack size/offset = 8 */
#endif
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1842 */  NdrFcShort( 0x410 ),    /* Type Offset=1040 */

    /* Return value */

/* 1844 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1846 */  NdrFcShort( 0x14 ), /* x86 Stack size/offset = 20 */
#else
            NdrFcShort( 0x18 ), /* MIPS & PPC Stack size/offset = 24 */
#endif
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1848 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure Update */

/* 1850 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1852 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1856 */  NdrFcShort( 0x27 ), /* 39 */
#ifndef _ALPHA_
/* 1858 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1860 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1862 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1864 */  0x4,        /* Oi2 Flags:  has return, */
            0x1,        /* 1 */

    /* Return value */

/* 1866 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1868 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1870 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure GetBoundingBox */

/* 1872 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1874 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1878 */  NdrFcShort( 0x28 ), /* 40 */
#ifndef _ALPHA_
/* 1880 */  NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 1882 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1884 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1886 */  0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x3,        /* 3 */

    /* Parameter MinPoint */

/* 1888 */  NdrFcShort( 0x4113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 1890 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1892 */  NdrFcShort( 0x402 ),    /* Type Offset=1026 */

    /* Parameter MaxPoint */

/* 1894 */  NdrFcShort( 0x4113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 1896 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1898 */  NdrFcShort( 0x402 ),    /* Type Offset=1026 */

    /* Return value */

/* 1900 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1902 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1904 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure IntersectWith */

/* 1906 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1908 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1912 */  NdrFcShort( 0x29 ), /* 41 */
#ifndef _ALPHA_
/* 1914 */  NdrFcShort( 0x14 ), /* x86, MIPS, PPC Stack size/offset = 20 */
#else
            NdrFcShort( 0x28 ), /* Alpha Stack size/offset = 40 */
#endif
/* 1916 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1918 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1920 */  0x7,        /* Oi2 Flags:  srv must size, clt must size, has return, */
            0x4,        /* 4 */

    /* Parameter IntersectObject */

/* 1922 */  NdrFcShort( 0xb ),  /* Flags:  must size, must free, in, */
#ifndef _ALPHA_
/* 1924 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1926 */  NdrFcShort( 0x476 ),    /* Type Offset=1142 */

    /* Parameter option */

/* 1928 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1930 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1932 */  0xe,        /* FC_ENUM32 */
            0x0,        /* 0 */

    /* Parameter intPoints */

/* 1934 */  NdrFcShort( 0x4113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 1936 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1938 */  NdrFcShort( 0x402 ),    /* Type Offset=1026 */

    /* Return value */

/* 1940 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1942 */  NdrFcShort( 0x10 ), /* x86, MIPS, PPC Stack size/offset = 16 */
#else
            NdrFcShort( 0x20 ), /* Alpha Stack size/offset = 32 */
#endif
/* 1944 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_PlotStyleName */

/* 1946 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1948 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1952 */  NdrFcShort( 0x2a ), /* 42 */
#ifndef _ALPHA_
/* 1954 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1956 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1958 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1960 */  0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter plotStyle */

/* 1962 */  NdrFcShort( 0x2113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1964 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1966 */  NdrFcShort( 0x2c ), /* Type Offset=44 */

    /* Return value */

/* 1968 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1970 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 1972 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure put_PlotStyleName */

/* 1974 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 1976 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1980 */  NdrFcShort( 0x2b ), /* 43 */
#ifndef _ALPHA_
/* 1982 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 1984 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1986 */  NdrFcShort( 0x8 ),  /* 8 */
/* 1988 */  0x6,        /* Oi2 Flags:  clt must size, has return, */
            0x2,        /* 2 */

    /* Parameter plotStyle */

/* 1990 */  NdrFcShort( 0x8b ), /* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1992 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 1994 */  NdrFcShort( 0x1a ), /* Type Offset=26 */

    /* Return value */

/* 1996 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1998 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 2000 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Lineweight */

/* 2002 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 2004 */  NdrFcLong( 0x0 ),   /* 0 */
/* 2008 */  NdrFcShort( 0x2c ), /* 44 */
#ifndef _ALPHA_
/* 2010 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 2012 */  NdrFcShort( 0x0 ),  /* 0 */
/* 2014 */  NdrFcShort( 0x10 ), /* 16 */
/* 2016 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter lineweight */

/* 2018 */  NdrFcShort( 0x2150 ),   /* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 2020 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 2022 */  0xe,        /* FC_ENUM32 */
            0x0,        /* 0 */

    /* Return value */

/* 2024 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2026 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 2028 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure put_Lineweight */

/* 2030 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 2032 */  NdrFcLong( 0x0 ),   /* 0 */
/* 2036 */  NdrFcShort( 0x2d ), /* 45 */
#ifndef _ALPHA_
/* 2038 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 2040 */  NdrFcShort( 0x8 ),  /* 8 */
/* 2042 */  NdrFcShort( 0x8 ),  /* 8 */
/* 2044 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter lineweight */

/* 2046 */  NdrFcShort( 0x48 ), /* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2048 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 2050 */  0xe,        /* FC_ENUM32 */
            0x0,        /* 0 */

    /* Return value */

/* 2052 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2054 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 2056 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_Hyperlinks */

/* 2058 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 2060 */  NdrFcLong( 0x0 ),   /* 0 */
/* 2064 */  NdrFcShort( 0x2e ), /* 46 */
#ifndef _ALPHA_
/* 2066 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 2068 */  NdrFcShort( 0x0 ),  /* 0 */
/* 2070 */  NdrFcShort( 0x8 ),  /* 8 */
/* 2072 */  0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter HyperLinks */

/* 2074 */  NdrFcShort( 0x13 ), /* Flags:  must size, must free, out, */
#ifndef _ALPHA_
/* 2076 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 2078 */  NdrFcShort( 0x494 ),    /* Type Offset=1172 */

    /* Return value */

/* 2080 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2082 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 2084 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_EntityName */

/* 2086 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 2088 */  NdrFcLong( 0x0 ),   /* 0 */
/* 2092 */  NdrFcShort( 0x2f ), /* 47 */
#ifndef _ALPHA_
/* 2094 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 2096 */  NdrFcShort( 0x0 ),  /* 0 */
/* 2098 */  NdrFcShort( 0x8 ),  /* 8 */
/* 2100 */  0x5,        /* Oi2 Flags:  srv must size, has return, */
            0x2,        /* 2 */

    /* Parameter EntityName */

/* 2102 */  NdrFcShort( 0x2113 ),   /* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 2104 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 2106 */  NdrFcShort( 0x2c ), /* Type Offset=44 */

    /* Return value */

/* 2108 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2110 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 2112 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Procedure get_EntityType */

/* 2114 */  0x33,       /* FC_AUTO_HANDLE */
            0x6c,       /* Old Flags:  object, Oi2 */
/* 2116 */  NdrFcLong( 0x0 ),   /* 0 */
/* 2120 */  NdrFcShort( 0x30 ), /* 48 */
#ifndef _ALPHA_
/* 2122 */  NdrFcShort( 0xc ),  /* x86, MIPS, PPC Stack size/offset = 12 */
#else
            NdrFcShort( 0x18 ), /* Alpha Stack size/offset = 24 */
#endif
/* 2124 */  NdrFcShort( 0x0 ),  /* 0 */
/* 2126 */  NdrFcShort( 0x10 ), /* 16 */
/* 2128 */  0x4,        /* Oi2 Flags:  has return, */
            0x2,        /* 2 */

    /* Parameter entType */

/* 2130 */  NdrFcShort( 0x2150 ),   /* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 2132 */  NdrFcShort( 0x4 ),  /* x86, MIPS, PPC Stack size/offset = 4 */
#else
            NdrFcShort( 0x8 ),  /* Alpha Stack size/offset = 8 */
#endif
/* 2134 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

    /* Return value */

/* 2136 */  NdrFcShort( 0x70 ), /* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2138 */  NdrFcShort( 0x8 ),  /* x86, MIPS, PPC Stack size/offset = 8 */
#else
            NdrFcShort( 0x10 ), /* Alpha Stack size/offset = 16 */
#endif
/* 2140 */  0x8,        /* FC_LONG */
            0x0,        /* 0 */

            0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
            NdrFcShort( 0x0 ),  /* 0 */
/*  2 */    
            0x12, 0x0,  /* FC_UP */
/*  4 */    NdrFcShort( 0xc ),  /* Offset= 12 (16) */
/*  6 */    
            0x1b,       /* FC_CARRAY */
            0x1,        /* 1 */
/*  8 */    NdrFcShort( 0x2 ),  /* 2 */
/* 10 */    0x9,        /* Corr desc: FC_ULONG */
            0x0,        /*  */
/* 12 */    NdrFcShort( 0xfffc ),   /* -4 */
/* 14 */    0x6,        /* FC_SHORT */
            0x5b,       /* FC_END */
/* 16 */    
            0x17,       /* FC_CSTRUCT */
            0x3,        /* 3 */
/* 18 */    NdrFcShort( 0x8 ),  /* 8 */
/* 20 */    NdrFcShort( 0xfffffff2 ),   /* Offset= -14 (6) */
/* 22 */    0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 24 */    0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 26 */    0xb4,       /* FC_USER_MARSHAL */
            0x83,       /* 131 */
/* 28 */    NdrFcShort( 0x0 ),  /* 0 */
/* 30 */    NdrFcShort( 0x4 ),  /* 4 */
/* 32 */    NdrFcShort( 0x0 ),  /* 0 */
/* 34 */    NdrFcShort( 0xffffffe0 ),   /* Offset= -32 (2) */
/* 36 */    
            0x11, 0x4,  /* FC_RP [alloced_on_stack] */
/* 38 */    NdrFcShort( 0x6 ),  /* Offset= 6 (44) */
/* 40 */    
            0x13, 0x0,  /* FC_OP */
/* 42 */    NdrFcShort( 0xffffffe6 ),   /* Offset= -26 (16) */
/* 44 */    0xb4,       /* FC_USER_MARSHAL */
            0x83,       /* 131 */
/* 46 */    NdrFcShort( 0x0 ),  /* 0 */
/* 48 */    NdrFcShort( 0x4 ),  /* 4 */
/* 50 */    NdrFcShort( 0x0 ),  /* 0 */
/* 52 */    NdrFcShort( 0xfffffff4 ),   /* Offset= -12 (40) */
/* 54 */    
            0x11, 0x10, /* FC_RP */
/* 56 */    NdrFcShort( 0x2 ),  /* Offset= 2 (58) */
/* 58 */    
            0x2f,       /* FC_IP */
            0x5a,       /* FC_CONSTANT_IID */
/* 60 */    NdrFcLong( 0x20400 ),   /* 132096 */
/* 64 */    NdrFcShort( 0x0 ),  /* 0 */
/* 66 */    NdrFcShort( 0x0 ),  /* 0 */
/* 68 */    0xc0,       /* 192 */
            0x0,        /* 0 */
/* 70 */    0x0,        /* 0 */
            0x0,        /* 0 */
/* 72 */    0x0,        /* 0 */
            0x0,        /* 0 */
/* 74 */    0x0,        /* 0 */
            0x46,       /* 70 */
/* 76 */    
            0x11, 0x10, /* FC_RP */
/* 78 */    NdrFcShort( 0x2 ),  /* Offset= 2 (80) */
/* 80 */    
            0x2f,       /* FC_IP */
            0x5a,       /* FC_CONSTANT_IID */
/* 82 */    NdrFcLong( 0xb2547d94 ),    /* -1303085676 */
/* 86 */    NdrFcShort( 0xca93 ),   /* -13677 */
/* 88 */    NdrFcShort( 0x11d1 ),   /* 4561 */
/* 90 */    0xb6,       /* 182 */
            0xf,        /* 15 */
/* 92 */    0x0,        /* 0 */
            0x60,       /* 96 */
/* 94 */    0xb0,       /* 176 */
            0x87,       /* 135 */
/* 96 */    0xe2,       /* 226 */
            0x35,       /* 53 */
/* 98 */    
            0x11, 0xc,  /* FC_RP [alloced_on_stack] [simple_pointer] */
/* 100 */   0x8,        /* FC_LONG */
            0x5c,       /* FC_PAD */
/* 102 */   
            0x11, 0x10, /* FC_RP */
/* 104 */   NdrFcShort( 0x2 ),  /* Offset= 2 (106) */
/* 106 */   
            0x2f,       /* FC_IP */
            0x5a,       /* FC_CONSTANT_IID */
/* 108 */   NdrFcLong( 0x0 ),   /* 0 */
/* 112 */   NdrFcShort( 0x0 ),  /* 0 */
/* 114 */   NdrFcShort( 0x0 ),  /* 0 */
/* 116 */   0xc0,       /* 192 */
            0x0,        /* 0 */
/* 118 */   0x0,        /* 0 */
            0x0,        /* 0 */
/* 120 */   0x0,        /* 0 */
            0x0,        /* 0 */
/* 122 */   0x0,        /* 0 */
            0x46,       /* 70 */
/* 124 */   
            0x11, 0x4,  /* FC_RP [alloced_on_stack] */
/* 126 */   NdrFcShort( 0x384 ),    /* Offset= 900 (1026) */
/* 128 */   
            0x13, 0x0,  /* FC_OP */
/* 130 */   NdrFcShort( 0x36c ),    /* Offset= 876 (1006) */
/* 132 */   
            0x2b,       /* FC_NON_ENCAPSULATED_UNION */
            0x9,        /* FC_ULONG */
/* 134 */   0x7,        /* Corr desc: FC_USHORT */
            0x0,        /*  */
/* 136 */   NdrFcShort( 0xfff8 ),   /* -8 */
/* 138 */   NdrFcShort( 0x2 ),  /* Offset= 2 (140) */
/* 140 */   NdrFcShort( 0x10 ), /* 16 */
/* 142 */   NdrFcShort( 0x2b ), /* 43 */
/* 144 */   NdrFcLong( 0x3 ),   /* 3 */
/* 148 */   NdrFcShort( 0x8008 ),   /* Simple arm type: FC_LONG */
/* 150 */   NdrFcLong( 0x11 ),  /* 17 */
/* 154 */   NdrFcShort( 0x8002 ),   /* Simple arm type: FC_CHAR */
/* 156 */   NdrFcLong( 0x2 ),   /* 2 */
/* 160 */   NdrFcShort( 0x8006 ),   /* Simple arm type: FC_SHORT */
/* 162 */   NdrFcLong( 0x4 ),   /* 4 */
/* 166 */   NdrFcShort( 0x800a ),   /* Simple arm type: FC_FLOAT */
/* 168 */   NdrFcLong( 0x5 ),   /* 5 */
/* 172 */   NdrFcShort( 0x800c ),   /* Simple arm type: FC_DOUBLE */
/* 174 */   NdrFcLong( 0xb ),   /* 11 */
/* 178 */   NdrFcShort( 0x8006 ),   /* Simple arm type: FC_SHORT */
/* 180 */   NdrFcLong( 0xa ),   /* 10 */
/* 184 */   NdrFcShort( 0x8008 ),   /* Simple arm type: FC_LONG */
/* 186 */   NdrFcLong( 0x6 ),   /* 6 */
/* 190 */   NdrFcShort( 0xd6 ), /* Offset= 214 (404) */
/* 192 */   NdrFcLong( 0x7 ),   /* 7 */
/* 196 */   NdrFcShort( 0x800c ),   /* Simple arm type: FC_DOUBLE */
/* 198 */   NdrFcLong( 0x8 ),   /* 8 */
/* 202 */   NdrFcShort( 0xffffff5e ),   /* Offset= -162 (40) */
/* 204 */   NdrFcLong( 0xd ),   /* 13 */
/* 208 */   NdrFcShort( 0xffffff9a ),   /* Offset= -102 (106) */
/* 210 */   NdrFcLong( 0x9 ),   /* 9 */
/* 214 */   NdrFcShort( 0xffffff64 ),   /* Offset= -156 (58) */
/* 216 */   NdrFcLong( 0x2000 ),    /* 8192 */
/* 220 */   NdrFcShort( 0xbe ), /* Offset= 190 (410) */
/* 222 */   NdrFcLong( 0x24 ),  /* 36 */
/* 226 */   NdrFcShort( 0x2c8 ),    /* Offset= 712 (938) */
/* 228 */   NdrFcLong( 0x4024 ),    /* 16420 */
/* 232 */   NdrFcShort( 0x2c2 ),    /* Offset= 706 (938) */
/* 234 */   NdrFcLong( 0x4011 ),    /* 16401 */
/* 238 */   NdrFcShort( 0x2c0 ),    /* Offset= 704 (942) */
/* 240 */   NdrFcLong( 0x4002 ),    /* 16386 */
/* 244 */   NdrFcShort( 0x2be ),    /* Offset= 702 (946) */
/* 246 */   NdrFcLong( 0x4003 ),    /* 16387 */
/* 250 */   NdrFcShort( 0x2bc ),    /* Offset= 700 (950) */
/* 252 */   NdrFcLong( 0x4004 ),    /* 16388 */
/* 256 */   NdrFcShort( 0x2ba ),    /* Offset= 698 (954) */
/* 258 */   NdrFcLong( 0x4005 ),    /* 16389 */
/* 262 */   NdrFcShort( 0x2b8 ),    /* Offset= 696 (958) */
/* 264 */   NdrFcLong( 0x400b ),    /* 16395 */
/* 268 */   NdrFcShort( 0x2a6 ),    /* Offset= 678 (946) */
/* 270 */   NdrFcLong( 0x400a ),    /* 16394 */
/* 274 */   NdrFcShort( 0x2a4 ),    /* Offset= 676 (950) */
/* 276 */   NdrFcLong( 0x4006 ),    /* 16390 */
/* 280 */   NdrFcShort( 0x2aa ),    /* Offset= 682 (962) */
/* 282 */   NdrFcLong( 0x4007 ),    /* 16391 */
/* 286 */   NdrFcShort( 0x2a0 ),    /* Offset= 672 (958) */
/* 288 */   NdrFcLong( 0x4008 ),    /* 16392 */
/* 292 */   NdrFcShort( 0x2a2 ),    /* Offset= 674 (966) */
/* 294 */   NdrFcLong( 0x400d ),    /* 16397 */
/* 298 */   NdrFcShort( 0x2a0 ),    /* Offset= 672 (970) */
/* 300 */   NdrFcLong( 0x4009 ),    /* 16393 */
/* 304 */   NdrFcShort( 0x29e ),    /* Offset= 670 (974) */
/* 306 */   NdrFcLong( 0x6000 ),    /* 24576 */
/* 310 */   NdrFcShort( 0x29c ),    /* Offset= 668 (978) */
/* 312 */   NdrFcLong( 0x400c ),    /* 16396 */
/* 316 */   NdrFcShort( 0x29a ),    /* Offset= 666 (982) */
/* 318 */   NdrFcLong( 0x10 ),  /* 16 */
/* 322 */   NdrFcShort( 0x8002 ),   /* Simple arm type: FC_CHAR */
/* 324 */   NdrFcLong( 0x12 ),  /* 18 */
/* 328 */   NdrFcShort( 0x8006 ),   /* Simple arm type: FC_SHORT */
/* 330 */   NdrFcLong( 0x13 ),  /* 19 */
/* 334 */   NdrFcShort( 0x8008 ),   /* Simple arm type: FC_LONG */
/* 336 */   NdrFcLong( 0x16 ),  /* 22 */
/* 340 */   NdrFcShort( 0x8008 ),   /* Simple arm type: FC_LONG */
/* 342 */   NdrFcLong( 0x17 ),  /* 23 */
/* 346 */   NdrFcShort( 0x8008 ),   /* Simple arm type: FC_LONG */
/* 348 */   NdrFcLong( 0xe ),   /* 14 */
/* 352 */   NdrFcShort( 0x27e ),    /* Offset= 638 (990) */
/* 354 */   NdrFcLong( 0x400e ),    /* 16398 */
/* 358 */   NdrFcShort( 0x284 ),    /* Offset= 644 (1002) */
/* 360 */   NdrFcLong( 0x4010 ),    /* 16400 */
/* 364 */   NdrFcShort( 0x242 ),    /* Offset= 578 (942) */
/* 366 */   NdrFcLong( 0x4012 ),    /* 16402 */
/* 370 */   NdrFcShort( 0x240 ),    /* Offset= 576 (946) */
/* 372 */   NdrFcLong( 0x4013 ),    /* 16403 */
/* 376 */   NdrFcShort( 0x23e ),    /* Offset= 574 (950) */
/* 378 */   NdrFcLong( 0x4016 ),    /* 16406 */
/* 382 */   NdrFcShort( 0x238 ),    /* Offset= 568 (950) */
/* 384 */   NdrFcLong( 0x4017 ),    /* 16407 */
/* 388 */   NdrFcShort( 0x232 ),    /* Offset= 562 (950) */
/* 390 */   NdrFcLong( 0x0 ),   /* 0 */
/* 394 */   NdrFcShort( 0x0 ),  /* Offset= 0 (394) */
/* 396 */   NdrFcLong( 0x1 ),   /* 1 */
/* 400 */   NdrFcShort( 0x0 ),  /* Offset= 0 (400) */
/* 402 */   NdrFcShort( 0xffffffff ),   /* Offset= -1 (401) */
/* 404 */   
            0x15,       /* FC_STRUCT */
            0x7,        /* 7 */
/* 406 */   NdrFcShort( 0x8 ),  /* 8 */
/* 408 */   0xb,        /* FC_HYPER */
            0x5b,       /* FC_END */
/* 410 */   
            0x13, 0x0,  /* FC_OP */
/* 412 */   NdrFcShort( 0x1fc ),    /* Offset= 508 (920) */
/* 414 */   
            0x2a,       /* FC_ENCAPSULATED_UNION */
            0x49,       /* 73 */
/* 416 */   NdrFcShort( 0x18 ), /* 24 */
/* 418 */   NdrFcShort( 0xa ),  /* 10 */
/* 420 */   NdrFcLong( 0x8 ),   /* 8 */
/* 424 */   NdrFcShort( 0x58 ), /* Offset= 88 (512) */
/* 426 */   NdrFcLong( 0xd ),   /* 13 */
/* 430 */   NdrFcShort( 0x78 ), /* Offset= 120 (550) */
/* 432 */   NdrFcLong( 0x9 ),   /* 9 */
/* 436 */   NdrFcShort( 0x94 ), /* Offset= 148 (584) */
/* 438 */   NdrFcLong( 0xc ),   /* 12 */
/* 442 */   NdrFcShort( 0xbc ), /* Offset= 188 (630) */
/* 444 */   NdrFcLong( 0x24 ),  /* 36 */
/* 448 */   NdrFcShort( 0x114 ),    /* Offset= 276 (724) */
/* 450 */   NdrFcLong( 0x800d ),    /* 32781 */
/* 454 */   NdrFcShort( 0x130 ),    /* Offset= 304 (758) */
/* 456 */   NdrFcLong( 0x10 ),  /* 16 */
/* 460 */   NdrFcShort( 0x148 ),    /* Offset= 328 (788) */
/* 462 */   NdrFcLong( 0x2 ),   /* 2 */
/* 466 */   NdrFcShort( 0x160 ),    /* Offset= 352 (818) */
/* 468 */   NdrFcLong( 0x3 ),   /* 3 */
/* 472 */   NdrFcShort( 0x178 ),    /* Offset= 376 (848) */
/* 474 */   NdrFcLong( 0x14 ),  /* 20 */
/* 478 */   NdrFcShort( 0x190 ),    /* Offset= 400 (878) */
/* 480 */   NdrFcShort( 0xffffffff ),   /* Offset= -1 (479) */
/* 482 */   
            0x1b,       /* FC_CARRAY */
            0x3,        /* 3 */
/* 484 */   NdrFcShort( 0x4 ),  /* 4 */
/* 486 */   0x19,       /* Corr desc:  field pointer, FC_ULONG */
            0x0,        /*  */
/* 488 */   NdrFcShort( 0x0 ),  /* 0 */
/* 490 */   
            0x4b,       /* FC_PP */
            0x5c,       /* FC_PAD */
/* 492 */   
            0x48,       /* FC_VARIABLE_REPEAT */
            0x49,       /* FC_FIXED_OFFSET */
/* 494 */   NdrFcShort( 0x4 ),  /* 4 */
/* 496 */   NdrFcShort( 0x0 ),  /* 0 */
/* 498 */   NdrFcShort( 0x1 ),  /* 1 */
/* 500 */   NdrFcShort( 0x0 ),  /* 0 */
/* 502 */   NdrFcShort( 0x0 ),  /* 0 */
/* 504 */   0x13, 0x0,  /* FC_OP */
/* 506 */   NdrFcShort( 0xfffffe16 ),   /* Offset= -490 (16) */
/* 508 */   
            0x5b,       /* FC_END */

            0x8,        /* FC_LONG */
/* 510 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 512 */   
            0x16,       /* FC_PSTRUCT */
            0x3,        /* 3 */
/* 514 */   NdrFcShort( 0x8 ),  /* 8 */
/* 516 */   
            0x4b,       /* FC_PP */
            0x5c,       /* FC_PAD */
/* 518 */   
            0x46,       /* FC_NO_REPEAT */
            0x5c,       /* FC_PAD */
/* 520 */   NdrFcShort( 0x4 ),  /* 4 */
/* 522 */   NdrFcShort( 0x4 ),  /* 4 */
/* 524 */   0x11, 0x0,  /* FC_RP */
/* 526 */   NdrFcShort( 0xffffffd4 ),   /* Offset= -44 (482) */
/* 528 */   
            0x5b,       /* FC_END */

            0x8,        /* FC_LONG */
/* 530 */   0x8,        /* FC_LONG */
            0x5b,       /* FC_END */
/* 532 */   
            0x21,       /* FC_BOGUS_ARRAY */
            0x3,        /* 3 */
/* 534 */   NdrFcShort( 0x0 ),  /* 0 */
/* 536 */   0x19,       /* Corr desc:  field pointer, FC_ULONG */
            0x0,        /*  */
/* 538 */   NdrFcShort( 0x0 ),  /* 0 */
/* 540 */   NdrFcLong( 0xffffffff ),    /* -1 */
/* 544 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 546 */   NdrFcShort( 0xfffffe48 ),   /* Offset= -440 (106) */
/* 548 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 550 */   
            0x1a,       /* FC_BOGUS_STRUCT */
            0x3,        /* 3 */
/* 552 */   NdrFcShort( 0x8 ),  /* 8 */
/* 554 */   NdrFcShort( 0x0 ),  /* 0 */
/* 556 */   NdrFcShort( 0x6 ),  /* Offset= 6 (562) */
/* 558 */   0x8,        /* FC_LONG */
            0x36,       /* FC_POINTER */
/* 560 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 562 */   
            0x11, 0x0,  /* FC_RP */
/* 564 */   NdrFcShort( 0xffffffe0 ),   /* Offset= -32 (532) */
/* 566 */   
            0x21,       /* FC_BOGUS_ARRAY */
            0x3,        /* 3 */
/* 568 */   NdrFcShort( 0x0 ),  /* 0 */
/* 570 */   0x19,       /* Corr desc:  field pointer, FC_ULONG */
            0x0,        /*  */
/* 572 */   NdrFcShort( 0x0 ),  /* 0 */
/* 574 */   NdrFcLong( 0xffffffff ),    /* -1 */
/* 578 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 580 */   NdrFcShort( 0xfffffdf6 ),   /* Offset= -522 (58) */
/* 582 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 584 */   
            0x1a,       /* FC_BOGUS_STRUCT */
            0x3,        /* 3 */
/* 586 */   NdrFcShort( 0x8 ),  /* 8 */
/* 588 */   NdrFcShort( 0x0 ),  /* 0 */
/* 590 */   NdrFcShort( 0x6 ),  /* Offset= 6 (596) */
/* 592 */   0x8,        /* FC_LONG */
            0x36,       /* FC_POINTER */
/* 594 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 596 */   
            0x11, 0x0,  /* FC_RP */
/* 598 */   NdrFcShort( 0xffffffe0 ),   /* Offset= -32 (566) */
/* 600 */   
            0x1b,       /* FC_CARRAY */
            0x3,        /* 3 */
/* 602 */   NdrFcShort( 0x4 ),  /* 4 */
/* 604 */   0x19,       /* Corr desc:  field pointer, FC_ULONG */
            0x0,        /*  */
/* 606 */   NdrFcShort( 0x0 ),  /* 0 */
/* 608 */   
            0x4b,       /* FC_PP */
            0x5c,       /* FC_PAD */
/* 610 */   
            0x48,       /* FC_VARIABLE_REPEAT */
            0x49,       /* FC_FIXED_OFFSET */
/* 612 */   NdrFcShort( 0x4 ),  /* 4 */
/* 614 */   NdrFcShort( 0x0 ),  /* 0 */
/* 616 */   NdrFcShort( 0x1 ),  /* 1 */
/* 618 */   NdrFcShort( 0x0 ),  /* 0 */
/* 620 */   NdrFcShort( 0x0 ),  /* 0 */
/* 622 */   0x13, 0x0,  /* FC_OP */
/* 624 */   NdrFcShort( 0x17e ),    /* Offset= 382 (1006) */
/* 626 */   
            0x5b,       /* FC_END */

            0x8,        /* FC_LONG */
/* 628 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 630 */   
            0x1a,       /* FC_BOGUS_STRUCT */
            0x3,        /* 3 */
/* 632 */   NdrFcShort( 0x8 ),  /* 8 */
/* 634 */   NdrFcShort( 0x0 ),  /* 0 */
/* 636 */   NdrFcShort( 0x6 ),  /* Offset= 6 (642) */
/* 638 */   0x8,        /* FC_LONG */
            0x36,       /* FC_POINTER */
/* 640 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 642 */   
            0x11, 0x0,  /* FC_RP */
/* 644 */   NdrFcShort( 0xffffffd4 ),   /* Offset= -44 (600) */
/* 646 */   
            0x2f,       /* FC_IP */
            0x5a,       /* FC_CONSTANT_IID */
/* 648 */   NdrFcLong( 0x2f ),  /* 47 */
/* 652 */   NdrFcShort( 0x0 ),  /* 0 */
/* 654 */   NdrFcShort( 0x0 ),  /* 0 */
/* 656 */   0xc0,       /* 192 */
            0x0,        /* 0 */
/* 658 */   0x0,        /* 0 */
            0x0,        /* 0 */
/* 660 */   0x0,        /* 0 */
            0x0,        /* 0 */
/* 662 */   0x0,        /* 0 */
            0x46,       /* 70 */
/* 664 */   
            0x1b,       /* FC_CARRAY */
            0x0,        /* 0 */
/* 666 */   NdrFcShort( 0x1 ),  /* 1 */
/* 668 */   0x19,       /* Corr desc:  field pointer, FC_ULONG */
            0x0,        /*  */
/* 670 */   NdrFcShort( 0x4 ),  /* 4 */
/* 672 */   0x1,        /* FC_BYTE */
            0x5b,       /* FC_END */
/* 674 */   
            0x1a,       /* FC_BOGUS_STRUCT */
            0x3,        /* 3 */
/* 676 */   NdrFcShort( 0x10 ), /* 16 */
/* 678 */   NdrFcShort( 0x0 ),  /* 0 */
/* 680 */   NdrFcShort( 0xa ),  /* Offset= 10 (690) */
/* 682 */   0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 684 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 686 */   NdrFcShort( 0xffffffd8 ),   /* Offset= -40 (646) */
/* 688 */   0x36,       /* FC_POINTER */
            0x5b,       /* FC_END */
/* 690 */   
            0x13, 0x0,  /* FC_OP */
/* 692 */   NdrFcShort( 0xffffffe4 ),   /* Offset= -28 (664) */
/* 694 */   
            0x1b,       /* FC_CARRAY */
            0x3,        /* 3 */
/* 696 */   NdrFcShort( 0x4 ),  /* 4 */
/* 698 */   0x19,       /* Corr desc:  field pointer, FC_ULONG */
            0x0,        /*  */
/* 700 */   NdrFcShort( 0x0 ),  /* 0 */
/* 702 */   
            0x4b,       /* FC_PP */
            0x5c,       /* FC_PAD */
/* 704 */   
            0x48,       /* FC_VARIABLE_REPEAT */
            0x49,       /* FC_FIXED_OFFSET */
/* 706 */   NdrFcShort( 0x4 ),  /* 4 */
/* 708 */   NdrFcShort( 0x0 ),  /* 0 */
/* 710 */   NdrFcShort( 0x1 ),  /* 1 */
/* 712 */   NdrFcShort( 0x0 ),  /* 0 */
/* 714 */   NdrFcShort( 0x0 ),  /* 0 */
/* 716 */   0x13, 0x0,  /* FC_OP */
/* 718 */   NdrFcShort( 0xffffffd4 ),   /* Offset= -44 (674) */
/* 720 */   
            0x5b,       /* FC_END */

            0x8,        /* FC_LONG */
/* 722 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 724 */   
            0x1a,       /* FC_BOGUS_STRUCT */
            0x3,        /* 3 */
/* 726 */   NdrFcShort( 0x8 ),  /* 8 */
/* 728 */   NdrFcShort( 0x0 ),  /* 0 */
/* 730 */   NdrFcShort( 0x6 ),  /* Offset= 6 (736) */
/* 732 */   0x8,        /* FC_LONG */
            0x36,       /* FC_POINTER */
/* 734 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 736 */   
            0x11, 0x0,  /* FC_RP */
/* 738 */   NdrFcShort( 0xffffffd4 ),   /* Offset= -44 (694) */
/* 740 */   
            0x1d,       /* FC_SMFARRAY */
            0x0,        /* 0 */
/* 742 */   NdrFcShort( 0x8 ),  /* 8 */
/* 744 */   0x2,        /* FC_CHAR */
            0x5b,       /* FC_END */
/* 746 */   
            0x15,       /* FC_STRUCT */
            0x3,        /* 3 */
/* 748 */   NdrFcShort( 0x10 ), /* 16 */
/* 750 */   0x8,        /* FC_LONG */
            0x6,        /* FC_SHORT */
/* 752 */   0x6,        /* FC_SHORT */
            0x4c,       /* FC_EMBEDDED_COMPLEX */
/* 754 */   0x0,        /* 0 */
            NdrFcShort( 0xfffffff1 ),   /* Offset= -15 (740) */
            0x5b,       /* FC_END */
/* 758 */   
            0x1a,       /* FC_BOGUS_STRUCT */
            0x3,        /* 3 */
/* 760 */   NdrFcShort( 0x18 ), /* 24 */
/* 762 */   NdrFcShort( 0x0 ),  /* 0 */
/* 764 */   NdrFcShort( 0xa ),  /* Offset= 10 (774) */
/* 766 */   0x8,        /* FC_LONG */
            0x36,       /* FC_POINTER */
/* 768 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 770 */   NdrFcShort( 0xffffffe8 ),   /* Offset= -24 (746) */
/* 772 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 774 */   
            0x11, 0x0,  /* FC_RP */
/* 776 */   NdrFcShort( 0xffffff0c ),   /* Offset= -244 (532) */
/* 778 */   
            0x1b,       /* FC_CARRAY */
            0x0,        /* 0 */
/* 780 */   NdrFcShort( 0x1 ),  /* 1 */
/* 782 */   0x19,       /* Corr desc:  field pointer, FC_ULONG */
            0x0,        /*  */
/* 784 */   NdrFcShort( 0x0 ),  /* 0 */
/* 786 */   0x1,        /* FC_BYTE */
            0x5b,       /* FC_END */
/* 788 */   
            0x16,       /* FC_PSTRUCT */
            0x3,        /* 3 */
/* 790 */   NdrFcShort( 0x8 ),  /* 8 */
/* 792 */   
            0x4b,       /* FC_PP */
            0x5c,       /* FC_PAD */
/* 794 */   
            0x46,       /* FC_NO_REPEAT */
            0x5c,       /* FC_PAD */
/* 796 */   NdrFcShort( 0x4 ),  /* 4 */
/* 798 */   NdrFcShort( 0x4 ),  /* 4 */
/* 800 */   0x13, 0x0,  /* FC_OP */
/* 802 */   NdrFcShort( 0xffffffe8 ),   /* Offset= -24 (778) */
/* 804 */   
            0x5b,       /* FC_END */

            0x8,        /* FC_LONG */
/* 806 */   0x8,        /* FC_LONG */
            0x5b,       /* FC_END */
/* 808 */   
            0x1b,       /* FC_CARRAY */
            0x1,        /* 1 */
/* 810 */   NdrFcShort( 0x2 ),  /* 2 */
/* 812 */   0x19,       /* Corr desc:  field pointer, FC_ULONG */
            0x0,        /*  */
/* 814 */   NdrFcShort( 0x0 ),  /* 0 */
/* 816 */   0x6,        /* FC_SHORT */
            0x5b,       /* FC_END */
/* 818 */   
            0x16,       /* FC_PSTRUCT */
            0x3,        /* 3 */
/* 820 */   NdrFcShort( 0x8 ),  /* 8 */
/* 822 */   
            0x4b,       /* FC_PP */
            0x5c,       /* FC_PAD */
/* 824 */   
            0x46,       /* FC_NO_REPEAT */
            0x5c,       /* FC_PAD */
/* 826 */   NdrFcShort( 0x4 ),  /* 4 */
/* 828 */   NdrFcShort( 0x4 ),  /* 4 */
/* 830 */   0x13, 0x0,  /* FC_OP */
/* 832 */   NdrFcShort( 0xffffffe8 ),   /* Offset= -24 (808) */
/* 834 */   
            0x5b,       /* FC_END */

            0x8,        /* FC_LONG */
/* 836 */   0x8,        /* FC_LONG */
            0x5b,       /* FC_END */
/* 838 */   
            0x1b,       /* FC_CARRAY */
            0x3,        /* 3 */
/* 840 */   NdrFcShort( 0x4 ),  /* 4 */
/* 842 */   0x19,       /* Corr desc:  field pointer, FC_ULONG */
            0x0,        /*  */
/* 844 */   NdrFcShort( 0x0 ),  /* 0 */
/* 846 */   0x8,        /* FC_LONG */
            0x5b,       /* FC_END */
/* 848 */   
            0x16,       /* FC_PSTRUCT */
            0x3,        /* 3 */
/* 850 */   NdrFcShort( 0x8 ),  /* 8 */
/* 852 */   
            0x4b,       /* FC_PP */
            0x5c,       /* FC_PAD */
/* 854 */   
            0x46,       /* FC_NO_REPEAT */
            0x5c,       /* FC_PAD */
/* 856 */   NdrFcShort( 0x4 ),  /* 4 */
/* 858 */   NdrFcShort( 0x4 ),  /* 4 */
/* 860 */   0x13, 0x0,  /* FC_OP */
/* 862 */   NdrFcShort( 0xffffffe8 ),   /* Offset= -24 (838) */
/* 864 */   
            0x5b,       /* FC_END */

            0x8,        /* FC_LONG */
/* 866 */   0x8,        /* FC_LONG */
            0x5b,       /* FC_END */
/* 868 */   
            0x1b,       /* FC_CARRAY */
            0x7,        /* 7 */
/* 870 */   NdrFcShort( 0x8 ),  /* 8 */
/* 872 */   0x19,       /* Corr desc:  field pointer, FC_ULONG */
            0x0,        /*  */
/* 874 */   NdrFcShort( 0x0 ),  /* 0 */
/* 876 */   0xb,        /* FC_HYPER */
            0x5b,       /* FC_END */
/* 878 */   
            0x16,       /* FC_PSTRUCT */
            0x3,        /* 3 */
/* 880 */   NdrFcShort( 0x8 ),  /* 8 */
/* 882 */   
            0x4b,       /* FC_PP */
            0x5c,       /* FC_PAD */
/* 884 */   
            0x46,       /* FC_NO_REPEAT */
            0x5c,       /* FC_PAD */
/* 886 */   NdrFcShort( 0x4 ),  /* 4 */
/* 888 */   NdrFcShort( 0x4 ),  /* 4 */
/* 890 */   0x13, 0x0,  /* FC_OP */
/* 892 */   NdrFcShort( 0xffffffe8 ),   /* Offset= -24 (868) */
/* 894 */   
            0x5b,       /* FC_END */

            0x8,        /* FC_LONG */
/* 896 */   0x8,        /* FC_LONG */
            0x5b,       /* FC_END */
/* 898 */   
            0x15,       /* FC_STRUCT */
            0x3,        /* 3 */
/* 900 */   NdrFcShort( 0x8 ),  /* 8 */
/* 902 */   0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 904 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 906 */   
            0x1b,       /* FC_CARRAY */
            0x3,        /* 3 */
/* 908 */   NdrFcShort( 0x8 ),  /* 8 */
/* 910 */   0x7,        /* Corr desc: FC_USHORT */
            0x0,        /*  */
/* 912 */   NdrFcShort( 0xffd8 ),   /* -40 */
/* 914 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 916 */   NdrFcShort( 0xffffffee ),   /* Offset= -18 (898) */
/* 918 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 920 */   
            0x1a,       /* FC_BOGUS_STRUCT */
            0x3,        /* 3 */
/* 922 */   NdrFcShort( 0x28 ), /* 40 */
/* 924 */   NdrFcShort( 0xffffffee ),   /* Offset= -18 (906) */
/* 926 */   NdrFcShort( 0x0 ),  /* Offset= 0 (926) */
/* 928 */   0x6,        /* FC_SHORT */
            0x6,        /* FC_SHORT */
/* 930 */   0x38,       /* FC_ALIGNM4 */
            0x8,        /* FC_LONG */
/* 932 */   0x8,        /* FC_LONG */
            0x4c,       /* FC_EMBEDDED_COMPLEX */
/* 934 */   0x0,        /* 0 */
            NdrFcShort( 0xfffffdf7 ),   /* Offset= -521 (414) */
            0x5b,       /* FC_END */
/* 938 */   
            0x13, 0x0,  /* FC_OP */
/* 940 */   NdrFcShort( 0xfffffef6 ),   /* Offset= -266 (674) */
/* 942 */   
            0x13, 0x8,  /* FC_OP [simple_pointer] */
/* 944 */   0x2,        /* FC_CHAR */
            0x5c,       /* FC_PAD */
/* 946 */   
            0x13, 0x8,  /* FC_OP [simple_pointer] */
/* 948 */   0x6,        /* FC_SHORT */
            0x5c,       /* FC_PAD */
/* 950 */   
            0x13, 0x8,  /* FC_OP [simple_pointer] */
/* 952 */   0x8,        /* FC_LONG */
            0x5c,       /* FC_PAD */
/* 954 */   
            0x13, 0x8,  /* FC_OP [simple_pointer] */
/* 956 */   0xa,        /* FC_FLOAT */
            0x5c,       /* FC_PAD */
/* 958 */   
            0x13, 0x8,  /* FC_OP [simple_pointer] */
/* 960 */   0xc,        /* FC_DOUBLE */
            0x5c,       /* FC_PAD */
/* 962 */   
            0x13, 0x0,  /* FC_OP */
/* 964 */   NdrFcShort( 0xfffffdd0 ),   /* Offset= -560 (404) */
/* 966 */   
            0x13, 0x10, /* FC_OP */
/* 968 */   NdrFcShort( 0xfffffc60 ),   /* Offset= -928 (40) */
/* 970 */   
            0x13, 0x10, /* FC_OP */
/* 972 */   NdrFcShort( 0xfffffc9e ),   /* Offset= -866 (106) */
/* 974 */   
            0x13, 0x10, /* FC_OP */
/* 976 */   NdrFcShort( 0xfffffc6a ),   /* Offset= -918 (58) */
/* 978 */   
            0x13, 0x10, /* FC_OP */
/* 980 */   NdrFcShort( 0xfffffdc6 ),   /* Offset= -570 (410) */
/* 982 */   
            0x13, 0x10, /* FC_OP */
/* 984 */   NdrFcShort( 0x2 ),  /* Offset= 2 (986) */
/* 986 */   
            0x13, 0x0,  /* FC_OP */
/* 988 */   NdrFcShort( 0xfffffc24 ),   /* Offset= -988 (0) */
/* 990 */   
            0x15,       /* FC_STRUCT */
            0x7,        /* 7 */
/* 992 */   NdrFcShort( 0x10 ), /* 16 */
/* 994 */   0x6,        /* FC_SHORT */
            0x2,        /* FC_CHAR */
/* 996 */   0x2,        /* FC_CHAR */
            0x38,       /* FC_ALIGNM4 */
/* 998 */   0x8,        /* FC_LONG */
            0x39,       /* FC_ALIGNM8 */
/* 1000 */  0xb,        /* FC_HYPER */
            0x5b,       /* FC_END */
/* 1002 */  
            0x13, 0x0,  /* FC_OP */
/* 1004 */  NdrFcShort( 0xfffffff2 ),   /* Offset= -14 (990) */
/* 1006 */  
            0x1a,       /* FC_BOGUS_STRUCT */
            0x7,        /* 7 */
/* 1008 */  NdrFcShort( 0x20 ), /* 32 */
/* 1010 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1012 */  NdrFcShort( 0x0 ),  /* Offset= 0 (1012) */
/* 1014 */  0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 1016 */  0x6,        /* FC_SHORT */
            0x6,        /* FC_SHORT */
/* 1018 */  0x6,        /* FC_SHORT */
            0x6,        /* FC_SHORT */
/* 1020 */  0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 1022 */  NdrFcShort( 0xfffffc86 ),   /* Offset= -890 (132) */
/* 1024 */  0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 1026 */  0xb4,       /* FC_USER_MARSHAL */
            0x83,       /* 131 */
/* 1028 */  NdrFcShort( 0x1 ),  /* 1 */
/* 1030 */  NdrFcShort( 0x10 ), /* 16 */
/* 1032 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1034 */  NdrFcShort( 0xfffffc76 ),   /* Offset= -906 (128) */
/* 1036 */  
            0x12, 0x0,  /* FC_UP */
/* 1038 */  NdrFcShort( 0xffffffe0 ),   /* Offset= -32 (1006) */
/* 1040 */  0xb4,       /* FC_USER_MARSHAL */
            0x83,       /* 131 */
/* 1042 */  NdrFcShort( 0x1 ),  /* 1 */
/* 1044 */  NdrFcShort( 0x10 ), /* 16 */
/* 1046 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1048 */  NdrFcShort( 0xfffffff4 ),   /* Offset= -12 (1036) */
/* 1050 */  
            0x11, 0xc,  /* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1052 */  0x6,        /* FC_SHORT */
            0x5c,       /* FC_PAD */
/* 1054 */  
            0x11, 0x10, /* FC_RP */
/* 1056 */  NdrFcShort( 0x2 ),  /* Offset= 2 (1058) */
/* 1058 */  
            0x2f,       /* FC_IP */
            0x5a,       /* FC_CONSTANT_IID */
/* 1060 */  NdrFcLong( 0xf8dd32d0 ),    /* -119721264 */
/* 1064 */  NdrFcShort( 0xf7df ),   /* -2081 */
/* 1066 */  NdrFcShort( 0x11d1 ),   /* 4561 */
/* 1068 */  0xa2,       /* 162 */
            0xc8,       /* 200 */
/* 1070 */  0x8,        /* 8 */
            0x0,        /* 0 */
/* 1072 */  0x9,        /* 9 */
            0xdc,       /* 220 */
/* 1074 */  0x63,       /* 99 */
            0x9a,       /* 154 */
/* 1076 */  
            0x11, 0x10, /* FC_RP */
/* 1078 */  NdrFcShort( 0x2 ),  /* Offset= 2 (1080) */
/* 1080 */  
            0x2f,       /* FC_IP */
            0x5a,       /* FC_CONSTANT_IID */
/* 1082 */  NdrFcLong( 0x5b57eea0 ),    /* 1532489376 */
/* 1086 */  NdrFcShort( 0xca9a ),   /* -13670 */
/* 1088 */  NdrFcShort( 0x11d1 ),   /* 4561 */
/* 1090 */  0xb6,       /* 182 */
            0xf,        /* 15 */
/* 1092 */  0x0,        /* 0 */
            0x60,       /* 96 */
/* 1094 */  0xb0,       /* 176 */
            0x87,       /* 135 */
/* 1096 */  0xe2,       /* 226 */
            0x35,       /* 53 */
/* 1098 */  
            0x11, 0x10, /* FC_RP */
/* 1100 */  NdrFcShort( 0x2 ),  /* Offset= 2 (1102) */
/* 1102 */  
            0x2f,       /* FC_IP */
            0x5a,       /* FC_CONSTANT_IID */
/* 1104 */  NdrFcLong( 0x0 ),   /* 0 */
/* 1108 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1110 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1112 */  0xc0,       /* 192 */
            0x0,        /* 0 */
/* 1114 */  0x0,        /* 0 */
            0x0,        /* 0 */
/* 1116 */  0x0,        /* 0 */
            0x0,        /* 0 */
/* 1118 */  0x0,        /* 0 */
            0x46,       /* 70 */
/* 1120 */  
            0x11, 0x10, /* FC_RP */
/* 1122 */  NdrFcShort( 0x2 ),  /* Offset= 2 (1124) */
/* 1124 */  
            0x2f,       /* FC_IP */
            0x5a,       /* FC_CONSTANT_IID */
/* 1126 */  NdrFcLong( 0x2928d4dd ),    /* 690541789 */
/* 1130 */  NdrFcShort( 0xca93 ),   /* -13677 */
/* 1132 */  NdrFcShort( 0x11d1 ),   /* 4561 */
/* 1134 */  0xb6,       /* 182 */
            0xf,        /* 15 */
/* 1136 */  0x0,        /* 0 */
            0x60,       /* 96 */
/* 1138 */  0xb0,       /* 176 */
            0x87,       /* 135 */
/* 1140 */  0xe2,       /* 226 */
            0x35,       /* 53 */
/* 1142 */  
            0x2f,       /* FC_IP */
            0x5a,       /* FC_CONSTANT_IID */
/* 1144 */  NdrFcLong( 0x20400 ),   /* 132096 */
/* 1148 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1150 */  NdrFcShort( 0x0 ),  /* 0 */
/* 1152 */  0xc0,       /* 192 */
            0x0,        /* 0 */
/* 1154 */  0x0,        /* 0 */
            0x0,        /* 0 */
/* 1156 */  0x0,        /* 0 */
            0x0,        /* 0 */
/* 1158 */  0x0,        /* 0 */
            0x46,       /* 70 */
/* 1160 */  
            0x11, 0xc,  /* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1162 */  0xe,        /* FC_ENUM32 */
            0x5c,       /* FC_PAD */
/* 1164 */  
            0x11, 0xc,  /* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1166 */  0xc,        /* FC_DOUBLE */
            0x5c,       /* FC_PAD */
/* 1168 */  
            0x11, 0x10, /* FC_RP */
/* 1170 */  NdrFcShort( 0xffffffe4 ),   /* Offset= -28 (1142) */
/* 1172 */  
            0x11, 0x10, /* FC_RP */
/* 1174 */  NdrFcShort( 0x2 ),  /* Offset= 2 (1176) */
/* 1176 */  
            0x2f,       /* FC_IP */
            0x5a,       /* FC_CONSTANT_IID */
/* 1178 */  NdrFcLong( 0xb2547d92 ),    /* -1303085678 */
/* 1182 */  NdrFcShort( 0x56e ),    /* 1390 */
/* 1184 */  NdrFcShort( 0x11d2 ),   /* 4562 */
/* 1186 */  0xb6,       /* 182 */
            0x51,       /* 81 */
/* 1188 */  0x0,        /* 0 */
            0x60,       /* 96 */
/* 1190 */  0xb0,       /* 176 */
            0x87,       /* 135 */
/* 1192 */  0xe2,       /* 226 */
            0x35,       /* 53 */

            0x0
        }
    };

const CInterfaceProxyVtbl * _AsdkSquareLib_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IAcadObjectEventsProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAcadHyperlinksProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAcadHyperlinkProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAcadObjectProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAcadEntityProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAsdkSquareWrapperProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAcadDictionaryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAcadXRecordProxyVtbl,
    0
};

const CInterfaceStubVtbl * _AsdkSquareLib_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IAcadObjectEventsStubVtbl,
    ( CInterfaceStubVtbl *) &_IAcadHyperlinksStubVtbl,
    ( CInterfaceStubVtbl *) &_IAcadHyperlinkStubVtbl,
    ( CInterfaceStubVtbl *) &_IAcadObjectStubVtbl,
    ( CInterfaceStubVtbl *) &_IAcadEntityStubVtbl,
    ( CInterfaceStubVtbl *) &_IAsdkSquareWrapperStubVtbl,
    ( CInterfaceStubVtbl *) &_IAcadDictionaryStubVtbl,
    ( CInterfaceStubVtbl *) &_IAcadXRecordStubVtbl,
    0
};

PCInterfaceName const _AsdkSquareLib_InterfaceNamesList[] = 
{
    "IAcadObjectEvents",
    "IAcadHyperlinks",
    "IAcadHyperlink",
    "IAcadObject",
    "IAcadEntity",
    "IAsdkSquareWrapper",
    "IAcadDictionary",
    "IAcadXRecord",
    0
};

const IID *  _AsdkSquareLib_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _AsdkSquareLib_CHECK_IID(n) IID_GENERIC_CHECK_IID( _AsdkSquareLib, pIID, n)

int __stdcall _AsdkSquareLib_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _AsdkSquareLib, 8, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _AsdkSquareLib, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _AsdkSquareLib, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _AsdkSquareLib, 8, *pIndex )
    
}

const ExtendedProxyFileInfo AsdkSquareLib_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _AsdkSquareLib_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _AsdkSquareLib_StubVtblList,
    (const PCInterfaceName * ) & _AsdkSquareLib_InterfaceNamesList,
    (const IID ** ) & _AsdkSquareLib_BaseIIDList,
    & _AsdkSquareLib_IID_Lookup, 
    8,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
