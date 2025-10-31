//
//
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

#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ss.h"
#include "io.h"
#include "AcString.h"	



CComQIPtr<IAcSmDatabase> pDb;		     // The sheet set's database
CComPtr<IAcSmObjectId> pDbId;			 // ObjectId of the database // Modified 2/2/05
CComQIPtr<IAcSmSheetSet> pSheetSet;      // Interface to 'this' sheet set
CComPtr<IAcSmObjectId> pSheetSetId;    // ObjectId of the sheet set // Modified 2/2/05
CComPtr<IAcSmPersist> pPersSS, pPersDb;   // Sheet set and db persists
CComPtr<IAcSmSheetSetMgr> pSSetMgr;    // pointer to sheet set manager class
CComPtr<IAcSmAcDbLayoutReference> pDefDwtLayoutRef; // Default dwt layout
CComPtr<IAcSmFileReference> pDefNewSheetLoc; // New sheet default location
long eventSSMCookie;
long eventDbCookie;
long eventSSetCookie;
int nSheetCount;			// Total number of sheets

CComObject<AsdkSmEventHandler>* pEventHandler;

bool isValid(const AcString& name) 
{
  if( (name.length() < 1) || (name == _T(" ")) )
    return false; 
  else			
    return true; 
}

// get yes or no choice from the user
bool getYorN(TCHAR *msg)
{

  int res, retcode;
  TCHAR kw[4];
  acutPrintf(_T("\n %s [Yes/No]"), msg);
  do
  {
    acedInitGet(RSG_NONULL, _T("Yes No"));
    retcode = acedGetInt(NULL, &res);
    switch (retcode)
    {
    case RTKWORD:
      if(acedGetInput(kw) != RTNORM)
      {
        acutPrintf(_T("\nError getting Yes/No choice"));
        return false;
      }

      if(_tcscmp(kw, _T("Yes")) == 0)
      {
        return true;
      }
      else if(_tcscmp(kw, _T("No")) == 0)
      {
        return false;	
      }
      else
      {
        acutPrintf(_T("\nKeyword Error!!"));
        return false;
      }
      break;
    default:
      acutPrintf(_T("\n Enter <Yes/No> :"));
      break;

    }
  } while(retcode != RTKWORD);

  return true;

}


