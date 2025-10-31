//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION: AcDbJoinEntityPE Protocol extension abstract base class
//
#include "acdb.h"
#include "dbmain.h"

#pragma once
#pragma pack (push, 8)

class AcDbJoinEntityPE : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbJoinEntityPE);

    virtual Acad::ErrorStatus 
        joinEntity(AcDbEntity* pPrimaryEntity, 
            AcDbEntity* pSecondaryEntity) const = 0;

    virtual Acad::ErrorStatus 
        joinEntities(AcDbEntity* pPrimaryEntity, 
            const AcArray<AcDbEntity*>& otherEntities,
            AcGeIntArray& joinedEntityIndices) const = 0;
};

#pragma pack (pop)

//#endif

