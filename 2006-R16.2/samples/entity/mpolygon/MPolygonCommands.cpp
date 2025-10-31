//
// (C) Copyright 1996-2002 by Autodesk, Inc. 
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


#include "StdAfx.h"
#include "StdArx.h"
#include "dbapserv.h"
#include "dbMPolygon.h"
#include "dbents.h"
#include "dbpl.h"
#include "adscodes.h"
#include "axlock.h"

Acad::ErrorStatus 
postToDb(AcDbEntity* ent, AcDbObjectId& objId)
{
    AcDbBlockTable*        pBlockTable = NULL;
    AcDbBlockTableRecord*  pMSpaceRecord = NULL;

	AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
	AcAxDocLock doc (pDb);//locks the current document w/ normal lock type

	Acad::ErrorStatus es = doc.lockStatus();
	if (es == Acad::eOk) // if our lock was successful
	{
		if ((es = pDb->getSymbolTable(pBlockTable, AcDb::kForRead))!= Acad::eOk) 
			return es;
		if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, pMSpaceRecord, AcDb::kForWrite)) != Acad::eOk) 
		{
			pBlockTable->close();
			return es;
		}
		if ((es = pBlockTable->close()) != Acad::eOk) 
		{
			pMSpaceRecord->close();
			return es;
		}
		if ((es = pMSpaceRecord->appendAcDbEntity(objId, ent)) != Acad::eOk) 
		{
			pMSpaceRecord->close();
			return es;
		}
		if ((es = pMSpaceRecord->close()) != Acad::eOk) 
		{
			return es;
		}
	}
	//no need to close the entity here
	return es;
}

bool appendLoop(AcDbEntity* pEnt,AcDbMPolygon *pMPoly)
{
	AcDbPolyline *pPoly= NULL;
	AcDb2dPolyline *p2dPoly = NULL;
	AcDbCircle *pCircle = NULL;

	if ((pPoly = AcDbPolyline::cast (pEnt)) != NULL)
	{
		if (pMPoly->appendLoopFromBoundary(pPoly) != Acad::eOk) //if it is not a closed pline we get 'eInvalidInput'
		{
			acutPrintf ("appendLoopFromBoundary() has failed.\n");
			acutPrintf ("Please make sure you select a closed (polyline or circle) entity and run the command again.\n");
			return false;
		}
	}
	else if ((p2dPoly = AcDb2dPolyline::cast (pEnt)) != NULL)
	{
		if (pMPoly->appendLoopFromBoundary(p2dPoly) != Acad::eOk) //if it is not a closed pline we get 'eInvalidInput'
		{
			acutPrintf ("appendLoopFromBoundary() has failed.\n");
			acutPrintf ("Please make sure you select a closed (polyline or circle) entity and run the command again.\n");
			return false;
		}
	}else
	if ((pCircle = AcDbCircle::cast (pEnt)) != NULL)
	{
		if (pMPoly->appendLoopFromBoundary(pCircle) != Acad::eOk)
		{
			acutPrintf ("appendLoopFromBoundary() has failed.\n");
			return false;
		}
	}
	else
	{
		acutPrintf("MPOLY only works on AcDbCircle, AcDbPolyline or AcDb2dPolyline objects.\n");
		return false;
	}
	return true;
}

// free the resbufs
//
void freeResBufs(struct resbuf **rb)
{
	if (*rb != NULL)
	{
		acutRelRb(*rb);
		*rb = NULL;
	}
}

// Prompt the user to select the objects and filter the selection set for
// "CIRCLE","LWPOLYLINE","POLYLINE"
//
int filterObjects(/*out*/ads_name ss)
{
	int resVal;
	char *chName[]={"CIRCLE","LWPOLYLINE","POLYLINE"};
    struct resbuf * resBufEntityFilter  = NULL; struct resbuf **resBufTemp;
    resBufTemp = &resBufEntityFilter;
    *resBufTemp = acutBuildList(-4, "<OR", 0);
    resBufTemp = &(*resBufTemp)->rbnext;

	for (int nIndex = 0 ; nIndex<3;nIndex++)
	{
		*resBufTemp = acutBuildList(RTDXF0, chName[nIndex], 0);
        resBufTemp = &(*resBufTemp)->rbnext;
	}        
    *resBufTemp = acutBuildList(-4, "OR>", 0);
    resBufTemp = &(*resBufTemp)->rbnext;
	while(true)
	{
		resVal=acedSSGet(NULL,NULL,NULL,resBufEntityFilter,ss );
		if (resVal == RTCAN || resVal == RTERROR)
		{
			if (resVal == RTERROR)//when user selects zero objects
				acutPrintf ("\nZero objects were selected.\n");
			freeResBufs(&resBufEntityFilter);
			return resVal;
		}	
		else
			break;
	}
	freeResBufs(&resBufEntityFilter);
	return resVal;
}

//
// ObjectARX defined commands