HRESULT
ListSheetSet(IAcSmDatabase *pDb)
{
  // List the contents of the sheet set at the command line

  HRESULT hr;

  if(!pDb)
    return E_FAIL;

  CComPtr<IAcSmEnumPersist> pEnum;
  CComPtr<IAcSmPersist> pItem;

  pDb->GetEnumerator(&pEnum);
  pEnum->Reset();

  acutPrintf(_T("\n ********  BEGIN  ************** "));
  acutPrintf(_T("\n"));
  while(SUCCEEDED(hr=pEnum->Next(&pItem)) && pItem)
  {
    CComQIPtr<IAcSmSubset> pSubSet = pItem;
    CComQIPtr<IAcSmSheet> pSheet = pItem;
    CComQIPtr<IAcSmCustomPropertyBag> pPropertyBag = pItem;
    CComBSTR bstrTypeName;

    //char name[80];
    //char desc[255];

    if (pSubSet != NULL)
    {
      CComBSTR bstrSubsetName;
      CComBSTR bstrSubSetDesc;
      pSubSet->GetName(&bstrSubsetName);
      pSubSet->GetDesc(&bstrSubSetDesc);
      acutPrintf(_T("\n -------------------------------"));
      acutPrintf(_T("\n SubSet Name : %s"), COLE2T(bstrSubsetName));
      acutPrintf(_T("\n Description : %s"), COLE2T(bstrSubSetDesc));
      acutPrintf(_T("\n -------------------------------"));

    } else if(pSheet != NULL)
    {
      CComBSTR bstrSheetName;
      CComBSTR bstrSheetDesc;
      CComBSTR bstrLayoutName;
      CComBSTR bstrFileName;
      TCHAR layout[80];
      TCHAR fileName[255];
      CComPtr<IAcSmAcDbLayoutReference> pLayoutRef;
      pSheet->GetName(&bstrSheetName);
      pSheet->GetDesc(&bstrSheetDesc);
      pSheet->GetLayout(&pLayoutRef);
      if (pLayoutRef)
      {
        pLayoutRef->GetName(&bstrLayoutName);
        pLayoutRef->GetFileName(&bstrFileName);
      }
      acutPrintf(_T("\n         Sheet             : %s"), COLE2T(bstrSheetName));
      acutPrintf(_T("\n         Sheet Description : %s"), COLE2T(bstrSheetDesc));
      acutPrintf(_T("\n         Layout Name       : %s"), COLE2T(bstrLayoutName));
      acutPrintf(_T("\n         FileName Name     : %s"), COLE2T(bstrFileName));
      acutPrintf(_T("\n"));
    } else if(pPropertyBag != NULL)
    {
      CComVariant val;
      CComQIPtr<IAcSmEnumProperty> pEnumProp;
      HRESULT hr;

      if(FAILED(hr = pPropertyBag->GetPropertyEnumerator(&pEnumProp))) 
      {
        acutPrintf(_T("\n Error: Cannot get property enumerator!!"));	
        return E_FAIL;
      }

      if(!pEnumProp)
      {
        acutPrintf(_T("\n Error: Property enumerator NULL!!"));	
        return E_FAIL;
      }

      CComBSTR propName;

      pEnumProp->Reset();
      CComQIPtr<IAcSmCustomPropertyValue> pValue;
      while(pEnumProp->Next(&propName,&pValue)== S_OK)
      {
        acutPrintf(_T("\n         Property Name       : %s"), COLE2T(propName));
        pValue->GetValue(&val);

        // NOTE: Prop values can have other types as well, such as long, double, and
        // even pointers to objects that implement IAcSmPersist. (vt == VT_UNKNOWN)

        if(val.vt == VT_BSTR)
        {    
          CComBSTR propValue(val.bstrVal);
          acutPrintf(_T("\n         Property Value      : %s"), COLE2T(propValue));
        } else if(val.vt == VT_R8) // Check if value is a doube 
        {
          acutPrintf(_T("\n         Property Value      : %f"), val.dblVal);
        } else if(val.vt == VT_I4) // or a long
        {
          acutPrintf(_T("\n         Property Value      : %d"), val.lVal);
        } else
        {
          acutPrintf(_T("\n         Property Value Type Unknown"));
        }
      }

    }

  } 

  acutPrintf(_T("\n"));
  acutPrintf(_T("\n ********   END   ************** "));

  return S_OK;
}


