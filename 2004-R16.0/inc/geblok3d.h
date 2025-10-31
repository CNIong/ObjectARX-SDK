#ifndef AC_GEBLOCK3D_H
#define AC_GEBLOCK3D_H
//
// (C) Copyright 1993-2002 by Autodesk, Inc.
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
// This file contains the class AcGeBoundBlock3d - An entity used to 
// represent a 3d bounding volume, a parallelepiped.
//

#include "geent3d.h"
#pragma pack (push, 8)
class AcGePoint3d;
class AcGeVector3d;

class 
GE_DLLEXPIMPORT
AcGeBoundBlock3d : public AcGeEntity3d
{
public:
                    
	AcGeBoundBlock3d ();
	AcGeBoundBlock3d (const AcGePoint3d& base, const AcGeVector3d& dir1,
					  const AcGeVector3d& dir2, const AcGeVector3d& dir3);
	AcGeBoundBlock3d (const AcGeBoundBlock3d& block);
    
	// Access methods.
    //    
    void              getMinMaxPoints  (AcGePoint3d& point1,
								        AcGePoint3d& point2) const;
    void              get              (AcGePoint3d& base,
								        AcGeVector3d& dir1,
								        AcGeVector3d& dir2,
								        AcGeVector3d& dir3) const;
	// Set methods.
    //    
    AcGeBoundBlock3d& set              (const AcGePoint3d& point1,
								        const AcGePoint3d& point2);
    AcGeBoundBlock3d& set              (const AcGePoint3d& base,
								        const AcGeVector3d& dir1,
								        const AcGeVector3d& dir2,
								        const AcGeVector3d& dir3);
    // Expand to contain point.
    //
    AcGeBoundBlock3d& extend           (const AcGePoint3d& point);
   
	// Expand by a specified distance.
    //
    AcGeBoundBlock3d& swell            (double distance);

    // Containment and intersection tests
    //
    Adesk::Boolean    contains         (const AcGePoint3d& point) const;
    Adesk::Boolean    isDisjoint       (const AcGeBoundBlock3d& block) const;

    // Assignment opearator
    //
    AcGeBoundBlock3d& operator =       (const AcGeBoundBlock3d& block);

    Adesk::Boolean     isBox    () const;
    AcGeBoundBlock3d&  setToBox (Adesk::Boolean);
};


#pragma pack (pop)
#endif
