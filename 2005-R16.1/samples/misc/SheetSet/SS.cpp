//
//
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


#include "stdafx.h"
#include "ss.h"
#include "io.h"
					 				 	 
	
bool isValid(char *name) 
{
	if( !name || strcmp(name,"") == 0 ||  strcmp(name," ") == 0 )
		return false; 
	else			
		return true; 
}

// get yes or no choice from the user
bool getYorN(char *msg)
{

	int res, retcode;
	char kw[4];
	acutPrintf("\n %s [Yes/No]", msg);
	do
	{
		acedInitGet(RSG_NONULL, "Yes No");
		retcode = acedGetInt(NULL, &res);
		switch (retcode)
		{
			case RTKWORD:
				if(acedGetInput(kw) != RTNORM)
				{
					acutPrintf("\nError getting Yes/No choice");
					return false;
				}

				if(strcmp(kw, "Yes") == 0)
				{
					return true;
				}
				else if(strcmp(kw, "No") == 0)
				{
					return false;	
				}
				else
				{
					acutPrintf("\nKeyword Error!!");
					return false;
				}
				break;
			default:
				acutPrintf("\n Enter <Yes/No> :");
				break;
			
		}
	} while(retcode != RTKWORD);
	
	return true;
	
}

HRESULT
AsdkSheetSet::isInitialized(char *funcName)
{
	if(!m_pSSetMgr.p)
	{
		acutPrintf("\n %s Failed! m_pSSetMgr = NULL!!!", funcName);
		return E_FAIL;
	}

	if(!m_pSheetSet.p)
	{
		acutPrintf("\n %s Failed! m_pSheetSet = NULL!!!", funcName);
		return E_FAIL;
	}

	if(!m_pDb.p)
	{
		acutPrintf("\n %s Failed! m_pDb = NULL!!!", funcName);
		return E_FAIL;
	}

	return S_OK;
}

HRESULT
AsdkSheetSet::List(IAcSmDatabase *pDb)
{
	// List the contents of the sheet set at the command line

	HRESULT hr;

	if(!pDb)
		return E_FAIL;

	CComPtr<IAcSmEnumPersist> pEnum;
    CComPtr<IAcSmPersist> pItem;

    pDb->GetEnumerator(&pEnum);
	pEnum->Reset();

	acutPrintf("\n ********  BEGIN  ************** ");
	acutPrintf("\n");
	while(SUCCEEDED(hr=pEnum->Next(&pItem)) && pItem)
    {
        CComQIPtr<IAcSmSubset> pSubSet = pItem;
		CComQIPtr<IAcSmSheet> pSheet = pItem;
		CComQIPtr<IAcSmCustomPropertyBag> pPropertyBag = pItem;
		CComBSTR bstrTypeName;

		char name[80];
		char desc[255];

        if (pSubSet != NULL)
        {
			BSTR bstrSubsetName;
			BSTR bstrSubSetDesc;
			pSubSet->GetName(&bstrSubsetName);
			pSubSet->GetDesc(&bstrSubSetDesc);
			strcpy(name, _bstr_t(bstrSubsetName).operator char*());
			strcpy(desc, _bstr_t(bstrSubSetDesc).operator char*());
			acutPrintf("\n -------------------------------");
			acutPrintf("\n SubSet Name : %s", name);
			acutPrintf("\n Description : %s", desc);
			acutPrintf("\n -------------------------------");
		} else if(pSheet != NULL)
		{
			BSTR bstrSheetName;
			BSTR bstrSheetDesc;
			BSTR bstrLayoutName;
			BSTR bstrFileName;
			char layout[80];
			char fileName[255];
			CComPtr<IAcSmAcDbLayoutReference> pLayoutRef;
			pSheet->GetName(&bstrSheetName);
			pSheet->GetDesc(&bstrSheetDesc);
			pSheet->GetLayout(&pLayoutRef);
			if (pLayoutRef)
			{
				pLayoutRef->GetName(&bstrLayoutName);
				pLayoutRef->GetFileName(&bstrFileName);
			}
			strcpy(name, _bstr_t(bstrSheetName).operator char*());
			strcpy(desc, _bstr_t(bstrSheetDesc).operator char*());
			strcpy(layout, _bstr_t(bstrLayoutName).operator char*());
			strcpy(fileName, _bstr_t(bstrFileName).operator char*());
			acutPrintf("\n         Sheet             : %s", name);
			acutPrintf("\n         Sheet Description : %s", desc);
			acutPrintf("\n         Layout Name       : %s", layout);
			acutPrintf("\n         FileName Name     : %s", fileName);
			acutPrintf("\n");
		} else if(pPropertyBag != NULL)
		{
			CComVariant val;
			CComQIPtr<IAcSmEnumProperty> pEnumProp;
			pPropertyBag->GetPropertyEnumerator(&pEnumProp);
			HRESULT hr;
			BSTR propName;
			BSTR propValue;

			pEnumProp->Reset();
			CComQIPtr<IAcSmCustomPropertyValue> pValue;
			while(pEnumProp->Next(&propName,&pValue)== S_OK)
			{
				strcpy(name, _bstr_t(propName).operator char*());
				acutPrintf("\n         Property Name       : %s", name);
				pValue->GetValue(&val);
				if(V_VT(&val)==VT_BSTR)
				{    // This Value is never VT_BSTR so what is wrong here???
					_bstr_t propValue = val;
					strcpy(desc, _bstr_t(propValue).operator char*());
					acutPrintf("\n         Property Value      : %s", desc);
				}
			}

		}
        
    } 

	acutPrintf("\n");
	acutPrintf("\n ********   END   ************** ");

	return S_OK;
}

