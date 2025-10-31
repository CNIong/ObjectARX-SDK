#ifndef AD_DBXLINE_H
#define AD_DBXLINE_H 1
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
// DESCRIPTION: Exported AcDbXline Entity class

#include "dbmain.h"
#include "dbcurve.h"

#pragma pack(push, 8)

class AcGePoint3d;
class AcGeVector3d;

class AcDbXline: public AcDbCurve
{
public:
    AcDbXline();
    ~AcDbXline();
    ACDB_DECLARE_MEMBERS(AcDbXline);
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

inline Adesk::Boolean AcDbXline::isClosed() const
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbXline::isPeriodic() const
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbXline::isPlanar() const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDbXline::getStartParam(double&) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::getEndParam(double&) const
{
    // endParam for an Xline is positive infinity
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::getStartPoint(AcGePoint3d&) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::getEndPoint(AcGePoint3d&) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::getSpline(AcDbSpline*&) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::extend(double newParam)
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::extend(Adesk::Boolean, const AcGePoint3d&)
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::getArea(double&) const
{
    return Acad::eNotApplicable;
}

#pragma pack(pop)

#endif

