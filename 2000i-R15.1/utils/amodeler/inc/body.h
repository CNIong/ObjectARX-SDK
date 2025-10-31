#ifndef AMODELER_INC_BODY_H
#define AMODELER_INC_BODY_H


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
// The header file "body.h" declares class Body which contains public methods 
// to create, manipulate, save/restore, measure and display bodies.
//
// HIERARCHY OF TOPOLOGICAL CLASSES
// ================================
//
// Entity                                   (file entity.h)
//        -> Body                           (file body.h)
//        -> Face                           (file face.h)
//        -> Edge                           (file edge.h)
//        -> Vertex                         (file vertex.h)
//        -> Surface                        (file surface.h)
//                   -> CylinderSurface     (file surface.h)
//                   -> ConeSurface         (file surface.h)
//                   -> SphereSurface       (file surface.h)
//                   -> TorusSurface        (file surface.h)
//        -> Curve                          (file curve.h)
//                   -> CircleCurve         (file curve.h)
//
// B-REP TOPOLOGICAL DATA STRUCTURE
// ================================
//
// Bodies are represented by their boundaries (Boundary representation, B-rep)
// using a modified Winged-Edge data structure. It is a dynamic data structure
// consisting of mutually interconnected objects representing Bodies, Surfaces,
// Faces, Edges, and Vertices (see figure topology.dwg). Non-manifold solid 
// bodies can also be represented.
//
// The faces are planar. Face normals point outwards from the body. Curved 
// surfaces are approximated by planar facets. Each facet which approximates
// a curved surface has a pointer to a surface object. The surface may be 
// cylindrical, conical, spherical, toroidal or unspecified (representing all 
// remaining surfaces for which we do not provide an exact equation). If an 
// operation which destroys the surface information (for example, non-uniform 
// scaling) is applied to the body, the surfaces also become of type 
// "unspecified". The exact surface equations are lost but the information that 
// the faces belong together and tessellate common surfaces is preserved.
//
// Each "real" "Euler" edge of the body is represented by at least one 
// pair of partner Edge objects (COEDGEs in the ACIS terminology) since each 
// edge of a solid body is shared by at least two faces. Non-manifold edges are
// represented by at least four (generally an even number of) partner edges.
//
// Edges shared by two approximating faces belonging to the same surface,  
// so-called "Approximating Edges", are marked by the AEF flag (Approximating  
// Edge Flag) and are normally displayed only if they are on the silhouette of
// the body.
//
// Each face is bounded by exactly one loop of its edges. Edges are arranged
// in a counterclockwise sense when looking from the outside of the body. 
// That means the interior of the face lies to the left of the edge.
//
// Holes in faces are connected to the outer loop of edges by a pair of 
// antiparallel, so-called "Bridge Edges" (such edges are marked by the BEF 
// flag (Bridge Edge Flag). 
// 
// Edges that are shared by a pair of faces having no discontinuity in slope
// at this edge are also marked as bridge edges. Bridge edges are not normally 
// displayed.
//
// Vertices just keep the x,y,z coordinates.
//
///////////////////////////////////////////////////////////////////////////////

#include "entity.h"
#include "interval.h"
#include "transf3d.h"
#include "color.h"
#include "morphmap.h"
#include "enums.h"

AMODELER_NAMESPACE_BEGIN

// Global body flags (for internal use only)
//
const Flag IPBF   = FLAG(0);  // Interval Present            Body Flag  
const Flag NEGBF  = FLAG(1);  // Negative                    Body Flag
const Flag DASHBF = FLAG(2);  // Display DASHed        lines Body Flag
const Flag WFBF   = FLAG(3);  // Display Wireframe           Body Flag
const Flag DAEBF  = FLAG(4);  // Display Approximating Edges Body Flag
const Flag DBEBF  = FLAG(5);  // Display Bridge        Edges Body Flag



///////////////////////////////////////////////////////////////////////////////
//                              Class Body
///////////////////////////////////////////////////////////////////////////////

