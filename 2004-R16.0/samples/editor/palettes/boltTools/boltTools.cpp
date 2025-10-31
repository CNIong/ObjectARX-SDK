//
//
// (C) Copyright 2002 by Autodesk, Inc. 
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
// BoltTools.cpp : Initialization functions
// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f BoltToolsps.mk in the project directory.
#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include <initguid.h>
#include "BoltTools.h"
#include <afxdllx.h>
#include "BoltTools_i.c"
#include "BoltTool.h"
#include "boltproperties.h"
#include "direct.h"

//#include "AcTcUiToolPaletteSet.h"
#include "actc.h"

HINSTANCE _hdllInstance =NULL ;

// This command registers an ARX command.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);
void initBoltCatalogs();
void initBoltCatalogs2();
void Initialize();

// Forward declaration of some XML utility functions.
BOOL                    GetChildNodeValue   (MSXML::IXMLDOMNode* pNode,
                                             LPCTSTR pszNodeName, 
                                             CString& sValue); 
BOOL                    GetChildNode        (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszNodeName, 
                                             MSXML::IXMLDOMNode** ppChild);
BOOL                    AddChildNode        (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszChildNodeName, 
                                             short nNodeType,
                                             MSXML::IXMLDOMNode** ppChild);
BOOL                    RemoveChildren      (MSXML::IXMLDOMNode* pNode);   

BOOL                    GetAttributeValue   (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszAttName, 
                                             CString& sValue);
BOOL                    GetAttributeValue   (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszAttName, 
                                             double& fValue);
BOOL                    GetAttributeValue   (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszAttName, 
                                             long& lValue);
BOOL                    GetAttributeValue   (MSXML::IXMLDOMNode* pNode, 
                                             LPCTSTR pszAttName, 
                                             GUID& guid);

BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              long lValue);
BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              const GUID& guid);

BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              const CString& sValue);
BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              double fValue);

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_BoltTool, CBoltTool)
END_OBJECT_MAP()

////////////////////////////////////////////////////////////////////////////
//
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(BoltToolsDLL);

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
		BoltToolsDLL.AttachInstance(hInstance);
		InitAcUiDLL();
		_Module.Init(ObjectMap, hInstance, &LIBID_asdkBOLTTOOLSLib);
		DisableThreadLibraryCalls(hInstance);
		Initialize();
	} else if (dwReason == DLL_PROCESS_DETACH) {
		// Terminate the library before destructors are called
		BoltToolsDLL.DetachInstance();
		_Module.Term();

	}
	return TRUE;    // ok
}


/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	// Registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	return _Module.UnregisterServer(TRUE);
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
	if (FAILED(DllRegisterServer()))
        acutPrintf("\nFailed to register.");//dbx safe
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT
	//}}AFX_ARX_INIT

	initBoltCatalogs(); // Only called when this module is explicity loaded into AutoCAD with the ARX or APPLOAD commands.
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	//}}AFX_ARX_EXIT
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

BOOL GetAttribute(MSXML::IXMLDOMNode* pNode, 
                  LPCTSTR pszAttName, 
                  MSXML::IXMLDOMAttribute** ppChild);

