//
// (C) Copyright 1998-2007 by Autodesk, Inc.
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
//  13. IAcadBaseObject2
//  14. IAcadShadowDisplay
//  15. IAcadBaseSubEntity

#ifndef __AXTEMPL_H_
#define __AXTEMPL_H_

#include "adesk.h"
#include "axobjref.h"
#include "axboiler.h"
#include "oleaprot.h"

#include "opmext.h"
#include "opmimp.h"
#include "dbobjptr.h"
#include "rxregsvc.h"
#pragma pack (push, 8)

#pragma warning (disable : 4786)
interface IAcadShadowDisplay;

// The following #defies may be used in place of VARIANT_TRUE and
// VARIANT_FALSE to avoid Microsoft compiler warnings C4310
#define ACAX_VARIANT_TRUE (VARIANT_BOOL) -1
#define ACAX_VARIANT_FALSE (VARIANT_BOOL) 0

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
        CComPtr<IAcadObject> pAcadObject;
        pT->QueryInterface(__uuidof(IAcadObject),(void**)&pAcadObject);
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
        Fire_OnChanged(DISPID_UNKNOWN);
    }

    void Fire_OnChanged(DISPID dispId)
    {
        T* pT = static_cast<T*>(this);
        pT->Lock();
        IUnknown** pp = m_vec.begin();
        while (pp < m_vec.end())
        {
            IPropertyNotifySink* pNotifySink = reinterpret_cast<IPropertyNotifySink*>(*pp);
            if(pNotifySink)
                pNotifySink->OnChanged(dispId);
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
        // There have been a number of CERs that show the open call below to
        // fail due to a bad objectId.  The failure caused an access violation,
        // so we try to head that off here by validating the objectId.  It
        // would be best if we could track down why the objectId is invalid,
        // but we have not been able to get the information necessary to actually
        // reproduce the bad Id, so we can't do anything more than try and
        // prevent the exception here.  Fixes bug #530196    Artc 11/3/03
        //
        if (!m_objId.isValid())
            return;

        AcDbObjectPointer<AcDbObject> pObject(m_objId, AcDb::kForRead, Adesk::kTrue);
        if(pObject.openStatus() != Acad::eOk)
        {
            //opening for read may fail if the object is open for write.
            //Since we are only trying to remove a transient reactor kForNotify
            //is sufficient.

            // There is only one valid situation for the following to be true:
            //
            // When a database is destroyed (closed) before all COM wrappers have
            // been released.
            //
            // Any other time this criteria is met should be investigated. No
            // ASSERT will be thrown, but if you step into this "return" then there
            // is a problem that needs to be researched.
            AcDbObject* pTemp;
            if (Acad::eOk != acdbOpenObject(pTemp,m_objId,AcDb::kForNotify,Adesk::kTrue))
            {
                return; // stop here or an access violation will follow
            }
            pObject.acquire(pTemp);
        }

        // get the OLE link manager and remove the link between the
        // database resident object and this COM wrapper.
        AcAxOleLinkManager* pOleLinkManager = AcAxGetOleLinkManager();
        _ASSERTE(pOleLinkManager != NULL);

        pOleLinkManager->SetIUnknown(pObject.object(), NULL);
    }

    // Implement to create a new object to the specified owner. Return
    // the new object id to the caller.
    virtual HRESULT CreateNewObject(AcDbObjectId& objId,
                                AcDbObjectId& ownerId, ACHAR* keyName) = 0;

// IAcadBaseObject
    STDMETHOD(SetObjectId)(AcDbObjectId& objId,
                    AcDbObjectId ownerId = AcDbObjectId::kNull,
                    ACHAR* keyName = NULL)
    {
        // If we are already wrapping an object we cannot be
        // set to wrap another, this would break the links
        // established by AcAxOleLinkManager and other COM
        // clients who have a reference to this wrapper instance.
        if (!m_objId.isNull())
            return E_FAIL;

        if(objId == AcDbObjectId::kNull)
        {
            HRESULT hr;
            if(FAILED(hr = CreateNewObject(objId, ownerId, keyName)))
                return hr;
        }

        m_objId = objId;
        _ASSERTE(m_objId != AcDbObjectId::kNull);
        ObjectIdModified();

        return S_OK;
    }

    STDMETHOD(GetObjectId)(AcDbObjectId* objId)
    {
        *objId = m_objId;
        return S_OK;
    }

    STDMETHOD(Clone)(AcDbObjectId /*ownerId*/, LPUNKNOWN* /*pUnkClone*/)
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
        ObjectIdModified();
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

    // Notify derived classes (e.g. IAcadBaseObject2Impl) that
    // objectId has been modified
    virtual void ObjectIdModified()
    {};
};

