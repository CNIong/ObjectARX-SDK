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
#include "StdAfx.h"
// ComPolygon.cpp : Implementation of CComPolygon
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "compoly_i.h"
#include "ComPolygon.h"
#include "dbsymtb.h"
#include "poly.h"
#include "axpnt3d.h"
#include "axpnt2d.h"
#include "dbxutil.h"
#include "dbapserv.h"

#include "axlock.h"



#define AXEntityDocLockNoDbOk(objId)                        \
    AcAxDocLock docLock(objId, AcAxDocLock::kNormal);       \
    if (docLock.lockStatus() != Acad::eNoDatabase && \
        docLock.lockStatus() != Acad::eOk)                  \
        throw docLock.lockStatus();

#define AXEntityDocLock(objId)                              \
    AcAxDocLock docLock(objId, AcAxDocLock::kNormal);       \
    if(docLock.lockStatus() != Acad::eOk)                   \
        throw docLock.lockStatus();

/////////////////////////////////////////////////////////////////////////////
// CComPolygon
#define CHECKOUTPARAM(x) if (x==NULL) return E_POINTER;

STDMETHODIMP CComPolygon::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IComPolygon,
        &IID_IAcadObject,
        &IID_IAcadEntity,
        &IID_IOPMPropertyExpander
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}



//This is used to get the value for an element in a group.
//The element is identified by the dwCookie parameter
STDMETHODIMP CComPolygon::GetElementValue(
	/* [in] */ DISPID dispID,
	/* [in] */ DWORD dwCookie,
	/* [out] */ VARIANT * pVarOut)
{
    CHECKOUTPARAM(pVarOut);
    if (dispID >= DISPID_NORMAL && dispID <= DISPID_STARTPOINT)
    {
        try
        {
            if (dwCookie>2)
                throw Acad::eInvalidInput;
            Acad::ErrorStatus es;
            AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	        if((es=pPoly.openStatus()) != Acad::eOk)
                throw es;

            AcAxPoint3d pt;
			Adesk::Boolean bAsVector=Adesk::kFalse;
			if (dispID == DISPID_NORMAL)
            {
                pt = pPoly->normal();
                //translate from wcs to ucs
                acdbWcs2Ucs(asDblArray(pt),asDblArray(pt),Adesk::kTrue);
                ::VariantCopy(pVarOut,&CComVariant(pt[dwCookie]));
            } else {
                AcAxPoint2d pt2d;
			    switch (dispID)
			    {
			    case DISPID_CENTER:
				    pt2d = pPoly->center();
				    break;
			    case DISPID_STARTPOINT:
				    pt2d = pPoly->startPoint();
				    break;
			    default:
				    throw Acad::eInvalidInput;
			    }
                pt.set(pt2d.x,pt2d.y,pPoly->elevation());
                //translate from wcs to ucs
                acdbEcs2Ucs(asDblArray(pt),asDblArray(pt),asDblArray(pPoly->normal()),Adesk::kFalse);
                ::VariantCopy(pVarOut,&CComVariant(pt[dwCookie]));
            }
        }
        catch(const Acad::ErrorStatus)
        {
            return Error(L"Failed to open object",IID_IComPolygon,E_FAIL);
        }
        catch(const HRESULT hr)
        {
            return Error(L"Invalid argument.",IID_IComPolygon,hr);
        }
    }
	return S_OK;
}

