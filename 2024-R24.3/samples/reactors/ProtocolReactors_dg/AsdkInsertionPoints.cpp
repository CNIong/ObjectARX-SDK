//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "stdafx.h"
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "adscodes.h"
#include "rxdefs.h"
#include "rxregsvc.h"
#include "accmd.h"
#include "acedads.h"
#include "dbmain.h"
#include "dbents.h"
#include "AcString.h"

#include "dbpl.h"
#include "dbapserv.h"
#include "rxprotevnt.h"
#include "dbobjptr.h"

#include "AsdkInsertionPoints.h"



Acad::ErrorStatus AsdkInsertionPoints::getInsertionPoints (
        const AcDbBlockTableRecord* pBlock,
        const AcDbBlockReference*   pBlkRef,
        AcGePoint3dArray& insPts,
		AcGeVector3dArray& alignmentDirections)
{
	AcString sName;
	Acad::ErrorStatus es = pBlock->getName(sName);
	if (_tcsicmp(sName, DYNBLKSAMP_BLOCKNAME) != 0)
		return Acad::eNotApplicable;

	insPts.append(AcGePoint3d(1.0, 0.0, 0.0)); //midpoint of side
	insPts.append(AcGePoint3d(1.0, -1.0, 0.0)); //buffered midpoint
	insPts.append(AcGePoint3d(2.0, 0.0, 0.0));	//endpoint
	insPts.append(AcGePoint3d(2.0, 1.0, 0.0)); //midpoint of side
	insPts.append(AcGePoint3d(3.0, 1.0, 0.0)); //buffered midpoint
	insPts.append(AcGePoint3d(2.0, 2.0, 0.0)); //endpoint
	insPts.append(AcGePoint3d(1.0, 2.0, 0.0)); //midpoint of side
	insPts.append(AcGePoint3d(1.0, 3.0, 0.0)); //buffered midpoint
	insPts.append(AcGePoint3d(0.0, 2.0, 0.0)); //endpoint
	insPts.append(AcGePoint3d(0.0, 1.0, 0.0)); //midpoint of side
	insPts.append(AcGePoint3d(-1.0, 1.0, 0.0)); //buffered midpoint
	
	alignmentDirections.append(AcGeVector3d(0.0, 1.0, 0.0));
	alignmentDirections.append(AcGeVector3d(0.0, 1.0, 0.0));
	alignmentDirections.append(AcGeVector3d(-1.0, 0.0, 0.0));
	alignmentDirections.append(AcGeVector3d(-1.0, 0.0, 0.0));
	alignmentDirections.append(AcGeVector3d(-1.0, 0.0, 0.0));
	alignmentDirections.append(AcGeVector3d(0.0, -1.0, 0.0));
	alignmentDirections.append(AcGeVector3d(0.0, -1.0, 0.0));
	alignmentDirections.append(AcGeVector3d(0.0, -1.0, 0.0));
	alignmentDirections.append(AcGeVector3d(1.0, 0.0, 0.0));
	alignmentDirections.append(AcGeVector3d(1.0, 0.0, 0.0));
	alignmentDirections.append(AcGeVector3d(1.0, 0.0, 0.0));
	

	return Acad::eOk;
}
