// (C) Copyright 2004 by Autodesk, Inc. 
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

#include "stdafx.h"

#include <gcroot.h>
#include <vcclr.h>
#include "mgdinterop.h" 

// special headers
#include "_vcclrit.h"

static AcMgObjectFactoryBase __nogc * __nogc *g_PEs = NULL;

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch(msg) 
	{
		// onload of arx
		case AcRx::kInitAppMsg: 
		{
			acrxDynamicLinker->registerAppMDIAware(pkt);

			// we add code that will use global variables or native classes with 
			// static data members (for example, the ATL, MFC, and CRT libraries use global variables)
			// once we do this we will receive linker error messages at compile time. 
			// To get round this problem, we must add code to manually initialize the static variables
			// see http://support.microsoft.com/?id=814472 for more details
			__crt_dll_initialize();

			// create a new object factory array
			static AcMgObjectFactoryBase* PEs[] = 
			{
				new AcMgObjectFactory<Autodesk::ObjectDbxSample::Poly,AsdkPoly>(), 
				// end the array with a NULL
				NULL
			};

			g_PEs = PEs;
			
		}break;

		case AcRx::kPreQuitMsg:
		{
			// clean up
			int i=0;
			while (g_PEs[i]!=NULL)
				delete g_PEs[i++];

			// use atexit.
			// see http://support.microsoft.com/?id=814472
			__crt_dll_terminate();

		}break;
	}

	return AcRx::kRetOK;
}
