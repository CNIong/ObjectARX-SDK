//
// (C) Copyright 1998, 2002 by Autodesk, Inc. 
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
// 04/07/98: Alan Quinton: Creation
#ifndef _OPMDIALOG_H
#define _OPMDIALOG_H

/////////////////////////////////////////////////////////////////////
// IOPMPropertyDialog
/////////////////////////////////////////////////////////////////////
DEFINE_GUID(IID_IOPMPropertyDialog, 0x8B384029, 0xACB0, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384029-ACB0-11D1-A2B4-080009DC639A") IOPMPropertyDialog : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IOPMPropertyDialog methods ***
    STDMETHOD(DoModal)(THIS_ /*[in/out]*/ BSTR* propValueString, /*[in]*/AcDbObjectIdArray* ObjectIdArray) PURE;
};

typedef IOPMPropertyDialog FAR* LPPROPERTYDIALOG;

/////////////////////////////////////////////////////////////////////
// IOPMPropertyDialog2
/////////////////////////////////////////////////////////////////////
// {9F82F13D-C850-444a-980C-B5EDC6679F4A}
DEFINE_GUID(IID_IOPMPropertyDialog2, 0x9f82f13d, 0xc850, 0x444a, 0x98, 0xc, 0xb5, 0xed, 0xc6, 0x67, 0x9f, 0x4a);

interface DECLSPEC_UUID("9F82F13D-C850-444A-980C-B5EDC6679F4A")  IOPMPropertyDialog2 : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IOPMPropertyDialog2 methods ***
    STDMETHOD(DoModal)(THIS_ /*[in/out]*/ BSTR* propValueString, /*[in]*/VARIANT ObjectUnknownArray) PURE;
};

typedef IOPMPropertyDialog2 FAR* LPPROPERTYDIALOG2;

#endif //_OPMDIALOG_H
