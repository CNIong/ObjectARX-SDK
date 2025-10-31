#ifndef AC_GENURBSF_H
#define AC_GENURBSF_H
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
// Description:
//
// This file implements the class AcGeNurbSurface, a representation
// for a non-uniform, rational BSpline surface.
//

#include "gegbl.h"
#include "gesurf.h"
#include "gept3dar.h"
#include "gedblar.h"
#pragma pack (push, 8)

class AcGeKnotVector;

class
GX_DLLEXPIMPORT
AcGeNurbSurface : public AcGeSurface
{
public:
   AcGeNurbSurface();
   AcGeNurbSurface(int degreeU, int degreeV, int propsInU, int propsInV,
                   int numControlPointsInU, int numControlPointsInV,
                   const AcGePoint3d controlPoints[],
                   const double weights[],
                   const AcGeKnotVector& uKnots,
                   const AcGeKnotVector& vKnots,
                   const AcGeTol& tol = AcGeContext::gTol);
   AcGeNurbSurface(const AcGeNurbSurface& nurb);

   // Assignment.
   //
   AcGeNurbSurface& operator = (const AcGeNurbSurface& nurb);

   // Geometric properties.
   //
   Adesk::Boolean   isRationalInU      () const;
   Adesk::Boolean   isPeriodicInU      (double&) const;
   Adesk::Boolean   isRationalInV      () const;
   Adesk::Boolean   isPeriodicInV      (double&) const;

   int singularityInU () const;
   int singularityInV () const;

   // Definition data.
   //
   int            degreeInU            () const;
   int            numControlPointsInU  () const;
   int            degreeInV            () const;
   int            numControlPointsInV  () const;
   void           getControlPoints     (AcGePoint3dArray& points) const;
   Adesk::Boolean getWeights           (AcGeDoubleArray& weights) const;

   int       numKnotsInU    () const;
   void      getUKnots      (AcGeKnotVector& uKnots) const;

   int       numKnotsInV    () const;
   void      getVKnots      (AcGeKnotVector& vKnots) const;

   void      getDefinition  (int& degreeU, int& degreeV,
                             int& propsInU,	int& propsInV,
                             int& numControlPointsInU,
                             int& numControlPointsInV,
                             AcGePoint3dArray& controlPoints,
                             AcGeDoubleArray& weights,
                             AcGeKnotVector& uKnots,
                             AcGeKnotVector& vKnots) const;

   // Reset surface
   //
   AcGeNurbSurface& set     (int degreeU, int degreeV,
                             int propsInU, int propsInV,
                             int numControlPointsInU,
                             int numControlPointsInV,
                             const AcGePoint3d controlPoints[],
                             const double weights[],
                             const AcGeKnotVector& uKnots,
                             const AcGeKnotVector& vKnots,
                             const AcGeTol& tol = AcGeContext::gTol);

};

#pragma pack (pop)
#endif
