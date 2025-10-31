#pragma once
#ifndef DBLOFTEDSURF_H
#define DBLOFTEDSURF_H
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
// The AcDbLoftedSurface class is the interface class for representing
// ASM lofted surfaces.  

#include "dbsurf.h"

#pragma pack(push, 8)


class AcDbLoftedSurface: public AcDbSurface
{
public:
    AcDbLoftedSurface ();
    virtual ~AcDbLoftedSurface();
    ACDB_DECLARE_MEMBERS(AcDbLoftedSurface);

    // Create lofted surface.
    virtual Acad::ErrorStatus createLoftedSurface (
        AcArray<AcDbEntity*>& crossSectionCurves,
        AcArray<AcDbEntity*>& guideCurves,
        AcDbEntity* pPathCurve, AcDbLoftOptions& loftOptions );

    // Return defining data.
    int           numCrossSections () const;
    AcDbEntity*   getCrossSection ( int idx ) const;
    int           numGuideCurves () const;
    AcDbEntity*   getGuideCurve ( int idx ) const;
    AcDbEntity*   getPathEntity () const;
    void          getLoftOptions ( AcDbLoftOptions& loftOptions ) const;

    // Set new loft options and recreate the surface.
    Acad::ErrorStatus  setLoftOptions ( const AcDbLoftOptions& loftOptions );

    // AcDbObject methods
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

    virtual bool isDependent() const;

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};
#pragma pack(pop)

#endif // DBLOFTEDSURF_H
