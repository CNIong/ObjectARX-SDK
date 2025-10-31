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
// calculated. This file contains implementation of AssocFilletConfig class
// that is all about geometry calculation and nothing about associativity.
//
//////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include <math.h>
#include "eoktest.h"
#include "gelnsg3d.h"
#include "gearc3d.h"
#include "geell3d.h"
#include "genurb3d.h"
#include "gecomp3d.h"
#include "geintrvl.h"
#include "gecint3d.h"
#include "gemat3d.h"
#include "AssocFilletconfig.h"
#include "acdbabb.h"   // AcDb::  abbreviations
#include "adeskabb.h"  // Adesk:: abbreviations


// Could this be accomplished using some general AcGe functionality?
//
static AcGeCurve3d* getUnboundedCurve(const AcGeCurve3d* pCurve)
{
    AcGeCurve3d* pUnboundedCurve = nullptr;

    if (pCurve->isKindOf(AcGe::kLinearEnt3d))
    {
        AcGeLine3d* const pNewLine = new AcGeLine3d();
        static_cast<const AcGeLinearEnt3d*>(pCurve)->getLine(*pNewLine);
        pUnboundedCurve = pNewLine;
    }
    else if (pCurve->isKindOf(AcGe::kCircArc3d))
    {
        const AcGeCircArc3d* const pArc = static_cast<const AcGeCircArc3d*>(pCurve);
        pUnboundedCurve = new AcGeCircArc3d(pArc->center(), pArc->normal(), pArc->refVec(), pArc->radius(), 0.0, 2*M_PI);
    }
    else if (pCurve->isKindOf(AcGe::kEllipArc3d))
    {
        const AcGeEllipArc3d* const pArc = static_cast<const AcGeEllipArc3d*>(pCurve);
        pUnboundedCurve = new AcGeEllipArc3d(pArc->center(), 
                                             pArc->majorAxis(), 
                                             pArc->minorAxis(), 
                                             pArc->majorRadius(), 
                                             pArc->minorRadius());
    }
    else
    {
        pUnboundedCurve = static_cast<AcGeCurve3d*>(pCurve->copy());
    }
    return pUnboundedCurve;
}
    

static void getUnbooundedOffsetCurves(const AcGeCurve3d*     pCurve, 
                                      const AcGeVector3d&    normal, 
                                      double                 radius, // Positive radius = left, negative radius = right
                                      AcGeCurve3d*&          pUnboundedBaseCurve, // Referenced by the offset curves
                                      AcArray<AcGeCurve3d*>& offsetCurves)
{
    pUnboundedBaseCurve = nullptr;
    offsetCurves.removeAll();

    pUnboundedBaseCurve = getUnboundedCurve(pCurve);

    AcGeVoidPointerArray offsetCurvesVoid;
    pUnboundedBaseCurve->getTrimmedOffset(radius, normal, offsetCurvesVoid, AcGe::kExtend);

    for (int i = 0; i < offsetCurvesVoid.length(); i++)
    {
        if (!VERIFY(static_cast<const AcGeEntity3d*>(offsetCurvesVoid[i])->isKindOf(AcGe::kCurve3d)))
            continue;
        AcGeCurve3d* const pOffsetCurve = static_cast<AcGeCurve3d*>(offsetCurvesVoid[i]);

        AcGeVoidPointerArray simpleOffsetCurves;
        if (pOffsetCurve->isKindOf(AcGe::kCompositeCrv3d))
        {
            static_cast<AcGeCompositeCurve3d*>(offsetCurvesVoid[i])->getCurveList(simpleOffsetCurves);
        }
        else
        {
            simpleOffsetCurves.append(pOffsetCurve);
        }

        for (int i = 0; i < simpleOffsetCurves.length(); i++)
        {
            offsetCurves.append(static_cast<AcGeCurve3d*>(simpleOffsetCurves[i]));
        }
    }
}
    

