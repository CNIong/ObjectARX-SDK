#ifndef AC_GEEXTC3D_H
#define AC_GEEXTC3D_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// This file contains the class AcGeExternalCurve3d - A
// representation for a curve that has its definition external to
// gelib.

#include "gecurv3d.h"
#include "gearc3d.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#pragma pack (push, 8)

class AcGeLine3d;
class AcGeLineSeg3d;
class AcGeRay3d;
class AcGeEllipArc3d;
class AcGeNurbCurve3d;
class AcGeExternalCurve2d;
class AcGeExternalCurve3d;

class
GX_DLLEXPIMPORT
AcGeExternalCurve3d : public AcGeCurve3d
{
public:
    AcGeExternalCurve3d();
    AcGeExternalCurve3d(const AcGeExternalCurve3d& src);
    AcGeExternalCurve3d(void* curveDef, AcGe::ExternalEntityKind curveKind,
                            Adesk::Boolean makeCopy = Adesk::kTrue);

    Adesk::Boolean isLine     () const;
    Adesk::Boolean isRay      () const;
    Adesk::Boolean isLineSeg  () const;
    Adesk::Boolean isCircArc  () const;
    Adesk::Boolean isEllipArc () const;
    Adesk::Boolean isNurbCurve() const;
    Adesk::Boolean isDefined  () const;

    // Conversion to native gelib curve
    //
    Adesk::Boolean isNativeCurve  (AcGeCurve3d*& nativeCurve) const;
    void           getExternalCurve (void*& curveDef) const;

    // Type of the external curve.
    //
    AcGe::ExternalEntityKind externalCurveKind() const;

    // Reset surface
    //
    AcGeExternalCurve3d& set(void* curveDef, AcGe::ExternalEntityKind curveKind,
                             Adesk::Boolean makeCopy = Adesk::kTrue);
    // Assignment operator
    //
    AcGeExternalCurve3d& operator = (const AcGeExternalCurve3d& src);

    // Ownership of curve
    //
    Adesk::Boolean       isOwnerOfCurve   () const;
    AcGeExternalCurve3d& setToOwnCurve    ();
};

#pragma pack (pop)
#endif
