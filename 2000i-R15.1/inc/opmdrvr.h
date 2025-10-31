//
// (C) Copyright 1997-1999 by Autodesk, Inc.
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
#ifndef _OPMDRVR_H
#define _OPMDRVR_H

// ICategorizeProperties methods
HRESULT AXAUTOEXP AcOpmMapPropertyToCategory(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispid, PROPCAT* ppropcat);
HRESULT AXAUTOEXP AcOpmGetCategoryName(IUnknown* pUnk, HINSTANCE hResInstance, ACAD_OPMPROPMAP_ENTRY* pMap, PROPCAT propcat, LCID lcid, BSTR* pbstrName);

// IPerPropertyBrowsing methods
HRESULT AXAUTOEXP AcOpmGetDisplayString(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BSTR *pBstr);
HRESULT AXAUTOEXP AcOpmMapPropertyToPage(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, CLSID *pClsid);
HRESULT AXAUTOEXP AcOpmGetPredefinedStrings(IUnknown* pUnk, HINSTANCE hResInstance, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, CALPOLESTR *pCaStringsOut, CADWORD *pCaCookiesOut);
HRESULT AXAUTOEXP AcOpmGetPredefinedValue(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, DWORD dwCookie, VARIANT *pVarOut);
 
 // IOPMPropertyExtension methods
HRESULT AXAUTOEXP AcOpmGetDisplayName(IUnknown* pUnk, HINSTANCE hResInstance, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BSTR *pBstr);
HRESULT AXAUTOEXP AcOpmEditable(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BOOL __RPC_FAR *bEditable);
HRESULT AXAUTOEXP AcOpmShowProperty(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BOOL *pShow);

#endif // _OPMDRVR_H
