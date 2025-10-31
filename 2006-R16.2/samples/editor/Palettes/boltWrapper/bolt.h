//
//
// (C) Copyright 2003 by Autodesk, Inc. 
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
// Bolt.h : Declaration of the CBolt

#ifndef __BOLT_H_
#define __BOLT_H_

#include "stdafx.h"
#include "resource.h"       // main symbols

#define DISPID_ALIGNMENT        0x00000001
#define DISPID_HEADDIAMETER     0x00000002
#define DISPID_HEADHEIGHT       0x00000003
#define DISPID_HEADSIDES        0x00000004
#define DISPID_MATERIALNAME     0x00000005
#define DISPID_POSITION         0x00000006
#define DISPID_SHAFTDIAMETER    0x00000007
#define DISPID_SHAFTLENGTH      0x00000008
#define DISPID_PARTNUMBER       0x00000009
#define DISPID_THREADLENGTH     0x0000000A
#define DISPID_THREADWIDTH      0x0000000B
#define DISPID_COLOR	        0x0000000C

// Category Ids
#define PROPCAT_Global					1
#define PROPCAT_BoltPosition			2
#define PROPCAT_Alignment				3
#define PROPCAT_Part_Desc				4
#define PROPCAT_Dimension   			5
#define PROPCAT_Color   			    6

// Category weights
#define PROPCAT_Global_Weight	 40
#define PROPCAT_Position_Weight	 40
#define PROPCAT_Alignment_Weight 40
#define PROPCAT_Color_Weight     40
#define PROPCAT_Dimension_Weight 20
#define PROPCAT_Part_Desc_Weight 30


/////////////////////////////////////////////////////////////////////////////
// CBolt
class ATL_NO_VTABLE CBolt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBolt, &CLSID_Bolt>,
	public ISupportErrorInfo,
    public IAcadEntityDispatchImpl<CBolt,&CLSID_Bolt, IBolt, &IID_IBolt, &LIBID_AsDkBOLTWRAPPERLib>
	,public IOPMPropertyExtensionImpl2<CBolt>,
	public ICategorizeProperties2Impl<CBolt>,
	public IOPMPropertyExpander,
	public IPerPropertyDisplayImpl<CBolt>
{
public:
	CBolt()
	{
	}

//this function replaces the DECLARE_REGISTRY_RESOURCEID(IDR_BOLT) macro
static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
{
    //In the AutoCAD environment it is better to link ATL dynamically
    return _Module.UpdateRegistryFromResource(IDR_BOLT, bRegister, NULL);
}

// DECLARE_NOT_AGGREGATABLE(CBolt)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBolt)
	COM_INTERFACE_ENTRY(IBolt)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(IAcadBaseObject)
	COM_INTERFACE_ENTRY(IAcadBaseObject2)
	COM_INTERFACE_ENTRY(IAcadObject)
	COM_INTERFACE_ENTRY(IAcadEntity)
    COM_INTERFACE_ENTRY(IRetrieveApplication)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IOPMPropertyExtension)
	COM_INTERFACE_ENTRY(IOPMPropertyExpander)
	COM_INTERFACE_ENTRY(IAcPiCategorizeProperties)
	COM_INTERFACE_ENTRY(IAcPiPropertyDisplay)
	COM_INTERFACE_ENTRY(IPerPropertyBrowsing)
END_COM_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAcadBaseObjectImpl
    virtual HRESULT CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName);
    virtual HINSTANCE GetResourceInstance()
    {
        return _Module.GetResourceInstance();
    }

	// IAcadBaseObject2Impl
    STDMETHOD(ForceDbResident)(VARIANT_BOOL *forceDbResident);
    STDMETHOD(AddToDb)(AcDbObjectId& objId, AcDbObjectId ownerId = AcDbObjectId::kNull, TCHAR* keyName = NULL);
    STDMETHOD(CreateObject)(AcDbObjectId ownerId = AcDbObjectId::kNull, TCHAR *keyName = NULL);

