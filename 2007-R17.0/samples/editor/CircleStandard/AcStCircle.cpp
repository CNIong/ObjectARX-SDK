//
//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
// AcStCircle.cpp : Implementation of CAcStCircle
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "AcStCircle.h"



// CAcStCircle
CAcStCircle::CAcStCircle()
{
    TRACE(_T("CAcStCircle::CAcStCircle() called.\n"));

	m_pPlugin = NULL;
	m_pError = NULL;
	m_pAcStMgr = NULL;
	m_pComDwgDb = NULL;
	m_pDwgDb = NULL;
	m_pDesc = AcDbCircle::desc();

	m_curIndex = -1;
	m_recommendedFixIndex = -1;

	m_objIdsToCheck.setLogicalLength(0);
	m_objIdsFix.setLogicalLength(0);
	m_circleCacheArray.setLogicalLength(0);
}

CAcStCircle::~CAcStCircle()
{
    TRACE(_T("CAcStCircle::~CAcStCircle() called.\n"));

	Clear();
}


STDMETHODIMP
CAcStCircle::FinalConstruct()
{
    TRACE(_T("CAcStCircle::FinalConstruct() called.\n"));
	return S_OK;
}

void
CAcStCircle::FinalRelease()
{
    TRACE(_T("CAcStCircle::FinalRelease() called.\n"));
	Clear();
}

STDMETHODIMP
CAcStCircle::get_Author(BSTR *pVal)
{
	*pVal = ::SysAllocString(L"Autodesk, Inc.");

	return S_OK;
}

STDMETHODIMP
CAcStCircle::get_Description(BSTR *pVal)
{
	*pVal = ::SysAllocString(L"Plugin to Check the Color of Database Resident Circles");

	return S_OK;
}

STDMETHODIMP
CAcStCircle::get_HRef(BSTR *pVal)
{
	*pVal = ::SysAllocString(L"http://www.autodesk.com");

	return S_OK;
}

STDMETHODIMP
CAcStCircle::get_Name(BSTR *pVal)
{
	*pVal = ::SysAllocString(L"AcStCircle Standard Plugin");

	return S_OK;
}

STDMETHODIMP
CAcStCircle::get_Version(BSTR *pVal)
{
	*pVal = ::SysAllocString(L"2.2");

	return S_OK;
}

STDMETHODIMP
CAcStCircle::get_Icon(long *pVal)
{
	*pVal = 1;
	return S_OK;
}

STDMETHODIMP
CAcStCircle::CheckSysvar(BSTR sysvarName, 
						VARIANT_BOOL bGetAllFixes, 
                        VARIANT_BOOL *bPassFail)
{
    TRACE(_T("CAcStCircle::CheckSysvar() called. Not Implemented!\n"));
	return E_NOTIMPL;
}

STDMETHODIMP
CAcStCircle::Initialize(IAcStManager2* pMgr)
{
    TRACE(_T("CAcStCircle::Initialize() called.\n"));

	m_pAcStMgr = pMgr;
	m_pPlugin = this;

	return S_OK;
}

STDMETHODIMP
CAcStCircle::Clear()
{
    TRACE(_T("CAcStCircle::Clear() called.\n"));

	m_pPlugin = NULL;
	m_curIndex = -1;
	m_recommendedFixIndex = -1;
	m_pAcStMgr = NULL;
	m_pComDwgDb = NULL;
	m_pDwgDb = NULL;
	m_pDesc = NULL;
	if(m_pError != NULL)
	{
		m_pError.Release();
		m_pError = NULL;
	}

	m_objIdsToCheck.setLogicalLength(0);
	m_objIdsFix.setLogicalLength(0);
	for(long i = 0; i < m_circleCacheArray.length(); i++)
	{
		if( m_circleCacheArray[i].pFix != NULL )
            m_circleCacheArray[i].pFix.Release();
		m_circleCacheArray[i].pFix = NULL;
	}
	m_circleCacheArray.setLogicalLength(0);
    
	return S_OK;
}

