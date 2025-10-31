// (C) Copyright 1996-2007 by Autodesk, Inc. 
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
//////////////////////////////////////////////////////////////
//
// Includes
//
//////////////////////////////////////////////////////////////
#define _AFX_NOFORCE_LIBS // we do not want to link to MFC DLLs or libs
#ifdef _DEBUG
#define WAS_DEBUG
#undef _DEBUG
#endif

#ifndef _AFXDLL
#define _AFXDLL //VC8:Building MFC application with /MD[d] (CRT dll version) requires MFC shared dll version
#endif

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "afxwin.h"  // need this because rxmfcapi.h needs windows header. 


#ifdef WAS_DEBUG
#undef WAS_DEBUG
#define _DEBUG
#endif

#include "aced.h"
#include "adslib.h"
#include "rxmfcapi.h"



#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

//////////////////////////////////////////////////////////////
//
// Standard C Test function
//
//////////////////////////////////////////////////////////////

void caps();                   // ARX callbacks 
void mouse();
void letterX();
void CC();
void uncaps();                   // ARX callbacks 
void unmouse();
void unletterX();
void unCC();

BOOL filterLC(MSG *pMsg);      // hook function for capsing.
BOOL filterMouse(MSG *pMsg);   // hook function for making mouse dragging
                               // only horizontal or vertical based on 
                               // SHIFT or Control key is pressed or not.
BOOL filterLetterX(MSG *pMsg); // hook for removing character 'x' or 'X'
void watchCC(const MSG *pMsg); // hook for watching if Ctrl-C is pressed.

static BOOL vMode; // holds mouse vertical Mode status
static BOOL hMode; // holds mouse horizontal Mode status

// preventing from inserting the same hook twice.
static BOOL capsDone = FALSE;
static BOOL mouseDone = FALSE;
static BOOL letterXDone = FALSE;
static BOOL CCDone = FALSE;

//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////


void initApp()
{

  acedRegCmds->addCommand( _T("MKEvents"),      // Group name 
                           _T("caps"),      // Global function name
                           _T("caps"),          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &caps );         // Function pointer
  acedRegCmds->addCommand( _T("MKEvents"),      // Group name 
                           _T("vhmouse"),      // Global function name
                           _T("vhmouse"),          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &mouse );         // Function pointer
  acedRegCmds->addCommand( _T("MKEvents"),      // Group name 
                           _T("watchCC"),      // Global function name
                           _T("watchCC"),          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &CC );         // Function pointer
  acedRegCmds->addCommand( _T("MKEvents"),      // Group name 
                           _T("noX"),      // Global function name
                           _T("noX"),          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &letterX );         // Function pointer

  acedRegCmds->addCommand( _T("MKEvents"),      // Group name 
                           _T("uncaps"),      // Global function name
                           _T("uncaps"),          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &uncaps );         // Function pointer
  acedRegCmds->addCommand( _T("MKEvents"),      // Group name 
                           _T("unvhmouse"),      // Global function name
                           _T("unvhmouse"),          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &unmouse );         // Function pointer
  acedRegCmds->addCommand( _T("MKEvents"),      // Group name 
                           _T("unwatchCC"),      // Global function name
                           _T("unwatchCC"),          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &unCC );         // Function pointer
  acedRegCmds->addCommand( _T("MKEvents"),      // Group name 
                           _T("yes"),      // Global function name
                           _T("yes"),          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &unletterX );         // Function pointer


  
  acutPrintf( _T(".OK!\n") );

}

void unloadApp()
{
  // Remove the command group because we are unloading
  //  
  acedRegCmds->removeGroup( _T("MKEvents") );

  // Removing all hooks <no matter they're planted or not>

  if (capsDone == TRUE)
      acedRemoveFilterWinMsg(filterLC); 

  if (mouseDone == TRUE)
      acedRemoveFilterWinMsg(filterMouse); 

  if (letterXDone == TRUE)
      acedRemoveFilterWinMsg(filterLetterX); 

  if (CCDone == TRUE)
      acedRemoveWatchWinMsg(watchCC); 

}


//////////////////////////////////////////////////////////////
//
// Entry point
//
//////////////////////////////////////////////////////////////

extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* pkt)
{
  switch( msg ) 
  {
    case AcRx::kInitAppMsg: 
      initApp();
      acrxUnlockApplication(pkt);
	  acrxDynamicLinker->registerAppMDIAware(pkt);
      break;
    case AcRx::kUnloadAppMsg: 
      unloadApp(); 
      break;
    default:
      break;
  }
  return AcRx::kRetOK; 
}



