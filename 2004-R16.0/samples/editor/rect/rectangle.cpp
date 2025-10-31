// (C) Copyright 1990-2002 by Autodesk, Inc. 
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

// Description:
//
// This program duplicates but enhanses the autolisp rectangle 
// command, formerly in acadr14.lsp, but uses AcEdJig to be able 
// to adjust for the current ucs normal. In addition, elevation, and
// thickness are supported. Note that sysvars are NOT changed by this
// command. ie plinewid, chamfera, chamferb, elevation, are NOT affected
// by this command.
//
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <aced.h>
#include <dbjig.h>
#include <geassign.h> // asDblArray()
#include <dbpl.h>     // lwpoly stuff.
#include <dbxutil.h>  // acdbWcs2Ecs() & acdbUcs2Ecs()
#include <dbapserv.h>
#include <rxregsvc.h>

#include <acedads.h>
#include <adscodes.h>

#include "DataMgr.h"
#include "appinfo.h"

// ----------------------------------------------------------------------------
// Some defines used.
//
#define ZERO    1e-10
#define PI      ((double)3.14159265358979323846)

#define MAKEUCSCOORD(x, y)      tmpPoint = (y); \
acdbWcs2Ecs(asDblArray(tmpPoint), asDblArray(tmpPoint), asDblArray(m_vecUnitZ),\
Adesk::kFalse); x[X] = tmpPoint[X]; x[Y] = tmpPoint[Y];

// ----------------------------------------------------------------------------
// A couple of helper functions.
//
bool inPaperSpace();
void createRect(void);
int  getIntSysVar(char* pszVarName);
bool setIntSysVar(char* pszVarName);
bool univec(AcGeVector3d& ap, AcGeVector3d& bp);
int  indexOfKeyWord(const char* keyWord, const char* initList);

//-----------------------------------------------------------------------------
//
class CRectInfo {
public:
    CRectInfo();

    AcGePoint3d     m_topLeftCorner;    // First point selection.
    double          m_first;            // First Chamfer distance.
    double          m_second;           // Second Chamfer distance.
    double          m_bulge;            // Bulge value.
    double          m_elev;             // Elevation.
    double          m_thick;            // Thickness.
    double          m_width;            // Width.
    double          m_radius;           // Fillet radius.
    bool            m_cornerTreatment;  // Filleting or chamfering.
    bool            m_elevHandSet;
    // m_chamfDirUnitVec is the vector direction of the chamfer of the
    // top left corner of the rectangle. The chamfer opposite the top left
    // corner will have the same vector direction and the ones on the
    // alternate corners will be perpendicular to this one.
    //
    AcGeVector3d    m_chamfDirUnitVec;  
};

AsdkDataManager<CRectInfo> rectDataMgr; // MDI Safe
#define plineInfo rectDataMgr.docData()

// ----------------------------------------------------------------------------
// Constructor.
//
CRectInfo::CRectInfo()
{
    m_topLeftCorner = AcGePoint3d();
    m_first = m_second = m_bulge = m_elev = m_thick = m_width = m_radius = 0.0;
    m_cornerTreatment = FALSE;
    m_elevHandSet = FALSE;
}

//-----------------------------------------------------------------------------
// This class allows the user to create a rectangle by
// picking it's alternate corners
//
class AsdkRectangleJig : public AcEdJig
{
public:
    AsdkRectangleJig();

    virtual DragStatus sampler();
    virtual Adesk::Boolean update();
    virtual AcDbEntity* entity() const;

    void    doRectangle();

    AcGePoint3d samplerCorner;
private:
    AcDbPolyline*   m_pLWPoly;
    AcGePoint3d     m_TopLeftCorner;
    AcGePoint3d     m_TopRightCorner;
    AcGePoint3d     m_BottomLeftCorner;
    AcGePoint3d     m_BottomRightCorner;
    AcGeVector3d    m_vecUnitZ;       // Unit vectors in the UCS plane
    AcGeVector3d    m_vecUnitX;
    AcGeVector3d    m_vecUnitY;
};

