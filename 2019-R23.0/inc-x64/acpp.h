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
/* Compiler settings for U:\develop\global\src\coreapps\opm\AcPp.idl:
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

#ifndef __AcPp_i_h__
#define __AcPp_i_h__

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


#ifndef __IAcPpPaletteSet2_FWD_DEFINED__
#define __IAcPpPaletteSet2_FWD_DEFINED__
typedef interface IAcPpPaletteSet2 IAcPpPaletteSet2;

#endif 	/* __IAcPpPaletteSet2_FWD_DEFINED__ */


#ifndef __IAcPpPaletteSetEvents_FWD_DEFINED__
#define __IAcPpPaletteSetEvents_FWD_DEFINED__
typedef interface IAcPpPaletteSetEvents IAcPpPaletteSetEvents;

#endif 	/* __IAcPpPaletteSetEvents_FWD_DEFINED__ */


#ifndef __IAcPpNavTreeNode_FWD_DEFINED__
#define __IAcPpNavTreeNode_FWD_DEFINED__
typedef interface IAcPpNavTreeNode IAcPpNavTreeNode;

#endif 	/* __IAcPpNavTreeNode_FWD_DEFINED__ */


#ifndef __IAcPpNavTreeNodeCollectionIter_FWD_DEFINED__
#define __IAcPpNavTreeNodeCollectionIter_FWD_DEFINED__
typedef interface IAcPpNavTreeNodeCollectionIter IAcPpNavTreeNodeCollectionIter;

#endif 	/* __IAcPpNavTreeNodeCollectionIter_FWD_DEFINED__ */


#ifndef __IAcPpNavTreeNodeCollection_FWD_DEFINED__
#define __IAcPpNavTreeNodeCollection_FWD_DEFINED__
typedef interface IAcPpNavTreeNodeCollection IAcPpNavTreeNodeCollection;

#endif 	/* __IAcPpNavTreeNodeCollection_FWD_DEFINED__ */


#ifndef __IAcPpNavTreeCmdBtn_FWD_DEFINED__
#define __IAcPpNavTreeCmdBtn_FWD_DEFINED__
typedef interface IAcPpNavTreeCmdBtn IAcPpNavTreeCmdBtn;

#endif 	/* __IAcPpNavTreeCmdBtn_FWD_DEFINED__ */


#ifndef __IAcPpNavTreeCmdBtnCollectionIter_FWD_DEFINED__
#define __IAcPpNavTreeCmdBtnCollectionIter_FWD_DEFINED__
typedef interface IAcPpNavTreeCmdBtnCollectionIter IAcPpNavTreeCmdBtnCollectionIter;

#endif 	/* __IAcPpNavTreeCmdBtnCollectionIter_FWD_DEFINED__ */


#ifndef __IAcPpNavTreeCmdBtnCollection_FWD_DEFINED__
#define __IAcPpNavTreeCmdBtnCollection_FWD_DEFINED__
typedef interface IAcPpNavTreeCmdBtnCollection IAcPpNavTreeCmdBtnCollection;

#endif 	/* __IAcPpNavTreeCmdBtnCollection_FWD_DEFINED__ */


#ifndef __IAcPpNavTree_FWD_DEFINED__
#define __IAcPpNavTree_FWD_DEFINED__
typedef interface IAcPpNavTree IAcPpNavTree;

#endif 	/* __IAcPpNavTree_FWD_DEFINED__ */


#ifndef __IAcPpNavTreeEvents_FWD_DEFINED__
#define __IAcPpNavTreeEvents_FWD_DEFINED__
typedef interface IAcPpNavTreeEvents IAcPpNavTreeEvents;

#endif 	/* __IAcPpNavTreeEvents_FWD_DEFINED__ */


#ifndef __IAcPpPalette2_FWD_DEFINED__
#define __IAcPpPalette2_FWD_DEFINED__
typedef interface IAcPpPalette2 IAcPpPalette2;

#endif 	/* __IAcPpPalette2_FWD_DEFINED__ */


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


#ifndef __AcPpPalette2_FWD_DEFINED__
#define __AcPpPalette2_FWD_DEFINED__

#ifdef __cplusplus
typedef class AcPpPalette2 AcPpPalette2;
#else
typedef struct AcPpPalette2 AcPpPalette2;
#endif /* __cplusplus */

