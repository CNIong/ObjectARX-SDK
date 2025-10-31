//
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2009-2011  by Autodesk, Inc.
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
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//////////////////////////////////////////////////////////////////////////////
//
// Name:            AcPointCloud.h
//
// Description:     Api for AcDbPointCloud
//                  NOTE:
//                  AcDbPointCloudObj.dbx must be loaded before any of these
//                  functions and classes are used.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "rxobject.h"

class AcPointCloudViewFrustum;

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// View frustum for defining area of interest for point extraction.
/// </summary>
class ACDB_PORT AcViewFrustum
{
public:
    AcViewFrustum();
    ~AcViewFrustum();

    void setNearUpperRight(double x, double y, double z);
    void setNearUpperLeft(double x, double y, double z);
    void setNearLowerLeft(double x, double y, double z);
    void setNearLowerRight(double x, double y, double z);

    void setFarUpperRight(double x, double y, double z);
    void setFarUpperLeft(double x, double y, double z);
    void setFarLowerLeft(double x, double y, double z);
    void setFarLowerRight(double x, double y, double z);

    void nearUpperRight(double& x, double& y, double& z) const;
    void nearUpperLeft(double& x, double& y, double& z) const;
    void nearLowerLeft(double& x, double& y, double& z) const;
    void nearLowerRight(double& x, double& y, double& z) const;

    void farUpperRight(double& x, double& y, double& z) const;
    void farUpperLeft(double& x, double& y, double& z) const;
    void farLowerLeft(double& x, double& y, double& z) const;
    void farLowerRight(double& x, double& y, double& z) const;

    void setNearClip(bool clip);
    bool nearClip() const;

    void setFarClip(bool clip);
    bool farClip() const;

    AcPointCloudViewFrustum* asPointCloudFrustum() const;
private:
    void* m_pData;
};

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Point definition for single precision points
/// </summary>
class ACDB_PORT AcPcPointFloat {
public:
    /// <summary>Position</summary>
    float m_x, m_y, m_z;
    /// <summary>
    /// Color format: 0xAARRGGBB
    /// Alpha needs to be >0 for the points to be visible
    /// Example colors:
    /// 0xffff0000 - Red
    /// 0xff000000 - Black
    /// 0xffffffff - White
    /// </summary>
    DWORD m_argb;
};

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Point definition for double precision points
/// </summary>
class ACDB_PORT AcPcPointDouble {
public:
    /// <summary>Position</summary>
    double m_x, m_y, m_z;
    /// <summary>
    /// Color format: 0xAARRGGBB
    /// Alpha needs to be >0 for the points to be visible
    /// Example colors:
    /// 0xffff0000 - Red
    /// 0xff000000 - Black
    /// 0xffffffff - White
    /// </summary>
    DWORD m_argb;
};

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Data buffer for points returned from the point cloud engine.
/// Points returned in the data buffer will be in local point cloud space.
/// To convert the points to world space you need to first add the XYZ offset
/// to the point and then transform the point using the entityTransform.
/// Example:
///
///     AcPcPointFloat p;
///     pBuffer->floatPoint(pointIndex, p);
///     double offsetX, offsetY, offsetZ;
///     pBuffer->offset(offsetX, offsetY, offsetZ);
///     AcGeMatrix3d xform;
///     pBuffer->entityTransform(xform);
///     AcGePoint3d pt(p->m_x+offsetX, p->m_y+offsetY, p->m_z+offsetZ);
///     pt = xform*pt; // Point is now in world space
///
/// </summary>
class ACDB_PORT IAcPcDataBuffer {
public:
    virtual ~IAcPcDataBuffer()              = 0 {};

    ///<summary>Indicate if the points are in single or double precision.</summary>
    virtual bool nativeDbl()                = 0;
    ///<summary>Resize the buffer. This may be a destructive operation.</summary>
    virtual bool resize(DWORD size)         = 0;
    ///<summary>Shrink the buffer without destroying its contents.</summary>
    virtual bool shrink(DWORD size)         = 0;
    /// <summary>Return the number of points in the buffer.</summary>
    virtual DWORD size() const              = 0;

