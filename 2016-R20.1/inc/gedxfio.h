//
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
// This file contains the class AcGeDxfIO - an utility class that
// performs DXF file IO.

#ifndef AC_GEDXFIO_H
#define AC_GEDXFIO_H

#include "dbfiler.h"
#include "gefileio.h"
#include "gelibver.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeDxfIO
{
public:

    // Write to file
    //
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeMatrix2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeScale2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint2dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector2dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeMatrix3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeScale3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint3dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector3dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeTol&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeInterval&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeKnotVector&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeDoubleArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeIntArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCurveBoundary&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePosition2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePointOnCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLine2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLineSeg2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeRay2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCircArc2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeEllipArc2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeExternalCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCubicSplineCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeNurbCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCompositeCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeOffsetCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePolyline2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePosition3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePointOnCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePointOnSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLine3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeRay3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLineSeg3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePlane&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeBoundedPlane&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCircArc3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeEllipArc3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCubicSplineCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeNurbCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCompositeCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeOffsetCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePolyline3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeAugPolyline3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeExternalCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCone&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCylinder&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeTorus&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeExternalSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeOffsetSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeNurbSurface&);
    static
   Acad::ErrorStatus outFields(AcDbDxfFiler*,const AcGeExternalBoundedSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeSphere&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeBoundBlock2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeBoundBlock3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCurveCurveInt2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCurveCurveInt3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeEllipCone&);

    // Read from file
    //
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeMatrix2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeScale2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint2dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector2dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeMatrix3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeScale3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint3dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector3dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeTol&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeInterval&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeKnotVector&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeDoubleArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeIntArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCurveBoundary&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePosition2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePointOnCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLine2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLineSeg2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeRay2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCircArc2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeEllipArc2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCubicSplineCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeNurbCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCompositeCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeOffsetCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePolyline2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePosition3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePointOnCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePointOnSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLine3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeRay3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLineSeg3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePlane&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeBoundedPlane&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCircArc3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeEllipArc3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCubicSplineCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeNurbCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCompositeCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeOffsetCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePolyline3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeAugPolyline3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCone&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCylinder&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeTorus&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeOffsetSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeNurbSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalBoundedSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeSphere&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeBoundBlock2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeBoundBlock3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCurveCurveInt2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCurveCurveInt3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeEllipCone&);

    static const AcGeLibVersion  AcGeDxfIOVersion;
};


#pragma pack (pop)
#endif