//-----------------------------------------------------------------------------
// Constructor that accepts a reference to a CRectInfo class which
// contains all the information need to initialize the polyline entitiy
// that will be used for dragging and ultimately be the polyline that
// gets to the database if all goes well. 
//
AsdkRectangleJig::AsdkRectangleJig()
{ 
    m_pLWPoly = new AcDbPolyline();
    samplerCorner = AcGePoint3d();
    plineInfo.m_cornerTreatment = plineInfo.m_first != 0.0
        || plineInfo.m_second != 0.0
        || plineInfo.m_radius != 0.0;

    // Now need to get the current UCS Z-Axis to be used as the normal vector 
    // for the rectangle. At the same time, we get the x and y unit direction 
    // vectors used later.
    //
    if(inPaperSpace()) {
      m_vecUnitX = acdbHostApplicationServices()->workingDatabase()->pucsxdir();
      m_vecUnitY = acdbHostApplicationServices()->workingDatabase()->pucsydir();
    } else {
      m_vecUnitX = acdbHostApplicationServices()->workingDatabase()->ucsxdir();
      m_vecUnitY = acdbHostApplicationServices()->workingDatabase()->ucsydir();
    }

    m_vecUnitZ = m_vecUnitX.crossProduct(m_vecUnitY);

    // Convert the incomming UCS point to ECS coordinate system
    //
    acdbUcs2Ecs(asDblArray(plineInfo.m_topLeftCorner), 
        asDblArray(m_TopLeftCorner), asDblArray(m_vecUnitZ), Adesk::kFalse);
    acdbUcs2Ecs(asDblArray(plineInfo.m_topLeftCorner), 
        asDblArray(plineInfo.m_topLeftCorner), asDblArray(m_vecUnitZ),
        Adesk::kFalse);
    AcGePoint2d initPoint;
    initPoint = AcGePoint2d(m_TopLeftCorner[X], m_TopLeftCorner[Y]);

    // If the user has set the elev option from the main command prompt,
    // then this will be the default until the user again sets it to 0.0.
    // If however the user simply picks a point with or without an object
    // snap, then use the Z value of the first point picked.
    //
    if (plineInfo.m_elevHandSet == TRUE)
        m_pLWPoly->setElevation(plineInfo.m_elev);
    else
        m_pLWPoly->setElevation(m_TopLeftCorner[Z]);

    // If we are indeed filleting or chamfering the corners, then
    // we'll add the extra verticies here to have their bulges and
    // distances from the real corner changed on the fly.
    // 
    if (plineInfo.m_cornerTreatment == TRUE) {
        for (int i = 0 ; i < 8; i++)
                m_pLWPoly->addVertexAt(i, initPoint);
    } else {
        for (int i = 0 ; i < 4; i++)
                m_pLWPoly->addVertexAt(i, initPoint);
    }

    m_pLWPoly->setNormal(m_vecUnitZ);
    m_pLWPoly->setClosed(Adesk::kTrue);
    m_pLWPoly->setThickness(plineInfo.m_thick);
    m_pLWPoly->setConstantWidth(plineInfo.m_width);
    // Get the current default linetype scale
    m_pLWPoly->setLinetypeScale(acdbHostApplicationServices()
        ->workingDatabase()->celtscale());
    // Now for jig dragger purposes, convert the point back to world
    // coordinates.
    //
    acdbEcs2Wcs(asDblArray(m_TopLeftCorner), 
        asDblArray(m_TopLeftCorner), asDblArray(m_vecUnitZ), Adesk::kFalse);
    acdbEcs2Wcs(asDblArray(plineInfo.m_topLeftCorner), 
        asDblArray(plineInfo.m_topLeftCorner), asDblArray(m_vecUnitZ),
        Adesk::kFalse);
}

//-----------------------------------------------------------------------------
// This function creates an AcDbPolyline object after the
// jig startes and aquires the necessary vertex for the opposite 
// corner from the drag samples.
//
void AsdkRectangleJig::doRectangle()
{
    AcEdJig::DragStatus stat;

    setDispPrompt("\nOther corner: ");

    // Get the other corner now.
    //
    stat = drag();

    // Now add the polyline rectangle to the database's current space
    // if we return a kNormal stat from drag(). If we don't then delete
    // the polyline.
    //        
    if (stat == kNormal) 
        append();
    else
        delete m_pLWPoly;
}

