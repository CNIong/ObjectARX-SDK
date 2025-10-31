//
//
// (C) Copyright 2002 by Autodesk, Inc. 
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
//
// BoltTool.h : Declaration of the CBoltTool

#ifndef __BOLTTOOL_H_
#define __BOLTTOOL_H_

#include "resource.h"       // main symbols
#include "AcTc_i.h"
#include "AcPi.h"
#include "clipdata.h"
//#include "AcTcUiPreview.h"
#include "boltproperties.h"

#define CF_AUTOCAD      "AutoCAD.r16"

/////////////////////////////////////////////////////////////////////////////
// CBoltTool
class ATL_NO_VTABLE CBoltTool : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBoltTool, &CLSID_BoltTool>,
	public IDispatchImpl<IBoltTool, &IID_IBoltTool, &LIBID_asdkBOLTTOOLSLib>,
	public IDispatchImpl<IAcadTool, &IID_IAcadTool, &LIBID_asdkBOLTTOOLSLib>,
    public IDispatchImpl<IAcadStockTool, &IID_IAcadStockTool, &LIBID_asdkBOLTTOOLSLib>,
	public IPropertyUnspecified,
	public IDropTarget,
	public IPerPropertyDisplay
{
public:
	
	CBoltTool()
	{
		mnColor=256;  // bylayer
		nIdCmdFirst=0;
		nIdCmdLast=0;
		strcpy(mLayer,"0");
		mpToolProp=NULL; 
		bDroppedTool=false;

		if (mcfAutoCAD == NULL) {
			mcfAutoCAD = (CLIPFORMAT)::RegisterClipboardFormat(CF_AUTOCAD);
			ASSERT(mcfAutoCAD != NULL);
		}

	}

DECLARE_REGISTRY_RESOURCEID(IDR_BOLTTOOL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBoltTool)
	COM_INTERFACE_ENTRY(IBoltTool)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IAcadStockTool)
    COM_INTERFACE_ENTRY(IAcadTool)
	COM_INTERFACE_ENTRY(IDropTarget)
	COM_INTERFACE_ENTRY(IPerPropertyDisplay)
	COM_INTERFACE_ENTRY(IPropertyUnspecified)
END_COM_MAP()

// IAcadStockTool members
public:
    STDMETHOD(CreateTool) (/*[out, retval]*/ IUnknown** ppTool);