AsdkSheetSet::AsdkSheetSet()
{
	m_nSheetCount = 0;
}

AsdkSheetSet::AsdkSheetSet(char* name,		
						   char* path,		
						   char* description,
						   char* templ,
						   char* defSheetLoc)
{
	m_nSheetCount = 0;
	create(name, path, description, templ, defSheetLoc);
}

AsdkSheetSet::~AsdkSheetSet()
{
	// Reset sheet count
	m_nSheetCount = 0;
	
	//Cleanup the class 
	cleanup();
}

HRESULT 
AsdkSheetSet::create(char* name,		
					 char* path,		
					 char* description,
					 char* templPath,
					 char* defSheetLoc)
{
	BOOL  bAlwaysCreate = TRUE;
	CComBSTR bstrSSName(name);	 // Sheet set name
	HRESULT hr;
	
	// If sheet set manager doesnt exist, create one
	if(!m_pSSetMgr.p)
	{
		if (FAILED(m_pSSetMgr.CoCreateInstance(CLSID_AcSmSheetSetMgr)))
		{
			acutPrintf("\n Error Cannot get sheet set manager!!");	
			return E_FAIL;
		}
	}
	 
	char fullPath[255];
	strcpy(fullPath, path);

	// If no trailing backslash entered, add it
	if (strcmp("\\" , &fullPath[strlen(fullPath)-1]) != 0)
		strcat(fullPath, "\\");

	// check if folder exists
	if(_access(fullPath,0))
	{
		acutPrintf("\n Error: Folder does not exist. Specify another folder!!!");
		return E_FAIL;
	}

	if(!strstr(name,".dst"))
		strcat(name, ".dst");	

	strcat(fullPath, name);
	
	CComBSTR bstrPath(fullPath);
	AcSmLockStatus lockStatus;
	
	// check if file exists 
	// If so, ask the user whether to overwrite or open existing
	if(!_access(fullPath,0))
	{
	   if(!getYorN("\n File exists!! Overwrite existing?"))
	   {
	    	// Don't overwrite existing
			// Just open the file
			// 2nd parameter = FALSE means don't fail if already open
			if(FAILED(m_pSSetMgr->OpenDatabase(bstrPath, FALSE, &m_pDb)))
			{
				acutPrintf("\n Error: Cannot open database!!");
				return E_FAIL;
			}
			
			// get the sheet set from the database.
			if (FAILED(m_pDb->GetSheetSet(&m_pSheetSet)))
			{  
				acutPrintf("\n Error: Cannot get sheet set");
				return E_FAIL;
			}
			
			return E_ABORT;
		}
	}  
	
	// create the database for the sheet set
	// bAlwaysCreate lets you override the existing file if it's set to true
	if (FAILED(hr = m_pSSetMgr->CreateDatabase(bstrPath, NULL, bAlwaysCreate, &m_pDb)))
	{
		acutPrintf("\nError: Cannot create database!");
		if (E_INVALIDARG == hr)
			acutPrintf("\n File name invalid!");		
		return E_FAIL;
	}

	
	 // lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Error: Database lock failed!");
        return E_FAIL;
	}

	CComBSTR bstrDesc(description);
	
	// set the sheet set db name, description = sheet set name, description
	 if (FAILED(m_pDb->SetName(bstrSSName)))
	 {
		acutPrintf("\n Error: Cannot set database name");
		return E_FAIL;
	 }
	 
	 if (FAILED(m_pDb->SetDesc(bstrDesc)))
	 {
		acutPrintf("\nError: Cannot set database description!");
		return E_FAIL;
	 }
	
	    // get the sheet set from the database.
    if (FAILED(m_pDb->GetSheetSet(&m_pSheetSet)))
	{  
		acutPrintf("\n Error: Cannot get sheet set");
        return E_FAIL;
	}

	// set the name and description to the sheet set
	if (FAILED(m_pSheetSet->SetName(bstrSSName)))
	{
		acutPrintf("\nError: Cannot set name!");
        return E_FAIL;
	}


    if (FAILED(m_pSheetSet->SetDesc(bstrDesc)))
	{
		acutPrintf("\nError: Cannot set description!");
        return E_FAIL;
	}

	if(isValid(templPath))
	{
		// set default template for layout at sheet set level
		overrideDefaultDWTLayout(templPath, m_pSheetSet);
	}

	if(isValid(defSheetLoc))
	{
		// set default sheet location
		setNewSheetLocation(defSheetLoc, m_pSheetSet);
	}

	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}
    else
		acutPrintf("\n Sheet set %s created", fullPath);
	
	return S_OK;

}