class DllImpExp Body : public Entity
{
public:

    ///////////////////////////////////////////////////////////////////////////
    //                  Constructor, destructor, assignment, copy
    // Notes:
    //
    // The copy constructor and "=" operator set the input body to empty body
    // so that its contents cannot be used any more. The copy constructor and 
    // "=" operator are MOVE rather than COPY actions.
    //
    // To make a real copy of a Body, use the Body::copy() method.
    ///////////////////////////////////////////////////////////////////////////

    Body();
    Body(const Body&);
    ~Body();

    Body& operator =(const Body &);
    
    Body copy() const; 

    void init(bool deleteContents); // Make the body empty (and delete contents)

    void modified();  // The body was modified in some way


    ///////////////////////////////////////////////////////////////////////////
    //  Boolean operations, plane sectioning, interference, point-in-body
    //
    // Note: 
    //
    // The Boolean operations and sectioning, including their operator form
    // (operators +, -, *, +=, -=, *=), reuse the entities of the input bodies
    // to produce the resulting body and set the input bodies to empty bodies.
    ///////////////////////////////////////////////////////////////////////////

    Body  boolOper   (Body&, BoolOperType);

    // The section method removes part of the body in the positive halfplane
    //
    void  section    (const Plane&); 

    Body  operator + (const Body& );
    Body  operator - (const Body& );
    Body  operator * (const Body& );
    Body  operator - (const Plane&);

    Body& operator +=(const Body& ); 
    Body& operator -=(const Body& ); 
    Body& operator *=(const Body& ); 
    Body& operator -=(const Plane&);

    BodyInterferenceType interfere  (const Body&   ) const;
    PointInBodyLocation  contains   (const Point3d&) const; 
    PointInBodyLocation  contains   (const Point3d&, 
                                     Entity*& coincidentEntity) const;

    BodyInterferenceType operator &&(const Body&   ) const;
    PointInBodyLocation  operator &&(const Point3d&) const;

    // PointInBodyLocation operator &&(const Point3d&, const Body&);

    // Tests the intersection of a ray against faces of the body and returns 
    // the entity which intersects the ray most close to the ray point. The 
    // tolearnce input argument is used for deciding whether the ray intersects
    // an edge or a vertex.
    //
    // The method returns:
    //
    // - RayBodyIntersection status indicating what type of entity
    //   (if any) has been intersected.
    //
    // - Pointer to the closest intersected object which may be:
    //     Face* when a  face   has been intersected.
    //     Edge* when an edge   has been intersected.
    //     Edge* when a  vertex has been intersected (use the Edge::vertex()
    //     method to obtain the Vertex*).
    //     
    // - Distance of the closest intersected entity from the ray point. 
    //
    RayBodyIntersection rayIntersection(
                             const Line3d& ray,
                             double        tolerance,
                             Entity*&      closestIntersectedEntity,
                             double&       closestEntiyDistanceAlongRay) const;

    RayBodyIntersection rayIntersection(
                             const Line3d& ray,
                             double        tolerance,
                             Entity*&      closestIntersectedEntity) const;

    // Just adds together faces, edges, vertices and surfaces of both bodies
    //
    Body combine(Body&);  


    ///////////////////////////////////////////////////////////////////////////
    //                          Geometric transformations
    ///////////////////////////////////////////////////////////////////////////

    Body& translate(const Vector3d&);

    Body& rotate   (const Line3d& axis, double angle);

    Body& scale    (const Point3d& fixedPt, double factor);

    // Scales in the directions of x, y and z axis by the scale factor 
    // xyzFactors.x, xyzFactors.y and xyzFactors.z, respectively
    //
    Body& scale    (const Point3d& fixedPt, const Vector3d& xyzFactors);

    // Scales (stretches) the body in the given direction. The axis.point is 
    // the fixed point, the axis.vector is the direction of the stretch. The 
    // length of the axis.vector defines the scale factor
    //
    Body& stretch  (const Line3d& axis);

    Body& mirror   (const Plane&);

