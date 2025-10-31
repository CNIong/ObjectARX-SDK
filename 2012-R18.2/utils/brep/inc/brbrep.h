//
#ifndef AC_BRBREP_H
#define AC_BRBREP_H 1
// (C) Copyright 1995-2010 by Autodesk, Inc.
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
// The AcBrBrep class is the interface class for the brep portion
// of an AutoCAD database entity. All the functionality supported
// by this class is implemented by the class AcBrImpBrep.
//
// This class defines the functions that are pertinent to the highest
// level of a brep toplogy adjacency hierarchy, and thus serves as
// a mapping between an AutoCAD solid, surface, region or body entity and
// AcBr. It is also used to set the brep owner of a face list in
// AcBrBrepFaceTraverser.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To set an
// AcBrBrep, call set() with a subentity path that contains the object
// ID for an AutoCAD solid, surface, region or body along with its chain of
// transforms (using nested AcDbBlockReferences) and kNullSubentId.
//
// The getPointRelationToBrep() and getCurveRelationToBrep()
// set-membership classifications are deprecated in favour of
// getPointContainment() and getLineContainment().
//
// The set() initialiser is used to set this object to a specific AcDb*
// object (i.e., solid, surface, region or body) that is not database-active.
// This initialises an object instantiated with the default constructor.
// If the entity is not an AcDb3dSolid, AcDbSurface, AcDbRegion or AcDbBody,
// Acad::eWrongObjectType is returned. In the event of an error,
// this object's data is unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcDbEntity;
class AcDb3dSolid;
class AcDbSurface;
class AcGePoint3d;
class AcGeCurve3d;


class AcBrBrep : public AcBrEntity
{
public:
	using AcBrEntity::set;
	using AcBrEntity::get;


    ACRX_DECLARE_MEMBERS(AcBrBrep);
    AcBrBrep();
    AcBrBrep(const AcBrBrep& src);
    ~AcBrBrep();

    // Assignment operator
    AcBrBrep&           operator =      (const AcBrBrep& src);

	// Set-Membership Classification (Note: deprecated functions)
    AcBr::ErrorStatus   getPointRelationToBrep(const AcGePoint3d& point, AcBr::Relation& relation) const;
    AcBr::ErrorStatus   getCurveRelationToBrep(const AcGeCurve3d& curve, AcBr::Relation& relation) const;

    // Queries & Initialisers
	AcBr::ErrorStatus	set				(const AcDbEntity& entity);
	AcBr::ErrorStatus	get				(AcDb3dSolid*& pSolid) const;
	AcBr::ErrorStatus	get				(AcDbSurface*& pSurface) const;
};


#endif