STDMETHODIMP
CAcStCircle::SetupForAudit(IAcadDatabase *pDb, 
                          BSTR szPathName, 
						  VARIANT vStdNameArray, 
                          VARIANT vStdPathArray, 
						  VARIANT vStdDbArray)
{
    TRACE(_T("CAcStCircle::SetupForAudit() called.\n"));

	Acad::ErrorStatus es;
	long uBound1 = 0, uBound2 = 0, lBound1 = 0, lBound2 = 0;
	SafeArrayGetLBound(vStdPathArray.parray, 1, &lBound1);
	SafeArrayGetUBound(vStdPathArray.parray, 1, &uBound1);	
	SafeArrayGetLBound(vStdDbArray.parray, 1, &lBound2);
	SafeArrayGetUBound(vStdDbArray.parray, 1, &uBound2);	
	
	// They should have the same dimension
	if ((lBound1 != lBound2) || (uBound1 != uBound2)) {
		return E_FAIL;
	}

	// Cache all circles ready to be checked in the current drawing.
	m_pComDwgDb = pDb;
	es = getEntitiesOfTypeFromComDb(pDb, m_pDesc, m_objIdsToCheck);
	VERIFY(es==Acad::eOk);

	// Iterate over the DWSes and cache all properties (color and radius) of standard circles 
	for (long j = lBound1; j <= uBound1; j++) 
	{	
		// Get the DWS database
		CComPtr<IAcadDatabase> pStdDb = NULL;
		getIUnknownElementFromSafeArray(&vStdDbArray, j, &(pStdDb.p));
		VERIFY(pStdDb != NULL);

		// Cache properties (color and radius) of all circles in the DWS database
		for(; !m_objIdsFix.isEmpty(); m_objIdsFix.removeLast()){}
		m_objIdsFix.setLogicalLength(0);
		es = getEntitiesOfTypeFromComDb((IAcadDatabase*&)pStdDb, m_pDesc, m_objIdsFix);
		for(int i=0; i<m_objIdsFix.length(); i++)
		{
			AcDbEntity* pEnt = NULL;
			AcDbCircle* pCir = NULL;
			es = acdbOpenAcDbEntity(pEnt, m_objIdsFix[i], AcDb::kForRead);
			VERIFY(pEnt);
			pCir = AcDbCircle::cast(pEnt);
			if( es == Acad::eOk && pCir != NULL )
			{
				circleCache cirCache;
				cirCache.color = pCir->colorIndex();
				cirCache.radius = pCir->radius();
				pCir->close();
				pCir = NULL;
				
				getStringElementFromSafeArray(&vStdNameArray, j, cirCache.standardFileName);
				
				FixPointer pFix = NULL;
				createNewFix(&pFix, CString(_T("Color fix")), cirCache.standardFileName);
				CString str;
				TCHAR strHandle[20];
				m_objIdsFix[i].handle().getIntoAsciiBuffer(strHandle);
				str.Format(_T("Color index %d of Circle %s"), cirCache.color, strHandle);
				pFix->put_FixObjectName( str.AllocSysString() );
				CComVariant var = cirCache.color;
				pFix->PropertyValuePut(L"Color", var);
				cirCache.pFix = pFix;
				m_circleCacheArray.append(cirCache);
			}
		}	// end of loop for fix objects
		
		pStdDb.Release();
	}	// end of loop for DWS database

	return S_OK;
}

STDMETHODIMP
CAcStCircle::StampDatabase(IAcadDatabase *pDb, VARIANT_BOOL *bStampIt)
{
    TRACE(_T("CAcStCircle::StampDatabase called.\n"));
   
	// If the DWS contains circles, we stamp it by returning *bStampIt as VARIANT_TRUE,
	// otherwise, returning *bStampIt as VARIANT_FALSE.
	Acad::ErrorStatus es;
	long stdCirCount;
	AcDbObjectIdArray m_objIds;

	es = getEntitiesOfTypeFromComDb(pDb, m_pDesc, m_objIds);
	VERIFY(es == Acad::eOk);
	stdCirCount = m_objIds.length();

	if(stdCirCount == 0)
		*bStampIt = VARIANT_FALSE;
	else 
		*bStampIt = VARIANT_TRUE;

	return S_OK;
}

// Write plugin information to batch checker report through a PluginInfoSectionNode
STDMETHODIMP
CAcStCircle::WritePluginInfo(IDispatch * pPluginInfoSectionNode)
{
    TRACE(_T("CAcStCircle::WritePluginInfo called.\n"));

    if ((m_pPlugin == NULL) || (pPluginInfoSectionNode == NULL))
        return E_INVALIDARG;
    try
    {
        // Query the IUnknown pointer for the IXMLDOMElement interface
        CComQIPtr<IXMLDOMElement> pPluginInfoSectionElement = pPluginInfoSectionNode;
        if (pPluginInfoSectionNode == NULL)
            return E_POINTER;
        CComBSTR szName;
 
        CComBSTR szVersion;
        CComBSTR szDescription;
        CComBSTR szAuthor;
        CComBSTR szHRef;
        CComBSTR szDwsName;
        CComBSTR szStatus = _T(/*MSG0*/"1");
 
        ThrowIfFail(m_pPlugin->get_Name(&szName));
        ThrowIfFail(m_pPlugin->get_Author(&szAuthor));
        ThrowIfFail(m_pPlugin->get_Version(&szVersion));
        ThrowIfFail(m_pPlugin->get_Description(&szDescription));
        ThrowIfFail(m_pPlugin->get_HRef(&szHRef));
 
        ThrowIfFail( writePluginInfoNode(pPluginInfoSectionElement,
                        szName,
                        szVersion,
                        szDescription,
                        szAuthor,
                        szHRef,
                        szDwsName,
                        szStatus
                        ) );
 
    }
    catch (HRESULT hr)
    {
        VERIFY(false);
        return hr;
    }

    return S_OK;
}

