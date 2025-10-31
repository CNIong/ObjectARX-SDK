//
//
// (C) Copyright 2002-2006 by Autodesk, Inc. 
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

#include "layerDialog.h"
#include "adskMyDbReactor.h"
#include "util.h"
#include "adskDocReactor.h"



//-----------------------------------------------------------------------------
#define szRDS _RXST("adsk")

adskMyDbReactor	*pDbReactor = NULL; // Pointer to database reactor
adskDocReactor *pDocReactor = NULL; 
const int kBufferLength = 800;
const int kLayerNameLength = 200;
void ads_regen();
//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint

Adesk::UInt8 giDrawOrderCtl = 0;

class CdrawordersampApp : public AcRxArxApp {

public:
	CdrawordersampApp () : AcRxArxApp () {}
	
	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		//detach doc reactor
		
		clearReactor();
		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}


	// ----- adskdrawordersamp._SortByLayer command (do not rename)
	static void adskdrawordersamp_SortByLayer(void)
	{
		layerDialog dlg(CWnd::FromHandle(adsw_acadMainWnd()));
		dlg.DoModal();
	}
	

	//This function attach doc reactor and db reactor
	static void attachReactor()
	{
		if (pDbReactor == NULL) 
		{
			pDbReactor = new adskMyDbReactor();
			AcDbDatabase* pDb= acdbHostApplicationServices()->workingDatabase();
			//add db reactor
			pDb->addReactor(pDbReactor); 
			//add doc reactor
			if(pDocReactor == NULL)
			{
				pDocReactor = new adskDocReactor();
				pDocReactor->Attach();
			}
			//set drawOrderCtl
			giDrawOrderCtl = pDb->drawOrderCtl();
			pDb->setDrawOrderCtl(0);
			AcDbSortentsTable *pSortTab = NULL;
			if(getOrCreateSortEntsDictionary(pSortTab))
			{
				acutPrintf(_T("\nDrawOrderByLayer is enabled."));
			}	
			pSortTab->close();
			pSortTab = NULL;
		}else
		{
			acutPrintf(_T("\nDrawOrderBylayer is already enabled."));
		}
		 
	}

	
	//This function remove db and doc reactors
	static void clearReactor()
	{
		if(pDbReactor)
		{
			AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
			if (pDb) 
			{
				//remove Db reactor
				pDb->removeReactor(pDbReactor);
				acutPrintf(_T("\nDrawOrderBylayer is disabled."));
				delete pDbReactor;
				pDbReactor = NULL;
				
				//set to original DrawOrderCtl
				pDb->setDrawOrderCtl(giDrawOrderCtl);
				//remove doc reactor
			}
		}else
		{
			acutPrintf(_T("\nDrawOrderByLayer is already disabled."));
		}
		
		if(pDocReactor)
		{
			pDocReactor->Detach();
			delete pDocReactor;
			pDocReactor = NULL;
		}
	}
	// ----- adskdrawordersamp._DrawOrderByLayer command (do not rename)
	static void adskdrawordersamp_DrawOrderByLayer(void)
	{

		TCHAR yesNo[8]={_T("")};
		acedInitGet(0, _T("Yes No")); 
        acedGetKword(_T("\nOrder the draworder of all new entities based on the draw order of their layers? Yes/No <Yes>: "), yesNo); 

		if (!_tcsicmp(yesNo, _T("")) || !_tcsnicmp(yesNo,_T("Yes"),_tcslen(yesNo))) 
			attachReactor();
		else
			clearReactor();
	}
	
	// ----- adskdrawordersamp._ReverseInLayer command (do not rename)
	//This function reverse the draworders of entities on a selected layer
	static void adskdrawordersamp_ReverseInLayer(void)
	{
		Acad::ErrorStatus es ; 
		AcDbObjectIdArray arrAllLayers;
		
		//Get all the layer names
		if(getAllLayers(arrAllLayers))
		{
			TCHAR* keywords = new TCHAR[kBufferLength];
			TCHAR* prompts = new TCHAR[kBufferLength];
			_tcscpy(prompts,_T("\nPlease select a layer("));
			for(int i = 0; i < arrAllLayers.length(); i++)
			{
				AcDbObject* pLayer;
				if(Acad::eOk == acdbOpenObject(pLayer, arrAllLayers.at(i), AcDb::kForRead))
				{
					const TCHAR* name;
					AcDbLayerTableRecord::cast(pLayer)->getName(name);
					if(i==0)
						_tcscpy(keywords,name);
					else
						_tcscat(keywords,name);
					_tcscat(keywords,_T(" "));
					_tcscat(prompts,name);
					if(i < (arrAllLayers.length() - 1))
						 _tcscat(prompts,_T("/"));
					else
                        _tcscat(prompts,_T("):  "));
				}
				pLayer->close();
			}
			//Add layer names to the key words
			if (acedInitGet(RSG_NONULL, keywords) != RTNORM)
			{
				acutPrintf(_T("\nFailed to list layer names."));
				delete [] keywords;
				return;
			}
			delete [] keywords;
			TCHAR kword[kLayerNameLength];
			
			//Prompt user to select a layer name
			if(acedGetKword(prompts,kword)!=RTNORM)
			{
				acutPrintf(_T("\nFailed to get the layer name"));
				return;
			}

			AcDbObjectIdArray entsOnLayer;
			AcDbObjectIdArray eIds;
			//Get all the entities on selected layer
			if(getAllEntitiesOnLayer(kword, entsOnLayer))
			{
				AcDbSortentsTable *pSortTab = NULL;
				if(getOrCreateSortEntsDictionary(pSortTab))
				{
					//Get current draworders
					pSortTab->getRelativeDrawOrder(entsOnLayer);
					//reverese draworders
					for(int i = entsOnLayer.length() - 1; i>=0 ; i--)
					{
						eIds.append(entsOnLayer.at(i));
					}
					es = pSortTab->setRelativeDrawOrder(eIds);
				}	
				pSortTab->close();
				pSortTab = NULL;
				ads_regen();
			}
			
		}
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CdrawordersampApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CdrawordersampApp, adskdrawordersamp, _SortByLayer, SortByLayer, ACRX_CMD_TRANSPARENT, NULL)

ACED_ARXCOMMAND_ENTRY_AUTO(CdrawordersampApp, adskdrawordersamp, _DrawOrderByLayer, DrawOrderByLayer, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CdrawordersampApp, adskdrawordersamp, _ReverseInLayer, ReverseInLayer, ACRX_CMD_TRANSPARENT, NULL)
