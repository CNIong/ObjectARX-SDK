//
//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// dbDynamicUCSPE.H
//
// DESCRIPTION: AcDbDynamicUCSPE Protocol extension abstract base class
//
#include "acdb.h"
#include "dbmain.h"

#pragma once
#pragma pack (push, 8)

//
//  AcDbDynamicUCSPE Protocol extension abstract base class. 
//
class AcDbDynamicUCSPE	: public AcRxObject
{
public:
    enum Flags {
        kDefault     = 0x00,
    };

	ACRX_DECLARE_MEMBERS(AcDbDynamicUCSPE);

    // Contract:
    // The implementer is expected to populate the result array 
    // with one or more AcGePlane objects and return Acad::eOk if successful.
    // Populate distToEdge with the distance from the point to the edge of the subent.  
    // This value is used when the subent is not to be highlighted unless the
    // distance is >= the current aperture value.  If the implementer doesn't
    // care about aperture tolerance, return this as a negative value and it
    // will be duly ignored.
    //
    // Expected failure codes are Acad::eNotImplementedYet or Acad::eNotApplicable.
    // Return Acad::eWrongObjectType if the object under the cursor is unsupported.
    // Return Acad::eWrongSubentityType if the subent under the cursor is unsupported.
    //
    virtual Acad::ErrorStatus 
        getCandidatePlanes(AcArray<AcGePlane>& results,
                            double &distToEdge,
                            double &objWidth,
                            double &objHeight,
                            AcDbEntity* pEnt,
                            const AcDbSubentId& subentId,
                            const AcGePlane& viewplane,
                            AcDbDynamicUCSPE::Flags flags = kDefault //reserved
                            ) const = 0;
};

#pragma pack (pop)


