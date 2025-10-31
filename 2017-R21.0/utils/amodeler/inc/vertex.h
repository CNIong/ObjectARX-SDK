///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
//
// The information contained herein is confidential, proprietary
// to Autodesk,  Inc.,  and considered a trade secret as defined
// in section 499C of the penal code of the State of California.
// Use of  this information  by  anyone  other  than  authorized
// employees of Autodesk, Inc.  is granted  only under a written
// non-disclosure agreement,  expressly  prescribing  the  scope
// and manner of such use.
//
// DESCRIPTION:
//
// The declaration of the class Vertex representing a vertex in the 
// topological structure of a body. See the "body.h" file and "topology.dwg"   
// figure for the description of the B-Rep data structure.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_VERTEX_H
#define AMODELER_INC_VERTEX_H


#include "entity.h"
#include "point3d.h"

AMODELER_NAMESPACE_BEGIN


// Global vertex flags
//
const Flag PICKVF         = FLAG(0);  // Pickable Vertex Flag (for vertex picking)
const Flag NONMANIFOLD_VF = FLAG(1);


class DllImpExp Vertex : public Entity
{
public:
    Vertex() : mpVertexSurfaceDataList(NULL), mpNext(NULL) {}
    Vertex(const Point3d&, Body*);
    ~Vertex();

    const Point3d& point     () const           { return mPoint; }
    Vertex*        next      () const           { return mpNext; }

    void           setPoint  (const Point3d& p) { mPoint  = p;   }
    void           setNext   (Vertex* v)        { mpNext  = v;   }
    void           transform (const Transf3d&); 
    void           modified  ();

    VertexSurfaceData* vertexSurfaceDataList   () const { return mpVertexSurfaceDataList; }
    void               deleteVertexSurfaceData ();
    void               setVertexSurfaceDataList(VertexSurfaceData* vsd) { mpVertexSurfaceDataList = vsd; }

    // Return the VertexSurfaceData corresponding to e->surface(). If it is not
    // already available in the list, evaluate it from  e->surface() or from 
    // the faces incident at this vertex (lazy evaluation)
    //
    VertexSurfaceData* vertexSurfaceData(const Edge* e); 
    
    void           print     (FILE* = NULL)         const;        // Not for public use
    void           save      (SaveRestoreCallback*) const;        // Not for public use
    void           restore   (SaveRestoreCallback*, int version); // Not for public use

    IntPoint3d     ip;  // Projected vertex coordinates (in integers).
                        // Used by the hidden-line algorithm and picking

    // Scratch data members (unioned to save space)
    //
    union
    {
        Vertex* vptr;
        int     n;
    };
    union
    {
        Edge*   eptr;
        Vertex* vptr1;
    };

private:

    Point3d            mPoint;            
    VertexSurfaceData* mpVertexSurfaceDataList; 
    Vertex*            mpNext; 

}; // class Vertex


// Inlines (do not look beyond this point)

inline Vertex::~Vertex()
{
    deleteVertexSurfaceData();
}


AMODELER_NAMESPACE_END
#endif
