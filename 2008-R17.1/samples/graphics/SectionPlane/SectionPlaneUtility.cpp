// (C) Copyright 2006-2007 by Autodesk, Inc. 
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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "StdAfx.H"

#include ".\SectionPlaneUtility.h"

#define szRDS _RXST("ADSK")
#define KPI	3.14159265

CSectionPlaneUtility::CSectionPlaneUtility(void)
{
}
CSectionPlaneUtility::~CSectionPlaneUtility(void)
{
}

void CSectionPlaneUtility::IterSections()
{
	AcDbSectionManager * pSecMgr;
	AcDbDatabase * pDb = acdbHostApplicationServices()->workingDatabase();
	Acad::ErrorStatus es;

	//Get the section manager
	es = pDb->getSectionManager(pSecMgr, AcDb::kForRead);
	if(es != Acad::eOk)
	{
		acutPrintf(_T("\nUnable to get section manager")); 
		return;
	}

	//Iterate through the sections
	AcDbSectionManagerIterator * pItr;
	es = pSecMgr->newIterator(pItr);
	pSecMgr->close();
	if(es != Acad::eOk)
	{
		acutPrintf(_T("\nUnable to create section iterator")); 
		delete pItr;
		return;
	}
	for(pItr->start(); !pItr->done(); pItr->step())
	{
		AcDbSection * pSection;
		es = pItr->getSection(pSection,AcDb::kForRead);
		if(es != Acad::eOk)
		{
			acutPrintf(_T("\nUnable to get section in iterator")); 
			pSection->close();
			return;
		}
		GetSectionData(pSection);
		pSection->close();
	}

	delete pItr;
}


void CSectionPlaneUtility::GetSection()
{
	//Select a section and print out some data about it
	Acad::ErrorStatus es;
	ads_name name;
	ads_point pt;
	acedEntSel(_T("\nSelect Section"), name, pt);
	AcDbObjectId objId;
	acdbGetObjectId(objId, name);
	AcDbObject * pObj;
	es = acdbOpenObject(pObj ,objId, AcDb::kForRead);
	if(es != Acad::eOk)
	{
		acutPrintf(_T("\nUnable to open object")); 
		return;
	}

	AcDbSection * pSection;
	pSection = AcDbSection::cast(pObj);
	if(pSection == NULL)
	{
		delete pSection;
		acutPrintf(_T("\nSelected entity not a SECTIONOBJECT"));
		return;
	}
	GetSectionData(pSection);
	pSection->close();

	// Another example getting a section with a certain name
	// Get the section named TESTSECTION
	/*AcDbObjectId objId;
	es = pSecMgr->getSection(_T("TESTSECTION"), objId);
	if(es != Acad::eOk)
	{
	return;
	}

	AcDbSection * pSection2;
	AcDbObject * pObj;
	acdbOpenObject(pObj,objId,AcDb::kForRead);
	pSection2 = pSection2->cast(pObj);	
	GetSectionData(pSection2);	*/
}