HRESULT
CAcStCircle::writePluginInfoNode(IXMLDOMElement* pPluginInfoSectionElement,
                        const CComBSTR& szPluginName,
                        const CComBSTR& szVersion,
                        const CComBSTR& szDescription,
                        const CComBSTR& szAuthor,
                        const CComBSTR& szHRef,
                        const CComBSTR& szDwsName,
                        const CComBSTR& szStatus    //notes
                        )
{
    if (pPluginInfoSectionElement == NULL)
        return E_INVALIDARG;
    try
    {
        // Get the node (it's the element that was passed)
        CComPtr<IXMLDOMNode> pSectionNode = NULL;
        ThrowIfFail(pPluginInfoSectionElement->QueryInterface(IID_IXMLDOMNode, (void**)(&pSectionNode)));
        // Create the new node
        CComPtr<IXMLDOMNode> pPluginInfoNode = NULL;
        CComBSTR tagname = STRING_PLUGININFO_TAG;
        ThrowIfFail( AddElementToNode(pSectionNode, tagname.m_str, &pPluginInfoNode) );
        // Query for element interface
        CComQIPtr<IXMLDOMElement> pPluginInfoElement = pPluginInfoNode;
        if (pPluginInfoElement == NULL)
            return E_POINTER;
 
        CComBSTR szAttName;
        CComVariant vAttValue;
        CComBSTR tmp;
     
        szAttName = FIELD_PLUGIN_PLUGINNAME; //"PluginName";
        vAttValue = szPluginName;
        ThrowIfFail(pPluginInfoElement->setAttribute(szAttName, vAttValue));
        
        szAttName = FIELD_PLUGIN_VERSION; //"Version";
        vAttValue = szVersion;
        ThrowIfFail(pPluginInfoElement->setAttribute(szAttName, vAttValue));
 
        szAttName = FIELD_PLUGIN_DESCRIPTION; //"Description";
        vAttValue = szDescription;
        ThrowIfFail(pPluginInfoElement->setAttribute(szAttName, vAttValue));
 
        szAttName = FIELD_PLUGIN_AUTHOR; //"Author";
        vAttValue = szAuthor;
        ThrowIfFail(pPluginInfoElement->setAttribute(szAttName, vAttValue));
 
        szAttName = FIELD_PLUGIN_HREF; //"HRef";
        vAttValue = szHRef;
        ThrowIfFail(pPluginInfoElement->setAttribute(szAttName, vAttValue));
 
        szAttName = FIELD_PLUGIN_DWSNAME; // dwsname
        vAttValue = szDwsName;
        ThrowIfFail(pPluginInfoElement->setAttribute(szAttName, vAttValue));
 
        szAttName = FIELD_PLUGIN_STATUS; // notes
        vAttValue = szStatus;
        ThrowIfFail(pPluginInfoElement->setAttribute(szAttName, vAttValue));
 
    }
    catch (HRESULT hr)
    {
        VERIFY(false);
        return hr;
    }
    return S_OK;
}

// // Adds a new child element to an existing parent node. 
// // Inputs:      pParentNode     Pointer to node element is added to
// //              szNodeName      Tag of new element
// // Outputs:     pNewElement     Pointer to new node added to parent
HRESULT
CAcStCircle::AddElementToNode(IXMLDOMNode *pParentNode, BSTR &szNodeName, IXMLDOMNode **pNewNode)
{
    if (NULL == pParentNode || NULL == pNewNode)
        return E_POINTER;

    if (SysStringLen(szNodeName) <= 0)
        return E_INVALIDARG;

    CComPtr<IXMLDOMDocument> pDoc;
    CComPtr<IXMLDOMElement> pElem;
    CComQIPtr<IXMLDOMNode> pElemAsNode;

    try {
        ThrowIfFail(pParentNode->get_ownerDocument(&pDoc));
        ThrowIfFail(pDoc->createElement(szNodeName, &pElem));
        pElemAsNode = pElem;
        if (!pElemAsNode)
            throw E_FAIL;

        ThrowIfFail(pParentNode->appendChild(pElemAsNode, pNewNode));
    }
    catch (HRESULT hr) {
        return hr;
    }

    return S_OK;
}

STDMETHODIMP
CAcStCircle::Start(IAcStError* pErr)
{
    TRACE(_T("CAcStCircle::Start() called.\n"));

	if(m_circleCacheArray.length() == 0)
		return S_OK;

	if (pErr != NULL)
	{
		long badId = 0;
		pErr->get_BadObjectId(&badId); 
		
		// Find the index for badobjectid in the m_objIdsToCheck array.
		for (m_curIndex=0; m_curIndex < m_objIdsToCheck.length(); m_curIndex++)
		{
			AcDbObjectId objId = m_objIdsToCheck.at(m_curIndex);
			if (objId.asOldId() == badId)
			{
				m_curIndex--;
				return Next(); 
			}
		}
	}

	// No error was passed in. Start checking from the very begining.
	m_curIndex = -1;
	return Next();
}

