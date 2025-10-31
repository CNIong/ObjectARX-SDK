#ifndef AC_GESSINT_H
#define AC_GESSINT_H
//
// (C) Copyright 1998-2004 by Autodesk, Inc. 
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
// Description: class  AcGeSurfSurfInt to hold data for intersections
// of two surfaces.

#include "adesk.h"
#include "geent3d.h"
#include "gegbl.h"
#include "gegblabb.h"
#pragma pack (push, 8)

class AcGeCurve3d;
class AcGeCurve2d;

class AcGeSurface;

// The intersection class constructor references surface objects, but the
// intersection object does not own them.  The surface objects are linked to the
// intersection object.  On deletion or modification of one of them, internal
// intersection results are marked as invalid and to be re-computed.
//
// Computation of the intersection does not happen on construction or set(), but
// on demand from one of the query functions..
//
// Any output geometry from an intersection object is owned by the caller.  The
// const base objects returned by surface1() and surface2() are not considered
// output objects.
//

class  
GX_DLLEXPIMPORT
AcGeSurfSurfInt  : public AcGeEntity3d
{

public:
    // Constructors.
    //
    AcGeSurfSurfInt ();
    AcGeSurfSurfInt (
						const AcGeSurface& srf1, 
						const AcGeSurface& srf2,
						const AcGeTol& tol = AcGeContext::gTol );
    AcGeSurfSurfInt (const AcGeSurfSurfInt& src);

    // General query functions.
    //
    const AcGeSurface  *surface1        () const;
    const AcGeSurface  *surface2        () const;
    AcGeTol            tolerance        () const;

    // Intersection query methods.
    //
    int                numResults (AcGe::AcGeIntersectError& err) const;
                    // Counts the number of intersection results of any dimension.
    AcGeCurve3d*   intCurve (int intNum, Adesk::Boolean isExternal, AcGe::AcGeIntersectError& err) const; 
					// Returns NULL if the dimension of  this intersection is not 1.
    AcGeCurve2d*   intParamCurve(int num, Adesk::Boolean isExternal, Adesk::Boolean isFirst, AcGe::AcGeIntersectError& err) const;
					// Returns NULL if the dimension of  this intersection is not 1.
                    // if isFirst returns parameter curve on 1st surface, otherwise returns parameter curve on 2nd surface.
	AcGePoint3d  intPoint (int intNum, AcGe::AcGeIntersectError& err) const;
					//  Invalid return if the dimension of this intersection is not 0.
    void               getIntPointParams (int intNum,
                                         AcGePoint2d& param1, AcGePoint2d& param2, AcGe::AcGeIntersectError& err) const;
	void getIntConfigs (int intNum, AcGe::ssiConfig& surf1Left,  AcGe::ssiConfig& surf1Right, 
							AcGe::ssiConfig& surf2Left,  AcGe::ssiConfig& surf2Right,  
							AcGe::ssiType& intType, int& dim, AcGe::AcGeIntersectError& err ) const; 
    int		getDimension (int intNum, AcGe::AcGeIntersectError& err) const;
	AcGe::ssiType	getType(int intNum, AcGe::AcGeIntersectError& err ) const;

    // Set functions.
    //
    AcGeSurfSurfInt& set (const AcGeSurface& srf1,
                                     const AcGeSurface& srf2,
                                     const AcGeTol& tol = AcGeContext::gTol);

    // Assignment operator.
    //
    AcGeSurfSurfInt& operator = (const AcGeSurfSurfInt& crvInt);
};
#pragma pack (pop)
#endif
