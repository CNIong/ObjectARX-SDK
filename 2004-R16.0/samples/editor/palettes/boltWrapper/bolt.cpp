//
//
// (C) Copyright 2002 by Autodesk, Inc. 
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
// Bolt.cpp : Implementation of CBolt
#include "stdafx.h"
#include "stdarx.h"
#include "BoltWrapper.h"
#include "Bolt.h"
#include "axpnt3d.h"


#define AXEntityDocLockNoDbOk(objId)                        \
    AcAxDocLock docLock(objId, AcAxDocLock::kNormal);       \
    if (docLock.lockStatus() != Acad::ErrorStatus::eNoDatabase && \
        docLock.lockStatus() != Acad::eOk)                  \
        throw docLock.lockStatus();



#define AXEntityDocLock(objId)                              \
    AcAxDocLock docLock(objId, AcAxDocLock::kNormal);       \
    if(docLock.lockStatus() != Acad::eOk)                   \
        throw docLock.lockStatus();

#define CHECKOUTPARAM(x) if (x==NULL) return E_POINTER;
/////////////////////////////////////////////////////////////////////////////
// CBolt

STDMETHODIMP CBolt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBolt
        
        ,&IID_IAcadEntity
        
        
        ,&IID_IOPMPropertyExpander
        
        
        ,&IID_ICategorizeProperties
        ,&IID_IOPMPropertyExtension
        
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CBolt::CreateNewObject(AcDbObjectId& objId, AcDbObjectId& ownerId, TCHAR* keyName)
{
    try 
    {
        AXEntityDocLock(ownerId);
        Acad::ErrorStatus es;
        AcDbObjectPointer<asdkBolt> pO;
        if((es = pO.create()) != Acad::eOk)
            throw es;
        AcDbDatabase* pDb = ownerId.database();
        pO->setDatabaseDefaults(pDb);
        AcDbBlockTableRecordPointer pBlockTableRecord(ownerId, AcDb::kForWrite);
        if((es = pBlockTableRecord.openStatus()) != Acad::eOk)
            throw es;
        if((es = pBlockTableRecord->appendAcDbEntity(objId, pO.object())) != Acad::eOk)
            throw es;
    }
    catch(const Acad::ErrorStatus)
    {
        //we can become more sophisticated 
        return Error(L"Failed to create asdkBolt",IID_IBolt,E_FAIL);
    }
    return S_OK;
}

// IAcadBaseObject2Impl
STDMETHODIMP CBolt::ForceDbResident(VARIANT_BOOL *forceDbResident)
{
        if (NULL == forceDbResident)
            return E_POINTER;
        
        *forceDbResident = ACAX_VARIANT_FALSE;
        return S_OK;
}


STDMETHODIMP CBolt::CreateObject(AcDbObjectId ownerId, TCHAR *keyName) 
{
        try 
        {
            Acad::ErrorStatus es;
            AcDbObjectPointer<asdkBolt> pBolt;
            if((es = pBolt.create()) != Acad::eOk)
                throw es;
		
			pBolt->setDatabaseDefaults(ownerId.database());
            asdkBolt *pTmp = NULL;
            pBolt.release(pTmp);
            
            SetObject((AcDbObject*&)pTmp);
        }
        catch(const Acad::ErrorStatus)
        {
            return Error(L"Failed to create Bolt",IID_IBolt,E_FAIL);
        }
        
        return S_OK;
}

STDMETHODIMP CBolt::AddToDb(AcDbObjectId& objId, AcDbObjectId ownerId, TCHAR* keyName)
{
    try 
    {
        AXEntityDocLock(ownerId);

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef, AcDb::kForRead);

        AcDbBlockTableRecordPointer pBlockTableRecord(ownerId, AcDb::kForWrite);
        if((es = pBlockTableRecord.openStatus()) != Acad::eOk)
            throw es;

        if((es = pBlockTableRecord->appendAcDbEntity(objId, pBolt.object())) != Acad::eOk)
            throw es;

    }
    catch(const Acad::ErrorStatus)
    {
        //we can becaome more sophisticated 
        return Error(L"Failed to add Bolt to database",IID_IBolt,E_FAIL);
    }

    return SetObjectId(objId);
}


