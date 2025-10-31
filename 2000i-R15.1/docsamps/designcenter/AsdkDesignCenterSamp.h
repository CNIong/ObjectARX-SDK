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

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jan 05 15:36:44 1999
 */
/* Compiler settings for V:\acad\tahoe\arx\docsamps\AsdkDesignCenterSamp\AsdkDesignCenterSamp.idl:
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

#ifndef __AsdkDesignCenterSamp_h__
#define __AsdkDesignCenterSamp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAcDcContentBrowser_FWD_DEFINED__
#define __IAcDcContentBrowser_FWD_DEFINED__
typedef interface IAcDcContentBrowser IAcDcContentBrowser;
#endif  /* __IAcDcContentBrowser_FWD_DEFINED__ */


#ifndef __IAcDcContentView_FWD_DEFINED__
#define __IAcDcContentView_FWD_DEFINED__
typedef interface IAcDcContentView IAcDcContentView;
#endif  /* __IAcDcContentView_FWD_DEFINED__ */


#ifndef __IAcDcContentFinderSite_FWD_DEFINED__
#define __IAcDcContentFinderSite_FWD_DEFINED__
typedef interface IAcDcContentFinderSite IAcDcContentFinderSite;
#endif  /* __IAcDcContentFinderSite_FWD_DEFINED__ */


#ifndef __IAcDcContentFinder_FWD_DEFINED__
#define __IAcDcContentFinder_FWD_DEFINED__
typedef interface IAcDcContentFinder IAcDcContentFinder;
#endif  /* __IAcDcContentFinder_FWD_DEFINED__ */


#ifndef __IAsdkDcContent_FWD_DEFINED__
#define __IAsdkDcContent_FWD_DEFINED__
typedef interface IAsdkDcContent IAsdkDcContent;
#endif  /* __IAsdkDcContent_FWD_DEFINED__ */


#ifndef __AsdkDcContent_FWD_DEFINED__
#define __AsdkDcContent_FWD_DEFINED__

#ifdef __cplusplus
typedef class AsdkDcContent AsdkDcContent;
#else
typedef struct AsdkDcContent AsdkDcContent;
#endif /* __cplusplus */

#endif  /* __AsdkDcContent_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_AsdkDesignCenterSamp_0000 */
/* [local] */ 

typedef /* [v1_enum][uuid] */ 
enum dcNavNodeRelation
    {   dcNavNodeFirst  = 0,
    dcNavNodeLast   = dcNavNodeFirst + 1,
    dcNavNodeSort   = dcNavNodeLast + 1
    }   dcNavNodeRelation;

typedef /* [v1_enum][uuid] */ 
enum dcPalColAlignment
    {   dcPalColLeft    = 0,
    dcPalColRight   = 1,
    dcPalColCenter  = 2
    }   dcPalColAlignment;

typedef /* [v1_enum][uuid] */ 
enum dcPalSortOrder
    {   dcPalAscending  = 0,
    dcPalDescending = 1
    }   dcPalSortOrder;

typedef /* [v1_enum][uuid] */ 
enum dcPalViewType
    {   dcPalIcon   = 0,
    dcPalSmallIcon  = 1,
    dcPalList   = 2,
    dcPalReport = 3
    }   dcPalViewType;

typedef /* [v1_enum][uuid] */ 
enum dcFinderTypeMask
    {   dcFinderTypeMaskDate    = 1,
    dcFinderTypeMaskAdvanced    = 2,
    dcFinderTypeMaskFileBased   = 4,
    dcFinderTypeMaskDateReturned    = 8,
    dcFinderTypeMaskSizeReturned    = 16
    }   dcFinderTypeMask;

typedef /* [v1_enum][uuid] */ 
enum dcFinderObjectTypes
    {   dcFinderADeskDrawing    = 0,
    dcFinderADeskBlock  = 1,
    dcFinderADeskLayer  = 2,
    dcFinderADeskActrix = 3,
    dcFinderADeskActrixCatalog  = 4,
    dcFinderADeskXref   = 5,
    dcFinderADeskLinetypes  = 6,
    dcFinderThirdParty  = 7,
    dcFinderADeskLayouts    = 8,
    dcFinderADeskDimStyles  = 9,
    dcFinderADeskTextStyles = 10
    }   dcFinderObjectTypes;

typedef /* [v1_enum][uuid] */ 
enum dcFinderCommands
    {   dcFinderCmdInsert   = 1,
    dcFinderCmdAttachAsXref = 2,
    dcFinderCmdCopy = 3,
    dcFinderCmdOpen = 4,
    dcFinderCmdLoad = 5,
    dcFinderCmdFirst    = 1,
    dcFinderCmdCustFirst    = 6,
    dcFinderCmdCustLast = 32,
    dcFinderCmdLast = 32
    }   dcFinderCommands;

typedef /* [v1_enum][uuid] */ 
enum dcContentMode
    {   dcDesktop   = 0,
    dcOpenDrawings  = 1,
    dcCustomContent = 2
    }   dcContentMode;

typedef /* [v1_enum][uuid] */ 
enum dcPane
    {   dcPreview   = 0,
    dcDescription   = 1,
    dcNavigator = 2
    }   dcPane;

typedef /* [v1_enum][uuid] */ 
enum dcMenuInfoFlag
    {   dcHelpText  = 0,
    dcValidate  = 1,
    dcVerb  = 2
    }   dcMenuInfoFlag;



extern RPC_IF_HANDLE __MIDL_itf_AsdkDesignCenterSamp_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AsdkDesignCenterSamp_0000_v0_0_s_ifspec;

#ifndef __IAcDcContentBrowser_INTERFACE_DEFINED__
#define __IAcDcContentBrowser_INTERFACE_DEFINED__

