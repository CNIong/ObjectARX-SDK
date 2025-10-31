//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// POLYJIG.CPP
//
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "polyjig.h"
#include "dbmain.h"
#include "poly.h"
#include "adslib.h"




extern Adesk::Boolean rx_uc2wc(ads_point p, ads_point q, Adesk::Boolean vec);

AsdkPolyJig::AsdkPolyJig() : mPoly(NULL) 
{
}


AsdkPolyJig::~AsdkPolyJig()
{
}


void               
AsdkPolyJig::initializePoly(AcGePoint2d  cen,
                            AcGeVector3d norm,
                            int          numSides,
                            double elev)
{
    mPoly = new AsdkPoly();
    mPoly->setNumSides(numSides);
    mPoly->setCenter(cen);
    mPoly->setNormal(norm);
    mPoly->setElevation(elev);
}


void 
AsdkPolyJig::acquire(AcGePoint2d  cen,
                     AcGeVector3d norm,
                     TCHAR*        name,
                     AcDbObjectId tsId,
                     double elev)
{
    int numSides = 0;
    while (numSides < 3) {
        switch (acedGetInt(_T("\nEnter number of sides: "), &numSides)) {
        case RTNORM:
            if (numSides < 3)
               acutPrintf(_T("\nNeed at least 3 sides."));
            break;
        default:
            return;
        }
    } 
    initializePoly(cen, norm, numSides, elev);
    dragAcquire(_T("\nLocate start point of polygon: "), name, tsId);
}


AcDbEntity* AsdkPolyJig::entity() const
{
    return mPoly;
}


AcEdJig::DragStatus	 
AsdkPolyJig::sampler()
{
    // set the special cursor type. If no cursor type is 
    // specified then acquireXXX method selects one for you.
    //
    setSpecialCursorType(AcEdJig::kCrosshair);

    // set the user input controls. This specifies how the
    // various user actions affect the drag sequence.
    //
    setUserInputControls((UserInputControls)
	                 (kNullResponseAccepted|kAccept3dCoordinates |
	                  kDontUpdateLastPoint));
    
    AcGePoint3d   secondPoint;
    AcGePoint3d center;
    mPoly->getCenter(center);
    AcGePoint3d startPoint;
    mPoly->getStartPoint(startPoint);
    //aquires points in WCS
    DragStatus stat = AcEdJig::acquirePoint(secondPoint, center);
    if (stat == kNormal) {
	    if (center == secondPoint)
	        stat = kOther;
	    else if (startPoint == secondPoint)
	        stat = kNoChange;
        else {
            acdbWcs2Ecs(asDblArray(secondPoint),asDblArray(secondPoint),asDblArray(mPoly->normal()),Adesk::kFalse);
            AcGePoint2d sp2d(secondPoint.x,secondPoint.y);
	        mPoly->setStartPoint(sp2d) ;
            mPoly->setElevation(secondPoint.z);
        }
    } else 
    	stat = kNoChange ;

    return stat ;
}


Adesk::Boolean 
AsdkPolyJig::dragAcquire(TCHAR* promptString,
                         TCHAR* name,
                         AcDbObjectId tsId)
{
    setDispPrompt(promptString);
    AcEdJig::DragStatus stat = drag();

    switch(stat) {
    case kNormal:
        mPoly->setName(name);
        mPoly->setTextStyle(tsId);
        append();
        break ;
    case kNoChange:
        delete mPoly;
        acutPrintf(_T("The drag status is kNoChange\n"));
        break ;
    case kCancel:
        delete mPoly;
        acutPrintf(_T("The drag status is kCancel\n"));
        break ;
    case kOther:
        delete mPoly;
        acutPrintf(_T("The drag status is kOther\n"));
        acutPrintf(_T("Invalid Instance\n"));
        break ;
    case kNull:
        delete mPoly;
        acutPrintf(_T("The drag status is kNull\n"));
        break ;
    default:
        delete mPoly;
        acutPrintf(_T("The drag status is %d\n"), stat);
        break ;
    }

    mPoly = NULL;
    return (stat == kNormal) || (stat == kOther) ;
}


Adesk::Boolean	
AsdkPolyJig::update()
{
    return Adesk::kTrue;
}
