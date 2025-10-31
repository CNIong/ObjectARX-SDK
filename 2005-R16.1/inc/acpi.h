/*
   (C) Copyright 1999-2003 by Autodesk, Inc. 
  
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
/* at Tue Feb 24 23:23:14 2004
 */
/* Compiler settings for U:\global\src\coreapps\opm\Acpi\acpi.idl:
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

#ifndef ___acpi_h__
#define ___acpi_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAcPiPropertyInspector_FWD_DEFINED__
#define __IAcPiPropertyInspector_FWD_DEFINED__
typedef interface IAcPiPropertyInspector IAcPiPropertyInspector;
#endif 	/* __IAcPiPropertyInspector_FWD_DEFINED__ */


#ifndef __IAcPiPropertyEditControl_FWD_DEFINED__
#define __IAcPiPropertyEditControl_FWD_DEFINED__
typedef interface IAcPiPropertyEditControl IAcPiPropertyEditControl;
#endif 	/* __IAcPiPropertyEditControl_FWD_DEFINED__ */


#ifndef __IAcPiPropertyEditEventsSink_FWD_DEFINED__
#define __IAcPiPropertyEditEventsSink_FWD_DEFINED__
typedef interface IAcPiPropertyEditEventsSink IAcPiPropertyEditEventsSink;
#endif 	/* __IAcPiPropertyEditEventsSink_FWD_DEFINED__ */


#ifndef __IAcPiPropertyUnspecified_FWD_DEFINED__
#define __IAcPiPropertyUnspecified_FWD_DEFINED__
typedef interface IAcPiPropertyUnspecified IAcPiPropertyUnspecified;
#endif 	/* __IAcPiPropertyUnspecified_FWD_DEFINED__ */


#ifndef __IAcPiPropertyDisplay_FWD_DEFINED__
#define __IAcPiPropertyDisplay_FWD_DEFINED__
typedef interface IAcPiPropertyDisplay IAcPiPropertyDisplay;
#endif 	/* __IAcPiPropertyDisplay_FWD_DEFINED__ */


#ifndef __IAcPiCategorizeProperties_FWD_DEFINED__
#define __IAcPiCategorizeProperties_FWD_DEFINED__
typedef interface IAcPiCategorizeProperties IAcPiCategorizeProperties;
#endif 	/* __IAcPiCategorizeProperties_FWD_DEFINED__ */


#ifndef __IAcPiPropCommandButtons_FWD_DEFINED__
#define __IAcPiPropCommandButtons_FWD_DEFINED__
typedef interface IAcPiPropCommandButtons IAcPiPropCommandButtons;
#endif 	/* __IAcPiPropCommandButtons_FWD_DEFINED__ */


#ifndef __IAcPiCommandButton_FWD_DEFINED__
#define __IAcPiCommandButton_FWD_DEFINED__
typedef interface IAcPiCommandButton IAcPiCommandButton;
#endif 	/* __IAcPiCommandButton_FWD_DEFINED__ */


#ifndef __IAcPiPropertyInspectorEventsSink_FWD_DEFINED__
#define __IAcPiPropertyInspectorEventsSink_FWD_DEFINED__
typedef interface IAcPiPropertyInspectorEventsSink IAcPiPropertyInspectorEventsSink;
#endif 	/* __IAcPiPropertyInspectorEventsSink_FWD_DEFINED__ */


#ifndef __IAcPiPropertyInspectorInputEventSink_FWD_DEFINED__
#define __IAcPiPropertyInspectorInputEventSink_FWD_DEFINED__
typedef interface IAcPiPropertyInspectorInputEventSink IAcPiPropertyInspectorInputEventSink;
#endif 	/* __IAcPiPropertyInspectorInputEventSink_FWD_DEFINED__ */


#ifndef __AcPiPropertyInspector_FWD_DEFINED__
#define __AcPiPropertyInspector_FWD_DEFINED__

#ifdef __cplusplus
typedef class AcPiPropertyInspector AcPiPropertyInspector;
#else
typedef struct AcPiPropertyInspector AcPiPropertyInspector;
#endif /* __cplusplus */

#endif 	/* __AcPiPropertyInspector_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_acpi_0000 */
/* [local] */ 

#define ACPI_DEFAULT             0x00000000
#define ACPI_CLEARCACHE_REFRESH  0x00000001
#define ACPI_CLEARCACHE_DYNAMIC  0x00000002
#define ACPI_CLEARCACHE_INCLUDED 0x00000004
#define ACPI_ACAD_DYN            0x00000008
#define ACPI_UNION               0x00000010
#define ACPI_SORTBYNAME          0x00000020
#define ACPI_SORTBYWEIGHT        0x00000040
#define ACPI_REFRESH             0x00000080
#define ACPI_SETCONTROLFOCUS     0x00000001
#define ACPI_SCROLLTOCONTROL     0x00000002
#define     AC_TVS_TOOLTIPS             0x00000001
#define     AC_TVS_GRIDLINES            0x00000002
#define     AC_TVS_SELHIGHLIGHT         0x00000004
#define     AC_TVS_GRIDMARKER           0x00000008
#define     AC_TVS_GRIDROUNDSTYLE       0x00000010
#define     AC_TVS_GRIDSTATUSBAR        0x00000020
#define     AC_TVS_GRIDSCROLLRIGHT      0x00000040
// default style is as follows:
#define     AC_TVS_GRID                 ((AC_TVS_SELHIGHLIGHT) | (AC_TVS_GRIDSTATUSBAR) | (AC_TVS_GRIDLINES) | (AC_TVS_TOOLTIPS) | (AC_TVS_GRIDROUNDSTYLE))
#define DISPID_READONLYBACKCOLOR -2000
#define DISPID_READONLYFORECOLOR -2001
#define DISPID_RBUTTONDOWN -2030
#define DISPID_MBUTTONDOWN -2031
#define DISPID_CHECKED -2010
#define DISPID_BEGINPROPERTYUPDATE -2002
#define DISPID_ENDPROPERTYUPDATE -2003
typedef /* [uuid] */  DECLSPEC_UUID("A8562C86-3B34-4539-A880-1AB4089BCF10") 
enum AcPiColorIndex
    {	ACPI_COLOR_TOP	= 0,
	ACPI_COLOR_CATEGORY	= 0x1,
	ACPI_COLOR_ITEM	= 0x2,
	ACPI_COLOR_BORDER	= 0x3,
	ACPI_COLOR_BORDER_ITEM	= 0x4,
	ACPI_COLOR_TEXT_TOP	= 0x5,
	ACPI_COLOR_TEXT_CATEGORY	= 0x6,
	ACPI_COLOR_TEXT_ITEM	= 0x7,
	ACPI_COLOR_FORE_HIGHLIGHT	= 0x8,
	ACPI_COLOR_BACK_HIGHLIGHT	= 0x9,
	ACPI_COLOR_3DSHADOW	= 0xa,
	ACPI_COLOR_BACK_CONTROL	= 0xb,
	ACPI_COLOR_SCROLLBACKGROUND	= 0xc,
	ACPI_COLOR_SCROLLTHUMB	= 0xd,
	ACPI_COLOR_SCROLLARROW	= 0xe,
	ACPI_COLOR_DOUBLECHEVRON1	= 0xf,
	ACPI_COLOR_DOUBLECHEVRON2	= 0x10,
	ACPI_COLOR_SINGLECHEVRON	= 0x11
    } 	AcPiColorIndex;

