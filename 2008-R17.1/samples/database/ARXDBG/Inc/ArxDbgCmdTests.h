//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
