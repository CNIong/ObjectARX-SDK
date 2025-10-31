#ifndef AC_BRMESH2D_H
#define AC_BRMESH2D_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrMesh2d class is the interface class for 2d meshes. All
// the functionality supported by this class is implemented by
// the class AcBrImpMesh2d.
//
// This class defines the functions that are pertinent to a two-
// dimensional (i.e., "faceted") mesh of either an entire solid or
// an individual surface.
//
// A 2d mesh is a mesh that maps to a 3d face set, and thus has
// associated geometry. The geometry, however, is stored at the
// individual elements and nodes, as are the mappings back to the
// original brep topology. A 2d mesh can also be thought of as a
// wire network, and its element set can be used to define a surface
// wireframe model. Non-manifold edges and vertices from the 3d face
// set are ignored and are not mapped to the mesh. Degenerate elements
// are discarded, along with their unique nodes.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To set an
// AcBrMesh2d object, call generate() using a valid mesh filter. To
// facet an entire solid, call generate() using a filter whose entity
// key is an AcBrBrep. To facet an individual surface, call generate()
// using a filter whose entity key is an AcBrFace.
//
// Deleting this object also deletes the elements and nodes that it
// generated, so the user should archive their own copies of the
// elements and nodes if necessary before deleting this mesh object.
//
// The set() mesh data initialiser is for internal use only. It is used
// to set this mesh's internal data using an unexported type.
//
// The get() mesh data query is for internal use only. It retrieves
// this mesh's internal data using an unexported type.
//
// The generate() mesh generation function is used to set the mesh
// using a filter (such as a face with associated mesh controls). This
// initialises a mesh object instantiated with the default constructor, 
// and deletes any existing elements and nodes. It also indirectly
// sets the topology object associated with the mesh. This function is
// interruptible using CTRL-C. If the mesh filter contains a null or 
// invalid topology key, or if the associated AutoCAD object has been 
// modified since the mesh filter was last set, Acad::eInvalidInput is 
// returned. If the topology key is of lower dimension than this 2d 
// mesh object (i.e., a 1d edge or a 0d vertex), eUnsuitableTopology 
// is returned. If the mesh generation is interrupted using CTRL-C,
// Acad::eUserBreak is returned. If the mesh fails to generate 
// elements on a specific face due to improperly formed topology 
// (such as the presence of an interior loop with no complementary 
// exterior loop), eDegenerateTopology is returned. If the mesh fails 
// to generate any elements, Acad::eAmbiguousOutput is returned. If 
// the mesh generates one or more degenerate elements (i.e., with
// fewer than three nodes - the minimum for a 2d element), Acad::
// eDegenerateGeometry is returned.
//
// NOTE: The following class is included herein because it will only
// require a single line of code to typedef it to a template in the
// next release. It's not a good idea to create temporary header files.
//
// The AcBrMesh2dFilter class is the interface class for 2d mesh filters.
// All the functionality supported by this class is implemented herein.
// This class will be replaced by a templated version from the STL's
// multimap associative container in a future release.
//
// This class defines the mapping between topology objects and 2d mesh
// controls that are used as filters on 2d mesh generation. Its main
// purpose is to provide a flexible, standalone type for the argument
// to the AcBrMesh2d::generate() mesh generation function.
//
// The insert() function associates a specific 2d mesh control with a
// topology object, and adds it to the multimap. For now, only a single
// entry is supported; repeated calls will overwrite previous values. The
// proper syntax is to supply the function with the return value of a call
// to make_pair(). This latter function comes from the STL, but is emulated
// for now in a local version. To establish default settings, use a null
// entity pointer with the desired default 2d mesh controls (not supported
// until the full STL multimap capabilities are implemented, as there must
// be a target object for the mesh and only one filter entry is currently
// suppported in this bastardised version of the STL multimap container).


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brmesh.h"
#include "brm2dctl.h"


// forward class declarations
class AcBrEntity;
class AcBrMesh2dControl;
class AcBrMesh;
class AcBrMesh2dData;


// these will come from STL in next release
static AcBrMesh2dControl AcBrMesh2dControlDefault;

struct pair {
    AcBrEntity*			first;
    AcBrMesh2dControl	second;
    pair() : first((AcBrEntity*)NULL), second(AcBrMesh2dControlDefault) {}
	pair(const AcBrEntity*& a, const AcBrMesh2dControl& b) : first((AcBrEntity*)a), second(b) {}
};

inline pair
make_pair(const AcBrEntity*& entity, const AcBrMesh2dControl& control)
{ return pair(entity, control); }


// these are temporary typedefs until STL is available
typedef pair value_type;
typedef void iterator;


class AcBrMesh2dFilter
{
public:
	AcBrMesh2dFilter();
    ~AcBrMesh2dFilter();
    
    // Insert
    iterator			insert			(const value_type& x);

private:
    // this is all temporary until STL is available
	friend class AcBrImpMesh2d;

    AcBrMesh2dFilter(const AcBrMesh2dFilter& src);
    AcBrMesh2dFilter&	operator =      (const AcBrMesh2dFilter& src);

    value_type			mKeyValuePair;
};


class AcBrMesh2d : public AcBrMesh
{
public:
    ACRX_DECLARE_MEMBERS(AcBrMesh2d);
    AcBrMesh2d();
    AcBrMesh2d(const AcBrMesh2d& src);
    ~AcBrMesh2d();
    
    // Assignment operator
    AcBrMesh2d&         operator =      (const AcBrMesh2d& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   set				(AcBrMesh2dData* mesh2d);
	AcBr::ErrorStatus	get				(AcBrMesh2dData*& mesh2d) const;

    // Mesh generation
    AcBr::ErrorStatus   generate		(const AcBrMesh2dFilter& meshFilter);
};


// Inline methods

inline
AcBrMesh2dFilter::AcBrMesh2dFilter() {}

inline
AcBrMesh2dFilter::~AcBrMesh2dFilter() {}

inline iterator
AcBrMesh2dFilter::insert(const value_type& x)
{ mKeyValuePair.first = x.first; mKeyValuePair.second = x.second; }


#endif
