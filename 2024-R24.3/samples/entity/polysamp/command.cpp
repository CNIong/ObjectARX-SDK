//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// COMMAND.CC 
//
// DESCRIPTION:
//
// This file contains the command interface code for Arx sample app -
// POLYSAMP.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif



#pragma warning(push)
#pragma warning(disable:4265)//disable missing virtual destructor warning - atlcom.h
#include <afxdisp.h>        // MFC OLE automation classes
#include <atlbase.h>
CComModule _Module;
#include <atlcom.h>
#pragma warning(pop) // C4265


#include "rxmfcapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include "adslib.h"
#include "acestext.h"
#include "dbents.h"
#include "dbregion.h"
#include "dbsol3d.h"

#include "gepnt3d.h"

#include "poly.h"
#include "polyjig.h"
#include "util.h"
#include "dbxutil.h"
#include "dbapserv.h"

#include <comdef.h>
#include "acdocman.h"

#include "acadi.h"
#include "compoly/compoly_i.h"
#include "compoly/compoly_i.c"
#include "axpnt2d.h"
#include "initguid.h"
#include "axboiler.h"
#include "axpnt2d.h"
#include "axpnt3d.h"

#include "polycmd.h"


// static functions used in this file.

static Acad::ErrorStatus getEditOption(TCHAR* option, size_t nOption, Adesk::Boolean& interrupted);

static Acad::ErrorStatus    growPoly	(AsdkPoly* poly);
static Acad::ErrorStatus    shrinkPoly	(AsdkPoly* poly);
static Acad::ErrorStatus    setNumSidesPoly(AsdkPoly*, int newNumSides);
static Acad::ErrorStatus    setPersSubentIdSolver(AsdkPoly*, AsdkPoly::PersSubentIdSolver newSolver);
static Acad::ErrorStatus    morePoly	(AsdkPoly* poly);
static Acad::ErrorStatus    lessPoly	(AsdkPoly* poly);
static Acad::ErrorStatus    thickenPoly (AsdkPoly* poly, AcDbEntity*& ent, AcGePoint2d&  savedCenter,AcGePoint2d&   savedStartPoint,
int& savedNumSides,AcGeVector3d&  savedNormal,TCHAR*    savedName , size_t nSavedName, double& savedElevation);
static Acad::ErrorStatus    flattenPoly (AcDb3dSolid* solid, AcDbEntity*& ent, const AcGePoint2d&  savedCenter, const AcGePoint2d&   savedStartPoint,
int savedNumSides,const AcGeVector3d&  savedNormal,const TCHAR*    savedName, double savedElevation);
static Acad::ErrorStatus    namePoly	(AsdkPoly* poly);
static Acad::ErrorStatus    stylePoly	(AsdkPoly* poly);
static Acad::ErrorStatus    setPolyArea (AsdkPoly* poly, double area);
static Acad::ErrorStatus    replaceEntity(AcDbEntity*& thisOne, 
                                          AcDbEntity*  with);

// Also used in hilit.cc and transact.cc
//
Acad::ErrorStatus
getYOrN(TCHAR* promptStr, Adesk::Boolean defaultY, Adesk::Boolean& yes,Adesk::Boolean& interrupted);

// Used to set the AsdkPoly static variable mUseDragData for determining
// whether AsdkPoly will use the no-clone-for-dragging mechanism or not.
//
void setUseDragData()
{
    int val, status;
    for(;;) {
        acutPrintf(_T("\nNew value for USEDRAGDATA <%s>: "),
            AsdkPoly::useDragData() ? _T("1") : _T("0"));
        status = acedGetInt(NULL, &val);
        if (status != RTNORM)
            break;

        if (val != 0 && val != 1) {
            acutPrintf(_T("\nValue must be 0 or 1"));
            continue;
        }
        
        AsdkPoly::setUseDragData(val == 1 ? true : false);
        break;
    }
}

