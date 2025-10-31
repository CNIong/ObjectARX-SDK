//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#include "dbappgrip.h"

#define DYNBLKSAMP_BLOCKNAME _T("ASDK_CUSTOM_BLOCK")

class AsdkInsertionPoints : public AcDbBlockInsertionPoints
{
public:
	AsdkInsertionPoints(){}
	~AsdkInsertionPoints(){}
    virtual Acad::ErrorStatus getInsertionPoints (
        const AcDbBlockTableRecord* pBlock,
        const AcDbBlockReference*   pBlkRef,
        AcGePoint3dArray& insPts,
		AcGeVector3dArray& alignmentDirections);
};