// IAcadTool members
public:
    STDMETHOD(get_EditMode) (/*[out, retval]*/ long* pVal);
    STDMETHOD(GetStockTool) (/*[out, retval]*/ IUnknown** ppToolClass);
    STDMETHOD(SetToolProperties) (/*[in]*/ IUnknown* pProp);
    STDMETHOD(Load) (/*[in]*/ IUnknown* pXmlElement);
    STDMETHOD(Save) (/*[in]*/ IUnknown* pXmlElement);
    STDMETHOD(Execute) (/*[in]*/ long lFlag, /*[in]*/ DWORD /*HWND*/ hWnd, /*[in]*/ DWORD point, /*[in]*/ DWORD dwKeyState);
    STDMETHOD(GetData) (/*[in]*/ VARIANT *pObjUnkArray, /*[in]*/ VARIANT *pDynUnkArray);
    STDMETHOD(BeginEdit) ();
    
	// CPH V059GLV4
	//STDMETHOD(Edit) (/*[in]*/ IUnknown* pProp, /*[out]*/ VARIANT_BOOL* pRet);
    //STDMETHOD(EndEdit) ();
	STDMETHOD (Edit) (/*[in]*/ IUnknown* pProp,/*[in]*/ LONG /*HWND*/ hWndParent, /*[out]*/ VARIANT_BOOL* pRet);
	STDMETHOD (EndEdit)(/*[in]*/ VARIANT_BOOL bEditCancelled);
	STDMETHOD (Dropped)(/*[in]*/ BSTR bstrUrl);
	STDMETHOD (Refreshed)(/*[in]*/ BSTR bstrUrl);
	STDMETHOD (SetEditorWindow)(/*[in]*/ LONG /*HWND*/ hWndEditor, /*[in]*/ IUnknown*	pPropInspector);
	STDMETHOD (ValidateEditChanges)();    
	STDMETHOD (GetToolProperties)(/*[out, retval]*/ IUnknown** pToolProp);
	//STDMETHOD(CancelExecution) (/*[in]*/ long lReason, /*[out]*/ long* pRetFlag);
	// end CPH
    
	STDMETHOD(New) ();
    STDMETHOD(GetDropTarget) (/*[out, retval]*/ IUnknown** ppDropTarget);

    STDMETHOD(GetContextMenu) (/*[in]*/ int nContextFlag, /*[in]*/ DWORD /*HMENU*/ hMenu, /*[in]*/ UINT idCmdFirst,/*[in]*/  UINT idCmdLast, /*[out, retval]*/ DWORD* pFlag);
    STDMETHOD(GetCommandString) (/*[in]*/ UINT idCmd, /*[out, retval]*/BSTR* pbstrHelpText);
    STDMETHOD(InvokeCommand) (/*[in]*/ UINT idCmd, /*[in]*/ DWORD /*HWND*/ hWnd);
    STDMETHOD(GetDragDropContextInfo) (/*[in]*/ IUnknown*	pIUnknown, /*[out]*/BSTR* pbstrText, /*[out]*/ DWORD* pFlag);
    

    // IDropTarget members
	STDMETHOD(DragEnter) (/*[unique][in]*/ IDataObject __RPC_FAR *pDataObj, /*[in]*/ DWORD grfKeyState, /*[in]*/ POINTL pt, /*[out][in]*/ DWORD __RPC_FAR *pdwEffect);
    STDMETHOD(DragOver) (/*[in]*/ DWORD grfKeyState, /*[in]*/ POINTL pt, /*[out][in]*/ DWORD __RPC_FAR *pdwEffect);
    STDMETHOD(DragLeave) (void);
    STDMETHOD(Drop) (/*[unique][in]*/ IDataObject __RPC_FAR *pDataObj, /*[in]*/ DWORD grfKeyState, /*[in]*/ POINTL pt, /*[out][in]*/ DWORD __RPC_FAR *pdwEffect);

    // IPropertyUnspecified Members
	STDMETHOD (IsValueUnspecified)(/*[in]*/ VARIANT varId, /*[out]*/ VARIANT_BOOL *pVal);
    STDMETHOD (SetUnspecified)(/*[in]*/ VARIANT varId, /*[in]*/ VARIANT_BOOL bIsUnspecified);
    STDMETHOD (IsUnspecifiedAllowed)(/*[in]*/ VARIANT varId, /*[out]*/ VARIANT_BOOL *pVal);
	STDMETHOD (GetUnspecifiedString)(VARIANT,BSTR * );

    // IPerPropertyDisplay members
    STDMETHOD(GetCustomPropertyCtrl) ( 
            /* [in] */ VARIANT varId,
            /* [in] */ LCID lcid,
            /* [out] */BSTR *pProgId);
        
    STDMETHOD(GetPropertyIcon) ( 
        /* [in] */ VARIANT varId,
        /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *pIcon);

    STDMETHOD(GetPropertyWeight) (
    /* [in] */ VARIANT varId,
    /* [out] */ long *pPropertyWeight);
    
    STDMETHOD(GetEllipsisBitMap) ( 
        /* [in] */ VARIANT varId,
        /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *pBitMap);
    
    STDMETHOD(GetPropTextColor) ( 
        /* [in] */ VARIANT varId,
        /* [out] */ OLE_COLOR __RPC_FAR *pTextColor);
    
    STDMETHOD(GetPropHelpProc) ( 
        /* [in] */ VARIANT varId,
        /* [out] */ LONG __RPC_FAR *pHelpProc);
    
    STDMETHOD(IsFullView) ( 
        /* [in] */ VARIANT varId,
        /* [out] */ VARIANT_BOOL __RPC_FAR *pbVisible,
        /* [out] */ DWORD __RPC_FAR *pIntegralHeight);

    BOOL                UpdatePreview       (void);
	
	
// IBoltTool
public:
	STDMETHOD(get_Layer)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Layer)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ThreadWidth)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_ThreadWidth)(/*[in]*/ double newVal);
	STDMETHOD(get_ThreadLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_ThreadLength)(/*[in]*/ double newVal);
	STDMETHOD(get_ShaftDiameter)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_ShaftDiameter)(/*[in]*/ double newVal);
	STDMETHOD(get_ShaftLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_ShaftLength)(/*[in]*/ double newVal);
	STDMETHOD(get_HeadHeight)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_HeadHeight)(/*[in]*/ double newVal);
	STDMETHOD(get_HeadSides)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_HeadSides)(/*[in]*/ long newVal);
	STDMETHOD(get_HeadDiameter)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_HeadDiameter)(/*[in]*/ double newVal);
	STDMETHOD(get_Color)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Color)(/*[in]*/ long newVal);
		
	
protected:

	static CLIPFORMAT   mcfAutoCAD;
	
	BOOL ExtractProperties(LPCTSTR pszTempFile);
	BOOL GetClipInfo(COleDataObject* pDataObject, ClipboardInfo* pClipboardInfo);
	
	CComPtr<IAcadToolProperties>  mpToolProp;
	BOOL mColorUnspecified;
	BOOL mLayerUnspecified;
	CBoltProperties props;
	HWND mhPreviewWnd;
	int mnColor;
	bool bDroppedTool;
	char partNumber[128];
	char mLayer[128];
	char materialName[128];
	long headSides;
	double threadWidth;
	double threadLength;
	double headDiameter;
	double headHeight;
	double shaftDiameter;
	double shaftLength;
	UINT nIdCmdFirst;
    UINT nIdCmdLast;
	STDMETHOD(get_partNumber)(BSTR* pVal);
	STDMETHOD(put_partNumber)(BSTR newVal);
	STDMETHOD(get_materialName)(BSTR* pVal);
	STDMETHOD(put_materialName)(BSTR newVal);
public:
	CString createUniqeImageName(void);
	void executeAsModifier(void);
};

#endif //__BOLTTOOL_H_
