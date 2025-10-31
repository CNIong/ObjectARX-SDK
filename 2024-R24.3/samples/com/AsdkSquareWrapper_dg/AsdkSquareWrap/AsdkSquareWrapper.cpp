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

// AsdkSquareWrapper.cpp : Implementation of CAsdkSquareWrapper
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "AsdkSquareLib.h"
#include "AsdkSquareWrapper.h"

#include "axpnt3d.h"
#include "axlock.h"


/////////////////////////////////////////////////////////////////////////////
// CAsdkSquareWrapper

STDMETHODIMP CAsdkSquareWrapper::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IAsdkSquareWrapper
    };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

STDMETHODIMP CAsdkSquareWrapper::GetElementValue(
    /* [in] */ DISPID dispID,
    /* [in] */ DWORD dwCookie,
    /* [out] */ VARIANT * pVarOut)
{
    if (pVarOut == NULL)
        return E_POINTER;

    AcAxObjectRefPtr<AsdkSquare> pSq(&m_objRef, AcDb::kForRead);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    if (dispID == DISPID_CENTERPOINT) {
        AcGePoint3d acgePt;
        pSq->squareCenter(acgePt);
        AcAxPoint3d acaxPt(acgePt);

        ::VariantCopy(pVarOut,&CComVariant(acaxPt[dwCookie]));
    }

    return S_OK;
}

STDMETHODIMP CAsdkSquareWrapper::SetElementValue(
    /* [in] */ DISPID dispID,
    /* [in] */ DWORD dwCookie,
    /* [in] */ VARIANT VarIn)
{
    AcAxDocLock docLock(m_objRef.objectId(), AcAxDocLock::kNormal);
    if(docLock.lockStatus() != Acad::eOk && docLock.lockStatus() != Acad::eNoDatabase)
        return E_ACCESSDENIED;
    AcAxObjectRefPtr<AsdkSquare> pSq(&m_objRef, AcDb::kForRead);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    if (dispID == DISPID_CENTERPOINT) {
        AcGePoint3d acgePt;
        pSq->squareCenter(acgePt);
        AcAxPoint3d acaxPt(acgePt);
        
        acaxPt[dwCookie] = V_R8(&VarIn);
        pSq->upgradeOpen();
        pSq->setSquareCenter(acaxPt);
        Fire_Notification(DISPID_CENTERPOINT);
    }

    return S_OK;
}

STDMETHODIMP CAsdkSquareWrapper::GetElementStrings( 
    /* [in] */ DISPID dispID,
    /* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
    /* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut)
{

    if (dispID == DISPID_CENTERPOINT)
    {
        long size;
        size = 3;
        pCaStringsOut->pElems = (LPOLESTR *)::CoTaskMemAlloc(sizeof(LPOLESTR) * size);
        pCaCookiesOut->pElems = (DWORD *)::CoTaskMemAlloc(sizeof(DWORD) * size);
        for (long i=0;i<size;i++)
            pCaCookiesOut->pElems[i] = i;
        
        pCaStringsOut->cElems = size;
        pCaCookiesOut->cElems = size;

        pCaStringsOut->pElems[0] = ::SysAllocString(L"Center X");
        pCaStringsOut->pElems[1] = ::SysAllocString(L"Center Y");
        pCaStringsOut->pElems[2] = ::SysAllocString(L"Center Z");
    }
    return S_OK;

}

STDMETHODIMP CAsdkSquareWrapper::GetElementGrouping(
    /* [in] */ DISPID dispID,
    /* [out] */ short *groupingNumber)
{
    return E_NOTIMPL;
}

STDMETHODIMP CAsdkSquareWrapper::GetGroupCount(
    /* [in] */ DISPID dispID,
    /* [out] */ long *nGroupCnt)
{
    return E_NOTIMPL;
}

STDMETHODIMP CAsdkSquareWrapper::GetPredefinedStrings(
    DISPID dispID, CALPOLESTR *pCaStringsOut, CADWORD *pCaCookiesOut)
{

    return E_NOTIMPL;

}

STDMETHODIMP CAsdkSquareWrapper::GetPredefinedValue(
    DISPID dispID, DWORD dwCookie, VARIANT *pVarOut)
{

    return E_NOTIMPL;

}

// IAcadBaseObjectImpl
HRESULT CAsdkSquareWrapper::CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName)
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
        return hr;
    }

    return S_OK;
}

// IAcadBaseObject2Impl
HRESULT CAsdkSquareWrapper::ForceDbResident(VARIANT_BOOL *forceDbResident) 
{
    if (NULL == forceDbResident)
        return E_POINTER;
    
    *forceDbResident = ACAX_VARIANT_FALSE;
    return S_OK;
}

