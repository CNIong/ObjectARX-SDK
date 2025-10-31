// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// COMMAND.CC 
//
// DESCRIPTION:
//
// This file contains the command interface code for Arx sample app -
// POLYSAMP.


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


// static functions used in this file.

static Acad::ErrorStatus getEditOption(char* option,Adesk::Boolean& interrupted);

static Acad::ErrorStatus    growPoly	(AsdkPoly* poly);
static Acad::ErrorStatus    shrinkPoly	(AsdkPoly* poly);
static Acad::ErrorStatus    morePoly	(AsdkPoly* poly);
static Acad::ErrorStatus    lessPoly	(AsdkPoly* poly);
static Acad::ErrorStatus    thickenPoly (AsdkPoly* poly, AcDbEntity*& ent, AcGePoint2d&  savedCenter,AcGePoint2d&   savedStartPoint,
int& savedNumSides,AcGeVector3d&  savedNormal,char*    savedName , double& savedElevation);
static Acad::ErrorStatus    flattenPoly (AcDb3dSolid* solid, AcDbEntity*& ent, const AcGePoint2d&  savedCenter, const AcGePoint2d&   savedStartPoint,
int savedNumSides,const AcGeVector3d&  savedNormal,const char*    savedName, double savedElevation);
static Acad::ErrorStatus    namePoly	(AsdkPoly* poly);
static Acad::ErrorStatus    stylePoly	(AsdkPoly* poly);
static Acad::ErrorStatus    setPolyArea (AsdkPoly* poly, double area);
static Acad::ErrorStatus    replaceEntity(AcDbEntity*& thisOne, 
                                          AcDbEntity*  with);

// Also used in hilit.cc and transact.cc
//
Acad::ErrorStatus
getYOrN(char* promptStr, Adesk::Boolean defaultY, Adesk::Boolean& yes,Adesk::Boolean& interrupted);