// Extracts a named child from the children of an element
//
// pNode [in]:          Node from which to extract the child
// pszNodeName [in]:    Child node name to extract
// ppChild [out]:       Output pointer to receive the extracted child node
//
// Returns TRUE on success. FALSE if the named child is not found or on 
// failure.
//
BOOL GetChildNode(MSXML::IXMLDOMNode* pNode, 
                  LPCTSTR pszNodeName, 
                  MSXML::IXMLDOMNode** ppChild)
{
    try {
        if (ppChild == NULL)
            return FALSE;

        *ppChild = NULL;

        if (pNode == NULL || pszNodeName == NULL)
            return FALSE;

        USES_CONVERSION;

        // Get the named child element from the list of children
        //
        MSXML::IXMLDOMNodeListPtr pChildren; 
        pNode->get_childNodes(&pChildren);
        if (pChildren == NULL) {
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
        SetLastError(e.Error());
        return FALSE;
    } catch (...) {
        return FALSE;
    }
    // Named child not found
    return FALSE;
}


// Extracts a string value of a named child node
//
// pNode [in]:          Parent node
// pszNodeName [in]:    Child node name whose value is to be extracted
// sValue [out]:        Variable to receive the string
//
// Returns TRUE on success. FALSE if the named child node is not found or 
// on failure.
//
BOOL GetChildNodeValue(MSXML::IXMLDOMNode* pNode, 
                       LPCTSTR pszNodeName, 
                       CString& sValue)
{
    try {
        sValue.Empty();

        if (pNode == NULL || pszNodeName == NULL)
            return FALSE;

        USES_CONVERSION;

        MSXML::IXMLDOMNodePtr pChild;
        if (!GetChildNode(pNode, pszNodeName, &pChild)) {
            // Child not found
            return FALSE;
        }

        CComVariant val;
        HRESULT hr = S_OK;
        if (pChild->hasChildNodes()) {
            // Get the text child and then get the value so that we can get the 
            // text whether the node has the text directly or as cdata.
            //
            MSXML::IXMLDOMNodePtr pText;
            pChild->get_firstChild(&pText);
        
            hr = pText->get_nodeValue(&val);

        } else {
            // Get the node value directly
            hr = pChild->get_nodeValue(&val);
        }

        if (FAILED(hr))
            return FALSE;

        if (val.vt != VT_NULL) {
            // Node value data type should be string
            if (val.vt != VT_BSTR)
                return FALSE;

            sValue = OLE2A(val.bstrVal);
        }
    } catch (_com_error  &e) {
        SetLastError(e.Error());
        return FALSE;
    } catch (...) {
        return FALSE;
    }
    return TRUE;
}

BOOL AddChildNode(MSXML::IXMLDOMNode* pNode, 
             LPCTSTR pszChildNodeName,
             short nNodeType,
             MSXML::IXMLDOMNode** ppChild
            )
{
    USES_CONVERSION;

    try {
        if (ppChild == NULL)
            return FALSE;

        *ppChild = NULL;

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
            if (pDoc == NULL)
                return FALSE;
        }

         _variant_t varType(nNodeType);
         //TODO 
         _bstr_t varName(strName);//pszChildNodeName);
     
        MSXML::IXMLDOMNodePtr pNewNode = pDoc->createNode(varType, varName, "");;
        *ppChild = pNewNode.GetInterfacePtr();
        // AddRef before returning
        if (*ppChild != NULL)
            (*ppChild)->AddRef();

        pNode->appendChild(*ppChild);
    } catch (_com_error  &e) {
        SetLastError(e.Error());
        return FALSE;
    } catch (...) {
        return FALSE;
    }
    return TRUE;
}

//Removes all the children nodes for a given node
//pNode[in] - node whose children will be removed
//Returns TRUE if success, FALSE otherise
//
BOOL RemoveChildren(MSXML::IXMLDOMNode* pNode)
{
    try {
        if (pNode == NULL)
            return FALSE;

        MSXML::IXMLDOMNodeListPtr pChildren; 
        HRESULT hr = pNode->get_childNodes(&pChildren);
        if ( FAILED(hr) || (pChildren == NULL))
            return FALSE;

        MSXML::IXMLDOMNodePtr pChildNode = pChildren->nextNode();
        for (; pChildNode != NULL; pChildNode = pChildren->nextNode()){
            MSXML::IXMLDOMNodePtr pRemove = pNode->removeChild(pChildNode);
            // Release it
            pRemove = NULL;
        }
    } catch (_com_error  &e) {
        SetLastError(e.Error());
        return FALSE;
    } catch (...) {
        return FALSE;
    }
    return TRUE;
}

// Writes the specific command data to a generic tool...such as used in AutoCAD.
BOOL WriteGenericToolData(MSXML::IXMLDOMNode* pXmlElement, const CString& sMacro)
{
    USES_CONVERSION;
    
	MSXML::IXMLDOMNodePtr pNodeIn = pXmlElement;
	
	// .\Macro
    MSXML::IXMLDOMNodePtr pNode;
    HRESULT hr = AddChildNode(pNodeIn, "Macro", MSXML::NODE_ELEMENT, &pNode);

    // Command Text
	MSXML::IXMLDOMNodePtr pNodeText;
    hr = AddChildNode(pNode, "", MSXML::NODE_CDATA_SECTION, &pNodeText);
    pNodeText->put_text(A2OLE(sMacro));
    return TRUE;
}

