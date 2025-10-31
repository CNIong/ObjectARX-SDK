///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2008-2009 by Autodesk, Inc.
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
///////////////////////////////////////////////////////////////////////////////
//
// Name:        dbsubd.h
//
// Description: AcDbSubDMesh api class declaration
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "dbmain.h"

#pragma pack(push, 8)

class AcDbSurface;

///////////////////////////////////////////////////////////////////////////////
// class AcDbSubDMesh
//
class ACDB_PORT AcDbSubDMesh: public AcDbEntity
{
    ACDB_DECLARE_MEMBERS(AcDbSubDMesh);

public:
                                AcDbSubDMesh            ();
    virtual                    ~AcDbSubDMesh            ();

    ///////////////////////////////////////////////////////////////////////////
    // Methods for AcDbSubDMesh
    ///////////////////////////////////////////////////////////////////////////
    //
    Acad::ErrorStatus           setSubDMesh             (const AcGePoint3dArray& vertexArray,
                                                         const AcArray<Adesk::Int32>& faceArray,
                                                         int subDLevel);

    Acad::ErrorStatus           setSphere               (double radius,
                                                         int divAxis,
                                                         int divHeight,
                                                         int subDLevel);

    Acad::ErrorStatus           setCylinder             (double majorRadius,
                                                         double minorRadius,
                                                         double height,
                                                         int divAxis,
                                                         int divHeight,
                                                         int divCap,
                                                         int subDLevel);

    Acad::ErrorStatus           setCone                 (double majorRadius,
                                                         double minorRadius,
                                                         double height,
                                                         int divAxis,
                                                         int divHeight,
                                                         int divCap,
                                                         double radiusRatio,
                                                         int subDLevel);

    Acad::ErrorStatus           setTorus                (double majorRadius,
                                                         int divSection,
                                                         int divSweepPath,
                                                         double sectionRadiusRatio,
                                                         double sectionRotate,
                                                         int subDLevel);

    Acad::ErrorStatus           setBox                  (double xLen,
                                                         double yLen,
                                                         double zLen,
                                                         int divX,
                                                         int divY,
                                                         int divZ,
                                                         int subDLevel);

    Acad::ErrorStatus           setWedge                (double xLen,
                                                         double yLen,
                                                         double zLen,
                                                         int divLength,
                                                         int divWidth,
                                                         int divHeight,
                                                         int divSlope,
                                                         int divCap,
                                                         int subDLevel);

    Acad::ErrorStatus           setPyramid              (double radius,
                                                         double height,
                                                         int divLength,
                                                         int divHeight,
                                                         int divCap,
                                                         int nSides,
                                                         double radiusRatio,
                                                         int subDLevel);

    Acad::ErrorStatus           subdDivideUp            ();
    Acad::ErrorStatus           subdDivideDown          ();
    Acad::ErrorStatus           subdRefine              ();
    Acad::ErrorStatus           subdRefine              (const AcDbFullSubentPathArray& subentPaths);
    Acad::ErrorStatus           subdLevel               (Adesk::Int32& result) const;

    Acad::ErrorStatus           splitFace               (const AcDbSubentId& subentFaceId,
                                                         const AcDbSubentId& subent0,
                                                         const AcGePoint3d& point0,
                                                         const AcDbSubentId& subent1,
                                                         const AcGePoint3d& point1);

    Acad::ErrorStatus           extrudeFaces            (const AcDbFullSubentPathArray& subentPaths,
                                                         double length,
                                                         const AcGeVector3d& dir,
                                                         double taper);

    Acad::ErrorStatus           extrudeFaces            (const AcDbFullSubentPathArray& subentPaths,
                                                         const AcGePoint3dArray& alongPath,
                                                         double taper);

    Acad::ErrorStatus           isWatertight            (bool& result) const;