// Used to set the AsdkPoly static variable mUseDragData for determining
// whether AsdkPoly will use the no-clone-for-dragging mechanism or not.
//
void setUseDragData()
{
    int val, status;
    for(;;) {
        acutPrintf("\nNew value for USEDRAGDATA <%s>: ",
            AsdkPoly::useDragData() ? "1" : "0");
        status = acedGetInt(NULL, &val);
        if (status != RTNORM)
            break;

        if (val != 0 && val != 1) {
            acutPrintf("\nValue must be 0 or 1");
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
    
    if (acedGetPoint(NULL, "\nLocate center of polygon: ", center) != RTNORM)
        return;
    
    char nameBuf[133];
    if (acedGetString(Adesk::kTrue, "\nEnter polygon name: ", nameBuf) != RTNORM)
        return;
    
    AcDbObjectId tsId = 0;
    char styleBuf[133], msg[133];
	// Get default text style
	struct resbuf result ;
	if ( acedGetVar ("TEXTSTYLE", &result) != RTNORM ) {
		acutPrintf("\nError while reading default AutoCAD text style setting");
		return ;
	}
	strcpy (styleBuf, result.resval.rstring) ;
	sprintf (msg, "\nEnter text style <%s>: ", result.resval.rstring) ;
	acdbFree (result.resval.rstring) ;

    if (acedGetString(Adesk::kTrue, msg, styleBuf) != RTNORM)
        return;
    
    if ( styleBuf[0] == '\0' ) {
		// Get default text style
		struct resbuf result ;
		if ( acedGetVar ("TEXTSTYLE", &result) != RTNORM ) {
			acutPrintf("\nError while reading default AutoCAD text style setting");
			return ;
		}
		strcpy (styleBuf, result.resval.rstring) ;
		acdbFree (result.resval.rstring) ;
	}

    if ( rx_getTextStyleId(styleBuf, 
                             acdbHostApplicationServices()->workingDatabase(), 
                             tsId) != Acad::eOk)
    {
        acutPrintf("\nInvalid text style name");
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
        
        acedInitGet(INP_NNEG, "");
        switch (acedGetInt("\nEnter number of sides: ", &nSides)) {
            
        case RTNORM:
            if (nSides < 3)
                acutPrintf("\nNeed at least 3 sides.");
            break;
        default:
            return;
        }
    }
    
    ads_point center, startPt, normal;
    
    if (acedGetPoint(NULL, "\nLocate center of polygon: ", center) != RTNORM)
        return;
    
    startPt[0] = center[0]; startPt[1] = center[1]; startPt[2] = center[2];
    while (asPnt3d(startPt) == asPnt3d(center)) {
        switch (acedGetPoint(center, "\nLocate start point of polygon: ", 
            startPt)) {
        case RTNORM:
            if (asPnt3d(center) == asPnt3d(startPt))
                acutPrintf("\nPick a point different from the center.");
            break;
        default:
            return;
        }
    }
    
    char nameBuf[133];
    if (acedGetString(Adesk::kTrue, "\nEnter polygon name: ", nameBuf) != RTNORM)
        return;
    
    AcDbObjectId tsId = 0;
    char styleBuf[133], msg[133];
	// Get default text style
	struct resbuf result ;
	if ( acedGetVar ("TEXTSTYLE", &result) != RTNORM ) {
		acutPrintf("\nError while reading default AutoCAD text style setting");
		return ;
	}
	strcpy (styleBuf, result.resval.rstring) ;
	sprintf (msg, "\nEnter text style <%s>: ", result.resval.rstring) ;
	acdbFree (result.resval.rstring) ;

    if (acedGetString(Adesk::kTrue, "\nEnter text style: ", styleBuf) != RTNORM)
        return;
    
    if ( styleBuf[0] == '\0' ) {
		// Get default text style
		struct resbuf result ;
		if ( acedGetVar ("TEXTSTYLE", &result) != RTNORM ) {
			acutPrintf("\nError while reading default AutoCAD text style setting");
			return ;
		}
		strcpy (styleBuf, result.resval.rstring) ;
		acdbFree (result.resval.rstring) ;
	}

    if ( rx_getTextStyleId(styleBuf, 
                         acdbHostApplicationServices()->workingDatabase(), 
                         tsId) != Acad::eOk)
	{
		acutPrintf("\nInvalid text style name");
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
        acutPrintf("\nOut of memory.");
        return;
    }
    
    if (poly->set(cen, start, nSides, norm, nameBuf, tsId, elev)!=Acad::eOk){
        delete poly;
        acutPrintf("\nCannot create AsdkPoly with given parameters.");
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
	int	     savedNumSides;
	AcGeVector3d  savedNormal;
	char	     savedName[133];
    double savedElevation;
    
    // Select an AsdkPoly entity.
    
    AsdkPoly	 *poly = NULL;
    AcDb3dSolid  *solid = NULL;
    AcDbObjectId  objId;
    
    ads_name	  ename;
    ads_point     ptres;

    AcDbEntity* ent;

	ads_name ss ;
	if ( acedSSGet ("_I", NULL, NULL, NULL, ss) == RTNORM ) {
		long n ;
		acedSSLength (ss, &n) ;
		switch ( n ) {
			case 0:
				//----- Not possible, but ?
				break ;
			case 1:
				acedSSName (ss, 0, ename) ;

				AOK(acdbGetObjectId(objId, ename));
        
				AOK(acdbOpenAcDbEntity(ent, objId, AcDb::kForRead));
				assert(ent != NULL);
        
				poly = AsdkPoly::cast(ent);
				if (poly == NULL) {
					acutPrintf("\nNot a polygon.");
					AOK(ent->close());
				}
				break ;
			default:
				//----- If more than one entity selected, fallback in standard selection mode
				break ;
		}
		acedSSFree (ss) ;
	}

	while ( poly == NULL ) {

		switch (acedEntSel("\nSelect a poly: ", ename, ptres)) {
        
		case RTNORM:
        
			AOK(acdbGetObjectId(objId, ename));
        
			AOK(acdbOpenAcDbEntity(ent, objId, AcDb::kForRead));
			assert(ent != NULL);
        
			poly = AsdkPoly::cast(ent);
			if (poly == NULL) {
				acutPrintf("\nNot a polygon.");
				AOK(ent->close());
				continue;
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
    
    char option[256];
    
    done = Adesk::kFalse;
    interrupted = Adesk::kFalse;
    
    while (!done && !interrupted) {
        
        AOK(getEditOption(option,interrupted));
        
        if (strcmp(option, "Grow") == 0) {
            
            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf("\nNot Applicable");
                continue;
            }
            AOK(growPoly(poly));
            
        } else if (strcmp(option, "Shrink") == 0) {
            
            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf("\nNot Applicable");
                continue;
            }
            AOK(shrinkPoly(poly));
            
        } else if (strcmp(option, "More") == 0) {
            
            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf("\nNot Applicable");
                continue;
            }
            AOK(morePoly(poly));
            
        } else if (strcmp(option, "Less") == 0) {
            
            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf("\nNot Applicable");
                continue;
            }
            AOK(lessPoly(poly));
            
        } else if (strcmp(option, "Thicken") == 0) {
            
            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf("\nNot Applicable");
                continue;
            }
            AOK(thickenPoly(poly, ent, savedCenter,savedStartPoint, savedNumSides,savedNormal,savedName,savedElevation));
            
            solid = AcDb3dSolid::cast(ent);
            assert(solid != NULL);
            poly = NULL;
            
            
            solid->draw();
            
        } else if (strcmp(option, "Flatten") == 0) {
            
            if (!ent->isKindOf(AcDb3dSolid::desc())) {
                acutPrintf("\nNot Applicable");
                continue;
            }
            AOK(flattenPoly(solid,ent,savedCenter,savedStartPoint, savedNumSides,savedNormal,savedName,savedElevation));
            
            poly = AsdkPoly::cast(ent);
            assert(poly != NULL);
            solid = NULL;
            
            
        } else if (strcmp(option, "Name") == 0) {
            
            if (!ent->isKindOf(AsdkPoly::desc())) {
                acutPrintf("\nNot Applicable");
                continue;
            }
            Acad::ErrorStatus es;
            if ((es = namePoly(poly)) != Acad::eOk) {
                acutPrintf("\nError setting Poly's name. Error: %s",
                    acadErrorStatusText(es));
                done = Adesk::kTrue;
                continue;
            }
            if ((es = stylePoly(poly)) != Acad::eOk) {
                acutPrintf("\nError setting Poly's text style. Error: %s",
                    acadErrorStatusText(es));
                done = Adesk::kTrue;
                continue;
            }
        } else if (strcmp(option, "EXit") == 0) {
            done = Adesk::kTrue;
        } else {
            done = Adesk::kTrue;
        }
        
    }
    
    // Close the entity corresponding to the open for read right
    // after selection.
    
    AOK(ent->close());
}


static Acad::ErrorStatus
getEditOption(char* option, Adesk::Boolean& interrupted)
{
    Acad::ErrorStatus es = Acad::eOk;
    int 	      as = RTNORM;

    acedInitGet(0, "Grow Shrink More Less Thicken Flatten Name EXit X");

    as = acedGetKword("\nEnter an option [Grow/Shrink/More/Less/Thicken/Flatten/Name/eXit]: ", option);

    switch (as) {
    case RTNORM:
        if (strcmp(option, "X") == 0) {
            strcpy(option, "EXit");
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
        acutPrintf("\nThat's it.");
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
int& savedNumSides,AcGeVector3d&  savedNormal,char*    savedName, double& savedElevation)
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
    strcpy(savedName, poly->name());
    
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
int savedNumSides,const AcGeVector3d& savedNormal,const char* savedName, double savedElevation)
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
    
    char nameBuf[133];
    if (acedGetString(Adesk::kTrue, "\nEnter new name: ", nameBuf) == RTNORM) {
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
    
    char nameBuf[133];
    int as;
    if ((as = acedGetString(Adesk::kTrue, "\nEnter new text style: ", 
        nameBuf)) == RTNORM) {
        // NULL string.
        if (strlen(nameBuf) == 0)
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
        acutPrintf("\nThat's it.");
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
getYOrN(char* promptStr, Adesk::Boolean defaultY, Adesk::Boolean& yes,Adesk::Boolean& interrupted)
{
    char option[256];
    yes = Adesk::kTrue;
    
    acedInitGet(0, "Yes No");
    int as = acedGetKword(promptStr, option);
    
    switch (as) {
    case RTNORM:
        if (strcmp(option, "Yes") == 0)
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
