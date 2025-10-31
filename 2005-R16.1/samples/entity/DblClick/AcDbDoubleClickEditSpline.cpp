//
// (C) Copyright 2001 by Autodesk, Inc. 
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
// AcDbDoubleClickEditSpline.cpp: implementation of the AcDbDoubleClickEditSpline class.

#include "stdafx.h"
#include "resource.h"
#include "AcDblClkEdit.h"
#include "AcDbDoubleClickEditSpline.h"
#include "acdocman.h"
#include "dbspline.h"
#include "dbpl.h"
#include "math.h"
#include "dbxutil.h"
#include "actrans.h"
#include "dbtrans.h"
#include "geassign.h"




#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AcDbDoubleClickEditSpline::AcDbDoubleClickEditSpline()
{

}

AcDbDoubleClickEditSpline::~AcDbDoubleClickEditSpline()
{

}


void AcDbDoubleClickEditSpline::startEdit(AcDbEntity *pEnt, AcGePoint3d clickpt)
{
	// Implement the startEdit notification handler to catch when
	// a user double-clicks a 'SPLINE' entity
	
	// Get the Current Document
	AcApDocument *pDoc=acDocManager->curDocument();
	AcDbSpline *pLine;
	
	// Cast the AcDbEntity pointer to AcDbSpline		
	if(pEnt->isKindOf(AcDbSpline::desc()) == Adesk::kTrue)
		pLine=AcDbSpline::cast(pEnt);
	else
	{
		acutPrintf("Error: Invalid AcDbSpline Entity");
		return;
	}
	
	acDocManager->lockDocument(pDoc,AcAp::kWrite);
	
	//Upgrade to write
	if(pLine->upgradeOpen()!=Acad::eOk)
	{
		acutPrintf("Error: Could Not open AcDbSpline Entity");
		return;
	}

	// iterate through all the vertices to find which
	// segment was clicked on, and place a fit-point there.
	for(int c=0;c<pLine->numFitPoints()-1;c++)
	{
		AcGePoint3d pt1,pt2;
		pLine->getFitPointAt(c,pt1);
		pLine->getFitPointAt(c+1,pt2);
		AcGeVector3d lineVec(pt2-pt1),clickVec(clickpt-pt1),
			clickVec2(pt2-clickpt);
		double ang=lineVec.angleTo(clickVec);
		
		// This is the filter...
		// .20 (20% of lineVec length) is an arbitrary length...
		if((sin(ang)*clickVec.length()<.2*lineVec.length()) && 
			clickVec.length()<lineVec.length() && 
			clickVec2.length()<lineVec.length()) 
		{
			// Add the fit-point
			ads_point outPt;
			AcGeVector3d norm(0,0,1);
			acdbWcs2Ecs(asDblArray(clickpt),outPt,asDblArray(norm),Adesk::kFalse);	
			pLine->insertFitPointAt(c+1,asPnt3d(outPt));
			break;
		}
	}
	
	pLine->close();

	acDocManager->unlockDocument(pDoc);

	// invoking acedSSSetFirst(NULL,NULL) here will clear the
	// pickfirst selection, if desired (not With spline though).
	//acedSSSetFirst(NULL,NULL);
	
	// Update the graphics...
	pLine->draw();
	actrTransactionManager->flushGraphics();
	acedUpdateDisplay();
}

void AcDbDoubleClickEditSpline::finishEdit()
{
	// No  need to implement for this example		
}