#define IPropertyInspector IAcPiPropertyInspector
#define IID_IPropertyInspector IID_IAcPiPropertyInspector
#define CLSID_PropertyInspector CLSID_AcPiPropertyInspector


extern RPC_IF_HANDLE __MIDL_itf_acpi_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_acpi_0000_v0_0_s_ifspec;

#ifndef __IAcPiPropertyInspector_INTERFACE_DEFINED__
#define __IAcPiPropertyInspector_INTERFACE_DEFINED__

/* interface IAcPiPropertyInspector */
/* [unique][helpstring][uuid][dual][object] */ 


EXTERN_C const IID IID_IAcPiPropertyInspector;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("22A2DE3F-1F1E-4F04-BD55-D0F1703281F9")
    IAcPiPropertyInspector : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( 
            /* [in] */ VARIANT *pObjUnkArray,
            /* [in] */ VARIANT *pDynUnkArray,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeepFocus( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetColor( 
            /* [in] */ AcPiColorIndex index,
            /* [in] */ OLE_COLOR color) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetColor( 
            /* [in] */ AcPiColorIndex __MIDL_0011,
            /* [retval][out] */ OLE_COLOR *pColor) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IUnknown **pIFont) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IUnknown *pIFont) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BoldFont( 
            /* [retval][out] */ IUnknown **pIFont) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BoldFont( 
            /* [in] */ IUnknown *pIFont) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPersistence( 
            /* [in] */ IUnknown *pINode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPersistence( 
            /* [in] */ IUnknown *pINode) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DelayRefresh( 
            /* [retval][out] */ VARIANT_BOOL *pbDelayRefresh) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DelayRefresh( 
            /* [in] */ VARIANT_BOOL bDelayRefresh) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPiPropertyInspectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPiPropertyInspector * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPiPropertyInspector * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPiPropertyInspector * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAcPiPropertyInspector * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAcPiPropertyInspector * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAcPiPropertyInspector * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAcPiPropertyInspector * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IAcPiPropertyInspector * This,
            /* [in] */ VARIANT *pObjUnkArray,
            /* [in] */ VARIANT *pDynUnkArray,
            /* [in] */ DWORD dwFlags);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            IAcPiPropertyInspector * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            IAcPiPropertyInspector * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_KeepFocus )( 
            IAcPiPropertyInspector * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetColor )( 
            IAcPiPropertyInspector * This,
            /* [in] */ AcPiColorIndex index,
            /* [in] */ OLE_COLOR color);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetColor )( 
            IAcPiPropertyInspector * This,
            /* [in] */ AcPiColorIndex __MIDL_0011,
            /* [retval][out] */ OLE_COLOR *pColor);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IAcPiPropertyInspector * This,
            /* [retval][out] */ IUnknown **pIFont);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            IAcPiPropertyInspector * This,
            /* [in] */ IUnknown *pIFont);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_BoldFont )( 
            IAcPiPropertyInspector * This,
            /* [retval][out] */ IUnknown **pIFont);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_BoldFont )( 
            IAcPiPropertyInspector * This,
            /* [in] */ IUnknown *pIFont);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPersistence )( 
            IAcPiPropertyInspector * This,
            /* [in] */ IUnknown *pINode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPersistence )( 
            IAcPiPropertyInspector * This,
            /* [in] */ IUnknown *pINode);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DelayRefresh )( 
            IAcPiPropertyInspector * This,
            /* [retval][out] */ VARIANT_BOOL *pbDelayRefresh);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DelayRefresh )( 
            IAcPiPropertyInspector * This,
            /* [in] */ VARIANT_BOOL bDelayRefresh);
        
        END_INTERFACE
    } IAcPiPropertyInspectorVtbl;

    interface IAcPiPropertyInspector
    {
        CONST_VTBL struct IAcPiPropertyInspectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPiPropertyInspector_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPiPropertyInspector_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPiPropertyInspector_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPiPropertyInspector_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAcPiPropertyInspector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAcPiPropertyInspector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAcPiPropertyInspector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAcPiPropertyInspector_Reset(This,pObjUnkArray,pDynUnkArray,dwFlags)	\
    (This)->lpVtbl -> Reset(This,pObjUnkArray,pDynUnkArray,dwFlags)

#define IAcPiPropertyInspector_get_Style(This,pVal)	\
    (This)->lpVtbl -> get_Style(This,pVal)

#define IAcPiPropertyInspector_put_Style(This,newVal)	\
    (This)->lpVtbl -> put_Style(This,newVal)

#define IAcPiPropertyInspector_get_KeepFocus(This,pVal)	\
    (This)->lpVtbl -> get_KeepFocus(This,pVal)

#define IAcPiPropertyInspector_SetColor(This,index,color)	\
    (This)->lpVtbl -> SetColor(This,index,color)

#define IAcPiPropertyInspector_GetColor(This,__MIDL_0011,pColor)	\
    (This)->lpVtbl -> GetColor(This,__MIDL_0011,pColor)

#define IAcPiPropertyInspector_get_Font(This,pIFont)	\
    (This)->lpVtbl -> get_Font(This,pIFont)

#define IAcPiPropertyInspector_put_Font(This,pIFont)	\
    (This)->lpVtbl -> put_Font(This,pIFont)

#define IAcPiPropertyInspector_get_BoldFont(This,pIFont)	\
    (This)->lpVtbl -> get_BoldFont(This,pIFont)

#define IAcPiPropertyInspector_put_BoldFont(This,pIFont)	\
    (This)->lpVtbl -> put_BoldFont(This,pIFont)

#define IAcPiPropertyInspector_SetPersistence(This,pINode)	\
    (This)->lpVtbl -> SetPersistence(This,pINode)

#define IAcPiPropertyInspector_GetPersistence(This,pINode)	\
    (This)->lpVtbl -> GetPersistence(This,pINode)

#define IAcPiPropertyInspector_get_DelayRefresh(This,pbDelayRefresh)	\
    (This)->lpVtbl -> get_DelayRefresh(This,pbDelayRefresh)

#define IAcPiPropertyInspector_put_DelayRefresh(This,bDelayRefresh)	\
    (This)->lpVtbl -> put_DelayRefresh(This,bDelayRefresh)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_Reset_Proxy( 
    IAcPiPropertyInspector * This,
    /* [in] */ VARIANT *pObjUnkArray,
    /* [in] */ VARIANT *pDynUnkArray,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAcPiPropertyInspector_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_get_Style_Proxy( 
    IAcPiPropertyInspector * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB IAcPiPropertyInspector_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_put_Style_Proxy( 
    IAcPiPropertyInspector * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB IAcPiPropertyInspector_put_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_get_KeepFocus_Proxy( 
    IAcPiPropertyInspector * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IAcPiPropertyInspector_get_KeepFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_SetColor_Proxy( 
    IAcPiPropertyInspector * This,
    /* [in] */ AcPiColorIndex index,
    /* [in] */ OLE_COLOR color);


void __RPC_STUB IAcPiPropertyInspector_SetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_GetColor_Proxy( 
    IAcPiPropertyInspector * This,
    /* [in] */ AcPiColorIndex __MIDL_0011,
    /* [retval][out] */ OLE_COLOR *pColor);


void __RPC_STUB IAcPiPropertyInspector_GetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_get_Font_Proxy( 
    IAcPiPropertyInspector * This,
    /* [retval][out] */ IUnknown **pIFont);


void __RPC_STUB IAcPiPropertyInspector_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_put_Font_Proxy( 
    IAcPiPropertyInspector * This,
    /* [in] */ IUnknown *pIFont);


void __RPC_STUB IAcPiPropertyInspector_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_get_BoldFont_Proxy( 
    IAcPiPropertyInspector * This,
    /* [retval][out] */ IUnknown **pIFont);


void __RPC_STUB IAcPiPropertyInspector_get_BoldFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_put_BoldFont_Proxy( 
    IAcPiPropertyInspector * This,
    /* [in] */ IUnknown *pIFont);


void __RPC_STUB IAcPiPropertyInspector_put_BoldFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_SetPersistence_Proxy( 
    IAcPiPropertyInspector * This,
    /* [in] */ IUnknown *pINode);


void __RPC_STUB IAcPiPropertyInspector_SetPersistence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_GetPersistence_Proxy( 
    IAcPiPropertyInspector * This,
    /* [in] */ IUnknown *pINode);


void __RPC_STUB IAcPiPropertyInspector_GetPersistence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_get_DelayRefresh_Proxy( 
    IAcPiPropertyInspector * This,
    /* [retval][out] */ VARIANT_BOOL *pbDelayRefresh);


void __RPC_STUB IAcPiPropertyInspector_get_DelayRefresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspector_put_DelayRefresh_Proxy( 
    IAcPiPropertyInspector * This,
    /* [in] */ VARIANT_BOOL bDelayRefresh);


void __RPC_STUB IAcPiPropertyInspector_put_DelayRefresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPiPropertyInspector_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_acpi_0252 */
/* [local] */ 

#define IPropertyEditControl IAcPiPropertyEditControl
#define IID_IPropertyEditControl IID_IAcPiPropertyEditControl


extern RPC_IF_HANDLE __MIDL_itf_acpi_0252_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_acpi_0252_v0_0_s_ifspec;

#ifndef __IAcPiPropertyEditControl_INTERFACE_DEFINED__
#define __IAcPiPropertyEditControl_INTERFACE_DEFINED__

/* interface IAcPiPropertyEditControl */
/* [unique][helpstring][uuid][dual][object] */ 


EXTERN_C const IID IID_IAcPiPropertyEditControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6371C569-72C0-43a0-A457-1E9D2EB9201E")
    IAcPiPropertyEditControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitEditControl( 
            /* [in] */ LPVARIANT pVarObjDispArray,
            /* [in] */ LPVARIANT pVarDynPropArray,
            /* [in] */ LPVARIANT pDispidArray,
            /* [in] */ VARIANT_BOOL bReadOnly) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeepFocus( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [id][helpstring][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][helpstring][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][helpstring][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_ForeColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][helpstring][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_ForeColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][helpstring][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_ReadOnlyBackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][helpstring][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_ReadOnlyBackColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][helpstring][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_ReadOnlyForeColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][helpstring][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_ReadOnlyForeColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][helpstring][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IUnknown *pIFont) = 0;
        
        virtual /* [id][helpstring][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IUnknown **pIFont) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPiPropertyEditControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPiPropertyEditControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPiPropertyEditControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAcPiPropertyEditControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitEditControl )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ LPVARIANT pVarObjDispArray,
            /* [in] */ LPVARIANT pVarDynPropArray,
            /* [in] */ LPVARIANT pDispidArray,
            /* [in] */ VARIANT_BOOL bReadOnly);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ DWORD dwFlags);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_KeepFocus )( 
            IAcPiPropertyEditControl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [id][helpstring][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][helpstring][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IAcPiPropertyEditControl * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][helpstring][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ForeColor )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][helpstring][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForeColor )( 
            IAcPiPropertyEditControl * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][helpstring][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReadOnlyBackColor )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][helpstring][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReadOnlyBackColor )( 
            IAcPiPropertyEditControl * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][helpstring][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReadOnlyForeColor )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][helpstring][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReadOnlyForeColor )( 
            IAcPiPropertyEditControl * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][helpstring][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            IAcPiPropertyEditControl * This,
            /* [in] */ IUnknown *pIFont);
        
        /* [id][helpstring][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IAcPiPropertyEditControl * This,
            /* [retval][out] */ IUnknown **pIFont);
        
        END_INTERFACE
    } IAcPiPropertyEditControlVtbl;

    interface IAcPiPropertyEditControl
    {
        CONST_VTBL struct IAcPiPropertyEditControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPiPropertyEditControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPiPropertyEditControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPiPropertyEditControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPiPropertyEditControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAcPiPropertyEditControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAcPiPropertyEditControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAcPiPropertyEditControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAcPiPropertyEditControl_InitEditControl(This,pVarObjDispArray,pVarDynPropArray,pDispidArray,bReadOnly)	\
    (This)->lpVtbl -> InitEditControl(This,pVarObjDispArray,pVarDynPropArray,pDispidArray,bReadOnly)

#define IAcPiPropertyEditControl_Refresh(This,dwFlags)	\
    (This)->lpVtbl -> Refresh(This,dwFlags)

#define IAcPiPropertyEditControl_get_KeepFocus(This,pVal)	\
    (This)->lpVtbl -> get_KeepFocus(This,pVal)

#define IAcPiPropertyEditControl_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define IAcPiPropertyEditControl_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define IAcPiPropertyEditControl_put_ForeColor(This,clr)	\
    (This)->lpVtbl -> put_ForeColor(This,clr)

#define IAcPiPropertyEditControl_get_ForeColor(This,pclr)	\
    (This)->lpVtbl -> get_ForeColor(This,pclr)

#define IAcPiPropertyEditControl_put_ReadOnlyBackColor(This,clr)	\
    (This)->lpVtbl -> put_ReadOnlyBackColor(This,clr)

#define IAcPiPropertyEditControl_get_ReadOnlyBackColor(This,pclr)	\
    (This)->lpVtbl -> get_ReadOnlyBackColor(This,pclr)

#define IAcPiPropertyEditControl_put_ReadOnlyForeColor(This,clr)	\
    (This)->lpVtbl -> put_ReadOnlyForeColor(This,clr)

#define IAcPiPropertyEditControl_get_ReadOnlyForeColor(This,pclr)	\
    (This)->lpVtbl -> get_ReadOnlyForeColor(This,pclr)

#define IAcPiPropertyEditControl_put_Font(This,pIFont)	\
    (This)->lpVtbl -> put_Font(This,pIFont)

#define IAcPiPropertyEditControl_get_Font(This,pIFont)	\
    (This)->lpVtbl -> get_Font(This,pIFont)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_InitEditControl_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [in] */ LPVARIANT pVarObjDispArray,
    /* [in] */ LPVARIANT pVarDynPropArray,
    /* [in] */ LPVARIANT pDispidArray,
    /* [in] */ VARIANT_BOOL bReadOnly);


