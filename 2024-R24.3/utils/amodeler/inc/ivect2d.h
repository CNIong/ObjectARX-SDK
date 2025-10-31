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

#ifndef AMODELER_INC_IVEC2D_H
#define AMODELER_INC_IVEC2D_H


#include "global.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp IntVector2d
{
public:

    // Note: No default constructor
    IntVector2d(int xx, int yy) : x(xx), y(yy) {}

    IntVector2d operator  +(IntVector2d v) const { return IntVector2d(x+v.x, y+v.y); }
    IntVector2d operator  -(IntVector2d v) const { return IntVector2d(x-v.x, y-v.y); }

    int         operator [](int index)     const { return (&x)[index]; }
    int&        operator [](int index)           { return (&x)[index]; }

    bool        operator ==(IntVector2d v) const { return x == v.x && y == v.y; }
    bool        operator !=(IntVector2d v) const { return !(*this == v); }

    void        operator +=(IntVector2d v)       { x += v.x; y += v.y; }
    void        operator -=(IntVector2d v)       { x -= v.x; y -= v.y; }
        
    // Public data members
    //
    int x, y;

};  // Class IntVector2d


AMODELER_NAMESPACE_END
#endif
