//
//
// (C) Copyright 2006-2008 by Autodesk, Inc.
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

#pragma once

#include "dbmain.h"

#pragma pack (push, 8)


class AcDbGeoData : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbGeoData);

    ACDB_PORT AcDbGeoData();
    ACDB_PORT virtual ~AcDbGeoData();
    
    ACDB_PORT AcDbObjectId blockTableRecordId() const;
    ACDB_PORT Acad::ErrorStatus setBlockTableRecordId(const AcDbObjectId& blockId);
    
    ACDB_PORT double latitude() const;
    ACDB_PORT  Acad::ErrorStatus setLatitude(double value);

    ACDB_PORT double longitude() const;
    ACDB_PORT Acad::ErrorStatus setLongitude(double value);

    ACDB_PORT double elevation() const;
    ACDB_PORT Acad::ErrorStatus setElevation(double value);

    ACDB_PORT AcDb::UnitsValue dwgUnits() const;
    ACDB_PORT Acad::ErrorStatus setDwgUnits(AcDb::UnitsValue value);

    ACDB_PORT AcGePoint3d dwgPoint() const;
    ACDB_PORT Acad::ErrorStatus setDwgPoint(const AcGePoint3d& pt);   

    ACDB_PORT AcGeVector3d upDirection() const;
    ACDB_PORT Acad::ErrorStatus setUpDirection(const AcGeVector3d& vec);   
    
    ACDB_PORT double northDirection() const;
    ACDB_PORT Acad::ErrorStatus setNorthDirection(double value);

    ACDB_PORT AcGeVector3d northDirectionVector() const;

    ACDB_PORT int numMeshPoints() const;
    ACDB_PORT Acad::ErrorStatus getMeshPointMap(int index, 
                                   AcGePoint2d& sourcePt,
                                   AcGePoint2d& destPt) const;
    ACDB_PORT Acad::ErrorStatus getMeshPointMaps(AcGePoint2dArray& sourcePts,
                                   AcGePoint2dArray& destPts) const;

    ACDB_PORT Acad::ErrorStatus addMeshPointMap(int index, 
                                   const AcGePoint2d& sourcePt,
                                   const AcGePoint2d& destPt);
    ACDB_PORT Acad::ErrorStatus setMeshPointMaps(
                                   const AcGePoint2dArray& sourcePts,
                                   const AcGePoint2dArray& destPts);
    ACDB_PORT Acad::ErrorStatus resetMeshPointMaps();

    ACDB_PORT int numMeshFaces() const;
    ACDB_PORT Acad::ErrorStatus getMeshFace(int faceIndex, 
                                   int& p0,
                                   int& p1,
                                   int& p2) const;
    ACDB_PORT Acad::ErrorStatus addMeshFace(int faceIndex, 
                                   int p0,
                                   int p1,
                                   int p2);

    ACDB_PORT bool  isForeignCoordinateSystem() const;
    ACDB_PORT Acad::ErrorStatus setIsForeignCoordinateSystem(bool value);

    ACDB_PORT double coordinateSystemMapUnits() const;
    ACDB_PORT Acad::ErrorStatus setCoordinateSystemMapUnits(double value); 

    ACDB_PORT const ACHAR* coordinateSystemDescription() const;
    ACDB_PORT Acad::ErrorStatus setCoordinateSystemDescription(const ACHAR* pDesc);

    ACDB_PORT const ACHAR* coordinateSystemDatumName() const;
    ACDB_PORT Acad::ErrorStatus setCoordinateSystemDatumName(const ACHAR* pDatum);

    ACDB_PORT const ACHAR* coordinateSystemWKT() const;
    ACDB_PORT Acad::ErrorStatus setCoordinateSystemWKT(const ACHAR* pWkt);

    ACDB_PORT const ACHAR* observationFrom() const;
    ACDB_PORT Acad::ErrorStatus setObservationFrom(const ACHAR* pFrom);

    ACDB_PORT const ACHAR* observationTo() const;
    ACDB_PORT Acad::ErrorStatus setObservationTo(const ACHAR* pTo);

    ACDB_PORT const ACHAR* observationCoverage() const;
    ACDB_PORT Acad::ErrorStatus setObservationCoverage(const ACHAR* pCoverage);

    ACDB_PORT const ACHAR* geoRSSTag() const;
    ACDB_PORT Acad::ErrorStatus setGeoRSSTag(const ACHAR* pTag);    
    
    ACDB_PORT Acad::ErrorStatus postToDb(AcDbObjectId& objId);
    ACDB_PORT Acad::ErrorStatus eraseFromDb(void); 

    ACDB_PORT Acad::ErrorStatus updateTransformationMatrix();

    ACDB_PORT Acad::ErrorStatus transformToLonLatAlt(const AcGePoint3d& dwgPt,
                                                     AcGePoint3d& geoPt) const;
    ACDB_PORT Acad::ErrorStatus transformToLonLatAlt(double x,
                                                     double y, 
                                                     double z,
                                                     double &lon,  
                                                     double &lat, 
                                                     double &alt) const;

    ACDB_PORT Acad::ErrorStatus transformFromLonLatAlt(const AcGePoint3d& geoPt,
                                                       AcGePoint3d& dwgPt) const;
    ACDB_PORT Acad::ErrorStatus transformFromLonLatAlt(double lon,
                                                       double lat, 
                                                       double alt,
                                                       double &x,  
                                                       double &y, 
                                                       double &z) const;

    //********************************************************************
    // Methods for Civil3D data
    //********************************************************************
    //
    // scaling parameters
    enum ScaleEstimationMethod {
        kScaleEstMethodUnity = 1,
        kScaleEstMethodUserDefined,
        kScaleEstMethodReferencePoint,
        kScaleEstMethodPrismoidal
    };
    
    ACDB_PORT bool doLocalToGridTransform(void) const;
    ACDB_PORT Acad::ErrorStatus setDoLocalToGridTransform(bool value);

    ACDB_PORT AcGePoint2d localReferencePoint(void) const;
    ACDB_PORT Acad::ErrorStatus setLocalReferencePoint(const AcGePoint2d& pt);

    ACDB_PORT AcGePoint2d gridReferencePoint(void) const;
    ACDB_PORT Acad::ErrorStatus setGridReferencePoint(const AcGePoint2d& pt);

    ACDB_PORT Adesk::UInt32 localReferencePointNumber(void) const;
    ACDB_PORT Acad::ErrorStatus setLocalReferencePointNumber(Adesk::UInt32 value);

    ACDB_PORT Adesk::UInt32 gridReferencePointNumber(void) const;
    ACDB_PORT Acad::ErrorStatus setGridReferencePointNumber(Adesk::UInt32 value);
    
    ACDB_PORT bool useRotationPoint(void) const;
    ACDB_PORT Acad::ErrorStatus setUseRotationPoint(bool value);

    ACDB_PORT AcGePoint2d localRotationPoint(void) const;
    ACDB_PORT Acad::ErrorStatus setLocalRotationPoint(const AcGePoint2d& pt);

    ACDB_PORT AcGePoint2d gridRotationPoint(void) const;
    ACDB_PORT Acad::ErrorStatus setGridRotationPoint(const AcGePoint2d& pt);

    ACDB_PORT double localToGridRotation(void) const;
    ACDB_PORT Acad::ErrorStatus setLocalToGridRotation(double value);

    ACDB_PORT double gridAzimuth(void) const;
    ACDB_PORT Acad::ErrorStatus setGridAzimuth(double value);

    ACDB_PORT AcDbGeoData::ScaleEstimationMethod scaleEstimationMethod(void) const;
    ACDB_PORT Acad::ErrorStatus setScaleEstimationMethod(AcDbGeoData::ScaleEstimationMethod value);

    ACDB_PORT double scaleFactor(void) const;
    ACDB_PORT Acad::ErrorStatus setScaleFactor(double value);

    ACDB_PORT bool doSeaLevelCorrection(void) const;
    ACDB_PORT Acad::ErrorStatus setDoSeaLevelCorrection(bool value);

    ACDB_PORT double seaLevelElevation(void) const;
    ACDB_PORT Acad::ErrorStatus setSeaLevelElevation(double value);

    ACDB_PORT double coordinateProjectionRadius(void) const;
    ACDB_PORT Acad::ErrorStatus setCoordinateProjectionradius(double value);

    
    //********************************************************************
    // Overridden methods from AcDbObject
    //********************************************************************
    //
    ACDB_PORT virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;

    ACDB_PORT virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;

};


//************************************************************************
//  Global API functions 
//************************************************************************
//
ACDB_PORT Acad::ErrorStatus acdbGetGeoDataObjId(AcDbDatabase *pDb, AcDbObjectId& objId);

#pragma pack (pop)

