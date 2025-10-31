#ifndef AC_GEOFFC3D_H
#define AC_GEOFFC3D_H
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
// This file contains the class AcGeOffsetCurve3d - A mathematical
// entity used to represent an exact offset of a 3d curve.


#include "gecurv3d.h"
#pragma pack (push, 8)

class 
GE_DLLEXPIMPORT
AcGeOffsetCurve3d : public AcGeCurve3d
{
public:

    // Constructors
    //
    AcGeOffsetCurve3d (const AcGeCurve3d& baseCurve, const AcGeVector3d& planeNormal,
                       double offsetDistance);
    AcGeOffsetCurve3d (const AcGeOffsetCurve3d& offsetCurve);

	// Query methods
	//
    const AcGeCurve3d*  curve             () const;
    AcGeVector3d        normal            () const; 
    double              offsetDistance    () const;
	Adesk::Boolean		paramDirection    () const;
	AcGeMatrix3d		transformation    () const;

	// Set methods
	//
    AcGeOffsetCurve3d&  setCurve          (const AcGeCurve3d& baseCurve);
    AcGeOffsetCurve3d&  setNormal         (const AcGeVector3d& planeNormal);
    AcGeOffsetCurve3d&  setOffsetDistance (double offsetDistance);

    // Assignment operator.
    //
    AcGeOffsetCurve3d&  operator = (const AcGeOffsetCurve3d& offsetCurve);
};

#pragma pack (pop)
#endif