    // The transformation maps points as follows:
    //
    // Point  src1             maps to point  dst1
    // Vector (src1,src2)      maps to vector (dst1,dst2)
    // Plane  (src1,src2,src3) maps to plane  (dst1,dst2,dst3)
    //
    Body& align    (const Point3d& src1, 
                    const Point3d& src2,
                    const Point3d& src3,
                    const Point3d& dst1,
                    const Point3d& dst2,
                    const Point3d& dst3);

    // The transformation maps points and vectors as follows:
    //
    // Point  src1             maps to point  dst1
    // Vector src2             maps to vector dst2
    // Plane  (src1,src2,src3) maps to plane  (dst1,dst2,dst3)
    //
    Body& align    (const Point3d&  src1, 
                    const Vector3d& src2,
                    const Vector3d& src3,
                    const Point3d&  dst1,
                    const Vector3d& dst2,
                    const Vector3d& dst3);

    // The transformation maps points and vectors as follows:
    //
    // Point  src1             maps to point  dst1
    // Vector src2             maps to vector dst2
    //
    Body& align    (const Point3d&  src1, 
                    const Vector3d& src2,
                    const Point3d&  dst1,
                    const Vector3d& dst2);

    Body& transform(const Transf3d&);

    Body& negate     ();
    Body  operator  -();                   

    Body& operator *=(const Transf3d&);          
    Body  operator * (const Transf3d&); 

    // Body operator *(const Transf3d&, Body&);
    

    ///////////////////////////////////////////////////////////////////////////
    //                          Mass properties
    ///////////////////////////////////////////////////////////////////////////

    // The meaning of the returned moments and products is as follows:
    //
    // moments.x  = integral x*x dv
    // moments.y  = integral y*y dv
    // moments.z  = integral z*z dv
    //
    // products.x = integral y*z dv
    // products.y = integral z*x dv
    // products.z = integral x*y dv
    //
    void massProperties(double&  area,
                        double&  volume,
                        Point3d& centroid,
                        Point3d& moments,
                        Point3d& products) const;

    double volume() const;


    ///////////////////////////////////////////////////////////////////////////
    //                          Primitives
    // Notes: 
    //
    // The "approx" argument specifies the number of facets approximating 
    // non-planar surfaces in one parametric direction. It must be at least 4.
    //
    // If you want the tessellated surface to lie within a certain tolerance
    // w.r.t. the exact surface, use function deviationToApprox() 
    // (file deviat.h) to convert your relative deviation to the number of 
    // approximating facets.
    //
    // The baseNormal argument, if provided, specifies the direction of the 
    // normal vector of the bottom and top circles of cylinders/cones. If the 
    // baseNormal is not parallel to the cylinder/cone axis, the cylinder/cone 
    // will be skewed and the surfaces will not be cylindrical/conical.
    //
    // If the baseNormal is not given or is Vector3d(0,0,0), the direction of
    // the cylinder/cone axis is used.
    //
    ///////////////////////////////////////////////////////////////////////////

    static Body box         (const Point3d&  corner, 
                             const Vector3d& sizes);

    static Body sphere      (const Point3d&  center, 
                             double          radius,
                             int             approx);  
    
    static Body cylinder    (const Line3d&   axis, 
                             double          radius, 
                             int             approx);

    static Body cylinder    (const Line3d&   axis, 
                             const Vector3d& baseNormal,
                             double          radius, 
                             int             approx);

    static Body cone        (const Line3d&   axis, 
                             double          radius1,  
                             double          radius2,  
                             int             approx);

    static Body cone        (const Line3d&   axis, 
                             const Vector3d& baseNormal,
                             double          radius1,  
                             double          radius2,  
                             int             approx);

    static Body torus       (const Line3d&   axis,     
                             double          majorRadius,  
                             double          minorRadius,  
                             int             majorApprox, 
                             int             minorApprox);

    static Body pipe        (const Line3d&   axis, 
                             double          outerRadius, 
                             double          innerRadius, 
                             int             approx);

