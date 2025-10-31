#ifndef AC_BRBCTRAV_H
#define AC_BRBCTRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrBrepComplexTraverser class is the interface class for brep
// complex traversers. All the functionality supported by this class
// is implemented by the class AcBrImpBrepComplexTraverser.
//
// This class defines the functions that are pertinent to a complex
// in the global context of a brep. It is used to traverse all of
// the unique complexes in a brep.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To
// set an AcBrBrepComplexTraverser, call setBrep() and/or setComplex()
// using valid, previously instantiated brep and complex objects.
//
// The setBrepAndComplex() list initialiser is used to set this 
// traverser to a specific brep complex list and starting position.
// This initialises a traverser instantiated with the default constructor, 
// and resets the criteria for the eBrepChanged error as well as the
// criteria for next() and done(). It also sets the validation level 
// to match that of the complex. The brep list owner is inferred from
// the complex, as it is unique. If the complex reference object is 
// uninitialised, or if the associated AutoCAD object has been modified
// since the complex reference object was last set, Acad::eInvalidInput 
// is returned. In the event of an error, this traverser's brep complex 
// list is unchanged.
//
// The setBrep() list owner initialiser is used to set this traverser 
// to a specific brep complex list, starting at the first complex in
// the list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error
// as well as the criteria for next() and done(). It also sets the
// validation level to match that of the brep. If the brep reference
// object is uninitialised, or if the associated AutoCAD object has
// been modified since the brep reference object was last set, Acad::
// eInvalidInput is returned. If the brep is not complex-bounded (e.g.,
// a wireframe or an empty/deleted/unsurfaced model), eDegenerateTopology 
// is returned. In the event of an error, this traverser's brep complex 
// list is unchanged.
//
// The getBrep() list owner query returns the brep owner of the
// complex list. The brep object is instantiated by the caller and
// passed by reference for getBrep() to set. If this traverser object
// is uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the traverser was last
// set, eBrepChanged is returned. In the event of an error, the
// brep reference object is unchanged and is thus likely to be
// uninitialised.
//
// The setComplex() list position initialiser is used to set this
// traverser's starting position to a specific complex in the brep
// complex list, which resets the criteria for next() and done(). If 
// this traverser object is uninitialised, eUninitialisedObject is
// returned. If the associated AutoCAD object has been modified since
// the traverser was last set, eBrepChanged is returned. If the complex
// reference object is uninitialised, or if the associated AutoCAD
// object has been modified since the complex reference object was last
// set, Acad::eInvalidInput is returned. If the complex is not in the
// brep complex list or is associated with a different AutoCAD object
// or revision, Acad::eWrongDatabase is returned. In the event of
// an error, this traverser's brep complex list is unchanged.
//
// The getComplex() list position query returns the complex at the current
// position in the brep complex list. The complex object is instantiated
// by the caller and passed by reference for getComplex() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// If the associated AutoCAD object has been modified since the traverser
// was last set, eBrepChanged is returned. If the complex is missing,
// Acad::eWrongDatabase is returned. In the event of an error, the complex
// reference object is unchanged and is thus likely to be uninitialised.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrBrep;
class AcBrComplex;


class AcBrBrepComplexTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrBrepComplexTraverser);
    AcBrBrepComplexTraverser();
    AcBrBrepComplexTraverser(const AcBrBrepComplexTraverser& src);
    ~AcBrBrepComplexTraverser();

    // Assignment operator
    AcBrBrepComplexTraverser& operator =(const AcBrBrepComplexTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setBrepAndComplex(const AcBrComplex& complex);
    AcBr::ErrorStatus   setBrep         (const AcBrBrep& brep);
    AcBr::ErrorStatus   getBrep         (AcBrBrep& brep) const;
    AcBr::ErrorStatus   setComplex      (const AcBrComplex& complex);
    AcBr::ErrorStatus   getComplex      (AcBrComplex& complex) const;
};


#endif