//This is used to set the value for an element in a group.
//The element is identified by the dwCookie parameter
STDMETHODIMP CComPolygon::SetElementValue(
	/* [in] */ DISPID dispID,
	/* [in] */ DWORD dwCookie,
	/* [in] */ VARIANT VarIn)
{
    if (dispID >= DISPID_NORMAL && dispID <= DISPID_STARTPOINT)
    {
        try
        {
            if (dwCookie>2)
                throw Acad::eInvalidInput;
            Acad::ErrorStatus es;
            AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	        if((es=pPoly.openStatus()) != Acad::eOk)
                throw es;

            AcAxPoint3d pt;
			AcAxPoint2d pt2d;
			if (dispID == DISPID_NORMAL)
            {
                pt = pPoly->normal();
                //translate from wcs to ucs
                acdbEcs2Ucs(asDblArray(pt),asDblArray(pt),asDblArray(pPoly->normal()),Adesk::kTrue);
            } else {
			    switch (dispID)
			    {
			    case DISPID_CENTER:
				    pt2d = pPoly->center();
				    break;
			    case DISPID_STARTPOINT:
				    pt2d = pPoly->startPoint();
				    break;
			    default:
				    throw Acad::eInvalidInput;
			    }
                pt.set(pt2d.x,pt2d.y,pPoly->elevation());
                //translate from wcs to ucs
                acdbEcs2Ucs(asDblArray(pt),asDblArray(pt),asDblArray(pPoly->normal()),Adesk::kFalse);
            }
	        pt[dwCookie] = V_R8(&VarIn);

            if (dispID == DISPID_NORMAL) {
                acdbUcs2Wcs(asDblArray(pt),asDblArray(pt),Adesk::kTrue);
                if ((es=pPoly->setNormal(pt.asVector()))!=Acad::eOk)
                    throw es;    
            }else { 
                acdbUcs2Ecs(asDblArray(pt),asDblArray(pt),asDblArray(pPoly->normal()),Adesk::kFalse);
                pt2d.set(pt.x,pt.y);
                pPoly->setElevation(pt.z);
                if (dispID == DISPID_CENTER)
                    if ((es=pPoly->setCenter(pt2d))!=Acad::eOk)
                        throw es;            
                if (dispID == DISPID_STARTPOINT)
                    if ((es=pPoly->setStartPoint(pt2d))!=Acad::eOk)
                        throw es;            
            }
            Fire_Notification(dispID);
        }
        catch(const Acad::ErrorStatus)
        {
            return Error(L"Failed to open object",IID_IComPolygon,E_FAIL);
        }
        catch(const HRESULT hr)
        {
            return Error(L"Invalid argument.",IID_IComPolygon,hr);
        }

    }
	return S_OK;
}
//This is called to get the display string for each
//element in a group.
//We return strings for each coordinate for this object
STDMETHODIMP CComPolygon::GetElementStrings( 
	/* [in] */ DISPID dispID,
	/* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
	/* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut)
{
    if (dispID >= DISPID_NORMAL && dispID <= DISPID_STARTPOINT)
    {
        long size;
        if (dispID == DISPID_NORMAL){
            size = 3;
            pCaStringsOut->pElems = (LPOLESTR *)::CoTaskMemAlloc(sizeof(LPOLESTR) * size);
            pCaCookiesOut->pElems = (DWORD *)::CoTaskMemAlloc(sizeof(DWORD) * size);
            for (long i=0;i<size;i++)
                pCaCookiesOut->pElems[i] = i;
            pCaStringsOut->pElems[0] = ::SysAllocString(L"Normal X");
            pCaStringsOut->pElems[1] = ::SysAllocString(L"Normal Y");
            pCaStringsOut->pElems[2] = ::SysAllocString(L"Normal Z");
            pCaStringsOut->cElems = size;
            pCaCookiesOut->cElems = size;
        }
        if (dispID == DISPID_CENTER || dispID == DISPID_STARTPOINT)
        {
            size = 2;
            pCaStringsOut->pElems = (LPOLESTR *)::CoTaskMemAlloc(sizeof(LPOLESTR) * size);
            pCaCookiesOut->pElems = (DWORD *)::CoTaskMemAlloc(sizeof(DWORD) * size);
            for (long i=0;i<size;i++)
                pCaCookiesOut->pElems[i] = i;
            pCaStringsOut->cElems = size;
            pCaCookiesOut->cElems = size;
        }
        if (dispID == DISPID_CENTER){
            pCaStringsOut->pElems[0] = ::SysAllocString(L"Center X");
            pCaStringsOut->pElems[1] = ::SysAllocString(L"Center Y");
        }
        if (dispID == DISPID_STARTPOINT){
            pCaStringsOut->pElems[0] = ::SysAllocString(L"StartPoint X");
            pCaStringsOut->pElems[1] = ::SysAllocString(L"StartPoint Y");
        }
    }
    return S_OK;
}


//This function is called to determine the number of elements in a group
//It defaults to the number of elements in the array (3 in this case)
STDMETHODIMP CComPolygon::GetElementGrouping(
    /* [in] */ DISPID dispID,
	/* [out] */ short *groupingNumber)
{
    return E_NOTIMPL;
}