// The 'MPOLY' command works for both simple and nested entities
//
void AsdkMPoly()
{
	Acad::ErrorStatus es;

	// Get the selected (filetered) objects.
	ads_name ss;
	acdbNameClear(ss);
	int nResult = filterObjects(ss);
	if (nResult == RTCAN || nResult == RTERROR)
	{
		// If user press 'Esc' or some other error (zero objects selected)
		return;
	}
	else
	{
		long lLength = -1;
		if (RTNORM != acedSSLength( ss, &lLength ) || (0 == lLength))
		{
			acedSSFree (ss);
			return;
		}
		else
		{
			ads_name entName;
			AcDbObjectId objId;
			AcDbEntity  *pEnt = NULL;
			AcDbMPolygon *pMPoly = new AcDbMPolygon();

			for (long lIndex =0; lIndex < lLength; lIndex++)
			{
				if (RTNORM != acedSSName( ss, lIndex, entName ))
					continue;
				// Get the AcDbObjectId for given entName
				es = acdbGetObjectId(objId, entName);
				es = acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead);
				if (es == Acad::eOk)
				{
					if (!appendLoop(pEnt,pMPoly))	// Inner loop		
					{
						pEnt->close();
						break;
					}
					pEnt->close();
				}
			}
			acedSSFree (ss);

			AcDbObjectId objId1;
			es = postToDb(pMPoly, objId1);
			if (es == Acad::eOk )
			{
				AcCmColor color;
				color.setColorIndex(10);

				es = pMPoly->setPatternAngle(45);
				es = pMPoly->setPatternDouble(true);
				es = pMPoly->setPatternScale(1.5);
				es = pMPoly->setPatternColor(color);
				es = pMPoly->setPatternSpace(1.5);
				es = pMPoly->setPattern(AcDbHatch::kPreDefined, "ANSI31");
				es = pMPoly->evaluateHatch();
				if (es != Acad::eOk)
				{
					//for example if we selected same entity as nested we get 
					//'eAmbiguousOutput' 
					acutPrintf ("evaluateHatch() has failed. Make sure you selected properly nested objects.\n");
					pMPoly->close();
					return;
				}
				es = pMPoly->balanceDisplay();
			
				if (!pMPoly->isBalanced())
					pMPoly->balanceTree();
				pMPoly->close();
			}
		}
	}
}

// The 'MPOLYADD' command adds "CIRCLE", "LWPOLYLINE" or "POLYLINE" objects to an existing MPolygon
//
void AsdkMPAddLoop()
{
    Acad::ErrorStatus es;
	ads_name entName;
	ads_point pt;

	AcDbObjectId objId;
	AcDbEntity *pEnt = NULL;
	AcDbMPolygon *pMPoly = NULL;

	while (true)
	{
		int nRet = acedEntSel ("Select MPolygon: \n", entName, pt);
		if (nRet == RTCAN || nRet == RTERROR)
		{
			return;
		}
		// Get the AcDbObjectId for given entName and open the entity
		es = acdbGetObjectId(objId, entName);
		es = acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead);
		if (es == Acad::eOk)
		{
			if (pEnt->isKindOf(AcDbMPolygon::desc()))	
			{
				pEnt->close();	// Close for the moment - will re-open for write later (from objId).
				break;
			}
			else
			{
				acutPrintf ("\nObject selected is not an MPolygon.\n");
				pEnt->close();
			}
		}
	}//while

	ads_name addSS;
	acdbNameClear(addSS);
	int nResult = filterObjects(addSS);
	if (nResult == RTCAN || nResult == RTERROR)
	{
		// If user press 'Esc' or some other error (zero objects selected)
		acedSSFree (addSS);
		return;
	}
	else
	{
		long lLength = -1;
		if (RTNORM != acedSSLength( addSS, &lLength ) || (0 == lLength))
		{
			acedSSFree (addSS);
			return;
		}
		else
		{
			// Re-open the MPoly object for write, now that the selection is over
			es = acdbOpenAcDbEntity(pEnt, objId, AcDb::kForWrite);
			if (es == Acad::eOk)
			{
				if ((pMPoly = AcDbMPolygon::cast(pEnt)) != NULL)
				{
					// Now step through the selected loops and add them in
					ads_name addEntName;
					AcDbObjectId addObjId;
					AcDbEntity *pAddEnt = NULL;

					for (long lIndex =0; lIndex < lLength; lIndex++)
					{
						if (RTNORM != acedSSName(addSS, lIndex, addEntName))
							continue;

						// Get the AcDbObjectId for the given addEntName and open the entity
						es = acdbGetObjectId(addObjId, addEntName);
						es = acdbOpenAcDbEntity(pAddEnt, addObjId, AcDb::kForRead);
						if (es == Acad::eOk)
						{
							if (!appendLoop(pAddEnt,pMPoly))	// Inner loop		
							{
								pAddEnt->close();
								break;
							}
							pAddEnt->close();
						}
					}
					es = pMPoly->balanceTree();
				}
				pEnt->close();
			}
		}
		acedSSFree (addSS);
	}
	return;
	
}