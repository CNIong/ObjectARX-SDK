//
//
// (C) Copyright 1990-2003 by Autodesk, Inc. 
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
//----- CFilterDocumentReactor.cpp : Implementation of CFilterDocumentReactor
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "CFilterDocumentReactor.h"

//-----------------------------------------------------------------------------
ACRX_CONS_DEFINE_MEMBERS(CFilterDocumentReactor, AcApDocManagerReactor, 1)

//-----------------------------------------------------------------------------
CFilterDocumentReactor::CFilterDocumentReactor (const bool autoInitAndRelease) : AcApDocManagerReactor(), mbAutoInitAndRelease(autoInitAndRelease) {
	if ( autoInitAndRelease ) {
		if ( acDocManager )
			acDocManager->addReactor (this) ;
		else
			mbAutoInitAndRelease =false ;
	}

}

//-----------------------------------------------------------------------------
CFilterDocumentReactor::~CFilterDocumentReactor () {
	Detach () ;
}

//-----------------------------------------------------------------------------
void CFilterDocumentReactor::Attach () {
	Detach () ;
	if ( !mbAutoInitAndRelease ) {
		if ( acDocManager ) {
			acDocManager->addReactor (this) ;
			mbAutoInitAndRelease =true ;
		}
	}
}

void CFilterDocumentReactor::Detach () {
	if ( mbAutoInitAndRelease ) {
		if ( acDocManager ) {
			acDocManager->removeReactor (this) ;
			mbAutoInitAndRelease =false ;
		}
	}
}

void CFilterDocumentReactor::documentToBeDestroyed(AcApDocument * pDocToDestroy)
{
	 //Delete each of the filters on this document
	  deleteSubSelFilter(pDocToDestroy);
	  deleteSubEntSelFilter(pDocToDestroy);
}


//Add a subselection filter
	  void CFilterDocumentReactor::addSubSelFilter(AcApDocument* pDoc)
    {
        if (pDoc == NULL)
            return;

        SSFMapIterator filtIter = mSSFMap.find((long) pDoc);
        if (filtIter == mSSFMap.end()) {
            CSubSelFilter *pSSFilter = new CSubSelFilter();
            pDoc->inputPointManager()->addSubSelectFilter(pSSFilter);
			acutPrintf("\nSubselection filter added to %s ",pDoc->fileName());
            SSFMapPair data((long) pDoc, pSSFilter);
            mSSFMap.insert(data);
        }
    }

	//Delete subselection filter
void CFilterDocumentReactor::deleteSubSelFilter(AcApDocument* pDoc)
    {
        assert(pDoc != NULL);
        if (pDoc == NULL)
            return;

        SSFMapIterator filtIter = mSSFMap.find((long) pDoc);
        if (filtIter != mSSFMap.end()) {
             CSubSelFilter *pSSFilter = (*filtIter).second;
            pDoc->inputPointManager()->removeSubSelectFilter(pSSFilter);
			acutPrintf("\nSubselection filter on %s has been removed",pDoc->fileName());
            assert(pSSFilter != NULL);
            delete pSSFilter;
			pSSFilter = NULL;
            mSSFMap.erase((long) pDoc);
        }
    }


//Add a subentity selection filter
	  void CFilterDocumentReactor::addSubEntSelFilter(AcApDocument* pDoc)
    {
        if (pDoc == NULL)
            return;

        SESFMapIterator filtIter = mSESFMap.find((long) pDoc);
        if (filtIter == mSESFMap.end()) {
            CSubEntSelFilter *pSESFilter = new CSubEntSelFilter();
			addSSgetFilterInputContextReactor(pDoc, pSESFilter); 
			acutPrintf("\nSubentity selection filter added to %s ",pDoc->fileName());
			SESFMapPair data((long) pDoc, pSESFilter);
            mSESFMap.insert(data);
        }
    }

	//Delet subentity selection filter
void CFilterDocumentReactor::deleteSubEntSelFilter(AcApDocument* pDoc)
    {
        assert(pDoc != NULL);
        if (pDoc == NULL)
            return;

        SESFMapIterator filtIter = mSESFMap.find((long) pDoc);
        if (filtIter != mSESFMap.end()) {
             CSubEntSelFilter *pSESFilter = (*filtIter).second;
			assert(pSESFilter != NULL);
		    removeSSgetFilterInputContextReactor(pDoc, pSESFilter);
			acutPrintf("\nSubentity selection filter on %s has been removed",pDoc->fileName());
            delete pSESFilter;
			pSESFilter = NULL;
            mSESFMap.erase((long) pDoc);

        }
    }

	void CFilterDocumentReactor::removeAllFilters()
    {
        AcApDocumentIterator* pIter = acDocManager->newAcApDocumentIterator();

        for (; !pIter->done(); pIter->step()) {
            deleteSubEntSelFilter(pIter->document());
			deleteSubSelFilter(pIter->document());
        }
    }

