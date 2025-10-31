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

//
// AXTEMPL.H
//
// Templates for the AutoCAD Automation API
//
// - ATL based templates
//
// - Implementations for:
//   1. IAcadBaseObject
//   2. IAcadObjectEvents
//   3. IRetrieveApplication
//   4. IAcadObject
//   5. IAcadEntity
//   6. IDispatch
//   7. IConnectionPointContainer
//   8. IConnectionPoint
//   9. ICategorizeProperties
//  10. IPerPropertyBrowsing
//  11. IOPMPropertyExtension
//  12. IAcadBaseDatabase
//

#ifndef __AXTEMPL_H_
#define __AXTEMPL_H_

#include "axboiler.h"
#include "oleaprot.h"

#include "opmext.h"
#include "opmimp.h"
#include "dbobjptr.h"
#pragma pack (push, 8)

#pragma warning (disable : 4786)

template<class T>
class ATL_NO_VTABLE IOPMPropertyExtensionImpl : 
    public ICategorizeProperties, 
    public IPerPropertyBrowsing, 
    public IOPMPropertyExtension
{
public:
    IOPMPropertyExtensionImpl()
    {
    }

    virtual ~IOPMPropertyExtensionImpl()
    {
    }

    virtual HINSTANCE GetResourceInstance() = 0;

// ICategorizeProperties methods
    STDMETHODIMP MapPropertyToCategory(DISPID dispid, PROPCAT* ppropcat)
    {
        return AcOpmMapPropertyToCategory(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispid, ppropcat);
    }

	STDMETHODIMP GetCategoryName(PROPCAT propcat, LCID lcid, BSTR* pbstrName)
    {
       return AcOpmGetCategoryName(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), T::GetOPMPropertyMap(), propcat, lcid, pbstrName);
    }

// IPerPropertyBrowsing methods
    STDMETHODIMP GetDisplayString(DISPID dispID, BSTR *pBstr)
    {
        return AcOpmGetDisplayString(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispID, pBstr);
    }
    
    STDMETHODIMP MapPropertyToPage(DISPID dispID, CLSID *pClsid)
    {
        return AcOpmMapPropertyToPage(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispID, pClsid);
    }

    STDMETHODIMP GetPredefinedStrings(DISPID dispID, CALPOLESTR *pCaStringsOut, CADWORD *pCaCookiesOut)
    {
        return AcOpmGetPredefinedStrings(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), T::GetOPMPropertyMap(), dispID, pCaStringsOut, pCaCookiesOut);
    }

    STDMETHODIMP GetPredefinedValue(DISPID dispID, DWORD dwCookie, VARIANT *pVarOut)
    {
        return AcOpmGetPredefinedValue(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispID, dwCookie, pVarOut);
    }

// IOPMPropertyExtension methods
    STDMETHODIMP GetDisplayName(
        DISPID dispID, 
        BSTR *pBstr)
    {
        return AcOpmGetDisplayName(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), T::GetOPMPropertyMap(), dispID, pBstr);
    }

	STDMETHODIMP Editable(
		/* [in] */ DISPID dispID,
		/* [out] */ BOOL __RPC_FAR *bEditable)
    {
	    return AcOpmEditable(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispID, bEditable);
    }

    STDMETHODIMP ShowProperty(
		/* [in] */ DISPID dispID,
		/* [out] */ BOOL *pShow)
    {
	    return AcOpmShowProperty(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispID, pShow);
    }
};

template <class T>
class CProxy_AcadObjectEvents : 
    public IConnectionPointImpl<T, &IID_IAcadObjectEvents, CComDynamicUnkArray>
{
public:

    void Fire_Modified()
	{
		T* pT = static_cast<T*>(this);
        IAcadObject* pAcadObject = static_cast<IAcadObject*>(pT);

		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IAcadObjectEvents* pAcadObjectEvents = reinterpret_cast<IAcadObjectEvents*>(*pp);
                _ASSERTE(pAcadObjectEvents != NULL);

                pAcadObjectEvents->Modified(pAcadObject);
			}
			pp++;
		}
		pT->Unlock();
	}
};

