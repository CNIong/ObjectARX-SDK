//
//
// (C) Copyright 2000-2002 by Autodesk, Inc. 
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
#include "StdArx.h"
#include "resource.h"
#include <afxdllx.h>
#include "PaletteSet.h"
#include "Palette.h"

// Global Palette Set and Palette
CMyPaletteSet  *pPaletteSet ;
CMyPalette *pPalette1;
CAdUiPalette *pPalette2;

HINSTANCE _hdllInstance =NULL ;

//Method to load/Save persistent data to CustPalette
void LoadPalette(CMyPalette *pPalette1);
void SavePalette(CMyPalette *pPalette1);

//Method to load/Save persistent data to CustPaletteSet
void LoadPaletteSet(CMyPaletteSet *pPaletteSet);
void SavePaletteSet(CMyPaletteSet *pPaletteSet);

// This command registers an ARX command.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);


// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS


////////////////////////////////////////////////////////////////////////////
//
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(PaletteDLL);

// Now you can use the CAcModuleResourceOverride class in
// your application to switch to the correct resource instance.
// Please see the ObjectARX Documentation for more details

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
        _hdllInstance = hInstance;
		// Extension DLL one time initialization
		PaletteDLL.AttachInstance(hInstance);
		InitAcUiDLL();
	} else if (dwReason == DLL_PROCESS_DETACH) {
		// Terminate the library before destructors are called
		PaletteDLL.DetachInstance();

	}
	return TRUE;    // ok
}



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


// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	// Create palette set
	pPaletteSet = new CMyPaletteSet;
	CRect rect(0, 0, 250, 500);
	pPaletteSet->Create("Palette",
		WS_OVERLAPPED | WS_DLGFRAME, 
		rect, 
		acedGetAcadFrame(), 
		PSS_EDIT_NAME | 
		PSS_PROPERTIES_MENU | 
		PSS_AUTO_ROLLUP |
		PSS_CLOSE_BUTTON
		);


	// Instantiate Palettes
	pPalette1 = new CMyPalette();  // custom palette
	pPalette2 = new CAdUiPalette(); 

//-------------Palette1-----------------------------------------
	pPalette1->Create(WS_CHILD | WS_VISIBLE,
		"Palette 1",
		pPaletteSet,
		PS_EDIT_NAME);

	//Add MFC controls to Palette1
	pPalette1->addControls();

	// Load Palette1's persistent data
	LoadPalette(pPalette1);

	// Add palette to palette set
	pPaletteSet->AddPalette(pPalette1);
	
//-----------End of Palette1 -----------------------------------

//-------------Palette2-----------------------------------------
	// Create dummy palette 2
	pPalette2->Create(WS_CHILD | WS_VISIBLE,
		"Palette 2",
		pPaletteSet,
		PS_EDIT_NAME);

	// Add palette 2 to palette set
	pPaletteSet->AddPalette(pPalette2);
//-----------End of Palette2 -----------------------------------

	// Finally show the palette set
	pPaletteSet->EnableDocking(CBRS_ALIGN_ANY);
	pPaletteSet->RestoreControlBar();

	// Load PaletteSet pesistent data
	LoadPaletteSet(pPaletteSet);

	CMDIFrameWnd* pAcadFrame = acedGetAcadFrame();
	pAcadFrame->ShowControlBar(pPaletteSet, TRUE, FALSE);

	if (pPaletteSet->GetOpacity() !=100)
		pPaletteSet->SetOpacity(100);
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	//Save Palette's persistent data
	SavePalette(pPalette1);
	//Save PaletteSet's persistent data
	SavePaletteSet(pPaletteSet);
	delete pPaletteSet;
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
	char cmdLocRes[65];

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

		CString sName = OLE2A(bstrName);
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

			CString sName = OLE2A(bstrName);
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
		TRACE("Exception\n");        
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

		MSXML::IXMLDOMNodePtr pNewNode = pDoc->createNode(varType, varName, "");;
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
		TRACE("Exception\n");        
		return FALSE;
	}

	return TRUE;
}

