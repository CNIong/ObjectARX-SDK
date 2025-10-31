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
