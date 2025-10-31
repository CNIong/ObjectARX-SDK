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
// Declarations of the overloads for these templated types are included 
// in their headers to avoid circular reference through acarray.h
//#include "gept2dar.h"
//#include "gept3dar.h"
//#include "gevc2dar.h"
//#include "gevc3dar.h"
//#include "geintarr.h"


#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeEntity2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCurveCurveInt2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeClipBoundary2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeBoundBlock2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCurve2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCircArc2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCompositeCurve2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeEllipArc2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeExternalCurve2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLinearEnt2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLine2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLineSeg2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeRay2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeOffsetCurve2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeSplineEnt2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCubicSplineCurve2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeNurbCurve2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePolyline2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePointEnt2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePointOnCurve2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePosition2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeHatch* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeEntity3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCurveCurveInt3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeBoundBlock3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCurve3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCircArc3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCompositeCurve3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeEllipArc3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeExternalCurve3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLinearEnt3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLine3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLineSeg3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeRay3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeOffsetCurve3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeSplineEnt3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCubicSplineCurve3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeNurbCurve3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePolyline3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeAugPolyline3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeDiscreteSpline3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePointEnt3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePointOnCurve3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePointOnSurface* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePosition3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeSurface* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCone* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCylinder* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeExternalSurface* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeNurbSurface* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeOffsetSurface* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePlanarEnt* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeBoundedPlane* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePlane* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeSphere* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeTorus* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeExternalBoundedSurface* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeTrimmedSurface* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeLibVersion* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeCurveBoundary* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeInterval* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeScale2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeScale3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeTol* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeKnotVector* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeMatrix2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeMatrix3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePoint2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGePoint3d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeVector2d* pT);
#ifdef AC_GEGETMTI_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe::metaTypeIndex AcGeGetMetaTypeIndex(AcGeVector3d* pT);
#endif