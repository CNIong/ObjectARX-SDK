//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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

//Implements Grip Enhancement and Dynamic Dimensioning call back methods
# include "GripImp.h"
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "dbxutil.h"
#include "AcCircle.h"
#include "tchar.h"



///////////////////////////////////////////////////
/////////Grip Call back function Implementation ///
//////////////////////////////////////////////////

//Tool Tip
const TCHAR* 
GripCback::GripToolTipFunc(AcDbGripData* pThis)
{
	return static_cast<TSTDSTRING*>(pThis->appData())->c_str();

}
	

//Hot grip Call back function Implementation
AcDbGripOperations::ReturnValue
GripCback::hotGripfunc(AcDbGripData			*pthis,
					   const AcDbObjectId	&entId,
						int					 contextFlags)
{
	AcDbGripOperations::ReturnValue gripStat(AcDbGripOperations::eOk);

	TSTDSTRING *psApppData = static_cast<TSTDSTRING *>(pthis->appData());
		
	if(psApppData)
	{
		if(*psApppData == _T("First")){
		gripStat=AcDbGripOperations::eGripHotToWarm;
		}
	}
	
	else
	{
	gripStat=AcDbGripOperations::eOk;
	}
	
	return gripStat;
}

AcDbGripOperations::ReturnValue
GripCback::hoverGripfunc(AcDbGripData		*pthis,
					   const AcDbObjectId	&entId,
						int					 contextFlags)
{
	return AcDbGripOperations::eOk;
 
}

AcDbGripOperations::ReturnValue 
GripCback::Rtclkfunc(AcDbGripDataArray			&hotGrips,
					 const AcDbObjectIdArray	&ents, 
					 TCHAR						*&menuName,
					 HMENU						&menu,
					 ContextMenuItemIndexPtr	&cb)
{
	menu = ::CreatePopupMenu();
	if(menu){
		::AppendMenu(menu,MF_STRING,1,_T("Print Center Coordinate for the entity"));
		::AppendMenu(menu,MF_STRING,2,_T("Normal Coordinate for the entity"));
		cb = ContextMenuItemIndexfunc;
	}
	return AcDbGripOperations::eOk;
}

void 
GripCback::ContextMenuItemIndexfunc(unsigned int index)
{
	
	AcDbEntity *pEnt=NULL;
	Acad::ErrorStatus es =getCurrentEntity(pEnt);
	if(Acad::eOk != es)
		return;

	//AcGeMatrix3d ucsToWcsMat, wcsToUcsMat;
	//acdbUcsMatrix(ucsToWcsMat);
 //   wcsToUcsMat = ucsToWcsMat.inverse();
	//AcCircle *pCircle=NULL;
	//if( pEnt->isKindOf(AcCircle::desc()) != Adesk::kTrue )
	// return;
	//
	//pCircle =AcCircle::cast(pEnt);
	//AcGePoint3d cenPt   = pCircle->Center();
	//AcGeVector3d normal = pCircle->normal();
	//cenPt.transformBy(wcsToUcsMat);
	pEnt->close();

	switch(index)
	{
	case 1:
		//acutPrintf("\nCenter: X= %f, Y= %f, Z= %f", cenPt.x, cenPt.y, cenPt.z);
		acutPrintf(_T("\nDummy Print"));
		break;
	case 2:
		//acutPrintf("\nNormal: X= %f, Y= %f, Z= %f", normal[0], normal[1], normal[2]);
		acutPrintf(_T("\nDummy Print"));
		break;
	default:
		break;
	};
}


Acad::ErrorStatus 
getCurrentEntity(AcDbEntity *&pEntity)
{
		AcDbBlockTable *pBlockTable;
		Adesk::Boolean bRetVal(Adesk::kFalse);
		Acad::ErrorStatus es(Acad::eNotImplementedYet);
		AcDbBlockTableRecord *pBlockRec=NULL;

	es = acdbHostApplicationServices()->workingDatabase()->
							getBlockTable(pBlockTable,AcDb::kForRead);

    if (es != Acad::eOk) {
        ads_alert(_T("Failed to get block table!"));
		return Acad::eInvalidInput;
    }

    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockRec, AcDb::kForRead);
    if (es != Acad::eOk) {
        ads_alert(_T("Failed to get block table record!"));
        pBlockTable->close();
		return Acad::eInvalidInput;
    }
	AcDbBlockTableRecordIterator *pIter=NULL; 
	
	es= pBlockRec->newIterator(pIter);
	if( Acad::eOk != es)
		return Acad::eInvalidInput;
	es= pIter->getEntity(pEntity,AcDb::kForRead);

	pBlockRec->close();
	if(pIter)
		delete pIter;

	pBlockRec=NULL;
	pBlockTable=NULL;
	pIter=NULL;
	return es;	

}