//IOPMPropertyExpander
STDMETHODIMP CBolt::GetElementValue(
	/* [in] */ DISPID dispID,
	/* [in] */ DWORD dwCookie,
	/* [out] */ VARIANT * pVarOut)
{
    if (dispID == 1)
	{
		CComVariant var;
		get_alignment(&var);
		AcAxPoint3d pt(var);
		pVarOut->vt = VT_R8;
		pVarOut->dblVal = pt[dwCookie];
		return S_OK;
	} else if (dispID == 6)
	{
		CComVariant var;
		get_position(&var);
		AcAxPoint3d pt(var);
		pVarOut->vt = VT_R8;
		pVarOut->dblVal = pt[dwCookie];
		return S_OK;
	}
    return E_NOTIMPL;

}

//IOPMPropertyExpander
STDMETHODIMP CBolt::SetElementValue(
	/* [in] */ DISPID dispID,
	/* [in] */ DWORD dwCookie,
	/* [in] */ VARIANT VarIn)
{
     if (dispID == 1)
	{
		CComVariant var;
		get_alignment(&var);
		AcAxPoint3d pt(var);
		pt[dwCookie] = VarIn.dblVal;
		pt.setVariant(var);
		put_alignment(var);
		return S_OK;
	} else if (dispID == 6)
	{
		CComVariant var;
		get_position(&var);
		AcAxPoint3d pt(var);
		pt[dwCookie] = VarIn.dblVal;
		pt.setVariant(var);
		put_position(var);
		return S_OK;
	}
    return E_NOTIMPL;

}

//IOPMPropertyExpander
STDMETHODIMP CBolt::GetElementStrings( 
	/* [in] */ DISPID dispID,
	/* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
	/* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut)
{
     if (dispID == 1)
	{
		pCaStringsOut->cElems = 3;
		pCaStringsOut->pElems = (LPOLESTR*)CoTaskMemAlloc(sizeof(LPOLESTR)*3);
		pCaStringsOut->pElems[0] = SysAllocString(L"Dir X");
		pCaStringsOut->pElems[1] = SysAllocString(L"Dir Y");
		pCaStringsOut->pElems[2] = SysAllocString(L"Dir Z");
		pCaCookiesOut->cElems = 3;
		pCaCookiesOut->pElems = (DWORD*)CoTaskMemAlloc(sizeof(DWORD)*3);
		for (int i=0;i<3;i++)
			pCaCookiesOut->pElems[i] = i;
		return S_OK;
	} else if (dispID == 6)
	{
		pCaStringsOut->cElems = 3;
		pCaStringsOut->pElems = (LPOLESTR*)CoTaskMemAlloc(sizeof(LPOLESTR)*3);
		pCaStringsOut->pElems[0] = SysAllocString(L"Pos X");
		pCaStringsOut->pElems[1] = SysAllocString(L"Pos Y");
		pCaStringsOut->pElems[2] = SysAllocString(L"Pos Z");
		pCaCookiesOut->cElems = 3;
		pCaCookiesOut->pElems = (DWORD*)CoTaskMemAlloc(sizeof(DWORD)*3);
		for (int i=0;i<3;i++)
			pCaCookiesOut->pElems[i] = i;
		return S_OK;
	} 
    return E_NOTIMPL;

}

//IOPMPropertyExpander
STDMETHODIMP CBolt::GetElementGrouping(
    /* [in] */ DISPID dispID,
	/* [out] */ short *groupingNumber)
{
    if (dispID == 1 || dispID == 6)
	{
		*groupingNumber = 0;
		return S_OK;
	}
	return E_NOTIMPL;

}

//IOPMPropertyExpander
STDMETHODIMP CBolt::GetGroupCount(
    /* [in] */ DISPID dispID,
	/* [out] */ long *nGroupCnt)
{
    if (dispID == 2 || dispID == 4)
	{
		*nGroupCnt = 3;
		return S_OK;
	}
	return E_NOTIMPL;

}

/// IOPMPropertyExtension
// OPM calls this function for each property to obtain a list of strings and cookies if they are available.
// This function is declared on the IPerPropertyBrowsing interface. Our IOPMPropertyExtensionImpl
// class implements this member by reading the values in the OPM property map.

