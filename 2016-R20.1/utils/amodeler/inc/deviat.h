///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
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

