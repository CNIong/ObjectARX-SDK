#ifndef AC_BRGEUTL_H
#define AC_BRGEUTL_H 1
// (C) Copyright 1996-1999 by Autodesk, Inc. 
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
// Function prototype definitions for brgeutl.cpp.


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