//
// IAcadBaseObject2Impl is an abstract base class.
//
// Used to manage both database resident and non-resident  objects, this class
// extends the IAcadBaseObjectImpl class to add support for non-database
// resident objects.  COM wrapper classes derive either from this class OR from
// IAcadBaseObjectImpl, not both
//
// Derived classes wanting to support non-database resident objects should
// override the following methods:
//
//      1. ForceDbResident
//      Override this method to return VARIANT_FALSE.
//
//      2. AddToDb
//      Override this method to add a non-database resident wrapped
//      object to a database. Be sure to call SetObjectId on the wrapper before
//      returning from AddToDb() to change the wrapper state and establish
//      database reactors for the database resident object.
//
//      3. CreateObject
//      Override this method to create a non-database resident
//      wrapped object of the correct type. Be sure to attach it to the
//      encapsulated AcAxObjectRef before returning.
//
// Derived classes should also call Fire_Notification before returning from any
// method which modifies a non-database resident object. This call is necessary
// because the notification mechanism used by the default implementation relies
// on AcDbObjectReactors and does not work for non-database resident objects.

#pragma warning(push)
#pragma warning(disable : 4100) // disable unreferenced formal paramter warning
template <class T, const CLSID* pclsid>
class ATL_NO_VTABLE IAcadBaseObject2Impl :
    public IAcadBaseObject2,
    public IAcadBaseObjectImpl<T, pclsid>
{
public:
    IAcadBaseObject2Impl()
    {
    };

    virtual ~IAcadBaseObject2Impl()
    {
    };

    // IAcadBaseObject2

    // Attaches the wrapper instance to an object via an AcDbObject pointer.
    STDMETHOD(SetObject)(AcDbObject*& pObj)
    {
        if (pObj->objectId().isNull())
        {
            NullObjectId();
            m_objRef.acquire(pObj);
            return S_OK;
        }
        else
        {
            AcDbObjectId tmpId = pObj->objectId();
            return SetObjectId(tmpId);
        }
    }

    // Releases a wrapper instance from an object only if the wrapper is to
    // a non-database resident object
    STDMETHOD(GetObject)(AcDbObject*& pObj)
    {
        pObj = NULL;
        if (!m_objRef.objectId().isNull())
            return E_FAIL;

        AcDbObjectId tmpId;
        m_objRef.release(tmpId, pObj);
        _ASSERTE(m_objId.isNull());
        _ASSERTE(tmpId.isNull());
        return S_OK;
    }
 

    // Objects which support non-database resident instances should override
    // this method to return FALSE.
    STDMETHOD(ForceDbResident)(VARIANT_BOOL *forceDbResident)
    {
        if (NULL == forceDbResident)
            return E_POINTER;

        *forceDbResident = ACAX_VARIANT_TRUE;
        return S_OK;
    }

    // Objects which support non-database resident wrappers must implement this
    // method to allow non-database resident objects to be added to a database.
    STDMETHOD(AddToDb)(AcDbObjectId& objId,
                       AcDbObjectId ownerId = AcDbObjectId::kNull,
                       ACHAR* keyName = NULL)
    {
        return E_NOTIMPL;
    }

    // Objects which support non-database resident wrappers must implement this
    // method to allow non-database resident objects to be created.
    STDMETHOD(CreateObject)(AcDbObjectId ownerId = AcDbObjectId::kNull,
                            ACHAR *keyName = NULL)
    {
        // Example implementation:
        //   releaseObject();
        //   AcDbLine *pLine = new AcDbLine();
        //   SetObject(pLine);
        // ...
        return E_NOTIMPL;
    }

    // Wrappers for non-database resident objects may have a reference to a
    // non-database resident object. This method allows callers to determine
    // if any object is actually being wrapped
    STDMETHOD(ObjectExists)(VARIANT_BOOL *objectExists)
    {
        if (NULL == objectExists)
            return E_POINTER;

        *objectExists = m_objRef.isNull() ? ACAX_VARIANT_FALSE : ACAX_VARIANT_TRUE;
        return S_OK;
    }

    STDMETHOD(OnModified)(DISPID dispId = DISPID_UNKNOWN)
    {
        Fire_Modified();
        Fire_OnChanged(dispId);
        return S_OK;
    }


protected:
    AcAxObjectRef m_objRef;

    // IAcadBaseObject override.
    // Capture the modified id in our object reference.
    virtual void ObjectIdModified()
    {
        releaseReference();
        m_objRef.acquire(m_objId);
    }

    // Derived classes which support non-database residency should call this
    // method from each of their "set" methods to notify connected listeners
    // that the property has changed. This is not necessary for
    // database-resident objects because AutoCAD's object and database reactors
    // fire the notification automatically.
    void Fire_Notification(DISPID dispId = DISPID_UNKNOWN)
    {
        if (m_objRef.objectId().isNull())
        {
            Fire_Modified();
            Fire_OnChanged(dispId);
        }
    }

    // Release the enclosed object reference, deleting the encapsulated
    // database object if it is not database resident
    STDMETHOD(releaseReference)()
    {
        AcDbObjectId tmpId;
        AcDbObject*  pTmp = NULL;
        m_objRef.release(tmpId, pTmp);
        if (NULL != pTmp && pTmp->objectId().isNull())
            delete pTmp;
        return S_OK;
    }
};
#pragma warning(pop)

