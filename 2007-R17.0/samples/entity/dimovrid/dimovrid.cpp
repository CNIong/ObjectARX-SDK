// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
//  dimovrid.cpp
//
// This program demonstrates what is necessary to add and/or modify dimvar 
// overrides attached to dimensions, leaders, or feature control frames.
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "rxregsvc.h"
#include "aced.h"
#include "dbsymtb.h"
#include "adslib.h"
#include "dbents.h"
#include "dbfcf.h"
#include "dblead.h"
#include "dbapserv.h"
#include "tchar.h"




// This function allows the user to enter desired dim overides and apply
// them to a selected entity of the appropriate type
//
void
applyIt()
{
    int gc;
    int err = acedGetInt(_T("\nEnter dimvar group code: "), &gc);
    if (err != RTNORM) {
        acutPrintf(_T("\nerror in dimvar group code input"));
        return;
    }
    
    enum ValueType {kInteger = 1070, kString = 1000, kHandle = 1005, kReal = 1040};
    ValueType type = kInteger;
    int iVal = 1;
    ads_real rVal = 2.5;
    TCHAR *sVal = NULL;
	
	bool dimName = true;
	
	// GRP CODE 5-7 (string value) have been deprecated in favor of grp codes 342-344 (handle value)
	// For convenience, prompt for block name and translate it into a handle
	if (gc > 340 && gc < 345) 
		acutPrintf(_T("\nEnter name of block rather than its handle..."));	
	if (gc > 4 && gc < 8)
			gc += 337; 
	else 
		dimName = false;
	
	if ((gc > 70 && gc < 79) || (gc > 169 && gc < 179) || (gc > 270 && gc < 278)
        || (gc > 279 && gc < 289))
    {
        err = acedGetInt(_T("\nEnter dimvar integer value: "), &iVal);
        if ((err != RTNONE) && (err != RTNORM)) {
            acutPrintf(_T("\nerror in real value input"));
            return;
        }
	// else if it's a real, as the user for the dim override real value
	//
    } else if ((gc > 39 && gc < 49) || (gc > 139 && gc < 148)) {
        type = kReal;
        err = acedGetReal(_T("\nEnter dimvar real: "), &rVal);
        if ((err != RTNONE) && (err != RTNORM)) {
            acutPrintf(_T("\nerror in real value input"));
            return;
        }
	// else if it's a string, ask the user for the dim override string value for DIM*POST or a 
	//		leader or arrow block name for grp codes 342-345
    }	else if (dimName || gc == 3 || gc == 4)
	{
		type = kString;
		sVal = (TCHAR*) malloc(17 * sizeof(TCHAR)); //acedGetString accepts 132 chars max
		if (NULL == sVal) 
        {
            acutPrintf(_T("\nCould not allocate memory"));
            return;
        }
		
        err = acedGetString(NULL, _T("\nEnter dimvar string value: "), sVal);
        if (err != RTNORM) {
            acutPrintf(_T("\nerror in string value input"));
            return;
        }

		if 	(dimName) 
		{
			type = kHandle;
			//verify arrowhead/leader block actually exists in DB and if so, grab its handle
			AcDbBlockTable *pBlockTable;
			acdbHostApplicationServices()->workingDatabase()
				->getSymbolTable(pBlockTable, AcDb::kForRead);
			
			AcDbBlockTableRecord *pBlockTableRecord;
			Acad::ErrorStatus es = pBlockTable->getAt(sVal, pBlockTableRecord, AcDb::kForRead);
			pBlockTable->close();
			
			if (es == Acad::eOk)
			{
				AcDbHandle handle;	
				pBlockTableRecord->getAcDbHandle(handle);
				handle.getIntoAsciiBuffer(sVal);
				pBlockTableRecord->close();
			} else {
				//i.e. maybe Acad::eKeyNotFound
				acutPrintf(_T("\nCan't access block in database.  Aborting."));
				return;
			}	
		}
	}
    // If the desired dimvar is an integer type then ask the user for the integer
    // override value to use.
	//
    else {
		// some codes not handled by app
		//		enum illegalCodes = {0, 1, 2, 70, 270, 278, 340, 371, 372};

        acutPrintf(_T("\nGroup code not handled by app."));
        return;
    }

    ads_name en;
    ads_point pt;
    if (acedEntSel(_T("\nSelect Dimension, Geometric Tolerance, or Leader:  "), en, pt) != RTNORM) {
        acutPrintf(_T("Nothing Selected\n"));
        return;
    }
    AcDbObjectId EntId;
    acdbGetObjectId(EntId, en);
    AcDbEntity *pEnt;
    if (acdbOpenObject(pEnt, EntId, AcDb::kForWrite) != Acad::eOk) {
        acutPrintf(_T("\nError opening the entity"));
        free (sVal);
        return;
    }
    // Check to make sure the selected entity is a type that can use
    // dim overrides.  This is a weak check because a user may try to 
	// for example apply a DIMLDRBLK override to a dimension - in such 
	// a case the override appears in the xdata, but nothing changes.
    if (!pEnt->isKindOf(AcDbDimension::desc())
        && !pEnt->isKindOf(AcDbFcf::desc())
        && !pEnt->isKindOf(AcDbLeader::desc()))
    {
        acutPrintf(_T("\nThe selected entity is not a dimension, leader,")
            _T(" or Geometric Tolerance!"));
            pEnt->close();
            free (sVal);
            return;
    }

    // Dim overrides are stored within the "ACAD" appid xdata, so get
    // any existing Xdata under the "ACAD" appId
    //
    struct resbuf *pRb = pEnt->xData(_T("ACAD"));

    // If there is already Xdata for the "ACAD" appId,  then search
    // through it to see if there're any dim overrides.  If so,  then
    // check if the one we're working with is already there and if it
    // is change it to the new value.  If it's not, then add it. If
    // there're no dim overrides,  then append the whole dim override
    // section to the existing Xdata
    //
    Adesk::Boolean override = Adesk::kFalse;
    if (pRb != NULL) {
        struct resbuf *pOneBack;
        // Now to parse the "ACAD" Xdata
        //
        for (struct resbuf *pTemp = pRb; pTemp!= NULL ;
            pTemp = pTemp->rbnext)
        {
            // Dimoverrides are stored together with a leading string name
            // tag of "DSTYLE", so if this string is present in the "ACAD"
            // Xdata then there are already dim overrides present for the
            // entity.
            //
            // We also need to "skip past this resbuf structure.
            //
            if ((pTemp->restype == 1000) && !_tcscmp(pTemp->resval.rstring,
                _T("DSTYLE")))
            {
                override = Adesk::kTrue;
                pOneBack = pTemp;
                continue;
            }
            // the dimvar DXF group code and value are in two resbufs.  The
            // first has resbuf.restype == 1070 with the dimvar DXF group code
            // in resval.rint. The second has resbuf.restype == 1070, or 1040,
            // or 1000 depending on if it's an int, a real, or a string.  The
            // dimvar value is in resval.rint, or resval.rreal, or
            // resval.rstring depending on the data type.
            //
            // So,  if we have a resbuf with restype == 1070 and it has the
            // dimvar group code we want, then we know there's already a
            // dim override for that dimvar.
            //
            // If we've got a resbuf with restype == 1002 and it's the "}"
            // closing brace,  then we know that our dimvar isn't overriden
            // yet.
            //
            int notInThere;
            if (override &&
               (((pTemp->restype == 1070) && (pTemp->resval.rint == gc))
                || (notInThere = ((pTemp->restype == 1002) 
                && (pTemp->resval.rstring[0] == _T('}'))))))
            {
                if (notInThere) {
                    // not in there so add a new resbuf pair
                    //
                    struct resbuf *pTemp2 = acutNewRb(1070);
                    pTemp2->resval.rint = gc;
                    pTemp2->rbnext = acutNewRb(1070); // dummy restype for now

                    // this code will never be hit on the first loop pass so
                    // pOneBack will always be initialized before getting here
                    //
                    pOneBack->rbnext = pTemp2;
                    pTemp2->rbnext->rbnext = pTemp;
                    pTemp = pTemp2->rbnext;
                } else
                    pTemp = pTemp->rbnext;

                // now pTemp points to the appropriate resbuf (new or
                // existing) and we can set the value
                //
                if (type == kInteger) {
                    pTemp->restype = 1070;
                    pTemp->resval.rint = iVal;
                } else if (type == kReal) {
                    pTemp->restype = 1040;
                    pTemp->resval.rreal = rVal;
                } else if (type == kHandle) {
					pTemp->restype = 1005;
                    pTemp->resval.rstring = sVal;
                } else { //kHandle
					pTemp->restype = 1000;
                    pTemp->resval.rstring = sVal;
				}
                break;  // we're done with the loop so get out
            }
            // pOneBack is set here so that when the main loop code is
            // executing it's pointing to the resbuf before the one
            // pointed to by pTemp.
            //
            pOneBack = pTemp;
        }
    // if there is no Xdata on the entity,  then add the complete "ACAD"
    // Xdata sequence with the desired dim override
    //
    } else {
        if (type == kInteger)
            pRb = acutBuildList(1001, _T("ACAD"), 1000, _T("DSTYLE"), 1002, _T("{"),
            1070, gc, type, iVal, 1002, _T("}"), RTNONE);
        else if (type == kReal)
            pRb = acutBuildList(1001, _T("ACAD"), 1000, _T("DSTYLE"), 1002, _T("{"),
            1070, gc, type, rVal, 1002, _T("}"), RTNONE);
        else {  //kHandle
            pRb = acutBuildList(1001, _T("ACAD"), 1000, _T("DSTYLE"), 1002, _T("{"),
                1070, gc, type, sVal, 1002, _T("}"), RTNONE);
            // in this one case we need to free sVal because it was
            // copied by acutBuildList
            //
            free (sVal);  
        }
    }
    // set the new Xdata list back into the entity
    //
    pEnt->setXData(pRb);

    acutRelRb(pRb);
    pEnt->close();
}


void
initApp()
{
    acedRegCmds->addCommand(_T("ASDK_DIM_COMMANDS"),
        _T("ASDK_DIMOVER"), _T("DIM_OVER"),  ACRX_CMD_MODAL, applyIt);
}

void
unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_DIM_COMMANDS"));
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}

