/*
   (C) Copyright 1999-2002 by Autodesk, Inc. 
  
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

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Feb 03 23:48:47 2003
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___AcPp_h__
#define ___AcPp_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAcPpAcadInput_FWD_DEFINED__
#define __IAcPpAcadInput_FWD_DEFINED__
typedef interface IAcPpAcadInput IAcPpAcadInput;
#endif 	/* __IAcPpAcadInput_FWD_DEFINED__ */


#ifndef __IAcPpPalette_FWD_DEFINED__
#define __IAcPpPalette_FWD_DEFINED__
typedef interface IAcPpPalette IAcPpPalette;
#endif 	/* __IAcPpPalette_FWD_DEFINED__ */


#ifndef __IAcPpPaletteEvents_FWD_DEFINED__
#define __IAcPpPaletteEvents_FWD_DEFINED__
typedef interface IAcPpPaletteEvents IAcPpPaletteEvents;
#endif 	/* __IAcPpPaletteEvents_FWD_DEFINED__ */


#ifndef __IAcPpPaletteSet_FWD_DEFINED__
#define __IAcPpPaletteSet_FWD_DEFINED__
typedef interface IAcPpPaletteSet IAcPpPaletteSet;
#endif 	/* __IAcPpPaletteSet_FWD_DEFINED__ */


#ifndef __IAcPpPaletteSetEvents_FWD_DEFINED__
#define __IAcPpPaletteSetEvents_FWD_DEFINED__
typedef interface IAcPpPaletteSetEvents IAcPpPaletteSetEvents;
#endif 	/* __IAcPpPaletteSetEvents_FWD_DEFINED__ */


#ifndef __AcPpAcadInput_FWD_DEFINED__
#define __AcPpAcadInput_FWD_DEFINED__

#ifdef __cplusplus
typedef class AcPpAcadInput AcPpAcadInput;
#else
typedef struct AcPpAcadInput AcPpAcadInput;
#endif /* __cplusplus */

#endif 	/* __AcPpAcadInput_FWD_DEFINED__ */


#ifndef __AcPpPaletteSet_FWD_DEFINED__
#define __AcPpPaletteSet_FWD_DEFINED__

#ifdef __cplusplus
typedef class AcPpPaletteSet AcPpPaletteSet;
#else
typedef struct AcPpPaletteSet AcPpPaletteSet;
#endif /* __cplusplus */

#endif 	/* __AcPpPaletteSet_FWD_DEFINED__ */


#ifndef __AcPpPalette_FWD_DEFINED__
#define __AcPpPalette_FWD_DEFINED__

#ifdef __cplusplus
typedef class AcPpPalette AcPpPalette;
#else
typedef struct AcPpPalette AcPpPalette;
#endif /* __cplusplus */

#endif 	/* __AcPpPalette_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "acpi.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_AcPp_0000 */
/* [local] */ 

#define ACPPINPUT_ID_VALUE           1
#define ACPPINPUT_ID_STATUS          2
#define ACPPINPUT_ID_DOCUMENT        3
#define ACPPINPUT_ID_CRONLY          4
#define ACPPINPUT_ID_PROMPT          5
#define ACPPINPUT_ID_PROMPT2         6
#define ACPPINPUT_ID_INITGETBIT      7
#define ACPPINPUT_ID_INITGETKWORD    8
#define ACPPINPUT_ID_BASEPOINT       9
#define ACPPINPUT_ID_PROMPTTYPE      10
#define ACPPINPUT_ID_ENABLENOTIFICATION 11


extern RPC_IF_HANDLE __MIDL_itf_AcPp_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AcPp_0000_v0_0_s_ifspec;

#ifndef __IAcPpAcadInput_INTERFACE_DEFINED__
#define __IAcPpAcadInput_INTERFACE_DEFINED__

/* interface IAcPpAcadInput */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum StatusType
    {	StatusPrompting	= -1,
	StatusRTNORM	= 5100,
	StatusRTERROR	= -5001,
	StatusRTCAN	= -5002,
	StatusRTNONE	= 5000,
	StatusRTREJ	= -5003,
	StatusRTKWORD	= -5005,
	StatusMODELESS	= 5027
    } 	StatusType;