//------------------- Load / Save Palette Data -----------------------------
void LoadPalette(CMyPalette *pPalette1)
{
	MSXML::IXMLDOMDocumentPtr pDoc = NULL;
	HRESULT hr = pDoc.CreateInstance(MSXML::CLSID_DOMDocument);

	char *pRoam,paletteBuffer[MAX_PATH];
	BOOL bResult=acdbHostApplicationServices()->getRoamableRootFolder(pRoam);
	strcpy(paletteBuffer, pRoam);
	strcat(paletteBuffer, "TestPalette.xml");
	CComVariant var(paletteBuffer);

	VARIANT_BOOL bReturn = pDoc->load(var);
	if (bReturn == VARIANT_TRUE) // success!
	{
		MSXML::IXMLDOMNodePtr pNode;
		GetChildNode(pDoc->documentElement,"Palette",&pNode);
		pPalette1->Load(pNode);
	}
}

void SavePalette(CMyPalette *pPalette1)
{
	MSXML::IXMLDOMDocumentPtr pDoc = NULL;
	HRESULT hr = pDoc.CreateInstance(MSXML::CLSID_DOMDocument);

	char *pRoam,paletteBuffer[MAX_PATH];
	BOOL bResult=acdbHostApplicationServices()->getRoamableRootFolder(pRoam);
	strcpy(paletteBuffer, pRoam);
	strcat(paletteBuffer, "TestPalette.xml");
	CComVariant var(paletteBuffer);

	// create a root element
	MSXML::IXMLDOMNodePtr pNode;
	if (AddChildNode(pDoc, "Palette", MSXML::NODE_ELEMENT, &pNode) == FALSE)
		return;
	pPalette1->Save(pNode);
	hr = pDoc->save(var);
}

//------------------- Load / Save PaletteSet Data -----------------------------
void LoadPaletteSet(CMyPaletteSet *pPaletteSet)
{
	MSXML::IXMLDOMDocumentPtr pDoc = NULL;
	HRESULT hr = pDoc.CreateInstance(MSXML::CLSID_DOMDocument);

	// Get the file where the palette set's properties are saved
	char *pRoam,paletteBuffer[MAX_PATH];
	BOOL bResult=acdbHostApplicationServices()->getRoamableRootFolder(pRoam);
	strcpy(paletteBuffer, pRoam);
	strcat(paletteBuffer, "TestPaletteSet.xml");
	CComVariant var(paletteBuffer);

	VARIANT_BOOL bReturn = pDoc->load(var);
	if (bReturn == VARIANT_TRUE) // success!
	{
		MSXML::IXMLDOMNodePtr pNode;
		GetChildNode(pDoc->documentElement,"PS",&pNode);

		// Call the base class version of Load.
		// This would re-establish the properties of
		// the palette set
		pPaletteSet->Load(pNode);
	}
}

void SavePaletteSet(CMyPaletteSet *pPaletteSet)
{
	// Persist the palette set data in TestPaletteSet.xml
	MSXML::IXMLDOMDocumentPtr pDoc = NULL;
	HRESULT hr = pDoc.CreateInstance(MSXML::CLSID_DOMDocument);

	// Save pallete set into roaming profile
	char *pRoam,paletteBuffer[MAX_PATH];
	BOOL bResult=acdbHostApplicationServices()->getRoamableRootFolder(pRoam);
	strcpy(paletteBuffer, pRoam);
	strcat(paletteBuffer, "TestPaletteSet.xml");
	CComVariant var(paletteBuffer);

	// create a root element
	MSXML::IXMLDOMNodePtr pNode;

	if (AddChildNode(pDoc, "PS", MSXML::NODE_ELEMENT, &pNode) == FALSE)
		return;

	// This calls the base class implementation of Save 
	// The base class adds its properties (as XML nodes) into pNode
	pPaletteSet->Save(pNode);

	// Save the xml document
	hr = pDoc->save(var);

}