//-----------------------------------------------------------------------------
// This function is called by the drag function in order to
// aquire a sample input
//
AcEdJig::DragStatus AsdkRectangleJig::sampler()
{
    DragStatus stat = kNormal;

    setUserInputControls((UserInputControls)
        (   AcEdJig::kNoNegativeResponseAccepted
         |  AcEdJig::kNoZeroResponseAccepted)
        );
   
    setSpecialCursorType(kCrosshair);

    stat = acquirePoint(m_BottomRightCorner, plineInfo.m_topLeftCorner);  

    // Now project the point at the crosshairs to the ECS of the 
    // polyline being drawn.
    //
    AcGePlane planeParallelToUCS(m_TopLeftCorner, m_vecUnitZ);    
    m_BottomRightCorner = m_BottomRightCorner.project(planeParallelToUCS, m_vecUnitZ);

    // If the newly acquired point is the same as it was
    // in the last sample, then we return kNoChange so that
    // AsdkRectangleJig::update() will not be called and the
    // last update call will be able to finish thus allowing
    // the polyline to fully elaborate.
    //
    if (samplerCorner != m_BottomRightCorner) {
        // m_BottomRightCorner will be used to update the remaining corners
        // in AsdkRectangleJig::update() below.
        //
        samplerCorner = m_BottomRightCorner;        
    } else if (stat == AcEdJig::kNormal)
        return AcEdJig::kNoChange;

    return stat;
}

