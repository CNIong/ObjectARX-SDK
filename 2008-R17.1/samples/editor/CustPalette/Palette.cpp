// (C) Copyright 2000-2006 by Autodesk, Inc. 
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

// Palette.cpp : Initialization functions
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "resource.h"
#include "PaletteSet.h"
#include "Palette.h"
#include "InspPalette.h"



// Global Palette Set Instance
CMyPaletteSet  *pPaletteSet ;

HINSTANCE _hdllInstance =NULL ;

// Callback for the command "PALETTESHOW"
void paletteShow();

// This command registers an ARX command.
void AddCommand(const TCHAR* cmdGroup, const TCHAR* cmdInt, const TCHAR* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);


// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG


/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg) {
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		InitApplication();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;
}

// Command implementation for "PALETTESHOW"
void paletteShow()
{
	CMDIFrameWnd* pAcadFrame = acedGetAcadFrame();
	// If the paletteset is already created, show it
	if(pPaletteSet)
	{
		pAcadFrame->ShowControlBar(pPaletteSet, TRUE, FALSE);
		return;
	}

	// If paletteset not created, create new palette set
	CDataPalette *pPalette1;
	CInspPalette *pPalette2;

	pPaletteSet = new CMyPaletteSet;
	CRect rect(0, 0, 250, 500);
	pPaletteSet->Create(_T("Custom PaletteXXX"),
		WS_OVERLAPPED | WS_DLGFRAME, 
		rect, 
		acedGetAcadFrame(), 
		PSS_EDIT_NAME | 
		PSS_PROPERTIES_MENU | 
		PSS_AUTO_ROLLUP |
		PSS_CLOSE_BUTTON
		);


	// Instantiate Palettes
	pPalette1 = new CDataPalette();  // data palette
	pPalette2 = new CInspPalette(); // Inpector palette

	//-------------Palette1-----------------------------------------
	pPalette1->Create(WS_CHILD | WS_VISIBLE,
		_T("Palette 1"),
		pPaletteSet,
		PS_EDIT_NAME);

	// Load Palette1's persistent data
	// LoadPalette(pPalette1);

	// Add palette to palette set
	pPaletteSet->AddPalette(pPalette1);

	//-----------End of Palette1 -----------------------------------

	//-------------Palette2-----------------------------------------
	// Create the palette which has the property inspector
	pPalette2->Create(WS_CHILD | WS_VISIBLE,
		_T("Palette 2"),
		pPaletteSet,
		PS_EDIT_NAME);

	// Add palette 2 to palette set
	pPaletteSet->AddPalette(pPalette2);
	//-----------End of Palette2 -----------------------------------

	// Finally show the palette set
	pPaletteSet->EnableDocking(CBRS_ALIGN_ANY);
	pPaletteSet->RestoreControlBar();

	// Load PaletteSet pesistent data
	pPaletteSet->LoadPaletteSet();

	pAcadFrame->ShowControlBar(pPaletteSet, TRUE, FALSE);

	if (pPaletteSet->GetOpacity() !=100)
		pPaletteSet->SetOpacity(100);

	// Change the title of the paletteset
	pPaletteSet->SetName(_T("Custom Palette"));
}

// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	// Add a command to show the paletteset
	AddCommand(_T("ASDK"), _T("PALETTESHOW"), _T("PALETTESHOW"), ACRX_CMD_MODAL, paletteShow);

	// Register the COM Server upon loading
	if ( FAILED(::DllRegisterServer ()) )
		acutPrintf (_T("Failed to register COM server.\n")) ;
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// Unregister commands
	acedRegCmds->removeGroup(_T("ASDK"));

	// Destroy the paletteset
	if(pPaletteSet)
	{
		pPaletteSet->DestroyWindow();
		delete pPaletteSet;
	}
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const TCHAR* cmdGroup, const TCHAR* cmdInt, const TCHAR* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
	TCHAR cmdLocRes[65];

	// If idLocal is not -1, it's treated as an ID for
	// a string stored in the resources.
	if (idLocal != -1) {

		// Load strings from the string table and register the command.
		::LoadString(_hdllInstance, idLocal, cmdLocRes, 64);
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

	} else
		// idLocal is -1, so the 'hard coded'
		// localized function name is used.
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}