//////////////////////////////////////////////////////////////

BOOL filterLC(MSG *pMsg)
{    
    // Change All lowercase to caps!!
    if (pMsg->message == WM_CHAR && (pMsg->wParam >= 97 && pMsg->wParam <= 122))
            pMsg->wParam -=32;

    return FALSE; // continue
}


// Pressing CTRL key when dragging makes the mouse moves vertical only
// Pressing SHIHT key when dragging makes the mouse moves horizontal only

BOOL filterMouse(MSG *pMsg)
{
    static long ptx=0;
    static long pty=0;

    if (pMsg->message == WM_MOUSEMOVE || pMsg->message == WM_LBUTTONDOWN
        || pMsg->message == WM_LBUTTONUP)
    {
        if ((pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP) &&
             (vMode == TRUE ||  hMode == TRUE))
        {
            pMsg->lParam = MAKELONG(ptx, pty);
            return FALSE;
        }

        if (pMsg->wParam == MK_CONTROL)
        {
            if (vMode == TRUE) // Prev Pt is set already
            {
                pMsg->lParam = MAKELONG(ptx, HIWORD(pMsg->lParam));
                pty = HIWORD(pMsg->lParam);
            } else 
                ptx= LOWORD(pMsg->lParam);
            vMode = TRUE;
            hMode = FALSE;
        } else if (pMsg->wParam == MK_SHIFT)
        {
            if (hMode == TRUE) // Prev Pt is set already
            {
                pMsg->lParam = MAKELONG(LOWORD(pMsg->lParam), pty);
                ptx = LOWORD(pMsg->lParam);
            } else
                pty= HIWORD(pMsg->lParam);
            hMode = TRUE;
            vMode = FALSE;
        } else
        {
            vMode = hMode =  FALSE;
        }
    }

    return FALSE; // continue
}


BOOL filterLetterX(MSG *pMsg)
{
    // Remove letter x or X
    if (pMsg->message == WM_CHAR && (pMsg->wParam == 120 || pMsg->wParam == 88))
        return TRUE; // throw away the message
    return FALSE; // continue
}

// watch for Control-C
void watchCC(const MSG *pMsg)
{
    if (pMsg->message == WM_CHAR && pMsg->wParam == 3)
        acutPrintf(_T("\nCtrl-C is pressed\n"));
}

///////////////////////

void caps()
{
    if (capsDone == TRUE) // already has the hook??
      return;
    acutPrintf( _T("Capsing...\n") );
    if (acedRegisterFilterWinMsg(filterLC) == FALSE)
        acutPrintf(_T("Can't register Windows Msg hook - Lower->upper\n"));
    else
      capsDone = TRUE;
}

void uncaps()
{
    if (capsDone == TRUE) 
    {
        acedRemoveFilterWinMsg(filterLC); 
        capsDone = FALSE;
    }
}

void mouse()
{
    if (mouseDone == TRUE) // already has the hook?
      return;
  
    ::vMode = FALSE;
    ::hMode = FALSE;
    acutPrintf( _T("mouseing...\n") );

    if (acedRegisterFilterWinMsg(filterMouse) == FALSE)
        acutPrintf(_T("Can't register Windows Msg hook - VH - mouse\n")); 
    else
        mouseDone = TRUE;
}

void unmouse()
{
 
    if (mouseDone == TRUE)
    {
        acedRemoveFilterWinMsg(filterMouse); 
        mouseDone = FALSE;
    }
}


void letterX()
{
    if (letterXDone == TRUE) // already has the hook?
      return;
    acutPrintf( _T("filtering letter x/X...\n") );
    if (acedRegisterFilterWinMsg(filterLetterX) == FALSE)
      acutPrintf(_T("Can't register Windows Msg hook - letterX\n"));
    else 
      letterXDone = TRUE;
}

void  unletterX()
{
    if (letterXDone == TRUE) 
    {
        acedRemoveFilterWinMsg(filterLetterX); 
        letterXDone = FALSE;
    }
}

void CC()
{
  
    if (CCDone == TRUE) // already has the hook?
      return;

    acutPrintf( _T("watching ctrl-C...\n") );
    if (acedRegisterWatchWinMsg(watchCC) == FALSE)
        acutPrintf(_T("Can't register Windows Msg hook - WatchCC\n"));
    else
        CCDone = TRUE;

}

void unCC()
{
  if (CCDone == TRUE) {
      acedRemoveWatchWinMsg(watchCC); 
      CCDone = FALSE;
  }

}





