// (C) Copyright 2002-2007 by Autodesk, Inc. 
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
//----- AsdkSliderCrank.h : Declaration of the AsdkSliderCrank
//-----------------------------------------------------------------------------
#pragma once

#ifdef SLIDERCRANKDB_MODULE
#define DLLIMPEXP __declspec(dllexport)
#else
//----- Note: we don't use __declspec(dllimport) here, because of the
//----- "local vtable" problem with msvc. If you use __declspec(dllimport),
//----- then, when a client dll does a new on the class, the object's
//----- vtable pointer points to a vtable allocated in that client
//----- dll. If the client dll then passes the object to another dll,
//----- and the client dll is then unloaded, the vtable becomes invalid
//----- and any virtual calls on the object will access invalid memory.
//-----
//----- By not using __declspec(dllimport), we guarantee that the
//----- vtable is allocated in the server dll during the ctor and the
//----- client dll does not overwrite the vtable pointer after calling
//----- the ctor. And, since we expect the server dll to remain in
//----- memory indefinitely, there is no problem with vtables unexpectedly
//----- going away.
#define DLLIMPEXP
#endif

//-----------------------------------------------------------------------------
#include "dbmain.h"

//Markers
#define CRANK 1
#define LINK 2
#define PINS 3
#define PISTON 4

//For individual grips
#define IN_CRANK_CENTER 0
#define IN_CRANK_RADIUS 1
#define IN_LINK_START 2
#define IN_LINK_END 3
#define IN_PISTON_CENTER 4

//For standard grips
#define ST_CRANK_CENTER 0
#define ST_CRANK_RADIUS 1
#define ST_LINK_START 2
#define ST_LINK_END 3
#define ST_PISTON_CENTER 4

//-----------------------------------------------------------------------------
class DLLIMPEXP AsdkSliderCrank : public AcDbEntity {
public:
    ACRX_DECLARE_MEMBERS(AsdkSliderCrank) ;

    //-define member variables
private:
    double m_crankRadius;
    double m_connectingLinkLength;
    double m_pistonSize;
    double m_pistonSkirtLength;
    double m_crankPinAngle;	
    AcGePoint3d m_location;
    AcGeVector3d m_sliderDirection;
    AcCmEntityColor m_connectingLinkColor;
    AcCmEntityColor m_pistonColor;
    AcCmEntityColor m_crankColor;

    static int m_stAppData[7];
protected:
    static Adesk::UInt32 kCurrentVersionNumber ;

    //declare member functions
private:
    void drawSliderCrank(AcGiWorldDraw *mode) const;
    void calculateLink(AcGePoint3d *pts) const;
    void calculatePiston(AcGePoint3d *pts) const;
    void checkLinkLength();

    void moveCrankQuadPt(AcGeVector3d offset);
    void moveLinkStartPt(AcGeVector3d offset);
    void xformLinkStartPt(AcGeMatrix3d mat);

    void moveLocationPt(AcGeMatrix3d mat);
    void moveLinkEndPt(AcGeVector3d offset);
    void movePistonCenterPt(AcGeVector3d offset);
    void xformPistonCenterPt(AcGeMatrix3d mat);

    //Set/Get functions
public:
    void setConnectingLinkLength(double connectingLinkLength);
    double connectingLinkLength();

    void setConnectingLinkColor(AcCmEntityColor col);
    AcCmEntityColor connectingLinkColor();

    void setPistonSize(double pistonSize);
    double pistonSize();

    void setPistonSkirtLength(double pistonSkirtLength);
    double pistonSkirtLength();

    void setPistonColor(AcCmEntityColor col);
    AcCmEntityColor pistonColor();

    void setCrankRadius(double crankRadius);
    double crankRadius();

    void setCrankPinAngle(double crankPinAngle);
    double crankPinAngle();

    void setCrankColor(AcCmEntityColor col);
    AcCmEntityColor crankColor();

    void setLocation(AcGePoint3d location);
    AcGePoint3d location();

    void setSliderDirection(AcGeVector3d sliderDirection);
    AcGeVector3d sliderDirection();

public:
    AsdkSliderCrank () ;
    virtual ~AsdkSliderCrank () ;

    //----- AcDbObject protocols
    //- Dwg Filing protocol
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

    //- Automation support
    virtual Acad::ErrorStatus getClassID (CLSID *pClsid) const ;
    virtual Acad::ErrorStatus getSubentClassId(const AcDbFullSubentPath& path,
        CLSID* pClsId) const;

    //----- AcDbEntity protocols
    //- Graphics protocol
    virtual Adesk::Boolean worldDraw (AcGiWorldDraw *mode) ;

    // -----------------------------------------------------------------------------
    virtual Acad::ErrorStatus getSubentPathsAtGsMarker(AcDb::SubentType  type, Adesk::GsMarker gsMark, const AcGePoint3d & pickPoint, const AcGeMatrix3d & viewXform, int & numPaths, AcDbFullSubentPath *& subentPaths, int  numInserts, AcDbObjectId * entAndInsertStack) const;	
    // -----------------------------------------------------------------------------
    virtual Acad::ErrorStatus getGsMarkersAtSubentPath(const AcDbFullSubentPath & subPath, AcArray<Adesk::GsMarker>& gsMarkers) const;
    // -----------------------------------------------------------------------------
    virtual AcDbEntity * subentPtr(const AcDbFullSubentPath & id) const;
    // -----------------------------------------------------------------------------
    virtual Acad::ErrorStatus transformSubentPathsBy(const AcDbFullSubentPathArray & paths, const AcGeMatrix3d & xform);
    // -----------------------------------------------------------------------------
    virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d & xform);
    // -----------------------------------------------------------------------------
    virtual Acad::ErrorStatus getGripPointsAtSubentPath(const AcDbFullSubentPath & path, AcDbGripDataPtrArray & grips, const double  curViewUnitSize, const int  gripSize, const AcGeVector3d & curViewDir, const int  bitflags) const;
    // -----------------------------------------------------------------------------
    virtual Acad::ErrorStatus moveGripPointsAtSubentPaths(const AcDbFullSubentPathArray & paths, const AcDbVoidPtrArray & gripAppData, const AcGeVector3d & offset, const int  bitflags);
    // -----------------------------------------------------------------------------
    virtual Acad::ErrorStatus getGripPoints(AcDbGripDataPtrArray & grips, const double  curViewUnitSize, const int  gripSize, const AcGeVector3d & curViewDir, const int  bitflags) const;
    // -----------------------------------------------------------------------------
    virtual Acad::ErrorStatus moveGripPointsAt(const AcDbVoidPtrArray & gripAppData, const AcGeVector3d & offset, const int  bitflags);
} ;

#ifdef SLIDERCRANKDB_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(AsdkSliderCrank)
#endif
