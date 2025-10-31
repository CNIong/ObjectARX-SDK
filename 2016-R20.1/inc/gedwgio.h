//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
// This file contains the class AcGeDwgIO - an utility class that
// performs DWG file IO.

#ifndef AC_GEDWGIO_H
#define AC_GEDWGIO_H

#include "dbfiler.h"
#include "gefileio.h"
#include "gelibver.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeDwgIO
{
public:

    // Write out to file
    //
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePoint2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeVector2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeMatrix2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeScale2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePoint2dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeVector2dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePoint3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeVector3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeMatrix3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeScale3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePoint3dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeVector3dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeTol&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeInterval&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeKnotVector&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeDoubleArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeIntArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCurveBoundary&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePosition2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePointOnCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeLine2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeLineSeg2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeRay2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCircArc2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeEllipArc2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeExternalCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCubicSplineCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeNurbCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCompositeCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeOffsetCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePolyline2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePosition3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePointOnCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePointOnSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeLine3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeRay3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeLineSeg3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePlane&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeBoundedPlane&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCircArc3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeEllipArc3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCubicSplineCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeNurbCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCompositeCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeOffsetCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePolyline3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeAugPolyline3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeExternalCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCone&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCylinder&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeTorus&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeExternalSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeOffsetSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeNurbSurface&);
    static
   Acad::ErrorStatus outFields(AcDbDwgFiler*,const AcGeExternalBoundedSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeSphere&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeBoundBlock2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeBoundBlock3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCurveCurveInt2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCurveCurveInt3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeEllipCone&);

    // Read in from file
    //
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePoint2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeVector2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeMatrix2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeScale2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePoint2dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeVector2dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePoint3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeVector3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeMatrix3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeScale3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePoint3dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeVector3dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeTol&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeInterval&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeKnotVector&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeDoubleArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeIntArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCurveBoundary&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePosition2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePointOnCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeLine2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeLineSeg2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeRay2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCircArc2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeEllipArc2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeExternalCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCubicSplineCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeNurbCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCompositeCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeOffsetCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePolyline2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePosition3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePointOnCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePointOnSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeLine3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeRay3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeLineSeg3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePlane&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeBoundedPlane&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCircArc3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeEllipArc3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCubicSplineCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCompositeCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeOffsetCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeNurbCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePolyline3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeAugPolyline3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeExternalCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCone&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCylinder&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeTorus&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeExternalSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeOffsetSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeNurbSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeExternalBoundedSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeSphere&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeBoundBlock2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeBoundBlock3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCurveCurveInt2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCurveCurveInt3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeEllipCone&);

    static const AcGeLibVersion  AcGeDwgIOVersion;
};


#pragma pack (pop)
#endif
