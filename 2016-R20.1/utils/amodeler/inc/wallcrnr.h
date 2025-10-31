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
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_WALLCRNR_H
#define AMODELER_INC_WALLCRNR_H


#include "global.h"

AMODELER_NAMESPACE_BEGIN


// Creates a wall corner body at the intersection of two walls. The first wall
// is defined by points p1,p2, the second wall is defined by points p2,p3. The 
// walls lie to the right from their defining line segments.
//
// The matingFacesColor input argument specifies the color which is going to be
// assigned to the faces and edges of the created corner body which touch the 
// two walls. Assigning a special color allows to identify edges which are at 
// the touch with the two walls and these marked edges may then not be 
// displayed or displayed in a different way.
//
// If the wall1,2NeedsToBeSectioned output argument is true, the corner body 
// intersects the wall and the wall needs to be sectioned (using the 
// Body::section(const Plane&) method) in order to make the wall cleanly touch 
// the corner body.
// 
// The output arguments matingPlane1,2 always contain the equations of the
// mating planes, regardless whether the mating planes actually intersect the
// walls or just touch them.
//
DllImpExp Body createWallCornerBody(
                    const Point2d& pt1,     // Start of wall 1
                    const Point2d& pt2,     // End of wall 1, start of wall 2
                    const Point2d& pt3,     // End of wall 2
                    bool           materialToTheLeft,
                    double         width1,  // Wall 1 width
                    double         width2,  // Wall 2 width
                    double         height,  // Wall height
                    Color          matingFacesColor,
                    Plane&         matingPlane1,
                    Plane&         matingPlane2,
                    bool&          wall1NeedsToBeSectioned,
                    bool&          wall2NeedsToBeSectioned);

AMODELER_NAMESPACE_END
#endif

