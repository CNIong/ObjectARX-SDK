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
// AsdkSquareWrapper.h : Declaration of the CAsdkSquareWrapper

#ifndef __ASDKSQUAREWRAPPER_H_
#define __ASDKSQUAREWRAPPER_H_

#include "axtempl.h"
#include "category.h"
#include "tchar.h"

#include "..\square\squarent.h"

#include "resource.h"       // main symbols


#define DISPID_NUMBER       0x01
#define DISPID_SQUARESIZE   0x02
#define DISPID_CENTERPOINT  0x03

/////////////////////////////////////////////////////////////////////////////
// CAsdkSquareWrapper
class ATL_NO_VTABLE CAsdkSquareWrapper : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CAsdkSquareWrapper, &CLSID_AsdkSquareWrapper>,
    public ISupportErrorInfo,
    public IAcadEntityDispatchImpl<CAsdkSquareWrapper, 
                                    &CLSID_AsdkSquareWrapper,
                                    IAsdkSquareWrapper,
                                    &IID_IAsdkSquareWrapper,
                                    &LIBID_ASDKSQUARELIBLib>,
    public IOPMPropertyExtensionImpl<CAsdkSquareWrapper>,
    public IOPMPropertyExpander
{
public:
    CAsdkSquareWrapper()
    {
    }

DECLARE_REGISTRY_RESOURCEID(IDR_ASDKSQUAREWRAPPER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAsdkSquareWrapper)
    COM_INTERFACE_ENTRY(IAsdkSquareWrapper)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(IAcadBaseObject)
    COM_INTERFACE_ENTRY(IAcadBaseObject2)
    COM_INTERFACE_ENTRY(IAcadObject)
    COM_INTERFACE_ENTRY(IAcadEntity)
    COM_INTERFACE_ENTRY(IRetrieveApplication)
    COM_INTERFACE_ENTRY(IConnectionPointContainer)
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
    
// IAsdkSquareWrapper
public:
    STDMETHOD(get_CenterPoint)(/*[out, retval]*/ VARIANT *pVal);
    STDMETHOD(put_CenterPoint)(/*[in]*/ VARIANT newVal);
    STDMETHOD(get_SquareSize)(/*[out, retval]*/ double *pVal);
    STDMETHOD(put_SquareSize)(/*[in]*/ double newVal);
    STDMETHOD(get_Number)(/*[out, retval]*/ short *pVal);
    STDMETHOD(put_Number)(/*[in]*/ short newVal);

// OPM
//
// IOPMPropertyExtension
//
BEGIN_OPMPROP_MAP()
    OPMPROP_ENTRY(0, 0x00000001, PROPCAT_Data, \
        0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
    OPMPROP_ENTRY(0, 0x00000003, PROPCAT_Geometry, \
        0, 0, 0, _T(""), 0, 1, IID_NULL, IID_NULL, "")
END_OPMPROP_MAP()

    STDMETHOD(GetCategoryName)(THIS_
                           /* [in]  */ PROPCAT propcat, 
                           /* [in]  */ LCID lcid,
                           /* [out] */ BSTR* pbstrName) { return S_FALSE;}

    virtual HINSTANCE GetResourceInstance()
    {
        return _Module.GetResourceInstance();
    }

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

private:
    //short mNumber;
};

#endif //__ASDKSQUAREWRAPPER_H_
