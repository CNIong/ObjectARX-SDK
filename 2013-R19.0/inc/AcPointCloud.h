//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
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
#include "AcString.h"

class AcPointCloudViewFrustum;
class IPointCloudFilter;

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
/// Point attributes definition
/// </summary>
class ACDB_PORT AcPcPointAttributes
{
public:
    /// <summary>Intensity, range 0 - 1</summary>
    float   m_intensity;
    /// <summary>Normal value</summary>
    float   m_nx, m_ny, m_nz;
    /// <summary>Classification value</summary>
    BYTE    m_classification;
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

    /// <summary>Return a array of point attributes.
    /// This may return NULL if the point cloud don't have such attributes.</summary>
    virtual AcPcPointAttributes* pointAttributes() = 0;

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
///
/// <remarks>
/// If indexing process starts asynchronously, in any derived class from
/// the callback class, developers shouldn't handle UI directly 
/// since it is still in the worker thread not main thread.
/// People need to marshal the calls to the main thread before doing UI.
/// </remarks>
class ACDB_PORT IAcPcIndexProgress {
public:
    /// <summary>
    /// This callback function indicates that the indexing process finishes
    /// with current progress and indexing result.
    /// </summary>
    /// <param name="progress">Current progress, range from 0.0 to 100.0</param>
    /// <param name="nResult">
    /// The result status of indexing:
    ///     Acad::eOk, index process successed
    ///     Acad::ePCInProgress, index process still works in progress
    ///     Acad::ePCUnknown ~ Acad::ePCNoEngineInfo, index process failed
    ///</param>
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
    /// <summary>
    /// Filter points to display
    /// </summary>
    ///
    /// <param name="inBuffer">The input buffer includes the original points</param>
    /// <param name="outBuffer">The output buffer includes the points after filtering</param>
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
/// <param name="newPointCloud">Created AcDbPointCloud entity, the caller responsible to destroy it</param>
/// <param name="indexFile">Point cloud index file</param>
/// <param name="sourceFile">Point cloud source file. This represent the original file
/// use to cerate the index. This entry can be blank.</param>
/// <param name="location">Location of point cloud entity. If entity is inserted at 
/// 0,0,0 the points will appear where they are located in the point cloud</param>
/// <param name="scale">Scale factor. 1.0 is default scale, and cannot less than 0.0</param>
/// <param name="rotation">Rotation Angle in degrees. 0 is default rotation</param>
///
/// <returns>
/// Returns Acad::eOk if successful
///</returns>
ACDB_PORT Acad::ErrorStatus acdbCreatePointCloudEntity(
    AcDbEntity*& newPointCloud,
    const AcString& indexFile, 
    const AcString& sourceFile, 
    AcGePoint3d&    location,
    double          scale = 1.0,
    double          rotation = 0.0);

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Attach a point cloud file into drawing as external reference item.
/// AcDbPointCloudObj.dbx must be loaded before this function is used.
/// </summary>
/// <param name="newPointCloud">Return the object id of created AcDbPointCloud entity
/// into destination database</param>
/// <param name="indexFile">Point cloud index file</param>
/// <param name="sourceFile">Point cloud source file. This represent the original file
/// use to cerate the index. This entry can be blank.</param>
/// <param name="location">Location of point cloud entity. If entity is inserted at 
/// 0,0,0 the points will appear where they are located in the point cloud</param>
/// <param name="scale">Scale factor. 1.0 is default scale, and cannot less than 0.0</param>
/// <param name="rotation">Rotation Angle in degrees. 0 is default rotation</param>
/// <param name="pDb">The destination database, use current working database if NULL</param>
///
/// <returns>
/// Returns Acad::eOk if successful
///</returns>
ACDB_PORT Acad::ErrorStatus acdbAttachPointCloudEntity(
    AcDbObjectId& newPointCloudId,
    const AcString& indexFile, 
    const AcString& sourceFile, 
    AcGePoint3d&    location,
    double          scale = 1.0,
    double          rotation = 0.0,
    AcDbDatabase*   pDb = NULL);

/// <summary>
/// Index a single scan file or merge multiple scan files to a point cloud.
/// The engine is selected by the output file format.
/// The input format must be supported by the engine for successful indexing.
/// AcDbPointCloudObj.dbx must be loaded before this function is used.
/// </summary>
/// <param name="inputFiles">The input scan file(s).
/// If the length is 1, index the scan file into a point cloud.
/// If the length is more than 1, merge scan files into a point cloud.</param>
/// <param name="outputFile">The output point cloud file. .PCG or .ISD.</param>
/// <param name="pCallback">Progress callback indicator for point cloud indexing.</param>
/// <param name="bAsync">Run index process asynchronously if true</param>
/// <param name="bImportColor">Import color attribute into point cloud file. PCG only.</param>
/// <param name="bImportIntensity">Import intensity attribute into the point cloud file. PCG only.</param>
/// <param name="bImportNormal">Import normal attribute into the point cloud file. PCG only.</param>
/// <param name="bCustom">Import custom attribute into the point cloud file. PCG only.</param>
///
/// <returns>
/// Returns Acad::eInvalidInput when the input or output files are empty or invalid
///         Acad::ePCInProgress when last index process is unfinished
///         Acad::eOk if indexing asynchronously, the result of asynchronous index
///                     should be got by call back indicator
///         Acad::eOk if indexing synchronously successes.
///         other: the actual result of synchronous indexing
///</returns>
ACDB_PORT Acad::ErrorStatus acpcIndexPointCloud(
    const AcStringArray& inputFiles,
    const AcString& outputFile,
    IAcPcIndexProgress* pCallback,
    bool bAsync = true,
    bool bImportColor = true,
    bool bImportIntensity = true,
    bool bImportNormal = false,
    bool bCustom = true);

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
/// <param name="pEnt">The destination point cloud entity.</param>
/// <param name="pFilter">The callback to filter point display</param>
/// 
/// <returns>
/// Returns Acad::eOk if successful
///</returns>
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
/// <param name="">The destination point cloud entity.</param>
/// 
/// <returns>
/// Returns Acad::eOk if successful
///</returns>
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
/// <param name="pEnt">The destination point cloud entity.</param>
/// <param name="ext">The extent area of interest for point extraction</param>
/// <param name="levelOfDetail">The percentage of the visiable points to be proccessed,
/// range from 0 to 100 </param>
/// <param name="pCallback">The callback of point processer</param>
/// 
/// <returns>
/// Returns Acad::eOk if successful
///</returns>
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
/// <param name="pEnt">The destination point cloud entity.</param>
/// <param name="frustum">The view frustum for defining area of interest for point extraction</param>
/// <param name="levelOfDetail">The percentage of the visiable points to be proccessed,
/// range from 0 to 100 </param>
/// <param name="pCallback">The callback of point processer</param>
/// 
/// <returns>
/// Returns Acad::eOk if successful
///</returns>
ACDB_PORT Acad::ErrorStatus acdbProcessPointCloudData(
    AcDbEntity* pEnt,
    const AcViewFrustum& frustum,
    int levelOfDetail,
    IAcPcPointProcessor* pCallback);

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Set a filter into point cloud engine of the given entity.
/// The filter works during engine reading points from data file.
/// </summary>
/// <param name="pEnt">The destination point cloud entity.</param>
/// <param name="pFilter">the customized filter which will be passed into engine,
/// remove custom filter in current engine if pass pFilter as NULL
/// It is the applications' responsibility to release the filter resource</param>
/// 
/// <returns>
/// Returns Acad::eOk if successful
///</returns>
///
/// <remarks>
/// NOTES:
///     If the point cloud entity has internal clipping filter already, the pFilter 
///     will be treated as one element of PointCloudIntersectionFilter
/// </remarks>
ACDB_PORT Acad::ErrorStatus acdbSetPointCloudFilter(
    AcDbEntity* pEnt,
    IPointCloudFilter* pFilter);

