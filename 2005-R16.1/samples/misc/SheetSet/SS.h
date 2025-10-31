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

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

// Import sheet set components
#import "C:\program files\common files\Autodesk shared\AcSmComponents16.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids
// Kalvaik - removed dependency on the typle library in common shared folder.
//#include "AcSmComponents16.h"

//////////////////////////////////////////////////////////////////////
// Event handler class
class ATL_NO_VTABLE AsdkSmEventHandler : 
					public CComObjectRootEx<CComSingleThreadModel>,
					public IAcSmEvents
{
	public:
		AsdkSmEventHandler() { }

	BEGIN_COM_MAP(AsdkSmEventHandler)
    COM_INTERFACE_ENTRY(IAcSmEvents)
	END_COM_MAP()

	// IAcSmEvents
	 STDMETHODIMP OnChanged (
        /*[in]*/ AcSmEvent event,
        /*[in]*/ IAcSmPersist *pComp )
	{
		BSTR bstrTypeName;
		char typeName[80];
		pComp->GetTypeName(&bstrTypeName);
		strcpy(typeName, _bstr_t(bstrTypeName).operator char*());
		acutPrintf("\n %s Modified!!! ", typeName);
		return S_OK;
	}
};

// This is the C++ class for the sheet set 

class AsdkSheetSet 
{
public:
	AsdkSheetSet();
	AsdkSheetSet(char* name,				  // name of sheet set
				 char* path,				  // path to sheet set
				 char* description,		      // description of the sheet set
				 char* templPath	= NULL,	  // If based on a template
				 char* defSheetLoc  = NULL	  // default sheet location
				 );

	~AsdkSheetSet();

	HRESULT create(char* name,				  // name of sheet set
				  char* path,				  // path to sheet set
				  char* description,		  // description of the sheet set
				  char* templPath    = NULL,  // If based on a template
				  char* defSheetLoc   = NULL	  // default sheet location
				 );

	HRESULT addSheet(IAcSmSheet** pNewSheet,			// Output - New sheet created
					 IAcSmSubset* pParentCategory,      // Parent category, if Null, add sheet to root sheet set
	                 char*        sheetName,			// Sheet name
					 char*        sheetDesc,			// Sheet description
					 char* layoutName = NULL,           // Layout name if sheet is based on a layout
					 char* layoutDwgPath = NULL        // layout drawing
					);

	HRESULT overrideDefaultDWTLayout (char* templPath,			// Name of drawing template
									  IAcSmSubset *pSubSet = NULL // Subset to override
									 );

	HRESULT createNestedCategory(char* categoryName,		   // Category Name
							       char* categoryDesc,		   // Category Description
								   IAcSmSubset *pParentSet,    // Parent category 
								   IAcSmSubset **pNewSubset  // OUT - Newly created category
								 );

	HRESULT setNewSheetLocation(char* defSheetLoc,		// Default sheet location
								IAcSmSubset *pSubSet    // Set set or category
								);	

	HRESULT addResourceFileLocation(char* resourceFileLocation); // resourceFileLocation is the 
															     // folder name(path) to resource files 
								

	HRESULT addLabelBlock(char* blockName,		// Name of label block
						  char* drawingName		// Full path to the drawing
						  );

	HRESULT addCalloutBlock(char* blockName,	// Name of callout block
							char* drawingName	// Full path to the drawing
						   );

	HRESULT addSheetSelectionSet(char* selSetName,			// Name of selection set
					        	 char* selSetDesc,			// Description 
							     IAcSmSheetSelSet **pSelSet	// Output pointer to selection set
							     );

	// Add custom properties (name-value pair) at the sheet set level
	HRESULT addCustomProperty(char* key,    // Property name
							  char* value,	 // Property value
							  IAcSmComponent *pComp = NULL, // Component (sheet, sheet set) to add property to
															// If null, the component is assumed to be sheet set 
							  PropertyFlags propertyFlag = (PropertyFlags)CUSTOM_SHEET_PROP
															// apply the properties for 
															// all the sheets in the sheet set by default
							 );

	HRESULT cleanup();
	
	// Check if sheet set components are initialized
	HRESULT isInitialized(char *funcName);      

	static HRESULT List(IAcSmDatabase *pDb);

	// Get the database
	HRESULT getDatabase(IAcSmDatabase *pDb)
	{
		// To do: Unsafe operation. Rectify
		if(!m_pDb.p)
			return E_POINTER;
		pDb = m_pDb.p;
		return S_OK;
	}

	HRESULT subscribeToNotifications();
	HRESULT unsubscribeToNotifications();

protected:
	//CComBSTR m_SSName;					 // Name of the sheet set
    CComPtr<IAcSmDatabase> m_pDb;		     // The sheet set's database
    CComPtr<IAcSmSheetSet> m_pSheetSet;      // Interface to 'this' sheet set
	CComPtr<IAcSmSheetSetMgr> m_pSSetMgr;    // pointer to sheet set manager class
	CComObject<AsdkSmEventHandler>* m_pEventHandler;
	CComPtr<IAcSmAcDbLayoutReference> pDefDwtLayoutRef; // Default dwt layout
	CComPtr<IAcSmFileReference> pDefNewSheetLoc; // New sheet default location
	long eventSSMCookie;
	long eventDbCookie;
	long eventSSetCookie;
	int m_nSheetCount;						 // Total number of sheets
public:	 // Kalvaik - moved these to public scope
	HRESULT LockDatabase();   // Lock sheet set database
	HRESULT UnlockDatabase(); // Unlock sheet set database
};


