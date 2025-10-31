// (C) Copyright 1998-1999 by Autodesk, Inc. 
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

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//////////////////////////////////////////////////////////////
//
// Includes
//
//////////////////////////////////////////////////////////////

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

#include "stdafx.h"
#include "aced.h"
#include <adslib.h>
                 
//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp()
{
  acedRegCmds->addCommand( "MFCStatic",      // Group name 
                           "staticmfc",      // Global function name
                           "staticmfc",          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &MFCTest );         // Function pointer
  ads_printf( "\nEnter \"staticMfc\" to bring up the dialog.\n" );

}

void unloadApp()
{
    // Remove the command group because we are unloading
    //
    acedRegCmds->removeGroup( "MFCStatic" );
}

//////////////////////////////////////////////////////////////
//
// Entry point
//
//////////////////////////////////////////////////////////////
extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* )
{
  switch( msg ) 
  {
    case AcRx::kInitAppMsg: 
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

// END CODE APPEARING IN SDK DOCUMENT.
