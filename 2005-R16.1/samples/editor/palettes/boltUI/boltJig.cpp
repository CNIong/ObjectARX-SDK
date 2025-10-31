//
//
// (C) Copyright 2003 by Autodesk, Inc. 
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

#include "boltjig.h"
#include "bolttool.h"

TCHAR *szDefaultValues [8] ={
	_T("6"), _T("2.0"), _T("10.0"), _T("3.0"),
		_T("0.2"), _T("0,0,0"), _T("5.0"), _T("2.0")
} ;

void asdkBoltJig()
{
	CComObject<AsdkBoltJig> prompt;
	prompt.promptLoop();
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void asdkCreateTools()
{
		CComObject<CBoltTool> tool;
		// Create the stock tool (definition)
		AcTcCatalog *pCatalog=tool.CreateStockToolATC(_T("BoltCatalog"));
		if(!pCatalog)
		{
			acutPrintf("\nFailed to create the Stock Tool\n");
			return;
		}
		// Create the 'BoltPalette'
		AcTcPalette *pPalette=tool.CreatePaletteATC(pCatalog,_T("BoltPalette"));
		if(!pPalette)
		{
			acutPrintf("\nFailed to create the Palette\n");
			return;
		}
		
		// Create the shape package to hold the flyout tool definitions
		AcTcPackage* pShapePackage=tool.CreateShapeCatalogATC(_T("Bolt Flyout Catalog"));
		if(!pShapePackage)
		{
			acutPrintf("\nFailed to create the Shape Catalog\n");
			return;
		}

		if(pShapePackage->GetChildCount()==0)
		{
			// Add two tools to this package
			tool.New();//Set Default Values specified in the New override for this tool.
			if(!tool.CreateToolATC(pShapePackage,_T("Stainless Bolt"),_T("IDB_BOLTIMAGE")))
				acutPrintf("\nFailed to create a Tool instance\n");
			
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
				acutPrintf("\nFailed to create a Tool instance\n");

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
				acutPrintf("\nFailed to create a Tool instance\n");
						
			if(!tool.CreateCommandToolATC(pShapePackage,_T("BoltJig"),_T("IDB_BOLTJIG"),_T("^C^CBOLTJIG")))
				acutPrintf("\nFailed to create the Command Tool instance\n");
		}
		
		// Now create a flyout tool, a regular tool, and a command tool on the palette.
		
		tool.New();//reset the properties...
		if(!tool.CreateFlyoutToolATC(pPalette,pShapePackage,"Bolt Flyout"))
			acutPrintf("\nFailed to create a Flyout Tool instance\n");
		if(!tool.CreateToolATC(pPalette,_T("Stainless Tool"),_T("IDB_BOLTIMAGE")))
			acutPrintf("\nFailed to create a Shape Tool instance\n");
		if(!tool.CreateCommandToolATC(pPalette,_T("BoltJig"),_T("IDB_BOLTJIG"),_T("^C^CBOLTJIG")))
			acutPrintf("\nFailed to create a Shape Command Tool instance\n");

		// Refresh the Tool Palette with the above changes.
		AcTcGetManager()->LoadCatalogs(); // Refresh the Palette in the AutoCAD UI.
}

// END CODE APPEARING IN SDK DOCUMENT.

