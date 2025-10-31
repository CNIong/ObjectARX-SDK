///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2007-2008 by Autodesk, Inc.
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
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
///////////////////////////////////////////////////////////////////////////////
//
// Name:            dbNavSettings.h
//
// Description:     3D Navigation Tools DB Settings API, along with AcDbHomeView
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#pragma pack(push, 8)

class AcDbImpHomeView;

///////////////////////////////////////////////////////////////////////////////
//
// class AcDbHomeView - navigation home view settings class
//

class AcDbHomeView
{
public:
    ACDB_PORT AcDbHomeView();
    ACDB_PORT AcDbHomeView(const AcDbHomeView& rhvw);
    ACDB_PORT virtual ~AcDbHomeView();

    // Member variable routines
    ACDB_PORT const AcGePoint3d&     eye()           const;
    ACDB_PORT const AcGePoint3d&     center()        const;
    ACDB_PORT const AcGeVector3d&    up()            const;
    ACDB_PORT const double           width()         const;
    ACDB_PORT const double           height()        const;
    ACDB_PORT const bool             isPerspective() const;

    ACDB_PORT void setEye         (const AcGePoint3d& ptEye);
    ACDB_PORT void setCenter      (const AcGePoint3d& ptCenter);
    ACDB_PORT void setUp          (const AcGeVector3d& vUp);
    ACDB_PORT void setWidth       (double dWidth);
    ACDB_PORT void setHeight      (double dHeight);
    ACDB_PORT void setPerspective (bool bPerspective);

    // DB access utility
    ACDB_PORT Acad::ErrorStatus setHomeView(AcDbDatabase * pDb) const;
    ACDB_PORT Acad::ErrorStatus getHomeView(AcDbDatabase * pDb,
                                            bool           bCreateDefault = false);

    // Fill members with default values
    ACDB_PORT void toggleDefaultSettings();

    ACDB_PORT bool            operator == (const AcDbHomeView& rhvw) const;
    ACDB_PORT bool            operator != (const AcDbHomeView& rhvw) const;
    ACDB_PORT AcDbHomeView&   operator  = (const AcDbHomeView& rhvw);

private:
    AcDbImpHomeView * mpImpObj;
};

// Navigation home view routine
ACDB_PORT 
Acad::ErrorStatus acdbSetHomeView(AcDbDatabase *        pDb, 
                                  const AcDbHomeView&   hmView);

ACDB_PORT 
Acad::ErrorStatus acdbGetHomeView(AcDbDatabase *        pDb, 
                                  AcDbHomeView&         hmView);

// ViewCube compass show/hide
ACDB_PORT Acad::ErrorStatus 
acdbSetShowCompass(AcDbDatabase *         pDb, 
                   bool                   bShow);

ACDB_PORT Acad::ErrorStatus 
acdbGetShowCompass(AcDbDatabase *         pDb, 
                   bool &                 bShow);

#pragma pack(pop)