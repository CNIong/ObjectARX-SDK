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

#pragma once
#include "acdbport.h"

/// <summary>
/// Implement this interface to define the volume of interest within the point cloud
/// when this volume of interest is more complex than a view frustum.
/// Efficiency of the implementation of this interface can critically affect 
/// performance of the point cloud access queries.
/// </summary>
class ACDB_PORT IPointCloudFilter
{
public:
    /// <summary>
    /// This method should check whether the cell, i.e. a box aligned with xyz axes,
    /// is inside, outside or on the border of the volume of interest.
    /// </summary>
    /// <param name="minX">Min X coordinate value of the test cell</param>
    /// <param name="minY">Min Y coordinate value of the test cell</param>
    /// <param name="minZ">Min Z coordinate value of the test cell</param>
    /// <param name="maxX">Max X coordinate value of the test cell</param>
    /// <param name="maxY">Max Y coordinate value of the test cell</param>
    /// <param name="maxZ">Max Z coordinate value of the test cell</param>
    ///
    /// <returns>
    /// Expected return values are -1, 0, or 1:
    /// -1 -- the box is rejected (outside the volume of interest)
    ///  1 -- the box is fully accepted (entire box is inside the volume of interest)
    ///  0 -- the box partially belongs to the volume of interest.
    /// </returns>
    ///
    /// <remarks>
    /// Note: If your filter does not support individual point filtering, you
    /// should only return -1 or 1 here.
    /// </remarks>
    virtual int testCell(double minX, double minY, double minZ,
                        double maxX, double maxY, double maxZ) const = 0;

    /// <summary>
    /// Test if the point is inside the volume of interest
    /// </summary>
    /// <param name="x">X coordinate value of the test point</param>
    /// <param name="y">Y coordinate value of the test point</param>
    /// <param name="z">Z coordinate value of the test point</param>
    ///
    /// <returns>
    /// 'true'  -- if it is accepted.
    /// 'false' -- if it is rejected.
    ///</returns>
    ///
    /// <remarks>
    /// Note: This function will be called once for every point in the cells that
    /// are intersected (testCell() returned 0) so it needs to be very fast.
    /// </remarks>
    virtual bool testPoint(float x, float y, float z) const = 0;

    /// <summary>
    /// This is an optimization hook that the implementer may ignore.
    /// The engine calls this method to promise to the IPointCloudFilter object that
    /// all following testCell() and acceptPoint() queries will be for cells and points
    /// within the (min, max) box specified here.
    /// This is until the next call to prepareForCell(). 
    /// </summary>
    /// <param name="minX">Min X coordinate value of the test cell</param>
    /// <param name="minY">Min Y coordinate value of the test cell</param>
    /// <param name="minZ">Min Z coordinate value of the test cell</param>
    /// <param name="maxX">Max X coordinate value of the test cell</param>
    /// <param name="maxY">Max Y coordinate value of the test cell</param>
    /// <param name="maxZ">Max Z coordinate value of the test cell</param>
    /// <param name="numTests">approximate number of testPoint() calls that the engine
    /// is going to make before the next such call</param>
    virtual void prepareForCell(double& minX, double& minY, double& minZ,
                                double& maxX, double& maxY, double& maxZ,
                                long numTests)
    {
        UNREFERENCED_PARAMETER(minX);
        UNREFERENCED_PARAMETER(minY);
        UNREFERENCED_PARAMETER(minZ);
        UNREFERENCED_PARAMETER(maxX);
        UNREFERENCED_PARAMETER(maxY);
        UNREFERENCED_PARAMETER(maxZ);
        UNREFERENCED_PARAMETER(numTests);
    };

    /// <summmary>
    /// This function creates a clone of the filter and returns a pointer to the clone
    /// The filter will always be cloned before it's used.
    /// The filter may be cloned multiple times if multithreaded filtering is enabled.
    /// </summmary>
    ///
    /// <returns>
    /// Return a copy of the filter.
    /// </returns>
    virtual IPointCloudFilter* clone() const = 0;

    /// <summmary>
    /// The engine will call this when it is done with a filter.
    /// This should delete the filter.
    /// Typically this would be implemented using 'delete this;'.
    /// </summmary>
    virtual void freeObject(void) = 0;

    /// <summmary>
    /// Returns a bool value indicating whether the filter is inverted.
    /// The default value is false.
    /// </summmary>
    ///
    /// <returns>ture if the filter is inverted</returns>
    virtual bool isInverted() const
    {
        return false;
    }

    /// <summmary>
    /// Set the filter as inverted or not, then we can get opposite result of original filter
    /// </summmary>
    /// <param name="bInverted">a bool value indicating whether the filter is inverted</param>
    virtual void setIsInverted(bool bInverted)
    {
        UNREFERENCED_PARAMETER(bInverted);
    }

};
