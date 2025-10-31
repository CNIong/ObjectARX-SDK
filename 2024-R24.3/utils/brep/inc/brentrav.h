#ifndef AC_BRENTRAV_H
#define AC_BRENTRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrElement2dNodeTraverser class is the interface class for
// element node traversers. All the functionality supported by this
// class is implemented by the class AcBrImpElement2dNodeTraverser.
//
// This class defines the functions that are pertinent to a node
// in the context of a 2d element. It is used to get access to node
// data contexted to the true geometry of the original surface, such
// as surface normals and uv parameter pairs (nodes are used by more
// than one mesh element and may also be associated with more than
// one surface). Nodes are consistently traversed in a clockwise
// direction on the element, as defined by the original face.
//
// The default constructor instantiates an uninitialised object. The
// function isNull() returns kTrue on an object created this way. To
// set an AcBrElement2dNodeTraverser, call setElement() using a valid,
// previously instantiated 2d element object.
//
// The setElement() list owner initialiser(1) is used to set this
// traverser to a specific element node list, starting at the
// first node in the list. This initialises a traverser instantiated
// with the default constructor, and resets the criteria for next()
// and done(). If the element reference object is uninitialised,
// Acad::eInvalidInput is returned. In the event of an error,
// this traverser's element node list is unchanged.
//
// The setElement() list owner initialiser(2) is used to set this
// traverser to a specific element node list, starting at the
// first node in the list. This initialises a traverser instantiated
// with the default constructor, and resets the criteria for next()
// and done(). If the mesh element traverser reference object is
// uninitialised, Acad::eInvalidInput is returned. In the event of
// an error, this traverser's element node list is unchanged.
//
// The getElement() list owner query returns the element owner of the
// element node list. The element object is instantiated by the caller
// and passed by reference for getElement() to set. If this traverser
// object is uninitialised, eUninitialisedObject is returned. In the
// event of an error, the element reference object is unchanged and
// is thus likely to be uninitialised.
//
// The setNode() list position initialiser is used to set this
// traverser's starting position to a specific node in the element
// node list, which resets the criteria for next() and done(). If
// this traverser object is uninitialised, eUninitialisedObject is
// returned. If the associated mesh object has been modified since the
// traverser was last set, eMeshChanged is returned. If the node
// reference object is uninitialised, or if the associated mesh object
// has been modified since the node reference object was last set,
// Acad::eInvalidInput is returned. If the node is not in the element
// node list or is associated with a different mesh object or revision,
// Acad::eInvalidInput is returned. In the event of an error, this
// traverser's element node list is unchanged.
//
// The getNode() list position query returns the node at the current
// position in the element node list. The node object is instantiated
// by the caller and passed by reference for getNode() to set. If this
// traverser object is uninitialised, eUninitialisedObject is returned.
// In the event of an error, the node reference object is unchanged and
// is thus likely to be uninitialised.
//
// The getSurfaceNormal() surface normal query returns the normalised
// model space normal vector computed on the original face at the 
// current node. The normal vector is returned as an AcGeVector3d, 
// with the entire chain of transforms from the original face applied. 
// The vector is instantiated by the caller and passed by reference for
// getSurfaceNormal() to set. If this traverser object is uninitialised, 
// eUninitialisedObject is returned. In the event of an error, the 
// normal vector reference argument's value is unchanged.
//
// The getParamPoint() parameter space point query returns the 2d
// element node's underlying parameter point as an AcGePoint2d, with
// the entire chain of transforms from the original face ignored as
// they are only pertinent to model space. The parameter point
// corresponds to the node's model space point projected onto the
// uv parameter space grid of the surface associated with the original
// face that generated this 2d element. A 2d point is a convenient
// way to represent a u,v parameter pair. The parameter point is
// instantiated by the caller and passed by reference for getParamPoint()
// to set. If this traverser object is uninitialised, eUninitialisedObject
// is returned. In the event of an error, the parameter point reference
// argument's value is unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "gegbl.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcGePoint2d;
class AcGeVector3d;
class AcBrElement2d;
class AcBrNode;
class AcBrMesh2dElement2dTraverser;


class AcBrElement2dNodeTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrElement2dNodeTraverser);
    AcBrElement2dNodeTraverser();
    AcBrElement2dNodeTraverser(const AcBrElement2dNodeTraverser& src);
    ~AcBrElement2dNodeTraverser();
    
    // Assignment operator
    AcBrElement2dNodeTraverser& operator =(const AcBrElement2dNodeTraverser& src);

    // Queries & Initialisers
	AcBr::ErrorStatus   setElement		(const AcBrMesh2dElement2dTraverser& mesh2dElement2dTraverser);
    AcBr::ErrorStatus   setElement		(const AcBrElement2d& element);
    AcBr::ErrorStatus   getElement		(AcBrElement2d& element) const;
    AcBr::ErrorStatus   setNode         (const AcBrNode& node);
    AcBr::ErrorStatus   getNode         (AcBrNode& node) const;

	// Upward links
	// Node usage by original face (1::1)
    AcBr::ErrorStatus   getSurfaceNormal(AcGeVector3d& vector) const;
    AcBr::ErrorStatus   getParamPoint	(AcGePoint2d& point) const;
};


#endif