void CSectionPlaneUtility::MoveOrRotateSection(int iMoveOrRotate, AcDbObjectId sectionId, AcGePoint3dArray sectVertices,ads_real * dist, ads_real * rotateAngle) 
{
	ads_real rotateAngleInRadians;

	if(iMoveOrRotate == 1)
	{   
		acedInitGet(RSG_OTHER, NULL);
		AcString promtForReal; // = AcString(_T("\nEnter distance to translate sectionplane: <%f>"), *dist);
		promtForReal.format(_T("\nEnter distance to translate sectionplane: <%f>"), *dist);
    	acedGetReal(promtForReal, &*dist);
		acutPrintf(_T("\nTranslating Section Plane"));
	}
	else if (iMoveOrRotate == 2)
	{
		acedInitGet(RSG_OTHER, NULL);
		AcString promtForAngle; 
		promtForAngle.format(_T("\nEnter angle to rotate sectionplane: <%f>"), *rotateAngle);
		acedGetReal(promtForAngle, &*rotateAngle);
		
		// Convert the angle to radians which is used below
		rotateAngleInRadians = *rotateAngle / (180 / KPI);
		acutPrintf(_T("\nRotating Sectionplane"));

	}
	
	AcDbSection * pSection;
	if(Acad::eOk != (acdbOpenObject(pSection, sectionId, AcDb::kForWrite)))
	{
		acutPrintf(_T("\nUnable to open section for write"));
		return;
	}
	
	
	AcGeVector3d secPlaneNormal = pSection->normal();
	AcGePlane secPlane;
	AcDb::Planarity flag;
	pSection->getPlane(secPlane, flag);

	AcGeMatrix3d wcsToEcsMat = AcGeMatrix3d::worldToPlane(secPlane);

	AcGeMatrix3d mat;
	AcGePoint3d origin;
	AcGeLineSeg3d lineSeg(sectVertices[0],sectVertices[1]);
	AcGeVector3d lineDirection = lineSeg.direction();
	AcGeVector3d zAxis = secPlaneNormal.crossProduct(lineDirection);

	mat.setCoordSystem(sectVertices[0],lineDirection, secPlaneNormal, zAxis);
	AcGeVector3d transVec; 
	if(iMoveOrRotate == 1)
	{
		//Move the section plane Forward or backward depending on value of dist
		transVec = AcGeVector3d(0,*dist,0);
		AcGeMatrix3d mat2;
		mat2.setToTranslation(transVec);
		mat = mat * transVec; 
		wcsToEcsMat = wcsToEcsMat * mat;
		pSection->transformBy(wcsToEcsMat);
	}
	else
	{
		// Rotate the section
		AcGePoint3d midPoint = lineSeg.midPoint();
		mat.setToRotation(rotateAngleInRadians, zAxis, midPoint);
		wcsToEcsMat = wcsToEcsMat * mat;
		pSection->transformBy(wcsToEcsMat);
	}
	pSection->close();
}

void CSectionPlaneUtility::Generate3dBlock(AcDbSection *pSection, AcDbObjectId solidId,AcString blkName, AcGePoint3d pntForBlkRefLocation, int iForLayerColor)

