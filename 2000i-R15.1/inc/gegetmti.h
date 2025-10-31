#ifndef AC_GEGETMTI_H
#define AC_GEGETMTI_CH
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
// DESCRIPTION:
// An overloaded and templated function to return an enum value corresponding
// to selected gelib types.
#include "gedll.h"

template <class T>
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(T* pT = 0) // pT is a dummy argument 
{ return AcGe::kAcGeUnknown; }


class AcGeEntity2d;
class AcGeCurveCurveInt2d;
class AcGeClipBoundary2d;
class AcGeBoundBlock2d;
class AcGeCurve2d;
class AcGeCircArc2d;
class AcGeCompositeCurve2d;
class AcGeEllipArc2d;
class AcGeExternalCurve2d;
class AcGeLinearEnt2d;
class AcGeLine2d;
class AcGeLineSeg2d;
class AcGeRay2d;
class AcGeOffsetCurve2d;
class AcGeSplineEnt2d;
class AcGeCubicSplineCurve2d;
class AcGeNurbCurve2d;
class AcGePolyline2d;
class AcGePointEnt2d;
class AcGePointOnCurve2d;
class AcGePosition2d;
class AcGeHatch;
class AcGeEntity3d;
class AcGeCurveCurveInt3d;
class AcGeBoundBlock3d;
class AcGeCurve3d;
class AcGeCircArc3d;
class AcGeCompositeCurve3d;
class AcGeEllipArc3d;
class AcGeExternalCurve3d;
class AcGeLinearEnt3d;
class AcGeLine3d;
class AcGeLineSeg3d;
class AcGeRay3d;
class AcGeOffsetCurve3d;
class AcGeSplineEnt3d;
class AcGeCubicSplineCurve3d;
class AcGeNurbCurve3d;
class AcGePolyline3d;
class AcGeAugPolyline3d;
class AcGeDiscreteSpline3d;
class AcGePointEnt3d;
class AcGePointOnCurve3d;
class AcGePointOnSurface;
class AcGePosition3d;
class AcGeSurface;
class AcGeCone;
class AcGeCylinder;
class AcGeExternalSurface;
class AcGeNurbSurface;
class AcGeOffsetSurface;
class AcGePlanarEnt;
class AcGeBoundedPlane;
class AcGePlane;
class AcGeSphere;
class AcGeTorus;
class AcGeExternalBoundedSurface;
class AcGeTrimmedSurface;
class AcGeLibVersion;
class AcGeCurveBoundary;
class AcGeInterval;
class AcGeScale2d;
class AcGeScale3d;
class AcGeTol;
class AcGeKnotVector;
class AcGeMatrix2d;
class AcGeMatrix3d;
class AcGePoint2d;
class AcGePoint3d;
class AcGeVector2d;
class AcGeVector3d;
class AcGeEllipCone;
// Declarations of the overloads for these templated types are included 
// in their headers to avoid circular reference through acarray.h
//#include "gept2dar.h"
//#include "gept3dar.h"
//#include "gevc2dar.h"
//#include "gevc3dar.h"
//#include "geintarr.h"


GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeEntity2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCurveCurveInt2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeClipBoundary2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeBoundBlock2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCurve2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCircArc2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCompositeCurve2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeEllipArc2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeExternalCurve2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLinearEnt2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLine2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLineSeg2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeRay2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeOffsetCurve2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeSplineEnt2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCubicSplineCurve2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeNurbCurve2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePolyline2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePointEnt2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePointOnCurve2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePosition2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeHatch* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeEntity3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCurveCurveInt3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeBoundBlock3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCurve3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCircArc3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCompositeCurve3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeEllipArc3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeExternalCurve3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLinearEnt3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLine3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLineSeg3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeRay3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeOffsetCurve3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeSplineEnt3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCubicSplineCurve3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeNurbCurve3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePolyline3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeAugPolyline3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeDiscreteSpline3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePointEnt3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePointOnCurve3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePointOnSurface* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePosition3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeSurface* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCone* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCylinder* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeExternalSurface* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeNurbSurface* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeOffsetSurface* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePlanarEnt* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeBoundedPlane* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePlane* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeSphere* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeTorus* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeExternalBoundedSurface* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeTrimmedSurface* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLibVersion* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCurveBoundary* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeInterval* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeScale2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeScale3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeTol* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeKnotVector* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeMatrix2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeMatrix3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePoint2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePoint3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeVector2d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeVector3d* pT);
GE_DLLEXPIMPORT
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeEllipCone* pT);
#endif
