//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//-----------------------------------------------------------------------------
//----- SimpleTool.cpp : Implementation of CSimpleTool
//-----------------------------------------------------------------------------
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "SimpleTool.h"
#include "actc_i.c"
#include "dbents.h"



TCHAR szToolName[MAX_PATH] = _T("Simple Tool");
TCHAR szToolImage[MAX_PATH] = _T("IDB_TOOL1");

static UINT m_nMenuIds[MAX_MENU_ENTRIES] = {0,0,0};

STDMETHODIMP CSimpleTool::New()
{
	m_StartX = 2.0;
	m_StartY = 2.0;
	m_StartZ = 0.0;
	m_EndX = 8.0;
	m_EndY = 8.0;
	m_EndZ = 0.0;
	_tcscpy_s(m_tcCmdName, _countof(m_tcCmdName), _T("_LINE"));
	return S_OK;
}

STDMETHODIMP CSimpleTool::get_CmdName(BSTR* pVal)
{
	CComBSTR bStr(m_tcCmdName);
	bStr.CopyTo(pVal);
	return S_OK;
}

STDMETHODIMP CSimpleTool::put_CmdName(BSTR pVal)
{
	CComBSTR bStr(pVal);
	COLE2T szCmdName(bStr);
	_tcscpy_s(m_tcCmdName, _countof(m_tcCmdName), szCmdName);
	return S_OK;
}

LPTSTR CSimpleTool::GetCmdName()
{
	return m_tcCmdName;
}

STDMETHODIMP CSimpleTool::get_StartX(DOUBLE* pVal)
{
	(*pVal) = m_StartX;
	return S_OK;
}

STDMETHODIMP CSimpleTool::put_StartX(DOUBLE newVal)
{
	m_StartX = newVal;
	return S_OK;
}

STDMETHODIMP CSimpleTool::get_StartY(DOUBLE* pVal)
{
	(*pVal) = m_StartY;
	return S_OK;
}

STDMETHODIMP CSimpleTool::put_StartY(DOUBLE newVal)
{
	m_StartY = newVal;
	return S_OK;
}

STDMETHODIMP CSimpleTool::get_StartZ(DOUBLE* pVal)
{
	(*pVal) = m_StartZ;
	return S_OK;
}

STDMETHODIMP CSimpleTool::put_StartZ(DOUBLE newVal)
{
	m_StartZ = newVal;
	return S_OK;
}

STDMETHODIMP CSimpleTool::get_EndX(DOUBLE* pVal)
{
	(*pVal) = m_EndX;
	return S_OK;
}

STDMETHODIMP CSimpleTool::put_EndX(DOUBLE newVal)
{
	m_EndX = newVal;
	return S_OK;
}

STDMETHODIMP CSimpleTool::get_EndY(DOUBLE* pVal)
{
	(*pVal) = m_EndY;
	return S_OK;
}

STDMETHODIMP CSimpleTool::put_EndY(DOUBLE newVal)
{
	m_EndY = newVal;
	return S_OK;
}

STDMETHODIMP CSimpleTool::get_EndZ(DOUBLE* pVal)
{
	(*pVal) = m_EndZ;
	return S_OK;
}

STDMETHODIMP CSimpleTool::put_EndZ(DOUBLE newVal)
{
	m_EndZ = newVal;
	return S_OK;
}

STDMETHODIMP CSimpleTool::executeCallback()
{
	AcGePoint3d ptStart(m_StartX, m_StartY, m_StartZ);
	AcGePoint3d ptEnd(m_EndX, m_EndY, m_EndZ);
	AcDbLine* pLine = new AcDbLine(ptStart, ptEnd);

	AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord *pBlockTableRecord;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
        AcDb::kForWrite);
    pBlockTable->close();

    AcDbObjectId lineId;
    pBlockTableRecord->appendAcDbEntity(lineId, pLine);

    pBlockTableRecord->close();
    pLine->close();

	return S_OK;
}

STDMETHODIMP CSimpleTool::dropCallback(AcDbEntity* pDropEntity)
{
	//::AfxMessageBox("Drop not supported at this time.");
	return E_NOTIMPL;
}

STDMETHODIMP CSimpleTool::Customize(/* [in] */ int nContextFlag,
							/* [in] */ DWORD hMenu,
							/* [in] */ UINT idCmdFirst,
						/* [in] */ UINT idCmdLast,
						/* [in] */ GUID *pPaletteId,
						/* [retval][out] */ DWORD *pFlag)
{
	int maxMenu = (idCmdLast - idCmdFirst) < MAX_MENU_ENTRIES ? (idCmdLast - idCmdFirst) : MAX_MENU_ENTRIES;
	AcTcPalette* pPalette = (AcTcPalette*)(AcTcGetManager()->FindItem(*pPaletteId));
	ASSERT(pPalette != NULL);

	TCHAR pszString[128];
	pPalette->GetName(pszString, 128);

	int i=0;	

	if (_tcscmp(pszString, _T("SimplePalette"))!= 0)
	{
		for (i=0; i < maxMenu ; i++)
		{
				m_nMenuIds[i] = 0;
		}
		return E_NOTIMPL;
	}

	for (i=0; i < maxMenu ; i++)
	{
			m_nMenuIds[i] = idCmdFirst + i;
	}

	CMenu* menu = new CMenu;
	if (menu->Attach(HMENU(hMenu))) 
	{	
		menu->InsertMenu(-1, MF_BYPOSITION, m_nMenuIds[0], _T("Menu&1"));
		menu->InsertMenu(-1, MF_BYPOSITION, m_nMenuIds[1], _T("Menu&2"));
		menu->InsertMenu(-1, MF_BYPOSITION, m_nMenuIds[2], _T("Menu&3"));
		menu->Detach();
	}
	delete menu;
	return S_OK;
}

STDMETHODIMP CSimpleTool::InvokeMenuCommand(/* [in] */ UINT idCmd,
									/* [in] */ GUID *pPaletteId,
									/* [in] */ DWORD hWnd,
								    /* [retval][out] */ DWORD *pFlag)
{
	if (idCmd == m_nMenuIds[0])
			::AfxMessageBox(_T("Menu1 chosen"));
	else if (idCmd == m_nMenuIds[1])
			::AfxMessageBox(_T("Menu2 chosen"));
	else if (idCmd == m_nMenuIds[2])
			::AfxMessageBox(_T("Menu3 chosen"));

	return S_OK;
}

// CSimpleTool

