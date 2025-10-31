#ifndef POLYSAMP_UTIL_H
#define POLYSAMP_UTIL_H
//
// (C) Copyright 1996-2007 by Autodesk, Inc. 
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
// UTIL.H
//
// DESCRIPTION: 

#include "acgi.h"

double  rx_fixangle(double angle);

void    rx_fixindex(int& index, int maxIndex);

Adesk::Boolean rx_wc2uc(ads_point p, ads_point q, Adesk::Boolean vec);

Adesk::Boolean rx_wc2ec(ads_point p, ads_point q, ads_point norm, 
			Adesk::Boolean vec);

Adesk::Boolean rx_uc2wc(ads_point p, ads_point q, Adesk::Boolean vec);

Adesk::Boolean rx_uc2ec(ads_point p, ads_point q, ads_point norm, 
			Adesk::Boolean vec);

Adesk::Boolean rx_ec2wc(ads_point p, ads_point q, ads_point norm, 
			Adesk::Boolean vec);

Adesk::Boolean rx_ec2uc(ads_point p, ads_point q, ads_point norm, 
			Adesk::Boolean vec);

Adesk::Boolean rx_ucsmat(AcGeMatrix3d& mat);

Acad::ErrorStatus postToDb(AcDbEntity* ent);
Acad::ErrorStatus addToDb(AcDbEntity* ent);

Acad::ErrorStatus postToDb(AcDbEntity* ent, AcDbObjectId& objId);
Acad::ErrorStatus addToDb(AcDbEntity* ent, AcDbObjectId& objId);

Acad::ErrorStatus rx_scanPline(AcDb2dPolyline*    pline,
		               AcGePoint3dArray&  points,
		               AcGeDoubleArray&   bulges);

Acad::ErrorStatus rx_scanPline(AcDb3dPolyline*    pline,
		               AcGePoint3dArray&  points);

Acad::ErrorStatus rx_makeArc(const AcGePoint3d    pt1, 
			     const AcGePoint3d    pt2, 
			           double         bulge,
			           AcGeCircArc3d& arc);

Acad::ErrorStatus rx_makeArc(const AcGePoint3d    pt1, 
			     const AcGePoint3d    pt2, 
			           double         bulge,
			     const AcGeVector3d   entNorm,
			           AcGeCircArc3d& arc);

// Given the name of a text style, see if it can be found
// in the current database and get its db id if so.
//
Acad::ErrorStatus rx_getTextStyleId(const TCHAR         *styleName,
                                          AcDbDatabase *db,
                                          AcDbObjectId &styleId);

// Given the db id of an AcDbTextStyleTableRecord, construct
// an AcGiTextStyle structure out of that text style.
//
Acad::ErrorStatus rx_getTextStyle(AcGiTextStyle &ts,
                                  AcDbObjectId  styleId);

Acad::ErrorStatus rx_makeSpline(const AcGePoint3dArray&     pts,
			        AcDbSpline*&         pSpline);
Acad::ErrorStatus
getUniformKnots(int numCtrlPts, int degree, int form, AcGeDoubleArray& knots);

#endif /*POLYSAMP_UTIL_H*/

//- This line allows us to get rid of the .def file in ARX projects
#ifndef _WIN64
#pragma comment(linker, "/export:_acrxGetApiVersion,PRIVATE")
#else
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#endif


