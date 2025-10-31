//
//
// (C) Copyright 2003-2007 by Autodesk, Inc.
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

//-----------------------------------------------------------------------------
//----- SimpleTool.h : Declaration of the CSimpleTool
//-----------------------------------------------------------------------------

#pragma once
#include "resource.h"       // main symbols
#include "acadi.h"
#include "SimpleToolPalette_i.h"
#include "AcTc.h"
#include "AcTc_i.h"
#include "AcExtensionModule.h"
#include "AcadToolImpl.h"

#define MAX_MENU_ENTRIES 3

extern TCHAR szToolName[MAX_PATH];
extern TCHAR szToolImage[MAX_PATH];

// CSimpleTool

class ATL_NO_VTABLE CSimpleTool :
	public CComCoClass<CSimpleTool, &CLSID_SimpleTool>,
	public AcadToolImpl<CSimpleTool, ISimpleTool, &CLSID_SimpleTool, szToolName, szToolImage>
{
public:


DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLETOOL)



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
public:
	STDMETHOD(executeCallback)();
	STDMETHOD(dropCallback)(AcDbEntity *pEntity);
	STDMETHOD(get_CmdName)(BSTR* pVal);
	STDMETHOD(put_CmdName)(BSTR pVal);
	STDMETHOD(get_StartX)(DOUBLE* pVal);
	STDMETHOD(put_StartX)(DOUBLE newVal);
	STDMETHOD(get_StartY)(DOUBLE* pVal);
	STDMETHOD(put_StartY)(DOUBLE newVal);
	STDMETHOD(get_StartZ)(DOUBLE* pVal);
	STDMETHOD(put_StartZ)(DOUBLE newVal);
	STDMETHOD(get_EndX)(DOUBLE* pVal);
	STDMETHOD(put_EndX)(DOUBLE newVal);
	STDMETHOD(get_EndY)(DOUBLE* pVal);
	STDMETHOD(put_EndY)(DOUBLE newVal);
	STDMETHOD(get_EndZ)(DOUBLE* pVal);
	STDMETHOD(put_EndZ)(DOUBLE newVal);

	STDMETHOD(New)();
	TCHAR m_tcCmdName[256];
	LPTSTR GetCmdName();
	double m_StartX;
	double m_StartY;
	double m_StartZ;
	double m_EndX;
	double m_EndY;
	double m_EndZ;

	BEGIN_OPMPROP_MAP()
	END_OPMPROP_MAP()

	virtual HINSTANCE GetResourceInstance()
	{
		return _AtlBaseModule.GetResourceInstance();
	}

	BEGIN_PERPROPDISPLAY_MAP2()
	END_PERPROPDISPLAY_MAP2()

	BEGIN_FLYOUT_SPECIFIC_MAP()
//		FLYOUT_ENTRY(1)
		FLYOUT_ENTRY(2)
	END_FLYOUT_SPECIFIC_MAP()

// IAcadToolContextMenu members
	STDMETHOD(Customize)(/* [in] */ int nContextFlag,
							/* [in] */ DWORD hMenu,
							/* [in] */ UINT idCmdFirst,
						/* [in] */ UINT idCmdLast,
						/* [in] */ GUID *pPaletteId,
						/* [retval][out] */ DWORD *pFlag);

	STDMETHOD(InvokeMenuCommand)(/* [in] */ UINT idCmd,
									/* [in] */ GUID *pPaletteId,
									/* [in] */ DWORD hWnd,
								    /* [retval][out] */ DWORD *pFlag);
private:
//	UINT m_nMenuIds[MAX_MENU_ENTRIES];
};

OBJECT_ENTRY_AUTO(__uuidof(SimpleTool), CSimpleTool)