void __RPC_STUB IAcPiPropertyEditControl_InitEditControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_Refresh_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAcPiPropertyEditControl_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_get_KeepFocus_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IAcPiPropertyEditControl_get_KeepFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_put_BackColor_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IAcPiPropertyEditControl_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_get_BackColor_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IAcPiPropertyEditControl_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_put_ForeColor_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IAcPiPropertyEditControl_put_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_get_ForeColor_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IAcPiPropertyEditControl_get_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_put_ReadOnlyBackColor_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IAcPiPropertyEditControl_put_ReadOnlyBackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_get_ReadOnlyBackColor_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IAcPiPropertyEditControl_get_ReadOnlyBackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_put_ReadOnlyForeColor_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IAcPiPropertyEditControl_put_ReadOnlyForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_get_ReadOnlyForeColor_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IAcPiPropertyEditControl_get_ReadOnlyForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_put_Font_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [in] */ IUnknown *pIFont);


void __RPC_STUB IAcPiPropertyEditControl_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditControl_get_Font_Proxy( 
    IAcPiPropertyEditControl * This,
    /* [retval][out] */ IUnknown **pIFont);


void __RPC_STUB IAcPiPropertyEditControl_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPiPropertyEditControl_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_acpi_0253 */
/* [local] */ 

