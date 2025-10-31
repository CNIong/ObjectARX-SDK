//
//
// (C) Copyright 1990-2007 by Autodesk, Inc. 
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
//----- AsdkRings.h : Declaration of the AsdkRings
//-----------------------------------------------------------------------------
#pragma once

#ifdef SELECTIONFILTERDB_MODULE
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
//#include "subselect.h"
//-----------------------------------------------------------------------------
class DLLIMPEXP AsdkRings : public AcDbEntity {

public:
    ACRX_DECLARE_MEMBERS(AsdkRings) ;

protected:
    static Adesk::UInt32 kCurrentVersionNumber ;

public:
    AsdkRings (AcGePoint3d center, double radius); //: AcDbEntity () {}
    AsdkRings ();
    virtual ~AsdkRings () {}

    //----- AcDbObject protocols
    //- Dwg Filing protocol
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

    //- Dxf Filing protocol
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;

    //----- AcDbEntity protocols
    //- Graphics protocol
    virtual Adesk::Boolean worldDraw (AcGiWorldDraw *mode) ;
    virtual Acad::ErrorStatus 
        AsdkRings::getSubentPathsAtGsMarker(AcDb::SubentType     type, 
        Adesk::GsMarker            gsMark,
        const AcGePoint3d&         pickPoint,
        const AcGeMatrix3d&        viewXform,
        int&                       numPaths, 
        AcDbFullSubentPath*&       subentPaths,
        int                        numInserts,
        AcDbObjectId*              entAndInsertStack) const; 

    virtual  Acad::ErrorStatus getGsMarkersAtSubentPath(
        const AcDbFullSubentPath& subPath, 
        AcArray<Adesk::GsMarker>& gsMarkers) const;

    //- Grip points protocol
    virtual Acad::ErrorStatus getGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const ;
    virtual Acad::ErrorStatus moveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) ;


    //Rings custom methods
    void setCenter(const AcGePoint3d cntr);
    void setRadii(const double radius);
    void setColor(const AcCmEntityColor color);
    void setSubSelState(const int subselstate);

    double getRadius() const;

    AcGePoint3d getCenter() const;
private:
    AcGeCircArc3d Circle_1,Circle_2,Circle_3;
    double radius_1, radius_2, radius_3;
    AcGePoint3d m_center;

    int m_subselectstate;  //0=full selection, 1=subselect only circle1, 2=subselect only circle2, 3=subselect only circle3
public:
    //Subselection methods
    bool hitTest(const AcGePoint3d&  wvpt, const AcGeVector3d& wvwdir);
    void AsdkRings::setSubSelection(const AcGePoint3d&  wvpt, const AcGeVector3d& wvwdir, int &marker);
    void clearSubSelection(void);
} ;

#ifdef SELECTIONFILTERDB_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(AsdkRings)
#endif