    static Body pipe        (const Line3d&   axis, 
                             const Vector3d& baseNormal,
                             double          outerRadius, 
                             double          innerRadius, 
                             int             approx);

    static Body pipeConic   (const Line3d&   axis, 
                             double          outerRadius1, 
                             double          innerRadius1, 
                             double          outerRadius2, 
                             double          innerRadius2, 
                             int             approx);

    static Body pipeConic   (const Line3d&   axis, 
                             const Vector3d& baseNormal,
                             double          outerRadius1, 
                             double          innerRadius1, 
                             double          outerRadius2, 
                             double          innerRadius2, 
                             int             approx);

    static Body tetrahedron (const Point3d&  p1, 
                             const Point3d&  p2, 
                             const Point3d&  p3, 
                             const Point3d&  p4);

    static Body reducingElbow(const Point3d& elbowCenter,
                             const Point3d&  endCenter1,
                             const Point3d&  endCenter2,
                             double          endRadius1,
                             double          endRadius2,
                             int             majorApprox,
                             int             minorApprox);

    static Body rectangleToCircleReducer
                            (const Point3d&  baseCorner, 
                             const Vector2d& baseSizes,
                             const Circle3d& topCircle,
                             int             approx);

    // Returns a body which is the convex hull of the given set of points.
    // This can be used to easily create a convex body by only specifying 
    // coordinates of its vertices.
    //
    static Body convexHull  (const Point3d   pts[], 
                             int             numPoints);

    // Returns a body which is the convex hull of the body. The original body
    // is left unchanged.
    //
    Body convexHull() const;


    ///////////////////////////////////////////////////////////////////////////
    //                          Sweeps
    // Notes:
    //
    // The description of the PolygonVertexData class can be found in the 
    // "vertdata.h" file.
    //
    // The polygon normal vector is needed to determine the orientation of arcs.
    //
    // The approximation, given as an argument to Body::axisRevolution() and
    // Body::endpointRevolution() means the approximation of the whole 2*pi
    // angle. If the revolution is less than 2*pi, the number of generated
    // segments will be proportionally smaller.
    //
    // The scaleFactor and twistAngle optional arguments allow the profile to
    // be scaled/rotated while being extruded. The scaleTwistFixedPt is the  
    // center of the scaling/rotation and must lie in the profile polygon plane.
    ///////////////////////////////////////////////////////////////////////////

    // Extrudes the given profile polygon along the extrusionVector
    //
    static Body extrusion     (const Point3d      plg       [], 
                               PolygonVertexData* vertexData[],
                               int                numVertices,   
                               const Vector3d&    plgNormal,
                               const Vector3d&    extrusionVector,
                               const Point3d&     scaleTwistFixedPt,
                               double             scaleFactor,
                               double             twistAngle  = 0.0);

    static Body extrusion     (const Point3d      plg       [], 
                               PolygonVertexData* vertexData[],
                               int                numVertices,   
                               const Vector3d&    plgNormal,
                               const Vector3d&    extrusionVector);

    // Extrudes the given profile polygon to the point pyramidApex
    //
    static Body pyramid       (const Point3d      plg       [], 
                               PolygonVertexData* vertexData[],
                               int                numVertices, 
                               const Vector3d&    plgNormal,
                               const Point3d&     pyramidApex);

    // Revolves the given profile polygon around the given axis
    //
    static Body axisRevolution(const Point3d      plg       [], 
                               PolygonVertexData* vertexData[],
                               int                numVertices,       
                               const Vector3d&    plgNormal,
                               const Line3d&      axis, 
                               double             revolutionAngle,
                               int                approx,
                               const Point3d&     scaleTwistFixedPt,
                               double             scaleFactor,
                               double             twistAngle = 0.0);

    static Body axisRevolution(const Point3d       plg      [], 
                               PolygonVertexData* vertexData[],
                               int                numVertices,       
                               const Vector3d&    plgNormal,
                               const Line3d&      axis, 
                               double             revolutionAngle,
                               int                approx);

