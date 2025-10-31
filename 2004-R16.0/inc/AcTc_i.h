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
/* at Tue Feb 04 00:56:47 2003
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

#ifndef __AcTc_i_h__
#define __AcTc_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAcadToolProperties_FWD_DEFINED__
#define __IAcadToolProperties_FWD_DEFINED__
typedef interface IAcadToolProperties IAcadToolProperties;
#endif 	/* __IAcadToolProperties_FWD_DEFINED__ */


#ifndef __IAcadStockTool_FWD_DEFINED__
#define __IAcadStockTool_FWD_DEFINED__
typedef interface IAcadStockTool IAcadStockTool;
#endif 	/* __IAcadStockTool_FWD_DEFINED__ */


#ifndef __IAcadTool_FWD_DEFINED__
#define __IAcadTool_FWD_DEFINED__
typedef interface IAcadTool IAcadTool;
#endif 	/* __IAcadTool_FWD_DEFINED__ */


#ifndef __IAcadToolDropTarget_FWD_DEFINED__
#define __IAcadToolDropTarget_FWD_DEFINED__
typedef interface IAcadToolDropTarget IAcadToolDropTarget;
#endif 	/* __IAcadToolDropTarget_FWD_DEFINED__ */


#ifndef __IAcadToolDragSource_FWD_DEFINED__
#define __IAcadToolDragSource_FWD_DEFINED__
typedef interface IAcadToolDragSource IAcadToolDragSource;
#endif 	/* __IAcadToolDragSource_FWD_DEFINED__ */


#ifndef __IAcadToolCopyPaste_FWD_DEFINED__
#define __IAcadToolCopyPaste_FWD_DEFINED__
typedef interface IAcadToolCopyPaste IAcadToolCopyPaste;
#endif 	/* __IAcadToolCopyPaste_FWD_DEFINED__ */


#ifndef __IAcadToolImage_FWD_DEFINED__
#define __IAcadToolImage_FWD_DEFINED__
typedef interface IAcadToolImage IAcadToolImage;
#endif 	/* __IAcadToolImage_FWD_DEFINED__ */


#ifndef __AcadToolProperties_FWD_DEFINED__
#define __AcadToolProperties_FWD_DEFINED__

#ifdef __cplusplus
typedef class AcadToolProperties AcadToolProperties;
#else
typedef struct AcadToolProperties AcadToolProperties;
#endif /* __cplusplus */

#endif 	/* __AcadToolProperties_FWD_DEFINED__ */


#ifndef __AcadToolImage_FWD_DEFINED__
#define __AcadToolImage_FWD_DEFINED__

#ifdef __cplusplus
typedef class AcadToolImage AcadToolImage;
#else
typedef struct AcadToolImage AcadToolImage;
#endif /* __cplusplus */

#endif 	/* __AcadToolImage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_AcTc_0000 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_AcTc_0000_0001
    {	kEditDefault	= 0,
	kEditCustom	= kEditDefault + 1,
	kEditNone	= kEditCustom + 1
    } 	ToolEditMode;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_AcTc_0000_0002
    {	kContextMenuPaletteTool	= 0,
	kContextMenuEditorImage	= kContextMenuPaletteTool + 1
    } 	ContextMenuFlag;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_AcTc_0000_0003
    {	kContextMenuShow	= 0,
	kContextMenuHide	= kContextMenuShow + 1,
	kExecutionCanceled	= kContextMenuHide + 1,
	kExecutionCancelRejected	= kExecutionCanceled + 1
    } 	ReturnFlag;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_AcTc_0000_0004
    {	kLButtonClicked	= 0,
	kDroppedInDrawing	= kLButtonClicked + 1
    } 	ExecutionContext;



extern RPC_IF_HANDLE __MIDL_itf_AcTc_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AcTc_0000_v0_0_s_ifspec;

#ifndef __IAcadToolProperties_INTERFACE_DEFINED__
#define __IAcadToolProperties_INTERFACE_DEFINED__

