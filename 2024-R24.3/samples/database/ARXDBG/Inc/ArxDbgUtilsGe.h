//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef ARXDBGUTILSGE_H
#define ARXDBGUTILSGE_H

struct ArxDbgUtilsGe {

static const double kPi;
static const double kHalfPi;
static const double kTwoPi;

static const double kRad0;
static const double kRad45;
static const double kRad90;
static const double kRad135;
static const double kRad180;
static const double kRad270;
static const double kRad360;


static double    radiansToDegrees(const double rads);
static double    degreesToRadians(const double degrees);

static bool      fuzzyEqual(double x1, double x2);

static AcGePoint3d    midpoint(const AcGePoint3d& pt1, const AcGePoint3d& pt2);

};

#endif // ARXDBGUTILSGE_H