STDMETHODIMP CBolt::GetPredefinedStrings(DISPID dispID, CALPOLESTR *pCaStringsOut, CADWORD *pCaCookiesOut)
{
	return IOPMPropertyExtensionImpl2<CBolt>::GetPredefinedStrings(dispID,pCaStringsOut,pCaCookiesOut);
}

// OPM calls this function when the user selects an element from a drop down list. OPM provides
// the cookie that we associated with the element in the GetPredefinedStrings function. We are
// responsible for mapping this cookie back to a value that the properties corresponding put_ function
// can understand. 
// In this particular case all we need to do is to provide the name of the text style as
// the put_TextStyle method needs that.

STDMETHODIMP CBolt::GetPredefinedValue(DISPID dispID, DWORD dwCookie, VARIANT *pVarOut)
{
	return IOPMPropertyExtensionImpl2<CBolt>::GetPredefinedValue(dispID,dwCookie,pVarOut);
}



///////////////////////////////////////////
// ICategorizeProperties2 Implementation //
///////////////////////////////////////////

  // BUG: removes all category names.
STDMETHODIMP CBolt::MapPropertyToCategory(
		DISPID dispID,		// [in]
		int *pCatID)	// [out]
{	
	switch (dispID)
	{
		case DISPID_ALIGNMENT:
			*pCatID = PROPCAT_Alignment;
			break;
		case DISPID_HEADDIAMETER:
			*pCatID = PROPCAT_Dimension;
			break;
		case DISPID_HEADHEIGHT:
			*pCatID = PROPCAT_Dimension;
			break;
		case DISPID_HEADSIDES:
			*pCatID = PROPCAT_Dimension;
			break;
		case DISPID_MATERIALNAME:
			*pCatID = PROPCAT_Part_Desc;
			break;
		case DISPID_POSITION:
			*pCatID = PROPCAT_Position;
			break;
		case DISPID_SHAFTDIAMETER:
			*pCatID = PROPCAT_Dimension;
			break;
		case DISPID_SHAFTLENGTH:
			*pCatID = PROPCAT_Dimension;
			break;
		case DISPID_PARTNUMBER:
			*pCatID = PROPCAT_Part_Desc;
			break;
		case DISPID_THREADLENGTH:
			*pCatID = PROPCAT_Dimension;
			break;
		case DISPID_THREADWIDTH:
			*pCatID = PROPCAT_Dimension;
			break;
		case DISPID_COLOR:
			*pCatID = PROPCAT_Color;
			break;
		default:
			return S_FALSE;
	}
	
	return S_OK;
}

	// checking this start.
STDMETHODIMP CBolt::GetCategoryName(
		int CatID,		// [in]
		LCID lCid,		// [in]
		BSTR *pCategoryName)	// [out]
{
	switch(CatID)
	{
	case PROPCAT_Global:
		*pCategoryName = ::SysAllocString(L"Bolt Global Properties");
		break;
	case PROPCAT_Position:
		*pCategoryName = ::SysAllocString(L"Bolt Position");
		break;
	case PROPCAT_Alignment:
		*pCategoryName = ::SysAllocString(L"Bolt Alignment");
		break;
	case PROPCAT_Color:
		*pCategoryName = ::SysAllocString(L"Bolt Color");
		break;
	case PROPCAT_Part_Desc:
		*pCategoryName = ::SysAllocString(L"Bolt Part Description");
		break;
	case PROPCAT_Dimension:
		*pCategoryName = ::SysAllocString(L"Bolt Dimensions");
		break;
	}

	return S_OK;
}

STDMETHODIMP CBolt::GetCategoryDescription(
		int CatID,					 //[in]
		LCID lCid,					 //[in]
		BSTR *pCategoryDescription)  //[out]
{	
	switch(CatID)
	{
	case PROPCAT_Global:
		*pCategoryDescription = ::SysAllocString(L"These are Bolt global properties");
		break;
	case PROPCAT_Position:
		*pCategoryDescription = ::SysAllocString(L"This is Bolt's drawing position");
		break;
	case PROPCAT_Alignment:
		*pCategoryDescription = ::SysAllocString(L"This is Bolt's alignment");
		break;
	case PROPCAT_Part_Desc:
		*pCategoryDescription = ::SysAllocString(L"These are properties describing the Bolt");
		break;
	case PROPCAT_Dimension:
		*pCategoryDescription = ::SysAllocString(L"These are the Bolt's dimensions");
		break;
	case PROPCAT_Color:
		*pCategoryDescription = ::SysAllocString(L"This is Bolt's color");
		break;
	}
	return S_OK;
}

