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

#ifndef POINT2D_H
namespace Atil { class Point2d; }
#endif
#ifndef MATRIX2D_H
namespace Atil { class Matrix2d; }
#endif

#ifndef VECTOR2D_H
#define VECTOR2D_H

namespace Atil
{

/// <summary>
/// This class holds a two dimensional vector in Cartesian coordinates.
/// It interacts with the <c>Matrix2d</c> and <c>Point2d</c> classes.
/// </summary>
///
class Vector2d 
{
public:
    /// <summary>The x offset.
    /// </summary>
    double x;
    /// <summary>The y offset.
    /// </summary>
    double y;

    /// <summary>
    /// The default (empty) constructor.
    /// </summary>
    ///
    Vector2d ();

    /// <summary>
    /// The initializing constructor.
    /// </summary>
    ///
    /// <param name="dx">This value will be set as the <c>x</c> member.
    /// </param>
    ///
    /// <param name="dy">This value will be set as the <c>y</c> member.
    /// </param>
    ///    
    Vector2d ( double valueX, double valueY );

    /// <summary>
    /// The copy constructor.
    /// </summary>
    ///
    /// <param name='x'> The instance to be copied. </param>
    ///
    Vector2d ( const Vector2d& xy );

    /// <summary>
    /// The destructor.
    /// </summary>
    ///
    virtual ~Vector2d ();

    /// <summary>
    /// This method will over write the current members with values from the argument.
    /// </summary>
    /// 
    /// <param name="v2d">A constant reference to a <c>Vector2d</c> instance that will be
    /// referenced for the <c>x</c> and <c>y</c> member values to be set.
    /// </param>
    ///
    virtual const Vector2d& set ( const Vector2d& v2d );

    /// <summary>
    /// This method will over write the current members with values from the arguments.
    /// </summary>
    ///
    /// <param name="dx">This value will be set as the <c>x</c> member.
    /// </param>
    ///
    /// <param name="dy">This value will be set as the <c>y</c> member.
    /// </param>
    /// 
    virtual const Vector2d& set ( double valueX, double valueY );

    /// <summary>
    /// This method will multiply the <c>Vector2d</c> by the <c>Matrix2d</c> affecting
    /// a 2 dimensional transform of the vector.
    /// </summary>
    /// 
    /// <param name="leftSide">The matrix that will be vector will be multiplied by.
    /// </param>
    ///
    virtual Vector2d& transformBy (const Matrix2d& leftSide);

    /// <summary>
    /// This method will rotate the vector counter clockwise through the specified angle.
    /// </summary>
    ///
    /// <param name="dRads">The angle that the vector should be rotated in Radians.
    /// </param>
    ///
    virtual const Vector2d& rotate ( double dRads );

    /// <summary>
    /// This method returns the length of the vector.
    /// </summary>
    ///
    virtual double length () const;

    /// <summary>
    /// This method returns the vector's counter clockwise angle from the positive X-Axis.
    /// </summary>
    ///
    virtual double angle () const;

    /// <summary>
    /// This method returns the angle between the vector and the argument vector. The return
    /// will always be less than or equal to PI.
    /// </summary>
    ///
    /// <param name="bvTo">A const reference to the vector to measure the angle from.
    /// </param>
    ///
    virtual double angleTo ( const Vector2d& bvTo ) const; // between 0 and Pi

    /// <summary>
    /// This method returns the counter clockwise angle between the vector and 
    /// the argument vector. The return will always be less than or equal to 2 * PI.
    /// </summary>
    ///
    /// <param name="bvTo">A const reference to the vector to measure the angle from.
    /// </param>
    ///
    virtual double ccwAngleTo ( const Vector2d& bvTo ) const; 

    /// <summary>
    /// This method will normalize (make the length of the vector equal to one) the vector.
    /// </summary>
    ///
    virtual const Vector2d& normalize();

