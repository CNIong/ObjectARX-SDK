// Copyright 2004-2006 by Autodesk, Inc.
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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

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