//-----------------------------------------------------------------------------
// This function is called to update the entity based on the
// input values
//
Adesk::Boolean AsdkRectangleJig::update()
{
    AcGePoint2d adjustedPoint;
    AcGePoint3d tmpPoint;       // Used by MAKEUCSCOORD macro.

    // We'll use the AcGeLine::intersectWith() function to infer the
    // remaining points.
    //
    AcGeLine3d lineX, lineY;
    lineX.set(m_TopLeftCorner, m_vecUnitX);
    lineY.set(m_BottomRightCorner, m_vecUnitY);
    // Top right corner is intersection of lineX and lineY.
    //
    lineX.intersectWith(lineY, m_TopRightCorner);

    lineX.set(m_BottomRightCorner, m_vecUnitX);
    lineY.set(m_TopLeftCorner, m_vecUnitY);
    // Bottom left corner is intersection of lineX and lineY.
    //
    lineX.intersectWith(lineY, m_BottomLeftCorner);

    AcGeVector3d tmpXVec, tmpYVec;
    // Check to see if we have flipped around the X or Y axis.
    //
    bool bXFlip = m_vecUnitX.dotProduct(m_TopLeftCorner - m_TopRightCorner)  >0;
    bool bYFlip = m_vecUnitY.dotProduct(m_TopLeftCorner - m_BottomLeftCorner)<0; 

    // If the rectangle is dragged into the first or third quadrant,
    // we need to reverse the sign of the bulge as well as reverse
    // the x and y direction vectors.
    //
    tmpXVec = bXFlip ? -1 * m_vecUnitX : m_vecUnitX;
    tmpYVec = bYFlip ? -1 * m_vecUnitY : m_vecUnitY;
   
    // Now update the polyline with the latest setting
    //
    if (plineInfo.m_cornerTreatment) {
        // We are going to fillet of chamfer this polyline rectangle. As such,
        // the constructor has added the extra points at the corners to allow
        // for there placement and bulge values to be updated on the fly.
        // If, during the dragging, the rectangle is still too small to show the
        // given radius or chamfer edges, the we will put the extra points in the 
        // corners and set the bulges to 0.0, so the rectangle retains its 
        // square corners until the user stretches the rectangle to a size large
        // enough to have the corner treatment displayed.
        //

        // Use temporaries to see if we're too small to show fillet/chamfer, so
        // we don't need to convert back to world.
        // 
        AcGePoint2d point_TL, point_TR, point_BL;
        MAKEUCSCOORD(point_TL, m_TopLeftCorner);
        MAKEUCSCOORD(point_TR, m_TopRightCorner);
        MAKEUCSCOORD(point_BL, m_BottomLeftCorner);

        bool tooSmall = (point_TL.distanceTo(point_TR)
            < plineInfo.m_first + plineInfo.m_second)
            || (point_TL.distanceTo(point_BL)
            < plineInfo.m_first + plineInfo.m_second);
        if (tooSmall) {
            // Still to small to show the corner treatment.
            //
            m_pLWPoly->setBulgeAt(0, 0.0);
            MAKEUCSCOORD(adjustedPoint, m_TopLeftCorner);
            m_pLWPoly->setPointAt(0, adjustedPoint);
            m_pLWPoly->setPointAt(1, adjustedPoint);

            m_pLWPoly->setBulgeAt(2, 0.0);  
            MAKEUCSCOORD(adjustedPoint, m_TopRightCorner);
            m_pLWPoly->setPointAt(2, adjustedPoint);
            m_pLWPoly->setPointAt(3, adjustedPoint);

            m_pLWPoly->setBulgeAt(4, 0.0);  
            MAKEUCSCOORD(adjustedPoint, m_BottomRightCorner);
            m_pLWPoly->setPointAt(4, adjustedPoint);
            m_pLWPoly->setPointAt(5, adjustedPoint);

            m_pLWPoly->setBulgeAt(6, 0.0);  
            MAKEUCSCOORD(adjustedPoint, m_BottomLeftCorner);
            m_pLWPoly->setPointAt(6, adjustedPoint);
            m_pLWPoly->setPointAt(7, adjustedPoint);
        } else {
            double tmpBulge;

            tmpBulge = ((!bXFlip && !bYFlip) || (bXFlip && bYFlip))
                ? plineInfo.m_bulge : -plineInfo.m_bulge;

            // Now we will set adjustedPoint to the intersection of the rectangle
            // sides with the place where the new end points will be.
            //
            m_pLWPoly->setBulgeAt(0, tmpBulge);
            MAKEUCSCOORD(adjustedPoint,
                m_TopLeftCorner + (-plineInfo.m_first * tmpYVec));
            m_pLWPoly->setPointAt(0, adjustedPoint);
                   
            MAKEUCSCOORD(adjustedPoint,
                m_TopLeftCorner + plineInfo.m_second * tmpXVec);
            m_pLWPoly->setPointAt(1, adjustedPoint);
    
            m_pLWPoly->setBulgeAt(2, tmpBulge); 
            MAKEUCSCOORD(adjustedPoint,
                m_TopRightCorner + (-plineInfo.m_first * tmpXVec));
            m_pLWPoly->setPointAt(2, adjustedPoint);

            MAKEUCSCOORD(adjustedPoint,
                m_TopRightCorner + (-plineInfo.m_second * tmpYVec));
            m_pLWPoly->setPointAt(3, adjustedPoint);
    
            m_pLWPoly->setBulgeAt(4, tmpBulge);
            MAKEUCSCOORD(adjustedPoint,
                m_BottomRightCorner + plineInfo.m_first * tmpYVec);
            m_pLWPoly->setPointAt(4, adjustedPoint);
            
            MAKEUCSCOORD(adjustedPoint,
                m_BottomRightCorner + (-plineInfo.m_second * tmpXVec));
            m_pLWPoly->setPointAt(5, adjustedPoint);

            m_pLWPoly->setBulgeAt(6, tmpBulge);
            MAKEUCSCOORD(adjustedPoint,
                m_BottomLeftCorner + plineInfo.m_first * tmpXVec);
            m_pLWPoly->setPointAt(6, adjustedPoint);
            
            MAKEUCSCOORD(adjustedPoint,
                m_BottomLeftCorner + plineInfo.m_second * tmpYVec);
            m_pLWPoly->setPointAt(7, AcGePoint2d(adjustedPoint[X],
                adjustedPoint[Y]));
        }
    } else {
        // If this polyline is not having its corners treated, ie chamfered, or 
        // filleted then simply update the corners. Since we knew this ahead of 
        // time, the constructor did not add any extra verticies at the corners.
        //
        MAKEUCSCOORD(adjustedPoint, m_TopLeftCorner);
        m_pLWPoly->setPointAt(0, adjustedPoint);

        MAKEUCSCOORD(adjustedPoint, m_TopRightCorner);
        m_pLWPoly->setPointAt(1, adjustedPoint);

        MAKEUCSCOORD(adjustedPoint, m_BottomRightCorner);
        m_pLWPoly->setPointAt(2, adjustedPoint);

        MAKEUCSCOORD(adjustedPoint, m_BottomLeftCorner);
        m_pLWPoly->setPointAt(3, adjustedPoint);
    } 
    return Adesk::kTrue;
}

