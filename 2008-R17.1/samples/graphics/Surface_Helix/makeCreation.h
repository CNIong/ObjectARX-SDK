// (C) Copyright 2002-2007 by Autodesk, Inc. 
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

class CMakeCreation
{
public:
	CMakeCreation(void);
	~CMakeCreation(void);

	// Add a plane surfaces  using AcDbPlaneSurface Class
	static void AddPlaneSurface();
	
	// Using AcDbExtrudedSurface class to create a extruded surface
	static void AddExtrudedSurface();
	
	// Using AcDbRevolvedSurface to create a revolved surface
	static void AddRevolvesurface();
	
	// Using the AcDbSweptSurface class adds a swept surfaces .
	static void AddSweptSurface();
	 
	// Using the AcDbLoftedSurface class creating a lofted Surface. 
	static void AddLoftedSurface();

	// Add a use AcDbHelix helix. 
	static void AddHelix();
	
	static void CreateExtrudedSurface(AcDbEntity* pSweepEnt,
										const AcGeVector3d& directionVec,
										AcDbSweepOptions& sweepOptions,
										AcCmColor col);

	 
	static AcDbObjectId AddEntityToDatabase(AcDbEntity *pEnt,
											ACHAR *spc=ACDB_MODEL_SPACE,
											AcDbDatabase *pDb=acdbHostApplicationServices()->workingDatabase());
	
	
};
