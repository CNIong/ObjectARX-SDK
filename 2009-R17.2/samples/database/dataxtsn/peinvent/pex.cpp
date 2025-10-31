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
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <string.h>

#include "dbmain.h"

#include "adscodes.h"
#include "acedads.h"
#include "acutads.h"

#include "pex.h"




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



// ========= AdskObjectInventory Protocol Extension Class  =========

// defines an effective "Inventory Id" member for AcDbObject, using
// Xdata for storage of the per-instance value.
//
ACRX_NO_CONS_DEFINE_MEMBERS(AsdkObjectInventory, AcRxObject);

Acad::ErrorStatus AsdkObjectInventory::inventoryId(const AcDbObject* pObj, TCHAR*& pIdStr) const
{
    // Start off assuming this is null.
    //
    pIdStr = NULL;
    struct resbuf *pRb = pObj->xData(PE_INVENTORY_SERVICE);
    if (pRb != NULL) {
        struct resbuf* pIdRb = pRb->rbnext;
        if ((pRb->restype != AcDb::kDxfRegAppName) ||
            ((pIdRb != NULL) && (pIdRb->restype != AcDb::kDxfXdAsciiString)))
        {
            pIdStr = NULL;
            acutRelRb(pRb);
            return Acad::eBadDxfSequence;
        }
        // No 2nd resbuf implies no inventory string.
        //
        if (pIdRb != NULL)
            pIdStr = strsave(pIdRb->resval.rstring);
        acutRelRb(pRb);
    }
    return Acad::eOk;
}


Acad::ErrorStatus AsdkObjectInventory::setInventoryId(AcDbObject* pObj, TCHAR* pInventoryId)
{
    struct resbuf* pRb;
    if (pInventoryId == NULL)
        pRb = acutBuildList(1001, PE_INVENTORY_SERVICE, RTNONE);
    else
        pRb = acutBuildList(1001, PE_INVENTORY_SERVICE, 1000, pInventoryId, RTNONE);

    // Make sure the REGAPP name is in the current drawing
    //
    struct resbuf* pAppId =acdbTblSearch(_T(/*NOXLATE*/"APPID"), PE_INVENTORY_SERVICE, 0);
    if ( pAppId == NULL )
        acdbRegApp(PE_INVENTORY_SERVICE);
    else
        acutRelRb(pAppId);

    pObj->setXData(pRb);

    acutRelRb(pRb);
    return Acad::eOk;
}
