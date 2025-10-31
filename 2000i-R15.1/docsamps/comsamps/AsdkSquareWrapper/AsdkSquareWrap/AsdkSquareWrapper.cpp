// (C) Copyright 1999 by Autodesk, Inc. 
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

// AsdkSquareWrapper.cpp : Implementation of CAsdkSquareWrapper
#include "stdafx.h"
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

    AcDbObjectPointer<AsdkSquare> pSq(m_objId, AcDb::kForRead);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    if (dispID == 0x03) {
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
    AcAxDocLock docLock(m_objId, AcAxDocLock::kNormal);
    if(docLock.lockStatus() != Acad::eOk)
        return E_ACCESSDENIED;
    AcDbObjectPointer<AsdkSquare> pSq(m_objId, AcDb::kForRead);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    if (dispID == 0x03) {
        AcGePoint3d acgePt;
        pSq->squareCenter(acgePt);
        AcAxPoint3d acaxPt(acgePt);
        
        acaxPt[dwCookie] = V_R8(&VarIn);
        pSq->upgradeOpen();
        pSq->setSquareCenter(acaxPt);
    }

    return S_OK;
}

STDMETHODIMP CAsdkSquareWrapper::GetElementStrings( 
    /* [in] */ DISPID dispID,
    /* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
    /* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut)
{

    if (dispID == 0x03)
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

HRESULT CAsdkSquareWrapper::CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName)
{
    try 
    {
        AcAxDocLock docLock(ownerId, AcAxDocLock::kNormal);
        if(docLock.lockStatus() != Acad::eOk)
            return E_ACCESSDENIED;

        Acad::ErrorStatus es;
        AcDbObjectPointer<AsdkSquare> pSq;
        if((es = pSq.create()) != Acad::eOk)
            throw es;

        AcDbDatabase* pDb = ownerId.database();
        pSq->setDatabaseDefaults(pDb);

        AcDbBlockTableRecordPointer pBlockTableRecord(ownerId, AcDb::kForWrite);
        if((es = pBlockTableRecord.openStatus()) != Acad::eOk)
            throw es;

        if((es = pBlockTableRecord->appendAcDbEntity(objId, pSq.object())) != Acad::eOk)
            throw es;
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to create square",IID_IAsdkSquareWrapper, E_FAIL);
    }

    return S_OK;

}

STDMETHODIMP CAsdkSquareWrapper::get_Number(short *pVal)
{
    // TODO: Add your implementation code here

    AcDbObjectPointer<AsdkSquare> pSq(m_objId, AcDb::kForRead);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    int id;
    pSq->squareId(id);
    *pVal = id;

    return S_OK;
}

STDMETHODIMP CAsdkSquareWrapper::put_Number(short newVal)
{
    AcAxDocLock docLock(m_objId, AcAxDocLock::kNormal);
    if(docLock.lockStatus() != Acad::eOk)
        return E_ACCESSDENIED;
    AcDbObjectPointer<AsdkSquare> pSq(m_objId, AcDb::kForWrite);
    if (pSq.openStatus() != Acad::eOk)
        return E_ACCESSDENIED;          

    pSq->setSquareId(newVal);

    return S_OK;
}

STDMETHODIMP CAsdkSquareWrapper::get_SquareSize(double *pVal)
{
    // TODO: Add your implementation code here
    AcDbObjectPointer<AsdkSquare> pSq(m_objId, AcDb::kForRead);
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
    AcAxDocLock docLock(m_objId, AcAxDocLock::kNormal);
    if(docLock.lockStatus() != Acad::eOk)
        return E_ACCESSDENIED;
    AcDbObjectPointer<AsdkSquare> pSq(m_objId, AcDb::kForWrite);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    pSq->setSquareSideLength(newVal);

    return S_OK;
}


STDMETHODIMP CAsdkSquareWrapper::get_CenterPoint(VARIANT *pVal)
{
    // TODO: Add your implementation code here
    AcDbObjectPointer<AsdkSquare> pSq(m_objId, AcDb::kForRead);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          

    AcAxPoint3d pt;
    pSq->squareCenter(pt);
    
    pt.setVariant(pVal);
    
    return S_OK;
}

STDMETHODIMP CAsdkSquareWrapper::put_CenterPoint(VARIANT newVal)
{
    AcAxDocLock docLock(m_objId, AcAxDocLock::kNormal);
    if(docLock.lockStatus() != Acad::eOk)
        return E_ACCESSDENIED;

    AcAxPoint3d pt = newVal;

    AcDbObjectPointer<AsdkSquare> pSq(m_objId, AcDb::kForWrite, Adesk::kTrue);
    if (pSq.openStatus() != Acad::eOk)
            return E_ACCESSDENIED;          
        
    pSq->setSquareCenter(pt);

    return S_OK;
}
