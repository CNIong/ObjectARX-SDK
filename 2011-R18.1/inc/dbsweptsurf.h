//
//
#pragma once
#ifndef DBSWEPTSURF_H
#define DBSWEPTSURF_H
//
// (C) Copyright 2005-2010 by Autodesk, Inc.
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

    /// <summary> 
    /// Default constructor.
    /// </summary>
    AcDbSweptSurface ();

    /// <summary> 
    /// Destructor.
    /// </summary>
    virtual ~AcDbSweptSurface();

    ACDB_DECLARE_MEMBERS(AcDbSweptSurface);

    /// <summary> 
    /// Creates a swept surface from the given profile along the
    /// specified path using the specified options.
    /// </summary>
    /// <param name="pSweepEnt"> 
    /// Input profile to be swept.  This may be an entity such as a curve or
    /// surface or region.
    /// </param>
    /// <param name="pPathEnt"> 
    /// Input path along which sweep profile is to be swept.  This entity must
    /// be a curve.
    /// </param>
    /// <param name="sweepOptions"> 
    /// Input sweep options. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus createSweptSurface ( AcDbEntity* pSweepEnt,
        AcDbEntity* pPathEnt, AcDbSweepOptions& sweepOptions );

    /// <summary> 
    /// Returns the entity that was swept.
    /// </summary>
    /// <returns>
    /// Copy of the entity that was swept to create the surface.  The caller
    /// should not delete this pointer or post it to the database.
    /// </returns>
    AcDbEntity*   getSweepEntity () const;

    /// <summary> 
    /// Returns the path entity that the sweep entity was swept along.
    /// </summary>
    /// <returns>
    /// Copy of the path entity. The caller should not delete this
    /// pointer or post it to the database.
    /// </returns>
    AcDbEntity*   getPathEntity () const;

    /// <summary> 
    /// Returns the data of the profile from which the surface was swept.
    /// </summary>
    /// <returns>
    /// Profile data object.  The caller is responsible for deleting this
    /// pointer if it is not NULL.  If the surface was swept from an edge
    /// of a surface or solid, then the returned profile object will only 
    /// contain the edge subent data if the surface is associative.
    /// Otherwise it will only contain the curve that was extracted from the
    /// edge.
    /// </returns>
    ACDB_PORT AcDb3dProfile* sweepProfile () const;

    /// <summary> 
    /// Returns the data of the profile of the path along which the sweep
    /// profile was swept.
    /// </summary>
    /// <returns>
    /// Profile data object.  The caller is responsible for deleting this
    /// pointer if it is not NULL.  If the surface was created by sweeping
    /// along an edge of a surface or solid, then the returned profile object
    /// will only contain the edge subent data if the surface is associative.
    /// Otherwise it will only contain the curve that was extracted from the
    /// edge.
    /// </returns>
    ACDB_PORT AcDb3dProfile* pathProfile () const;

    /// <summary> 
    /// Gets the options that were used to create the surface.
    /// </summary>
    /// <param name="sweepOptions"> 
    /// Output options that were used to create the surface. 
    /// </param>
    void               getSweepOptions ( AcDbSweepOptions& sweepOptions ) const;

    /// <summary> 
    /// Set the sweep options.
    /// </summary>
    /// <param name="sweepOptions"> 
    /// Input sweep options.  
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setSweepOptions ( const AcDbSweepOptions& sweepOptions );

    /// <summary> 
    /// Returns the length of the path curve.
    /// </summary>
    /// <returns>
    /// Length of the path curve.
    /// </returns>
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
