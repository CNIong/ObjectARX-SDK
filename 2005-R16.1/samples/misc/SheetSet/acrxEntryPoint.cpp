// (C) Copyright 1990-2003 by Autodesk, Inc. 
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
//----- acrxEntryPoint.h
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "ss.h"
#include "io.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

//-----------------------------------------------------------------------------
#define szRDS _RXST("Asdk")

CString csModulePath;

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CSheetSetApp : public AcRxArxApp {

public:
	CSheetSetApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		// TODO: Add your initialization code here
		acutPrintf("\nEnter 'SSC' to create a sheet set");
		acutPrintf("Enter 'SSList' to list a sheet set");
		
		// Get the module path.
		HMODULE hMod=GetModuleHandle("AsdkSheetSet.arx");
		char szModulePath[MAX_PATH];
		GetModuleFileName(hMod,szModulePath,MAX_PATH);
        csModulePath=(CString)szModulePath;
		csModulePath=csModulePath.Left(csModulePath.ReverseFind('\\'));
		return (retCode) ;

	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		
		// necessary to relase all pointers and unlock database when done!!
		ss.cleanup();
		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}


	// ----- AsdkSheetSet._CreateSheetSet command (do not rename)
	static void AsdkSheetSet_SSC(void)
	{
		HRESULT hr;
		
		// start with a clean sheet set
		ss.cleanup();
		
		char name[MAX_PATH];
		char path[MAX_PATH];
		
		
        int retval = acedGetString(TRUE, "\nNew Sheet Set file name (no extension required): ", name);

        if (RTCAN == retval || RTNONE == retval || (strcmp(name, "") == 0))
        {
            acutPrintf("\nInvalid Input.");
            return;
        }
	  
       acutPrintf("\n Browse to location where you want to create the sheet set: ");
	   
	   // Get path from the user using file dialog
	   struct resbuf *rb = acutNewRb(RTSTR);
	   if (RTNORM == acedGetFileNavDialog("Browse location",NULL,NULL, NULL, 2048, &rb)) 
		  strcpy(path, rb->resval.rstring);
	   else
	   {   
			acutPrintf("\n**Error**");
			acutRelRb(rb);
			return;	
		}

        acutRelRb(rb);
        
		// Create a sheet set
		hr = ss.create(name,                    // file name will have extension *.dst
					   path,                    // folder where *.dst will be created
				       "This is my sheet set"   // description
				      );
				      

		if(FAILED(hr))
		{
		  return;
		}
		
		// Notify start
		ss.subscribeToNotifications();

		// Add custom properties at the sheet set level
		// The custom propety (key-value pair) will be
		// inherited by all the sheets in the sheet set
		ss.addCustomProperty("Custom Property 1", "XXXXX");
		ss.addCustomProperty("Custom Property 2", "YYYYY");

		// Add sheets
		CComPtr<IAcSmSheet> pSheet1, pSheet2, pSheet3, pSheet4;

		
		
		// Add sheet1 to root
		CString csFileName=csModulePath + "\\sheet1.dwg";
		ss.addSheet(&pSheet1,							// Output new sheet
					NULL,                               // Parent category is the sheet set itself
					"sheet1",							// Sheet name
					"This is sheet 1",					// Sheet description
					"Sheet 1",					// Layout name
					csFileName.GetBuffer());  // Layout drawing


					
		CComPtr<IAcSmSubset> pCategoryX, pCategoryXX;
		
		// Create a new category "Site Details" under root sheet set
		ss.createNestedCategory("Category X",
		                        "This is category X",
		                        NULL,
		                        &pCategoryX);
		                        
		// Create a new category under category "Site Details"
        ss.createNestedCategory("Nested Category X",
                                "This is a nested category X",
                                 pCategoryX,
                                 &pCategoryXX);

		
		// Add sheet2 based on a layout to category "Site details"
		csFileName=csModulePath + "\\sheet2.dwg";
		ss.addSheet(&pSheet2,													   // Output new sheet
					pCategoryX,                                                    // Parent category
					"sheet 2",									                   // Sheet name
					"This is sheet 2",							                   // Sheet description
					"Sheet 2",									                   // Layout name
					csFileName.GetBuffer());  // Layout drawing path
		
					
		csFileName=csModulePath + "\\sheet3.dwg";
		ss.addSheet(&pSheet3,
					pCategoryXX,
					"Sheet 3",
					"This is sheet 3",
					"Sheet 3",
					csFileName.GetBuffer());
		
		// Add custom property for sheet1
		ss.addCustomProperty("ABCD",   // Key
							 "####",   // Value
							 pSheet1); // Component to add property to

		// Add a resource location to the sheet set
		ss.addResourceFileLocation(csModulePath.GetBuffer());

		// Add label block to the sheet set
		csFileName=csModulePath + "\\Label Block.dwg";
		if(_access(csFileName, 0) != -1)
			ss.addLabelBlock("Label", csFileName.GetBuffer());
		else
			acutPrintf("\n %s does not exist", csFileName.GetBuffer());
		
		// Add a callout blocks
		
		// block 'Right'
		csFileName=csModulePath + "\\Pointer Blocks.dwg";
		
		ss.addCalloutBlock("Right", csFileName.GetBuffer());

		// block 'Left'
		ss.addCalloutBlock("Left", csFileName.GetBuffer());

		// block 'Up'
		ss.addCalloutBlock("Up", csFileName.GetBuffer());

		// block 'down'
		ss.addCalloutBlock("Down", csFileName.GetBuffer());
							
		// Add Selection Set (of sheets) to the sheet set
		CComPtr<IAcSmSheetSelSet> pSheetSelSet;

		ss.addSheetSelectionSet("MySelectionSet",			// Selection set name
						       "This is my selection set",  // Selection set description
							   &pSheetSelSet				// Output selection set
							   );

		//Kalvaik - Added locking and unlocking database
		//Lock the database
		ss.LockDatabase();
		// Add the three sheets created to the sheet sel set
		if(pSheetSelSet)
		{
			pSheetSelSet->Add(pSheet1);
			pSheetSelSet->Add(pSheet2);
			pSheetSelSet->Add(pSheet3);
		}
		
		//Unlock the database
		ss.UnlockDatabase();
		// Notify End
		ss.unsubscribeToNotifications();

	}

	static void AsdkSheetSet_SSList(void)
	{


		// Get the user to select a sheet set (extn *.dst)
		// SSC will create one for example. File name = MySheetSet.dst
		 char *fname;
		 struct resbuf *rb;
		// Get a dwg file from the user.
		//
		rb = acutNewRb(RTSTR);
		if(RTNORM != acedGetFileD("Pick a sheet set file", NULL, "dst", 0, rb))
		{
			acutRelRb(rb);
			return;
		}
		fname = (char*)acad_malloc(strlen(rb->resval.rstring) + 1);
		strcpy(fname, rb->resval.rstring);
		acutRelRb(rb);
		
		CComBSTR bstrName(fname);
		CComPtr<IAcSmSheetSetMgr> pSSetMgr;
		CComPtr<IAcSmSheetSet> pSheetSet; 
		CComPtr<IAcSmDatabase> pDb;
		bool openNew = false;

		 if (FAILED(pSSetMgr.CoCreateInstance(CLSID_AcSmSheetSetMgr)))
		{
			acutPrintf("\n Cannot get sheet set manager");
			acad_free(fname);
			return;
		}

		// create the database for the sheet set
		// bAlwaysCreate lets you override the existing file if it's set to true
		if(SUCCEEDED(pSSetMgr->FindOpenDatabase(bstrName, &pDb)))
		{
			acutPrintf("\n Database already open");
		}
		// else open existing database
		// the second parameter = TRUE indicates 
		// the function will fail if a database is already open
		else if (SUCCEEDED(pSSetMgr->OpenDatabase(bstrName, TRUE, &pDb)))
		{
			openNew = true;
		} 
		else
		{
			acutPrintf("\n Cannot open database");
			acad_free(fname);
			return;
		}

		// List the sheet set
		if(FAILED(AsdkSheetSet::List(pDb)))
		{
			acutPrintf("\n List Failed");
		}

		// If open by us, we close it ourselves
		if(openNew)
		{
			pSSetMgr->Close(pDb);
		}

		acad_free(fname);
	}

	// Start notification
	static void AsdkSheetSet_SSNotify(void)
	{
		ss.subscribeToNotifications();
	}

	// Stop notification
	static void AsdkSheetSet_SSUnNotify(void)
	{
		ss.unsubscribeToNotifications();
	}

	// List all open databases
	static void AsdkSheetSet_SSListAll(void)
	{
		CComPtr<IAcSmSheetSetMgr> pSSetMgr;
		CComPtr<IAcSmDatabase> pDb;
		HRESULT hr;

		 if (FAILED(pSSetMgr.CoCreateInstance(CLSID_AcSmSheetSetMgr)))
		{
			acutPrintf("\n Cannot get sheet set manager");
			return;
		}

		CComPtr<IAcSmEnumDatabase> pDbEnumerator;

		// Enumerate through all open databases
		pSSetMgr->GetDatabaseEnumerator(&pDbEnumerator);
		CComPtr<IAcSmDatabase> pItem;

		while(SUCCEEDED(hr=pDbEnumerator->Next(&pItem)) && pItem)
		{
			AsdkSheetSet::List(pItem);
		}
	}

	static AsdkSheetSet ss;  // Sheet set variable
} ;

// Initialize static class variable
AsdkSheetSet CSheetSetApp::ss;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CSheetSetApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CSheetSetApp, AsdkSheetSet, _SSC, SSC, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSheetSetApp, AsdkSheetSet, _SSList, SSList, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSheetSetApp, AsdkSheetSet, _SSNotify, SSNotify, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSheetSetApp, AsdkSheetSet, _SSUnNotify, SSUnNotify, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSheetSetApp, AsdkSheetSet, _SSListAll, SSListAll, ACRX_CMD_TRANSPARENT, NULL)
