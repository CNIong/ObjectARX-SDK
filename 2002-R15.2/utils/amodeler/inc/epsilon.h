#ifndef AMODELER_INC_EPSILON_H
#define AMODELER_INC_EPSILON_H


///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1996 by Autodesk, Inc.
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

AMODELER_NAMESPACE_BEGIN


// Don't use the following global variables directly, use the inline functions
// instead. We have to keep these variables in the header file to be able to
// inline the access functions.
//
DllImpExp extern double       gEpsAbs;
DllImpExp extern double       gEpsAbsSqrd;
DllImpExp extern const double gEpsNor;
DllImpExp extern const double gEpsNorSqrd;


inline double epsAbs    () { return gEpsAbs;     }
inline double epsAbsSqrd() { return gEpsAbsSqrd; }

inline double epsNor    () { return gEpsNor;     }
inline double epsNorSqrd() { return gEpsNorSqrd; }

DllImpExp extern void setEpsAbs(double eps);


AMODELER_NAMESPACE_END
#endif
