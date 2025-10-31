///////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form. 
//
// DESCRIPTION:
//
// Function for converting a relative deviation to circle approximation number.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_DEVIAT_H
#define AMODELER_INC_DEVIAT_H


#include "global.h"

AMODELER_NAMESPACE_BEGIN


// Minimum and maximum approximation which the deviationToApprox() function
// may return.
//
const int kMinApprox = 4;
const int kMaxApprox = 128;

// Returns circle approximation (positive integer number) from a relative 
// deviation (0 < relDev < 1). The approximation is rounded up to the nearest 
// multiple of 4.
//
// The relative deviation is the maximum distance of the sides of a regular 
// n-sided polygon, inscribed into a unit circle, from the circle. The function
// deviationToApprox() returns the number "n" for which this distance is equal
// or smaller than the required "relDev".
//
DllImpExp int deviationToApprox(double relDev);


AMODELER_NAMESPACE_END
#endif