/* interface IAcDcContentBrowser */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcDcContentBrowser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9F8AB2D8-D57F-11D1-A92C-0060B0A1F6BB")
    IAcDcContentBrowser : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddPaletteItem( 
            /* [string][in] */ BSTR bstrText,
            /* [in] */ VARIANT varImageIndex,
            /* [in] */ VARIANT varItemData,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarAddedItemIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddNavigatorNode( 
            /* [in] */ VARIANT varhRelativeNode,
            /* [in] */ dcNavNodeRelation sRelationship,
            /* [string][in] */ BSTR bstrText,
            /* [in] */ VARIANT varIconIndex,
            /* [in] */ VARIANT varSelectedIconIndex,
            /* [in] */ VARIANT varbMayhaveChildren,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarAddedNodeID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDCFrameWindow( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvarhFrameWindow) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetItemDescription( 
            /* [string][in] */ BSTR bstrDescription) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPaletteImageList( 
            /* [in] */ VARIANT varhImageList,
            /* [in] */ VARIANT varbLarge) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetNavigatorImageList( 
            /* [in] */ VARIANT varhImageList,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarImageListOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPaletteMultiSelect( 
            /* [in] */ VARIANT varbMultiSelect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertPaletteColumn( 
            /* [in] */ VARIANT varIndex,
            /* [in] */ BSTR bstrText,
            /* [in] */ dcPalColAlignment eFormat) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteAllPaletteItems( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSelectedNavNodeText( 
            /* [string][out] */ BSTR __RPC_FAR *bstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCurrentViewMode( 
            /* [retval][out] */ dcContentMode __RPC_FAR *psMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPaletteSubItem( 
            /* [in] */ VARIANT varItemIndex,
            /* [in] */ VARIANT varColumnIndex,
            /* [in] */ BSTR bstrSubItemText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SortPaletteItems( 
            /* [in] */ VARIANT varpfnFunction,
            /* [in] */ VARIANT varSortData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RestorePaletteSelection( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDCStatusBar( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvarhStatusBar) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPaneInfo( 
            /* [in] */ dcPane ePane,
            /* [out] */ VARIANT __RPC_FAR *pvarWidth,
            /* [out] */ VARIANT __RPC_FAR *pvarHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPaletteViewType( 
            /* [in] */ dcPalViewType eViewType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NavigateTo( 
            /* [in] */ dcContentMode eViewMode,
            /* [in] */ BSTR bstrPath) = 0;
        
    };
    
#else   /* C style interface */

    typedef struct IAcDcContentBrowserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAcDcContentBrowser __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAcDcContentBrowser __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddPaletteItem )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [string][in] */ BSTR bstrText,
            /* [in] */ VARIANT varImageIndex,
            /* [in] */ VARIANT varItemData,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarAddedItemIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddNavigatorNode )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ VARIANT varhRelativeNode,
            /* [in] */ dcNavNodeRelation sRelationship,
            /* [string][in] */ BSTR bstrText,
            /* [in] */ VARIANT varIconIndex,
            /* [in] */ VARIANT varSelectedIconIndex,
            /* [in] */ VARIANT varbMayhaveChildren,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarAddedNodeID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDCFrameWindow )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarhFrameWindow);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetItemDescription )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [string][in] */ BSTR bstrDescription);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPaletteImageList )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ VARIANT varhImageList,
            /* [in] */ VARIANT varbLarge);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNavigatorImageList )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ VARIANT varhImageList,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarImageListOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPaletteMultiSelect )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ VARIANT varbMultiSelect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InsertPaletteColumn )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ VARIANT varIndex,
            /* [in] */ BSTR bstrText,
            /* [in] */ dcPalColAlignment eFormat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteAllPaletteItems )( 
            IAcDcContentBrowser __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSelectedNavNodeText )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [string][out] */ BSTR __RPC_FAR *bstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentViewMode )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [retval][out] */ dcContentMode __RPC_FAR *psMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPaletteSubItem )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ VARIANT varItemIndex,
            /* [in] */ VARIANT varColumnIndex,
            /* [in] */ BSTR bstrSubItemText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SortPaletteItems )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ VARIANT varpfnFunction,
            /* [in] */ VARIANT varSortData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestorePaletteSelection )( 
            IAcDcContentBrowser __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDCStatusBar )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarhStatusBar);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPaneInfo )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ dcPane ePane,
            /* [out] */ VARIANT __RPC_FAR *pvarWidth,
            /* [out] */ VARIANT __RPC_FAR *pvarHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPaletteViewType )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ dcPalViewType eViewType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NavigateTo )( 
            IAcDcContentBrowser __RPC_FAR * This,
            /* [in] */ dcContentMode eViewMode,
            /* [in] */ BSTR bstrPath);
        
        END_INTERFACE
    } IAcDcContentBrowserVtbl;

    interface IAcDcContentBrowser
    {
        CONST_VTBL struct IAcDcContentBrowserVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcDcContentBrowser_QueryInterface(This,riid,ppvObject) \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcDcContentBrowser_AddRef(This)    \
    (This)->lpVtbl -> AddRef(This)

#define IAcDcContentBrowser_Release(This)   \
    (This)->lpVtbl -> Release(This)


#define IAcDcContentBrowser_AddPaletteItem(This,bstrText,varImageIndex,varItemData,pvarAddedItemIndex)  \
    (This)->lpVtbl -> AddPaletteItem(This,bstrText,varImageIndex,varItemData,pvarAddedItemIndex)

#define IAcDcContentBrowser_AddNavigatorNode(This,varhRelativeNode,sRelationship,bstrText,varIconIndex,varSelectedIconIndex,varbMayhaveChildren,pvarAddedNodeID)    \
    (This)->lpVtbl -> AddNavigatorNode(This,varhRelativeNode,sRelationship,bstrText,varIconIndex,varSelectedIconIndex,varbMayhaveChildren,pvarAddedNodeID)

#define IAcDcContentBrowser_GetDCFrameWindow(This,pvarhFrameWindow) \
    (This)->lpVtbl -> GetDCFrameWindow(This,pvarhFrameWindow)

#define IAcDcContentBrowser_SetItemDescription(This,bstrDescription)    \
    (This)->lpVtbl -> SetItemDescription(This,bstrDescription)

#define IAcDcContentBrowser_SetPaletteImageList(This,varhImageList,varbLarge)   \
    (This)->lpVtbl -> SetPaletteImageList(This,varhImageList,varbLarge)

#define IAcDcContentBrowser_SetNavigatorImageList(This,varhImageList,pvarImageListOffset)   \
    (This)->lpVtbl -> SetNavigatorImageList(This,varhImageList,pvarImageListOffset)

#define IAcDcContentBrowser_SetPaletteMultiSelect(This,varbMultiSelect) \
    (This)->lpVtbl -> SetPaletteMultiSelect(This,varbMultiSelect)

#define IAcDcContentBrowser_InsertPaletteColumn(This,varIndex,bstrText,eFormat) \
    (This)->lpVtbl -> InsertPaletteColumn(This,varIndex,bstrText,eFormat)

#define IAcDcContentBrowser_DeleteAllPaletteItems(This) \
    (This)->lpVtbl -> DeleteAllPaletteItems(This)

#define IAcDcContentBrowser_GetSelectedNavNodeText(This,bstrText)   \
    (This)->lpVtbl -> GetSelectedNavNodeText(This,bstrText)

#define IAcDcContentBrowser_GetCurrentViewMode(This,psMode) \
    (This)->lpVtbl -> GetCurrentViewMode(This,psMode)

#define IAcDcContentBrowser_SetPaletteSubItem(This,varItemIndex,varColumnIndex,bstrSubItemText) \
    (This)->lpVtbl -> SetPaletteSubItem(This,varItemIndex,varColumnIndex,bstrSubItemText)

#define IAcDcContentBrowser_SortPaletteItems(This,varpfnFunction,varSortData)   \
    (This)->lpVtbl -> SortPaletteItems(This,varpfnFunction,varSortData)

#define IAcDcContentBrowser_RestorePaletteSelection(This)   \
    (This)->lpVtbl -> RestorePaletteSelection(This)

#define IAcDcContentBrowser_GetDCStatusBar(This,pvarhStatusBar) \
    (This)->lpVtbl -> GetDCStatusBar(This,pvarhStatusBar)

#define IAcDcContentBrowser_GetPaneInfo(This,ePane,pvarWidth,pvarHeight)    \
    (This)->lpVtbl -> GetPaneInfo(This,ePane,pvarWidth,pvarHeight)

#define IAcDcContentBrowser_SetPaletteViewType(This,eViewType)  \
    (This)->lpVtbl -> SetPaletteViewType(This,eViewType)

#define IAcDcContentBrowser_NavigateTo(This,eViewMode,bstrPath) \
    (This)->lpVtbl -> NavigateTo(This,eViewMode,bstrPath)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_AddPaletteItem_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [string][in] */ BSTR bstrText,
    /* [in] */ VARIANT varImageIndex,
    /* [in] */ VARIANT varItemData,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarAddedItemIndex);


