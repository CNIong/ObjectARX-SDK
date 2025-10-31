//
// (C) Copyright 2002-2008 by Autodesk, Inc. 
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
#include "resource.h"
#include "acgitransient.h"
//-----------------------------------------------------------------------------
#define szRDS _RXST("ADS")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CAsdkTransientGraphicsApp : public AcRxArxApp {

public:
	static int m_nRollovertips;
	static int m_nSelctionPreview;
	CAsdkTransientGraphicsApp () : AcRxArxApp () 
	{
		
	}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) 
	{
		// TODO: Add your code here
		struct resbuf rb;
		acedGetVar(L"ROLLOVERTIPS", &rb);
		rb.resval.rint = m_nRollovertips; //reset
		acedSetVar(L"ROLLOVERTIPS", &rb);

		rb.resval.rint = m_nSelctionPreview; //off
		acedSetVar(L"SELECTIONPREVIEW", &rb);

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

public:
	// -----------------------------------------------------------------------------
	
public:

	// - ADSAsdkTransientGraphics.TGVisibility command (do not rename)
	static void AsdkTransientGraphicsTGVisibility(void)
	{
		// Add your code for command ADSAsdkTransientGraphics.TGVisibility here
		CString keyWord = _T("");
		CString strText = _T("Show Transient Graphics tooltip [");

		strText = strText + L" Yes" + L"/";
		keyWord = L" Yes";
		strText = strText + " No" + "/";
		keyWord = keyWord + " " +  " No";

		if(DocVars.docData().m_pTransientEntity == NULL)
		{
			strText = strText + "]" + "<" + L"No" + "> :";
		}
		else 
		{
			strText = strText + "]" + "<" + L"Yes" + "> :";
		}
		
		acedInitGet(0,keyWord);
		ACHAR kShowTransient[133];
		if(acedGetKword(strText, kShowTransient) != RTNORM)
			return;

		if(_tcsicmp(kShowTransient, L"Yes") == 0)
		{
			//off the rollovertips
			struct resbuf rb;
			acedGetVar(L"ROLLOVERTIPS", &rb);
			m_nRollovertips = rb.resval.rint;
			rb.resval.rint = 0; //off
			acedSetVar(L"ROLLOVERTIPS", &rb);

			acedGetVar(L"SELECTIONPREVIEW", &rb);
			m_nSelctionPreview = rb.resval.rint;
			rb.resval.rint = 0; //off
			acedSetVar(L"SELECTIONPREVIEW", &rb);


			//Add a text style called tooltip font
			AcDbTextStyleTableRecord *pTxtStyleRec;
			AcDbTextStyleTable *pTxtSTbl;
			AcDbObjectId styleObjectId;

			acdbHostApplicationServices()->workingDatabase()->getTextStyleTable(pTxtSTbl,AcDb::kForRead);

			if(pTxtSTbl->has(L"TOOLTIPSTYLE") == false)
			{
				pTxtSTbl->upgradeOpen();
				pTxtStyleRec = new AcDbTextStyleTableRecord();
				pTxtStyleRec->setName(L"TOOLTIPSTYLE");
				pTxtStyleRec->setFont(L"Arial",Adesk::kFalse,Adesk::kFalse,ANSI_CHARSET,DEFAULT_PITCH);
				pTxtSTbl->add(styleObjectId,pTxtStyleRec);
				pTxtStyleRec->close();
			}
			else
			{
				pTxtSTbl->getAt(L"TOOLTIPSTYLE", styleObjectId);
			}
			pTxtSTbl->close();

			//Add new the Transient Graphics
			AcGiTransientManager* pTransientManager = acgiGetTransientManager();

			if(DocVars.docData().m_pTransientEntity != NULL)
			{
				AcArray<int> viewportNumbers;
				DocVars.docData().m_pTransientEntity->getViewportsForTransientGraphics(viewportNumbers);
				pTransientManager->eraseTransient(DocVars.docData().m_pTransientEntity, viewportNumbers);
				DocVars.docData().ClenUp();
			}

			DocVars.docData().m_pTransientEntity = new AsdkTransientEntity();
			AcArray<int> viewportNumbers;

			struct resbuf *pRbVports = NULL;
			if(acedVports(&pRbVports) != RTNORM)
			{  
				acutPrintf(L"\nError in acedVports!"); 
			}
			
			// 
			// Loop the result buffer and store viewport numbers in the vector 
			// 
			while(pRbVports)
			{  
				// Skip RTLB 
				pRbVports = pRbVports->rbnext;
				// Store viewport number
				if(pRbVports->restype != RTSHORT) 
				{    
					acutPrintf(L"\nError in pRbVports: RTSHORT expected!"); 
				} 
				viewportNumbers.append(pRbVports->resval.rint); 
				
				// Skip LowerLeft Point, UpperRight Point and RTLE
				if(pRbVports != NULL)
					pRbVports = pRbVports->rbnext; 

				if(pRbVports != NULL)
					pRbVports = pRbVports->rbnext; 

				if(pRbVports != NULL)
					pRbVports = pRbVports->rbnext; 
				
				if(pRbVports != NULL)
					pRbVports = pRbVports->rbnext;  
			} 
			acutRelRb(pRbVports);

			DocVars.docData().m_pTransientEntity->setViewportsForTransientGraphics(viewportNumbers);
			pTransientManager->addTransient(DocVars.docData().m_pTransientEntity, kAcGiDirectShortTerm,
									0, viewportNumbers); 

			DocVars.docData().m_pTransientEntity->setTooltipTextStyle(styleObjectId);
			DocVars.docData().m_pInputPointMonitor = new AsdkInputPointMonitor(::acDocManagerPtr()->curDocument());
		}
		else if(_tcsicmp(kShowTransient, L"No") == 0)
		{
			struct resbuf rb;
			acedGetVar(L"ROLLOVERTIPS", &rb);
			rb.resval.rint = m_nRollovertips; //reset
			acedSetVar(L"ROLLOVERTIPS", &rb);

			rb.resval.rint = m_nSelctionPreview; //off
			acedSetVar(L"SELECTIONPREVIEW", &rb);

			//delete the Transient Graphics
			if(DocVars.docData().m_pTransientEntity != NULL)
			{
				AcArray<int> viewportNumbers;
				DocVars.docData().m_pTransientEntity->getViewportsForTransientGraphics(viewportNumbers);

				AcGiTransientManager* pTransientManager = acgiGetTransientManager();
				pTransientManager->eraseTransient(DocVars.docData().m_pTransientEntity, viewportNumbers);

				DocVars.docData().ClenUp();
			}
		}
	}

} ;

int CAsdkTransientGraphicsApp::m_nRollovertips = 0;
int CAsdkTransientGraphicsApp::m_nSelctionPreview = 0;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CAsdkTransientGraphicsApp)

// -----------------------------------------------------------------------------


ACED_ARXCOMMAND_ENTRY_AUTO(CAsdkTransientGraphicsApp, AsdkTransientGraphics, TGVisibility, TGV, ACRX_CMD_TRANSPARENT, NULL)
