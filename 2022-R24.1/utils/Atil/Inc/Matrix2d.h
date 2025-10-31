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

#ifndef MATRIX2D_H
#define MATRIX2D_H

#ifndef POINT2D_H
namespace Atil { class Point2d; }
#endif
#ifndef VECTOR2D_H
namespace Atil { class Vector2d; }
#endif

namespace Atil
{
/// <summary>
/// The <c>Matrix2d</c> class defines a basic two-dimensional (3x3) matrix class. 
/// It inter operates with the <c>Vector2d</c> and <c>Point2d</c> classes to provide
/// basic geometry functionality for use when transforming images.
/// </summary>
///
class Matrix2d
{
public:
    /// <summary>
    /// A static construction-type method that will construct a matrix and set it to
    /// a translation as specified by the arguments.
    /// </summary>
    /// 
    /// <param name="vec">A constant reference to a <c>Vector2d</c> instance that specifies
    /// the translation to be set into the matrix.
    /// </param>
    ///
    /// <returns>
    /// This method returns an initialized <c>Matrix2d</c> instance.
    /// </returns>
    ///
    static Matrix2d translation(const Vector2d& vec);

    /// <summary>
    /// A static construction-type method that will construct a matrix and set it to
    /// a rotation about a point as specified by the arguments.
    /// </summary>
    /// 
    /// <param name="angle">A double that specifies the angle of rotation.
    /// </param>
    ///
    /// <param name="center">A constant reference to a <c>Point2d</c> that holds the
    /// point to rotate about.
    /// </param>
    ///
    /// <returns>
    /// This method returns an initialized <c>Matrix2d</c> instance.
    /// </returns>
    ///   
    static Matrix2d rotation(double angle, const Point2d& center);

    /// <summary>
    /// A static construction-type method that will construct a matrix and set it to
    /// a scale about a point as specified by the arguments.
    /// </summary>
    /// 
    /// <param name="scaleAll">A double that specifies the scale.
    /// </param>
    ///
    /// <param name="center">A constant reference to a <c>Point2d</c> that holds the
    /// point to scale about.
    /// </param>
    ///
    /// <returns>
    /// This method returns an initialized <c>Matrix2d</c> instance.
    /// </returns>
    ///
    static Matrix2d scaling(double scaleAll, const Point2d& center);

    /// <summary>
    /// A static construction-type method that will construct a matrix and set it to
    /// a mirror over a point as specified by the arguments.
    /// </summary>
    /// 
    /// <param name="pnt">A constant reference to a <c>Point2d</c> that holds the
    /// point to mirror.
    /// </param>
    ///
    /// <returns>
    /// This method returns an initialized <c>Matrix2d</c> instance.
    /// </returns>
    ///
    static Matrix2d mirroring(const Point2d& pnt);

    /// <summary>
    /// A static construction-type method that will construct a matrix and set it to
    /// the tranformation from a source to a destination two dimensional coordinate system.
    /// </summary>
    /// 
    /// <param name="fromOrigin">A constant reference to a <c>Point2d</c> that holds the
    /// origin of the source coordinate system.
    /// </param>
    ///
    /// <param name="fromE0">A constant reference to a <c>Vector2d</c> that holds the
    /// x axis (length and angle) of the source.
    /// </param>
    ///
    /// <param name="fromE1">A constant reference to a <c>Vector2d</c> that holds the
    /// y axis (length and angle) of the source.
    /// </param>
    /// 
    /// <param name="toOrigin">A constant reference to a <c>Point2d</c> that holds the
    /// origin of the destination coordinate system.
    /// </param>
    ///
    /// <param name="toE0">A constant reference to a <c>Vector2d</c> that holds the
    /// x axis (length and angle) of the destination.
    /// </param>
    ///
    /// <param name="toE1">A constant reference to a <c>Vector2d</c> that holds the
    /// y axis (length and angle) of the destination.
    /// </param>
    ///
    /// <returns>
    /// This method returns an initialized <c>Matrix2d</c> instance.
    /// </returns>
    ///
    static Matrix2d alignCoordSys(const Point2d& fromOrigin,
        const Vector2d& fromE0, const Vector2d& fromE1,
        const Point2d& toOrigin, const Vector2d& toE0, const Vector2d& toE1);

public:

