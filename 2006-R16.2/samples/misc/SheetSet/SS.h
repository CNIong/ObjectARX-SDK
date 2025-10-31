// (C) Copyright 1990-2004 by Autodesk, Inc. 
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

#include "AcString.h"

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

// Utility functions for sheet set operations

HRESULT createSheetSet(const AcString& name,				  // name of sheet set
				const AcString& path,				  // path to sheet set
				const AcString& description,		  // description of the sheet set
				const AcString& templPath ,			// If based on a template
				const AcString& defSheetLoc 	    // default sheet location
				);

HRESULT addSheet(IAcSmObjectId** pNewSheetId,			// Output - New sheet created // Modified 2/2/05
					//IAcSmSubset* pParentCategory,      // Parent category, if Null, add sheet to root sheet set
					IAcSmObjectId* pParentCategoryId, // Modified 2/2/05
	                const AcString&        sheetName,		// Sheet name
					const AcString&        sheetDesc,		// Sheet description
					const AcString& layoutName,     // Layout name if sheet is based on a layout
					const AcString& layoutDwgPath   // layout drawing
				);

HRESULT overrideDefaultDWTLayout(const AcString& templPath,			// Name of drawing template
								 const AcString& layoutName,        // Name of the layout
									IAcSmSubset *pSubSet = NULL // Subset to override
									);

HRESULT createNestedCategory(const AcString& categoryName,		   // Category Name
							    const AcString& categoryDesc,		   // Category Description
								//IAcSmSubset *pParentSet,    // Parent category 
								IAcSmObjectId *pParentSetId,  // modified 2/2/05
								IAcSmObjectId** pNewSubsetId  // OUT - Newly created category // Modified 2/2/05
								);

HRESULT setNewSheetLocation(const AcString& defSheetLoc,		// Default sheet location
							IAcSmSubset *pSubSet    // Set set or category
							);	

HRESULT addResourceFileLocation(const AcString& resourceFileLocation); // resourceFileLocation is the 
															    // folder name(path) to resource files 
							

HRESULT addLabelBlock(const AcString& blockName,		// Name of label block
						const AcString& drawingName		// Full path to the drawing
						);

HRESULT addCalloutBlock(const AcString& blockName,	// Name of callout block
						const AcString& drawingName	// Full path to the drawing
						);

HRESULT addSheetSelectionSet(const AcString& selSetName,			// Name of selection set
					        	const AcString& selSetDesc,			// Description 
							    IAcSmObjectId** pSelSetId	// Output pointer to selection set //Modified 2/2/05
							    );

// Add custom properties (name-value pair) at the sheet set level
HRESULT addCustomProperty(const AcString& key,    // Property name
							const AcString& value,	 // Property value
							// IAcSmComponent *pComp = NULL, // Component (sheet, sheet set) to add property to
														// If null, the component is assumed to be sheet set 
							IAcSmObjectId *pCompId, // Modified 2/2/05
							PropertyFlags propertyFlag								
							);

HRESULT cleanup();
 
HRESULT ListSheetSet(IAcSmDatabase *pDb);


HRESULT subscribeToNotifications();
HRESULT unsubscribeToNotifications();


HRESULT LockDatabase();   // Lock sheet set database
HRESULT UnlockDatabase(); // Unlock sheet set database