STDMETHODIMP CBolt::ShowCategory(
		int CatID,		// [in]
		VARIANT_BOOL *pShow)	// [out]
{	
	return S_OK;
}


STDMETHODIMP CBolt::GetCategoryWeight(
		int CatID,				//[in]
		long *pCategoryWeight)  //[out]
{
	HRESULT hr = E_NOTIMPL;
	return hr;
}

STDMETHODIMP CBolt::GetParentCategory(
		int CatID,			//[in]
		int *pParentCatID) //[out]
{
	switch(CatID)
	{
	case PROPCAT_Alignment:
		*pParentCatID = PROPCAT_Global;
		break;
	case PROPCAT_Position:
		*pParentCatID = PROPCAT_Global;
		break;
	case PROPCAT_Color:
		*pParentCatID = PROPCAT_Global;
		break;
	}

	return S_OK;
}

STDMETHODIMP CBolt::GetUniqueID(
		BSTR *pVal) //[out]
{
	return E_NOTIMPL;
}

 // checking this end
// throwing assert.
STDMETHODIMP CBolt::GetCommandButtons(
		int CatID,					//[in]
		VARIANT *pCatCommandBtns)   //[out]
{
	return E_NOTIMPL;
}



	////////////////////////////////////////
	// IPerPropertyDisplay Implementation //
	////////////////////////////////////////
 // checking this start.
STDMETHODIMP CBolt::GetCustomPropertyCtrl(
		VARIANT Id,			//[in]
		LCID lcid,			//[in]
		BSTR *pProgId)		//[out]

{
	return S_OK;
}


STDMETHODIMP CBolt::GetPropTextColor(
		VARIANT Id,				//[in]
		OLE_COLOR *pTextColor)	//[out]
{
	OLE_COLOR col = 1;
	pTextColor = &col;
	return S_OK;
}
	
STDMETHODIMP CBolt::IsFullView(
		VARIANT Id,				//[in]
		VARIANT_BOOL *pVisible,	//[out]
		DWORD *pIntegralHeight)//[out]
{
	return S_OK;
}


STDMETHODIMP CBolt::GetPropertyWeight(
		VARIANT Id,				//[in]
		long *pPropertyWeight)	//[out]
{
	HRESULT hr = E_NOTIMPL;
	return hr;
}

STDMETHODIMP CBolt::GetDisplayName(/*[in]*/DISPID dispID,/*[out]*/BSTR *propName)
{
	return E_NOTIMPL;
}


STDMETHODIMP CBolt::Editable(/*[in]*/DISPID dispID, /*[out]*/BOOL* bEditable)
{
	return E_NOTIMPL;
}
    
STDMETHODIMP CBolt::ShowProperty(/*[in]*/DISPID dispID, /*[out]*/BOOL *pShow)
{
	return E_NOTIMPL;
}

STDMETHODIMP CBolt::get_alignment(VARIANT *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint3d pt;
		AcGeVector3d align = pBolt->getAlignment();
       	pt.set(align.x, align.y, align.z);
		pt.setVariant(*pVal);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;
}