void __RPC_STUB IAcDcContentBrowser_AddPaletteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_AddNavigatorNode_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [in] */ VARIANT varhRelativeNode,
    /* [in] */ dcNavNodeRelation sRelationship,
    /* [string][in] */ BSTR bstrText,
    /* [in] */ VARIANT varIconIndex,
    /* [in] */ VARIANT varSelectedIconIndex,
    /* [in] */ VARIANT varbMayhaveChildren,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarAddedNodeID);


void __RPC_STUB IAcDcContentBrowser_AddNavigatorNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_GetDCFrameWindow_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarhFrameWindow);


void __RPC_STUB IAcDcContentBrowser_GetDCFrameWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_SetItemDescription_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [string][in] */ BSTR bstrDescription);


void __RPC_STUB IAcDcContentBrowser_SetItemDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_SetPaletteImageList_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [in] */ VARIANT varhImageList,
    /* [in] */ VARIANT varbLarge);


void __RPC_STUB IAcDcContentBrowser_SetPaletteImageList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_SetNavigatorImageList_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [in] */ VARIANT varhImageList,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarImageListOffset);


void __RPC_STUB IAcDcContentBrowser_SetNavigatorImageList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_SetPaletteMultiSelect_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [in] */ VARIANT varbMultiSelect);


void __RPC_STUB IAcDcContentBrowser_SetPaletteMultiSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_InsertPaletteColumn_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [in] */ VARIANT varIndex,
    /* [in] */ BSTR bstrText,
    /* [in] */ dcPalColAlignment eFormat);


void __RPC_STUB IAcDcContentBrowser_InsertPaletteColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_DeleteAllPaletteItems_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This);


void __RPC_STUB IAcDcContentBrowser_DeleteAllPaletteItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_GetSelectedNavNodeText_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [string][out] */ BSTR __RPC_FAR *bstrText);


void __RPC_STUB IAcDcContentBrowser_GetSelectedNavNodeText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_GetCurrentViewMode_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [retval][out] */ dcContentMode __RPC_FAR *psMode);


void __RPC_STUB IAcDcContentBrowser_GetCurrentViewMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_SetPaletteSubItem_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [in] */ VARIANT varItemIndex,
    /* [in] */ VARIANT varColumnIndex,
    /* [in] */ BSTR bstrSubItemText);


void __RPC_STUB IAcDcContentBrowser_SetPaletteSubItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_SortPaletteItems_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [in] */ VARIANT varpfnFunction,
    /* [in] */ VARIANT varSortData);


void __RPC_STUB IAcDcContentBrowser_SortPaletteItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_RestorePaletteSelection_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This);


void __RPC_STUB IAcDcContentBrowser_RestorePaletteSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_GetDCStatusBar_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarhStatusBar);


void __RPC_STUB IAcDcContentBrowser_GetDCStatusBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_GetPaneInfo_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [in] */ dcPane ePane,
    /* [out] */ VARIANT __RPC_FAR *pvarWidth,
    /* [out] */ VARIANT __RPC_FAR *pvarHeight);


void __RPC_STUB IAcDcContentBrowser_GetPaneInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_SetPaletteViewType_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [in] */ dcPalViewType eViewType);


void __RPC_STUB IAcDcContentBrowser_SetPaletteViewType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentBrowser_NavigateTo_Proxy( 
    IAcDcContentBrowser __RPC_FAR * This,
    /* [in] */ dcContentMode eViewMode,
    /* [in] */ BSTR bstrPath);


void __RPC_STUB IAcDcContentBrowser_NavigateTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif  /* __IAcDcContentBrowser_INTERFACE_DEFINED__ */


