///////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form. 
//
// DESCRIPTION:
//
// Definition of type 'Flag' which is an 'unsigned int', used for storing
// flags (on/off values).  
//
// Flags are used extensively throughout the modeler. Each topological entity 
// has (by deriving from the class Entity) a set of flags it is using to mark
// some conditions. For example, a Body has a flag IPBF indicating whether
// the bounding interval (box) is evaluated or not.
//
// Flags starting from 0 up are called global flags and are used to mark entity
// properties which are part of the state of the entity. The above mentioned
// IPBF flag is an example of a global flag. 
//
// Flags starting from 31 down are called local flags. They are used by some
// operations (notably by Booleans and hidden-line removal) to store temporary
// information. 
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_FLAGS_H
#define AMODELER_INC_FLAGS_H


AMODELER_NAMESPACE_BEGIN


typedef unsigned Flag;


Flag inline FLAG(unsigned int i) { return (1 << i); }


// Flag set 'a' is subset of flag set 'b'
//
inline int isSubset(Flag a, Flag b) { return ((a & b) == a); }


enum OnOff { kOff, kOn };


AMODELER_NAMESPACE_END
#endif

