// (C) Copyright 2002-2005 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
//----- AsdkSliderCrank.cpp : Implementation of AsdkSliderCrank
//-----------------------------------------------------------------------------
#include "StdAfx.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 AsdkSliderCrank::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
                         AsdkSliderCrank, AcDbEntity,
                         AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
                         AcDbProxyEntity::kNoOperation, ASDKSLIDERCRANK,
                         "ASDKSLIDERCRANKAPP"
                         "|Product Desc:     Slider Crank Mechanism"
                         "|Company:          Autodesk"
                         "|WEB Address:      www.autodesk.com"
                         )

//-----------------------------------------------------------------------------
int AsdkSliderCrank::m_stAppData[7] = {0,1,2,3,4,5,6};


AsdkSliderCrank::AsdkSliderCrank () : AcDbEntity () 
{	
    m_connectingLinkColor.setColorIndex(1);
    m_pistonColor.setColorIndex(2);
    m_crankColor.setColorIndex(3);
}

AsdkSliderCrank::~AsdkSliderCrank () 
{
}

void AsdkSliderCrank::checkLinkLength()
{
    if (m_connectingLinkLength < m_crankRadius)
        m_connectingLinkLength = m_crankRadius;
}

//Set/Get methods
void AsdkSliderCrank::setCrankRadius(double crankRadius)
{
    assertWriteEnabled();
    m_crankRadius = crankRadius;
    checkLinkLength();
}

double AsdkSliderCrank::crankRadius()
{
    assertReadEnabled();
    return m_crankRadius;
}

void AsdkSliderCrank::setConnectingLinkLength(double connectingLinkLength)
{
    assertWriteEnabled();
    m_connectingLinkLength = connectingLinkLength;
    checkLinkLength();
}
double AsdkSliderCrank::connectingLinkLength()
{
    assertReadEnabled();
    return m_connectingLinkLength;
}

void AsdkSliderCrank::setPistonSize(double pistonSize)
{
    assertWriteEnabled();
    m_pistonSize = pistonSize;
}

double AsdkSliderCrank::pistonSize()
{
    assertReadEnabled();
    return m_pistonSize;
}

void AsdkSliderCrank::setPistonSkirtLength(double pistonSkirtLength)
{
    assertWriteEnabled();
    m_pistonSkirtLength = pistonSkirtLength;
}

double AsdkSliderCrank::pistonSkirtLength()
{
    assertReadEnabled();
    return m_pistonSkirtLength;
}

void AsdkSliderCrank::setCrankPinAngle(double crankPinAngle)
{
    assertWriteEnabled();
    m_crankPinAngle = crankPinAngle;
}

double AsdkSliderCrank::crankPinAngle()
{
    assertReadEnabled();
    return m_crankPinAngle;
}

void AsdkSliderCrank::setLocation(AcGePoint3d location)
{
    assertWriteEnabled();
    m_location = location;
}
AcGePoint3d AsdkSliderCrank::location()
{
    assertReadEnabled();
    return m_location;
}

void AsdkSliderCrank::setSliderDirection(AcGeVector3d sliderDirection)
{
    assertWriteEnabled();
    m_sliderDirection = sliderDirection;
}

AcGeVector3d AsdkSliderCrank::sliderDirection()
{
    assertReadEnabled();
    return m_sliderDirection;
}

void AsdkSliderCrank::setPistonColor(AcCmEntityColor col)
{
    assertWriteEnabled();
    m_pistonColor = col;
}

AcCmEntityColor AsdkSliderCrank::pistonColor()
{
    assertReadEnabled();
    return m_pistonColor;
}

void AsdkSliderCrank::setCrankColor(AcCmEntityColor col)
{
    assertWriteEnabled();
    m_crankColor = col;
}

AcCmEntityColor AsdkSliderCrank::crankColor()
{
    assertReadEnabled();
    return m_crankColor;
}

void AsdkSliderCrank::setConnectingLinkColor(AcCmEntityColor col)
{
    assertWriteEnabled();
    m_connectingLinkColor = col;
}

AcCmEntityColor AsdkSliderCrank::connectingLinkColor()
{
    assertReadEnabled();
    return m_connectingLinkColor;
}