//This function is called to determine how many groups there are in
//the array.
//For example in case of the polyline this is the number of vertices.
//We are not implementing this because it defaults to nGroupCnt = 0
STDMETHODIMP CComPolygon::GetGroupCount(
    /* [in] */ DISPID dispID,
	/* [out] */ long *nGroupCnt)
{
    return E_NOTIMPL;
}
//OPM calls this function for each property to obtain a list of strings and cookies if they are available.
//For our textstyle property we would like to display all the textstyles currently available in the database.
//This function is declared on the IPerPropertyBrowsing interface. Our IOPMPropertyExtensionImpl
//class implements this member by reading the values in the OPM property map. (You set this up in your
//head file when you use BEGIN_OPMPROP_MAP, OPMPROP_ENTRY, END_OPMPROP_MAP macros.)
//Since we need a dynamic list of entries in this drop down list and a static map cannot implement this, 
//we need to override this function a provide dynamic list of text styles to OPM.
STDMETHODIMP CComPolygon::GetPredefinedStrings(DISPID dispID, CALPOLESTR *pCaStringsOut, CADWORD *pCaCookiesOut)
{
    if (dispID != DISPID_TEXTSTYLENAME)
        return  IOPMPropertyExtensionImpl<CComPolygon>::GetPredefinedStrings(dispID,pCaStringsOut,pCaCookiesOut);
    AcDbTextStyleTable* pTT;
    
    AcDbDatabase *pDb = m_objRef.objectId().database();
    if (NULL == pDb)
        pDb = acdbHostApplicationServices()->workingDatabase();
    
    if (pDb->getTextStyleTable(pTT,AcDb::kForRead)==Acad::eOk)
    {
        AcDbTextStyleTableIterator* pIter;
        if (pTT->newIterator(pIter)==Acad::eOk)
        {
            long size = 0;

            // Clear the array.
            mObjectIdArray.removeAll();

            for (pIter->start();!pIter->done();pIter->step())
                size++;
            pCaStringsOut->pElems = (LPOLESTR *)::CoTaskMemAlloc(sizeof(LPOLESTR) * size);
            pCaCookiesOut->pElems = (DWORD *)::CoTaskMemAlloc(sizeof(DWORD) * size);
            long i=0;
            for (pIter->start();!pIter->done();pIter->step())
            {
                AcDbTextStyleTableRecord* pTTR;
                if (pIter->getRecord(pTTR,AcDb::kForRead)!=Acad::eOk)
                    continue;
                const TCHAR* pName = NULL;
                if (pTTR->getName(pName)==Acad::eOk){
                    //we want to show the name of the textstyle as 
                    //it appears in the database
                    pCaStringsOut->pElems[i] = ::SysAllocString(pName);
                    pCaCookiesOut->pElems[i] = mObjectIdArray.append(pTTR->objectId());
                }
                pTTR->close();
                i++;
            }
            pCaStringsOut->cElems = i;
            pCaCookiesOut->cElems = i;
        }
        if (pIter)
            delete pIter;
        pTT->close();
    }
    return S_OK;
}
//OPM calls this function when the user selects an element from a drop down list. OPM provides
//the cookie that we associated with the element in the GetPredefinedStrings function. We are
//responsible for mapping this cookie back to a value that the properties corresponding put_ function
//can understand. 
//In this particular case all we need to do is to provide the name of the text style as
//the put_TextStyle method needs that.
STDMETHODIMP CComPolygon::GetPredefinedValue(DISPID dispID, DWORD dwCookie, VARIANT *pVarOut)
{
    if (dispID != DISPID_TEXTSTYLENAME)
        return  IOPMPropertyExtensionImpl<CComPolygon>::GetPredefinedValue(dispID,dwCookie, pVarOut);

    assert((INT_PTR)dwCookie >= 0);
    assert((INT_PTR)dwCookie < mObjectIdArray.length());
    AcDbObjectId id = mObjectIdArray[dwCookie];
    assert(!id.isNull());

    AcDbTextStyleTableRecord* pTTR;
    HRESULT hr = S_OK;
    if (acdbOpenObject(pTTR,id,AcDb::kForRead)!=Acad::eOk)
        return E_FAIL;
    const TCHAR* pName = NULL;
    if (pTTR->getName(pName)==Acad::eOk)
        ::VariantCopy(pVarOut,&CComVariant(pName));
    else
        hr = E_FAIL;
    pTTR->close();
    return hr;
}