HRESULT 
AsdkSheetSet::addSheet(IAcSmSheet** pNewSheet,
					   IAcSmSubset* pParentCategory,
                       char* sheetName,
					   char* sheetDesc,
					   char* layoutName,
					   char* layoutDwgPath)
{
	
	if (FAILED(isInitialized("addSheet")))
		return E_FAIL;
	
	// Sheet subset or category
	CComQIPtr<IAcSmSubset> pSubSet;
	
	 // lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Database lock failed!");
        return E_FAIL;
	}

    if(!pParentCategory)
	{
        // insert sheet at root
        pSubSet = m_pSheetSet;
	}
    else
        pSubSet = pParentCategory;
        
    // Add a sheet to sheet root or sub-category
    // A new sheet based on a dwt can be added *only* if the following 2 conditions are satisfied
    // 1.  A default drawing template (which *should* contain a sheet/layout ) 
    //     is set up for the sheet set
    // 2.  A default location where the new sheet will be placed is set up
    //	   for the sheet set
	if(!isValid(layoutName))
	{
		// Check for above conditions
		if((pDefDwtLayoutRef.p == NULL) || (pDefNewSheetLoc.p == NULL))
		{
			acutPrintf("\n Cannot add new sheet %s!!", sheetName);
		}   else
		{
		
			// If layoutName is invalid, 
			// create a fresh sheet (not based on existing layout)
			
			CComBSTR bstrSheetName(sheetName); // sheet name
			CComBSTR bstrSheetDesc(sheetDesc); // sheet description

			HRESULT hr;
			if(FAILED(hr  =pSubSet->AddNewSheet(bstrSheetName, bstrSheetDesc, pNewSheet)))
			{
				acutPrintf("\n Cannot add new sheet");
				return E_FAIL;
			}	
		}
		
	} else
	// add a sheet based on existing layout
	{
		 CComPtr<IAcSmAcDbLayoutReference> pLayoutRef;

		// create the NamedAcDbObjectReference.
		if(FAILED(pLayoutRef.CoCreateInstance(L"AcSmComponents.AcSmAcDbLayoutReference")))
		{ 
			acutPrintf("\n Cannot create named object reference");
			return E_FAIL;
		}

		if(FAILED(pLayoutRef->InitNew(m_pSheetSet)))
		{
			acutPrintf("\n Cannot initialize layout");
			return E_FAIL;
		}

		CComBSTR bstrLayoutName(layoutName); // layout name

		// Set layout name
		if(FAILED(pLayoutRef->SetName(bstrLayoutName)))
		{
			acutPrintf("\n Cannot set layout name");
			return E_FAIL;
		}

		CComBSTR bstrDwgName(layoutDwgPath); // layout drawing name
			
		// Set layout drawing name
		if(FAILED(pLayoutRef->SetFileName(bstrDwgName)))
		{
			acutPrintf("\n Cannot set layout drawing name");
			return E_FAIL;
		}

		// Import the sheet into the sheet set by passing the 
		// IAcSmNamedAcDbObjectReference 
		// - which is a SheetSet reference to a layout 
		if(FAILED(pSubSet->ImportSheet(pLayoutRef, pNewSheet)))
		{
			acutPrintf("\n Failed to import sheet %s", layoutDwgPath);
			return E_FAIL;
		}

		// insert the component(sheet) 
		if(FAILED(pSubSet->InsertComponent(*pNewSheet, NULL)))
		{
			acutPrintf("\n Failed to insert sheet");
			return E_FAIL;
		}
	}

	// set the sheet number.
	CString sFormat;
	sFormat.Format("%d", m_nSheetCount + 1);
	CComBSTR bstrSheetNumber = sFormat.AllocSysString();
	if(pNewSheet && FAILED((*pNewSheet)->SetNumber(bstrSheetNumber)))
	{
		acutPrintf("\n Failed to set sheet number");
		return E_FAIL;
	}

	// Increment sheet count
	m_nSheetCount++;	

	// Unlock database
	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}

	return S_OK;
}

