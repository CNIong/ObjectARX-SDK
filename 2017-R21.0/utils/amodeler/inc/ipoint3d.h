///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
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
// Declares class IntPoint3d keeping a 3D point in integer space.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_IPOINT3D_H
#define AMODELER_INC_IPOINT3D_H


#include "ipoint2d.h"
#include "ivect3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp IntPoint3d
{
public:

    IntPoint3d() {} // Note: No default constructor
    IntPoint3d(int xx, int yy, int zz) : x(xx), y(yy), z(zz) {}

    IntPoint3d  operator  +(IntPoint3d  p) const { return IntPoint3d (x+p.x, y+p.y, z+p.z); }
    IntPoint3d  operator  +(IntVector3d v) const { return IntPoint3d (x+v.x, y+v.y, z+v.z); }
    IntVector3d operator  -(IntPoint3d  p) const { return IntVector3d(x-p.x, y-p.y, z-p.z); }
    IntPoint3d  operator  -(IntVector3d v) const { return IntPoint3d (x-v.x, y-v.y, z-v.z); }
    IntPoint3d  operator  -()              const { return IntPoint3d(-x, -y, -z);           }

    int         operator [](int index)     const { return (&x)[index]; }
    int&        operator [](int index)           { return (&x)[index]; }

    bool        operator ==(IntPoint3d  p) const { return x == p.x && y == p.y && z == p.z; }
    bool        operator !=(IntPoint3d  p) const { return !(*this == p); }

    void        operator +=(IntPoint3d  p) { x += p.x; y += p.y; z += p.z; }
    void        operator +=(IntVector3d v) { x += v.x; y += v.y; z += v.z; }
    void        operator -=(IntPoint3d  p) { x -= p.x; y -= p.y; z -= p.z; }
    void        operator -=(IntVector3d v) { x -= v.x; y -= v.y; z -= v.z; }

    const IntPoint2d& toIntPoint2d() const { return *((IntPoint2d*)this); }
        
    // Public data members
    //
    int x, y, z;

    static const IntPoint3d kNull;

};  // Class IntPoint3d


AMODELER_NAMESPACE_END
#endif
