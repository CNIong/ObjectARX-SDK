#ifndef AC_BRMENT_H
#define AC_BRMENT_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrMeshEntity class is the interface base class for mesh
// objects and subobjects. All the functionality supported by
// this class is implemented by the class AcBrImpMeshEntity.
//
// This class defines the functions that are common to all mesh
// objects and subobjects, and cannot be instantiated as it has no
// meaning on its own. It is derived from AcRxObject in order to
// provide full service run-time type-checking for all derived
// mesh classes.
//
// The AcRxObject::isEqualTo() equivalence function is redefined to
// check content equality between two mesh objects. kTrue is returned
// if this object is valid and has been equated to another valid mesh
// object of the same subclass. Equivalence is defined as having the
// same associated topological entity and the same internal data.
//
// The isNull() validator function tests whether this mesh object
// has been set to anything meaningful. kTrue is returned if it is
// uninitialised; kFalse is returned if it is valid/initialised.
//
// The getEntityAssociated() associated topology query returns the
// dimensionally lowest topology object associated with this mesh
// object. For a 2d mesh, it returns a face, shell or brep. For a 2d
// element, it returns a face. For a node, it returns a vertex, edge
// or face. The topology object is passed as a null AcBrEntity base
// class reference pointer for getEntityAssociated() to instantiate.
// If this mesh object is uninitialised, eUninitialisedObject is
// returned. If the AutoCAD object associated with the topology
// object has been modified since this mesh object's internal
// data was last set, eBrepChanged is returned. If the associated
// topology object is not the right type for this mesh object,
// Acad::eWrongSubentityType is returned. If the AcBrEntity
// allocation comes back null, Acad::eOutOfMemory is returned.
// If the associated topology object fails to map to a valid
// subentity ID, Acad::eNotInDatabase is returned. In the event
// of an error, the topology reference pointer is unchanged and
// thus likely points to a null object.
//
// The setValidationLevel() prioritisation function sets the validation
// level to be used in all data queries that require access to the
// associated AutoCAD object. In general, this means any function that
// accesses the brep topology. If set to kNoValidation, eBrepChanged
// will no longer be returned by functions called on this mesh object.
// Any query that returns a newly instantiated AcBr object uses this
// mesh object's validation level to initialise the new object. Note
// that a request to generate a new mesh must still validate the brep
// first (cf. AcBrMesh2d::generate()), as it is not possible to compute
// a mesh on an out-of-scope model.
//
// The getValidationLevel() prioritisation query returns a dedicated
// ValidationType enum corresponding to the validation level currrently
// being used by this mesh object.
//
// The brepChanged() status query returns a simple Boolean indicating
// whether the associated AutoCAD object has changed since this mesh
// object was last set. kFalse is returned if it has not changed or
// if the associated object is non-database resident; kTrue is returned
// either if it has changed or if it is not possible to determine
// whether it has changed (which generally indicates that the AutoCAD
// object has gone out of scope due to deletion).


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"


// forward class declarations
class AcBrEntity;
class AcBrImpMeshEntity;


class AcBrMeshEntity : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcBrMeshEntity);
    virtual ~AcBrMeshEntity();

    // Equivalence                    
    Adesk::Boolean      isEqualTo       (const AcRxObject* other) const;
    
    // Queries & Initialisers
    Adesk::Boolean      isNull          () const;
    
	// Topology
	AcBr::ErrorStatus   getEntityAssociated(AcBrEntity*& entity) const;

	// Validation
	AcBr::ErrorStatus	setValidationLevel(const AcBr::ValidationLevel& = *(AcBr::ValidationLevel*)NULL);
	AcBr::ErrorStatus	getValidationLevel(AcBr::ValidationLevel& validationLevel) const;
	Adesk::Boolean		brepChanged		() const;

protected:
    AcBrMeshEntity();
    AcBrMeshEntity(const AcBrMeshEntity&);
    AcBrMeshEntity&     operator =      (const AcBrMeshEntity&);

    AcBrImpMeshEntity*	mpImp;
};


#endif