// Utility to write a tools specific properties to a node in the XML file...
void WritePropertiesToCatalog(CBoltProperties props,MSXML::IXMLDOMNode* pParentNode)
{
	MSXML::IXMLDOMNodePtr pEntityNode;
	AddChildNode(pParentNode, "Entity", MSXML::NODE_ELEMENT, &pEntityNode);
	MSXML::IXMLDOMNodePtr pChildNode;
	AddChildNode(pEntityNode, "Part_Number", MSXML::NODE_ELEMENT, &pChildNode);
	SetAttributeValue(pChildNode, "Value", props.partNumber);
	// Add Color to Entity
	AddChildNode(pEntityNode, "Color", MSXML::NODE_ELEMENT, &pChildNode);
	SetAttributeValue(pChildNode, "Value", (long) props.color);
	SetAttributeValue(pChildNode, "Unspecified", (long)0);
	// Place the entity on a layer
	AddChildNode(pEntityNode, "Layer", MSXML::NODE_ELEMENT, &pChildNode);
	SetAttributeValue(pChildNode, "Value", props.layer);
	SetAttributeValue(pChildNode, "Unspecified", (long)0);
	
	AddChildNode(pParentNode, "Bolt", MSXML::NODE_ELEMENT, &pEntityNode);
	MSXML::IXMLDOMNodePtr pChildNode2;

	// Add Material to Entity
	AddChildNode(pEntityNode, "Material", MSXML::NODE_ELEMENT, &pChildNode);
	SetAttributeValue(pChildNode, "Value", props.materialName);
	
	AddChildNode(pEntityNode, "Head_Diameter", MSXML::NODE_ELEMENT, &pChildNode2);
	SetAttributeValue(pChildNode2, "Value", props.headDiameter);

	AddChildNode(pEntityNode, "Head_Sides", MSXML::NODE_ELEMENT, &pChildNode2);
	SetAttributeValue(pChildNode2, "Value", (long) props.headSides);

	AddChildNode(pEntityNode, "Head_Height", MSXML::NODE_ELEMENT, &pChildNode2);
	SetAttributeValue(pChildNode2, "Value",  props.headHeight);

	AddChildNode(pEntityNode, "Shaft_Length", MSXML::NODE_ELEMENT, &pChildNode2);
	SetAttributeValue(pChildNode2, "Value", props.shaftLength);

	AddChildNode(pEntityNode, "Shaft_Diameter", MSXML::NODE_ELEMENT, &pChildNode2);
	SetAttributeValue(pChildNode2, "Value", props.shaftDiameter);

	AddChildNode(pEntityNode, "Thread_Length", MSXML::NODE_ELEMENT, &pChildNode2);
	SetAttributeValue(pChildNode2, "Value", props.threadLength);

	AddChildNode(pEntityNode, "Thread_Width", MSXML::NODE_ELEMENT, &pChildNode2);
	SetAttributeValue(pChildNode2, "Value", props.threadWidth);
}

AcTcTool *GetToolFromPalette(AcTcPalette* pPalette,int index,MSXML::IXMLDOMNode*& pParentNode)
{
	// Get the Tool.
	AcTcTool *pTool = (AcTcTool*) pPalette->GetChild(index);
	
	// Get the data node...returned in pParentNode
	IUnknown* pUnk = NULL;
	pTool->GetToolData(&pUnk);
	HRESULT hr = pUnk->QueryInterface(MSXML::IID_IXMLDOMNode, (void**) &pParentNode);
	pUnk->Release();
	return pTool;
}

char modulePath[MAX_PATH];
CString imagePath;
const char *pCatalogPath;

// Called from DllMain to initialize some tool-wide path strings.
void Initialize()
{
	HMODULE moduleHandle=GetModuleHandle("asdkBoltTools.arx");
	DWORD res=GetModuleFileName(moduleHandle,modulePath,MAX_PATH);
	
	// The location of the actual images should be roamable, and in the profiles directory, so:
	BOOL bResult=acdbHostApplicationServices()->getRoamableRootFolder(pCatalogPath);
}

