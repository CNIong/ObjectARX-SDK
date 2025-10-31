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
// ComPolygon.cpp : Implementation of CComPolygon
#include "stdafx.h"
#include "compoly.h"
#include "ComPolygon.h"
#include "dbsymtb.h"
#include "poly.h"
#include "axpnt3d.h"
#include "axpnt2d.h"
#include "dbxutil.h"

#include "axlock.h"

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
    if (dispID >= 0x03 && dispID <= 0x05)
    {
        try
        {
            if (dwCookie>2)
                throw Acad::eInvalidInput;
            Acad::ErrorStatus es;
            AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForRead,Adesk::kTrue);
	        if((es=pPoly.openStatus()) != Acad::eOk)
                throw es;

            AcAxPoint3d pt;
			Adesk::Boolean bAsVector=Adesk::kFalse;
			if (dispID == 0x03)
            {
                pt = pPoly->normal();
                //translate from wcs to ucs
                acdbWcs2Ucs(asDblArray(pt),asDblArray(pt),Adesk::kTrue);
                ::VariantCopy(pVarOut,&CComVariant(pt[dwCookie]));
            } else {
                AcAxPoint2d pt2d;
			    switch (dispID)
			    {
			    case 0x04:
				    pt2d = pPoly->center();
				    break;
			    case 0x05:
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
    if (dispID >= 0x03 && dispID <= 0x05)
    {
        try
        {
            if (dwCookie>2)
                throw Acad::eInvalidInput;
            Acad::ErrorStatus es;
            AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForWrite,Adesk::kTrue);
	        if((es=pPoly.openStatus()) != Acad::eOk)
                throw es;

            AcAxPoint3d pt;
			AcAxPoint2d pt2d;
			if (dispID == 0x03)
            {
                pt = pPoly->normal();
                //translate from wcs to ucs
                acdbEcs2Ucs(asDblArray(pt),asDblArray(pt),asDblArray(pPoly->normal()),Adesk::kTrue);
            } else {
			    switch (dispID)
			    {
			    case 0x04:
				    pt2d = pPoly->center();
				    break;
			    case 0x05:
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

            if (dispID == 0x03) {
                acdbUcs2Wcs(asDblArray(pt),asDblArray(pt),Adesk::kTrue);
                if ((es=pPoly->setNormal(pt.asVector()))!=Acad::eOk)
                    throw es;    
            }else { 
                acdbUcs2Ecs(asDblArray(pt),asDblArray(pt),asDblArray(pPoly->normal()),Adesk::kFalse);
                pt2d.set(pt.x,pt.y);
                pPoly->setElevation(pt.z);
                if (dispID == 0x04)
                    if ((es=pPoly->setCenter(pt2d))!=Acad::eOk)
                        throw es;            
                if (dispID == 0x05)
                    if ((es=pPoly->setStartPoint(pt2d))!=Acad::eOk)
                        throw es;            
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
//This is called to get the display string for each
//element in a group.
//We return strings for each coordinate for this object
STDMETHODIMP CComPolygon::GetElementStrings( 
	/* [in] */ DISPID dispID,
	/* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
	/* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut)
{
    if (dispID >= 0x03 && dispID <= 0x05)
    {
        long size;
        if (dispID == 0x03){
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
        if (dispID == 0x04 || dispID == 0x05)
        {
            size = 2;
            pCaStringsOut->pElems = (LPOLESTR *)::CoTaskMemAlloc(sizeof(LPOLESTR) * size);
            pCaCookiesOut->pElems = (DWORD *)::CoTaskMemAlloc(sizeof(DWORD) * size);
            for (long i=0;i<size;i++)
                pCaCookiesOut->pElems[i] = i;
            pCaStringsOut->cElems = size;
            pCaCookiesOut->cElems = size;
        }
        if (dispID == 0x04){
            pCaStringsOut->pElems[0] = ::SysAllocString(L"Center X");
            pCaStringsOut->pElems[1] = ::SysAllocString(L"Center Y");
        }
        if (dispID == 0x05){
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
    if (dispID != 0x6)
        return  IOPMPropertyExtensionImpl<CComPolygon>::GetPredefinedStrings(dispID,pCaStringsOut,pCaCookiesOut);
    USES_CONVERSION;
    AcDbTextStyleTable* pTT;
    if (m_objId.database()->getTextStyleTable(pTT,AcDb::kForRead)==Acad::eOk)
    {
        AcDbTextStyleTableIterator* pIter;
        if (pTT->newIterator(pIter)==Acad::eOk)
        {
            long size = 0;
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
                const char* pName = NULL;
                if (pTTR->getName(pName)==Acad::eOk){
                    //we want to show the name of the textstyle as 
                    //it appears in the database
                    pCaStringsOut->pElems[i] = ::SysAllocString(A2W(pName));
                    //and use the object id as the cookie
                    pCaCookiesOut->pElems[i] = pTTR->objectId().asOldId();
                }
                pTTR->close();
                i++;
            }
            pCaStringsOut->cElems = i;
            pCaCookiesOut->cElems = i;
        }
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
    if (dispID != 0x6)
        return  IOPMPropertyExtensionImpl<CComPolygon>::GetPredefinedValue(dispID,dwCookie, pVarOut);
    USES_CONVERSION;
    AcDbObjectId id;
    id.setFromOldId(dwCookie);
    AcDbTextStyleTableRecord* pTTR;
    HRESULT hr = S_OK;
    if (acdbOpenObject(pTTR,id,AcDb::kForRead)!=Acad::eOk)
        return E_FAIL;
    const char* pName = NULL;
    if (pTTR->getName(pName)==Acad::eOk)
        *pVarOut = CComVariant(A2W(pName));
    else
        hr = E_FAIL;
    pTTR->close();
    return hr;
}
HRESULT CComPolygon::CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName)
{
    try 
    {
        AXEntityDocLock(ownerId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkPoly> pPoly;
        if((es = pPoly.create()) != Acad::eOk)
            throw es;

        AcDbDatabase* pDb = ownerId.database();
        pPoly->setDatabaseDefaults(pDb);

        AcDbBlockTableRecordPointer pBlockTableRecord(ownerId, AcDb::kForWrite);
        if((es = pBlockTableRecord.openStatus()) != Acad::eOk)
            throw es;

        if((es = pBlockTableRecord->appendAcDbEntity(objId, pPoly.object())) != Acad::eOk)
            throw es;
    }
    catch(const Acad::ErrorStatus)
    {
        //we can becaome more sophisticated 
        return Error(L"Failed to create polygon",IID_IComPolygon,E_FAIL);
    }

    return S_OK;
}

STDMETHODIMP CComPolygon::get_TextString(BSTR * pVal)
{
    CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        USES_CONVERSION;
        *pVal = SysAllocString(A2W(pPoly->name()));
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
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        USES_CONVERSION;
        if ((es=pPoly->setName(W2A(newVal)))!=Acad::eOk)
            throw es;
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
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForRead,Adesk::kTrue);
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
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        if ((es=pPoly->setNumSides(newVal))!=Acad::eOk)
            throw es;
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
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForRead,Adesk::kTrue);
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
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        if ((es=pPoly->setNormal(pt.asVector()))!=Acad::eOk)
            throw es;
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
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForRead,Adesk::kTrue);
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
        AcAxPoint2d pt = newVal;
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        if ((es=pPoly->setCenter(pt))!=Acad::eOk)
            throw es;
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
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForRead,Adesk::kTrue);
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
        AcAxPoint2d pt = newVal;
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        
        if ((es=pPoly->setStartPoint(pt))!=Acad::eOk)
            throw es;
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
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;
        AcDbTextStyleTableRecordPointer pTextStyleRecord(pPoly->styleId(),AcDb::kForRead);
        if((es=pTextStyleRecord.openStatus()) != Acad::eOk)
            throw es;
        const char* pName;
        if ((es=pTextStyleRecord->getName(pName))!=Acad::eOk)
            throw es;

        USES_CONVERSION;
        *pVal = ::SysAllocString(A2W(pName));
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
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;

        USES_CONVERSION;
        AcDbTextStyleTableRecordPointer pTextStyleRecord(W2A(newVal),m_objId.database(),AcDb::kForRead);
        if((es=pTextStyleRecord.openStatus()) != Acad::eOk)
            throw es;

        if ((es=pPoly->setTextStyle(pTextStyleRecord->objectId()))!=Acad::eOk)
            throw es;
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
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId, AcDb::kForRead);
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
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForRead,Adesk::kTrue);
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
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkPoly> pPoly(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pPoly.openStatus()) != Acad::eOk)
            throw es;

        pPoly->setElevation(newVal);
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
