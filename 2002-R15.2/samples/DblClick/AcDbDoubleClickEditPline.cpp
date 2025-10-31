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
// AcDbDoubleClickEditPline.cpp: implementation of the AcDbDoubleClickEditPline class.

#include "stdafx.h"
#include "resource.h"
#include "AcDbDoubleClickEditPline.h"
#include "AcDblClkEdit.h"
#include "acdocman.h"
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

AcDbDoubleClickEditPline::AcDbDoubleClickEditPline()
{

}

AcDbDoubleClickEditPline::~AcDbDoubleClickEditPline()
{

}

void AcDbDoubleClickEditPline::startEdit(AcDbEntity *pEnt, AcGePoint3d clickpt)
{
	// Implement the startEdit notification handler to catch when
	// a user double-clicks a 'POLYLINE' entity
	
	// Get the Current Document
	AcApDocument *pDoc=acDocManager->curDocument(); 
	AcDbPolyline *pLine;
		
	// Cast the AcDbEntity pointer to AcDbPolyline
	if(pEnt->isKindOf(AcDbPolyline::desc()) == Adesk::kTrue)
		pLine=AcDbPolyline::cast(pEnt);
	else
	{
		acutPrintf("Error: Invalid AcDbPolyline Object");
		return;
	}
	
	acDocManager->lockDocument(pDoc,AcAp::kWrite);
	
	// Upgrade to write
	if(pLine->upgradeOpen()!=Acad::eOk)
	{
		acutPrintf("Error: Could Not open AcDbPolyline Object");
		return;
	}
	
	// iterate through all the vertices to find which
	// segment was clicked on, and place a vertex there.
	for(unsigned int c=0;c<pLine->numVerts()-1;c++)
	{
		AcGePoint3d pt1,pt2;
		pLine->getPointAt(c,pt1);
		pLine->getPointAt(c+1,pt2);
		AcGeVector3d lineVec(pt2-pt1),clickVec(clickpt-pt1),
			clickVec2(pt2-clickpt);
		double ang=lineVec.angleTo(clickVec);
		
		// This is the filter...
		// .05 (5% of lineVec length) is an arbitrary length...
		if((sin(ang)*clickVec.length()<.05*lineVec.length()) && 
			clickVec.length()<lineVec.length() && 
			clickVec2.length()<lineVec.length()) 
		{
			// Add the point Here!
			ads_point outPt;
			acdbWcs2Ecs(asDblArray(clickpt),outPt,asDblArray(pLine->normal()),Adesk::kFalse);	
			pLine->addVertexAt(c+1,asPnt2d(outPt));
			break;
		}
	}
	
	pLine->close();

	acDocManager->unlockDocument(pDoc);
	
	// invoking acedSSSetFirst(NULL,NULL) here will clear the
	// pickfirst selection, if desired (not With pline though).
	//acedSSSetFirst(NULL,NULL);
	
	// Update the graphics...
	pLine->draw();
	actrTransactionManager->flushGraphics();
	acedUpdateDisplay();
}

void AcDbDoubleClickEditPline::finishEdit()
{
	// No  need to implement for this example
}