HRESULT 
createSheetSet(const AcString& name,		
               const AcString& path,		
               const AcString& description,
               const AcString& templPath,
               const AcString& defSheetLoc)
{


  AcString nameCopy(name);

  BOOL  bAlwaysCreate = TRUE;
  CComBSTR bstrSSName(nameCopy.kTCharPtr());	 // Sheet set name
  HRESULT hr;

  // If sheet set manager doesnt exist, create one
  if(!pSSetMgr.p)
  {
    if (FAILED(pSSetMgr.CoCreateInstance(CLSID_AcSmSheetSetMgr)))
    {
      acutPrintf(_T("\n Error Cannot get sheet set manager!!"));	
      return E_FAIL;
    }
  }

  AcString fullPath(path);

  // If no trailing backslash entered, add it
  if (fullPath.substrRev(1) != _T("\\"))
    fullPath = fullPath + _T("\\");

  // check if folder exists
  if(_taccess(fullPath,0))
  {
    acutPrintf(_T("\n Error: Folder does not exist. Specify another folder!!!"));
    return E_FAIL;
  }

  AcString suffix(_T(".dst"));
  if(nameCopy.find(*(suffix.kTCharPtr())) < 0) // find(const AcString&) not yet implemented!
    nameCopy += suffix;

  fullPath = fullPath + nameCopy;

  CComBSTR bstrPath(fullPath.kTCharPtr());
  AcSmLockStatus lockStatus;

  // check if file exists 
  // If so, ask the user whether to overwrite or open existing
  if(!_taccess(fullPath.kTCharPtr(),0))
  {
    if(!getYorN(_T("\n File exists!! Overwrite existing?")))
    {
      // Don't overwrite existing
      // Just open the file
      // 2nd parameter = FALSE means don't fail if already open
      if(FAILED(pSSetMgr->OpenDatabase(bstrPath, FALSE, &pDb)))
      {
        acutPrintf(_T("\n Error: Cannot open database!!"));
        return E_FAIL;
      }

      // Cache the objectID for future use (do not cache object pointer!)
      pDb->GetObjectId(&pDbId); // Modified 2/2/05

      // get the sheet set from the database.
      if (FAILED(pDb->GetSheetSet(&pSheetSet)))
      {  
        acutPrintf(_T("\n Error: Cannot get sheet set"));
        return E_FAIL;
      }

      // Cache the objectID for future use (do not cache object pointer!)
      pSheetSet->GetObjectId(&pSheetSetId); // Modified 2/2/05

      return E_ABORT;
    }
  }  

  // create the database for the sheet set
  // bAlwaysCreate lets you override the existing file if it's set to true
  if (FAILED(hr = pSSetMgr->CreateDatabase(bstrPath, NULL, bAlwaysCreate, &pDb)))
  {
    acutPrintf(_T("\nError: Cannot create database!"));
    if (E_INVALIDARG == hr)
      acutPrintf(_T("\n File name invalid!"));		
    return E_FAIL;
  }

  // Cache the objectID for future use (do not cache object pointer!)
  pDb->GetObjectId(&pDbId); // Modified 2/2/05

  // lock the the database first before doing any modification operation on it //RK- added "modification"
  if (FAILED(LockDatabase()))
  {
    acutPrintf(_T("\n Error: Database lock failed!"));
    return E_FAIL;
  }

  CComBSTR bstrDesc(description.kTCharPtr());

  // set the sheet set db name, description = sheet set name, description
  if (FAILED(pDb->SetName(bstrSSName)))
  {
    acutPrintf(_T("\n Error: Cannot set database name"));
    return E_FAIL;
  }

  if (FAILED(pDb->SetDesc(bstrDesc)))
  {
    acutPrintf(_T("\nError: Cannot set database description!"));
    return E_FAIL;
  }

  // get the sheet set from the database.
  if (FAILED(pDb->GetSheetSet(&pSheetSet)))
  {  
    acutPrintf(_T("\n Error: Cannot get sheet set"));
    return E_FAIL;
  }

  pSheetSet->GetObjectId(&pSheetSetId); // Modified 2/2/05

  // set the name and description to the sheet set
  if (FAILED(pSheetSet->SetName(bstrSSName)))
  {
    acutPrintf(_T("\nError: Cannot set name!"));
    return E_FAIL;
  }


  if (FAILED(pSheetSet->SetDesc(bstrDesc)))
  {
    acutPrintf(_T("\nError: Cannot set description!"));
    return E_FAIL;
  }

  if(isValid(templPath))
  {
    // set default template for layout at sheet set level
    AcString layoutName(_T("TEST")); // Assume this layout exists in the DWT
    overrideDefaultDWTLayout(templPath, layoutName, pSheetSet);
  }

  if(isValid(defSheetLoc))
  {
    // set default sheet location
    setNewSheetLocation(defSheetLoc, pSheetSet);
  }

  acutPrintf(_T("\n Sheet set %s created"), fullPath.kTCharPtr());

  return S_OK;

}

