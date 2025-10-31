//
//
// (C) Copyright 1990-2006 by Autodesk, Inc. 
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
#include "StdAfx.h"
//-----------------------------------------------------------------------------
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "CFilterDocumentReactor.h"


//-----------------------------------------------------------------------------
#define szRDS _RXST("Asdk")
 
 CSubSelFilter *pSSFilter;
 AsdkRings *pRings;
 CSubEntSelFilter *pSESFilter;
 void AppendEnt(AcDbEntity *);
 static CFilterDocumentReactor *pFilterDocReactor;

 
void AppendEnt(AcDbEntity *pEnt)
{

	AcDbBlockTable *pBT;
	AcDbBlockTableRecord *pBTR;

	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBT,AcDb::kForRead);
	pBT->getAt(ACDB_MODEL_SPACE,pBTR,AcDb::kForWrite);
	pBT->close();

	Acad::ErrorStatus es;

	//add entity to model space
	es = pBTR->appendAcDbEntity(pEnt);
	pBTR->close();

}

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint

class CSelectionFilterUIApp : public AcRxArxApp {

public:
	CSelectionFilterUIApp () : AcRxArxApp (){}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		// TODO: Add your initialization code here

        acutPrintf(_T("\n\nCommands: "));
		acutPrintf(_T("\n-------------------------------------------"));
		acutPrintf(_T("\nADDSUBENTFILTER -> Add subentity selection filter"));
		acutPrintf(_T("\nSUBENTSEL -> Do subentity selection\n"));
		acutPrintf(_T("\nDELSUBENTFILTER -> Delete subentity selection filter\n\n"));
		acutPrintf(_T("\nADDSUBSELFILTER -> Add subselection filter"));
		acutPrintf(_T("\nRINGS -> Add Rings(custom entity)"));
		acutPrintf(_T("\nDELSUBSELFILTER -> Delete subselection filter\n"));
		acutPrintf(_T("\nDELFILTERS -> Delete all filters\n"));

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {

		AsdkSelectionFilterUI_DelFilters();
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		// TODO: Add your code here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

   // ----- AsdkSelectionFilterUI.SubentSel command (do not rename)
	static void AsdkSelectionFilterUI_SubentSel(void)
	{
		// we have to allow duplicates; otherwise, the xref would be selectable
      // only once (because the main entity is the one that counts).
      
   setAllowDuplicateSelection(curDoc(), true); 
    ads_name sset, eName;
	AcDbObjectId id;
	
    // "_:n" gives us nested entities
    //
    if (RTNORM == acedSSGet(_T("_:n"), NULL, NULL, NULL, sset))
    {
        acutPrintf(_T("\n"));
        long len = 0;
        acedSSLength(sset, &len);
        for (long i = 0; i < len; i++)// For each entity in sset
        {
           
			resbuf *rb = NULL;
            // We use ssnamex() here, because the regular ssname()
            // would give only the main entity (the xref)
            //
            if (RTNORM == acedSSNameX(&rb, sset, i))//Get the sub entity
            {
                resbuf *rbWalk = rb;
                while (NULL != rbWalk)
                {
                    if (RTENAME == rbWalk->restype)
                    {
                        eName[0] = rbWalk->resval.rlname[0];
						eName[1] = rbWalk->resval.rlname[1];
						if(Acad::eOk == acdbGetObjectId(id, eName))
						{					
                            acutPrintf(_T("Entity %d: <%x>"), i, id.asOldId());
							AcDbEntity *pEnt;
							if (Acad::eOk == acdbOpenObject(pEnt, id, AcDb::kForRead))
							{
								acutPrintf(_T("(%s)\n"), pEnt->isA()->name());
								pEnt->close();
							}
							else
								acutPrintf(_T("\nCouldn't open object"));
						}
						rbWalk = NULL; //force quit out of loop	
					}
                    else
                        rbWalk = rbWalk->rbnext;
                }
                acutRelRb(rb);
            }
        }
        acedSSFree(sset);
	}  

	       setAllowDuplicateSelection(curDoc(), false); 
	}

	// ----- AsdkSelectionFilterUI._AddSubselFilter command (do not rename)
	static void AsdkSelectionFilterUI_AddSubselFilter(void)
	{

	  // Add new subselection filter for the current document
	
		if (!pFilterDocReactor){
			pFilterDocReactor = new CFilterDocumentReactor();
	        acDocManager->addReactor(pFilterDocReactor);
		}
		 pFilterDocReactor ->addSubSelFilter(curDoc());

	}

	
	// ----- AsdkSelectionFilterUI._AddSubentFilter command (do not rename)
	static void AsdkSelectionFilterUI_AddSubentFilter(void)
	{

			  // Add new subentity selection filter for the current document
		if (!pFilterDocReactor){
			pFilterDocReactor = new CFilterDocumentReactor();
	        acDocManager->addReactor(pFilterDocReactor);
		}
         pFilterDocReactor ->addSubEntSelFilter(curDoc());

	}


	// ----- AsdkSelectionFilterUI._DelFilters command (do not rename) (REMOVE ALL FILTERS
	static void AsdkSelectionFilterUI_DelFilters(void)
	{
		
			if (!pFilterDocReactor) return;
             pFilterDocReactor ->removeAllFilters();
          
			 acDocManager->removeReactor(pFilterDocReactor);
             delete pFilterDocReactor;
             pFilterDocReactor = NULL;
	         if (pRings != NULL)pRings ->setSubSelState(0);
		
		}

	// ----- AsdkSelectionFilterUI_Rings command (do not rename)
	static void AsdkSelectionFilterUI_Rings(void)
	{

		//Create the custom entity (Rings)
	 AcGePoint3d cen; 
	 ads_point pt; 
     ads_real radius_1;

     acedGetPoint(NULL, _T("\nClick to select center of circles: "), asDblArray( cen ));
	
	 pt[X] = cen[0]; pt[Y]=cen[1]; pt[Z]=cen[2];

     acedGetDist(pt, _T("\nDrag line to indicate radius of smallest circle: "), &radius_1);


	// Add new custom (Rings) entity
	pRings  = new AsdkRings(cen,(double) radius_1);
	pRings ->setDatabaseDefaults();
	AppendEnt((AcDbEntity *)pRings);  
	pRings ->close();
	
	}

	
	// ----- AsdkSelectionFilterUI._DelSubentFilter command (do not rename)
	static void AsdkSelectionFilterUI_DelSubentFilter(void)
	{
			if (!pFilterDocReactor) return;
             pFilterDocReactor->deleteSubEntSelFilter(curDoc());
	}

	// ----- AsdkSelectionFilterUI._DelSubselFilter command (do not rename)
	static void AsdkSelectionFilterUI_DelSubselFilter(void)
	{
	
			if (!pFilterDocReactor) return;
             pFilterDocReactor ->deleteSubSelFilter(curDoc());
	         if (pRings != NULL)pRings ->setSubSelState(0);

		
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CSelectionFilterUIApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CSelectionFilterUIApp, AsdkSelectionFilterUI, _AddSubentFilter, AddSubentFilter, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSelectionFilterUIApp, AsdkSelectionFilterUI, _AddSubselFilter, AddSubselFilter, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSelectionFilterUIApp, AsdkSelectionFilterUI, _DelFilters, DelFilters, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSelectionFilterUIApp, AsdkSelectionFilterUI, _Rings, Rings, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSelectionFilterUIApp, AsdkSelectionFilterUI, _SubentSel, SubentSel, ACRX_CMD_TRANSPARENT, NULL)


ACED_ARXCOMMAND_ENTRY_AUTO(CSelectionFilterUIApp, AsdkSelectionFilterUI, _DelSubentFilter, DelSubentFilter, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSelectionFilterUIApp, AsdkSelectionFilterUI, _DelSubselFilter, DelSubselFilter, ACRX_CMD_TRANSPARENT, NULL)