//
// IRetrieveApplicationImpl
//
// Used to manage the Application interface for the objects.
// Do not derive from this class if your objects are to work
// with a non-AutoCAD based host application.
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
    public IAcadBaseObject2Impl<C, pclsid>,
    public IRetrieveApplicationImpl
{
public:

    IAcadObjectDispatchImpl()
    {
        // ATL doesn't support multiple LCID's at the same time
        // Whatever LCID is queried for first is the one that is used.
        _tih.EnsureTI(acrxProductLCID());
    }

    virtual ~IAcadObjectDispatchImpl()
    {
    }

    STDMETHOD(get_Application)(LPDISPATCH* pVal)
    {
        return GetApplicationObject(pVal);
    }

    STDMETHOD(get_ObjectID)(Adesk::IntDbId *pVal)
    {
        *pVal = m_objRef.objectId().asOldId();
        return S_OK;
    }

    STDMETHOD(get_OwnerID)(Adesk::IntDbId *pVal)
    {
        return AcAxGetOwnerId(m_objRef, pVal);
    }

#ifdef _WIN64
    STDMETHOD(get_ObjectID32)(Adesk::Int32 *pVal)
    {
        if(pVal)
            *pVal = AcAxGetObjectId32(m_objRef.objectId().asOldId());
        return S_OK;
    }

    STDMETHOD(get_OwnerID32)(Adesk::Int32 *pVal)
    {
        Adesk::IntDbId objId;
        HRESULT hr = AcAxGetOwnerId(m_objRef, &objId);
        if(pVal)
            *pVal = AcAxGetObjectId32(objId);
        return hr;
    }
#endif

    STDMETHOD(Delete)()
    {
        return AcAxErase(m_objRef);
    }

    STDMETHOD(SetXData)(VARIANT type, VARIANT data)
    {
        return AcAxSetXData(m_objRef, type, data);
    }

    STDMETHOD(GetXData)(BSTR bstrName, VARIANT* type, VARIANT* data)
    {
        return AcAxGetXData(m_objRef, bstrName, type, data);
    }

    STDMETHOD(get_ObjectName)(BSTR *pVal)
    {
        return AcAxGetObjectName(m_objRef, pVal);
    }

    STDMETHOD(get_Handle)(BSTR *pVal)
    {
        return AcAxGetHandle(m_objRef, pVal);
    }

    STDMETHOD(get_HasExtensionDictionary)(VARIANT_BOOL* bHasDictionary)
    {
        return AcAxHasExtensionDictionary(m_objRef, bHasDictionary);
    }

    STDMETHOD(GetExtensionDictionary)(IAcadDictionary** pExtDictionary)
    {
        return AcAxGetExtensionDictionary(m_objRef, m_App, pExtDictionary);
    }

    STDMETHOD(get_Database)(IAcadDatabase** pDatabase)
    {
        if(m_objRef.objectId() == AcDbObjectId::kNull ||
           m_objRef.objectId().database() == NULL)
        {
            return RaiseArxException(*piid, 0, Acad::eNoDatabase);
        }

        CComPtr<IDispatch> pDispatch;
        HRESULT hr = AcAxGetDatabase(m_objRef.objectId().database(), m_App, &pDispatch);

        if(SUCCEEDED(hr))
        {
            hr = pDispatch->QueryInterface(IID_IAcadDatabase,
                 reinterpret_cast<LPVOID*>(pDatabase));
        }

        return hr;
    }

    STDMETHOD(get_Document)(LPDISPATCH* pDocument)
    {
        if(m_objRef.objectId() == AcDbObjectId::kNull ||
           m_objRef.objectId().database() == NULL)
        {
            return RaiseArxException(*piid, 0, Acad::eNoDatabase);
        }

        AcAxOleLinkManager* pOleLinkManager = AcAxGetOleLinkManager();
        _ASSERTE(pOleLinkManager != NULL);

        *pDocument = pOleLinkManager->GetDocIDispatch(m_objRef.objectId().database());
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
        return AcAxGetColor(m_objRef, pVal);
    }

    STDMETHODIMP put_Color(AcColor newVal)
    {
        return AcAxPutColor(m_objRef, newVal);
    }

    STDMETHODIMP get_TrueColor(IAcadAcCmColor** pColor)
    {
        return AcAxGetTrueColor(m_objRef, pColor);
    }

    STDMETHODIMP put_TrueColor(IAcadAcCmColor* color)
    {
        return AcAxPutTrueColor(m_objRef, color);
    }

    STDMETHODIMP get_Layer(BSTR * pVal)
    {
        return AcAxGetLayer(m_objRef, pVal);
    }

    STDMETHODIMP put_Layer(BSTR newVal)
    {
        return AcAxPutLayer(m_objRef, newVal);
    }

    STDMETHODIMP get_Linetype(BSTR * pVal)
    {
        return AcAxGetLinetype(m_objRef, pVal);
    }

    STDMETHODIMP put_Linetype(BSTR newVal)
    {
        return AcAxPutLinetype(m_objRef, newVal);
    }

    STDMETHODIMP get_Material(BSTR * pVal)
    {
        return AcAxGetMaterial(m_objRef, pVal);
    }

    STDMETHODIMP put_Material(BSTR newVal)
    {
        return AcAxPutMaterial(m_objRef, newVal);
    }

    STDMETHODIMP get_LinetypeScale(double * pVal)
    {
        return AcAxGetLinetypeScale(m_objRef, pVal);
    }

    STDMETHODIMP put_LinetypeScale(double newVal)
    {
        return AcAxPutLinetypeScale(m_objRef, newVal);
    }

    STDMETHODIMP get_Visible(VARIANT_BOOL * pVal)
    {
        return AcAxGetVisible(m_objRef, pVal);
    }

    STDMETHODIMP put_Visible(VARIANT_BOOL newVal)
    {
        return AcAxPutVisible(m_objRef, newVal);
    }

    STDMETHODIMP ArrayPolar(int numObjs, double fillAngle, VARIANT basePoint, VARIANT * pArrayObjs)
    {
        return AcAxArrayPolar(m_objRef, m_App, numObjs, fillAngle, basePoint, pArrayObjs);
    }

    STDMETHODIMP ArrayRectangular(int numRows, int numCols, int numLvls, double disRows, double disCols, double disLvls, VARIANT * pArrayObjs)
    {
        return AcAxArrayRectangular(m_objRef, m_App, numRows, numCols, numLvls, disRows, disCols, disLvls, pArrayObjs);
    }

    STDMETHODIMP Highlight(VARIANT_BOOL bFlag)
    {
        return AcAxHighlight(m_objRef, bFlag);
    }

    STDMETHODIMP Copy(LPDISPATCH * pCopyObj)
    {
        return AcAxCopy(m_objRef, m_App, pCopyObj);
    }

    STDMETHODIMP Move(VARIANT fromPoint, VARIANT toPoint)
    {
        return AcAxMove(m_objRef, fromPoint, toPoint);
    }

    STDMETHODIMP Rotate(VARIANT basePoint, double rotationAngle)
    {
        return AcAxRotate(m_objRef, basePoint, rotationAngle);
    }

    STDMETHODIMP Rotate3D(VARIANT point1, VARIANT point2, double rotationAngle)
    {
        return AcAxRotate3D(m_objRef, point1, point2, rotationAngle);
    }

    STDMETHODIMP Mirror(VARIANT point1, VARIANT point2, LPDISPATCH * pMirrorObj)
    {
        return AcAxMirror(m_objRef, m_App, point1, point2, pMirrorObj);
    }

    STDMETHODIMP Mirror3D(VARIANT point1, VARIANT point2, VARIANT point3, LPDISPATCH * pMirrorObj)
    {
        return AcAxMirror3D(m_objRef, m_App, point1, point2, point3, pMirrorObj);
    }

    STDMETHODIMP ScaleEntity(VARIANT basePoint, double scaleFactor)
    {
        return AcAxScaleEntity(m_objRef, basePoint, scaleFactor);
    }

    STDMETHODIMP TransformBy(VARIANT transMatrix)
    {
        return AcAxTransformBy(m_objRef, transMatrix);
    }

    STDMETHODIMP Update()
    {
        return AcAxUpdate(m_objRef);
    }

    STDMETHODIMP GetBoundingBox(VARIANT * minPoint, VARIANT * maxPoint)
    {
        return AcAxGetBoundingBox(m_objRef, minPoint, maxPoint);
    }

    STDMETHODIMP IntersectWith(LPDISPATCH pEntity, AcExtendOption option, VARIANT * intPoints)
    {
        return AcAxIntersectWith(m_objRef, pEntity, option, intPoints);
    }

    STDMETHODIMP get_PlotStyleName(BSTR* plotStyleName)
    {
        return AcAxGetPlotStyleName(m_objRef, plotStyleName);
    }

    STDMETHODIMP put_PlotStyleName(BSTR plotStyleName)
    {
        return AcAxPutPlotStyleName(m_objRef, plotStyleName);
    }

    STDMETHODIMP get_Lineweight(ACAD_LWEIGHT* lineweight)
    {
        return AcAxGetLineWeight(m_objRef, lineweight);
    }

    STDMETHODIMP put_Lineweight(ACAD_LWEIGHT lineweight)
    {
        return AcAxPutLineWeight(m_objRef, lineweight);
    }

    STDMETHODIMP get_Hyperlinks(IAcadHyperlinks** pHyperlinks)
    {
        return AcAxGetHyperlinks(m_objRef, m_App, pHyperlinks);
    }

    //
    // Provided for backwards compatibility; for future coding
    // use call ObjectName() instead of EntityName()
    //
    STDMETHOD(get_EntityName)(BSTR *pVal)
    {
        return AcAxGetObjectName(m_objRef, pVal);
    }

    //
    // Provided for backwards compatibility; for future coding
    // use QueryInterface() to determine object type. In VB,
    // the TypeOf function can be used.
    //
    STDMETHOD(get_EntityType)(long* /*entType*/)
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

// IAcadBaseSubEntity
template <class C, const CLSID* pclsid, class T, const IID* piid,
    const GUID* plibid,
    WORD wMajor = 1, WORD wMinor = 0, class tihclass = CComTypeInfoHolder>
class ATL_NO_VTABLE IAcadBaseSubEntityImpl : 
    public IDispatchImpl<T, piid, plibid, wMajor, wMinor, tihclass>,
    public IAcadBaseSubEntity,
    public IRetrieveApplicationImpl,
    public IConnectionPointContainerImpl<C>,
    public CProxy_AcadObjectEvents<C>,
    public CProxy_PropertyNotifySink<C>
{
public:
    IAcadBaseSubEntityImpl()
    {
    }
    //
    // TODO: MGraf - Addressing the link manager to follow.
    // I expect this mechanism to fall apart with the mutliple select situation,
    // but I'm moving forward with implementation for now.
    virtual ~IAcadBaseSubEntityImpl()
    {
        // unregister ourself with the link manager (mimic IAcadBaseObjectImpl)
        if (!m_objId.isValid())
            return;

        AcDbObjectPointer<AcDbObject> pObject(m_objId, AcDb::kForRead,
            Adesk::kTrue);
        if (pObject.openStatus() != Acad::eOk) {
            // try open for notify as last resort.
            AcDbObject* pTemp;
            if (Acad::eOk != acdbOpenObject(pTemp, m_objId, AcDb::kForNotify,
                Adesk::kTrue))
            {
                return; 
            }
            pObject.acquire(pTemp);
        }
        AcAxOleLinkManager* pOleLinkManager = AcAxGetOleLinkManager();
        _ASSERTE(pOleLinkManager != NULL);

        pOleLinkManager->SetIUnknown(pObject.object(), m_subentPath.subentId(),
            NULL);
    }

    STDMETHOD(OnModified)()
    {
        Fire_Modified();
        Fire_OnChanged();
        return S_OK;
    }

    STDMETHOD(SetFullSubEntPath)(AcDbFullSubentPath& subentPath)
    {
        m_subentPath = subentPath;
        AcDbObjectIdArray objectIds = m_subentPath.objectIds();
        if (0 != objectIds.length())
            m_objId = objectIds[objectIds.length() - 1];
        return S_OK;
    }

    STDMETHOD(GetFullSubEntPath)(AcDbFullSubentPath* subentPath)
    {
        *subentPath = m_subentPath;
        return S_OK;
    }

    STDMETHOD(GetClassID)(CLSID& clsid) 
    {
        clsid = *pclsid;
        return S_OK;
    }

    STDMETHOD(get_ObjectName)(BSTR *pVal)
    {
        return AcAxGetObjectName(m_objId, pVal);
    }
    // Parent property returned as default:
    STDMETHODIMP get_Color(IAcadAcCmColor** pColor)
    {
        return AcAxGetTrueColor(m_objId, pColor);
    }
    STDMETHODIMP get_Layer(BSTR * pVal)
    {
        return AcAxGetLayer(m_objId, pVal);
    }
    STDMETHODIMP get_Linetype(BSTR * pVal)
    {
        return AcAxGetLinetype(m_objId, pVal);
    }
    STDMETHODIMP get_LinetypeScale(double * pVal)
    {
        return AcAxGetLinetypeScale(m_objId, pVal);
    }
    STDMETHODIMP get_PlotStyleName(BSTR* plotStyleName)
    {
        return AcAxGetPlotStyleName(m_objId, plotStyleName);
    }
    STDMETHODIMP get_Lineweight(ACAD_LWEIGHT* lineweight)
    {
        return AcAxGetLineWeight(m_objId, lineweight);
    }
    STDMETHODIMP get_Hyperlinks(IAcadHyperlinks** pHyperlinks)
    {
        return AcAxGetHyperlinks(m_objId, m_App, pHyperlinks);
    }

// IConnectionPointContainerImpl
BEGIN_CONNECTION_POINT_MAP(C)
    CONNECTION_POINT_ENTRY(IID_IAcadObjectEvents)
    CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

protected:
    STDMETHODIMP parentObjectId(AcDbObjectId &objID)
    {
        AcDbObjectIdArray objectIds = m_subentPath.objectIds();
        if (0 != objectIds.length()) {
            objID = objectIds[objectIds.length() - 1];
            return S_OK;
        }
        return E_FAIL;
    }
    AcDbFullSubentPath m_subentPath;
    AcDbObjectId m_objId;
};

#define IPropCommandButtonsImpl IAcPiPropCommandButtonsImpl
template<class T>
class ATL_NO_VTABLE IAcPiPropCommandButtonsImpl :
    public IAcPiPropCommandButtons
{
public:
    CMDBTN_VECTOR m_CmdBtnVector;

    CMDBTN_VECTOR & GetCmdBtnVector()
    {
        return m_CmdBtnVector;
    }

    bool IsDefaultCmdBtnEntry(CMDBTN_ENTRY in)
    {
        if(in.m_lpEnBtnBmpRes != NULL)
            return false;

        if(in.m_nEnBtnBmpType != PICTYPE_UNINITIALIZED)
            return false;

        if(in.m_lpDisBtnBmpRes != NULL)
            return false;

        if(in.m_nDisBtnBmpType != PICTYPE_UNINITIALIZED)
            return false;

        if(in.m_pfnBtnProc != NULL)
            return false;

        if(in.m_nBtnNameId != NULL)
            return false;

        if(in.m_nStyle != NULL)
            return false;

        return true;
    }

    IAcPiPropCommandButtonsImpl()
    {
        m_CmdBtnVector.clear();
        int i=0;
        while(!IsDefaultCmdBtnEntry(T::GetPropCmdBtnArray()[i]))
        {
            m_CmdBtnVector.push_back(T::GetPropCmdBtnArray()[i]);
            i++;
        }
    }

    virtual ~IAcPiPropCommandButtonsImpl()
    {
    }

    virtual HINSTANCE GetResourceInstance() = 0;

// IAcPiPropCommandButtons methods
    STDMETHODIMP GetButtons(VARIANT *pCmdBtns)
    {
       return AcOpmGetCommandButtons(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), GetCmdBtnVector(), pCmdBtns);
    }
};

