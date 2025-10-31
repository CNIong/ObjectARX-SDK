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
// Faces and edges have a color attribute.
//
// The modeler calls the defaultColor() function anytime it needs to obtain
// the current color value. This is the only interface of the modeler to the
// "color subsystem." Otherwise, the color is irrelevant to the modeler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_COLOR_H
#define AMODELER_INC_COLOR_H


#include "global.h"

AMODELER_NAMESPACE_BEGIN


enum Color { kColor1            = 1, 
             kColor2            = 2,
             kColor3            = 3,
             kColor4            = 4,    // Feel free to invent more colors
             kColorInvisible    = -1 };


DllImpExp extern Color gDefaultColor;


inline Color defaultColor   ()         { return gDefaultColor; }
inline void  setDefaultColor(Color co) { gDefaultColor = co;   }
 
AMODELER_NAMESPACE_END
#endif