// Invoked by the command - DRAGPOLY
//
void 
dragPolyCommand()
{
    int nSides = 0;
    
    ads_point center, startPt, normal;
    
    if (acedGetPoint(NULL, _T("\nLocate center of polygon: "), center) != RTNORM)
        return;
    
    TCHAR nameBuf[133];
    if (acedGetString(Adesk::kTrue, _T("\nEnter polygon name: "), nameBuf) != RTNORM)
        return;
    
    AcDbObjectId tsId = 0;
    TCHAR styleBuf[133], msg[133];
	// Get default text style
	struct resbuf result ;
	if ( acedGetVar (_T("TEXTSTYLE"), &result) != RTNORM ) {
		acutPrintf(_T("\nError while reading default AutoCAD text style setting"));
		return ;
	}
	_tcscpy (styleBuf, result.resval.rstring) ;
    _stprintf (msg, _T("\nEnter text style <%ls>: "), result.resval.rstring) ;
	acdbFree (result.resval.rstring) ;

    if (acedGetString(Adesk::kTrue, msg, styleBuf) != RTNORM)
        return;
    
    if ( styleBuf[0] == _T('\0') ) {
		// Get default text style
		struct resbuf result2 ;
		if ( acedGetVar (_T("TEXTSTYLE"), &result2) != RTNORM ) {
			acutPrintf(_T("\nError while reading default AutoCAD text style setting"));
			return ;
		}
		_tcscpy (styleBuf, result2.resval.rstring) ;
		acdbFree (result2.resval.rstring) ;
	}

    if ( rx_getTextStyleId(styleBuf, 
                             acdbHostApplicationServices()->workingDatabase(), 
                             tsId) != Acad::eOk)
    {
        acutPrintf(_T("\nInvalid text style name"));
        return;
    }
    
    
    // Set the normal to the plane of the polygon to be the same as the
    // z direction of the current ucs, i.e. (0, 0, 1) since we also got the
    // center and start point in the current UCS. (acedGetPoint() returns in
    // the current UCS.)
    
    normal[X] = 0.0; normal[Y] = 0.0; normal[Z] = 1.0;

    acdbUcs2Wcs(normal, normal, Adesk::kTrue);
    acdbUcs2Ecs(center, center, normal, Adesk::kFalse);
    acdbUcs2Ecs(startPt, startPt, normal, Adesk::kFalse);
    double elev = center[2];
    AcGePoint2d cen = asPnt2d(center), start = asPnt2d(startPt);
    AcGeVector3d norm = asVec3d(normal);
    
    AsdkPolyJig* pJig = new AsdkPolyJig();
    pJig->acquire(cen, norm, nameBuf, tsId, elev);
    
    delete pJig;
}
// Invoked by the command - POLY
//
void 
polyCommand()
{
    int nSides = 0;
    
    while (nSides < 3) {
        
        acedInitGet(INP_NNEG, _T(""));
        switch (acedGetInt(_T("\nEnter number of sides: "), &nSides)) {
            
        case RTNORM:
            if (nSides < 3)
                acutPrintf(_T("\nNeed at least 3 sides."));
            break;
        default:
            return;
        }
    }
    
    ads_point center, startPt, normal;
    
    if (acedGetPoint(NULL, _T("\nLocate center of polygon: "), center) != RTNORM)
        return;
    
    startPt[0] = center[0]; startPt[1] = center[1]; startPt[2] = center[2];
    while (asPnt3d(startPt) == asPnt3d(center)) {
        switch (acedGetPoint(center, _T("\nLocate start point of polygon: "), 
            startPt)) {
        case RTNORM:
            if (asPnt3d(center) == asPnt3d(startPt))
                acutPrintf(_T("\nPick a point different from the center."));
            break;
        default:
            return;
        }
    }
    
    TCHAR nameBuf[133];
    if (acedGetString(Adesk::kTrue, _T("\nEnter polygon name: "), nameBuf) != RTNORM)
        return;
    
    AcDbObjectId tsId = 0;
    TCHAR styleBuf[133], msg[133];
	// Get default text style
	struct resbuf result ;
	if ( acedGetVar (_T("TEXTSTYLE"), &result) != RTNORM ) {
		acutPrintf(_T("\nError while reading default AutoCAD text style setting"));
		return ;
	}
	_tcscpy (styleBuf, result.resval.rstring) ;
    _stprintf (msg, _T("\nEnter text style <%ls>: "), result.resval.rstring) ;
	acdbFree (result.resval.rstring) ;

    if (acedGetString(Adesk::kTrue, _T("\nEnter text style: "), styleBuf) != RTNORM)
        return;
    
    if ( styleBuf[0] == _T('\0') ) {
		// Get default text style
		struct resbuf result2 ;
		if ( acedGetVar (_T("TEXTSTYLE"), &result2) != RTNORM ) {
			acutPrintf(_T("\nError while reading default AutoCAD text style setting"));
			return ;
		}
		_tcscpy (styleBuf, result2.resval.rstring) ;
		acdbFree (result2.resval.rstring) ;
	}

    if ( rx_getTextStyleId(styleBuf, 
                         acdbHostApplicationServices()->workingDatabase(), 
                         tsId) != Acad::eOk)
	{
		acutPrintf(_T("\nInvalid text style name"));
		return;
	}
    
    
    // Set the normal to the plane of the polygon to be the same as the
    // z direction of the current ucs, i.e. (0, 0, 1) since we also got the
    // center and start point in the current UCS. (acedGetPoint() returns in
    // the current UCS.)
    
    normal[X] = 0.0; normal[Y] = 0.0; normal[Z] = 1.0;

    acdbUcs2Wcs(normal, normal, Adesk::kTrue);    
    acdbUcs2Ecs(center, center,normal, Adesk::kFalse);
    acdbUcs2Ecs(startPt, startPt,normal, Adesk::kFalse);
    double elev = center[2];
    AcGePoint2d cen = asPnt2d(center), start = asPnt2d(startPt);
    AcGeVector3d norm = asVec3d(normal);
    
    AsdkPoly* poly = new AsdkPoly;
    if (poly==NULL){
        acutPrintf(_T("\nOut of memory."));
        return;
    }
    
    if (poly->set(cen, start, nSides, norm, nameBuf, tsId, elev)!=Acad::eOk){
        delete poly;
        acutPrintf(_T("\nCannot create AsdkPoly with given parameters."));
        return;
    }
    
    poly->setDatabaseDefaults(acdbHostApplicationServices()->workingDatabase());
    postToDb(poly);
}

