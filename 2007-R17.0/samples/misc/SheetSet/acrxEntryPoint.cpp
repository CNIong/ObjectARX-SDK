// (C) Copyright 1990-2006 by Autodesk, Inc. 
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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ss.h"
#include "io.h"
#include "AcString.h"



CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

//-----------------------------------------------------------------------------
#define szRDS _RXST("Asdk")

AcString csModulePath;

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CSheetSetApp : public AcRxArxApp {

public:
  CSheetSetApp () : AcRxArxApp () {}

  virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
    AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
    // TODO: Add your initialization code here
    acutPrintf(_T("\nEnter 'SSC' to create a sheet set"));
    acutPrintf(_T("\nEnter 'SSList' to list a sheet set"));

    // Get the module path.
    HMODULE hMod=GetModuleHandle(_T("AsdkSheetSet.arx"));
    TCHAR szModulePath[MAX_PATH];
    GetModuleFileName(hMod,szModulePath,MAX_PATH);
    csModulePath=(AcString)szModulePath;
    csModulePath=csModulePath.substr(csModulePath.findRev(_T('\\')));
    return (retCode) ;

  }

  virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
    AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

    // necessary to relase all pointers and unlock database when done!!
    cleanup();
    return (retCode) ;
  }

  virtual void RegisterServerComponents () {
  }


  // ----- AsdkSheetSet._CreateSheetSet command (do not rename)
  static void AsdkSheetSet_SSC(void)
  {
    HRESULT hr;

    // start with a clean sheet set
    cleanup();

    TCHAR nameIn[MAX_PATH];
    int retval = acedGetString(TRUE, _T("\nNew Sheet Set file name (no extension required): "), nameIn);
    AcString name(nameIn);

    if (RTCAN == retval || RTNONE == retval || (name.length() < 1))
    {
      acutPrintf(_T("\nInvalid Input."));
      return;
    }

    acutPrintf(_T("\n Browse to location where you want to create the sheet set: "));

    // Get path from the user using file dialog
    struct resbuf *rb = acutNewRb(RTSTR);
    TCHAR pathIn[MAX_PATH];
    if (RTNORM == acedGetFileNavDialog(_T("Browse location"),NULL,NULL, NULL, 2048, &rb)) 
      _tcscpy(pathIn, rb->resval.rstring);
    else
    {   
      acutPrintf(_T("\n**Error**"));
      acutRelRb(rb);
      return;	
    }

    AcString path(pathIn);
    acutRelRb(rb);

    AcString templPath, defaultSheetLoc;

    // Create a sheet set
    // Note: This function locks the database by default
    // Make sure you unlock the db when finished
    hr = createSheetSet(name,                    // file name will have extension *.dst
      path,                    // folder where *.dst will be created
      AcString(_T("This is my sheet set")),   // description
      templPath,
      defaultSheetLoc
      );


    if(FAILED(hr))
    {
      cleanup();
      return;
    }

    // Lock the database to modify objects.

    // Best Practice :
    // Db should only be locked when you plan to make changes and should
    // be locked and unlocked as few times as possible.
    if(FAILED(LockDatabase()))
      acutPrintf(_T("\nDatabase lock failed"));


    // Notify start
    subscribeToNotifications();

    // Add custom properties at the sheet set level
    // The custom propety (key-value pair) will be
    // inherited by all the sheets in the sheet set
    if(FAILED(addCustomProperty(_T("Custom Property 1"), _T("XXXXX"), NULL, (PropertyFlags)CUSTOM_SHEET_PROP)))
      acutPrintf(_T("\nError: Cannot add custom property 1"));
    if(FAILED(addCustomProperty(_T("Custom Property 2"), _T("YYYYY"), NULL, (PropertyFlags)CUSTOM_SHEET_PROP)))
      acutPrintf(_T("\nError: Cannot add custom property 2"));


    CComPtr<IAcSmObjectId> pSheet1Id, pSheet2Id, pSheet3Id; //Modified 2/2/05


    // Add sheet1 to root
    AcString csFileName=csModulePath + _T("\\sheet1.dwg");
    if(FAILED(addSheet(&pSheet1Id,					// Output new sheet //Modified 2/2/05
      NULL,                               // Parent category is the sheet set itself
      _T("sheet1"),							// Sheet name
      _T("This is sheet 1"),					// Sheet description
      _T("Sheet 1"),							// Layout name
      csFileName)))						// Layout drawing
    {
      acutPrintf(_T("\nError: Cannot add sheet1"));
    }


    CComPtr<IAcSmObjectId> pCategoryXId, pCategoryXXId; //Modified 2/2/05

    // Create a new category X under root sheet set
    if(FAILED(createNestedCategory(_T("Category X"),
      _T("This is category X"),
      NULL,
      &pCategoryXId))) //Modified 2/2/05
      acutPrintf(_T("\nError: Cannot create CategoryX"));

    // Create a new nested category under category XX
    if(FAILED(createNestedCategory(_T("Nested Category XX"),
      _T("This is a nested category XX"),
      pCategoryXId,
      &pCategoryXXId))) //Modified 2/2/05
      acutPrintf(_T("\nError: Cannot create nested categoryXX"));

    // Add sheet2 based on a layout to category X
    csFileName=csModulePath + _T("\\sheet2.dwg");
    if(FAILED(addSheet(&pSheet2Id,													   // Output new sheet
      pCategoryXId,                                                    // Parent category
      _T("sheet 2"),									                   // Sheet name
      _T("This is sheet 2"),							                   // Sheet description
      _T("Sheet 2"),									                   // Layout name
      csFileName)))  // Layout drawing path	
    {
      acutPrintf(_T("\nError: Cannot add sheet2"));
    }

    csFileName=csModulePath + _T("\\sheet3.dwg");
    if(FAILED(addSheet(&pSheet3Id,
      pCategoryXXId,
      _T("Sheet 3"),
      _T("This is sheet 3"),
      _T("Sheet 3"),
      csFileName)))
    {
      acutPrintf(_T("\nError: Cannot add sheet3"));
    }


    // Add custom property for sheet1
    if(FAILED(addCustomProperty(_T("ABCD"),   // Key
      _T("####"),   // Value
      pSheet1Id,  // Component to add property to
      (PropertyFlags)CUSTOM_SHEET_PROP)))
    {
      acutPrintf(_T("\nError: Cannot add custom property"));
    }


    // Add a resource location to the sheet set
    if(FAILED(addResourceFileLocation(csModulePath)))
    {
      acutPrintf(_T("\nError: Cannot add resource file location"));
    }

    // Add label block to the sheet set
    csFileName=csModulePath + _T("\\Label Block.dwg");
    if(_taccess(csFileName, 0) != -1)
    {
      if(FAILED(addLabelBlock(_T("Label"), csFileName)))
        acutPrintf(_T("\nError: Cannot add label block"));
    }
    else
    {
      acutPrintf(_T("\n %s does not exist"), csFileName.kTCharPtr());
    }

    // Add a callout blocks

    // block 'Right'
    csFileName=csModulePath + _T("\\Pointer Blocks.dwg");

    if(FAILED(addCalloutBlock(_T("Right"), csFileName)))
      acutPrintf(_T("Error: Cannot add callout block Right"));

    // block 'Left'
    if(FAILED(addCalloutBlock(_T("Left"), csFileName)))
      acutPrintf(_T("Error: Cannot add callout block Left"));

    // block 'Up'
    if(FAILED(addCalloutBlock(_T("Up"), csFileName)))
      acutPrintf(_T("\nError: Cannot add callout block Up"));

    // block 'down'
    if(FAILED(addCalloutBlock(_T("Down"), csFileName)))
      acutPrintf(_T("\nError: Cannot add calloutblock Down"));

    // Get sheet Selection Set 
    CComPtr<IAcSmObjectId> pSheetSelSetId; // Modified 2/2/05

    if(FAILED(addSheetSelectionSet(_T("MySelectionSet"),			// Selection set name
      _T("This is my selection set"),  // Selection set description
      &pSheetSelSetId				// Output selection set
      )))
      acutPrintf(_T("Error: Cannot add sheet selection set"));


    // Notify End
    if(FAILED(unsubscribeToNotifications()))
      acutPrintf(_T("Error: unsubscribeToNotifications failed!"));

    //Unlock the database
    if(FAILED(UnlockDatabase()))
      acutPrintf(_T("Error: Database unlock Failed!!"));

    // Best practice :
    // Do not directly cache pointers to sheet set objects. Use objectids. 
    // A reload of the db that occurs on lock, or unlock will cause 
    // object pointers to become invalid. ObjectIds avoid this issue.
    // In other words... Object instances should not be directly accessed 
    // after the db has been unlocked. If you need to access a sheet set resident
    // object after an unlock call, store the id, unlock, and then use 
    // the id to get the instance of the object.

    CComQIPtr<IAcSmSheet> pSheet1, pSheet2, pSheet3;
    CComPtr<IAcSmPersist> pSheet1Pers, pSheet2Pers, pSheet3Pers;
    CComQIPtr<IAcSmSheetSelSet> pSheetSelSet;
    CComPtr<IAcSmPersist> pSheetSelSetPers;

    // Get object pointers from cached objectIds
    if(pSheet1Id.p)
    {
      pSheet1Id->GetPersistObject(&pSheet1Pers);
      pSheet1 = pSheet1Pers;
    }
    if(pSheet2Id.p)
    {
      pSheet2Id->GetPersistObject(&pSheet2Pers);
      pSheet2 = pSheet2Pers;
    }
    if(pSheet3Id.p)
    {
      pSheet3Id->GetPersistObject(&pSheet3Pers);
      pSheet3 = pSheet3Pers;
    }

    // Get object from ObjectId //Modified 2/2/05
    if(pSheetSelSetId.p)
    {
      pSheetSelSetId->GetPersistObject(&pSheetSelSetPers); //Modified 2/2/05
      pSheetSelSet = pSheetSelSetPers;
    }

    //Before modifying, lock the database
    if(FAILED(LockDatabase()))
      acutPrintf(_T("Error: Database lock Failed!!"));

    // Add the three sheets created to the sheet sel set
    if(pSheetSelSet)
    {
      pSheetSelSet->Add(pSheet1);
      pSheetSelSet->Add(pSheet2);
      pSheetSelSet->Add(pSheet3);
    }

    // Unlock the Db
    if(FAILED(UnlockDatabase()))
      acutPrintf(_T("Error: Database unlock Failed!!"));

    // Cleanup all pointers
    cleanup();

  }

  static void AsdkSheetSet_SSList(void)
  {


    // Get the user to select a sheet set (extn *.dst)
    // SSC will create one for example. File name = MySheetSet.dst
    struct resbuf *rb;
    // Get a dwg file from the user.
    //
    rb = acutNewRb(RTSTR);
    if(RTNORM != acedGetFileD(_T("Pick a sheet set file"), NULL, _T("dst"), 0, rb))
    {
      acutRelRb(rb);
      return;
    }

    CComBSTR bstrName(rb->resval.rstring); 
    acutRelRb(rb);

    CComPtr<IAcSmSheetSetMgr> pSSetMgr;
    CComPtr<IAcSmSheetSet> pSheetSet; 
    CComPtr<IAcSmDatabase> pDb;
    bool openNew = false;

    if (FAILED(pSSetMgr.CoCreateInstance(CLSID_AcSmSheetSetMgr)))
    {
      acutPrintf(_T("\n Cannot get sheet set manager"));
      return;
    }

    // create the database for the sheet set
    // bAlwaysCreate lets you override the existing file if it's set to true
    if(SUCCEEDED(pSSetMgr->FindOpenDatabase(bstrName, &pDb)))
    {
      acutPrintf(_T("\n Database already open"));
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
      acutPrintf(_T("\n Cannot open database"));
      return;
    }

    // List the sheet set
    if(FAILED(ListSheetSet(pDb)))
    {
      acutPrintf(_T("\n List Failed"));
    }

    // Note: No need to close the db. If we're only one referencing the db, it will automatcally
    // close when pDb goes out of scope and releases the interface pointer.
  }

  // List all open databases
  static void AsdkSheetSet_SSListAll(void)
  {
    CComPtr<IAcSmSheetSetMgr> pSSetMgr;
    CComPtr<IAcSmDatabase> pDb;
    HRESULT hr;

    if (FAILED(pSSetMgr.CoCreateInstance(CLSID_AcSmSheetSetMgr)))
    {
      acutPrintf(_T("\n Cannot get sheet set manager"));
      return;
    }

    CComPtr<IAcSmEnumDatabase> pDbEnumerator;

    // Enumerate through all open databases
    if(FAILED(pSSetMgr->GetDatabaseEnumerator(&pDbEnumerator))) 
    {
      acutPrintf(_T("\nError: Cannot get database enumerator!"));
      return;
    }

    if(!pDbEnumerator)
    {
      acutPrintf(_T("\nError: Database enumerator is NULL!"));
      return;
    }

    CComPtr<IAcSmDatabase> pItem;

    // Note: Next returns S_FALSE when done which is not an error so SUCCEEDED returns true. 
    while ((pDbEnumerator->Next(&pItem) == S_OK) && (pItem != NULL)) 
    {
      ListSheetSet(pItem);        
    }

  }

} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CSheetSetApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CSheetSetApp, AsdkSheetSet, _SSC, SSC, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSheetSetApp, AsdkSheetSet, _SSList, SSList, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSheetSetApp, AsdkSheetSet, _SSListAll, SSListAll, ACRX_CMD_TRANSPARENT, NULL)
