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
// Epsilon related variables and functions.
//
// The modeler recognizes two epsilons:
//
//  - Absolute   epsilon, used for comparing distances. 
//  - Normalized epsilon, used for comparing values normalized to 1.
//
// The values of the epsilon variables can be accessed via inline functions:
//
//   epsAbs()
//   epsAbsSqrd()   ... squared
//
//   epsNor()
//   epsNorSqrd()   ... squared
//
// The normalized epsilon is not supposed to be changed by the user. To change
// the value of the absolute epsilon, use setEpsAbs() function.
//
// The default value of epsAbs() is 1e-8 which is appropriate for models of the
// size in the interval 0.1 to 100. If your models are much larger or much
// smaller, change the value of epsAbs() by calling setEpsAbs().
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_EPSILON_H
#define AMODELER_INC_EPSILON_H


AMODELER_NAMESPACE_BEGIN

class Interval3d;

// Don't use the following global variables directly, use the inline functions
// instead. We have to keep these variables in the header file to be able to
// inline the access functions.
//
DllImpExp extern double gEpsAbs;
DllImpExp extern double gEpsAbsSqrd;
DllImpExp extern double gEpsNor;     
DllImpExp extern double gEpsNorSqrd; 


inline double epsAbs    () { return gEpsAbs;     }
inline double epsAbsSqrd() { return gEpsAbsSqrd; }

inline double epsNor    () { return gEpsNor;     }
inline double epsNorSqrd() { return gEpsNorSqrd; }

DllImpExp extern void setEpsAbs(double eps);
DllImpExp extern void setEpsNor(double eps); // Should not be called by end users

// Potentially grows the value of the global epsAbs so that it is also 
// appropriate for the given object. It only increates the value of epsAbs, 
// if needed, it never decreases it, thus maintaining the largest epsAbs that 
// is large enough for all objects.
//
DllImpExp extern void adjustEpsAbsByObject(const Interval3d& objectInterval);

// Sets the maximum allowed value of epsAbs. Any larger values will be reduced 
// to maxEpsAbs. If maxEpsAbs is 0.0, no maximum is imposed. This limit has
// been introduced mainly to make sure adjustEpsAbsByObject() does not increase
// epsAbs beyond some reasonable value.
//
DllImpExp extern void setMaxEpsAbs(double maxEpsAbs);


// Sets a global variable that is used to control how the Boolean operation
// algorithm handles intersections of faces that are almost coplanar
//
DllImpExp extern bool setAdjustEpsAbsInFlatIntersections(bool);


AMODELER_NAMESPACE_END
#endif
