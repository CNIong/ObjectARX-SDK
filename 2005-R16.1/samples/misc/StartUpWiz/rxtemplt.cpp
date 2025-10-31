// 
// (C) Copyright 1993-1999 by Autodesk, Inc. 
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

#include "stdafx.h"
#include "rxtemplt.h"
                 
//////////////////////////////////////////////////////////////
//
// Standard C Test function
//
//////////////////////////////////////////////////////////////

void rxTest()
{
  // Clear AutoCAD OEM command throat before issuing any 
  // commands or returning from Wizard. 
  ads_command(RTNONE);
  MFCTest();
}

//////////////////////////////////////////////////////////////

void rxTest0()
{
  // Clear AutoCAD OEM command throat before issuing any 
  // commands or returning from Wizard. 
  ads_command(RTNONE);
  MFCTest0();
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp()
{
  InitMFC();

  acedRegCmds->addCommand( "StartWiz",        // Group name 
                           "StartWiz",        // Global function name
                           "StartWiz",        // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &rxTest );         // Function pointer

  acedRegCmds->addCommand( "ShowWiz",        // Group name 
                           "ShowWiz",        // Global function name
                           "ShowWiz",        // Local function name
                           ACRX_CMD_MODAL,   // Type
                           &rxTest0 );       // Function pointer
}

void unloadApp()
{
  // Remove the command group because we are unloading
  //
  acedRegCmds->removeGroup( "StartWiz" );

  // fin MFC
  EndMFC();
}

//////////////////////////////////////////////////////////////
//
// Entry point
//
//////////////////////////////////////////////////////////////


extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        // This application can be unloaded
        acrxDynamicLinker->unlockApplication(pkt);
        // This is an MDI aware application
        acrxDynamicLinker->registerAppMDIAware(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
		break;
    }
    return AcRx::kRetOK;
}
