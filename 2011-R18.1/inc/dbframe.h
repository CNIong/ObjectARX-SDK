#ifndef AD_DBFRAME_H
#define AD_DBFRAME_H
//
// (C) Copyright 1996-2004 by Autodesk, Inc.
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
//
// DESCRIPTION:  Class header for AcDbFrame
//               Common Base for Raster and OLE 2 Container Features
//
//    AcDbEntity
//      AcDbFrame
//        AcDbOleFrame
//          AcDbOle2Frame  
//

#include "dbmain.h"
#include "gepnt3d.h"

#pragma pack (push, 8)

class ADESK_NO_VTABLE AcDbFrame: public AcDbEntity
{
protected:
    AcDbFrame();
public:
    ACDB_DECLARE_MEMBERS(AcDbFrame);
    virtual ~AcDbFrame();

    // --- AcDbObject Protocol

    // virtual Adesk::Boolean worldDraw(AcGiWorldDraw*);
    // virtual void viewportDraw(AcGiViewportDraw* mode);
    // virtual Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;

};

#pragma pack (pop)

#endif  // AD_DBRAME_H

