//#ifndef ARX_DBMATCH_H
//#define ARX_DBMATCH_H
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
// dbInterferencePE.H
//
// DESCRIPTION: AcDbInterferencePE Protocol extension abstract base class
//
#include "acdb.h"
#include "dbmain.h"

#pragma once
#pragma pack (push, 8)

//
//  AcDbInterferencePE Protocol extension abstract base class. 
//
class AcDbInterferencePE : public AcRxObject
{
public:
    enum Flags {
        kDefault     = 0x00,
    };

    ACRX_DECLARE_MEMBERS(AcDbInterferencePE);

    // Contract:
    // Implementer is expected to create new AcDbEntity instance(s), based 
    // on interference between the two provided entities, and append the
    // new ents to the provided array. The caller will either post the new 
    // ents to the db or delete them. 
    //  If the implementer does not know how to generate interference
    // between the provided entities, they should return "eNotApplicable" 
    // or "eNotImplementedYet".
    // If the provided objects do not intersect, return "eNoIntersections".
    virtual Acad::ErrorStatus 
        createInterferenceObjects(  AcArray<AcDbEntity*>& interferenceObjects,
                                    AcDbEntity* pEnt1, 
                                    AcDbEntity* pEnt2,
                                    unsigned int flags ) const = 0;
};

#pragma pack (pop)

//#endif

