//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
// The AcDbRegion class is the interface class for representing
// regions inside AutoCAD.  All the functionality supported by
// this class is implemented in the class AcDbImpRegion and its
// base classes.

#ifndef GEOMENT_DBREGION_H
#define GEOMENT_DBREGION_H

#include "dbmain.h"
#include "dbsubeid.h"
#include "gepnt3d.h"
#include "gevec3d.h"

#pragma pack(push, 8)

class AcDbRegion: public  AcDbEntity
{
public:
    ACDB_PORT
    AcDbRegion();
    ACDB_PORT ~AcDbRegion();

    GEOMENT_DECLARE_MEMBERS(AcDbRegion);

    static  
    Acad::ErrorStatus createFromCurves(const AcDbVoidPtrArray& curveSegments, 
                                       AcDbVoidPtrArray& regions);


    /// <summary>
    /// This static member function creates AcDbRegion objects from the closed loops represented by the curves contained in the curveSegments array. 
    /// The newly created region objects are returned in the regions array. 
    /// </summary>
    /// <param name="curveSegments">
    /// An array of curves to be converted
    /// The objects in curveSegments must be opened for read and not for write. If the objects are opened for write, calling this function will crash AutoCAD. 
    /// The curveSegments array must contain only pointers to AcDbLine, AcDbArc, AcDbEllipse, AcDbCircle, AcDbSpline, AcDb3dPolyline, or AcDbPolyline objects. 
    /// </param>
    /// <param name="regions">
    /// Output array containing created AcDbRegion objects.
    /// It is the calling application's responsibility to either add the AcDbRegion objects returned in the regions array to an AcDbDatabase object or to delete them when they are no longer needed. 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if the function is completely successful.If there is any problem during the creation of an AcDbRegion object from any of the curves in curveSegments, then this function returns Acad::eInvalidInputand the regions array contains pointers to any AcDbRegion objects that were created before the error occurred.So, do not assume that a non - Acad::eOk return status indicates a total failure with no dynamically - allocated AcDbRegion objects returned.
    /// </returns>
    ACDB_PORT
    static
    Acad::ErrorStatus createFromCurves(const AcArray<AcDbEntity*>& curveSegments, AcArray<AcDbRegion*>& regions);


    virtual Acad::ErrorStatus getPerimeter(double&) const;
    virtual Acad::ErrorStatus getArea(double& regionArea) const;

    virtual void*             ASMBodyCopy(bool bDeepCopy = false) const; // INTERNAL USE ONLY
    virtual void const *      getLockedASMBody();                        // INTERNAL USE ONLY
    virtual void              unlockASMBody();                           // INTERNAL USE ONLY
    virtual void*             getLockedWritableASMBody();                // INTERNAL USE ONLY
    virtual void              commitWritableASMBody();                   // INTERNAL USE ONLY
    ACDB_PORT
    virtual Acad::ErrorStatus setASMBody(const void* modelerBody);       // INTERNAL USE ONLY

    virtual Acad::ErrorStatus getAreaProp(
                                 const AcGePoint3d&  origin,
                                 const AcGeVector3d& xAxis,
                                 const AcGeVector3d& yAxis,
                                 double&             perimeter,
                                 double&             area,
                                 AcGePoint2d&        centroid,
                                 double              momInertia[2],
                                 double&             prodInertia,
                                 double              prinMoments[2],
                                 AcGeVector2d        prinAxes[2],
                                 double              radiiGyration[2],
                                 AcGePoint2d&        extentsLow,
                                 AcGePoint2d&        extentsHigh)const;

    
    virtual Acad::ErrorStatus getPlane(AcGePlane& regionPlane) const;

    ACDB_PORT void dragStatus(const AcDb::DragStat) override;

    virtual Adesk::Boolean    isNull () const;
    virtual Acad::ErrorStatus getNormal(AcGeVector3d&) const;

    virtual AcDbSubentId      internalSubentId      (void* ent) const;                // INTERNAL USE ONLY
    virtual void*             internalSubentPtr     (const AcDbSubentId& id) const;   // INTERNAL USE ONLY
 
    virtual Acad::ErrorStatus booleanOper(AcDb::BoolOperType operation, AcDbRegion* otherRegion);

    virtual Adesk::UInt32 numChanges() const;
	
    ACDB_PORT virtual bool usesGraphicsCache();

    ACDB_PORT Acad::ErrorStatus getPlane(AcGePlane& plane, AcDb::Planarity& type) const override;

protected:
    
    Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

#pragma pack(pop)

#endif
