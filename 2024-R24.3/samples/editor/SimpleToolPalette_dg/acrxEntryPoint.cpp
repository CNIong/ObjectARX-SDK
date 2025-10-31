//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//-----------------------------------------------------------------------------
//----- acrxEntryPoint.h
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

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

		try
		{
			// Don't redefine the stock tool if it's already in the catalog
			if (AcTcGetManager()->FindStockTool(tool.GetObjectCLSID()) != NULL)
				throw _T("Stock Tool already created");

			if (SUCCEEDED(tool.New()))
			{
				tool.AddRef ();
				AcTcCatalog *pCatalog = tool.CreateStockToolATC(_T("SimpleCatalog"));
				if(pCatalog == NULL)
					throw _T("Couldn't Create Catalog");

				AcTcPalette* pPalette = tool.CreatePaletteATC(pCatalog, _T("SimplePalette"));
				if(pPalette == NULL)
					throw _T("Couldn't Create Palette");
				
				AcTcPackage* pPackage = tool.CreateShapeCatalogATC(_T("*AutoCADShapes"));
				if(pPackage == NULL)
					throw _T("Couldn't Create Shape Catalog");

				if(NULL == tool.CreateFlyoutToolATC(pPalette, pPackage))
					throw _T("Couldn't Create Flyout Tool");

				if(NULL == tool.CreateCommandToolATC(pPalette, _T("Line"), _T("IDB_TOOL1"), tool.GetCmdName()))
					throw _T("Couldn't Create Command Tool");

				if(NULL == tool.CreateToolATC(pPalette))
					throw _T("Couldn't Create Tool");

				if(FALSE == AcTcGetManager()->LoadCatalogs())
					throw _T("Error loading Catalogs");
			}
		}
		catch(const TCHAR* pMessage)
		{
			acutPrintf(pMessage);
		}
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CSimpleToolPaletteApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CSimpleToolPaletteApp, asdkSimpleToolPalette, _CREATESIMPLE, CREATESIMPLE, ACRX_CMD_TRANSPARENT, NULL)