    /// <summary>
    /// The default (empty) constructor.
    /// </summary>
    ///
    Matrix2d();
    /// <summary>
    /// The copy constructor.
    /// </summary>
    ///
    /// <param name='src'>
    /// The instance to copy.
    /// </param>
    ///
    Matrix2d(const Matrix2d& src);

    /// <summary>
    /// A static instance of <c>Matrix2d</c> set to the identity matrix.
    /// </summary>
    ///
    static const Matrix2d kIdentity;

    /// <summary>
    /// This method will set the matrix to the identity matrix.
    /// </summary>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>
    /// </returns>
    ///
    Matrix2d& setToIdentity();

    /// <summary>
    /// The multiplication operator will multiply the matrix by the argument.
    /// </summary>
    /// 
    /// <param name="mat">A constant reference to a <c>Matrix2d</c>.
    /// </param>
    /// 
    /// <returns>
    /// A <c>Matrix2d</c> instance is returned set to the result of the operator.
    /// </returns>
    ///
    Matrix2d operator*(const Matrix2d& mat) const;

    /// <summary>
    /// The multiply and assign operator will multiply the matrix by the argument
    /// with the result over writing the current matrix values.
    /// </summary>
    /// 
    /// <param name="mat">A constant reference to a <c>Matrix2d</c>.
    /// </param>
    /// 
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& operator*=(const Matrix2d& mat);

    /// <summary>
    /// This method will multiply placing the argument to the left of the matrix
    /// with the result over writing the current matrix values.
    /// </summary>
    /// 
    /// <param name="leftSide">A constant reference to a <c>Matrix2d</c>.
    /// </param>
    /// 
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& preMultBy(const Matrix2d& leftSide);

    /// <summary>
    /// This method will multiply placing the argument to the right of the matrix
    /// with the result over writing the current matrix values.
    /// </summary>
    /// 
    /// <param name="rightSide">A constant reference to a <c>Matrix2d</c>.
    /// </param>
    /// 
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& postMultBy(const Matrix2d& rightSide);

    /// <summary>
    /// This method will calculate the dot product of the arguments
    /// with the result over writing the current matrix values.
    /// </summary>
    /// 
    /// <param name="mat1">A constant reference to a <c>Matrix2d</c>.
    /// </param>
    /// 
    /// <param name="mat2">A constant reference to a <c>Matrix2d</c>.
    /// </param>
    /// 
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& setToProduct(const Matrix2d& mat1, const Matrix2d& mat2);

    /// <summary>
    /// This method will calculate the invert of the matrix and the result
    /// will over write the current matrix values.
    /// </summary>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& invert();

    /// <summary>
    /// This method will calculate the invert of the matrix.
    /// </summary>
    ///
    /// <returns>
    /// A <c>Matrix2d</c> instance is returned set to the result.
    /// </returns>
    ///
    Matrix2d inverse() const;
    
    /// <summary>
    /// This method will test if the matrix is singular and therefor not invertible.
    /// </summary>
    ///
    /// <returns>
    /// This will return true if the matrix is singular.
    /// </returns>
    ///
    bool isSingular() const;

    /// <summary>
    /// This method will set the matrix to its transpose.
    /// </summary>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& transposeIt();

    /// <summary>
    /// This method will generate the transpose of the matrix.
    /// </summary>
    ///
    /// <returns>
    /// A <c>Matrix2d</c> instance is returned set to the result.
    /// </returns>
    ///
    Matrix2d transpose() const;
   
    /// <summary>
    /// The equals operator tests for equivalence using the infinity norm.
    /// </summary>
    ///
    /// <param name='mat'> The <c>Matrix2d</c> to be compared. </param>
    ///
    /// <returns>
    /// Returns true if the argument is identical to <c>*this</c>.
    /// </returns>
    ///
    bool operator== (const Matrix2d& mat) const;

    /// <summary>
    /// The not equals operator for equivalence using the infinity norm.
    /// </summary>
    ///
    /// <param name='mat'>The <c>Matrix2d</c> to be compared. </param>
    ///
    /// <returns>
    /// Returns true if the argument is not identical to <c>*this</c>.
    /// </returns>
    ///
    bool operator!= (const Matrix2d& mat) const;

    /// <summary>
    /// This method tests for equivalence using the infinity norm.
    /// </summary>
    ///
    /// <param name='mat'> The <c>Matrix2d</c> to be compared. </param>
    ///
    /// <returns>
    /// Returns true if the argument is identical to <c>*this</c>.
    /// </returns>
    ///
    bool isEqualTo (const Matrix2d& mat) const;

