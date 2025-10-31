///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
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