/*void
populateGripStatusInfo(GripStatus   &gripOpStatus)
{
	gripOpStatus.insert(GripStatus_type(AcDbGripOperations::kGripStart,"GripStart"));
	gripOpStatus.insert(GripStatus_type(AcDbGripOperations::kGripEnd,"GripEnd"));
	gripOpStatus.insert(GripStatus_type(AcDbGripOperations::kGripAbort,"GripAbort"));
	gripOpStatus.insert(GripStatus_type(AcDbGripOperations::kStretch,"GripStretch"));
	gripOpStatus.insert(GripStatus_type(AcDbGripOperations::kMove,"GripMove"));
	gripOpStatus.insert(GripStatus_type(AcDbGripOperations::kRotate,"GripRotate"));
	gripOpStatus.insert(GripStatus_type(AcDbGripOperations::kScale,"GripScale"));
	gripOpStatus.insert(GripStatus_type(AcDbGripOperations::kMirror,"GripMirror"));
}
*/

void							    
GripCback::OpStatusfunc(AcDbGripData		 *pthis,
			const AcDbObjectId&				 entId,
			AcDbGripOperations::GripStatus	 stat)
{
	return;
}

bool 
GripCback::WorldDrawfunc(AcDbGripData		 *pThis,
			  AcGiWorldDraw					 *pWd,
			  const AcDbObjectId&			 entId, 
			  AcDbGripOperations::DrawType	 type, 
			  AcGePoint3d					 *cursor,
			  double						  dGripSize)
{
	static const Adesk::UInt16 kYellow =50;
	AcGePoint3d			point = pThis->gripPoint();
	AcGeVector3d		normal(0,0,1);

	pWd->subEntityTraits().setFillType(kAcGiFillAlways);
	pWd->subEntityTraits().setThickness(3);
	pWd->subEntityTraits().setColor(kYellow);
	pWd->geometry().circle(point,0.2,normal);
	return true;
}

void 
GripCback::GripViewportDrawfunc(AcDbGripData				 *pThis, 
								AcGiViewportDraw			 *pVd,
								const AcDbObjectId			 &entId, 
								AcDbGripOperations::DrawType type, 
								AcGePoint3d					 *cursor,
								int							 gripSize)
{
	double radius(0.2);
	AcGeVector3d normal(0,0,1);
	TSTDSTRING sAppData(static_cast<TCHAR *>(pThis->appData()));
	AcGePoint3d ep = pThis->gripPoint();
	//pWd->subEntityTraits().
	pVd->subEntityTraits().setColor(Colors::kYellow);
	pVd->geometry().circle(ep,radius, normal);

}

///////////////////////////////////////////////////
/////////Dynamic Dimensioning Call back function Implementation ///
//////////////////////////////////////////////////
void
DynDimCback::hotGripDimensionfunc(AcDbGripData *pGrip, 
					 const AcDbObjectId		   &objId,
					 AcDbDimDataPtrArray	   &dimDataArr)
{
	return;
}

void
DynDimCback::hoverGripDimensionfunc(AcDbGripData				*pGrip,
									const AcDbObjectId			&objId,
									AcDbDimDataPtrArray			&dimDataArr)
{
	return;
}


Adesk::Boolean addEntity(AcDbEntity *pEntity)
{
	AcDbBlockTable *pBlockTable;
	Adesk::Boolean bRetVal(Adesk::kFalse);
	

    Acad::ErrorStatus es = acdbHostApplicationServices()->workingDatabase()->
							getBlockTable(pBlockTable,AcDb::kForRead);

    if (es != Acad::eOk) {
        ads_alert(_T("Failed to get block table!"));
        return Adesk::kFalse;
    }

    AcDbBlockTableRecord *pBlockRec;
    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite);
    if (es != Acad::eOk) {
        ads_alert(_T("Failed to get block table record!"));
        pBlockTable->close();
		return Adesk::kFalse;
    }

    es = pBlockRec->appendAcDbEntity(pEntity);
	
    if (es != Acad::eOk)
	{
        ads_alert(_T("Failed to append entity!"));
		bRetVal = Adesk::kFalse;
	}
	else
		bRetVal = Adesk::kTrue;
	

	 pBlockTable->close();
     pBlockRec->close();
	 pEntity->close();
     return bRetVal;
}