HRESULT 
addSheet(IAcSmObjectId** pNewSheetId, // Modified 2/2/05
         IAcSmObjectId* pParentCategoryId, // Modified 2/2/05
         const AcString& sheetName,
         const AcString& sheetDesc,
         const AcString& layoutName,
         const AcString& layoutDwgPath)
{

  CComPtr<IAcSmSheet> pNewSheet; // Modified 2/2/05
  CComQIPtr<IAcSmSubset> pParentCategory;


  // Sheet subset or category
  CComQIPtr<IAcSmSubset> pSubSet;


  CComPtr<IAcSmPersist> pPersParentCategory;
  if(pParentCategoryId)
  {
    pParentCategoryId->GetPersistObject(&pPersParentCategory);
    pParentCategory = pPersParentCategory;
  }

  if(!pParentCategory)
  {
    // insert sheet at root
    pSubSet = pSheetSet;
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
      acutPrintf(_T("\n Cannot add new sheet %s!!"), sheetName.kTCharPtr());
    }   else
    {
      // If layoutName is invalid, 
      // create a fresh sheet (not based on existing layout)

      CComBSTR bstrSheetName(sheetName.kTCharPtr()); // sheet name
      CComBSTR bstrSheetDesc(sheetDesc.kTCharPtr()); // sheet description

      HRESULT hr;
      if(FAILED(hr  =pSubSet->AddNewSheet(bstrSheetName, bstrSheetDesc, &pNewSheet)))
      {
        acutPrintf(_T("\n Cannot add new sheet"));
        return E_FAIL;
      }	
      pNewSheet->GetObjectId(pNewSheetId);
    }

  } else
    // add a sheet based on existing layout
  {
    CComPtr<IAcSmAcDbLayoutReference> pLayoutRef;

    // create the NamedAcDbObjectReference.
    if(FAILED(pLayoutRef.CoCreateInstance(L"AcSmComponents.AcSmAcDbLayoutReference.17")))
    { 
      acutPrintf(_T("\n Cannot create named object reference"));
      return E_FAIL;
    }

    HRESULT hr;

    if(FAILED(hr = pLayoutRef->InitNew(pSheetSet)))
    {
      acutPrintf(_T("\n Cannot initialize layout"));
      return E_FAIL;
    }

    CComBSTR bstrLayoutName(layoutName.kTCharPtr()); // layout name

    // Set layout name
    if(FAILED(pLayoutRef->SetName(bstrLayoutName)))
    {
      acutPrintf(_T("\n Cannot set layout name"));
      return E_FAIL;
    }

    CComBSTR bstrDwgName(layoutDwgPath.kTCharPtr()); // layout drawing name

    // Set layout drawing name
    if(FAILED(pLayoutRef->SetFileName(bstrDwgName)))
    {
      acutPrintf(_T("\n Cannot set layout drawing name"));
      return E_FAIL;
    }

    // Import the sheet into the sheet set by passing the 
    // IAcSmNamedAcDbObjectReference 
    // - which is a SheetSet reference to a layout 
    if(FAILED(pSubSet->ImportSheet(pLayoutRef, &pNewSheet)))
    {
      acutPrintf(_T("\n Failed to import sheet %s"), layoutDwgPath.kTCharPtr());
      return E_FAIL;
    }

    // insert the component(sheet) 
    if(FAILED(pSubSet->InsertComponent(pNewSheet, NULL)))
    {
      acutPrintf(_T("\n Failed to insert sheet"));
      return E_FAIL;
    }

    pNewSheet->GetObjectId(pNewSheetId); // Modified 2/2/05
  }

  // set the sheet number.
  TCHAR sformat[32];
  _stprintf_s(sformat,_T("%d"),nSheetCount+1);
  if(pNewSheet && FAILED(pNewSheet->SetNumber(CComBSTR(sformat))))
  {
    acutPrintf(_T("\n Failed to set sheet number"));
    return E_FAIL;
  }

  // Increment sheet count
  nSheetCount++;	

  return S_OK;
}

