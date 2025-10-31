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
// Description:
//
// This program demonstrates how to use AcEdJig to provide a
// user interface for AcDbEllipse creation that's slightly
// different from that provided by AutoCAD itself.
//
// One limitation in it's current form is that if the user
// tries to make the minor axis longer than the major axis,
// then the ellipse will end up circular because the radius
// ratio cannot be larger than 1.0.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <adslib.h>
#include <dbjig.h>
#include <dbelipse.h>
#include <aced.h>
#include <geassign.h>
#include <dbapserv.h>
#include "tchar.h"



// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

class AsdkEllipseJig : public AcEdJig

// This class allows the user to create an ellipse by
// picking its center point and then dragging to select the
// desired major axis and minor axis lengths.  During the
// drag operations, the user will be able to visually see
// what the ellipse looks like at any time.
//
{
public:
    AsdkEllipseJig(const AcGePoint3d&, const AcGeVector3d&);
    void doIt();
    virtual DragStatus sampler();
    virtual Adesk::Boolean update();
    virtual AcDbEntity* entity() const;

private:
    AcDbEllipse *mpEllipse;
    AcGePoint3d mCenterPt, mAxisPt;
    AcGeVector3d mMajorAxis, mNormal;
    double mRadiusRatio;
    int mPromptCounter;
};

// The following defines the constructor that accepts a point to be used as the
// centerpoint of the ellipse and the current UCS normal
// vector to be used as the normal for the ellipse.  It
// also initializes the radius ratio to a small value so
// that during selection of the major axis, the ellipse
// will appear as a line.  The prompt counter is also
// initialized to 0.
//
AsdkEllipseJig::AsdkEllipseJig(
    const AcGePoint3d& pt,
    const AcGeVector3d& normal)
: mCenterPt(pt),
  mNormal(normal),
  mRadiusRatio(0.00001),
  mPromptCounter(0)
{
	// Calculate a proper initial offset for the major axis from the current view extents.
	//
	struct resbuf rb;
	memset (&rb, 0, sizeof (struct resbuf));
	acedGetVar (_T("VIEWSIZE"), &rb);
	double majorAxisInitialOffset = rb.resval.rreal/1000.0;
	mMajorAxis = AcGeVector3d(majorAxisInitialOffset,0,0); // Offset the major axis a bit from the center point.
}


// This function creates an AcDbEllipse object and gets the
// jig started acquiring the necessary info to properly fill
// it in.
//
void
AsdkEllipseJig::doIt()
{
    mpEllipse = new AcDbEllipse();
	mpEllipse->set(mCenterPt, mNormal, mMajorAxis, mRadiusRatio); // Set default parameters for the ellipse.

    // Get the major axis vector from the user.
    //
    // At this time, mPromptCounter == 0
    //
    setDispPrompt(_T("\nEllipse major axis: "));
    AcEdJig::DragStatus stat = drag();

    // Get the ellipse's radius ratio.
    //
    mPromptCounter++;   // now == 1
    setDispPrompt(_T("\nEllipse minor axis: "));
    stat = drag();

    // Now add the ellipse to the database's current space.
    //
    append();
}

// This function is called by the drag function to
// acquire a sample input.
//
AcEdJig::DragStatus
AsdkEllipseJig::sampler()
{
    DragStatus stat;

    setUserInputControls((UserInputControls)
        (AcEdJig::kAccept3dCoordinates
         | AcEdJig::kNoNegativeResponseAccepted
         | AcEdJig::kNoZeroResponseAccepted));

    if (mPromptCounter == 0) {

        // Aquire the major axis endpoint.
        //
        // If the newly acquired point is the same as it was
        // in the last sample, then we return kNoChange so the
        // AsdkEllipseJig::update() function will not be called and the
        // last update call will be able to finish, thus allowing
        // the ellipse to fully elaborate.
        //
        static AcGePoint3d axisPointTemp;
        stat = acquirePoint(mAxisPt, mCenterPt);
        if (axisPointTemp != mAxisPt)
            axisPointTemp = mAxisPt;
        else if (stat == AcEdJig::kNormal)
            return AcEdJig::kNoChange;
    }
    else if (mPromptCounter == 1) {

        // Aquire the distance from ellipse center to minor
        // axis endpoint. This will be used to calculate the
        // radius ratio.
        //
        // If the newly acquired distance is the same as it was
        // in the last sample, then we return kNoChange so the
        // AsdkEllipseJig::update() function will not be called and the
        // last update call will be able to finish, thus allowing
        // the ellipse to fully elaborate.
        //
        static double radiusRatioTemp = -1;
        stat = acquireDist(mRadiusRatio, mCenterPt);
        if (radiusRatioTemp != mRadiusRatio)
            radiusRatioTemp = mRadiusRatio;
        else if (stat == AcEdJig::kNormal)
            return AcEdJig::kNoChange;
    }
    return stat;
}

