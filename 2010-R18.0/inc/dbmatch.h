#ifndef ARX_DBMATCH_H
#define ARX_DBMATCH_H
//
// (C) Copyright 1993-2007 by Autodesk, Inc.
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
// DBMATCH.H
//
// DESCRIPTION: AcDbMatchProperties Protocol extension abstract base class
//
// NOTE:
// Default implementation to be attached to AcDbEntity as a catch-all. This
// guarantees that this protocol extension will be found  for any entity so
// the search up the AcRxClass tree will not fail and abort AutoCAD.  
//
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
        kSetAllFlagsOn = 0xFFFF
    };

	ACRX_DECLARE_MEMBERS(AcDbMatchProperties);

	virtual void copyProperties(AcDbEntity* pSrcEntity, AcDbEntity* pTrgEntity,
								unsigned int flag) const  = 0;
};

#pragma pack (pop)

#endif

