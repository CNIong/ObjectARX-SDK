#pragma once
#ifndef DBREVOLVEDSURF_H
#define DBREVOLVEDSURF_H
//
// (C) Copyright 2005-2009 by Autodesk, Inc.
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
// The AcDbRevolvedSurface class is the interface class for representing
// ASM revolved surfaces.  

#include "dbsurf.h"

#pragma pack(push, 8)


class AcDbRevolvedSurface: public AcDbSurface
{
public:
    AcDbRevolvedSurface ();
    virtual ~AcDbRevolvedSurface();
    ACDB_DECLARE_MEMBERS(AcDbRevolvedSurface);

    // Create revolved surface.
    virtual Acad::ErrorStatus createRevolvedSurface ( AcDbEntity* pRevEnt,
        const AcGePoint3d& axisPnt, const AcGeVector3d& axisDir,
        double revAngle, double startAngle,
        AcDbRevolveOptions& revolveOptions );

    // Return the revolve entity.
    AcDbEntity*   getRevolveEntity () const;

    // Get/set the axis of revolution.
    AcGePoint3d        getAxisPnt () const;
    Acad::ErrorStatus  setAxisPnt ( const AcGePoint3d& pnt );
    AcGeVector3d       getAxisVec () const;
    Acad::ErrorStatus  setAxisVec ( const AcGeVector3d& vec );

    // Get/set angle of revolution.
    double             getRevolveAngle () const;
    Acad::ErrorStatus  setRevolveAngle ( double ang );
    double             getStartAngle () const;

    // Get/set revolve options for the surface.
    void               getRevolveOptions ( AcDbRevolveOptions& revolveOptions ) const;
    Acad::ErrorStatus  setRevolveOptions ( const AcDbRevolveOptions& revolveOptions );

    // Set all defining data.
    Acad::ErrorStatus  setRevolve ( const AcGePoint3d& axisPnt, const AcGeVector3d& axisVec,
                                    double revAngle, const AcDbRevolveOptions& revolveOptions );

    // AcDbObject methods
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;
    
    virtual bool isDependent() const;

protected:
    // AcDbEntity methods
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};
#pragma pack(pop)

#endif // DBREVOLVEDSURF_H
