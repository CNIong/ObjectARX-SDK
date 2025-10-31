//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brgeutl.cpp.

#ifndef AC_BRGEUTL_H
#define AC_BRGEUTL_H 1

#include "adesk.h"
#include "genurb2d.h"
#include "brgbl.h"
#include "brface.h"
#include "bredge.h"
#include "brletrav.h"


// forward class declarations
class AcGeSurface;
class AcGeCurve3d;
class AcGeCurve2d;
class AcGeNurbCurve2d;
class AcBrFace;
class AcBrEdge;
class AcBrLoopEdgeTraverser;


AcBr::ErrorStatus   getNativeSurface(const AcBrFace& faceEntity,
                                     AcGeSurface*&   surfaceGeometry,
                                     AcGeSurface*&   nativeGeometry);

AcBr::ErrorStatus   getNativeCurve(const AcBrEdge& edgeEntity,
                                   AcGeCurve3d*&   curveGeometry,
                                   AcGeCurve3d*&   nativeGeometry);

AcBr::ErrorStatus   getNativeOrientedCurve(const AcBrLoopEdgeTraverser& loopEdge,
                                           AcGeCurve3d*&                curveGeometry,
                                           AcGeCurve3d*&                nativeGeometry);

AcBr::ErrorStatus   getNativeParamCurve(const AcBrLoopEdgeTraverser& loopEdge,
                                        AcGeCurve2d*&                pcurveGeometry,
                                        AcGeNurbCurve2d&             nurbGeometry);


#endif