template <class T>
class CProxy_PropertyNotifySink : 
    public IConnectionPointImpl<T, &IID_IPropertyNotifySink, CComDynamicUnkArray>
{
public:

	void Fire_OnChanged()
	{
	    T* pT = static_cast<T*>(this);
	    pT->Lock();
        IUnknown** pp = m_vec.begin();
	    while (pp < m_vec.end())
	    {
		    IPropertyNotifySink* pNotifySink = reinterpret_cast<IPropertyNotifySink*>(*pp);
            if(pNotifySink) 
                pNotifySink->OnChanged(DISPID_UNKNOWN);
            pp++;
	    }
	    pT->Unlock();
    }
};

//
// IAcadBaseObjectImpl is an abstract base class.
//
// Used to manage the AcDbObjectId and transient reactor of 
// the DB resident object. All event firing through the
// IAcadObjectEvents interface is handled here. The CreateNewObject 
// must be implemented by the client of this class.
//
template <class T, const CLSID* pclsid>
class ATL_NO_VTABLE IAcadBaseObjectImpl : 
    public IAcadBaseObject,
	public IConnectionPointContainerImpl<T>,
	public CProxy_AcadObjectEvents<T>,
	public CProxy_PropertyNotifySink<T>
{
public:
    IAcadBaseObjectImpl()
    {
    }

    virtual ~IAcadBaseObjectImpl()
    {
        AcDbObjectPointer<AcDbObject> pObject(m_objId, AcDb::kForRead, Adesk::kTrue);

        // There is only one valid situation for the following to be true:
        //
        // When a database is destroyed (closed) before all COM wrappers have 
        // been released.
        //
        // Any other time this criteria is met should be investigated. No 
        // ASSERT will be thrown, but if you step into this "return" then there
        // is a problem that needs to be researched.
        if(pObject.openStatus() != Acad::eOk)
        {
            return; // stop here or an access violation will follow
        }
        
        // get the OLE link manager and remove the link between the
        // database resident object and this COM wrapper.
        AcAxOleLinkManager* pOleLinkManager = AcAxGetOleLinkManager();
        _ASSERTE(pOleLinkManager != NULL);

        pOleLinkManager->SetIUnknown(pObject.object(), NULL);
    }

    virtual HRESULT CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName) = 0;

// IAcadBaseObject
    STDMETHOD(SetObjectId)(AcDbObjectId& objId, AcDbObjectId ownerId = AcDbObjectId::kNull, TCHAR* keyName = NULL)
    {
        if(objId == AcDbObjectId::kNull) 
        {
            HRESULT hr;
            if(FAILED(hr = CreateNewObject(objId, ownerId, keyName)))
                return hr;
        }

        m_objId = objId;
        _ASSERTE(m_objId != AcDbObjectId::kNull);

        return S_OK;
    }

    STDMETHOD(GetObjectId)(AcDbObjectId* objId)
    {
        *objId = m_objId;
        return S_OK;
    }

    STDMETHOD(Clone)(AcDbObjectId ownerId, LPUNKNOWN* pUnkClone)
    {
        return E_NOTIMPL;
    }
    
    STDMETHOD(GetClassID)(CLSID& clsid) 
    {
        clsid = *pclsid;
        return S_OK;
    }
    
    STDMETHOD(NullObjectId)(void)
    {
        m_objId = AcDbObjectId::kNull;
        return S_OK;
    }

    STDMETHOD(OnModified)(void)
    {
        Fire_Modified();
        Fire_OnChanged();
        return S_OK;
    }

// IConnectionPointContainerImpl
BEGIN_CONNECTION_POINT_MAP(T)
	CONNECTION_POINT_ENTRY(IID_IAcadObjectEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

protected:
    AcDbObjectId m_objId;
};

