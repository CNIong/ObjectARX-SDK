#ifndef AC_GEBLOCK2D_H
#define AC_GEBLOCK2D_H
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
// This file contains the class AcGeBoundBlock2d - An entity used to 
// represent a 2d bounding volume, a parallelogram.
//

#include "geent2d.h"
#pragma pack (push, 8)
class AcGePoint2d;
class AcGeVector2d;

class 
GE_DLLEXPIMPORT
AcGeBoundBlock2d : public AcGeEntity2d
{
public:
                    
	AcGeBoundBlock2d ();
	AcGeBoundBlock2d (const AcGePoint2d& point1, const AcGePoint2d& point2);
	AcGeBoundBlock2d (const AcGePoint2d& base,
                      const AcGeVector2d& dir1, const AcGeVector2d& dir2);
	AcGeBoundBlock2d (const AcGeBoundBlock2d& block);
    
	// Access methods.
    //    
    void              getMinMaxPoints  (AcGePoint2d& point1,
								        AcGePoint2d& point2) const;
    void              get              (AcGePoint2d& base,
								        AcGeVector2d& dir1,
								        AcGeVector2d& dir2) const;
    
	// Set methods.
    //    
    AcGeBoundBlock2d& set         (const AcGePoint2d& point1,
                                   const AcGePoint2d& point2);
    AcGeBoundBlock2d& set         (const AcGePoint2d& base,
                                   const AcGeVector2d& dir1,
                                   const AcGeVector2d& dir2);
    // Expand to contain point.
    //
    AcGeBoundBlock2d& extend      (const AcGePoint2d& point);
   
	// Expand by a specified distance.
    //
    AcGeBoundBlock2d& swell       (double distance);

    // Containment and intersection tests
    //
    Adesk::Boolean    contains    (const AcGePoint2d& point) const;
    Adesk::Boolean    isDisjoint  (const AcGeBoundBlock2d& block)
                                                 const;
    // Assignment operator
    //
    AcGeBoundBlock2d& operator =  (const AcGeBoundBlock2d& block);

	Adesk::Boolean    isBox     () const;
	AcGeBoundBlock2d& setToBox  (Adesk::Boolean);
};


#pragma pack (pop)
#endif
