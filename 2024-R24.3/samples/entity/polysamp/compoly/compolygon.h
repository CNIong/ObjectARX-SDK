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
// ComPolygon.h : Declaration of the CComPolygon

#ifndef __COMPOLYGON_H_
#define __COMPOLYGON_H_

#include "resource.h"       // main symbols
#include "dynprops.h"
#include "axtempl.h"
#include "tchar.h"

// DISPIDs for resources
#define DISPID_TEXTSTRING   0x00000001
#define DISPID_NUMSIDES     0x00000002
#define DISPID_NORMAL       0x00000003
#define DISPID_CENTER       0x00000004
#define DISPID_STARTPOINT   0x00000005
#define DISPID_TEXTSTYLENAME 0x00000006
#define DISPID_GETVERTICES  0x00000007
#define DISPID_ELEVATION    0x00000008

/////////////////////////////////////////////////////////////////////////////
// CComPolygon
class ATL_NO_VTABLE CComPolygon : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComPolygon, &CLSID_ComPolygon>,
	public ISupportErrorInfo,
	public IAcadEntityDispatchImpl<CComPolygon, &CLSID_ComPolygon, 
                                   IComPolygon, &IID_IComPolygon, 
                                   &LIBID_COMPOLYLib>,
    //These are the OPM related interfaces. These interfaces
    //are usually not used by any other ObjectDBX host than 
    //AutoCAD, although they could be. AutoCAD uses them
    //to customize the display of this object's properties
    //in the Object Property Manager pane.
    public IOPMPropertyExtensionImpl<CComPolygon>,
    //If a property is VT_ARRAY then IOPMPropertyExpander is QueryInterface-d for
    public IOPMPropertyExpander
{
public:
	CComPolygon()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMPOLYGON)
DECLARE_NOT_AGGREGATABLE(CComPolygon)

BEGIN_COM_MAP(CComPolygon)
	COM_INTERFACE_ENTRY(IComPolygon)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(IAcadBaseObject)
    COM_INTERFACE_ENTRY(IAcadBaseObject2)
	COM_INTERFACE_ENTRY(IAcadObject)
	COM_INTERFACE_ENTRY(IAcadEntity)
    COM_INTERFACE_ENTRY(IRetrieveApplication)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
    COM_INTERFACE_ENTRY(IOPMPropertyExtension)
    COM_INTERFACE_ENTRY(ICategorizeProperties)
    COM_INTERFACE_ENTRY(IPerPropertyBrowsing)
    COM_INTERFACE_ENTRY(IOPMPropertyExpander)
END_COM_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAcadBaseObjectImpl
    virtual HRESULT CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName);

// IAcadBaseObject2Impl
    STDMETHOD(ForceDbResident)(VARIANT_BOOL *forceDbResident);
    STDMETHOD(AddToDb)(AcDbObjectId& objId, AcDbObjectId ownerId = AcDbObjectId::kNull, TCHAR* keyName = NULL);
    STDMETHOD(CreateObject)(AcDbObjectId ownerId = AcDbObjectId::kNull, TCHAR *keyName = NULL);

// IComPolygon
public:
	STDMETHOD(get_Elevation)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Elevation)(/*[in]*/ double newVal);
	STDMETHOD(GetVertices)(/*[retval, out]*/ VARIANT* pnts);
	STDMETHOD(get_TextStyleName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TextStyleName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_StartPoint)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_StartPoint)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_Center)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Center)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_Normal)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Normal)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_NumSides)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumSides)(/*[in]*/ long newVal);
	STDMETHOD(get_TextString)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TextString)(/*[in]*/ BSTR newVal);

//
// OPM
//

// IOPMPropertyExtension
BEGIN_OPMPROP_MAP()
    OPMPROP_ENTRY(0, 0x00000001, PROPCAT_Text, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000002, PROPCAT_Appearance, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000003, PROPCAT_Data, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000004, PROPCAT_Data, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000005, PROPCAT_Data, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000006, PROPCAT_Text, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000008, PROPCAT_Data, 0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
END_OPMPROP_MAP()


    STDMETHOD(GetCategoryName)(THIS_
                           /* [in]  */ PROPCAT propcat, 
                           /* [in]  */ LCID lcid,
                           /* [out] */ BSTR* pbstrName) { return S_FALSE;}

    virtual HINSTANCE GetResourceInstance()
    {
        return _Module.GetResourceInstance();
    }
    //Used for property expansion (currently variant types)
	STDMETHOD(GetElementValue)(
		/* [in] */ DISPID dispID,
		/* [in] */ DWORD dwCookie,
		/* [out] */ VARIANT * pVarOut) ;

    //Used for property expansion (currently variant types)
	STDMETHOD(SetElementValue)(
		/* [in] */ DISPID dispID,
		/* [in] */ DWORD dwCookie,
		/* [in] */ VARIANT VarIn) ;       

    //Used for property expansion (currently variant types)
	STDMETHOD(GetElementStrings)( 
		/* [in] */ DISPID dispID,
		/* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
		/* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut) ;

    //Used for property expansion (currently variant types)
    STDMETHOD(GetElementGrouping)(
        /* [in] */ DISPID dispID,
		/* [out] */ short *groupingNumber) ;

    //Used for property expansion (currently variant types)
    STDMETHOD(GetGroupCount)(
        /* [in] */ DISPID dispID,
		/* [out] */ long *nGroupCnt) ;
    STDMETHOD(GetPredefinedStrings)(
        /* [in] */ DISPID dispID,
        /* [out] */ CALPOLESTR *pCaStringsOut,
        /* [out] */ CADWORD *pCaCookiesOut);
    STDMETHOD(GetPredefinedValue)(
        /* [in] */ DISPID dispID, 
        /* [out] */ DWORD dwCookie, 
        /* [out] */ VARIANT *pVarOut);

    protected:
        AcDbObjectIdArray mObjectIdArray;
};

#endif //__COMPOLYGON_H_
