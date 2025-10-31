#ifndef AC_GEENT3D_H
#define AC_GEENT3D_H
//
// (C) Copyright 1993-2007 by Autodesk, Inc.
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
// This file contains the class GeEntity3d - An abstract base class
// for all Geometry Library 3d entities.

#include "gegbl.h"
#include "gepnt3d.h"
#include "geent2d.h"
#include "geintrvl.h"
#include "gegblnew.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeEntity3d
{
public:
    ~AcGeEntity3d();

    // Run time type information.
    //
    Adesk::Boolean   isKindOf    (AcGe::EntityId entType) const;
    AcGe::EntityId   type        () const;

    // Make a copy of the entity.
    //
    AcGeEntity3d*    copy        () const;
    AcGeEntity3d&    operator =  (const AcGeEntity3d& entity);

    // Equivalence
    //
    Adesk::Boolean   operator == (const AcGeEntity3d& entity) const;
    Adesk::Boolean   operator != (const AcGeEntity3d& entity) const;
    Adesk::Boolean   isEqualTo   (const AcGeEntity3d& ent,
                                  const AcGeTol& tol = AcGeContext::gTol) const;
    // Matrix multiplication
    //
    AcGeEntity3d&    transformBy (const AcGeMatrix3d& xfm);
    AcGeEntity3d&    translateBy (const AcGeVector3d& translateVec);
    AcGeEntity3d&    rotateBy    (double angle, const AcGeVector3d& vec,
                                  const AcGePoint3d& wrtPoint = AcGePoint3d::kOrigin);
    AcGeEntity3d&    mirror      (const AcGePlane& plane);
    AcGeEntity3d&    scaleBy     (double scaleFactor,
                                  const AcGePoint3d& wrtPoint
                                  = AcGePoint3d::kOrigin);
    // Point containment
    //
    Adesk::Boolean   isOn        (const AcGePoint3d& pnt,
                                  const AcGeTol& tol = AcGeContext::gTol) const;
protected:
    friend class AcGeImpEntity3d;
    AcGeImpEntity3d  *mpImpEnt;
    int              mDelEnt;
    AcGeEntity3d ();
    AcGeEntity3d (const AcGeEntity3d&);
    AcGeEntity3d (AcGeImpEntity3d&, int);
    AcGeEntity3d (AcGeImpEntity3d*);
    AcGeEntity2d* newEntity2d (AcGeImpEntity3d*) const;
    AcGeEntity2d* newEntity2d (AcGeImpEntity3d&, int) const;
    AcGeEntity3d* newEntity3d (AcGeImpEntity3d*) const;
    AcGeEntity3d* newEntity3d (AcGeImpEntity3d&, int) const;
};

__forceinline AcGeEntity2d*
AcGeEntity3d::newEntity2d (AcGeImpEntity3d *impEnt ) const
{
    return GENEWLOC( AcGeEntity2d, this) ( impEnt );
}

__forceinline AcGeEntity3d*
AcGeEntity3d::newEntity3d (AcGeImpEntity3d *impEnt ) const
{
    return GENEWLOC( AcGeEntity3d, this) ( impEnt );
}

__forceinline AcGeEntity3d*
AcGeEntity3d::newEntity3d(AcGeImpEntity3d& impEnt, int dummy) const
{
    return GENEWLOC( AcGeEntity3d, this)(impEnt, dummy);
}

__forceinline AcGeEntity2d*
AcGeEntity3d::newEntity2d(AcGeImpEntity3d& impEnt, int dummy) const
{
    return GENEWLOC( AcGeEntity2d, this)(impEnt, dummy);
}

#pragma pack (pop)
#endif