void 
polyeditCommand()
{
	Adesk::Boolean interrupted = Adesk::kFalse;
	Adesk::Boolean	    done;
    Acad::ErrorStatus es = Acad::eOk;
    AcDbFullSubentPath nullSub;
	AcGePoint2d   savedCenter;
	AcGePoint2d   savedStartPoint;
	int	     savedNumSides = 0;
	AcGeVector3d  savedNormal;
    const size_t nSavedName = 133;
	TCHAR	     savedName[nSavedName];
    double savedElevation = 0.0;
    
    // Select an AsdkPoly entity.
    
    AsdkPoly	 *poly = NULL;
    AcDb3dSolid  *solid = NULL;
    AcDbObjectId  objId;
    
    ads_name	  ename;
    ads_point     ptres;

    AcDbEntity* ent = NULL;

	ads_name ss ;
	if ( acedSSGet (_T("_I"), NULL, NULL, NULL, ss) == RTNORM ) {
		Adesk::Int32 n ;
		acedSSLength (ss, &n) ;
		switch ( n ) {
			case 0:
				//----- Not possible, but ?
				break ;
			case 1:
				acedSSName (ss, 0, ename) ;
				acdbGetObjectId(objId, ename);
				if ( acdbOpenAcDbEntity(ent, objId, AcDb::kForRead) == Acad::eOk )
				{
				assert(ent != NULL);
				poly = AsdkPoly::cast(ent);
				if (poly == NULL) {
					acutPrintf(_T("\nNot a polygon."));
						ent->close();
					}
				}
				break ;
			default:
				//----- If more than one entity selected, fallback in standard selection mode
				break ;
		}
		acedSSFree (ss) ;
	}

	while ( poly == NULL ) {

        switch (acedEntSel(_T("\nSelect a poly: "), ename, ptres)) {
        
		case RTNORM:
			acdbGetObjectId(objId, ename);
			if ( acdbOpenAcDbEntity(ent, objId, AcDb::kForRead) == Acad::eOk )
			{
			assert(ent != NULL);
			poly = AsdkPoly::cast(ent);
			if (poly == NULL) {
				acutPrintf(_T("\nNot a polygon."));
					ent->close();
				continue;
			}
			}
			break;
        
		case RTNONE:
		case RTCAN:
			return;
		default:
			continue;
		}
		break;
	}

    // Now we have a polygon. Start editing it.
    const size_t nOption = 256;
    TCHAR option[nOption];
    
    done = Adesk::kFalse;
    interrupted = Adesk::kFalse;
    
    while (!done && !interrupted) {
        
		if ( getEditOption(option, nOption, interrupted) != Acad::eOk )
			continue;
        
        if (_tcscmp(option, L"NUmsides") == 0) 
        {
            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf(L"\nNot Applicable");
                continue;
            }
            const int oldNumSides = poly->numSides();
            int newNumSides = oldNumSides;

            acutPrintf(L"\nCurrent number of sides=%d\n", oldNumSides);

            acedInitGet(INP_NNEG, _T(""));
            switch (acedGetInt(L"\nEnter number of sides: ", &newNumSides)) 
            {
            case RTNORM:
                if (!(3 <= newNumSides && newNumSides <= AsdkPoly::kMaxNumSides))
                {
                    acutPrintf(L"\nNeed at least 3 sides and no more than %d sides.", AsdkPoly::kMaxNumSides);
                    continue;
                }
                break;
            case RTNONE:
                newNumSides = oldNumSides;
                break;
            default:
                interrupted = true;
                continue;
            }

            if (setNumSidesPoly(poly, newNumSides) != Acad::eOk)
                continue;
        }
        else if (_tcscmp(option, L"Perssubentidsolver") == 0) 
        {
            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf(L"\nNot Applicable");
                continue;
            }
            const AsdkPoly::PersSubentIdSolver oldSolver = poly->getPersSubentIdSolver();
            int newSolver = (int)oldSolver;

            acutPrintf(L"\nCurrent PersSubentIdSolver=%d\n", (int)oldSolver);

            acedInitGet(INP_NNEG, _T(""));
            switch (acedGetInt(L"\nEnter PersSubentIdSolver index: ", &newSolver))
            {
            case RTNORM:
                break;
            case RTNONE:
                newSolver = (int)oldSolver;
                break;
            default:
                interrupted = true;
                continue;
            }

            if (setPersSubentIdSolver(poly, (AsdkPoly::PersSubentIdSolver)newSolver) != Acad::eOk)
                continue;

        } else if (_tcscmp(option, _T("Grow")) == 0) {
             if (!ent->isKindOf(AsdkPoly::desc())) {
                 acutPrintf(_T("\nNot Applicable"));
                 continue;
             }
             if ( growPoly(poly) != Acad::eOk )
                 continue;

        } else if (_tcscmp(option, _T("Shrink")) == 0) {

             if (!ent->isKindOf(AsdkPoly::desc())) {
                 acutPrintf(_T("\nNot Applicable"));
                 continue;
             }
             if ( shrinkPoly(poly) != Acad::eOk )
                 continue;

        } else if (_tcscmp(option, _T("More")) == 0) {

            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf(_T("\nNot Applicable"));
                continue;
            }
            if ( morePoly(poly) != Acad::eOk )
                continue;

        } else if (_tcscmp(option, _T("Less")) == 0) {

            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf(_T("\nNot Applicable"));
                continue;
            }
            if ( lessPoly(poly) != Acad::eOk )
                continue;
            
        } else if (_tcscmp(option, _T("Thicken")) == 0) {
            
            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf(_T("\nNot Applicable"));
                continue;
            }
			// If thickenPoly fails, it may be due to ASM modeler being unavailable.
            if (thickenPoly(poly, ent, savedCenter,savedStartPoint, savedNumSides,savedNormal,savedName, nSavedName, savedElevation) != Acad::eOk)
			{
                acutPrintf(_T("\nUnable to perform Thicken operation."));
                continue;
            }
            
            solid = AcDb3dSolid::cast(ent);
            assert(solid != NULL);
            poly = NULL;
            
            
            solid->draw();
            
        } else if (_tcscmp(option, _T("Flatten")) == 0) {
            
            if (!ent->isKindOf(AcDb3dSolid::desc())) {
                acutPrintf(_T("\nNot Applicable"));
                continue;
            }
			if ( flattenPoly(solid,ent,savedCenter,savedStartPoint, savedNumSides,savedNormal,savedName,savedElevation) != Acad::eOk )
				continue;
            
            poly = AsdkPoly::cast(ent);
            assert(poly != NULL);
            solid = NULL;
            
        } else if (_tcscmp(option, _T("Name")) == 0) {
            
            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf(_T("\nNot Applicable"));
                continue;
            }
            if ((es = namePoly(poly)) != Acad::eOk) {
                acutPrintf(_T("\nError setting Poly's name. Error: %s"),
                    acadErrorStatusText(es));
                done = Adesk::kTrue;
                continue;
            }
            if ((es = stylePoly(poly)) != Acad::eOk) {
                acutPrintf(_T("\nError setting Poly's text style. Error: %s"),
                    acadErrorStatusText(es));
                done = Adesk::kTrue;
                continue;
            }
        } else if (_tcscmp(option, _T("EXit")) == 0) {
            done = Adesk::kTrue;
        } else {
            done = Adesk::kTrue;
        }
        
    }
    
    // Close the entity corresponding to the open for read right
    // after selection.
    ent->close();
}