#ifndef __IAcDcContentView_INTERFACE_DEFINED__
#define __IAcDcContentView_INTERFACE_DEFINED__

/* interface IAcDcContentView */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcDcContentView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("625cecb0-a722-11d1-9715-92a923000000")
    IAcDcContentView : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ VARIANT varBrowser,
            /* [in] */ VARIANT varReserved) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetImageLists( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NavigatorNodeExpanding( 
            /* [in] */ VARIANT varhNode,
            /* [string][in] */ BSTR bstrNodeText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NavigatorNodeCollapsing( 
            /* [in] */ VARIANT varhNode,
            /* [string][in] */ BSTR bstrNodeText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NavigatorNodeClick( 
            /* [in] */ VARIANT varhNode,
            /* [string][in] */ BSTR bstrNodeText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NavigatorMouseUp( 
            /* [in] */ VARIANT varhNode,
            /* [string][in] */ BSTR bstrNodeText,
            /* [in] */ VARIANT varX,
            /* [in] */ VARIANT varY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PaletteItemClick( 
            /* [string][in] */ BSTR bstrItemText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PaletteItemDblClick( 
            /* [string][in] */ BSTR bstrItemText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PaletteColumnClick( 
            /* [in] */ VARIANT varIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PaletteMouseUp( 
            /* [in] */ VARIANT varButton,
            /* [in] */ VARIANT varItemTexts,
            /* [in] */ VARIANT varX,
            /* [in] */ VARIANT varY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PaletteMouseDown( 
            /* [in] */ VARIANT varButton,
            /* [string][in] */ BSTR bstrItemText,
            /* [in] */ VARIANT varX,
            /* [in] */ VARIANT varY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RenderPreviewWindow( 
            /* [string][in] */ BSTR bstrItemText,
            /* [in] */ VARIANT varhPreviewWindow) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PreviewMouseUp( 
            /* [in] */ VARIANT varButton,
            /* [in] */ VARIANT varX,
            /* [in] */ VARIANT varY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PaletteBeginDrag( 
            /* [in] */ VARIANT varbstrItemTexts,
            /* [in] */ VARIANT varX,
            /* [in] */ VARIANT varY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseBrowser( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryContextMenu( 
            /* [in] */ VARIANT varhMenu,
            /* [in] */ VARIANT varIndex,
            /* [in] */ VARIANT varCmdFirst,
            /* [in] */ VARIANT varCmdLast,
            /* [in] */ VARIANT varItemTexts) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeCommand( 
            /* [in] */ VARIANT varMenuItemID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsExpandable( 
            /* [string][in] */ BSTR bstrItemText,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarIsExpandable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLargeImage( 
            /* [in] */ BSTR bstrFileName,
            /* [out][in] */ VARIANT __RPC_FAR *pvarhLargeImage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSmallImageListForContent( 
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarhImageList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLargeImageListForContent( 
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarhImageList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCommandString( 
            /* [in] */ VARIANT varMenuID,
            /* [in] */ dcMenuInfoFlag __MIDL_0015,
            /* [out] */ VARIANT __RPC_FAR *pvarReserved,
            /* [out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
    };
    
#else   /* C style interface */

    typedef struct IAcDcContentViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAcDcContentView __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAcDcContentView __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varBrowser,
            /* [in] */ VARIANT varReserved);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetImageLists )( 
            IAcDcContentView __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IAcDcContentView __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NavigatorNodeExpanding )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varhNode,
            /* [string][in] */ BSTR bstrNodeText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NavigatorNodeCollapsing )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varhNode,
            /* [string][in] */ BSTR bstrNodeText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NavigatorNodeClick )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varhNode,
            /* [string][in] */ BSTR bstrNodeText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NavigatorMouseUp )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varhNode,
            /* [string][in] */ BSTR bstrNodeText,
            /* [in] */ VARIANT varX,
            /* [in] */ VARIANT varY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PaletteItemClick )( 
            IAcDcContentView __RPC_FAR * This,
            /* [string][in] */ BSTR bstrItemText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PaletteItemDblClick )( 
            IAcDcContentView __RPC_FAR * This,
            /* [string][in] */ BSTR bstrItemText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PaletteColumnClick )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PaletteMouseUp )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varButton,
            /* [in] */ VARIANT varItemTexts,
            /* [in] */ VARIANT varX,
            /* [in] */ VARIANT varY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PaletteMouseDown )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varButton,
            /* [string][in] */ BSTR bstrItemText,
            /* [in] */ VARIANT varX,
            /* [in] */ VARIANT varY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderPreviewWindow )( 
            IAcDcContentView __RPC_FAR * This,
            /* [string][in] */ BSTR bstrItemText,
            /* [in] */ VARIANT varhPreviewWindow);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PreviewMouseUp )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varButton,
            /* [in] */ VARIANT varX,
            /* [in] */ VARIANT varY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PaletteBeginDrag )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varbstrItemTexts,
            /* [in] */ VARIANT varX,
            /* [in] */ VARIANT varY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseBrowser )( 
            IAcDcContentView __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryContextMenu )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varhMenu,
            /* [in] */ VARIANT varIndex,
            /* [in] */ VARIANT varCmdFirst,
            /* [in] */ VARIANT varCmdLast,
            /* [in] */ VARIANT varItemTexts);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeCommand )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varMenuItemID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsExpandable )( 
            IAcDcContentView __RPC_FAR * This,
            /* [string][in] */ BSTR bstrItemText,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarIsExpandable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLargeImage )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ BSTR bstrFileName,
            /* [out][in] */ VARIANT __RPC_FAR *pvarhLargeImage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSmallImageListForContent )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarhImageList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLargeImageListForContent )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarhImageList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCommandString )( 
            IAcDcContentView __RPC_FAR * This,
            /* [in] */ VARIANT varMenuID,
            /* [in] */ dcMenuInfoFlag __MIDL_0015,
            /* [out] */ VARIANT __RPC_FAR *pvarReserved,
            /* [out] */ BSTR __RPC_FAR *pbstrName);
        
        END_INTERFACE
    } IAcDcContentViewVtbl;

    interface IAcDcContentView
    {
        CONST_VTBL struct IAcDcContentViewVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcDcContentView_QueryInterface(This,riid,ppvObject)    \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcDcContentView_AddRef(This)   \
    (This)->lpVtbl -> AddRef(This)

#define IAcDcContentView_Release(This)  \
    (This)->lpVtbl -> Release(This)


#define IAcDcContentView_Initialize(This,varBrowser,varReserved)    \
    (This)->lpVtbl -> Initialize(This,varBrowser,varReserved)

#define IAcDcContentView_SetImageLists(This)    \
    (This)->lpVtbl -> SetImageLists(This)

#define IAcDcContentView_Refresh(This)  \
    (This)->lpVtbl -> Refresh(This)

#define IAcDcContentView_NavigatorNodeExpanding(This,varhNode,bstrNodeText) \
    (This)->lpVtbl -> NavigatorNodeExpanding(This,varhNode,bstrNodeText)

#define IAcDcContentView_NavigatorNodeCollapsing(This,varhNode,bstrNodeText)    \
    (This)->lpVtbl -> NavigatorNodeCollapsing(This,varhNode,bstrNodeText)

#define IAcDcContentView_NavigatorNodeClick(This,varhNode,bstrNodeText) \
    (This)->lpVtbl -> NavigatorNodeClick(This,varhNode,bstrNodeText)

#define IAcDcContentView_NavigatorMouseUp(This,varhNode,bstrNodeText,varX,varY) \
    (This)->lpVtbl -> NavigatorMouseUp(This,varhNode,bstrNodeText,varX,varY)

#define IAcDcContentView_PaletteItemClick(This,bstrItemText)    \
    (This)->lpVtbl -> PaletteItemClick(This,bstrItemText)

#define IAcDcContentView_PaletteItemDblClick(This,bstrItemText) \
    (This)->lpVtbl -> PaletteItemDblClick(This,bstrItemText)

#define IAcDcContentView_PaletteColumnClick(This,varIndex)  \
    (This)->lpVtbl -> PaletteColumnClick(This,varIndex)

#define IAcDcContentView_PaletteMouseUp(This,varButton,varItemTexts,varX,varY)  \
    (This)->lpVtbl -> PaletteMouseUp(This,varButton,varItemTexts,varX,varY)

#define IAcDcContentView_PaletteMouseDown(This,varButton,bstrItemText,varX,varY)    \
    (This)->lpVtbl -> PaletteMouseDown(This,varButton,bstrItemText,varX,varY)

#define IAcDcContentView_RenderPreviewWindow(This,bstrItemText,varhPreviewWindow)   \
    (This)->lpVtbl -> RenderPreviewWindow(This,bstrItemText,varhPreviewWindow)

#define IAcDcContentView_PreviewMouseUp(This,varButton,varX,varY)   \
    (This)->lpVtbl -> PreviewMouseUp(This,varButton,varX,varY)

#define IAcDcContentView_PaletteBeginDrag(This,varbstrItemTexts,varX,varY)  \
    (This)->lpVtbl -> PaletteBeginDrag(This,varbstrItemTexts,varX,varY)

#define IAcDcContentView_ReleaseBrowser(This)   \
    (This)->lpVtbl -> ReleaseBrowser(This)

#define IAcDcContentView_QueryContextMenu(This,varhMenu,varIndex,varCmdFirst,varCmdLast,varItemTexts)   \
    (This)->lpVtbl -> QueryContextMenu(This,varhMenu,varIndex,varCmdFirst,varCmdLast,varItemTexts)

#define IAcDcContentView_InvokeCommand(This,varMenuItemID)  \
    (This)->lpVtbl -> InvokeCommand(This,varMenuItemID)

#define IAcDcContentView_IsExpandable(This,bstrItemText,pvarIsExpandable)   \
    (This)->lpVtbl -> IsExpandable(This,bstrItemText,pvarIsExpandable)

#define IAcDcContentView_GetLargeImage(This,bstrFileName,pvarhLargeImage)   \
    (This)->lpVtbl -> GetLargeImage(This,bstrFileName,pvarhLargeImage)

#define IAcDcContentView_GetSmallImageListForContent(This,bstrFileName,pvarhImageList)  \
    (This)->lpVtbl -> GetSmallImageListForContent(This,bstrFileName,pvarhImageList)

#define IAcDcContentView_GetLargeImageListForContent(This,bstrFileName,pvarhImageList)  \
    (This)->lpVtbl -> GetLargeImageListForContent(This,bstrFileName,pvarhImageList)

#define IAcDcContentView_GetCommandString(This,varMenuID,__MIDL_0015,pvarReserved,pbstrName)    \
    (This)->lpVtbl -> GetCommandString(This,varMenuID,__MIDL_0015,pvarReserved,pbstrName)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_Initialize_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varBrowser,
    /* [in] */ VARIANT varReserved);