typedef /* [v1_enum] */ 
enum PromptType
    {	GetAngle	= 1,
	GetCorner	= 2,
	GetDist	= 3,
	GetInt	= 4,
	GetKword	= 5,
	GetOrient	= 6,
	GetPoint	= 7,
	GetReal	= 8,
	GetString	= 9,
	EntSel	= 10
    } 	PromptType;


EXTERN_C const IID IID_IAcPpAcadInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07816A95-3C14-4236-B9D3-AA7F4A4A1EFB")
    IAcPpAcadInput : public IUnknown
    {
    public:
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_Status( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_Document( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_Document( 
            /* [in] */ IUnknown *newVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_CrOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_CrOnly( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_Prompt( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_Prompt( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_Prompt2( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_Prompt2( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_InitGetBit( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_InitGetBit( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_InitGetKword( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_InitGetKword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_BasePoint( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_BasePoint( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_PromptType( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_PromptType( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnableNotification( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableNotification( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoPrompt( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CancelPrompt( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPpAcadInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpAcadInput * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpAcadInput * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpAcadInput * This);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IAcPpAcadInput * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Status )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Status )( 
            IAcPpAcadInput * This,
            /* [in] */ long newVal);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Document )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Document )( 
            IAcPpAcadInput * This,
            /* [in] */ IUnknown *newVal);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CrOnly )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CrOnly )( 
            IAcPpAcadInput * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Prompt )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Prompt )( 
            IAcPpAcadInput * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Prompt2 )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Prompt2 )( 
            IAcPpAcadInput * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InitGetBit )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InitGetBit )( 
            IAcPpAcadInput * This,
            /* [in] */ long newVal);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InitGetKword )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InitGetKword )( 
            IAcPpAcadInput * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BasePoint )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BasePoint )( 
            IAcPpAcadInput * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PromptType )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PromptType )( 
            IAcPpAcadInput * This,
            /* [in] */ short newVal);
        
        /* [helpstring][requestedit][bindable][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EnableNotification )( 
            IAcPpAcadInput * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][requestedit][bindable][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EnableNotification )( 
            IAcPpAcadInput * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoPrompt )( 
            IAcPpAcadInput * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CancelPrompt )( 
            IAcPpAcadInput * This);
        
        END_INTERFACE
    } IAcPpAcadInputVtbl;

    interface IAcPpAcadInput
    {
        CONST_VTBL struct IAcPpAcadInputVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpAcadInput_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPpAcadInput_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPpAcadInput_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPpAcadInput_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define IAcPpAcadInput_put_Value(This,newVal)	\
    (This)->lpVtbl -> put_Value(This,newVal)

#define IAcPpAcadInput_get_Status(This,pVal)	\
    (This)->lpVtbl -> get_Status(This,pVal)

#define IAcPpAcadInput_put_Status(This,newVal)	\
    (This)->lpVtbl -> put_Status(This,newVal)

#define IAcPpAcadInput_get_Document(This,pVal)	\
    (This)->lpVtbl -> get_Document(This,pVal)

#define IAcPpAcadInput_put_Document(This,newVal)	\
    (This)->lpVtbl -> put_Document(This,newVal)

#define IAcPpAcadInput_get_CrOnly(This,pVal)	\
    (This)->lpVtbl -> get_CrOnly(This,pVal)

#define IAcPpAcadInput_put_CrOnly(This,newVal)	\
    (This)->lpVtbl -> put_CrOnly(This,newVal)

#define IAcPpAcadInput_get_Prompt(This,pVal)	\
    (This)->lpVtbl -> get_Prompt(This,pVal)

#define IAcPpAcadInput_put_Prompt(This,newVal)	\
    (This)->lpVtbl -> put_Prompt(This,newVal)

#define IAcPpAcadInput_get_Prompt2(This,pVal)	\
    (This)->lpVtbl -> get_Prompt2(This,pVal)

#define IAcPpAcadInput_put_Prompt2(This,newVal)	\
    (This)->lpVtbl -> put_Prompt2(This,newVal)

#define IAcPpAcadInput_get_InitGetBit(This,pVal)	\
    (This)->lpVtbl -> get_InitGetBit(This,pVal)

#define IAcPpAcadInput_put_InitGetBit(This,newVal)	\
    (This)->lpVtbl -> put_InitGetBit(This,newVal)

#define IAcPpAcadInput_get_InitGetKword(This,pVal)	\
    (This)->lpVtbl -> get_InitGetKword(This,pVal)

#define IAcPpAcadInput_put_InitGetKword(This,newVal)	\
    (This)->lpVtbl -> put_InitGetKword(This,newVal)

#define IAcPpAcadInput_get_BasePoint(This,pVal)	\
    (This)->lpVtbl -> get_BasePoint(This,pVal)

#define IAcPpAcadInput_put_BasePoint(This,newVal)	\
    (This)->lpVtbl -> put_BasePoint(This,newVal)

#define IAcPpAcadInput_get_PromptType(This,pVal)	\
    (This)->lpVtbl -> get_PromptType(This,pVal)

#define IAcPpAcadInput_put_PromptType(This,newVal)	\
    (This)->lpVtbl -> put_PromptType(This,newVal)

#define IAcPpAcadInput_get_EnableNotification(This,pVal)	\
    (This)->lpVtbl -> get_EnableNotification(This,pVal)

#define IAcPpAcadInput_put_EnableNotification(This,newVal)	\
    (This)->lpVtbl -> put_EnableNotification(This,newVal)

#define IAcPpAcadInput_DoPrompt(This)	\
    (This)->lpVtbl -> DoPrompt(This)

#define IAcPpAcadInput_CancelPrompt(This)	\
    (This)->lpVtbl -> CancelPrompt(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_Value_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IAcPpAcadInput_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_Value_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IAcPpAcadInput_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_Status_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IAcPpAcadInput_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_Status_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ long newVal);


void __RPC_STUB IAcPpAcadInput_put_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_Document_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB IAcPpAcadInput_get_Document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_Document_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ IUnknown *newVal);


void __RPC_STUB IAcPpAcadInput_put_Document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_CrOnly_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IAcPpAcadInput_get_CrOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_CrOnly_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IAcPpAcadInput_put_CrOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_Prompt_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IAcPpAcadInput_get_Prompt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_Prompt_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IAcPpAcadInput_put_Prompt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_Prompt2_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IAcPpAcadInput_get_Prompt2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_Prompt2_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IAcPpAcadInput_put_Prompt2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_InitGetBit_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IAcPpAcadInput_get_InitGetBit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_InitGetBit_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ long newVal);


void __RPC_STUB IAcPpAcadInput_put_InitGetBit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_InitGetKword_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IAcPpAcadInput_get_InitGetKword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_InitGetKword_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IAcPpAcadInput_put_InitGetKword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_BasePoint_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IAcPpAcadInput_get_BasePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_BasePoint_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IAcPpAcadInput_put_BasePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_PromptType_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IAcPpAcadInput_get_PromptType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_PromptType_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ short newVal);


void __RPC_STUB IAcPpAcadInput_put_PromptType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_get_EnableNotification_Proxy( 
    IAcPpAcadInput * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IAcPpAcadInput_get_EnableNotification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][requestedit][bindable][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_put_EnableNotification_Proxy( 
    IAcPpAcadInput * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IAcPpAcadInput_put_EnableNotification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_DoPrompt_Proxy( 
    IAcPpAcadInput * This);


void __RPC_STUB IAcPpAcadInput_DoPrompt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpAcadInput_CancelPrompt_Proxy( 
    IAcPpAcadInput * This);


void __RPC_STUB IAcPpAcadInput_CancelPrompt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPpAcadInput_INTERFACE_DEFINED__ */


#ifndef __IAcPpPalette_INTERFACE_DEFINED__
#define __IAcPpPalette_INTERFACE_DEFINED__

/* interface IAcPpPalette */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpPalette;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A20A927F-5508-4624-9157-FD5CBE5B2D64")
    IAcPpPalette : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InspectorControl( 
            /* [retval][out] */ IAcPiPropertyInspector **pInspector) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPpPaletteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpPalette * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpPalette * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpPalette * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IAcPpPalette * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IAcPpPalette * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InspectorControl )( 
            IAcPpPalette * This,
            /* [retval][out] */ IAcPiPropertyInspector **pInspector);
        
        END_INTERFACE
    } IAcPpPaletteVtbl;

    interface IAcPpPalette
    {
        CONST_VTBL struct IAcPpPaletteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpPalette_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPpPalette_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPpPalette_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPpPalette_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IAcPpPalette_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IAcPpPalette_get_InspectorControl(This,pInspector)	\
    (This)->lpVtbl -> get_InspectorControl(This,pInspector)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpPalette_get_Name_Proxy( 
    IAcPpPalette * This,
    /* [retval][out] */ BSTR *name);


void __RPC_STUB IAcPpPalette_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpPalette_put_Name_Proxy( 
    IAcPpPalette * This,
    /* [in] */ BSTR name);


void __RPC_STUB IAcPpPalette_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpPalette_get_InspectorControl_Proxy( 
    IAcPpPalette * This,
    /* [retval][out] */ IAcPiPropertyInspector **pInspector);


void __RPC_STUB IAcPpPalette_get_InspectorControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPpPalette_INTERFACE_DEFINED__ */


#ifndef __IAcPpPaletteEvents_INTERFACE_DEFINED__
#define __IAcPpPaletteEvents_INTERFACE_DEFINED__

/* interface IAcPpPaletteEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpPaletteEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1EA7682-303C-4173-BA92-0EEF3DD3756E")
    IAcPpPaletteEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnNameChanged( 
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnSelectionChanged( 
            /* [in] */ VARIANT *newObjectArray,
            /* [in] */ VARIANT *newPropMgrArray,
            /* [out][in] */ VARIANT_BOOL *bHandled) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPpPaletteEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpPaletteEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpPaletteEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpPaletteEvents * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnNameChanged )( 
            IAcPpPaletteEvents * This,
            /* [in] */ BSTR newName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnSelectionChanged )( 
            IAcPpPaletteEvents * This,
            /* [in] */ VARIANT *newObjectArray,
            /* [in] */ VARIANT *newPropMgrArray,
            /* [out][in] */ VARIANT_BOOL *bHandled);
        
        END_INTERFACE
    } IAcPpPaletteEventsVtbl;

    interface IAcPpPaletteEvents
    {
        CONST_VTBL struct IAcPpPaletteEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpPaletteEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPpPaletteEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPpPaletteEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPpPaletteEvents_OnNameChanged(This,newName)	\
    (This)->lpVtbl -> OnNameChanged(This,newName)

#define IAcPpPaletteEvents_OnSelectionChanged(This,newObjectArray,newPropMgrArray,bHandled)	\
    (This)->lpVtbl -> OnSelectionChanged(This,newObjectArray,newPropMgrArray,bHandled)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteEvents_OnNameChanged_Proxy( 
    IAcPpPaletteEvents * This,
    /* [in] */ BSTR newName);


void __RPC_STUB IAcPpPaletteEvents_OnNameChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteEvents_OnSelectionChanged_Proxy( 
    IAcPpPaletteEvents * This,
    /* [in] */ VARIANT *newObjectArray,
    /* [in] */ VARIANT *newPropMgrArray,
    /* [out][in] */ VARIANT_BOOL *bHandled);


void __RPC_STUB IAcPpPaletteEvents_OnSelectionChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPpPaletteEvents_INTERFACE_DEFINED__ */


#ifndef __IAcPpPaletteSet_INTERFACE_DEFINED__
#define __IAcPpPaletteSet_INTERFACE_DEFINED__

/* interface IAcPpPaletteSet */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum DockPos
    {	Floating	= -1,
	Left	= 0xe81c,
	Right	= 0xe81d
    } 	DockPos;


EXTERN_C const IID IID_IAcPpPaletteSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0CC0CED7-7D69-490b-A84B-A7500674A29C")
    IAcPpPaletteSet : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddPalette( 
            /* [in] */ IAcPpPalette *pPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeletePalette( 
            /* [in] */ IAcPpPalette *pPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertPalette( 
            /* [in] */ int index,
            /* [in] */ IAcPpPalette *pPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPalette( 
            /* [in] */ int index,
            /* [retval][out] */ IAcPpPalette **pPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPaletteByName( 
            /* [in] */ BSTR paletteName,
            /* [retval][out] */ IAcPpPalette **pPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ActivatePalette( 
            /* [in] */ IAcPpPalette *pPalette) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PaletteCount( 
            /* [retval][out] */ int *nPalettes) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Visibility( 
            /* [retval][out] */ VARIANT_BOOL *bIsVisible) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Visibility( 
            /* [in] */ VARIANT_BOOL bIsVisible) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentIndex( 
            /* [retval][out] */ int *nCurrentIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDockingState( 
            /* [out] */ int *nDockPos,
            /* [out] */ long *left,
            /* [out] */ long *top,
            /* [out] */ long *width,
            /* [out] */ long *height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDockingState( 
            /* [in] */ int nDockPos,
            /* [in] */ long left,
            /* [in] */ long top,
            /* [in] */ long width,
            /* [in] */ long height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFloatingRect( 
            /* [out] */ long *left,
            /* [out] */ long *top,
            /* [out] */ long *width,
            /* [out] */ long *height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDockingRect( 
            /* [out] */ int *nDockPos,
            /* [out] */ long *left,
            /* [out] */ long *top,
            /* [out] */ long *width,
            /* [out] */ long *height) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPpPaletteSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpPaletteSet * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpPaletteSet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpPaletteSet * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddPalette )( 
            IAcPpPaletteSet * This,
            /* [in] */ IAcPpPalette *pPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeletePalette )( 
            IAcPpPaletteSet * This,
            /* [in] */ IAcPpPalette *pPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InsertPalette )( 
            IAcPpPaletteSet * This,
            /* [in] */ int index,
            /* [in] */ IAcPpPalette *pPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPalette )( 
            IAcPpPaletteSet * This,
            /* [in] */ int index,
            /* [retval][out] */ IAcPpPalette **pPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPaletteByName )( 
            IAcPpPaletteSet * This,
            /* [in] */ BSTR paletteName,
            /* [retval][out] */ IAcPpPalette **pPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ActivatePalette )( 
            IAcPpPaletteSet * This,
            /* [in] */ IAcPpPalette *pPalette);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PaletteCount )( 
            IAcPpPaletteSet * This,
            /* [retval][out] */ int *nPalettes);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Visibility )( 
            IAcPpPaletteSet * This,
            /* [retval][out] */ VARIANT_BOOL *bIsVisible);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Visibility )( 
            IAcPpPaletteSet * This,
            /* [in] */ VARIANT_BOOL bIsVisible);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentIndex )( 
            IAcPpPaletteSet * This,
            /* [retval][out] */ int *nCurrentIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDockingState )( 
            IAcPpPaletteSet * This,
            /* [out] */ int *nDockPos,
            /* [out] */ long *left,
            /* [out] */ long *top,
            /* [out] */ long *width,
            /* [out] */ long *height);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDockingState )( 
            IAcPpPaletteSet * This,
            /* [in] */ int nDockPos,
            /* [in] */ long left,
            /* [in] */ long top,
            /* [in] */ long width,
            /* [in] */ long height);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFloatingRect )( 
            IAcPpPaletteSet * This,
            /* [out] */ long *left,
            /* [out] */ long *top,
            /* [out] */ long *width,
            /* [out] */ long *height);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDockingRect )( 
            IAcPpPaletteSet * This,
            /* [out] */ int *nDockPos,
            /* [out] */ long *left,
            /* [out] */ long *top,
            /* [out] */ long *width,
            /* [out] */ long *height);
        
        END_INTERFACE
    } IAcPpPaletteSetVtbl;

    interface IAcPpPaletteSet
    {
        CONST_VTBL struct IAcPpPaletteSetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpPaletteSet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPpPaletteSet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPpPaletteSet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPpPaletteSet_AddPalette(This,pPalette)	\
    (This)->lpVtbl -> AddPalette(This,pPalette)

#define IAcPpPaletteSet_DeletePalette(This,pPalette)	\
    (This)->lpVtbl -> DeletePalette(This,pPalette)

#define IAcPpPaletteSet_InsertPalette(This,index,pPalette)	\
    (This)->lpVtbl -> InsertPalette(This,index,pPalette)

#define IAcPpPaletteSet_GetPalette(This,index,pPalette)	\
    (This)->lpVtbl -> GetPalette(This,index,pPalette)

#define IAcPpPaletteSet_GetPaletteByName(This,paletteName,pPalette)	\
    (This)->lpVtbl -> GetPaletteByName(This,paletteName,pPalette)

#define IAcPpPaletteSet_ActivatePalette(This,pPalette)	\
    (This)->lpVtbl -> ActivatePalette(This,pPalette)

#define IAcPpPaletteSet_get_PaletteCount(This,nPalettes)	\
    (This)->lpVtbl -> get_PaletteCount(This,nPalettes)

#define IAcPpPaletteSet_get_Visibility(This,bIsVisible)	\
    (This)->lpVtbl -> get_Visibility(This,bIsVisible)

#define IAcPpPaletteSet_put_Visibility(This,bIsVisible)	\
    (This)->lpVtbl -> put_Visibility(This,bIsVisible)

#define IAcPpPaletteSet_get_CurrentIndex(This,nCurrentIndex)	\
    (This)->lpVtbl -> get_CurrentIndex(This,nCurrentIndex)

#define IAcPpPaletteSet_GetDockingState(This,nDockPos,left,top,width,height)	\
    (This)->lpVtbl -> GetDockingState(This,nDockPos,left,top,width,height)

#define IAcPpPaletteSet_SetDockingState(This,nDockPos,left,top,width,height)	\
    (This)->lpVtbl -> SetDockingState(This,nDockPos,left,top,width,height)

#define IAcPpPaletteSet_GetFloatingRect(This,left,top,width,height)	\
    (This)->lpVtbl -> GetFloatingRect(This,left,top,width,height)

#define IAcPpPaletteSet_GetDockingRect(This,nDockPos,left,top,width,height)	\
    (This)->lpVtbl -> GetDockingRect(This,nDockPos,left,top,width,height)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_AddPalette_Proxy( 
    IAcPpPaletteSet * This,
    /* [in] */ IAcPpPalette *pPalette);


void __RPC_STUB IAcPpPaletteSet_AddPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_DeletePalette_Proxy( 
    IAcPpPaletteSet * This,
    /* [in] */ IAcPpPalette *pPalette);


void __RPC_STUB IAcPpPaletteSet_DeletePalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_InsertPalette_Proxy( 
    IAcPpPaletteSet * This,
    /* [in] */ int index,
    /* [in] */ IAcPpPalette *pPalette);


void __RPC_STUB IAcPpPaletteSet_InsertPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_GetPalette_Proxy( 
    IAcPpPaletteSet * This,
    /* [in] */ int index,
    /* [retval][out] */ IAcPpPalette **pPalette);


void __RPC_STUB IAcPpPaletteSet_GetPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_GetPaletteByName_Proxy( 
    IAcPpPaletteSet * This,
    /* [in] */ BSTR paletteName,
    /* [retval][out] */ IAcPpPalette **pPalette);


void __RPC_STUB IAcPpPaletteSet_GetPaletteByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_ActivatePalette_Proxy( 
    IAcPpPaletteSet * This,
    /* [in] */ IAcPpPalette *pPalette);


void __RPC_STUB IAcPpPaletteSet_ActivatePalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_get_PaletteCount_Proxy( 
    IAcPpPaletteSet * This,
    /* [retval][out] */ int *nPalettes);


void __RPC_STUB IAcPpPaletteSet_get_PaletteCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_get_Visibility_Proxy( 
    IAcPpPaletteSet * This,
    /* [retval][out] */ VARIANT_BOOL *bIsVisible);


void __RPC_STUB IAcPpPaletteSet_get_Visibility_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_put_Visibility_Proxy( 
    IAcPpPaletteSet * This,
    /* [in] */ VARIANT_BOOL bIsVisible);


void __RPC_STUB IAcPpPaletteSet_put_Visibility_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_get_CurrentIndex_Proxy( 
    IAcPpPaletteSet * This,
    /* [retval][out] */ int *nCurrentIndex);


void __RPC_STUB IAcPpPaletteSet_get_CurrentIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_GetDockingState_Proxy( 
    IAcPpPaletteSet * This,
    /* [out] */ int *nDockPos,
    /* [out] */ long *left,
    /* [out] */ long *top,
    /* [out] */ long *width,
    /* [out] */ long *height);


void __RPC_STUB IAcPpPaletteSet_GetDockingState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_SetDockingState_Proxy( 
    IAcPpPaletteSet * This,
    /* [in] */ int nDockPos,
    /* [in] */ long left,
    /* [in] */ long top,
    /* [in] */ long width,
    /* [in] */ long height);


void __RPC_STUB IAcPpPaletteSet_SetDockingState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_GetFloatingRect_Proxy( 
    IAcPpPaletteSet * This,
    /* [out] */ long *left,
    /* [out] */ long *top,
    /* [out] */ long *width,
    /* [out] */ long *height);


void __RPC_STUB IAcPpPaletteSet_GetFloatingRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSet_GetDockingRect_Proxy( 
    IAcPpPaletteSet * This,
    /* [out] */ int *nDockPos,
    /* [out] */ long *left,
    /* [out] */ long *top,
    /* [out] */ long *width,
    /* [out] */ long *height);


void __RPC_STUB IAcPpPaletteSet_GetDockingRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPpPaletteSet_INTERFACE_DEFINED__ */


#ifndef __IAcPpPaletteSetEvents_INTERFACE_DEFINED__
#define __IAcPpPaletteSetEvents_INTERFACE_DEFINED__

/* interface IAcPpPaletteSetEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpPaletteSetEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C3F530AF-E211-49fa-9E02-28290E4141F6")
    IAcPpPaletteSetEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnPaletteAdded( 
            /* [in] */ IAcPpPalette *pNewPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnPaletteDeleted( 
            /* [in] */ IAcPpPalette *pPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnPaletteActivated( 
            /* [in] */ IAcPpPalette *pPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnPaletteDeActivated( 
            /* [in] */ IAcPpPalette *pPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnSelectionChanged( 
            /* [in] */ VARIANT *newObjectArray,
            /* [in] */ VARIANT *newPropMgrArray) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnVisibilityChanged( 
            /* [in] */ VARIANT_BOOL bIsVisible) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPpPaletteSetEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpPaletteSetEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpPaletteSetEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpPaletteSetEvents * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnPaletteAdded )( 
            IAcPpPaletteSetEvents * This,
            /* [in] */ IAcPpPalette *pNewPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnPaletteDeleted )( 
            IAcPpPaletteSetEvents * This,
            /* [in] */ IAcPpPalette *pPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnPaletteActivated )( 
            IAcPpPaletteSetEvents * This,
            /* [in] */ IAcPpPalette *pPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnPaletteDeActivated )( 
            IAcPpPaletteSetEvents * This,
            /* [in] */ IAcPpPalette *pPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnSelectionChanged )( 
            IAcPpPaletteSetEvents * This,
            /* [in] */ VARIANT *newObjectArray,
            /* [in] */ VARIANT *newPropMgrArray);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnVisibilityChanged )( 
            IAcPpPaletteSetEvents * This,
            /* [in] */ VARIANT_BOOL bIsVisible);
        
        END_INTERFACE
    } IAcPpPaletteSetEventsVtbl;

    interface IAcPpPaletteSetEvents
    {
        CONST_VTBL struct IAcPpPaletteSetEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpPaletteSetEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPpPaletteSetEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPpPaletteSetEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPpPaletteSetEvents_OnPaletteAdded(This,pNewPalette)	\
    (This)->lpVtbl -> OnPaletteAdded(This,pNewPalette)

#define IAcPpPaletteSetEvents_OnPaletteDeleted(This,pPalette)	\
    (This)->lpVtbl -> OnPaletteDeleted(This,pPalette)

#define IAcPpPaletteSetEvents_OnPaletteActivated(This,pPalette)	\
    (This)->lpVtbl -> OnPaletteActivated(This,pPalette)

#define IAcPpPaletteSetEvents_OnPaletteDeActivated(This,pPalette)	\
    (This)->lpVtbl -> OnPaletteDeActivated(This,pPalette)

#define IAcPpPaletteSetEvents_OnSelectionChanged(This,newObjectArray,newPropMgrArray)	\
    (This)->lpVtbl -> OnSelectionChanged(This,newObjectArray,newPropMgrArray)

#define IAcPpPaletteSetEvents_OnVisibilityChanged(This,bIsVisible)	\
    (This)->lpVtbl -> OnVisibilityChanged(This,bIsVisible)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSetEvents_OnPaletteAdded_Proxy( 
    IAcPpPaletteSetEvents * This,
    /* [in] */ IAcPpPalette *pNewPalette);


void __RPC_STUB IAcPpPaletteSetEvents_OnPaletteAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSetEvents_OnPaletteDeleted_Proxy( 
    IAcPpPaletteSetEvents * This,
    /* [in] */ IAcPpPalette *pPalette);


void __RPC_STUB IAcPpPaletteSetEvents_OnPaletteDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSetEvents_OnPaletteActivated_Proxy( 
    IAcPpPaletteSetEvents * This,
    /* [in] */ IAcPpPalette *pPalette);


void __RPC_STUB IAcPpPaletteSetEvents_OnPaletteActivated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSetEvents_OnPaletteDeActivated_Proxy( 
    IAcPpPaletteSetEvents * This,
    /* [in] */ IAcPpPalette *pPalette);


void __RPC_STUB IAcPpPaletteSetEvents_OnPaletteDeActivated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSetEvents_OnSelectionChanged_Proxy( 
    IAcPpPaletteSetEvents * This,
    /* [in] */ VARIANT *newObjectArray,
    /* [in] */ VARIANT *newPropMgrArray);


void __RPC_STUB IAcPpPaletteSetEvents_OnSelectionChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPpPaletteSetEvents_OnVisibilityChanged_Proxy( 
    IAcPpPaletteSetEvents * This,
    /* [in] */ VARIANT_BOOL bIsVisible);


void __RPC_STUB IAcPpPaletteSetEvents_OnVisibilityChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPpPaletteSetEvents_INTERFACE_DEFINED__ */



#ifndef __AcPpLib_LIBRARY_DEFINED__
#define __AcPpLib_LIBRARY_DEFINED__

/* library AcPpLib */
/* [custom][helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AcPpLib;

EXTERN_C const CLSID CLSID_AcPpAcadInput;

#ifdef __cplusplus

class DECLSPEC_UUID("9307A809-170D-4A75-B8EC-D3C462D2F4DB")
AcPpAcadInput;
#endif

EXTERN_C const CLSID CLSID_AcPpPaletteSet;

#ifdef __cplusplus

class DECLSPEC_UUID("2FAA8BEA-AB1B-479a-97B2-6E7AAB38750E")
AcPpPaletteSet;
#endif

EXTERN_C const CLSID CLSID_AcPpPalette;

#ifdef __cplusplus

class DECLSPEC_UUID("83E53FB0-C3F9-44c8-8917-1A79D89B90AA")
AcPpPalette;
#endif
#endif /* __AcPpLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