static Acad::ErrorStatus
getEditOption(TCHAR* option, size_t nOption, Adesk::Boolean& interrupted)
{
    Acad::ErrorStatus es = Acad::eOk;
    int 	      as = RTNORM;

    acedInitGet(0, _T("NUmsides Grow Shrink More Less Thicken Flatten Name Perssubentidsolver EXit X"));

    as = acedGetKword(_T("\nEnter an option [NUmsides/Grow/Shrink/More/Less/Thicken/Flatten/Name/Perssubentidsolver/eXit]: "),
                        option, nOption);

    switch (as) {
    case RTNORM:
        if (_tcscmp(option, _T("X")) == 0) {
            _tcscpy_s(option, nOption,_T("EXit"));
        }
        break;
    default:
        interrupted = Adesk::kTrue;
        break;
    }
    
    return es;
}



// Increases the area of the polygon by one quarter of its original
// area. New area = 1.25 * old area

static Acad::ErrorStatus 
growPoly(AsdkPoly* poly)
{
    Acad::ErrorStatus es = Acad::eOk;
    
    double oldArea;
    if ((es = poly->getArea(oldArea)) != Acad::eOk) {
        return es;
    }
    
    double area = oldArea * 1.25;
    
    if ((es = setPolyArea(poly, area)) != Acad::eOk) {
        return es;
    }
    
    return es;
}


