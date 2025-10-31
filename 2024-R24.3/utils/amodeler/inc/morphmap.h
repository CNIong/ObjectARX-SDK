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
// The MorphingMap class is used to define the morphing between the profiles
// (bodies with a single face) which have different topology (usually different 
// number of face vertices).
//
// The mapping is a sequence of individual mappings:
//
//  fromIndex --> toIndex
//  fromIndex --> toIndex
//  fromIndex --> toIndex
//    .................
//
// The fromIndex is an index of a vertex (actually of an edge pointing to the
// vertex) in one profile and toIndex is an index of the corresponding vertex 
// in the other profile. This defines the correspondence between the vertices
// on both profiles.
//
// Only some forms of mapping are allowed:
//
// Mapping 1 --> 1:
//
//  fromIndex1 --> toIndex1
//  fromIndex2 --> toIndex2
//
// The distance (number of vertices) between fromIndex1 and fromIndex2 must be 
// the same as the distance between toIndex1 and toIndex2. Quadrilateral faces
// will be generated between the two profiles.
//
// Mapping 1 --> n
//
//  fromIndex1 --> toIndex1
//  fromIndex1 --> toIndex2
//
// Triangular faces, all sharing one common vertex fromIndex1, will be 
// generated between the two profiles.
//
// Mapping n --> 1
//
//  fromIndex1 --> toIndex1
//  fromIndex2 --> toIndex1
//
// Triangular faces, all sharing one common vertex toIndex1, will be generated
// between the two profiles.
//
// An example of a mapping of a rectangle to a circle, approximated by 24 
// segments, may be:
//
//      0  --> 16
//      0  --> 24
//      1  --> 24
//      1  -->  0
//      2  -->  0
//      2  -->  8
//      3  -->  8
//      3  --> 16
//
// The 'visibility' code given to each individual mapping specifies how the
// visibility attributes of the edges should be assigned:
//
// - kCrossEdgeIsApprox means that the edge going from fromIndex to toIndex 
//   should be marked as approximating.
//
// - kBaseEdgeIsApprox means that the edges between fromIndex1 and fromIndex2
//   should be marked as approximating.
//
// In addition, all the "cross edges" (between the two profiles), for which 
// there is no explicit mapping, are also marked approximating. For example, 
// in the mapping:
//
//      0 --> 16
//      0 --> 24
//
// all cross edges starting from vertex 0 and ending in vertices 17, 18, 19, 
// 20, 21, 22 and 23 will automatically be marked approximating.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_MORPHMAP_H
#define AMODELER_INC_MORPHMAP_H


#include "global.h"
#include "darray.h"


AMODELER_NAMESPACE_BEGIN


class DllImpExp MorphingMap
{
public:
    MorphingMap() {}
    MorphingMap(const MorphingMap&);
    ~MorphingMap();

    MorphingMap& operator =(const MorphingMap&);

    void  add  (int from, int to, int vis = 0);
    void  addAt(int index, int from, int to, int vis = 0);
    void  del  (int index);
    void  get  (int index, int& fromIndex, int& toIndex, int& visibility) const;

    int  length() const { return mArray.length(); }
    bool isNull() const { return mArray.length() == 0; }
    bool isIdentity() const;

    void setToExplicitIdentityMap(int numEdges); // Mapping 0-->0, 1-->1, 2-->2, 3-->3, etc.

    void createFromTwoPointLoops(const std::vector<Point2d>&, const std::vector<Point2d>&);

    void init();         // Empties the map
    void print() const;

    // Converts mapping m --> n (m > n) to:
    // a --> 1
    // n --> n
    // b --> 1
    //
    // and mapping m --> n (m < n) to:
    // 1 --> a
    // m --> m
    // 1 --> b
    //
    // where a = abs(m-n+1)/2 and b = abs(m-n) - a
    //
    void normalize(int numEdges0, int numEdges1);

    void remapIndices(const std::vector<int>& fromIndexMap, const std::vector<int>& toIndexMap);

    static const MorphingMap kNull;

    enum { kCrossEdgeIsApprox = 1, kBaseEdgeIsApprox = 2 };

private:

    class MorphingMapElem
    {
    public:
        MorphingMapElem(int i, int j, int vis = 0) : fromIndex(i), toIndex(j), visibility(vis) {} 

        int fromIndex;
        int toIndex;
        int visibility;
    };

    Darray mArray;  // Dynamic array of pointers to MorphingMapElems 
}; // class MorphingMap



// The following functions are mainly for the internal use

DllImpExp void makeIndexToEdgeMap(  int                 prof0NumEdges, 
                                    const Body&         prof1, 
                                    const MorphingMap&  morphingMap,
                                    Darray&             indexToEdgeMap);

DllImpExp void splitMorphingMap(    const Body&         prof0, 
                                    const Body&         prof1, 
                                    const MorphingMap&  morphingMap,
                                    Body&               midProf,
                                    MorphingMap&        midMorphingMap, 
                                    MorphingMap&        morphingMap0, 
                                    MorphingMap&        morphingMap1); 

AMODELER_NAMESPACE_END
#endif