static AcGeVector3d getCurveNormal(const AcGeCurve3d* pCurve)
{
    AcGePlane plane;
    if (pCurve->isKindOf(AcGe::kCircArc3d))
        return ((AcGeCircArc3d*) pCurve)->normal();
    else  if (pCurve->isKindOf(AcGe::kEllipArc3d))
        return ((AcGeEllipArc3d*) pCurve)->normal();
    else  if (pCurve->isPlanar(plane))
        return plane.normal();  // Arbitrary normal, not good
    return AcGeVector3d::kZAxis;
}


static AcGeVector3d getCurveNormal(const AcGeCurve3d* curve[2])
{
    const bool isLinear0 = curve[0]->isKindOf(AcGe::kLinearEnt3d) != 0;
    const bool isLinear1 = curve[1]->isKindOf(AcGe::kLinearEnt3d) != 0;

    if (isLinear0 && isLinear1)
    {
        const AcGeLinearEnt3d* const pLine0 = (const AcGeLinearEnt3d*)curve[0];
        const AcGeLinearEnt3d* const pLine1 = (const AcGeLinearEnt3d*)curve[1];
        const AcGeVector3d vec0 = pLine0->direction().normalize();
        const AcGeVector3d vec1 = pLine1->direction().normalize();
        AcGeVector3d normal;
        if (vec0.isCodirectionalTo(vec1))
        {
            const AcGePoint3d pnt0 = pLine0->pointOnLine();
            const AcGePoint3d pnt1 = pLine1->closestPointTo(pnt0);
            normal = vec0.crossProduct(pnt1 - pnt0);
        }
        else
        {
            normal = vec0.crossProduct(vec1);
        }
        if (!normal.isZeroLength())
            normal.normalize();
        else
            normal = AcGeVector3d::kZAxis;
        return normal;
    }
    else if (isLinear0)
    {
        return getCurveNormal(curve[1]);
    }
    else
    {
        return getCurveNormal(curve[0]);
    }
}


static void getCurveParamRange(const AcGeCurve3d* pCurve, bool& isClosed, AcGeInterval& paramInterval, double& paramPeriod)
{
    isClosed = false;
    pCurve->getInterval(paramInterval);
    paramPeriod = 0.0;

    if (!VERIFY(pCurve != nullptr))
        return;

    AcGePoint3d p0, p1;
    isClosed = pCurve->isPeriodic(paramPeriod) || 
               pCurve->isClosed()              || 
               pCurve->hasStartPoint(p0) && pCurve->hasEndPoint(p1) && p0.isEqualTo(p1);
}


// Takes into account that the curve may be periodic or closed, and returns the
// shortest distance that may happen to be over the seam or end of the curve
//
static double paramDistance(const AcGeCurve3d* pCurve, double param0, double param1)
{
    bool isClosed = false;
    AcGeInterval paramInterval;
    double paramPeriod = 0.0;
    getCurveParamRange(pCurve, isClosed, paramInterval, paramPeriod);

    double minDist = fabs(param1 - param0);

    if (paramPeriod != 0.0)
    {
        param0 = fmod(param0 + 2*paramPeriod, paramPeriod);
        param1 = fmod(param1 + 2*paramPeriod, paramPeriod);

        minDist = __min(minDist, fabs(param0 - param1 + paramPeriod));
        minDist = __min(minDist, fabs(param1 - param0 + paramPeriod));
    }
    else if (isClosed)
    {
        // Closed curve (the start and end point coincide)
        //
        double fromParam = paramInterval.lowerBound();
        double toParam   = paramInterval.upperBound();

        minDist = __min(minDist, fabs(param0 - fromParam) + fabs(param1 - toParam));
        minDist = __min(minDist, fabs(param1 - fromParam) + fabs(param0 - toParam));
    }
    return minDist;
}


// Iterates over all intersections of the offsets of the two given curves
//
class AcDbOffsetCurveIntersectionIter
{
public:
    AcDbOffsetCurveIntersectionIter(const AcGeCurve3d*  curve[2],
                                    const AcGeVector3d& normal, 
                                    double              offsetDist,
                                    bool                offsetLeft[2]);
    ~AcDbOffsetCurveIntersectionIter();

