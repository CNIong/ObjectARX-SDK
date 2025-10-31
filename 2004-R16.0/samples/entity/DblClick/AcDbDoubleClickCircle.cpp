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
// AcDbDoubleClickCircle.cpp: implementation of the AcDbDoubleClickCircle class.

#include "stdafx.h"
#include "resource.h"
#include "AcDbDoubleClickCircle.h"
#include "dbents.h"
#include "aced.h"
#include "acdocman.h"
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

AcDbDoubleClickCircle::AcDbDoubleClickCircle()
{

}

AcDbDoubleClickCircle::~AcDbDoubleClickCircle()
{

}

extern Adesk::Boolean acedPostCommand(const char *);


void AcDbDoubleClickCircle::startEdit(AcDbEntity *pEnt, AcGePoint3d pt)
{
	// Implement the startEdit notification handler to catch when
	// a user double-clicks a 'CIRCLE' entity
	
	// Get the Current Document
	AcApDocument *pDoc=acDocManager->curDocument();
	AcDbCircle *pCircle;
		
	// Cast the AcDbEntity pointer to AcDbPolyline	
	if(pEnt->isKindOf(AcDbCircle::desc()) == Adesk::kTrue)
		pCircle=AcDbCircle::cast(pEnt);
	else
	{
		acutPrintf("Error: Invalid AcDbCircle Object");
		return;
	}
	
	acDocManager->lockDocument(pDoc,AcAp::kWrite);
	
	// Upgrade to write
	if(pCircle->upgradeOpen()!=Acad::eOk)
	{
		acutPrintf("Error: Could Not open AcDbCircle Object");
		return;
	}
	
	// Get the current Color
	Adesk::UInt16 color=pCircle->colorIndex();
	// Modify the color
	if(pCircle->setColorIndex((color+1)%10)!=Acad::eOk)
	{
		acutPrintf("Error: Could Not Modify AcDbCircle Object");
		return;
	}
	
	pCircle->close();

	acDocManager->unlockDocument(pDoc);
	
	// clear the pickfirst selection set.
	acedSSSetFirst(NULL,NULL);
	
	// Update the graphics...
	pCircle->draw();
	actrTransactionManager->flushGraphics();
	acedUpdateDisplay();
}

void AcDbDoubleClickCircle::finishEdit()
{
	// No  need to implement for this example	
}