HRESULT CComPolygon::CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName)
{
    try 
    {
        HRESULT hr;
        
        if (FAILED(hr = CreateObject(ownerId, keyName)))
            throw hr;
        if (FAILED(hr = AddToDb(objId, ownerId, keyName)))
            throw hr;
    }
    catch(HRESULT hr)
    {
        //we can become more sophisticated 
        return hr;
    }

    return S_OK;
}

// IAcadBaseObject2Impl
STDMETHODIMP CComPolygon::ForceDbResident(VARIANT_BOOL *forceDbResident)
{
        if (NULL == forceDbResident)
            return E_POINTER;
        
        *forceDbResident = ACAX_VARIANT_FALSE;
        return S_OK;
}

STDMETHODIMP CComPolygon::CreateObject(AcDbObjectId ownerId, TCHAR *keyName) 
{
        try 
        {
            Acad::ErrorStatus es;
            AcDbObjectPointer<AsdkPoly> pPoly;
            if((es = pPoly.create()) != Acad::eOk)
                throw es;

            pPoly->setDatabaseDefaults(ownerId.database());
            AsdkPoly *pTmp = NULL;
            pPoly.release(pTmp);
            
            SetObject((AcDbObject*&)pTmp);
        }
        catch(const Acad::ErrorStatus)
        {
            return Error(L"Failed to create polygon",IID_IComPolygon,E_FAIL);
        }
        
        return S_OK;
}

STDMETHODIMP CComPolygon::AddToDb(AcDbObjectId& objId, AcDbObjectId ownerId, TCHAR* keyName)
{
    try 
    {
        AXEntityDocLock(ownerId);

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef, AcDb::kForRead);

        AcDbBlockTableRecordPointer pBlockTableRecord(ownerId, AcDb::kForWrite);
        if((es = pBlockTableRecord.openStatus()) != Acad::eOk)
            throw es;

        if((es = pBlockTableRecord->appendAcDbEntity(objId, pPoly.object())) != Acad::eOk)
            throw es;

    }
    catch(const Acad::ErrorStatus)
    {
        //we can becaome more sophisticated 
        return Error(L"Failed to add polygon to database",IID_IComPolygon,E_FAIL);
    }

    return SetObjectId(objId);
}

STDMETHODIMP CComPolygon::get_TextString(BSTR * pVal)
{
    CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        *pVal = SysAllocString(pPoly->name());
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IComPolygon,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CComPolygon::put_TextString(BSTR newVal)
{
    try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        if ((es=pPoly->setName(newVal))!=Acad::eOk)
            throw es;
        else 
            Fire_Notification(DISPID_TEXTSTRING);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set name.",IID_IComPolygon,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CComPolygon::get_NumSides(long * pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        *pVal = pPoly->numSides();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IComPolygon,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CComPolygon::put_NumSides(long newVal)
{
    try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        if ((es=pPoly->setNumSides(newVal))!=Acad::eOk)
            throw es;
        else 
            Fire_Notification(DISPID_NUMSIDES);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set sides.",IID_IComPolygon,E_FAIL);
    }
	return S_OK;

}

STDMETHODIMP CComPolygon::get_Normal(VARIANT * pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint3d pt = pPoly->normal();
        pt.setVariant(pVal);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }
	return S_OK;
}

