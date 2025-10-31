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
// The declaration of the class Face representing a planar face in the 
// topological structure of a body. See the "body.h" file and "topology.dwg" 
// figure for the description of the B-Rep data structure.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_FACE_H
#define AMODELER_INC_FACE_H


#include "body.h"
#include "plane.h"
#include "enums.h"

AMODELER_NAMESPACE_BEGIN


// Global face flags
//
const Flag FFF      = FLAG(0);  // Front  Face Flag
const Flag CONVEXFF = FLAG(1);  // Convex Face Flag



class DllImpExp Face : public Entity
{
public:
    Face();
    Face(                 Body*);
    Face(       Surface*, Body*);
    Face(Edge*, Surface*, Body*);
    Face(const Face&);
    ~Face();

    // The following face constructors create a face and a loop of edges and
    // vertices which bound the face. If the body pointer is not null, the 
    // face is added to the body. 
    //
    // If the checkPlanarity input argument is true, the planarity of the 
    // created face is checked and if it is not planar, it is broken into 
    // multiple triangular faces.
    //
    // The "type" argument may be:
    //
    // 0 ... Forward direction of the edge loop wrt the input data 
    // 1 ... Reverse direction of the edge loop wrt the input data
    // 2 ... Two faces and edge loops (forward and reverse) are created,
    //       the corresponding edges are linked via their partner pointers,
    //       pointer to the forward face is returned

    // Create a circular face
    //
    Face(const Circle3d&, int type, int approx, Body*);

    // Create a face from polygon data, the same as for sweep operations
    //
    Face(const Point3d      plg       [],
         PolygonVertexData* vertexData[],
         int                numVertices, 
         const Vector3d&    plgNormal,
         int                type,  
         bool               checkPlanarity, 
         Body*);

    // Create a face from an array of points
    //
    Face(Point3d            p[], 
         int                numEdges,
         int                type, 
         bool               checkPlanarity,
         Body*,
         Edge**             createdEdges = NULL);  // TODO The last argument is stupid

    // Create a face from an array of vertices
    //
    Face(Vertex*            vertices[],
         Curve*             curves[],
         Edge*              partners[], 
         int                numEdges, 
         int                type, 
         bool               checkPlanarity, 
         Body*, 
         Edge**             createdEdges = NULL);

    void     modified      ();  // The face was modified in some way

    int      edgeCount     () const;
    Edge*    edge          (int edgeIndexInFace) const;
    
    Edge*    edgeLoop      () const        { return mpEdgeLoop; }
    Surface* surface       () const        { return mpSurface;  }
    Face*    next          () const        { return mpNext;     }
    Face*    prev          () const        { return mpPrev;     }
    Color    color         () const        { return mColor;     }
    void*    attrib        () const        { return mpAttrib;   }

    void     setEdgeLoop   (Edge*       e) { mpEdgeLoop = e;    }
    void     setSurface    (Surface*    s) { mpSurface  = s;    }
    void     setNext       (Face*       f) { mpNext     = f;    }
    void     setPrev       (Face*       f) { mpPrev     = f;    }

    void     setColor      (Color, bool edgesAlso = false, bool partnerEdgesAlso = false);
    void     setAttrib     (void* a)       { mpAttrib = a; }

    void     addEdge       (Edge*, Edge* prevEdge = NULL);
    void     removeEdge    (Edge*); // Does not delete the removed edge
    void     deleteAllEdges();

    void     negate        ();
    
    void     paint         (const Body&, Color, bool dae=false, bool dbe=false);

    void     massProperties(const Body&,
                            bool     dae,
                            bool     dbe,
                            double&  perimeter,
                            double&  area,
                            Point3d& centroid) const;

    double   area          () const;  // Calculate the face area, also set the plane

    void     triangulate   (OutputTriangleCallback*, 
                            TriangulationType = kGenerateTriangles) const;

    // Transforms the face by the given transformation and add side faces. The
    // face is thus lifted from its current location to a new location. 
    //
    void  lift(const Transf3d&, bool checkPlanarity, Body* owningBody);

    // Extracts all loops of the face, skipping the bridge edges. 
    // Each std::vector<Edge*> represents one extracted loop. The outer loop
    // of the face is also returned.
    //
    void extractAllLoops(std::vector<std::vector<Edge*> >& loops) const;

    // Splits the face at vertices e1->vertex() and e2->vertex(), e1 and e2 
    // being edges of this face. The newly created edges between this face and 
    // the newly created one are assigned the "approximating" flag
    //
    Face* split(Edge* e1, Edge* e2, Body*);

