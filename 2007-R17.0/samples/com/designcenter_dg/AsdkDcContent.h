// (C) Copyright 1999-2006 by Autodesk, Inc. 
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