//Draw the custom object
void AsdkSliderCrank::drawSliderCrank(AcGiWorldDraw *mode) const
{
    //Draw the flywheel, using the crank radius
    mode->subEntityTraits().setSelectionMarker(CRANK);
    mode->subEntityTraits().setTrueColor(m_crankColor);
    mode->geometry().circle(m_location, m_crankRadius, AcGeVector3d::kZAxis);

    //Draw the cross hair
    AcGePoint3d pts[2];
    pts[0]= m_location + (m_sliderDirection * (m_crankRadius / 4));
    pts[1]= m_location - (m_sliderDirection * (m_crankRadius / 4));
    mode->geometry().worldLine(pts);

    AcGeVector3d vec = m_sliderDirection.perpVector();
    pts[0]= m_location + (vec * (m_crankRadius / 4));
    pts[1]= m_location - (vec * (m_crankRadius / 4));
    mode->geometry().worldLine(pts);

    //Draw the connecting rod
    mode->subEntityTraits().setSelectionMarker(LINK);
    mode->subEntityTraits().setTrueColor(m_connectingLinkColor);
    AcGePoint3d linkpts[2];
    calculateLink(linkpts);
    mode->geometry().worldLine(linkpts);	

    //Draw the pin at both ends
    mode->subEntityTraits().setSelectionMarker(PINS);	
    mode->geometry().circle(linkpts[0], (m_crankRadius/25.0), AcGeVector3d::kZAxis);
    mode->geometry().circle(linkpts[1], (m_crankRadius/25.0), AcGeVector3d::kZAxis);

    //Draw the piston
    AcGePoint3d pistonpts[5];
    calculatePiston(pistonpts);
    mode->subEntityTraits().setSelectionMarker(PISTON);
    mode->subEntityTraits().setTrueColor(m_pistonColor);
    mode->geometry().polyline(4,pistonpts);
}

//Calculate the connecting link points
void AsdkSliderCrank::calculateLink(AcGePoint3d *pts) const
{
    AcGeVector3d vec = m_sliderDirection;
    vec = vec.normalize();
    vec = vec*m_crankRadius;
    vec = vec.rotateBy(m_crankPinAngle,AcGeVector3d::kZAxis);

    pts[0] = m_location+vec;	
    AcGeCircArc3d circ(pts[0],AcGeVector3d::kZAxis,m_connectingLinkLength);
    AcGeLine3d sliderPath(m_location,m_sliderDirection);

    AcGePoint3d pt1, pt2;
    int num;
    circ.intersectWith(sliderPath,num,pt1,pt2);

    AcGeVector3d vec1 = pt1 - m_location;
    if (m_sliderDirection.isCodirectionalTo(vec1))
        pts[1] = pt1;
    else
        pts[1] = pt2;
}

//Calculate the piston
void AsdkSliderCrank::calculatePiston(AcGePoint3d *pts) const
{
    AcGePoint3d sliderpts[2];
    calculateLink(sliderpts);

    AcGeVector3d slidervec = m_sliderDirection;
    AcGeVector3d perpvec = m_sliderDirection.perpVector();
    perpvec.normalize();

    double halfsize = m_pistonSize/2.0;

    AcGePoint3d piston = sliderpts[1] + (slidervec.normalize() * halfsize);
    pts[1] = piston + (perpvec * halfsize); //piston face
    pts[2] = piston - (perpvec * halfsize);
    pts[0] = pts[1] - (slidervec * m_pistonSkirtLength); //piston skirt
    pts[3] = pts[2] - (slidervec * m_pistonSkirtLength);	
    pts[4] = piston; //piston center
}

void AsdkSliderCrank::moveCrankQuadPt(AcGeVector3d offset)
{
    if (offset.length() < AcGeContext::gTol.equalPoint()) return;	
    setCrankRadius(m_crankRadius + offset.length() * (offset.x/fabs(offset.x)));
}

void AsdkSliderCrank::moveLocationPt(AcGeMatrix3d mat)
{
    m_location.transformBy(mat);
}

void AsdkSliderCrank::moveLinkEndPt(AcGeVector3d offset)
{
    if (offset.length() < AcGeContext::gTol.equalPoint()) return;	
    setConnectingLinkLength(m_connectingLinkLength + offset.length() * (offset.x/fabs(offset.x)));
}

