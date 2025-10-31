#ifndef AC_GETOL_H
#define AC_GETOL_H
//
// (C) Copyright 1993-2007 by Autodesk, Inc.
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
// DESCRIPTION:
//
// This file contains the functionality for managing tolerances within
// gelib.
//
// This is an instantiable class that is initialized to the default
// tolerances.  Subsequently, the tolerances within it can be customized
// to suite a specific need.  For example, an instance of this class
// may be specialized to be utilized during surface intersection.
//
// DESCRIPTION
//
// 1. Two points p1 and p2 are equal if and only if
//
//           (p1 - p2).length() <= equalPoint
//
// 2. Two vectors v1 and v2 are equal if and only if
//
//           (v1 - v2).length() <= equalVector
//
// 3. Two vectors v1 and v2 are parallel if and only if
//
//         ( v1/v1.length() - v2/v2.length() ).length() < equalVector
//     OR  ( v1/v1.length() + v2/v2.length() ).length() < equalVector
//
// 4. Two vectors v1 and v2 are perpendicular if and only if
//
//       abs((v1.dotProduct(v2))/(v1.length()*v2.length())) <= equalVector
//
// 5. Two lines or rays are parallel (perpendicular) if and only if
//    their directional vectors are parallel (perpendicular)
//
// 6. Two lines are equal if and only if they have points within equalPoint
//    and they are parallel.
//
// IMPORTANT: These rules mean that two lines are close to each other as
//            point sets in the part of the modeling space of diameter
//            DIAM, if only the tolerance equalVector is set tighter than
//            equalPoint/DIAM

#ifndef unix
#include <stdlib.h>
#endif
#include "gedll.h"
#include "gedblar.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeTol {
public:
    AcGeTol();

    // Inquiry functions.
    //
    double  equalPoint          () const;
    double  equalVector         () const;

    // Set functions.
    //
    void    setEqualPoint       ( double val );
    void    setEqualVector      ( double val );

private:
    double				mTolArr[5];
    int                 mAbs;

    friend class AcGeTolA;
};

// Inlines for AcGeTol
//

__forceinline void AcGeTol::setEqualVector( double val )
    { mTolArr[1] = val; }

__forceinline double AcGeTol::equalVector() const
    { return mTolArr[1]; }

__forceinline void AcGeTol::setEqualPoint( double val )
    { mTolArr[0] = val; }

__forceinline double AcGeTol::equalPoint() const
    { return mTolArr[0]; }

#pragma pack (pop)
#endif
