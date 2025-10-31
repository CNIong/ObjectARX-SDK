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

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.h
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "SimpleTool.h"


//-----------------------------------------------------------------------------
#define szRDS _RXST("asdk")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CSimpleToolPaletteApp : public AcRxArxApp {

public:
	CSimpleToolPaletteApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		// TODO: Add your code here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
		//----- Self-register COM server upon loading.
		if ( FAILED(::DllRegisterServer ()) )
			acutPrintf (_RXST("Failed to register COM server.\n")) ;
	}


	// ----- asdkSimpleToolPalette._CREATESIMPLE command (do not rename)
	static void asdkSimpleToolPalette_CREATESIMPLE(void)
	{
		// Add your code for command asdkSimpleToolPalette._CREATESIMPLE here
		CComObject<CSimpleTool> tool;
		// Don't redefine the stock tool if it's already in the catalog
		if (AcTcGetManager()->FindStockTool(tool.GetObjectCLSID()) != NULL)
			return;

		if (SUCCEEDED(tool.New()))
		{
			AcTcCatalog *pCatalog = tool.CreateStockToolATC(_T("SimpleCatalog"));
			AcTcPalette* pPalette = tool.CreatePaletteATC(pCatalog, _T("SimplePalette"));
			AcTcPackage* pPackage = tool.CreateShapeCatalogATC("*AutoCADShapes");
			tool.CreateFlyoutToolATC(pPalette, pPackage);
			tool.CreateCommandToolATC(pPalette, "Line", "IDB_TOOL1", tool.GetCmdName());
			tool.CreateToolATC(pPalette);
			AcTcGetManager()->LoadCatalogs();
		}
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CSimpleToolPaletteApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CSimpleToolPaletteApp, asdkSimpleToolPalette, _CREATESIMPLE, CREATESIMPLE, ACRX_CMD_TRANSPARENT, NULL)
