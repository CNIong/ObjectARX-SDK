//
//
// (C) Copyright 2006-2007 by Autodesk, Inc.
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

#pragma once

#include "dbmain.h"

#pragma pack (push, 8)

class AcDbBreakPointRef;

class AcDbBreakData : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbBreakData);

    AcDbBreakData();
    virtual ~AcDbBreakData();
    
    AcDbObjectId dimObjId() const;
    Acad::ErrorStatus setDimObjId(const AcDbObjectId& dimId);

    Acad::ErrorStatus addBreakPointRef(AcDbBreakPointRef* ptRef);
    Acad::ErrorStatus getBreakPointRef(int lineIndex, 
                              AcArray<AcDbBreakPointRef*>& ptRefs) const;
    Acad::ErrorStatus getBreakPointRef(AcArray<AcDbBreakPointRef*>& ptRefs) const;
    Acad::ErrorStatus deleteAllBreakPointRefs();
    Acad::ErrorStatus removeAssociativity(bool force = true);
    Acad::ErrorStatus postToDb(AcDbObjectId& breakObjId);
    Acad::ErrorStatus eraseFromDb(void); 

    //********************************************************************
    // Overridden methods from AcDbObject
    //********************************************************************
    //
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;

    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;

    virtual void  modifiedGraphics(const AcDbEntity* pEnt);

    //********************************************************************
    //  APIs for Internal use only
    //********************************************************************
    //
    Acad::ErrorStatus updateAssociativity(const AcDbObjectIdArray& ids, int cmdType);
};

class AcDbBreakPointRef : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbBreakPointRef);

    enum BreakPointType { 
        kDynamic           = 0,
        kStatic            = 1,
        kStatic2Point      = 2
    };

    AcDbBreakPointRef();
    virtual ~AcDbBreakPointRef();

    AcDbBreakPointRef::BreakPointType pointType() const;
    Acad::ErrorStatus setPointType(AcDbBreakPointRef::BreakPointType newVal);
    Adesk::Int32 lineIndex() const;
    Acad::ErrorStatus setLineIndex(Adesk::Int32 index);
    AcGePoint3d breakPoint() const;
    Acad::ErrorStatus setBreakPoint(const AcGePoint3d& pt);
    AcGePoint3d breakPoint2() const;
    Acad::ErrorStatus setBreakPoint2(const AcGePoint3d& pt);
    Acad::ErrorStatus getBreakPointId(AcDbFullSubentPath& idPath) const;
    Acad::ErrorStatus setBreakPointId(const AcDbFullSubentPath& idPath);
    AcDbEntity *subentPtr() const;
    Acad::ErrorStatus intersectWith(const AcDbEntity* pEnt,
                                    AcGePoint3dArray& points,
                                    AcGePoint3dArray& textBoxPts);
 
    //********************************************************************
    // Overridden methods from AcDbObject
    //********************************************************************
    //
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;

    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;
};

//************************************************************************
//  Global API functions 
//************************************************************************
//
Acad::ErrorStatus acdbGetBreakSubentIndex(AcDbEntity* pEnt,
                                     const AcGePoint3d& pickPt, 
                                     const AcGeVector3d& viewDir, 
                                     int& subentIndex,
                                     AcGePoint3d& ptOnEnt,
                                     const AcGeTol& tol = AcGeContext::gTol);

#pragma pack (pop)