{
	Acad::ErrorStatus es;
	
	AcDbSectionSettings* pSettings;
	if(Acad::eOk != (pSection->getSettings(pSettings, AcDb::kForWrite)))
	{	
		acutPrintf(_T("\nUnable to get settings from section"));
		return;
	}
		
	// Show cut away section	
	pSettings->setVisibility(AcDbSectionSettings::kLiveSection, 
                                             AcDbSectionSettings::kForegroundGeometry, true);

	AcDbObjectIdArray entityIds, solidIds, blkRefIds, ids;
	AcDbSectionSettings::SectionType nSecType = AcDbSectionSettings::k3dSection;
    
	ids.append(solidId);
	
	es = pSettings->setSourceObjects(nSecType, ids);
	es = pSettings->getSourceObjects(nSecType, entityIds);
	int nLength = entityIds.length();
        AcDbObjectId id;
        for (int i = 0; i < nLength; i++)
		{
            AcDbEntity *pEnt = NULL;
            id = entityIds[i];
            es = acdbOpenObject(pEnt, id, AcDb::kForRead);
            if (es == eOk)
			{
                if (pEnt->isA() == AcDbBlockReference::desc())
                    blkRefIds.append(id);
                else if (pEnt->isKindOf(AcDb3dSolid::desc())
                        || pEnt->isKindOf(AcDbSurface::desc())
                        || pEnt->isKindOf(AcDbBody::desc())
                        || pEnt->isKindOf(AcDbRegion::desc()))
                    solidIds.append(id);
           
                pEnt->close();
            }
		}

		int nOptions = pSettings->generationOptions(AcDbSectionSettings::k3dSection);
		
		AcArray<AcDbEntity*> boundaryList, fillList, backgroundList, foregroundList, tangentList;
		AcDbEntity *pEnt = NULL;

		for (int i = 0; i < solidIds.length(); i++)
		{
			AcArray<AcDbEntity*> boundarySet, fillSet, backgroundSet;
			AcArray<AcDbEntity*> foregroundSet, tangentSet;
	        
			AcDbEntity *pEnt = NULL;
			es = acdbOpenObject(pEnt, solidIds[i], AcDb::kForRead);
			if (es == eOk)
			{
				es = pSection->generateSectionGeometry(pEnt,
								boundarySet, fillSet, backgroundSet, 
								foregroundSet, tangentSet);
				pEnt->close();

				boundaryList.append(boundarySet);
				fillList.append(fillSet);
				backgroundList.append(backgroundSet);
				foregroundList.append(foregroundSet);
				tangentList.append(tangentSet);
			}
		}
	
		pSection->close();
		pSettings->close();

		AcArray<AcDbEntity*> entList;
	    entList.append(boundaryList);
		entList.append(fillList);
        entList.append(backgroundList);
    	entList.append(foregroundList);
 		entList.append(tangentList);
		AcString sBlockName = "SECTION_BLOCK";
		
		AcDbDatabase * pDb = acdbHostApplicationServices()->workingDatabase();

		MakeSectionBlock(entList, pDb, blkName, true, pntForBlkRefLocation, iForLayerColor);

}
void CSectionPlaneUtility::GetSectionData(AcDbSection* pSection)
{
		Acad::ErrorStatus es;
		AcString sectionName;
		es =pSection->getName(sectionName);
		if(es != Acad::eOk)
		{
			acutPrintf(_T("\nUnable to get name of section"));
			return;
		}
		LPCTSTR secName = sectionName.kwszPtr();
 		acutPrintf(_T("\nSection name is: %s"), secName);

		AcDbSection::State secState;
		secState = pSection->state();
		switch(secState)
		{
		case AcDbSection::kPlane:
			acutPrintf(_T("\nSection State is Plane"));
			break;
		case AcDbSection::kBoundary:
			acutPrintf(_T("\nSection State is Boundary"));
			break;
		case AcDbSection::kVolume:
			acutPrintf(_T("\nSection State is Volume"));
		}

		AcGePoint3dArray pts;
		pSection->getVertices(pts);
		acutPrintf(_T("\nVertices for this section"));		
		for(int i=0; i<pts.length(); i++)
		{
			acutPrintf(_T("\nPoint %i is %f,%f,%f"),i,pts[i].x,pts[i].y,pts[i].z);
		}

		AcGeVector3d vertDirection;
		vertDirection = pSection->verticalDirection();
		acutPrintf(_T("\nVector is %f,%f,%f"),vertDirection.x,vertDirection.y,vertDirection.z);
		
		double dHeight;
		AcDbSection::Height nHeightType = AcDbSection::kHeightBelowSectionLine;
		
		dHeight = pSection->height(nHeightType);
		acutPrintf(_T("\nHeight below section pLine is %f"), dHeight);

	
		AcDbSectionSettings* pSettings;
		es = pSection->getSettings(pSettings, AcDb::kForWrite);
		if(es != Acad::eOk)
		{
			acutPrintf(_T("\nUnable to get sections settings"));
			delete pSettings;
			return;
		}
		AcDbSectionSettings::SectionType nSecType2 = pSettings->currentSectionType();

		switch(nSecType2)
		{
		case AcDbSectionSettings::kLiveSection:
			acutPrintf(_T("\nSectionSettings Type is kLiveSection"));
			break;
		case AcDbSectionSettings::k2dSection:
			acutPrintf(_T("\nSectionSettings Type is k2dSection"));
			break;
		case AcDbSectionSettings::k3dSection:
			acutPrintf(_T("\nSectionSettings Type is k3dSection"));
		}
		
		pSettings->close();
		pSection->close();

}

Acad::ErrorStatus CSectionPlaneUtility::createLayer (const TCHAR *layerName, AcDbObjectId &layerId, int iForLayerColor) {
	Acad::ErrorStatus es ;
	AcDbLayerTable *pTable ;

	layerId =AcDbObjectId::kNull ;
	if ( (es =acdbHostApplicationServices ()->workingDatabase ()->getLayerTable (pTable, AcDb::kForRead)) == Acad::eOk ) {
		// Use the overload of AcDbLayerTable::getAt() that returns the id
		if ( (es =pTable->getAt (layerName, layerId, Adesk::kFalse)) != Acad::eOk ) {
			// Create a new layer table record using the layer name passed in
			AcDbLayerTableRecord *pLTRec =new AcDbLayerTableRecord ;
			pLTRec->setName (layerName) ;
			
			AcCmColor col;
			
			col.setColorIndex(iForLayerColor); // set color to red
			pLTRec->setColor(col);
			// Set other properties - color, linetype, state - if desired
			// this will require more input than this simple example provides
			if ( (es =pTable->upgradeOpen ()) == Acad::eOk ) {
				es =pTable->add (layerId, pLTRec) ;
				// Since the new layer was successfully added to the database,
				// close it - DON'T delete it
				pLTRec->close () ;
			} else {
				// The object is not part of the database, therefore we should
				// delete it to avoid a memory leak
				delete pLTRec ;
			}
		}
		pTable->close () ;
	}
	return (es) ;
}