//-----------------------------------------------------------------------------
// This function must be implemented to return a pointer to
// the entity being manipulated by the jig.
//
AcDbEntity* AsdkRectangleJig::entity() const
{
    return m_pLWPoly;
}

//-----------------------------------------------------------------------------
// 
bool inPaperSpace()
{
    return (getIntSysVar(/*NOXLATE*/"TILEMODE") == 0) && (getIntSysVar(/*NOXLATE*/"CVPORT") == 1);
}

//-----------------------------------------------------------------------------
// Uses acedGetVar() to get the sysvars.
//
int getIntSysVar(char* pszVarName)
{   
    struct resbuf rb;

    acedGetVar(pszVarName,&rb);

    return(rb.resval.rint);
}

//-----------------------------------------------------------------------------
// Uses acedSetvar() to set the sysvars.
//
bool setIntSysVar(char* pszVarName, int val)
{   
    struct resbuf rb;

    rb.restype = RTSHORT;
    rb.resval.rint = val;

    return (acedSetVar(pszVarName,&rb) == RTNORM);
}

//-----------------------------------------------------------------------------
// Turn the given vector into a unit vector with the same direction.
//
bool univec(AcGeVector3d& ap, AcGeVector3d& bp)
{
    double d;

    if ((d = (bp[X] * bp[X] + bp[Y] * bp[Y] + bp[Z] * bp[Z])) <= (ZERO * ZERO))
        return FALSE;
    d = 1.0 / sqrt(d);
    ap[X] = bp[X] * d;
    ap[Y] = bp[Y] * d;
    ap[Z] = bp[Z] * d;
    return TRUE;
}