    // Returns the next intersection point between the two offset curves.
    // Also returns parametric position of the intersection. The parameterization
    // of the offset curves seems to match parameterization of the original curves,
    // therefore the parametric position is on the original curves at the closest
    // point to the offset curve intersection
    //
    bool getNext(AcGePoint3d&      intersPoint,
                 double            param[2],   
                 AcGe::AcGeXConfig config[2]);

private:
    AcGeCurve3d*          mBaseCurve[2];
    AcArray<AcGeCurve3d*> mOffsetCurves[2];
    AcGeVector3d          mNormal;
    AcGeCurveCurveInt3d   mCurrentCurveCurveInters;
    int                   mCurrentCurveIndex[2];
    int                   mCurrentIntersectionIndex;
};
    

AcDbOffsetCurveIntersectionIter::AcDbOffsetCurveIntersectionIter(const AcGeCurve3d*  curve[2],
                                                                 const AcGeVector3d& normal, 
                                                                 double              offsetDist,
                                                                 bool                offsetLeft[2])
  : mNormal(normal)
{
    mBaseCurve[0] = mBaseCurve[1] = nullptr;
    mCurrentCurveIndex[0] = mCurrentCurveIndex[1] = 0;
    mCurrentIntersectionIndex = -1; // The intersection object is not initialized

    getUnbooundedOffsetCurves(curve[0], normal, offsetLeft[0] ? offsetDist : -offsetDist, mBaseCurve[0], mOffsetCurves[0]); 
    getUnbooundedOffsetCurves(curve[1], normal, offsetLeft[1] ? offsetDist : -offsetDist, mBaseCurve[1], mOffsetCurves[1]);
}


AcDbOffsetCurveIntersectionIter::~AcDbOffsetCurveIntersectionIter()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < mOffsetCurves[i].length(); j++)
            delete mOffsetCurves[i][j];
        mOffsetCurves[i].removeAll();
        delete mBaseCurve[i];
    }
}


bool AcDbOffsetCurveIntersectionIter::getNext(AcGePoint3d&      intersPoint, 
                                              double            param[2], 
                                              AcGe::AcGeXConfig config[2])
{
    for (; mCurrentCurveIndex[0] < mOffsetCurves[0].length(); mCurrentCurveIndex[0]++)
    {
        for (; mCurrentCurveIndex[1] < mOffsetCurves[1].length(); mCurrentCurveIndex[1]++)
        {
            if (mCurrentIntersectionIndex == -1) // Not initalized
            {
                mCurrentCurveCurveInters.set(*mOffsetCurves[0][mCurrentCurveIndex[0]], 
                                             *mOffsetCurves[1][mCurrentCurveIndex[1]],
                                             mNormal);
                mCurrentIntersectionIndex = 0;
            }

            if (mCurrentIntersectionIndex < mCurrentCurveCurveInters.numIntPoints())
            {
                // Return the current intersection and advance to the next one
                //
                intersPoint = mCurrentCurveCurveInters.intPoint(mCurrentIntersectionIndex);
                mCurrentCurveCurveInters.getIntParams(mCurrentIntersectionIndex, param[0], param[1]);
                mCurrentCurveCurveInters.getIntConfigs(mCurrentIntersectionIndex, config[0], config[1]);
                mCurrentIntersectionIndex++;
                return true;
            }
            else
            {
                // All intersections used up. Mark the intersection not initialized, 
                // so that it is initialized with next curves on the next cycle of the loop
                //
                mCurrentIntersectionIndex = -1; 
            }
        }
        mCurrentCurveIndex[1] = 0; // Outer loop will advance, inner loop needs to start from to beginning
    }
    return false; // All intersections returned
}


AssocFilletConfig::AssocFilletConfig()
  : mIntersCrossingType(1), mHaveIntersPoint(false), mIsInitialized(false)
{
    mIsIncoming[0] = mIsIncoming[1] = true;
    mParam[0] = mParam[1] = 0.0;
}
    

void AssocFilletConfig::setPickPoints(const AcGePoint3d  pickPoint[2])
{
    mIsInitialized = false;
    mPickPoint[0] = pickPoint[0];
    mPickPoint[1] = pickPoint[1];
}


