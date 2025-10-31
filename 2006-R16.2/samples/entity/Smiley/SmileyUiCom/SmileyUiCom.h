
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Aug 12 17:40:24 2002
 */
/* Compiler settings for .\SmileyUiCom.idl:
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

#ifndef __SmileyUiCom_h__
#define __SmileyUiCom_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___ISmileyApplicationEvents_FWD_DEFINED__
#define ___ISmileyApplicationEvents_FWD_DEFINED__
typedef interface _ISmileyApplicationEvents _ISmileyApplicationEvents;
#endif 	/* ___ISmileyApplicationEvents_FWD_DEFINED__ */


#ifndef __ISmileyApplication_FWD_DEFINED__
#define __ISmileyApplication_FWD_DEFINED__
typedef interface ISmileyApplication ISmileyApplication;
#endif 	/* __ISmileyApplication_FWD_DEFINED__ */


#ifndef __SmileyApplication_FWD_DEFINED__
#define __SmileyApplication_FWD_DEFINED__

#ifdef __cplusplus
typedef class SmileyApplication SmileyApplication;
#else
typedef struct SmileyApplication SmileyApplication;
#endif /* __cplusplus */

#endif 	/* __SmileyApplication_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __SmileyUi_LIBRARY_DEFINED__
#define __SmileyUi_LIBRARY_DEFINED__

/* library SmileyUi */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SmileyUi;

#ifndef ___ISmileyApplicationEvents_DISPINTERFACE_DEFINED__
#define ___ISmileyApplicationEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISmileyApplicationEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ISmileyApplicationEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("066DA2A4-CC00-11D2-B585-0010A401A37F")
    _ISmileyApplicationEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISmileyApplicationEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ISmileyApplicationEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ISmileyApplicationEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ISmileyApplicationEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ISmileyApplicationEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ISmileyApplicationEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ISmileyApplicationEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ISmileyApplicationEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ISmileyApplicationEventsVtbl;

    interface _ISmileyApplicationEvents
    {
        CONST_VTBL struct _ISmileyApplicationEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISmileyApplicationEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ISmileyApplicationEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ISmileyApplicationEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ISmileyApplicationEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ISmileyApplicationEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ISmileyApplicationEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ISmileyApplicationEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISmileyApplicationEvents_DISPINTERFACE_DEFINED__ */


#ifndef __ISmileyApplication_INTERFACE_DEFINED__
#define __ISmileyApplication_INTERFACE_DEFINED__

/* interface ISmileyApplication */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISmileyApplication;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("066DA2A3-CC00-11D2-B585-0010A401A37F")
    ISmileyApplication : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateSmiley( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISmileyApplicationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISmileyApplication * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISmileyApplication * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISmileyApplication * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISmileyApplication * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISmileyApplication * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISmileyApplication * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISmileyApplication * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateSmiley )( 
            ISmileyApplication * This);
        
        END_INTERFACE
    } ISmileyApplicationVtbl;

    interface ISmileyApplication
    {
        CONST_VTBL struct ISmileyApplicationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISmileyApplication_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISmileyApplication_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISmileyApplication_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISmileyApplication_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISmileyApplication_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISmileyApplication_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISmileyApplication_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISmileyApplication_CreateSmiley(This)	\
    (This)->lpVtbl -> CreateSmiley(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISmileyApplication_CreateSmiley_Proxy( 
    ISmileyApplication * This);


void __RPC_STUB ISmileyApplication_CreateSmiley_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISmileyApplication_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SmileyApplication;

#ifdef __cplusplus

class DECLSPEC_UUID("88870444-C4D8-11D2-B579-0010A401A3C5")
SmileyApplication;
#endif
#endif /* __SmileyUi_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


