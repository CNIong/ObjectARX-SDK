//
//
// (C) Copyright 1998-2002 by Autodesk, Inc. 
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
// AcStCircle.h : Declaration of the CAcStCircle

#pragma once
#include "resource.h"       // main symbols
#include "stdafx.h"

#include "CircleStandard.h"

// Field definition strings for plugin 
#define FIELD_PLUGIN_PLUGINNAME     "PluginName"
#define FIELD_PLUGIN_VERSION        "Version"
#define FIELD_PLUGIN_DESCRIPTION    "Description"
#define FIELD_PLUGIN_AUTHOR         "Author"
#define FIELD_PLUGIN_HREF           "HRef"
#define FIELD_PLUGIN_DWSNAME        "DWSName"
#define FIELD_PLUGIN_STATUS         "Status"

// Strings used for tags in XML filer
#define STRING_FILEREPORTS_TAG  "AcStFileReports"
#define STRING_AUDITREPORT_TAG  "AcStAuditReport"
#define STRING_FILEREPORT_TAG   "AcStFileReport"
#define STRING_DWSSECTION_TAG   "AcStDWSSection"
#define STRING_DWSFILE_TAG      "AcStDWSFile"
#define STRING_DWSPLUGIN_TAG    "AcStDWSPlugin"
#define STRING_DWSITEM_TAG      "AcStDWSItem"
#define STRING_PLUGININFOSECTION_TAG "AcStPluginInfoSection"
#define STRING_PLUGININFO_TAG   "AcStPluginInfo"
#define STRING_RESULTSSECTION_TAG "AcStResultsSection"
#define STRING_RESULTSPLUGIN_TAG "AcStResultsPlugin"
#define STRING_RESULT_TAG       "AcStResult"
#define STRING_RESULTSFIX_TAG   "AcStResultsFix"
#define STRING_RESULTPROPERTY_TAG "AcStResultProperty"

// CAcStCircle

