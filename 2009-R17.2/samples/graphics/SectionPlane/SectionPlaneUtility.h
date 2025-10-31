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
#include "StdAfx.h"

class CSectionPlaneUtility
{
public:
	CSectionPlaneUtility(void);
	~CSectionPlaneUtility(void);
	
	static void GetSection();
	static void IterSections();
	
	static void GetSectionData(AcDbSection* pSection);

	static void CSectionPlaneUtility::MoveOrRotateSection(int iMoveOrRotate,
															AcDbObjectId sectionId, 
															AcGePoint3dArray sectVertices,
															ads_real * dist,
															ads_real * rotateAngle);

	static void Generate3dBlock(AcDbSection *pPlane, 
								AcDbObjectId solidId,
								AcString blkName,
								AcGePoint3d pntForBlkRefLocation,
								int iForLayerColor);

								
		static void MakeSectionBlock(AcArray<AcDbEntity*>& ents, 
											AcDbDatabase *pDb,
											AcString sBLockName,
											bool bCreateBlkRef);
		
		static void MakeSectionBlock(AcArray<AcDbEntity*>& ents, 
											AcDbDatabase *pDb,
											AcString sBLockName,
											bool bCreateBlkRef,
											AcGePoint3d pntForBlkRefLocation,
											int iForLayerColor);

	static AcDbObjectId AddEntityToDatabase(AcDbEntity *pEnt,
											ACHAR *spc=ACDB_MODEL_SPACE,
											AcDbDatabase *pDb=acdbHostApplicationServices()->workingDatabase());

	static Acad::ErrorStatus createLayer (const TCHAR* layerName, AcDbObjectId& layerId, int iForLayerColor);
	
};