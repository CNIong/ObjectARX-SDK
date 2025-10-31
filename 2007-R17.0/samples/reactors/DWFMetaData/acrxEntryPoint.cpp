//  Copyright 2004-2006 by Autodesk, Inc.
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
//----- acrxEntryPoint.h
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "DWFReactors.h"
#include "DWFEntReactor.h"


AcTestDMMEntReactor  gClientDMMReactor;
//-----------------------------------------------------------------------------
#define szRDS _RXST("")


AcTestPublishReactor gPublishReactor;
HINSTANCE ghInst1;
//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CDWFMetaDataApp : public AcRxArxApp {

public:
	CDWFMetaDataApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		// TODO: Add your initialization code here

		bool bRet = false;

		if(!acrxServiceIsRegistered(_T("AcPublish"))) 
		{
		    bRet = acrxLoadModule(_T("AcPublish.arx"), false, false);
		}
 
		
		HINSTANCE hInst = ::GetModuleHandle(_T("AcPublish.arx"));
		if (hInst)
		{  
		ACGLOBADDPUBLISHREACTOR pAcGlobAddPublishReactor = 
		(ACGLOBADDPUBLISHREACTOR)GetProcAddress(hInst,  "AcGlobAddPublishReactor");
			if (pAcGlobAddPublishReactor != NULL)
			{
				pAcGlobAddPublishReactor(&gPublishReactor);
			}
		}

		if (!acrxServiceIsRegistered(_T("AcEPlotX"))) 
		{
			bRet = acrxLoadModule(_T("AcEPlotx.arx"), false, false);		
			ghInst1 = ::GetModuleHandle(_T("AcEPlotX.arx"));
			
		}
		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		HINSTANCE hInst = ::GetModuleHandle(_T(/*MSG0*/"AcPublish.arx"));
		if (hInst)
		{
			ACGLOBREMOVEPUBLISHREACTOR pAcGlobRemovePublishReactor = (ACGLOBREMOVEPUBLISHREACTOR)GetProcAddress(
			hInst, "AcGlobRemovePublishReactor");
			if (pAcGlobRemovePublishReactor != NULL)
				pAcGlobRemovePublishReactor(&gPublishReactor);
		}
		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CDWFMetaDataApp)

