#ifndef AD_DBXUTIL_H
#define AD_DBXUTIL_H 1
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// DESCRIPTION: Header for homeless utilities exported to the API.
//

#include "acadstrc.h"
#include "adesk.h"
#include "adsdef.h"
#include "dbid.h"
#include "acutmem.h"

#include "windows.h"

#pragma pack (push, 8)

class AcGeMatrix3d;
class AcDbObject;

// --------- Coordinate-system conversions ---------

bool    acdbWcs2Ucs(ads_point p, ads_point q, bool vec);
bool    acdbWcs2Ecs(ads_point p, ads_point q, ads_point norm, bool vec);
bool    acdbUcs2Wcs(ads_point p, ads_point q, bool vec);
bool    acdbUcs2Ecs(ads_point p, ads_point q, ads_point norm, bool vec);
bool    acdbEcs2Wcs(ads_point p, ads_point q, ads_point norm, bool vec);
bool    acdbEcs2Ucs(ads_point p, ads_point q, ads_point norm, bool vec);

// --------- Miscellaneous ---------

AcDbObjectId      acdbGetCurVportId(AcDbDatabase* pDb);
Acad::ErrorStatus acdbGetProxyInfo(AcDbObject *pObj, char*& dxfName,
                                   char*& className, char*& appName);
bool    acdbUcsMatrix(AcGeMatrix3d& mat, AcDbDatabase * pDb = NULL);

Acad::ErrorStatus acdbGetExtnames(bool &value, AcDbDatabase *pDb);
Acad::ErrorStatus acdbSetExtnames(AcDbDatabase *pDb, bool value);

bool acdbGetPreviewBitmapFromDwg(const char* pszDwgfilename,
                                 HBITMAP* pPreviewBmp,
                                 HPALETTE* pRetPal);

const char* acdbGetReservedString(AcDb::reservedStringEnumType reservedType,
    bool bGetLocalized = true);
const char* acdbXlateReservedString(const char* strSource,
    bool bGetLocalized = true);
bool acdbIsReservedString(const char* strString,
    AcDb::reservedStringEnumType reservedType);

#pragma pack (pop)
#endif // AD_DBXUTIL_H
