//
//
// (C) Copyright 2002-2003 by Autodesk, Inc. 
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
//----- adskDocReactor.cpp : Implementation of adskDocReactor
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "adskDocReactor.h"
#include "adskMyDbReactor.h"

//-----------------------------------------------------------------------------
ACRX_CONS_DEFINE_MEMBERS(adskDocReactor, AcApDocManagerReactor, 1)

//-----------------------------------------------------------------------------
adskDocReactor::adskDocReactor (const bool autoInitAndRelease) : AcApDocManagerReactor(), mbAutoInitAndRelease(autoInitAndRelease) {
	if ( autoInitAndRelease ) {
		if ( acDocManager )
			acDocManager->addReactor (this) ;
		else
			mbAutoInitAndRelease =false ;
	}
	
}

//-----------------------------------------------------------------------------
adskDocReactor::~adskDocReactor () {
	Detach () ;
}

//-----------------------------------------------------------------------------
void adskDocReactor::Attach () {
	Detach () ;
	if ( !mbAutoInitAndRelease ) {
		if ( acDocManager ) {
			acDocManager->addReactor (this) ;
			mbAutoInitAndRelease =true ;
		}
	}
}

void adskDocReactor::Detach () {
	if ( mbAutoInitAndRelease ) {
		if ( acDocManager ) {
			acDocManager->removeReactor (this) ;
			mbAutoInitAndRelease =false ;
		}
	}
}

AcApDocManager *adskDocReactor::Subject () const {
	return (acDocManager) ;
}

bool adskDocReactor::IsAttached () const {
	return (mbAutoInitAndRelease) ;
}  



extern bool gbDraworderChanged;

//If the draworder has been changed, regen the drawing 
//
void  adskDocReactor::documentLockModeChanged(AcApDocument* pDoc, AcAp::DocLockMode myPreviousMode, 
			AcAp::DocLockMode myCurrentMode, AcAp::DocLockMode currentMode, const char* pGlobalCmdName)
{
	if(pGlobalCmdName[0]=='#'&& gbDraworderChanged == true)
	{
		ads_regen();
		acutPrintf("regened change mode");
		gbDraworderChanged = false;
	}
}