//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//   acedxref.h  -  XREF API Definitions
    


#ifndef   _ACEDXREF_H
#define   _ACEDXREF_H
#pragma pack (push, 8)

class AcDbBlockTableRecord;

Acad::ErrorStatus
acedXrefAttach(const ACHAR*           XrefPathname,
               const ACHAR*           XrefBlockname,
                     AcDbObjectId*   pXrefBTRid       = NULL,
                     AcDbObjectId*   pXrefRefid       = NULL,
               const AcGePoint3d*    pXrefInsertPt    = NULL,
               const AcGeScale3d*    pXrefScale       = NULL,
               const double*         pXrefRotateAngle = NULL,
               const bool            bQuiet           = true,
                     AcDbDatabase*   pHostDb          = NULL,
               const wchar_t*       wszPassword       = NULL);

Acad::ErrorStatus
acedXrefOverlay(const ACHAR*           XrefPathname,
                const ACHAR*           XrefBlockname,
                      AcDbObjectId*   pXrefBTRid       = NULL,
                      AcDbObjectId*   pXrefRefid       = NULL,
                const AcGePoint3d*    pXrefInsertPt    = NULL,
                const AcGeScale3d*    pXrefScale       = NULL,
                const double*         pXrefRotateAngle = NULL,
                const bool            bQuiet           = true,
                      AcDbDatabase*   pHostDb          = NULL,
                const wchar_t*        wszPassword      = NULL);

Acad::ErrorStatus
acedXrefUnload(const ACHAR*           XrefBlockname,
               const bool            bQuiet        = true,
                     AcDbDatabase*   pHostDb       = NULL);
Acad::ErrorStatus
acedXrefDetach(const ACHAR*           XrefBlockname,
               const bool            bQuiet        = true,
                     AcDbDatabase*   pHostDb       = NULL);
Acad::ErrorStatus
acedXrefReload(const ACHAR*           XrefBlockname,
               const bool            bQuiet        = true, 
                     AcDbDatabase*   pHostDb       = NULL);
Acad::ErrorStatus
acedXrefBind(const ACHAR*           XrefBlockname,
             const bool            bInsertBind     = false,
             const bool            bQuiet          = true,
                   AcDbDatabase*   pHostDb         = NULL);

Acad::ErrorStatus
acedXrefCreateBlockname(const ACHAR*  XrefPathname,
                              ACHAR*& XrefBlockname);

Acad::ErrorStatus
acedXrefReload(const AcDbObjectIdArray& XrefBTRids,
                     bool               bQuiet     = true,
                     AcDbDatabase*      pHostDb    = NULL);

Acad::ErrorStatus
acedXrefXBind(const AcDbObjectIdArray symbolIds,
              const bool              bQuiet       = true,
                    AcDbDatabase*     pHostDb      = NULL);

Acad::ErrorStatus
acedXrefResolve(AcDbDatabase* pHostDb, const bool bQuiet = true);

Acad::ErrorStatus
acedXrefNotifyCheckFileChanged(AcDbObjectId btrId, bool& hasChanged);

Acad::ErrorStatus
acedSkipXrefNotification(AcDbDatabase* pHostDb, const ACHAR* xrefName);

Acad::ErrorStatus ACDB_PORT 
acedSetXrefResolvedWithUpdateStatus(AcDbBlockTableRecord* pBTR);

#pragma pack (pop)
#endif /* _ACEDXREF_H */