// Decrease the area of the polygon by twenty percent.
// New area = 0.8 * old area. That way "Grow" followed by a "Shrink"
// will bring the polygon back to its original size.

static Acad::ErrorStatus 
shrinkPoly(AsdkPoly* poly)
{
    Acad::ErrorStatus es = Acad::eOk;
    
    double oldArea;
    if ((es = poly->getArea(oldArea)) != Acad::eOk) {
        return es;
    }
    
    double area = oldArea * 0.8;
    
    if ((es = setPolyArea(poly, area)) != Acad::eOk) {
        return es;
    }
    
    return es;
}

static Acad::ErrorStatus setNumSidesPoly(AsdkPoly* pPoly, int newNumSides)
{
    Acad::ErrorStatus es = pPoly->upgradeOpen();
    if (es != Acad::eOk)
        return es;

    es = pPoly->setNumSides(newNumSides);

    pPoly->downgradeOpen();
    return es;
}

static Acad::ErrorStatus setPersSubentIdSolver(AsdkPoly* pPoly, AsdkPoly::PersSubentIdSolver newSolver)
{
    Acad::ErrorStatus es = pPoly->upgradeOpen();
    if (es != Acad::eOk)
        return es;

    pPoly->setPersSubentIdSolver(newSolver);

    pPoly->downgradeOpen();
    return Acad::eOk;
}

// Increases the number of sides of the polygon by one.

static Acad::ErrorStatus 
morePoly(AsdkPoly* poly)
{
    Acad::ErrorStatus es = Acad::eOk;
    
    int numSides = poly->numSides() + 1;
    
    if ((es = poly->upgradeOpen()) != Acad::eOk) {
        return es;
    }
    if ((es = poly->setNumSides(numSides)) != Acad::eOk) {
        poly->downgradeOpen();
        return es;
    }
    if ((es = poly->downgradeOpen()) != Acad::eOk) {
        return es;
    }
    
    return es;
}

// Decreases the number of sides of the polygon by one.

static Acad::ErrorStatus 
lessPoly(AsdkPoly* poly)
{
    Acad::ErrorStatus es = Acad::eOk;
    
    if (poly->numSides() == 3) {
        acutPrintf(_T("\nThat's it."));
        return es;
    }
    int numSides = poly->numSides()  - 1;
    
    if ((es = poly->upgradeOpen()) != Acad::eOk) {
        return es;
    }
    if ((es = poly->setNumSides(numSides)) != Acad::eOk) {
        poly->downgradeOpen();
        return es;
    }
    if ((es = poly->downgradeOpen()) != Acad::eOk) {
        return es;
    }
    
    return es;
}


// Extrudes the region to a height that is one-fourth the perimeter.

static Acad::ErrorStatus 
thickenPoly(AsdkPoly* poly,AcDbEntity*& ent, AcGePoint2d&  savedCenter,AcGePoint2d&   savedStartPoint,
int& savedNumSides,AcGeVector3d&  savedNormal,TCHAR*    savedName,size_t nSavedName,double& savedElevation)
{
    Acad::ErrorStatus es = Acad::eOk;
    int i;
    AcDbVoidPtrArray lines;
    AcDbVoidPtrArray regions;
    
    // Explode to a set of lines
    //
    if ((es = poly->explode(lines)) != Acad::eOk) {
        for (i = 0; i < lines.length(); i++) {
            delete (AcRxObject*)lines[i];
        }
        for (i = 0; i < regions.length(); i++) {
            delete (AcRxObject*)regions[i];
        }
        return es;
    }
    
    // Create a region from the set of lines.
    //
    if ((es = AcDbRegion::createFromCurves(lines, regions)) != Acad::eOk) {
        for (i = 0; i < lines.length(); i++) {
            delete (AcRxObject*)lines[i];
        }
        for (i = 0; i < regions.length(); i++) {
            delete (AcRxObject*)regions[i];
        }
        return es;
    }
    assert(regions.length() == 1);
    AcDbRegion* region = AcDbRegion::cast((AcRxObject*)regions[0]);
    assert(region != NULL);
    
    // Extrude the region to create a solid.
    //
    double height;
    if ((es = poly->getDistAtParam(6.28318530717958647692, height))
        != Acad::eOk)
    {
        for (i = 0; i < lines.length(); i++) {
            delete (AcRxObject*)lines[i];
        }
        for (i = 0; i < regions.length(); i++) {
            delete (AcRxObject*)regions[i];
        }
        return es;
    }
    height *= 0.25;
    
    AcDb3dSolid* solid = new AcDb3dSolid;
    assert(solid != NULL);
    if ((es = solid->extrude(region, height, 0.0)) != Acad::eOk) {
        delete solid;
        for (i = 0; i < lines.length(); i++) {
            delete (AcRxObject*)lines[i];
        }
        for (i = 0; i < regions.length(); i++) {
            delete (AcRxObject*)regions[i];
        }
        return es;
    }
    
    // Save up the data to flatten the solid.
    //
    savedCenter     = poly->center();
    savedStartPoint = poly->startPoint();
    savedNumSides   = poly->numSides();
    savedNormal     = poly->normal();
    savedElevation  = poly->elevation();
    // Copy the poly name
    //
    _tcscpy_s(savedName, nSavedName,poly->name());
    
    // Now we have a solid. Change the entity to be this solid
    
    if ((es = solid->setPropertiesFrom(poly)) != Acad::eOk) {
        delete solid;
        for (i = 0; i < lines.length(); i++) {
            delete (AcRxObject*)lines[i];
        }
        for (i = 0; i < regions.length(); i++) {
            delete (AcRxObject*)regions[i];
        }
        return es;
    }
    ent = poly;
    if ((es = ent->upgradeOpen()) != Acad::eOk) {
        delete solid;
        for (i = 0; i < lines.length(); i++) {
            delete (AcRxObject*)lines[i];
        }
        for (i = 0; i < regions.length(); i++) {
            delete (AcRxObject*)regions[i];
        }
        return es;
    }
    es = replaceEntity(ent, solid);
    if ((es != Acad::eOk) && (es != Acad::eObjectToBeDeleted)) {
        ent->downgradeOpen();
        delete solid; 
        for (i = 0; i < lines.length(); i++) {
            delete (AcRxObject*)lines[i];
        }
        for (i = 0; i < regions.length(); i++) {
            delete (AcRxObject*)regions[i];
        }
        return es;
    }
    es = ent->downgradeOpen();
    
    for (i = 0; i < lines.length(); i++) {
        delete (AcRxObject*)lines[i];
    }
    for (i = 0; i < regions.length(); i++) {
        delete (AcRxObject*)regions[i];
    }
    return es;
}


