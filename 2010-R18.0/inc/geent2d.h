#ifndef AC_GEENT2D_H
#define AC_GEENT2D_H
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
// This file contains the class GeEntity2d - An abstract base class
// for all Geometry Library 2d entities.

#include "gegbl.h"
#include "gepnt2d.h"
#include "geintrvl.h"
#include "gegblnew.h"
#pragma pack (push, 8)

class
GE_DLLEXPIMPORT
AcGeEntity2d
{
public:
    ~AcGeEntity2d();

    // Run time type information.
    //
    Adesk::Boolean   isKindOf    (AcGe::EntityId entType) const;
    AcGe::EntityId   type        () const;

    // Make a copy of the entity.
    //
    AcGeEntity2d*    copy        () const;
    AcGeEntity2d&    operator =  (const AcGeEntity2d& entity);

    // Equivalence
    //
    Adesk::Boolean   operator == (const AcGeEntity2d& entity) const;
    Adesk::Boolean   operator != (const AcGeEntity2d& entity) const;
    Adesk::Boolean   isEqualTo   (const AcGeEntity2d& entity,
                                  const AcGeTol& tol = AcGeContext::gTol) const;
                                            
    // Matrix multiplication
    //
    AcGeEntity2d&    transformBy (const AcGeMatrix2d& xfm);
    AcGeEntity2d&    translateBy (const AcGeVector2d& translateVec);
    AcGeEntity2d&    rotateBy    (double angle, const AcGePoint2d& wrtPoint
                                  = AcGePoint2d::kOrigin);      
    AcGeEntity2d&    mirror      (const AcGeLine2d& line);
    AcGeEntity2d&    scaleBy     (double scaleFactor,
                                  const AcGePoint2d& wrtPoint
                                  = AcGePoint2d::kOrigin);
    // Point containment
    //
    Adesk::Boolean   isOn        (const AcGePoint2d& pnt,
                                  const AcGeTol& tol = AcGeContext::gTol) const;
protected:
    friend class AcGeEntity3d;
    friend class AcGeImpEntity3d;
    AcGeImpEntity3d* mpImpEnt;
    int mDelEnt;
    AcGeEntity2d ();
    AcGeEntity2d (const AcGeEntity2d&);
    AcGeEntity2d (AcGeImpEntity3d&, int);
    AcGeEntity2d (AcGeImpEntity3d*);
    AcGeEntity2d*    newEntity2d (AcGeImpEntity3d*) const;
};


__forceinline AcGeEntity2d*   
AcGeEntity2d::newEntity2d (AcGeImpEntity3d *impEnt ) const
{
    return GENEWLOC( AcGeEntity2d, this) ( impEnt );
}

#pragma pack (pop)
#endif