STDMETHODIMP CBolt::put_alignment(VARIANT newVal)
{
	try
    {
        AcAxPoint3d pt = newVal;
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;

		pBolt->setAlignment(pt.asVector());
		Fire_Notification(DISPID_ALIGNMENT); 

		// See axtempl.h for Fire_Notification
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set alignment.",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;
}

STDMETHODIMP CBolt::get_headDiameter(double *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
        
        *pVal = pBolt->getHeadDiameter();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IBolt,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CBolt::put_headDiameter(double newVal)
{
	try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;

        pBolt->setHeadDiameter(newVal);
        Fire_Notification(DISPID_HEADDIAMETER); 
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set head diameter",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;
}

STDMETHODIMP CBolt::get_headHeight(double *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
        
        *pVal = pBolt->getHeadHeight();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IBolt,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CBolt::put_headHeight(double newVal)
{
	try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;

        pBolt->setHeadHeight(newVal);
        Fire_Notification(DISPID_HEADHEIGHT); 
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set head height",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;
}

STDMETHODIMP CBolt::get_headSides(int *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
        
        *pVal = pBolt->getHeadSides();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IBolt,E_FAIL);
    }
	return S_OK;

}

STDMETHODIMP CBolt::put_headSides(int newVal)
{
	try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;

        pBolt->setHeadSides(newVal);
        Fire_Notification(DISPID_HEADSIDES); 
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set head sides.",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;
}

STDMETHODIMP CBolt::get_materialName(BSTR *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
    
		CComBSTR bstrMaterialName(pBolt->materialName);
		*pVal = bstrMaterialName.Copy();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IBolt,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CBolt::put_materialName(BSTR newVal)
{
	try
    {
		USES_CONVERSION;
		AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;

		strcpy(pBolt->materialName,OLE2A(newVal));
        Fire_Notification(DISPID_MATERIALNAME); 
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set shaft length.",IID_IBolt,E_FAIL);
    }
	
	return S_OK;
}

STDMETHODIMP CBolt::get_position(VARIANT *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
        AcAxPoint3d pt = pBolt->getPosition();
        pt.setVariant(*pVal);
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object.",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;
}

STDMETHODIMP CBolt::put_position(VARIANT newVal)
{
	try
    {
        AcAxPoint3d pt = newVal;
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
		pBolt->setPosition(pt);
		Fire_Notification(DISPID_POSITION); 
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set position.",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;

}

STDMETHODIMP CBolt::get_shaftDiameter(double *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
        
        *pVal = pBolt->getShaftDiameter();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IBolt,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CBolt::put_shaftDiameter(double newVal)
{
		try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;

        pBolt->setShaftDiameter(newVal);
        Fire_Notification(DISPID_SHAFTDIAMETER); 
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set shaft diameter.",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;
}

STDMETHODIMP CBolt::get_shaftLength(double *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
        
        *pVal = pBolt->getShaftLength();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IBolt,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CBolt::put_shaftLength(double newVal)
{
	try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;

        pBolt->setShaftLength(newVal);
        Fire_Notification(DISPID_SHAFTLENGTH); 
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set shaft length.",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;
}

STDMETHODIMP CBolt::get_partNumber(BSTR *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
    
		CComBSTR bstrPartNumber(pBolt->partNumber);
		*pVal = bstrPartNumber.Copy();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IBolt,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CBolt::put_partNumber(BSTR newVal)
{
	try
    {
		USES_CONVERSION;
		AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;

		strcpy(pBolt->partNumber,OLE2A(newVal));
		Fire_Notification(DISPID_PARTNUMBER); 
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set shaft length.",IID_IBolt,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CBolt::get_threadLength(double *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
        
        *pVal = pBolt->getThreadLength();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IBolt,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CBolt::put_threadLength(double newVal)
{
	try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;

        pBolt->setThreadLength(newVal);
        Fire_Notification(DISPID_THREADLENGTH); 
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set thread length.",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;
}

STDMETHODIMP CBolt::get_threadWidth(double *pVal)
{
	CHECKOUTPARAM(pVal);
    try
    {
        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForRead,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;
        
        *pVal = pBolt->getThreadWidth();
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to open object",IID_IBolt,E_FAIL);
    }
	return S_OK;
}

STDMETHODIMP CBolt::put_threadWidth(double newVal)
{
	try
    {
        AXEntityDocLockNoDbOk(m_objRef.objectId());

        Acad::ErrorStatus es;
        AcAxObjectRefPtr<asdkBolt> pBolt(&m_objRef,AcDb::kForWrite,Adesk::kTrue);
	    if((es=pBolt.openStatus()) != Acad::eOk)
            throw es;

        pBolt->setThreadWidth(newVal);
        Fire_Notification(DISPID_THREADWIDTH); 
    }
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to set thread width.",IID_IBolt,E_FAIL);
    }
    catch(const HRESULT hr)
    {
        return Error(L"Invalid argument.",IID_IBolt,hr);
    }
	return S_OK;
}