ErrorStatus AssocFilletConfig::initializeFromPickPoints(const AcGeCurve3d* curve[2], 
                                                        double             radius)
{
    if (!VERIFY(curve[0] != nullptr && curve[1] != nullptr))
        return eInvalidInput;

    AcGeTolSetter relaxedTol;
    const AcGeVector3d normal = getCurveNormal(curve);
    if (normal.length() < 0.5)
        return Acad::eInvalidNormal;

    bool offsetLeft[2] = { false, false, };
    for (int i = 0; i < 2; i++)
    {
        AcGePointOnCurve3d pointOnCurve;
        curve[i]->getClosestPointTo(mPickPoint[1-i], pointOnCurve);
        const AcGeVector3d vec = normal.crossProduct(pointOnCurve.deriv(1));
        offsetLeft[i] = vec.dotProduct(mPickPoint[1-i]-pointOnCurve.point()) > 0.0;
    }

    // Iterate over all intersection points between the two offset curves and 
    // find the one that is closest to the pick points
    //
    AcDbOffsetCurveIntersectionIter iter(curve, normal, radius, offsetLeft);

    double            minDist = 1e30;
    AcGePoint3d       intersPnt;
    double            param[2] = { 0.0, 0.0, };
    AcGe::AcGeXConfig config[2];

    while (iter.getNext(intersPnt, param, config))
    {
        const double dist = intersPnt.distanceTo(mPickPoint[0]) + intersPnt.distanceTo(mPickPoint[1]);
        if (dist < minDist)
        {
            // Compute directionToArc pointing in the direction to the fillet arc 
            // curve for determining if curves are incoming into the fillet arc
            //
            AcGeVector3d       directionToArc;  // The sum of two direction vectors
            AcGePointOnCurve3d pointOnCurve[2]; // Points where the fillet arc touches the curves

            for (int i = 0; i < 2; i++)
            {
                curve[i]->getClosestPointTo(intersPnt, pointOnCurve[i]);
                if (radius != 0.0)
                {
                    directionToArc += (pointOnCurve[i].point() - intersPnt).normal(); 
                }
                else
                {
                    directionToArc += (intersPnt - mPickPoint[i]).normal();
                }
            }
            for (int i = 0; i < 2; i++)
            {
                mIsIncoming[i] = directionToArc.dotProduct(pointOnCurve[i].deriv(1)) > 0.0;
            }
            if (setIntersectionCrossingType(config) != eOk)
                continue;

            mParam[0] = param[0];
            mParam[1] = param[1];
            minDist   = dist;
        }
    }
    if (minDist > 1e29)
        return eInvalidInput; // No intersection point found

    mIsInitialized = true;
    return eOk; 
}


ErrorStatus AssocFilletConfig::setIntersectionCrossingType(AcGe::AcGeXConfig config[2])
{
    ErrorStatus  err = eOk;

    if (config[0] == AcGe::kLeftRight) // Regular (crossing) intersection
    {
        mIntersCrossingType = 1;
    }
    else if (config[0] == AcGe::kRightLeft)
    {
        mIntersCrossingType = 0;
    }
    else  if (config[0] == AcGe::kLeftLeft) // Tangential intersection
    {
        if (config[1] == AcGe::kLeftLeft)
        {
            mIntersCrossingType = mIsIncoming[0] && !mIsIncoming[1] ? 1 : 0;
        }
        else  if (config[2] == AcGe::kRightRight)
        {
            mIntersCrossingType = mIsIncoming[0] && mIsIncoming[1] ? 1 : 0;
        }
        else
            err = eInvalidInput;
    }
    else  if (config[0] == AcGe::kRightRight)
    {
        if (config[1] == AcGe::kLeftLeft)
        {
            mIntersCrossingType = !mIsIncoming[0] && !mIsIncoming[1] ? 1 : 0;
        }
        else  if (config[1] == AcGe::kRightRight)
        {
            mIntersCrossingType = !mIsIncoming[0] && mIsIncoming[1] ? 1 : 0;
        }
        else
            err = eInvalidInput;
    }
    else
        err = eInvalidInput;
    return err;
}


