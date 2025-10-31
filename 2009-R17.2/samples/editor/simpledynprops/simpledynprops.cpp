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
// SimpleDynProp.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f SimpleDynPropps.mk in the project directory.
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "resource.h"
#include "initguid.h"
#include "SimpleDynProps.h"
#include "SimpleProperty.h"
#include <comdef.h>

#include "rxdlinkr.h"
#include "dbents.h"
#include "accmd.h"
#include "CategorizedProperty.h"
#include "EnumProperty.h"
#include "xrecordmanager.h"
#include "adslib.h"



CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)

END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE;    // ok
}



//this class encapsulates attachment and detachment of
//the dynamic properties
class PropertyAdmin
{
    static bool m_bInitialized;
    static AcRxClass* m_pClass;
    static CComObject<CSimpleProperty>* m_pSimple;
    static CComObject<CCategorizedProperty>* m_pCategorized;
    static CComObject<CEnumProperty>* m_pEnum;
public:
    static void initialize();
    static void uninitialize();
    static bool isInitialized() { return m_bInitialized;}
};
bool PropertyAdmin::m_bInitialized = false;
CComObject<CSimpleProperty>* PropertyAdmin::m_pSimple = NULL;
CComObject<CCategorizedProperty>* PropertyAdmin::m_pCategorized = NULL;
CComObject<CEnumProperty>* PropertyAdmin::m_pEnum = NULL;
AcRxClass* PropertyAdmin::m_pClass = AcDbEntity::desc();

void PropertyAdmin::initialize()
{
    if (m_bInitialized)
        return;
    m_bInitialized = true;
    try 
    {
        CComPtr<IPropertyManager> pPropMan;
        if ((pPropMan.p = GET_OPMPROPERTY_MANAGER(m_pClass))==NULL)
            _com_issue_error(E_FAIL);
        _com_util::CheckError(CComObject<CSimpleProperty>::CreateInstance(&m_pSimple));
        m_pSimple->AddRef();
        _com_util::CheckError(CComObject<CCategorizedProperty>::CreateInstance(&m_pCategorized));
        m_pCategorized->AddRef();
        _com_util::CheckError(CComObject<CEnumProperty>::CreateInstance(&m_pEnum));
        m_pEnum->AddRef();
        _com_util::CheckError(pPropMan->AddProperty(m_pSimple));
        _com_util::CheckError(pPropMan->AddProperty(m_pCategorized));
        _com_util::CheckError(pPropMan->AddProperty(m_pEnum));
    }
    catch(const _com_error& )
    {
        uninitialize();                
        acutPrintf(_T("\nSimpleDynProps: initialize failed!!!\n"));
        return;
    }
}

void PropertyAdmin::uninitialize()
{
    if (!m_bInitialized)
        return;
    m_bInitialized = false;
    try
    {
        CComPtr<IPropertyManager> pPropMan;
        if ((pPropMan.p = GET_OPMPROPERTY_MANAGER(m_pClass))==NULL)
            _com_issue_error(E_FAIL);
        if (m_pSimple)
        {
            _com_util::CheckError(pPropMan->RemoveProperty(m_pSimple));
            m_pSimple->Release();
        }
        if (m_pCategorized)
        {
            _com_util::CheckError(pPropMan->RemoveProperty(m_pCategorized));
            m_pCategorized->Release();
        }
        if (m_pEnum)
        {
            _com_util::CheckError(pPropMan->RemoveProperty(m_pEnum));
            m_pEnum->Release();
        }
    }
    catch(const _com_error& )
    {
        acutPrintf(_T("\nSimpleDynProps: uninitialize failed!!!\n"));
    }
}
//assign the xrecord to the object
//the xrecord stores the value for the properties
//for now it looks like this:
//double,double,long
//
void assignData()
{
    if (!PropertyAdmin::isInitialized())
    {
        acutPrintf(_T("\nThe dynamic properties failed to intialize. Command is disabled."));
        return;
    }
    ads_name ss;
    if (acedSSGet(NULL,NULL,NULL,NULL,ss)!=RTNORM)
        return;
    long len=0;
    acedSSLength(ss,&len);
    ads_name ent;
    AcDbObjectId id;
    for (long i=0;i<len;i++){
        if (acedSSName(ss,i,ent)==RTNORM)
            if (acdbGetObjectId(id,ent)==Acad::eOk)
                XRecordManager::createDefaultData(id);
    }
    ads_ssfree(ss);
}
const TCHAR* cstrCommandGroup = _T("ASDK_SIMPLEDYNPROPS");

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
	switch (msg) {
	case AcRx::kInitAppMsg:
        //unlock the application
		acrxDynamicLinker->unlockApplication(pkt);
        acrxDynamicLinker->registerAppMDIAware(pkt);
        PropertyAdmin::initialize();
        acedRegCmds->addCommand(cstrCommandGroup,_T("assignData"),_T("assignData"),ACRX_CMD_MODAL,assignData);
		break;
	case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup(cstrCommandGroup);
        PropertyAdmin::uninitialize();
        break;
	}
	return AcRx::kRetOK;
}



