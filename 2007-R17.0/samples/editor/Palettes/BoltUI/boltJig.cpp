//
//
// (C) Copyright 2003-2006 by Autodesk, Inc. 
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
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "boltjig.h"
#include "bolttool.h"



TCHAR *szDefaultValues [8] ={
	_T("6"), _T("2.0"), _T("10.0"), _T("3.0"),
		_T("0.2"), _T("0,0,0"), _T("5.0"), _T("2.0")
} ;

void asdkBoltJig()
{
	try 
	{
		CComObject<AsdkBoltJig> prompt;
		prompt.promptLoop();
		acedSetIUnknownForCurrentCommand(NULL);
	}
	catch(HRESULT hr)
	{
		acutPrintf(_T("\nBOLTJIG Command failed\n: %d"),hr);
	}
	catch(...)
	{
		acutPrintf(_T("\nBOLTJIG Command failed\n"));
	}
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void asdkCreateTools()
{
	try
	{
		CComObject<CBoltTool> tool;

		// Create the stock tool (definition)
		AcTcCatalog *pCatalog=tool.CreateStockToolATC(_T("BoltCatalog"));
		if(!pCatalog)
			throw _T("\nFailed to create the Stock Tool\n");
		
		// Create the 'BoltPalette'
		AcTcPalette *pPalette=tool.CreatePaletteATC(pCatalog,_T("BoltPalette"));
		if(!pPalette)
			throw _T("\nFailed to create the Palette\n");

		// Create the shape package to hold the flyout tool definitions
		AcTcPackage* pShapePackage=tool.CreateShapeCatalogATC(_T("Bolt Flyout Catalog"));
		if(!pShapePackage)
			throw _T("\nFailed to create the Shape Catalog\n");
		
		if(pShapePackage->GetChildCount()==0)
		{
			// Add two tools to this package
			tool.New();//Set Default Values specified in the New override for this tool.
			if(!tool.CreateToolATC(pShapePackage,_T("Stainless Bolt"),_T("IDB_BOLTIMAGE")))
				throw _T("\nFailed to create a Tool instance\n");
			
			// Now, create additional tools with different parameters:
			tool.m_HeadSides=6;
			tool.m_HeadHeight=2.5f;
			tool.m_ShaftLength=12.0f;
			tool.m_ShaftDiameter=3.0f;
			tool.m_ThreadLength=3.5f;
			tool.m_ThreadWidth=0.1f;
			tool.m_HeadDiameter=7.0f;
			tool.m_Color.setColorIndex(2);
			_tcscpy(tool.m_MaterialName,_T("Aluminum"));
			_tcscpy(tool.m_PartNumber,_T("Unassigned"));			
			if(!tool.CreateToolATC(pShapePackage,_T("Aluminum Bolt"),_T("IDB_BOLTALUMINUM")))
				throw _T("\nFailed to create a Tool instance\n");

			// A separate galvanized tool.
			tool.m_HeadSides=6;
			tool.m_HeadHeight=3.5f;
			tool.m_ShaftLength=15.0f;
			tool.m_ShaftDiameter=5.0f;
			tool.m_ThreadLength=5.5f;
			tool.m_ThreadWidth=0.3f;
			tool.m_HeadDiameter=9.0f;
			tool.m_Color.setColorIndex(4);
			_tcscpy(tool.m_MaterialName,_T("Galvanized"));
			_tcscpy(tool.m_PartNumber,_T("Unassigned"));			
			if(!tool.CreateToolATC(pShapePackage,_T("Galvanized"),_T("IDB_BOLTGALVANIZED")))
				throw _T("\nFailed to create a Tool instance\n");
						
			if(!tool.CreateCommandToolATC(pShapePackage,_T("BoltJig"),_T("IDB_BOLTJIG"),_T("^C^CBOLTJIG")))
				throw  _T("\nFailed to create the Command Tool instance\n");
		}
		
		// Now create a flyout tool, a regular tool, and a command tool on the palette.
		
		tool.New();//reset the properties...
		if(!tool.CreateFlyoutToolATC(pPalette,pShapePackage,_T("Bolt Flyout")))
			throw _T("\nFailed to create a Flyout Tool instance\n");
		if(!tool.CreateToolATC(pPalette,_T("Stainless Tool"),_T("IDB_BOLTIMAGE")))
			throw _T("\nFailed to create a Shape Tool instance\n");
		if(!tool.CreateCommandToolATC(pPalette,_T("BoltJig"),_T("IDB_BOLTJIG"),_T("^C^CBOLTJIG")))
			throw _T("\nFailed to create a Shape Command Tool instance\n");

		// Refresh the Tool Palette with the above changes.
		AcTcGetManager()->LoadCatalogs(); // Refresh the Palette in the AutoCAD UI.
	}
	catch (TCHAR *message)
	{
		acutPrintf(message);
	}
	catch (...)
	{
		acutPrintf(_T("\nError in CREATTOOLS command\n"));
	}
}

// END CODE APPEARING IN SDK DOCUMENT.