void AssocFilletConfig::adjustTweakedLine(int index, AcGeCurve3d* pCurve) const
{
    if (!VERIFY(pCurve != nullptr))
        return;
    if (!(pCurve->isKindOf(AcGe::kLineSeg3d)))
        return;
    if (!mHaveIntersPoint)
        return; // Cannot use the intersection point of the input curves because it does not exist

    AcGeLineSeg3d* const pLineSeg = static_cast<AcGeLineSeg3d*>(pCurve);

    AcGePoint3d touchPoint;
    AcGePoint3d otherPoint;
    
    if (mIsIncoming[index])
    {
        touchPoint = pLineSeg->endPoint();
        otherPoint = pLineSeg->startPoint();
    }
    else
    {
        touchPoint = pLineSeg->startPoint();
        otherPoint = pLineSeg->endPoint();
    }
    const AcGeVector3d toTouchPointVector  = touchPoint   - otherPoint;
    const AcGeVector3d toIntersPointVector = mIntersPoint - otherPoint;

    if (touchPoint.isEqualTo(mArcEndPoint[index])             && 
        !toTouchPointVector.isParallelTo(toIntersPointVector) &&
        !toIntersPointVector.isZeroLength())
    {
        // The changed input curve (line segment) has the point that touches 
        // the fillet arc unchanged, but the angle of the line changed. 
        //
        // It looks like the line was stretched or rotated. We want to simulate as 
        // if the stretch or rotation were around the intersection of the infinite
        // line with the other curve, not around the touch point with the fillet arc

        if (pLineSeg->startPoint().isEqualTo(touchPoint))
        {
            pLineSeg->set(mIntersPoint, otherPoint);
        }
        else
        {
            pLineSeg->set(otherPoint, mIntersPoint);
        }
    }
}


void AssocFilletConfig::transformBy(const AcGeMatrix3d& trans)
{
    mArcEndPoint[0].transformBy(trans);
    mArcEndPoint[1].transformBy(trans);
    mIntersPoint   .transformBy(trans);
    mPickPoint[0]  .transformBy(trans);
    mPickPoint[1]  .transformBy(trans);

    if (trans.det() < 0) // If mirror transform, reverse mIntersCrossingType 
    {
        mIntersCrossingType = mIntersCrossingType == 1 ? 0 : 1;
    }
}