HRESULT
AsdkSheetSet::overrideDefaultDWTLayout(char* templPath,
									  IAcSmSubset *pSubSet)
{
	if(FAILED(isInitialized("overrideDefaultDWTLayout")))
		return E_FAIL;
	
	 // lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Database lock failed!");
        return E_FAIL;
	}

	CComQIPtr<IAcSmSubset> pSub = pSubSet;
	if(!pSub.p)
		pSubSet = m_pSheetSet;

	// if a default layout exists, release it first
	if(pDefDwtLayoutRef.p)
		pDefDwtLayoutRef.Release();

	// create the NamedAcDbObjectReference.
	if(FAILED(pDefDwtLayoutRef.CoCreateInstance(L"AcSmComponents.AcSmAcDbLayoutReference")))
	{ 
		acutPrintf("\n Cannot create named object reference");
		return E_FAIL;
	}

	if(FAILED(pDefDwtLayoutRef->InitNew(pSubSet)))
	{
		acutPrintf("\n Cannot initialize layout");
		return E_FAIL;
	}

	// Set template path
	CComBSTR bstrDwtPath(templPath); // layout drawing name
		
	// Set layout drawing name
	if(FAILED(pDefDwtLayoutRef->SetFileName(bstrDwtPath)))
	{
		acutPrintf("\n Cannot set template path");
		return E_FAIL;
	}

	// Override default drawing template at the subset level
	if(FAILED(pSubSet->SetDefDwtLayout(pDefDwtLayoutRef)))
	{
		acutPrintf("\n Cannot override template path");
		return E_FAIL;
	}

	// Unlock database
	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}

	return S_OK;
}

HRESULT
AsdkSheetSet::createNestedCategory(char* categoryName,		   // Category Name
							       char* categoryDesc,		   // Category Description
								   IAcSmSubset *pParentSet,    // Parent category 
								   IAcSmSubset **pNewSubset  // OUT - Newly created category		
								  )
{
	if(FAILED(isInitialized("createNestedCategory")))
		return E_FAIL;
	
	 // lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Database lock failed!");
        return E_FAIL;
	}

	CComQIPtr<IAcSmSubset> pSubSet = pParentSet;
	if(!pSubSet.p)
		// Create a category at the root
		pSubSet = m_pSheetSet;

	CComBSTR bstrCatName(categoryName); // Category name
	CComBSTR bstrCatDesc(categoryDesc); // Category description

	// create a new subset 
	if(FAILED(pSubSet->CreateSubset(bstrCatName, bstrCatDesc, pNewSubset)))
	{
		acutPrintf("\n Subset creation failed");
		return E_FAIL;
	}

	// Unlock database
	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}

	return S_OK;
}

