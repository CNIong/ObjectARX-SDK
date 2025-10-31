// (C) Copyright 2002-2008 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
//----- MyEntityWrapper.h : Declaration of the CMyEntityWrapper
//-----------------------------------------------------------------------------
#pragma once
#include "resource.h"

#include "QuickProperties.h"

//----- CMyEntityWrapper
class ATL_NO_VTABLE CMyEntityWrapper : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyEntityWrapper, &CLSID_MyEntityWrapper>,
	public ISupportErrorInfo,
	public IOPMPropertyExtensionImpl<CMyEntityWrapper>,
	public IOPMPropertyExpander,
	public IAcadEntityDispatchImpl<CMyEntityWrapper, &CLSID_MyEntityWrapper, IMyEntityWrapper, &IID_IMyEntityWrapper, &LIBID_adskQuickPropertiesLib>,
  // allows control of which properties appear in the CUI QuickProps pane
  public IFilterableProperty  
#ifdef NEVER
	//- Please do not remove the following line. It is here to make .NET ATL Wizards
	//- running properly. The parent class will not compile but is required by .NET to recognize
	//-	this class as being an ATL coclass
	,public IDispatchImpl<IMyEntityWrapper, &IID_IIMyEntityWrapper, &LIBID_adskQuickPropertiesLib>
#endif
{
public:
	CMyEntityWrapper () {
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MYENTITYWRAPPER)

	BEGIN_COM_MAP(CMyEntityWrapper)
		COM_INTERFACE_ENTRY(IMyEntityWrapper)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IOPMPropertyExtension)
		COM_INTERFACE_ENTRY(ICategorizeProperties)
		COM_INTERFACE_ENTRY(IPerPropertyBrowsing)
		COM_INTERFACE_ENTRY(IOPMPropertyExpander)
		COM_INTERFACE_ENTRY(IAcadBaseObject)
		COM_INTERFACE_ENTRY(IAcadBaseObject2)
		COM_INTERFACE_ENTRY(IAcadObject)
		COM_INTERFACE_ENTRY(IAcadEntity)
		COM_INTERFACE_ENTRY(IRetrieveApplication)
    COM_INTERFACE_ENTRY(IFilterableProperty)
	END_COM_MAP()

	//----- ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct () {
		return (S_OK) ;
	}
	
	void FinalRelease () {
	}

	//IAcadBaseObjectImpl
	virtual HRESULT CreateNewObject (AcDbObjectId &objId, AcDbObjectId &ownerId, TCHAR *keyName);

