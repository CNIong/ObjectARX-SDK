// (C) Copyright 1996 by Autodesk, Inc. 
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
//	project name:	Chameleon
//
//	file name:		access.h
//
//  Created:		October, 1996	
//
//	top class:		Access
//	problems:		.




// ### Access definition-headers ######################################################
// The needed modules and their definitions:

#ifndef _Access_H
#define _Access_H 1

// own header
#include "CustomApplication.h"		// CustomApplication

// arx Header
#include "accmd.h"		// AcRx, AppRetCode, acrxEntryPoint, acedRegCmds
#include "adscodes.h"	// RTNONE, RTNORM

// ### end header


// Command group name for registry.
#define IMAGE_COMMANDS	"IMAGE_COMMANDS"
  



// ... prototypes .....................................................................
// This prototypes of classes and functions that are needed in that module.

// ... Rx Module Interface Functions
extern "C" 
{ 	__declspec(dllexport)	AcRx::AppRetCode  acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);	}
void loadModule();
void unloadModule();
void cmdAccess();

// ... end prototypes ...
 

#endif // _Access_H




// ____________________________________________________________________________________
// END OF FILE
