// (C) Copyright 2004-2006 by Autodesk, Inc. 
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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include <gcroot.h>
#include <vcclr.h>
#include "mgdinterop.h" 

static AcMgObjectFactoryBase __nogc * __nogc *g_PEs = NULL;

extern "C" AcRx::AppRetCode __declspec(dllexport)
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch(msg) 
	{
		// onload of arx
		case AcRx::kInitAppMsg: 
		{
			acrxDynamicLinker->registerAppMDIAware(pkt);

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

		}break;
	}

	return AcRx::kRetOK;
}