void __RPC_STUB IAcDcContentView_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_SetImageLists_Proxy( 
    IAcDcContentView __RPC_FAR * This);


void __RPC_STUB IAcDcContentView_SetImageLists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_Refresh_Proxy( 
    IAcDcContentView __RPC_FAR * This);


void __RPC_STUB IAcDcContentView_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_NavigatorNodeExpanding_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varhNode,
    /* [string][in] */ BSTR bstrNodeText);


void __RPC_STUB IAcDcContentView_NavigatorNodeExpanding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_NavigatorNodeCollapsing_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varhNode,
    /* [string][in] */ BSTR bstrNodeText);


void __RPC_STUB IAcDcContentView_NavigatorNodeCollapsing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_NavigatorNodeClick_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varhNode,
    /* [string][in] */ BSTR bstrNodeText);


void __RPC_STUB IAcDcContentView_NavigatorNodeClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_NavigatorMouseUp_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varhNode,
    /* [string][in] */ BSTR bstrNodeText,
    /* [in] */ VARIANT varX,
    /* [in] */ VARIANT varY);


void __RPC_STUB IAcDcContentView_NavigatorMouseUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_PaletteItemClick_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [string][in] */ BSTR bstrItemText);


void __RPC_STUB IAcDcContentView_PaletteItemClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_PaletteItemDblClick_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [string][in] */ BSTR bstrItemText);


