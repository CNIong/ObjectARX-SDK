#ifndef AD_DBXUTIL_H
#define AD_DBXUTIL_H 1
//
// (C) Copyright 1993-2006 by Autodesk, Inc.
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
#include "dbidar.h"
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

AcDbObjectId acdbGetCurVportTableRecordId(AcDbDatabase* pDb);
AcDbObjectId      acdbGetCurVportId(AcDbDatabase* pDb);
Acad::ErrorStatus acdbGetProxyInfo(AcDbObject *pObj, ACHAR*& dxfName,
                                   ACHAR*& className, ACHAR*& appName);
bool    acdbUcsMatrix(AcGeMatrix3d& mat, AcDbDatabase * pDb = NULL);

Acad::ErrorStatus acdbGetExtnames(bool &value, AcDbDatabase *pDb);
Acad::ErrorStatus acdbSetExtnames(AcDbDatabase *pDb, bool value);

bool acdbGetPreviewBitmapFromDwg(const ACHAR* pszDwgfilename,
                                 HBITMAP* pPreviewBmp,
                                 HPALETTE* pRetPal);

const ACHAR* acdbGetReservedString(AcDb::reservedStringEnumType reservedType,
    bool bGetLocalized = true);
const ACHAR* acdbXlateReservedString(const ACHAR* strSource,
    bool bGetLocalized = true);
bool acdbIsReservedString(const ACHAR* strString,
    AcDb::reservedStringEnumType reservedType);

// acdbGetUnitsConversion
//
// Obtains the double value that represents the differnce in scale between two
// AcDb::UnitsValue enumerations. The returned conversion factor provides the
// multiplier needed to convert units measured in "from" units to the units
// measured in "to" units. 
// 
//   toValue = conversionFactor * fromValue
//
// (For example, if the "to" units are millimeters and the "from" units are
// inches the conversion factor is 25.4).
//   
// Returns eOk if succesful. Returns eInvalidInput if either of the UnitsValue
// enums are invalid.

Acad::ErrorStatus acdbGetUnitsConversion (AcDb::UnitsValue from,
                                          AcDb::UnitsValue to,
                                          double& conversionFactor);

// See if a filename has a corresponding .dwk file next to it.
bool ADESK_STDCALL acdbDwkFileExists(const ACHAR *pszFileName);

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
                          const ACHAR* name, 
                          const ACHAR* categoryName,
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
                           ACHAR*& fontName);

Acad::ErrorStatus
acdbOleSetSelectedFontName(const AcDbOle2Frame* pOleEnt,
                           const ACHAR* fontName);

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
                                   ACHAR*& fontName);

Acad::ErrorStatus
acdbOleSetOriginalSelectedFontName(const AcDbOle2Frame* pOleEnt,
                                   const ACHAR* fontName);

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
// Internal use only. 
bool 
acdbGetDimTextBackground(AcDbObject *pObj, 
                         int& bgFlag, 
                         AcCmColor& bgColor);

// Internal use only. 
bool 
acdbSetDimTextBackground(AcDbObject *pObj, 
                         int bgFlag, 
                         AcCmColor* pBgColor,
                         bool autoClearOverride = true);

// Internal use only. 
bool 
acdbGetDimExtensionLength(AcDbObject *pObj, 
                          double& fValue);

// Internal use only. 
bool 
acdbSetDimExtensionLength(AcDbObject *pObj, 
                          double fValue,
                          bool autoClearOverride = true);
                          
// Internal use only. 
bool 
acdbGetFixedLengthExtLineEnabled(AcDbObject *pObj,
                   int& nValue);

// Internal use only. 
bool 
acdbSetFixedLengthExtLineEnabled(AcDbObject *pObj, 
                        int nValue, 
                        bool autoClearOverride=true);

// Internal use only. 
bool 
acdbGetArcLengthSymbolPlacement(AcDbObject *pObj,
                                int& nValue);

// Internal use only. 
bool 
acdbSetArcLengthSymbolPlacement(AcDbObject *pObj, 
                          int nValue,
                          bool autoClearOverride = true);
                          
// Internal use only.                           
bool 
acdbGetDimLineLinetype(AcDbObject *pObj,
                       AcDbObjectId& oidValue);

// Internal use only. 
bool 
acdbSetDimLineLinetype(AcDbObject *pObj,
                       AcDbObjectId oidValue,
                       bool autoClearOverride = true);

// Internal use only. 
bool 
acdbGetDimExt1Linetype(AcDbObject *pObj,
                       AcDbObjectId& oidValue);

// Internal use only. 
bool 
acdbSetDimExt1Linetype(AcDbObject *pObj,
                       AcDbObjectId oidValue,
                       bool autoClearOverride = true);
                       
// Internal use only.                        
bool 
acdbGetDimExt2Linetype(AcDbObject *pObj,
                       AcDbObjectId& oidValue);

// Internal use only. 
bool 
acdbSetDimExt2Linetype(AcDbObject *pObj,
                       AcDbObjectId oidValue,
                       bool autoClearOverride = true);
                       
// Internal use only.                        
bool 
acdbGetLargeRadDimJogAngle(AcDbObject *pObj,
								double& fJogAngle);

// Internal use only. 
bool 
acdbSetLargeRadDimJogAngle(AcDbObject *pObj, 
								double fJogAngle,
								bool autoClearOverride = true);
                                
// Internal use only.                                 
bool 
acdbGetDimFlipArrow(AcDbObject *pObj,
                    int& nValue);

// Internal use only. 
bool 
acdbSetDimFlipArrow(AcDbObject *pObj, 
                    int nValue,
                    bool autoClearOverride = true);
                    
// Internal use only.                     
bool 
acdbGetDimFlipArrowWhich(AcDbObject *pObj,
                         int& nValue);
                         
// Internal use only.                          
bool 
acdbSetDimFlipArrowWhich(AcDbObject *pObj, 
                          int nValue,
                          bool autoClearOverride = true);

// get/set a flag for dimstyle, linetype and layer object to exempt from
// CAD STANDARD check.
// pObj: pointer to AcDbObject
// bitFlags = 0x00:   No Exemption  
// bitFlags = 0x01:   Exempt from CAD Standard check
// 
bool acdbGetExemptCheckFlag(AcDbObject *pObj, int& bitFlags);

bool acdbSetExemptCheckFlag(AcDbObject *pObj, int bitFlags);

// Visual Style from viewport
AcDbObjectId acdbGetViewportVisualStyle();
Acad::ErrorStatus acdbSetViewportVisualStyle(AcDbObjectId visualStyleId);

// acdbForceTextAdjust()
// Forces the text to be adjusted in all text objects in the objectid array.
// objIds: input array of AcDbObjectId objects whose text will be adjusted.
//         Supported objects are AcDbText, AcDbBlockReference and AcDbBlockTableRecord.
Acad::ErrorStatus acdbForceTextAdjust(const AcDbObjectIdArray& objIds);

#pragma pack (pop)
#endif // AD_DBXUTIL_H