// This function is called to update the entity based on the
// input values.
//
Adesk::Boolean
AsdkEllipseJig::update()
{
    switch (mPromptCounter) {
    case 0:

        // At this time, mAxis contains the value of one
        // endpoint of the desired major axis.  The
        // AcDbEllipse class stores the major axis as the
        // vector from the center point to where the axis
        // intersects the ellipse path (such as half of the true
        // major axis), so we already have what we need.
        //
        mMajorAxis = mAxisPt - mCenterPt;
        break;
    case 1:

        // Calculate the radius ratio.  mRadiusRatio
        // currently contains the distance from the ellipse
        // center to the current pointer position.  This is
        // half of the actual minor axis length.  Since
        // AcDbEllipse stores the major axis vector as the
        // vector from the center point to the ellipse curve
        // (half the major axis), to get the radius ratio we
        // simply divide the value currently in mRadiusRatio
        // by the length of the stored major axis vector.
        //
        mRadiusRatio = mRadiusRatio / mMajorAxis.length();
        break;
    }

    // Now update the ellipse with the latest setting.
    //
    mpEllipse->set(mCenterPt, mNormal, mMajorAxis,
        mRadiusRatio);

    return Adesk::kTrue;
}

// This function must be implemented to return a pointer to
// the entity being manipulated by the jig.
//
AcDbEntity*
AsdkEllipseJig::entity() const
{
    return mpEllipse;
}

// This function uses the AcEdJig mechanism to create and
// drag an ellipse entity.  The creation criteria are
// slightly different from the AutoCAD command.  In this
// case, the user selects an ellipse center point and then,
// drags to visually select the major and minor axes
// lengths.  This sample is somewhat limited; if the
// minor axis ends up longer than the major axis, then the
// ellipse will just be round because the radius ratio
// cannot be greater than 1.0.
//
void
createEllipse()
{
    // First, have the user select the ellipse center point.
    // We don't use the jig for this because there is
    // nothing to see yet.
    //
    AcGePoint3d tempPt;
    struct resbuf rbFrom, rbTo;

    acedGetPoint(NULL, _T("\nEllipse center point: "),
        asDblArray(tempPt));

    // The point we just got is in UCS coordinates, but
    // AcDbEllipse works in WCS, so convert the point.
    //
    rbFrom.restype = RTSHORT;
    rbFrom.resval.rint = 1; // from UCS
    rbTo.restype = RTSHORT;
    rbTo.resval.rint = 0; // to WCS

    acedTrans(asDblArray(tempPt), &rbFrom, &rbTo,
        Adesk::kFalse, asDblArray(tempPt));

    // Now you need to get the current UCS z-Axis to be used
    // as the normal vector for the ellipse.
    //
    AcGeVector3d x = acdbHostApplicationServices()->workingDatabase()
                     ->ucsxdir();
    AcGeVector3d y = acdbHostApplicationServices()->workingDatabase()
                     ->ucsydir();
    AcGeVector3d normalVec = x.crossProduct(y);
    normalVec.normalize();

    // Create an AsdkEllipseJig object passing in the
    // center point just selected by the user and the normal
    // vector just calculated.
    //
    AsdkEllipseJig *pJig
        = new AsdkEllipseJig(tempPt, normalVec);

    // Now start up the jig to interactively get the major
    // and minor axes lengths.
    //
    pJig->doIt();

    // Now delete the jig object, since it is no longer needed.
    //
    delete pJig;
}

void
initApp()
{
    acedRegCmds->addCommand(_T("ASDK_VISUAL_ELLIPSE"),
        _T("ASDK_VELLIPSE"), _T("VELLIPSE"), ACRX_CMD_MODAL,
        createEllipse);
}

void
unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_VISUAL_ELLIPSE"));
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}

// END CODE APPEARING IN SDK DOCUMENT.