    /// <summary>Return a array of single precision points.
    /// This may return NULL if the buffer is not single precision.</summary>
    virtual AcPcPointFloat*  floatPoints () = 0;
    /// <summary>Return a array of double precision points.
    /// This may return NULL if the buffer is not double precision.</summary>
    virtual AcPcPointDouble* doublePoints() = 0;

    /// <summary>Return a point in single precision.
    /// This will work regardless of the native precision of the buffer.</summary>
    virtual bool floatPoint  (DWORD ptIx, AcPcPointFloat&  pt) const    = 0;
    /// <summary>Return a point in double precision.
    /// This will work regardless of the native precision of the buffer.</summary>
    virtual bool doublePoint (DWORD ptIx, AcPcPointDouble& pt) const    = 0;

    /// <summary>Set a point in single precision.
    /// This will work regardless of the native precision of the buffer.</summary>
    virtual bool setFloatPoint  (DWORD ptIx, AcPcPointFloat&  pt)       = 0;
    /// <summary>Set a point in double precision.
    /// This will work regardless of the native precision of the buffer.</summary>
    virtual bool setDoublePoint (DWORD ptIx, AcPcPointDouble& pt)       = 0;

    /// <summary>Get the translation offset of the points.
    /// This offset needs to be added to each point in order to get the 
    /// original location of the point in the point cloud</summary>
    virtual bool offset   (double& x, double& y, double& z) const       = 0;
    /// <summary>This transform needs to be applied to the points to
    /// get the points in world space.</summary>
    virtual bool entityTransform(AcGeMatrix3d& matrix) const            = 0;

    /// <summary>Copy the contents of the given buffer.</summary>
    virtual void copyFrom(IAcPcDataBuffer const & from)                 = 0;
};


//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Progress callback indicator for point cloud indexing. 
/// </summary>
/// <Notes>
/// If indexing process starts asynchronously, in any derived class from
/// the callback class, developers shouldn't handle UI directly 
/// since it is still in the worker thread not main thread.
/// People need to marshal the calls to the main thread before doing UI.
/// </Notes>
class ACDB_PORT IAcPcIndexProgress {
public:
    /// <summary>
    /// This callback function indicates that the indexing process finishes
    /// with current progress and indexing result.
    /// </summary>
    virtual void finished(float progress, Acad::ErrorStatus nResult) = 0;
};


//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Callback class to filter point display.
/// The original points are provided in the inBuffer.
/// The resulting points are placed into the outBuffer.
/// Points can be added, removed, or modified. Any resulting point in the
/// outBuffer will be displayed.
/// </summary>
class ACDB_PORT IAcPcPointFilter {
public: 
    virtual void doFilter(
        const IAcPcDataBuffer& inBuffer, 
        IAcPcDataBuffer&       outBuffer) = 0;
};

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Point processor. This class let you extract points from the drawing for
/// export or interrogation purposes. These operations do not affect the
/// current point display.
/// </summary>
class ACDB_PORT IAcPcPointProcessor {
public:
    /// <summary>Return true to cancel processing.</summary>
    virtual bool cancel()   = 0;  

    /// <summary>Called to abort the process</summary>
    virtual void abort()    = 0; 

    /// <summary>Called after the last call to ProcessPoints</summary>
    virtual void finished() = 0;

    /// <summary>Process point in buffer. This will be called repeatedly with 
    /// new buffer contents until all points have been processed.</summary>
    virtual bool processPoints() = 0; 

    /// <summary>Filter, if available, to filter points.
    /// Called before processPoints() on the next batch of points.</summary>
    virtual IAcPcPointFilter*  filter() = 0;

    /// <summary>The buffer used to store points</summary>
    IAcPcDataBuffer* buffer();

