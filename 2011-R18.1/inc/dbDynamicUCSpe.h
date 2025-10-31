//
// (C) Copyright 1993-2006 by Autodesk, Inc.
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