STDMETHODIMP
CAcStCircle::Next()
{
    TRACE(_T("CAcStCircle::Next() called.\n"));

	if(m_circleCacheArray.length() == 0)
		return S_OK;
    if (m_curIndex >= m_objIdsToCheck.length())
		return E_FAIL;

	if(m_pError != NULL)
	{
		m_pError.Release();
		m_pError = NULL; 
	}
	m_curIndex++;
	bool bFoundError = false;
	AcDbObjectId badId = NULL;
	Acad::ErrorStatus es;

	while (m_curIndex < m_objIdsToCheck.length())
	{
		AcDbObjectId objId = m_objIdsToCheck.at(m_curIndex);

		// Try to find a circle with the same color from the cached standard circles.
		AcDbEntity* pEnt = NULL;
		AcDbCircle* pCir = NULL;
		es = acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead);
		VERIFY(es == Acad::eOk && pEnt);
		pCir = AcDbCircle::cast(pEnt);
		VERIFY(pCir);
		long colorIndex = pCir->colorIndex();
		pCir->close();
		
		int index;
		for( index=0; index < m_circleCacheArray.length(); index++)
		{
			if( colorIndex == m_circleCacheArray.at(index).color )
				break;
		}
		
		if(index == m_circleCacheArray.length())
		{
			bFoundError = true;
			badId = objId;
		}

		if ( bFoundError )
       {
           // We found an error so create a local error object.
           m_pError = NULL;
			HRESULT hr;
			hr = m_pError.CoCreateInstance(CLSID_AcStError);
			VERIFY(hr==S_OK);
			hr = m_pError->put_Plugin(m_pPlugin);
			VERIFY(hr==S_OK);
			hr = m_pError->put_Description(L"Color is non-standard");
			VERIFY(hr==S_OK);
			hr = m_pError->put_BadObjectId(badId.asOldId());
			VERIFY(hr==S_OK);
			CString str;
			TCHAR strHandle[20];
			badId.handle().getIntoAsciiBuffer(strHandle);
			str.Format(_T("color index %d of Circle %s"), colorIndex, strHandle); 
			hr = m_pError->put_BadObjectName(str.AllocSysString());
			VERIFY(hr==S_OK);

			hr = m_pError->put_ErrorTypeName(L"Color");
			VERIFY(hr==S_OK);
			hr = m_pError->put_ResultStatus(AcStResultStatus(acStResFlagsNone));
			VERIFY(hr==S_OK);
			CComVariant var;
			var = colorIndex;
			hr = m_pError->PropertyValuePut(L"Color", var);
			VERIFY(hr==S_OK);

			break;
       }
	   
		m_curIndex++;
	}

	return S_OK;
}

STDMETHODIMP
CAcStCircle::Done(/*[out, retval]*/ VARIANT_BOOL* bIsDone)
{
    TRACE(_T("CAcStCircle::Done() called.\n"));

	if( m_pError == NULL )
		*bIsDone = VARIANT_BOOL(TRUE);
	else
		*bIsDone = VARIANT_BOOL(FALSE);

	return S_OK;
}

STDMETHODIMP
CAcStCircle::GetError(/*[out, retval]*/ IAcStError** pErr)
{
    TRACE(_T("CAcStCircle::GetError() called.\n"));

	if(m_pError == NULL)
	{
		*pErr = NULL;
		return S_OK;
	}

	return m_pError.CopyTo(pErr);
}


STDMETHODIMP
CAcStCircle::SetContext(/*[in]*/ VARIANT objIdArray, VARIANT_BOOL bUseDb)
{
    TRACE(_T("CAcStCircle::SetContext() called.\n"));

	return S_OK;
}

STDMETHODIMP
CAcStCircle::GetObjectFilter(/*[out, retval]*/ VARIANT* classNameArray)
{
    TRACE(_T("CAcStCircle::GetObjectFilter() called.\n"));

    CStringArray csFilterArray;
	CString strCir = _T("AcDbCircle");
    csFilterArray.Add(strCir); 
    return VariantFromArray(csFilterArray, classNameArray);	
}

STDMETHODIMP
CAcStCircle::GetRecommendedFix(	/*[in]*/IAcStError* pError, 
							   /*[out, retval]*/IAcStFix** ppFix)
{
    TRACE(_T("CAcStCircle::GetRecommendedFix() called.\n"));

	if(m_circleCacheArray.length() == 0)
	{
		setErrorStatusFlags(pError, acStResNoRecommendedFix, true);
		return S_OK;
	}

	HRESULT hr = S_OK;  
	hr = FindRecommendedFixIndex(pError, m_recommendedFixIndex);
	if(FAILED(hr))
	{
		setErrorStatusFlags(pError, acStResNoRecommendedFix, true);
		return S_OK;
	}

	m_circleCacheArray[m_recommendedFixIndex].pFix.CopyTo(ppFix);

	return hr;
}

// This function loads the variant fixArray with an array of IAcStFix* for the given error.
// If null is passed for the error, the function will return all available fixes.
STDMETHODIMP
CAcStCircle::GetAllFixes(IAcStError* pError, VARIANT* fixArray, long* recommendedFixIndex)
{
    TRACE(_T("CAcStCircle::GetAllFixes() called.\n"));

	*recommendedFixIndex = -1;

	long count = m_circleCacheArray.length();
	if(count == 0)
		return S_OK;

	fixArray->parray = SafeArrayCreateVector(VT_UNKNOWN, 0, count);
	fixArray->vt = VT_ARRAY | VT_UNKNOWN;
	if (fixArray->parray == NULL)
		return E_OUTOFMEMORY;

	IUnknown* pUnk;
	for(long index = 0; index < count; index++)
	{
		FixPointer pFix = NULL;
		pFix = m_circleCacheArray.at(index).pFix;
		pUnk = reinterpret_cast<IUnknown*>(pFix.p);
		if (pUnk == NULL)
			return E_FAIL;
		SafeArrayPutElement(fixArray->parray, &index, pUnk);
	}
	
	if (pError == NULL)
		return S_OK;

	//	Find the recommendedFixIndex.
	*recommendedFixIndex = -1;
	FindRecommendedFixIndex(pError, *recommendedFixIndex);

	if (*recommendedFixIndex == -1)
		ThrowIfFail( setErrorStatusFlags(pError, acStResNoRecommendedFix, true) );
	else
		ThrowIfFail( setErrorStatusFlags(pError, acStResNoRecommendedFix, false) );

    return S_OK;
}

