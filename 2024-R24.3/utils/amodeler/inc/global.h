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
// The basic include file to be included into any modeler file. It contains
// some very basic stuff, needed almost everywhere in the modeler.
//
///////////////////////////////////////////////////////////////////////////////


#ifndef AMODELER_INC_GLOBAL_H
#define AMODELER_INC_GLOBAL_H


// The same header files are used both to build the DLL and to use the DLL
//
#if !defined(LIB_VERSION_OF_AMODELER) && !defined(unix)
#ifdef BUILD_AECMODELER
#define DllImpExp __declspec(dllexport)
#else
#define DllImpExp __declspec(dllimport)
#endif
#else
#define DllImpExp
#endif



// If ve are using VC++4.0 compiler or newer, we define namespace AModeler 
// to contain all AModeler symbols. VC++2.2 compiler and older versions do 
// not support namespaces.
//
#if defined(_ADESK_MAC_) || _MSC_VER >= 1000
#define AMODELER_NAMESPACE         AModeler
#define AMODELER_NAMESPACE_BEGIN   namespace AModeler {
#define AMODELER_NAMESPACE_END     }
#else
#define AMODELER_NAMESPACE         
#define AMODELER_NAMESPACE_BEGIN  
#define AMODELER_NAMESPACE_END
#endif

AMODELER_NAMESPACE_BEGIN

// Let us define 'bool' to look the same as the proposed standard C++ 
// data type 'bool'. Try to avoid redefining it if some other header 
// file already defined it.
//
#if _MSC_VER < 1100
#if !defined(true) && !defined(__GNUC__)
typedef int bool;     
const   int true  = 1;
const   int false = 0;
#endif
#endif

AMODELER_NAMESPACE_END


// Include some very frequently used header files so that they do not have
// to be included every time
//
#include <stdio.h>
#include <stdlib.h>
#include "massert.h"   // Our own assert
#include "errcodes.h"
#include "epsilon.h"
#include "flags.h"



AMODELER_NAMESPACE_BEGIN

// The values of the following constants are assigned in global.cpp. Otherwise 
// the VC++4.0 compiler would generate the same initialization code in 
// each file into which "global.h" is included.
//
DllImpExp extern const double kPi;      
DllImpExp extern const double kTwoPi;    
DllImpExp extern const double kHalfPi;

DllImpExp extern const double kMaxReal;  // A very big number, but not too big
DllImpExp extern const double kMinReal;
DllImpExp extern const double kDeg2Rad;  // Degrees --> radians coefficient
DllImpExp extern const double kEpsZero;  // Really a very small value

const int kTooBigInt = 10000000;    // Too big number of anything is 10 million



// We, Pascal people, used to have sqr() function and some other goodies
//
inline double sqr (double a) { return a * a;                      }
inline int    sign(double a) { return a > 0 ? 1 : a < 0 ? -1 : 0; }
inline bool   odd (int    a) { return a & 0x1;                    }

#ifndef _ADESK_MAC_
inline int round(double d)  // Is there is a C function doing this?
{
    return d >= 0 ? (int)(d + 0.5) : (int)(d - 0.5);
}
#endif

#ifdef unix
#define __max(a,b)  ((a) >= (b) ? (a) : (b))
#define __min(a,b)  ((a) <= (b) ? (a) : (b))
#endif


inline int prevIndex(int i, int n) { return i ==   0 ? n-1 : i-1; }
inline int nextIndex(int i, int n) { return i == n-1 ? 0   : i+1; }


// Forward declaration of some commonly used classes so that we do not have to
// forward-declare them in header files every time they are needed.
//
class Point2d;
class Vector2d;
class Point3d;
class Vector3d;
class IntPoint2d;
class IntVector2d;
class IntPoint3d;
class IntVector3d;
class Transf3d;
class Line3d;
class Circle3d;
class Plane;
class Interval1d;
class Interval2d;
class Interval3d;
class IntInterval1d;
class IntInterval2d;
class IntInterval3d;
class Entity;
class Body;
class Face;
class Edge;
class Vertex;
class Surface;
class CylinderSurface;
class ConeSurface;
class SphereSurface;
class TorusSurface;
class Curve;
class CircleCurve;
class PolygonVertexData;
class OutputPolylineCallback;
class OutputTriangleCallback;
class SaveRestoreCallback;
class SaveToSatCallback;
class TopologyChangeCallback;
class TriangleCache;
class Darray;
class MorphingMapElem;
class MorphingMap;
class VertexSurfaceData;
class HideIntegerTransform;

typedef bool abool; // TODO Jiri Kripac: Why has this been added? Remove it


// Boolean operations consume the input bodies (set them to empty bodies) at 
// the end. This happens even when the operations fail, i.e. when they throw 
// exceptions. This may sometimes be inconvenient, particularly when doing 
// a whole series of Boolean operations with a set of bodies. Any single 
// Boolean operation failure looses the result of all Boolean operations 
// performed so far. It would be better if a single failed Boolean operation 
// lost just the single body that failed to Boolean but the rest was preserved.
//
// This option allows to instruct the Boolean operations to keep the input 
// bodies unchanged when the operation fails (they are still consumed when the
// operation succeeds). There is a penalty of a backup copy of the input bodies
// before every Boolean operation so use this option when you feel its benefit
// outweighs its cost.
//
// The default value of this option is false.
//
DllImpExp void setKeepInputBodiesWhenBooleanOperationsFail(bool yesNo);
DllImpExp bool keepInputBodiesWhenBooleanOperationsFail();


AMODELER_NAMESPACE_END
#endif
