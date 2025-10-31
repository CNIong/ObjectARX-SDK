#ifndef AC_BRGBLABB_H
#define AC_BRGBLABB_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// This file contains abbreviated definitions for the Autodesk Boundary
// Representation library, as defined in brgbl.h.
//
// Using the fully qualified names from the "AcBr" struct can be
// cumbersome. If there are no global name conflicts use the following
// synonyms for convenience.
//
// Note:  All interface descriptions must use fully qualified names.
//        That is, header files MUST NOT include this file and MUST
//        NOT use these abbreviations.
//
// Note:  If any of the following abbreviations cause conflicts and
//        this file cannot be included, then the acceptable abbreviations
//        (those that do not cause conflicts) will have to be manually
//        introduced, or another abbreviation header file will have to
//        be created containing only the acceptable abbreviations.
//
// Note:  When this file is included in a source file, it MUST BE
//        included AFTER all other include files (except possibly
//        other abbreviation include files).
//        For example:
//            #include "adesk.h"
//            #include "brgbl.h"
//            #include "foo.h"
//            #include "bar.h"
//            #include "adeskabb.h"
//            #include "brgblabb.h" // <- Must be last!
//
// Note:  This abbreviation file cannot coexist with acdbabb.h or
//        any other abbreviation file that abbreviates error codes.


#include "acadstrc.h"
#include "brgbl.h"


typedef AcBr::ErrorStatus		AcBrErrorStatus;
typedef AcBr::Relation			AcBrRelation;
typedef AcBr::Element2dShape	AcBrElement2dShape;
typedef AcBr::LoopType			AcBrLoopType;
typedef AcBr::ValidationLevel	AcBrValidationLevel;
typedef AcBr::ShellType			AcBrShellType;


const AcBrErrorStatus	eOk					= AcBr::eOk;
const AcBrErrorStatus	eNotImplementedYet	= AcBr::eNotImplementedYet;
const AcBrErrorStatus	eNotApplicable		= AcBr::eNotApplicable;
const AcBrErrorStatus	eInvalidInput		= AcBr::eInvalidInput;
const AcBrErrorStatus	eOutOfMemory		= AcBr::eOutOfMemory;
const AcBrErrorStatus	eNullObjectPointer	= AcBr::eNullObjectPointer;
const AcBrErrorStatus	eWrongObjectType	= AcBr::eWrongObjectType;
const AcBrErrorStatus	eWrongSubentityType	= AcBr::eWrongSubentityType;
const AcBrErrorStatus	eBrepChanged		= AcBr::eBrepChanged;
const AcBrErrorStatus	eNullObjectId		= AcBr::eNullObjectId;
const AcBrErrorStatus	eNullSubentityId	= AcBr::eNullSubentityId;
const AcBrErrorStatus	eObjectIdMismatch	= AcBr::eObjectIdMismatch;
const AcBrErrorStatus	eTopologyMismatch	= AcBr::eTopologyMismatch;
const AcBrErrorStatus	eUnsuitableTopology	= AcBr::eUnsuitableTopology;
const AcBrErrorStatus	eUnsuitableGeometry	= AcBr::eUnsuitableGeometry;
const AcBrErrorStatus	eMissingGeometry	= AcBr::eMissingGeometry;
const AcBrErrorStatus	eMissingSubentity	= AcBr::eMissingSubentity;
const AcBrErrorStatus	eInvalidObject		= AcBr::eInvalidObject;
const AcBrErrorStatus	eAmbiguousOutput	= AcBr::eAmbiguousOutput;
const AcBrErrorStatus	eDegenerateTopology	= AcBr::eDegenerateTopology;
const AcBrErrorStatus	eUninitialisedObject = AcBr::eUninitialisedObject;


#endif