#define IPerPropertyDisplayImpl IAcPiPropertyDisplayImpl
template<class T>
class ATL_NO_VTABLE IAcPiPropertyDisplayImpl :
    public IAcPiPropertyDisplay
{
public:
    PROP_DISP_VECTOR m_PropDispVector;

    PROP_DISP_VECTOR & GetPerPropDisplayVector()
    {
        return m_PropDispVector;
    }
    bool IsDefaultPerPropDispEntry(PER_PROP_DISP_ENTRY in)
    {
        if(in.m_bFullView != false)
            return false;

        if(in.m_ProgID != NULL)
            return false;

        if(in.m_dispid != -1)
            return false;

        if(in.m_dwIntegralHeight != -1)
            return false;

        if(in.m_lpEllipsisBmpRes != NULL)
            return false;

        if(in.m_nEllipsisBmpType != PICTYPE_UNINITIALIZED)
            return false;

        if(in.m_lpLeftIconRes != NULL)
            return false;

        if(in.m_nLeftIconType != PICTYPE_UNINITIALIZED)
            return false;

        if(in.m_nWeight != -1)
            return false;

        if(in.m_TextColor != 0x80000008)
            return false;

        return true;
    }

    IAcPiPropertyDisplayImpl()
    {
        m_PropDispVector.clear();
        int i=0;
        while(!IsDefaultPerPropDispEntry(T::GetPerPropDisplayArray()[i]))
        {
            m_PropDispVector.push_back(T::GetPerPropDisplayArray()[i]);
            i++;
        }
    }

    virtual ~IAcPiPropertyDisplayImpl()
    {
    }

    virtual HINSTANCE GetResourceInstance() = 0;

// IAcPiPropertyDisplay methods
    STDMETHODIMP GetCustomPropertyCtrl(VARIANT Id, LCID lcid, BSTR *psProgId)
    {
        return AcOpmGetCustomPropertyCtrl(reinterpret_cast<IUnknown*>(this), GetPerPropDisplayVector(), Id, lcid, psProgId);
    }

    STDMETHODIMP GetPropertyIcon(VARIANT Id, IUnknown **ppIcon)
    {
        return AcOpmGetPropertyIcon(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), GetPerPropDisplayVector(), Id, ppIcon);
    }

    STDMETHODIMP GetPropTextColor(VARIANT Id, OLE_COLOR *pTextColor)
    {
        return AcOpmGetPropTextColor(reinterpret_cast<IUnknown*>(this), GetPerPropDisplayVector(), Id, pTextColor);
    }

    STDMETHODIMP IsFullView(VARIANT Id, VARIANT_BOOL *pbVisible, DWORD *pIntegralHeight)
    {
        return AcOpmIsPropFullView(reinterpret_cast<IUnknown*>(this), GetPerPropDisplayVector(), Id, pbVisible, pIntegralHeight);
    }

    STDMETHODIMP GetPropertyWeight(VARIANT Id, long *pPropertyWeight)
    {
        return AcOpmGetPropertyWeight(reinterpret_cast<IUnknown*>(this), GetPerPropDisplayVector(), Id, pPropertyWeight);
    }
};