#endif 	/* __AcPpPalette2_FWD_DEFINED__ */


#ifndef __AcPpNavTree_FWD_DEFINED__
#define __AcPpNavTree_FWD_DEFINED__

#ifdef __cplusplus
typedef class AcPpNavTree AcPpNavTree;
#else
typedef struct AcPpNavTree AcPpNavTree;
#endif /* __cplusplus */

#endif 	/* __AcPpNavTree_FWD_DEFINED__ */


#ifndef __AcPpNavTreeNode_FWD_DEFINED__
#define __AcPpNavTreeNode_FWD_DEFINED__

#ifdef __cplusplus
typedef class AcPpNavTreeNode AcPpNavTreeNode;
#else
typedef struct AcPpNavTreeNode AcPpNavTreeNode;
#endif /* __cplusplus */

#endif 	/* __AcPpNavTreeNode_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "acpi.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_AcPp_0000_0000 */
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


extern RPC_IF_HANDLE __MIDL_itf_AcPp_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AcPp_0000_0000_v0_0_s_ifspec;

#ifndef __IAcPpAcadInput_INTERFACE_DEFINED__
#define __IAcPpAcadInput_INTERFACE_DEFINED__

/* interface IAcPpAcadInput */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum StatusType
    {
        StatusPrompting	= -1,
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
    {
        GetAngle	= 1,
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
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpAcadInput_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpAcadInput_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpAcadInput_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define IAcPpAcadInput_put_Value(This,newVal)	\
    ( (This)->lpVtbl -> put_Value(This,newVal) ) 

#define IAcPpAcadInput_get_Status(This,pVal)	\
    ( (This)->lpVtbl -> get_Status(This,pVal) ) 

#define IAcPpAcadInput_put_Status(This,newVal)	\
    ( (This)->lpVtbl -> put_Status(This,newVal) ) 

#define IAcPpAcadInput_get_Document(This,pVal)	\
    ( (This)->lpVtbl -> get_Document(This,pVal) ) 

#define IAcPpAcadInput_put_Document(This,newVal)	\
    ( (This)->lpVtbl -> put_Document(This,newVal) ) 

#define IAcPpAcadInput_get_CrOnly(This,pVal)	\
    ( (This)->lpVtbl -> get_CrOnly(This,pVal) ) 

#define IAcPpAcadInput_put_CrOnly(This,newVal)	\
    ( (This)->lpVtbl -> put_CrOnly(This,newVal) ) 

#define IAcPpAcadInput_get_Prompt(This,pVal)	\
    ( (This)->lpVtbl -> get_Prompt(This,pVal) ) 

#define IAcPpAcadInput_put_Prompt(This,newVal)	\
    ( (This)->lpVtbl -> put_Prompt(This,newVal) ) 

#define IAcPpAcadInput_get_Prompt2(This,pVal)	\
    ( (This)->lpVtbl -> get_Prompt2(This,pVal) ) 

#define IAcPpAcadInput_put_Prompt2(This,newVal)	\
    ( (This)->lpVtbl -> put_Prompt2(This,newVal) ) 

#define IAcPpAcadInput_get_InitGetBit(This,pVal)	\
    ( (This)->lpVtbl -> get_InitGetBit(This,pVal) ) 

#define IAcPpAcadInput_put_InitGetBit(This,newVal)	\
    ( (This)->lpVtbl -> put_InitGetBit(This,newVal) ) 

#define IAcPpAcadInput_get_InitGetKword(This,pVal)	\
    ( (This)->lpVtbl -> get_InitGetKword(This,pVal) ) 

#define IAcPpAcadInput_put_InitGetKword(This,newVal)	\
    ( (This)->lpVtbl -> put_InitGetKword(This,newVal) ) 

#define IAcPpAcadInput_get_BasePoint(This,pVal)	\
    ( (This)->lpVtbl -> get_BasePoint(This,pVal) ) 

#define IAcPpAcadInput_put_BasePoint(This,newVal)	\
    ( (This)->lpVtbl -> put_BasePoint(This,newVal) ) 

#define IAcPpAcadInput_get_PromptType(This,pVal)	\
    ( (This)->lpVtbl -> get_PromptType(This,pVal) ) 

#define IAcPpAcadInput_put_PromptType(This,newVal)	\
    ( (This)->lpVtbl -> put_PromptType(This,newVal) ) 

#define IAcPpAcadInput_get_EnableNotification(This,pVal)	\
    ( (This)->lpVtbl -> get_EnableNotification(This,pVal) ) 

#define IAcPpAcadInput_put_EnableNotification(This,newVal)	\
    ( (This)->lpVtbl -> put_EnableNotification(This,newVal) ) 

#define IAcPpAcadInput_DoPrompt(This)	\
    ( (This)->lpVtbl -> DoPrompt(This) ) 

#define IAcPpAcadInput_CancelPrompt(This)	\
    ( (This)->lpVtbl -> CancelPrompt(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpPalette_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpPalette_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpPalette_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IAcPpPalette_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 

#define IAcPpPalette_get_InspectorControl(This,pInspector)	\
    ( (This)->lpVtbl -> get_InspectorControl(This,pInspector) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpPaletteEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpPaletteEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpPaletteEvents_OnNameChanged(This,newName)	\
    ( (This)->lpVtbl -> OnNameChanged(This,newName) ) 

#define IAcPpPaletteEvents_OnSelectionChanged(This,newObjectArray,newPropMgrArray,bHandled)	\
    ( (This)->lpVtbl -> OnSelectionChanged(This,newObjectArray,newPropMgrArray,bHandled) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpPaletteEvents_INTERFACE_DEFINED__ */


#ifndef __IAcPpPaletteSet_INTERFACE_DEFINED__
#define __IAcPpPaletteSet_INTERFACE_DEFINED__

/* interface IAcPpPaletteSet */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum DockPos
    {
        Floating	= -1,
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
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpPaletteSet_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpPaletteSet_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpPaletteSet_AddPalette(This,pPalette)	\
    ( (This)->lpVtbl -> AddPalette(This,pPalette) ) 

#define IAcPpPaletteSet_DeletePalette(This,pPalette)	\
    ( (This)->lpVtbl -> DeletePalette(This,pPalette) ) 

#define IAcPpPaletteSet_InsertPalette(This,index,pPalette)	\
    ( (This)->lpVtbl -> InsertPalette(This,index,pPalette) ) 

#define IAcPpPaletteSet_GetPalette(This,index,pPalette)	\
    ( (This)->lpVtbl -> GetPalette(This,index,pPalette) ) 

#define IAcPpPaletteSet_GetPaletteByName(This,paletteName,pPalette)	\
    ( (This)->lpVtbl -> GetPaletteByName(This,paletteName,pPalette) ) 

#define IAcPpPaletteSet_ActivatePalette(This,pPalette)	\
    ( (This)->lpVtbl -> ActivatePalette(This,pPalette) ) 

#define IAcPpPaletteSet_get_PaletteCount(This,nPalettes)	\
    ( (This)->lpVtbl -> get_PaletteCount(This,nPalettes) ) 

#define IAcPpPaletteSet_get_Visibility(This,bIsVisible)	\
    ( (This)->lpVtbl -> get_Visibility(This,bIsVisible) ) 

#define IAcPpPaletteSet_put_Visibility(This,bIsVisible)	\
    ( (This)->lpVtbl -> put_Visibility(This,bIsVisible) ) 

#define IAcPpPaletteSet_get_CurrentIndex(This,nCurrentIndex)	\
    ( (This)->lpVtbl -> get_CurrentIndex(This,nCurrentIndex) ) 

#define IAcPpPaletteSet_GetDockingState(This,nDockPos,left,top,width,height)	\
    ( (This)->lpVtbl -> GetDockingState(This,nDockPos,left,top,width,height) ) 

#define IAcPpPaletteSet_SetDockingState(This,nDockPos,left,top,width,height)	\
    ( (This)->lpVtbl -> SetDockingState(This,nDockPos,left,top,width,height) ) 

#define IAcPpPaletteSet_GetFloatingRect(This,left,top,width,height)	\
    ( (This)->lpVtbl -> GetFloatingRect(This,left,top,width,height) ) 

#define IAcPpPaletteSet_GetDockingRect(This,nDockPos,left,top,width,height)	\
    ( (This)->lpVtbl -> GetDockingRect(This,nDockPos,left,top,width,height) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpPaletteSet_INTERFACE_DEFINED__ */


#ifndef __IAcPpPaletteSet2_INTERFACE_DEFINED__
#define __IAcPpPaletteSet2_INTERFACE_DEFINED__

/* interface IAcPpPaletteSet2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpPaletteSet2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F5EEE553-BE37-4513-8D10-4F2721BAE333")
    IAcPpPaletteSet2 : public IUnknown
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Anchored( 
            /* [out] */ VARIANT_BOOL *isAnchored) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcPpPaletteSet2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpPaletteSet2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpPaletteSet2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpPaletteSet2 * This);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Anchored )( 
            IAcPpPaletteSet2 * This,
            /* [out] */ VARIANT_BOOL *isAnchored);
        
        END_INTERFACE
    } IAcPpPaletteSet2Vtbl;

    interface IAcPpPaletteSet2
    {
        CONST_VTBL struct IAcPpPaletteSet2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpPaletteSet2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpPaletteSet2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpPaletteSet2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpPaletteSet2_get_Anchored(This,isAnchored)	\
    ( (This)->lpVtbl -> get_Anchored(This,isAnchored) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpPaletteSet2_INTERFACE_DEFINED__ */


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
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpPaletteSetEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpPaletteSetEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpPaletteSetEvents_OnPaletteAdded(This,pNewPalette)	\
    ( (This)->lpVtbl -> OnPaletteAdded(This,pNewPalette) ) 

#define IAcPpPaletteSetEvents_OnPaletteDeleted(This,pPalette)	\
    ( (This)->lpVtbl -> OnPaletteDeleted(This,pPalette) ) 

#define IAcPpPaletteSetEvents_OnPaletteActivated(This,pPalette)	\
    ( (This)->lpVtbl -> OnPaletteActivated(This,pPalette) ) 

#define IAcPpPaletteSetEvents_OnPaletteDeActivated(This,pPalette)	\
    ( (This)->lpVtbl -> OnPaletteDeActivated(This,pPalette) ) 

#define IAcPpPaletteSetEvents_OnSelectionChanged(This,newObjectArray,newPropMgrArray)	\
    ( (This)->lpVtbl -> OnSelectionChanged(This,newObjectArray,newPropMgrArray) ) 

#define IAcPpPaletteSetEvents_OnVisibilityChanged(This,bIsVisible)	\
    ( (This)->lpVtbl -> OnVisibilityChanged(This,bIsVisible) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpPaletteSetEvents_INTERFACE_DEFINED__ */


#ifndef __IAcPpNavTreeNode_INTERFACE_DEFINED__
#define __IAcPpNavTreeNode_INTERFACE_DEFINED__

/* interface IAcPpNavTreeNode */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpNavTreeNode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11E68B1B-2A9F-4b1d-BB58-CD5A43FB6F30")
    IAcPpNavTreeNode : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ long *pID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParentID( 
            /* [retval][out] */ long *pID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Label( 
            /* [retval][out] */ BSTR *pLabel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeftIconRes( 
            /* [retval][out] */ BSTR *pPath) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeftIconResType( 
            /* [retval][out] */ ULONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObject( 
            VARIANT *pObject) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcPpNavTreeNodeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpNavTreeNode * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpNavTreeNode * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpNavTreeNode * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IAcPpNavTreeNode * This,
            /* [retval][out] */ long *pID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParentID )( 
            IAcPpNavTreeNode * This,
            /* [retval][out] */ long *pID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Label )( 
            IAcPpNavTreeNode * This,
            /* [retval][out] */ BSTR *pLabel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftIconRes )( 
            IAcPpNavTreeNode * This,
            /* [retval][out] */ BSTR *pPath);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LeftIconResType )( 
            IAcPpNavTreeNode * This,
            /* [retval][out] */ ULONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetObject )( 
            IAcPpNavTreeNode * This,
            VARIANT *pObject);
        
        END_INTERFACE
    } IAcPpNavTreeNodeVtbl;

    interface IAcPpNavTreeNode
    {
        CONST_VTBL struct IAcPpNavTreeNodeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpNavTreeNode_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpNavTreeNode_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpNavTreeNode_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpNavTreeNode_get_ID(This,pID)	\
    ( (This)->lpVtbl -> get_ID(This,pID) ) 

#define IAcPpNavTreeNode_get_ParentID(This,pID)	\
    ( (This)->lpVtbl -> get_ParentID(This,pID) ) 

#define IAcPpNavTreeNode_get_Label(This,pLabel)	\
    ( (This)->lpVtbl -> get_Label(This,pLabel) ) 

#define IAcPpNavTreeNode_get_LeftIconRes(This,pPath)	\
    ( (This)->lpVtbl -> get_LeftIconRes(This,pPath) ) 

#define IAcPpNavTreeNode_get_LeftIconResType(This,pVal)	\
    ( (This)->lpVtbl -> get_LeftIconResType(This,pVal) ) 

#define IAcPpNavTreeNode_GetObject(This,pObject)	\
    ( (This)->lpVtbl -> GetObject(This,pObject) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpNavTreeNode_INTERFACE_DEFINED__ */


#ifndef __IAcPpNavTreeNodeCollectionIter_INTERFACE_DEFINED__
#define __IAcPpNavTreeNodeCollectionIter_INTERFACE_DEFINED__

/* interface IAcPpNavTreeNodeCollectionIter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpNavTreeNodeCollectionIter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("82AE492A-56B9-45cb-81DD-9678CA98E3B4")
    IAcPpNavTreeNodeCollectionIter : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Next( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Current( 
            /* [out] */ IAcPpNavTreeNode **pNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Done( 
            /* [out] */ VARIANT_BOOL *pBool) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcPpNavTreeNodeCollectionIterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpNavTreeNodeCollectionIter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpNavTreeNodeCollectionIter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpNavTreeNodeCollectionIter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IAcPpNavTreeNodeCollectionIter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IAcPpNavTreeNodeCollectionIter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Current )( 
            IAcPpNavTreeNodeCollectionIter * This,
            /* [out] */ IAcPpNavTreeNode **pNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Done )( 
            IAcPpNavTreeNodeCollectionIter * This,
            /* [out] */ VARIANT_BOOL *pBool);
        
        END_INTERFACE
    } IAcPpNavTreeNodeCollectionIterVtbl;

    interface IAcPpNavTreeNodeCollectionIter
    {
        CONST_VTBL struct IAcPpNavTreeNodeCollectionIterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpNavTreeNodeCollectionIter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpNavTreeNodeCollectionIter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpNavTreeNodeCollectionIter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpNavTreeNodeCollectionIter_Start(This)	\
    ( (This)->lpVtbl -> Start(This) ) 

#define IAcPpNavTreeNodeCollectionIter_Next(This)	\
    ( (This)->lpVtbl -> Next(This) ) 

#define IAcPpNavTreeNodeCollectionIter_Current(This,pNode)	\
    ( (This)->lpVtbl -> Current(This,pNode) ) 

#define IAcPpNavTreeNodeCollectionIter_Done(This,pBool)	\
    ( (This)->lpVtbl -> Done(This,pBool) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpNavTreeNodeCollectionIter_INTERFACE_DEFINED__ */


#ifndef __IAcPpNavTreeNodeCollection_INTERFACE_DEFINED__
#define __IAcPpNavTreeNodeCollection_INTERFACE_DEFINED__

/* interface IAcPpNavTreeNodeCollection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpNavTreeNodeCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A28A23F-9714-4c48-8BE9-CB8D591F1F3C")
    IAcPpNavTreeNodeCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddNode( 
            /* [in] */ IAcPpNavTreeNode *pNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteNode( 
            /* [in] */ IAcPpNavTreeNode *pNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteAllNodes( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNodeCollectionIter( 
            /* [retval][out] */ IAcPpNavTreeNodeCollectionIter **PIter) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcPpNavTreeNodeCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpNavTreeNodeCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpNavTreeNodeCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpNavTreeNodeCollection * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddNode )( 
            IAcPpNavTreeNodeCollection * This,
            /* [in] */ IAcPpNavTreeNode *pNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteNode )( 
            IAcPpNavTreeNodeCollection * This,
            /* [in] */ IAcPpNavTreeNode *pNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteAllNodes )( 
            IAcPpNavTreeNodeCollection * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNodeCollectionIter )( 
            IAcPpNavTreeNodeCollection * This,
            /* [retval][out] */ IAcPpNavTreeNodeCollectionIter **PIter);
        
        END_INTERFACE
    } IAcPpNavTreeNodeCollectionVtbl;

    interface IAcPpNavTreeNodeCollection
    {
        CONST_VTBL struct IAcPpNavTreeNodeCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpNavTreeNodeCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpNavTreeNodeCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpNavTreeNodeCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpNavTreeNodeCollection_AddNode(This,pNode)	\
    ( (This)->lpVtbl -> AddNode(This,pNode) ) 

#define IAcPpNavTreeNodeCollection_DeleteNode(This,pNode)	\
    ( (This)->lpVtbl -> DeleteNode(This,pNode) ) 

#define IAcPpNavTreeNodeCollection_DeleteAllNodes(This)	\
    ( (This)->lpVtbl -> DeleteAllNodes(This) ) 

#define IAcPpNavTreeNodeCollection_GetNodeCollectionIter(This,PIter)	\
    ( (This)->lpVtbl -> GetNodeCollectionIter(This,PIter) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpNavTreeNodeCollection_INTERFACE_DEFINED__ */


#ifndef __IAcPpNavTreeCmdBtn_INTERFACE_DEFINED__
#define __IAcPpNavTreeCmdBtn_INTERFACE_DEFINED__

/* interface IAcPpNavTreeCmdBtn */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpNavTreeCmdBtn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("17F515C8-18E6-4731-A29A-12A5AB72F2A9")
    IAcPpNavTreeCmdBtn : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBtnImage( 
            /* [out] */ BSTR *pPath,
            /* [out] */ ULONG *pImgType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Execute( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcPpNavTreeCmdBtnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpNavTreeCmdBtn * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpNavTreeCmdBtn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpNavTreeCmdBtn * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IAcPpNavTreeCmdBtn * This,
            /* [retval][out] */ BSTR *pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBtnImage )( 
            IAcPpNavTreeCmdBtn * This,
            /* [out] */ BSTR *pPath,
            /* [out] */ ULONG *pImgType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Execute )( 
            IAcPpNavTreeCmdBtn * This);
        
        END_INTERFACE
    } IAcPpNavTreeCmdBtnVtbl;

    interface IAcPpNavTreeCmdBtn
    {
        CONST_VTBL struct IAcPpNavTreeCmdBtnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpNavTreeCmdBtn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpNavTreeCmdBtn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpNavTreeCmdBtn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpNavTreeCmdBtn_get_Name(This,pName)	\
    ( (This)->lpVtbl -> get_Name(This,pName) ) 

#define IAcPpNavTreeCmdBtn_GetBtnImage(This,pPath,pImgType)	\
    ( (This)->lpVtbl -> GetBtnImage(This,pPath,pImgType) ) 

#define IAcPpNavTreeCmdBtn_Execute(This)	\
    ( (This)->lpVtbl -> Execute(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpNavTreeCmdBtn_INTERFACE_DEFINED__ */


#ifndef __IAcPpNavTreeCmdBtnCollectionIter_INTERFACE_DEFINED__
#define __IAcPpNavTreeCmdBtnCollectionIter_INTERFACE_DEFINED__

/* interface IAcPpNavTreeCmdBtnCollectionIter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpNavTreeCmdBtnCollectionIter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B14B5F9-D967-4c62-AE3B-FAD4CF051F63")
    IAcPpNavTreeCmdBtnCollectionIter : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Next( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Current( 
            /* [out] */ IAcPpNavTreeCmdBtn **pNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Done( 
            /* [out] */ VARIANT_BOOL *pBool) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcPpNavTreeCmdBtnCollectionIterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpNavTreeCmdBtnCollectionIter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpNavTreeCmdBtnCollectionIter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpNavTreeCmdBtnCollectionIter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IAcPpNavTreeCmdBtnCollectionIter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IAcPpNavTreeCmdBtnCollectionIter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Current )( 
            IAcPpNavTreeCmdBtnCollectionIter * This,
            /* [out] */ IAcPpNavTreeCmdBtn **pNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Done )( 
            IAcPpNavTreeCmdBtnCollectionIter * This,
            /* [out] */ VARIANT_BOOL *pBool);
        
        END_INTERFACE
    } IAcPpNavTreeCmdBtnCollectionIterVtbl;

    interface IAcPpNavTreeCmdBtnCollectionIter
    {
        CONST_VTBL struct IAcPpNavTreeCmdBtnCollectionIterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpNavTreeCmdBtnCollectionIter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpNavTreeCmdBtnCollectionIter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpNavTreeCmdBtnCollectionIter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpNavTreeCmdBtnCollectionIter_Start(This)	\
    ( (This)->lpVtbl -> Start(This) ) 

#define IAcPpNavTreeCmdBtnCollectionIter_Next(This)	\
    ( (This)->lpVtbl -> Next(This) ) 

#define IAcPpNavTreeCmdBtnCollectionIter_Current(This,pNode)	\
    ( (This)->lpVtbl -> Current(This,pNode) ) 

#define IAcPpNavTreeCmdBtnCollectionIter_Done(This,pBool)	\
    ( (This)->lpVtbl -> Done(This,pBool) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpNavTreeCmdBtnCollectionIter_INTERFACE_DEFINED__ */


#ifndef __IAcPpNavTreeCmdBtnCollection_INTERFACE_DEFINED__
#define __IAcPpNavTreeCmdBtnCollection_INTERFACE_DEFINED__

/* interface IAcPpNavTreeCmdBtnCollection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpNavTreeCmdBtnCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5AD8767E-93C1-4256-8031-29D726F4D8ED")
    IAcPpNavTreeCmdBtnCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddButton( 
            /* [in] */ IAcPpNavTreeCmdBtn *pBtn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteButton( 
            /* [in] */ IAcPpNavTreeCmdBtn *pBtn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteAllButtons( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCmdBtnCollectionIter( 
            /* [retval][out] */ IAcPpNavTreeCmdBtnCollectionIter **pIter) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcPpNavTreeCmdBtnCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpNavTreeCmdBtnCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpNavTreeCmdBtnCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpNavTreeCmdBtnCollection * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddButton )( 
            IAcPpNavTreeCmdBtnCollection * This,
            /* [in] */ IAcPpNavTreeCmdBtn *pBtn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteButton )( 
            IAcPpNavTreeCmdBtnCollection * This,
            /* [in] */ IAcPpNavTreeCmdBtn *pBtn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteAllButtons )( 
            IAcPpNavTreeCmdBtnCollection * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCmdBtnCollectionIter )( 
            IAcPpNavTreeCmdBtnCollection * This,
            /* [retval][out] */ IAcPpNavTreeCmdBtnCollectionIter **pIter);
        
        END_INTERFACE
    } IAcPpNavTreeCmdBtnCollectionVtbl;

    interface IAcPpNavTreeCmdBtnCollection
    {
        CONST_VTBL struct IAcPpNavTreeCmdBtnCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpNavTreeCmdBtnCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpNavTreeCmdBtnCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpNavTreeCmdBtnCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpNavTreeCmdBtnCollection_AddButton(This,pBtn)	\
    ( (This)->lpVtbl -> AddButton(This,pBtn) ) 

#define IAcPpNavTreeCmdBtnCollection_DeleteButton(This,pBtn)	\
    ( (This)->lpVtbl -> DeleteButton(This,pBtn) ) 

#define IAcPpNavTreeCmdBtnCollection_DeleteAllButtons(This)	\
    ( (This)->lpVtbl -> DeleteAllButtons(This) ) 

#define IAcPpNavTreeCmdBtnCollection_GetCmdBtnCollectionIter(This,pIter)	\
    ( (This)->lpVtbl -> GetCmdBtnCollectionIter(This,pIter) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpNavTreeCmdBtnCollection_INTERFACE_DEFINED__ */


#ifndef __IAcPpNavTree_INTERFACE_DEFINED__
#define __IAcPpNavTree_INTERFACE_DEFINED__

/* interface IAcPpNavTree */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpNavTree;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3412E0C1-20F7-43dd-B9ED-4299CCD4506C")
    IAcPpNavTree : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( 
            /* [in] */ IAcPpNavTreeNodeCollection *pNodeCollection,
            /* [in] */ IAcPpNavTreeCmdBtnCollection *pCmdBtnCollection) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcPpNavTreeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpNavTree * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpNavTree * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpNavTree * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IAcPpNavTree * This,
            /* [in] */ IAcPpNavTreeNodeCollection *pNodeCollection,
            /* [in] */ IAcPpNavTreeCmdBtnCollection *pCmdBtnCollection);
        
        END_INTERFACE
    } IAcPpNavTreeVtbl;

    interface IAcPpNavTree
    {
        CONST_VTBL struct IAcPpNavTreeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpNavTree_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpNavTree_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpNavTree_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpNavTree_Reset(This,pNodeCollection,pCmdBtnCollection)	\
    ( (This)->lpVtbl -> Reset(This,pNodeCollection,pCmdBtnCollection) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpNavTree_INTERFACE_DEFINED__ */


#ifndef __IAcPpNavTreeEvents_INTERFACE_DEFINED__
#define __IAcPpNavTreeEvents_INTERFACE_DEFINED__

/* interface IAcPpNavTreeEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpNavTreeEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E08AE839-864C-42a7-90D2-F700306C811C")
    IAcPpNavTreeEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnSelectionChanged( 
            /* [in] */ VARIANT *pIntArray,
            /* [out] */ VARIANT *pObjUnkArray,
            /* [out][in] */ VARIANT_BOOL *bHandled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnDblClickTreeItem( 
            /* [in] */ ULONG index,
            /* [in] */ UINT nResourceId) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcPpNavTreeEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpNavTreeEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpNavTreeEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpNavTreeEvents * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnSelectionChanged )( 
            IAcPpNavTreeEvents * This,
            /* [in] */ VARIANT *pIntArray,
            /* [out] */ VARIANT *pObjUnkArray,
            /* [out][in] */ VARIANT_BOOL *bHandled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnDblClickTreeItem )( 
            IAcPpNavTreeEvents * This,
            /* [in] */ ULONG index,
            /* [in] */ UINT nResourceId);
        
        END_INTERFACE
    } IAcPpNavTreeEventsVtbl;

    interface IAcPpNavTreeEvents
    {
        CONST_VTBL struct IAcPpNavTreeEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpNavTreeEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpNavTreeEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpNavTreeEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpNavTreeEvents_OnSelectionChanged(This,pIntArray,pObjUnkArray,bHandled)	\
    ( (This)->lpVtbl -> OnSelectionChanged(This,pIntArray,pObjUnkArray,bHandled) ) 

#define IAcPpNavTreeEvents_OnDblClickTreeItem(This,index,nResourceId)	\
    ( (This)->lpVtbl -> OnDblClickTreeItem(This,index,nResourceId) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpNavTreeEvents_INTERFACE_DEFINED__ */


#ifndef __IAcPpPalette2_INTERFACE_DEFINED__
#define __IAcPpPalette2_INTERFACE_DEFINED__

/* interface IAcPpPalette2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcPpPalette2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("772460DD-82F1-4e99-B7BF-5AA4B31E3DB1")
    IAcPpPalette2 : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NavTree( 
            /* [retval][out] */ IAcPpNavTree **pNavTree) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NavTree( 
            /* [in] */ IAcPpNavTree *pNavTree) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAcPpPalette2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAcPpPalette2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAcPpPalette2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAcPpPalette2 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NavTree )( 
            IAcPpPalette2 * This,
            /* [retval][out] */ IAcPpNavTree **pNavTree);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NavTree )( 
            IAcPpPalette2 * This,
            /* [in] */ IAcPpNavTree *pNavTree);
        
        END_INTERFACE
    } IAcPpPalette2Vtbl;

    interface IAcPpPalette2
    {
        CONST_VTBL struct IAcPpPalette2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcPpPalette2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAcPpPalette2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAcPpPalette2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAcPpPalette2_get_NavTree(This,pNavTree)	\
    ( (This)->lpVtbl -> get_NavTree(This,pNavTree) ) 

#define IAcPpPalette2_put_NavTree(This,pNavTree)	\
    ( (This)->lpVtbl -> put_NavTree(This,pNavTree) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcPpPalette2_INTERFACE_DEFINED__ */



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

EXTERN_C const CLSID CLSID_AcPpPalette2;

#ifdef __cplusplus

class DECLSPEC_UUID("D43BEA50-AE29-4bd6-83B6-DE3ED23F517A")
AcPpPalette2;
#endif

EXTERN_C const CLSID CLSID_AcPpNavTree;

#ifdef __cplusplus

class DECLSPEC_UUID("F06460E2-3313-47b0-B464-DAC6B1F45A21")
AcPpNavTree;
#endif

EXTERN_C const CLSID CLSID_AcPpNavTreeNode;

#ifdef __cplusplus

class DECLSPEC_UUID("927E6A91-B46D-4149-B0F9-EC25712FF1E0")
AcPpNavTreeNode;
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