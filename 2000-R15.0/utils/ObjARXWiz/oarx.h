// [!HeaderName] : Declaration of the [!ClassName]
[!crlf]
[!if=(FileExists, "FALSE")]
#ifndef __[!UpperShortName]_H_
#define __[!UpperShortName]_H_
[!crlf]
#include "resource.h"       // main symbols
#include "[!AcDbHeaderName]"
#include "axtempl.h"
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!AddIncludeFile(TargetFile, AcDbHeaderName)]
[!AddIncludeFile(TargetFile, "axtempl.h")]
[!endif]

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]

class ATL_NO_VTABLE [!ClassName] : 
[!if=(ThreadingModel, "Single")]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if=(ThreadingModel, "Apartment")]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
	public CComCoClass<[!ClassName], &CLSID_[!CoClassName]>,
	public ISupportErrorInfo,
[!if=(DerivedFrom,"AcDbEntity")]
    public IAcadEntityDispatchImpl<[!ClassName],&CLSID_[!CoClassName], [!InterfaceName], &IID_[!InterfaceName], &LIBID_[!LibName]>
[!else]
    public IAcadObjectDispatchImpl<[!ClassName],&CLSID_[!CoClassName],  [!InterfaceName], &IID_[!InterfaceName], &LIBID_[!LibName]>
[!endif]
[!if=(OpmPropExtImpl,"TRUE")]
    ,public IOPMPropertyExtensionImpl<[!ClassName]>
[!endif]
[!if=(OpmPropExpander,"TRUE")]
    ,public IOPMPropertyExpander
[!endif]
{
public:
	[!ClassName]()
	{
	}

[!crlf]
DECLARE_REGISTRY_RESOURCEID([!IDR_REGISTRYID])
[!if=(Aggregatable, "NO")]
DECLARE_NOT_AGGREGATABLE([!ClassName])
[!endif]
[!crlf]
DECLARE_PROTECT_FINAL_CONSTRUCT()

[!crlf]
BEGIN_COM_MAP([!ClassName])
	COM_INTERFACE_ENTRY([!InterfaceName])
	COM_INTERFACE_ENTRY(IDispatch)
[!if=(ErrorInfoEnabled, "TRUE")]
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
[!endif]
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
    COM_INTERFACE_ENTRY(IAcadBaseObject)
	COM_INTERFACE_ENTRY(IAcadObject)
[!if=(DerivedFrom,"AcDbEntity")]
	COM_INTERFACE_ENTRY(IAcadEntity)
[!endif]
    COM_INTERFACE_ENTRY(IRetrieveApplication)
[!if=(OpmPropExtImpl,"TRUE")]
    COM_INTERFACE_ENTRY(IOPMPropertyExtension)
    COM_INTERFACE_ENTRY(ICategorizeProperties)
    COM_INTERFACE_ENTRY(IPerPropertyBrowsing)
[!endif]
[!if=(OpmPropExpander,"TRUE")]
    COM_INTERFACE_ENTRY(IOPMPropertyExpander)
[!endif]
END_COM_MAP()
[!crlf]

[!if=(ConnectionPointsEnabled, "TRUE")]
BEGIN_CONNECTION_POINT_MAP([!ClassName])
[!if=(IPROPERTYNOTIFYSINK, "TRUE")]
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
[!endif]
END_CONNECTION_POINT_MAP()
[!crlf]
[!endif]

[!if=(ErrorInfoEnabled, "TRUE")]
[!crlf]
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
[!endif]
// IAcadBaseObjectImpl
    virtual HRESULT CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName);
    virtual HINSTANCE GetResourceInstance()
    {
        return _Module.GetResourceInstance();
    }
[!if=(OpmPropExtImpl,"TRUE")]

// IOPMPropertyExtension
BEGIN_OPMPROP_MAP()
//TO DO: Use the OPMPROP_ENTRY macro for each of your properties
END_OPMPROP_MAP()
[!endif]
[!if=(OpmPropExpander,"TRUE")]

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
[!endif]
// [!InterfaceName]
public:

};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif //__[!UpperShortName]_H_
[!endif]
