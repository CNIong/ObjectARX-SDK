#ifndef AC_BRLOOP_H
#define AC_BRLOOP_H 1
// (C) Copyright 1995-1999 by Autodesk, Inc.
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
// The AcBrLoop class is the interface class for brep loops. All the
// functionality supported by this class is implemented by the class
// AcBrImpLoop.
//
// This class defines the functions that are pertinent to the loop
// level of a brep topology adjacency hierarchy, which is not exposed
// as a subentity type in AutoCAD and thus cannot be directly set by
// the user; it is set indirectly by the traversers. It is also used
// to set the first loop of a loop list in AcBrFaceLoopTraverser. 
//
// Loops are secondary brep elements and thus have no associated
// geometry. Conceptually, a loop corresponds to a set of neighbouring
// boundary curves on a bounded surface. 
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To set an
// AcBrLoop, call AcBrFaceLoopTraverser::getLoop() or
// AcBrEdgeLoopTraverser::getLoop() using this loop object as input.
//
// The getFace() upward adjacency query returns the face that is
// bounded by this loop (always unique). The face is instantiated by 
// the caller and passed by reference for getFace() to set. If this
// loop object is uninitialised, eUninitialisedObject is returned. If 
// the associated AutoCAD object has been modified since the subentity
// path was last set, eBrepChanged is returned. If the face is missing
// or fails to map to a valid subentity ID, Acad::eNotInDatabase is
// returned. In the event of an error, the face reference object is
// unchanged and is thus likely to be uninitialised.
//
// The getType() loop type query returns a dedicated LoopType enum which
// identifies this loop as being either kLoopExterior or kLoopInterior.
// Note that ambiguous loops on closed periodic surfaces (whether nurb
// parametric or analytic) return kLoopUnclassified; whereas base loops
// on cones and cylinders generally return kLoopWinding.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcBrFace;


class AcBrLoop : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrLoop);
    AcBrLoop();
    AcBrLoop(const AcBrLoop& src);
    ~AcBrLoop();

    // Assignment operator
    AcBrLoop&           operator =      (const AcBrLoop& src);

    // Upward links
    // Face usage of loop (1::1)
    AcBr::ErrorStatus   getFace         (AcBrFace& face) const;

	// Loop type (e.g., exterior vs. interior)
	AcBr::ErrorStatus   getType			(AcBr::LoopType& type) const;
};


#endif