//-----------------------------------------------------------------------------
// Returns an index for the keyWord in initList.
//
int  indexOfKeyWord(const char* keyWord, const char* initList)
{
    char* spaceAfterKW = NULL;
    char* tmpPtr       = NULL;
    char* kwPosition   = NULL;
    int i = 0;

    // Set the tmpPtr to the character after the first underscore. This
    // will be the start of the non-translated strings. 
    // acedGetInput() returns English!
    //
    // Bypass the const'ness of initList.
    tmpPtr = strstr(initList, *&(initList));
    kwPosition = strstr(tmpPtr, keyWord);

    while(spaceAfterKW < kwPosition) {
        spaceAfterKW = strstr(tmpPtr, " ");
        if (spaceAfterKW == NULL || spaceAfterKW > kwPosition) 
            break;
        tmpPtr = spaceAfterKW + 1;
        i++;
    }
    return i;
}
//-----------------------------------------------------------------------------
// This function uses the AcEdJig mechanism to create and
// drag the polyline entity.  
//
void createRect()
{
    // First have the user select the first corner point.
    // We don't use the Jig for this because there is
    // nothing to see yet.
    //
    int stat, oldOrthoMode;
    int terminated = FALSE;
    char keyWord[10];

    plineInfo.m_elevHandSet = plineInfo.m_elev != 0.0; 

    // Since it looks quite strange to have orthomode on while trying to draw a
    // rectangle, we'll temporarily turn it off. Remembering the current setting
    // and resetting it when we leave.
    //
    oldOrthoMode = getIntSysVar(/*NOXLATE*/"ORTHOMODE");
    setIntSysVar(/*NOXLATE*/"ORTHOMODE", 0);

    // Flip to the graphic screen
    //
    acedGraphScr();

    // Add value line.
    if ((plineInfo.m_first != 0.0 && plineInfo.m_second != 0 && plineInfo.m_radius == 0.0) ||
        (plineInfo.m_elev != 0) ||(plineInfo.m_radius != 0)||(plineInfo.m_thick != 0) ||
        (plineInfo.m_width != 0))
    {
        acutPrintf("\nRectangle modes:  ");
        if (plineInfo.m_first != 0.0 && plineInfo.m_second != 0.
            && plineInfo.m_radius == 0.0)
        {
            acutPrintf("Chamfer=%.16q0 x %.16q0 ",
                plineInfo.m_first, plineInfo.m_second);
        }
        if (plineInfo.m_elev != 0.)
            acutPrintf("Elevation=%.16q0  ", plineInfo.m_elev);
        if (plineInfo.m_radius != 0.)
            acutPrintf("Fillet=%.16q0  ", plineInfo.m_radius);
        if (plineInfo.m_thick != 0.)
            acutPrintf("Thickness=%.16q0  ", plineInfo.m_thick);
        if (plineInfo.m_width != 0.)
            acutPrintf("Width=%.16q0  ", plineInfo.m_width);
        acutPrintf("\n");
    }

    while(!terminated) {
        // Main prompt for user input.
        //
        acedInitGet(RSG_NONULL, "Chamfer Elevation Fillet Thickness Width");
        if ((stat = acedGetPoint(NULL,
            "\nChamfer/Elevation/Fillet/Thickness/Width/<First corner>: ",
            asDblArray(plineInfo.m_topLeftCorner)))== RTKWORD)
        {
            acedGetInput(keyWord);
        }
        else {
            if (stat == RTCAN)
                terminated = TRUE;
            break;
        }
        switch(indexOfKeyWord(keyWord,
            "Chamfer Elevation Fillet Thickness Width"))
        {
    // Chamfer;
        case 0:
            // Retrieve the first chamfer distance. 
            //
            acutPrintf("\nFirst chamfer distance for rectangles <%.16q0>: ", 
                plineInfo.m_first == 0.0
                ? plineInfo.m_radius : plineInfo.m_first);
            if ((stat = acedGetDist(NULL, NULL, &plineInfo.m_first)) == RTCAN)
            {
                terminated = TRUE;
                break;
            } else if (stat == RTNONE && plineInfo.m_first == 0.0)
                plineInfo.m_second = plineInfo.m_radius;

            // Retrieve the second chamfer distance. 
            //
            acutPrintf("\nSecond chamfer distance for rectangles <%.16q0>: ", 
                plineInfo.m_second == 0.0
                ? plineInfo.m_first : plineInfo.m_second);
            if ((stat = acedGetDist(NULL, NULL, &plineInfo.m_second)) == RTCAN)
            {
                plineInfo.m_first = 0.0;
                plineInfo.m_second= 0.0;
                terminated = TRUE;
            } else {
                if (stat == RTNONE && plineInfo.m_second == 0.0)
                    plineInfo.m_second = plineInfo.m_first;
                // If we actually set the chamfer distances, then zero out the
                // radius and bulge.
                //
                plineInfo.m_radius = 0.0;
                plineInfo.m_bulge  = 0.0;
            }
            break;
    // Elevation;
        case 1:
            // Retrieve the radius to apply to the filleting of the corners. 
            // 
            acutPrintf("\nElevation for rectangles <%.16q0>: ",
                plineInfo.m_elev);
            if ((stat = acedGetDist(NULL, NULL, &plineInfo.m_elev)) == RTCAN)
                terminated = TRUE;
            plineInfo.m_elevHandSet = (plineInfo.m_elev == 0.0) ? FALSE : TRUE;
            break;
    // Fillet;
        case 2:
            // Retrieve the radius to apply to the filleting of the corners. 
            // If the user has previously used the chamfer, then use the 
            // first disance as the default for the radius.
            //
            acutPrintf("\nFillet radius for rectangles <%.16q0>: ", 
                plineInfo.m_radius == 0.0
                ? plineInfo.m_first : plineInfo.m_radius);
            if ((stat = acedGetDist(NULL, NULL, &plineInfo.m_radius)) == RTCAN)
            {
                terminated = TRUE;
            } else {
                if (stat == RTNONE && plineInfo.m_radius == 0.0)
                    plineInfo.m_radius = plineInfo.m_first;

                plineInfo.m_second = plineInfo.m_first = plineInfo.m_radius;

                // Bulge is tangent of 1/4 of the included angle.
                // We'll assume normal[Z] > 0. & clock wise for now, 
                // hence the '-'.
                plineInfo.m_bulge = -tan(PI / 8.0);
            }
            break;
    // Thickness;
        case 3:
            // Retrieve the thickness to apply to the polyline. 
            // 
            acutPrintf("\nThickness for rectangles <%.16q0>: ",
                plineInfo.m_thick);
            if ((stat = acedGetDist(NULL, NULL, &plineInfo.m_thick)) == RTCAN)
            {
                terminated = TRUE;
            }
            break;
    // Width;
        case 4:
            // Retrieve the width to apply to the polyline. 
            // 
            acutPrintf("\nWidth for rectangles <%.16q0>: ",
                plineInfo.m_width);
            if ((stat = acedGetDist(NULL, NULL, &plineInfo.m_width)) == RTCAN)
            {
                terminated = TRUE;
            }
            break;
    // Just in case;
        default:
              terminated = TRUE;
              break;
        }
    } 

    if (!terminated) {
        if (plineInfo.m_first != 0.0) {
            // If we are treating the corners, then calculate the unit vector
            // of the corners. Note for filleting the angle is 45 degrees. 
            //
            plineInfo.m_chamfDirUnitVec = AcGeVector3d(plineInfo.m_second,
                plineInfo.m_first, plineInfo.m_elev);
            univec(plineInfo.m_chamfDirUnitVec, plineInfo.m_chamfDirUnitVec);
        }
        // Create an AsdkRectangleJig object passing in the CRectInfo sturcture
        // filled during the users input
        //
        AsdkRectangleJig* pJig = new AsdkRectangleJig();

        // Now start up the jig to interactively get the opposite corner.
        //
        pJig->doRectangle();

        // Now delete the jig object since it's no longer needed
        //
        delete pJig;
    }

    // Be nice and reset it now.
    //
    setIntSysVar(/*NOXLATE*/"ORTHOMODE", oldOrthoMode);

    return;
}