    /// <summary>
    /// This method returns the scaling effect of the current matrix values.
    /// </summary>
    ///
    /// <returns>
    /// Returns a double that is the scale in the <c>Matrix2d</c>.
    /// </returns>
    ///
    double scale(void);

    /// <summary>
    /// This method will return the determinant.
    /// </summary>
    ///
    /// <returns>
    /// Return the determinant as a double.
    /// </returns>
    ///
    double det() const;

    /// <summary>
    /// This method will set the matrix to the translation specified.
    /// </summary>
    ///
    /// <param name="vec">A constant reference to a <c>Vector2d</c> specifying the translation.
    /// </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& setTranslation(const Vector2d& vec);

    /// <summary>
    /// This method will return the translation effect of the current matrix.
    /// </summary>
    /// 
    /// <returns>
    /// This returns a <c>Vector2d</c> specifying the translation.
    /// </returns>
    ///
    Vector2d translation() const;

    /// <summary>
    /// This method will return the scaling, rotation, mirror components.
    /// </summary>
    ///
    /// <param name="scale">A double reference that will be set to the
    /// scaling effect of the matrix.
    /// </param>
    ///
    /// <param name="angle">A double reference that will be set to the
    /// rotation effect of the matrix.
    /// </param>
    ///
    /// <param name="isMirror">A reference to a bool that will be set to true
    /// if the matrix effects a mirror.
    /// </param>
    ///
    /// <param name="reflex">A <c>Vector2d</c> reference that will be set to 
    /// the mirror effect if the matrix effects a mirror.
    /// </param>
    /// 
    /// <returns>
    /// This will return true if the operation is successful and the results are valid.
    /// </returns>
    bool isConformal (double& scale, double& angle,
        bool& isMirror, Vector2d& reflex) const;

    /// <summary>
    /// This method will use the parameters to set the matrix to represent a 
    /// coordinate system.
    /// </summary>
    ///
    /// <param name="origin">A constant reference to a <c>Point2d</c> that holds the
    /// origin of the coordinate system.
    /// </param>
    ///
    /// <param name="e0">A constant reference to a <c>Vector2d</c> that holds the
    /// x axis (length and angle) of the source.
    /// </param>
    ///
    /// <param name="e1">A constant reference to a <c>Vector2d</c> that holds the
    /// y axis (length and angle) of the source.
    /// </param>
    ///    
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& setCoordSystem(const Point2d& origin,
        const Vector2d& e0, const Vector2d& e1);

    /// <summary>
    /// This method will return the represent coordinates system in the parameters.
    /// </summary>
    ///
    /// <param name="origin">A reference to a <c>Point2d</c> that is set to the
    /// origin of the coordinate system.
    /// </param>
    ///
    /// <param name="e0">A reference to a <c>Vector2d</c> that is set to the
    /// x axis (length and angle) of the source.
    /// </param>
    ///
    /// <param name="e1">A reference to a <c>Vector2d</c> that is set to the
    /// y axis (length and angle) of the source.
    /// </param>
    ///    
    void getCoordSystem(Point2d& origin,
        Vector2d& e0, Vector2d& e1) const;

    /// <summary>
    /// This method will set the matrix to the translation as specified by the arguments.
    /// </summary>
    /// 
    /// <param name="vec">A constant reference to a <c>Vector2d</c> instance that specifies
    /// the translation to be set into the matrix.
    /// </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& setToTranslation(const Vector2d& vec);

    /// <summary>
    /// This method will set the matrix to the be rotation about a point
    /// as specified by the arguments.
    /// </summary>
    /// 
    /// <param name="angle">A double that specifies the angle of rotation.
    /// </param>
    ///
    /// <param name="center">A constant reference to a <c>Point2d</c> that holds the
    /// point to rotate about.
    /// </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& setToRotation(double angle, const Point2d& center);

    /// <summary>
    /// This method will set the matrix to be scaling about a point
    /// as specified by the arguments.
    /// </summary>
    /// 
    /// <param name="scaleAll">A double that specifies the scale.
    /// </param>
    ///
    /// <param name="center">A constant reference to a <c>Point2d</c> that holds the
    /// point to scale about.
    /// </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& setToScaling(double scaleAll, const Point2d& center);

