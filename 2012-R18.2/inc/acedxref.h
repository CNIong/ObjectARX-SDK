//
// (C) Copyright 1998-2008 by Autodesk, Inc. 
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

Acad::ErrorStatus
acedSetXrefResolvedWithUpdateStatus(AcDbBlockTableRecord* pBTR);

#pragma pack (pop)
#endif /* _ACEDXREF_H */