//Calculate the Link start point given the new end point of the link
//Used to move the piston using grips
void AsdkSliderCrank::movePistonCenterPt(AcGeVector3d offset)
{
    if (offset.length() < AcGeContext::gTol.equalPoint()) return;	

    AcGePoint3d sliderPts[2];
    calculateLink(sliderPts);
    AcGePoint3d endPt =  sliderPts[1];

    offset.rotateBy(m_sliderDirection.angleTo(AcGeVector3d::kXAxis,AcGeVector3d::kZAxis),AcGeVector3d::kZAxis);
    double len = offset.x;

    endPt = endPt + (m_sliderDirection * len);

    AcGeCircArc3d circ(endPt,AcGeVector3d::kZAxis,m_connectingLinkLength);
    AcGeCircArc3d circ1(m_location,AcGeVector3d::kZAxis,m_crankRadius);

    AcGePoint3d pt1, pt2;
    int num;
    circ.intersectWith(circ1,num,pt1,pt2);

    AcGePoint3d newPt;
    if (0 == num) 
    {
        if(m_location.distanceTo(endPt) < m_location.distanceTo(sliderPts[1]))
            newPt = m_location - (m_sliderDirection * m_crankRadius);
        else
            newPt = m_location + (m_sliderDirection * m_crankRadius);;
    }
    else
    {
        //Check the distance
        if(sliderPts[0].distanceTo(pt1) < sliderPts[0].distanceTo(pt2))
            newPt = pt1;
        else
            newPt = pt2;
    }

    AcGeVector3d vec = newPt - m_location;
    setCrankPinAngle(m_sliderDirection.angleTo(vec,AcGeVector3d::kZAxis));	
}

void AsdkSliderCrank::xformPistonCenterPt(AcGeMatrix3d mat)
{
    //Get the rotation component only
    //This is used to rotate the crank when it is subselected and rotate is used	
    movePistonCenterPt(mat.translation());
}

//Calculate the end point of the link given the new start point of the link on the crank
void AsdkSliderCrank::moveLinkStartPt(AcGeVector3d offset)
{
    AcGePoint3d pts[2];
    calculateLink(pts);
    AcGePoint3d newPt = pts[0] + offset;
    AcGeVector3d vec = newPt - m_location;
    setCrankPinAngle(m_sliderDirection.angleTo(vec,AcGeVector3d::kZAxis));	
}