// Compute the fillet arc between the two curves based on the input radius and
// the configuration data
//
ErrorStatus AssocFilletConfig::evaluate(bool           updateState,
                                        AcGeCurve3d*   curve[2],
                                        double         radius, 
                                        const bool     isTrimCurve[2],
                                        bool           adjustTweakedCurves,
                                        AcGeCircArc3d& filletArcOut)
{
    filletArcOut = AcGeCircArc3d();
    AcGeTolSetter relaxedTol;

    if (!isInitialized())
    {
        initializeFromPickPoints(const_cast<const AcGeCurve3d**>(curve), radius);
    }

    if (adjustTweakedCurves && radius != 0.0)
    {
        for (int i = 0; i < 2; i++)
        {
            if (isTrimCurve[i])
            {
                adjustTweakedLine(i, curve[i]);
            }
        }
    }
    if (!VERIFY(isInitialized()))
        return eNotInitializedYet; // It actually means "cannot be initialized"

    const AcGeVector3d normal = getCurveNormal((const AcGeCurve3d**)curve);
    if (normal.length() < 0.5)
        return eInvalidInput;

    bool left[2] = { !mIsIncoming[1], mIsIncoming[0], };

    if (mIntersCrossingType == 0)
    {
        left[0] = !left[0];
        left[1] = !left[1];
    }

    bool         isClosed[2] = { false, false, };
    AcGeInterval paramInterval[2];
    double       paramPeriod[2] = { 0.0, 0.0, };
    getCurveParamRange(curve[0], isClosed[0], paramInterval[0], paramPeriod[0]);
    getCurveParamRange(curve[1], isClosed[1], paramInterval[1], paramPeriod[1]);

    // Find an intersection between the two offset curves that matches the configuration
    //
    AcDbOffsetCurveIntersectionIter iter((const AcGeCurve3d**)curve, normal, radius, left);

    double      minParamDist = 1e30;
    AcGePoint3d bestIntersPnt;
    double      bestParam[2] = { 0.0, 0.0, };
    AcGePoint3d intersPnt;
    double      param[2] = { 0.0, 0.0, };
    AcGe::AcGeXConfig config[2];

    while (iter.getNext(intersPnt, param, config))
    {
        // Check if configuration of this intersection point matches
        //
        if (mIntersCrossingType == 1 && config[0] == AcGe::kLeftRight || 
            mIntersCrossingType == 0 && config[0] == AcGe::kRightLeft ||
            config[0] == AcGe::kLeftLeft || config[0] == AcGe::kRightRight)
        {
            const double paramDist0 = paramDistance(curve[0], param[0], mParam[0]);
            const double paramDist1 = paramDistance(curve[1], param[1], mParam[1]);
            const double paramDist  = paramDist0 + paramDist1;
            if (paramDist < minParamDist)
            {
                minParamDist  = paramDist;
                bestIntersPnt = intersPnt;
                bestParam[0]  = param[0];
                bestParam[1]  = param[1];
            }
        }
    }
    if (minParamDist > 1e29)
        return eInvalidInput; // No intersection point found

    AcGePoint3d   arcEndPoint[2];
    AcGeCircArc3d filletArc;

    if (radius == 0.0)
    {
        filletArc = AcGeCircArc3d(bestIntersPnt, normal, 0.0); // Create a degenerate fillet arc
    }
    else
    {
        // Create a fillet arc

        AcGePointOnCurve3d pointOnCurve0, pointOnCurve1;
        arcEndPoint[0] = pointOnCurve0.point(*curve[0], bestParam[0]);
        arcEndPoint[1] = pointOnCurve1.point(*curve[1], bestParam[1]);
        const AcGeVector3d vec0 = arcEndPoint[0] - bestIntersPnt;
        const AcGeVector3d vec1 = arcEndPoint[1] - bestIntersPnt;
        AcGeVector3d vec2 = vec0.crossProduct(vec1);
        AcGeVector3d arcRefVec;
        double arcAngle = 0.0;

        if (vec2.isZeroLength())
        {
            // 180 degree arc (tangent intersection)
            //
            vec2 = pointOnCurve1.deriv(1);
            if (!mIsIncoming[0])
                vec2.negate();
            vec2 = normal.crossProduct(vec2);
            arcRefVec = vec2.dotProduct(vec1) > 0.0 ? vec1 : vec0;
            arcAngle = M_PI;
        }
        else
        {
            // Regular case where arc angle is less than 180 degrees
            //
            arcRefVec = vec2.dotProduct(normal) > 0.0 ? vec0 : vec1;
            arcAngle = vec0.angleTo(vec1);
        }
              
        filletArc = AcGeCircArc3d(bestIntersPnt, normal, arcRefVec, radius, 0.0, arcAngle);
    }

    // If requested, trim/extend the input curves to the fillet arc
    //
    if ((isTrimCurve[0] && trimOrExtendCurve(curve[0], bestParam[0], mIsIncoming[0]) != eOk) ||
        (isTrimCurve[1] && trimOrExtendCurve(curve[1], bestParam[1], mIsIncoming[1]) != eOk))
    {
        return eInvalidInput;
    }

    if (updateState)
    {
        // Update the cached data
        //
        mParam[0] = bestParam[0];
        mParam[1] = bestParam[1];

        if (radius == 0.0)
        {
            mArcEndPoint[0] = mArcEndPoint[1] = mIntersPoint = filletArc.center();
        }
        else
        {
            mArcEndPoint[0] = arcEndPoint[0];
            mArcEndPoint[1] = arcEndPoint[1];
            mHaveIntersPoint = getIntersectionPoint((const AcGeCurve3d**)curve, mIntersPoint) == eOk;
        }
    }
    filletArcOut = filletArc;
    return eOk; 
}