static Acad::ErrorStatus 
flattenPoly(AcDb3dSolid* solid,AcDbEntity*& ent,const AcGePoint2d& savedCenter, const AcGePoint2d& savedStartPoint,
int savedNumSides,const AcGeVector3d& savedNormal,const TCHAR* savedName, double savedElevation)
{
    Acad::ErrorStatus es = Acad::eOk;
    
    AsdkPoly* poly = new AsdkPoly;
    if (poly==NULL)
        return Acad::eOutOfMemory;

    if ((es=poly->set(savedCenter, savedStartPoint, savedNumSides, savedNormal, savedName, savedElevation))!=Acad::eOk){
        delete poly;
        return es;
    }
    
    // Change the entity to be the poly. 
    
    if ((es = poly->setPropertiesFrom(solid)) != Acad::eOk) {
        delete poly;
        return es;
    }
    ent = solid;
    if ((es = ent->upgradeOpen()) != Acad::eOk) {
        delete poly;
        return es;
    }
    es = replaceEntity(ent, poly);
    if((es != Acad::eOk) && (es != Acad::eObjectToBeDeleted)) {
        ent->downgradeOpen();
        delete poly; 
        return es;
    }
    if ((es = ent->downgradeOpen()) != Acad::eOk) {
        return es;
    }
    
    return es;
}


// Solicit a new name for the polygon

static Acad::ErrorStatus 
namePoly(AsdkPoly* poly)
{
    Acad::ErrorStatus es = Acad::eOk;
    
    TCHAR nameBuf[133];
    if (acedGetString(Adesk::kTrue, _T("\nEnter new name: "), nameBuf) == RTNORM) {
        if ((es = poly->upgradeOpen()) != Acad::eOk) {
            return es;
        }
        if ((es = poly->setName(nameBuf)) != Acad::eOk) {
            poly->downgradeOpen();
            return es;
        }
        
        return poly->downgradeOpen();
    } else
        return Acad::eInvalidInput;
}


// Solicit a new text style for the polygon

static Acad::ErrorStatus 
stylePoly(AsdkPoly* poly)
{
    Acad::ErrorStatus es = Acad::eOk;
    
    TCHAR nameBuf[133];
    int as;
    if ((as = acedGetString(Adesk::kTrue, _T("\nEnter new text style: "), 
        nameBuf)) == RTNORM) {
        // NULL string.
        if (_tcslen(nameBuf) == 0)
            return Acad::eOk;
        AcDbObjectId tsId;
        if ((es = rx_getTextStyleId(nameBuf, 
                acdbHostApplicationServices()->workingDatabase(), 
                tsId)) != Acad::eOk)
            return es;
        if ((es = poly->upgradeOpen()) != Acad::eOk) {
            return es;
        }
        if ((es = poly->setTextStyle(tsId)) != Acad::eOk) {
            poly->downgradeOpen();
            return es;
        }
        return poly->downgradeOpen();
    } else if (as == RTCAN)
        return Acad::eOk;
    else
        return Acad::eInvalidInput;
}


