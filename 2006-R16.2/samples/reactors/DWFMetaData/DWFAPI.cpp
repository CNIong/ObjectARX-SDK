// (C) Copyright 2004 by Autodesk, Inc. 
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
// DWFAPI.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "DWFAPI.h"
#include "U:\develop\global\src\coreapps\acmgdreverse\mgPublishUtils.h"
#include "dbents.h"
#include <stack>
#include "AcDMMapi.h"
#include "steelSect.h"  // this is required for the custom entity CSteelSection
#include "dynprops.h"

TdDMMReactor *g_pDMMReactor = NULL;
//TdPublishReactor *g_pPubReactor = NULL;
//TdPublishUIReactor *g_pPubUIReactor = NULL;
CCW_AcPublishMgdServices* g_pDxServices;
bool g_bIncludeBlockInfo;

std::stack<int>g_NodeStack;
std::vector<unsigned long>g_entIdVec;

int BlockNo = 0;
bool invalidTest = true;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString OUTFILE(L"C:\\Current Project\\DWFAPI\\DWFs\\OutFile.txt");

HINSTANCE _hdllInstance = NULL;
//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CDWFAPIApp

BEGIN_MESSAGE_MAP(CDWFAPIApp, CWinApp)
END_MESSAGE_MAP()

// CDWFAPIApp construction

CDWFAPIApp::CDWFAPIApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDWFAPIApp object

CDWFAPIApp theApp;


// CDWFAPIApp initialization

BOOL CDWFAPIApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal=-1)
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

// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT
	AddCommand("DWFAPI", "dwfapi", "DWFAPI", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET,DWFAPI);
	//}}AFX_ARX_INIT

	// TODO: add your initialization functions
	acedPostCommandPrompt();
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	acedRegCmds->removeGroup("ASDKPROPERTY_INS");
	//}}AFX_ARX_EXIT

	// TODO: clean up your application

}



////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg) {
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		InitApplication();
		acutPrintf("\nType 'DWFAPI' to run the app.");
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;
}
// print functions.
void myPrintf(CString text, CString filename)
{
	if (filename != "")
	{
		FILE *stream;
		if((stream = fopen(filename, "a+")) == NULL)
		{
			printf("\n...Output file could not be created!");
			exit(0);
		}

		// write the text.
		fprintf(stream, text);

		// close the file output if opened.
		if(fclose(stream))
			printf("\n...Output file could not be closed!");
	}
	else
		printf(text);
}

void myPrintf(CString text)
{
	printf(text);
}