// Called to actually create the catalogs, and the tools on each.
void initBoltCatalogs()
{
	acutPrintf("\nCreating Catalogs and Palettes in the Current Profile.\n");
	
	// Set the module handle so we can use the resources within this ARX for the tool icons.
	CAcModuleResourceOverride resourceOverride;
	
	// {63403065-9629-47e4-ADB0-A2BDBE256408}
	const GUID StockToolId = { 0x63403065, 0x9629, 0x47e4, { 0xad, 0xb0, 0xa2, 0xbd, 0xbe, 0x25, 0x64, 0x8 } };
	
	// This is the ID of the Generic Stock Tool distributed with AutoCAD in the file AcTcTools.atc.
	// 2AE7120B-CEE4-47A5-9B50-EF9F3ADE24AC
	const GUID GenericStockToolId = {0x2ae7120b,0xcee4,0x47a5,{0x9b,0x50,0xef,0x9f,0x3a,0xde,0x24,0xac}};
	
	GUID guid;
	
	HRESULT hResult;
	BOOL bResult;
    		
	// Create the stock tool catalog entry:
	AcTcStockTool *pStockTool=new AcTcStockTool;

	bResult=pStockTool->SetID(&StockToolId);
	bResult=pStockTool->SetComClassID(CLSID_BoltTool);
	
	// Set the module file name for the Stock Tool's COM interface object: modulePath set in initialize()...
	bResult=pStockTool->SetModuleFileName(modulePath);
		
	bResult=pStockTool->Save((CString) pCatalogPath+"\\Support\\RegisteredTools\\BoltStockTool.atc");

	// Create the tool catalog entry.

	AcTcCatalog *pCatalog=new AcTcCatalog;
	hResult=CoCreateGuid(&guid);
	bResult=pCatalog->SetID(&guid);
	bResult=pCatalog->SetName("Acme Bolt Catalog");

	// First Palette...
	AcTcPalette *pPalette = new AcTcPalette;
	hResult=CoCreateGuid(&guid);
	bResult=pPalette->SetID(&guid);
	bResult=pPalette->SetName("Stainless");
	pCatalog->AddChild(pPalette);

	// Second Palette...
	AcTcPalette *pPalette2 = new AcTcPalette;
	hResult=CoCreateGuid(&guid);
	bResult=pPalette2->SetID(&guid);
    bResult=pPalette2->SetName("Galvanized");
	pCatalog->AddChild(pPalette2);

	// Add 3 basic tools to each palette.
	for(int c=0;c<3;c++)
	{	
		AcTcTool* pTool = new AcTcTool();
		hResult=CoCreateGuid(&guid);
		bResult=pTool->SetID(&guid);
		
		// Attach the tool icon to the tool...
		AcTcImageList *pList=pTool->GetImageList();
		AcTcImage image;
		CBitmap bitmap;
		bitmap.LoadBitmap("IDB_BOLTIMAGE");
		image.Load(bitmap.operator HBITMAP());
		pList->Add(&image);
		
		bResult=pTool->SetStockToolID(&StockToolId);
		pPalette->AddChild(pTool);

		AcTcTool* pTool2 = new AcTcTool();
		hResult=CoCreateGuid(&guid);
		bResult=pTool2->SetID(&guid);
		
		// Attach the tool icon to the tool...
		AcTcImageList *pList2=pTool2->GetImageList();
		pList2->Add(&image);
		
		bResult=pTool2->SetStockToolID(&StockToolId);
		pPalette2->AddChild(pTool2);
	}
	
    // Add a basic COMMAND tool to the first catalog to demonstrate how to create generic tools to run Acad commands:
	AcTcTool* pTool = new AcTcTool();
	hResult=CoCreateGuid(&guid);
	bResult=pTool->SetID(&guid);
	
	// Attach the red tool icon to this tool.
	AcTcImageList *pList=pTool->GetImageList();	
	AcTcImage image;
	CBitmap bitmap;
	bitmap.LoadBitmap("IDB_BOLTJIG");
	image.Load(bitmap.operator HBITMAP());
	pList->Add(&image);
		
	bResult=pTool->SetStockToolID(&GenericStockToolId);
	pPalette->AddChild(pTool);
	
	bResult=pCatalog->Save((CString)pCatalogPath+"\\Support\\ToolPalette\\BoltTool.atc");

	// Re-open the catalog so we can write the basic tools out.

	bResult=pCatalog->Reset();
	bResult=pCatalog->Load((CString)pCatalogPath+"\\Support\\ToolPalette\\BoltTool.atc");
	pPalette = (AcTcPalette*) pCatalog->GetChild(0);
	pPalette2 = (AcTcPalette*) pCatalog->GetChild(1);
	
	CBoltProperties props;
	
	MSXML::IXMLDOMNode* pParentNode = NULL;

	// Tool 0
	pTool = GetToolFromPalette(pPalette,0,pParentNode);
	RemoveChildren(pParentNode);
	bResult=pTool->SetName(_T("S10-3-3-5"));
	
	props.color=256;// By Layer
	strcpy(props.layer,"0");

	props.headDiameter=5.0f;
	props.headHeight=2.0f;
	props.headSides=6;
	strcpy(props.materialName,"Stainless");
	strcpy(props.partNumber,"S10-3-3-5");//sl,tl,sd,hd
	props.shaftDiameter=3.0f;
	props.shaftLength=10.0f;
	props.threadLength=3.0f;
	props.threadWidth=0.2f;
	WritePropertiesToCatalog(props,pParentNode);
	
	// Write the tool to the Galvanized palette
	pTool = GetToolFromPalette(pPalette2,0,pParentNode);
	RemoveChildren(pParentNode);
	bResult=pTool->SetName(_T("G10-3-3-5"));
	strcpy(props.partNumber,"G10-3-3-5");//sl,tl,sd,hd
	strcpy(props.materialName,"Galvanized");	
	WritePropertiesToCatalog(props,pParentNode);

	// Tool1
	pTool = GetToolFromPalette(pPalette,1,pParentNode);
	RemoveChildren(pParentNode);
	bResult=pTool->SetName(_T("S8-2-3-5"));
	strcpy(props.materialName,"Stainless");
	props.shaftLength=8.0f;
	props.threadLength=2.0f;
	strcpy(props.partNumber,"S8-2-3-5");//sl,tl,sd,hd
	WritePropertiesToCatalog(props,pParentNode);

	// Write the tool to the Galvanized palette
	pTool = GetToolFromPalette(pPalette2,1,pParentNode);
	RemoveChildren(pParentNode);
	bResult=pTool->SetName(_T("G8-2-3-5"));
	strcpy(props.partNumber,"G8-2-3-5");//sl,tl,sd,hd	
	strcpy(props.materialName,"Galvanized");	
	WritePropertiesToCatalog(props,pParentNode);

	// Tool2
	pTool = GetToolFromPalette(pPalette,2,pParentNode);
	RemoveChildren(pParentNode);
	bResult=pTool->SetName(_T("S9-3-3-7"));
	strcpy(props.materialName,"Stainless");
	props.shaftLength=9.0f;
	props.threadLength=3.0f;
	props.headDiameter=7.0f;
	strcpy(props.partNumber,"S9-3-3-7");//sl,tl,sd,hd
	WritePropertiesToCatalog(props,pParentNode);
	
	// Write the tool to the Galvanized palette
	pTool = GetToolFromPalette(pPalette2,2,pParentNode);
	RemoveChildren(pParentNode);
	bResult=pTool->SetName(_T("G9-3-3-7"));
	strcpy(props.partNumber,"G9-3-3-7");//sl,tl,sd,hd	
	strcpy(props.materialName,"Galvanized");	
	WritePropertiesToCatalog(props,pParentNode);

	// Now get the default COMMAND tool to adjust these parameters.
	pTool = GetToolFromPalette(pPalette,3,pParentNode);
	RemoveChildren(pParentNode);
	bResult=pTool->SetName(_T("BOLTJIG"));
	WriteGenericToolData(pParentNode,"^C^CBOLTJIG ");
    
	// Resave.
	bResult=pCatalog->Save((CString)pCatalogPath+"\\Support\\ToolPalette\\BoltTool.atc");	
}