public:
  //////////////////////////////////////////////////////////////////////////
  // my properties
  STDMETHOD(get_MyType)(/*[out, retval]*/ LONG *pVal);
  STDMETHOD(put_MyType)(/*[in]*/ LONG newVal);
  STDMETHOD(get_MyPointValue)(/*[out, retval]*/ ACAD_POINT *pVal);
  STDMETHOD(put_MyPointValue)(/*[in]*/ ACAD_POINT newVal);
  // for box, just made up properties
  STDMETHOD(get_MyTextString)(/*[out, retval]*/ BSTR *pVal);
  STDMETHOD(put_MyTextString)(/*[in]*/ BSTR newVal);
  STDMETHOD(get_MyRotation)(/*[out, retval]*/ ACAD_ANGLE *pVal);
  STDMETHOD(put_MyRotation)(/*[in]*/ ACAD_ANGLE newVal);
  STDMETHOD(get_MyLength)(/*[out, retval]*/ ACAD_DISTANCE *pVal);
  STDMETHOD(put_MyLength)(/*[in]*/ ACAD_DISTANCE newVal);
  // for sphere, just made up properties
  STDMETHOD(get_MyDropDown)(/*[out, retval]*/ LONG *pVal);
  STDMETHOD(put_MyDropDown)(/*[in]*/ LONG newVal);
  STDMETHOD(get_MySurfaceArea)(/*[out, retval]*/ ACAD_NOUNITS *pVal);
  STDMETHOD(put_MySurfaceArea)(/*[in]*/ ACAD_NOUNITS newVal);
  // for cylinder, just made up properties
  STDMETHOD(get_MyRadius)(/*[out, retval]*/ ACAD_DISTANCE *pVal);
  STDMETHOD(put_MyRadius)(/*[in]*/ ACAD_DISTANCE newVal);
  STDMETHOD(get_MyWidth)(/*[out, retval]*/ ACAD_DISTANCE *pVal);
  STDMETHOD(put_MyWidth)(/*[in]*/ ACAD_DISTANCE newVal);
  STDMETHOD(get_MyHeight)(/*[out, retval]*/ ACAD_DISTANCE *pVal);
  STDMETHOD(put_MyHeight)(/*[in]*/ ACAD_DISTANCE newVal);

  //////////////////////////////////////////////////////////////////////////
  
  //IAcadBaseObject2Impl
	STDMETHOD(ForceDbResident)(VARIANT_BOOL *forceDbResident) ;
	STDMETHOD(CreateObject)(AcDbObjectId ownerId =AcDbObjectId::kNull, TCHAR *keyName =NULL);
	STDMETHOD(AddToDb)(AcDbObjectId &objId, AcDbObjectId ownerId =AcDbObjectId::kNull, TCHAR *keyName =NULL);

	//IOPMPropertyExtension
  STDMETHOD(ShowProperty)(/*[in]*/ DISPID dispid,/*[out]*/ BOOL* pShow);
	BEGIN_OPMPROP_MAP()
    OPMPROP_CAT_ENTRY(     IDS_OPM_MyTitle, 0x00000401, NULL, NULL) 
    OPMPROP_ENTRY(     IDS_OPM_MyType, 0x00000001, IDS_OPM_MyCategory, IDS_OPM_MyCategory, 0, IDS_OPM_EnumValues, _T("0;1;2"), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(    IDS_OPM_MyPointValue, 0x00000002, IDS_OPM_MyGeometryCategory, IDS_OPM_MyGeometryCategory, IDS_OPM_PositionXYZ, 0, _T(""), 3, 1, IID_NULL, IID_NULL, "")
    // for box, just made up properties
    OPMPROP_CAT_ENTRY(IDS_OPM_MyTextString, 0x00000003, IDS_OPM_MyCategory, IDS_OPM_MyCategory)
    OPMPROP_CAT_ENTRY(    IDS_OPM_MyLength, 0x00000004, IDS_OPM_MyGeometryCategory, IDS_OPM_MyGeometryCategory)
    OPMPROP_CAT_ENTRY(  IDS_OPM_MyRotation, 0x00000005, IDS_OPM_MyGeometryCategory, IDS_OPM_MyGeometryCategory)
    // for sphere, just made up properties
    OPMPROP_ENTRY(     IDS_OPM_MyDropdown, 0x00000006, IDS_OPM_MyCategory, IDS_OPM_MyCategory, 0, IDS_OPM_MyDropDownValues, _T("0;1;2;3"), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_CAT_ENTRY(IDS_OPM_MySurfaceArea, 0x00000007, IDS_OPM_MyGeometryCategory, IDS_OPM_MyGeometryCategory)
    // for cylinder, just made up properties
    OPMPROP_CAT_ENTRY(    IDS_OPM_MyRadius, 0x00000008, IDS_OPM_MyGeometryCategory, IDS_OPM_MyGeometryCategory)
    OPMPROP_CAT_ENTRY(    IDS_OPM_MyHeight, 0x00000009, IDS_OPM_MyGeometryCategory, IDS_OPM_MyGeometryCategory)
    OPMPROP_CAT_ENTRY(     IDS_OPM_MyWidth, 0x0000000A, IDS_OPM_MyGeometryCategory, IDS_OPM_MyGeometryCategory)

	END_OPMPROP_MAP()
	
  //IOPMPropertyExtensionImpl
	virtual HINSTANCE GetResourceInstance () { return (_hdllInstance) ; }

	//IOPMPropertyExpander
	STDMETHOD(GetElementValue)(/*[in]*/DISPID dispID, /*[in]*/DWORD dwCookie, /*[out]*/VARIANT *pVarOut);
	STDMETHOD(SetElementValue)(/*[in]*/DISPID dispID, /*[in]*/DWORD dwCookie, /*[in]*/VARIANT VarIn);
	STDMETHOD(GetElementStrings)(/*[in]*/DISPID dispID, /*[out]*/OPMLPOLESTR __RPC_FAR *pCaStringsOut, /*[out]*/OPMDWORD __RPC_FAR *pCaCookiesOut);
	
  STDMETHOD(GetElementGrouping)(/*[in]*/DISPID dispID, /*[out]*/short *groupingNumber);
	STDMETHOD(GetGroupCount)(/*[in]*/DISPID dispID, /*[out]*/long *nGroupCnt);

  // IFilterableProperty
  // allows control of which properties appear in the CUI QuickProps pane
  STDMETHOD(ShowFilterableProperty)(/*[in]*/DISPID dispID, /*[in]*/AcFilterablePropertyContext context, /*[out, retval]*/BOOL* pbShow);

public:
	//IMyEntityWrapper

} ;

OBJECT_ENTRY_AUTO(__uuidof(MyEntityWrapper), CMyEntityWrapper)

// for use by the quick properties
//////////////////////////////////////////////////////////////////////////
// {9E86419D-2A4E-4d71-954C-58FF58AD2C30}
static const GUID GUID_MyEntityNormal = 
{ 0x9e86419d, 0x2a4e, 0x4d71, { 0x95, 0x4c, 0x58, 0xff, 0x58, 0xad, 0x2c, 0x30 } };
// {323358A1-2475-4128-953D-6D000FF54A1D}
static const GUID GUID_MyEntityWithText = 
{ 0x323358a1, 0x2475, 0x4128, { 0x95, 0x3d, 0x6d, 0x0, 0xf, 0xf5, 0x4a, 0x1d } };
// {6A5348B5-4E68-4ba3-A43C-D57E0E2F0F9C}
static const GUID GUID_MyEntityThicknessWithText = 
{ 0x6a5348b5, 0x4e68, 0x4ba3, { 0xa4, 0x3c, 0xd5, 0x7e, 0xe, 0x2f, 0xf, 0x9c } };
//////////////////////////////////////////////////////////////////////////

