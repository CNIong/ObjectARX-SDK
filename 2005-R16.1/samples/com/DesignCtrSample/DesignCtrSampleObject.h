//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
// DesignCtrSampleObject.h : Declaration of the CDesignCtrSampleObject

#ifndef __DESIGNCTRSAMPLEOBJECT_H_
#define __DESIGNCTRSAMPLEOBJECT_H_

#include "resource.h"       // main symbols

#if defined(_DEBUG) && !defined(DEBUG_THIS_ONLY)
#undef _DEBUG
#define DEBUG_THIS_ONLY
#endif

#include <atlwin.h>
#include <atlctl.h>
#include <afxcmn.h>

#ifdef DEBUG_THIS_ONLY
#undef DEBUG_THIS_ONLY
#define _DEBUG
#endif


#include "WhipMdiChildWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CDesignCtrSampleObject
class ATL_NO_VTABLE CDesignCtrSampleObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDesignCtrSampleObject, &CLSID_DesignCtrSampleObject>,
	public ISupportErrorInfo,
	public IDispatchImpl<IDesignCtrSampleObject, &IID_IDesignCtrSampleObject, &LIBID_DesignCtrSampleLib>,
	// added manually
	public CWindowImplBase,
	public IAcDcContentView

{
public:
	//added manually
	DECLARE_WND_CLASS(NULL)

	CDesignCtrSampleObject() : m_pWhipWnd(NULL)
	{
	}
	// added manually
	~CDesignCtrSampleObject()
	{
		if(m_pWhipWnd && m_pWhipWnd->m_hWnd)
			delete m_pWhipWnd;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DESIGNCTRSAMPLEOBJECT)

BEGIN_COM_MAP(CDesignCtrSampleObject)
	COM_INTERFACE_ENTRY(IDesignCtrSampleObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IAcDcContentView)
END_COM_MAP()

// added manually to make the call non-abstract
BEGIN_MSG_MAP(CDesignCtrSampleObject)
END_MSG_MAP()

	//
	HRESULT OnDraw(ATL_DRAWINFO& di);
    HRESULT FinalRelease();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDesignCtrSampleObject
public:
	// IAcCeContentView
    STDMETHOD(Initialize)(/* [in] */ VARIANT varBrowser,
            /* [in] */ VARIANT varReserved);
    STDMETHOD(SetImageLists)();
    STDMETHOD(NavigatorNodeExpanding)(/*[in]*/ VARIANT varhNode
                                      , /*[in]*/ BSTR bstrFullPath);
    STDMETHOD(NavigatorNodeCollapsing)(/*[in]*/ VARIANT varhNode
                                       , /*[in]*/ BSTR bstrFullPath);
    STDMETHOD(NavigatorNodeClick)(/*[in]*/ VARIANT varhNode
                                  , /*[in, string]*/ BSTR bstrFullPath);
    STDMETHOD(NavigatorMouseUp)(/*[in]*/ VARIANT varhNode
                                , /*[in, string]*/ BSTR bstrFullPath
                                , /*[in]*/ VARIANT varX, /*[in]*/ VARIANT varY);
    STDMETHOD(PaletteItemClick)(/*[in]*/ BSTR bstrItemText);
    STDMETHOD(PaletteItemDblClick)(/*[in]*/ BSTR bstrItemText);
    STDMETHOD(PaletteColumnClick)(/*[in]*/ VARIANT varIndex);        
    STDMETHOD(PaletteMouseUp)(/*[in]*/ VARIANT varButton
                              , /*[in]*/ VARIANT varItemTexts
                              , /*[in]*/ VARIANT varX, /*[in]*/ VARIANT varY);
    STDMETHOD(PaletteMouseDown)(/*[in]*/ VARIANT varButton
                              , /*[in]*/ BSTR bstrFullText 
                              , /*[in]*/ VARIANT varX, /*[in]*/ VARIANT varY);
    STDMETHOD(RenderPreviewWindow)(/*[in]*/ BSTR bstrFullText
                                   , /*[in]*/ VARIANT varhPreviewWindow);
    STDMETHOD(PreviewMouseUp)(/*[in]*/ VARIANT varButton, /*[in]*/ VARIANT varX
                              , /*[in]*/ VARIANT varY);
    STDMETHOD(Refresh)();
    STDMETHOD(PaletteBeginDrag)(/*[in]*/ VARIANT varItemTexts
                                , /*[in]*/ VARIANT varX, /*[in]*/VARIANT varY);
    STDMETHOD(ReleaseBrowser)();
    STDMETHOD(QueryContextMenu)(/*[in]*/ VARIANT varhMenu
                                , /*[in]*/ VARIANT varIndex
                                , /*[in]*/ VARIANT varCmdFirst
                                , /*[in]*/ VARIANT varCmdLast
                                , /*[in]*/ VARIANT varItemTexts);
    STDMETHOD(InvokeCommand)(/*[in]*/ VARIANT varMenuID);


    STDMETHOD(IsExpandable)(/* [string][in] */ BSTR bstrItemText
							, /* [retval][out] */ VARIANT __RPC_FAR *pvarIsExpandable);
    
    STDMETHOD(GetLargeImage)(/* [in] */ BSTR bstrFileName
							, /* [out][in] */ VARIANT __RPC_FAR *pvarhLargeImage);

	STDMETHOD(GetSmallImageListForContent)(/*[in]*/ BSTR bstrFileName
                                           , /*[out]*/ VARIANT *pvarhImageList);
    STDMETHOD(GetLargeImageListForContent)(/*[in]*/ BSTR bstrFileName
                                           , /*[out]*/ VARIANT *pvarhImageList);
    STDMETHOD(GetCommandString)(
        /*[in]*/ VARIANT varMenuID          // menu id
        , /*[in]*/ dcMenuInfoFlag   // which information is required
        , /*[out]*/ VARIANT *pvarReserved   // reserved, handlers must ignore this
        , /*[out]*/ BSTR *pbstrName         // menu information
    );
    STDMETHOD(DeleteItemData)(/*[in]*/ dcItemDataSource dcSrc
                              , /*[in]*/ VARIANT varItemDataArray);

// added manually
private:
    HWND    m_hCEFrameWnd;
    CImageList *m_pSmallImageList;
    CImageList *m_pLargeImageList;

    CString m_strSelectedItemText;
    CComPtr<IAcDcContentBrowser>    m_spContentBrowser;
    HGLOBAL m_hSelectedItemPict;
    int     m_nSelectedItemIndex;
    RECT    m_SelectedItemRect;
protected:
	void createWhipWndAndShowContent();
	void destroyWhipWnd();
protected:
//	CWhip* m_pWhip;
	CWhipMdiChildWnd* m_pWhipWnd;
};


#endif //__DESIGNCTRSAMPLEOBJECT_H_
