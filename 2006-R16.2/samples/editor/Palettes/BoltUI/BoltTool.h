//
//
// (C) Copyright 2003-2004 by Autodesk, Inc. 
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
// BoltTool.h : Declaration of the CBoltTool

#pragma once
#include "resource.h"       // main symbols

#include "stdafx.h"
#include "boltUI.h"
// CBoltTool
#define MAX_MENU_ENTRIES 4


#include "acadtoolimpl.h"
extern TCHAR szBoltToolName[MAX_PATH]; // Declared in the tools .cpp file
extern TCHAR szBoltImage[MAX_PATH];// -   -

class ATL_NO_VTABLE CBoltTool : 
	public CComCoClass<CBoltTool, &CLSID_CBoltTool>,
	public AcadToolImpl<CBoltTool,IBoltTool, &CLSID_CBoltTool,szBoltToolName,szBoltImage>
{
public:
	CBoltTool()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_BOLTTOOL)

	BEGIN_PERPROPDISPLAY_MAP2()
			PROP_DISP_ENTRY2(1, "AcPEXCtl.AcPePropertyEditorColor.16", NULL, NULL, NULL, NULL, 0x000000ff, FALSE, 1, 0)
			PROP_DISP_ENTRY2(2, "AcPEXCtl.AcPePropertyEditorLayer.16", NULL, NULL, NULL, NULL, 0x000000ff, FALSE, 1, 0)
			PROP_DISP_ENTRY2(3,"AcPEXCtl.AcPePropertyEditorEllipses.16",NULL,NULL,NULL,NULL,0x000000ff, FALSE, 1, 0)
	END_PERPROPDISPLAY_MAP2()

	BEGIN_FLYOUT_SPECIFIC_MAP()
			FLYOUT_ENTRY(1)
			FLYOUT_ENTRY(2)
			FLYOUT_ENTRY(3)
	END_FLYOUT_SPECIFIC_MAP()

    virtual HINSTANCE GetResourceInstance()
    {
		return _AtlBaseModule.GetResourceInstance();
    }		

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	long m_HeadSides;
	double m_HeadHeight;
	double m_ShaftLength;
	double m_ThreadLength;
	double m_ThreadWidth;
	double m_HeadDiameter;
	double m_ShaftDiameter;
	TCHAR m_MaterialName[128];
	TCHAR m_PartNumber[128];
    
    
	STDMETHOD(get_HeadSides)(LONG* pVal);
	STDMETHOD(put_HeadSides)(LONG newVal);
	STDMETHOD(get_HeadHeight)(DOUBLE* pVal);
	STDMETHOD(put_HeadHeight)(DOUBLE newVal);
	STDMETHOD(get_ShaftLength)(DOUBLE* pVal);
	STDMETHOD(put_ShaftLength)(DOUBLE newVal);
	STDMETHOD(get_ThreadLength)(DOUBLE* pVal);
	STDMETHOD(put_ThreadLength)(DOUBLE newVal);
	STDMETHOD(get_ThreadWidth)(DOUBLE* pVal);
	STDMETHOD(put_ThreadWidth)(DOUBLE newVal);
	STDMETHOD(get_HeadDiameter)(DOUBLE* pVal);
	STDMETHOD(put_HeadDiameter)(DOUBLE newVal);
	STDMETHOD(get_ShaftDiameter)(DOUBLE* pVal);
	STDMETHOD(put_ShaftDiameter)(DOUBLE newVal);
	STDMETHOD(get_MaterialName)(BSTR *pVal);
	STDMETHOD(put_MaterialName)(BSTR newVal);
	STDMETHOD(get_PartNumber)(BSTR*pVal);
	STDMETHOD(put_PartNumber)(BSTR newVal);
	STDMETHOD(executeCallback)();
	STDMETHOD(dropCallback)(AcDbEntity *pDropEntity);
	STDMETHOD(New)();
	STDMETHOD(BeginMultipleEdit)( VARIANT tools,VARIANT stockToolIds);
	STDMETHOD(get_EditMode) (/*[out, retval]*/ long* pVal);
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

};

OBJECT_ENTRY_AUTO(__uuidof(CBoltTool), CBoltTool)
