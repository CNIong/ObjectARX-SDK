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
// Declaration of classes representing curves. Edges may have pointers to
// curve objects which represent the exact geometry the edges tessellate.
//
// The curves are not fully supported by the modeler. Mostly, edges will have
// NULL curve pointer. Currently, the only situation when Curve objects are 
// created is in the complex Face constructors which create faces along with 
// their loops of edges and vertices.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_CURVE_H
#define AMODELER_INC_CURVE_H


#include "entity.h"
#include "circle3d.h"
#include "transf3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp Curve : public Entity
//
// The base class, provides the common protocol.
//
{
public:
    Curve(Body* = NULL);

    // We support these curve types
    //
    enum Type { kUnspecified, kCircle };

    virtual Type     type     () const = NULL;
    virtual Curve*   copy     () const = NULL;

    // The transform() method returns true if the curve was successfully 
    // transformed or false if it could not be transformed (e.g. a circle 
    // cannot be stretched in a direction not parallel to its axis).
    //
    virtual bool     transform(const Transf3d&,
                               Transf3d::Type  transfType  = Transf3d::kUnknown,
                               const Vector3d& stretchVect = Vector3d::kNull) = NULL;

    virtual void     print    (FILE* = NULL)         const = NULL;
    virtual void     save     (SaveRestoreCallback*) const;
    virtual void     restore  (SaveRestoreCallback*)       {}

    Curve*           next     () const     { return mpNext; }
    void             setNext  (Curve* c)   { mpNext = c;    }

    // Scratch data members
    //
    Curve* cptr;
    int    n;     // For print

private:

    Curve* mpNext;   // Next curve in the list of all curves of a body

}; // class Curve



class DllImpExp UnspecifiedCurve : public Curve
//
// Represents all curves which we do not explicitly recognize and do not 
// maintain their exact equations. 
//
// We keep an UnspecifiedCurve object for each such curve so that all the 
// edges which belong to these curves at least know they belong to the same 
// curve.
//
{
public:

    UnspecifiedCurve(Body* b = NULL) : Curve(b) {}
    
    virtual Type     type     () const { return kUnspecified; }
    virtual Curve*   copy     () const { return new UnspecifiedCurve(*this); }
    virtual void     print    (FILE* = NULL) const;

    virtual bool     transform(const Transf3d&,
                               Transf3d::Type  /*transfType*/  = Transf3d::kUnknown,
                               const Vector3d& /*stretchVect*/ = Vector3d::kNull) 
    { return true; }

}; // class UnspecifiedCurve



class DllImpExp CircleCurve : public Curve
{
public:

    CircleCurve() {}
    CircleCurve(const Circle3d&, int approx, Body*); 

    // Return circle definiton data
    //
    const Transf3d&  transf   () const { return mTransf;          }
    Point3d          origin   () const { return mTransf.origin(); }
    Line3d           axis     () const;  
    double           radius   () const { return mRadius; }
    int              approx   () const { return mApprox; }
    Circle3d         circle   () const { return Circle3d(axis(), mRadius); }

    virtual Type     type     () const { return kCircle; }
    virtual Curve*   copy     () const { return new CircleCurve(*this); }

    virtual bool     transform(const Transf3d&, 
                               Transf3d::Type  transfType  = Transf3d::kUnknown,
                               const Vector3d& stretchVect = Vector3d::kNull);

    virtual void     print    (FILE* = NULL)          const;
    virtual void     save     (SaveRestoreCallback*)  const;
    virtual void     restore  (SaveRestoreCallback*);

private:

    Transf3d mTransf;
    double   mRadius;
    int      mApprox;

}; // class CircleCurve



AMODELER_NAMESPACE_END
#endif
