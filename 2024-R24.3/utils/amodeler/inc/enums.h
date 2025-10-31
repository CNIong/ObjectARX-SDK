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
// Some popular enums.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_ENUMS_H
#define AMODELER_INC_ENUMS_H


#include "global.h"

AMODELER_NAMESPACE_BEGIN

enum BoolOperType
{
    kBoolOperUnite,
    kBoolOperSubtract,
    kBoolOperIntersect
};

enum BodyInterferenceType
{
    kBodiesDoNotInterfere,
    kBodiesTouch,
    kBodiesInterfere
};

enum PointInBodyLocation
{
    kPointOutsideBody,
    kPointAtVertex,
    kPointOnEdge,
    kPointInFace,
    kPointInsideBody
};

enum HiddenLinesDisplay
{
    kHiddenLinesInvisible,
    kHiddenLinesDashed,
    kHiddenLinesVisible
};

enum HiddenLineDrawingImprove
{
    kNoDrawingImprove,
    kConnectDrawingImprove,
    kArcReconstructDrawingImprove
};

enum TriangulationType
{
    kGenerateTriangles,
    kGenerateQuadrilaterals,
    kGenerateTriStrips,
    kGenerateTriStripsPerSurface
};

enum RayBodyIntersection
{
    kRayDoesNotIntersect,
    kRayPointAtVertex,
    kRayPointOnEdge,
    kRayPointInFace,
    kRayIntersectsVertex,
    kRayIntersectsEdge,
    kRayIntersectsFace
};


AMODELER_NAMESPACE_END
#endif