#define ICategorizeProperties2Impl IAcPiCategorizePropertiesImpl
template<class T>
class ATL_NO_VTABLE IAcPiCategorizePropertiesImpl :
    public IAcPiCategorizeProperties
{
public:
    CATEGORY_VECTOR  m_CategoryVector;
    CATCMDBTN_VECTOR m_CatCmdBtnVector;

    CATEGORY_VECTOR & GetCategoryVector()
    {
        return m_CategoryVector;
    }

    CATCMDBTN_VECTOR & GetCmdBtnVector()
    {
        return m_CatCmdBtnVector;
    }

    bool IsDefaultCategoryEntry(CATEGORY_ENTRY in)
    {
        if(in.m_CatID != -1)
            return false;

        if(in.m_nWeight != -1)
            return false;

        if(in.m_ParentCatID != -1)
            return false;

        if(in.m_nDescId != 0)
            return false;

        if(in.m_nNameId != 0)
            return false;

        return true;
    }

    bool IsDefaultCmdBtnEntry(CATCMDBTN_ENTRY in)
    {
        if(in.m_CatID != -1)
            return false;

        if(in.m_lpEnBtnBmpRes != NULL)
            return false;

        if(in.m_nEnBtnBmpType != PICTYPE_UNINITIALIZED)
            return false;

        if(in.m_lpDisBtnBmpRes != NULL)
            return false;

        if(in.m_nDisBtnBmpType != PICTYPE_UNINITIALIZED)
            return false;

        if(in.m_nStyle != NULL)
            return false;

        if(in.m_pfnBtnProc != NULL)
            return false;

        if(in.m_nBtnNameId != 0)
            return false;

        return true;
    }

    IAcPiCategorizePropertiesImpl()
    {
        m_CatCmdBtnVector.clear();
        m_CategoryVector.clear();
        int i=0;
        while(!IsDefaultCmdBtnEntry(T::GetCmdBtnArray()[i]))
        {
            m_CatCmdBtnVector.push_back(T::GetCmdBtnArray()[i]);
            i++;
        }

        i=0;
        while(!IsDefaultCategoryEntry(T::GetCatArray()[i]))
        {
            m_CategoryVector.push_back(T::GetCatArray()[i]);
            i++;
        }
    }

    virtual ~IAcPiCategorizePropertiesImpl()
    {
    }

    virtual HINSTANCE GetResourceInstance() = 0;

// IAcPiCategorizeProperties methods
    STDMETHODIMP MapPropertyToCategory(DISPID dispid, PROPCAT* ppropcat)
    {
        return AcOpmMapPropertyToCategory(reinterpret_cast<IUnknown*>(this), T::GetOPMPropertyMap(), dispid, ppropcat);
    }

    STDMETHODIMP GetCategoryName(PROPCAT propcat, LCID lcid, BSTR* pbstrName)
    {
       HRESULT hr;
       hr = AcOpmGetCategoryName(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), T::GetOPMPropertyMap(), propcat, lcid, pbstrName);
       if(hr == S_FALSE) {
           hr = AcOpmGetCategoryName(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), GetCategoryVector(), propcat, lcid, pbstrName);
       }
       return hr;
    }

    STDMETHODIMP GetCategoryDescription(PROPCAT propcat, LCID lcid, BSTR* pbstrDesc)
    {
       return AcOpmGetCategoryDescription(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), GetCategoryVector(), propcat, lcid, pbstrDesc);
    }

    STDMETHODIMP GetCategoryWeight(PROPCAT CatID, long *pCategoryWeight)
    {
       return AcOpmGetCategoryWeight(reinterpret_cast<IUnknown*>(this), GetCategoryVector(), CatID, pCategoryWeight);
    }

    STDMETHODIMP GetParentCategory(PROPCAT CatID, PROPCAT *pParentCatID)
    {
       return AcOpmGetParentCategory(reinterpret_cast<IUnknown*>(this), GetCategoryVector(), CatID, pParentCatID);
    }

    STDMETHODIMP GetCommandButtons(PROPCAT CatID, VARIANT *pCatCmdBtns)
    {
       return AcOpmGetCategoryCommandButtons(reinterpret_cast<IUnknown*>(this), GetResourceInstance(), GetCmdBtnVector(), CatID, pCatCmdBtns);
    }
};