ErrorStatus AssocFilletConfig::trimOrExtendCurve(AcGeCurve3d* pCurve, double param, bool isIncoming)
{
    bool         isClosed = false;
    AcGeInterval paramInterval;
    double       paramPeriod = 0.0;
    getCurveParamRange(pCurve, isClosed, paramInterval, paramPeriod);

    if (paramPeriod != 0.0)
        return eOk; // Doesn't make sense to trim periodic curves

    if (isIncoming)
    {
        if (paramPeriod > 0.0)
        {
            if (param <= paramInterval.lowerBound())
                param += paramPeriod;
        }
        paramInterval.setUpper(param); 
    }
    else
    {
        if (paramPeriod > 0.0)
        {
            if (param >= paramInterval.upperBound())
                param -= paramPeriod;
        }
        paramInterval.setLower(param);
    }
    if (paramInterval.isBoundedBelow() && 
        paramInterval.isBoundedAbove() && 
        paramInterval.lowerBound() >= paramInterval.upperBound())
    {
        return eInvalidInput;
    }

    pCurve->setInterval(paramInterval);

    AcGe::EntityId degenerateType;
    if (pCurve->isDegenerate(degenerateType))
        return eInvalidInput;
    return eOk;
}


ErrorStatus AssocFilletConfig::getIntersectionPoint(const AcGeCurve3d* curve[2], 
                                                    AcGePoint3d&       intersPoint) const
{
    intersPoint = AcGePoint3d::kOrigin;

    if (!VERIFY(curve[0] != nullptr && curve[1] != nullptr))
        return eNullPtr;

    AcGeCurve3d* pUnboundedCurve[2] = { getUnboundedCurve(curve[0]), getUnboundedCurve(curve[1]), };
    std::unique_ptr<AcGeCurve3d> delete0(pUnboundedCurve[0]);
    std::unique_ptr<AcGeCurve3d> delete1(pUnboundedCurve[1]);

    bool doNotTrimCurves[2] = { false, false, };
    AcGeCircArc3d filletArc;
    AssocFilletConfig config = *this;
    ErrorStatus err = config.evaluate(false/*updateState*/, pUnboundedCurve, 0.0/*radius*/, doNotTrimCurves, false, filletArc);
    if (err == eOk)
    {
        intersPoint = filletArc.center();
    }
    return err;
}


ErrorStatus AssocFilletConfig::dwgOutFields(AcDbDwgFiler* pFiler) const
{
    pFiler->writeBool   (mIsIncoming[0]);
    pFiler->writeBool   (mIsIncoming[1]);
    pFiler->writeInt32  (mIntersCrossingType);
    pFiler->writeDouble (mParam[0]);
    pFiler->writeDouble (mParam[1]);
    pFiler->writePoint3d(mArcEndPoint[0]);
    pFiler->writePoint3d(mArcEndPoint[1]);
    pFiler->writeBool   (mHaveIntersPoint);
    if (mHaveIntersPoint)
        pFiler->writePoint3d(mIntersPoint);
    pFiler->writeBool   (mIsInitialized);
    if (!mIsInitialized)
    {
        pFiler->writePoint3d(mPickPoint[0]);
        pFiler->writePoint3d(mPickPoint[1]);
    }
    return pFiler->filerStatus();
}


ErrorStatus AssocFilletConfig::dwgInFields(AcDbDwgFiler* pFiler)
{
    pFiler->readBool   (&mIsIncoming[0]);
    pFiler->readBool   (&mIsIncoming[1]);
    pFiler->readInt32  ((Int32*)(&mIntersCrossingType));
    pFiler->readDouble (&mParam[0]);
    pFiler->readDouble (&mParam[1]);
    pFiler->readPoint3d(&mArcEndPoint[0]);
    pFiler->readPoint3d(&mArcEndPoint[1]);
    pFiler->readBool   (&mHaveIntersPoint);
    if (mHaveIntersPoint)
        pFiler->readPoint3d(&mIntersPoint);
    pFiler->readBool   (&mIsInitialized);
    if (!mIsInitialized)
    {
        pFiler->readPoint3d(&mPickPoint[0]);
        pFiler->readPoint3d(&mPickPoint[1]);
    }
    return pFiler->filerStatus();
}


