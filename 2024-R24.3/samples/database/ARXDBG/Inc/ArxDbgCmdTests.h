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

#ifndef ARXDBGCMDTESTS_H
#define ARXDBGCMDTESTS_H

#include "ArxDbgCmd.h"
#include "ArxDbgXdata.h"

/****************************************************************************
**
**  CLASS ArxDbgCmdTests:
**
**  **jma
**
*************************************/

class ArxDbgCmdTests : public ArxDbgCmd {

public:
					ArxDbgCmdTests()	{}
    virtual			~ArxDbgCmdTests()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

		// static command functions
	static void	testState();
	static void	testXform();
	static void testEntMake();
	static void	testTblMake();
	static void testExtents();
	static void testIntersect();
	static void testGetGripPoints();
	static void testGetStretchPoints();
	static void testGetOsnapPoints();
	static void testExtDictAdd();
	static void testExtDictRemove();
	static void testTransDatabaseClones();
	static void testXdata();
	static void testColor();
	static void testCurve();
	static void testPurge();
	static void testCountReferences();
	static void testWblockCloneObjects();
	static void testWorldDraw();
	static void testDwgFiler();
	static void testSelSet();

		// helper functions
	static void	makePointEnt(const AcGePoint3d& pt, int colorIndex);
	static void	extMakeAFace(AcDbBlockTableRecord* blkRec,
						const AcGePoint3d& pt1, const AcGePoint3d& pt2,
						const AcGePoint3d& pt3, const AcGePoint3d& pt4);
	static void	printSnapPts(LPCTSTR typeStr, const AcGePoint3dArray& pts,
						Acad::ErrorStatus es);
	static void	testGetXdata(ArxDbgAppXdata& xdata1, ArxDbgAppXdata& xdata2);

};


#endif    // ARXDBGCMDTESTS_H