STDMETHODIMP
CAcStCircle::GetPropertyDiffs(IAcStError* pError, 
                                    IAcStFix* pFix, 
                                    VARIANT* pPropNames,
                                    VARIANT* pErrorValues,
                                    VARIANT* pFixValues,
                                    VARIANT* pFixableStatuses)
{
    TRACE(_T("CAcStCircle::GetPropertyDiffs() called.\n"));

    try
    {
		long propCount;
		ThrowIfFail(pError->get_PropertyCount(&propCount));

        CStringArray csPropNames;
        CStringArray csErrorValues;
        CStringArray csFixValues;
        VARIANT_BOOL* pTmpFixableStatus = NULL;
        if (propCount > 0)
            pTmpFixableStatus = new VARIANT_BOOL[propCount];

        for (long i=0; i < propCount; i++)
        {
            CComBSTR szPropName;
            CComVariant errorPropValue;
			ThrowIfFail(pError->PropertyGetAt(i, &szPropName, &errorPropValue));
            CComVariant fixPropValue;
			if (S_OK != pFix->PropertyValueGet(szPropName, &fixPropValue))
                continue;

            //fix object has the same prop, so see if they match.
            CString csPropName = (CString)szPropName;
            CString csErrorValue;
			csErrorValue.Format(_T("index %d"), errorPropValue.intVal);
            CString csFixValue;
			csFixValue.Format(_T("index %d"), fixPropValue.intVal);

            if (csErrorValue.CollateNoCase(csFixValue) == 0)
                continue; // Props match so move on.

            csPropNames.Add(csPropName);
            csErrorValues.Add(csErrorValue);
            csFixValues.Add(csFixValue);
        }

        propCount = csPropNames.GetSize(); 
        if (propCount > 0)
        {
            ThrowIfFail( VariantFromArray(csPropNames, pPropNames) );
            ThrowIfFail( VariantFromArray(csErrorValues, pErrorValues) );
            ThrowIfFail( VariantFromArray(csFixValues, pFixValues) );
            // initialize the fixable status array elements to contain VARIANT_TRUE
            for (int i=0; i < propCount; i++)
                pTmpFixableStatus[i] = VARIANT_TRUE;

            ThrowIfFail( VariantFromArray(pTmpFixableStatus, pFixableStatuses, propCount, VT_BOOL, false) );
        }

        if (pTmpFixableStatus != NULL)
            delete [] pTmpFixableStatus;
    }
    catch (HRESULT hr)
    {
        VERIFY(false);
        return hr;
    }
    
	return S_OK;
}

STDMETHODIMP
CAcStCircle::FixError(	/*[in]*/IAcStError* pError, 
						/*[in]*/IAcStFix* pInFix, 
						/*[out]*/BSTR* pFailedReason)
{
    TRACE(_T("CAcStCircle::FixError() called.\n"));

	if (pError == NULL)
		return S_OK;

	SysFreeString(*pFailedReason);
	CString csFailedReason = _T("Fixed successfully.");

	bool bFixedError = false;
	Acad::ErrorStatus es;
	AcDbObjectId badObjId;
	CComPtr<IAcStFix> pFix = pInFix;
	HRESULT hr;

	// If the fix object is null then attempt to get the recommended fix.
	if (pFix == NULL)
	{
		hr = GetRecommendedFix(pError, &pFix);
		if (pFix == NULL)
		{
			// Set the error's result status to failed and noRecommendedFix
			enum AcStResultStatus flags = (AcStResultStatus)(acStResFixFailed | acStResNoRecommendedFix);
			setErrorStatusFlags(pError, flags, true);
			csFailedReason = _T("Can't find a recommended fix!");
			CComBSTR tmp = csFailedReason;
			tmp.CopyTo(pFailedReason);
			return hr;
		}
	}

	try
	{
		long id = 0;
		if(FAILED(hr=pError->get_BadObjectId(&id)))
			throw(hr);
		badObjId.setFromOldId(id);

		// Fix the bad circle
		AcTransaction* pTrans = NULL;
		pTrans = acdbTransactionManager->startTransaction();
		if (pTrans == NULL)
		    throw E_FAIL;

		AcDbObject* pObj = NULL;
		AcDbCircle* pCir = NULL;
		hr = pTrans->getObject(pObj, badObjId, AcDb::kForWrite);
		if (pObj == NULL)
			throw E_FAIL;

		pCir = AcDbCircle::cast(pObj);
		if (pCir == NULL)
			throw(Acad::eInvalidInput);

		CComVariant var;
		hr = pFix->PropertyValueGet(L"Color", &var);
		if(FAILED(hr))
			throw(hr);

		es = pCir->setColorIndex(var.intVal);
		if(es != Acad::eOk)
			throw(es);

		bFixedError = true;
		ThrowIfFail( setErrorStatusFlags(pError, acStResFixed, true) );
		acdbTransactionManager->endTransaction();
	}
	catch (HRESULT)
	{
		csFailedReason = _T("Error when handling pError or pFix object!");
		setErrorStatusFlags(pError, acStResFixFailed, true);
		acdbTransactionManager->abortTransaction();	
	}
	catch (Acad::ErrorStatus)
	{
		csFailedReason = _T("Error when handling bad circle object!");
		setErrorStatusFlags(pError, acStResFixFailed, true);
		acdbTransactionManager->abortTransaction();	
	}

	CComBSTR tmp = csFailedReason;
	tmp.CopyTo(pFailedReason);

	return hr;
}

