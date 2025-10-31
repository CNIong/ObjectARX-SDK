//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////



/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

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


#ifndef __IAcadToolProperties2_FWD_DEFINED__
#define __IAcadToolProperties2_FWD_DEFINED__
typedef interface IAcadToolProperties2 IAcadToolProperties2;

#endif 	/* __IAcadToolProperties2_FWD_DEFINED__ */


#ifndef __IAcadToolProperties3_FWD_DEFINED__
#define __IAcadToolProperties3_FWD_DEFINED__
typedef interface IAcadToolProperties3 IAcadToolProperties3;

#endif 	/* __IAcadToolProperties3_FWD_DEFINED__ */


#ifndef __IAcadStockTool_FWD_DEFINED__
#define __IAcadStockTool_FWD_DEFINED__
typedef interface IAcadStockTool IAcadStockTool;

#endif 	/* __IAcadStockTool_FWD_DEFINED__ */


#ifndef __IAcadToolContextMenu_FWD_DEFINED__
#define __IAcadToolContextMenu_FWD_DEFINED__
typedef interface IAcadToolContextMenu IAcadToolContextMenu;

#endif 	/* __IAcadToolContextMenu_FWD_DEFINED__ */


#ifndef __IAcadTool_FWD_DEFINED__
#define __IAcadTool_FWD_DEFINED__
typedef interface IAcadTool IAcadTool;

#endif 	/* __IAcadTool_FWD_DEFINED__ */


#ifndef __IAcadTool2_FWD_DEFINED__
#define __IAcadTool2_FWD_DEFINED__
typedef interface IAcadTool2 IAcadTool2;

#endif 	/* __IAcadTool2_FWD_DEFINED__ */


#ifndef __IAcadToolFlyoutShape_FWD_DEFINED__
#define __IAcadToolFlyoutShape_FWD_DEFINED__
typedef interface IAcadToolFlyoutShape IAcadToolFlyoutShape;

#endif 	/* __IAcadToolFlyoutShape_FWD_DEFINED__ */


#ifndef __IAcadToolSort_FWD_DEFINED__
#define __IAcadToolSort_FWD_DEFINED__
typedef interface IAcadToolSort IAcadToolSort;

#endif 	/* __IAcadToolSort_FWD_DEFINED__ */


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