static Acad::ErrorStatus 
setPolyArea(AsdkPoly* poly, double area)
{
    Acad::ErrorStatus es = Acad::eOk;
    
    double theta = 3.14159265358979323846 * 0.5 - 3.14159265358979323846 / poly->numSides();
    double circumRadius = sqrt
        ((2.0 * area) / (poly->numSides() * sin(2.0 * theta)));
    
    if (circumRadius < 1.0e-10) {
        acutPrintf(_T("\nThat's it."));
        return Acad::eOk;
    }
    
    AcGeVector2d vec = poly->startPoint() - poly->center();
    vec.normalize();
    vec *= circumRadius;
    AcGePoint2d startPt = poly->center() + vec;
    
    if ((es = poly->upgradeOpen()) != Acad::eOk) {
        return es;
    }
    if ((es = poly->setStartPoint(startPt)) != Acad::eOk) {
        poly->downgradeOpen();
        return es;
    }
    if ((es = poly->downgradeOpen()) != Acad::eOk) {
        return es;
    }
    
    return es;
}


//  Replace "thisOne" with "with" in the database.  As currently written,
//  "thisOne" must be open for write on entry.  "with" is non-database-
//  resident, and on return, it is open for write (and is in the
//  database).  On success, "thisOne" is set equal with "with".
//
static Acad::ErrorStatus 
replaceEntity(AcDbEntity*& thisOne, AcDbEntity*  with)
{
    Acad::ErrorStatus es = thisOne->handOverTo(with);
    if (es == Acad::eObjectToBeDeleted) {
        delete thisOne;
        thisOne = with;
    }
    return es;
}


Acad::ErrorStatus
getYOrN(TCHAR* promptStr, Adesk::Boolean defaultY, Adesk::Boolean& yes,Adesk::Boolean& interrupted)
{
    TCHAR option[256];
    yes = Adesk::kTrue;
    
    acedInitGet(0, _T("Yes No"));
    int as = acedGetKword(promptStr, option);
    
    switch (as) {
    case RTNORM:
        if (_tcscmp(option, _T("Yes")) == 0)
            yes = Adesk::kTrue;
        else
            yes = Adesk::kFalse;
        break;
        
    case RTNONE:
        if (defaultY)
            yes = Adesk::kTrue;
        else
            yes = Adesk::kFalse;
        break;
        
    case RTCAN:
        interrupted = Adesk::kTrue;
        break;
    default:
        break;
    }
    
    return Acad::eOk;
}

// 
// Command which demonstrates creating an entity with the IAcadBaseObject2
// interface and interacting with OPM for input
//
class CPolyCommand
{
    int m_retval;
    bool m_bFail;
    bool m_bDone;
    DWORD m_dConnectionID;

    CComPtr<IUnknown> m_pUnkCmd;
    CComPtr<IComPolygon> m_pPoly;
    CComQIPtr<IAcadBaseObject2> m_pBaseObj;
    CComObject<CComPolyCmd>* m_pPolyCmd;
    CComPtr<IConnectionPoint> m_pConPt;

    AcDbDatabase* m_pDb;
    void fail() {
        m_bFail = m_bDone = true;
    }
public:

    CPolyCommand();
    ~CPolyCommand();

    HRESULT initialize();

    HRESULT appendToSpace();

    void setDefaults();
    //
    // all input acquired, or command was aborted
    bool done() { return m_bDone; }
    //
    // to indicate if all input passed validation
    bool success() { return !m_bFail; }
    // 
    // issue prompt, get input
    void getInput();
};
CPolyCommand::CPolyCommand()
{
    m_bFail = false;
    m_bDone = false;
}
HRESULT CPolyCommand::initialize()
{
    HRESULT hr = S_OK;

    try {
        // Get an instance of a wrapper for a non-db-resident polygon
        if (FAILED(hr = m_pPoly.CoCreateInstance(CLSID_ComPolygon))) {
            // most likely problem, be a little more descriptive here
            acutPrintf(_T("\nUnable to load ComPolygon"));
            throw hr;
        }

        // Get the base object - needed for those methods inherited by polygon
        m_pBaseObj = m_pPoly;
        m_pBaseObj->CreateObject();

        // Get an instance of a listner so we know when input has been
        // entered in OPM
        if (FAILED(hr = CComObject<CComPolyCmd>::CreateInstance(&m_pPolyCmd)))
            throw hr;

        m_pPolyCmd->SetDocument(curDoc());
        hr = m_pPolyCmd->QueryInterface(IID_IUnknown,(LPVOID *)&m_pUnkCmd);
        if (FAILED(hr))
            throw hr;

        // Attach the listener to the polygon wrapper
        CComQIPtr<IConnectionPointContainer> pPtContainer;
        pPtContainer = m_pPoly;
        hr = pPtContainer->FindConnectionPoint(
            IID_IPropertyNotifySink,&m_pConPt);
        if (FAILED(hr))
            throw hr;

        if (FAILED(hr = m_pConPt->Advise(m_pUnkCmd,&m_dConnectionID)))
            throw hr;

        acedSetIUnknownForCurrentCommand(m_pPoly);

        m_pDb = curDoc()->database();

        setDefaults();

    } catch (HRESULT) {
        fail();
    }
    return hr;
}
CPolyCommand::~CPolyCommand()
{
    // Detach listener
    if (m_pConPt) m_pConPt->Unadvise(m_dConnectionID);
}

