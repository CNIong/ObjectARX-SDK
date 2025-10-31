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

    ACDB_PORT bool isDefaultHomeView() const;

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