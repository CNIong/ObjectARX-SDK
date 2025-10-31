//
// (C) Copyright 2002-2004 by Autodesk, Inc. 
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
/////////////////////////////////////////////
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"
#include "BlockViewDlg.h"

// This is command 'BLOCKVIEW'
void AsdkBlockView()
{
    //switch our resources to the foreground
    CAcModuleResourceOverride overr;
    //construct and display the preview dialog
    CBlockViewDlg dlg;
    dlg.DoModal();
}

// This is command 'CONFIGGS'
void AsdkConfigGS()
{
	const char* regEntry = NULL; 
	char regPath[2024];	
	
	// Get the current AutoCAD registry path 
	// e.g. Software\Autodesk\AutoCAD\R16.2\ACAD-301:409 
	regEntry = acrxProductKey();
	// this is the path we want	
	sprintf (regPath, "%s\\3DGS Configuration\\GSHEIDI10", regEntry); 
		
	// get the GsManager from current MDI Client Window 
	AcGsManager *pGsMgr = acgsGetGsManager (NULL); 	
	// if we go the gs manager ok
	if (pGsMgr != NULL)		
	{ 
		// get the GsClass factory
		AcGsClassFactory *pClassFactory = pGsMgr->getGSClassFactory(); 	
		// if we got it ok
		if (pClassFactory != NULL) 
		{
			// now get the gs config class
			AcGsConfig *pConfig = pClassFactory->getConfig(); 
			// if we got this ok too
			if (pConfig != NULL)
			{
				// display the config dialog
				pConfig->configure (regPath, true); 
			}
		}
	}
}