    /// <summary>
    /// This method will calculate the normal of the vector and return a new 
    /// <c>Vector2d</c> instance set to the normal.
    /// </summary>
    ///
    /// <returns>
    /// A <c>Vector2d</c> instance set to the normal of the vector.
    /// </returns>
    ///
    virtual Vector2d normal() const;

    /// <summary>
    /// This method negates the vector.
    /// </summary>
    ///
    virtual const Vector2d& negate();

    /// <summary>
    /// This method returns a new vector that is perpendicular to vector.
    /// </summary>
    ///
    /// <returns>
    /// This method returns a <c>Vector2d</c> set to a perpendicular normal vector.
    /// </returns>
    ///
    virtual Vector2d perpVector( ) const;

    /// <summary>
    /// This method calculates the dot product of the vector and the argument.
    /// </summary>
    ///
    /// <param name='v'> The argument to calculate the dot product with. </param>
    ///
    virtual double dotProduct(const Vector2d& v) const;

    /// <summary>
    /// This method tests if the vector and the argument have the same angle.
    /// </summary>
    ///
    /// <param name='iv'> The argument to test the direction of. </param>
    ///
    virtual bool isCodirectionalTo( const Vector2d& iv ) const;

    /// <summary>
    /// This method tests if the vector and the argument specify the same line.
    /// </summary>
    ///
    /// <param name='v'> The argument to be tested. </param>
    ///
    virtual bool isParallelTo ( const Vector2d& v ) const;

    /// <summary>
    /// This method returns true if the <c>x</c> and <c>y</c> members of the
    /// vector and the argument are equal.
    /// </summary>
    ///
    /// <param name="v">A const reference to the vector to test for equality.
    /// </param>
    ///
    virtual bool isEqualTo (const Vector2d& v) const;

    /// <summary>
    /// This method calculates the nearest x or y axis and returns a <c>Vector2d</c> set to
    /// that axis.
    /// </summary>
    ///
    /// <returns>
    /// This methods returns a <c>Vector2d</c> instance set to one of the four axis of 
    /// the Cartesian coordinate system (x, y, -x, -y).
    /// </returns>
    ///
    virtual Vector2d  getOrthoVector ( ) const;

    /// <summary>
    /// The negation operator negates returns the negation of the <c>Vector2d</c>
    /// </summary>
    ///
    /// <returns>
    /// This methods returns a <c>Vector2d</c> instance set to negation of the vector.
    /// </returns>
    ///
    virtual Vector2d operator-() const;

    /// <summary>
    /// The subtraction operator.
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be operated with. </param>
    ///
    /// <returns>
    /// This methods returns a <c>Vector2d</c> instance result of the subtraction.
    /// </returns>
    ///
    virtual Vector2d operator-(const Vector2d& rhs) const;

    /// <summary>
    /// The subtract and assign operator. The result of the subtraction over writes
    /// the current value of the vector.
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be operated with. </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    virtual Vector2d& operator-=(const Vector2d& rhs);

    /// <summary>
    /// An operator that subtracts the vector from a <c>Point2d</c> instance.
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be operated with. </param>
    ///
    /// <returns>
    /// This methods returns a <c>Point2d</c> instance result of the subtraction.
    /// </returns>
    ///
    virtual Point2d operator-(const Point2d& rhs) const;

    /// <summary>
    /// An operator that adds the vector to a <c>Point2d</c> instance.
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be operated with. </param>
    ///
    /// <returns>
    /// This methods returns a <c>Point2d</c> instance result of the addition.
    /// </returns>
    ///
    virtual Point2d operator+(const Point2d& rhs) const;

    /// <summary>
    /// The addition operator.
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be operated with. </param>
    ///
    /// <returns>
    /// This methods returns a <c>Vector2d</c> instance result of the addition.
    /// </returns>
    ///
    virtual Vector2d operator+(const Vector2d& rhs) const;

    /// <summary>
    /// The addition and assign operator. The result of the addition over writes
    /// the current value of the vector.
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be operated with. </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    virtual Vector2d& operator+=(const Vector2d& rhs);