void __RPC_STUB IAcDcContentView_PaletteItemDblClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_PaletteColumnClick_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varIndex);


void __RPC_STUB IAcDcContentView_PaletteColumnClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_PaletteMouseUp_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varButton,
    /* [in] */ VARIANT varItemTexts,
    /* [in] */ VARIANT varX,
    /* [in] */ VARIANT varY);


void __RPC_STUB IAcDcContentView_PaletteMouseUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_PaletteMouseDown_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varButton,
    /* [string][in] */ BSTR bstrItemText,
    /* [in] */ VARIANT varX,
    /* [in] */ VARIANT varY);


void __RPC_STUB IAcDcContentView_PaletteMouseDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_RenderPreviewWindow_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [string][in] */ BSTR bstrItemText,
    /* [in] */ VARIANT varhPreviewWindow);


void __RPC_STUB IAcDcContentView_RenderPreviewWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_PreviewMouseUp_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varButton,
    /* [in] */ VARIANT varX,
    /* [in] */ VARIANT varY);


void __RPC_STUB IAcDcContentView_PreviewMouseUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_PaletteBeginDrag_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varbstrItemTexts,
    /* [in] */ VARIANT varX,
    /* [in] */ VARIANT varY);


void __RPC_STUB IAcDcContentView_PaletteBeginDrag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_ReleaseBrowser_Proxy( 
    IAcDcContentView __RPC_FAR * This);


void __RPC_STUB IAcDcContentView_ReleaseBrowser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_QueryContextMenu_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varhMenu,
    /* [in] */ VARIANT varIndex,
    /* [in] */ VARIANT varCmdFirst,
    /* [in] */ VARIANT varCmdLast,
    /* [in] */ VARIANT varItemTexts);


void __RPC_STUB IAcDcContentView_QueryContextMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_InvokeCommand_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varMenuItemID);


void __RPC_STUB IAcDcContentView_InvokeCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_IsExpandable_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [string][in] */ BSTR bstrItemText,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarIsExpandable);


void __RPC_STUB IAcDcContentView_IsExpandable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_GetLargeImage_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ BSTR bstrFileName,
    /* [out][in] */ VARIANT __RPC_FAR *pvarhLargeImage);


void __RPC_STUB IAcDcContentView_GetLargeImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_GetSmallImageListForContent_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ BSTR bstrFileName,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarhImageList);


void __RPC_STUB IAcDcContentView_GetSmallImageListForContent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_GetLargeImageListForContent_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ BSTR bstrFileName,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarhImageList);


