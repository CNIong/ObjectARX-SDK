// (C) Copyright 1996-2008 by Autodesk, Inc. 
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
// ========= EDINVENT:  ARX Extension Dictionary Example ================ 
//
//  Test App for ARx Usage of Extension Dictionary in conjunction
//  with the AcDb library.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "dbmain.h"
#include "dbproxy.h"

#include "adscodes.h"
#include "acedads.h"
#include "tchar.h"

// This app's exported Extension Object Class
//
#include "edinvent.h"



//  STRSAVE  --  Allocate a duplicate of a string
//
static TCHAR*
strsave(const TCHAR *t)
{
    const size_t nSize = _tcslen(t) + 1;
    TCHAR *c = (TCHAR*)malloc((unsigned) (nSize) * sizeof(TCHAR));
    if (c == NULL) {
        acutPrintf (_T("Application %s FATAL ERROR: Out of memory\n"), acedGetAppName());
        return c;
    }
    errno_t err = _tcscpy_s(c, nSize, t);
    assert(err == 0);
    return c;
}

// ========= AsdkInventoryData Extension Object Class  =========
//
// defines an effective "Inventory Id" member for AcDbObject, using
// Xdata for storage of the per-instance value.

ACRX_DXF_DEFINE_MEMBERS(AsdkInventoryData,AcDbObject,
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
AcDbProxyObject::kNoOperation,ASDKINVENTORYDATA,
    Extension Dictionary Inventory Id);

AsdkInventoryData::AsdkInventoryData()
{
    mId = NULL;
}

AsdkInventoryData::~AsdkInventoryData()
{
    if (mId != NULL)
        free(mId);
}


TCHAR*
AsdkInventoryData::inventoryId() const
{
    if (mId == NULL)
        return NULL;
    return strsave(mId);
}

void
AsdkInventoryData::setInventoryId(const TCHAR*inventoryId)
{
    if (mId != NULL) {
        free(mId);
        mId = NULL;
    }
    if (inventoryId != NULL)
        mId = strsave(inventoryId);
}

Acad::ErrorStatus
AsdkInventoryData::dwgInFields(AcDbDwgFiler* filer)
{
    assertWriteEnabled();
 
    Acad::ErrorStatus es;
    es = AcDbObject::dwgInFields(filer);
    assert(es == Acad::eOk);

    // Free Up Previous String.
    //
    setInventoryId(NULL);
    es = filer->readItem(&mId);
    assert(es == Acad::eOk);

    return es;
}


Acad::ErrorStatus
AsdkInventoryData::dwgOutFields(AcDbDwgFiler* filer) const
{
    assertReadEnabled();

    Acad::ErrorStatus es;
    es = AcDbObject::dwgOutFields(filer);
    assert(es == Acad::eOk);

    es = filer->writeItem(mId);
    assert(es == Acad::eOk);

    return es;
}


Acad::ErrorStatus
AsdkInventoryData::dxfInFields(AcDbDxfFiler* filer)
{
    assertWriteEnabled();

    Acad::ErrorStatus es = AcDbObject::dxfInFields(filer);
    
    if(es == Acad::eOk)
    {
        if (!filer->atSubclassData(_T(/*NOXLATE*/"AsdkInventoryData")))
            return filer->filerStatus();

        resbuf rb;
        es = filer->readResBuf(&rb);

        if ((es == Acad::eOk) && (rb.restype == AcDb::kDxfXTextString))
            setInventoryId(rb.resval.rstring);
        else {
            // unrecognized group. Push it back so that the subclass
            // can read it again.
            //
            filer->pushBackItem();
            es = Acad::eBadDxfSequence;
        }
    }
    return es;
}
 
Acad::ErrorStatus
AsdkInventoryData::dxfOutFields(AcDbDxfFiler* filer) const
{
    assertReadEnabled();
 
    if (AcDbObject::dxfOutFields(filer) != Acad::eOk)
        return filer->filerStatus();
    
    filer->writeItem(AcDb::kDxfSubclass, _T(/*NOXLATE*/"AsdkInventoryData"));
    filer->writeItem(AcDb::kDxfXTextString, mId);
    
    return filer->filerStatus();
}
