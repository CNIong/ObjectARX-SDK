// (C) Copyright 1990-2002 by Autodesk, Inc. 
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
// Written by Cyrille Fauvel
// Autodesk Developer Technical Services


// The AcRxDynPropMgr class is used internally by AcRxArxApp to map
// dynamic property classes to AcRxClass instances. ObjectARX applications
// that do not use AcRxArxApp may use AcRxDynPropMgr by dynamically
// instantiating it in the acrxEntryPoint method's AcRx::kInitAppMsg case,
// and deleting it in the AcRx::kUnloadAppMsg case.
//
// AcRxDynPropMgr uses the OPM_DYNPROP_OBJECT_ENTRY_AUTO macro for its
// mappings. Clients should declare one OPM_DYNPROP_OBJECT_ENTRY_AUTO macro
// for each mapping, i.e.:
//
//	OPM_DYNPROP_OBJECT_ENTRY_AUTO(CMyDynProp, AcDbLine) 
//	OPM_DYNPROP_OBJECT_ENTRY_AUTO(CMyDynProp, AcDbCircle) 
//
// These macros should appear in the dynamic property class header file
// after the class declaration.

//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
struct _OPM_DYNPROP_ENTRY {
    _ATL_CREATORFUNC *pfnCreateInstance ;
    const char *strCmd ;
    AcRxClass *pClass ;
    IDynamicProperty *pProp ;
} ;

#pragma section("OPM_DYNPROP$__a", read, shared)
#pragma section("OPM_DYNPROP$__z", read, shared)
#pragma section("OPM_DYNPROP$__m", read, shared)

extern "C" {
	__declspec(selectany) __declspec(allocate("OPM_DYNPROP$__a")) _OPM_DYNPROP_ENTRY* __pOpmObjMapEntryFirst =NULL ;
	__declspec(selectany) __declspec(allocate("OPM_DYNPROP$__z")) _OPM_DYNPROP_ENTRY* __pOpmObjMapEntryLast =NULL ;
}

#define OPM_DYNPROP_OBJECT_ENTRY_PRAGMA(class) __pragma(comment(linker, "/include:___pOpmObjMap_" #class)) ;

#define OPM_DYNPROP_OBJECT_ENTRY_AUTO(class, rxclass) \
	__declspec(selectany) _OPM_DYNPROP_ENTRY __OpmObjMap_##class = {class::_CreatorClass::CreateInstance, NULL, rxclass::desc (), NULL} ; \
	extern "C" __declspec(allocate("OPM_DYNPROP$__m")) __declspec(selectany) _OPM_DYNPROP_ENTRY* const __pOpmObjMap_##class = &__OpmObjMap_##class ; \
	OPM_DYNPROP_OBJECT_ENTRY_PRAGMA(class)

//-----------------------------------------------------------------------------
class AcRxDynPropManager {
	
public:
	AcRxDynPropManager () {
		_OPM_DYNPROP_ENTRY **m_ppOpmObjMapEntryFirst =&__pOpmObjMapEntryFirst + 1 ;
		_OPM_DYNPROP_ENTRY **m_ppOpmObjMapEntryLast =&__pOpmObjMapEntryLast ;
		for ( _OPM_DYNPROP_ENTRY **ppEntry =m_ppOpmObjMapEntryFirst ; ppEntry < m_ppOpmObjMapEntryLast ; ppEntry++ ) {
			if ( *ppEntry != NULL ) {
				CComPtr<IPropertyManager> pPropMan ;
				ATLASSERT( !((*ppEntry)->pClass && (*ppEntry)->strCmd) ) ;
				ATLASSERT( (*ppEntry)->pClass || (*ppEntry)->strCmd ) ;
				if ( (*ppEntry)->pClass != NULL ) {
					if ( (pPropMan =GET_OPMPROPERTY_MANAGER ((*ppEntry)->pClass)) == NULL )
						_com_issue_error (E_FAIL) ;
				} else {
					//----- Please note that command properties are not supported in this release
					ATLASSERT( FALSE ) ;
					if ( (pPropMan =GET_OPM_COMMAND_PROPERTY_MANAGER ((*ppEntry)->strCmd)) == NULL )
						_com_issue_error (E_FAIL) ;
				}
				_com_util::CheckError ((*ppEntry)->pfnCreateInstance (NULL, __uuidof (IDynamicProperty), (void **)&((*ppEntry)->pProp))) ;
				(*ppEntry)->pProp->AddRef () ;
				_com_util::CheckError (pPropMan->AddProperty ((*ppEntry)->pProp)) ;
			}
		}
	}
	virtual ~AcRxDynPropManager () {
		_OPM_DYNPROP_ENTRY **m_ppOpmObjMapEntryFirst =&__pOpmObjMapEntryFirst + 1 ;
		_OPM_DYNPROP_ENTRY **m_ppOpmObjMapEntryLast =&__pOpmObjMapEntryLast ;
		for ( _OPM_DYNPROP_ENTRY **ppEntry =m_ppOpmObjMapEntryFirst ; ppEntry < m_ppOpmObjMapEntryLast ; ppEntry++ ) {
			if ( *ppEntry != NULL ) {
				ATLASSERT( !((*ppEntry)->pClass && (*ppEntry)->strCmd) ) ;
				ATLASSERT( (*ppEntry)->pClass || (*ppEntry)->strCmd ) ;
				CComPtr<IPropertyManager> pPropMan ;
				if ( (*ppEntry)->pClass != NULL ) {
					if ( (pPropMan =GET_OPMPROPERTY_MANAGER ((*ppEntry)->pClass)) == NULL )
						_com_issue_error (E_FAIL) ;
				} else {
					if ( (pPropMan =GET_OPM_COMMAND_PROPERTY_MANAGER ((*ppEntry)->strCmd)) == NULL )
						_com_issue_error (E_FAIL) ;
				}
				if ( (*ppEntry)->pProp != NULL ) {
					_com_util::CheckError (pPropMan->RemoveProperty ((*ppEntry)->pProp)) ;
					(*ppEntry)->pProp->Release () ;
				}
			}
		}
	}
} ;
