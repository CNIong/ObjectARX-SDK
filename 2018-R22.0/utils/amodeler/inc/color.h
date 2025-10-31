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
