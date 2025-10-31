//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Look at this file only if you are interested in how the fillet geometry is
// calculated. This file contains declaration of AssocFilletConfig class
// that is all about geometry calculation and nothing about associativity.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "dbmain.h"
#pragma pack (push, 8)

// The center of a fillet arc is the point of intersection between the two
// offsets of the filleted curves, where the offset distance is equal to the
// fillet radius.  Since the offset curves may intersect each other in more
// than one point, we need some way to classify the intersection points so
// that we use the same one during each evaluation of the fillet arc.
// This class encapsulates the data needed to make that classification.
//
// We store two pieces of data for an intersection point:
//
//    1) The configuration of the curves at the intersection point which is
//       stored in mIntersCrossingType.  This configuration is relative to the 
//       normal of the plane in which the curves lie.  Since there are two possible
//       normals to a plane, it is vital that the associative fillet evaluator
//       use a consistent normal vector for each evaluation.  When the
//       fillet evaluator intersects the two offset curves, it chooses the
//       intersection point for the fillet arc center based on the value of
//       mIntersCrossingType.
//
//       The normal vector defines a 'left' and 'right' side for each curve
//       based on the curve's parameterization.  We assume that the
//       intersection is transversal (i.e. not tangential), so there are only
//       two options here:  curve1 either crosses curve2 from left to right
//       at their intersection point, or else curve1 crosses curve2 from
//       right to left.  If in fact the intersection really is tangential, we
//       still classify it as one of these two options based on the values of
//       mIsIncoming[0] and mIsIncoming[1].
//
//    2) Whether or not each curve is coming into the fillet arc, based on the
//       curve's parameterization.  This data is stored in mIsIncoming[0] and mIsIncoming[1].
//       At a given intersect point, there are four possible fillet arcs based on
//       the four possible combinations of mIncoming[0] and mIncoming[1].
//
// These two pieces of data are sufficient to uniquely classify the intersection
// if each of the two curves is a line or arc.  However if one or both of the
// curves is an ellipse or spline, then more information may be needed.
// For instance two ellipses can intersect in four points, and two of these
// points will have mIntersCrossingType set to true and the other two will have 
// mIntersCrossingType set to false.  Therefore the correct intersection point 
// cannot be determined by mIntersCrossingType alone.  We therefore store additional 
// information such as the parameter values of the intersection point from the last 
// evaluation, which we can use to choose the correct intersection.  This is not 
// a foolproof way of choosing the intersection, but it may work in the majority 
// of cases.

class AssocFilletConfig
{
public:
    AssocFilletConfig ();
    ~AssocFilletConfig() {}

    bool isInitialized() const { return mIsInitialized; }

    void setPickPoints(const AcGePoint3d  pickPoint[2]);

    Acad::ErrorStatus initializeFromPickPoints(const AcGeCurve3d* curve[2], 
                                               double             radius);

    // Compute the fillet arc between the two curves based on the input radius and
    // the configuration data, and update (trim/extend) the input curves
    //
    Acad::ErrorStatus evaluate(bool           updateState,
                               AcGeCurve3d*   curve[2], 
                               double         radius, 
                               const bool     isTrimCurve[2],
                               bool           adjustTweakedCurves,
                               AcGeCircArc3d& filletArc);

    void transformBy(const AcGeMatrix3d&);
   
    Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;     
    Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);      
    Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;     
    Acad::ErrorStatus dxfInFields (AcDbDxfFiler*); 
    
private:
    // Return the point of intersection on the two (non-offset) curves about which 
    // the fillet arc was created. The fillet arc is created by intersecting two 
    // offset curves, and it may be the case that the original (non-offset) curves 
    // do not actually intersect. In this case, this function will return non eOk.  
    // Otherwise it will return eOk along with the intersection point
    //
    Acad::ErrorStatus getIntersectionPoint(const AcGeCurve3d* curve[2], 
                                           AcGePoint3d&       intersPoint) const;

    // Adjust the tweaked line in case its one end point is at the endpoint of the 
    // current fillet arc but the other endpoint changed. Adjust it as if its first 
    // endpoint was at the intersection of the line with the other curve. This makes 
    // the dragging behave as if the line was extended to intersect the other curve 
    // and then stretched or rotated, making it a more intuitive dragging behavior
    //
    void adjustTweakedLine(int index, AcGeCurve3d*) const;

    // Trim or extend the input curve to the input parameter
    //
    static Acad::ErrorStatus trimOrExtendCurve(AcGeCurve3d*, double param, bool isIncoming);

    // Set the value of mIntersCrossingType based on the given intersection configuration 
    // and mIsIncoming[]
    //
    Acad::ErrorStatus setIntersectionCrossingType(AcGe::AcGeXConfig config[2]);

    bool         mIsIncoming[2];
    int          mIntersCrossingType; // 1 == First curve crosess the second curve from left to right, 0 == First curve crosses from right to left
    double       mParam[2];           // Parameters at points of tangency of each curve with fillet arc
    AcGePoint3d  mArcEndPoint[2];     // Points of tangency of each curve with fillet arc
    AcGePoint3d  mIntersPoint;        // Intersection of the two (non-offset) input curves
    bool         mHaveIntersPoint;    // mIntersPoint is valid iff mHaveIntersPoint is true
    bool         mIsInitialized;      // The configuration has been intialized from the pick points
    AcGePoint3d  mPickPoint[2];       // Used when !mIsInitialized to intialize other data
};


class AcGeTolSetter
{
public:
    explicit AcGeTolSetter(double distanceTol = 1e-6, double unitValueTol = 1e-10)
    {
        mPrevTol = AcGeContext::gTol;
        AcGeContext::gTol.setEqualPoint (distanceTol);
        AcGeContext::gTol.setEqualVector(unitValueTol);
    }
    ~AcGeTolSetter()
    {
        AcGeContext::gTol = mPrevTol;
    }
private:
    AcGeTol mPrevTol;
};

#pragma pack (pop)
