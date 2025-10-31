//
#ifndef AD_DBLAYOUT_H
#define AD_DBLAYOUT_H
//
// (C) Copyright 1998-2009 by Autodesk, Inc. 
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
// DESCRIPTION: Exported protocol for AutoCAD's built in symbol
//      tables, their table  specific record types, and
//      their iterators.

#include "dbmain.h"
#include "dbdict.h"
#include "AdAChar.h"
#include "dbplotsettings.h"

#pragma pack(push, 8)

// Class definition for paperspace layout object

class AcDbLayout: public AcDbPlotSettings
{
public:
            ACDB_DECLARE_MEMBERS(AcDbLayout);

    AcDbLayout();
    virtual ~AcDbLayout     ();

    AcDbObjectId      
    getBlockTableRecordId   () const;

    virtual Acad::ErrorStatus 
    setBlockTableRecordId   (AcDbObjectId BlockTableRecordId);

    virtual Acad::ErrorStatus 
    addToLayoutDict         (AcDbDatabase *towhichDb,
                             AcDbObjectId BlockTableRecordId);

    Acad::ErrorStatus 
    getLayoutName           (const ACHAR*& layoutName) const;

    Acad::ErrorStatus 
    getLayoutName           (ACHAR*& layoutName) const;

    virtual Acad::ErrorStatus 
    setLayoutName           (const ACHAR* layoutName);

    int               
    getTabOrder             () const;

    virtual void              
    setTabOrder             (int newOrder);

    bool
    getTabSelected          () const;

    virtual void              
    setTabSelected          (Adesk::Boolean tabSelected);

    AcDbObjectIdArray 
    getViewportArray        () const;

#ifdef _WINDOWS_
    Acad::ErrorStatus getThumbnail (BITMAPINFO*& thumbnail) const;
    Acad::ErrorStatus setThumbnail(const BITMAPINFO * thumbnail);
#endif

    void
    getLimits (AcGePoint2d& limMin, AcGePoint2d& limMax) const;

    void
    getExtents (AcGePoint3d& extMin, AcGePoint3d& extMax) const;

    Acad::ErrorStatus
    initialize(AcDbObjectId* paperVportId = NULL);

    bool
    annoAllVisible() const;

    Acad::ErrorStatus
    setAnnoAllVisible(bool newVal);

protected:
    virtual Acad::ErrorStatus 
    subGetClassID              (CLSID* pClsid) const;
};

#pragma pack(pop)

#endif
