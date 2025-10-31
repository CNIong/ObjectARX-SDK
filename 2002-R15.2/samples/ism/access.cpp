// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
//	file name:		access.cpp
//
//  Created:		October, 1996	
//
//	problems:		.
//




// ### Access definition-headers ####################################################
// The header file of this module:

// access.h
#include "access.h"	// all

// ### end header



// !!! Global functions !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// ___ loadModule _____________________________________________________________________
//	
//	description:	Add command to the ARX command stack.
//					Rebuild the ARX runtime class tree after new classes are added. 
//	parameter:		.
//	return value:	.
//	problems:		.
void loadModule()
{
	// Add command to the ARX command stack.
	acedRegCmds->addCommand(IMAGE_COMMANDS,
							"ISMEXAMPLE",
							"ISMEXAMPLE",
							ACRX_CMD_MODAL,
							&cmdAccess);	
	// Output
	ads_printf("To start the example type the command: ISMEXAMPLE . \n"); 
}
// ___ end loadModule




// ___ unloadModule ______________________________________________________________________
//	
//	description:	Unloads the ARX module filename. Before physically unloading the module,
//					the application's acrxEntryPoint() function is called with the kUnloadAppMsg 
//					message to allow it to perform cleanup.  
//					Notification is also sent about the impending unload.
//	parameter:		.
//	return value:	.
//	problems:		.
void unloadModule()
{
	// Removes the command group with the name cmdGroupName from the CommandStack and deletes 
	// the command group dictionary object and all the AcEdCommand objects stored within it.
	acedRegCmds->removeGroup(IMAGE_COMMANDS);
}
// ___ end unloadModule




// ___ acrxEntryPoint ______________________________________________________________________
//	
//	description:	Locally defined entry point invoked by Rx.
//
//	parameter:		msg		The first parameter, a data member of class AcRx called msg, 
//							represents the message sent from the ARX kernel to the application.
//					pkt		The second parameter is an opaque handle to data passed to 
//							the lock and unlock functions for the application.
//
//	return value:	The function returns a status code, such as RSRSLT and RSERR.
//	problems:		.
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
    switch(msg) {
	    case AcRx::kInitAppMsg:
	        acrxDynamicLinker->unlockApplication(pkt);
			// register as MDI aware
			acrxDynamicLinker->registerAppMDIAware(pkt);
            // Load in the db portion of the ISM
            if (!acrxDynamicLinker->loadModule("acISMobj15.dbx", true)) {
    		    return AcRx::kRetError;
            }
			loadModule();
			break;

	    case AcRx::kUnloadAppMsg:
	        unloadModule();
            // Unload the db portion of the ISM
            acrxDynamicLinker->unloadModule("acISMobj15.dbx");
			break;
	    case AcRx::kLoadDwgMsg:
	    case AcRx::kUnloadDwgMsg:
	    case AcRx::kInvkSubrMsg:
	    default:
			break;
    }
    return AcRx::kRetOK;
}
// ___ end acrxEntryPoint




// ___ cmdAccess ____________________________________________________________________
//	
//	description:	This function is called from AutoCad when the command "ISMEXAMPLE"
//					is used.
//					Attachs an image.
//	parameter:		.
//	return value:	.
//	problems:		.
void cmdAccess()
{
	// declaration
	Acad::ErrorStatus	ErrorStatus;

	CustomApplication	oCustomApplication;	// Example object
	AcDbObjectId		EntityId;			// Id of the 

	// attach image
	ErrorStatus = oCustomApplication.newImageAttach (EntityId);	// returns Entity Id.
		// check
		if (ErrorStatus != Acad::eOk)
		// Failed to attach image.
			ads_printf("Error: Attach example image failed.\n"); 

	// manipulate image
	ErrorStatus = oCustomApplication.manipulate (EntityId);
		// check
		if (ErrorStatus != Acad::eOk)
		// Failed to manipulate image.
			ads_printf("Error: Manipulate example image failed.\n"); 

} 
// ___ end cmdAccess


// !!! end Global functions 




// ____________________________________________________________________________________
// END OF FILE