class ATL_NO_VTABLE CAcStCircle : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAcStCircle, &CLSID_AcStCircle>,
	public IDispatchImpl<IAcStPlugin2, &IID_IAcStPlugin2, &LIBID_AcStMgr, 1, 0>
{
public:
    CAcStCircle();
    virtual ~CAcStCircle();

DECLARE_REGISTRY_RESOURCEID(IDR_ACSTCIRCLE)


BEGIN_COM_MAP(CAcStCircle)
	COM_INTERFACE_ENTRY(IAcStPlugin2)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

// IAcStPlugin2
public:
    STDMETHOD(get_Author)(BSTR *pVal);
    STDMETHOD(get_Description) (BSTR *pVal);
    STDMETHOD(get_HRef) (BSTR *pVal);
    STDMETHOD(get_Name) (BSTR *pVal);
    STDMETHOD(get_Version) (BSTR *pVal);
    STDMETHOD(get_Icon) (long *pVal);
    STDMETHOD(CheckSysvar) (BSTR sysvarName, 
		                    VARIANT_BOOL bGetAllFixes, 
                            VARIANT_BOOL *bPassFail);
    STDMETHOD(Initialize)(IAcStManager2 *pMgr);
    STDMETHOD(Clear)();
    STDMETHOD(SetupForAudit) (struct IAcadDatabase *pDb, 
                              BSTR szPathName, 
							  VARIANT stdNameArray, 
                              VARIANT stdPathArray, 
							  VARIANT stdDbArray);
    STDMETHOD(StampDatabase) (struct IAcadDatabase *pDb, VARIANT_BOOL *bStampIt);

    STDMETHOD(Start)(struct IAcStError* pErr );
    STDMETHOD(Next)();
    STDMETHOD(Done)(VARIANT_BOOL *bIsDone);
    STDMETHOD(GetError)(struct IAcStError** pErr);
    STDMETHOD(SetContext)(VARIANT objIdArray, VARIANT_BOOL bUseDb); 
    STDMETHOD(GetObjectFilter)(VARIANT* classNameArray);
    STDMETHOD(WritePluginInfo)(IDispatch * pPluginInfoSectionNode);
	STDMETHOD(GetRecommendedFix)(struct IAcStError* pError, struct IAcStFix** ppFix);
    STDMETHOD(GetAllFixes)(struct IAcStError* pError, VARIANT* fixArray, long* recommendedFixIndex);
    STDMETHOD(GetPropertyDiffs)(struct IAcStError* pError, 
                                struct IAcStFix* pFix, 
                                VARIANT* pPropNames,
                                VARIANT* pErrorValues,
                                VARIANT* pFixValues,
                                VARIANT* pFixableStatuses);

    STDMETHOD(FixError)(struct IAcStError* pError, struct IAcStFix* pFix, BSTR* pFailedReason);
    STDMETHOD(UpdateStatus)(struct IAcStError* pError);

	HRESULT FindRecommendedFixIndex(IAcStError* pError,	long& recommendedFixIndex);

// CComObjectRootEx overrides
public:
    STDMETHOD(FinalConstruct)();
    void FinalRelease();

// Helper functions
public:
	HRESULT writePluginInfoNode(IXMLDOMElement* pPluginInfoSectionElement,
                        const CComBSTR& szPluginName,
                        const CComBSTR& szVersion,
                        const CComBSTR& szDescription,
                        const CComBSTR& szAuthor,
                        const CComBSTR& szHRef,
                        const CComBSTR& szDwsName,
                        const CComBSTR& szStatus    //notes
                        );
	HRESULT AddElementToNode(IXMLDOMNode *pParentNode, BSTR &szNodeName, IXMLDOMNode **pNewNode);

	inline void ThrowIfFail(HRESULT hr);
	HRESULT VariantIsEmpty(const VARIANT *pVariant);
	HRESULT VariantIsNull(const VARIANT *Variant);
	HRESULT setErrorStatusFlags(IAcStError* pError, enum AcStResultStatus flags, bool bSet);
	HRESULT createNewFix(IAcStFix** ppFix, 
										const CString& csDescription,
										const CString& csStandardFileName);
	
	HRESULT getDatabase(IAcadDatabase *pDb, AcDbDatabase **pAcDb);
	template<typename T>
	inline HRESULT getIUnknownElementFromSafeArray(VARIANT* vArray, long index, T** ppItem);

	HRESULT getStringElementFromSafeArray(VARIANT* vArray, long index, CString& csOut);
	// Allocates and returns a variant containing a vector of VARIANTS
	HRESULT VariantFromArray(const CStringArray &array,
                     VARIANT            *pVarArray,
                     bool               bCreateVariantArray = false);
	// Allocates and returns a SAFEARRAY of VT_BSTR or VT_VARIANTs containing
	HRESULT SafeArrayFromArray(const CStringArray &strings,
                       SAFEARRAY          *&psa,
                       bool               bCreateVariantArray = false);
	// AcDb selection method
	Acad::ErrorStatus getEntitiesOfTypeFromComDb(IAcadDatabase*& pComDb,
								AcRxClass*& pDesc, 
								AcDbObjectIdArray& ids);

	template<class Type>
    HRESULT VariantFromArray(const Type *pArray,
                     VARIANT    *pVarArray,
                     long       count,
                     VARTYPE    vt,
                     bool       bCreateVariantArray = false);
	template<class Type>
    HRESULT SafeArrayFromArray(const Type   *pArray,
                       SAFEARRAY    *&psa,
                       long         count,
                       VARTYPE      vt,
                       bool         bCreateVariantArray = false);

// Class member variables
private:
	CComPtr<IAcStManager2>	m_pAcStMgr;
	CComPtr<IAcStError>		m_pError;
	CComPtr<IAcStPlugin2>	m_pPlugin;
	CComPtr<IAcadDatabase>	m_pComDwgDb;
	AcDbDatabase*			m_pDwgDb;
	long                  m_curIndex;
	long					m_recommendedFixIndex;
	AcDbObjectIdArray		m_objIdsToCheck;
	AcDbObjectIdArray		m_objIdsFix;

	AcRxClass* m_pDesc;

	// Used to cache radius and color properties of circles
	class circleCache {
	public:
		double radius;
		long color;
		CString standardFileName;
		FixPointer pFix;
	};
	AcArray<circleCache> m_circleCacheArray;

};

OBJECT_ENTRY_AUTO(__uuidof(AcStCircle), CAcStCircle)
