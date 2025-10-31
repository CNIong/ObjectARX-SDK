#ifndef AC_BRMETRAV_H
#define AC_BRMETRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrMesh2dElement2dTraverser class is the interface class for
// mesh element traversers. All the functionality supported by this
// class is implemented by the class AcBrImpMesh2dElement2dTraverser.
//
// This class defines the functions that are pertinent to a 2d element
// in the global context of a 2d mesh. It is used to seed a downward
// hierarchical traversal of a 2d mesh, or to traverse all of the unique
// 2d elements and nodes in a 2d mesh.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To
// set an AcBrMesh2dElement2dTraverser, call setMesh() using a valid,
// previously instantiated 2d mesh object.
//
// The setMeshAndElement() list initialiser is used to set this traverser
// to a specific mesh element list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for next() and done(). The mesh list owner is inferred
// from the element, as it is unique. If the element reference object
// is uninitialised, Acad::eInvalidInput is returned. In the event of
// an error, this traverser's mesh element list is unchanged.
//
// The setMesh() list owner initialiser is used to set this traverser
// to a specific mesh element list, starting at the first element 
// in the list. This initialises a traverser instantiated with the
// default constructor, and resets the criteria for next() and
// done(). If the mesh reference object is uninitialised,
// Acad::eInvalidInput is returned. In the event of an error,
// this traverser's mesh element list is unchanged.
//
// The getMesh() list owner query returns the mesh owner of the mesh
// element list. The mesh object is instantiated by the caller and
// passed by reference for getMesh() to set. If this traverser object
// is uninitialised, eUninitialisedObject is returned. In the event
// of an error, the mesh reference object is unchanged and is thus
// likely to be uninitialised.
//
// The setElement() list position initialiser is used to set this
// traverser's starting position to a specific element in the mesh
// element list, which resets the criteria for next() and done(). If
// this traverser object is uninitialised, eUninitialisedObject is
// returned. If the associated mesh object has been modified since the
// traverser was last set, eMeshChanged is returned. If the element
// reference object is uninitialised, or if the associated mesh object
// has been modified since the element reference object was last set,
// Acad::eInvalidInput is returned. If the element is not in the mesh
// element list or is associated with a different mesh object or
// revision, Acad::eInvalidInput is returned. In the event of an
// error, this traverser's mesh element list is unchanged.
//
// The getElement() list position query returns the element at the
// current position in the mesh element list. The element object is
// instantiated by the caller and passed as by reference for getElement()
// to set. If this traverser object is uninitialised, eUninitialisedObject
// is returned. In the event of an error, the element reference object
// is unchanged and is thus likely to be uninitialised.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrMesh2d;
class AcBrElement2d;


class AcBrMesh2dElement2dTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrMesh2dElement2dTraverser);
    AcBrMesh2dElement2dTraverser();
    AcBrMesh2dElement2dTraverser(const AcBrMesh2dElement2dTraverser& src);
    ~AcBrMesh2dElement2dTraverser();
    
    // Assignment operator
    AcBrMesh2dElement2dTraverser& operator =(const AcBrMesh2dElement2dTraverser& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   setMeshAndElement(const AcBrElement2d& element2d);
    AcBr::ErrorStatus   setMesh         (const AcBrMesh2d& mesh2d);
    AcBr::ErrorStatus   getMesh         (AcBrMesh2d& mesh2d) const;
    AcBr::ErrorStatus   setElement		(const AcBrElement2d& element2d);
    AcBr::ErrorStatus   getElement		(AcBrElement2d& element2d) const;
};


#endif