// set any properties not determined by the command 
void CPolyCommand::setDefaults()
{
    double dElevation = m_pDb->elevation();
    m_pPoly->put_Elevation(dElevation);
}

// everything went ok, append entity to the database
HRESULT CPolyCommand::appendToSpace()
{
    AcDbObjectId obj(NULL);
    m_pBaseObj->AddToDb(obj,m_pDb->currentSpaceId(),_T("AsdkPoly"));

    return Acad::eOk;
}
// input may either return RTNORM (from command line) or RTMODELESS (from OPM)
// if it is RTMODELSS, the entity already has that value set.
// if it not RTMODELSS, we process as before, setting the value on m_pPoly
void CPolyCommand::getInput()
{
    ads_point tmpc;
    TCHAR tmpBuf[133];
    if (!m_pPolyCmd->GotNumSides()) {
        int nSides;
        acedInitGet(INP_NNEG, _T(""));
        if ((m_retval = acedGetInt(_T("\nEnter number of sides: "), &nSides))
            == RTNORM)
        {
            if (nSides < 3) {
                acutPrintf(_T("\nNeed at least 3 sides."));
                return;
            }
            m_pPoly->put_NumSides(nSides);
        }
    } else if (!m_pPolyCmd->GotCenter()) {
        if ((m_retval = acedGetPoint(NULL,
            _T("\nLocate center of polygon: "), tmpc)) == RTNORM)
        {
            AcAxPoint3d pt2d(tmpc[0],tmpc[1],0);
            m_pPoly->put_Center(*pt2d.asVariantPtr());
        }
    } else if (!m_pPolyCmd->GotStartPoint()) {
        AcAxPoint2d pt2dCtr(0.0,0.0);
        VARIANT *pVar = pt2dCtr.asVariantPtr();
        m_pPoly->get_Center(pVar);
        pt2dCtr = pVar;
        ads_point cp = { pt2dCtr.x, pt2dCtr.y };
        if ((m_retval = acedGetPoint(cp,
            _T("\nLocate start point of polygon: "), tmpc)) == RTNORM)
        {
            AcAxPoint3d pt3d(tmpc[0],tmpc[1],0);

            if (AcAxPoint3d (pt2dCtr.x, pt2dCtr.y,0) == pt3d) {
                acutPrintf(_T("\nPick a point different from the center."));
                return;
            }
            m_pPoly->put_StartPoint(*pt3d.asVariantPtr());
        }
    } else if (!m_pPolyCmd->GotTextString()) {
        if ((m_retval = acedGetString(Adesk::kTrue,
            _T("\nEnter polygon name: "),tmpBuf)) == RTNORM)
        {
            m_pPoly->put_TextString(_bstr_t(tmpBuf));
        }
    } else if (!m_pPolyCmd->GotTextStyleName()) {
        if ((m_retval = acedGetString(Adesk::kTrue,
            _T("\nEnter text style: "), tmpBuf)) == RTNORM)
        {
            AcDbObjectId tsId;
            if (tmpBuf[0] == _T('\0') ) {
                // Get default text style
                struct resbuf result ;
                if ( acedGetVar (_T("TEXTSTYLE"), &result) != RTNORM ) {
                    acutPrintf(
                _T("\nError while reading default AutoCAD text style setting"));
                    fail();
                    return;
                }
                _tcscpy (tmpBuf, result.resval.rstring) ;
                acdbFree (result.resval.rstring) ;
            }
            if ( rx_getTextStyleId(tmpBuf, 
                     acdbHostApplicationServices()->workingDatabase(), 
                     tsId) != Acad::eOk)
            {
                acutPrintf(_T("\nInvalid text style name"));
                fail();
                return;
            }
            m_pPoly->put_TextStyleName(_bstr_t(tmpBuf));
        }
    } else
        m_bDone = true;
    if (m_retval != RTNORM && m_retval != RTMODELESS)
        fail();
}
void 
polyCommand2()
{
    CPolyCommand polyCmd;
 
    polyCmd.initialize();

    while (!polyCmd.done())
        polyCmd.getInput();

    if (polyCmd.success())
        polyCmd.appendToSpace();
    return;
}