HRESULT
AsdkSheetSet::setNewSheetLocation(char* defSheetLoc,
								 IAcSmSubset *pSubSet)
{
	if (FAILED(isInitialized("setNewSheetLocation")))
		return E_FAIL;
	
	 // lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Database lock failed!");
        return E_FAIL;
	}

	CComQIPtr<IAcSmSubset> pSub = pSubSet;
	if(!pSub.p)
		// Create a category at the root
		pSub = m_pSheetSet;

	// If new sheet location is specified, release it
	if(pDefNewSheetLoc.p)
		pDefNewSheetLoc.Release();
		
    if (FAILED(pDefNewSheetLoc.CoCreateInstance(L"AcSmComponents.AcSmFileReference")))
	{
		acutPrintf("\n Cannot create file reference");
        return E_POINTER;
	}

    if (FAILED(pDefNewSheetLoc->InitNew(m_pDb)))
	{
		acutPrintf("\n Cannot initialize file reference");
        return E_FAIL;
	}

	CComBSTR bstrFileName(defSheetLoc); // sheet location

    if (FAILED(pDefNewSheetLoc->SetFileName(bstrFileName)))
	{
        return E_FAIL;
	}

	if(FAILED(pSub->SetNewSheetLocation(pDefNewSheetLoc)))
	{
		acutPrintf("\n Cannot add default sheet location");
        return E_FAIL;
	}

	// Unlock database
	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}

	return S_OK;
}

HRESULT
AsdkSheetSet::addResourceFileLocation(char* resourceFileLocation)
{
	if(FAILED(isInitialized("addResourceFileLocation")))
		return E_FAIL;
	
	 // lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Database lock failed!");
        return E_FAIL;
	}

	CComPtr<IAcSmResources> pResources = NULL;

    if (FAILED(m_pSheetSet->GetResources(&pResources)))
        return E_FAIL;
    
   
	CComBSTR bstrResourceLoc(resourceFileLocation);

    CComPtr<IAcSmFileReference> pFileReference = NULL;
    if (FAILED(pFileReference.CoCreateInstance(L"AcSmComponents.AcSmFileReference")))
	{
        return E_POINTER;
	}

    if (FAILED(pFileReference->InitNew(m_pDb)))
	{
        return E_FAIL;
	}

    if (FAILED(pFileReference->SetFileName(bstrResourceLoc)))
	{
        return E_FAIL;
	}

    // add the resource location.
    if (FAILED(pResources->Add(pFileReference)))
        return E_FAIL;

	// Unlock database
	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}

	return S_OK;
}

HRESULT
AsdkSheetSet::addLabelBlock(char* blockName,
							char* drawingPath)
{
	if(FAILED(isInitialized("addLabelBlock")))
		return E_FAIL;
	
	 // lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Database lock failed!");
        return E_FAIL;
	}

	CComPtr<IAcSmAcDbBlockRecordReference> pLabelRef = NULL;
    
	if (FAILED(pLabelRef.CoCreateInstance(L"AcSmComponents.AcSmAcDbBlockRecordReference")))
	{
		acutPrintf("\n addLabelBlock Failed!   Cannot create named object reference");
        return E_POINTER;
    }
    
	if (FAILED(pLabelRef->InitNew(m_pDb)))
        return E_FAIL;
    
	CComBSTR bstrDrawingLoc(drawingPath);
    
	if (FAILED(pLabelRef->SetFileName(bstrDrawingLoc)))
	{
		acutPrintf("\n addLabelBlock Failed!   Cannot set file %s", drawingPath);
        return E_FAIL;
	}

	CComBSTR bstrBlockName(blockName);
   
    if (FAILED(pLabelRef->SetName(bstrBlockName)))
	{
		acutPrintf("\n addLabelBlock Failed!   Cannot set block name %s", blockName);
        return E_FAIL;
	}

    if(FAILED(m_pSheetSet->SetDefLabelBlk(pLabelRef)))
	{
        return E_FAIL;
	}

	// Unlock database
	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}

    return S_OK;
}

