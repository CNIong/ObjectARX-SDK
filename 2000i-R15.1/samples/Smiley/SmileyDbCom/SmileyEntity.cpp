//
// (C) Copyright 2000 by Autodesk, Inc. 
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

// SmileyEntity.cpp : Implementation of CSmileyEntity

#include "stdafx.h"
#include "SmileyDbCom.h"
#include "SmileyEntity.h"
#include "SmileyCats.h"
#include "axpnt3d.h"
#include "dbproxy.h"
#include "dbxutil.h"
#include "geassign.h"

#define AXEntityDocLock(objId)                              \
    AcAxDocLock docLock(objId, AcAxDocLock::kNormal);       \
    if(docLock.lockStatus() != Acad::eOk)                   \
        throw docLock.lockStatus();
/////////////////////////////////////////////////////////////////////////////
// CSmileyEntity
#define CHECKOUTPARAM(x) if (x==NULL) return E_POINTER;

ACRX_DEFINE_MEMBERS( AsdkSmiley );

STDMETHODIMP CSmileyEntity::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISmileyEntity,
        &IID_IAcadObject,
        &IID_IAcadEntity,
        &IID_IOPMPropertyExpander,
        &IID_ICategorizeProperties,
        //&IID_IPerPropertyBrowsing,
        &IID_IOPMPropertyExtension
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CSmileyEntity::CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName)
{
    try 
    {
        AXEntityDocLock(ownerId);
        Acad::ErrorStatus es;
        AsdkSmiley *pSmiley = (AsdkSmiley*)AsdkSmiley::desc()->create();
        if ( NULL == pSmiley )
            throw Acad::eOutOfMemory;
        AcDbDatabase* pDb = ownerId.database();
        pSmiley->setDatabaseDefaults(pDb);
        AcDbBlockTableRecordPointer pBlockTableRecord(ownerId, AcDb::kForWrite);
        if((es = pBlockTableRecord.openStatus()) != Acad::eOk)
		{
			delete pSmiley;
            throw es;
		}
        if((es = pBlockTableRecord->appendAcDbEntity(objId, pSmiley)) != Acad::eOk)
		{
			delete pSmiley;
            throw es;
		}
		pSmiley->close();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to create Smiley through entity interface.",IID_ISmileyEntity,E_FAIL);
    }
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// CSmileyEntity methods
//
STDMETHODIMP CSmileyEntity::get_Radius(double FAR* d)
{
    CHECKOUTPARAM(d);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        *d = pSmiley->radius();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::put_Radius(double d)
{
    try
    {
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        pSmiley->setRadius(d);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::get_Center(VARIANT* pv)
{
	CHECKOUTPARAM(pv);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint3d pt = pSmiley->center();
        pt.setVariant(pv);
    }
	    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::put_Center(VARIANT var)
{
    try
    {
        AcAxPoint3d pt = var;
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        pSmiley->setCenter(pt);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::get_Normal(VARIANT* pv)
{
	CHECKOUTPARAM(pv);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint3d pt = pSmiley->normal();
        pt.setVariant(pv);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::put_Normal(VARIANT var)
{
    try
    {
        AcAxPoint3d pt = var;
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        pSmiley->setNormal( pt.asVector() );
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::get_EyesSize(double FAR* d)
{
    CHECKOUTPARAM(d);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        *d = pSmiley->eyeSize();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::put_EyesSize(double d)
{
    try
    {
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        pSmiley->setEyeSize(d);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::get_EyesHeight(double FAR* d)
{
    CHECKOUTPARAM(d);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        *d = pSmiley->eyesHeight();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::put_EyesHeight(double d)
{
    try
    {
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        pSmiley->setEyesHeight(d);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::get_EyesApart(double FAR* d)
{
    CHECKOUTPARAM(d);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        *d = pSmiley->eyesApart();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::put_EyesApart(double d)
{
    try
    {
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        pSmiley->setEyesApart(d);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::get_MouthCenter(VARIANT* d)
{
	CHECKOUTPARAM(d);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint3d pt = pSmiley->mouthCenter();
        pt.setVariant(d);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::get_MouthLeft(VARIANT* pv)
{
	CHECKOUTPARAM(pv);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint3d pt = pSmiley->mouthLeft();
        pt.setVariant(pv);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::put_MouthLeft(VARIANT var)
{
    try
    {
        AcAxPoint3d pt = var;
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        pSmiley->setMouthLeft(pt);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::get_MouthBottom(VARIANT* pv)
{
	CHECKOUTPARAM(pv);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint3d pt = pSmiley->mouthBottom();
        pt.setVariant(pv);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::put_MouthBottom(VARIANT var)
{
    try
    {
        AcAxPoint3d pt = var;
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        pSmiley->setMouthBottom(pt);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::get_MouthRight(VARIANT* pv)
{
	CHECKOUTPARAM(pv);
    try
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint3d pt = pSmiley->mouthRight();
        pt.setVariant(pv);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::put_MouthRight(VARIANT var)
{
    try
    {
        AcAxPoint3d pt = var;
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        pSmiley->setMouthRight(pt);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
    }
	return S_OK;
}

STDMETHODIMP CSmileyEntity::ScaleRadius(double r)
{
    try 
    {
        AXEntityDocLock(m_objId);

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pSmiley.openStatus()) != Acad::eOk)
            throw es;
        
        pSmiley->scaleRadius(r);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_ISmileyEntity,E_FAIL);
    }
	return S_OK;
}


// IOPMPropertyExpander
// This is used to get the value for an element in a group.
// The element is identified by the dwCookie parameter
STDMETHODIMP CSmileyEntity::GetElementValue(
	/* [in] */ DISPID dispID,
	/* [in] */ DWORD dwCookie,
	/* [out] */ VARIANT * pVarOut)
{
    CHECKOUTPARAM(pVarOut);
    if ( 0x02 == dispID || 0x03 == dispID || ( dispID >= 0x07 && dispID <= 0x0A ))
    {
        try
        {
            if( dwCookie > 2 )
                throw Acad::eInvalidInput;
            Acad::ErrorStatus es;
            AcDbObjectPointer<AsdkSmiley> pSmiley(m_objId,AcDb::kForRead,Adesk::kTrue);
	        if(( es = pSmiley.openStatus()) != Acad::eOk)
                throw es;

            AcAxPoint3d pt;
			switch( dispID )
            {
			    case 0x02:
					pt = pSmiley->center();
					break;
			    case 0x03:
				    pt = pSmiley->normal();
					break;
			    case 0x07:
				    pt = pSmiley->mouthCenter();
					break;
			    case 0x08:
				    pt = pSmiley->mouthLeft();
					break;
			    case 0x09:
				    pt = pSmiley->mouthBottom();
					break;
			    case 0x0A:
				    pt = pSmiley->mouthRight();
					break;
			    default:
				    throw Acad::eInvalidInput;
			}
			acdbWcs2Ucs( asDblArray( pt ), asDblArray( pt ), Adesk::kTrue );
			::VariantCopy( pVarOut,&CComVariant( pt[dwCookie] ));
        }
        catch( const Acad::ErrorStatus )
        {
            return Error( L"Failed to open object", IID_ISmileyEntity, E_FAIL );
        }
        catch( const HRESULT hr )
        {
            return Error( L"Invalid argument.", IID_ISmileyEntity, hr );
        }
    }
	return S_OK;
}

// IOPMPropertyExpander
// This is used to set the value for an element in a group.
// The element is identified by the dwCookie parameter
STDMETHODIMP CSmileyEntity::SetElementValue(
	/* [in] */ DISPID dispID,
	/* [in] */ DWORD dwCookie,
	/* [in] */ VARIANT VarIn)
{
    if ( 0x02 == dispID || 0x03 == dispID || ( dispID >= 0x08 && dispID <= 0x0A ))
    {
        try
        {
            if ( dwCookie > 2 )
                throw Acad::eInvalidInput;
            Acad::ErrorStatus es;
            AcDbObjectPointer<AsdkSmiley> pSmiley( m_objId, AcDb::kForWrite, Adesk::kTrue );
	        if(( es = pSmiley.openStatus()) != Acad::eOk )
                throw es;

            AcAxPoint3d pt;
			switch( dispID )
            {
			    case 0x02:
					pt = pSmiley->center();
					break;
			    case 0x03:
				    pt = pSmiley->normal();
					break;
			    case 0x08:
				    pt = pSmiley->mouthLeft();
					break;
			    case 0x09:
				    pt = pSmiley->mouthBottom();
					break;
			    case 0x0A:
				    pt = pSmiley->mouthRight();
					break;
			    default:
				    throw Acad::eInvalidInput;
			}
            //translate from wcs to ucs
            acdbEcs2Ucs(asDblArray(pt),asDblArray(pt),asDblArray(pSmiley->normal()),Adesk::kTrue);

			pt[dwCookie] = V_R8(&VarIn);

            acdbUcs2Wcs(asDblArray(pt),asDblArray(pt),Adesk::kTrue);

			switch ( dispID )
            {
			    case 0x02:
					pSmiley->setCenter( pt );
					break;
			    case 0x03:
				    pSmiley->setNormal( pt.asVector() );
					break;
			    case 0x08:
				    pSmiley->setMouthLeft( pt );
					break;
			    case 0x09:
				    pSmiley->setMouthBottom( pt );
					break;
			    case 0x0A:
				    pSmiley->setMouthRight( pt );
					break;
			}
        }
        catch(const Acad::ErrorStatus)
        {
            return Error(L"Failed to open object",IID_ISmileyEntity,E_FAIL);
        }
        catch(const HRESULT hr)
        {
            return Error(L"Invalid argument.",IID_ISmileyEntity,hr);
        }

    }
	return S_OK;
}

// IOPMPropertyExpander
// This is called to get the display string for each element in a group.
// We return strings for each coordinate for this object
STDMETHODIMP CSmileyEntity::GetElementStrings( 
	/* [in] */ DISPID dispID,
	/* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
	/* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut)
{
    if ( 0x02 == dispID || 0x03 == dispID || ( dispID >= 0x07 && dispID <= 0x0A ))
    {
        long size = 3;
        pCaStringsOut->pElems = (LPOLESTR *)::CoTaskMemAlloc(sizeof(LPOLESTR) * size);
        pCaCookiesOut->pElems = (DWORD *)::CoTaskMemAlloc(sizeof(DWORD) * size);
        for ( long i=0; i<size; i++)
            pCaCookiesOut->pElems[i] = i;
        pCaStringsOut->cElems = size;
        pCaCookiesOut->cElems = size;

		switch ( dispID )
        {
			case 0x02:
				pCaStringsOut->pElems[0] = ::SysAllocString(L"Center X");
				pCaStringsOut->pElems[1] = ::SysAllocString(L"Center Y");
				pCaStringsOut->pElems[2] = ::SysAllocString(L"Center Z");
				break;
			case 0x03:
				pCaStringsOut->pElems[0] = ::SysAllocString(L"Normal X");
				pCaStringsOut->pElems[1] = ::SysAllocString(L"Normal Y");
				pCaStringsOut->pElems[2] = ::SysAllocString(L"Normal Z");
				break;
			case 0x07:
				pCaStringsOut->pElems[0] = ::SysAllocString(L"MouthCenter X");
				pCaStringsOut->pElems[1] = ::SysAllocString(L"MouthCenter Y");
				pCaStringsOut->pElems[2] = ::SysAllocString(L"MouthCenter Z");
				break;
			case 0x08:
				pCaStringsOut->pElems[0] = ::SysAllocString(L"MouthLeft X");
				pCaStringsOut->pElems[1] = ::SysAllocString(L"MouthLeft Y");
				pCaStringsOut->pElems[2] = ::SysAllocString(L"MouthLeft Z");
				break;
			case 0x09:
				pCaStringsOut->pElems[0] = ::SysAllocString(L"MouthBottom X");
				pCaStringsOut->pElems[1] = ::SysAllocString(L"MouthBottom Y");
				pCaStringsOut->pElems[2] = ::SysAllocString(L"MouthBottom Z");
				break;
			case 0x0A:
				pCaStringsOut->pElems[0] = ::SysAllocString(L"MouthRight X");
				pCaStringsOut->pElems[1] = ::SysAllocString(L"MouthRight Y");
				pCaStringsOut->pElems[2] = ::SysAllocString(L"MouthRight Z");
				break;
		}
    }

    return S_OK;
}

// IOPMPropertyExpander
// This function is called to determine the number of elements in a group
// It defaults to the number of elements in the array (3 in this case)
STDMETHODIMP CSmileyEntity::GetElementGrouping(
    /* [in] */ DISPID dispID,
	/* [out] */ short *groupingNumber)
{
    return E_NOTIMPL;
}

// IOPMPropertyExpander
// This function is called to determine how many groups there are in
// the array.
// For example in case of the polyline this is the number of vertices.
// We are not implementing this because it defaults to nGroupCnt = 0
STDMETHODIMP CSmileyEntity::GetGroupCount(
    /* [in] */ DISPID dispID,
	/* [out] */ long *nGroupCnt)
{
    return E_NOTIMPL;
}

// OPM calls this function for each property to obtain a list of strings and cookies if they are available.
// This function is declared on the IPerPropertyBrowsing interface. Our IOPMPropertyExtensionImpl
// class implements this member by reading the values in the OPM property map.
STDMETHODIMP CSmileyEntity::GetPredefinedStrings(DISPID dispID, CALPOLESTR *pCaStringsOut, CADWORD *pCaCookiesOut)
{
	return IOPMPropertyExtensionImpl<CSmileyEntity>::GetPredefinedStrings(dispID,pCaStringsOut,pCaCookiesOut);
}

// OPM calls this function when the user selects an element from a drop down list. OPM provides
// the cookie that we associated with the element in the GetPredefinedStrings function. We are
// responsible for mapping this cookie back to a value that the properties corresponding put_ function
// can understand. 
// In this particular case all we need to do is to provide the name of the text style as
// the put_TextStyle method needs that.
STDMETHODIMP CSmileyEntity::GetPredefinedValue(DISPID dispID, DWORD dwCookie, VARIANT *pVarOut)
{
	return IOPMPropertyExtensionImpl<CSmileyEntity>::GetPredefinedValue(dispID,dwCookie,pVarOut);
}

STDMETHODIMP CSmileyEntity::GetCategoryName(PROPCAT propcat, LCID lcid, BSTR* pbstrName)
{
	switch ( propcat )
	{
	case PROPCAT_Face:
		*pbstrName = ::SysAllocString(L"Face");
		break;
	case PROPCAT_Eyes:
		*pbstrName = ::SysAllocString(L"Eyes");
		break;
	case PROPCAT_Mouth:
		*pbstrName = ::SysAllocString(L"Mouth");
		break;
	default:
		return S_FALSE;
	}
	return S_OK;
}