    Acad::ErrorStatus           numOfFaces              (Adesk::Int32& result) const;
    Acad::ErrorStatus           numOfSubDividedFaces    (Adesk::Int32& result) const;
    Acad::ErrorStatus           numOfSubDividedFacesAt  (const AcDbFullSubentPathArray& subentPaths, Adesk::Int32& result) const;
    Acad::ErrorStatus           numOfVertices           (Adesk::Int32& result) const;
    Acad::ErrorStatus           numOfSubDividedVertices (Adesk::Int32& result) const;
    Acad::ErrorStatus           numOfEdges              (Adesk::Int32& result) const;

    Acad::ErrorStatus           getVertices             (AcGePoint3dArray& vertexArray) const;
    Acad::ErrorStatus           getEdgeArray            (AcArray<Adesk::Int32>& edgeArray) const;
    Acad::ErrorStatus           getFaceArray            (AcArray<Adesk::Int32>& faceArray) const;
    Acad::ErrorStatus           getNormalArray          (AcGeVector3dArray& normalArray) const;

    Acad::ErrorStatus           getSubDividedVertices   (AcGePoint3dArray& vertexArray) const;
    Acad::ErrorStatus           getSubDividedFaceArray  (AcArray<Adesk::Int32>& faceArray) const;
    Acad::ErrorStatus           getSubDividedNormalArray(AcGeVector3dArray& normalArray) const;

    Acad::ErrorStatus           getVertexAt             (Adesk::Int32 nIndex, AcGePoint3d& vertex) const;
    Acad::ErrorStatus           setVertexAt             (Adesk::Int32 nIndex, const AcGePoint3d& vertex);
    Acad::ErrorStatus           getVertexAt             (const AcDbSubentId& id, AcGePoint3d& vertex) const;
    Acad::ErrorStatus           setVertexAt             (const AcDbSubentId& id, const AcGePoint3d& vertex);

    Acad::ErrorStatus           getSubDividedVertexAt   (Adesk::Int32 nIndex, AcGePoint3d& vertex) const;
    Acad::ErrorStatus           getSubDividedVertexAt   (const AcDbSubentId& id, AcGePoint3d& vertex) const;

    Acad::ErrorStatus           setCrease               (double creaseVal);
    Acad::ErrorStatus           setCrease               (const AcDbFullSubentPathArray& subentPaths, double creaseVal);
    Acad::ErrorStatus           getCrease               (const AcDbFullSubentPathArray& subentPaths, AcArray<double>& result) const;
    Acad::ErrorStatus           getCrease               (const AcDbSubentId& id, double& result) const;

    Acad::ErrorStatus           getAdjacentSubentPath   (const AcDbFullSubentPath& path,
                                                         AcDb::SubentType type,
                                                         AcDbFullSubentPathArray& subentPaths) const;

    Acad::ErrorStatus           getSubentPath           (Adesk::Int32 nIndex,
                                                         AcDb::SubentType type,
                                                         AcDbFullSubentPathArray& subentPaths) const;

    Acad::ErrorStatus           convertToSurface        (bool bConvertAsSmooth, const AcDbSubentId& id, AcDbSurface*& pSurface) const;
    Acad::ErrorStatus           convertToSurface        (bool bConvertAsSmooth, bool optimize, AcDbSurface*& pSurface) const;
    Acad::ErrorStatus           convertToSolid          (bool bConvertAsSmooth, bool optimize, AcDb3dSolid*& pSolid) const;

    Acad::ErrorStatus           getSubentColor          (const AcDbSubentId& id, AcCmColor& color) const;
    Acad::ErrorStatus           setSubentColor          (const AcDbSubentId& id, const AcCmColor& color);
    Acad::ErrorStatus           getSubentMaterial       (const AcDbSubentId& id, AcDbObjectId& material) const;
    Acad::ErrorStatus           setSubentMaterial       (const AcDbSubentId& id, const AcDbObjectId& material);
    Acad::ErrorStatus           getSubentMaterialMapper (const AcDbSubentId& id, AcGiMapper& mapper) const;
    Acad::ErrorStatus           setSubentMaterialMapper (const AcDbSubentId& id, const AcGiMapper& mapper);