// Extracts a string attribute from an element
//
// pNode [in]:          Node from which to extract the attribute
// pszAttName [in]:     Attribute name to extract
// sValue [out]:        Variable to receive the string
//
// Returns TRUE on success. FALSE if the named attribute is not found or 
// on failure.
//
BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                       LPCTSTR pszAttName, 
                       CString& sValue)
{
    sValue.Empty();

    if (pNode == NULL || pszAttName == NULL)
        return FALSE;

    USES_CONVERSION;

    MSXML::IXMLDOMAttributePtr pAttr;
    if (!GetAttribute(pNode, pszAttName, &pAttr))
        return FALSE;

    CComVariant val;
    HRESULT hr = pAttr->get_value(&val);

    sValue = OLE2A(val.bstrVal);

    return TRUE;
}

BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                       LPCTSTR pszAttName, 
                       char *sValue)
{
    if (pNode == NULL || pszAttName == NULL)
        return FALSE;

    USES_CONVERSION;

    MSXML::IXMLDOMAttributePtr pAttr;
    if (!GetAttribute(pNode, pszAttName, &pAttr))
        return FALSE;

    CComVariant val;
    HRESULT hr = pAttr->get_value(&val);

    strcpy(sValue,OLE2A(val.bstrVal));

    return TRUE;
}