//----- Register the Application in the AutoCAD registry (demand loading)

#define APPNAME "Rectang"
#define GROUPNAME "ACAD_RECTANGLE"

void registerForDemandLoading()
{
	// Fill the AppInfo structure with our demand loading details.
	AcadAppInfo appInfo;
	appInfo.setAppName(APPNAME);// AppName
	appInfo.setModuleName(acedGetAppName());// The physical location of the module
	appInfo.setAppDesc("Rectangle");// Description
	appInfo.setLoadReason( // Specify when we want this app to load.
		AcadApp::LoadReasons(
		AcadApp::kOnCommandInvocation |
		AcadApp::kOnLoadRequest));
	
	appInfo.writeToRegistry(false,true);// Write the AppInfo to the registry, don't write to DBX registry section.
	
	appInfo.writeGroupNameToRegistry(GROUPNAME);// Write the group,
	appInfo.writeCommandNameToRegistry("RECTANGLE","RECTANGLE"); // and the commands.
	appInfo.writeCommandNameToRegistry("RECTANG","RECTANG");
}

// ----------------------------------------------------------------------------
// Register the rectangle command.
//
void initApp()
{
    registerForDemandLoading();

    acedRegCmds->addCommand(/*NOXLATE*/"ACAD_RECTANGLE", /*NOXLATE*/"RECTANG", "RECTANG", ACRX_CMD_MODAL, createRect);
    acedRegCmds->addCommand(/*NOXLATE*/"ACAD_RECTANGLE", /*NOXLATE*/"RECTANGLE", "RECTANGLE", ACRX_CMD_MODAL, createRect);
}

// ----------------------------------------------------------------------------
// UnRegister the rectangle command.
//
void unloadApp()
{
    acedRegCmds->removeGroup(/*NOXLATE*/"ACAD_RECTANGLE");
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        acrxRegisterAppMDIAware(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}
