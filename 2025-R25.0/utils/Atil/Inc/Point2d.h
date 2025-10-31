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
#ifndef VECTOR2D_H
namespace Atil { class Vector2d; }
#endif
#ifndef MATRIX2D_H
namespace Atil { class Matrix2d; }
#endif

#ifndef POINT2D_H
#define POINT2D_H

namespace Atil
{
/// <summary>
/// The <c>Point2d</c> class defines a point in Cartesian space. This contrasts with the
/// <c>Offset</c> class which defines an offset from the image coordinate system origin.
/// </summary>
///
/// <remarks>
/// This class works together with the <c>Vector2d</c>,
/// <see cref="Vector2d"/> and <c>Matrix2d</c> <see cref="Matrix2d"/>.
/// </remarks>
class Point2d
{
// The members x and y are deliberately public to facilitate easy use.
// This also implies that the x and y members of this class will not change.
//
public:
    /// <summary> The x coordinate in floating point image space.
    /// </summary>
    double x;
    /// <summary> The y coordinate in floating point image space.
    /// </summary>
    double y;

public:
    /// <summary>
    /// Empty or blank constructor.
    /// </summary>
    ///
    Point2d ();
    /// <summary>
    /// An integer setting constructor. The <c>x</c> and <c>y</c> members will
    /// be set to the integer arguments.
    /// </summary>
    ///
    /// <param name= 'x'>
    /// The integer x coordinate.
    /// </param>
    ///
    /// <param name= 'y'>
    /// The integer y coordinate.
    /// </param>
    ///
    Point2d ( int valueX, int  valueY );
    /// <summary>
    /// An double setting constructor. The <c>x</c> and <c>y</c> members will
    /// be set to the double arguments.
    /// </summary>
    ///
    /// <param name= 'x'>
    /// The double x coordinate.
    /// </param>
    ///
    /// <param name= 'y'>
    /// The double y coordinate.
    /// </param>
    ///
    Point2d ( double valueX, double valueY );

    /// <summary> The destructor.
    /// </summary>
    ~Point2d ();

    /// <summary>
    /// This method sets the <c>x</c> and <c>y</c> members to the input values.
    /// </summary>
    /// 
    /// <param name="x">The value to be set into the <c>x</c> member.
    /// </param>
    /// 
    /// <param name="y">The value to be set into the <c>y</c> member.
    /// </param>
    ///
    /// <returns>
    /// This will return a const reference to <c>*this</c>.
    /// </returns>
    ///
    const Point2d& set ( int valueX, int  valueY );

    /// <summary>
    /// This method sets the <c>x</c> and <c>y</c> members to the input values.
    /// </summary>
    /// 
    /// <param name="x">The value to be set into the <c>x</c> member.
    /// </param>
    /// 
    /// <param name="y">The value to be set into the <c>y</c> member.
    /// </param>
    ///
    /// <returns>
    /// This will return a const reference to <c>*this</c>.
    /// </returns>
    ///   
    const Point2d& set ( double valueX, double valueY );
    
    /// <summary>
    /// This method will multiply the point by the matrix within the
    /// <c>Matrix2d</c> reference. <see cref="Matrix2d"/>
    /// </summary>
    ///
    /// <param name="leftSide">This is the matrix to multiply the point members
    /// by. 
    /// </param>
    ///
    /// <returns>
    /// This will return a reference to <c>*this</c>.
    /// </returns>
    ///
    Point2d& transformBy (const Matrix2d& leftSide);

    /// <summary>
    /// This method will calculate the euclidean distance between this point
    /// and the argument.
    /// </summary>
    ///
    /// <param name="ipPoint">The point to calculate the distance to.
    /// </param>
    ///
    /// <returns>
    /// This returns the distance to the argument as a double.
    /// </returns>
    ///
    double distance( const Point2d& ipPoint ) const;

    /// <summary>
    /// This method subtracts the argument's values from the members and returns
    /// the result as a <c>Vector2d</c>
    /// </summary>
    ///
    /// <param name='rhs'> The value to be operated with. </param>
    ///
    /// <returns>
    /// This subtraction results in a <c>Vector2d</c> that describes the delta
    /// from this point and the argument.
    /// </returns>
    ///
    Vector2d operator-(const Point2d& rhs) const;

    /// <summary>
    /// This adds the offset specified in the <c>Vector2d</c> argument to
    /// the members.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be operated with. </param>
    ///
    /// <returns>
    /// This method returns a new <c>Point2d</c> object with the result.
    /// </returns>
    ///
    Point2d operator+(const Vector2d& rhs) const;

    /// <summary>
    /// This adds the offset specified in the <c>Vector2d</c> argument to
    /// the members and sets the <c>Point2d</c> to the result.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be operated with. </param>
    ///
    /// <returns>
    /// This will return a reference to <c>*this</c>.
    /// </returns>
    ///
    Point2d& operator+=(const Vector2d& rhs);

    /// <summary>
    /// The equals operator will return true if both the <c>x</c> and <c>y</c> members
    /// are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be operated with. </param>
    ///
    /// <returns>
    /// This will return true of the points are equivalent.
    /// </returns>
    ///
    bool operator==(const Point2d& rhs) const;

    /// <summary>
    /// The equals operator will return false if both the <c>x</c> and <c>y</c> members
    /// are equal.
    /// </summary>
    ///
    /// <param name='rhs'> The value to be operated with. </param>
    ///
    /// <returns>
    /// This will return true of the points are not equivalent.
    /// </returns>
    ///
    bool operator!=(const Point2d& rhs) const;
};


} // end of namespace Atil

#endif
