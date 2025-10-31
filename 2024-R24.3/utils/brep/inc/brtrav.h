#ifndef AC_BRTRAV_H
#define AC_BRTRAV_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrTraverser class is the interface base class for traversers.
// All the functionality supported by this class is implemented by the
// class AcBrImpTraverser.
//
// This class defines the functions that are common to all traversers,
// and cannot be instantiated as it has no meaning on its own. It is
// derived from AcRxObject in order to provide full service run-time
// type-checking for all derived topology traverser classes.
//
// The AcRxObject::isEqualTo() equivalence function is redefined to
// check content equality between two traverser objects. kTrue is
// returned if this object is valid and has been equated to another
// valid traverser object of the same subclass. Equivalence is defined
// as having the same list owner and list position.
//
// The isNull() validator function tests whether this traverser object
// has been set to anything meaningful. kTrue is returned if it is
// uninitialised; kFalse is returned if it is valid/initialised.
//
// The done() status query returns kTrue if the entire list has
// been traversed (using the next() function); as determined by the
// list owner and the most recently set starting position. kTrue is
// also returned if this traverser object is uninitialised, or if
// the AutoCAD object has been modified since this traverser object
// was last set (in order to prevent infinite loops in user code).
//
// The next() incrementor function adjusts the traverser to point to
// the next object in the list. All lists are treated internally as
// persistent circular, ordered lists for purposes of setting the
// starting position, but are then exported as persistent linear,
// ordered lists -- that is, once every object in the list has been
// traversed, this function has no further effect until restart() is
// called. Every attempt is made to traverse each object only once,
// but certain non-manifold conditions may pre-empt this goal or even
// render it inappropriate (such as the case of loop edge traverser).
// If this traverser object is uninitialised, eUninitialisedObject is
// returned. If the associated AutoCAD object has been modified since
// this traverser was last set, eBrepChanged is returned.
//
// The restart() reset function adjusts the traverser to point to the
// first object in the list, as determined by the most recent call to
// the set starting position function in the derived traverser class.
// If this traverser object is uninitialised, eUninitialisedObject is
// returned. If the associated AutoCAD object has been modified since
// this traverser was last set, eBrepChanged is returned.
//
// The setValidationLevel() prioritisation function sets the validation
// level to be used in all data queries that require access to the
// associated AutoCAD object. In general, this means any function that
// accesses the brep topology. If set to kNoValidation, eBrepChanged
// will no longer be returned by functions called on this traverser
// object. Any query that returns a newly instantiated AcBr object
// uses this traverser object's validation level to initialise the
// new object. Additionally, any function that sets the traverser
// list owner or list position also sets this traverser object's
// validation level to match that of the function argument.
//
// The getValidationLevel() prioritisation query returns a dedicated
// ValidationType enum corresponding to the validation level currrently
// being used by this traverser object.
//
// The brepChanged() status query returns a simple Boolean indicating
// whether the associated AutoCAD object has changed since this traverser
// object was last set. kFalse is returned if it has not changed or if
// the associated object is non-database resident; kTrue is returned
// either if it has changed or if it is not possible to determine
// whether it has changed (which generally indicates that the AutoCAD
// object has gone out of scope due to deletion).
//
// The set() traverser data initialiser is no longer supported.
//
// The get() traverser data query is for internal use only. It retrieves 
// this traverser object's internal data using an unexported type.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"


// forward class declarations
class AcBrImpTraverser;
class AcBrTraverserData;


class AcBrTraverser : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcBrTraverser);
    virtual ~AcBrTraverser();
    
    // Equivalence                    
    Adesk::Boolean      isEqualTo       (const AcRxObject* other) const;
                        
    // Queries & Initialisers
    Adesk::Boolean      isNull          () const;

    // Topological traversal
    Adesk::Boolean      done            () const;
    AcBr::ErrorStatus   next            ();
    AcBr::ErrorStatus   restart         ();

	// Validation
	AcBr::ErrorStatus	setValidationLevel(const AcBr::ValidationLevel& = *(AcBr::ValidationLevel*)NULL);
	AcBr::ErrorStatus	getValidationLevel(AcBr::ValidationLevel& validationLevel) const;
	Adesk::Boolean		brepChanged		() const;

    // Queries & Initialisers
	// (Note: obsolete function)
	AcBr::ErrorStatus	set				(AcBrTraverserData* traverserData);
	AcBr::ErrorStatus	get				(AcBrTraverserData*& traverserData) const;

protected:
    AcBrTraverser();
    AcBrTraverser(const AcBrTraverser& src);
    AcBrTraverser&      operator =      (const AcBrTraverser& src);

    AcBrImpTraverser*   mpImp;
};


#endif

