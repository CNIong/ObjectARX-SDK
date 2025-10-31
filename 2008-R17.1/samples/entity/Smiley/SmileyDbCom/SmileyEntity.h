//
// (C) Copyright 2000-2006 by Autodesk, Inc. 
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

// SmileyEntity.h : Declaration of the CSmileyEntity

#ifndef __SMILEYENTITY_H_
#define __SMILEYENTITY_H_

#include "resource.h"       // main symbols
#include "..\SmileyDb\AsdkSmiley.h"
#include "SmileyCats.h"
#include "axtempl.h"
#include "tchar.h"

/////////////////////////////////////////////////////////////////////////////
// CSmileyEntity
class ATL_NO_VTABLE CSmileyEntity : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSmileyEntity, &CLSID_SmileyEntity>,
	public ISupportErrorInfo,
    public IAcadEntityDispatchImpl<CSmileyEntity,&CLSID_SmileyEntity, ISmileyEntity, &IID_ISmileyEntity, &LIBID_SmileyDb>,
    public IOPMPropertyExtensionImpl<CSmileyEntity>,
    public IOPMPropertyExpander,
	public IPerPropertyDisplay
    
{
public:
	CSmileyEntity()
	{
		// Instantiate the marshalling object
	}

static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
{ 
	return _Module.UpdateRegistryFromResource(IDR_SMILEYENTITY, bRegister);
}

//DECLARE_REGISTRY_RESOURCEID(IDR_SMILEYENTITY)
DECLARE_NOT_AGGREGATABLE(CSmileyEntity)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSmileyEntity)
	COM_INTERFACE_ENTRY(ISmileyEntity)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(IAcadBaseObject)
	COM_INTERFACE_ENTRY(IAcadObject)
	COM_INTERFACE_ENTRY(IAcadEntity)
    COM_INTERFACE_ENTRY(IRetrieveApplication)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
    COM_INTERFACE_ENTRY(IOPMPropertyExtension)
    COM_INTERFACE_ENTRY(ICategorizeProperties)
	COM_INTERFACE_ENTRY(IPerPropertyDisplay)
    COM_INTERFACE_ENTRY(IOPMPropertyExpander)
END_COM_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IAcadBaseObjectImpl
    virtual HRESULT CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName);

// ISmileyEntity
public:
	STDMETHOD(ScaleRadius)(double r);
	STDMETHODIMP get_Radius(double FAR* r);
	STDMETHODIMP put_Radius(double r); 
	STDMETHODIMP get_Center(VARIANT* pv);
	STDMETHODIMP put_Center(VARIANT var);
	STDMETHODIMP get_Normal(VARIANT* pv);
	STDMETHODIMP put_Normal(VARIANT var);
	STDMETHODIMP get_EyesSize(double FAR* s);
	STDMETHODIMP put_EyesSize(double s); 
	STDMETHODIMP get_EyesApart(double FAR* s);
	STDMETHODIMP put_EyesApart(double s); 
	STDMETHODIMP get_EyesHeight(double FAR* h);
	STDMETHODIMP put_EyesHeight(double h); 
	STDMETHODIMP get_MouthCenter(VARIANT* pv);
	STDMETHODIMP get_MouthLeft(VARIANT* pv);
	STDMETHODIMP put_MouthLeft(VARIANT var);
	STDMETHODIMP get_MouthBottom(VARIANT* pv);
	STDMETHODIMP put_MouthBottom(VARIANT var);
	STDMETHODIMP get_MouthRight(VARIANT* pv);
	STDMETHODIMP put_MouthRight(VARIANT var);
	STDMETHODIMP get_BackgroundColor(VARIANT *pv);
	STDMETHODIMP put_BackgroundColor(VARIANT var);
	
	//
	// OPM
	//
	
	// IPerPropertyDisplay
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

	
	
	
	// IOPMPropertyExtension

BEGIN_OPMPROP_MAP()
    OPMPROP_ENTRY(0, 0x00000001, PROPCAT_Face, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000002, PROPCAT_Face, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000003, PROPCAT_Face, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000004, PROPCAT_Eyes, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000005, PROPCAT_Eyes, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000006, PROPCAT_Eyes, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000007, PROPCAT_Mouth, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000008, PROPCAT_Mouth, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000009, PROPCAT_Mouth, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x0000000A, PROPCAT_Mouth, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
END_OPMPROP_MAP()

	STDMETHODIMP GetCategoryName(
		PROPCAT propcat,	// [in]
		LCID lcid,			// [in]
		BSTR* pbstrName);	// [out]

    virtual HINSTANCE GetResourceInstance()
    {
        return _Module.GetResourceInstance();
    }


	//IOPMPropertyExpander

	STDMETHOD(GetElementValue)(
		DISPID dispID,		// [in] 
		DWORD dwCookie,		// [in]
		VARIANT * pVarOut);	// [out]

	STDMETHOD(SetElementValue)(
		DISPID dispID,		// [in]
		DWORD dwCookie,		// [in]
		VARIANT VarIn);		// [in]       

	STDMETHOD(GetElementStrings)( 
		DISPID dispID,	// [in]
		OPMLPOLESTR __RPC_FAR *pCaStringsOut,	// [out]
		OPMDWORD __RPC_FAR *pCaCookiesOut);	// [out]

	STDMETHOD(GetElementGrouping)(
        DISPID dispID,	// [in]
		short *groupingNumber);	// [out]

	STDMETHOD(GetGroupCount)(
        DISPID dispID,	// [in]
		long *nGroupCnt);	// [out]

	STDMETHOD(GetPredefinedStrings)(
        DISPID dispID,	// [in]
        CALPOLESTR *pCaStringsOut,	// [out]
        CADWORD *pCaCookiesOut);	// [out]

	STDMETHOD(GetPredefinedValue)(
        DISPID dispID,	// [in] 
        DWORD dwCookie,	// [out] 
        VARIANT *pVarOut);	// [out]

	// ICategorizeProperties methods

    STDMETHODIMP MapPropertyToCategory(DISPID dispid, PROPCAT* ppropcat)
    {
        return AcOpmMapPropertyToCategory(reinterpret_cast<IUnknown*>(this), CSmileyEntity::GetOPMPropertyMap(), dispid, ppropcat);
    }
};

#endif //__SMILEYENTITY_H_
