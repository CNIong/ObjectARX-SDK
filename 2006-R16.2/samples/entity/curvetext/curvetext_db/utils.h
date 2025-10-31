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

#ifndef _UTILS_H
#define _UTILS_H 

#define ABOVE 0
#define MIDDLE 1
#define BELOW 2

#include <dbmain.h>
#include "CurveText.h"
#include <dbapserv.h>
extern "C"	const char* acadErrorStatusText(Acad::ErrorStatus);

#define		PI			3.14159265358979323846
#define		MESSAGE(x)	acadErrorStatusText(x)

#define INTERNAL_STATUS_ERROR(x) \
  acrx_abort("!%s@%d: %s", __FILE__, __LINE__, MESSAGE(x))

#define RETURN_STATUS_ERROR(x) { \
	char errorBuffer[256];	\
	sprintf(errorBuffer, "!%s@%d: %s", \
			__FILE__, __LINE__, MESSAGE(x)); \
			acutPrintf(errorBuffer); \
	return x; }

#define AOK(what) { Acad::ErrorStatus stat = what; \
  if (stat != Acad::eOk) INTERNAL_STATUS_ERROR(stat); }

#define ISOK(what) {Acad::ErrorStatus stat = what; \
if (stat != Acad::eOk) RETURN_STATUS_ERROR(stat);}


struct 
GLOBALS
{
	// Therefore, the maximum limit for the string
	// in our curveText is 255 characters...
	double widthArray[256];
	bool dynamicDisplay;
};

extern struct GLOBALS global;

Acad::ErrorStatus	getTextStyleName(CString& styleName, 
									 AcDbObjectId styleId);
AcDbObjectId		getStandardStyleId();
void				updateRegistry();
void				printPoint(AcGePoint3d pt);


#endif