STDMETHODIMP
CAcStCircle::UpdateStatus(IAcStError* pError)
{
    TRACE(_T("CAcStCircle::UpdateStatus() called.\n"));

    return S_OK;
}


HRESULT 
CAcStCircle::FindRecommendedFixIndex(/*[in]*/	IAcStError* pError,
									 /*[out]*/	long& recommendedFixIndex)
{
	if (pError == NULL)
		return S_OK;

	// Get the objectId for this error
	Acad::ErrorStatus es;
	AcDbObjectId badObjId;
	badObjId.setNull();
	long id = 0;
	pError->get_BadObjectId(&id);
	if( id == 0 )
		return S_OK;

	badObjId.setFromOldId(id);

	// Attempt to get a fix color from the cached m_circleCacheArray
	// Rule: the color of the standard circle with the nearest radius as the bad one.
	AcDbEntity* pEnt = NULL;
	AcDbCircle* pCir = NULL;
	es = acdbOpenAcDbEntity(pEnt, badObjId, AcDb::kForRead);
	if(es != Acad::eOk || pEnt == NULL)
		return E_FAIL;

	pCir = AcDbCircle::cast(pEnt);
	if(pCir == NULL)
		return E_FAIL;
	double radiusToBeChecked = pCir->radius();
	pCir->close();

 	circleCache cirCache = m_circleCacheArray.at(0);
	double diff = fabs(radiusToBeChecked - cirCache.radius);
	recommendedFixIndex = 0;
	for( int i=0; i < m_circleCacheArray.length(); i++)
	{
		if( diff > fabs(radiusToBeChecked-m_circleCacheArray.at(i).radius) )
		{
			cirCache = m_circleCacheArray.at(i);
			diff = fabs(radiusToBeChecked - cirCache.radius);
			recommendedFixIndex = i;
		}
	}

	return S_OK;
}

///////////////////////////////////////////////////////////////////////
//	Helper functions
///////////////////////////////////////////////////////////////////////
HRESULT
CAcStCircle::createNewFix(IAcStFix** ppFix, 
                                 const CString& csDescription,
                                 const CString& csStandardFileName)
{
	try
	{
		FixPointer pFix = NULL;
       ThrowIfFail(pFix.CoCreateInstance(CLSID_AcStFix));
       ThrowIfFail( pFix->put_Description(CComBSTR(csDescription)) );
       ThrowIfFail( pFix->put_StandardFileName(CComBSTR(csStandardFileName)) );
		ThrowIfFail(pFix.CopyTo( ppFix ));
	}
    catch(HRESULT)
	{
		VERIFY(false);
		return E_FAIL;
	}
	return S_OK;
}

// Sets or clears the specified AcStResultStatus flags on the provided error object.
// Pass in bSet=true to set the flags and bSet=false to clear them.
HRESULT
CAcStCircle::setErrorStatusFlags(IAcStError* pError, enum AcStResultStatus flags, bool bSet)
{
    if (pError == NULL)
        return E_POINTER;
    enum AcStResultStatus curFlags;
    HRESULT hr = pError->get_ResultStatus(&curFlags);
    if(S_OK != hr )
        return hr;
    curFlags = (AcStResultStatus)(curFlags | flags);
    if (!bSet)
        curFlags = (AcStResultStatus)(curFlags - flags);
    hr = pError->put_ResultStatus(curFlags);
    if(S_OK != hr )
        return hr;
    return S_OK;
}

HRESULT
CAcStCircle::VariantFromArray(const CStringArray &array,
                     VARIANT            *pVarArray,
                     bool               bCreateVariantArray)
{
    try {
        if (NULL == pVarArray)
            throw E_INVALIDARG;

        if (FAILED(VariantIsEmpty(pVarArray)))
            VariantClear(pVarArray);

        if (array.GetSize() <= 0)
            throw S_OK;

		HRESULT hr = SafeArrayFromArray(array, pVarArray->parray, bCreateVariantArray);
        if ( FAILED(hr) )
			throw hr;
        if (bCreateVariantArray)
            pVarArray->vt = VT_ARRAY | VT_VARIANT;
        else
            pVarArray->vt = VT_ARRAY | VT_BSTR;

    }
    catch (HRESULT hr) {
        return hr;
    }

    return S_OK;
}

