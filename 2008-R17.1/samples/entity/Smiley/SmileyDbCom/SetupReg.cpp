//
// (C) Copyright 2000-2006 by Autodesk, Inc. 
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

// SetupReg.cpp: implementation of the setupRegistrar function
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "stdarx.h"
#include "SmileyDbCom.h"



extern HINSTANCE _hdllInstance;

//sets up the registrar
HRESULT setupRegistrar(/*[out]*/IRegistrar** p)
{
    USES_CONVERSION;
	HRESULT hRes = S_OK;
    hRes = CoCreateInstance(CLSID_Registrar, NULL,
                            CLSCTX_INPROC_SERVER, IID_IRegistrar, (void**)p);
	if (SUCCEEDED (hRes)) {
        //workaround to a workaround in ATL.DLL:
        //ATL registers everything with short file name to avoid the CreateProcess bug on NT
        //ARX-es are loaded with long file name but CoCreateInstance
        //will bring in another instance of the same dll because
        //LoadLibrary is unable to figure out that the dlls loaded with
        //long and short filenames are actually the same
        TCHAR szModule[_MAX_PATH];
        ::GetModuleFileName(_hdllInstance, szModule, _MAX_PATH);
	    (*p)->AddReplacement(OLESTR("MODULE_FIXED"),  T2OLE(szModule));
    }
    return hRes;
}