    // Revolves the given profile polygon about the axis defined by the first 
    // and the last point of the profile
    //
    static Body endpointRevolution(
                               const Point3d      plg       [], 
                               PolygonVertexData* vertexData[],
                               int                numVertices,  
                               const Vector3d&    plgNormal,
                               double             revolutionAngle,
                               int                approx);

    // The extrusionAlongPath() method creates a body by extruding the given
    // startProfile along the given path. If the endProfile is provided, the
    // startProfile gradually morphs its shape and topology to the endProfile 
    // while being extruded. The start and end profiles are left unchanged
    // by the operation.
    //
    // The profiles are bodies containing a single face. The normal of the
    // profiles must point in the direction of the path. To easily create the 
    // profiles, please see the face constructors in file 'inc\face.h', mainly
    // the constructor which creates a face from an augmented polygon.
    //
    // The start point of the path must lie in the plane of the startProfile 
    // and, if the endProfile is provided, the end point of the path must 
    // lie in the plane of the endProfile.
    //
    // The profile may also be scaled and twisted while being extruded, the
    // center of scaling/twist being scaleTwistFixedPt.
    //
    // The optional morphingMap argument specifies how the topology of the
    // startProfile morph to the topology of the endProfile. For the 
    // description of the MorphingMap class, see file 'inc\morphmap.h'.
    //
    // If pathIsClosed, the scaleFactor must be 1 and the twistAngle must be
    // either 0 or a multiple of 2*pi.
    //
    // If checkBodyValidity is true, the resulting body is checked and if it 
    // looks like self-intersecting, an exception is thrown. However, this test 
    // is not perfect, it may reject some valid but distorted bodies, or, on 
    // the other hand, do not reject some invalid or degenerated bodies.
    //
    static Body extrusionAlongPath(
                              const Body&        startProfile,
                              const Body&        endProfile,
                              const Point3d      pathPlg       [], 
                              PolygonVertexData* pathVertexData[],
                              int                pathNumVertices,
                              bool               pathIsClosed,
                              bool               checkBodyValidity = true,
                              const Point3d&     scaleTwistFixedPt = Point3d::kNull,
                              double             scaleFactor       = 1.0,
                              double             twistAngle        = 0.0,
                              const MorphingMap& morphingMap = MorphingMap::kNull);

    // The skin() method creates a body which covers the given set of profiles 
    // (cross-sections). If !isClosed, the first and the last profile will be 
    // the caps of the created body, otherwise the body will be closed, 
    // a torus-like shape. The input profiles are left unchanged.
    //
    // Each profile is a body containing a single face. The direction of the
    // face normal is important, each face normal should point in the direction
    // of the next profile. To create the profiles, please see the face 
    // constructors in file 'inc\face.h', mainly the constructor which creates 
    // a face from an augmented polygon.
    //
    // The checkPlanarity argument specifies whether the generated faces should
    // be checked for the planarity and broken into triangles if not planar.
    // Do not check the planarity only if you are absolutely sure that all the 
    // generated faces are planar.
    //
    // The morphingMaps array defines the topology morphing between the 
    // individual profiles. The first MorphingMap in the array specifies the
    // morphing between the first and second profile, etc. For the description
    // of the MorphingMap class, see file 'inc\morphmap.h'.
    // 
    // The Edge::eptr pointers in the edges of the input profiles will at the
    // end point to the coresponding edges of the created skin body. This can 
    // be used to identify which edges in the resulting body correspond to 
    // which profiles.
    //
    static Body skin          (Body*              profiles[],
                               int                numProfiles,
                               bool               isClosed,
                               bool               checkPlanarity,
                               MorphingMap**      morphingMaps = NULL);


