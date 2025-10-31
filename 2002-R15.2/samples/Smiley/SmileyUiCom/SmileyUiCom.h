/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Feb 28 12:28:20 2000
 */
/* Compiler settings for C:\ObjectARX 2000\Samples\Smiley\SmileyUiCom\SmileyUiCom.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
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

#ifdef __cplusplus
extern "C"{
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


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __AsdkSmileyUiComLib_LIBRARY_DEFINED__
#define __AsdkSmileyUiComLib_LIBRARY_DEFINED__

/* library AsdkSmileyUiComLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AsdkSmileyUiComLib;

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
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ISmileyApplicationEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ISmileyApplicationEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ISmileyApplicationEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ISmileyApplicationEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ISmileyApplicationEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ISmileyApplicationEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ISmileyApplicationEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ISmileyApplicationEventsVtbl;

    interface _ISmileyApplicationEvents
    {
        CONST_VTBL struct _ISmileyApplicationEventsVtbl __RPC_FAR *lpVtbl;
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
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISmileyApplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISmileyApplication __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISmileyApplication __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISmileyApplication __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISmileyApplication __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISmileyApplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISmileyApplication __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSmiley )( 
            ISmileyApplication __RPC_FAR * This);
        
        END_INTERFACE
    } ISmileyApplicationVtbl;

    interface ISmileyApplication
    {
        CONST_VTBL struct ISmileyApplicationVtbl __RPC_FAR *lpVtbl;
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
    ISmileyApplication __RPC_FAR * This);


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
#endif /* __AsdkSmileyUiComLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