//
// IRetrieveApplicationImpl
//
// Used to manage the Application interface for the objects.
// Do not derive from this class if your objects are to work
// with DWG Unplugged.
//
class ATL_NO_VTABLE IRetrieveApplicationImpl : 
    public IRetrieveApplication
{
public:
    IRetrieveApplicationImpl()
    {
        m_App = NULL;
    }

    virtual ~IRetrieveApplicationImpl()
    {
        if(m_App != NULL)
            m_App->Release();
    }
	
    STDMETHOD(SetApplicationObject)(LPDISPATCH pApp)
	{
        if(m_App != NULL)
            return E_FAIL;
        m_App = pApp;

        // only addref if there is a valid pointer
        if(m_App != NULL)
            m_App->AddRef();

    	return S_OK;
	}

    // not exported via
    STDMETHOD(GetApplicationObject)(LPDISPATCH* pApp)
	{
        *pApp = m_App;
        if(m_App == NULL)
            return E_FAIL;

        m_App->AddRef();
    	return S_OK;
	}

protected:
    LPDISPATCH m_App;
};

//
// IAcadObjectDispatchImpl
//
// Used to implement all the common object properties
// and methods.
//
template <class C, const CLSID* pclsid, class T, const IID* piid, const GUID* plibid, 
WORD wMajor = 1, WORD wMinor = 0, class tihclass = CComTypeInfoHolder>
class ATL_NO_VTABLE IAcadObjectDispatchImpl : 
    public IDispatchImpl<T, piid, plibid, wMajor, wMinor, tihclass>,
    public IAcadBaseObjectImpl<C, pclsid>,
    public IRetrieveApplicationImpl
{
public:
    
    IAcadObjectDispatchImpl()
    {
    }

    virtual ~IAcadObjectDispatchImpl()
    {
    }

	STDMETHOD(get_Application)(LPDISPATCH* pVal)
    {
        return GetApplicationObject(pVal);
    }

	STDMETHOD(get_ObjectID)(long *pVal)
    {
        if(m_objId == AcDbObjectId::kNull) 
        {
            return RaiseArxException(*piid, 0, Acad::eNullObjectId);
        }

        *pVal = m_objId.asOldId();
        return S_OK;
    }

	STDMETHOD(get_OwnerID)(long *pVal)
    {
        return AcAxGetOwnerId(m_objId, pVal);
    }

	STDMETHOD(Delete)()
    {
        return AcAxErase(m_objId);
    }

	STDMETHOD(SetXData)(VARIANT type, VARIANT data)
    {
	    return AcAxSetXData(m_objId, type, data);
    }

	STDMETHOD(GetXData)(BSTR bstrName, VARIANT* type, VARIANT* data)
    {
        return AcAxGetXData(m_objId, bstrName, type, data);
    }

	STDMETHOD(get_ObjectName)(BSTR *pVal)
    {
        return AcAxGetObjectName(m_objId, pVal);
    }

    STDMETHOD(get_Handle)(BSTR *pVal)
    {
        return AcAxGetHandle(m_objId, pVal);
    }

    STDMETHOD(get_HasExtensionDictionary)(VARIANT_BOOL* bHasDictionary)
    {
        return AcAxHasExtensionDictionary(m_objId, bHasDictionary);
    }

    STDMETHOD(GetExtensionDictionary)(IAcadDictionary** pExtDictionary)
    {
        return AcAxGetExtensionDictionary(m_objId, m_App, pExtDictionary);
    }

    STDMETHOD(get_Database)(IAcadDatabase** pDatabase)
    {
        if(m_objId == AcDbObjectId::kNull ||
           m_objId.database() == NULL)
        {
            return RaiseArxException(*piid, 0, Acad::eNoDatabase);
        }

        CComPtr<IDispatch> pDispatch;
        HRESULT hr = AcAxGetDatabase(m_objId.database(), m_App, &pDispatch);

        if(SUCCEEDED(hr))
        {
            hr = pDispatch->QueryInterface(IID_IAcadDatabase,
                 reinterpret_cast<LPVOID*>(pDatabase));
        }

        return hr;
    }

    STDMETHOD(get_Document)(LPDISPATCH* pDocument)
    {
        if(m_objId == AcDbObjectId::kNull ||
           m_objId.database() == NULL)
        {
            return RaiseArxException(*piid, 0, Acad::eNoDatabase);
        }

        AcAxOleLinkManager* pOleLinkManager = AcAxGetOleLinkManager();
        _ASSERTE(pOleLinkManager != NULL);

        *pDocument = pOleLinkManager->GetDocIDispatch(m_objId.database());
        if(*pDocument == NULL)
        {
            return RaiseArxException(*piid, 0, Acad::eNoDocument);
        }

        (*pDocument)->AddRef();

        return S_OK;
    }

    //
    // Provided for backwards compatibility; for future coding
    // use call Delete() instead of Erase()
    //
	STDMETHOD(Erase)()
    {
        return Delete();
    }

};