    ///////////////////////////////////////////////////////////////////////////
    //                       Hidden-line display
    // Notes:
    //
    // The Body::hideDisplay() method displays a list of bodies linked by their 
    // Body::next() pointers. The method must be called for the first body in 
    // the list.
    //
    // The projectionTransf is the projection transformation which is used to 
    // project the body. It may either be a parallel or perspective projection. 
    // See the Transf3d class (file "transf3d.h") for the various ways of 
    // defining projections.
    //
    // The OutputPolylineCallback is a pointer to a callback object whose method
    // is called to output visible and hidden line segments. See the "callback.h" 
    // file for the definition of the abstract base class OutputPolylineCallback  
    // and the "dxfout.h" and "dxfout.cpp" files for a sample callback class.
    //
    // The outputProjectedCoords input arguments specifies whether the 
    // coordinates returned to the callback methods should be projected by the
    // projecionTransf or whether they should be the original non-projected
    // coordinates (e.g. to be fed to the AcGiViewportDraw object).
    //
    // The HiddenLineDrawingImprove argument specifies whether the resulting
    // drawing should be cleaned up to produce a better quality output drawing.
    //
    // The possible levels are:
    //
    //  kNoDrawingImprove             ... No drawing improvement is performed,
    //                                    the output from the Body::hideDisplay()
    //                                    method is a bunch of line segments.
    //
    //  kConnectDrawingImprove        ... If line segments share an endpoint, 
    //                                    they are conected to a polyline. If 
    //                                    segments overlap, the bottom segments
    //                                    are trimmed or removed.
    //
    //  kArcReconstructDrawingImprove ... The same as above but also tries to
    //                                    reconstruct arcs and circles from 
    //                                    polygons which represent arcs/circles.
    //                                    
    ///////////////////////////////////////////////////////////////////////////

    void hideDisplay   (const Transf3d&            projectionTransf, 
                        OutputPolylineCallback*,
                        bool                       outputProjectedCoords = true,
                        HiddenLineDrawingImprove = kNoDrawingImprove);

    // Saves the hidden-line drawing directly to a DXF file
    //
    void hideDisplayDxf(const Transf3d&            projectionTransf, 
                        const char*                dxfFileName,
                        bool                       outputProjectedCoords = true,
                        HiddenLineDrawingImprove = kNoDrawingImprove);
                                                                            
    // Sets the edge visibility characteristics
    //
    void setHiddenLineParams
                (HiddenLinesDisplay hiddenLinesDisplay = kHiddenLinesInvisible,
                 bool               displayApproxEdges = false,
                 bool               displayBridgeEdges = false);


    ///////////////////////////////////////////////////////////////////////////
    //                      Picking vertices, edges, faces
    // Notes:
    //
    // Vertices, edges, and faces of bodies can be picked after their bodies 
    // have been projected and displayed by calling the Body::hideDisplay() 
    // method. You must do this before the bodies are modified.
    //
    // The pickPoint and aperture input arguments are expressed in the 
    // coordinate system of the projected body (see the projectionTransf 
    // argument to Body::hideDisplay() method).
    //
    // - Vertices are picked by positioning the pickPoint over the vertex.
    //
    // - Edges are picked by positioning the pickPoint over the edge.
    //
    // - Faces are picked by positioning the pickPoint to lie inside the face.
    //
    // - Bodies are picked by positioning the pickPOint inside any body face.
    //
    // The methods return pointer to the topological entity (Vertex, Edge, Face, 
    // Body) which in the projection overlaps the aperture square (square whose 
    // center in at pickPoint and size is 'aperture') and which is closest to
    // the view point. The optional output Body argument is used to return the 
    // pointer to the body which contains the returned picked entity. Notice 
    // that the Body::hideDisplay() method may be used to display a whole list 
    // of bodies and therefore it is needed to know which body the picked 
    // entity belongs to.
    ///////////////////////////////////////////////////////////////////////////
    
    Vertex* pickVertex(const Point3d& pickPoint, double aperture, Body** bPicked=NULL) const;
    Edge*   pickEdge  (const Point3d& pickPoint, double aperture, Body** bPicked=NULL) const;
    Face*   pickFace  (const Point3d& pickPoint, double aperture, Body** bPicked=NULL) const;
    Body*   pickBody  (const Point3d& pickPoint, double aperture                     ) const;