    /// <summary>
    /// This method will set the matrix to be scaling about a point
    /// as specified by the arguments.
    /// </summary>
    /// 
    /// <param name="scaleX">A double that specifies the scale for the x.
    /// </param>
    ///
    /// <param name="scaleY">A double that specifies the scale for the y.
    /// </param>
    ///
    /// <param name="center">A constant reference to a <c>Point2d</c> that holds the
    /// point to scale about.
    /// </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& setToScaling(double scaleX, double scaleY,
        const Point2d& center);

    /// <summary>
    /// This method will set the matrix to a mirror over a point
    /// as specified by the arguments.
    /// </summary>
    /// 
    /// <param name="pnt">A constant reference to a <c>Point2d</c> that holds the
    /// point to mirror.
    /// </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& setToMirroring(const Point2d& pnt);
    
    /// <summary>
    /// This method will set the matrix to the transformation from a source to a
    /// destination two dimensional coordinate system.
    /// </summary>
    /// 
    /// <param name="fromOrigin">A constant reference to a <c>Point2d</c> that holds the
    /// origin of the source coordinate system.
    /// </param>
    ///
    /// <param name="fromE0">A constant reference to a <c>Vector2d</c> that holds the
    /// x axis (length and angle) of the source.
    /// </param>
    ///
    /// <param name="fromE1">A constant reference to a <c>Vector2d</c> that holds the
    /// y axis (length and angle) of the source.
    /// </param>
    /// 
    /// <param name="toOrigin">A constant reference to a <c>Point2d</c> that holds the
    /// origin of the destination coordinate system.
    /// </param>
    ///
    /// <param name="toE0">A constant reference to a <c>Vector2d</c> that holds the
    /// x axis (length and angle) of the destination.
    /// </param>
    ///
    /// <param name="toE1">A constant reference to a <c>Vector2d</c> that holds the
    /// y axis (length and angle) of the destination.
    /// </param>
    ///
    /// <returns>
    /// Returns a reference to <c>*this</c>.
    /// </returns>
    ///
    Matrix2d& setToAlignCoordSys(const Point2d&  fromOrigin,
        const Vector2d& fromE0, const Vector2d& fromE1,
        const Point2d&  toOrigin, const Vector2d& toE0, const Vector2d& toE1);


    /// <summary>
    /// The () operator allows access to the members of the matrix.
    /// </summary>
    ///
    /// <param name= 'row'>
    /// The index of the row that should be accessed.
    /// </param>
    ///
    /// <param name= 'column'>
    /// The index of the column that should be accessed.
    /// </param>
    ///
    /// <returns>
    /// Returns the value at a specific position in the matrix.
    /// </returns>
    ///
    double operator()(unsigned int row, unsigned int column) const;

    /// <summary>
    /// The () operator allows access to the members of the matrix.
    /// </summary>
    ///
    /// <param name= 'row'>
    /// The index of the row that should be accessed.
    /// </param>
    ///
    /// <param name= 'column'>
    /// The index of the column that should be accessed.
    /// </param>
    ///
    /// <returns>
    /// Returns a reference to the value at a specific position in the matrix.
    /// </returns>
    ///
    double& operator()(unsigned int row, unsigned int column);

    // The components of the matrix ([row][column]).
    double entry[3][3];
};

/// <summary>
/// Return the element in position [row][column]
/// of the `entry' array.
/// </summary>
///
/// <param name= 'row'>
/// The index of the row that should be accessed.
/// </param>
///
/// <param name= 'column'>
/// The index of the column that should be accessed.
/// </param>
///
/// <returns>
/// Returns a reference to the value at a specific position in the matrix.
/// </returns>
///
inline double Matrix2d::operator() (unsigned int row, unsigned int column) const
{
    return entry[row][column];
}

/// <summary>
/// Return a reference to the element in position [row][column]
/// of the `entry' array.
/// </summary>
///
/// <param name= 'row'>
/// The index of the row that should be accessed.
/// </param>
///
/// <param name= 'column'>
/// The index of the column that should be accessed.
/// </param>
///
/// <returns>
/// Returns a reference to the value at a specific position in the matrix.
/// </returns>
///
inline double& Matrix2d::operator() (unsigned int row, unsigned int column)
{
    return entry[row][column];
}

}

#endif