// Extracts a double value attribute from an element
//
// pNode [in]:          Node from which to extract the attribute
// pszAttName [in]:     Attribute name to extract
// fValue [out]:        Variable to receive the double value
//
// Returns TRUE on success. FALSE if the named attribute is not found or 
// on failure.
//
BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                       LPCTSTR pszAttName, 
                       double& fValue)
{
    fValue = 0.0;

    if (pNode == NULL || pszAttName == NULL)
        return FALSE;

    MSXML::IXMLDOMAttributePtr pAttr;
    if (!GetAttribute(pNode, pszAttName, &pAttr))
        return FALSE;

    CComVariant val;
    HRESULT hr = pAttr->get_value(&val);

    if (val.vt == VT_BSTR) {
        USES_CONVERSION;
        fValue = atof(OLE2A(val.bstrVal));
    } else {
        fValue = val.dblVal;
    }
    return TRUE;
}


// Extracts a long value attribute from an element
//
// pNode [in]:          Node from which to extract the attribute
// pszAttName [in]:     Attribute name to extract
// lValue [out]:        Variable to receive the long value
//
// Returns TRUE on success. FALSE if the named attribute is not found or 
// on failure.
//
BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                       LPCTSTR pszAttName, 
                       long& lValue)
{
    lValue = 0;

    if (pNode == NULL || pszAttName == NULL)
        return FALSE;

    MSXML::IXMLDOMAttributePtr pAttr;
    if (!GetAttribute(pNode, pszAttName, &pAttr))
        return FALSE;

    CComVariant val;
    HRESULT hr = pAttr->get_value(&val);

    if (val.vt == VT_BSTR) {
        USES_CONVERSION;
        lValue = atol(OLE2A(val.bstrVal));

    } else {
        lValue = val.lVal;
    }
    return TRUE;
}


// Extracts a GUID attribute from an element
//
// pNode [in]:          Node from which to extract the attribute
// pszAttName [in]:     Attribute name to extract
// guid [out]:          Variable to receive the GUID
//
// Returns TRUE on success. FALSE if the attribute child is not found or 
// on failure.
//
BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                       LPCTSTR pszAttName, 
                       GUID& guid)
{
    ZeroMemory(&guid, sizeof(GUID));

    if (pNode == NULL || pszAttName == NULL)
        return FALSE;
    
    USES_CONVERSION;

    // Read the GUID attribute as string
    CString sValue;
    if (!GetAttributeValue(pNode, pszAttName, sValue)) {
        // Attribute not found
        return FALSE;
    }

    // GUID should be enclosed in {}
    // Enclose GUID in {} if not already enclosed
    if (sValue.GetLength() > 0 && sValue[0] != '{')
        sValue.Insert(0, '{');
    if (sValue.GetLength() > 0 && sValue[sValue.GetLength() - 1] != '}')
        sValue += '}';

    HRESULT hr = CLSIDFromString(A2OLE(sValue), &guid);

    return SUCCEEDED(hr);
}

BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              const CString& sValue)
{
    MSXML::IXMLDOMElementPtr pElement = pNode;

    if (pNode == NULL || pElement == NULL || pszAttName == NULL)
        return FALSE;

    CComVariant var(sValue);
    HRESULT hr = pElement->setAttribute(pszAttName, var);

	return SUCCEEDED(hr);
}


// Sets a double value to the specifiec attribute of an element
//
// pNode [in]:          Node which contains the attribute
// pszAttName [in]:     Attribute name to set
// fValue [in]:         Attribute value to set
//
// Returns TRUE on success. FALSE if the named attribute is not found or 
// on failure.
//
BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              double fValue)
{
    MSXML::IXMLDOMElementPtr pElement = pNode;

    if (pNode == NULL || pElement == NULL || pszAttName == NULL)
        return FALSE;

    CComVariant var(fValue);
    HRESULT hr = pElement->setAttribute(pszAttName, var);

    return SUCCEEDED(hr);
}