    ///////////////////////////////////////////////////////////////////////////
    //                          Triangulation
    // Notes:
    //
    // The OutputTriangleCallback is a pointer to a callback object whose 
    // method is called to output the individual triangles or quadrilaterals. 
    // See file callback.h for the definition of the abstract base class 
    // OutputTriangleCallback and files dxfout.h and dxfout.cpp for a sample 
    // callback class.
    //
    // The TriangulationType specifies what type of output is going to be
    // generated. Currently it may be triangles, quadrilaterals or triangle 
    // strips.
    //
    // The cacheTriangles Boolean argument specifies whether the evaluated 
    // triangles are to be be cached so that the next time they are needed, 
    // they are quickly read from the cache instead of reevaluated from
    // the model. 
    ///////////////////////////////////////////////////////////////////////////

    void triangulate   (OutputTriangleCallback*, 
                        TriangulationType type = kGenerateTriangles,
                        bool cacheTriangles    = true) const;

    // Saves the triangles directly to a DXF file
    //
    void triangulateDxf(const char* dxfFileName, 
                        TriangulationType type = kGenerateTriangles,
                        bool cacheTriangles    = true) const;

    // Breaks the given face into several triangular faces. This method can be
    // used, for example, to break faces into triangles before the faces become
    // non-planar (the face must be triangularized before it becomes 
    // non-planar, otherwise, when the face already is non-planar, the 
    // triangularization would not work).
    //
    // The newly created triangular faces and edges will inherit its color from 
    // the original face.
    //
    void triangulateFace(Face*);

    // Use this method with caution. It will create a large number of 
    // triangular faces which are not memory efficient.
    //
    void triangulateAllFaces();


    ///////////////////////////////////////////////////////////////////////////
    //                          Save, restore, print
    ///////////////////////////////////////////////////////////////////////////

    void        save   (FILE*)                const;
    void        save   (SaveRestoreCallback*) const;

    static Body restore(FILE*);                 // Returns a newly created body
    static Body restore(SaveRestoreCallback*);  // Returns a newly created body

    void        print  (FILE* = NULL) const;    // FILE* == NULL ==> stdout
    

    ///////////////////////////////////////////////////////////////////////////
    //                      Other modifications
    ///////////////////////////////////////////////////////////////////////////

    // Merges coincident vertices and then links edges sharing common vertices
    // so that they are linked via their partner pointers. It does not try to 
    // reorient the faces to make each real edge shared by antiparallel edges.
    // 
    // This method can be used, for example, to create a body as a collection 
    // of individual non-connected faces and calling the stitchFaces() method 
    // to created the proper topological structure.
    //
    void stitchFaces();

    // Merges coplanar faces and collinear edges to produce a smaller model. 
    // Faces are merged only if the common edge is a bridge edge and both faces 
    // have the same color. Edges are merged only if they have the same color.
    // Boolean operations already call this method, no other operations, e.g.
    // sweeps do.
    //
    void mergeCoplanarEntities();

    // Copy the geometry (vertex coordinates and surface equations) from a 
    // given body this body, optionally transforming the geometry by the given 
    // transform. The two bodies must be topologically identical.
    //
    // This method can be used to help implement efficient dragging when the 
    // topology of the body stays the same but the geometry changes with each 
    // drag.
    //
    // Note: We do not transform the surfaces yet. We might either transform
    //       them or replace them with UnspecifiedSurfaces. TBD
    //
    void copyGeomFrom(const Body&, const Transf3d& = Transf3d::kIdentity);

    // Changes the coordinates of the selected vertices. The vertices are
    // identified by their positions in the vertex list of the body, the first
    // vertex being number 0, etc.
    //
    // If checkPlanarity is true and changing vertex coordinates would make
    // some faces non-planar, these faces are first triangulated. However, it
    // is still very easy to create an invalid body by this method so use this
    // method with care.
    //
    // The face surfaces are not modified (TBD).

