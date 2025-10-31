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
// The declaration of the class Edge representing an edge (COEDGE in the ACIS
// terminology) in the topological structure of a body. See the "body.h" file and
// the "topology.dwg" figure for the description of the B-Rep data structure.
//
// Circles:
//
// Edges are straight line segments. When the straight edge is an aproximation 
// of a circle (resulting from the intersection of a planar face with faces 
// which approximate a non-planar surface), the geometry of the circle can be 
// obtained by the Edge::circle() method.
// 
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_EDGE_H
#define AMODELER_INC_EDGE_H


#pragma warning(push)
#pragma warning(disable : 4702) // unreachable code
#include <vector>
#pragma warning(pop)
#include "entity.h"
#include "color.h"
#include "circle3d.h"
#include "vertex.h"

AMODELER_NAMESPACE_BEGIN


// Global edge flags
//
const Flag AEF    = FLAG(0);   // Approximating Edge Flag
const Flag BEF    = FLAG(1);   // Bridge        Edge Flag
const Flag PICKEF = FLAG(2);   // Pickable      Edge Flag (for edge picking)


class DllImpExp Edge : public Entity
{
public:
    Edge();
    
    // Creates an edge and links it into the topological data structure.
    //
    // The vertex pointer must not be NULL.
    //
    // If prevEdge is NULL and face is given, the edge will be added after the 
    // face->edgeLoop() edge, otherwise the edge will be added after the 
    // prevEdge in the loop of edges.
    //
    // If the owning face is not NULL, the face->edgeLoop() of the face is 
    // set to point to this newly created edge. This way, when adding edges of 
    // a face, you can pass prevEdge as NULL and the new edges will be added
    // in the proper order.
    //
    Edge(Vertex*, Face* face, Edge* prevEdge, Edge* partner, Curve* = NULL);
    
    // The following function creates two (partner) Edge objects whose owning 
    // faces are are f1 and f2 and end vertices are v1 and v2. These two Edge 
    // objects represent a "real" or "Euler" edge of the model, an edge 
    // between faces f1, f2 and with end vertices v1, v2. Returns pointer to the 
    // Edge object owned by face f1.
    //
    // The me() function must be used in such a way that the newly created
    // real edge (pair of edges) touches already existing edges of face f1 and
    // face f2 (touches the edges in edge loops of faces f1, f2). The only 
    // exception to this rule is when an edge loop of a face is empty.
    //
    // extern Edge* me(Face* f1, Face* f2, Vertex* v1, Vertex* v2);
    
    Vertex* vertex        () const    { return mpVertex;  }
    Face*   face          () const    { return mpFace;    }
    Edge*   next          () const    { return mpNext;    }
    Edge*   prev          () const    { return mpPrev;    }
    Edge*   partner       () const    { return mpPartner; }
    Curve*  curve         () const    { return mpCurve;   }
    Color   color         () const    { return mColor;    }
    
    void    setVertex     (Vertex* v) { mpVertex  = v;    }
    void    setFace       (Face*   f) { mpFace    = f;    }
    void    setNext       (Edge*   e) { mpNext    = e;    }
    void    setPrev       (Edge*   e) { mpPrev    = e;    }
    void    setPartner    (Edge* par) { mpPartner = par;  }

    void    setCurve      (Curve*, bool partnersAlso = false); 
    void    setColor      (Color,  bool partnersAlso = false);
    
    // Add/remove edge to/from the cyclical list of partner edges
    //
    void    addPartner    (Edge*);
    void    removePartner ();

    // Orders the partner edges around a non-manifold Euler edge so that the
    // partner pointer of each edge is going to point to the edge whose face 
    // geometrically immediately follows the face of the edge, when going 
    // around the Euler edge.
    //
    // The direction of the ordering depends on which edge is chosen as "this"
    // edge. Out of the two possible partners of this edge, it chooses the one 
    // for which the segment between the face of this edge and the face of the
    // partner edge represents the interior of the solid.
    //
    // If there is a problem and the partner edges are not correctly ordered, 
    // an exception is thrown.
    //
    // This method does nothing for manifold edges. No ordering is needed
    // because there are only two edges around an Euler edge.
    //
    // Notice that if you do not call this method, the partner edges sharing
    // the same Euler edge are not ordered around the Euler edge.
    //
    void orderPartnerEdgesAroundEulerEdge();