// Sets a long value to the specifiec attribute of an element
//
// pNode [in]:          Node which contains the attribute
// pszAttName [in]:     Attribute name to set
// lValue [in]:         Attribute value to set
//
// Returns TRUE on success. FALSE if the named attribute is not found or 
// on failure.
//
BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              long lValue)
{
    MSXML::IXMLDOMElementPtr pElement = pNode;

    if (pNode == NULL || pElement == NULL || pszAttName == NULL)
        return FALSE;

    CComVariant var(lValue);
    HRESULT hr = pElement->setAttribute(pszAttName, var);

    return SUCCEEDED(hr);
}


// Sets a GUID to the specifiec attribute of an element
//
// pNode [in]:          Node which contains the attribute
// pszAttName [in]:     Attribute name to set
// guid [in]:           Attribute value to set
//
// Returns TRUE on success. FALSE if the named attribute is not found or 
// on failure.
//
BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                              LPCTSTR pszAttName, 
                              const GUID& guid)
{
    if (pNode == NULL || pszAttName == NULL)
        return FALSE;
    
    USES_CONVERSION;

    CComBSTR bstrGuid;
    HRESULT hr = StringFromCLSID(guid, &bstrGuid);

    return SetAttributeValue(pNode, pszAttName, OLE2A(bstrGuid));
}

BOOL GetAttribute(MSXML::IXMLDOMNode* pNode, 
                  LPCTSTR pszAttName, 
                  MSXML::IXMLDOMAttribute** ppChild)
{
    if (ppChild == NULL)
        return FALSE;

    *ppChild = NULL;

    if (pNode == NULL || pszAttName == NULL)
        return FALSE;

    USES_CONVERSION;

    // Read the attributes of the item
    //
    MSXML::IXMLDOMNamedNodeMapPtr pAttributes;
    pNode->get_attributes(&pAttributes);
    if (pAttributes == NULL) {
        // Wrong node type, may be
        return FALSE;
    }

    long nCount;
    pAttributes->get_length(&nCount);
    if (nCount < 1) {
        return FALSE;
    }

    MSXML::IXMLDOMAttributePtr pAttr;
    pAttr = pAttributes->getNamedItem(_bstr_t(pszAttName));
    if (pAttr == NULL) {
        // The named attribute is not found
        return FALSE;
    }

    *ppChild = pAttr.GetInterfacePtr();

    // AddRef before returning
    if (*ppChild != NULL)
        (*ppChild)->AddRef();

    return TRUE;
}

// Gets the static and dynamic properties
//
BOOL GetUnknownArrays(int nCount, 
                      IUnknown** pObjUnkArray, 
                      VARIANT* pStatUnkArray, 
                      VARIANT* pDynPMUnkArrays)
{
    if (nCount < 1) 
        return FALSE;

    COleSafeArray StatUnkArray, DynPMUnkArrays;
    StatUnkArray.Attach(*pStatUnkArray);
    DynPMUnkArrays.Attach(*pDynPMUnkArrays);

    // Populate the SafeArray of Static object IUnknowns
    StatUnkArray.CreateOneDim(VT_VARIANT, nCount);
    DynPMUnkArrays.CreateOneDim(VT_VARIANT, nCount);

    try {
        for(long i=0; i<nCount; i++) {
            StatUnkArray.PutElement(&i, &CComVariant(pObjUnkArray[i]));

            COleSafeArray DynamicPMArray;
            DynamicPMArray.CreateOneDim(VT_VARIANT, 1);
            DynamicPMArray.PutElement(&i, &CComVariant((IUnknown*) NULL));
            
            DynPMUnkArrays.PutElement(&i, (LPVARIANT*) &DynamicPMArray);
        }

    } catch(COleException *pe) {
        char buffer[1024];
        pe->GetErrorMessage(buffer, 1024);
        return FALSE;
    }

    *pStatUnkArray = StatUnkArray.Detach();
    *pDynPMUnkArrays = DynPMUnkArrays.Detach();

    return TRUE;
}

