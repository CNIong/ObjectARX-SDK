#ifndef AC_GEPONSRF_H
#define AC_GEPONSRF_H
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
// class AcGePointOnSurface to keep information of a point belonging
// to a surface.

#include "gepent3d.h"
#pragma pack (push, 8)

class AcGeSurface;

class
GE_DLLEXPIMPORT
AcGePointOnSurface : public AcGePointEnt3d
{
public:
    AcGePointOnSurface();
    AcGePointOnSurface(const AcGeSurface& surf);
    AcGePointOnSurface(const AcGeSurface& surf, const AcGePoint2d& param);
    AcGePointOnSurface(const AcGePointOnSurface& src);

    // Assignment operator.
    //
    AcGePointOnSurface& operator =     (const AcGePointOnSurface& src);

    // Query functions.
    //
    const AcGeSurface*  surface        () const;
    AcGePoint2d         parameter      () const;

    // Functions to evaluate a point.
    //
    AcGePoint3d         point          () const;
    AcGePoint3d         point          (const AcGePoint2d& param );
    AcGePoint3d         point          (const AcGeSurface& surf,
                                        const AcGePoint2d& param);

    // Functions to evaluate surface normal.
    //
    AcGeVector3d        normal         () const;
    AcGeVector3d        normal         (const AcGePoint2d& param );
    AcGeVector3d        normal         (const AcGeSurface& surf,
                                        const AcGePoint2d& param);
    // Functions to evaluate derivatives.
    //
    AcGeVector3d        uDeriv         (int order) const;
    AcGeVector3d        uDeriv         (int order, const AcGePoint2d& param);
    AcGeVector3d        uDeriv         (int order, const AcGeSurface& surf,
                                        const AcGePoint2d& param);

    AcGeVector3d        vDeriv         (int order) const;
    AcGeVector3d        vDeriv         (int order, const AcGePoint2d& param);
    AcGeVector3d        vDeriv         (int order, const AcGeSurface& surf,
                                        const AcGePoint2d& param);

    // Functions to evaluate the mixed partial.
    //
    AcGeVector3d        mixedPartial   () const;
    AcGeVector3d        mixedPartial   (const AcGePoint2d& param);
    AcGeVector3d        mixedPartial   (const AcGeSurface& surf,
                                        const AcGePoint2d& param);

    // Functions to compute the tangent vector in a given direction.
    //
    AcGeVector3d        tangentVector  (const AcGeVector2d& vec) const;
    AcGeVector3d        tangentVector  (const AcGeVector2d& vec,
                                        const AcGePoint2d& param);
    AcGeVector3d        tangentVector  (const AcGeVector2d& vec,
                                        const AcGeSurface& vecSurf,
                                        const AcGePoint2d& param);

    // Functions to invert a tangent vector to parameter space.
    //
    AcGeVector2d        inverseTangentVector  (const AcGeVector3d& vec) const;
    AcGeVector2d        inverseTangentVector  (const AcGeVector3d& vec,
                                               const AcGePoint2d& param);
    AcGeVector2d        inverseTangentVector  (const AcGeVector3d& vec,
                                               const AcGeSurface& surf,
                                               const AcGePoint2d& param);
    // Set functions.
    //
    AcGePointOnSurface& setSurface     (const AcGeSurface& surf);
    AcGePointOnSurface& setParameter   (const AcGePoint2d& param);
};

#pragma pack (pop)
#endif

