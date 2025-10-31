#ifndef GEOMENT_DBELIPSE_H
#define GEOMENT_DBELIPSE_H
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
//
// DESCRIPTION:
//
// The AcDbEllipse class represents both a full ellipse and an elliptical
// arc. The parametrization of the ellipse is the vector equation
//
//         P(O) = A * cos(O) + B * sin(O)
// 
// where A and B are the semi major and minor axes respectively.

#include "gegbl.h"
#include "dbmain.h"
#include "dbcurve.h"

#pragma pack(push, 8)

class AcDbEllipse: public  AcDbCurve
{
public:
    AcDbEllipse();
    AcDbEllipse(const AcGePoint3d&  center,
                const AcGeVector3d& unitNormal,
                const AcGeVector3d& majorAxis,
                double              radiusRatio,
                double              startAngle = 0.0,
                double              endAngle   = 6.28318530717958647692);
    virtual ~AcDbEllipse();
    ACDB_DECLARE_MEMBERS(AcDbEllipse);

    AcGePoint3d center() const;
    Acad::ErrorStatus setCenter(const AcGePoint3d& center);

    AcGeVector3d normal() const;
    AcGeVector3d majorAxis() const;
    AcGeVector3d minorAxis() const;

    double radiusRatio() const;
    Acad::ErrorStatus setRadiusRatio(double ratio);

    double startAngle() const;
    Acad::ErrorStatus setStartAngle(double startAngle);    

    double endAngle() const;
    Acad::ErrorStatus setEndAngle(double endAngle);

    Acad::ErrorStatus setStartParam(double startParam);
    Acad::ErrorStatus setEndParam(double endParam);

    double paramAtAngle(double angle) const;
    double angleAtParam(double param) const;

    Acad::ErrorStatus get(AcGePoint3d& center, AcGeVector3d& unitNormal,
        AcGeVector3d& majorAxis, double& radiusRatio, double& startAngle,
        double& endAngle) const;

    Acad::ErrorStatus set(const AcGePoint3d& center,
        const AcGeVector3d& unitNormal, const AcGeVector3d& majorAxis,
        double radiusRatio, double startAngle = 0.0,
        double endAngle = 6.28318530717958647692);

    Adesk::Boolean isNull() const;
  
    DBCURVE_METHODS

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;

};

#pragma pack(pop)

#endif
