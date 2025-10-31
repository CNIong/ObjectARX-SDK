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

#ifndef OFFSET_H
#define OFFSET_H

namespace Atil
{
/// <summary>
/// This class holds two integers that are offsets from the origin of the image 
/// coordinate system. The image coordinate system places 0,0 at the upper left
/// pixel of the image and y progress positively down the rows of the image.
/// </summary>
///
class Offset 
{
public:
    /// <summary> The x coordinate in pixel space.
    /// </summary>
    Int32 x;
    /// <summary> The y coordinate in pixel space.
    /// </summary>
    Int32 y;

    /// <summary>
    /// The trivial constructor.
    /// </summary>
    /// 
    Offset ();

    /// <summary>
    /// A setting constructor that will initialize the offset.
    /// </summary>
    /// 
    /// <param name="nX">The value to be set into <c>x</c>.
    /// </param>
    ///
    /// <param name="nY">The value to be set into <c>y</c>.
    /// </param>
    /// 
    Offset ( Int32 valueX, Int32 valueY );

    /// <summary> The destructor. </summary>
    ~Offset ();
    
    /// <summary>
    /// A setting method that will set both the x and the y of the offset.
    /// </summary>
    /// 
    /// <param name="x">The value to be set into <c>x</c>.
    /// </param>
    ///
    /// <param name="y">The value to be set into <c>y</c>.
    /// </param>
    /// 
    /// <returns>
    /// A const reference to the modified <c>Offset</c> instance.
    /// </returns>
    const Offset& set( Int32 valueX, Int32 valueY);

    /// <summary>
    /// The equals operator will over right the current values with those of the argument.
    /// </summary>
    ///
    /// <param name="rhs">The value to be set.
    /// </param>
    ///
    /// <returns>
    /// A reference to the modified <c>Offset</c> instance.
    /// </returns>
    Offset& operator=( const Offset& rhs );

    /// <summary>
    /// This method will add an integer value to both the <c>x</c> and the <c>y</c> of
    /// the offset and return the sum in a new <c>Offset</c> instance.
    /// </summary>
    ///
    /// <param name="nOffset">The value to be added to x and y.
    /// </param>
    ///
    /// <returns>
    /// A new <c>Offset</c> with the result of the operation.
    /// </returns>
    Offset operator+( Int32 nOffset ) const;

    /// <summary>
    /// This method will add an integer value to both the <c>x</c> and the <c>y</c>
    /// of the offset and assign the <c>Offset</c> to that value.
    /// </summary>
    ///
    /// <param name="nOffset">The value to be added to x and y.
    /// </param>
    ///
    /// <returns>
    /// A reference to the modified <c>Offset</c> instance.
    /// </returns>
    Offset& operator+=( Int32 nOffset );

    /// <summary>
    /// This method will subtract an integer value from both the <c>x</c> and the <c>y</c> of
    /// the offset and return the sum in a new <c>Offset</c> instance.
    /// </summary>
    ///
    /// <param name="nOffset">The value to be subtracted from x and y.
    /// </param>
    ///
    /// <returns>
    /// A new <c>Offset</c> with the result of the operation.
    /// </returns>
    Offset operator-( Int32 nOffset ) const;

    /// <summary>
    /// This method will subtract an integer value from both the <c>x</c> and the <c>y</c>
    /// of the offset and assign the <c>Offset</c> to that value.
    /// </summary>
    ///
    /// <param name="nOffset">The value to be subtracted from x and y.
    /// </param>
    ///
    /// <returns>
    /// A reference to the modified <c>Offset</c> instance.
    /// </returns>
    Offset& operator-=( Int32 nOffset );

    /// <summary>
    /// This method will multiply both the <c>x</c> and the <c>y</c> of the offset
    /// by the integer value and return the sum in a new <c>Offset</c> instance.
    /// </summary>
    ///
    /// <param name="nValue">The value to be multiplied into x and y.
    /// </param>
    ///
    /// <returns>
    /// A new <c>Offset</c> with the result of the operation.
    /// </returns>
    Offset operator*( Int32 nValue ) const;

    /// <summary>
    /// This method will multiply both the <c>x</c> and the <c>y</c> of the offset
    /// by the integer value and assign the <c>Offset</c> to that value.
    /// </summary>
    ///
    /// <param name="nValue">The value to be multiplied into x and y.
    /// </param>
    ///
    /// <returns>
    /// A reference to the modified <c>Offset</c> instance.
    /// </returns>
    Offset& operator*=( Int32 nValue );

    /// <summary>
    /// This method will add the <c>Offset</c> and return the sum in a new 
    /// <c>Offset</c> instance.
    /// </summary>
    ///
    /// <param name="rhs">The <c>Offset</c> to be added.
    /// </param>
    ///
    /// <returns>
    /// A new <c>Offset</c> with the result of the operation.
    /// </returns>
    Offset operator+( const Offset& rhs ) const;

    /// <summary>
    /// This method will add the <c>Offset</c> and assign the <c>Offset</c> to that value.
    /// </summary>
    ///
    /// <param name="rhs">The <c>Offset</c> to be added.
    /// </param>
    ///
    /// <returns>
    /// A reference to the modified <c>Offset</c> instance.
    /// </returns>
    Offset& operator+=( const Offset& rhs );

    /// <summary>
    /// This method will subtract the <c>Offset</c> and return the sum in a new 
    /// <c>Offset</c> instance.
    /// </summary>
    ///
    /// <param name="rhs">The <c>Offset</c> to be subtracted from x and y.
    /// </param>
    ///
    /// <returns>
    /// A new <c>Offset</c> with the result of the operation.
    /// </returns>
    Offset operator-( const Offset& rhs ) const;

    /// <summary>
    /// This method will subtract the <c>Offset</c> and assign the <c>Offset</c> to that value.
    /// </summary>
    ///
    /// <param name="rhs">The <c>Offset</c> to be subtracted from x and y.
    /// </param>
    ///
    /// <returns>
    /// A reference to the modified <c>Offset</c> instance.
    /// </returns>
    Offset& operator-=( const Offset& rhs );
    
    /// <summary>
    /// The equals operator will return true if the <c>x</c> and the <c>y</c> of the two
    /// <c>Offset</c>s are equal.
    /// </summary>
    ///
    /// <param name="rhs">The <c>Offset</c> to be tested for equality with.
    /// </param>
    ///
    /// <returns>
    /// This will return true if the x and y values of the <c>Offset</c>s are equal.
    /// </returns>
    bool operator==( const Offset& rhs ) const;

    /// <summary>
    /// The equals operator will return false if the <c>x</c> and the <c>y</c> of the two
    /// <c>Offset</c>s are equal.
    /// </summary>
    ///
    /// <param name="rhs">The <c>Offset</c> to be tested for inequality with.
    /// </param>
    ///
    /// <returns>
    /// This will return false if the x and y values of the <c>Offset</c>s are equal.
    /// </returns>
    bool operator!=( const Offset& rhs ) const;
};

} //end of namespace

#ifndef OFFSET_INL
#include <Offset.inl>
#endif

#endif