HRESULT CAsdkSquareWrapper::AddToDb(AcDbObjectId& objId, AcDbObjectId ownerId, TCHAR* keyName)
{
    try 
    {
        AcAxDocLock docLock(ownerId);

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<AsdkSquare> pSq(&m_objRef, AcDb::kForRead);

        AcDbBlockTableRecordPointer pBlockTableRecord(ownerId, AcDb::kForWrite);
        if((es = pBlockTableRecord.openStatus()) != Acad::eOk)
            throw es;

        if((es = pBlockTableRecord->appendAcDbEntity(objId, pSq.object())) != Acad::eOk)
            throw es;
    }
    catch(const Acad::ErrorStatus)
    {
        //we can becaome more sophisticated 
        return Error(L"Failed to add square to database", IID_IAsdkSquareWrapper ,E_FAIL);
    }

    return SetObjectId(objId);
}

HRESULT CAsdkSquareWrapper::CreateObject(AcDbObjectId ownerId, TCHAR *keyName) 
{
    try 
    {
        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSquare> pSq;
        if((es = pSq.create()) != Acad::eOk)
            throw es;

        pSq->setDatabaseDefaults(ownerId.database());

        AsdkSquare *pTmp = NULL;
        pSq.release(pTmp);

        SetObject((AcDbObject*&)pTmp);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to create square",IID_IAsdkSquareWrapper, E_FAIL);
    }

    return S_OK;
}

// IAsdkSquareWrapper
STDMETHODIMP CAsdkSquareWrapper::get_Number(short *pVal)
{
    // TODO: Add your implementation code here

    AcAxObjectRefPtr<AsdkSquare> pSq(&m_objRef, AcDb::kForRead);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    int id;
    pSq->squareId(id);
    *pVal = id;

    return S_OK;
}

STDMETHODIMP CAsdkSquareWrapper::put_Number(short newVal)
{
    AcAxDocLock docLock(m_objRef.objectId(), AcAxDocLock::kNormal);
    if(docLock.lockStatus() != Acad::eOk && docLock.lockStatus() != Acad::eNoDatabase)
        return E_ACCESSDENIED;
    AcAxObjectRefPtr<AsdkSquare> pSq(&m_objRef, AcDb::kForWrite);
    if (pSq.openStatus() != Acad::eOk)
        return E_ACCESSDENIED;          

    pSq->setSquareId(newVal);
    Fire_Notification(DISPID_NUMBER);

    return S_OK;
}

STDMETHODIMP CAsdkSquareWrapper::get_SquareSize(double *pVal)
{
    // TODO: Add your implementation code here
    AcAxObjectRefPtr<AsdkSquare> pSq(&m_objRef, AcDb::kForRead);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    double size;
    pSq->squareSideLength(size);
    *pVal = size;

    return S_OK;
}

STDMETHODIMP CAsdkSquareWrapper::put_SquareSize(double newVal)
{
    // TODO: Add your implementation code here
    AcAxDocLock docLock(m_objRef.objectId(), AcAxDocLock::kNormal);
    if(docLock.lockStatus() != Acad::eOk && docLock.lockStatus() != Acad::eNoDatabase)
        return E_ACCESSDENIED;
    AcAxObjectRefPtr<AsdkSquare> pSq(&m_objRef, AcDb::kForWrite);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    pSq->setSquareSideLength(newVal);
    Fire_Notification(DISPID_SQUARESIZE);

    return S_OK;
}


STDMETHODIMP CAsdkSquareWrapper::get_CenterPoint(VARIANT *pVal)
{
    // TODO: Add your implementation code here
    AcAxObjectRefPtr<AsdkSquare> pSq(&m_objRef, AcDb::kForRead);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    AcAxPoint3d pt;
    pSq->squareCenter(pt);
    
    pt.setVariant(pVal);
    
    return S_OK;
}

STDMETHODIMP CAsdkSquareWrapper::put_CenterPoint(VARIANT newVal)
{
    AcAxDocLock docLock(m_objRef.objectId(), AcAxDocLock::kNormal);
    if(docLock.lockStatus() != Acad::eOk && docLock.lockStatus() != Acad::eNoDatabase)
        return E_ACCESSDENIED;

    AcAxPoint3d pt = newVal;

    AcAxObjectRefPtr<AsdkSquare> pSq(&m_objRef, AcDb::kForWrite, Adesk::kTrue);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          
        
    pSq->setSquareCenter(pt);
    Fire_Notification(DISPID_CENTERPOINT);

    return S_OK;
}
