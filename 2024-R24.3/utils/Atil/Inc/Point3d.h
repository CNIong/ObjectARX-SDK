///////////////////////////////////////////////////////////////////////////////
//
// (C) Autodesk, Inc. 2007-2011. All rights reserved.
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
    Point3d( int valueX, int  valueY, int valueZ );

    ///<summary>The constructor.</summary>
    ///<param name='x'>The value to set into the X value.</param>
    ///<param name='y'>The value to set into the Y value.</param>
    ///<param name='z'>The value to set into the Z value.</param>
    Point3d( double valueX, double valueY, double valueZ );

    ///<summary>The destructor.</summary>
    ~Point3d() ;

    ///<summary>This sets the point.</summary>
    ///<param name='x'>The value to set into the X value.</param>
    ///<param name='y'>The value to set into the Y value.</param>
    ///<param name='z'>The value to set into the Z value.</param>
    ///<returns>A reference to "this".</returns>	
    const Point3d& set( int valueX, int  valueY, int valueZ );

    ///<summary>This sets the point.</summary>
    ///<param name='x'>The value to set into the X value.</param>
    ///<param name='y'>The value to set into the Y value.</param>
    ///<param name='z'>The value to set into the Z value.</param>
    ///<returns>A reference to "this".</returns>
    const Point3d& set( double valueX, double valueY, double valueZ );

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