    // "This" face represents a positive face. The given holeFaces vector 
    // contains faces completely inside this face, coplanar with this faces, 
    // but with opposite orientation.
    //
    // The method joins the hole faces with this face by adding bridge edges.
    // The hole faces are then set to faces containg no edges. The result of 
    // this joining may be more than one well-formed face. All the faces are
    // returned in the faces vector. Notice that if the result is more than
    // one face, new faces are created and "this" face will become empty, i.e.
    // containing no edges
    // 
    void insertHoles(const std::vector<Face*>& holeFaces, // Hole faces, coplanar and completely inside "this" face
                     Body*                     pBody,     // Body that receives the new vertices and new faces
                     std::vector<Face*>&       faces);    // The resulting contiguous faces (may be more than one)

    // Valid faces represent a single contiguous area. This method decomposes 
    // a (potentially invalid) face that may represent several contiguous areas 
    // into several valid faces that each represents a single contiguous area.
    //
    // The result is returned in contiguousFaces vector. If the result is more 
    // than one face, new faces are created and "this" face will become empty,
    // i.e. containing no edges
    //
    void decomposeIntoContiguousFaces(Body* pBody, std::vector<Face*>& contiguousFaces);

    const Plane&         plane       () const;  // Face plane 
    const Interval3d&    interval    () const;  // Face interval (bounding box)
    const IntInterval3d& projInterval() const;  // Integer projected interval

    void deletePlane          () const;
    void deleteInterval       () const;
    void deleteProjInterval   () const;

    void setProjInterval      (const IntInterval3d&) const;

    bool isPointInside(const Point3d&)   const; // Returns true iff the point is inside or on edge/vertex
    bool isPlanar(double eps = epsAbs()) const;
    bool isSelfIntersecting()            const;

    void print   (FILE* = NULL)          const;
    void save    (SaveRestoreCallback*)  const;
    void restore (SaveRestoreCallback*, int version);
    
    // Scratch variables (unioned to save space)
    //
    union
    {
        Edge* iel;   // Inner edge list   (Booleans)
        Face* fptr;  // Next face in list (hide, interfere)
        int   n;     // Entity index      (print)
    };

private:

    Edge*          mpEdgeLoop;     // One edge in the loop of edges of the face
    Surface*       mpSurface;      // Exact surface, NULL for real planar faces

    Face*          mpNext;         // Next face in the linear list of faces of a body
    Face*          mpPrev;

    Plane*         mpPlane;        // Face plane
    Interval3d*    mpInterval;     // Face interval
    IntInterval3d* mpProjInterval; // Integer projected interval (hide, picking)

    Color          mColor;         // Face color
    void*          mpAttrib;       // Arbitrary user-defined attribute data

    double evaluatePlane   () const;  // Evaluate face plane, return face area  
    void   evaluateInterval() const;  // Evaluate face interval

};  // class Face


AMODELER_NAMESPACE_END


// Inlines (do not look beyond this point)

#include "edge.h"

AMODELER_NAMESPACE_BEGIN


inline const Plane& Face::plane() const 
{
    if (mpPlane == NULL)
        evaluatePlane();

    MASSERT(mpPlane->isValid());
    
    return *mpPlane; 
}



inline const Interval3d& Face::interval() const 
{ 
    if (mpInterval == NULL)
        evaluateInterval();

    return *mpInterval;
}


inline const IntInterval3d& Face::projInterval() const 
{ 
    MASSERT(mpProjInterval != NULL);
    return *mpProjInterval;
}


inline void Face::addEdge(Edge* e, Edge* prevEdge)
{
    if (e == NULL) {
        FAIL;
        return;
    }

    // The edge should be in a neutral state
    //
    MASSERT(e->next() == NULL && e->prev() == NULL && e->face() == NULL);

    // If no prevEdge is given, use Face::edgeLoop()
    //
    if (prevEdge == NULL)
        prevEdge = edgeLoop();

    if (prevEdge != NULL) 
    {
        e->addAfter(prevEdge);

    } else {
        // Adding the first edge to the face
        //
        e->setNext(e);
        e->setPrev(e);
    }

    e->setFace(this);
    setEdgeLoop(e);  // Let this face point to the given edge
}


inline void Face::removeEdge(Edge* e)
{
    if (e == NULL || e->face() != this)
    {
        FAIL;
        return;
    }

    // If the Face::edgeLoop() pointer of this face points to the edge being
    // removed, change it to point to another edge in the loop of edges of this
    // face
    //
    if (edgeLoop() == e)
    {
        if (e->next() != e)
        {
            setEdgeLoop(e->next());
        }
        else
        {
            setEdgeLoop(NULL); // We are removing the last edge in the loop
        }
    }

    // Unlink the edge and put it to a neutral state
    //
    e->next()->setPrev(e->prev());
    e->prev()->setNext(e->next());
    e->removePartner();

    e->setNext(NULL);
    e->setPrev(NULL);
    e->setFace(NULL);
}

AMODELER_NAMESPACE_END
#endif
