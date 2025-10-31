/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Mar 26 15:10:54 2001
 */
/* Compiler settings for D:\Autodesk\ObjectARX\Banff\samples\eTransmit\eTransmitNotifier.idl:
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

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __eTransmitNotifier_h__
#define __eTransmitNotifier_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAddFileHandler_FWD_DEFINED__
#define __IAddFileHandler_FWD_DEFINED__
typedef interface IAddFileHandler IAddFileHandler;
#endif 	/* __IAddFileHandler_FWD_DEFINED__ */


#ifndef __AddFileHandler_FWD_DEFINED__
#define __AddFileHandler_FWD_DEFINED__

#ifdef __cplusplus
typedef class AddFileHandler AddFileHandler;
#else
typedef struct AddFileHandler AddFileHandler;
#endif /* __cplusplus */

#endif 	/* __AddFileHandler_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAddFileHandler_INTERFACE_DEFINED__
#define __IAddFileHandler_INTERFACE_DEFINED__

/* interface IAddFileHandler */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAddFileHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("37A4DBE5-7031-11D4-845F-0010A4ECE8B9")
    IAddFileHandler : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAddFileHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAddFileHandler __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAddFileHandler __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAddFileHandler __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAddFileHandler __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAddFileHandler __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAddFileHandler __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAddFileHandler __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IAddFileHandlerVtbl;

    interface IAddFileHandler
    {
        CONST_VTBL struct IAddFileHandlerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAddFileHandler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAddFileHandler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAddFileHandler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAddFileHandler_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAddFileHandler_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAddFileHandler_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAddFileHandler_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAddFileHandler_INTERFACE_DEFINED__ */



#ifndef __AsdkETRANSMITNOTIFIERLib_LIBRARY_DEFINED__
#define __AsdkETRANSMITNOTIFIERLib_LIBRARY_DEFINED__

/* library AsdkETRANSMITNOTIFIERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AsdkETRANSMITNOTIFIERLib;

EXTERN_C const CLSID CLSID_AddFileHandler;

#ifdef __cplusplus

class DECLSPEC_UUID("37A4DBE6-7031-11D4-845F-0010A4ECE8B9")
AddFileHandler;
#endif
#endif /* __AsdkETRANSMITNOTIFIERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