void AsdkSliderCrank::xformLinkStartPt(AcGeMatrix3d mat)
{
    //Get the rotation component only
    //This is used to rotate the crank when it is subselected and rotate is used
    AcGeVector3d vec = AcGeVector3d::kXAxis;
    vec.transformBy(mat);	

    double ang = AcGeVector3d::kXAxis.angleTo(vec,AcGeVector3d::kZAxis);
    if (ang > AcGeContext::gTol.equalPoint()) //change only angle is not zero
        setCrankPinAngle(m_sliderDirection.angleTo(vec,AcGeVector3d::kZAxis));		
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus AsdkSliderCrank::dwgOutFields (AcDbDwgFiler *pFiler) const {
    assertReadEnabled () ;
    //----- Save parent class information first.
    Acad::ErrorStatus es =AcDbEntity::dwgOutFields (pFiler) ;
    if ( es != Acad::eOk )
        return (es) ;
    //----- Object version number needs to be saved first
    if ( (es =pFiler->writeUInt32 (AsdkSliderCrank::kCurrentVersionNumber)) != Acad::eOk )
        return (es) ;
    //----- Output params
    //.....

    pFiler->writeDouble(m_crankRadius);
    pFiler->writeDouble(m_connectingLinkLength);
    pFiler->writeDouble(m_pistonSize);
    pFiler->writeDouble(m_pistonSkirtLength);
    pFiler->writeDouble(m_crankPinAngle);
    pFiler->writePoint3d(m_location);
    pFiler->writeVector3d(m_sliderDirection);
    pFiler->writeUInt32(m_pistonColor.color());
    pFiler->writeUInt32(m_connectingLinkColor.color());
    pFiler->writeUInt32(m_crankColor.color());

    return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus AsdkSliderCrank::dwgInFields(AcDbDwgFiler *pFiler) 
{
    assertWriteEnabled () ;
    //----- Read parent class information first.
    Acad::ErrorStatus es =AcDbEntity::dwgInFields (pFiler) ;
    if ( es != Acad::eOk )
        return (es) ;
    //----- Object version number needs to be read first
    Adesk::UInt32 version =0 ;
    if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
        return (es) ;
    if ( version > AsdkSliderCrank::kCurrentVersionNumber )
        return (Acad::eMakeMeProxy) ;
    //- Uncomment the 2 following lines if your current object implementation cannot
    //- support previous version of that object.
    //if ( version < AsdkSliderCrank::kCurrentVersionNumber )
    //	return (Acad::eMakeMeProxy) ;
    //----- Read params
    //.....

    pFiler->readDouble(&m_crankRadius);
    pFiler->readDouble(&m_connectingLinkLength);
    pFiler->readDouble(&m_pistonSize);
    pFiler->readDouble(&m_pistonSkirtLength);
    pFiler->readDouble(&m_crankPinAngle);
    pFiler->readPoint3d(&m_location);
    pFiler->readVector3d(&m_sliderDirection);


    Adesk::UInt32 col;
    pFiler->readUInt32(&col);
    m_pistonColor.setColor(col);

    pFiler->readUInt32(&col);
    m_connectingLinkColor.setColor(col);

    pFiler->readUInt32(&col);
    m_crankColor.setColor(col);

    return (pFiler->filerStatus ()) ;
}

//- Automation support
Acad::ErrorStatus AsdkSliderCrank::getClassID (CLSID *pClsid) const {
    assertReadEnabled () ;
    ::CLSIDFromProgID (_T("SliderCrankDb.SliderCrank"), pClsid) ;

    return (Acad::eOk) ;
}

Acad::ErrorStatus AsdkSliderCrank::getSubentClassId(const AcDbFullSubentPath& path,
                                                    CLSID* pClsId) const
{
    assertReadEnabled () ;

    if(CRANK == path.subentId().index())
    {
        ::CLSIDFromProgID (_T("SliderCrankDb.Crank"), pClsId) ;
    }
    else if(LINK == path.subentId().index())
    {
        ::CLSIDFromProgID (_T("SliderCrankDb.ConnectingLink"), pClsId) ;
    }else if(PISTON == path.subentId().index())
    {
        ::CLSIDFromProgID (_T("SliderCrankDb.Piston"), pClsId) ;
    }

    return (Acad::eOk) ;
}

//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean AsdkSliderCrank::worldDraw (AcGiWorldDraw *mode) {
    assertReadEnabled () ;

    //Draw slider and crank
    drawSliderCrank(mode);
    return Adesk::kTrue; //No viewport specific graphics
}

// -----------------------------------------------------------------------------
Acad::ErrorStatus AsdkSliderCrank::getSubentPathsAtGsMarker(AcDb::SubentType  type, int  gsMark, const AcGePoint3d & pickPoint, const AcGeMatrix3d & viewXform, int & numPaths, AcDbFullSubentPath *& subentPaths, int  numInserts, AcDbObjectId * entAndInsertStack) const
{
    assertReadEnabled();

    AcDbFullSubentPath *pPaths = new AcDbFullSubentPath[1];	
    pPaths->subentId().setIndex(gsMark);
    pPaths->subentId().setType(AcDb::kClassSubentType);
    pPaths->subentId().setTypeClass(AsdkSliderCrank::desc());

    pPaths->objectIds().append(this->objectId());

    subentPaths = pPaths;
    numPaths = 1;

    return (Acad::eOk);
}

// -----------------------------------------------------------------------------
Acad::ErrorStatus AsdkSliderCrank::getGsMarkersAtSubentPath(const AcDbFullSubentPath & subPath, AcDbIntArray & gsMarkers) const
{
    assertReadEnabled () ;
    gsMarkers.append(subPath.subentId().index());
    return (Acad::eOk);	
}

// -----------------------------------------------------------------------------
AcDbEntity * AsdkSliderCrank::subentPtr(const AcDbFullSubentPath & id) const
{
    assertReadEnabled () ;

    if(CRANK == id.subentId().index())
    {
        return new AcDbCircle(m_location,AcGeVector3d::kZAxis, m_crankRadius);			
    }
    else if(LINK == id.subentId().index())
    {
        AcGePoint3d sliderpts[2];
        calculateLink(sliderpts);
        return new AcDbLine(sliderpts[0], sliderpts[1]);
    }else if(PISTON == id.subentId().index())
    {
        AcGePoint3d pistonpts[5];
        calculatePiston(pistonpts);

        AcDbPolyline *pPLine = new AcDbPolyline();
        pPLine->setNormal(AcGeVector3d::kZAxis);

        for (int i = 0; i < 5; i++) 
        {
            pPLine->addVertexAt(i, AcGePoint2d(pistonpts[i].x,pistonpts[i].y));
        }		
        return pPLine;
    }

    return (NULL) ;
}

// -----------------------------------------------------------------------------
Acad::ErrorStatus AsdkSliderCrank::transformSubentPathsBy(const AcDbFullSubentPathArray & paths, const AcGeMatrix3d & xform)
{
    assertWriteEnabled();

    //Find out how many subents were selected
    //If more than one, then apply transformby to the entity itself

    if (1 < paths.length())
    {
        transformBy(xform);
        return (Acad::eOk);	
    }

    //Else apply transformation to individual subents
    switch(paths.at(0).subentId().index()) 
    {
    case CRANK:
        {			
            moveLocationPt(xform);
        }
        break;
    case LINK:
        {
            //Do nothing
        }
        break;
    case PISTON:
        {
            xformPistonCenterPt(xform);
        }
        break;
    default:
        break;
    }
    return (Acad::eOk);	
}

// -----------------------------------------------------------------------------
Acad::ErrorStatus AsdkSliderCrank::transformBy(const AcGeMatrix3d & xform)
{
    assertWriteEnabled();

    m_location.transformBy(xform);
    m_sliderDirection.transformBy(xform);

    return (Acad::eOk);	
}

// -----------------------------------------------------------------------------
Acad::ErrorStatus AsdkSliderCrank::getGripPointsAtSubentPath(const AcDbFullSubentPath & path, AcDbGripDataPtrArray & grips, const double  curViewUnitSize, const int  gripSize, const AcGeVector3d & curViewDir, const int  bitflags) const
{
    assertReadEnabled();

    switch(path.subentId().index()) 
    {
    case CRANK:
        {		
            //IN_CRANK_CENTER
            AcDbGripData *pGrip1 = new AcDbGripData();
            pGrip1->setAppData((void *)(&m_stAppData[IN_CRANK_CENTER]));
            pGrip1->setGripPoint(m_location);
            grips.append(pGrip1);

            //IN_CRANK_RADIUS
            AcDbGripData *pGrip2 = new AcDbGripData();
            pGrip2->setAppData((void *)(&m_stAppData[IN_CRANK_RADIUS]));
            AcGeVector3d vec = AcGeVector3d::kXAxis * m_crankRadius;
            pGrip2->setGripPoint(m_location + vec);
            grips.append(pGrip2);
        }
        break;
    case LINK:
        {
            AcGePoint3d linkpts[2];
            calculateLink(linkpts);

            //IN_LINK_START
            AcDbGripData *pGrip1 = new AcDbGripData();
            pGrip1->setAppData((void *)(&m_stAppData[IN_LINK_START]));
            pGrip1->setGripPoint(linkpts[0]);
            grips.append(pGrip1);

            //IN_LINK_END
            AcDbGripData *pGrip2 = new AcDbGripData();
            pGrip2->setAppData((void *)(&m_stAppData[IN_LINK_END]));			
            pGrip2->setGripPoint(linkpts[1]);
            grips.append(pGrip2);
        }
        break;
    case PISTON:
        {
            AcGePoint3d pistonpts[5];
            calculatePiston(pistonpts);

            AcDbGripData *pGrip1 = new AcDbGripData();
            pGrip1->setAppData((void *)(&m_stAppData[IN_PISTON_CENTER]));
            pGrip1->setGripPoint(pistonpts[4]);
            grips.append(pGrip1);
        }
        break;
    default:
        break;
    }
    return (Acad::eOk) ;
}

// -----------------------------------------------------------------------------
Acad::ErrorStatus AsdkSliderCrank::moveGripPointsAtSubentPaths(const AcDbFullSubentPathArray & paths, const AcDbVoidPtrArray & gripAppData, const AcGeVector3d & offset, const int  bitflags)
{
    assertWriteEnabled();

    if (1 > paths.length()) return Acad::eOk;

    int *idx = (int*)gripAppData.at(0);	

    switch(paths.at(0).subentId().index()) 
    {
    case CRANK:
        {
            switch(*idx) 
            {
            case IN_CRANK_CENTER: //Move the whole mechanism w.r.t. center of the crank/wheel
                {
                    AcGeMatrix3d mat;
                    mat.setToTranslation(offset);
                    moveLocationPt(mat);		
                }
                break;
            case IN_CRANK_RADIUS: //Modify the radius of the crank/wheel
                {			
                    moveCrankQuadPt(offset);		
                }
                break;
            }
        }
        break;
    case LINK:
        {
            switch(*idx) 
            {
            case IN_LINK_START: //Modify the start point of the link on the crank
                {
                    moveLinkStartPt(offset);
                }
                break;
            case IN_LINK_END:  //Modify the end point of the link on the slide
                {
                    moveLinkEndPt(offset);
                }		
                break;
            }
        }
        break;
    case PISTON:
        {
            movePistonCenterPt(offset);
        }
        break;
    }

    return (Acad::eOk) ;
}

// -----------------------------------------------------------------------------
Acad::ErrorStatus AsdkSliderCrank::getGripPoints(AcDbGripDataPtrArray & grips, const double  curViewUnitSize, const int  gripSize, const AcGeVector3d & curViewDir, const int  bitflags) const
{
    assertReadEnabled();

    for (int i =0; i < 5; i++) 
    {
        AcDbGripData *pGrip = new AcDbGripData();
        pGrip->setAppData((void *)(&m_stAppData[i]));

        switch(i) 
        {
        case ST_CRANK_CENTER:
            {
                pGrip->setGripPoint(m_location);
            }
            break;
        case ST_CRANK_RADIUS: //Second crank radius
            {
                AcGeVector3d vec = AcGeVector3d::kXAxis * m_crankRadius;
                pGrip->setGripPoint(m_location + vec);
            }
            break;
        case ST_LINK_START: //Third slide start point
            {
                AcGePoint3d linkpts[2];
                calculateLink(linkpts);
                pGrip->setGripPoint(linkpts[0]);
            }
            break;
        case ST_LINK_END: //Fourth slide end point
            {
                AcGePoint3d linkpts[2];
                calculateLink(linkpts);
                pGrip->setGripPoint(linkpts[1]);
            }
            break;
        case ST_PISTON_CENTER: //Fifth piston center
            {
                AcGePoint3d pistonpts[5];
                calculatePiston(pistonpts);
                pGrip->setGripPoint(pistonpts[4]);
            }
            break;
        }

        grips.append(pGrip);
    }

    return (Acad::eOk) ;
}

// -----------------------------------------------------------------------------
Acad::ErrorStatus AsdkSliderCrank::moveGripPointsAt(const AcDbVoidPtrArray & gripAppData, const AcGeVector3d & offset, const int  bitflags)
{
    assertWriteEnabled();

    if (1 > gripAppData.length()) return Acad::eOk;

    int *idx = (int*)gripAppData.at(0);	

    switch(*idx) 
    {
    case ST_CRANK_CENTER: //Move the whole mechanism w.r.t. center of the crank/wheel
        {
            AcGeMatrix3d mat;
            mat.setToTranslation(offset);
            moveLocationPt(mat);		
        }
        break;
    case ST_CRANK_RADIUS: //Modify the radius of the crank/wheel
        {			
            moveCrankQuadPt(offset);		
        }
        break;
    case ST_LINK_START: //Modify the start point of the link on the crank
        {
            moveLinkStartPt(offset);
        }
        break;
    case ST_LINK_END:  //Modify the end point of the link on the slide
        {
            moveLinkEndPt(offset);
        }		
        break;
    case ST_PISTON_CENTER:  //Modify the position of the piston
        {
            movePistonCenterPt(offset);
        }		
        break;
    }

    return (Acad::eOk) ;
}