    void changeVertexCoordinates(int     vertexIndices       [],
                                 Point3d newVertexCoordinates[],
                                 int     numVertices,
                                 bool    checkPlanarity = true);

    
    ///////////////////////////////////////////////////////////////////////////
    //                          Set color
    // Note:
    //
    // Faces and Edges have a color attribute. The color does not have any 
    // meaning to the modeler, it is just an integer number (an enum).
    ///////////////////////////////////////////////////////////////////////////

    void setColor (Color);    // Set color of all faces and edges of the body


    ///////////////////////////////////////////////////////////////////////////
    //                          Linking bodies
    // Note: 
    //
    // Linear list of bodies, currently used only when bodies are linked for 
    // display.
    ///////////////////////////////////////////////////////////////////////////

    Body*    next             () const     { return mpNext; }
    void     setNext          (Body* nxt)  { mpNext = nxt;  }


    ///////////////////////////////////////////////////////////////////////////
    //                  Counting topological entities
    ///////////////////////////////////////////////////////////////////////////

    int      vertexCount  () const;
    int      edgeCount    () const;  
    int      faceCount    () const;
    int      surfaceCount () const;
    int      curveCount   () const;
    int      triangleCount() const;


    ///////////////////////////////////////////////////////////////////////////
    //                          Body predicates
    ///////////////////////////////////////////////////////////////////////////

    bool     isNull           () const     { return mpFaceList == NULL; }
    bool     isNegated        () const     { return !!isFlagOn(NEGBF);  } 
    bool     isValid          () const;


    ///////////////////////////////////////////////////////////////////////////
    //                      Topology access methods 
    ///////////////////////////////////////////////////////////////////////////

    Face*    faceList         () const     { return mpFaceList;    }
    Surface* surfaceList      () const     { return mpSurfaceList; }
    Curve*   curveList        () const     { return mpCurveList;   }
    Vertex*  vertexList       () const     { return mpVertexList;  }

    void     setFaceList      (Face*    f) { mpFaceList    = f;    }
    void     setSurfaceList   (Surface* s) { mpSurfaceList = s;    }
    void     setCurveList     (Curve*   c) { mpCurveList   = c;    }
    void     setVertexList    (Vertex*  v) { mpVertexList  = v;    }

    void     addFace          (Face*   );
    void     addSurface       (Surface*);
    void     addCurve         (Curve*  );
    void     addVertex        (Vertex* );


    ///////////////////////////////////////////////////////////////////////////
    //                          And the rest 
    ///////////////////////////////////////////////////////////////////////////

    const Interval3d& interval() const;  // Obtain body interval (bounding box) 

    void evaluateVertexSurfaceData  () const;
    void deleteVertexSurfaceData    () const;

    void setAEFAndBEFFlags          ();
    void deleteFaceIntervals        () const;
    void deleteFaceIntervalsAndPlanes() const;

    void deleteMarkedFaces          (Flag);
    void deleteMarkedSurfaces       (Flag);
    void deleteMarkedCurves         (Flag);
    void deleteMarkedVertices       (Flag);

    void setFaceFlags               (OnOff, Flag) const;
    void setSurfaceFlags            (OnOff, Flag) const;
    void setCurveFlags              (OnOff, Flag) const;
    void setEdgeFlags               (OnOff, Flag) const;
    void setVertexFlags             (OnOff, Flag) const;

private:

    Face*      mpFaceList;     // Linear list of all faces
    Surface*   mpSurfaceList;  // Linear list of all surfaces
    Curve*     mpCurveList;    // Linear list of all curves
    Vertex*    mpVertexList;   // Linear list of all vertices
    Body*      mpNext;         // Next body, currently used only by hideDisplay()

    Interval3d mInterval;      // Enclosing interval of the body

    TriangleCache* mpTriangleCache; 

};  // class Body


// Externs of out-of-class operators
//
extern Body                operator * (const Transf3d&,      Body&); 
extern PointInBodyLocation operator &&(const Point3d&, const Body&);


AMODELER_NAMESPACE_END
#endif

