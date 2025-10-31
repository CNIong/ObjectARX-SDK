// (C) Copyright 2005-2007 by Autodesk, Inc. 
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
// InspData.cpp : Implementation of CInspData
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "InspData.h"



// CInspData
STDMETHODIMP CInspData::get_FileName(BSTR* pVal)
{
	return S_OK;
}

STDMETHODIMP CInspData::put_FileName(BSTR newVal)
{
	// TODO: Add your implementation code here
	return S_OK;
}

// IDWGPreview
STDMETHODIMP CInspData::GetFileName(BSTR *fileName)
{
	if (fileName==NULL)
		return E_POINTER;
	*fileName = ::SysAllocString(L"C:\\Program Files\\AutoCAD 2008\\Sample\\db_samp.dwg");
	return S_OK;
}

STDMETHODIMP CInspData::get_Preview(BOOL* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CInspData::put_Preview(BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

