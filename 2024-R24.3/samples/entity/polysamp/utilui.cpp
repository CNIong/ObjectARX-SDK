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
// UTILUI.CPP 
//
// DESCRIPTION:
//
// This file contains utility routines needed for implementing 
// rx sample app - POLY.


#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "assert.h"
#include "math.h"
#include "adslib.h"

#include "gepnt3d.h"
#include "gearc2d.h"
#include "gearc3d.h"

#include "dbspline.h"
#include "dbents.h"
#include "dbsymtb.h"

#include "poly.h"
#include "util.h"

#include "dbapserv.h"




// Given the name of a text style, look up that name and
// return the db id of the TextStyleTableRecord.
//
Acad::ErrorStatus 
rx_getTextStyleId(const TCHAR         *styleName,
                        AcDbDatabase *db,
                        AcDbObjectId &styleId)
{
    AcDbTextStyleTable *pStyleTable;
    Acad::ErrorStatus es = db->getSymbolTable(
                              pStyleTable, AcDb::kForRead);
    if (es == Acad::eOk) {
        es = pStyleTable->getAt(styleName, styleId, Adesk::kFalse);
        pStyleTable->close();
    }
    return es;
}


//*************************************************************************
// Database related utility routines 
//*************************************************************************


Acad::ErrorStatus 
postToDb(AcDbEntity* ent)
//
//  Append specified entity to current space of current drawing.
//
{
    AcDbObjectId objId;

    return postToDb(ent, objId);
}


Acad::ErrorStatus 
postToDb(AcDbEntity* ent, AcDbObjectId& objId)
{

    Acad::ErrorStatus      es;
    AcDbBlockTable*        pBlockTable;
    AcDbBlockTableRecord*  pSpaceRecord;

    if ((es = acdbHostApplicationServices()->workingDatabase()->
           getSymbolTable(pBlockTable, AcDb::kForRead))
           != Acad::eOk) {
        return es;
    }

    if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, 
                                 pSpaceRecord,
                                 AcDb::kForWrite)) != Acad::eOk) {
        return es;
    }

    if ((es = pBlockTable->close()) != Acad::eOk) {
        return es;
    }

    if ((es = pSpaceRecord->appendAcDbEntity(objId, ent)) != Acad::eOk) {
        return es;
    }

    if ((es = pSpaceRecord->close()) != Acad::eOk) {
        return es;
    }

    return ent->close();
}


Acad::ErrorStatus 
addToDb(AcDbEntity* ent)
//
//  Append specified entity to current space of current drawing.
//
{
    AcDbObjectId objId;

    return addToDb(ent, objId);
}


Acad::ErrorStatus 
addToDb(AcDbEntity* ent, AcDbObjectId& objId)
{

    Acad::ErrorStatus      es;
    AcDbBlockTable*        pBlockTable;
    AcDbBlockTableRecord*  pSpaceRecord;

    if ((es = acdbHostApplicationServices()->workingDatabase()->
           getSymbolTable(pBlockTable, AcDb::kForRead))
           != Acad::eOk) {
        return es;
    }

    if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, 
                                 pSpaceRecord,
                                 AcDb::kForWrite)) != Acad::eOk) {
        return es;
    }


    if ((es = pBlockTable->close()) != Acad::eOk) {
        return es;
    }
    if ((es = pSpaceRecord->appendAcDbEntity(objId, ent)) != Acad::eOk) {
        return es;
    }

    return pSpaceRecord->close();
}

