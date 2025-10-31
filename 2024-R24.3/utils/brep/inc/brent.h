#ifndef AC_BRENT_H
#define AC_BRENT_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrEntity class is the interface base class for topology
// objects. All the functionality supported by this class is
// implemented by the class AcBrImpEntity.
//
// This class defines the functions that are common to all topology
// objects, and cannot be instantiated as it has no meaning on 
// its own. It is derived from AcRxObject in order to provide full
// service run-time type-checking for all derived topology classes.
//
// The AcRxObject::isEqualTo() equivalence function is redefined to
// check content equality between two topology objects. kTrue is
// returned if this object is valid and has been equated to another
// valid topology object of the same subclass. Equivalence is defined
// as having the same subentity path and the same brep revision number.
//
// The isNull() validator function tests whether this topology object
// has been set to anything meaningful. kTrue is returned if it is
// uninitialised; kFalse is returned if it is valid/initialised.
//
// The setSubentPath() and getSubentPath() topology data initialiser
// and query functions are deprecated in favour of set() and get().
//
// The getBoundBlock() geometric bounds query returns the model space
// bounding block for this topology object. The bounding block is
// returned as an AcGeBoundBlock3d, with the entire chain of transforms
// from the subentity path applied. The bounding block is instantiated
// by the caller and passed by reference for getBoundBlock() to set. If
// this topology object is uninitialised, eUninitialisedObject is returned. 
// If the associated AutoCAD object has been modified since the subentity
// path was last set, eBrepChanged is returned. If the bounding block is
// empty or unbounded, Acad::eAmbiguousOutput is returned. In the event
// of an error, the bounding block reference argument's value is unchanged.
//
// The getPointContainment() set-membership classification determines
// whether a point lies inside, outside or on the geometric bounds of
// this topology object. If the point lies outside, AcGe::kOutside is
// returned along with a null container object. If inside, AcGe::kInside
// is returned along with a copy of this topology object. If the point
// lies on the geometric bounds, AcGe::kOnBoundary is returned along with
// the lowest-level topology object that contains the point (e.g., if
// the point lies along an edge boundary of a face, the edge is returned).
// The container object is passed as a null AcBrEntity base class reference
// pointer for getPointContainment() to instantiate. In order for the
// point to be in the same evaluation space as this topology object, the
// entire inverted chain of transforms from the subentity path is applied
// to the point before checking containment. If this topology object is
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the subentity path was last set,
// eBrepChanged is returned. If the containment cannot be determined,
// Acad::eAmbiguousOutput is returned. If the AcBrEntity allocation comes
// back null, Acad::eOutOfMemory is returned. In the event of an error,
// the containment reference argument's value is unchanged and is thus
// meaningless, and the container reference pointer is unchanged and thus
// likely points to a null object.
//
// The getLineContainment() set-membership classification determines
// whether a line lies inside, outside or on the geometric bounds of this
// topology object. If the line lies entirely outside, a null hit array
// is returned (with numHitsFound = 0). If the line is a finite segment
// that lies entirely inside or on the geometric bounds, the end points
// of the line are returned as the hits (with numHitsFound = 2). All other
// cases represent line-solid intersections, and generate hit arrays that
// segment the line at each intersection point. The line may be either a
// line segment, a ray or an infinite line, cast to AcGeLinearEnt3d. The   
// numHitsWanted argument should be set to zero to find all hits, set to
// one to find just the first intersection, or to some other quantisation.
// The hit array is passed as a null AcBrHit reference pointer for
// getLineContainment() to instantiate. It is the user's responsibility
// to delete[] the returned array of hits. In order for the line to be in
// the same evaluation space as this topology object, the entire inverted
// chain of transforms from the subentity path is applied to the line
// before checking containment. If this topology object is uninitialised,
// eUninitialisedObject is returned. If the associated AutoCAD object has
// been modified since the subentity path was last set, eBrepChanged is
// returned. If the containment cannot be determined, Acad::eAmbiguousOutput 
// is returned. If the AcBrHit array allocation comes back null, Acad::
// eOutOfMemory is returned. In the event of an error, the hit array
// reference pointer is unchanged and thus likely points to a null array,
// and the number of hits found is zero.
//
// The getBrep() owner query returns the brep that is at the top of this
// topology object's adjacency hierarchy. The brep object is instantiated
// by the caller and passed by reference for getBrep() to set. If this
// topology object is uninitialised, eUninitialisedObject is returned. 
// If the associated AutoCAD object has been modified since the subentity
// path was last set, eBrepChanged is returned. If the brep is missing,
// Acad::eNotInDatabase is returned. In the event of an error, the brep
// reference object is unchanged and is thus likely to be uninitialised.
//
// The setValidationLevel() prioritisation function sets the validation
// level to be used in all data queries that require access to the
// associated AutoCAD object. In general, this means any function that
// accesses the brep topology. If set to kNoValidation, eBrepChanged
// will no longer be returned by functions called on this topology object.
// Any query that returns a newly instantiated AcBr object uses this
// topology object's validation level to initialise the new object.
//
// The getValidationLevel() prioritisation query returns a dedicated
// ValidationType enum corresponding to the validation level currrently
// being used by this topology object.
//
// The brepChanged() status query returns a simple Boolean indicating
// whether the associated AutoCAD object has changed since this topology
// object was last set. kFalse is returned if it has not changed or
// if the associated object is non-database resident; kTrue is returned
// either if it has changed or if it is not possible to determine
// whether it has changed (which generally indicates that the AutoCAD
// object has gone out of scope due to deletion).
//
// The set() topology data initialiser is used to set this topology
// object's internal data using a subentity path in AutoCAD. This
// initialises an object instantiated with the default constructor, and
// resets the criteria for the eBrepChanged error as well as setting
// the validation level to AcBr::kFullValidation. If the subentity path
// is empty, or the object ID array is empty or contains any null entries,
// Acad::eNullObjectId is returned. If the subentity is not the right
// type for this topology object, Acad::eWrongSubentityType is returned.
// If the associated AutoCAD object is not an AcDb3dSolid, AcDbSurface, AcDbRegion,
// AcDbBody or derived type, Acad::eWrongObjectType is returned. If the 
// subentity ID contains a null index or fails to map to a valid subentity,
// Acad::eInvalidIndex is returned. In the cases of AcBrComplex, AcBrShell
// and AcBrLoop, this function is disabled and returns Acad::eNotApplicable
// since complexes, shells and loops do not have subentity representations 
// in AutoCAD. In the special case of AcBrEdge, if the edge is free or
// otherwise unembedded (such as a wire edge), eUnsuitableTopology is
// returned. Singularities map to edges in AutoCAD and thus can be used 
// to initialise an AcBrEdge for the express purpose of querying the
// vertex, but cannot be queried for curve geometry or used to set a 
// loop edge traverser. In the event of an error, this topology object's 
// internal data is unchanged.
//
// The get() topology data query retrieves this topology object's internal
// data using a subentity path in AutoCAD. If this topology object is
// uninitialised, eUninitialisedObject is returned. If there is no valid
// AutoCAD object associated with this topology object, Acad::eNotInDatabase
// is returned. In the cases of AcBrComplex, AcBrShell and AcBrLoop, this 
// function is disabled and returns Acad::eNotApplicable since complexes,
// shells and loops do not have subentity representations in AutoCAD. 
//
// The set() topology data initialiser(2) is for internal use only. It is
// used to set this topology object's internal data using an unexported type.
//
// The get() topology data query(2) is for internal use only. It retrieves
// this topology object's internal data using an unexported type.
//
// The getMassProps() geometric properties query returns the mass 
// properties contributed by this topology object. The mass properties
// are returned as an AcBrMassProps, with the entire chain of transforms 
// from the subentity path applied where appropriate. The density (if 
// supplied) is used to scale the mass properties; otherwise a uniform
// unity density is assumed. The achieved tolerance (if supplied),
// relative to the volume, is returned as a double. The mass properties 
// structure is instantiated by the caller and passed by reference for 
// getMassProps() to set. If this topology object is uninitialised, 
// eUninitialisedObject is returned. If the associated AutoCAD object 
// has been modified since the subentity path was last set, eBrepChanged 
// is returned. In the cases of AcBrFace, AcBrLoop, AcBrEdge and 
// AcBrVertex, this function is disabled and returns Acad::
// eNotApplicable since faces, loops, edges and vertices have no 
// volume and therefore have no mass properties. In the event of an
// error, the mass properties reference argument's value is unchanged.
//
// The getVolume() 3d amount query query returns the volume of this 
// topology object as a double, with the maximum scale factor applied 
// from the nested transforms. The achieved relative tolerance (if
// supplied) is returned as a double. If this topology object is 
// uninitialised, eUninitialisedObject is returned. If the associated
// AutoCAD object has been modified since the subentity path was last 
// set, eBrepChanged is returned. In the cases of AcBrFace, AcBrLoop, 
// AcBrEdge and AcBrVertex, this function is disabled and returns Acad::
// eNotApplicable since faces, loops, edges and vertices have no volume. 
// In the event of an error, the volume reference argument's value is 
// unchanged.
//
// The getSurfaceArea() 2d amount query returns the surface area of this 
// topology object as a double, with the maximum scale factor applied 
// from the nested transforms. The achieved relative tolerance (if
// supplied) is returned as a double. If this topology object is 
// uninitialised, eUninitialisedObject is returned. If the associated 
// AutoCAD object has been modified since the subentity path was last 
// set, eBrepChanged is returned. In the cases of AcBrLoop, AcBrEdge 
// and AcBrVertex, this function is disabled and returns Acad::
// eNotApplicable since loops, edges and vertices have no area. In the
// event of an error, the area reference argument's value is unchanged.
//
// The getPerimeterLength() 1d amount query returns the perimeter length
// of this topology object as a double, with the maximum scale factor 
// applied from the nested transforms. The achieved relative tolerance 
// (if supplied) is returned as a double. If this topology object is 
// uninitialised, eUninitialisedObject is returned. If the associated 
// AutoCAD object has been modified since the subentity path was last
// set, eBrepChanged is returned. In the case of AcBrVertex, this 
// function is disabled and returns Acad::eNotApplicable since vertices 
// have no length. In the event of an error, the length reference 
// argument's value is unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "gegbl.h"
#include "brgbl.h"
#include "brprops.h"


