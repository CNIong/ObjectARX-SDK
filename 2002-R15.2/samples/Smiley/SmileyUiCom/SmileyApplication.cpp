//
// (C) Copyright 2000 by Autodesk, Inc. 
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

// SmileyApplication.cpp : Implementation of CSmileyApplication

#include "stdafx.h"
#include "SmileyUiCom.h"
#include "SmileyApplication.h"
#include "acdocman.h"

/////////////////////////////////////////////////////////////////////////////
// CSmileyApplication

STDMETHODIMP CSmileyApplication::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISmileyApplication
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

extern HINSTANCE hArxModule;

typedef void (*CommandFunc)();

STDMETHODIMP CSmileyApplication::CreateSmiley()
{
	try {
		if ( NULL == hArxModule )
			throw Acad::eNullHandle;

		const int kSmileyLock = 1;

        CommandFunc createSmileyFuncPtr = (CommandFunc)::GetProcAddress( hArxModule, "createSmiley" );
		if ( NULL == createSmileyFuncPtr )
			throw Acad::eNotApplicable;

		AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
		AcAxDocLock docLock( pDb, AcAxDocLock::kCurDocSwitch );
		if(docLock.lockStatus() != Acad::eOk)
			throw docLock.lockStatus();
		
		if ( !acedSetOLELock( kSmileyLock ))
			throw Acad::eLockConflict;

		(*createSmileyFuncPtr)();
		
		acedClearOLELock(kSmileyLock);
		acedPostCommandPrompt();
	}
    catch(const Acad::ErrorStatus)
    {
        return Error(L"Failed to create Smiley through application interface.",IID_ISmileyApplication,E_FAIL);
    }
	return S_OK;
}
