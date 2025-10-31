//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//
// This file contains the class AcGeLine2d - A mathematical entity
// used to represent an infinite line in 2-space.

#ifndef AC_GELINE2D_H
#define AC_GELINE2D_H

#include "gelent2d.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeLine2d : public AcGeLinearEnt2d
{
public:
    AcGeLine2d();
    AcGeLine2d(const AcGeLine2d& line);
    AcGeLine2d(const AcGePoint2d& pnt, const AcGeVector2d& vec);
    AcGeLine2d(const AcGePoint2d& pnt1, const AcGePoint2d& pnt2);

    // The x-axis and y-axis lines.
    //
    static const AcGeLine2d kXAxis;
    static const AcGeLine2d kYAxis;

    // Set methods.
    //
    AcGeLine2d& set (const AcGePoint2d& pnt, const AcGeVector2d& vec);
    AcGeLine2d& set (const AcGePoint2d& pnt1, const AcGePoint2d& pnt2);

    // Assignment operator.
    //
    AcGeLine2d& operator = (const AcGeLine2d& line);
};

#pragma pack (pop)
#endif