HRESULT
overrideDefaultDWTLayout(const AcString& templPath,
                         const AcString& layoutName,  
                         IAcSmSubset *pSubSet)
{

  CComQIPtr<IAcSmSubset> pSub = pSubSet;
  if(!pSub.p)
    pSubSet = pSheetSet;

  // if a default layout exists, release it first
  if(pDefDwtLayoutRef.p)
    pDefDwtLayoutRef.Release();

  // create the NamedAcDbObjectReference.
  if(FAILED(pDefDwtLayoutRef.CoCreateInstance(L"AcSmComponents.AcSmAcDbLayoutReference.17")))
  { 
    acutPrintf(_T("\n Cannot create named object reference"));
    return E_FAIL;
  }

  if(FAILED(pDefDwtLayoutRef->InitNew(pSubSet)))
  {
    acutPrintf(_T("\n Cannot initialize layout"));
    return E_FAIL;
  }

  // Set template path
  CComBSTR bstrDwtPath(templPath.kTCharPtr()); // layout drawing name
  CComBSTR bstrLayoutName(layoutName.kTCharPtr()); // layout  name

  // Set layout drawing name
  if(FAILED(pDefDwtLayoutRef->SetFileName(bstrDwtPath)))
  {
    acutPrintf(_T("\n Cannot set template path"));
    return E_FAIL;
  }

  // The layout reference also needs to know the name and/or handle of 
  // the layout it is supposed to refer to.
  // We need to also set the layout name and/or acdbhandle for pDefDwtLayoutRef
  // here.
  // An even better approach is to call the SetAcDbObject method to
  // ensure that _all_ data is properly populated in the IAcSmLayoutRference object.
  // The ideal case is to open the dwg database, get the desired IAcadLayout, and 
  // call the SetAcDbObject method. For example:
  //   pDefDwtLayoutRef->SetAcDbObject(pLayout);

  // Set layout  name
  if(FAILED(pDefDwtLayoutRef->SetName(bstrLayoutName)))
  {
    acutPrintf(_T("\n Cannot set layout name"));
    return E_FAIL;
  }

  // Override default drawing template at the subset level
  if(FAILED(pSubSet->SetDefDwtLayout(pDefDwtLayoutRef)))
  {
    acutPrintf(_T("\n Cannot override template path"));
    return E_FAIL;
  }

  return S_OK;
}

HRESULT
createNestedCategory(const AcString& categoryName,		   // Category Name
                     const AcString& categoryDesc,		   // Category Description
                     IAcSmObjectId *pParentSetId, // parent category Id - Modified 2/2/05
                     IAcSmObjectId** pNewSubsetId  // OUT - Newly created category	// Modified 2/2/05
                     )
{
  CComPtr<IAcSmSubset> pNewSubset; // Modified 2/2/05
  CComQIPtr<IAcSmSubset> pParentSet;


  CComPtr<IAcSmPersist> pParentSetPers;
  if(pParentSetId)
  {
    pParentSetId->GetPersistObject(&pParentSetPers);
    pParentSet = pParentSetPers;
  }

  CComQIPtr<IAcSmSubset> pSubSet = pParentSet;
  if(!pSubSet.p)
    // Create a category at the root
    pSubSet = pSheetSet;

  CComBSTR bstrCatName(categoryName.kTCharPtr()); // Category name
  CComBSTR bstrCatDesc(categoryDesc.kTCharPtr()); // Category description

  // create a new subset 
  if(FAILED(pSubSet->CreateSubset(bstrCatName, bstrCatDesc, &pNewSubset))) // Modified 2/2/05
  {
    acutPrintf(_T("\n Subset creation failed"));
    return E_FAIL;
  }

  pNewSubset->GetObjectId(pNewSubsetId);

  return S_OK;
}