//Utility functions to add and get the child node from the parent XML-DOM node
BOOL GetChildNode(MSXML::IXMLDOMNode* pNode, 
							  LPCTSTR pszNodeName, 
							  MSXML::IXMLDOMNode** ppChild)
{
	try {
		ASSERT(ppChild != NULL);
		if (ppChild == NULL)
			return FALSE;

		*ppChild = NULL;

		ASSERT(pNode != NULL && pszNodeName != NULL);
		if (pNode == NULL || pszNodeName == NULL)
			return FALSE;

		USES_CONVERSION;

		CComBSTR bstrName;
		pNode->get_nodeName(&bstrName);

		CString sName = OLE2T(bstrName);
		if (sName.CompareNoCase(pszNodeName) == 0) {
			*ppChild = pNode;
			// AddRef before returning
			if (*ppChild != NULL)
				(*ppChild)->AddRef();
			return TRUE;
		}
		// Get the named child element from the list of children
		//
		MSXML::IXMLDOMNodeListPtr pChildren; 
		pNode->get_childNodes(&pChildren);
		ASSERT(pChildren != NULL);
		if (pChildren == NULL) {
			ASSERT(FALSE);
			return FALSE;
		}

		int nCount = pChildren->Getlength();
		if (nCount < 1) {
			// No children
			return FALSE;
		}

		for (long i=0; i<nCount; i++) {
			MSXML::IXMLDOMNodePtr pNode;
			pChildren->get_item(i, &pNode);
			ASSERT(pNode != NULL);

			CComBSTR bstrName;
			pNode->get_nodeName(&bstrName);

			CString sName = OLE2T(bstrName);
			if (sName.CompareNoCase(pszNodeName) == 0) {
				*ppChild = pNode.GetInterfacePtr();
				// AddRef before returning
				if (*ppChild != NULL)
					(*ppChild)->AddRef();
				return TRUE;
			}
		}
	} catch (_com_error  &e) {
		ASSERT(FALSE);
		SetLastError(e.Error());
		return FALSE;
	} catch (...) {
		TRACE(_T("Exception\n"));        
		return FALSE;
	}

	// Named child not found
	return FALSE;
}

BOOL AddChildNode(MSXML::IXMLDOMNode* pNode, LPCTSTR pszChildNodeName,
							  short nNodeType, MSXML::IXMLDOMNode** ppChild)
{
	USES_CONVERSION;

	try {
		ASSERT(ppChild != NULL);
		if (ppChild == NULL)
			return FALSE;

		*ppChild = NULL;

		ASSERT(pNode != NULL && pszChildNodeName != NULL );
		if (pNode == NULL || pszChildNodeName == NULL)
			return FALSE;

		CString strName(pszChildNodeName);

		MSXML::IXMLDOMDocumentPtr pDoc;
		MSXML::DOMNodeType type;
		pNode->get_nodeType(&type);
		if (type == MSXML::NODE_DOCUMENT)
			pDoc = pNode;
		else {
			pNode->get_ownerDocument(&pDoc);
			ASSERT( pDoc != NULL);
			if (pDoc == NULL)
				return FALSE;
		}

		_variant_t varType(nNodeType);
		_bstr_t varName(strName);//pszChildNodeName);

		MSXML::IXMLDOMNodePtr pNewNode = pDoc->createNode(varType, varName, _T(""));;
		*ppChild = pNewNode.GetInterfacePtr();
		// AddRef before returning
		if (*ppChild != NULL)
			(*ppChild)->AddRef();

		pNode->appendChild(*ppChild);
	} catch (_com_error  &e) {
		ASSERT(FALSE);
		SetLastError(e.Error());
		return FALSE;
	} catch (...) {
		TRACE(_T("Exception\n"));        
		return FALSE;
	}

	return TRUE;
}

