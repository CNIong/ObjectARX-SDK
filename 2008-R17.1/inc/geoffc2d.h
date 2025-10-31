#ifndef AC_GEOFFC2D_H
#define AC_GEOFFC2D_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// DESCRIPTION:
//
// This file contains the class AcGeOffsetCurve2d - A mathematical
// entity used to represent an exact offset of a 2d curve.


#include "gecurv2d.h"
#pragma pack (push, 8)

class 
GE_DLLEXPIMPORT
AcGeOffsetCurve2d : public AcGeCurve2d
{
public:

    // Constructors
    //
    AcGeOffsetCurve2d (const AcGeCurve2d& baseCurve, double offsetDistance);
    AcGeOffsetCurve2d (const AcGeOffsetCurve2d& offsetCurve);

	// Query methods
	//
    const AcGeCurve2d*  curve             () const;
    double              offsetDistance    () const;
	Adesk::Boolean		paramDirection    () const;
	AcGeMatrix2d		transformation    () const;

	// Set methods
	//
    AcGeOffsetCurve2d&  setCurve          (const AcGeCurve2d& baseCurve);
    AcGeOffsetCurve2d&  setOffsetDistance (double distance);

    // Assignment operator.
    //
    AcGeOffsetCurve2d&  operator = (const AcGeOffsetCurve2d& offsetCurve);
};

#pragma pack (pop)
#endif