HRESULT
setNewSheetLocation(const AcString& defSheetLoc,
                    IAcSmSubset *pSubSet)
{

  CComQIPtr<IAcSmSubset> pSub = pSubSet;
  if(!pSub.p)
    // Create a category at the root
    pSub = pSheetSet;

  // If new sheet location is specified, release it
  if(pDefNewSheetLoc.p)
    pDefNewSheetLoc.Release();

  if (FAILED(pDefNewSheetLoc.CoCreateInstance(L"AcSmComponents.AcSmFileReference.17")))
  {
    acutPrintf(_T("\n Cannot create file reference"));
    return E_POINTER;
  }

  if (FAILED(pDefNewSheetLoc->InitNew(pDb)))
  {
    acutPrintf(_T("\n Cannot initialize file reference"));
    return E_FAIL;
  }

  CComBSTR bstrFileName(defSheetLoc.kTCharPtr()); // sheet location

  if (FAILED(pDefNewSheetLoc->SetFileName(bstrFileName)))
  {
    return E_FAIL;
  }

  if(FAILED(pSub->SetNewSheetLocation(pDefNewSheetLoc)))
  {
    acutPrintf(_T("\n Cannot add default sheet location"));
    return E_FAIL;
  }


  return S_OK;
}

HRESULT
addResourceFileLocation(const AcString& resourceFileLocation)
{
  CComPtr<IAcSmResources> pResources = NULL;

  if (FAILED(pSheetSet->GetResources(&pResources)))
    return E_FAIL;


  CComBSTR bstrResourceLoc(resourceFileLocation.kTCharPtr());

  CComPtr<IAcSmFileReference> pFileReference = NULL;
  if (FAILED(pFileReference.CoCreateInstance(L"AcSmComponents.AcSmFileReference.17")))
  {
    return E_POINTER;
  }

  if (FAILED(pFileReference->InitNew(pDb)))
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

  return S_OK;
}

HRESULT
addLabelBlock(const AcString& blockName,
              const AcString& drawingPath)
{

  CComPtr<IAcSmAcDbBlockRecordReference> pLabelRef = NULL;

  if (FAILED(pLabelRef.CoCreateInstance(L"AcSmComponents.AcSmAcDbBlockRecordReference.17")))
  {
    acutPrintf(_T("\n addLabelBlock Failed!   Cannot create named object reference"));
    return E_POINTER;
  }

  if (FAILED(pLabelRef->InitNew(pDb)))
    return E_FAIL;

  CComBSTR bstrDrawingLoc(drawingPath.kTCharPtr());

  if (FAILED(pLabelRef->SetFileName(bstrDrawingLoc)))
  {
    acutPrintf(_T("\n addLabelBlock Failed!   Cannot set file %s"), drawingPath.kTCharPtr());
    return E_FAIL;
  }

  CComBSTR bstrBlockName(blockName.kTCharPtr());

  if (FAILED(pLabelRef->SetName(bstrBlockName)))
  {
    acutPrintf(_T("\n addLabelBlock Failed!   Cannot set block name %s"), blockName.kTCharPtr());
    return E_FAIL;
  }

  if(FAILED(pSheetSet->SetDefLabelBlk(pLabelRef)))
  {
    return E_FAIL;
  }


  return S_OK;
}

HRESULT
addCalloutBlock(const AcString& blockName,
                const AcString& drawingName)
{

  CComPtr<IAcSmCalloutBlocks> pCalloutBlk = NULL;
  if (FAILED(pSheetSet->GetCalloutBlocks(&pCalloutBlk)))
  {
    acutPrintf(_T("\n addCalloutBlock failed! Cannot get callout blocks!!"));
    return E_FAIL;
  }

  CComBSTR bstrBlockName(blockName.kTCharPtr());
  CComBSTR bstrFileName(drawingName.kTCharPtr());

  CComPtr<IAcSmAcDbBlockRecordReference> pCalloutRef = NULL;
  if (FAILED(pCalloutRef.CoCreateInstance(L"AcSmComponents.AcSmAcDbBlockRecordReference.17")))
  {
    acutPrintf(_T("\n addCalloutBlock failed! Cannot get named object reference!!"));
    return E_POINTER;
  }


  if (FAILED(pCalloutRef->InitNew(pDb)))
    return E_FAIL;

  if (FAILED(pCalloutRef->SetFileName(bstrFileName)))
  {
    acutPrintf(_T("\n addCalloutBlock failed! Cannot set file name %s!!"), drawingName.kTCharPtr());
    return E_FAIL;
  }

  if (FAILED(pCalloutRef->SetName(bstrBlockName)))
  {
    acutPrintf(_T("\n addCalloutBlock failed! Cannot set block name %s!!"), blockName.kTCharPtr());
    return E_FAIL;
  }

  if(FAILED(pCalloutBlk->Add(pCalloutRef)))
  {
    acutPrintf(_T("\n addCalloutBlock failed! Cannot add callout reference!!"));
    return E_FAIL;
  }

  return S_OK;
}

