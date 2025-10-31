#ifndef AC_GECINT2D_H
#define AC_GECINT2D_H
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
// Description: class  AcGeCurveCurveInt2d to hold data for intersectios
// of two 2d curves

#include "adesk.h"
#include "gegbl.h"
#include "geent2d.h"
#include "geponc2d.h"
#include "geintrvl.h"
#pragma pack (push, 8)

class AcGeCurve2d;


class  
GE_DLLEXPIMPORT
AcGeCurveCurveInt2d : public AcGeEntity2d
{

public:
    // Constructors.
    //
    AcGeCurveCurveInt2d ();
    AcGeCurveCurveInt2d (const AcGeCurve2d& curve1, const AcGeCurve2d& curve2,
                         const AcGeTol& tol = AcGeContext::gTol );
    AcGeCurveCurveInt2d (const AcGeCurve2d& curve1, const AcGeCurve2d& curve2,
                         const AcGeInterval& range1, const AcGeInterval& range2,
                         const AcGeTol& tol = AcGeContext::gTol);
    AcGeCurveCurveInt2d (const AcGeCurveCurveInt2d& src);

    // General query functions.
    //
    const AcGeCurve2d  *curve1          () const;
    const AcGeCurve2d  *curve2          () const;
    void               getIntRanges     (AcGeInterval& range1,
                                         AcGeInterval& range2) const;
    AcGeTol            tolerance        () const;

    // Intersection query methods.
    //
    int                numIntPoints     () const;
    AcGePoint2d        intPoint         (int intNum) const;
    void               getIntParams     (int intNum,
                                         double& param1, double& param2) const;
    void               getPointOnCurve1 (int intNum, AcGePointOnCurve2d&) const;
    void               getPointOnCurve2 (int intNum, AcGePointOnCurve2d&) const;
    void			   getIntConfigs    (int intNum, AcGe::AcGeXConfig& config1wrt2, 
                                         AcGe::AcGeXConfig& config2wrt1) const;
    Adesk::Boolean     isTangential     (int intNum) const;
    Adesk::Boolean     isTransversal    (int intNum) const;
    double             intPointTol      (int intNum) const;
    int                overlapCount     () const;
	Adesk::Boolean	   overlapDirection () const;
    void               getOverlapRanges (int overlapNum,
                                         AcGeInterval& range1,
                                         AcGeInterval& range2) const;

    // Curves change their places
    //
    void               changeCurveOrder (); 
        
    // Order with respect to parameter on the first/second curve.
    //
    AcGeCurveCurveInt2d& orderWrt1  ();    
    AcGeCurveCurveInt2d& orderWrt2  ();
    
	// Set functions.
    //
    AcGeCurveCurveInt2d& set        (const AcGeCurve2d& curve1,
                                     const AcGeCurve2d& curve2,
                                     const AcGeTol& tol = AcGeContext::gTol);
    AcGeCurveCurveInt2d& set        (const AcGeCurve2d& curve1,
                                     const AcGeCurve2d& curve2,
                                     const AcGeInterval& range1,
                                     const AcGeInterval& range2,
                                     const AcGeTol& tol = AcGeContext::gTol);

    // Assignment operator.
    //
    AcGeCurveCurveInt2d& operator = (const AcGeCurveCurveInt2d& src);
};

#pragma pack (pop)
#endif
