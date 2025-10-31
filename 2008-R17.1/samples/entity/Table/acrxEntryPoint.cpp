//
//
// (C) Copyright 2003-2007 by Autodesk, Inc. 
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

#include "asdktable.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


//-----------------------------------------------------------------------------
#define szRDS _RXST("Asdk")

#include "BlkDefDlg.h"



//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CtableApp : public AcRxArxApp {

public:
	CtableApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		// TODO: Add your initialization code here

		acutPrintf(ACRX_T("\nCommands defined in this sample: "));
		acutPrintf(ACRX_T("\n#0 BlkTbl: popps up a dialog which lists out all blocks. A table can be created from choosing a block and a table style."));
		acutPrintf(ACRX_T("\n#1 DatLnk: creates a data link of excel type and sets it to cell (2,2)."));
		acutPrintf(ACRX_T("\n#2 BrkTbl: breaks a table at the 1/3 of its height."));
		acutPrintf(ACRX_T("\n#3 TblTpl: creates a table template from the selected table and creates a table style 'MyTableStyle' to hold the table template."));
		acutPrintf(ACRX_T("\n#4 MltCnt: creates multiple contents, two blocks and a text, in cell (3, 0)."));
		acutPrintf(ACRX_T("\n#5 RstTbl: restores a table if it is broken."));
		
		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		// TODO: Add your code here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

	// ----- Asdktable._blktbl command (do not rename)
	static void Asdktable_blktbl(void)
	{
		// Add your code for command Asdktable._blktbl here
		CAcModuleResourceOverride resOverride;
			
		// Create the dialog
		CBlkDefDlg *pDlg = new CBlkDefDlg(acedGetAcadFrame());
		pDlg->DoModal();
		
		pDlg->DestroyWindow();
		delete pDlg;
	}

	//////////////////////////////////////////////////////////////////////////
	//	Table Enhancements
	//////////////////////////////////////////////////////////////////////////

	// - Asdktable._datlnk command (do not rename)
	static void Asdktable_datlnk(void)
	{
		// Add your code for command Asdktable._datlnk here
		createAndSetDataLink();
	}

	// - Asdktable._brktbl command (do not rename)
	static void Asdktable_brktbl(void)
	{
		// Add your code for command Asdktable._brktbl here
		breakTable();
	}

	// - Asdktable._tbltpl command (do not rename)
	static void Asdktable_tbltpl(void)
	{
		// Add your code for command Asdktable._tbltpl here
		createTemplate();
	}

	// - Asdktable._mltcnt command (do not rename)
	static void Asdktable_mltcnt(void)
	{
		// Add your code for command Asdktable._mltcnt here
		createMultipleContent();
	}

	// - Asdktable._rsttbl command (do not rename)
	static void Asdktable_rsttbl(void)
	{
		// Add your code for command Asdktable._rsttbl here
		restoreTable();
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CtableApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CtableApp, Asdktable, _blktbl, blktbl, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CtableApp, Asdktable, _datlnk, datlnk, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CtableApp, Asdktable, _brktbl, brktbl, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CtableApp, Asdktable, _tbltpl, tbltpl, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CtableApp, Asdktable, _mltcnt, mltcnt, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CtableApp, Asdktable, _rsttbl, rsttbl, ACRX_CMD_TRANSPARENT, NULL)