HRESULT
addSheetSelectionSet(const AcString& selSetName,			 // Name of selection set
                     const AcString& selSetDesc,			 // Description 
                     IAcSmObjectId** pSelSetId) // Output pointer to selection set  // Modified 2/2/05
{
  CComPtr<IAcSmSheetSelSet> pSelSet; // Modified 2/2/05


  CComPtr<IAcSmSheetSelSets> pSelSetS = NULL;
  if (FAILED(pSheetSet->GetSheetSelSets(&pSelSetS)) || (pSelSetS == NULL))
  {
    acutPrintf(_T("\n addSheetSelectionSet failed! Cannot get selection sets!!"));
    return E_FAIL;
  }



  // add a selection set to the selection set collection of the sheet set
  CComBSTR selSet(selSetName.kTCharPtr());
  CComBSTR selDesc(selSetDesc.kTCharPtr());

  if (FAILED (pSelSetS->Add(selSet, selDesc, &pSelSet)))
  {
    acutPrintf(_T("\n addSheetSelectionSet failed! Cannot add selection set %s!!"), selSetName.kTCharPtr());
    return E_FAIL;
  }

  pSelSet->GetObjectId(pSelSetId); // Modified 2/2/05

  return S_OK;
}


HRESULT
addCustomProperty(const AcString& key,             // Property name
                  const AcString& value,	       // Property value
                  // IAcSmComponent *pComp, // Component to add custom properties to
                  IAcSmObjectId *pCompId,   // modified 2/2/05
                  PropertyFlags propertyFlag) // Property flag which specifies
                  // whether to inherit properties 
                  // for all sheets in the sheet set
                  // or to only apply at sheet set level

{

  CComQIPtr<IAcSmComponent> pCmp;
  CComQIPtr<IAcSmComponent> pComp;
  CComPtr<IAcSmPersist> pCompPers;

  if (!pComp.p) 
    // if null, create properties for sheet set
    pCmp = pSheetSet;
  else
    pCmp = pComp;

  // Add one custom property at the sheet set level
  CComPtr<IAcSmCustomPropertyBag> pBag = NULL;

  if(FAILED(pCmp->GetCustomPropertyBag(&pBag)))
  {
    acutPrintf(_T("\nError: custom property bag."));
    return E_FAIL;
  }

  CComPtr<IAcSmCustomPropertyValue> pPropVal;
  if (FAILED(pPropVal.CoCreateInstance(L"AcSmComponents.AcSmCustomPropertyValue.17")))
  {
    acutPrintf(_T("\nError: initializing custom property."));
    return E_POINTER;
  }

  if(FAILED(pPropVal->InitNew(pBag)))
  {
    acutPrintf(_T("\nError: initializing custom property value."));
    return E_FAIL;
  }

  HRESULT hr;
  // set the property flag.
  if(FAILED(( hr = pPropVal->SetFlags((PropertyFlags)propertyFlag))))
  {
    acutPrintf(_T("\nError: setting custom property flag."));
    return E_FAIL;
  } 

  // set the property name(key)
  CComBSTR propName(key.kTCharPtr());
  if(FAILED(pBag->SetProperty(propName, pPropVal)))
  {
    acutPrintf(_T("\nError: attaching custom property to sheet set."));
    return E_FAIL;
  }

  // set the property value(for the key)
  CComVariant val(value.kTCharPtr());
  if(FAILED(pPropVal->SetValue(val)))
  {
    acutPrintf(_T("\nError: setting custom property value."));
    return E_FAIL;
  }

  return S_OK;
}