/* interface __MIDL_itf_AcTc_0000_0000 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_AcTc_0000_0000_0001
    {
        kEditDefault	= 0,
        kEditCustom	= ( kEditDefault + 1 ) ,
        kEditNone	= ( kEditCustom + 1 ) ,
        kEditMultiple	= 0x4
    } 	ToolEditMode;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_AcTc_0000_0000_0002
    {
        kContextNone	= -1,
        kContextMenuPaletteTool	= ( kContextNone + 1 ) ,
        kContextMenuEditorImage	= ( kContextMenuPaletteTool + 1 ) ,
        kContextMenuPaletteBackground	= ( kContextMenuEditorImage + 1 ) ,
        kContextMenuPaletteSetTab	= ( kContextMenuPaletteBackground + 1 ) ,
        kContextMenuPaletteSetCaption	= ( kContextMenuPaletteSetTab + 1 ) ,
        kContextMenuPaletteSetOptionButton	= ( kContextMenuPaletteSetCaption + 1 ) 
    } 	ContextMenuFlag;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_AcTc_0000_0000_0003
    {
        kContextMenuShow	= 0,
        kContextMenuHide	= ( kContextMenuShow + 1 ) ,
        kExecutionCanceled	= ( kContextMenuHide + 1 ) ,
        kExecutionCancelRejected	= ( kExecutionCanceled + 1 ) ,
        kContextMenuUpdatePalette	= ( kExecutionCancelRejected + 1 ) 
    } 	ReturnFlag;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_AcTc_0000_0000_0004
    {
        kLButtonClicked	= 0,
        kDroppedInDrawing	= ( kLButtonClicked + 1 ) 
    } 	ExecutionContext;



extern RPC_IF_HANDLE __MIDL_itf_AcTc_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AcTc_0000_0000_v0_0_s_ifspec;

#ifndef __IAcadToolProperties_INTERFACE_DEFINED__
#define __IAcadToolProperties_INTERFACE_DEFINED__

/* interface IAcadToolProperties */
/* [unique][custom][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C7D10438-330C-461D-9DC0-C2D31F746D37")
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
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ToolType( 
            /* [retval][out] */ LONG *pToolType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ToolType( 
            /* [in] */ LONG lToolType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsFlyoutEnabled( 
            /* [retval][out] */ VARIANT_BOOL *pEnabled) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsFlyoutEnabled( 
            /* [in] */ VARIANT_BOOL bUseFlyout) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShapePackageId( 
            /* [retval][out] */ GUID *pId) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShapePackageId( 
            /* [in] */ GUID *pId) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentShapeId( 
            /* [retval][out] */ GUID *pId) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentShapeId( 
            /* [in] */ GUID *pId) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ActiveShapeIds( 
            /* [retval][out] */ VARIANT *pShapes) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ActiveShapeIds( 
            /* [in] */ VARIANT *pShapes) = 0;
        
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
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCurrentShape( 
            /* [out] */ IUnknown **ppTool) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOverlayImage( 
            /* [out] */ IUnknown **pVal,
            /* [out] */ BSTR *pResourceName,
            /* [out] */ BSTR *pSourceFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOverlayImage( 
            /* [in] */ IUnknown *newVal,
            /* [in] */ BSTR sResourceName,
            /* [in] */ BSTR sSourceFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAcTcTool( 
            /* [retval][out] */ DWORD_PTR *ppAcTcTool) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcadToolPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolProperties * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAcadToolProperties * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
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
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ToolType )( 
            IAcadToolProperties * This,
            /* [retval][out] */ LONG *pToolType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ToolType )( 
            IAcadToolProperties * This,
            /* [in] */ LONG lToolType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsFlyoutEnabled )( 
            IAcadToolProperties * This,
            /* [retval][out] */ VARIANT_BOOL *pEnabled);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsFlyoutEnabled )( 
            IAcadToolProperties * This,
            /* [in] */ VARIANT_BOOL bUseFlyout);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShapePackageId )( 
            IAcadToolProperties * This,
            /* [retval][out] */ GUID *pId);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ShapePackageId )( 
            IAcadToolProperties * This,
            /* [in] */ GUID *pId);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentShapeId )( 
            IAcadToolProperties * This,
            /* [retval][out] */ GUID *pId);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CurrentShapeId )( 
            IAcadToolProperties * This,
            /* [in] */ GUID *pId);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActiveShapeIds )( 
            IAcadToolProperties * This,
            /* [retval][out] */ VARIANT *pShapes);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ActiveShapeIds )( 
            IAcadToolProperties * This,
            /* [in] */ VARIANT *pShapes);
        
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCurrentShape )( 
            IAcadToolProperties * This,
            /* [out] */ IUnknown **ppTool);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOverlayImage )( 
            IAcadToolProperties * This,
            /* [out] */ IUnknown **pVal,
            /* [out] */ BSTR *pResourceName,
            /* [out] */ BSTR *pSourceFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetOverlayImage )( 
            IAcadToolProperties * This,
            /* [in] */ IUnknown *newVal,
            /* [in] */ BSTR sResourceName,
            /* [in] */ BSTR sSourceFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAcTcTool )( 
            IAcadToolProperties * This,
            /* [retval][out] */ DWORD_PTR *ppAcTcTool);
        
        END_INTERFACE
    } IAcadToolPropertiesVtbl;

    interface IAcadToolProperties
    {
        CONST_VTBL struct IAcadToolPropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolProperties_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadToolProperties_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadToolProperties_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadToolProperties_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAcadToolProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAcadToolProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAcadToolProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAcadToolProperties_get_ID(This,pId)	\
    ( (This)->lpVtbl -> get_ID(This,pId) ) 

#define IAcadToolProperties_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IAcadToolProperties_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IAcadToolProperties_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define IAcadToolProperties_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define IAcadToolProperties_get_ToolTipText(This,pVal)	\
    ( (This)->lpVtbl -> get_ToolTipText(This,pVal) ) 

#define IAcadToolProperties_put_ToolTipText(This,newVal)	\
    ( (This)->lpVtbl -> put_ToolTipText(This,newVal) ) 

#define IAcadToolProperties_get_HelpFile(This,pVal)	\
    ( (This)->lpVtbl -> get_HelpFile(This,pVal) ) 

#define IAcadToolProperties_put_HelpFile(This,newVal)	\
    ( (This)->lpVtbl -> put_HelpFile(This,newVal) ) 

#define IAcadToolProperties_get_HelpCommand(This,pVal)	\
    ( (This)->lpVtbl -> get_HelpCommand(This,pVal) ) 

#define IAcadToolProperties_put_HelpCommand(This,newVal)	\
    ( (This)->lpVtbl -> put_HelpCommand(This,newVal) ) 

#define IAcadToolProperties_get_HelpData(This,pVal)	\
    ( (This)->lpVtbl -> get_HelpData(This,pVal) ) 

#define IAcadToolProperties_put_HelpData(This,newVal)	\
    ( (This)->lpVtbl -> put_HelpData(This,newVal) ) 

#define IAcadToolProperties_get_IsReadOnly(This,pReadOnly)	\
    ( (This)->lpVtbl -> get_IsReadOnly(This,pReadOnly) ) 

#define IAcadToolProperties_get_ToolType(This,pToolType)	\
    ( (This)->lpVtbl -> get_ToolType(This,pToolType) ) 

#define IAcadToolProperties_put_ToolType(This,lToolType)	\
    ( (This)->lpVtbl -> put_ToolType(This,lToolType) ) 

#define IAcadToolProperties_get_IsFlyoutEnabled(This,pEnabled)	\
    ( (This)->lpVtbl -> get_IsFlyoutEnabled(This,pEnabled) ) 

#define IAcadToolProperties_put_IsFlyoutEnabled(This,bUseFlyout)	\
    ( (This)->lpVtbl -> put_IsFlyoutEnabled(This,bUseFlyout) ) 

#define IAcadToolProperties_get_ShapePackageId(This,pId)	\
    ( (This)->lpVtbl -> get_ShapePackageId(This,pId) ) 

#define IAcadToolProperties_put_ShapePackageId(This,pId)	\
    ( (This)->lpVtbl -> put_ShapePackageId(This,pId) ) 

#define IAcadToolProperties_get_CurrentShapeId(This,pId)	\
    ( (This)->lpVtbl -> get_CurrentShapeId(This,pId) ) 

#define IAcadToolProperties_put_CurrentShapeId(This,pId)	\
    ( (This)->lpVtbl -> put_CurrentShapeId(This,pId) ) 

#define IAcadToolProperties_get_ActiveShapeIds(This,pShapes)	\
    ( (This)->lpVtbl -> get_ActiveShapeIds(This,pShapes) ) 

#define IAcadToolProperties_put_ActiveShapeIds(This,pShapes)	\
    ( (This)->lpVtbl -> put_ActiveShapeIds(This,pShapes) ) 

#define IAcadToolProperties_GetImage(This,cx,cy,pVal,sResourceName,sSourceFile)	\
    ( (This)->lpVtbl -> GetImage(This,cx,cy,pVal,sResourceName,sSourceFile) ) 

#define IAcadToolProperties_SetImage(This,cx,cy,newVal,sResourceName,sSourceFile)	\
    ( (This)->lpVtbl -> SetImage(This,cx,cy,newVal,sResourceName,sSourceFile) ) 

#define IAcadToolProperties_GetCustomData(This,ppVal)	\
    ( (This)->lpVtbl -> GetCustomData(This,ppVal) ) 

#define IAcadToolProperties_GetCurrentShape(This,ppTool)	\
    ( (This)->lpVtbl -> GetCurrentShape(This,ppTool) ) 

#define IAcadToolProperties_GetOverlayImage(This,pVal,pResourceName,pSourceFile)	\
    ( (This)->lpVtbl -> GetOverlayImage(This,pVal,pResourceName,pSourceFile) ) 

#define IAcadToolProperties_SetOverlayImage(This,newVal,sResourceName,sSourceFile)	\
    ( (This)->lpVtbl -> SetOverlayImage(This,newVal,sResourceName,sSourceFile) ) 

#define IAcadToolProperties_GetAcTcTool(This,ppAcTcTool)	\
    ( (This)->lpVtbl -> GetAcTcTool(This,ppAcTcTool) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadToolProperties_INTERFACE_DEFINED__ */


#ifndef __IAcadToolProperties2_INTERFACE_DEFINED__
#define __IAcadToolProperties2_INTERFACE_DEFINED__

/* interface IAcadToolProperties2 */
/* [unique][custom][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolProperties2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A0E6B0E3-09FB-4E3C-B134-5EDD05CBAB37")
    IAcadToolProperties2 : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ItemOption( 
            /* [retval][out] */ LONG *pItemOption) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ItemOption( 
            /* [in] */ LONG lItemOption) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageOption( 
            /* [retval][out] */ LONG *pImageOption) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImageOption( 
            /* [in] */ LONG lImageOption) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcadToolProperties2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolProperties2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadToolProperties2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadToolProperties2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAcadToolProperties2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAcadToolProperties2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAcadToolProperties2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAcadToolProperties2 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ItemOption )( 
            IAcadToolProperties2 * This,
            /* [retval][out] */ LONG *pItemOption);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ItemOption )( 
            IAcadToolProperties2 * This,
            /* [in] */ LONG lItemOption);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageOption )( 
            IAcadToolProperties2 * This,
            /* [retval][out] */ LONG *pImageOption);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageOption )( 
            IAcadToolProperties2 * This,
            /* [in] */ LONG lImageOption);
        
        END_INTERFACE
    } IAcadToolProperties2Vtbl;

    interface IAcadToolProperties2
    {
        CONST_VTBL struct IAcadToolProperties2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolProperties2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadToolProperties2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadToolProperties2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadToolProperties2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAcadToolProperties2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAcadToolProperties2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAcadToolProperties2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAcadToolProperties2_get_ItemOption(This,pItemOption)	\
    ( (This)->lpVtbl -> get_ItemOption(This,pItemOption) ) 

#define IAcadToolProperties2_put_ItemOption(This,lItemOption)	\
    ( (This)->lpVtbl -> put_ItemOption(This,lItemOption) ) 

#define IAcadToolProperties2_get_ImageOption(This,pImageOption)	\
    ( (This)->lpVtbl -> get_ImageOption(This,pImageOption) ) 

#define IAcadToolProperties2_put_ImageOption(This,lImageOption)	\
    ( (This)->lpVtbl -> put_ImageOption(This,lImageOption) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadToolProperties2_INTERFACE_DEFINED__ */


#ifndef __IAcadToolProperties3_INTERFACE_DEFINED__
#define __IAcadToolProperties3_INTERFACE_DEFINED__

/* interface IAcadToolProperties3 */
/* [unique][custom][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolProperties3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F1800037-CB71-47BB-8C06-C4F3C5336316")
    IAcadToolProperties3 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDarkImage( 
            /* [in] */ long cx,
            /* [in] */ long cy,
            /* [out] */ IUnknown **pVal,
            /* [out] */ BSTR *sResourceName,
            /* [out] */ BSTR *sSourceFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDarkImage( 
            /* [in] */ long cx,
            /* [in] */ long cy,
            /* [in] */ IUnknown *newVal,
            /* [in] */ BSTR sResourceName,
            /* [in] */ BSTR sSourceFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDarkOverlayImage( 
            /* [out] */ IUnknown **pVal,
            /* [out] */ BSTR *pResourceName,
            /* [out] */ BSTR *pSourceFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDarkOverlayImage( 
            /* [in] */ IUnknown *newVal,
            /* [in] */ BSTR sResourceName,
            /* [in] */ BSTR sSourceFile) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcadToolProperties3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolProperties3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadToolProperties3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadToolProperties3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAcadToolProperties3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAcadToolProperties3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAcadToolProperties3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAcadToolProperties3 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDarkImage )( 
            IAcadToolProperties3 * This,
            /* [in] */ long cx,
            /* [in] */ long cy,
            /* [out] */ IUnknown **pVal,
            /* [out] */ BSTR *sResourceName,
            /* [out] */ BSTR *sSourceFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDarkImage )( 
            IAcadToolProperties3 * This,
            /* [in] */ long cx,
            /* [in] */ long cy,
            /* [in] */ IUnknown *newVal,
            /* [in] */ BSTR sResourceName,
            /* [in] */ BSTR sSourceFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDarkOverlayImage )( 
            IAcadToolProperties3 * This,
            /* [out] */ IUnknown **pVal,
            /* [out] */ BSTR *pResourceName,
            /* [out] */ BSTR *pSourceFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDarkOverlayImage )( 
            IAcadToolProperties3 * This,
            /* [in] */ IUnknown *newVal,
            /* [in] */ BSTR sResourceName,
            /* [in] */ BSTR sSourceFile);
        
        END_INTERFACE
    } IAcadToolProperties3Vtbl;

    interface IAcadToolProperties3
    {
        CONST_VTBL struct IAcadToolProperties3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolProperties3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadToolProperties3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadToolProperties3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadToolProperties3_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAcadToolProperties3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAcadToolProperties3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAcadToolProperties3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAcadToolProperties3_GetDarkImage(This,cx,cy,pVal,sResourceName,sSourceFile)	\
    ( (This)->lpVtbl -> GetDarkImage(This,cx,cy,pVal,sResourceName,sSourceFile) ) 

#define IAcadToolProperties3_SetDarkImage(This,cx,cy,newVal,sResourceName,sSourceFile)	\
    ( (This)->lpVtbl -> SetDarkImage(This,cx,cy,newVal,sResourceName,sSourceFile) ) 

#define IAcadToolProperties3_GetDarkOverlayImage(This,pVal,pResourceName,pSourceFile)	\
    ( (This)->lpVtbl -> GetDarkOverlayImage(This,pVal,pResourceName,pSourceFile) ) 

#define IAcadToolProperties3_SetDarkOverlayImage(This,newVal,sResourceName,sSourceFile)	\
    ( (This)->lpVtbl -> SetDarkOverlayImage(This,newVal,sResourceName,sSourceFile) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadToolProperties3_INTERFACE_DEFINED__ */


#ifndef __IAcadStockTool_INTERFACE_DEFINED__
#define __IAcadStockTool_INTERFACE_DEFINED__

/* interface IAcadStockTool */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadStockTool;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B9A18560-C006-4F2D-8E22-FF55389DABEB")
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
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadStockTool_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadStockTool_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadStockTool_CreateTool(This,ppTool)	\
    ( (This)->lpVtbl -> CreateTool(This,ppTool) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadStockTool_INTERFACE_DEFINED__ */


#ifndef __IAcadToolContextMenu_INTERFACE_DEFINED__
#define __IAcadToolContextMenu_INTERFACE_DEFINED__

/* interface IAcadToolContextMenu */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolContextMenu;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C717E8F3-14C7-4D64-B442-72876DE32510")
    IAcadToolContextMenu : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Customize( 
            /* [in] */ int nContextFlag,
            /* [in] */ DWORD_PTR hMenu,
            /* [in] */ UINT idCmdFirst,
            /* [in] */ UINT idCmdLast,
            /* [in] */ GUID *pPaletteId,
            /* [retval][out] */ DWORD *pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMenuHelp( 
            /* [in] */ UINT idCmd,
            /* [retval][out] */ BSTR *pbstrHelpText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeMenuCommand( 
            /* [in] */ UINT idCmd,
            /* [in] */ GUID *pPaletteId,
            /* [in] */ DWORD_PTR hWnd,
            /* [retval][out] */ DWORD *pFlag) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcadToolContextMenuVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolContextMenu * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadToolContextMenu * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadToolContextMenu * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Customize )( 
            IAcadToolContextMenu * This,
            /* [in] */ int nContextFlag,
            /* [in] */ DWORD_PTR hMenu,
            /* [in] */ UINT idCmdFirst,
            /* [in] */ UINT idCmdLast,
            /* [in] */ GUID *pPaletteId,
            /* [retval][out] */ DWORD *pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMenuHelp )( 
            IAcadToolContextMenu * This,
            /* [in] */ UINT idCmd,
            /* [retval][out] */ BSTR *pbstrHelpText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InvokeMenuCommand )( 
            IAcadToolContextMenu * This,
            /* [in] */ UINT idCmd,
            /* [in] */ GUID *pPaletteId,
            /* [in] */ DWORD_PTR hWnd,
            /* [retval][out] */ DWORD *pFlag);
        
        END_INTERFACE
    } IAcadToolContextMenuVtbl;

    interface IAcadToolContextMenu
    {
        CONST_VTBL struct IAcadToolContextMenuVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolContextMenu_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadToolContextMenu_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadToolContextMenu_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadToolContextMenu_Customize(This,nContextFlag,hMenu,idCmdFirst,idCmdLast,pPaletteId,pFlag)	\
    ( (This)->lpVtbl -> Customize(This,nContextFlag,hMenu,idCmdFirst,idCmdLast,pPaletteId,pFlag) ) 

#define IAcadToolContextMenu_GetMenuHelp(This,idCmd,pbstrHelpText)	\
    ( (This)->lpVtbl -> GetMenuHelp(This,idCmd,pbstrHelpText) ) 

#define IAcadToolContextMenu_InvokeMenuCommand(This,idCmd,pPaletteId,hWnd,pFlag)	\
    ( (This)->lpVtbl -> InvokeMenuCommand(This,idCmd,pPaletteId,hWnd,pFlag) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadToolContextMenu_INTERFACE_DEFINED__ */


#ifndef __IAcadTool_INTERFACE_DEFINED__
#define __IAcadTool_INTERFACE_DEFINED__

/* interface IAcadTool */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadTool;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4909ACC0-3574-4867-A120-543FB288E5F9")
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
            /* [in] */ LONG_PTR lFlag,
            /* [in] */ DWORD_PTR hWnd,
            /* [in] */ DWORD point,
            /* [in] */ DWORD dwKeyState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetData( 
            /* [in] */ VARIANT *pObjUnkArray,
            /* [in] */ VARIANT *pDynUnkArray) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BeginEdit( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Edit( 
            /* [in] */ IUnknown *pProp,
            /* [in] */ LONG_PTR hWndParent,
            /* [out] */ VARIANT_BOOL *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EndEdit( 
            /* [in] */ VARIANT_BOOL bEditCancelled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE New( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDropTarget( 
            /* [retval][out] */ IUnknown **ppDropTarget) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetContextMenu( 
            /* [in] */ INT_PTR nContextFlag,
            /* [in] */ DWORD_PTR hMenu,
            /* [in] */ UINT idCmdFirst,
            /* [in] */ UINT idCmdLast,
            /* [retval][out] */ DWORD_PTR *pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCommandString( 
            /* [in] */ UINT idCmd,
            /* [retval][out] */ BSTR *pbstrHelpText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeCommand( 
            /* [in] */ UINT idCmd,
            /* [in] */ DWORD_PTR hWnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDragDropContextInfo( 
            /* [in] */ IUnknown *pIUnknown,
            /* [out] */ BSTR *pbstrText,
            /* [out] */ DWORD *pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Dropped( 
            /* [in] */ BSTR bstrUrl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refreshed( 
            /* [in] */ BSTR bstrUrl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEditorWindow( 
            /* [in] */ LONG_PTR hWndEditor,
            /* [in] */ IUnknown *pPropInspector) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ValidateEditChanges( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetToolProperties( 
            /* [retval][out] */ IUnknown **pToolProp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BeginMultipleEdit( 
            /* [in] */ VARIANT tools,
            /* [in] */ VARIANT stockToolIds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EndMultipleEdit( 
            /* [in] */ VARIANT tools,
            /* [in] */ VARIANT stockToolIds,
            /* [in] */ VARIANT_BOOL bEditCancelled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MultipleEdit( 
            /* [in] */ VARIANT tools,
            /* [in] */ VARIANT stockToolIds,
            /* [in] */ LONG_PTR hWndParent,
            /* [out] */ VARIANT_BOOL *pRet) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcadToolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadTool * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
            /* [in] */ LONG_PTR lFlag,
            /* [in] */ DWORD_PTR hWnd,
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
            /* [in] */ LONG_PTR hWndParent,
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
            /* [in] */ INT_PTR nContextFlag,
            /* [in] */ DWORD_PTR hMenu,
            /* [in] */ UINT idCmdFirst,
            /* [in] */ UINT idCmdLast,
            /* [retval][out] */ DWORD_PTR *pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCommandString )( 
            IAcadTool * This,
            /* [in] */ UINT idCmd,
            /* [retval][out] */ BSTR *pbstrHelpText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InvokeCommand )( 
            IAcadTool * This,
            /* [in] */ UINT idCmd,
            /* [in] */ DWORD_PTR hWnd);
        
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
            /* [in] */ LONG_PTR hWndEditor,
            /* [in] */ IUnknown *pPropInspector);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ValidateEditChanges )( 
            IAcadTool * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetToolProperties )( 
            IAcadTool * This,
            /* [retval][out] */ IUnknown **pToolProp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BeginMultipleEdit )( 
            IAcadTool * This,
            /* [in] */ VARIANT tools,
            /* [in] */ VARIANT stockToolIds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EndMultipleEdit )( 
            IAcadTool * This,
            /* [in] */ VARIANT tools,
            /* [in] */ VARIANT stockToolIds,
            /* [in] */ VARIANT_BOOL bEditCancelled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MultipleEdit )( 
            IAcadTool * This,
            /* [in] */ VARIANT tools,
            /* [in] */ VARIANT stockToolIds,
            /* [in] */ LONG_PTR hWndParent,
            /* [out] */ VARIANT_BOOL *pRet);
        
        END_INTERFACE
    } IAcadToolVtbl;

    interface IAcadTool
    {
        CONST_VTBL struct IAcadToolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadTool_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadTool_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadTool_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadTool_get_EditMode(This,pVal)	\
    ( (This)->lpVtbl -> get_EditMode(This,pVal) ) 

#define IAcadTool_GetStockTool(This,ppToolClass)	\
    ( (This)->lpVtbl -> GetStockTool(This,ppToolClass) ) 

#define IAcadTool_SetToolProperties(This,pProp)	\
    ( (This)->lpVtbl -> SetToolProperties(This,pProp) ) 

#define IAcadTool_Load(This,pXmlElement)	\
    ( (This)->lpVtbl -> Load(This,pXmlElement) ) 

#define IAcadTool_Save(This,pXmlElement)	\
    ( (This)->lpVtbl -> Save(This,pXmlElement) ) 

#define IAcadTool_Execute(This,lFlag,hWnd,point,dwKeyState)	\
    ( (This)->lpVtbl -> Execute(This,lFlag,hWnd,point,dwKeyState) ) 

#define IAcadTool_GetData(This,pObjUnkArray,pDynUnkArray)	\
    ( (This)->lpVtbl -> GetData(This,pObjUnkArray,pDynUnkArray) ) 

#define IAcadTool_BeginEdit(This)	\
    ( (This)->lpVtbl -> BeginEdit(This) ) 

#define IAcadTool_Edit(This,pProp,hWndParent,pRet)	\
    ( (This)->lpVtbl -> Edit(This,pProp,hWndParent,pRet) ) 

#define IAcadTool_EndEdit(This,bEditCancelled)	\
    ( (This)->lpVtbl -> EndEdit(This,bEditCancelled) ) 

#define IAcadTool_New(This)	\
    ( (This)->lpVtbl -> New(This) ) 

#define IAcadTool_GetDropTarget(This,ppDropTarget)	\
    ( (This)->lpVtbl -> GetDropTarget(This,ppDropTarget) ) 

#define IAcadTool_GetContextMenu(This,nContextFlag,hMenu,idCmdFirst,idCmdLast,pFlag)	\
    ( (This)->lpVtbl -> GetContextMenu(This,nContextFlag,hMenu,idCmdFirst,idCmdLast,pFlag) ) 

#define IAcadTool_GetCommandString(This,idCmd,pbstrHelpText)	\
    ( (This)->lpVtbl -> GetCommandString(This,idCmd,pbstrHelpText) ) 

#define IAcadTool_InvokeCommand(This,idCmd,hWnd)	\
    ( (This)->lpVtbl -> InvokeCommand(This,idCmd,hWnd) ) 

#define IAcadTool_GetDragDropContextInfo(This,pIUnknown,pbstrText,pFlag)	\
    ( (This)->lpVtbl -> GetDragDropContextInfo(This,pIUnknown,pbstrText,pFlag) ) 

#define IAcadTool_Dropped(This,bstrUrl)	\
    ( (This)->lpVtbl -> Dropped(This,bstrUrl) ) 

#define IAcadTool_Refreshed(This,bstrUrl)	\
    ( (This)->lpVtbl -> Refreshed(This,bstrUrl) ) 

#define IAcadTool_SetEditorWindow(This,hWndEditor,pPropInspector)	\
    ( (This)->lpVtbl -> SetEditorWindow(This,hWndEditor,pPropInspector) ) 

#define IAcadTool_ValidateEditChanges(This)	\
    ( (This)->lpVtbl -> ValidateEditChanges(This) ) 

#define IAcadTool_GetToolProperties(This,pToolProp)	\
    ( (This)->lpVtbl -> GetToolProperties(This,pToolProp) ) 

#define IAcadTool_BeginMultipleEdit(This,tools,stockToolIds)	\
    ( (This)->lpVtbl -> BeginMultipleEdit(This,tools,stockToolIds) ) 

#define IAcadTool_EndMultipleEdit(This,tools,stockToolIds,bEditCancelled)	\
    ( (This)->lpVtbl -> EndMultipleEdit(This,tools,stockToolIds,bEditCancelled) ) 

#define IAcadTool_MultipleEdit(This,tools,stockToolIds,hWndParent,pRet)	\
    ( (This)->lpVtbl -> MultipleEdit(This,tools,stockToolIds,hWndParent,pRet) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadTool_INTERFACE_DEFINED__ */


#ifndef __IAcadTool2_INTERFACE_DEFINED__
#define __IAcadTool2_INTERFACE_DEFINED__

/* interface IAcadTool2 */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadTool2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CB0E3669-222E-46AB-9DD0-9876E6D052AD")
    IAcadTool2 : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateImage( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcadTool2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadTool2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadTool2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadTool2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateImage )( 
            IAcadTool2 * This);
        
        END_INTERFACE
    } IAcadTool2Vtbl;

    interface IAcadTool2
    {
        CONST_VTBL struct IAcadTool2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadTool2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadTool2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadTool2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadTool2_UpdateImage(This)	\
    ( (This)->lpVtbl -> UpdateImage(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadTool2_INTERFACE_DEFINED__ */


#ifndef __IAcadToolFlyoutShape_INTERFACE_DEFINED__
#define __IAcadToolFlyoutShape_INTERFACE_DEFINED__

/* interface IAcadToolFlyoutShape */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolFlyoutShape;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2F1A2EE9-32C3-489A-A29E-08851FC927DA")
    IAcadToolFlyoutShape : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFlyoutTools( 
            /* [in] */ VARIANT *pFlyoutToolIds) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcadToolFlyoutShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolFlyoutShape * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadToolFlyoutShape * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadToolFlyoutShape * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFlyoutTools )( 
            IAcadToolFlyoutShape * This,
            /* [in] */ VARIANT *pFlyoutToolIds);
        
        END_INTERFACE
    } IAcadToolFlyoutShapeVtbl;

    interface IAcadToolFlyoutShape
    {
        CONST_VTBL struct IAcadToolFlyoutShapeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolFlyoutShape_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadToolFlyoutShape_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadToolFlyoutShape_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadToolFlyoutShape_SetFlyoutTools(This,pFlyoutToolIds)	\
    ( (This)->lpVtbl -> SetFlyoutTools(This,pFlyoutToolIds) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadToolFlyoutShape_INTERFACE_DEFINED__ */


#ifndef __IAcadToolSort_INTERFACE_DEFINED__
#define __IAcadToolSort_INTERFACE_DEFINED__

/* interface IAcadToolSort */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolSort;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF6D759E-0EDD-46DF-9E0B-8DC01A206CF7")
    IAcadToolSort : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Compare( 
            /* [in] */ IUnknown *pTool,
            /* [in] */ long lSortOption,
            /* [retval][out] */ long *pResult) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcadToolSortVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcadToolSort * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcadToolSort * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcadToolSort * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Compare )( 
            IAcadToolSort * This,
            /* [in] */ IUnknown *pTool,
            /* [in] */ long lSortOption,
            /* [retval][out] */ long *pResult);
        
        END_INTERFACE
    } IAcadToolSortVtbl;

    interface IAcadToolSort
    {
        CONST_VTBL struct IAcadToolSortVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadToolSort_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadToolSort_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadToolSort_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadToolSort_Compare(This,pTool,lSortOption,pResult)	\
    ( (This)->lpVtbl -> Compare(This,pTool,lSortOption,pResult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadToolSort_INTERFACE_DEFINED__ */


#ifndef __IAcadToolDropTarget_INTERFACE_DEFINED__
#define __IAcadToolDropTarget_INTERFACE_DEFINED__

/* interface IAcadToolDropTarget */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolDropTarget;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("76B9A439-B3BF-4346-8001-74EBFAD3113A")
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
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadToolDropTarget_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadToolDropTarget_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadToolDropTarget_DragEnter(This,pDataObj,grfKeyState,pt,pdwEffect)	\
    ( (This)->lpVtbl -> DragEnter(This,pDataObj,grfKeyState,pt,pdwEffect) ) 

#define IAcadToolDropTarget_DragOver(This,grfKeyState,pt,pdwEffect)	\
    ( (This)->lpVtbl -> DragOver(This,grfKeyState,pt,pdwEffect) ) 

#define IAcadToolDropTarget_DragLeave(This)	\
    ( (This)->lpVtbl -> DragLeave(This) ) 

#define IAcadToolDropTarget_Drop(This,pDataObj,grfKeyState,pt,pdwEffect,pCurrentStockToolId,pParentId,pNewToolIds)	\
    ( (This)->lpVtbl -> Drop(This,pDataObj,grfKeyState,pt,pdwEffect,pCurrentStockToolId,pParentId,pNewToolIds) ) 

#define IAcadToolDropTarget_GetDragDropContextMenuItem(This,pIUnknown,pbstrText,pFlag)	\
    ( (This)->lpVtbl -> GetDragDropContextMenuItem(This,pIUnknown,pbstrText,pFlag) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadToolDropTarget_INTERFACE_DEFINED__ */


#ifndef __IAcadToolDragSource_INTERFACE_DEFINED__
#define __IAcadToolDragSource_INTERFACE_DEFINED__

/* interface IAcadToolDragSource */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolDragSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8C6D2B1-A430-4949-8F5A-FF3C3533CF00")
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
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadToolDragSource_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadToolDragSource_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadToolDragSource_BeginDrag(This,pToolIds,pAllStockToolIds,pCurrentStockToolId,pDataObject,dwKeyState)	\
    ( (This)->lpVtbl -> BeginDrag(This,pToolIds,pAllStockToolIds,pCurrentStockToolId,pDataObject,dwKeyState) ) 

#define IAcadToolDragSource_DragInProgress(This,dwDropEffect)	\
    ( (This)->lpVtbl -> DragInProgress(This,dwDropEffect) ) 

#define IAcadToolDragSource_EndDrag(This,dwDropEffect)	\
    ( (This)->lpVtbl -> EndDrag(This,dwDropEffect) ) 

#define IAcadToolDragSource_DragEnterDrawing(This,pDataObject,grfKeyState,pt,pDropEffect)	\
    ( (This)->lpVtbl -> DragEnterDrawing(This,pDataObject,grfKeyState,pt,pDropEffect) ) 

#define IAcadToolDragSource_DragOverDrawing(This,grfKeyState,pt,pDropEffect)	\
    ( (This)->lpVtbl -> DragOverDrawing(This,grfKeyState,pt,pDropEffect) ) 

#define IAcadToolDragSource_DragLeaveDrawing(This)	\
    ( (This)->lpVtbl -> DragLeaveDrawing(This) ) 

#define IAcadToolDragSource_DropInDrawing(This,pDataObject,grfKeyState,pt,pDropEffect)	\
    ( (This)->lpVtbl -> DropInDrawing(This,pDataObject,grfKeyState,pt,pDropEffect) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadToolDragSource_INTERFACE_DEFINED__ */


#ifndef __IAcadToolCopyPaste_INTERFACE_DEFINED__
#define __IAcadToolCopyPaste_INTERFACE_DEFINED__

/* interface IAcadToolCopyPaste */
/* [oleautomation][custom][local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolCopyPaste;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5E32FE25-7769-4C8E-9447-DB921D1D249E")
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
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadToolCopyPaste_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadToolCopyPaste_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadToolCopyPaste_Copy(This,pToolIds,pAllStockToolIds,pCurrentStockToolId,pDataObject)	\
    ( (This)->lpVtbl -> Copy(This,pToolIds,pAllStockToolIds,pCurrentStockToolId,pDataObject) ) 

#define IAcadToolCopyPaste_Paste(This,pCurrentStockToolId,pParentId,pDataObject,pNewToolIds)	\
    ( (This)->lpVtbl -> Paste(This,pCurrentStockToolId,pParentId,pDataObject,pNewToolIds) ) 

#define IAcadToolCopyPaste_CanPaste(This,pDataObject,pCanPaste)	\
    ( (This)->lpVtbl -> CanPaste(This,pDataObject,pCanPaste) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadToolCopyPaste_INTERFACE_DEFINED__ */


#ifndef __IAcadToolImage_INTERFACE_DEFINED__
#define __IAcadToolImage_INTERFACE_DEFINED__

/* interface IAcadToolImage */
/* [local][custom][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcadToolImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74009B5D-217A-44B6-8271-3A439851EAB5")
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
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcadToolImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcadToolImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcadToolImage_Load(This,bsFileName)	\
    ( (This)->lpVtbl -> Load(This,bsFileName) ) 

#define IAcadToolImage_Save(This,bsFileName)	\
    ( (This)->lpVtbl -> Save(This,bsFileName) ) 

#define IAcadToolImage_Render(This,hdc,x,y,cx,cy,nStyle,bTransparentBitmap)	\
    ( (This)->lpVtbl -> Render(This,hdc,x,y,cx,cy,nStyle,bTransparentBitmap) ) 

#define IAcadToolImage_GetSize(This,pWidth,pHeight)	\
    ( (This)->lpVtbl -> GetSize(This,pWidth,pHeight) ) 

#define IAcadToolImage_GetType(This,pType)	\
    ( (This)->lpVtbl -> GetType(This,pType) ) 

#define IAcadToolImage_IsImageLoaded(This,pVal)	\
    ( (This)->lpVtbl -> IsImageLoaded(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadToolImage_INTERFACE_DEFINED__ */



#ifndef __AcTcLib_LIBRARY_DEFINED__
#define __AcTcLib_LIBRARY_DEFINED__

/* library AcTcLib */
/* [helpstring][custom][version][uuid] */ 


EXTERN_C const IID LIBID_AcTcLib;

EXTERN_C const CLSID CLSID_AcadToolProperties;

#ifdef __cplusplus

class DECLSPEC_UUID("8C7C7AB1-0466-4FEB-B15A-5DF69318A043")
AcadToolProperties;
#endif

EXTERN_C const CLSID CLSID_AcadToolImage;

#ifdef __cplusplus

class DECLSPEC_UUID("79DC18B6-B07B-4559-BFB9-3DD88D9E8A5A")
AcadToolImage;
#endif
#endif /* __AcTcLib_LIBRARY_DEFINED__ */

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