STDMETHODIMP CComPolygon::put_Normal(VARIANT newVal)
{
    try
    {
        AcAxPoint3d pt = newVal;
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        if ((es=pPoly->setNormal(pt.asVector()))!=Acad::eOk)
            throw es;
        else
            Fire_Notification(DISPID_NORMAL);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set normal.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }
	return S_OK;

}

STDMETHODIMP CComPolygon::get_Center(VARIANT * pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint2d pt = pPoly->center();
        pt.setVariant(pVal);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }
	return S_OK;

}

STDMETHODIMP CComPolygon::put_Center(VARIANT newVal)
{
    try
    {
        AcAxPoint3d pt = newVal;
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        if ((es=pPoly->setCenter(AcGePoint2d(pt.x,pt.y)))!=Acad::eOk)
            throw es;
        else
            Fire_Notification(DISPID_CENTER);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set Center.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }
	return S_OK;
}

STDMETHODIMP CComPolygon::get_StartPoint(VARIANT * pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint2d pt = pPoly->startPoint();
        pt.setVariant(pVal);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }
	return S_OK;
}

STDMETHODIMP CComPolygon::put_StartPoint(VARIANT newVal)
{
    try
    {
        AcAxPoint3d pt = newVal;
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        if ((es=pPoly->setStartPoint(AcGePoint2d(pt.x,pt.y)))!=Acad::eOk)
            throw es;
        else
            Fire_Notification(DISPID_STARTPOINT);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set StartPoint.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }
	return S_OK;
}

STDMETHODIMP CComPolygon::get_TextStyleName(BSTR * pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        AcDbTextStyleTableRecordPointer pTextStyleRecord(pPoly->styleId(),AcDb::kForRead);
        if((es=pTextStyleRecord.openStatus()) != Acad::eOk)
            throw es;
        const TCHAR* pName;
        if ((es=pTextStyleRecord->getName(pName))!=Acad::eOk)
            throw es;

        *pVal = ::SysAllocString(pName);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }
	return S_OK;
}

STDMETHODIMP CComPolygon::put_TextStyleName(BSTR newVal)
{
	try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;

        AcDbDatabase* pDb = m_objRef.objectId().database();
        if (NULL == pDb)
            pDb = acdbHostApplicationServices()->workingDatabase();
        
        AcDbTextStyleTableRecordPointer pTextStyleRecord(newVal,pDb,AcDb::kForRead);
        if((es=pTextStyleRecord.openStatus()) != Acad::eOk)
            throw es;

        if ((es=pPoly->setTextStyle(pTextStyleRecord->objectId()))!=Acad::eOk)
            throw es;
        else
            Fire_Notification(DISPID_TEXTSTYLENAME);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set TextStyleName.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }
	return S_OK;
}

STDMETHODIMP CComPolygon::GetVertices(VARIANT* coordinates)
{
	try
    {
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef, AcDb::kForRead);
		Acad::ErrorStatus es;
        if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;

        // get all the vertices
        AcAxPoint3dArray pts;
        if ((es = pPoly->getVertices3d(pts))!=Acad::eOk)
			throw es;
        pts.setVariant(coordinates);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to get Vertices.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }

	return S_OK;
}

STDMETHODIMP CComPolygon::get_Elevation(double *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        *pVal = pPoly->elevation();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }
	return S_OK;
}

STDMETHODIMP CComPolygon::put_Elevation(double newVal)
{
    try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkPoly> pPoly(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;

        pPoly->setElevation(newVal);
        Fire_Notification(DISPID_ELEVATION);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set TextStyleName.",IID_IComPolygon,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IComPolygon,hr);
    }
	return S_OK;
}