//TdDMMReactor class implementation.
TdDMMReactor::TdDMMReactor()
{
	A1=false;
	A2=false;
	A3=false;
	A4=false;
}
TdDMMReactor::~TdDMMReactor()
{
	A1=false;
	A2=false;
	A3=false;
	A4=false;
}
//wchar_t* TdDMMReactor::D2W(double value)
//{
//	CString str;
//	str.Format("%g",value);
//	USES_CONVERSION;
//	m_wchar = A2W(str);
//	return m_wchar;
//}
void TdDMMReactor::OnBeginEntity(AcDMMEntityReactorInfo * pInfo) //#4
{
	if (A1 == false)
	{
		myPrintf("\nTdDMMReactor::OnBeginEntity", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nTdDMMReactor::OnBeginEntity");
		A1 = true;
	}
	if (g_bIncludeBlockInfo)
	{
		AcDbEntity* pEntity = pInfo->entity();
		AcDbObjectId objId = pEntity->objectId();
		long oldId = objId.asOldId();

		unsigned long front = 0;

		// this is a custom entity.
		// assigning a property to the custom entity.

		if (pEntity->isKindOf(CSteelSection::desc()))
		{
			myPrintf("\nCSteelSection FOUND, assigning metadata properties to it.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nCSteelSection FOUND, assigning metadata properties to it.");

			CSteelSection* pSteelEnt = (CSteelSection*)pEntity;
			AcDMMEPlotProperties props0;
			AcDMMEPlotProperty prop0;
			prop0.SetCategory(L"Steel Section");

			USES_CONVERSION;
			prop0.SetName(L"Section Type");
			//Adesk::Int16 SType;
			//(CSteelSection*)pEntity->getSectionType(SType);
			prop0.SetValue(L"W Section");
			props0.AddProperty(&prop0);

			prop0.SetName(L"Section Depth");
			//Adesk::Int16 SType;
			double depth = pSteelEnt->getDepth();
			m_cstr.Format("%g",depth);
			m_wchar = A2W(m_cstr);
			prop0.SetValue(m_wchar);
			props0.AddProperty(&prop0);

			prop0.SetName(L"Section Length");
			//Adesk::Int16 SType;
			double length = pSteelEnt->getLength();
			m_cstr.Format("%g",length);
			m_wchar = A2W(m_cstr);
			prop0.SetValue(m_wchar);
			props0.AddProperty(&prop0);

			prop0.SetName(L"Section Flange Width");
			//Adesk::Int16 SType;
			double fWidth = pSteelEnt->getFlangeWidth();
			m_cstr.Format("%g",fWidth);
			m_wchar = A2W(m_cstr);
			prop0.SetValue(m_wchar);
			props0.AddProperty(&prop0);

			prop0.SetName(L"Section Flange Thickness");
			//Adesk::Int16 SType;
			double fThick = pSteelEnt->getFlangeThickness();
			m_cstr.Format("%g",fThick);
			m_wchar = A2W(m_cstr);
			prop0.SetValue(m_wchar);
			props0.AddProperty(&prop0);

			prop0.SetName(L"Section Web Thickness");
			//Adesk::Int16 SType;
			double wThick = pSteelEnt->getWebThickness();
			m_cstr.Format("%g",wThick);
			m_wchar = A2W(m_cstr);
			prop0.SetValue(m_wchar);
			props0.AddProperty(&prop0);

			const wchar_t* wsUnique0 = pInfo->UniqueEntityId();
			AcDMMWideString wsPropId0; // need an unique ID for properties.
			wsPropId0 = L"CUSTOM_ENTITY-";
			wsPropId0 += wsUnique0;
			delete wsUnique0;
			props0.SetId(PCWIDESTR(wsPropId0));
			pInfo->AddProperties(&props0); // add props obj to cache
			// Invalid value test.
			if (invalidTest == true)
			{
				AcDMMEPlotProperties props100;
				AcDMMEPlotProperty prop100;
				props100.AddProperty(&prop100);
				props100.AddProperty(NULL);
				pInfo->AddProperties(&props100);
				//DID 607332
				//pInfo->AddProperties(NULL);
			}

			// to test different AcDMMProperty methods.
			// SetType, SetUnit, SetName, SetValue
			AcDMMEPlotProperty* prop00 = new AcDMMEPlotProperty();
			prop00->SetName(L"Test Name");
			prop00->SetValue(L"Test Value");
			prop00->SetType(L"Test Type");
			prop00->SetUnits(L"Test Unit");
			AcDMMEPlotProperty* prop01 = prop00;

			// GetType, GetUnit, GetName, GetValue
			if(strcmp(OLE2A(prop00->GetName()), "Test Name") == 0)
				myPrintf("\nPassed: AcDMMEPlotProperty::SetName(), GetName() work fine.", OUTFILE);
			else
				myPrintf("\nFailed: AcDMMEPlotProperty::SetName(), GetName() do not work fine.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMEPlotProperty::SetName(), GetName().");
			if(strcmp(OLE2A(prop00->GetValue()), "Test Value") == 0)
				myPrintf("\nPassed: AcDMMEPlotProperty::SetValue(), GetValue() work fine.", OUTFILE);
			else
				myPrintf("\nFailed: AcDMMEPlotProperty::SetValue(), GetValue() do not work fine.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMEPlotProperty::SetValue(), GetValue()");
			if(strcmp(OLE2A(prop00->GetType()), "Test Type") == 0)
				myPrintf("\nPassed: AcDMMEPlotProperty::SetType(), GetType() work fine.", OUTFILE);
			else
				myPrintf("\nFailed: AcDMMEPlotProperty::SetType(), GetType() do not work fine.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMEPlotProperty::SetType(), GetType()");
			if(strcmp(OLE2A(prop00->GetUnits()), "Test Unit") == 0)
				myPrintf("\nPassed: AcDMMEPlotProperty::SetUnits(), GetUnits() work fine.", OUTFILE);
			else
				myPrintf("\nFailed: AcDMMEPlotProperty::SetUnits(), GetUnits() do not work fine.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMEPlotProperty::SetUnits(), GetUnits()");

			// to test different AcDMMProperties methods for testing.
			AcDMMEPlotProperties props00 = props0;
			const AcDMMEPlotPropertyVec propVec = props00.GetProperties();
			
			//AcDMMEPlotProperty* tempProp;
			int noProp = propVec.size();
			for (int i=0; i<=noProp; i++)
			{
				const AcDMMEPlotProperty* tempProp = props00.GetProperty(i);
			}

			// Invalid value test.
			if (invalidTest == true)
			{
				const AcDMMEPlotProperty* tempProp100 = props00.GetProperty(0);
				const AcDMMEPlotProperty* tempProp101 = props00.GetProperty(123456);
				const AcDMMEPlotProperty* tempProp102 = props00.GetProperty(-34);
			}

			props00.SetId(L"Partha ID");
			props00.SetNamespace(L"http:\\www.autodesk.com", L"Partha Location");
			AcDMMStringVec IdVec00;
			IdVec00.push_back(wsPropId0);
			props00.SetRefs(IdVec00);

			// Invalid value test.
			if (invalidTest == true)
			{
				AcDMMStringVec vec100;
				props00.SetRefs(vec100);
			}

			if(strcmp(OLE2A(props00.GetId()), "Partha ID") == 0)
				myPrintf("\nPassed: AcDMMEPlotProperties::SetId(), GetId() work fine.", OUTFILE);
			else
				myPrintf("\nFailed: AcDMMEPlotProperties::SetId(), GetId() do not work fine.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMEPlotProperties::SetId(), GetId()");
			if(strcmp(OLE2A(props00.GetNamespaceUrl()), "http:\\www.autodesk.com") == 0)
				myPrintf("\nPassed: AcDMMEPlotProperties::SetNameSpace(), GetNameSpaceUrl() work fine.", OUTFILE);
			else
				myPrintf("\nFailed: AcDMMEPlotProperties::SetNameSpace(), GetNameSpaceUrl() do not work fine.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMEPlotProperties::SetNameSpace(), GetNameSpaceUrl()");
			if(strcmp(OLE2A(props00.GetNamespaceLocation()), "Partha Location") == 0)
				myPrintf("\nPassed: AcDMMEPlotProperties::SetNameSpace(), GetNameSpaceLocation() work fine.", OUTFILE);
			else
				myPrintf("\nFailed: AcDMMEPlotProperties::SetNameSpace(), GetNameSpaceLocation() do not work fine.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMEPlotProperties::SetNameSpace(), GetNameSpaceLocation()");
			if(props00.GetRefs()->size() == IdVec00.size())
				myPrintf("\nPassed: AcDMMEPlotProperties::SetRef(), GetRef() work fine.", OUTFILE);
			else
				myPrintf("\nFailed: AcDMMEPlotProperties::SetRef(), GetRef() do not work fine.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMEPlotProperties::SetRef(), GetRef()");

			// AcDMMWideString.
			// for testing only will not be written
			AcDMMWideString wsTemp(wsPropId0);
			size_t len0 = wsTemp.GetLength();
			if (wsTemp.GetLength() == 57)
				myPrintf("\nAcDMMWideString::GetLength() returns correcft length.", OUTFILE);
			else
				myPrintf("\nAcDMMWideString::GetLength() does not return correct length.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMWideString::GetLength()");
			if (!wsTemp.IsEmpty())
				wsTemp.Empty();
			if (wsTemp.IsEmpty())
				myPrintf("\nAcDMMWideString::IsEmpty(), Empty() works fine", OUTFILE);
			else
				myPrintf("\nAcDMMWideString::IsEmpty(), Empty() do not work fine", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMWideString::IsEmpty(), Empty()");

			// string Vector
			AcDMMStringVec IdVec0;
			IdVec0.push_back(wsPropId0);

			int nodeId0 = 0;
			const AcDMMNode* node0;
			// check to see if this node already assigned
			if(!pInfo->GetEntityNode(objId, front, nodeId0))
			{
				nodeId0 = pInfo->GetNextAvailableNodeId();
				node0 = new AcDMMNode(nodeId0, L"CUSTOM_ENTITY");
				bool bret;
				bret = pInfo->AddNodeToMap(objId, front, nodeId0);
				// Invalid value test.
				if (invalidTest == true)
				{
					int NodeId100;
					unsigned long front100 = g_entIdVec.front();
					AcDbObjectId objId100 = pEntity->objectId();
					pInfo->AddNodeToMap(0, front100, NodeId100);
					pInfo->AddNodeToMap(objId100, 0, NodeId100);
					pInfo->AddNodeToMap(objId100, -3, NodeId100);
					pInfo->AddNodeToMap(objId100, front100, 0);
					pInfo->AddNodeToMap(objId100, front100, 123456);
					pInfo->AddNodeToMap(objId100, front100, -4);
				}
				ASSERT(bret);
			}
			else
			{
				// use the existing node.
				node0 = pInfo->GetNode(nodeId0);
				// Invalid value test.
				if (invalidTest == true)
				{
					pInfo->GetNode(0);
					pInfo->GetNode(100000);
					pInfo->GetNode(-10);
				}
				//bool bret;
				//bret = pInfo->AddNodeToMap(objId, front, nodeId0);
				//ASSERT(bret);
			}
			// Invalid value test.
			if (invalidTest == true)
			{
				int iNodeId100;
				unsigned long front100 = g_entIdVec.front();
				AcDbObjectId objId100 = pEntity->objectId();
				pInfo->GetEntityNode(0, front100, iNodeId100);
				pInfo->GetEntityNode(objId100, 0, iNodeId100);
				pInfo->GetEntityNode(objId100, -3, iNodeId100);
			}
			ASSERT(0 != nodeId0);
			if(0 != nodeId0)
			{
				g_NodeStack.push(nodeId0);
				//associate the properties with the node.
				pInfo->AddPropertiesIds(&IdVec0, (AcDMMNode&)*node0);
				// Invalid value test.
				if (invalidTest == true)
				{
					AcDMMStringVec IdVec100;
					const AcDMMNode* node100;
					pInfo->AddPropertiesIds(&IdVec100, (AcDMMNode&)*node0);
					// DID 607346
					//pInfo->AddPropertiesIds(NULL, (AcDMMNode&)*node0);
					const AcDMMNode* node101 = NULL;
					pInfo->AddPropertiesIds(&IdVec100, (AcDMMNode&)*node101);
					// DID 607346
					//pInfo->AddPropertiesIds(NULL, (AcDMMNode&)*node101);
				}
			}
		}
		
		if (pEntity->isKindOf(AcDbBlockReference::desc()) && (g_pDxServices != NULL)) // block
		{
			myPrintf("\nBlock FOUND, assigning metadata properties to it.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nBlock FOUND, assigning metadata properties to it");
			// get the block name.
			AcDbBlockReference* pBlkRef = 0;
			char* blkName = 0;
			if(acdbOpenObject(pBlkRef, objId, AcDb::kForRead) == Acad::eOk)
			{
				AcDbBlockTableRecord* pTblRec = 0;

				if(acdbOpenObject(pTblRec, pBlkRef->blockTableRecord(), AcDb::kForRead) == Acad::eOk)
				{
					pTblRec->getName(blkName);
					pTblRec->close();
				}
				pBlkRef->close();
			}
			// get blocks properties from DX api.
			g_entIdVec.push_back(oldId);
			front = g_entIdVec.front();
			AcDMMEPlotPropertyVec propVec;

			// FIRST SET OF PROPERTIES.
			AcDMMEPlotProperties props;
			g_pDxServices->get_block_properties(objId, &propVec);
			//add properties to prop objects.
			AcDMMEPlotPropertyVec::const_iterator iter = propVec.begin();
			// get all the standard meta properties and write them in the new
			// property collection.
			while (iter != propVec.end())
			{
				AcDMMEPlotProperty prop = (*iter++);
				props.AddProperty(&prop);
			}
			// write a custom property.
			AcDMMEPlotProperty prop1(L"ParthaProperty", L"ParthaValue");

			USES_CONVERSION;
			if (blkName != "")
				prop1.SetCategory(A2W(blkName));
			else
                prop1.SetCategory(L"Custom Catagory1");
			props.AddProperty(&prop1);

			const wchar_t* wsUnique = pInfo->UniqueEntityId();
			AcDMMWideString wsPropId; // need an unique ID for properties.
			wsPropId = L"PARTHA-";
			wsPropId += wsUnique;
			delete wsUnique;
			props.SetId(PCWIDESTR(wsPropId));
			pInfo->AddProperties(&props); // add props obj to cache
			// Invalid value test.
			if (invalidTest == true)
			{
				AcDMMEPlotProperties props100;
				AcDMMEPlotProperty prop100;
				props100.AddProperty(&prop100);
				props100.AddProperty(NULL);
				pInfo->AddProperties(&props100);
				//DID 607332
				//pInfo->AddProperties(NULL);
			}

			// string Vector
			AcDMMStringVec IdVec;
			IdVec.push_back(wsPropId);

			int nodeId = 0;
			const AcDMMNode* node;
			// check to see if this node already assigned
			if(!pInfo->GetEntityNode(objId, front, nodeId))
			{
				// create a node for this entity.
				nodeId = pInfo->GetNextAvailableNodeId();
				node = new AcDMMNode(nodeId, L"PARTHA");
				bool bret;
				bret = pInfo->AddNodeToMap(objId, front, nodeId);
				ASSERT(bret);
				// Invalid value test.
				if (invalidTest == true)
				{
					int NodeId100;
					unsigned long front100 = g_entIdVec.front();
					AcDbObjectId objId100 = pEntity->objectId();
					pInfo->AddNodeToMap(0, front100, NodeId100);
					pInfo->AddNodeToMap(objId100, 0, NodeId100);
					pInfo->AddNodeToMap(objId100, -3, NodeId100);
					pInfo->AddNodeToMap(objId100, front100, 0);
					pInfo->AddNodeToMap(objId100, front100, 123456);
					pInfo->AddNodeToMap(objId100, front100, -4);
				}
			}
			else
			{
				// use the existing node.
				node = pInfo->GetNode(nodeId);
				// Invalid value test.
				if (invalidTest == true)
				{
					pInfo->GetNode(0);
					pInfo->GetNode(100000);
					pInfo->GetNode(-10);
				}
			}
			// Invalid value test.
			if (invalidTest == true)
			{
				int iNodeId100;
				unsigned long front100 = g_entIdVec.front();
				AcDbObjectId objId100 = pEntity->objectId();
				pInfo->GetEntityNode(0, front100, iNodeId100);
				pInfo->GetEntityNode(objId100, 0, iNodeId100);
				pInfo->GetEntityNode(objId100, -3, iNodeId100);
			}
			ASSERT(0 != nodeId);
			if (0 != nodeId)
			{
				g_NodeStack.push(nodeId);
				// associate the properties with the node.
				pInfo->AddPropertiesIds(&IdVec, (AcDMMNode &)*node);
				// Invalid value test.
				if (invalidTest == true)
				{
					AcDMMStringVec IdVec100;
					const AcDMMNode* node100;
					pInfo->AddPropertiesIds(&IdVec100, (AcDMMNode&)*node100);
					// DID 607346
					//pInfo->AddPropertiesIds(NULL, (AcDMMNode&)*node100);
					const AcDMMNode* node101 = NULL;
					pInfo->AddPropertiesIds(&IdVec100, (AcDMMNode&)*node101);
					// DID 607346
					//pInfo->AddPropertiesIds(NULL, (AcDMMNode&)*node101);;
				}
			}

			// AcDMMNode::SetNodeNumber(), nodeNumber()
			// this node will not be added to the map.
			// this is for testing purpose only.
			int xNodeId = nodeId+1;
			AcDMMNode* node1 = new AcDMMNode(nodeId, L"PARTHA01");
			node1->SetNodeNumber(xNodeId);
			if(node1->nodeNumber() == xNodeId)
				myPrintf("\nPassed: AcDMMNode::SetNodeNumber(), nodeMumber() work fine.", OUTFILE);
			else
				myPrintf("\nFailed: AcDMMNode::SetNodeNumber(), nodeNumber() do not work fine.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMNode::SetNodeNumber(), nodeMumber()");

			// Invalid value test.
			if (invalidTest == true)
			{
				AcDMMNode* node100 = new AcDMMNode(nodeId, L"!@#$%^&*");
				node100->SetNodeNumber(0);
				node100->SetNodeNumber(12345);
				node100->SetNodeNumber(-34);
			}

			//AcDMMNode::SetNodeName(), NodeName()
			wchar_t* name = L"PARTHA02";
			node1->SetNodeName(name);
			if(strcmp(OLE2A(node1->nodeName()), "PARTHA02") == 0)
				myPrintf("\nPassed: AcDMMNode::SetNodeName(), nodeName() work fine.", OUTFILE);
			else
				myPrintf("\nFailed: AcDMMNode::SetNodeName(), nodeNAme() do not work fine.", OUTFILE);
			pInfo->GetPlotLogger()->logMessage("\nAcDMMNode::SetNodeName(), nodeName()");

			// Invalid value test.
			if (invalidTest == true)
			{
				node1->SetNodeName(L"");
			}

			// SECOND SET OF PROPERTIES.
			AcDMMEPlotProperties props2;
			AcDMMEPlotProperty prop2(L"BappaProperty", L"BappaValue");
			if (blkName != "")
				prop2.SetCategory(A2W(blkName));
			else
				prop2.SetCategory(L"Custom Catagory2");
			props2.AddProperty(&prop2);

			const wchar_t* wsUnique2 = pInfo->UniqueEntityId();
			AcDMMWideString wsPropId2; // need an unique ID for properties.
			wsPropId2 = L"BAPPA-";
			wsPropId2 += wsUnique2;
			delete wsUnique2;
			props2.SetId(PCWIDESTR(wsPropId2));
			pInfo->AddProperties(&props2); // add props obj to cache
			// Invalid value test.
			if (invalidTest == true)
			{
				AcDMMEPlotProperties props100;
				AcDMMEPlotProperty prop100;
				props100.AddProperty(&prop100);
				props100.AddProperty(NULL);
				pInfo->AddProperties(&props100);
				//DID 607332
				//pInfo->AddProperties(NULL);
			}

			// string Vector
			AcDMMStringVec IdVec2;
			IdVec2.push_back(wsPropId2);

			int nodeId2 = 0;
			const AcDMMNode* node2;
			AcDMMNode* node02 = NULL;
			bool whichOne = true;
			// check to see if this node already assigned
			if(!pInfo->GetEntityNode(objId, front, nodeId2))
			{
				// create a node for this entity.
				nodeId2 = pInfo->GetNextAvailableNodeId();
				// try to add the node in a different way.
				//node2 = new AcDMMNode(nodeId2, L"BAPPA");
				//bool bret2;
				//bret2 = pInfo->AddNodeToMap(objId, front, nodeId2);
				node02->SetNodeNumber(nodeId2);
				// Invalid value test.
				if (invalidTest == true)
				{
					AcDMMNode* node100 = new AcDMMNode(nodeId, L"!@#$%^&*");
					node100->SetNodeNumber(0);
					node100->SetNodeNumber(12345);
					node100->SetNodeNumber(-34);
				}
				node02->SetNodeName(L"BAPPA");
				// Invalid value test.
				if (invalidTest == true)
				{
					node02->SetNodeName(L"");
				}
				pInfo->SetCurrentNode(nodeId2, 0);
				// Invalid value test.
				if (invalidTest == true)
				{
					pInfo->SetCurrentNode(0, 0);
					pInfo->SetCurrentNode(-3, 0);
					pInfo->SetCurrentNode(0, -5);
				}
				whichOne = true;
				AcDMMNode node03;
				pInfo->GetCurrentEntityNode(node03, 0);
				/*if (node03.nodeNumber != node02->nodeNumber())
					myPrintf("\nFailed: AcDMMEntityReactorInfo::GetCurrentEntityNode() does not get the correct entity node.", OUTFILE);*/
				//ASSERT(bret2);
				// Invalid value test.
				if (invalidTest == true)
				{
					AcDMMNode node100;
					pInfo->GetCurrentEntityNode(node100, 3345);
					pInfo->GetCurrentEntityNode(node100, -2);
				}
			}
			else
			{
				// use the existing node.
				node2 = pInfo->GetNode(nodeId2);
				// Invalid value test.
				if (invalidTest == true)
				{
					pInfo->GetNode(0);
					pInfo->GetNode(100000);
					pInfo->GetNode(-10);
				}
				pInfo->SetNodeName(nodeId2, L"BAPPA01");
				// Invalid value test.
				if (invalidTest == true)
				{
					int node100;
					pInfo->SetNodeName(node100, L"xx");
					node100=12;
					pInfo->SetNodeName(node100, L"");
				}
				pInfo->SetCurrentNode(nodeId2, 0);
				// Invalid value test.
				if (invalidTest == true)
				{
					pInfo->SetCurrentNode(0, 0);
					pInfo->SetCurrentNode(-3, 0);
					pInfo->SetCurrentNode(0, -5);
				}
				whichOne = false;
				AcDMMNode node03;
				pInfo->GetCurrentEntityNode(node03, 0);
				/*if (node03.nodeNumber != node2->nodeNumber())
					myPrintf("\nFailed: AcDMMEntityReactorInfo::GetCurrentEntityNode() does not get the correct entity node.", OUTFILE);*/
				// Invalid value test.
				if (invalidTest == true)
				{
					AcDMMNode node100;
					pInfo->GetCurrentEntityNode(node100, 3098);
					pInfo->GetCurrentEntityNode(node100, -2);
				}
			}

			// Invalid value test.
			if (invalidTest == true)
			{
				int iNodeId100;
				unsigned long front100 = g_entIdVec.front();
				AcDbObjectId objId100 = pEntity->objectId();
				pInfo->GetEntityNode(0, front100, iNodeId100);
				pInfo->GetEntityNode(objId100, 0, iNodeId100);
				pInfo->GetEntityNode(objId100, -3, iNodeId100);
			}

			ASSERT(0 != nodeId2);
			if (0 != nodeId2)
			{
				g_NodeStack.push(nodeId2);
				// associate the properties with the node.
				if (whichOne == false)
					pInfo->AddPropertiesIds(&IdVec2, (AcDMMNode &)*node2);
				else
					pInfo->AddPropertiesIds(&IdVec2, (AcDMMNode &)*node02);
				// Invalid value test.
				if (invalidTest == true)
				{
					AcDMMStringVec IdVec100;
					const AcDMMNode* node100;
					pInfo->AddPropertiesIds(&IdVec100, (AcDMMNode&)*node100);
					// DID 607346
					//pInfo->AddPropertiesIds(NULL, (AcDMMNode&)*node100);
					const AcDMMNode* node101 = NULL;
					pInfo->AddPropertiesIds(&IdVec100, (AcDMMNode&)*node101);
					// DID 607346
					//pInfo->AddPropertiesIds(NULL, (AcDMMNode&)*node101);
				}
			}
		}
		else
		{
			if (!g_NodeStack.empty())
			{
				//ASSERT(!g_entIdVec.empty());
				int iNodeId = g_NodeStack.top();
				front = g_entIdVec.front();
				//if no one else has assigned a Node Id for this entity
				if(!pInfo->GetEntityNode(objId, front, iNodeId))
				{
					// associate this entity with the top node on the stack
					bool bret;
					bret = pInfo->AddNodeToMap(objId, front, iNodeId);
					ASSERT(bret);
					// Invalid value test.
					if (invalidTest == true)
					{
						int NodeId100;
						unsigned long front100 = g_entIdVec.front();
						AcDbObjectId objId100 = pEntity->objectId();
						pInfo->AddNodeToMap(0, front100, NodeId100);
						pInfo->AddNodeToMap(objId100, 0, NodeId100);
						pInfo->AddNodeToMap(objId100, -3, NodeId100);
						pInfo->AddNodeToMap(objId100, front100, 0);
						pInfo->AddNodeToMap(objId100, front100, 123456);
						pInfo->AddNodeToMap(objId100, front100, -4);
					}
				}
				// Invalid value test.
				if (invalidTest == true)
				{
					int iNodeId100;
					unsigned long front100 = g_entIdVec.front();
					AcDbObjectId objId100 = pEntity->objectId();
					pInfo->GetEntityNode(0, front100, iNodeId100);
					pInfo->GetEntityNode(objId100, 0, iNodeId100);
					pInfo->GetEntityNode(objId100, -3, iNodeId100);
				}
				if(pEntity->isKindOf(AcDbBlockEnd::desc()))
				{
					g_NodeStack.pop();
					g_entIdVec.pop_back();
				}
			}
		}
		pInfo->flush();
		// this is a test to Job Cancled methods. Make sure when you un-comment these,
		// you hit the TdPublishReactor::OnCancelledOrFailedPublishing reactor.
		//pInfo->cancelTheJob();
		//if (!pInfo->isCancelled())
		//	myPrintf("\nThe job is correctly cancled.", OUTFILE);
	}
}
void TdDMMReactor::OnBeginSheet(AcDMMSheetReactorInfo * pInfo) //#3
{
	if (A2 == false)
	{
		myPrintf("\nTdDMMReactor::OnBeginSheet", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nTdDMMReactor::OnBeginSheet");
		A2 = true;
	}
	// be sure to start with empty stack
	while (!g_NodeStack.empty())
		g_NodeStack.pop();

	if (!pInfo->isModelLayout()) // Layout
	{
		// add a resource
		AcDMMResourceInfo res(L"ParthaSheetResource", L"text", L"C:\\Current Project\\DWFAPI\\DWFs\\Reflection Paper.doc");
		AcDMMResourceVec resVec;
		resVec.push_back(res);
		pInfo->AddPageResources(resVec);

		// Invalid value test.
		if (invalidTest == true)
		{
			AcDMMResourceVec pVec100;
			pInfo->AddPageResources(pVec100);
		}

		// add a property
		AcDMMEPlotPropertyVec propVec;

		//AcDMMEPlotProperty prop(L"ParthaSheetProperty", L"ParthaSheetValue");
		//prop.SetCategory(L"ParthaSheetProp");
		//propVec.push_back(prop);

		// plotLayoutId()
		long plotLayId = pInfo->plotLayoutId().asOldId();
		AcDMMEPlotProperty propLayId(L"Layout ID", (wchar_t*)plotLayId);
		propLayId.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propLayId);

		// plotArea()
		AcDMMSheetReactorInfo::PlotArea plotarea = pInfo->plotArea();
		AcDMMEPlotProperty propPlotArea;
		propPlotArea.SetName(L"Plot Area");
		switch (plotarea)
		{
		case AcDMMSheetReactorInfo::PlotArea::kDisplay:
			propPlotArea.SetValue(L"Plot display, the visible portion of the picture.");
			break;
		case AcDMMSheetReactorInfo::PlotArea::kExtents:
			propPlotArea.SetValue(L"Plot extents, i.e. all geometry.");
			break;
		case AcDMMSheetReactorInfo::PlotArea::kLimits:
			propPlotArea.SetValue(L"Plot the limits set by the user.");
			break;
		case AcDMMSheetReactorInfo::PlotArea::kView:
			propPlotArea.SetValue(L"Plot a named view.");
			break;
		case AcDMMSheetReactorInfo::PlotArea::kWindow:
			propPlotArea.SetValue(L"Plot a user specified window - a rectangular area.");
			break;
		case AcDMMSheetReactorInfo::PlotArea::kLayout:
			propPlotArea.SetValue(L"Plot the extents of the layout.");
			break;
		}
		propPlotArea.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotArea);

		//plotRotation().
		AcDMMSheetReactorInfo::PlotRotation plotrotation = pInfo->plotRotation();
		AcDMMEPlotProperty propPlotRotation;
		propPlotRotation.SetName(L"Plot Rotation");
		switch (plotrotation)
		{
		case AcDMMSheetReactorInfo::PlotRotation::k0degrees:
			propPlotRotation.SetValue(L"0 degrees camera rotation.");
			break;
		case AcDMMSheetReactorInfo::PlotRotation::k180degrees:
			propPlotRotation.SetValue(L"90 degrees camera rotation.");
			break;
		case AcDMMSheetReactorInfo::PlotRotation::k270degrees:
			propPlotRotation.SetValue(L"180 degrees camera rotation, i.e., plot upside down.");
			break;
		case AcDMMSheetReactorInfo::PlotRotation::k90degrees:
			propPlotRotation.SetValue(L"270 degrees camera rotation.");
			break;
		}
		propPlotRotation.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotRotation);

		// plotMediaUnit().
		AcDMMSheetReactorInfo::PlotMediaUnits plotmediaunits = pInfo->plotMediaUnits();
		AcDMMEPlotProperty propPlotMediaUnits;
		propPlotMediaUnits.SetName(L"Plot Rotation");
		switch (plotmediaunits)
		{
		case AcDMMSheetReactorInfo::PlotMediaUnits::kInches:
			propPlotMediaUnits.SetValue(L"Using imperial units.");
			break;
		case AcDMMSheetReactorInfo::PlotMediaUnits::kMillimeters:
			propPlotMediaUnits.SetValue(L"Using metric units.");
			break;
		case AcDMMSheetReactorInfo::PlotMediaUnits::kPixels:
			propPlotMediaUnits.SetValue(L"Using dimensionaless raster units, not expected for DWF.");
			break;
		}
		propPlotMediaUnits.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotMediaUnits);

		USES_CONVERSION;
		// paperScale().
		double paperScale = pInfo->paperScale();
		bool isScale = pInfo->isScaleSpecified();
		AcDMMEPlotProperty propPaperScale;
		propPaperScale.SetName(L"Paper Scale");
		if (isScale)
		{
			m_cstr.Format("%g",paperScale);
			m_wchar = A2W(m_cstr);
			propPaperScale.SetValue(m_wchar);
		}
		else
		{
			propPaperScale.SetValue(L"Scale to Fit.");
		}
		propPaperScale.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPaperScale);

		// drawingScale().
		double drawingScale = pInfo->drawingScale();
		AcDMMEPlotProperty propDrawingScale;
		propDrawingScale.SetName(L"Drawing Scale");
		m_cstr.Format("%g",drawingScale);
		m_wchar = A2W(m_cstr);
		propDrawingScale.SetValue(m_wchar);
		propDrawingScale.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propDrawingScale);

		// originX().
		double OriginX = pInfo->originX();
		AcDMMEPlotProperty propOriginX;
		propOriginX.SetName(L"Drawing Origin X");
		m_cstr.Format("%g",OriginX);
		m_wchar = A2W(m_cstr);
		propOriginX.SetValue(m_wchar);
		propOriginX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propOriginX);

		// originY().
		double OriginY = pInfo->originY();
		AcDMMEPlotProperty propOriginY;
		propOriginY.SetName(L"Drawing Origin Y");
		m_cstr.Format("%g",OriginY);
		m_wchar = A2W(m_cstr);
		propOriginY.SetValue(m_wchar);
		propOriginY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propOriginY);

		// plotWindowMinX().
		double PlotWinMinX = pInfo->plotWindowMinX();
		AcDMMEPlotProperty propPlotWinMinX;
		propPlotWinMinX.SetName(L"Plot Window MinX");
		m_cstr.Format("%g",PlotWinMinX);
		m_wchar = A2W(m_cstr);
		propPlotWinMinX.SetValue(m_wchar);
		propPlotWinMinX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotWinMinX);

		// plotWindowMinY().
		double PlotWinMinY = pInfo->plotWindowMinY();
		AcDMMEPlotProperty propPlotWinMinY;
		propPlotWinMinY.SetName(L"Plot Window MinY");
		m_cstr.Format("%g",PlotWinMinY);
		m_wchar = A2W(m_cstr);
		propPlotWinMinY.SetValue(m_wchar);
		propPlotWinMinY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotWinMinY);

		// plotWindowMaxX().
		double PlotWinMaxX = pInfo->plotWindowMaxX();
		AcDMMEPlotProperty propPlotWinMaxX;
		propPlotWinMaxX.SetName(L"Plot Window MaxX");
		m_cstr.Format("%g",PlotWinMaxX);
		m_wchar = A2W(m_cstr);
		propPlotWinMaxX.SetValue(m_wchar);
		propPlotWinMaxX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotWinMaxX);

		// plotWindowMinY().
		double PlotWinMaxY = pInfo->plotWindowMaxY();
		AcDMMEPlotProperty propPlotWinMaxY;
		propPlotWinMaxY.SetName(L"Plot Window MaxY");
		m_cstr.Format("%g",PlotWinMaxY);
		m_wchar = A2W(m_cstr);
		propPlotWinMaxY.SetValue(m_wchar);
		propPlotWinMaxY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotWinMaxY);

		//viewPlotted()
		const TCHAR* ViewPlotted = pInfo->viewPlotted();
		AcDMMEPlotProperty propViewPlotted;
        propViewPlotted.SetName(L"View Plotted");
		if (strcmp(ViewPlotted, "") == 0)
			propViewPlotted.SetValue(L"View name not defined.");
		else
		{
			m_cstr.Format("%s",ViewPlotted);
			m_wchar = A2W(m_cstr);
			propViewPlotted.SetValue(m_wchar);
		}
		propViewPlotted.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propViewPlotted);

		// areLinesHidden().
		bool areLinesHidden = pInfo->areLinesHidden();
		AcDMMEPlotProperty propIsLinesHidden;
		propIsLinesHidden.SetName(L"Are lines hidden");
		if (areLinesHidden)
			propIsLinesHidden.SetValue(L"Yes");
		else
			propIsLinesHidden.SetValue(L"No");
		propIsLinesHidden.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propIsLinesHidden);

		// arePlottingLineWeights().
		bool arePlottingLineWeights = pInfo->arePlottingLineWeights();
		AcDMMEPlotProperty propPlottingLineWeights;
		propPlottingLineWeights.SetName(L"Are Plotting Line Weights");
		if (arePlottingLineWeights)
			propPlottingLineWeights.SetValue(L"Yes");
		else
			propPlottingLineWeights.SetValue(L"No");
		propPlottingLineWeights.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlottingLineWeights);

		// areScallingLineWeights().
		bool areScallingLineWeights = pInfo->areScalingLineWeights();
		AcDMMEPlotProperty propScallingLineWeights;
		propScallingLineWeights.SetName(L"Are Scalling Line Weights");
		if (areScallingLineWeights)
			propScallingLineWeights.SetValue(L"Yes");
		else
			propScallingLineWeights.SetValue(L"No");
		propScallingLineWeights.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propScallingLineWeights);

		// displayMinX().
		double displayMinX = pInfo->displayMinX();
		AcDMMEPlotProperty propDisplayMinX;
		propDisplayMinX.SetName(L"Display Min X");
		m_cstr.Format("%g",displayMinX);
		m_wchar = A2W(m_cstr);
		propDisplayMinX.SetValue(m_wchar);
		propDisplayMinX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propDisplayMinX);

		// displayMinY().
		double displayMinY = pInfo->displayMinY();
		AcDMMEPlotProperty propDisplayMinY;
		propDisplayMinY.SetName(L"Display Min Y");
		m_cstr.Format("%g",displayMinY);
		m_wchar = A2W(m_cstr);
		propDisplayMinY.SetValue(m_wchar);
		propDisplayMinY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propDisplayMinY);

		// displayMaxX().
		double displayMaxX = pInfo->displayMaxX();
		AcDMMEPlotProperty propDisplayMaxX;
		propDisplayMaxX.SetName(L"Display Max X");
		m_cstr.Format("%g",displayMaxX);
		m_wchar = A2W(m_cstr);
		propDisplayMaxX.SetValue(m_wchar);
		propDisplayMaxX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propDisplayMaxX);

		// displayMaxY().
		double displayMaxY = pInfo->displayMaxY();
		AcDMMEPlotProperty propDisplayMaxY;
		propDisplayMaxY.SetName(L"Display Max Y");
		m_cstr.Format("%g",displayMaxY);
		m_wchar = A2W(m_cstr);
		propDisplayMaxY.SetValue(m_wchar);
		propDisplayMaxY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propDisplayMaxY);

		// layoutMarginMinX().
		double layoutMarginMinX = pInfo->layoutMarginMinX();
		AcDMMEPlotProperty propLayoutMarginMinX;
		propLayoutMarginMinX.SetName(L"Layout Margin Min X");
		m_cstr.Format("%g",layoutMarginMinX);
		m_wchar = A2W(m_cstr);
		propLayoutMarginMinX.SetValue(m_wchar);
		propLayoutMarginMinX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propLayoutMarginMinX);

		// layoutMarginMinY().
		double layoutMarginMinY = pInfo->layoutMarginMinY();
		AcDMMEPlotProperty propLayoutMarginMinY;
		propLayoutMarginMinY.SetName(L"Layout Margin Min Y");
		m_cstr.Format("%g",layoutMarginMinY);
		m_wchar = A2W(m_cstr);
		propLayoutMarginMinY.SetValue(m_wchar);
		propLayoutMarginMinY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propLayoutMarginMinY);

		// layoutMarginMaxX().
		double layoutMarginMaxX = pInfo->layoutMarginMaxX();
		AcDMMEPlotProperty propLayoutMarginMaxX;
		propLayoutMarginMaxX.SetName(L"Layout Margin Max X");
		m_cstr.Format("%g",layoutMarginMaxX);
		m_wchar = A2W(m_cstr);
		propLayoutMarginMaxX.SetValue(m_wchar);
		propLayoutMarginMaxX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propLayoutMarginMaxX);

		// layoutMarginMaxY().
		double layoutMarginMaxY = pInfo->layoutMarginMaxY();
		AcDMMEPlotProperty propLayoutMarginMaxY;
		propLayoutMarginMaxY.SetName(L"Layout Margin Max Y");
		m_cstr.Format("%g",layoutMarginMaxY);
		m_wchar = A2W(m_cstr);
		propLayoutMarginMaxY.SetValue(m_wchar);
		propLayoutMarginMaxY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propLayoutMarginMaxY);

		// printableBoundsX().
		double printableBoundsX = pInfo->printableBoundsX();
		AcDMMEPlotProperty propPrintableBoundsX;
		propPrintableBoundsX.SetName(L"Printable Bounds X");
		m_cstr.Format("%g",printableBoundsX);
		m_wchar = A2W(m_cstr);
		propPrintableBoundsX.SetValue(m_wchar);
		propPrintableBoundsX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPrintableBoundsX);

		// printableBoundsY().
		double printableBoundsY = pInfo->printableBoundsY();
		AcDMMEPlotProperty propPrintableBoundsY;
		propPrintableBoundsY.SetName(L"Printable Bounds Y");
		m_cstr.Format("%g",printableBoundsY);
		m_wchar = A2W(m_cstr);
		propPrintableBoundsY.SetValue(m_wchar);
		propPrintableBoundsY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPrintableBoundsY);

		// maxBoundsX().
		double maxBoundsX = pInfo->maxBoundsX();
		AcDMMEPlotProperty propMaxBoundsX;
		propMaxBoundsX.SetName(L"Max Bounds X");
		m_cstr.Format("%g",maxBoundsX);
		m_wchar = A2W(m_cstr);
		propMaxBoundsX.SetValue(m_wchar);
		propMaxBoundsX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propMaxBoundsX);

		// maxBoundsY().
		double maxBoundsY = pInfo->maxBoundsY();
		AcDMMEPlotProperty propMaxBoundsY;
		propMaxBoundsY.SetName(L"Max Bounds Y");
		m_cstr.Format("%g",maxBoundsY);
		m_wchar = A2W(m_cstr);
		propMaxBoundsY.SetValue(m_wchar);
		propMaxBoundsY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propMaxBoundsY);

		// stepsPerInch().
		double stepsPerInch = pInfo->stepsPerInch();
		AcDMMEPlotProperty propStepsPerInch;
		propMaxBoundsY.SetName(L"Steps per Inch");
		m_cstr.Format("%g",stepsPerInch);
		m_wchar = A2W(m_cstr);
		propMaxBoundsY.SetValue(m_wchar);
		propMaxBoundsY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propMaxBoundsY);

		//configuration()
		const TCHAR* configuration = pInfo->configuration();
		AcDMMEPlotProperty propConfiguration;
		propConfiguration.SetName(L"Configuration");
		if (strcmp(configuration, "") == 0)
			propConfiguration.SetValue(L"Configuration name not defined.");
		else
		{
			m_cstr.Format("%s",configuration);
			m_wchar = A2W(m_cstr);
			propConfiguration.SetValue(m_wchar);
		}
		propConfiguration.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propConfiguration);

		//plotToFilePath()
		const TCHAR* plotToFilePath = pInfo->plotToFilePath();
		AcDMMEPlotProperty propPlotToFilePath;
		propPlotToFilePath.SetName(L"Plot To File Path");
		if (strcmp(plotToFilePath, "") == 0)
			propPlotToFilePath.SetValue(L"Plot To File Path not defined.");
		else
		{
			m_cstr.Format("%s",plotToFilePath);
			m_wchar = A2W(m_cstr);
			propPlotToFilePath.SetValue(m_wchar);
		}
		propPlotToFilePath.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotToFilePath);

		//plotToFileName()
		const TCHAR* plotToFileName = pInfo->plotToFileName();
		AcDMMEPlotProperty propPlotToFileName;
		propPlotToFileName.SetName(L"Plot To File Name");
		if (strcmp(plotToFileName, "") == 0)
			propPlotToFileName.SetValue(L"Plot To File Name not defined.");
		else
		{
			m_cstr.Format("%s",plotToFileName);
			m_wchar = A2W(m_cstr);
			propPlotToFileName.SetValue(m_wchar);
		}
		propPlotToFileName.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotToFileName);

		//caninicalMediaName()
		const TCHAR* caninicalMediaName = pInfo->canonicalMediaName();
		AcDMMEPlotProperty propCaninicalMediaName;
		propCaninicalMediaName.SetName(L"Caninical Media Name");
		if (strcmp(caninicalMediaName, "") == 0)
			propCaninicalMediaName.SetValue(L"Caninical Media Name not defined.");
		else
		{
			m_cstr.Format("%s",caninicalMediaName);
			m_wchar = A2W(m_cstr);
			propCaninicalMediaName.SetValue(m_wchar);
		}
		propCaninicalMediaName.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propCaninicalMediaName);

		/////////////////
		// plotBoundsMinX().
		double plotBoundsMinX = pInfo->plotBoundsMinX();
		AcDMMEPlotProperty propPlotBoundsMinX;
		propPlotBoundsMinX.SetName(L"Plot Bounds Min X");
		m_cstr.Format("%g",plotBoundsMinX);
		m_wchar = A2W(m_cstr);
		propPlotBoundsMinX.SetValue(m_wchar);
		propPlotBoundsMinX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotBoundsMinX);

		// plotBoundsMinY().
		double plotBoundsMinY = pInfo->plotBoundsMinY();
		AcDMMEPlotProperty propPlotBoundsMinY;
		propPlotBoundsMinY.SetName(L"Plot Bounds Min Y");
		m_cstr.Format("%g",plotBoundsMinY);
		m_wchar = A2W(m_cstr);
		propPlotBoundsMinY.SetValue(m_wchar);
		propPlotBoundsMinY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotBoundsMinY);

		// plotBoundsMaxX().
		double plotBoundsMaxX = pInfo->plotBoundsMaxX();
		AcDMMEPlotProperty propPlotBoundsMaxX;
		propPlotBoundsMaxX.SetName(L"Plot Bounds Max X");
		m_cstr.Format("%g",plotBoundsMaxX);
		m_wchar = A2W(m_cstr);
		propPlotBoundsMaxX.SetValue(m_wchar);
		propPlotBoundsMaxX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotBoundsMaxX);

		// plotBoundsMaxY().
		double plotBoundsMaxY = pInfo->plotBoundsMaxY();
		AcDMMEPlotProperty propPlotBoundsMaxY;
		propPlotBoundsMaxY.SetName(L"Plot Bounds Max Y");
		m_cstr.Format("%g",plotBoundsMaxY);
		m_wchar = A2W(m_cstr);
		propPlotBoundsMaxY.SetValue(m_wchar);
		propPlotBoundsMaxY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propPlotBoundsMaxY);

		// layoutBoundsMinX().
		double layoutBoundsMinX = pInfo->layoutBoundsMinX();
		AcDMMEPlotProperty propLayoutBoundsMinX;
		propLayoutBoundsMinX.SetName(L"Layout Bounds Min X");
		m_cstr.Format("%g",layoutBoundsMinX);
		m_wchar = A2W(m_cstr);
		propLayoutBoundsMinX.SetValue(m_wchar);
		propLayoutBoundsMinX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propLayoutBoundsMinX);

		// layoutBoundsMinY().
		double layoutBoundsMinY = pInfo->layoutBoundsMinY();
		AcDMMEPlotProperty propLayoutBoundsMinY;
		propLayoutBoundsMinY.SetName(L"Layout Bounds Min Y");
		m_cstr.Format("%g",layoutBoundsMinY);
		m_wchar = A2W(m_cstr);
		propLayoutBoundsMinY.SetValue(m_wchar);
		propLayoutBoundsMinY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propLayoutBoundsMinY);

		// layoutBoundsMaxX().
		double layoutBoundsMaxX = pInfo->layoutBoundsMaxX();
		AcDMMEPlotProperty propLayoutBoundsMaxX;
		propLayoutBoundsMaxX.SetName(L"Layout Bounds Max X");
		m_cstr.Format("%g",layoutBoundsMaxX);
		m_wchar = A2W(m_cstr);
		propLayoutBoundsMaxX.SetValue(m_wchar);
		propLayoutBoundsMaxX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propLayoutBoundsMaxX);

		// plotBoundsMaxY().
		double layoutBoundsMaxY = pInfo->layoutBoundsMaxY();
		AcDMMEPlotProperty propLayoutBoundsMaxY;
		propLayoutBoundsMaxY.SetName(L"Layout Bounds Max Y");
		m_cstr.Format("%g",layoutBoundsMaxY);
		m_wchar = A2W(m_cstr);
		propLayoutBoundsMaxY.SetValue(m_wchar);
		propLayoutBoundsMaxY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propLayoutBoundsMaxY);

		// effectivePlotOffsetX().
		double effectivePlotOffsetX = pInfo->effectivePlotOffsetX();
		AcDMMEPlotProperty propEffectivePlotOffsetX;
		propEffectivePlotOffsetX.SetName(L"Effective Plot Offset X");
		m_cstr.Format("%g",effectivePlotOffsetX);
		m_wchar = A2W(m_cstr);
		propEffectivePlotOffsetX.SetValue(m_wchar);
		propEffectivePlotOffsetX.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propEffectivePlotOffsetX);

		// effectivePlotOffsetY().
		double effectivePlotOffsetY = pInfo->effectivePlotOffsetY();
		AcDMMEPlotProperty propEffectivePlotOffsetY;
		propEffectivePlotOffsetY.SetName(L"Effective Plot Offset Y");
		m_cstr.Format("%g",effectivePlotOffsetY);
		m_wchar = A2W(m_cstr);
		propEffectivePlotOffsetY.SetValue(m_wchar);
		propEffectivePlotOffsetY.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propEffectivePlotOffsetY);

		// effectivePlotOffsetXdevice().
		int effectivePlotOffsetXdevice = pInfo->effectivePlotOffsetXdevice();
		AcDMMEPlotProperty propEffectivePlotOffsetXdevice;
		propEffectivePlotOffsetXdevice.SetName(L"Effective Plot Offset X Device");
		m_cstr.Format("%d",effectivePlotOffsetXdevice);
		m_wchar = A2W(m_cstr);
		propEffectivePlotOffsetXdevice.SetValue(m_wchar);
		propEffectivePlotOffsetXdevice.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propEffectivePlotOffsetXdevice);

		// effectivePlotOffsetYdevice().
		int effectivePlotOffsetYdevice = pInfo->effectivePlotOffsetYdevice();
		AcDMMEPlotProperty propEffectivePlotOffsetYdevice;
		propEffectivePlotOffsetYdevice.SetName(L"Effective Plot Offset Y Device");
		m_cstr.Format("%d",effectivePlotOffsetYdevice);
		m_wchar = A2W(m_cstr);
		propEffectivePlotOffsetYdevice.SetValue(m_wchar);
		propEffectivePlotOffsetYdevice.SetCategory(L"ParthaSheetProp");
		propVec.push_back(propEffectivePlotOffsetYdevice);

		// Add all properties to the Sheet Info object.
		pInfo->AddPageProperties(propVec); // add props obj to cache

		// Invalid value test.
		if (invalidTest == true)
		{
			AcDMMEPlotPropertyVec pVec100;
			pInfo->AddPageProperties(pVec100);
		}
		
	}
	else // model Layout
	{
		// add a property
		AcDMMEPlotProperty prop(L"ParthaModelProperty", L"ParthaModelValue");
		prop.SetCategory(L"ParthaModelProp");
		AcDMMEPlotPropertyVec propVec;
		propVec.push_back(prop);
		pInfo->AddPageProperties(propVec); // add props obj to cache

		// Invalid value test.
		if (invalidTest == true)
		{
			AcDMMEPlotPropertyVec pVec100;
			pInfo->AddPageProperties(pVec100);
		}

		// add a resource
		AcDMMResourceInfo res(L"ParthaModelResource", L"text", L"C:\\Current Project\\DWFAPI\\DWFs\\Resource-zip.zip");
		USES_CONVERSION;
		// SetRole()
		char* role = "Partha's role";
		res.SetRole(A2W(role));
		const char* outRole = OLE2A(res.GetRole());
		if (strcmp(outRole, role) == 0)
			myPrintf("\nAcDMMResourceInfo::role(), getRole() worked fine.", OUTFILE);
		else
			myPrintf("\nAcDMMResourceInfo::role(), getRole() did not work fine.", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nAcDMMResourceInfo::role(), getRole()");
		// SetMime()
		char* mime = "Partha's mime";
		res.SetMime(A2W(mime));
		const char* outMime = OLE2A(res.GetMime());
		if (strcmp(outMime, mime) == 0)
			myPrintf("\nAcDMMResourceInfo::mime(), getMime() worked fine.", OUTFILE);
		else
			myPrintf("\nAcDMMResourceInfo::mime(), getMime() did not work fine.", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nAcDMMResourceInfo::mime(), getMime()");
		// SetPath()
		char* path = "C:\\Partha's Path";
		res.SetPath(A2W(path));
		const char* outPath = OLE2A(res.GetPath());
		if (strcmp(outPath, path) == 0)
			myPrintf("\nAcDMMResourceInfo::path(), getPath() worked fine.", OUTFILE);
		else
			myPrintf("\nAcDMMResourceInfo::path(), getPath() did not work fine.", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nAcDMMResourceInfo::path(), getPath()");
		// = operator.
		AcDMMResourceInfo res1 = res;
		res1.SetRole(L"Bappa's role");
		const char* outPath1 = OLE2A(res1.GetPath());
		if (strcmp(outPath1, path) == 0)
			myPrintf("\nAcDMMResourceInfo::'=' operator worked fine.", OUTFILE);
		else
			myPrintf("\nAcDMMResourceInfo::'=' operator did not work fine.", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nAcDMMResourceInfo::'=' operator");
		// other constructor;
		AcDMMResourceInfo res2(res1);
		res2.SetRole(L"Anit's role");
		const char* outPath2 = OLE2A(res2.GetPath());
		if (strcmp(outPath2, path) == 0)
			myPrintf("\nAcDMMResourceInfo::other constructor worked fine.", OUTFILE);
		else
			myPrintf("\nAcDMMResourceInfo::other constructor did not work fine.", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nAcDMMResourceInfo::other constructor");

		AcDMMResourceVec resVec;
		resVec.push_back(res);
		resVec.push_back(res1);
		resVec.push_back(res2);
		pInfo->AddPageResources(resVec);

	}
}
void TdDMMReactor::OnEndEntity(AcDMMEntityReactorInfo * pInfo) //#5
{
	if (A3 == false)
	{
		myPrintf("\nTdDMMReactor::OnEndEntity", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nTdDMMReactor::OnEndEntity");
		A3 = true;
	}
}
void TdDMMReactor::OnEndSheet(AcDMMSheetReactorInfo * pInfo) //#6
{
	if (A4 == false)
	{
		myPrintf("\nTdDMMReactor::OnEndSheet", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nTdDMMReactor::OnEndSheet");
		A4 = true;
	}
}
// TdPublishReactor class implementation.
TdPublishReactor::TdPublishReactor()
{
	B1=false;
	B2=false;
	B3=false;
	B4=false;
	B5=false;
	B6=false;
	B7=false;
	B8=false;
}
TdPublishReactor::~TdPublishReactor()
{
	B1=false;
	B2=false;
	B3=false;
	B4=false;
	B5=false;
	B6=false;
	B7=false;
	B8=false;
}
void TdPublishReactor::OnAboutToBeginBackgroundPublishing(AcPublishBeforeJobInfo* pInfo)
{
	if (B1 == false)
	{
		myPrintf("\nTdPublishReactor::OnAboutToBeginBackgroundPublishing", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		B1 = true;
	}

	// check to see if this job is publishing to DWF
	// GetDSDData().
	if (pInfo->GetDSDData()->sheetType() == AcPlDSDEntry::SheetType::kOriginalDevice)
		// not a DWF job, nothing to do here
		return;
	else
		myPrintf("\n Passed: AcPublishBeforeJobInfo::GetDSDData", OUTFILE);

	// WritePrivateSection()
	AcNameValuePairVec valuePairVec;
	AcNameValuePair nameValuePair(_T("Partha_JobBefore_Private_Name"), _T("Partha_JobBefore_Private_Value"));
	// Invalid value test.
	if (invalidTest == true)
	{
		AcNameValuePair nameValuePair100(_T("!@#$^%^*&*&%&*%"), _T("^$$&*%%_*^&*%&$%^"));
	}
	// Invalid value test.
	if (invalidTest == true)
	{
		AcNameValuePair nameValuePair100(_T("!@#$^%^*&*&%&*%"), _T("^$$&*%%_*^&*%&$%^"));
	}
	valuePairVec.push_back(nameValuePair);
	pInfo->WritePrivateSection(_T("Partha JobBefore Private Data"), valuePairVec);

	// Invalid value test.
	if (invalidTest == true)
	{
		AcNameValuePairVec valuePairVec100;
		pInfo->WritePrivateSection(_T("^$$^^"), valuePairVec100);
	}

	//JobWillPublishInBackground
	bool ret = pInfo->JobWillPublishInBackground();
	if (ret == true)
		myPrintf("\nPassed: AcPublishBeforeJobInfo::JobWillPublishInBackground(), publishing background.", OUTFILE);
	else
		myPrintf("\nPassed: AcPublishBeforeJobInfo::JobWillPublishInBackground(), publishing foreground.", OUTFILE);
}
void TdPublishReactor::OnAboutToBeginPublishing(AcPublishBeginJobInfo* pInfo) //#1
{
	if (B2 == false)
	{
		myPrintf("\nTdPublishReactor::OnAboutToBeginPublishing", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nTdPublishReactor::OnAboutToBeginPublishing");
		B2 = true;
	}
	// check to see if this job is publishing to DWF
	// GetDSDData().
	if (pInfo->GetDSDData()->sheetType() == AcPlDSDEntry::SheetType::kOriginalDevice)
		// not a DWF job, nothing to do here
		return;
	else
		myPrintf("\n Passed: AcPublishBeginJobInfo::GetDSDData", OUTFILE);
	pInfo->GetPlotLogger()->logMessage("\nAcPublishBeginJobInfo::GetDSDData");

	// make sure AcEplotX.arx is loaded
	if (!acrxServiceIsRegistered("AcEPlotX")) {
		acrxLoadModule("AcEPlotx.arx", false, false);
	}
	HINSTANCE hInst = NULL;
	hInst = ::GetModuleHandle("AcEPlotX.arx");
	ASSERT(NULL != hInst);
	if ((hInst)) {
		ACGLOBADDDMMREACTOR pAcGlobalAddDMMReactor = NULL;
		pAcGlobalAddDMMReactor = (ACGLOBADDDMMREACTOR)GetProcAddress(hInst, _T("AcGlobAddDMMReactor"));
		ASSERT(NULL != pAcGlobalAddDMMReactor);
		if (NULL != pAcGlobalAddDMMReactor) {
			ASSERT(NULL == g_pDMMReactor);
			g_pDMMReactor = new TdDMMReactor();
			pAcGlobalAddDMMReactor(g_pDMMReactor);
		}
	}
	// here is where we will load the BLK file (if one is configured)
	AcNameValuePairVec valuePairVec;
	// Invalid value test.
	if (invalidTest == true)
	{
		AcNameValuePair nameValuePair100(_T("!@#$^%^*&*&%&*%"), _T("^$$&*%%_*^&*%&$%^"));
	}
	bool bIncludeBlockInfo = false;
	CString csIncludeBlockInfo;
	CString csBlockTmplFilePath;
	valuePairVec = pInfo->GetPrivateData("AutoCAD Block Data");    
	AcNameValuePairVec::const_iterator iter = valuePairVec.begin();
	while (iter != valuePairVec.end()) {
		AcNameValuePair pair = (*iter++);
		CString csName = pair.name();
		CString csValue = pair.value();
		if (csName == _T("IncludeBlockInfo"))
			if (csValue == "1")
				bIncludeBlockInfo = true;
			else
				bIncludeBlockInfo = false;
		if (csName == _T("BlockTmplFilePath"))
			csBlockTmplFilePath = csValue;
	}
	if (bIncludeBlockInfo && !csBlockTmplFilePath.IsEmpty())
	{
		// verify that the file exists?
		g_pDxServices = new CCW_AcPublishMgdServices(csBlockTmplFilePath);
		g_bIncludeBlockInfo = true;
	}
	else
		g_bIncludeBlockInfo = false;

	// WritePrivateSection()
	AcNameValuePairVec valuePairVec1;
	//AcNameValuePair nameValuePair(_T("Partha_JobBegin_Private_Name"), _T("Partha_JobBegin_Private_Value"));
	AcNameValuePair nameValuePair;
	//AcNameValuePair::SetName()
	nameValuePair.setName(_T("Partha_JobBegin_Private_Name"));
	//AcNameValuePair::SetValue()
	nameValuePair.setValue(_T("Partha_JobBegin_Private_Value"));
	//AcNameValuePair::name()
	if (strcmp(nameValuePair.name(), _T("Partha_JobBegin_Private_Name")) == 0)
		myPrintf("\nPassed: AcNameValuePair::name() returned correct name", OUTFILE);
	else
		myPrintf("\nFailed: AcNameValuePair::name() did not return correct name", OUTFILE);
	pInfo->GetPlotLogger()->logMessage("\nAcNameValuePair::name()");
	//AcNameValuePair::value()
	if (strcmp(nameValuePair.name(), _T("Partha_JobBegin_Private_Name")) == 0)
		myPrintf("\nPassed: AcNameValuePair::name() returned correct name", OUTFILE);
	else
		myPrintf("\nFailed: AcNameValuePair::name() did not return correct name", OUTFILE);
	pInfo->GetPlotLogger()->logMessage("\nAcNameValuePair::name()");
	//AcNameValuePair::= operator
	AcNameValuePair nameValuePair1 = nameValuePair;
	//AcNameValuePair::AcNameValuePair(const AcNameValuePair &src)
	AcNameValuePair nameValuePair2(nameValuePair1);

	valuePairVec1.push_back(nameValuePair2);
	pInfo->WritePrivateSection(_T("Partha JobBegin Private Data"), valuePairVec1);

	// Invalid value test.
	if (invalidTest == true)
	{
		AcNameValuePairVec valuePairVec100;
		pInfo->WritePrivateSection(_T("^$$^^"), valuePairVec100);
	}

	//JobWillPublishInBackground
	bool ret = pInfo->JobWillPublishInBackground();
	if (ret == true)
		myPrintf("\nPassed: AcPublishBeginJobInfo::JobWillPublishInBackground(), publishing background.", OUTFILE);
	else
		myPrintf("\nPassed: AcPublishBeginJobInfo::JobWillPublishInBackground(), publishing foreground.", OUTFILE);
	pInfo->GetPlotLogger()->logMessage("\nAcPublishBeginJobInfo::JobWillPublishInBackground()");
}
void TdPublishReactor::OnAboutToEndPublishing(AcPublishReactorInfo *pInfo) //#9
{
	if (B3 == false)
	{
		myPrintf("\nTdPublishReactor::OnAboutToEndPublishing", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		B3 = true;
	}
	//cleaning up DMMReactor
	if (NULL != g_pDMMReactor) {
		HINSTANCE hInst0 = ::GetModuleHandle("AcEPlotX.arx");
		if ((hInst0)) {
			ACGLOBREMOVEDMMREACTOR pAcGlobalRemoveDMMReactor = (ACGLOBREMOVEDMMREACTOR)GetProcAddress(hInst0, "AcGlobRemoveDMMReactor");
				ASSERT(NULL != pAcGlobalRemoveDMMReactor);
			if (NULL != pAcGlobalRemoveDMMReactor)
				pAcGlobalRemoveDMMReactor(g_pDMMReactor);
			else
				AfxMessageBox("\nFailed to remove DMMReactor to the Manager.");
			g_pDMMReactor = NULL;
		}
	}

	// dwfFileName()
	const char* fileName = pInfo->dwfFileName();
	if (strcmp(fileName, "") == 0)
		myPrintf("\nFailed: AcPublishReactorInfo::dwfFileName(), failed to get the DWF file name.", OUTFILE);
	else
		myPrintf("\nPassed: AcPublishReactorInfo::dwfFileName(), got the DWF file name.", OUTFILE);

	// tempDwfFileName()
	const char* tempFileName = pInfo->tempDwfFileName();
	if (strcmp(tempFileName, "") == 0)
		myPrintf("\nFailed: AcPublishReactorInfo::tempDwfFileName(), failed to get the temporary DWF file name.", OUTFILE);
	else
		myPrintf("\nPassed: AcPublishReactorInfo::tempDwfFileName(), got the temporary DWF file name.", OUTFILE);

	// dwfPassword()
	const char* dwfPassword = pInfo->dwfPassword();
	if (strcmp(dwfPassword, "") == 0)
		myPrintf("\nPassed: AcPublishReactorInfo::dwfPassword(), there is no password for this DWF file.", OUTFILE);
	else
		myPrintf("\nPassed: AcPublishReactorInfo::dwfPassword(), got the DWF file password.", OUTFILE);

	// getUnrecognizedDSDData()
	AcArray<char*>* urSectionArray;
	AcArray<char*>* urDataArray;

	pInfo->getUnrecognizedDSDData(urSectionArray, urDataArray);

	int len = urSectionArray->length();
	char* section;
	char* data;
	CString str;
	myPrintf("\nPassed:UnRecognized DSD data:", OUTFILE);
	for (int i=0; i<len; i++)
	{
		section = urSectionArray->at(i);
		data = urDataArray->at(i);
		str.Format("\n\tSection = %s: Data = %s", section, data);
		myPrintf(str, OUTFILE);
	}

	if (pInfo->isMultiSheetDwf())
		myPrintf("\nPassed: It's a Multisheet DWF file.", OUTFILE);
	else
		myPrintf("\nPassed: It's a Single DWF file.", OUTFILE);
}
void TdPublishReactor::OnAboutToMoveFile(AcPublishReactorInfo *pInfo)  //#8
{
	if (B4 == false)
	{
		myPrintf("\nTdPublishReactor::OnAboutToMoveFile", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		B4 = true;
	}
}
void TdPublishReactor::OnBeginAggregation(AcPublishAggregationInfo *pInfo) //#7
{
	if (B5 == false)
	{
		myPrintf("\nTdPublishReactor::OnBeginAggregation", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nTdPublishReactor::OnBeginAggregation");
		B5 = true;
	}

	// addGlobalProperties()
	AcDMMEPlotProperty prop(L"Partha_Global_Property", L"Partha_Global_Value");
	AcDMMEPlotPropertyVec propVec;
	propVec.push_back(prop);
	pInfo->AddGlobalProperties(propVec);
	myPrintf("\nAcPublishAggregationInfo::AddGlobalProperties(), added global properties.", OUTFILE);
	pInfo->GetPlotLogger()->logMessage("\nAcPublishAggregationInfo::AddGlobalProperties()");

	// Invalid value test.
	if (invalidTest == true)
	{
		AcDMMEPlotPropertyVec vec100;
		pInfo->AddGlobalProperties(vec100);
	}

	// addGlobalResources()
	AcDMMResourceInfo res(L"Partha_Global_Resource", L"Partha", L"C:\\Current Project\\DWFAPI\\DWFs\\Volcano_lava.JPG");
	AcDMMResourceVec resVec;
	resVec.push_back(res);
	pInfo->AddGlobalResources(resVec);
	myPrintf("\nAcPublishAggregationInfo::AddGlobalResources(), added global resources.", OUTFILE);
	pInfo->GetPlotLogger()->logMessage("\nAcPublishAggregationInfo::AddGlobalResources()");

	// Invalid value test.
	if (invalidTest == true)
	{
		AcDMMResourceVec res100;
		pInfo->AddGlobalResources(res100);
	}

	// dwfFileName()
	const char* fileName = pInfo->dwfFileName();
	if (strcmp(fileName, "") == 0)
		myPrintf("\nFailed: AcPublishAggregationInfo::dwfFileName(), failed to get the DWF file name.", OUTFILE);
	else
		myPrintf("\nPassed: AcPublishAggregationInfo::dwfFileName(), got the DWF file name.", OUTFILE);
	pInfo->GetPlotLogger()->logMessage("\nAcPublishAggregationInfo::dwfFileName()");

	// tempDwfFileName()
	const char* tempFileName = pInfo->tempDwfFileName();
	// DID #605461: the call returns NULL and crash gere.
	// uncomment when the bug is fixed.
	//if (strcmp(tempFileName, "") == 0)
	//	myPrintf("\nFailed: AcPublishAggregationInfo::tempDwfFileName(), failed to get the temporary DWF file name.", OUTFILE);
	//else
	//	myPrintf("\nPassed: AcPublishAggregationInfo::tempDwfFileName(), got the temporary DWF file name.", OUTFILE);

	// dwfPassword()
	const char* dwfPassword = pInfo->dwfPassword();
	if (strcmp(dwfPassword, "") == 0)
		myPrintf("\nPassed: AcPublishAggregationInfo::dwfPassword(), there is no password for this DWF file.", OUTFILE);
	else
		myPrintf("\nPassed: AcPublishAggregationInfo::dwfPassword(), got the DWF file password.", OUTFILE);
	pInfo->GetPlotLogger()->logMessage("\nAcPublishAggregationInfo::dwfPassword()");
}
void TdPublishReactor::OnBeginPublishingSheet(AcPublishSheetInfo *pInfo) //#2
{
	if (B6 == false)
	{
		myPrintf("\nTdPublishReactor::OnBeginPublishingSheet", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		pInfo->GetPlotLogger()->logMessage("\nTdPublishReactor::OnBeginPublishingSheet");
		B6 = true;
	}

	// check to see if this job is publishing to DWF
	// GetDSDEntity().
	const AcPlDSDEntry* pEntity = pInfo->GetDSDEntry();
	if (pEntity != NULL)
		if ((strcmp(pEntity->dwgName(), "") != 0) &&
			(strcmp(pEntity->layout(), "") != 0))
			myPrintf("\nPassed: AcPublishSheetInfo::GetDSDEntry(): return DSD entity /w valid DWG name and layout name.", OUTFILE);
		else
			myPrintf("\nFailed: AcPublishSheetInfo::GetDSDEntry(): return DSD entity but failed to return valid DWG name and layout name.", OUTFILE);
	else
		myPrintf("\nFailed: AcPublishSheetInfo::GetDSDEntry(): failed to return DSD entity for the sheet.", OUTFILE);
	pInfo->GetPlotLogger()->logMessage("\nAcPublishSheetInfo::GetDSDEntry()");

	// GetUniqueId()
	const char* uniqueId = pInfo->GetUniqueId();
	if (strcmp(uniqueId, "") == 0)
		myPrintf("\nFailed: AcPublishSheetInfo::GetUniqueId(), failed to get the unique ID.", OUTFILE);
	else
		myPrintf("\nPassed: AcPublishSheetInfo::GetUniqueId(), got the unique ID.", OUTFILE);
	pInfo->GetPlotLogger()->logMessage("\nAcPublishSheetInfo::GetUniqueId()");

}
void TdPublishReactor::OnCancelledOrFailedPublishing(AcPublishReactorInfo *pInfo)
{
	if (B7 == false)
	{
		myPrintf("\nTdPublishReactor::OnCancelledOrFailedPublishing", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		B7 = true;
	}
	// Cleaning up all reactors.
	//DMMReactor
	if (NULL != g_pDMMReactor) {
		HINSTANCE hInst0 = ::GetModuleHandle("AcEPlotX.arx");
		if ((hInst0)) {
			ACGLOBREMOVEDMMREACTOR pAcGlobalRemoveDMMReactor = (ACGLOBREMOVEDMMREACTOR)GetProcAddress(hInst0, "AcGlobRemoveDMMReactor");
				ASSERT(NULL != pAcGlobalRemoveDMMReactor);
			if (NULL != pAcGlobalRemoveDMMReactor)
				pAcGlobalRemoveDMMReactor(g_pDMMReactor);
			else
				AfxMessageBox("\nFailed to remove DMMReactor to the Manager.");
			g_pDMMReactor = NULL;
		}
	}
}
void TdPublishReactor::OnEndPublish(AcPublishReactorInfo *pInfo)  //#10
{
	if (B8 == false)
	{
		myPrintf("\nTdPublishReactor::OnEndPublish", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		B8 = true;
	}
}
// TdPublishUIReactor class implementation
TdPublishUIReactor::TdPublishUIReactor()
{
	C1=false;
}
TdPublishUIReactor::~TdPublishUIReactor()
{
	C1=false;
}
void TdPublishUIReactor::OnInitPublishOptionsDialog(IUnknown **pUnk, AcPublishUIReactorInfo *pInfo)
{
	if (C1 == false)
	{
		myPrintf("\nTdPublishUIReactor::OnInitPublishOptionsDialog", OUTFILE);
		myPrintf("\n------------------------------------\n", OUTFILE);
		C1 = true;
	}

	// check to see if this job is publishing to DWF
	// GetDSDData().
	if (pInfo->GetDSDData()->sheetType() == AcPlDSDEntry::SheetType::kOriginalDevice)
		// not a DWF job, nothing to do here
		return;

	// WritePrivateSection()
	AcNameValuePairVec valuePairVec1;
	AcNameValuePair nameValuePair1(_T("Partha_PublishOption_Private_Name1"), _T("Partha_PublishOption_Private_Value1"));
	// Invalid value test.
	if (invalidTest == true)
	{
		AcNameValuePair nameValuePair100(_T("!@#$^%^*&*&%&*%"), _T("^$$&*%%_*^&*%&$%^"));
	}
	valuePairVec1.push_back(nameValuePair1);
	pInfo->WritePrivateSection(_T("Partha PublishOption Private Data1"), valuePairVec1);

	AcNameValuePairVec valuePairVec2;
	AcNameValuePair nameValuePair2(_T("Partha_PublishOption_Private_Name2"), _T("Partha_PublishOption_Private_Value2"));
	valuePairVec2.push_back(nameValuePair2);
	pInfo->WritePrivateSection(_T("Partha PublishOption Private Data2"), valuePairVec2);

	AcNameValuePairVec valuePairVec3;
	AcNameValuePair nameValuePair3(_T("Partha_PublishOption_Private_Name3"), _T("Partha_PublishOption_Private_Value3"));
	valuePairVec3.push_back(nameValuePair3);
	pInfo->WritePrivateSection(_T("Partha PublishOption Private Data3"), valuePairVec3);

	// get the a specific data and change it.
	const AcNameValuePairVec pPairVec = pInfo->GetPrivateData(_T("Partha PublishOption Private Data2"));
	// Invalid value test.
	if (invalidTest == true)
	{
		AcNameValuePair nameValuePair100(_T("!@#$^%^*&*&%&*%"), _T("^$$&*%%_*^&*%&$%^"));
	}
	int size = pPairVec.size();
	for (int i = 0; i < size; i++) {
		CString name, value, str;
		AcNameValuePair pPair = pPairVec.at(i);
		name = pPair.name();
		value = pPair.value();
		str = "\nPassed: Name-Value  of the private 2nd private data written is " + name + "," + value;
		myPrintf(str, OUTFILE);
	}
	
	// add a new property in the publish-options dialog.
	//CComPtr<IPropertyManager2> pPropMan;
	//(*pUnk)->QueryInterface(IID_IPropertyManager2, (void **)&pPropMan);


	//JobWillPublishInBackground
	bool ret = pInfo->JobWillPublishInBackground();
	if (ret == true)
		myPrintf("\nPassed: AcPublishUIReactorInfo::JobWillPublishInBackground(), publishing background.", OUTFILE);
	else
		myPrintf("\nPassed: AcPublishUIReactorInfo::JobWillPublishInBackground(), publishing foreground.", OUTFILE);
}

/*
//prepared for DevDays PPT. At run time enable above code and disable following code
void AcTestDMMEntReactor:: OnBeginEntity(AcDMMEntityReactorInfo * pInfo)
{	
	int nNodeId = 0;
	bool bRet = pInfo->GetEntityNode(pInfo->entity()->objectId(),0, nNodeId);
	if (!bRet)
	{
		//step1: Detect your entity
		AcDbEntity* pEntity = pInfo->entity();

		//step2: container for object's metadata
		AcDMMEPlotProperties props;

		//step3: Assume we want to get the handle of object and publish same as metadata
		AcDMMEPlotProperty * entityProp1 = new AcDMMEPlotProperty(L"Handle", locale_to_wchar(m_EntGenralPorps.m_chHandle));
		entityProp1->SetCategory(L"DMMAPI");
		

		//step4:Add each of AcDMMEPlotProperty objects to the AcDMMEPlotProperties 
		props.AddProperty(entityProp1);
		
		//step5:Generate a unique ID, Assign same ID to props
		const wchar_t * wsUnique = pInfo->UniqueEntityId();
		AcDMMWideString wsPropId; // need a unique string id for properties
		wsPropId =  L"ACAD";	  //application name (optional)
		wsPropId += wsUnique;
		delete wsUnique;
		props.SetId(PCWIDESTR(wsPropId));
		pInfo->AddProperties(&props);

		//step6:To associate the metadata to a graphic object we need NodeId:
		int nodeId = pInfo->GetNextAvailableNodeId();
		// create a Node for this entity
		AcDMMNode node(nodeId, L"dummy");

		AcDMMStringVec IdVec;
		IdVec.push_back(wsPropId);
		
		//step7: assign node to entity
		bRet = pInfo->AddNodeToMap(pEntity->objectId(), 0, nodeId);

		// step8: Now associate your properties with this node by calling AddPropertiesIds() 
		pInfo->AddPropertiesIds(&IdVec, node);
	}

}
*/
void AcTestDMMEntReactor::ProcessBlocks(AcDMMEntityReactorInfo * pInfo)
{
	AcDbEntity* pEntity = pInfo->entity();
	AcDbObjectId objId = pEntity->objectId();
	long oldId = objId.asOldId();
	bool bret;
	//unsigned long front = 0;
	AcDbObjectIdArray objectIds;

	if (pEntity->isKindOf(AcDbBlockReference::desc())) // block
	{
		pInfo->GetPlotLogger()->logMessage("\nBlock FOUND, assigning metadata properties to it");

		// Add the object Id to the objectIds array.
		objectIds.append(objId);

		// get the block name.
		AcDbBlockReference* pBlkRef = 0;
		const char* blkName = 0;
		if(acdbOpenObject(pBlkRef, objId, AcDb::kForRead) == Acad::eOk)
		{
			AcDbBlockTableRecord* pTblRec = 0;

			if(acdbOpenObject(pTblRec, pBlkRef->blockTableRecord(), AcDb::kForRead) == Acad::eOk)
			{
				pTblRec->getName(blkName);
				pTblRec->close();
				
			}
			pBlkRef->close();
		}	
		g_entIdVec.push_back(oldId);
		//front = g_entIdVec.front();
		AcDMMEPlotPropertyVec propVec;

		// FIRST SET OF PROPERTIES.
		AcDMMEPlotProperties props;
		//add properties to prop objects.
		AcDMMEPlotPropertyVec::const_iterator iter = propVec.begin();
		// get all the standard meta properties and write them in the new
		// property collection.
		while (iter != propVec.end())
		{
			AcDMMEPlotProperty prop = (*iter++);
			props.AddProperty(&prop);
		}
		// write a custom property.
		AcDMMEPlotProperty prop1(L"TestProperty", L"TestValue");
		prop1.SetType(L"string");

		USES_CONVERSION;
		if (blkName != "")
			prop1.SetCategory(A2W(blkName));
		else
			prop1.SetCategory(L"Custom Catagory1");
		props.AddProperty(&prop1);

		const wchar_t* wsUnique = pInfo->UniqueEntityId();
		//step5:Generate a unique ID, Assign same ID to props
		AcDMMWideString wsPropId; // need a unique string id for properties
		wsPropId =  L"ACAD";
		wsPropId += wsUnique;
		delete wsUnique;
		props.SetId(PCWIDESTR(wsPropId));
		pInfo->AddProperties(&props); // add props obj to cache
	

		// string Vector
		AcDMMStringVec IdVec;
		IdVec.push_back(wsPropId);

		int nodeId = 0;
		const AcDMMNode* node;
		// check to see if this node already assigned
		if(!pInfo->GetEntityNode(objId, objectIds, nodeId))
		{
			// create a node for this entity.
			nodeId = pInfo->GetNextAvailableNodeId();
			node = new AcDMMNode(nodeId, L"PARTHA");			
			bret = pInfo->AddNodeToMap(objId, 0, nodeId);
			ASSERT(bret);									
			g_NodeStack.push(nodeId);
			// associate the properties with the node.
			bret = pInfo->AddPropertiesIds(&IdVec, (AcDMMNode &)*node);
			
		}
	}

}