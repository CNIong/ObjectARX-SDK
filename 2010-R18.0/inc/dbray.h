#ifndef AD_DBRAY_H
#define AD_DBRAY_H 1
//
// (C) Copyright 1993-2009 by Autodesk, Inc.
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
// DESCRIPTION: Exported AcDbRay Entity class

#include "dbmain.h"
#include "dbcurve.h"

#pragma pack(push, 8)

class AcGePoint3d;
class AcGeVector3d;

class AcDbRay: public AcDbCurve
{
public:
    AcDbRay();
    ~AcDbRay();
    ACDB_DECLARE_MEMBERS(AcDbRay);
    DBCURVE_METHODS

    Acad::ErrorStatus getOffsetCurvesGivenPlaneNormal(
        const AcGeVector3d& normal, double offsetDist,
        AcDbVoidPtrArray& offsetCurves) const;
    
    AcGePoint3d  basePoint() const;
    void         setBasePoint(const AcGePoint3d& pt); 

    AcGeVector3d unitDir() const;
    void         setUnitDir(const AcGeVector3d& vec);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

inline Adesk::Boolean AcDbRay::isClosed() const      
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbRay::isPeriodic() const      
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbRay::isPlanar() const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDbRay::getStartParam(double& startParam) const
{
    startParam = 0.0;
    return Acad::eOk;
}

inline Acad::ErrorStatus AcDbRay::getEndParam(double& ) const
{
    // endParam for a Ray is positive infinity
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbRay::getEndPoint(AcGePoint3d& ) const 
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbRay::getSpline(AcDbSpline*& ) const 
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbRay::getArea(double& ) const 
{
    return Acad::eNotApplicable;
}

#pragma pack(pop)

#endif