//
// IAcadEntityDispatchImpl
//
// Used to implement all the common entity properties
// and methods.
//
template <class C, const CLSID* pclsid, class T, const IID* piid, const GUID* plibid, 
WORD wMajor = 1, WORD wMinor = 0, class tihclass = CComTypeInfoHolder>
class ATL_NO_VTABLE IAcadEntityDispatchImpl : 
    public IAcadObjectDispatchImpl<C, pclsid, T, piid, plibid, wMajor, wMinor, tihclass>
{
public:
	
    STDMETHODIMP get_Color(AcColor* pVal)
    {
	    return AcAxGetColor(m_objId, pVal);
    }

    STDMETHODIMP put_Color(AcColor newVal)
    {
        return AcAxPutColor(m_objId, newVal);
    }

    STDMETHODIMP get_Layer(BSTR * pVal)
    {
	    return AcAxGetLayer(m_objId, pVal);
    }

    STDMETHODIMP put_Layer(BSTR newVal)
    {
	    return AcAxPutLayer(m_objId, newVal);
    }

    STDMETHODIMP get_Linetype(BSTR * pVal)
    {
	    return AcAxGetLinetype(m_objId, pVal);
    }

    STDMETHODIMP put_Linetype(BSTR newVal)
    {
        return AcAxPutLinetype(m_objId, newVal);
    }

    STDMETHODIMP get_LinetypeScale(double * pVal)
    {
	    return AcAxGetLinetypeScale(m_objId, pVal);
    }

    STDMETHODIMP put_LinetypeScale(double newVal)
    {
	    return AcAxPutLinetypeScale(m_objId, newVal);
    }

    STDMETHODIMP get_Visible(VARIANT_BOOL * pVal)
    {
	    return AcAxGetVisible(m_objId, pVal);
    }

    STDMETHODIMP put_Visible(VARIANT_BOOL newVal)
    {
	    return AcAxPutVisible(m_objId, newVal);
    }

    STDMETHODIMP ArrayPolar(int numObjs, double fillAngle, VARIANT basePoint, VARIANT * pArrayObjs)
    {
	    return AcAxArrayPolar(m_objId, m_App, numObjs, fillAngle, basePoint, pArrayObjs);
    }

    STDMETHODIMP ArrayRectangular(int numRows, int numCols, int numLvls, double disRows, double disCols, double disLvls, VARIANT * pArrayObjs)
    {
        return AcAxArrayRectangular(m_objId, m_App, numRows, numCols, numLvls, disRows, disCols, disLvls, pArrayObjs);
    }

    STDMETHODIMP Highlight(VARIANT_BOOL bFlag)
    {
	    return AcAxHighlight(m_objId, bFlag);
    }

    STDMETHODIMP Copy(LPDISPATCH * pCopyObj)
    {
        return AcAxCopy(m_objId, m_App, pCopyObj);
    }

    STDMETHODIMP Move(VARIANT fromPoint, VARIANT toPoint)
    {
	    return AcAxMove(m_objId, fromPoint, toPoint);
    }

    STDMETHODIMP Rotate(VARIANT basePoint, double rotationAngle)
    {
	    return AcAxRotate(m_objId, basePoint, rotationAngle);
    }

    STDMETHODIMP Rotate3D(VARIANT point1, VARIANT point2, double rotationAngle)
    {
	    return AcAxRotate3D(m_objId, point1, point2, rotationAngle);
    }

    STDMETHODIMP Mirror(VARIANT point1, VARIANT point2, LPDISPATCH * pMirrorObj)
    {
	    return AcAxMirror(m_objId, m_App, point1, point2, pMirrorObj);
    }

    STDMETHODIMP Mirror3D(VARIANT point1, VARIANT point2, VARIANT point3, LPDISPATCH * pMirrorObj)
    {
	    return AcAxMirror3D(m_objId, m_App, point1, point2, point3, pMirrorObj);
    }

    STDMETHODIMP ScaleEntity(VARIANT basePoint, double scaleFactor)
    {
	    return AcAxScaleEntity(m_objId, basePoint, scaleFactor);
    }

    STDMETHODIMP TransformBy(VARIANT transMatrix)
    {
	    return AcAxTransformBy(m_objId, transMatrix);
    }

    STDMETHODIMP Update()
    {
	    return AcAxUpdate(m_objId);
    }

    STDMETHODIMP GetBoundingBox(VARIANT * minPoint, VARIANT * maxPoint)
    {
	    return AcAxGetBoundingBox(m_objId, minPoint, maxPoint);
    }

    STDMETHODIMP IntersectWith(LPDISPATCH pEntity, AcExtendOption option, VARIANT * intPoints)
    {
	    return AcAxIntersectWith(m_objId, pEntity, option, intPoints);
    }

    STDMETHODIMP get_PlotStyleName(BSTR* plotStyleName)
    {
	    return AcAxGetPlotStyleName(m_objId, plotStyleName);
    }

    STDMETHODIMP put_PlotStyleName(BSTR plotStyleName)
    {
	    return AcAxPutPlotStyleName(m_objId, plotStyleName);
    }

    STDMETHODIMP get_Lineweight(ACAD_LWEIGHT* lineweight)
    {
	    return AcAxGetLineWeight(m_objId, lineweight);
    }

    STDMETHODIMP put_Lineweight(ACAD_LWEIGHT lineweight)
    {
	    return AcAxPutLineWeight(m_objId, lineweight);
    }

    STDMETHODIMP get_Hyperlinks(IAcadHyperlinks** pHyperlinks)
    {
	    return AcAxGetHyperlinks(m_objId, m_App, pHyperlinks);
    }

    //
    // Provided for backwards compatibility; for future coding
    // use call ObjectName() instead of EntityName()
    //
    STDMETHOD(get_EntityName)(BSTR *pVal)
    {
        return AcAxGetObjectName(m_objId, pVal);
    }

    //
    // Provided for backwards compatibility; for future coding
    // use QueryInterface() to determine object type. In VB,
    // the TypeOf function can be used.
    //
    STDMETHOD(get_EntityType)(long* entType)
    {
        return E_NOTIMPL;
    }
};

//
// IAcadBaseDatabaseImpl is an abstract base class.
//
// Used to manage the AcDbDatabase pointer.
//
template <const CLSID* pclsid>
class ATL_NO_VTABLE IAcadBaseDatabaseImpl : 
    public IAcadBaseDatabase
{
public:
    IAcadBaseDatabaseImpl()
    {
        m_Database = NULL;
    }

// IAcadBaseDatabase
    STDMETHOD(SetDatabase)(AcDbDatabase*& pDb)
    {
        m_Database = pDb;
        return S_OK;
    }

    STDMETHOD(GetDatabase)(AcDbDatabase** pDb)
    {
        if(pDb == NULL)
            return E_POINTER;

        *pDb = m_Database;
        return S_OK;
    }

    STDMETHOD(GetClassID)(CLSID& clsid) 
    {
        clsid = *pclsid;
        return S_OK;
    }

protected:
    AcDbDatabase* m_Database;
};

#pragma pack (pop)
#endif