#define IPropEditUIEventsSink IAcPiPropertyEditEventsSink
#define IID_IPropEditUIEventsSink IID_IAcPiPropertyEditEventsSink


extern RPC_IF_HANDLE __MIDL_itf_acpi_0253_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_acpi_0253_v0_0_s_ifspec;

#ifndef __IAcPiPropertyEditEventsSink_INTERFACE_DEFINED__
#define __IAcPiPropertyEditEventsSink_INTERFACE_DEFINED__

/* interface IAcPiPropertyEditEventsSink */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID_IAcPiPropertyEditEventsSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7332190-3EA0-4fff-9785-8E8E0D3F6B21")
    IAcPiPropertyEditEventsSink : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnClick( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnDblClick( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnKeyDown( 
            /* [in] */ long pnChar,
            /* [in] */ long keyData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnKeyUp( 
            /* [in] */ long pnChar,
            /* [in] */ long keyData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnRButtonDown( 
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnMButtonDown( 
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnBeginPropertyUpdate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnEndPropertyUpdate( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPiPropertyEditEventsSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPiPropertyEditEventsSink * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPiPropertyEditEventsSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPiPropertyEditEventsSink * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnClick )( 
            IAcPiPropertyEditEventsSink * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnDblClick )( 
            IAcPiPropertyEditEventsSink * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnKeyDown )( 
            IAcPiPropertyEditEventsSink * This,
            /* [in] */ long pnChar,
            /* [in] */ long keyData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnKeyUp )( 
            IAcPiPropertyEditEventsSink * This,
            /* [in] */ long pnChar,
            /* [in] */ long keyData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnRButtonDown )( 
            IAcPiPropertyEditEventsSink * This,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnMButtonDown )( 
            IAcPiPropertyEditEventsSink * This,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnBeginPropertyUpdate )( 
            IAcPiPropertyEditEventsSink * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnEndPropertyUpdate )( 
            IAcPiPropertyEditEventsSink * This);
        
        END_INTERFACE
    } IAcPiPropertyEditEventsSinkVtbl;

    interface IAcPiPropertyEditEventsSink
    {
        CONST_VTBL struct IAcPiPropertyEditEventsSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPiPropertyEditEventsSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPiPropertyEditEventsSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPiPropertyEditEventsSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPiPropertyEditEventsSink_OnClick(This)	\
    (This)->lpVtbl -> OnClick(This)

#define IAcPiPropertyEditEventsSink_OnDblClick(This)	\
    (This)->lpVtbl -> OnDblClick(This)

#define IAcPiPropertyEditEventsSink_OnKeyDown(This,pnChar,keyData)	\
    (This)->lpVtbl -> OnKeyDown(This,pnChar,keyData)

#define IAcPiPropertyEditEventsSink_OnKeyUp(This,pnChar,keyData)	\
    (This)->lpVtbl -> OnKeyUp(This,pnChar,keyData)

#define IAcPiPropertyEditEventsSink_OnRButtonDown(This,wParam,lParam)	\
    (This)->lpVtbl -> OnRButtonDown(This,wParam,lParam)

#define IAcPiPropertyEditEventsSink_OnMButtonDown(This,wParam,lParam)	\
    (This)->lpVtbl -> OnMButtonDown(This,wParam,lParam)

#define IAcPiPropertyEditEventsSink_OnBeginPropertyUpdate(This)	\
    (This)->lpVtbl -> OnBeginPropertyUpdate(This)

#define IAcPiPropertyEditEventsSink_OnEndPropertyUpdate(This)	\
    (This)->lpVtbl -> OnEndPropertyUpdate(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditEventsSink_OnClick_Proxy( 
    IAcPiPropertyEditEventsSink * This);


void __RPC_STUB IAcPiPropertyEditEventsSink_OnClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditEventsSink_OnDblClick_Proxy( 
    IAcPiPropertyEditEventsSink * This);


void __RPC_STUB IAcPiPropertyEditEventsSink_OnDblClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditEventsSink_OnKeyDown_Proxy( 
    IAcPiPropertyEditEventsSink * This,
    /* [in] */ long pnChar,
    /* [in] */ long keyData);


void __RPC_STUB IAcPiPropertyEditEventsSink_OnKeyDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditEventsSink_OnKeyUp_Proxy( 
    IAcPiPropertyEditEventsSink * This,
    /* [in] */ long pnChar,
    /* [in] */ long keyData);


void __RPC_STUB IAcPiPropertyEditEventsSink_OnKeyUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditEventsSink_OnRButtonDown_Proxy( 
    IAcPiPropertyEditEventsSink * This,
    /* [in] */ WPARAM wParam,
    /* [in] */ LPARAM lParam);


void __RPC_STUB IAcPiPropertyEditEventsSink_OnRButtonDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditEventsSink_OnMButtonDown_Proxy( 
    IAcPiPropertyEditEventsSink * This,
    /* [in] */ WPARAM wParam,
    /* [in] */ LPARAM lParam);


void __RPC_STUB IAcPiPropertyEditEventsSink_OnMButtonDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditEventsSink_OnBeginPropertyUpdate_Proxy( 
    IAcPiPropertyEditEventsSink * This);


void __RPC_STUB IAcPiPropertyEditEventsSink_OnBeginPropertyUpdate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyEditEventsSink_OnEndPropertyUpdate_Proxy( 
    IAcPiPropertyEditEventsSink * This);


void __RPC_STUB IAcPiPropertyEditEventsSink_OnEndPropertyUpdate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPiPropertyEditEventsSink_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_acpi_0254 */
/* [local] */ 

#define IPropertyUnspecified  IAcPiPropertyUnspecified
#define IID_IPropertyUnspecified IID_IAcPiPropertyUnspecified


extern RPC_IF_HANDLE __MIDL_itf_acpi_0254_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_acpi_0254_v0_0_s_ifspec;

#ifndef __IAcPiPropertyUnspecified_INTERFACE_DEFINED__
#define __IAcPiPropertyUnspecified_INTERFACE_DEFINED__

/* interface IAcPiPropertyUnspecified */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPiPropertyUnspecified;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("63ECCF04-51B1-4fe1-972C-9EFD420ADEF4")
    IAcPiPropertyUnspecified : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsValueUnspecified( 
            /* [in] */ VARIANT varId,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUnspecified( 
            /* [in] */ VARIANT varId,
            /* [in] */ VARIANT_BOOL bIsUnspecified) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsUnspecifiedAllowed( 
            /* [in] */ VARIANT varId,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUnspecifiedString( 
            /* [in] */ VARIANT varId,
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPiPropertyUnspecifiedVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPiPropertyUnspecified * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPiPropertyUnspecified * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPiPropertyUnspecified * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsValueUnspecified )( 
            IAcPiPropertyUnspecified * This,
            /* [in] */ VARIANT varId,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUnspecified )( 
            IAcPiPropertyUnspecified * This,
            /* [in] */ VARIANT varId,
            /* [in] */ VARIANT_BOOL bIsUnspecified);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsUnspecifiedAllowed )( 
            IAcPiPropertyUnspecified * This,
            /* [in] */ VARIANT varId,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUnspecifiedString )( 
            IAcPiPropertyUnspecified * This,
            /* [in] */ VARIANT varId,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IAcPiPropertyUnspecifiedVtbl;

    interface IAcPiPropertyUnspecified
    {
        CONST_VTBL struct IAcPiPropertyUnspecifiedVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPiPropertyUnspecified_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPiPropertyUnspecified_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPiPropertyUnspecified_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPiPropertyUnspecified_IsValueUnspecified(This,varId,pVal)	\
    (This)->lpVtbl -> IsValueUnspecified(This,varId,pVal)

#define IAcPiPropertyUnspecified_SetUnspecified(This,varId,bIsUnspecified)	\
    (This)->lpVtbl -> SetUnspecified(This,varId,bIsUnspecified)

#define IAcPiPropertyUnspecified_IsUnspecifiedAllowed(This,varId,pVal)	\
    (This)->lpVtbl -> IsUnspecifiedAllowed(This,varId,pVal)

#define IAcPiPropertyUnspecified_GetUnspecifiedString(This,varId,pVal)	\
    (This)->lpVtbl -> GetUnspecifiedString(This,varId,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyUnspecified_IsValueUnspecified_Proxy( 
    IAcPiPropertyUnspecified * This,
    /* [in] */ VARIANT varId,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IAcPiPropertyUnspecified_IsValueUnspecified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyUnspecified_SetUnspecified_Proxy( 
    IAcPiPropertyUnspecified * This,
    /* [in] */ VARIANT varId,
    /* [in] */ VARIANT_BOOL bIsUnspecified);


void __RPC_STUB IAcPiPropertyUnspecified_SetUnspecified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyUnspecified_IsUnspecifiedAllowed_Proxy( 
    IAcPiPropertyUnspecified * This,
    /* [in] */ VARIANT varId,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IAcPiPropertyUnspecified_IsUnspecifiedAllowed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyUnspecified_GetUnspecifiedString_Proxy( 
    IAcPiPropertyUnspecified * This,
    /* [in] */ VARIANT varId,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IAcPiPropertyUnspecified_GetUnspecifiedString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPiPropertyUnspecified_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_acpi_0255 */
/* [local] */ 

#define IPerPropertyDisplay IAcPiPropertyDisplay
#define IID_IPerPropertyDisplay IID_IAcPiPropertyDisplay


extern RPC_IF_HANDLE __MIDL_itf_acpi_0255_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_acpi_0255_v0_0_s_ifspec;

#ifndef __IAcPiPropertyDisplay_INTERFACE_DEFINED__
#define __IAcPiPropertyDisplay_INTERFACE_DEFINED__

/* interface IAcPiPropertyDisplay */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPiPropertyDisplay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6a0d7861-8773-4d56-ac16-95aff3051ebd")
    IAcPiPropertyDisplay : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCustomPropertyCtrl( 
            /* [in] */ VARIANT Id,
            /* [in] */ LCID lcid,
            /* [out] */ BSTR *pProgId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPropertyIcon( 
            /* [in] */ VARIANT Id,
            /* [out] */ IUnknown **pIcon) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPropTextColor( 
            /* [in] */ VARIANT Id,
            /* [out] */ OLE_COLOR *pTextColor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsFullView( 
            /* [in] */ VARIANT Id,
            /* [out] */ VARIANT_BOOL *pbVisible,
            /* [out] */ DWORD *pIntegralHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPropertyWeight( 
            /* [in] */ VARIANT Id,
            /* [out] */ long *pPropertyWeight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPiPropertyDisplayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPiPropertyDisplay * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPiPropertyDisplay * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPiPropertyDisplay * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCustomPropertyCtrl )( 
            IAcPiPropertyDisplay * This,
            /* [in] */ VARIANT Id,
            /* [in] */ LCID lcid,
            /* [out] */ BSTR *pProgId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyIcon )( 
            IAcPiPropertyDisplay * This,
            /* [in] */ VARIANT Id,
            /* [out] */ IUnknown **pIcon);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPropTextColor )( 
            IAcPiPropertyDisplay * This,
            /* [in] */ VARIANT Id,
            /* [out] */ OLE_COLOR *pTextColor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsFullView )( 
            IAcPiPropertyDisplay * This,
            /* [in] */ VARIANT Id,
            /* [out] */ VARIANT_BOOL *pbVisible,
            /* [out] */ DWORD *pIntegralHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyWeight )( 
            IAcPiPropertyDisplay * This,
            /* [in] */ VARIANT Id,
            /* [out] */ long *pPropertyWeight);
        
        END_INTERFACE
    } IAcPiPropertyDisplayVtbl;

    interface IAcPiPropertyDisplay
    {
        CONST_VTBL struct IAcPiPropertyDisplayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPiPropertyDisplay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPiPropertyDisplay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPiPropertyDisplay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPiPropertyDisplay_GetCustomPropertyCtrl(This,Id,lcid,pProgId)	\
    (This)->lpVtbl -> GetCustomPropertyCtrl(This,Id,lcid,pProgId)

#define IAcPiPropertyDisplay_GetPropertyIcon(This,Id,pIcon)	\
    (This)->lpVtbl -> GetPropertyIcon(This,Id,pIcon)

#define IAcPiPropertyDisplay_GetPropTextColor(This,Id,pTextColor)	\
    (This)->lpVtbl -> GetPropTextColor(This,Id,pTextColor)

#define IAcPiPropertyDisplay_IsFullView(This,Id,pbVisible,pIntegralHeight)	\
    (This)->lpVtbl -> IsFullView(This,Id,pbVisible,pIntegralHeight)

#define IAcPiPropertyDisplay_GetPropertyWeight(This,Id,pPropertyWeight)	\
    (This)->lpVtbl -> GetPropertyWeight(This,Id,pPropertyWeight)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyDisplay_GetCustomPropertyCtrl_Proxy( 
    IAcPiPropertyDisplay * This,
    /* [in] */ VARIANT Id,
    /* [in] */ LCID lcid,
    /* [out] */ BSTR *pProgId);


void __RPC_STUB IAcPiPropertyDisplay_GetCustomPropertyCtrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyDisplay_GetPropertyIcon_Proxy( 
    IAcPiPropertyDisplay * This,
    /* [in] */ VARIANT Id,
    /* [out] */ IUnknown **pIcon);


void __RPC_STUB IAcPiPropertyDisplay_GetPropertyIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyDisplay_GetPropTextColor_Proxy( 
    IAcPiPropertyDisplay * This,
    /* [in] */ VARIANT Id,
    /* [out] */ OLE_COLOR *pTextColor);


void __RPC_STUB IAcPiPropertyDisplay_GetPropTextColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyDisplay_IsFullView_Proxy( 
    IAcPiPropertyDisplay * This,
    /* [in] */ VARIANT Id,
    /* [out] */ VARIANT_BOOL *pbVisible,
    /* [out] */ DWORD *pIntegralHeight);


void __RPC_STUB IAcPiPropertyDisplay_IsFullView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyDisplay_GetPropertyWeight_Proxy( 
    IAcPiPropertyDisplay * This,
    /* [in] */ VARIANT Id,
    /* [out] */ long *pPropertyWeight);


void __RPC_STUB IAcPiPropertyDisplay_GetPropertyWeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPiPropertyDisplay_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_acpi_0256 */
/* [local] */ 

#define ICategorizeProperties2 IAcPiCategorizeProperties
#define IID_ICategorizeProperties2 IID_IAcPiCategorizeProperties


extern RPC_IF_HANDLE __MIDL_itf_acpi_0256_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_acpi_0256_v0_0_s_ifspec;

#ifndef __IAcPiCategorizeProperties_INTERFACE_DEFINED__
#define __IAcPiCategorizeProperties_INTERFACE_DEFINED__

/* interface IAcPiCategorizeProperties */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPiCategorizeProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8590b992-d9a1-48d1-899a-358d77e1512a")
    IAcPiCategorizeProperties : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MapPropertyToCategory( 
            /* [in] */ DISPID dispID,
            /* [out] */ int *pCatID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCategoryName( 
            /* [in] */ int CatID,
            /* [in] */ LCID lCid,
            /* [out] */ BSTR *pCategoryName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCategoryDescription( 
            /* [in] */ int CatID,
            /* [in] */ LCID lCid,
            /* [out] */ BSTR *pCategoryDescription) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCategoryWeight( 
            /* [in] */ int CatID,
            /* [out] */ long *pCategoryWeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParentCategory( 
            /* [in] */ int CatID,
            /* [out] */ int *pParentCatID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUniqueID( 
            /* [out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCommandButtons( 
            /* [in] */ int CatID,
            /* [out] */ VARIANT *pCatCmdBtns) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPiCategorizePropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPiCategorizeProperties * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPiCategorizeProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPiCategorizeProperties * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MapPropertyToCategory )( 
            IAcPiCategorizeProperties * This,
            /* [in] */ DISPID dispID,
            /* [out] */ int *pCatID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCategoryName )( 
            IAcPiCategorizeProperties * This,
            /* [in] */ int CatID,
            /* [in] */ LCID lCid,
            /* [out] */ BSTR *pCategoryName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCategoryDescription )( 
            IAcPiCategorizeProperties * This,
            /* [in] */ int CatID,
            /* [in] */ LCID lCid,
            /* [out] */ BSTR *pCategoryDescription);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCategoryWeight )( 
            IAcPiCategorizeProperties * This,
            /* [in] */ int CatID,
            /* [out] */ long *pCategoryWeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetParentCategory )( 
            IAcPiCategorizeProperties * This,
            /* [in] */ int CatID,
            /* [out] */ int *pParentCatID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUniqueID )( 
            IAcPiCategorizeProperties * This,
            /* [out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCommandButtons )( 
            IAcPiCategorizeProperties * This,
            /* [in] */ int CatID,
            /* [out] */ VARIANT *pCatCmdBtns);
        
        END_INTERFACE
    } IAcPiCategorizePropertiesVtbl;

    interface IAcPiCategorizeProperties
    {
        CONST_VTBL struct IAcPiCategorizePropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPiCategorizeProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPiCategorizeProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPiCategorizeProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPiCategorizeProperties_MapPropertyToCategory(This,dispID,pCatID)	\
    (This)->lpVtbl -> MapPropertyToCategory(This,dispID,pCatID)

#define IAcPiCategorizeProperties_GetCategoryName(This,CatID,lCid,pCategoryName)	\
    (This)->lpVtbl -> GetCategoryName(This,CatID,lCid,pCategoryName)

#define IAcPiCategorizeProperties_GetCategoryDescription(This,CatID,lCid,pCategoryDescription)	\
    (This)->lpVtbl -> GetCategoryDescription(This,CatID,lCid,pCategoryDescription)

#define IAcPiCategorizeProperties_GetCategoryWeight(This,CatID,pCategoryWeight)	\
    (This)->lpVtbl -> GetCategoryWeight(This,CatID,pCategoryWeight)

#define IAcPiCategorizeProperties_GetParentCategory(This,CatID,pParentCatID)	\
    (This)->lpVtbl -> GetParentCategory(This,CatID,pParentCatID)

#define IAcPiCategorizeProperties_GetUniqueID(This,pVal)	\
    (This)->lpVtbl -> GetUniqueID(This,pVal)

#define IAcPiCategorizeProperties_GetCommandButtons(This,CatID,pCatCmdBtns)	\
    (This)->lpVtbl -> GetCommandButtons(This,CatID,pCatCmdBtns)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiCategorizeProperties_MapPropertyToCategory_Proxy( 
    IAcPiCategorizeProperties * This,
    /* [in] */ DISPID dispID,
    /* [out] */ int *pCatID);


void __RPC_STUB IAcPiCategorizeProperties_MapPropertyToCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiCategorizeProperties_GetCategoryName_Proxy( 
    IAcPiCategorizeProperties * This,
    /* [in] */ int CatID,
    /* [in] */ LCID lCid,
    /* [out] */ BSTR *pCategoryName);


void __RPC_STUB IAcPiCategorizeProperties_GetCategoryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiCategorizeProperties_GetCategoryDescription_Proxy( 
    IAcPiCategorizeProperties * This,
    /* [in] */ int CatID,
    /* [in] */ LCID lCid,
    /* [out] */ BSTR *pCategoryDescription);


void __RPC_STUB IAcPiCategorizeProperties_GetCategoryDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiCategorizeProperties_GetCategoryWeight_Proxy( 
    IAcPiCategorizeProperties * This,
    /* [in] */ int CatID,
    /* [out] */ long *pCategoryWeight);


void __RPC_STUB IAcPiCategorizeProperties_GetCategoryWeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiCategorizeProperties_GetParentCategory_Proxy( 
    IAcPiCategorizeProperties * This,
    /* [in] */ int CatID,
    /* [out] */ int *pParentCatID);


void __RPC_STUB IAcPiCategorizeProperties_GetParentCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiCategorizeProperties_GetUniqueID_Proxy( 
    IAcPiCategorizeProperties * This,
    /* [out] */ BSTR *pVal);


void __RPC_STUB IAcPiCategorizeProperties_GetUniqueID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiCategorizeProperties_GetCommandButtons_Proxy( 
    IAcPiCategorizeProperties * This,
    /* [in] */ int CatID,
    /* [out] */ VARIANT *pCatCmdBtns);


void __RPC_STUB IAcPiCategorizeProperties_GetCommandButtons_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPiCategorizeProperties_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_acpi_0257 */
/* [local] */ 

#define IPropCommandButtons IAcPiPropCommandButtons
#define IID_IPropCommandButtons IID_IAcPiPropCommandButtons


extern RPC_IF_HANDLE __MIDL_itf_acpi_0257_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_acpi_0257_v0_0_s_ifspec;

#ifndef __IAcPiPropCommandButtons_INTERFACE_DEFINED__
#define __IAcPiPropCommandButtons_INTERFACE_DEFINED__

/* interface IAcPiPropCommandButtons */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPiPropCommandButtons;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6CD83FA-32A5-4c1e-9F2E-487A612F4A77")
    IAcPiPropCommandButtons : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetButtons( 
            /* [retval][out] */ VARIANT *pButtons) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPiPropCommandButtonsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPiPropCommandButtons * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPiPropCommandButtons * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPiPropCommandButtons * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetButtons )( 
            IAcPiPropCommandButtons * This,
            /* [retval][out] */ VARIANT *pButtons);
        
        END_INTERFACE
    } IAcPiPropCommandButtonsVtbl;

    interface IAcPiPropCommandButtons
    {
        CONST_VTBL struct IAcPiPropCommandButtonsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPiPropCommandButtons_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPiPropCommandButtons_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPiPropCommandButtons_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPiPropCommandButtons_GetButtons(This,pButtons)	\
    (This)->lpVtbl -> GetButtons(This,pButtons)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropCommandButtons_GetButtons_Proxy( 
    IAcPiPropCommandButtons * This,
    /* [retval][out] */ VARIANT *pButtons);


void __RPC_STUB IAcPiPropCommandButtons_GetButtons_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPiPropCommandButtons_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_acpi_0258 */
/* [local] */ 

#define ICommandButton IAcPiCommandButton
#define IID_ICommandButton IID_IAcPiCommandButton


extern RPC_IF_HANDLE __MIDL_itf_acpi_0258_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_acpi_0258_v0_0_s_ifspec;

#ifndef __IAcPiCommandButton_INTERFACE_DEFINED__
#define __IAcPiCommandButton_INTERFACE_DEFINED__

/* interface IAcPiCommandButton */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPiCommandButton;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A5EAB6FD-EB1A-43d5-BCE0-2DA8C40F21BA")
    IAcPiCommandButton : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [in] */ LCID lcid,
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_EnabledPicture( 
            /* [retval][out] */ IUnknown **pPicture) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DisabledPicture( 
            /* [retval][out] */ IUnknown **pPicture) = 0;
        
        virtual /* [helpstring][bindable][propget][id] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *bEnabled) = 0;
        
        virtual /* [helpstring][bindable][propput][id] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL bEnabled) = 0;
        
        virtual /* [helpstring][bindable][propget][id] */ HRESULT STDMETHODCALLTYPE get_Checked( 
            /* [retval][out] */ VARIANT_BOOL *bChecked) = 0;
        
        virtual /* [helpstring][bindable][propput][id] */ HRESULT STDMETHODCALLTYPE put_Checked( 
            /* [in] */ VARIANT_BOOL bChecked) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ButtonStyle( 
            /* [retval][out] */ long *style) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Execute( 
            /* [in] */ VARIANT Objects) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPiCommandButtonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPiCommandButton * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPiCommandButton * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPiCommandButton * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IAcPiCommandButton * This,
            /* [in] */ LCID lcid,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_EnabledPicture )( 
            IAcPiCommandButton * This,
            /* [retval][out] */ IUnknown **pPicture);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DisabledPicture )( 
            IAcPiCommandButton * This,
            /* [retval][out] */ IUnknown **pPicture);
        
        /* [helpstring][bindable][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IAcPiCommandButton * This,
            /* [retval][out] */ VARIANT_BOOL *bEnabled);
        
        /* [helpstring][bindable][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IAcPiCommandButton * This,
            /* [in] */ VARIANT_BOOL bEnabled);
        
        /* [helpstring][bindable][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Checked )( 
            IAcPiCommandButton * This,
            /* [retval][out] */ VARIANT_BOOL *bChecked);
        
        /* [helpstring][bindable][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Checked )( 
            IAcPiCommandButton * This,
            /* [in] */ VARIANT_BOOL bChecked);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ButtonStyle )( 
            IAcPiCommandButton * This,
            /* [retval][out] */ long *style);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Execute )( 
            IAcPiCommandButton * This,
            /* [in] */ VARIANT Objects);
        
        END_INTERFACE
    } IAcPiCommandButtonVtbl;

    interface IAcPiCommandButton
    {
        CONST_VTBL struct IAcPiCommandButtonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPiCommandButton_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPiCommandButton_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPiCommandButton_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPiCommandButton_GetName(This,lcid,name)	\
    (This)->lpVtbl -> GetName(This,lcid,name)

#define IAcPiCommandButton_get_EnabledPicture(This,pPicture)	\
    (This)->lpVtbl -> get_EnabledPicture(This,pPicture)

#define IAcPiCommandButton_get_DisabledPicture(This,pPicture)	\
    (This)->lpVtbl -> get_DisabledPicture(This,pPicture)

#define IAcPiCommandButton_get_Enabled(This,bEnabled)	\
    (This)->lpVtbl -> get_Enabled(This,bEnabled)

#define IAcPiCommandButton_put_Enabled(This,bEnabled)	\
    (This)->lpVtbl -> put_Enabled(This,bEnabled)

#define IAcPiCommandButton_get_Checked(This,bChecked)	\
    (This)->lpVtbl -> get_Checked(This,bChecked)

#define IAcPiCommandButton_put_Checked(This,bChecked)	\
    (This)->lpVtbl -> put_Checked(This,bChecked)

#define IAcPiCommandButton_get_ButtonStyle(This,style)	\
    (This)->lpVtbl -> get_ButtonStyle(This,style)

#define IAcPiCommandButton_Execute(This,Objects)	\
    (This)->lpVtbl -> Execute(This,Objects)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiCommandButton_GetName_Proxy( 
    IAcPiCommandButton * This,
    /* [in] */ LCID lcid,
    /* [retval][out] */ BSTR *name);


void __RPC_STUB IAcPiCommandButton_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IAcPiCommandButton_get_EnabledPicture_Proxy( 
    IAcPiCommandButton * This,
    /* [retval][out] */ IUnknown **pPicture);


void __RPC_STUB IAcPiCommandButton_get_EnabledPicture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IAcPiCommandButton_get_DisabledPicture_Proxy( 
    IAcPiCommandButton * This,
    /* [retval][out] */ IUnknown **pPicture);


void __RPC_STUB IAcPiCommandButton_get_DisabledPicture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][bindable][propget][id] */ HRESULT STDMETHODCALLTYPE IAcPiCommandButton_get_Enabled_Proxy( 
    IAcPiCommandButton * This,
    /* [retval][out] */ VARIANT_BOOL *bEnabled);


void __RPC_STUB IAcPiCommandButton_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][bindable][propput][id] */ HRESULT STDMETHODCALLTYPE IAcPiCommandButton_put_Enabled_Proxy( 
    IAcPiCommandButton * This,
    /* [in] */ VARIANT_BOOL bEnabled);


void __RPC_STUB IAcPiCommandButton_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][bindable][propget][id] */ HRESULT STDMETHODCALLTYPE IAcPiCommandButton_get_Checked_Proxy( 
    IAcPiCommandButton * This,
    /* [retval][out] */ VARIANT_BOOL *bChecked);


void __RPC_STUB IAcPiCommandButton_get_Checked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][bindable][propput][id] */ HRESULT STDMETHODCALLTYPE IAcPiCommandButton_put_Checked_Proxy( 
    IAcPiCommandButton * This,
    /* [in] */ VARIANT_BOOL bChecked);


void __RPC_STUB IAcPiCommandButton_put_Checked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IAcPiCommandButton_get_ButtonStyle_Proxy( 
    IAcPiCommandButton * This,
    /* [retval][out] */ long *style);


void __RPC_STUB IAcPiCommandButton_get_ButtonStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiCommandButton_Execute_Proxy( 
    IAcPiCommandButton * This,
    /* [in] */ VARIANT Objects);


void __RPC_STUB IAcPiCommandButton_Execute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPiCommandButton_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_acpi_0259 */
/* [local] */ 

#define IPropertyInspectorSink IAcPiPropertyInspectorEventsSink
#define IID_IPropertyInspectorSink IID_IAcPiPropertyInspectorEventsSink


extern RPC_IF_HANDLE __MIDL_itf_acpi_0259_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_acpi_0259_v0_0_s_ifspec;

#ifndef __IAcPiPropertyInspectorEventsSink_INTERFACE_DEFINED__
#define __IAcPiPropertyInspectorEventsSink_INTERFACE_DEFINED__

/* interface IAcPiPropertyInspectorEventsSink */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPiPropertyInspectorEventsSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3EAF5E3F-5D7B-4873-B8F4-A6D9B2D1EB33")
    IAcPiPropertyInspectorEventsSink : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Rebuild( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RefreshControl( 
            /* [in] */ VARIANT var,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPropertyControl( 
            /* [in] */ VARIANT var,
            /* [out] */ IUnknown **ppUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPiPropertyInspectorEventsSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPiPropertyInspectorEventsSink * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPiPropertyInspectorEventsSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPiPropertyInspectorEventsSink * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Rebuild )( 
            IAcPiPropertyInspectorEventsSink * This,
            /* [in] */ DWORD dwFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RefreshControl )( 
            IAcPiPropertyInspectorEventsSink * This,
            /* [in] */ VARIANT var,
            /* [in] */ DWORD dwFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyControl )( 
            IAcPiPropertyInspectorEventsSink * This,
            /* [in] */ VARIANT var,
            /* [out] */ IUnknown **ppUnk);
        
        END_INTERFACE
    } IAcPiPropertyInspectorEventsSinkVtbl;

    interface IAcPiPropertyInspectorEventsSink
    {
        CONST_VTBL struct IAcPiPropertyInspectorEventsSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPiPropertyInspectorEventsSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPiPropertyInspectorEventsSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPiPropertyInspectorEventsSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPiPropertyInspectorEventsSink_Rebuild(This,dwFlags)	\
    (This)->lpVtbl -> Rebuild(This,dwFlags)

#define IAcPiPropertyInspectorEventsSink_RefreshControl(This,var,dwFlags)	\
    (This)->lpVtbl -> RefreshControl(This,var,dwFlags)

#define IAcPiPropertyInspectorEventsSink_GetPropertyControl(This,var,ppUnk)	\
    (This)->lpVtbl -> GetPropertyControl(This,var,ppUnk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspectorEventsSink_Rebuild_Proxy( 
    IAcPiPropertyInspectorEventsSink * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAcPiPropertyInspectorEventsSink_Rebuild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspectorEventsSink_RefreshControl_Proxy( 
    IAcPiPropertyInspectorEventsSink * This,
    /* [in] */ VARIANT var,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAcPiPropertyInspectorEventsSink_RefreshControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspectorEventsSink_GetPropertyControl_Proxy( 
    IAcPiPropertyInspectorEventsSink * This,
    /* [in] */ VARIANT var,
    /* [out] */ IUnknown **ppUnk);


void __RPC_STUB IAcPiPropertyInspectorEventsSink_GetPropertyControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPiPropertyInspectorEventsSink_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_acpi_0260 */
/* [local] */ 

#define IPropertyInspectorInputEventSink IAcPiPropertyInspectorInputEventSink
#define IID_IPropertyInspectorInputEventSink IID_IAcPiPropertyInspectorInputEventSink


extern RPC_IF_HANDLE __MIDL_itf_acpi_0260_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_acpi_0260_v0_0_s_ifspec;

#ifndef __IAcPiPropertyInspectorInputEventSink_INTERFACE_DEFINED__
#define __IAcPiPropertyInspectorInputEventSink_INTERFACE_DEFINED__

/* interface IAcPiPropertyInspectorInputEventSink */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPiPropertyInspectorInputEventSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B6E9DB08-8B45-4ad2-B33C-985BBE4F3756")
    IAcPiPropertyInspectorInputEventSink : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnKeyDown( 
            /* [in] */ long pnChar,
            /* [in] */ long keyData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnPopulateContextMenu( 
            /* [in] */ VARIANT *flagArray,
            /* [in] */ VARIANT *idArray,
            /* [in] */ VARIANT *szItemArray) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnContextMenuCommand( 
            /* [in] */ int cmdId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAcPiPropertyInspectorInputEventSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPiPropertyInspectorInputEventSink * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPiPropertyInspectorInputEventSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPiPropertyInspectorInputEventSink * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnKeyDown )( 
            IAcPiPropertyInspectorInputEventSink * This,
            /* [in] */ long pnChar,
            /* [in] */ long keyData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnPopulateContextMenu )( 
            IAcPiPropertyInspectorInputEventSink * This,
            /* [in] */ VARIANT *flagArray,
            /* [in] */ VARIANT *idArray,
            /* [in] */ VARIANT *szItemArray);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnContextMenuCommand )( 
            IAcPiPropertyInspectorInputEventSink * This,
            /* [in] */ int cmdId);
        
        END_INTERFACE
    } IAcPiPropertyInspectorInputEventSinkVtbl;

    interface IAcPiPropertyInspectorInputEventSink
    {
        CONST_VTBL struct IAcPiPropertyInspectorInputEventSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPiPropertyInspectorInputEventSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcPiPropertyInspectorInputEventSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcPiPropertyInspectorInputEventSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcPiPropertyInspectorInputEventSink_OnKeyDown(This,pnChar,keyData)	\
    (This)->lpVtbl -> OnKeyDown(This,pnChar,keyData)

#define IAcPiPropertyInspectorInputEventSink_OnPopulateContextMenu(This,flagArray,idArray,szItemArray)	\
    (This)->lpVtbl -> OnPopulateContextMenu(This,flagArray,idArray,szItemArray)

#define IAcPiPropertyInspectorInputEventSink_OnContextMenuCommand(This,cmdId)	\
    (This)->lpVtbl -> OnContextMenuCommand(This,cmdId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspectorInputEventSink_OnKeyDown_Proxy( 
    IAcPiPropertyInspectorInputEventSink * This,
    /* [in] */ long pnChar,
    /* [in] */ long keyData);


void __RPC_STUB IAcPiPropertyInspectorInputEventSink_OnKeyDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspectorInputEventSink_OnPopulateContextMenu_Proxy( 
    IAcPiPropertyInspectorInputEventSink * This,
    /* [in] */ VARIANT *flagArray,
    /* [in] */ VARIANT *idArray,
    /* [in] */ VARIANT *szItemArray);


void __RPC_STUB IAcPiPropertyInspectorInputEventSink_OnPopulateContextMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcPiPropertyInspectorInputEventSink_OnContextMenuCommand_Proxy( 
    IAcPiPropertyInspectorInputEventSink * This,
    /* [in] */ int cmdId);


void __RPC_STUB IAcPiPropertyInspectorInputEventSink_OnContextMenuCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAcPiPropertyInspectorInputEventSink_INTERFACE_DEFINED__ */



#ifndef __ACPILib_LIBRARY_DEFINED__
#define __ACPILib_LIBRARY_DEFINED__

/* library ACPILib */
/* [custom][helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ACPILib;

EXTERN_C const CLSID CLSID_AcPiPropertyInspector;

#ifdef __cplusplus

class DECLSPEC_UUID("31DBB451-9109-41EA-854C-B25905225AEA")
AcPiPropertyInspector;
#endif
#endif /* __ACPILib_LIBRARY_DEFINED__ */

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