/* interface IAcadToolProperties */
/* [unique][custom][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8498A0F-A997-454B-AC19-9555139DFB10")
    IAcadToolProperties : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ GUID *pId) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ToolTipText( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ToolTipText( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HelpFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HelpFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HelpCommand( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HelpCommand( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HelpData( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HelpData( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsReadOnly( 
            /* [retval][out] */ VARIANT_BOOL *pReadOnly) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetImage( 
            /* [in] */ long cx,
            /* [in] */ long cy,
            /* [out] */ IUnknown **pVal,
            /* [out] */ BSTR *sResourceName,
            /* [out] */ BSTR *sSourceFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetImage( 
            /* [in] */ long cx,
            /* [in] */ long cy,
            /* [in] */ IUnknown *newVal,
            /* [in] */ BSTR sResourceName,
            /* [in] */ BSTR sSourceFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCustomData( 
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcadToolPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolProperties * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadToolProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadToolProperties * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAcadToolProperties * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAcadToolProperties * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAcadToolProperties * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAcadToolProperties * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IAcadToolProperties * This,
            /* [retval][out] */ GUID *pId);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IAcadToolProperties * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IAcadToolProperties * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IAcadToolProperties * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IAcadToolProperties * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ToolTipText )( 
            IAcadToolProperties * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ToolTipText )( 
            IAcadToolProperties * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HelpFile )( 
            IAcadToolProperties * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HelpFile )( 
            IAcadToolProperties * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HelpCommand )( 
            IAcadToolProperties * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HelpCommand )( 
            IAcadToolProperties * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HelpData )( 
            IAcadToolProperties * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HelpData )( 
            IAcadToolProperties * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsReadOnly )( 
            IAcadToolProperties * This,
            /* [retval][out] */ VARIANT_BOOL *pReadOnly);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetImage )( 
            IAcadToolProperties * This,
            /* [in] */ long cx,
            /* [in] */ long cy,
            /* [out] */ IUnknown **pVal,
            /* [out] */ BSTR *sResourceName,
            /* [out] */ BSTR *sSourceFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetImage )( 
            IAcadToolProperties * This,
            /* [in] */ long cx,
            /* [in] */ long cy,
            /* [in] */ IUnknown *newVal,
            /* [in] */ BSTR sResourceName,
            /* [in] */ BSTR sSourceFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCustomData )( 
            IAcadToolProperties * This,
            /* [retval][out] */ IUnknown **ppVal);
        
        END_INTERFACE
    } IAcadToolPropertiesVtbl;

    interface IAcadToolProperties
    {
        CONST_VTBL struct IAcadToolPropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcadToolProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcadToolProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcadToolProperties_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAcadToolProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAcadToolProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAcadToolProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAcadToolProperties_get_ID(This,pId)	\
    (This)->lpVtbl -> get_ID(This,pId)

#define IAcadToolProperties_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IAcadToolProperties_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IAcadToolProperties_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define IAcadToolProperties_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define IAcadToolProperties_get_ToolTipText(This,pVal)	\
    (This)->lpVtbl -> get_ToolTipText(This,pVal)

#define IAcadToolProperties_put_ToolTipText(This,newVal)	\
    (This)->lpVtbl -> put_ToolTipText(This,newVal)

#define IAcadToolProperties_get_HelpFile(This,pVal)	\
    (This)->lpVtbl -> get_HelpFile(This,pVal)

#define IAcadToolProperties_put_HelpFile(This,newVal)	\
    (This)->lpVtbl -> put_HelpFile(This,newVal)

#define IAcadToolProperties_get_HelpCommand(This,pVal)	\
    (This)->lpVtbl -> get_HelpCommand(This,pVal)

#define IAcadToolProperties_put_HelpCommand(This,newVal)	\
    (This)->lpVtbl -> put_HelpCommand(This,newVal)

#define IAcadToolProperties_get_HelpData(This,pVal)	\
    (This)->lpVtbl -> get_HelpData(This,pVal)

#define IAcadToolProperties_put_HelpData(This,newVal)	\
    (This)->lpVtbl -> put_HelpData(This,newVal)

#define IAcadToolProperties_get_IsReadOnly(This,pReadOnly)	\
    (This)->lpVtbl -> get_IsReadOnly(This,pReadOnly)

#define IAcadToolProperties_GetImage(This,cx,cy,pVal,sResourceName,sSourceFile)	\
    (This)->lpVtbl -> GetImage(This,cx,cy,pVal,sResourceName,sSourceFile)

#define IAcadToolProperties_SetImage(This,cx,cy,newVal,sResourceName,sSourceFile)	\
    (This)->lpVtbl -> SetImage(This,cx,cy,newVal,sResourceName,sSourceFile)

#define IAcadToolProperties_GetCustomData(This,ppVal)	\
    (This)->lpVtbl -> GetCustomData(This,ppVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_get_ID_Proxy( 
    IAcadToolProperties * This,
    /* [retval][out] */ GUID *pId);


void __RPC_STUB IAcadToolProperties_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_get_Name_Proxy( 
    IAcadToolProperties * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IAcadToolProperties_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_put_Name_Proxy( 
    IAcadToolProperties * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IAcadToolProperties_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_get_Description_Proxy( 
    IAcadToolProperties * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IAcadToolProperties_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_put_Description_Proxy( 
    IAcadToolProperties * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IAcadToolProperties_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_get_ToolTipText_Proxy( 
    IAcadToolProperties * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IAcadToolProperties_get_ToolTipText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_put_ToolTipText_Proxy( 
    IAcadToolProperties * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IAcadToolProperties_put_ToolTipText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_get_HelpFile_Proxy( 
    IAcadToolProperties * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IAcadToolProperties_get_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_put_HelpFile_Proxy( 
    IAcadToolProperties * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IAcadToolProperties_put_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_get_HelpCommand_Proxy( 
    IAcadToolProperties * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IAcadToolProperties_get_HelpCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_put_HelpCommand_Proxy( 
    IAcadToolProperties * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IAcadToolProperties_put_HelpCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_get_HelpData_Proxy( 
    IAcadToolProperties * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IAcadToolProperties_get_HelpData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_put_HelpData_Proxy( 
    IAcadToolProperties * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IAcadToolProperties_put_HelpData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_get_IsReadOnly_Proxy( 
    IAcadToolProperties * This,
    /* [retval][out] */ VARIANT_BOOL *pReadOnly);


void __RPC_STUB IAcadToolProperties_get_IsReadOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_GetImage_Proxy( 
    IAcadToolProperties * This,
    /* [in] */ long cx,
    /* [in] */ long cy,
    /* [out] */ IUnknown **pVal,
    /* [out] */ BSTR *sResourceName,
    /* [out] */ BSTR *sSourceFile);


void __RPC_STUB IAcadToolProperties_GetImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_SetImage_Proxy( 
    IAcadToolProperties * This,
    /* [in] */ long cx,
    /* [in] */ long cy,
    /* [in] */ IUnknown *newVal,
    /* [in] */ BSTR sResourceName,
    /* [in] */ BSTR sSourceFile);


void __RPC_STUB IAcadToolProperties_SetImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolProperties_GetCustomData_Proxy( 
    IAcadToolProperties * This,
    /* [retval][out] */ IUnknown **ppVal);


void __RPC_STUB IAcadToolProperties_GetCustomData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcadToolProperties_INTERFACE_DEFINED__ */


#ifndef __IAcadStockTool_INTERFACE_DEFINED__
#define __IAcadStockTool_INTERFACE_DEFINED__

/* interface IAcadStockTool */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadStockTool;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F3D70D77-8B79-4277-99E4-704E4C17DC6E")
    IAcadStockTool : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateTool( 
            /* [retval][out] */ IUnknown **ppTool) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcadStockToolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadStockTool * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadStockTool * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadStockTool * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTool )( 
            IAcadStockTool * This,
            /* [retval][out] */ IUnknown **ppTool);
        
        END_INTERFACE
    } IAcadStockToolVtbl;

    interface IAcadStockTool
    {
        CONST_VTBL struct IAcadStockToolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadStockTool_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcadStockTool_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcadStockTool_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcadStockTool_CreateTool(This,ppTool)	\
    (This)->lpVtbl -> CreateTool(This,ppTool)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadStockTool_CreateTool_Proxy( 
    IAcadStockTool * This,
    /* [retval][out] */ IUnknown **ppTool);


void __RPC_STUB IAcadStockTool_CreateTool_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcadStockTool_INTERFACE_DEFINED__ */


#ifndef __IAcadTool_INTERFACE_DEFINED__
#define __IAcadTool_INTERFACE_DEFINED__

/* interface IAcadTool */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadTool;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7B064668-E0BE-4fdf-9322-DC484024878F")
    IAcadTool : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EditMode( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStockTool( 
            /* [retval][out] */ IUnknown **ppToolClass) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetToolProperties( 
            /* [in] */ IUnknown *pProp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ IUnknown *pXmlElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ IUnknown *pXmlElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Execute( 
            /* [in] */ long lFlag,
            /* [in] */ DWORD hWnd,
            /* [in] */ DWORD point,
            /* [in] */ DWORD dwKeyState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetData( 
            /* [in] */ VARIANT *pObjUnkArray,
            /* [in] */ VARIANT *pDynUnkArray) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BeginEdit( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Edit( 
            /* [in] */ IUnknown *pProp,
            /* [in] */ LONG hWndParent,
            /* [out] */ VARIANT_BOOL *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EndEdit( 
            /* [in] */ VARIANT_BOOL bEditCancelled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE New( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDropTarget( 
            /* [retval][out] */ IUnknown **ppDropTarget) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetContextMenu( 
            /* [in] */ int nContextFlag,
            /* [in] */ DWORD hMenu,
            /* [in] */ UINT idCmdFirst,
            /* [in] */ UINT idCmdLast,
            /* [retval][out] */ DWORD *pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCommandString( 
            /* [in] */ UINT idCmd,
            /* [retval][out] */ BSTR *pbstrHelpText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeCommand( 
            /* [in] */ UINT idCmd,
            /* [in] */ DWORD hWnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDragDropContextInfo( 
            /* [in] */ IUnknown *pIUnknown,
            /* [out] */ BSTR *pbstrText,
            /* [out] */ DWORD *pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Dropped( 
            /* [in] */ BSTR bstrUrl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refreshed( 
            /* [in] */ BSTR bstrUrl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEditorWindow( 
            /* [in] */ LONG hWndEditor,
            /* [in] */ IUnknown *pPropInspector) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ValidateEditChanges( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetToolProperties( 
            /* [retval][out] */ IUnknown **pToolProp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcadToolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadTool * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadTool * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadTool * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EditMode )( 
            IAcadTool * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetStockTool )( 
            IAcadTool * This,
            /* [retval][out] */ IUnknown **ppToolClass);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetToolProperties )( 
            IAcadTool * This,
            /* [in] */ IUnknown *pProp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IAcadTool * This,
            /* [in] */ IUnknown *pXmlElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IAcadTool * This,
            /* [in] */ IUnknown *pXmlElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Execute )( 
            IAcadTool * This,
            /* [in] */ long lFlag,
            /* [in] */ DWORD hWnd,
            /* [in] */ DWORD point,
            /* [in] */ DWORD dwKeyState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetData )( 
            IAcadTool * This,
            /* [in] */ VARIANT *pObjUnkArray,
            /* [in] */ VARIANT *pDynUnkArray);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BeginEdit )( 
            IAcadTool * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Edit )( 
            IAcadTool * This,
            /* [in] */ IUnknown *pProp,
            /* [in] */ LONG hWndParent,
            /* [out] */ VARIANT_BOOL *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EndEdit )( 
            IAcadTool * This,
            /* [in] */ VARIANT_BOOL bEditCancelled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *New )( 
            IAcadTool * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDropTarget )( 
            IAcadTool * This,
            /* [retval][out] */ IUnknown **ppDropTarget);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetContextMenu )( 
            IAcadTool * This,
            /* [in] */ int nContextFlag,
            /* [in] */ DWORD hMenu,
            /* [in] */ UINT idCmdFirst,
            /* [in] */ UINT idCmdLast,
            /* [retval][out] */ DWORD *pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCommandString )( 
            IAcadTool * This,
            /* [in] */ UINT idCmd,
            /* [retval][out] */ BSTR *pbstrHelpText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InvokeCommand )( 
            IAcadTool * This,
            /* [in] */ UINT idCmd,
            /* [in] */ DWORD hWnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDragDropContextInfo )( 
            IAcadTool * This,
            /* [in] */ IUnknown *pIUnknown,
            /* [out] */ BSTR *pbstrText,
            /* [out] */ DWORD *pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Dropped )( 
            IAcadTool * This,
            /* [in] */ BSTR bstrUrl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refreshed )( 
            IAcadTool * This,
            /* [in] */ BSTR bstrUrl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEditorWindow )( 
            IAcadTool * This,
            /* [in] */ LONG hWndEditor,
            /* [in] */ IUnknown *pPropInspector);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ValidateEditChanges )( 
            IAcadTool * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetToolProperties )( 
            IAcadTool * This,
            /* [retval][out] */ IUnknown **pToolProp);
        
        END_INTERFACE
    } IAcadToolVtbl;

    interface IAcadTool
    {
        CONST_VTBL struct IAcadToolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadTool_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcadTool_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcadTool_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcadTool_get_EditMode(This,pVal)	\
    (This)->lpVtbl -> get_EditMode(This,pVal)

#define IAcadTool_GetStockTool(This,ppToolClass)	\
    (This)->lpVtbl -> GetStockTool(This,ppToolClass)

#define IAcadTool_SetToolProperties(This,pProp)	\
    (This)->lpVtbl -> SetToolProperties(This,pProp)

#define IAcadTool_Load(This,pXmlElement)	\
    (This)->lpVtbl -> Load(This,pXmlElement)

#define IAcadTool_Save(This,pXmlElement)	\
    (This)->lpVtbl -> Save(This,pXmlElement)

#define IAcadTool_Execute(This,lFlag,hWnd,point,dwKeyState)	\
    (This)->lpVtbl -> Execute(This,lFlag,hWnd,point,dwKeyState)

#define IAcadTool_GetData(This,pObjUnkArray,pDynUnkArray)	\
    (This)->lpVtbl -> GetData(This,pObjUnkArray,pDynUnkArray)

#define IAcadTool_BeginEdit(This)	\
    (This)->lpVtbl -> BeginEdit(This)

#define IAcadTool_Edit(This,pProp,hWndParent,pRet)	\
    (This)->lpVtbl -> Edit(This,pProp,hWndParent,pRet)

#define IAcadTool_EndEdit(This,bEditCancelled)	\
    (This)->lpVtbl -> EndEdit(This,bEditCancelled)

#define IAcadTool_New(This)	\
    (This)->lpVtbl -> New(This)

#define IAcadTool_GetDropTarget(This,ppDropTarget)	\
    (This)->lpVtbl -> GetDropTarget(This,ppDropTarget)

#define IAcadTool_GetContextMenu(This,nContextFlag,hMenu,idCmdFirst,idCmdLast,pFlag)	\
    (This)->lpVtbl -> GetContextMenu(This,nContextFlag,hMenu,idCmdFirst,idCmdLast,pFlag)

#define IAcadTool_GetCommandString(This,idCmd,pbstrHelpText)	\
    (This)->lpVtbl -> GetCommandString(This,idCmd,pbstrHelpText)

#define IAcadTool_InvokeCommand(This,idCmd,hWnd)	\
    (This)->lpVtbl -> InvokeCommand(This,idCmd,hWnd)

#define IAcadTool_GetDragDropContextInfo(This,pIUnknown,pbstrText,pFlag)	\
    (This)->lpVtbl -> GetDragDropContextInfo(This,pIUnknown,pbstrText,pFlag)

#define IAcadTool_Dropped(This,bstrUrl)	\
    (This)->lpVtbl -> Dropped(This,bstrUrl)

#define IAcadTool_Refreshed(This,bstrUrl)	\
    (This)->lpVtbl -> Refreshed(This,bstrUrl)

#define IAcadTool_SetEditorWindow(This,hWndEditor,pPropInspector)	\
    (This)->lpVtbl -> SetEditorWindow(This,hWndEditor,pPropInspector)

#define IAcadTool_ValidateEditChanges(This)	\
    (This)->lpVtbl -> ValidateEditChanges(This)

#define IAcadTool_GetToolProperties(This,pToolProp)	\
    (This)->lpVtbl -> GetToolProperties(This,pToolProp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcadTool_get_EditMode_Proxy( 
    IAcadTool * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IAcadTool_get_EditMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_GetStockTool_Proxy( 
    IAcadTool * This,
    /* [retval][out] */ IUnknown **ppToolClass);


void __RPC_STUB IAcadTool_GetStockTool_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_SetToolProperties_Proxy( 
    IAcadTool * This,
    /* [in] */ IUnknown *pProp);


void __RPC_STUB IAcadTool_SetToolProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_Load_Proxy( 
    IAcadTool * This,
    /* [in] */ IUnknown *pXmlElement);


void __RPC_STUB IAcadTool_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_Save_Proxy( 
    IAcadTool * This,
    /* [in] */ IUnknown *pXmlElement);


void __RPC_STUB IAcadTool_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_Execute_Proxy( 
    IAcadTool * This,
    /* [in] */ long lFlag,
    /* [in] */ DWORD hWnd,
    /* [in] */ DWORD point,
    /* [in] */ DWORD dwKeyState);


void __RPC_STUB IAcadTool_Execute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_GetData_Proxy( 
    IAcadTool * This,
    /* [in] */ VARIANT *pObjUnkArray,
    /* [in] */ VARIANT *pDynUnkArray);


void __RPC_STUB IAcadTool_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_BeginEdit_Proxy( 
    IAcadTool * This);


void __RPC_STUB IAcadTool_BeginEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_Edit_Proxy( 
    IAcadTool * This,
    /* [in] */ IUnknown *pProp,
    /* [in] */ LONG hWndParent,
    /* [out] */ VARIANT_BOOL *pRet);


void __RPC_STUB IAcadTool_Edit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_EndEdit_Proxy( 
    IAcadTool * This,
    /* [in] */ VARIANT_BOOL bEditCancelled);


void __RPC_STUB IAcadTool_EndEdit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_New_Proxy( 
    IAcadTool * This);


void __RPC_STUB IAcadTool_New_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_GetDropTarget_Proxy( 
    IAcadTool * This,
    /* [retval][out] */ IUnknown **ppDropTarget);


void __RPC_STUB IAcadTool_GetDropTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_GetContextMenu_Proxy( 
    IAcadTool * This,
    /* [in] */ int nContextFlag,
    /* [in] */ DWORD hMenu,
    /* [in] */ UINT idCmdFirst,
    /* [in] */ UINT idCmdLast,
    /* [retval][out] */ DWORD *pFlag);


void __RPC_STUB IAcadTool_GetContextMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_GetCommandString_Proxy( 
    IAcadTool * This,
    /* [in] */ UINT idCmd,
    /* [retval][out] */ BSTR *pbstrHelpText);


void __RPC_STUB IAcadTool_GetCommandString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_InvokeCommand_Proxy( 
    IAcadTool * This,
    /* [in] */ UINT idCmd,
    /* [in] */ DWORD hWnd);


void __RPC_STUB IAcadTool_InvokeCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_GetDragDropContextInfo_Proxy( 
    IAcadTool * This,
    /* [in] */ IUnknown *pIUnknown,
    /* [out] */ BSTR *pbstrText,
    /* [out] */ DWORD *pFlag);


void __RPC_STUB IAcadTool_GetDragDropContextInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_Dropped_Proxy( 
    IAcadTool * This,
    /* [in] */ BSTR bstrUrl);


void __RPC_STUB IAcadTool_Dropped_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_Refreshed_Proxy( 
    IAcadTool * This,
    /* [in] */ BSTR bstrUrl);


void __RPC_STUB IAcadTool_Refreshed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_SetEditorWindow_Proxy( 
    IAcadTool * This,
    /* [in] */ LONG hWndEditor,
    /* [in] */ IUnknown *pPropInspector);


void __RPC_STUB IAcadTool_SetEditorWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_ValidateEditChanges_Proxy( 
    IAcadTool * This);


void __RPC_STUB IAcadTool_ValidateEditChanges_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadTool_GetToolProperties_Proxy( 
    IAcadTool * This,
    /* [retval][out] */ IUnknown **pToolProp);


void __RPC_STUB IAcadTool_GetToolProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcadTool_INTERFACE_DEFINED__ */


#ifndef __IAcadToolDropTarget_INTERFACE_DEFINED__
#define __IAcadToolDropTarget_INTERFACE_DEFINED__

/* interface IAcadToolDropTarget */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolDropTarget;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6FE6AD02-DDE9-4619-A77A-05A183D613AD")
    IAcadToolDropTarget : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DragEnter( 
            /* [in] */ IDataObject *pDataObj,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [out][in] */ DWORD *pdwEffect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DragOver( 
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [out][in] */ DWORD *pdwEffect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DragLeave( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Drop( 
            /* [in] */ IDataObject *pDataObj,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [out][in] */ DWORD *pdwEffect,
            /* [in] */ GUID *pCurrentStockToolId,
            /* [in] */ GUID *pParentId,
            /* [retval][out] */ VARIANT *pNewToolIds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDragDropContextMenuItem( 
            /* [in] */ IUnknown *pIUnknown,
            /* [out] */ BSTR *pbstrText,
            /* [out] */ DWORD *pFlag) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcadToolDropTargetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolDropTarget * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadToolDropTarget * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadToolDropTarget * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DragEnter )( 
            IAcadToolDropTarget * This,
            /* [in] */ IDataObject *pDataObj,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [out][in] */ DWORD *pdwEffect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DragOver )( 
            IAcadToolDropTarget * This,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [out][in] */ DWORD *pdwEffect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DragLeave )( 
            IAcadToolDropTarget * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Drop )( 
            IAcadToolDropTarget * This,
            /* [in] */ IDataObject *pDataObj,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [out][in] */ DWORD *pdwEffect,
            /* [in] */ GUID *pCurrentStockToolId,
            /* [in] */ GUID *pParentId,
            /* [retval][out] */ VARIANT *pNewToolIds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDragDropContextMenuItem )( 
            IAcadToolDropTarget * This,
            /* [in] */ IUnknown *pIUnknown,
            /* [out] */ BSTR *pbstrText,
            /* [out] */ DWORD *pFlag);
        
        END_INTERFACE
    } IAcadToolDropTargetVtbl;

    interface IAcadToolDropTarget
    {
        CONST_VTBL struct IAcadToolDropTargetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolDropTarget_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcadToolDropTarget_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcadToolDropTarget_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcadToolDropTarget_DragEnter(This,pDataObj,grfKeyState,pt,pdwEffect)	\
    (This)->lpVtbl -> DragEnter(This,pDataObj,grfKeyState,pt,pdwEffect)

#define IAcadToolDropTarget_DragOver(This,grfKeyState,pt,pdwEffect)	\
    (This)->lpVtbl -> DragOver(This,grfKeyState,pt,pdwEffect)

#define IAcadToolDropTarget_DragLeave(This)	\
    (This)->lpVtbl -> DragLeave(This)

#define IAcadToolDropTarget_Drop(This,pDataObj,grfKeyState,pt,pdwEffect,pCurrentStockToolId,pParentId,pNewToolIds)	\
    (This)->lpVtbl -> Drop(This,pDataObj,grfKeyState,pt,pdwEffect,pCurrentStockToolId,pParentId,pNewToolIds)

#define IAcadToolDropTarget_GetDragDropContextMenuItem(This,pIUnknown,pbstrText,pFlag)	\
    (This)->lpVtbl -> GetDragDropContextMenuItem(This,pIUnknown,pbstrText,pFlag)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDropTarget_DragEnter_Proxy( 
    IAcadToolDropTarget * This,
    /* [in] */ IDataObject *pDataObj,
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [out][in] */ DWORD *pdwEffect);


void __RPC_STUB IAcadToolDropTarget_DragEnter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDropTarget_DragOver_Proxy( 
    IAcadToolDropTarget * This,
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [out][in] */ DWORD *pdwEffect);


void __RPC_STUB IAcadToolDropTarget_DragOver_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDropTarget_DragLeave_Proxy( 
    IAcadToolDropTarget * This);


void __RPC_STUB IAcadToolDropTarget_DragLeave_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDropTarget_Drop_Proxy( 
    IAcadToolDropTarget * This,
    /* [in] */ IDataObject *pDataObj,
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [out][in] */ DWORD *pdwEffect,
    /* [in] */ GUID *pCurrentStockToolId,
    /* [in] */ GUID *pParentId,
    /* [retval][out] */ VARIANT *pNewToolIds);


void __RPC_STUB IAcadToolDropTarget_Drop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDropTarget_GetDragDropContextMenuItem_Proxy( 
    IAcadToolDropTarget * This,
    /* [in] */ IUnknown *pIUnknown,
    /* [out] */ BSTR *pbstrText,
    /* [out] */ DWORD *pFlag);


void __RPC_STUB IAcadToolDropTarget_GetDragDropContextMenuItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcadToolDropTarget_INTERFACE_DEFINED__ */


#ifndef __IAcadToolDragSource_INTERFACE_DEFINED__
#define __IAcadToolDragSource_INTERFACE_DEFINED__

/* interface IAcadToolDragSource */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolDragSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74A34F77-8C7B-4a43-B3A8-D5BBFBC1F40C")
    IAcadToolDragSource : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BeginDrag( 
            /* [in] */ VARIANT *pToolIds,
            /* [in] */ VARIANT *pAllStockToolIds,
            /* [in] */ GUID *pCurrentStockToolId,
            /* [in] */ IDataObject *pDataObject,
            /* [in] */ DWORD dwKeyState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DragInProgress( 
            /* [in] */ DWORD dwDropEffect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EndDrag( 
            /* [in] */ DWORD dwDropEffect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DragEnterDrawing( 
            /* [in] */ IDataObject *pDataObject,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [retval][out] */ DWORD *pDropEffect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DragOverDrawing( 
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [retval][out] */ DWORD *pDropEffect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DragLeaveDrawing( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DropInDrawing( 
            /* [in] */ IDataObject *pDataObject,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [retval][out] */ DWORD *pDropEffect) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcadToolDragSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolDragSource * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadToolDragSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadToolDragSource * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BeginDrag )( 
            IAcadToolDragSource * This,
            /* [in] */ VARIANT *pToolIds,
            /* [in] */ VARIANT *pAllStockToolIds,
            /* [in] */ GUID *pCurrentStockToolId,
            /* [in] */ IDataObject *pDataObject,
            /* [in] */ DWORD dwKeyState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DragInProgress )( 
            IAcadToolDragSource * This,
            /* [in] */ DWORD dwDropEffect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EndDrag )( 
            IAcadToolDragSource * This,
            /* [in] */ DWORD dwDropEffect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DragEnterDrawing )( 
            IAcadToolDragSource * This,
            /* [in] */ IDataObject *pDataObject,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [retval][out] */ DWORD *pDropEffect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DragOverDrawing )( 
            IAcadToolDragSource * This,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [retval][out] */ DWORD *pDropEffect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DragLeaveDrawing )( 
            IAcadToolDragSource * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DropInDrawing )( 
            IAcadToolDragSource * This,
            /* [in] */ IDataObject *pDataObject,
            /* [in] */ DWORD grfKeyState,
            /* [in] */ POINTL pt,
            /* [retval][out] */ DWORD *pDropEffect);
        
        END_INTERFACE
    } IAcadToolDragSourceVtbl;

    interface IAcadToolDragSource
    {
        CONST_VTBL struct IAcadToolDragSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolDragSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcadToolDragSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcadToolDragSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcadToolDragSource_BeginDrag(This,pToolIds,pAllStockToolIds,pCurrentStockToolId,pDataObject,dwKeyState)	\
    (This)->lpVtbl -> BeginDrag(This,pToolIds,pAllStockToolIds,pCurrentStockToolId,pDataObject,dwKeyState)

#define IAcadToolDragSource_DragInProgress(This,dwDropEffect)	\
    (This)->lpVtbl -> DragInProgress(This,dwDropEffect)

#define IAcadToolDragSource_EndDrag(This,dwDropEffect)	\
    (This)->lpVtbl -> EndDrag(This,dwDropEffect)

#define IAcadToolDragSource_DragEnterDrawing(This,pDataObject,grfKeyState,pt,pDropEffect)	\
    (This)->lpVtbl -> DragEnterDrawing(This,pDataObject,grfKeyState,pt,pDropEffect)

#define IAcadToolDragSource_DragOverDrawing(This,grfKeyState,pt,pDropEffect)	\
    (This)->lpVtbl -> DragOverDrawing(This,grfKeyState,pt,pDropEffect)

#define IAcadToolDragSource_DragLeaveDrawing(This)	\
    (This)->lpVtbl -> DragLeaveDrawing(This)

#define IAcadToolDragSource_DropInDrawing(This,pDataObject,grfKeyState,pt,pDropEffect)	\
    (This)->lpVtbl -> DropInDrawing(This,pDataObject,grfKeyState,pt,pDropEffect)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDragSource_BeginDrag_Proxy( 
    IAcadToolDragSource * This,
    /* [in] */ VARIANT *pToolIds,
    /* [in] */ VARIANT *pAllStockToolIds,
    /* [in] */ GUID *pCurrentStockToolId,
    /* [in] */ IDataObject *pDataObject,
    /* [in] */ DWORD dwKeyState);


void __RPC_STUB IAcadToolDragSource_BeginDrag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDragSource_DragInProgress_Proxy( 
    IAcadToolDragSource * This,
    /* [in] */ DWORD dwDropEffect);


void __RPC_STUB IAcadToolDragSource_DragInProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDragSource_EndDrag_Proxy( 
    IAcadToolDragSource * This,
    /* [in] */ DWORD dwDropEffect);


void __RPC_STUB IAcadToolDragSource_EndDrag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDragSource_DragEnterDrawing_Proxy( 
    IAcadToolDragSource * This,
    /* [in] */ IDataObject *pDataObject,
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [retval][out] */ DWORD *pDropEffect);


void __RPC_STUB IAcadToolDragSource_DragEnterDrawing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDragSource_DragOverDrawing_Proxy( 
    IAcadToolDragSource * This,
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [retval][out] */ DWORD *pDropEffect);


void __RPC_STUB IAcadToolDragSource_DragOverDrawing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDragSource_DragLeaveDrawing_Proxy( 
    IAcadToolDragSource * This);


void __RPC_STUB IAcadToolDragSource_DragLeaveDrawing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolDragSource_DropInDrawing_Proxy( 
    IAcadToolDragSource * This,
    /* [in] */ IDataObject *pDataObject,
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [retval][out] */ DWORD *pDropEffect);


void __RPC_STUB IAcadToolDragSource_DropInDrawing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcadToolDragSource_INTERFACE_DEFINED__ */


#ifndef __IAcadToolCopyPaste_INTERFACE_DEFINED__
#define __IAcadToolCopyPaste_INTERFACE_DEFINED__

/* interface IAcadToolCopyPaste */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolCopyPaste;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E1F1CB3B-5FC6-4eb8-86DD-AF0CFAFE6B00")
    IAcadToolCopyPaste : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Copy( 
            /* [in] */ VARIANT *pToolIds,
            /* [in] */ VARIANT *pAllStockToolIds,
            /* [in] */ GUID *pCurrentStockToolId,
            /* [in] */ IDataObject *pDataObject) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Paste( 
            /* [in] */ GUID *pCurrentStockToolId,
            /* [in] */ GUID *pParentId,
            /* [in] */ IDataObject *pDataObject,
            /* [retval][out] */ VARIANT *pNewToolIds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CanPaste( 
            /* [in] */ IDataObject *pDataObject,
            /* [retval][out] */ VARIANT_BOOL *pCanPaste) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcadToolCopyPasteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolCopyPaste * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadToolCopyPaste * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadToolCopyPaste * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Copy )( 
            IAcadToolCopyPaste * This,
            /* [in] */ VARIANT *pToolIds,
            /* [in] */ VARIANT *pAllStockToolIds,
            /* [in] */ GUID *pCurrentStockToolId,
            /* [in] */ IDataObject *pDataObject);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Paste )( 
            IAcadToolCopyPaste * This,
            /* [in] */ GUID *pCurrentStockToolId,
            /* [in] */ GUID *pParentId,
            /* [in] */ IDataObject *pDataObject,
            /* [retval][out] */ VARIANT *pNewToolIds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CanPaste )( 
            IAcadToolCopyPaste * This,
            /* [in] */ IDataObject *pDataObject,
            /* [retval][out] */ VARIANT_BOOL *pCanPaste);
        
        END_INTERFACE
    } IAcadToolCopyPasteVtbl;

    interface IAcadToolCopyPaste
    {
        CONST_VTBL struct IAcadToolCopyPasteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolCopyPaste_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcadToolCopyPaste_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcadToolCopyPaste_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcadToolCopyPaste_Copy(This,pToolIds,pAllStockToolIds,pCurrentStockToolId,pDataObject)	\
    (This)->lpVtbl -> Copy(This,pToolIds,pAllStockToolIds,pCurrentStockToolId,pDataObject)

#define IAcadToolCopyPaste_Paste(This,pCurrentStockToolId,pParentId,pDataObject,pNewToolIds)	\
    (This)->lpVtbl -> Paste(This,pCurrentStockToolId,pParentId,pDataObject,pNewToolIds)

#define IAcadToolCopyPaste_CanPaste(This,pDataObject,pCanPaste)	\
    (This)->lpVtbl -> CanPaste(This,pDataObject,pCanPaste)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolCopyPaste_Copy_Proxy( 
    IAcadToolCopyPaste * This,
    /* [in] */ VARIANT *pToolIds,
    /* [in] */ VARIANT *pAllStockToolIds,
    /* [in] */ GUID *pCurrentStockToolId,
    /* [in] */ IDataObject *pDataObject);


void __RPC_STUB IAcadToolCopyPaste_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolCopyPaste_Paste_Proxy( 
    IAcadToolCopyPaste * This,
    /* [in] */ GUID *pCurrentStockToolId,
    /* [in] */ GUID *pParentId,
    /* [in] */ IDataObject *pDataObject,
    /* [retval][out] */ VARIANT *pNewToolIds);


void __RPC_STUB IAcadToolCopyPaste_Paste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolCopyPaste_CanPaste_Proxy( 
    IAcadToolCopyPaste * This,
    /* [in] */ IDataObject *pDataObject,
    /* [retval][out] */ VARIANT_BOOL *pCanPaste);


void __RPC_STUB IAcadToolCopyPaste_CanPaste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcadToolCopyPaste_INTERFACE_DEFINED__ */


#ifndef __IAcadToolImage_INTERFACE_DEFINED__
#define __IAcadToolImage_INTERFACE_DEFINED__

/* interface IAcadToolImage */
/* [local][custom][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BE67D23E-E36A-11D5-B4E5-00B0D03E954A")
    IAcadToolImage : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ BSTR bsFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ BSTR bsFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Render( 
            /* [in] */ HDC hdc,
            /* [in] */ long x,
            /* [in] */ long y,
            /* [in] */ long cx,
            /* [in] */ long cy,
            /* [in] */ long nStyle,
            /* [in] */ VARIANT_BOOL bTransparentBitmap) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSize( 
            /* [out] */ long *pWidth,
            /* [out] */ long *pHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetType( 
            /* [out] */ short *pType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsImageLoaded( 
            /* [out] */ BOOL *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcadToolImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolImage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadToolImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadToolImage * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IAcadToolImage * This,
            /* [in] */ BSTR bsFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IAcadToolImage * This,
            /* [in] */ BSTR bsFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Render )( 
            IAcadToolImage * This,
            /* [in] */ HDC hdc,
            /* [in] */ long x,
            /* [in] */ long y,
            /* [in] */ long cx,
            /* [in] */ long cy,
            /* [in] */ long nStyle,
            /* [in] */ VARIANT_BOOL bTransparentBitmap);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSize )( 
            IAcadToolImage * This,
            /* [out] */ long *pWidth,
            /* [out] */ long *pHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetType )( 
            IAcadToolImage * This,
            /* [out] */ short *pType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsImageLoaded )( 
            IAcadToolImage * This,
            /* [out] */ BOOL *pVal);
        
        END_INTERFACE
    } IAcadToolImageVtbl;

    interface IAcadToolImage
    {
        CONST_VTBL struct IAcadToolImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolImage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcadToolImage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcadToolImage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcadToolImage_Load(This,bsFileName)	\
    (This)->lpVtbl -> Load(This,bsFileName)

#define IAcadToolImage_Save(This,bsFileName)	\
    (This)->lpVtbl -> Save(This,bsFileName)

#define IAcadToolImage_Render(This,hdc,x,y,cx,cy,nStyle,bTransparentBitmap)	\
    (This)->lpVtbl -> Render(This,hdc,x,y,cx,cy,nStyle,bTransparentBitmap)

#define IAcadToolImage_GetSize(This,pWidth,pHeight)	\
    (This)->lpVtbl -> GetSize(This,pWidth,pHeight)

#define IAcadToolImage_GetType(This,pType)	\
    (This)->lpVtbl -> GetType(This,pType)

#define IAcadToolImage_IsImageLoaded(This,pVal)	\
    (This)->lpVtbl -> IsImageLoaded(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolImage_Load_Proxy( 
    IAcadToolImage * This,
    /* [in] */ BSTR bsFileName);


void __RPC_STUB IAcadToolImage_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolImage_Save_Proxy( 
    IAcadToolImage * This,
    /* [in] */ BSTR bsFileName);


void __RPC_STUB IAcadToolImage_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolImage_Render_Proxy( 
    IAcadToolImage * This,
    /* [in] */ HDC hdc,
    /* [in] */ long x,
    /* [in] */ long y,
    /* [in] */ long cx,
    /* [in] */ long cy,
    /* [in] */ long nStyle,
    /* [in] */ VARIANT_BOOL bTransparentBitmap);


void __RPC_STUB IAcadToolImage_Render_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolImage_GetSize_Proxy( 
    IAcadToolImage * This,
    /* [out] */ long *pWidth,
    /* [out] */ long *pHeight);


void __RPC_STUB IAcadToolImage_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolImage_GetType_Proxy( 
    IAcadToolImage * This,
    /* [out] */ short *pType);


void __RPC_STUB IAcadToolImage_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcadToolImage_IsImageLoaded_Proxy( 
    IAcadToolImage * This,
    /* [out] */ BOOL *pVal);


void __RPC_STUB IAcadToolImage_IsImageLoaded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcadToolImage_INTERFACE_DEFINED__ */



#ifndef __AcTcLib_LIBRARY_DEFINED__
#define __AcTcLib_LIBRARY_DEFINED__

/* library AcTcLib */
/* [helpstring][custom][version][uuid] */ 


EXTERN_C const IID LIBID_AcTcLib;

EXTERN_C const CLSID CLSID_AcadToolProperties;

#ifdef __cplusplus

class DECLSPEC_UUID("497C8B53-E920-4450-8DD8-D73F83CB8F0F")
AcadToolProperties;
#endif

EXTERN_C const CLSID CLSID_AcadToolImage;

#ifdef __cplusplus

class DECLSPEC_UUID("BE67D23F-E36A-11D5-B4E5-00B0D03E954A")
AcadToolImage;
#endif
#endif /* __AcTcLib_LIBRARY_DEFINED__ */

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


