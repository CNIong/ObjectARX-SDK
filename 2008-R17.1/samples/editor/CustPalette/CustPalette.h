// (C) Copyright 2005-2006 by Autodesk, Inc. 
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

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu Sep 15 10:56:39 2005
 */
/* Compiler settings for .\CustPalette.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __CustPalette_h__
#define __CustPalette_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IInspData_FWD_DEFINED__
#define __IInspData_FWD_DEFINED__
typedef interface IInspData IInspData;
#endif 	/* __IInspData_FWD_DEFINED__ */


#ifndef __IDWGPreview_FWD_DEFINED__
#define __IDWGPreview_FWD_DEFINED__
typedef interface IDWGPreview IDWGPreview;
#endif 	/* __IDWGPreview_FWD_DEFINED__ */


#ifndef __InspData_FWD_DEFINED__
#define __InspData_FWD_DEFINED__

#ifdef __cplusplus
typedef class InspData InspData;
#else
typedef struct InspData InspData;
#endif /* __cplusplus */

#endif 	/* __InspData_FWD_DEFINED__ */


#ifndef __DWGPreview_FWD_DEFINED__
#define __DWGPreview_FWD_DEFINED__

#ifdef __cplusplus
typedef class DWGPreview DWGPreview;
#else
typedef struct DWGPreview DWGPreview;
#endif /* __cplusplus */

#endif 	/* __DWGPreview_FWD_DEFINED__ */


#ifndef __PropPage_FWD_DEFINED__
#define __PropPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class PropPage PropPage;
#else
typedef struct PropPage PropPage;
#endif /* __cplusplus */

#endif 	/* __PropPage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IInspData_INTERFACE_DEFINED__
#define __IInspData_INTERFACE_DEFINED__

/* interface IInspData */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IInspData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("621BA68B-5688-4BD8-80E6-C0097FAD9AC9")
    IInspData : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Preview( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Preview( 
            /* [in] */ BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInspDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInspData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInspData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInspData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInspData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInspData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInspData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInspData * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileName )( 
            IInspData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileName )( 
            IInspData * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Preview )( 
            IInspData * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Preview )( 
            IInspData * This,
            /* [in] */ BOOL newVal);
        
        END_INTERFACE
    } IInspDataVtbl;

    interface IInspData
    {
        CONST_VTBL struct IInspDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInspData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInspData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInspData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInspData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInspData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInspData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInspData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInspData_get_FileName(This,pVal)	\
    (This)->lpVtbl -> get_FileName(This,pVal)

#define IInspData_put_FileName(This,newVal)	\
    (This)->lpVtbl -> put_FileName(This,newVal)

#define IInspData_get_Preview(This,pVal)	\
    (This)->lpVtbl -> get_Preview(This,pVal)

#define IInspData_put_Preview(This,newVal)	\
    (This)->lpVtbl -> put_Preview(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInspData_get_FileName_Proxy( 
    IInspData * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IInspData_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInspData_put_FileName_Proxy( 
    IInspData * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IInspData_put_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInspData_get_Preview_Proxy( 
    IInspData * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IInspData_get_Preview_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInspData_put_Preview_Proxy( 
    IInspData * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IInspData_put_Preview_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInspData_INTERFACE_DEFINED__ */


#ifndef __IDWGPreview_INTERFACE_DEFINED__
#define __IDWGPreview_INTERFACE_DEFINED__

/* interface IDWGPreview */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDWGPreview;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E7FF7C38-71E7-4EAD-80C7-FA263D8CEA8E")
    IDWGPreview : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFileName( 
            /* [in] */ BSTR *fileName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDWGPreviewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDWGPreview * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDWGPreview * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDWGPreview * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFileName )( 
            IDWGPreview * This,
            /* [in] */ BSTR *fileName);
        
        END_INTERFACE
    } IDWGPreviewVtbl;

    interface IDWGPreview
    {
        CONST_VTBL struct IDWGPreviewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDWGPreview_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDWGPreview_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDWGPreview_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDWGPreview_GetFileName(This,fileName)	\
    (This)->lpVtbl -> GetFileName(This,fileName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDWGPreview_GetFileName_Proxy( 
    IDWGPreview * This,
    /* [in] */ BSTR *fileName);


void __RPC_STUB IDWGPreview_GetFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDWGPreview_INTERFACE_DEFINED__ */



#ifndef __AsdkCustPaletteLib_LIBRARY_DEFINED__
#define __AsdkCustPaletteLib_LIBRARY_DEFINED__

/* library AsdkCustPaletteLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AsdkCustPaletteLib;

EXTERN_C const CLSID CLSID_InspData;

#ifdef __cplusplus

class DECLSPEC_UUID("27116BE4-11DA-4D43-952F-EF03EAA62884")
InspData;
#endif

EXTERN_C const CLSID CLSID_DWGPreview;

#ifdef __cplusplus

class DECLSPEC_UUID("44EF9F52-159F-480F-9AD8-6289C8C41ADE")
DWGPreview;
#endif

EXTERN_C const CLSID CLSID_PropPage;

#ifdef __cplusplus

class DECLSPEC_UUID("8D92B6D5-EFBA-4AA1-93F4-F8C3D34FC1FB")
PropPage;
#endif
#endif /* __AsdkCustPaletteLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


