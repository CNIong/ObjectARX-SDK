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
// teselate.cpp
//
// Example of a unit circle centered at the origin that 
// depends on a viewport's view of the circle and tries
// to draw the circle with a polyline with the minimum
// number of discernible segments.

// With the VPORTS command,  you can create 4 viewports,
// click on one, zoom in on it,  click on another and back
// up from it, then do a REGENALL. All of the viewports
// will calculate the minimally-segmented polyline
// representation of the circle.  This demonstrates one
// reason why getNumPixelsInUnitSquare is needed.  This
// does not show how to optimally code this task.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"
#include "tchar.h"



const Adesk::UInt16 kRed     = 1;
const Adesk::UInt16 kYellow  = 2;
const Adesk::UInt16 kGreen   = 3;
const Adesk::UInt16 kCyan    = 4;
const Adesk::UInt16 kBlue    = 5;
const Adesk::UInt16 kMagenta = 6;


class AsdkTesselateSamp: public AcDbEntity
{
public:

    ACRX_DECLARE_MEMBERS(AsdkTesselateSamp);
protected:
    virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw *);
    void subViewportDraw(AcGiViewportDraw *);
    Acad::ErrorStatus subTransformBy(const AcGeMatrix3d &);
};

ACRX_DXF_DEFINE_MEMBERS(AsdkTesselateSamp,AcDbEntity,\
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
0,ASDKTESSELATESAMP,AsdkTesselate Sample);


Acad::ErrorStatus
AsdkTesselateSamp::subTransformBy(const AcGeMatrix3d &xfm)
{
    return Acad::eOk;
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Adesk::Boolean
AsdkTesselateSamp::subWorldDraw(AcGiWorldDraw *pW)
{
    // Draw a red 1 x 1 drawing-unit square centered at the
    // world coordinate origin and parallel to the XY-plane.
    //
    const Adesk::UInt32 num_pts = 5;
    AcGePoint3d verts[num_pts];
    verts[0] = verts[4] = AcGePoint3d(-0.5, -0.5, 0.0);
    verts[1] = AcGePoint3d( 0.5, -0.5, 0.0);
    verts[2] = AcGePoint3d( 0.5,  0.5, 0.0);
    verts[3] = AcGePoint3d(-0.5,  0.5, 0.0);

    pW->subEntityTraits().setColor(kRed);
    pW->geometry().polyline(num_pts, verts);

    // If regenType is kAcGiSaveWorldDrawForProxy then we
    // must return Adesk::kTrue, otherwise we need to return
    // Adesk::kFalse to trigger calls to our viewportDraw().
    //
    return (pW->regenType() == kAcGiSaveWorldDrawForProxy);
}


void
AsdkTesselateSamp::subViewportDraw(AcGiViewportDraw *pV)
{
    static double two_pi = atan(1.0) * 8.0;

    // Get the number of pixels on the X- and Y-edges of
    // a unit square centered at (0.0, 0.0, 0.0), in
    // world coordinates.
    //
    AcGePoint3d center(0.0, 0.0, 0.0);
    AcGePoint2d area;
    pV->viewport().getNumPixelsInUnitSquare(center, area);
   
    // If the 'area' values are negative, then we are in
    // perspective mode and the 'center' is too close or
    // in back of the viewport.
    //
    if (area.x > 0.0) {

        // Print out the number of pixels along the
        // y-axis of the unit square used in
        // getNumPixelsInUnitSquare.
        //
        AcGeVector3d norm(0.0, 0.0, 1.0);
        AcGeVector3d dir(1.0, 0.0, 0.0);
        TCHAR buf[100];
        _stprintf(buf, _T("%7.3lf"), area.y);
        pV->geometry().text(center, norm, dir, 1.0, 1.0,
            0.0, buf);

        // Draw a circle that depends on how big the circle
        // is in the viewport.  This is a problem of
        // figuring out the least number of segments needed
        // by a polyline so it doesn't look segmented.
        //
        // By the way, the worldDraw() and viewportDraw() of
        // an entity in a viewport are only called during a
        // regen and not necessarily during a ZOOM or PAN.
        // The reason is that a REGEN produces something
        // akin to a very high resolution image internally
        // that AutoCAD can zoom in or pan around,
        // until you get too close to this image or any of
        // its edges -- at which point a REGEN is internally
        // invoked for that viewport and a new internal
        // image is created (ready to be mildly zoomed and
        // panned upon.)
        //
        double radius = 0.5;
        double half_pixel_hgt = 2.0 / area.x; // in world
                                              // coords
        int num_segs = 8;
        double angle = two_pi / num_segs;

        if (half_pixel_hgt > radius / 2) {
            // The circle is around or less than the size
            // of a pixel. So generate a very small octagon.
            num_segs = 8;
        } else {
            // Given a circle centered at the origin of a
            // given 'radius' in the XY-plane, and given a
            // vertical line that intersects the X-axis at
            // 'radius - half a pixel', what is the angle
            // from the X-axis of a line segment from the
            // origin to the point where the vertical line
            // and the circle intersect?  Two pi divided by
            // this angle gives you a minimum number of
            // segments needed by a polyline to 'look' like
            // a circle and not be able to differentiate
            // the individual segments because the visual
            // differences are less than the size of a
            // pixel.  (This is not the only way to figure
            // this out but it's sufficient.)
            //
            angle = acos((radius - 1.0 / (area.x / 2.0))
                / radius);
            double d_num_segs = two_pi / angle;

            // Limit the number of segments from 8 to
            // 128 and use whole numbers for
            // this count.
            //
            if (d_num_segs < 8.0) {
                num_segs = 8;
            } else if (d_num_segs > 128.0) {
                num_segs = 128;
            } else {
                num_segs = (int)d_num_segs;
            }
        }
        // Calculate the vertices of the polyline from the
        // start, around the circle, and back to the start
        // to close the polyline.
        //
        angle = 0.0;
        double angle_inc = two_pi / (double)num_segs;

        AcGePoint3d* verts = new AcGePoint3d[num_segs + 1];

        for (int i = 0; i <= num_segs; i++,
            angle += angle_inc)
        {
            verts[i].x = center.x + radius * cos(angle);
            verts[i].y = center.y + radius * sin(angle);
            verts[i].z = center.z;
        }
        pV->geometry().polyline(num_segs + 1, verts);

        delete [] verts;
    }
}

// END CODE APPEARING IN SDK DOCUMENT.

void
addAsdkTesselateSampObject()
{
    AsdkTesselateSamp *pNewObj = new AsdkTesselateSamp;

    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord *pBlock;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlock,
        AcDb::kForWrite);

    AcDbObjectId objId;
    pBlock->appendAcDbEntity(objId, pNewObj);

    pBlockTable->close();
    pBlock->close();
    pNewObj->close();
}

void
initAsdkTesselateSamp()
{
    AsdkTesselateSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand(_T("ASDK_TESSELATE_SAMP"),
                            _T("ASDKTESSELATESAMP"),
                            _T("TESSELATESAMP"),
                            ACRX_CMD_TRANSPARENT,
                            addAsdkTesselateSampObject);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch (msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initAsdkTesselateSamp();
	    break;
	case AcRx::kUnloadAppMsg:
	    acedRegCmds->removeGroup(_T("ASDK_TESSELATE_SAMP"));
            deleteAcRxClass(AsdkTesselateSamp::desc());
    }
    return AcRx::kRetOK;
}
