// (C) Copyright 2002-2006 by Autodesk, Inc. 
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

#include "resource.h"
#include "makeCreation.h"



//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CSurfHelixApp : public AcRxArxApp {

public:
	CSurfHelixApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		acutPrintf(_T("\nCommands:"));

		acutPrintf(_T("\n1.  ADDPLANESURF"));
		acutPrintf(_T("\n2.  ADDEXTRUDSURF"));
		acutPrintf(_T("\n3.  ADDREVSURF"));
		acutPrintf(_T("\n4.  ADDSWEPTSURF"));
		acutPrintf(_T("\n5.  ADDLOFTSURF"));
		acutPrintf(_T("\n6.  ADDHELIX "));
		acutPrintf(_T("\n8.  ADDALL"));

		acutPrintf(_T("\n7.  MAKESECTION"));
		acutPrintf(_T("\n9.  GETSECTION"));
		acutPrintf(_T("\n10. ITERSECTIONS \n"));

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

	// - ADSKSurfHelix._addplanesurf command (do not rename)
	static void ADSKSurfHelix_addplanesurf(void)
	{				
		// Add a plane surfaces  using AcDbPlaneSurface Class
		 CMakeCreation::AddPlaneSurface();			
	}
		
	// - ADSKSurfHelix._addextrudsurf command (do not rename)
	static void ADSKSurfHelix_addextrudsurf(void)
	{	
		// Using AcDbExtrudedSurface class to create a extruded surface , 
		// creating a Table which has 4 legs and table top
		CMakeCreation::AddExtrudedSurface();
	}

	// - ADSKSurfHelix._addrevsurf command (do not rename)
	static void ADSKSurfHelix_addrevsurf(void)
	{
		// Using AcDbRevolvedSurface to create a revolved surface i.e create a Pen holder on top of the table
		CMakeCreation::AddRevolvesurface();			
	}

	// - ADSKSurfHelix._addsweptsurf command (do not rename)
	static void ADSKSurfHelix_addsweptsurf(void)
	{
		CMakeCreation::AddSweptSurface();	
	}

	// - ADSKSurfHelix._addloftsurf command (do not rename)
	static void ADSKSurfHelix_addloftsurf(void)
	{
		CMakeCreation::AddLoftedSurface();	
	}

	// - ADSKSurfHelix._addhelix command (do not rename)
	static void ADSKSurfHelix_addhelix(void)
	{
		CMakeCreation::AddHelix();		
	}

	// - ADSKSurfHelix._addall command (do not rename)
	static void ADSKSurfHelix_addall(void)
	{
		// Add your code for command ADSKSurfHelix._addall here
		// This is a utility command that just calls all the above surface commands and the helix generation command.
		CMakeCreation::AddPlaneSurface();
		CMakeCreation::AddExtrudedSurface();
		CMakeCreation::AddRevolvesurface();
		CMakeCreation::AddSweptSurface();
		CMakeCreation::AddLoftedSurface();
		CMakeCreation::AddHelix();
	}

	// - ADSKSurfHelix._makeSection command (do not rename)
	static void ADSKSurfHelix_makeSection(void)
	{
		CMakeCreation::MakeSection();
	}

	// - ADSKSurfHelix._getSection command (do not rename)
	static void ADSKSurfHelix_getSection(void)
	{
		CMakeCreation::GetSection();
	}

	// - ADSKSurfHelix._iterSections command (do not rename)
	static void ADSKSurfHelix_iterSections(void)
	{
		CMakeCreation::IterSections();
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CSurfHelixApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CSurfHelixApp, ADSKSurfHelix, _addplanesurf, addplanesurf, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSurfHelixApp, ADSKSurfHelix, _addextrudsurf, addextrudsurf, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSurfHelixApp, ADSKSurfHelix, _addrevsurf, addrevsurf, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSurfHelixApp, ADSKSurfHelix, _addsweptsurf, addsweptsurf, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSurfHelixApp, ADSKSurfHelix, _addloftsurf, addloftsurf, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSurfHelixApp, ADSKSurfHelix, _addhelix, addhelix, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSurfHelixApp, ADSKSurfHelix, _addall, addall, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSurfHelixApp, ADSKSurfHelix, _makeSection, makeSection, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSurfHelixApp, ADSKSurfHelix, _getSection, getSection, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSurfHelixApp, ADSKSurfHelix, _iterSections, iterSections, ACRX_CMD_TRANSPARENT, NULL)