// forward class declarations
class AcDbFullSubentPath;
class AcGeBoundBlock3d;
class AcGePoint3d;
class AcGeLinearEnt3d;
class AcBrHit;
class AcBrBrep;
class AcBrImpEntity;
class AcBrBrepData;


class AcBrEntity : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcBrEntity);
    virtual ~AcBrEntity();
    
    // Equivalence                    
    Adesk::Boolean      isEqualTo       (const AcRxObject* other) const;
    
    // Queries & Initialisers
    Adesk::Boolean      isNull          () const;
    AcBr::ErrorStatus   setSubentPath   (AcDbFullSubentPath& subpath);
    AcBr::ErrorStatus   getSubentPath   (AcDbFullSubentPath& subPath) const;
	
	Adesk::Boolean		checkEntity		() const;
	void*				getEntity		() const;
	AcBr::ErrorStatus	setEntity		(void*	pData,
										 AcDbFullSubentPath& subPath = *(AcDbFullSubentPath*)NULL);

    // Geometric bounds (i.e., model space bounding box)
    AcBr::ErrorStatus   getBoundBlock   (AcGeBoundBlock3d& block) const;

    // Set-Membership Classification
    AcBr::ErrorStatus   getPointContainment(const AcGePoint3d& point,
                                            AcGe::PointContainment& containment,
                                            AcBrEntity*& container) const;

    AcBr::ErrorStatus   getLineContainment(const AcGeLinearEnt3d& line,
                                           const Adesk::UInt32& numHitsWanted,
                                           Adesk::UInt32&       numHitsFound,
                                           AcBrHit*&            hits) const;

    // Upward link to brep owner of subentity (1::1)
    AcBr::ErrorStatus   getBrep         (AcBrBrep& brep) const;

	// Validation
	AcBr::ErrorStatus	setValidationLevel(const AcBr::ValidationLevel& level = *(AcBr::ValidationLevel*)NULL);
	AcBr::ErrorStatus	getValidationLevel(AcBr::ValidationLevel& level) const;
	Adesk::Boolean		brepChanged		() const;

    // Queries & Initialisers
    AcBr::ErrorStatus   set				(const AcDbFullSubentPath& path);
    AcBr::ErrorStatus   get				(AcDbFullSubentPath& path) const;
	AcBr::ErrorStatus	set				(AcBrBrepData* data);
	AcBr::ErrorStatus	get				(AcBrBrepData*& data) const;

	// Geometric properties
	AcBr::ErrorStatus	getMassProps	(AcBrMassProps& massProps,
		                                 const double&  density     = *(double*)NULL,
		                                 const double&  tolRequired = *(double*)NULL,
		                                 double&        tolAchieved = *(double*)NULL) const;
	AcBr::ErrorStatus	getVolume		(double&       volume,
		                                 const double& tolRequired = *(double*)NULL,
		                                 double&       tolAchieved = *(double*)NULL) const;
	AcBr::ErrorStatus	getSurfaceArea	(double&       area,
		                                 const double& tolRequired = *(double*)NULL,
		                                 double&       tolAchieved = *(double*)NULL) const;
	AcBr::ErrorStatus	getPerimeterLength(double&       length,
		                                   const double& tolRequired = *(double*)NULL,
		                                   double&       tolAchieved = *(double*)NULL) const;

protected:
    AcBrEntity();
    AcBrEntity(const AcBrEntity& src);
    AcBrEntity&         operator =      (const AcBrEntity& src);

    AcBrImpEntity*      mpImp;
};


#endif