void __RPC_STUB IAcDcContentView_GetLargeImageListForContent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAcDcContentView_GetCommandString_Proxy( 
    IAcDcContentView __RPC_FAR * This,
    /* [in] */ VARIANT varMenuID,
    /* [in] */ dcMenuInfoFlag __MIDL_0015,
    /* [out] */ VARIANT __RPC_FAR *pvarReserved,
    /* [out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IAcDcContentView_GetCommandString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif  /* __IAcDcContentView_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_AsdkDesignCenterSamp_0212 */
/* [local] */ 

typedef /* [public][public] */ struct  __MIDL___MIDL_itf_AsdkDesignCenterSamp_0212_0001
    {
    LPCOLESTR lpObjectName;
    LPCOLESTR lpObjectType;
    LPCOLESTR lpCustomValue;
    LPCOLESTR lpLocation;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    short nBitmapIndex;
    short nObjectType;
    short nObjectTypeEx;
    }   FINDOBJECTINFO;



extern RPC_IF_HANDLE __MIDL_itf_AsdkDesignCenterSamp_0212_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AsdkDesignCenterSamp_0212_v0_0_s_ifspec;

#ifndef __IAcDcContentFinderSite_INTERFACE_DEFINED__
#define __IAcDcContentFinderSite_INTERFACE_DEFINED__

/* interface IAcDcContentFinderSite */
/* [ref][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcDcContentFinderSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F6F24140-EC52-11d1-B9C7-0060B0B5E151")
    IAcDcContentFinderSite : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetObjectInfo( 
            /* [in] */ FINDOBJECTINFO __RPC_FAR *lpObjectInfo,
            /* [retval][out] */ boolean __RPC_FAR *pbContinue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMessage( 
            /* [string][in] */ LPCOLESTR lpMessage,
            /* [retval][out] */ boolean __RPC_FAR *pbContinue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPropertyValue( 
            /* [string][in] */ LPCOLESTR lpPropertyValue,
            /* [retval][out] */ boolean __RPC_FAR *pbContinue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTypeBitmap( 
            /* [string][in] */ LPCOLESTR lpTypeName,
            /* [in] */ IPictureDisp __RPC_FAR *lpPictureDisp,
            /* [out] */ short __RPC_FAR *pnBitmapIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QueryContinueFind( 
            /* [retval][out] */ boolean __RPC_FAR *pbContinue) = 0;
        
    };
    
#else   /* C style interface */

    typedef struct IAcDcContentFinderSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAcDcContentFinderSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAcDcContentFinderSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAcDcContentFinderSite __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObjectInfo )( 
            IAcDcContentFinderSite __RPC_FAR * This,
            /* [in] */ FINDOBJECTINFO __RPC_FAR *lpObjectInfo,
            /* [retval][out] */ boolean __RPC_FAR *pbContinue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMessage )( 
            IAcDcContentFinderSite __RPC_FAR * This,
            /* [string][in] */ LPCOLESTR lpMessage,
            /* [retval][out] */ boolean __RPC_FAR *pbContinue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPropertyValue )( 
            IAcDcContentFinderSite __RPC_FAR * This,
            /* [string][in] */ LPCOLESTR lpPropertyValue,
            /* [retval][out] */ boolean __RPC_FAR *pbContinue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTypeBitmap )( 
            IAcDcContentFinderSite __RPC_FAR * This,
            /* [string][in] */ LPCOLESTR lpTypeName,
            /* [in] */ IPictureDisp __RPC_FAR *lpPictureDisp,
            /* [out] */ short __RPC_FAR *pnBitmapIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryContinueFind )( 
            IAcDcContentFinderSite __RPC_FAR * This,
            /* [retval][out] */ boolean __RPC_FAR *pbContinue);
        
        END_INTERFACE
    } IAcDcContentFinderSiteVtbl;

    interface IAcDcContentFinderSite
    {
        CONST_VTBL struct IAcDcContentFinderSiteVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcDcContentFinderSite_QueryInterface(This,riid,ppvObject)  \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcDcContentFinderSite_AddRef(This) \
    (This)->lpVtbl -> AddRef(This)

#define IAcDcContentFinderSite_Release(This)    \
    (This)->lpVtbl -> Release(This)


#define IAcDcContentFinderSite_SetObjectInfo(This,lpObjectInfo,pbContinue)  \
    (This)->lpVtbl -> SetObjectInfo(This,lpObjectInfo,pbContinue)

#define IAcDcContentFinderSite_SetMessage(This,lpMessage,pbContinue)    \
    (This)->lpVtbl -> SetMessage(This,lpMessage,pbContinue)

#define IAcDcContentFinderSite_SetPropertyValue(This,lpPropertyValue,pbContinue)    \
    (This)->lpVtbl -> SetPropertyValue(This,lpPropertyValue,pbContinue)

#define IAcDcContentFinderSite_SetTypeBitmap(This,lpTypeName,lpPictureDisp,pnBitmapIndex)   \
    (This)->lpVtbl -> SetTypeBitmap(This,lpTypeName,lpPictureDisp,pnBitmapIndex)

#define IAcDcContentFinderSite_QueryContinueFind(This,pbContinue)   \
    (This)->lpVtbl -> QueryContinueFind(This,pbContinue)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinderSite_SetObjectInfo_Proxy( 
    IAcDcContentFinderSite __RPC_FAR * This,
    /* [in] */ FINDOBJECTINFO __RPC_FAR *lpObjectInfo,
    /* [retval][out] */ boolean __RPC_FAR *pbContinue);


void __RPC_STUB IAcDcContentFinderSite_SetObjectInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinderSite_SetMessage_Proxy( 
    IAcDcContentFinderSite __RPC_FAR * This,
    /* [string][in] */ LPCOLESTR lpMessage,
    /* [retval][out] */ boolean __RPC_FAR *pbContinue);


void __RPC_STUB IAcDcContentFinderSite_SetMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinderSite_SetPropertyValue_Proxy( 
    IAcDcContentFinderSite __RPC_FAR * This,
    /* [string][in] */ LPCOLESTR lpPropertyValue,
    /* [retval][out] */ boolean __RPC_FAR *pbContinue);


void __RPC_STUB IAcDcContentFinderSite_SetPropertyValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinderSite_SetTypeBitmap_Proxy( 
    IAcDcContentFinderSite __RPC_FAR * This,
    /* [string][in] */ LPCOLESTR lpTypeName,
    /* [in] */ IPictureDisp __RPC_FAR *lpPictureDisp,
    /* [out] */ short __RPC_FAR *pnBitmapIndex);


void __RPC_STUB IAcDcContentFinderSite_SetTypeBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinderSite_QueryContinueFind_Proxy( 
    IAcDcContentFinderSite __RPC_FAR * This,
    /* [retval][out] */ boolean __RPC_FAR *pbContinue);


void __RPC_STUB IAcDcContentFinderSite_QueryContinueFind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif  /* __IAcDcContentFinderSite_INTERFACE_DEFINED__ */


#ifndef __IAcDcContentFinder_INTERFACE_DEFINED__
#define __IAcDcContentFinder_INTERFACE_DEFINED__

/* interface IAcDcContentFinder */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAcDcContentFinder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7EE59AE-E9F7-11D1-B9C2-0060B0B5E151")
    IAcDcContentFinder : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IAcDcContentFinderSite __RPC_FAR *pClient) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumerateObjects( 
            /* [in] */ IAcDcContentFinderSite __RPC_FAR *pClient,
            /* [string][in] */ LPCOLESTR lpTypeName,
            /* [string][in] */ LPCOLESTR lpDirName,
            /* [string][in] */ LPCOLESTR lpFilter,
            /* [in] */ boolean bRecurse,
            /* [string][in] */ LPCOLESTR lpPropertyRequested,
            /* [in] */ boolean bAdvPropertySearch) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumeratePropertyValues( 
            /* [string][in] */ LPCOLESTR lpPropertyName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsMultiselectionEnabled( 
            /* [string][in] */ LPCOLESTR lpTypeName,
            /* [retval][out] */ boolean __RPC_FAR *pbEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InvokeCommand( 
            /* [in] */ int nCmdId,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pNames,
            /* [in] */ int nObjectType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Interrupt( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitPopupMenu( 
            /* [in] */ int hMenu) = 0;
        
    };
    
#else   /* C style interface */

    typedef struct IAcDcContentFinderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAcDcContentFinder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAcDcContentFinder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAcDcContentFinder __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IAcDcContentFinder __RPC_FAR * This,
            /* [in] */ IAcDcContentFinderSite __RPC_FAR *pClient);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateObjects )( 
            IAcDcContentFinder __RPC_FAR * This,
            /* [in] */ IAcDcContentFinderSite __RPC_FAR *pClient,
            /* [string][in] */ LPCOLESTR lpTypeName,
            /* [string][in] */ LPCOLESTR lpDirName,
            /* [string][in] */ LPCOLESTR lpFilter,
            /* [in] */ boolean bRecurse,
            /* [string][in] */ LPCOLESTR lpPropertyRequested,
            /* [in] */ boolean bAdvPropertySearch);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumeratePropertyValues )( 
            IAcDcContentFinder __RPC_FAR * This,
            /* [string][in] */ LPCOLESTR lpPropertyName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsMultiselectionEnabled )( 
            IAcDcContentFinder __RPC_FAR * This,
            /* [string][in] */ LPCOLESTR lpTypeName,
            /* [retval][out] */ boolean __RPC_FAR *pbEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeCommand )( 
            IAcDcContentFinder __RPC_FAR * This,
            /* [in] */ int nCmdId,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pNames,
            /* [in] */ int nObjectType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Interrupt )( 
            IAcDcContentFinder __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitPopupMenu )( 
            IAcDcContentFinder __RPC_FAR * This,
            /* [in] */ int hMenu);
        
        END_INTERFACE
    } IAcDcContentFinderVtbl;

    interface IAcDcContentFinder
    {
        CONST_VTBL struct IAcDcContentFinderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcDcContentFinder_QueryInterface(This,riid,ppvObject)  \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcDcContentFinder_AddRef(This) \
    (This)->lpVtbl -> AddRef(This)

#define IAcDcContentFinder_Release(This)    \
    (This)->lpVtbl -> Release(This)


#define IAcDcContentFinder_Initialize(This,pClient) \
    (This)->lpVtbl -> Initialize(This,pClient)

#define IAcDcContentFinder_EnumerateObjects(This,pClient,lpTypeName,lpDirName,lpFilter,bRecurse,lpPropertyRequested,bAdvPropertySearch) \
    (This)->lpVtbl -> EnumerateObjects(This,pClient,lpTypeName,lpDirName,lpFilter,bRecurse,lpPropertyRequested,bAdvPropertySearch)

#define IAcDcContentFinder_EnumeratePropertyValues(This,lpPropertyName) \
    (This)->lpVtbl -> EnumeratePropertyValues(This,lpPropertyName)

#define IAcDcContentFinder_IsMultiselectionEnabled(This,lpTypeName,pbEnable)    \
    (This)->lpVtbl -> IsMultiselectionEnabled(This,lpTypeName,pbEnable)

#define IAcDcContentFinder_InvokeCommand(This,nCmdId,pNames,nObjectType)    \
    (This)->lpVtbl -> InvokeCommand(This,nCmdId,pNames,nObjectType)

#define IAcDcContentFinder_Interrupt(This)  \
    (This)->lpVtbl -> Interrupt(This)

#define IAcDcContentFinder_InitPopupMenu(This,hMenu)    \
    (This)->lpVtbl -> InitPopupMenu(This,hMenu)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinder_Initialize_Proxy( 
    IAcDcContentFinder __RPC_FAR * This,
    /* [in] */ IAcDcContentFinderSite __RPC_FAR *pClient);


void __RPC_STUB IAcDcContentFinder_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinder_EnumerateObjects_Proxy( 
    IAcDcContentFinder __RPC_FAR * This,
    /* [in] */ IAcDcContentFinderSite __RPC_FAR *pClient,
    /* [string][in] */ LPCOLESTR lpTypeName,
    /* [string][in] */ LPCOLESTR lpDirName,
    /* [string][in] */ LPCOLESTR lpFilter,
    /* [in] */ boolean bRecurse,
    /* [string][in] */ LPCOLESTR lpPropertyRequested,
    /* [in] */ boolean bAdvPropertySearch);


void __RPC_STUB IAcDcContentFinder_EnumerateObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinder_EnumeratePropertyValues_Proxy( 
    IAcDcContentFinder __RPC_FAR * This,
    /* [string][in] */ LPCOLESTR lpPropertyName);


void __RPC_STUB IAcDcContentFinder_EnumeratePropertyValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinder_IsMultiselectionEnabled_Proxy( 
    IAcDcContentFinder __RPC_FAR * This,
    /* [string][in] */ LPCOLESTR lpTypeName,
    /* [retval][out] */ boolean __RPC_FAR *pbEnable);


void __RPC_STUB IAcDcContentFinder_IsMultiselectionEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinder_InvokeCommand_Proxy( 
    IAcDcContentFinder __RPC_FAR * This,
    /* [in] */ int nCmdId,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pNames,
    /* [in] */ int nObjectType);


void __RPC_STUB IAcDcContentFinder_InvokeCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinder_Interrupt_Proxy( 
    IAcDcContentFinder __RPC_FAR * This);


void __RPC_STUB IAcDcContentFinder_Interrupt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAcDcContentFinder_InitPopupMenu_Proxy( 
    IAcDcContentFinder __RPC_FAR * This,
    /* [in] */ int hMenu);


void __RPC_STUB IAcDcContentFinder_InitPopupMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif  /* __IAcDcContentFinder_INTERFACE_DEFINED__ */


#ifndef __IAsdkDcContent_INTERFACE_DEFINED__
#define __IAsdkDcContent_INTERFACE_DEFINED__

/* interface IAsdkDcContent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAsdkDcContent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C555913C-A4EA-11D2-A7DA-0060B0872457")
    IAsdkDcContent : public IDispatch
    {
    public:
    };
    
#else   /* C style interface */

    typedef struct IAsdkDcContentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAsdkDcContent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAsdkDcContent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAsdkDcContent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAsdkDcContent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAsdkDcContent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAsdkDcContent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAsdkDcContent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IAsdkDcContentVtbl;

    interface IAsdkDcContent
    {
        CONST_VTBL struct IAsdkDcContentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAsdkDcContent_QueryInterface(This,riid,ppvObject)  \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAsdkDcContent_AddRef(This) \
    (This)->lpVtbl -> AddRef(This)

#define IAsdkDcContent_Release(This)    \
    (This)->lpVtbl -> Release(This)


#define IAsdkDcContent_GetTypeInfoCount(This,pctinfo)   \
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAsdkDcContent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)    \
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAsdkDcContent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)  \
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAsdkDcContent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)    \
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif  /* C style interface */




#endif  /* __IAsdkDcContent_INTERFACE_DEFINED__ */



#ifndef __ASDKDESIGNCENTERSAMPLib_LIBRARY_DEFINED__
#define __ASDKDESIGNCENTERSAMPLib_LIBRARY_DEFINED__

/* library ASDKDESIGNCENTERSAMPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ASDKDESIGNCENTERSAMPLib;

EXTERN_C const CLSID CLSID_AsdkDcContent;

#ifdef __cplusplus

class DECLSPEC_UUID("AF67CC1B-83C2-11D2-A7BD-0060B0872457")
AsdkDcContent;
#endif
#endif /* __ASDKDESIGNCENTERSAMPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