    // Deletes the edge and its partners, fixing the adjacent topology so that
    // the edge is reduced to the start vertex of the edge. If edgeLoop() of 
    // the face points to an edge that will be deleted, it is changed to point 
    // to the next edge in the loop (or to NULL if it was the only edge in the 
    // loop)
    //
    void collapse(); 

    void    addAfter      (Edge* prevEdge);  // Add after an edge in a loop

    // The following methods check for the bridge partners, i.e. a partner that
    // has the same face as the edge. These methods do not look at the BEF flag
    //
    Edge*   getPartnerBridgeEdge() const; // Returns NULL if not a bridge
    Edge*   nextSkipBridge      () const;
    Edge*   prevSkipBridge      () const;

    // Returns parameters of a circle if the edge lies on a geometric circle.
    // Returns a circle with radius 0 if the edge does not lie on a geometric 
    // circle
    //
    Circle3d circle() const;

    // Returns angle between the two faces sharing the "real" edge (or 0 if it
    // is a non-manifold edge). For convex edges, the angle is less than pi;
    // for concave edges, the angle is greater than pi.
    //
    double angleBetweenFaces() const;

    // Returns angle between this edge and the previous edge. The angle is
    // measured in the plane of the face owning these two edges.
    //
    double angleBetweenEdges() const;

    // Returns coordinates of the point of the edge vertex.
    //
    Point3d point() const;

    // Returns vector of the edge.
    //
    Vector3d vector() const
    { 
        return mpNext->mpVertex->point() - mpVertex->point(); 
    }

    // Returns unit vector of the edge.
    //
    Vector3d unitVector() const;

    // Returns a Line3d object with the edge geometry (point and vector).
    //
    Line3d line() const;

    // Returns a unit normal vector to the edge. The direction of the normal 
    // vector is inside the face owning this edge
    //
    Vector3d normal() const;

    // Returns a unit normal vector at the vertex of the edge. The normal is
    // calculated as follows:
    //
    // - If the face of the edge has no surface, the face plane normal is 
    //   returned.
    // - If the face has UnspecifiedSurface, the normal is calculated as a 
    //   weighted average of the plane normals of the faces which point to
    //   the same UnspecifiedSurface.
    // - If the face has a surface, the surface normal is returned.
    //
    Vector3d vertexNormal() const;

    // Returns plane of the face owning this edge.
    //
    Plane plane() const;

    // Returns surface of the face owning this edge.
    //
    Surface* surface() const;

    // Returns true if the edge lies on a circle.
    //
    bool isOnCircle() const;

    // Returns true if the edge is on a circle and all the edges on that 
    // circle make a full circle.
    //
    bool isOnFullCircle() const;

    // Returns true if the "real" edge is shared by exactly two faces.
    //
    bool isManifold() const;

    bool angleBetweenFacesIsConvex  () const;  
    bool angleBetweenFacesIsConcave () const;  
    bool angleBetweenFacesIsStraight() const;  
    bool isBridge                   () const;
    bool isApprox                   () const;

    void setApproxFlag (OnOff = kOn);
    void setBridgeFlag (OnOff = kOn);

    bool hasPartner(Edge*) const;
    
    // Returns true for exactly one of the partner edges representing a "real"
    // "Euler" edge. Returns false for all other partner edges. The edge which   
    // is chosen is picked at random. This method is intended to be used,
    // for example, to draw all "real" edges of the body. Using this method 
    // ensures that each "real" edge is drawn only once.
    //
    bool isEulerEdge() const;

    Edge* eulerEdge(); // Returns the edge in the partner loop that isEulerEdge

    bool canMergeWithPrevious(bool sameColorOnly) const;

    void print  (FILE* = NULL)         const;  // Not for public use
    void save   (SaveRestoreCallback*) const;  // Not for public use
    void restore(SaveRestoreCallback*);        // Not for public use

    void mergeLoopsSharingEdge  ();
    void mergeLoopsAddBridgeEdge(Edge* innerEdge);

