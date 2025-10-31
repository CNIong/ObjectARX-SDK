//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgUtilsGe.h"



// predefined constants for common angles
const double ArxDbgUtilsGe::kPi       = 3.14159265358979323846;
const double ArxDbgUtilsGe::kHalfPi   = 3.14159265358979323846 / 2.0;
const double ArxDbgUtilsGe::kTwoPi	  = 3.14159265358979323846 * 2.0;

const double ArxDbgUtilsGe::kRad0     = 0.0;
const double ArxDbgUtilsGe::kRad45    = 3.14159265358979323846 / 4.0;
const double ArxDbgUtilsGe::kRad90    = 3.14159265358979323846 / 2.0;
const double ArxDbgUtilsGe::kRad135   = (3.14159265358979323846 * 3.0) / 4.0;
const double ArxDbgUtilsGe::kRad180   = 3.14159265358979323846;
const double ArxDbgUtilsGe::kRad270   = 3.14159265358979323846 * 1.5;
const double ArxDbgUtilsGe::kRad360   = 3.14159265358979323846 * 2.0;


/****************************************************************************
**
**  ArxDbgUtilsGe::radiansToDegrees
**
**  **jma
**
*************************************/

double
ArxDbgUtilsGe::radiansToDegrees(const double rads)
{
    return rads * (180.0 / kPi);
}

/****************************************************************************
**
**  ArxDbgUtilsGe::degreesToRadians
**
**  **jma
**
*************************************/

double
ArxDbgUtilsGe::degreesToRadians(const double degrees)
{
    return degrees * (kPi / 180.0);
}

/****************************************************************************
**
**  ArxDbgUtilsGe::fuzzyEqual (DOUBLES)
**
**  **jma
**
*************************************/

bool
ArxDbgUtilsGe::fuzzyEqual(double x1, double x2)
{
    return (fabs(x1 - x2) <= AcGeContext::gTol.equalPoint());
}

/****************************************************************************
**
**  ArxDbgUtilsGe::midpoint
**
**  **jma
**
*************************************/

AcGePoint3d
ArxDbgUtilsGe::midpoint(const AcGePoint3d& pt1, const AcGePoint3d& pt2)
{
    AcGePoint3d newPt;

    newPt.x =(pt1.x + pt2.x) / 2.0;
    newPt.y =(pt1.y + pt2.y) / 2.0;
    newPt.z =(pt1.z + pt2.z) / 2.0;

    return newPt;
}


