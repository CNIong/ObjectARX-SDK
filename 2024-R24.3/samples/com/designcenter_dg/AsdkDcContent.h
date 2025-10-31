//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

// AsdkDcContent.h : Declaration of the CAsdkDcContent

#ifndef __ASDKDCCONTENT_H_
#define __ASDKDCCONTENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAsdkDcContent
class ATL_NO_VTABLE CAsdkDcContent : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CAsdkDcContent, &CLSID_AsdkDcContent>,
    public ISupportErrorInfo,
    public IDispatchImpl<IAsdkDcContent, &IID_IAsdkDcContent, &LIBID_ASDKDESIGNCENTERSAMPLib>,
    public CWindowImplBase,
    public IAcDcContentView
{
public:
    CAsdkDcContent()
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_ASDKDCCONTENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAsdkDcContent)
    COM_INTERFACE_ENTRY(IAsdkDcContent)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(IAcDcContentView)
END_COM_MAP()

BEGIN_MSG_MAP(CAsdkDcContent)
END_MSG_MAP()

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAsdkDcContent
public:
    void OpenAndDisplayTextFile();
    void OpenAndInsertTextFile();
    
    CString OpenAndReadTextFile(DWORD& length);
    
    STDMETHOD(Initialize)(/*[in]*/ VARIANT varBrowser, VARIANT varReserved);
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

    STDMETHOD(GetCommandString) (
        /*[in]*/ VARIANT varMenuID          // menu id
        , /*[in]*/ dcMenuInfoFlag           // which information is required
        , /*[out]*/ VARIANT *pvarReserved   // reserved, handlers must ignore this
        , /*[out]*/ BSTR *pbstrName         // menu information
    );

    STDMETHOD(DeleteItemData)(/*[in]*/ dcItemDataSource dcSrc
                              , /*[in]*/ VARIANT varItemDataArray);
private:

    TCHAR * m_strSelectedItemText;
    IAcDcContentBrowser* m_pBrowser;

};

#endif //__ASDKDCCONTENT_H_
