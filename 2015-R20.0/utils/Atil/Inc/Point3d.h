//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2014 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif

#ifndef POINT3D_H
#define POINT3D_H

namespace Atil
{
///<summary> A simple three-dimensional point class. Point3d holds double X, Y, and Z values, all of which 
/// are public members. Consult Point3d.h for more information.</summary>
class Point3d 
{
public:
    ///<summary>The x value.</summary>
    double x;
    ///<summary>The y value.</summary>
    double y;
    ///<summary>The z value.</summary>
    double z;

public:
    ///<summary>The constructor.</summary>
    Point3d() ;

    ///<summary>The constructor.</summary>
    ///<param name='x'>The value to set into the X value.</param>
    ///<param name='y'>The value to set into the Y value.</param>
    ///<param name='z'>The value to set into the Z value.</param>
    Point3d( int x, int  y, int z );

    ///<summary>The constructor.</summary>
    ///<param name='x'>The value to set into the X value.</param>
    ///<param name='y'>The value to set into the Y value.</param>
    ///<param name='z'>The value to set into the Z value.</param>
    Point3d( double x, double y, double z );

    ///<summary>The destructor.</summary>
    ~Point3d() ;

    ///<summary>This sets the point.</summary>
    ///<param name='x'>The value to set into the X value.</param>
    ///<param name='y'>The value to set into the Y value.</param>
    ///<param name='z'>The value to set into the Z value.</param>
    ///<returns>A reference to "this".</returns>	
    const Point3d& set( int x, int  y, int z );

    ///<summary>This sets the point.</summary>
    ///<param name='x'>The value to set into the X value.</param>
    ///<param name='y'>The value to set into the Y value.</param>
    ///<param name='z'>The value to set into the Z value.</param>
    ///<returns>A reference to "this".</returns>
    const Point3d& set( double x, double y, double z );

    ///<summary>The eguals operator.</summary>
    ///<param name='rhs'>The <c>Point3d</c> to compare.</param>
    ///<returns>This returns true if the points match.</returns>
    bool operator==(const Point3d& rhs) const;

    ///<summary>The not eguals operator.</summary>
    ///<param name='rhs'>The <c>Point3d</c> to compare.</param>
    ///<returns>This returns true if the points don't match.</returns>
    bool operator!=(const Point3d& rhs) const;
};

} //end of namespace

#endif
