#pragma once
#ifndef GEOMENT_DBSOL3D_H
#define GEOMENT_DBSOL3D_H
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
// DESCRIPTION:
//
// The AcDb3dSolid class is the interface class for representing B-REP solids.
//

#include "dbmain.h"
#include "dbsubeid.h"
#include "gepnt3d.h"
#include "gevec3d.h"
#include "acarray.h"
#include "dbsurf.h"

#pragma pack(push, 8)

class AcDb3dSolid: public  AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDb3dSolid);
    AcDb3dSolid();
    virtual ~AcDb3dSolid();

    virtual Acad::ErrorStatus createBox(double xLen, double yLen, double zLen);
    virtual Acad::ErrorStatus createFrustum(double height, double xRadius,
        double yRadius, double topXRadius);
    virtual Acad::ErrorStatus createSphere(double radius);
    virtual Acad::ErrorStatus createTorus(double majorRadius, double minorRadius);
    virtual Acad::ErrorStatus createPyramid(double height, int sides, 
        double radius, double topRadius = 0.0 );
    virtual Acad::ErrorStatus createWedge(double xLen, double yLen, double zLen);
    virtual Acad::ErrorStatus extrude(const AcDbRegion* region, double height,
        double taperAngle = 0.0);
    virtual Acad::ErrorStatus extrudeAlongPath(const AcDbRegion* region,
        const AcDbCurve* path, double taperAngle = 0.0);

    // Calls to this function should be replaced with calls to createRevolvedSolid.
    virtual Acad::ErrorStatus revolve(const AcDbRegion* region,
        const AcGePoint3d& axisPoint, const AcGeVector3d& axisDir,
        double angleOfRevolution);

    // Create revolved solid by revolving an entity or face.
    virtual Acad::ErrorStatus createRevolvedSolid ( AcDbEntity* pRevEnt,
                                                    const AcGePoint3d& axisPnt,
                                                    const AcGeVector3d& axisDir,
                                                    double revAngle, double startAngle,
                                                    AcDbRevolveOptions& revolveOptions );
    virtual Acad::ErrorStatus createRevolvedSolid ( AcDbEntity* pRevEnt,
                                                    const AcDbSubentId& faceSubentId,
                                                    const AcGePoint3d& axisPnt,
                                                    const AcGeVector3d& axisDir,
                                                    double revAngle, double startAngle,
                                                    AcDbRevolveOptions& revolveOptions );

    // Create swept solid by sweeping an entity or face along a path.
    virtual Acad::ErrorStatus createSweptSolid ( AcDbEntity* pSweepEnt,
                                                 AcDbEntity* pPathEnt,
                                                 AcDbSweepOptions& sweepOptions );
    virtual Acad::ErrorStatus createSweptSolid ( AcDbEntity *pSweepEnt,
                                                 const AcDbSubentId& faceSubentId,
                                                 AcDbEntity* pPathEnt,
                                                 AcDbSweepOptions& sweepOptions );

    // Create extruded solid by extruding an entity or face.
    virtual Acad::ErrorStatus createExtrudedSolid ( AcDbEntity* pSweepEnt,
                                                    const AcGeVector3d& directionVec,
                                                    AcDbSweepOptions& sweepOptions );
    virtual Acad::ErrorStatus createExtrudedSolid ( AcDbEntity* pSweepEnt,
                                                    const AcDbSubentId& faceSubentId,
                                                    const AcGeVector3d& directionVec, 
                                                    AcDbSweepOptions& sweepOptions );
    virtual Acad::ErrorStatus createExtrudedSolid ( AcDbEntity* pSweepEnt,
                                                    const AcDbSubentId& faceSubentId,
                                                    double height, 
                                                    AcDbSweepOptions& sweepOptions );
    
    // Create lofted solid.
    virtual Acad::ErrorStatus createLoftedSolid (
        AcArray<AcDbEntity*>& crossSectionCurves,
        AcArray<AcDbEntity*>& guideCurves,
        AcDbEntity* pPathCurve, AcDbLoftOptions& loftOptions );

    virtual Acad::ErrorStatus createFrom(const AcDbEntity* pFromEntity);

    virtual  Acad::ErrorStatus getArea(double& area) const;
    virtual void* body() const;  // INTERNAL USE ONLY

    virtual Acad::ErrorStatus checkInterference(const AcDb3dSolid* otherSolid,
        Adesk::Boolean createNewSolid, Adesk::Boolean& solidsInterfere,
        AcDb3dSolid*& commonVolumeSolid)const;

    virtual Acad::ErrorStatus getMassProp(double& volume,
        AcGePoint3d& centroid, double momInertia[3], double prodInertia[3],
        double prinMoments[3], AcGeVector3d prinAxes[3], 
        double radiiGyration[3], AcDbExtents& extents) const;

    virtual Adesk::Boolean isNull() const;

    virtual Acad::ErrorStatus getSection(const AcGePlane& plane,
        AcDbRegion*& sectionRegion) const;

    virtual Acad::ErrorStatus stlOut(const ACHAR* fileName, 
        Adesk::Boolean asciiFormat) const;

    virtual AcDbSubentId internalSubentId(void* ent) const;          // INTERNAL USE ONLY
    virtual void* internalSubentPtr(const AcDbSubentId& id) const;   // INTERNAL USE ONLY

    // Subentity acquisition.
    //
    virtual Acad::ErrorStatus booleanOper(AcDb::BoolOperType operation,
        AcDb3dSolid* solid);
    virtual Acad::ErrorStatus setBody(const void* modelerBody);  // INTERNAL USE ONLY

    virtual Acad::ErrorStatus getSlice(const AcGePlane& plane,
        Adesk::Boolean getNegHalfToo, AcDb3dSolid*& negHalfSolid);
    virtual Acad::ErrorStatus getSlice(AcDbSurface* pSurface,
        bool bGetNegHalfToo, AcDb3dSolid*& pNegHalfSolid);
    
    virtual Adesk::UInt32 numChanges() const;

    virtual Acad::ErrorStatus copyEdge(const AcDbSubentId &subentId,
        AcDbEntity *&newEntity);
    virtual Acad::ErrorStatus copyFace(const AcDbSubentId &subentId,
        AcDbEntity *&newEntity);
    virtual Acad::ErrorStatus extrudeFaces(
        const AcArray<AcDbSubentId *> &faceSubentIds, double height, 
        double taper);
    virtual Acad::ErrorStatus extrudeFacesAlongPath(
        const AcArray<AcDbSubentId *> &faceSubentIds, const AcDbCurve* path);
    virtual Acad::ErrorStatus imprintEntity(const AcDbEntity *pEntity);
    virtual Acad::ErrorStatus cleanBody();
    virtual Acad::ErrorStatus offsetBody(double offsetDistance);
    virtual Acad::ErrorStatus offsetFaces(
        const AcArray<AcDbSubentId *> &faceSubentIds, double offsetDistance);
    virtual Acad::ErrorStatus removeFaces(
        const AcArray<AcDbSubentId *> &faceSubentIds);
    virtual Acad::ErrorStatus separateBody(AcArray<AcDb3dSolid *> &newSolids);
    virtual Acad::ErrorStatus shellBody(
        const AcArray<AcDbSubentId *> &faceSubentIds, double offsetDistance);
    virtual Acad::ErrorStatus taperFaces(
        const AcArray<AcDbSubentId *> &faceSubentIds, 
        const AcGePoint3d &basePoint, const AcGeVector3d &draftVector,
        double draftAngle);
    virtual Acad::ErrorStatus transformFaces(
        const AcArray<AcDbSubentId *> &faceSubentIds,
        const AcGeMatrix3d &matrix);

    virtual Acad::ErrorStatus setSubentColor(const AcDbSubentId &subentId,
        const AcCmColor &color);
    virtual Acad::ErrorStatus getSubentColor(const AcDbSubentId &subentId,
        AcCmColor &color) const;

    virtual Acad::ErrorStatus setSubentMaterial(const AcDbSubentId &subentId,
                                                AcDbObjectId matId);
    virtual Acad::ErrorStatus getSubentMaterial(const AcDbSubentId &subentId,
                                                AcDbObjectId& matId) const;


    virtual Acad::ErrorStatus setSubentMaterialMapper(const AcDbSubentId &subentId,
                                                    const AcGiMapper& mapper);
    virtual Acad::ErrorStatus getSubentMaterialMapper(const AcDbSubentId &subentId,
                                                    AcGiMapper& mapper) const;



    virtual bool recordHistory() const;

    virtual Acad::ErrorStatus setRecordHistory(bool bRecord);

    virtual bool showHistory() const;

    virtual Acad::ErrorStatus setShowHistory(bool bShow);

    virtual Acad::ErrorStatus convertToBrepAtSubentPaths(
                                 const AcDbFullSubentPathArray& paths);

    virtual Acad::ErrorStatus chamferEdges(
                            const AcArray<AcDbSubentId *> &edgeSubentIds,
                            const AcDbSubentId& baseFaceSubentId, 
                            double baseDist, double otherDist);

    virtual Acad::ErrorStatus filletEdges(
                            const AcArray<AcDbSubentId *> &edgeSubentIds,
                            const AcGeDoubleArray& radius, 
                            const AcGeDoubleArray& startSetback, 
                            const AcGeDoubleArray& endSetback);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};

#pragma pack(pop)

#endif
