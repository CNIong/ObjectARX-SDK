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
// DBMATCH.H
//
// DESCRIPTION: AcDbMatchProperties Protocol extension abstract base class
//
// NOTE:
// Default implementation to be attached to AcDbEntity as a catch-all. This
// guarantees that this protocol extension will be found  for any entity so
// the search up the AcRxClass tree will not fail and abort AutoCAD.  
//

#ifndef ARX_DBMATCH_H
#define ARX_DBMATCH_H

#include "acdb.h"
#include "dbmain.h"

#pragma pack (push, 8)

class AcDbMatchProperties	: public AcRxObject
//
//  AcDbMatchProperties Protocol extension abstract base class. 
//
{
public:
    enum Flags {
        kColorFlag     = 0x1,
        kLayerFlag     = 0x2,
        kLtypeFlag     = 0x4,
        kThicknessFlag = 0x8,
        kLtscaleFlag   = 0x10,
        kTextFlag      = 0x20,
        kDimensionFlag = 0x40,
        kHatchFlag     = 0x80,
        kLweightFlag   = 0x100,
        kPlotstylenameFlag = 0x200,
        kPolylineFlag  = 0x400,
        kViewportFlag  = 0x800,
        kTableFlag     = 0x1000,
        kMaterialFlag  = 0x2000,
        kShadowDisplayFlag    = 0x4000,
        kMultileaderFlag      = 0x8000,
        kTransparencyFlag     = 0x10000,
        kSetAllFlagsOn = 0x1FFFF
    };

	ACRX_DECLARE_MEMBERS(AcDbMatchProperties);

	virtual void copyProperties(AcDbEntity* pSrcEntity, AcDbEntity* pTrgEntity,
								unsigned int flag) const  = 0;
};

#pragma pack (pop)

#endif