void CSectionPlaneUtility::MakeSectionBlock(AcArray<AcDbEntity*>& ents, 
                                            AcDbDatabase *pDb,
                                           	AcString sBlockName,
                                            bool bCreateBlkRef,
											AcGePoint3d pntForBlkRefLocation,
											int iForLayerColor)
{
    if (pDb == NULL || ents.length() <= 0)
        return; 

    AcDbBlockTable* pBlockTable = NULL;
    ErrorStatus es = pDb->getBlockTable(pBlockTable, kForWrite);
	if(es!= Acad::eOk) 
        return;
    
    AcDbBlockTableRecord* pBTR = new AcDbBlockTableRecord;
    if (pBTR == NULL)
	{
        pBlockTable->close();
        return;
    }
    //sBlockName = "SectionBlock";
    pBTR->setName(sBlockName);

    AcDb::UnitsValue insUnit = pDb->insunits();
    pBTR->setBlockInsertUnits(insUnit);

	AcDbObjectId btrId;
    es = pBlockTable->add(btrId, pBTR);
	if(es != Acad::eOk)
	{
		acutPrintf(_T("Unable to create block"));
		pBlockTable->close();
		delete pBTR;
		return;
	}
    pBlockTable->close();

    for (int ii = 0; ii < ents.length(); ii++) {
        AcDbEntity *pEnt = (AcDbEntity*)ents[ii];
        pEnt->upgradeOpen();
		AcDbObjectId layId = AcDbObjectId::kNull;
		es = createLayer(sBlockName,layId,iForLayerColor);
		
		pEnt->setLayer(layId);
		es = pBTR->appendAcDbEntity(pEnt);
        pEnt->close();
    }

    pBTR->close();
    if (bCreateBlkRef) {
        AcDbBlockReference* pBlockRef = new AcDbBlockReference();
        if (pBlockRef == NULL)
            return;

        es = pBlockRef->setBlockTableRecord(btrId);
      	pBlockRef->setPosition(pntForBlkRefLocation);
        pBlockRef->setColorIndex(256); // color by layer
		
		AcDbObjectId layId = AcDbObjectId::kNull;
		es = createLayer(sBlockName,layId,iForLayerColor);
		if(es!=Acad::eOk)
		{
			pBlockRef->close();
			return;
		}
		pBlockRef->setLayer(layId);

        // Add it to the current space 
        AcDbObjectId blkRefId; 

		AddEntityToDatabase(pBlockRef);
		pBlockRef->close();
    }
}
	AcDbObjectId CSectionPlaneUtility::AddEntityToDatabase(AcDbEntity *pEnt, ACHAR *spc, AcDbDatabase *pDb)
{
	// Adding entity in to the Database, by default it will add in to ModelSpace
	AcDbObjectId outObjId=AcDbObjectId::kNull;
	Acad::ErrorStatus es;
	if(NULL != spc && NULL != pEnt && NULL != pDb)
	{
		AcDbBlockTablePointer pBT(pDb->blockTableId(),AcDb::kForRead);

		if(Acad::eOk == pBT.openStatus())
		{
			AcDbObjectId recordId=AcDbObjectId::kNull;
			pBT->getAt(spc,recordId);
			AcDbBlockTableRecordPointer pBtr(recordId, AcDb::kForWrite);
			if(Acad::eOk == pBtr.openStatus())
			{
				es = pBtr->appendAcDbEntity(outObjId,pEnt);
				if(es != Acad::eOk)
				{
					acutPrintf(_T("\nUnable to append entity to block table record"));
					return outObjId;
				}
			}
		}
	}
	return outObjId;
}
  