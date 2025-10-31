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
// The declaration of the class VertexSurfaceData which represents the surface
// parameters at the given vertex. Currently, the only surface parameter is
// its normal, in the future it may be the u-v space coordinates, derivatives,
// etc.
//
// Each vertex may keep a linear list of VertexSurfaceData objects, one object
// for each surface the vertex lies in. The VertexSurfaceData is evaluated on 
// demand (lazily) when it is needed - when Vertex::vertexSurfaceData() method
// is called. It is then kept in the vertex for subsequent reuses.
//
// Note: To obtain the vertex normal of a vertex of a face, use the 
//       Edge::vertexNormal() method. This method retrieves the correct vertex
//       normal from the vertex and possibly reverses it so that it is the 
//       same direction as the face plane normal.
//       
// If the face is planar (has no surface), the VertexSurfaceData is not 
// evaluated and stored and the vertex normal is the normal of the face plane.
//
// If the face has a surface pointer and the surface is not UnspecifiedSurface,
// the VertexSurfaceData is evaluated from the exact surface definition.
//
// Otherwise, if the face has a pointer to an UnspecifiedSurface, the 
// VertexSurfaceData (the normal) is evaluated as the weighted average of the
// normals of planes of all the faces which share this vertex and which 
// point to the same UnspecifiedSurface. The weight is the angle at the vertex 
// returned by the Edge::angleBetweenEdges() method.
//
// The VertexSurfaceData is saved/restored/copied with the body and transformed
// when the body is transformed. Even if the surfaces of the body are destroyed 
// (converted to UnspecifiedSurfaces) by a non-uniform scaling transformation, 
// for example, the precise VertexSurfaceData is still preserved.
//
// If you intend to use vertex normals after applying some type of a
// transformation which destroys the exact surface equations, it is wise to
// evaluate the VertexSurfaceData before aplying the transformation. This way
// the VertexSurfaceData is evaluated from the precise surface equations, 
// cached, and then transformed. Otherwise, it would be evaluated from the face
// plane normals by the weighted averaging method which might be less accurate.
//
// The Body::evaluate/deleteVertexSurfaceData() method is used to evaluate or
// delete the VertexSurfaceData of all body vertices.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_VERTSURF_H
#define AMODELER_INC_VERTSURF_H


#include "entity.h"
#include "vector3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp VertexSurfaceData : public Entity
{
public:
    VertexSurfaceData() : mpSurface(NULL), mpNext(NULL), mNormal(0,0,0) {}

    VertexSurfaceData(const Edge*);

    Surface*           surface() const                  { return mpSurface; }
    VertexSurfaceData* next   () const                  { return mpNext;    }
    const Vector3d&    normal () const                  { return mNormal;   }

    void               setNext   (VertexSurfaceData* pVsd) { mpNext = pVsd; }
    void               setSurface(Surface*           s)    { mpSurface = s; }
    void               transform (const Transf3d&    t)    { mNormal  *= t; }


    void            print     (FILE* = NULL)         const; // Not for public use
    void            save      (SaveRestoreCallback*) const; // Not for public use
    void            restore   (SaveRestoreCallback*);       // Not for public use

private:

    Surface*           mpSurface; 
    VertexSurfaceData* mpNext;  
    Vector3d           mNormal;  // Direction of the surface normal at the vertex
//  Point2d            mParamPoint;

}; // class VertexSurfaceData


AMODELER_NAMESPACE_END
#endif
