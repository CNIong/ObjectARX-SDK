#ifndef AD_DBPL_H
#define AD_DBPL_H 1
//
// (C) Copyright 1996-2009 by Autodesk, Inc.
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
// DESCRIPTION:  Lightweight polyline API header file.
//

#include "dbmain.h"
#include "dbcurve.h"

#include "gelnsg2d.h"
#include "gelnsg3d.h"
#include "gearc2d.h"
#include "gearc3d.h"
#include "gept2dar.h"
#include "dbboiler.h"

#pragma pack(push, 8)

class AcDb2dPolyline;

class AcDbPolyline : public AcDbCurve
{

public:
                      AcDbPolyline();
                      AcDbPolyline(unsigned int num_verts);
    virtual          ~AcDbPolyline();


    ACDB_DECLARE_MEMBERS(AcDbPolyline);


    //**********************************************************************
    // AcDbPolyline methods.
    //**********************************************************************

    Acad::ErrorStatus convertFrom(AcDbEntity*& pPline, 
                                  Adesk::Boolean transferId = Adesk::kTrue);
    Acad::ErrorStatus convertTo(AcDb2dPolyline*&  pPline,
                                Adesk::Boolean transferId = Adesk::kTrue) const;

    Acad::ErrorStatus getPointAt(unsigned int, AcGePoint3d& pt) const;

    enum SegType {
        kLine,
        kArc,
        kCoincident,
        kPoint,
        kEmpty
    };

    SegType           segType           (unsigned int index) const;

    Acad::ErrorStatus getLineSegAt      (unsigned int index,
                                         AcGeLineSeg2d& ln) const;
    Acad::ErrorStatus getLineSegAt      (unsigned int index,
                                         AcGeLineSeg3d& ln) const;
    Acad::ErrorStatus getArcSegAt       (unsigned int index,
                                         AcGeCircArc2d& arc) const;
    Acad::ErrorStatus getArcSegAt       (unsigned int index,
                                         AcGeCircArc3d& arc) const;
    virtual Adesk::Boolean onSegAt      (unsigned int index, const AcGePoint2d& pt2d,
                                         double& param) const;

    //**********************************************************************
    // AcDbPolyline methods.
    //**********************************************************************
   
    void              setClosed       (Adesk::Boolean);
    void              setPlinegen     (Adesk::Boolean);
    void              setElevation    (double);
    Acad::ErrorStatus setThickness    (double);
    Acad::ErrorStatus setConstantWidth(double);
    Acad::ErrorStatus setNormal       (const AcGeVector3d&);

    Adesk::Boolean    isOnlyLines     ()                        const;
    Adesk::Boolean    hasPlinegen     ()                        const;
    double            elevation       ()                        const;
    double            thickness       ()                        const;
    Acad::ErrorStatus getConstantWidth(double&)                 const;
    AcGeVector3d      normal          ()                        const;

    Acad::ErrorStatus addVertexAt     (unsigned int index,
                                       const AcGePoint2d& pt,
                                       double bulge = 0.,
                                       double startWidth = -1.,
                                       double endWidth = -1.,
                                       Adesk::Int32 vertexIdentifier = 0);

    Acad::ErrorStatus removeVertexAt  (unsigned int index);

    unsigned int      numVerts        ()                        const;

    Acad::ErrorStatus getPointAt        (unsigned int index,
                                       AcGePoint2d& pt)         const;
    Acad::ErrorStatus getBulgeAt      (unsigned int index,
                                       double&      bulge)      const;
    Acad::ErrorStatus getVertexIdentifierAt(unsigned int index,
                                            Adesk::Int32& vertexIdentifier) const;
    Acad::ErrorStatus getWidthsAt     (unsigned int index,
                                       double&      startWidth,
                                       double&      endWidth)   const;

    Acad::ErrorStatus setPointAt      (unsigned int index,
                                       const AcGePoint2d& pt);
    Acad::ErrorStatus setBulgeAt      (unsigned int index,
                                       double       bulge);
    Acad::ErrorStatus setVertexIdentifierAt(unsigned int index,
                                       Adesk::Int32 suggestedValue);
    Acad::ErrorStatus setWidthsAt     (unsigned int index,
                                       double       startWidth,
                                       double       endWidth);

    Acad::ErrorStatus minimizeMemory  ();
    Acad::ErrorStatus maximizeMemory  ();

    void              reset           (Adesk::Boolean reuse,
                                       unsigned int numVerts);


    Adesk::Boolean     hasBulges       ()        const;
    Adesk::Boolean     hasVertexIdentifiers()    const;
    Adesk::Boolean     hasWidth        ()        const;

    //**********************************************************************
    // AcDbCurve methods.
    //**********************************************************************

    DBCURVE_METHODS

    //*************************************************************************
    // Overridden methods from AcDEntity
    //*************************************************************************


    virtual void              getEcs(AcGeMatrix3d& retVal) const;

    virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* filer,
                                               AcRxClass*    classobj);

    //*************************************************************************
    // Overridden methods from AcDbObject
    //*************************************************************************

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

    virtual void              saveAs(AcGiWorldDraw* mode,
                                     AcDb::SaveType st);


protected:

    //*************************************************************************
    // Overridden methods from AcDEntity
    //*************************************************************************

    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};


inline Adesk::Boolean AcDbPolyline::isPlanar() const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDbPolyline::getStartParam(double& startParam) const
{
    startParam = 0.;
    return Acad::eOk;
}

inline Acad::ErrorStatus AcDbPolyline::getSpline(AcDbSpline*& spline) const
{
    return Acad::eNotApplicable;
}

#pragma pack(pop)

#endif /*AD_DBPL_H*/
