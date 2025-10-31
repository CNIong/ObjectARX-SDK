//
// (C) Copyright 1999 by Autodesk, Inc. 
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
#include <aced.h>
#include <rxregsvc.h>

void initApp();
void unloadApp();

void helloWorld();

void initApp()
{
    // register a command with the AutoCAD command mechanism
    acedRegCmds->addCommand("HELLOWORLD_COMMANDS",
							"Hello",
							"Bonjour",
                            ACRX_CMD_TRANSPARENT,
                            helloWorld);
}

void unloadApp()
{
    acedRegCmds->removeGroup("HELLOWORLD_COMMANDS");
}

void helloWorld()
{
    acutPrintf("\nHello World!");
}

extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) 
	    {
		case AcRx::kInitAppMsg:
			acrxDynamicLinker->unlockApplication(pkt);
			acrxRegisterAppMDIAware(pkt);
			initApp();
			break;
		case AcRx::kUnloadAppMsg:
			unloadApp();
			break;
		default:
		break;
    }
    return AcRx::kRetOK;
}