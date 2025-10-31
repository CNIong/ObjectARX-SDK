#ifndef AD_DBXUTIL_H
#define AD_DBXUTIL_H 1
//
// (C) Copyright 1993-2003 by Autodesk, Inc.
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
class AcDbOle2Frame;
class AcCmColor;

// --------- Coordinate-system conversions ---------

bool    acdbWcs2Ucs(ads_point p, ads_point q, bool vec);
bool    acdbWcs2Ecs(ads_point p, ads_point q, ads_point norm, bool vec);
bool    acdbUcs2Wcs(ads_point p, ads_point q, bool vec);
bool    acdbUcs2Ecs(ads_point p, ads_point q, ads_point norm, bool vec);
bool    acdbEcs2Wcs(ads_point p, ads_point q, ads_point norm, bool vec);
bool    acdbEcs2Ucs(ads_point p, ads_point q, ads_point norm, bool vec);

AcGeVector3d     ucsXDir();
AcGeVector3d     ucsYDir();
void			 ucsNormalVector(AcGeVector3d& ucsNormalVec);

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

// See if a filename has a corresponding .dwk file next to it.
bool ADESK_STDCALL acdbDwkFileExists(const char *pszFileName);

// Returns number of ids that were queued for regen.
//
int ADESK_STDCALL acdbQueueForRegen(const AcDbObjectId *pIdArray,
                                    int nNumIds);

// --------- Dynamic Dimension dimstyle manipulations ---------

AcDbObjectId  acdbGetDynDimStyleId( AcDbDatabase* pDb = NULL );

// --------- View and Viewport Management ---------------------


// This function creates a view from the given viewport.  It is a view of
// the viewport in its layout.  The size of the view are stretched to
// include any associated label block as well as some desirable padding
// around the sum of the viewport and label block extents.
Acad::ErrorStatus
acdbCreateViewByViewport( AcDbDatabase *pDb,
                          AcDbObjectId viewportId, 
                          const char* name, 
                          const char* categoryName,
                          AcDbObjectId labelBlockId,
                          AcDbObjectId& view);



// OLE

// Below is a wrapper for AcDbImpOle2Frame::hitTest(..) to make it 
// accessible from within the coreads\acadapp arx app for OLE object
// face selection support.  It returns Acad::eOk if the passed pickpoint
// is within the bounds of the OLE object, any other return value should
// be interpreted as if the pickpoint is not within the bounds of the 
// object.
Acad::ErrorStatus
acdbOleHitTest(const AcDbOle2Frame* pOleEnt,     
               const AcGePoint3d&  wvpt, 
               const AcGeVector3d& wvwdir);

Acad::ErrorStatus
acdbOleGetRotationMatrix(const AcDbOle2Frame* pOleEnt,
                         AcGeMatrix3d& rotMat);

// Original width and height is used in
// calculating reset scale
Acad::ErrorStatus
acdbOleGetOriginalWidthHeight(const AcDbOle2Frame* pOleEnt,
                              double& width, 
                              double& height);

Acad::ErrorStatus
acdbOleSetOriginalWidthHeight(const AcDbOle2Frame* pOleEnt,
                              const double width, 
                              const double height);

// Selected font name, point size and size in Acad units
// is to persist the selected font name from the 
// OLE Text Size dialog
Acad::ErrorStatus
acdbOleGetSelectedFontName(const AcDbOle2Frame* pOleEnt,
                           char*& fontName);

Acad::ErrorStatus
acdbOleSetSelectedFontName(const AcDbOle2Frame* pOleEnt,
                           const char* fontName);

Acad::ErrorStatus
acdbOleGetSelectedFontPointSize(const AcDbOle2Frame* pOleEnt,
                                int& pointSize);

Acad::ErrorStatus
acdbOleSetSelectedFontPointSize(const AcDbOle2Frame* pOleEnt,
                                const int pointSize);

Acad::ErrorStatus
acdbOleGetSelectedTextSizeInAcadUnits(const AcDbOle2Frame* pOleEnt,
                                      double& sizeInAcadUnits);

Acad::ErrorStatus
acdbOleSetSelectedTextSizeInAcadUnits(const AcDbOle2Frame* pOleEnt,
                                      const double sizeInAcadUnits);

// Originally selected font name, point size and size in Acad units
// is to support Reset.  
Acad::ErrorStatus
acdbOleGetOriginalSelectedFontName(const AcDbOle2Frame* pOleEnt,
                                   char*& fontName);

Acad::ErrorStatus
acdbOleSetOriginalSelectedFontName(const AcDbOle2Frame* pOleEnt,
                                   const char* fontName);

Acad::ErrorStatus
acdbOleGetOriginalSelectedFontPointSize(const AcDbOle2Frame* pOleEnt,
                                        int& pointSize);

Acad::ErrorStatus
acdbOleSetOriginalSelectedFontPointSize(const AcDbOle2Frame* pOleEnt,
                                        const int pointSize);

Acad::ErrorStatus
acdbOleGetOriginalSelectedTextSizeInAcadUnits(const AcDbOle2Frame* pOleEnt,
                                              double& sizeInAcadUnits);

Acad::ErrorStatus
acdbOleSetOriginalSelectedTextSizeInAcadUnits(const AcDbOle2Frame* pOleEnt,
                                              const double sizeInAcadUnits);

// Dimension text background fill utility functions (for internal use)
// 
// pObj must be a AcDbDimension or AcDbDimStyleTableRecord derived object
// which stores dim text background fill in xData.
// bgFlag = 0: No fill for dimension text 
// bgFlag = 1: Use Acad drawing background color for dim text fill
// bgFlag = 2: Use specified color for dim text fill
 
bool 
acdbGetDimTextBackground(AcDbObject *pObj, 
                         int& bgFlag, 
                         AcCmColor& bgColor);

bool 
acdbSetDimTextBackground(AcDbObject *pObj, 
                         int bgFlag, 
                         AcCmColor* pBgColor,
                         bool autoClearOverride = true);

#pragma pack (pop)
#endif // AD_DBXUTIL_H
