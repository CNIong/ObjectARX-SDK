//
//
#pragma once
#ifndef DBSWEPTSURF_H
#define DBSWEPTSURF_H
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
// The AcDbSweptSurface class is the interface class for representing
// ASM swept surfaces.  

#include "dbsurf.h"

#pragma pack(push, 8)


class AcDbSweptSurface: public AcDbSurface
{
public:
    AcDbSweptSurface ();
    virtual ~AcDbSweptSurface();
    ACDB_DECLARE_MEMBERS(AcDbSweptSurface);

    // Create swept surface.
    virtual Acad::ErrorStatus createSweptSurface ( AcDbEntity* pSweepEnt,
        AcDbEntity* pPathEnt, AcDbSweepOptions& sweepOptions );

    // Return defining data.
    AcDbEntity*   getSweepEntity () const;
    AcDbEntity*   getPathEntity () const;

    // Get/set the sweep options.
    void               getSweepOptions ( AcDbSweepOptions& sweepOptions ) const;
    Acad::ErrorStatus  setSweepOptions ( const AcDbSweepOptions& sweepOptions );

    // Return length of path curve.
    Acad::ErrorStatus  getPathLength ( double& len ) const;

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

#endif // DBSWEPTSURF_H