HRESULT
cleanup()
{

  // unlock the file.
  AcSmLockStatus lockStatus;

  if(!pDb.p)
    return E_FAIL;

  if(FAILED(pDb->GetLockStatus(&lockStatus)))
    return E_FAIL;

  if ((lockStatus == AcSmLockStatus_Locked_Local) || (lockStatus == AcSmLockStatus_Locked_Remote))
    if (FAILED(pDb->UnlockDb(pDb, true)))
    {
      acutPrintf(_T("\n Error: failed to unlock the database."));
      return E_FAIL;
    }


    // Remove listener
    unsubscribeToNotifications();

    // release all pointers
    if(pDefDwtLayoutRef.p)
      pDefDwtLayoutRef.Release();
    if(pDefNewSheetLoc.p)
      pDefNewSheetLoc.Release();
    if(pDb.p)
      pDb.Release();
    if(pDbId.p)
      pDbId.Release();
    if(pPersDb.p)
      pPersDb.Release();
    if(pSheetSet.p)
      pSheetSet.Release();
    if(pSheetSetId.p)
      pSheetSetId.Release();
    if(pPersSS.p)
      pPersSS.Release();
    if(pSSetMgr.p)
      pSSetMgr.Release();

    //reset sheet count
    nSheetCount = 0;

    return S_OK;
}

HRESULT
LockDatabase()
{
  if(!pDb.p)
    return E_POINTER;

  AcSmLockStatus lockStatus;
  pDb->GetLockStatus(&lockStatus);
  if (lockStatus == AcSmLockStatus_UnLocked)
  {
    if (FAILED(pDb->LockDb(pDb)))
    {
      return E_FAIL;
    }
  } else
  {
    acutPrintf(_T("\n Database already locked"));
  }

  return S_OK;
}

HRESULT
UnlockDatabase()
{

  if(!pDb.p)
    return E_POINTER;

  AcSmLockStatus lockStatus;
  pDb->GetLockStatus(&lockStatus);
  if ((lockStatus == AcSmLockStatus_Locked_Local) || (lockStatus == AcSmLockStatus_Locked_Remote))
  {
    if (FAILED(pDb->UnlockDb(pDb, true)))
    {
      acutPrintf(_T("\n Error: failed to unlock the database"));
      return E_FAIL;
    }
  }

  return S_OK;
}

HRESULT
subscribeToNotifications()
{

  if(pEventHandler)
    return S_OK;

  _com_util::CheckError(CComObject<AsdkSmEventHandler>::CreateInstance(&pEventHandler));
  pEventHandler->AddRef();

  // Register for notifications

  // Sheet set manager events
  HRESULT hr;
  hr = pSSetMgr->Register(pEventHandler, &eventSSMCookie);

  // Database events
  hr = pDb->Register(pEventHandler, &eventDbCookie);

  // Sheet set events
  hr = pSheetSet->Register(pEventHandler, &eventSSetCookie);

  return S_OK;
}

HRESULT
unsubscribeToNotifications()
{

  HRESULT hr;

  if (pEventHandler)
  {
    // unregister notifications
    // Sheet set manager event
    hr = pSSetMgr->Unregister(eventSSMCookie);

    // Database events
    hr = pDb->Unregister(eventDbCookie);

    // Sheet set events
    hr = pSheetSet->Unregister(eventSSetCookie);

    ULONG res = pEventHandler->Release();
    pEventHandler = NULL;
  }


  return S_OK;
}