    /// <summary>For internal use</summary>
    void setBuffer(IAcPcDataBuffer* buffer);

private:
    IAcPcDataBuffer* mpBuffer;
};

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Create an AcDbPointCloud entity.
/// AcDbPointCloudObj.dbx must be loaded before this function is used.
/// </summary>
ACDB_PORT Acad::ErrorStatus acdbCreatePointCloudEntity(
	/// <summary>Created AcDbPointCloud entity, the caller responsible to destroy it</summary>
	AcDbEntity*& newPointCloud,
    /// <summary>Point cloud index file.</summary>
    const AcString& indexFile, 
    /// <summary>Point cloud source file. This represent the original file use
    /// to cerate the index. This entry can be blank.</summary>
    const AcString& sourceFile, 
    /// <summary>Location of point cloud entity. If entity is inserted at 
    /// 0,0,0 the points will appear where they are located in the point cloud.
    ///</summary>
    AcGePoint3d&    location,
    /// <summary>Scale factor. 1.0 is default scale, and cannot less than 0.0</summary>
    double          scale = 1.0,
    /// <summary>Rotation Angle in degrees. 0 is default rotation</summary>
    double          rotation = 0.0);

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Index a point cloud.
/// The engine is selected by the output file format.
/// The input format must be supported by the engine for successful indexing.
/// AcDbPointCloudObj.dbx must be loaded before this function is used.
/// </summary>
ACDB_PORT Acad::ErrorStatus acpcIndexPointCloud(
    const AcString& inputFile,
    const AcString& outputFile,
    IAcPcIndexProgress* pCallback);

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Modify point cloud data view.
/// This function allows a filter to be inserted into the display pipeline 
/// of point cloud objects. This filter can inspect and modify the point set
/// before they are displayed. 
/// If the entity is already in a database, this will cause a redisplay with
/// the modified point set.
/// It is the applications responsibility to remove any filter added
/// by using acdbResetPointCloudDataView()
/// AcDbPointCloudObj.dbx must be loaded before this function is used.
/// </summary>
ACDB_PORT Acad::ErrorStatus acdbModifyPointCloudDataView(
    AcDbEntity* pEnt,
    IAcPcPointFilter* pFilter
    );

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Clear the filter from the given entity.
/// Any filter added to a point cloud entity needs to be removed using this
/// function.
/// AcDbPointCloudObj.dbx must be loaded before this function is used.
/// </summary>
ACDB_PORT Acad::ErrorStatus acdbResetPointCloudDataView(
    AcDbEntity* pEnt
    );


//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Select a set of points within the point cloud entity.
/// This function does not modify the points or affect the display of the given
/// entity. 
/// The points within the given extents will be passed to the callback for
/// processing. Points will be extracted from the point cloud engine with the
/// selected level of detail (the POINTCLOUDDENSITY sysvar is not honored),
/// and the processPoints() function in the callback will be called repeatedly
/// as the buffer is filled up until all points have been processed.
/// The buffer will be sized so that no unreasonable memory pressure is put on
/// the system.
/// Note that there is no clipping performed after extracting the points so
/// it is likely that a number of points outside the given extents will be
/// returned. The actual extents of the points returned depend on the
/// point cloud engine being used.
/// AcDbPointCloudObj.dbx must be loaded before this function is used.
/// </summary>
ACDB_PORT Acad::ErrorStatus acdbProcessPointCloudData(
    AcDbEntity* pEnt,
    const AcDbExtents& ext,
    int levelOfDetail,
    IAcPcPointProcessor* pCallback);

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Select a set of points within the point cloud entity.
/// This function does not modify the points or affect the display of the given
/// entity. 
/// The points within the given extents will be passed to the callback for
/// processing. Points will be extracted from the point cloud engine with the
/// selected level of detail (the POINTCLOUDDENSITY sysvar is not honored),
/// and the processPoints() function in the callback will be called repeatedly
/// as the buffer is filled up until all points have been processed.
/// The buffer will be sized so that no unreasonable memory pressure is put on
/// the system.
/// Note that there is no clipping performed after extracting the points so
/// it is likely that a number of points outside the given view frustum will be
/// returned. The actual extents of the points returned depend on the
/// point cloud engine being used.
/// AcDbPointCloudObj.dbx must be loaded before this function is used.
/// </summary>
ACDB_PORT Acad::ErrorStatus acdbProcessPointCloudData(
    AcDbEntity* pEnt,
    const AcViewFrustum& frustum,
    int levelOfDetail,
    IAcPcPointProcessor* pCallback);
