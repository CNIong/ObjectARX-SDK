//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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


Acad::ErrorStatus
acedXrefAttach(const char*           XrefPathname,
               const char*           XrefBlockname,
                     AcDbObjectId*   pXrefBTRid       = NULL,
                     AcDbObjectId*   pXrefRefid       = NULL,
               const AcGePoint3d*    pXrefInsertPt    = NULL,
               const AcGeScale3d*    pXrefScale       = NULL,
               const double*         pXrefRotateAngle = NULL,
               const bool            bQuiet           = true);

Acad::ErrorStatus
acedXrefOverlay(const char*           XrefPathname,
                const char*           XrefBlockname,
                      AcDbObjectId*   pXrefBTRid       = NULL,
                      AcDbObjectId*   pXrefRefid       = NULL,
                const AcGePoint3d*    pXrefInsertPt    = NULL,
                const AcGeScale3d*    pXrefScale       = NULL,
                const double*         pXrefRotateAngle = NULL,
                const bool            bQuiet           = true);

Acad::ErrorStatus
acedXrefUnload(const char*           XrefBlockname,
               const bool            bQuiet        = true);
Acad::ErrorStatus
acedXrefDetach(const char*           XrefBlockname,
               const bool            bQuiet        = true);
Acad::ErrorStatus
acedXrefReload(const char*           XrefBlockname,
               const bool            bQuiet        = true);
Acad::ErrorStatus
acedXrefBind(const char*           XrefBlockname,
             const bool            bInsertBind     = false,
             const bool            bQuiet          = true);

Acad::ErrorStatus
acedXrefCreateBlockname(const char*  XrefPathname,
                              char*& XrefBlockname);

Acad::ErrorStatus
acedXrefReload(const AcDbObjectIdArray& XrefBTRids,
               bool                     bQuiet     = true);

Acad::ErrorStatus
acedXrefXBind(const AcDbObjectIdArray symbolIds,
              const bool              bQuiet      = true);

#pragma pack (pop)
#endif /* _ACEDXREF_H */