HRESULT
CAcStCircle::VariantIsEmpty(const VARIANT *pVariant)
{
    if (NULL == pVariant)
        return E_INVALIDARG;
    if ((V_VT(pVariant) & VT_TYPEMASK) == VT_EMPTY)
        return S_OK;
    else
        return E_FAIL;
}

HRESULT
CAcStCircle::SafeArrayFromArray(const CStringArray &strings,
                       SAFEARRAY          *&psa,
                       bool               bCreateVariantArray)
{
    HRESULT hr;
    VARIANT varData;
    VariantInit(&varData);
    VARTYPE vt = VT_BSTR;

    try {
        // Allocate the safe array
        long nElems = strings.GetSize();
        if (nElems < 1)
            throw E_INVALIDARG;

        if (bCreateVariantArray)
            vt = VT_VARIANT;

        psa = SafeArrayCreateVector(vt, 0, nElems);
        if (NULL == psa)
            throw E_OUTOFMEMORY;


        // Put the data in the safearray
        for (long i = 0; i < nElems; i++) {
            if (!bCreateVariantArray) {
                if (FAILED(hr = SafeArrayPutElement(
                    psa,
                    &i,
                    reinterpret_cast < void *>
                    (strings.GetAt(i).AllocSysString()))))
                    throw hr;
            } else {
                varData.vt = VT_BSTR;
                varData.bstrVal = strings.GetAt(i).AllocSysString();
                if (FAILED(hr = SafeArrayPutElement(psa, &i, &varData)))
                    throw hr;
                VariantClear(&varData);
            }
        }
    }
    catch (HRESULT hres) {
        VariantClear(&varData);
        if (NULL != psa)
            SafeArrayDestroy(psa);

        return hres;
    }

    return S_OK;
}

// Returns the AcDbDatabase pointer for an IAcadDatabase object. 
HRESULT CAcStCircle::getDatabase(IAcadDatabase *pDb, AcDbDatabase **pAcDb)
{
    if (NULL == pDb || NULL == pAcDb)
        return E_INVALIDARG;

    *pAcDb = NULL;

    try {

        CComQIPtr<IAcadBaseDatabase> pBaseDb = pDb;
        
        if (!pBaseDb)
            throw E_FAIL;

		HRESULT hr = pBaseDb->GetDatabase(pAcDb);
    }
    catch (HRESULT hr)
    {
        return hr;
    }

    return S_OK;
}


// Utility method for finding entities of a certain type, e.g. AcDbCircle, 
// from ModelSpace in the database.
Acad::ErrorStatus 
CAcStCircle::getEntitiesOfTypeFromComDb(IAcadDatabase*& pComDb, 
                 AcRxClass*& pDesc, 
                 AcDbObjectIdArray& ids) 
{
    if (NULL == pComDb)
        return Acad::eNoDatabase;
    if (NULL == pDesc)
        return Acad::eInvalidInput;

    Acad::ErrorStatus es = Acad::eOk;
	HRESULT hr;
	IAcStBlockProxy *pMSProxy = NULL;
	long count = 0;

	try {
		hr = m_pAcStMgr->get_ModelSpaceProxy(  pComDb,  &pMSProxy );
		if(hr != S_OK)
			throw(hr);

		hr = pMSProxy->get_Count(&count);
		if(hr != S_OK)
			throw(hr);

		// iterate through the model space and get all entities with the type pDesc.
		for (long item = 0; item < count; item++)
		{
			IAcadEntity *pComEnt = NULL;
			AcDbObjectId objId;
			long longID;
			BSTR bstr;
			CString strObjName;
			CComVariant  varItem(item);

			hr = pMSProxy->Item(varItem, &pComEnt);
			if(hr != S_OK)
				throw(hr);

			pComEnt->get_ObjectID(&longID);
			objId.setFromOldId(longID);
			pComEnt->get_ObjectName(&bstr);
			strObjName = (CString)(bstr);
			if( strObjName.Compare(pDesc->name()) == 0)
			{
				ids.append(objId);
			}
			::SysFreeString(bstr);
			pComEnt->Release();
		}
	}
	catch( HRESULT )
	{
		VERIFY(false);
		TRACE(_T("COM failed.\n"));
	}
    return es;
}

HRESULT
CAcStCircle::VariantIsNull(const VARIANT *Variant)
{
    if (NULL == Variant)
        return E_INVALIDARG;

    if (((V_VT(Variant) & VT_TYPEMASK) == VT_ERROR &&
        (V_ERROR(Variant) & DISP_E_PARAMNOTFOUND)) ||
        (V_VT(Variant) & VT_TYPEMASK) == VT_NULL)
        return S_OK;
    else
        return E_FAIL;
}

HRESULT CAcStCircle::getStringElementFromSafeArray(VARIANT* vArray, long index, CString& csOut)
{
    if (vArray == NULL)
        return E_INVALIDARG;

    HRESULT hr;
    try
    {
        CComBSTR szTmp;
        hr = SafeArrayGetElement(vArray->parray, &index, reinterpret_cast<void*>(&szTmp));
		if(FAILED(hr))
			throw(hr);
        csOut = szTmp;
    }
    catch (HRESULT)
    {
        VERIFY(false);
        return hr;
    }
    return S_OK;
}