    // Returns all edges of the face of this edge that are incident at the same 
    // two faces as this edge is. The edges are sorted along the direction of
    // this edge.
    //
    // If connectedSequenceOnly is true, only edges that form a connected 
    // sequence of which this edge is part are returned. A connected sequence
    // is defined (for this purpose only) as a sequence of edges where the end
    // vertex of one edge is equal to the start vertex of the next edge.
    //
    // If connectedSequenceOnly is false, all edges are returned, possibly
    // forming more than one connected sequence
    // 
    void getAllEdgesSharingSameFaces(bool                connectedSequenceOnly, 
                                     std::vector<Edge*>& sortedEdges);

    void getAllEdgesStartingFromVertex(std::vector<Edge*>&);
    void getAllEdgesEndingInVertex    (std::vector<Edge*>&);

    void split (Vertex*);   // Splits at vertex
    void merge ();          // Merges with previous edge
    void remove();          // Removes from the data structure, does not delete it

    union  // Scratch data members (unioned to save space)
    {
        Edge*          eptr;  // Next edge in list               (hide)
        Edge*          nie;   // Next inner edge                 (Boooleans)
        int            xmin;  // Min x-coord of edge             (hide)
        IntInterval3d* ibp;   // Integer projected edge interval (hide) 
        int            n;     // Entity index                    (print)
    };

private:

    Vertex*  mpVertex;   // The start vertex of the edge.
    Face*    mpFace;     // The owning face.

    Edge*    mpNext;     // The next edge in the loop of edges of a face.
    Edge*    mpPrev;     // The previous edge in the loop of edges of a face.

    Edge*    mpPartner;  // The partner edge, which is the edge of a face  
                         // adjacent to the face owning this edge. All partner edges form
                         // a cyclical list which may contain more than two
                         // edges if the "real" edge is a non-manifold one.

    Curve*   mpCurve;    // Optional pointer to the underlying curve (not used
                         // much yet, may be set to NULL even if the edge is on
                         // a curve).

    Color    mColor;     // Edge color.

};  // class Edge


DllImpExp extern Edge* me      (Face* f1, Face* f2, Vertex* v1, Vertex* v2);
DllImpExp extern Edge* makeEdgeLoop(const Circle3d&, int type, int approx, Face* f1, Face* f2, Body*);
DllImpExp extern Edge* makeEdgeLoop(Vertex* [], Curve* [], Edge* [], int numEdges, int type, Face* f1, Face* f2);


AMODELER_NAMESPACE_END


// Inlines (do not look beyond this point)

#include "face.h"

AMODELER_NAMESPACE_BEGIN


inline Edge::Edge() 
      : mpVertex (NULL),
        mpFace   (NULL), 
        mpNext   (NULL), 
        mpPrev   (NULL), 
        mpCurve  (NULL),
        mColor   (defaultColor())
{
   mpPartner = this;
}



inline void Edge::removePartner()
{
    Edge* e = this;

    do {
    } while ((e = e->partner())->partner() != this);

    e->setPartner(partner());
    setPartner(this);
}



inline void Edge::addAfter(Edge* prevEdge)
{
    MASSERT(prevEdge != NULL);

    setNext(prevEdge->next());
    setPrev(prevEdge);
    prevEdge->setNext(this);
    if (next() != NULL) {
        next()->setPrev(this);
    } else {
        FAIL;  // Not a cyclical loop of edges
    }
}



inline Point3d Edge::point() const
{
    return mpVertex->point();
}



inline Vector3d Edge::unitVector() const 
{ 
    return (next()->point() - point()).normalize(); 
}



inline bool Edge::isManifold() const
{
    return partner()->partner() == this && partner() != this;
}



inline Plane Edge::plane() const
{
    return mpFace->plane();
}



inline Surface* Edge::surface() const
{
    return mpFace->surface();
}



inline Line3d Edge::line() const
{
    return Line3d(mpVertex->point(), vector());
}



inline bool Edge::isBridge() const
{
    return isFlagOn(BEF);
}



inline bool Edge::isApprox() const
{
    return isFlagOn(AEF);
}


AMODELER_NAMESPACE_END
#endif