    /// <summary>
    /// The multiplication operator. This will multiply the vector by argument. 
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be operated with. </param>
    ///
    /// <returns>
    /// This methods returns a <c>Vector2d</c> instance result of the multiplication.
    /// </returns>
    ///
    virtual Vector2d operator*(const double& rhs) const;

    /// <summary>
    /// The multiplication and assign operator. The result of the multiplication over writes
    /// the current value of the vector.
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be operated with. </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    virtual Vector2d& operator*=( const double& rhs);

    /// <summary>
    /// The division operator. This will divide the vector by argument. 
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be operated with. </param>
    ///
    /// <returns>
    /// This methods returns a <c>Vector2d</c> instance result of the division.
    /// </returns>
    ///
    virtual Vector2d operator/(const double&rhs) const;

    /// <summary>
    /// The divide and assign operator. The result of the division over writes
    /// the current value of the vector.
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be operated with. </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    virtual Vector2d& operator/=( const double& rhs);

    /// <summary>
    /// The equals operator. 
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be tested. </param>
    ///
    /// <returns> Returns true the arguments are equal.
    /// </returns>
    virtual bool operator==(const Vector2d& rhs) const;

    /// <summary>
    /// The not equal operator. 
    /// </summary>
    ///
    /// <param name='rhs'> The argument to be tested. </param>
    ///
    /// <returns> Returns true the arguments are not equal.
    /// </returns>
    virtual bool operator!=(const Vector2d& rhs) const;
};


//////
// When using vectors in the image coordinate system, you should use this
// class. It takes the upper-left coordinate system of images into account
// when calculating angles.
//
class VectorUL : public Vector2d
{
public:
    /// <summary>
    /// The default (empty) constructor.
    /// </summary>
    ///
    VectorUL ();

    /// <summary>
    /// The initializing constructor.
    /// </summary>
    ///
    /// <param name="dx">This value will be set as the <c>x</c> member.
    /// </param>
    ///
    /// <param name="dy">This value will be set as the <c>y</c> member.
    /// </param>
    ///  
    VectorUL ( double dx, double dy );

    /// <summary>
    /// The copy constructor.
    /// </summary>
    ///
    VectorUL ( const Vector2d& xy );

    /// <summary>
    /// The destructor.
    /// </summary>
    ///
    virtual ~VectorUL ();

    /// <summary>
    /// This method will rotate the vector counter clockwise through the specified angle.
    /// </summary>
    ///
    /// <param name="dRads">The angle that the vector should be rotated in Radians.
    /// </param>
    ///
    /// <remarks>
    /// This operation uses an upper-left image based coordinates system where the positive
    /// y axis points down the image.
    /// </remarks>
    ///
    virtual const Vector2d& rotate ( double dRads );

    /// <summary>
    /// This method returns a new vector that is perpendicular to vector.
    /// </summary>
    ///
    /// <returns>
    /// This method returns a <c>Vector2d</c> set to a perpendicular normal vector.
    /// </returns>
    ///
    /// <remarks>
    /// This operation uses an upper-left image based coordinates system where the positive
    /// y axis points down the image.
    /// </remarks>
    ///
    virtual Vector2d perpVector( ) const;

    /// <summary>
    /// This method returns the vector's counter clockwise angle from the positive X-Axis.
    /// </summary>
    ///
    /// <remarks>
    /// This operation uses an upper-left image based coordinates system where the positive
    /// y axis points down the image.
    /// </remarks>
    ///
    virtual double angle () const;

    /// <summary>
    /// This method returns the counter clockwise angle between the vector and 
    /// the argument vector. The return will always be less than or equal to 2 * PI.
    /// </summary>
    ///
    /// <param name="bvTo">A const reference to the vector to measure the angle from.
    /// </param>
    ///
    /// <remarks>
    /// This operation uses an upper-left image based coordinates system where the positive
    /// y axis points down the image.
    /// </remarks>
    ///
    virtual double ccwAngleTo ( const Vector2d& bvTo ) const; 
};

} //end of namespace

#endif