template<typename T>
inline HRESULT CAcStCircle::getIUnknownElementFromSafeArray(VARIANT* vArray, long index, T** ppItem)
{
    if (vArray == NULL)
        return E_INVALIDARG;

    IUnknown* pUnk = NULL;
	HRESULT hr;
    try
    {
        hr = SafeArrayGetElement(vArray->parray, &index, reinterpret_cast<void*>(&pUnk));
		if(FAILED(hr))
			throw(hr);
        if (pUnk == NULL)
	        return E_POINTER;
        hr = pUnk->QueryInterface(ppItem);
		if(FAILED(hr))
			throw(hr);
		pUnk->Release();
		pUnk = NULL;
        VERIFY(*ppItem != NULL); // complain if we didn't succeed.
    }
    catch (HRESULT)
    {
		pUnk->Release();
		pUnk = NULL;
		VERIFY(false);
        return hr;
    }
    return S_OK;
};

inline void
CAcStCircle::ThrowIfFail(HRESULT hr)
{
    if (FAILED(hr))
        throw hr;
}

template<class Type>
HRESULT CAcStCircle::VariantFromArray(const Type *pArray,
                     VARIANT    *pVarArray,
                     long       count,
                     VARTYPE    vt,
                     bool       bCreateVariantArray)
{
    try {
        if (
            ((vt & VT_TYPEMASK) == VT_BSTR)  // ((vt & VT_BSTR) && (vt != VT_UNKNOWN)) ||
            || NULL == pVarArray
            || NULL == pArray )
            throw E_INVALIDARG;

        ThrowIfFail(SafeArrayFromArray(pArray, pVarArray->parray, count, vt,
                                       bCreateVariantArray));

        if (bCreateVariantArray)
            pVarArray->vt = VT_ARRAY | VT_VARIANT;
        else
            pVarArray->vt = VT_ARRAY | vt;

    }
    catch(HRESULT hr) {
        return hr;
    }

    return S_OK;
}

// Allocates and populates a safe array (vector) from an
// arbitary typed input vector. The VARTYPE
// parameter defines both the contents of the safe array and the
// type of the input array. The function will return a safearray of
// variants of type "vt" if bCreateVariantArray is "true".
// The number of objects in the array is specified in count. VT_BSTR
// is not supported; use StringArrayFromSafeArray.
template<class Type>
HRESULT CAcStCircle::SafeArrayFromArray(const Type   *pArray,
                       SAFEARRAY    *&psa,
                       long         count,
                       VARTYPE      vt,
                       bool         bCreateVariantArray )
{
    if (pArray == NULL)
        return NULL;

    HRESULT hr;
    void HUGEP *pData = NULL;

    psa = NULL;

    try {
        // Validate the input parameters
        if (((vt & VT_TYPEMASK) == VT_BSTR) ||
            NULL == pArray ||
            count <= 0) 
        {
            VERIFY(false); // Really shouldn't get here
            return E_INVALIDARG;
        }

        if (bCreateVariantArray)
        {
            // Allocate the safe array
            psa = SafeArrayCreateVector(VT_VARIANT, 0, count);
            if (NULL == psa)
                throw E_OUTOFMEMORY;

            CComVariant vElem;
            for (long i = 0; i < count; i++) {
                vElem = pArray[i];
                ThrowIfFail(SafeArrayPutElement(psa, &i,
                    reinterpret_cast < void *> (&vElem)));
                vElem.Clear();
            }
        }
        else if (vt == VT_UNKNOWN)
        {
            // Need to add each element to the safearray using SafeArrayPutElement so that the 
            // reference count gets properly incremented.
            psa = SafeArrayCreateVector(vt, 0, count);
            if (NULL == psa)
                throw E_OUTOFMEMORY;
            IUnknown* pUnk;
            for (long i = 0; i < count; i++) {
                pUnk = reinterpret_cast<IUnknown*>(pArray[i]);
                if (pUnk == NULL)
                    continue;
                ThrowIfFail(SafeArrayPutElement(psa, &i, pUnk)); // This will automatically AddRef
            }
        }
        else 
        {
            // The output array is not an array of variants, or IUnknown so simply copy the data using memcpy.
            // Allocate the safe array
            psa = SafeArrayCreateVector(vt, 0, count);
            if (NULL == psa)
                throw E_OUTOFMEMORY;
            // Access the array data pointer
            if (FAILED(hr = SafeArrayAccessData(psa, &pData)))
                throw hr;
            // Copy the data using memcopy
            size_t size = count * sizeof(Type);
            VERIFY(size > 0);
            memcpy(pData, pArray, size);
            // Release the array data pointer
            SafeArrayUnaccessData(psa);
        }
    }
    catch(HRESULT hres) {
        if (NULL != pData)
            SafeArrayUnaccessData(psa);

        if (NULL != psa)
            SafeArrayDestroy(psa);
        psa = NULL;

        return hres;
    }
    return S_OK;
}