    Acad::ErrorStatus           getFacePlane            (const AcDbSubentId& id, AcGePlane& facePlane) const;

    Acad::ErrorStatus           computeVolume           (double &retVolume) const;
    Acad::ErrorStatus           computeSurfaceArea      (double &retSurfArea) const;

    ///////////////////////////////////////////////////////////////////////////
    // Overridden methods from AcDbEntity
    ///////////////////////////////////////////////////////////////////////////
    //
    virtual void                dragStatus              (const AcDb::DragStat status);
    virtual Acad::ErrorStatus   subGetClassID           (CLSID* pClsid) const;

    ///////////////////////////////////////////////////////////////////////////
    // Overridden methods from AcGiDrawable
    ///////////////////////////////////////////////////////////////////////////
    //
    virtual bool                bounds                  ( AcDbExtents& retBounds ) const;

    ///////////////////////////////////////////////////////////////////////////
    // Internal use
    ///////////////////////////////////////////////////////////////////////////
    //
    Acad::ErrorStatus           setSphere               (const AcGeMatrix3d& xForm,
                                                         int divAxis,
                                                         int divHeight,
                                                         int subDLevel);

    Acad::ErrorStatus           setCylinder             (const AcGeMatrix3d& xForm,
                                                         int divAxis,
                                                         int divHeight,
                                                         int divCap,
                                                         int subDLevel);

    Acad::ErrorStatus           setCone                 (const AcGeMatrix3d& xForm,
                                                         int divAxis,
                                                         int divHeight,
                                                         int divCap,
                                                         double radiusRatio,
                                                         int subDLevel);

    Acad::ErrorStatus           setTorus                (const AcGeMatrix3d& xForm,
                                                         int divSection,
                                                         int divSweepPath,
                                                         double sectionRadiusRatio,
                                                         double sectionRotate,
                                                         int subDLevel);

    Acad::ErrorStatus           setBox                  (const AcGeMatrix3d& xForm,
                                                         int divX,
                                                         int divY,
                                                         int divZ,
                                                         int subDLevel);

    Acad::ErrorStatus           setWedge                (const AcGeMatrix3d& xForm,
                                                         int divLength,
                                                         int divWidth,
                                                         int divHeight,
                                                         int divSlope,
                                                         int divCap,
                                                         int subDLevel);

    Acad::ErrorStatus           setPyramid              (const AcGeMatrix3d& xForm,
                                                         int divLength,
                                                         int divHeight,
                                                         int divCap,
                                                         int nSides,
                                                         double radiusRatio,
                                                         int subDLevel);

    Acad::ErrorStatus           computeRayIntersection  (const AcGePoint3d  &rayStart, 
                                                         const AcGeVector3d &rayDir,    
                                                         AcArray<AcDbSubentId> &retSubents,
                                                         AcArray<double>       &retIntersectDist ) const;

};

///////////////////////////////////////////////////////////////////////////
//  Global API functions 
///////////////////////////////////////////////////////////////////////////
//
struct MeshFaceterSettings
{
    double faceterDevSurface;
    double faceterDevNormal;
    double faceterGridRatio;
    double faceterMaxEdgeLength;
    Adesk::UInt16 faceterMaxGrid;
    Adesk::UInt16 faceterMinUGrid;
    Adesk::UInt16 faceterMinVGrid;
    Adesk::Int16 faceterMeshType;
};

typedef struct MeshFaceterSettings  AcDbFaceterSettings;

ACDB_PORT  Acad::ErrorStatus acdbGetObjectMesh(AcDbObject *pObj, 
                                               const AcDbFaceterSettings *faceter,
                                               AcGePoint3dArray& vertexArray, 
                                               AcArray<Adesk::Int32>& faceArray,
                                               AcGiFaceData*& faceData); 

#pragma pack(pop)
