#pragma once
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
// The AcDbSurface class is the interface class for representing
// ASM surfaces inside AutoCAD.  

#include "dbmain.h"
#include "dbsubeid.h"
#include "gepnt3d.h"
#include "gevec3d.h"
#include "dbbody.h"
#include "dbRevolveOptions.h"
#include "dbSweepOptions.h"
#include "dbLoftOptions.h"

#pragma pack(push, 8)


class AcDbSurface: public AcDbEntity
{
public:
    AcDbSurface();
    virtual ~AcDbSurface();
    ACDB_DECLARE_MEMBERS(AcDbSurface);

    // Create a swept surface from 2D entity with thickness
    // or a planar surface from a closed curve or a region.
    static Acad::ErrorStatus createFrom ( const AcDbEntity* pFromEntity,
                                          AcDbSurface*& pNewSurface );

    // Convert planar surface to region.  Return separate region for each face.
    virtual Acad::ErrorStatus convertToRegion ( AcArray<AcDbEntity*>& regions );

    // Create a 3DSOLID by thickening the surface by a 
    // specified amount.
    virtual Acad::ErrorStatus thicken(double thickness,
        bool bBothSides, AcDb3dSolid*& pSolid) const;

    virtual Acad::ErrorStatus createInterferenceObjects(
        AcArray<AcDbEntity*>& interferenceObjects,
        AcDbEntity* pEntity, unsigned int flags ) const;

    virtual Acad::ErrorStatus booleanUnion(const AcDbSurface* pSurface2,
        AcDbSurface*& pNewSurface);
    virtual Acad::ErrorStatus booleanSubtract(const AcDbSurface* pSurface2,
        AcDbSurface*& pNewSurface);
    virtual Acad::ErrorStatus booleanSubtract(const AcDb3dSolid* pSolid,
        AcDbSurface*& pNewSurface);
    virtual Acad::ErrorStatus booleanIntersect(const AcDbSurface* pSurface2,
        AcArray<AcDbEntity*>& intersectionEntities);
    virtual Acad::ErrorStatus booleanIntersect(const AcDb3dSolid* pSolid,
        AcArray<AcDbEntity*>& intersectionEntities);
    virtual Acad::ErrorStatus imprintEntity(const AcDbEntity* pEntity);
    virtual Acad::ErrorStatus createSectionObjects(const AcGePlane& sectionPlane,
        AcArray<AcDbEntity*>& sectionObjects) const;
    virtual Acad::ErrorStatus sliceByPlane(const AcGePlane& slicePlane,
        AcDbSurface*& pNegHalfSurface, AcDbSurface*& pNewSurface);
    virtual Acad::ErrorStatus sliceBySurface(
        const AcDbSurface* pSlicingSurface, AcDbSurface*& pNegHalfSurface,
        AcDbSurface*& pNewSurface);
    virtual Acad::ErrorStatus chamferEdges(
        const AcArray<AcDbSubentId *> &edgeSubentIds,
        const AcDbSubentId& baseFaceSubentId, 
        double baseDist, double otherDist);
    virtual Acad::ErrorStatus filletEdges(
        const AcArray<AcDbSubentId *> &edgeSubentIds,
        const AcGeDoubleArray& radius, 
        const AcGeDoubleArray& startSetback, 
        const AcGeDoubleArray& endSetback);

    virtual Acad::ErrorStatus setSubentColor(const AcDbSubentId& subentId,
        const AcCmColor& color);
    virtual Acad::ErrorStatus getSubentColor(const AcDbSubentId& subentId,
        AcCmColor& color) const;

    virtual Acad::ErrorStatus setSubentMaterial(const AcDbSubentId& subentId,
        const AcDbObjectId& matId);
    virtual Acad::ErrorStatus getSubentMaterial(const AcDbSubentId& subentId,
        AcDbObjectId& matId) const;

    virtual Acad::ErrorStatus setSubentMaterialMapper(const AcDbSubentId& subentId,
        const AcGiMapper& mapper);
    virtual Acad::ErrorStatus getSubentMaterialMapper(const AcDbSubentId& subentId,
        AcGiMapper& mapper) const;

    virtual Acad::ErrorStatus getArea(double& area) const;

    virtual void* body() const;  // INTERNAL USE ONLY
    virtual Acad::ErrorStatus setBody(const void* modelerBody);  // INTERNAL USE ONLY
    virtual AcDbSubentId internalSubentId(void* ent) const;          // INTERNAL USE ONLY
    virtual void* internalSubentPtr(const AcDbSubentId& id) const;   // INTERNAL USE ONLY

    // AcDbObject methods
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

    virtual Adesk::UInt16       uIsolineDensity() const;
    virtual Acad::ErrorStatus   setUIsolineDensity(Adesk::UInt16 numIsolines);

    virtual Adesk::UInt16       vIsolineDensity() const;
    virtual Acad::ErrorStatus   setVIsolineDensity(Adesk::UInt16 numIsolines);

protected:
    // AcDbEntity methods
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;

};
#pragma pack(pop)