HRESULT
AsdkSheetSet::addCalloutBlock(char* blockName,
							  char* drawingName)
{
	if(FAILED(isInitialized("addCalloutBlock")))
		return E_FAIL;

	// lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Database lock failed!");
        return E_FAIL;
	}

	CComPtr<IAcSmCalloutBlocks> pCalloutBlk = NULL;
	if (FAILED(m_pSheetSet->GetCalloutBlocks(&pCalloutBlk)))
	{
		acutPrintf("\n addCalloutBlock failed! Cannot get callout blocks!!");
		return E_FAIL;
	}

	CComBSTR bstrBlockName(blockName);
	CComBSTR bstrFileName(drawingName);

	CComPtr<IAcSmAcDbBlockRecordReference> pCalloutRef = NULL;
	if (FAILED(pCalloutRef.CoCreateInstance(L"AcSmComponents.AcSmAcDbBlockRecordReference")))
	{
		acutPrintf("\n addCalloutBlock failed! Cannot get named object reference!!");
		return E_POINTER;
	}
		

	if (FAILED(pCalloutRef->InitNew(m_pDb)))
		return E_FAIL;

	if (FAILED(pCalloutRef->SetFileName(bstrFileName)))
	{
		acutPrintf("\n addCalloutBlock failed! Cannot set file name %s!!", drawingName);
		return E_FAIL;
	}

	if (FAILED(pCalloutRef->SetName(bstrBlockName)))
	{
		acutPrintf("\n addCalloutBlock failed! Cannot set block name %s!!", blockName);
		return E_FAIL;
	}
	 
	if(FAILED(pCalloutBlk->Add(pCalloutRef)))
	{
		acutPrintf("\n addCalloutBlock failed! Cannot add callout reference!!");
		return E_FAIL;
	}

		// Unlock database
	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}

	return S_OK;
}

HRESULT
AsdkSheetSet::addSheetSelectionSet(char* selSetName,			 // Name of selection set
					     		   char* selSetDesc,			 // Description 
							       IAcSmSheetSelSet **pSelSet) // Output pointer to selection set
{

	if(FAILED(isInitialized("addSheetSelectionSet")))
		return E_FAIL;
	
	 // lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Database lock failed!");
        return E_FAIL;
	}

	CComPtr<IAcSmSheetSelSets> pSelSetS = NULL;
    if (FAILED(m_pSheetSet->GetSheetSelSets(&pSelSetS)) || (pSelSetS == NULL))
    {
		acutPrintf("\n addSheetSelectionSet failed! Cannot get selection sets!!");
        return E_FAIL;
    }
  

    // add a selection set to the selection set collection of the sheet set
    CComBSTR selSet(selSetName);
    CComBSTR selDesc(selSetDesc);

    if (FAILED (pSelSetS->Add(selSet, selDesc, pSelSet)))
    {
		acutPrintf("\n addSheetSelectionSet failed! Cannot add selection set %s!!", selSetName);
        return E_FAIL;
    }

	// Unlock database
	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}

    return S_OK;
}


HRESULT
AsdkSheetSet::addCustomProperty(char* key,             // Property name
			  				    char* value,	       // Property value
								IAcSmComponent *pComp, // Component to add custom properties to
								PropertyFlags propertyFlag) // Property flag which specifies
														    // whether to inherit properties 
															// for all sheets in the sheet set
															// or to only apply at sheet set level
							   
{

	if(FAILED(isInitialized("addCustomProperty")))
		return E_FAIL;
		
	CComQIPtr<IAcSmComponent> pCmp;

	if (!pComp)
		// if null, create properties for sheet set
		pCmp = m_pSheetSet;
	else
		pCmp = pComp;

	// lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Database lock failed!");
        return E_FAIL;
	}

	 // Add one custom property at the sheet set level
    CComPtr<IAcSmCustomPropertyBag> pBag = NULL;

    if(FAILED(pCmp->GetCustomPropertyBag(&pBag)))
    {
        acutPrintf("\nError: custom property bag.");
        return E_FAIL;
    }

    CComPtr<IAcSmCustomPropertyValue> pPropVal;
    if (FAILED(pPropVal.CoCreateInstance(L"AcSmComponents.AcSmCustomPropertyValue")))
    {
        acutPrintf("\nError: initializing custom property.");
        return E_POINTER;
    }

    if(FAILED(pPropVal->InitNew(pBag)))
    {
        acutPrintf("\nError: initializing custom property value.");
        return E_FAIL;
    }

	HRESULT hr;
    // set the property flag.
    if(FAILED(( hr = pPropVal->SetFlags((PropertyFlags)propertyFlag))))
    {
        acutPrintf("\nError: setting custom property flag.");
        return E_FAIL;
    } 

	// set the property name(key)
	CComBSTR propName(key);
    if(FAILED(pBag->SetProperty(propName, pPropVal)))
    {
        acutPrintf("\nError: attaching custom property to sheet set.");
        return E_FAIL;
    }

	// set the property value(for the key)
    CComVariant val(value);
    if(FAILED(pPropVal->SetValue(val)))
    {
        acutPrintf("\nError: setting custom property value.");
        return E_FAIL;
    }

	// Unlock database
	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}

	return S_OK;
}

