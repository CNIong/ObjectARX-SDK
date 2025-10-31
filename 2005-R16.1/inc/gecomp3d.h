#ifndef AC_GECOMP3D_H
#define AC_GECOMP3D_H
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
// This file contains the class AcGeCompositeCurve3d - A mathematical
// entity used to represent a composite curve. Curve is parametrized 
// by Ravi-parametrization: that is n-th segment is parametrized by
// interval [ n, n + 1 ];


#include "gecurv3d.h"
#include "gevptar.h"
#include "geintarr.h"
#pragma pack (push, 8)

class 
GE_DLLEXPIMPORT
AcGeCompositeCurve3d : public AcGeCurve3d
{
public:
    AcGeCompositeCurve3d  ();
    AcGeCompositeCurve3d  (const AcGeVoidPointerArray& curveList);
    AcGeCompositeCurve3d  (const AcGeVoidPointerArray& curveList,
		                   const AcGeIntArray& isOwnerOfCurves);
    AcGeCompositeCurve3d  (const AcGeCompositeCurve3d& compCurve);

    // Definition of trimmed curve
    //
    void		          getCurveList       (AcGeVoidPointerArray& curveList) const;

    // Set methods
    //
    AcGeCompositeCurve3d& setCurveList       (const AcGeVoidPointerArray& curveList);
    AcGeCompositeCurve3d& setCurveList       (const AcGeVoidPointerArray& curveList,
		                                      const AcGeIntArray& isOwnerOfCurves);
	
	// Convert parameter on composite to parameter on component curve and vice-versa.
	//
	double				  globalToLocalParam ( double param, int& segNum ) const; 
	double				  localToGlobalParam ( double param, int segNum ) const; 

    // Assignment operator.
    //
    AcGeCompositeCurve3d& operator =         (const AcGeCompositeCurve3d& compCurve);
};

#pragma pack (pop)
#endif