// IBolt
public:
	STDMETHOD(get_threadWidth)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_threadWidth)(/*[in]*/ double newVal);
	STDMETHOD(get_threadLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_threadLength)(/*[in]*/ double newVal);
	STDMETHOD(get_partNumber)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_partNumber)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_shaftLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_shaftLength)(/*[in]*/ double newVal);
	STDMETHOD(get_shaftDiameter)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_shaftDiameter)(/*[in]*/ double newVal);
	STDMETHOD(get_position)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_position)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_materialName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_materialName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_headSides)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_headSides)(/*[in]*/ long newVal);
	STDMETHOD(get_headHeight)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_headHeight)(/*[in]*/ double newVal);
	STDMETHOD(get_headDiameter)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_headDiameter)(/*[in]*/ double newVal);
	STDMETHOD(get_alignment)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_alignment)(/*[in]*/ VARIANT newVal);
	
	//IOPMPropertyExtension	
	BEGIN_OPMPROP_MAP()
	// DescriptionID, dispID, catagoryID, catagoryNameID, 
	// elements string list ID (semi-colon separator), 
	// predefined strings ID (semi-colon separator), predefined values, 
	// grouping, editable property, other, proppage
	OPMPROP_ENTRY(0, DISPID_POSITION,	  PROPCAT_Position, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_ALIGNMENT,	  PROPCAT_Alignment, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_COLOR,        PROPCAT_Color,     0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_HEADDIAMETER, PROPCAT_Dimension, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_HEADHEIGHT,	  PROPCAT_Dimension, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_HEADSIDES,	  PROPCAT_Dimension, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_SHAFTDIAMETER,PROPCAT_Dimension, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_SHAFTLENGTH,  PROPCAT_Dimension, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_THREADLENGTH ,PROPCAT_Dimension, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_THREADWIDTH,  PROPCAT_Dimension, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_MATERIALNAME, PROPCAT_Part_Desc, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	OPMPROP_ENTRY(0, DISPID_PARTNUMBER,	  PROPCAT_Part_Desc, 0, 0, 0, "", 0, 1, IID_NULL, IID_NULL, "")
	END_OPMPROP_MAP()

	///////////////////////////////////////////
	// ICategorizeProperties2 Implementation //
	///////////////////////////////////////////
	BEGIN_CAT_MAP()
	//nId, NameId, DescId, nParentId, nWeight
	
	//#define CATEGORY_MAP_ENTRY(nId, NameId, DescId, nParentId, nWeight)
	CATEGORY_MAP_ENTRY(PROPCAT_Global, IDS_GLOBAL, IDS_GLOBAL_DESC, 0, PROPCAT_Global_Weight)
	CATEGORY_MAP_ENTRY(PROPCAT_Global, IDS_POSITION, IDS_POSITION_DESC, PROPCAT_Global, PROPCAT_Position_Weight)
	CATEGORY_MAP_ENTRY(PROPCAT_Global, IDS_ALIGNMENT, IDS_ALIGNMENT_DESC,  PROPCAT_Global, PROPCAT_Alignment_Weight)
	CATEGORY_MAP_ENTRY(PROPCAT_Color, IDS_COLOR, IDS_COLOR_DESC,  PROPCAT_Global, PROPCAT_Color_Weight)
	CATEGORY_MAP_ENTRY(PROPCAT_Part_Desc, IDS_PART, IDS_PART_DESC, 0, PROPCAT_Part_Desc_Weight)
	CATEGORY_MAP_ENTRY(PROPCAT_Dimension, IDS_DIMENSION, IDS_DIMENSION_DESC, 0, PROPCAT_Dimension_Weight)
    END_CAT_MAP()

		////////////////////////////////////////
	// IPerPropertyDisplay Implementation //
	////////////////////////////////////////
	BEGIN_PERPROPDISPLAY_MAP()

	PROP_DISP_ENTRY(DISPID_POSITION, "", MAKEINTRESOURCE(IDB_BITMAP1), PICTYPE_BITMAP, NULL,
					PICTYPE_UNINITIALIZED, RGB(255, 0, 0), false, 1, PROPCAT_Position_Weight)
	PROP_DISP_ENTRY(DISPID_ALIGNMENT, "", MAKEINTRESOURCE(IDB_BITMAP2), PICTYPE_BITMAP, NULL,
					PICTYPE_UNINITIALIZED, RGB(255, 0, 0), false, 1, PROPCAT_Alignment_Weight)

	END_PERPROPDISPLAY_MAP()

	BEGIN_CATCMDBTN_MAP()
	END_CATCMDBTN_MAP()

	BEGIN_CMDBTN_MAP()
	END_CMDBTN_MAP()

	//IOPMPropertyExpander
	STDMETHOD(GetElementValue)(
		/* [in] */ DISPID dispID,
		/* [in] */ DWORD dwCookie,
		/* [out] */ VARIANT * pVarOut) ;
    //IOPMPropertyExpander
	STDMETHOD(SetElementValue)(
		/* [in] */ DISPID dispID,
		/* [in] */ DWORD dwCookie,
		/* [in] */ VARIANT VarIn) ;       
    //IOPMPropertyExpander
	STDMETHOD(GetElementStrings)( 
		/* [in] */ DISPID dispID,
		/* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
		/* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut) ;
    //IOPMPropertyExpander
    STDMETHOD(GetElementGrouping)(
        /* [in] */ DISPID dispID,
		/* [out] */ short *groupingNumber) ;
    //IOPMPropertyExpander
    STDMETHOD(GetGroupCount)(
        /* [in] */ DISPID dispID,
		/* [out] */ long *nGroupCnt) ;
    STDMETHOD(GetPredefinedStrings)(
	    /*[in]*/DISPID dispID, 
		/*[out]*/CALPOLESTR *pCaStringsOut,
		/*[out]*/CADWORD *pCaCookiesOut);
	STDMETHOD(GetPredefinedValue)(
	    /*[in]*/DISPID dispID, 
		/*[out]*/DWORD dwCookie,
		/*[out]*/VARIANT *pVarOut);


	////////////////////////////////////////////
	// ICategorizeProperties2 Implementation //
	////////////////////////////////////////////
	STDMETHOD(MapPropertyToCategory)(/*[in]*/DISPID dispID,/*[out]*/int *pCatID);
	STDMETHOD(GetCategoryName)(/*[in]*/int CatID,/*[in]*/LCID lCid,/*[out]*/BSTR *pCategoryName);
	STDMETHOD(GetCategoryDescription)(/*[in]*/int CatID,/*[in]*/LCID lCid,/*[out]*/BSTR *pCategoryDescription);
	STDMETHOD(ShowCategory)(/*[in]*/int CatID,/*[out]*/VARIANT_BOOL *pShow);
	STDMETHOD(GetCategoryWeight)(/*[in]*/int CatID,/*[out]*/long *pCategoryWeight);
	STDMETHOD(GetParentCategory)(/*[in]*/int CatID,/*[out]*/int *pParentCatID);
	STDMETHOD(GetUniqueID)(/*[out]*/BSTR *pVal);
  // throwing assert.
	STDMETHOD(GetCommandButtons)(/*[in]*/int CatID,/*[out]*/VARIANT *pCatCommandBtns);


	  
	////////////////////////////////////////
	// IPerPropertyDisplay Implementation //
	////////////////////////////////////////
	STDMETHOD(GetCustomPropertyCtrl)(/*[in]*/VARIANT Id,/*[in]*/LCID lcid,/*[out]*/BSTR *pProgId);
	STDMETHOD(GetPropTextColor)(/*[in]*/VARIANT Id,/*[out]*/OLE_COLOR *pTextColor);
	STDMETHOD(IsFullView)(/*[in]*/VARIANT Id,/*[out]*/VARIANT_BOOL *pVisible,/*[out]*/DWORD *pIntegralHeight);
	STDMETHOD(GetPropertyWeight)(/*[in]*/VARIANT Id,/*[out]*/long *pPropertyWeight);

	//IOPMPropertyExtension
	//Implement this function to override the name of the property
    STDMETHOD(GetDisplayName)(/*[in]*/DISPID dispID,/*[out]*/BSTR *propName);
    //Override to make property read-only
	STDMETHOD(Editable)(/*[in]*/DISPID dispID, /*[out]*/BOOL* bEditable);
	//Override to hide the property from display
	STDMETHOD(ShowProperty)(/*[in]*/DISPID dispID, /*[out]*/BOOL *pShow);
};


// Helper macro for Get/Put methods
#define BEGIN_PROP_GETPUT(CLASS,OPENMODE)\
	try\
	{\
		AcAxDocLock docLock(m_objRef.objectId(),AcAxDocLock::kNormal);\
		Acad::ErrorStatus es;\
		AcAxObjectRefPtr<CLASS> pEntity(&m_objRef,OPENMODE,Adesk::kTrue);\
		if((es=pEntity.openStatus())!=Acad::eOk)\
			throw es;

#define END_PROP_GETPUT(INTERFACEID)\
	}\
    catch(const Acad::ErrorStatus)\
    {\
        return Error(L"Failed to set Entity Property",INTERFACEID,E_FAIL);\
    }\
    catch(const HRESULT hr)\
    {\
        return Error(L"Invalid argument.",INTERFACEID,hr);\
    }\
	return S_OK;

#endif //__BOLT_H_