HRESULT
AsdkSheetSet::cleanup()
{
    // unlock the file.
    AcSmLockStatus lockStatus;
    
    if(!m_pDb.p)
		return E_FAIL;

	if(FAILED(m_pDb->GetLockStatus(&lockStatus)))
		return E_FAIL;

    if ((lockStatus == AcSmLockStatus_Locked_Local) || (lockStatus == AcSmLockStatus_Locked_Remote))
        if (FAILED(m_pDb->UnlockDb(m_pDb, true)))
        {
            acutPrintf("\n Error: failed to unlock the database.");
            return E_FAIL;
        }
        
	// Remove listener
	unsubscribeToNotifications();
	
	// release all pointers
	if(pDefDwtLayoutRef.p)
	    pDefDwtLayoutRef.Release();
	if(pDefNewSheetLoc.p)
		pDefNewSheetLoc.Release();
	if(m_pDb.p)
		m_pDb.Release();
	if(m_pSheetSet.p)
		m_pSheetSet.Release();
	if(m_pSSetMgr.p)
		m_pSSetMgr.Release();
	
	//reset sheet count
	m_nSheetCount = 0;
	
    return S_OK;
}

HRESULT
AsdkSheetSet::LockDatabase()
{
	if(!m_pDb.p)
		return E_POINTER;

	AcSmLockStatus lockStatus;
    m_pDb->GetLockStatus(&lockStatus);
    if (lockStatus == AcSmLockStatus_UnLocked)
	{
		if (FAILED(m_pDb->LockDb(m_pDb)))
		{
			return E_FAIL;
		}
	} else
	{
		// acutPrintf("\n Database already locked");
	}

	return S_OK;
}

HRESULT
AsdkSheetSet::UnlockDatabase()
{
	if(!m_pDb.p)
		return E_POINTER;
		
	AcSmLockStatus lockStatus;
    m_pDb->GetLockStatus(&lockStatus);
    if ((lockStatus == AcSmLockStatus_Locked_Local) || (lockStatus == AcSmLockStatus_Locked_Remote))
	{
        if (FAILED(m_pDb->UnlockDb(m_pDb, true)))
        {
            acutPrintf("\n Error: failed to unlock the database");
            return E_FAIL;
        }
	}

	return S_OK;
}

HRESULT
AsdkSheetSet::subscribeToNotifications()
{
		
	if(FAILED(isInitialized("subscribeToNotifications" )))
		return E_FAIL;
		
	if(m_pEventHandler)
		return S_OK;
		
	_com_util::CheckError(CComObject<AsdkSmEventHandler>::CreateInstance(&m_pEventHandler));
	m_pEventHandler->AddRef();
	// Register for notifications
	
	// Sheet set manager events
	m_pSSetMgr->Register(m_pEventHandler, &eventSSMCookie);

	// Database events
	m_pDb->Register(m_pEventHandler, &eventDbCookie);

	// Sheet set events
	m_pSheetSet->Register(m_pEventHandler, &eventSSetCookie);

	return S_OK;
}

HRESULT
AsdkSheetSet::unsubscribeToNotifications()
{
	if(FAILED(isInitialized("unsubscribeToNotifications" )))
		return E_FAIL;
		
	if (m_pEventHandler)
    {
		// unregister notifications
		// Sheet set manager events
		m_pSSetMgr->Unregister(eventSSMCookie);

		// Database events
		m_pDb->Unregister(eventDbCookie);

		// Sheet set events
		m_pSheetSet->Unregister(eventSSetCookie);

        _com_util::CheckError(CComObject<AsdkSmEventHandler>::CreateInstance(&m_pEventHandler));
            m_pEventHandler->Release();
		m_pEventHandler = NULL;
    }
	return S_OK;
}