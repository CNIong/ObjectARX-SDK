//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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

