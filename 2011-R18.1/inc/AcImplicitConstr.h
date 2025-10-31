
//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2007-2009 by Autodesk, Inc. 
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

#pragma once
#include "AcConstrainedGeometry.h"
#include "AcGeomConstraint.h"
#pragma pack (push, 8)

/// <summary>
/// This class represents a Perpendicular constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two lines.
/// </summary>
///
class ACDB_PORT AcPerpendicularConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcPerpendicularConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcPerpendicularConstraint();
};

/// <summary>
/// This class represents a Normal constraint node in the owning AcDbAssoc2dConstraintGroup.
/// Currently tt can only be applied between a line and circle(or arc).
/// </summary>
///
class ACDB_PORT AcNormalConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcNormalConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcNormalConstraint();
};

/// <summary>
/// This class represents a PointCurve (coincident) constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between a constrained point and a constrained curve.
/// </summary>
///
class ACDB_PORT AcPointCurveConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcPointCurveConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcPointCurveConstraint();
};

/// <summary>
/// This class represents a Colinear (coincident) constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained line.
/// </summary>
///
class ACDB_PORT AcColinearConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcColinearConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcColinearConstraint();
};

/// <summary>
/// This class represents a PointCoincidence (coincident) constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained point.
/// </summary>
///
class ACDB_PORT AcPointCoincidenceConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcPointCoincidenceConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcPointCoincidenceConstraint();
};

/// <summary>
/// This class represents a Concentric constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two circles, arcs or ellipses.
/// </summary>
///
class ACDB_PORT AcConcentricConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConcentricConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcConcentricConstraint();
};

/// <summary>
/// This class represents a Concentric constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between a point and a circle, arc or ellipse.
/// </summary>
///
class ACDB_PORT AcCenterPointConstraint: public AcConcentricConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcCenterPointConstraint);
};

/// <summary>
/// This class represents a Tangent constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained curve.
/// </summary>
///
class ACDB_PORT AcTangentConstraint : public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcTangentConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcTangentConstraint();
};

/// <summary>
/// This class represents a EqualRadius constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained circles (arcs).
/// </summary>
///
class ACDB_PORT AcEqualRadiusConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcEqualRadiusConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcEqualRadiusConstraint();
};

/// <summary>
/// This class represents a EqualDistance constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two pairs of points.
/// </summary>
///
class ACDB_PORT AcEqualDistanceConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcEqualDistanceConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcEqualDistanceConstraint();
};

/// <summary>
/// This class represents a EqualLength constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained bounded lines (not rays).
/// </summary>
///
class ACDB_PORT AcEqualLengthConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcEqualLengthConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcEqualLengthConstraint();
};

/// <summary>
/// This class represents a Parallel constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained lines.
/// </summary>
///
class ACDB_PORT AcParallelConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcParallelConstraint);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  /// <param name="bCreateImp">
  /// Input Boolean indicating whether the implementation object should be created.
  /// The default value is true.
  /// </param>
  ///
  AcParallelConstraint(bool bCreateImp = true);
};

/// <summary>
/// This class represents a Horizontal constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied on one constrained line.
/// </summary>
///
class ACDB_PORT AcHorizontalConstraint: public AcParallelConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcHorizontalConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcHorizontalConstraint();
};

/// <summary>
/// This class represents a Vertical constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied on one constrained line.
/// </summary>
///
class ACDB_PORT AcVerticalConstraint: public AcParallelConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcVerticalConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcVerticalConstraint();
};

/// <summary>
/// This class represents a EqualCurvature constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between a bounded spline and a bounded curve.
/// </summary>
///
class ACDB_PORT AcEqualCurvatureConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcEqualCurvatureConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcEqualCurvatureConstraint();
};


/// <summary>
/// This class represents a Symmetric constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two same type of constrained geometries (except spline).
/// </summary>
///
class ACDB_PORT AcSymmetricConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcSymmetricConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcSymmetricConstraint();
};

/// <summary>
/// This class represents a MidPoint constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between a point and a bounded line (not ray) or arc.
/// </summary>
///
class ACDB_PORT AcMidPointConstraint: public AcGeomConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcMidPointConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcMidPointConstraint();
};

/// <summary>
/// This class represents a Fixed constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied on any constrained geometry.
/// </summary>
///
class ACDB_PORT AcFixedConstraint : public AcGeomConstraint
{
public:
  ACRX_DECLARE_MEMBERS(AcFixedConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcFixedConstraint();
};

/// <summary>
/// This class represents a EqualHelpParameter constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two AcHelpParameter objects which belong to the same spline or ellipse.
/// </summary>
///
class ACDB_PORT AcEqualHelpParameterConstraint : public AcGeomConstraint
{
public:
  ACRX_DECLARE_MEMBERS(AcEqualHelpParameterConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcEqualHelpParameterConstraint();

  /// <summary> 
  /// Returns pointers to the two AcHelpParameter objects which this constraint is connected to.
  /// </summary>
  /// <param name="pHelpParameter1"> 
  /// The returned pointer to the first AcHelpParameter object.
  /// </param>
  /// <param name="pHelpParameter2"> 
  /// The returned pointer to the second AcHelpParameter object.
  /// </param>
  /// <returns> Returns Acad::eOk if successful. </returns>
  ///
  Acad::ErrorStatus getEqualHelpParameters(AcHelpParameter*& pHelpParameter1, AcHelpParameter*& pHelpParameter2) const;
};

/// <summary>
/// This class represents a G2Smooth composite constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between a constrained bounded spline and other constrained bounded curve.
/// It is a combination of AcTangentConstraint and AcEqualCurvatureConstraint.
/// </summary>
///
class ACDB_PORT AcG2SmoothConstraint : public AcCompositeConstraint
{
public:
  ACRX_DECLARE_MEMBERS(AcG2SmoothConstraint);

  /// <summary> default constructor. </summary>
  /// 
  AcG2SmoothConstraint();
};

#pragma pack (pop)
