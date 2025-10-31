///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
//
// The information contained herein is confidential, proprietary
// to Autodesk,  Inc.,  and considered a trade secret as defined
// in section 499C of the penal code of the State of California.
// Use of  this information  by  anyone  other  than  authorized
// employees of Autodesk, Inc.  is granted  only under a written
// non-disclosure agreement,  expressly  prescribing  the  scope
// and manner of such use.
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