ErrorStatus AssocFilletConfig::dxfOutFields(AcDbDxfFiler* pFiler) const
{
    pFiler->writeBool   (AcDb::kDxfBool,   mIsIncoming[0]);
    pFiler->writeBool   (AcDb::kDxfBool+1, mIsIncoming[1]);
    pFiler->writeInt32  (AcDb::kDxfInt32,  mIntersCrossingType);
    pFiler->writeDouble (AcDb::kDxfReal+1, mParam[0]);
    pFiler->writeDouble (AcDb::kDxfReal+2, mParam[1]);
    pFiler->writePoint3d(kDxfXCoord,       mArcEndPoint[0]);
    pFiler->writePoint3d(kDxfXCoord+1,     mArcEndPoint[1]);
    pFiler->writeBool   (AcDb::kDxfBool+3, mHaveIntersPoint);
    pFiler->writePoint3d(kDxfXCoord+2,     mIntersPoint);
    pFiler->writeBool   (AcDb::kDxfBool+4, mIsInitialized);
    pFiler->writePoint3d(kDxfXCoord+3,     mPickPoint[0]);
    pFiler->writePoint3d(kDxfXCoord+4,     mPickPoint[1]);
    return pFiler->filerStatus();
}


ErrorStatus AssocFilletConfig::dxfInFields(AcDbDxfFiler* pFiler)
{
    ErrorStatus  err = eOk;
    resbuf rb;

    while ((err = pFiler->readResBuf(&rb)) == eOk)
    {
        switch (rb.restype) 
        {
            case AcDb::kDxfBool:
                mIsIncoming[0] = rb.resval.rint != 0;
                break;
            case AcDb::kDxfBool+1:
                mIsIncoming[1] = rb.resval.rint != 0;
                break;
            case AcDb::kDxfInt32:
                mIntersCrossingType = rb.resval.rint;
                break;
            case AcDb::kDxfBool+3:
                mHaveIntersPoint = rb.resval.rint != 0;
                break;
            case AcDb::kDxfBool+4:
                mIsInitialized = rb.resval.rint != 0;
                break;
            case AcDb::kDxfReal+1:
                mParam[0] = rb.resval.rreal;
                break;
            case AcDb::kDxfReal+2:
                mParam[1] = rb.resval.rreal;
                break;
            case AcDb::kDxfXCoord:
                mArcEndPoint[0][0] = rb.resval.rpoint[X];
                mArcEndPoint[0][1] = rb.resval.rpoint[Y];
                mArcEndPoint[0][2] = rb.resval.rpoint[Z];
                break;
            case AcDb::kDxfXCoord+1:
                mArcEndPoint[1][0] = rb.resval.rpoint[X];
                mArcEndPoint[1][1] = rb.resval.rpoint[Y];
                mArcEndPoint[1][2] = rb.resval.rpoint[Z];
                break;
            case AcDb::kDxfXCoord+2:
                mIntersPoint[0] = rb.resval.rpoint[X];
                mIntersPoint[1] = rb.resval.rpoint[Y];
                mIntersPoint[2] = rb.resval.rpoint[Z];
                break;
            case AcDb::kDxfXCoord+3:
                mPickPoint[0][0] = rb.resval.rpoint[X];
                mPickPoint[0][1] = rb.resval.rpoint[Y];
                mPickPoint[0][2] = rb.resval.rpoint[Z];
                break;
            case AcDb::kDxfXCoord+4:
                mPickPoint[1][0] = rb.resval.rpoint[X];
                mPickPoint[1][1] = rb.resval.rpoint[Y];
                mPickPoint[1][2] = rb.resval.rpoint[Z];
                break;
            default:
                pFiler->pushBackItem();
                err = eInvalidDxfCode;
                break;
        }
    }
    return err;
}
