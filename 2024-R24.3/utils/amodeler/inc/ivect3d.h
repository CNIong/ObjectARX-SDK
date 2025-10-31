///////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form. 
//
// DESCRIPTION:
//
//  Declares class IntVector3d keeping a 3D vector in integer space.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_IVEC3D_H
#define AMODELER_INC_IVEC3D_H


#include "global.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp IntVector3d
{
public:

    // Note: No default constructor
    IntVector3d(int xx, int yy, int zz) : x(xx), y(yy), z(zz) {}

    IntVector3d operator  +(IntVector3d v) const { return IntVector3d(x+v.x, y+v.y, z+v.z); }
    IntVector3d operator  -(IntVector3d v) const { return IntVector3d(x-v.x, y-v.y, z-v.z); }

    int         operator [](int index)     const { return (&x)[index]; }
    int&        operator [](int index)           { return (&x)[index]; }

    bool        operator ==(IntVector3d v) const { return x == v.x && y == v.y && z == v.z; }
    bool        operator !=(IntVector3d v) const { return !(*this == v); }

    void        operator +=(IntVector3d v)       { x += v.x; y += v.y; z += v.z; }
    void        operator -=(IntVector3d v)       { x -= v.x; y -= v.y; z -= v.z; }
        
    // Public data members
    //
    int x, y, z;

};  // Class IntVector3d


AMODELER_NAMESPACE_END
#endif
