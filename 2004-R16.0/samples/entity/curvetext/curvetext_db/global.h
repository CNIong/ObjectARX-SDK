// (C) Copyright 1993-1998 by Autodesk, Inc.
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

#ifndef GLOBAL_H
#define GLOBAL_H

struct 
GLOBALS
{
	// Therefore, the maximum limit for the string
	// in our curveText is 256 characters...
	double widthArray[256];

//	AcDcCurveText *pEnt;
//	double startDist;
//	double length;
//	double dist;
//	bool isFirstPoint;
//	bool isDynamic;

//	CString string;
//	CString style;
//	AcDbObjectId styleId;
//	double size;
//	double space;
//	int position;
//	bool showCurve;
//	bool showText;
//	bool fit;
//	bool dynamic;
//	bool getPointDone;
//	bool repeat;
//	bool reverse;
	bool dynamicDisplay;
	double viewSize;
//	RECT clientRect;
};

extern struct GLOBALS global;

#endif