template<class T>
class ATL_NO_VTABLE IOPMPropertyExtensionImpl2 :
    public IPerPropertyBrowsing,
    public IOPMPropertyExtension
{
public:
    IOPMPropertyExtensionImpl2()
    {
    }

    virtual ~IOPMPropertyExtensionImpl2()
    {
    }

    virtual HINSTANCE GetResourceInstance() = 0;

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


template <class C>
class ATL_NO_VTABLE IAcadShadowDisplayImpl :  public IAcadShadowDisplay
{
public:

    STDMETHODIMP get_ShadowDisplay(AcShadowDisplayType* pShadowDisplay)
    {
        CComPtr<IAcadBaseObject> pAcadBaseObject;
        HRESULT hr = QueryInterface(IID_IAcadBaseObject, (LPVOID*) &pAcadBaseObject);
        if(FAILED(hr))
            return S_FALSE;

        AcDbObjectId objId;
        pAcadBaseObject->GetObjectId(&objId);
        return AcAxGetShadowDisplay(objId, pShadowDisplay);
    }

    STDMETHODIMP put_ShadowDisplay(AcShadowDisplayType shadowDisplay)
    {
        CComPtr<IAcadBaseObject> pAcadBaseObject;
        HRESULT hr = QueryInterface(IID_IAcadBaseObject, (LPVOID*) &pAcadBaseObject);
        if(FAILED(hr))
            return S_FALSE;

        AcDbObjectId objId;
        pAcadBaseObject->GetObjectId(&objId);
        return AcAxPutShadowDisplay(objId, shadowDisplay);
    }

    STDMETHODIMP get_EnableShadowDisplay(BOOL* bEnabled)
    {
        *bEnabled = TRUE;

        return S_OK;
    }
};

#pragma pack (pop)
#endif
