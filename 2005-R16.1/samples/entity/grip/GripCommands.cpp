//
// (C) Copyright 1998-2003 by Autodesk, Inc. 
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



# include "GripCommands.h"
# include "AcCircle.h"
# include "AcLine.h"
# include "AcRect.h"
# include "AcCircleJig.h"
# include "dbxutil.h"
#include  "AcRectJig.h"
# define MAX_BUFFER_SIZE 133

AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg)
	{
	case AcRx::kInitAppMsg :
		acrxDynamicLinker->unlockApplication(pkt);
		initApp();
        acrxDynamicLinker->registerAppMDIAware(pkt);
		break;
	case AcRx::kUnloadAppMsg :
		unloadApp();

	}
	return AcRx::kRetOK;
}

void initApp(void)
{
	acedRegCmds->addCommand("GRIPSAMPLE",
							"CIRCLEGRIP",
							"CIRCLEGRIP",
							ACRX_CMD_MODAL,
							CircleGrip);
	
	acedRegCmds->addCommand("GRIPSAMPLE",
							"RECTJIG",
							"RECTJIG",
							ACRX_CMD_MODAL,RectangleGrip);
	AcCircle::rxInit();
	AcLine::rxInit();
	AcRectangle::rxInit();
}
void unloadApp(void)
{
	deleteAcRxClass(AcCircle::desc());
	deleteAcRxClass(AcLine::desc());
	deleteAcRxClass(AcRectangle::desc());
}

void CircleGrip(void)
{
	acutPrintf("Successfully loaded the custom grip sample for custom circle\n");
	Adesk::Boolean es(kFalse);

	AcCircle *pCircle = new AcCircle();
	AcCircleJig *pCicleJig = new AcCircleJig(acdbHostApplicationServices()->workingDatabase(),pCircle );

	AcDbObjectId stylentId = acdbGetDynDimStyleId();
	AcDbDimStyleTableRecord *pDimStyleTblRecord = NULL;

	es = acdbOpenObject(pDimStyleTblRecord,stylentId,AcDb::kForWrite);
	if(Acad::eOk != es)
		acutPrintf("Error in opening the AcDbDimStyleTable entity");
	AcCmColor cm;
	//cm.setColor( cm.blue() );
	//cm.setRGB(0,0,255);
	cm.setColorIndex(20);
	es =pDimStyleTblRecord->setDimclrt(cm);
	pDimStyleTblRecord->erase();
	pDimStyleTblRecord->close();	
	

	pCicleJig->dragIt();
	delete pCicleJig;
}

// ACRECT command main entry.
//
void RectangleGrip()
{
    AcRectangle *pRect = new AcRectangle();
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    AcRectJig jig(pDb, pRect);

    if (jig.acquireDefPoints() == Acad::eOk) {
        jig.prepRect();
        jig.dragIt();
    } else {
        delete pRect;
    }
}
