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

#ifndef AMODELER_INC_BODY_H
#define AMODELER_INC_BODY_H


#pragma warning(push)
#pragma warning(disable : 4702) // unreachable code
#include <vector>
#pragma warning(pop)
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
    //
    // Notice the setKeepInputBodiesWhenBooleanOperationsFail() global
    // function that controls whether the input bodies are or are not preserved
    // when the Boolean operations fail.
    ///////////////////////////////////////////////////////////////////////////

    Body boolOper(Body&, BoolOperType, bool hideZeroSlopeEdges = true, TopologyChangeCallback* = NULL, bool keepInputBodiesWhenFails = keepInputBodiesWhenBooleanOperationsFail());

    // The section method removes part of the body in the positive halfplane
    //
    void section(const Plane&, bool keepInputBodyWhenFails = keepInputBodiesWhenBooleanOperationsFail());

    // The section method removes part of the body in the positive halfplane.
    // Unlike the method above, if the part of the body that is to be removed
    // consists of several lumps (disjoint closed volumes), it only removes one
    // of the lumps, the lump whose one vertex is closest to the given point
    //
    void section(const Plane&, const Point3d& point, bool keepInputBodyWhenFails = keepInputBodiesWhenBooleanOperationsFail());

    // The slice method slices the body with a plane and returns all the loops
    // that result from the slicing. If everything goes OK, this method returns 
    // true. If any kind of problem happens, instead of throwing an exception, 
    // it returns false but it still tries to generate and return as many loops 
    // as possible, so that the client code gets at least something. An exception 
    // is thrown only if something seriously bad happens, not when some loops 
    // cannot be generated.
    //
    // The outputVertices contains coordinates of all vertices of all loops.
    // Some vertices may be shared by several loops.
    //
    // The outputLoops vector contains the description of the generated loops.
    // The outer (positive) loops are oriented CCW wrt the slicing plane normal.
    // The inner (negative) loops represent holes in outer loops and are 
    // oriented CW. The loops follow the rule of valid edge loops in AModeler,
    // i.e. each loop bounds a single contiguous area. The loops do not intersect
    // but they may touch at vertices, both touch each other or self-touch.
    // The loops do not contain any bridge edges. 
    // 
    // In the outputLoops vector each outer loop may optionally be followed by
    // one or more inner loops that represent holes in the outer loop. The
    // format is as follows:
    //
    // - number of outer loop vertices (stored as a positive number)
    // - outer loop vertex index 
    // - outer loop vertex index
    // - ...
    // - number of inner loop vertices (stored as a negative number)
    // - inner loop vertex index
    // - inner loop vertex index
    // - ...
    // - number of inner loop vertices (stored as a negative number)
    // - inner loop vertex index
    // - inner loop vertex index
    // - ...
    // - ...
    // - number of outer loop vertices (stored as a positive number)
    // - ...
    //
    bool slice(const Plane&, std::vector<Point3d>& outputVertices, std::vector<int>& outputLoops) const;

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

    // Returns a point on the boundary of this body that is closest to the
    // given testPoint. Also returns the pClosestEntity the closest point lies 
    // on (it may be a vertex, an edge or a face entity). If the body is null,
    // pClosestEntity is set to NULL and (0,0,0) is returned.
    //
    Point3d closestPointOnBody(Point3d testPoint, Entity*& pClosestEntity) const;

    // Classifies the line segment (startPoint, endPoint) against the body. 
    // It breaks the line segment into fragments and for each fragment returns
    // its classification wrt the body, i.e. whether the fragment lies outside
    // the body, on an edge/face of the body or inside the body.
    // 
    // The first element of the fragmentPoints vector is the startPoint, the
    // last element is the endPoint, the other elements are points where the
    // line segment intersects the boundary of the body.
    //
    // The fragmentClassifications returns the classifications of the individual
    // fragments. The length of this vector is one less than the length of the
    // fragmentPoints vector. Each fragment is represented by:
    //
    // Start point of the fragment:    fragmentPoints[i]
    // End   point of the fragment:    fragmentPoints[i+1]
    // Classification of the fragment: fragmentClassifications[i]
    //
    void classifyLineSegment(const Point3d&                    startPoint, 
                             const Point3d&                    endPoint, 
                             std::vector<Point3d>&             fragmentPoints,
                             std::vector<PointInBodyLocation>& fragmentClassifications);

    // Returns true iff the given plane intersects or touches the body
    //
    bool planeIntersectsBody(const Plane&) const;

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

    enum torus_type { DONUT_TORUS, APPLE_TORUS, LEMON_TORUS, VORTEX_TORUS };

    static Body torus_extension(
                             const Line3d&   axis, 
                             double          majorRadius,   
                             double          minorRadius,  
                             int             majorApprox, 
                             int             minorApprox);

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
                               double             twistAngle = 0.0);

    static Body extrusion     (const Point3d      plg       [], 
                               PolygonVertexData* vertexData[],
                               int                numVertices,   
                               const Vector3d&    plgNormal,
                               const Vector3d&    extrusionVector);

    static Body extrusion     (const Point3d      plg       [], 
                               PolygonVertexData* vertexData[],
                               int                numVertices,   
                               const Vector3d&    plgNormal,
                               const Vector3d&    extrusionVector,
                               const std::vector<void*>*    attribs);

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

    static Body axisRevolution(const Point3d      plg       [], 
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
    // If pathIsClosed, the scaleFactor must be 1 and the twistAngle must be
    // either 0 or a multiple of 2*pi.
    //
    // If checkBodyValidity is true, the resulting body is checked and if it 
    // looks like self-intersecting, an exception is thrown. However, this test 
    // is not perfect, it may reject some valid but distorted bodies, or, on 
    // the other hand, do not reject some invalid or degenerated bodies.
    //
    // The optional morphingMap argument specifies how the topology of the
    // startProfile morph to the topology of the endProfile. For the 
    // description of the MorphingMap class, see file 'inc\morphmap.h'.
    //
    static Body extrusionAlongPath(

        const Body&             startProfile,
        const Body&             endProfile,
        const Point3d           pathPlg       [], 
        PolygonVertexData*      pathVertexData[],
        int                     pathNumVertices,
        bool                    pathIsClosed,
        bool                    checkBodyValidity                 = true,
        const Point3d&          scaleTwistFixedPt                 = Point3d::kNull,
        double                  scaleFactor                       = 1.0,
        double                  twistAngle                        = 0.0,

        // MorphingMap related arguments
        //
        const MorphingMap&      morphingMap                       = MorphingMap::kNull,
        bool                    calcluateMorphingMapAutomatically = false,
        std::vector<int>        startProfileSignificantVertices   = std::vector<int>(), 
        std::vector<int>        endProfileSignificantVertices     = std::vector<int>());

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
    // If markInnerProfileEdgesAsApprox is true, the edges corresponding to the
    // inner profiles (all profiles except the first and the last one if
    // isClosed is false, or all profiles, if isClosed is true), will be marked 
    // as approximating.
    //
    // If ckeckInputProfiles is false, the input profiles are not checked for
    // validity, otherwise they are.
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
                               MorphingMap**      morphingMaps                  = NULL,
                               bool               markInnerProfileEdgesAsApprox = false,
                               bool               ckeckInputProfiles            = true);


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
    // The optional HideIntegerTransform, if given and not NULL, is filled in 
    // with the transformation from projected integer to projected double
    // coordinates. This is needed as input to the subentity picking methods.
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
                        bool                     = true,
                        HiddenLineDrawingImprove = kNoDrawingImprove,
                        HideIntegerTransform*    = NULL); // Output argument, may be NULL

    // Saves the hidden-line drawing directly to a DXF file
    //
    void hideDisplayDxf(const Transf3d&            projectionTransf, 
                        const wchar_t*             dxfFileName,
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
    
    Vertex* pickVertex(const Point3d& pickPoint, double aperture, const HideIntegerTransform&, Body** bPicked=NULL) const;
    Edge*   pickEdge  (const Point3d& pickPoint, double aperture, const HideIntegerTransform&, Body** bPicked=NULL) const;
    Face*   pickFace  (const Point3d& pickPoint, double aperture, const HideIntegerTransform&, Body** bPicked=NULL) const;
    Body*   pickBody  (const Point3d& pickPoint, double aperture, const HideIntegerTransform&) const;


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
    void triangulateDxf(const wchar_t* dxfFileName, 
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

    void        save   (SaveRestoreCallback*) const;
    void        save   (FILE*)                const;
    void        save   (const wchar_t* fileName) const;

    static Body restore(SaveRestoreCallback*);  // Returns a newly created body
    static Body restore(FILE*);                 // Returns a newly created body
    static Body restore(const wchar_t* fileName);  // Returns a newly created body

    // Save to ACIS SAT text file. If colorsAlso is true, every face and edge 
    // receives a color-adesk-attrib
    //
    void        saveToSat(SaveToSatCallback*,   bool colorsAlso = false) const;
    void        saveToSat(FILE*,                bool colorsAlso = false) const;
    void        saveToSat(const wchar_t* fileName, bool colorsAlso = false) const;

    void        print  (FILE* = NULL) const;    // FILE* == NULL ==> stdout
     

    ///////////////////////////////////////////////////////////////////////////
    //                      Other modifications
    ///////////////////////////////////////////////////////////////////////////

    // Merges coincident vertices and then links edges sharing common vertices
    // so that they are linked via their partner pointers. It does not try to 
    // reorient the individual faces to make each real edge shared by 
    // antiparallel edges. However, when the volume of the resulting body is 
    // negative, it negates the whole body to make it positive.
    // 
    // This method can be used, for example, to create a body as a collection 
    // of individual non-connected faces and calling the stitchFaces() method 
    // to created the proper topological structure.
    //
    // If splitEdges is true, if there are some vertices lying on edges, the
    // edges are split by these vertices. If splitEdges is false and such
    // vertices exist, the resulting body will be invalid because it is not 
    // allowed for vertices to lie inside edges.
    //
    // If orientFaces is true, the code tries to consistently orient all the 
    // faces so that the result is a valid B-Rep of a solid body. If orientFaces
    // is false, the faces are assumed to be already correctly oriented.
    //
    // If addMissingFaces is true, the code tries to add new faces when there
    // are gaps in the boundary, i.e. when there are edges shared by only one
    // face. The new faces are added only if all the gaps can be successfully
    // covered by newly added planar faces. If at least one gap cannot be
    // covered, no new faces are added.
    //
    void stitchFaces(bool splitEdges = false, bool orientFaces = false, bool addMissingFaces = false);

    // Merges coplanar faces and collinear edges to produce a smaller model.
    // Boolean operations already call this method, no other operations, e.g.
    // sweeps do.
    //
    // If bridgeEdgesOnly is true, the common edges between the faces being
    // merged must be bridge edges, otherwise the faces are not merged. 
    // If sameColorOnly is true, the merged faces and edges must have the 
    // same color, otherwise they are not merged
    //
    void mergeCoplanarEntities(bool bridgeEdgesOnly    = true,
                               bool sameColorOnly      = true,
                               TopologyChangeCallback* = NULL);

    // The face of this edge is preserved, the face of the partner edge is
    // deleted
    //
    void mergeCoplanarFaces(Edge* pEdgeBetweenFaces);

    // Finds surfaces that are geometrically equal and leaves just one surface
    // for each group of equal surface objects
    //
    void mergeEqualSurfaces();

    // Adjusts the facets resulting from the tessellation of arcs in "this" 
    // extrusion body so that the facets cleanly coincide with the corresponding
    // arc tessellation facets in the referenceExtrusion body. The reason for 
    // this adjustment is to make the subsequent Boolean operations between 
    // these two extrusion bodies succeed; without this adjustment the Boolean 
    // operations might frequently fail because some of the facets might almost 
    // coincide but not cleanly enough to be considered exactly coincident.
    //
    // An explanation: When arcs are tessellated, the tessellation is done as
    // if a whole circle was tessellated and then the portion of the tessellated
    // polygon that belongs to the arc was cut off. The start point of the first 
    // tessellated segment and the end point of the last tessellated segment are 
    // then moved to lie on the exact circle, so that the tessellated polygon 
    // starts and ends at the same points as the exact arc does. 
    //
    // When two overlapping arcs with the same centers and radii, but different 
    // start and end angles are tessellated, the tessellated segments of the two 
    // arcs cleanly overlap except for the first and the last segment of each 
    // tessellated arc, because their start/end points have been moved to lie
    // on the exact circle. These segments then cause problems when Boolean 
    // operations are performed with bodies created by extruding profiles 
    // containing such overlapping arcs, because these segments are almost 
    // coincident with segments of the other arc , but not cleanly enough to 
    // be considered exactly coincident. This method tries to fix these cases
    // by making all tessellated segments of the corresponding arcs exactly 
    // coincident.
    //
    // This body as well as the referenceExtrusion body must be bodies created
    // as simple linear extrusions. They must not contain any holes but may 
    // contain multiple lumps. The extrusion vectors and the profiles of the 
    // two extrusions must be parallel, but not identical, i.e. the extrusion 
    // vectors may have a different lengths and the profiles need not lie in
    // the same plane.
    //
    // This body may be modified by this method. If it is modified, it is 
    // guaranteed that it passes the Body::isValid(1) check. The result of the 
    // operation is indicated by:
    //
    //  changedSomething    ... True iff this body was modified.
    //  everythingSucceeded ... False iff some facets they should be adjusted 
    //                          might be left not adjusted.
    //
    // Note: This method is rather complex. Use it only if really necessary
    // and make sure the two bodies are really only simple extrusions, not 
    // general bodies.
    //
    void makeArcTessellationsInExtrusionsCoincide(const Body&     referenceExtrusion, 
                                                  const Vector3d& extrusionVector, // Of this extrusion body
                                                  bool&           changedSomething,
                                                  bool&           everythingSucceeded);

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

    // Changes the coordinates of the selected vertices. If checkPlanarity is 
    // true and changing vertex coordinates would make some faces non-planar, 
    // these faces are first triangulated. However, it is still very easy to 
    // create an invalid body by this method so use this method with care.
    //
    // The face surfaces are not modified (TBD).
    //
    void changeVertexCoordinates(Vertex* changedVertices         [],
                                 Point3d changedVertexCoordinates[],
                                 int     numChangedVertices,
                                 bool    checkPlanarity = true);

    // Extracts the shell (a connected manifold set of faces) that contains the 
    // given face from the body and returns it in a new body by moving the 
    // topological entities from this body to the new body. Only topological 
    // entities that cannot be moved because they are also needed in this body 
    // are copied and not moved.
    //
    // If no face is given, it extract the shell that contains the first face
    // in the body.
    //
    // Notice that the returned body may be negative if the extracted shell
    // represents a cavity
    //
    Body extractShell(Face* pFaceInTheShell = NULL);

    // Extracts a single face from the body and returns it in a new body by 
    // moving it and the corresponding edges from this body to the new body
    // and cloning the corresponding vertices to the new body. Surfaces and 
    // curves are neither moved nor cloned and the extracted face loses the 
    // surface and curve data.
    //
    // If this body contains zero or one face, this body is simply returned 
    // and no face extraction is executed because it is not needed.
    //
    // If no face is given, it extracts the first face in the body.
    //
    // The returned body is a profile body and can be used as an input to
    // extrusions and similar operations
    //
    Body extractFace(Face* pFaceToExtract = NULL);

    // Decomposes the body into one or more lump bodies. A "lump" is a body 
    // that represents a single contiguous 3D volume. It is always bounded by 
    // a single outer shell and possibly by several inner shells that represent 
    // cavities. This body then becomes empty
    //
    void decomposeIntoLumps(std::vector<Body*>& lumpBodies);

    // Moves pFaceToMove along the given vector in the direction of the face 
    // normal. 
    // 
    // If the method succeeds, the body is modified. If it cannot perform the
    // move because it would result in an invalid body, an exception is thrown
    // and the body becomes empty (this is just to make the implementation of
    // this method more efficient).
    //
    // The pointer to the face after being moved is returned in 
    // pFaceToMoveAfterMove. It may be a different pointer than the original 
    // pFaceToMove because the face might have been merged with another face,
    // for example. If the method didn't succeed, the pointer is set to NULL.
    // 
    // The two Boolean arguments define the constraints that are preserved when 
    // the face is moved. This defines how the result of the move will look
    // like.
    //
    // keepAdjacentFacePlanesFixed ... Constraints the planes of the faces 
    //   adjacent to the face being moved not to change, i.e. their slopes to
    //   remain fixed. Their edges may change, however, such as the faces may
    //   be stretched or shrunk.
    //
    // keepFaceGeometryFixed ... Constraints the geometry of the face being 
    //   moved to be fixed, i.e. the face is moved as rigid, only its location
    //   changes.
    //
    // There are four different possible combinations. They will now be
    // individually listed.
    //
    // - keepAdjacentFacePlanesFixed == false, keepFaceGeometryFixed == false:
    //
    //   The face is moved along the given vector, the angle between the vector
    //   and the face normal must be less than pi/2. Side faces are always added
    //   to connect the moved face with the rest of the body and these newly 
    //   added faces are not merged with the existing faces of the body, even 
    //   if they are coplanar with them.
    //
    //   (This first case does not naturally reflect the meaning of the two 
    //   Boolean constraints, but functionality like this was needed so I added
    //   it somehow forcefully. The remaining three cases logically reflect the 
    //   meaning of the two Boolean constraints).
    //
    // - keepAdjacentFacePlanesFixed == false, keepFaceGeometryFixed == true:
    //
    //   The face is moved along the given vector. The face geometry does not 
    //   change. The adjacent faces may get tilted, stretched or shrunk.
    //
    // - keepAdjacentFacePlanesFixed == true, keepFaceGeometryFixed == false:
    //
    //   The face is moved along the direction of its normal (the given vector
    //   is projected onto the face normal). When the face is moved, its 
    //   geometry may change depending on the slopes of planes of the adjacent
    //   faces. The planes of the adjacent faces remain fixed, but their 
    //   geometry may change, the faces may be stretched or shrunk. 
    //
    // - keepAdjacentFacePlanesFixed == true, keepFaceGeometryFixed == true:
    //   
    //   The face is moved along the direction of its normal (the given vector
    //   is projected onto the face normal). The face geometry does not change.
    //   The planes of the adjacent faces also remain fixed, but their geometry 
    //   may change, the faces may be stretched or shrunk. This option may
    //   cause additional side faces to be generated to satisfy both 
    //   constraints.
    //
    void moveFace(Face*           pFaceToMove,
                  const Vector3d& vector,
                  bool            keepAdjacentFacePlanesFixed,
                  bool            keepFaceGeometryFixed,
                  Face*&          pFaceToMoveAfterMove);

    // Traverses all faces of the body that have no surface attached and
    // faces that share edges and whose face plane normals differ by less than
    // the given angleTolerance are grouped by assigning the same newly created
    // UnspecifiedSurface to them. This way these grouped faces can be smooth 
    // shaded, for example. The minNumberOfFacesInSurface specifies the minimum 
    // number of faces in a group for which a new UnspecifiedSurface is generated. 
    // It must be at least two.
    //
    void generateUnspecifiedSurfaces(double angleTolerance, int minNumberOfFacesInSurface = 2);

    void generateUnspecifiedSurfacesFromApproxEdges(int minNumberOfFacesInSurface = 2);

    // Converts a body whose set of faces represents a terrain surface to 
    // a volumetric terrain body by adding vertical side faces and horizontal 
    // bottom faces so that the result is a well-formed body.
    //
    // The body must at the beginning contain a set of faces that define the 
    // surface of the terrain. The orientation of the faces does not matter,
    // and the edges of the individual faces do not need to be paired via their
    // partner edge pointers. But the set of faces must not contain any vertical 
    // faces and the projection of the outline of the terrain surface onto the
    // XY plane must form one or more loops. The projected loops represent both
    // the outer outlines as well as the inner outlines of (holes in) the 
    // terrain surface. The loops may touch at vertices, representing 
    // non-manifold conditions. 
    //
    // In other words, the terrain surface may consists of several contiguous 
    // regions that may contain holes and the regions as well as their holes 
    // may touch each other at non-manifold vertices.
    //
    // The terrain surface can easily be created by simply adding all the 
    // individual faces to the body by using the face constructors:
    //
    // Face(Point3d pts[], ...) or
    // Face(Vertex* vertices[], ...)
    //
    // The given height argument is the distance of the newly generated bottom
    // faces from the lowest vertex of the terrain surface. The bottomFaces
    // vector is an output argument that will contain the newly generated bottom
    // faces, in case the client application needs an access to them (there may
    // be generated more than one bottom face because the terrain surface faces
    // may form several contiguous regions).
    //
    // If checkValidity is true and the terrain body, generated from the set of
    // faces of the terrain surface, would be invalid, an exception is thrown.
    // An exception is also thrown when the operation cannot be completed, 
    // usually because the original terrain surface is invalid. In both cases, 
    // this body is emptied because it is invalid anyway.
    //
    void convertToTerrainBody(double              height, 
                              bool                checkValidity, 
                              std::vector<Face*>& bottomFaces);


    ///////////////////////////////////////////////////////////////////////////
    //                          Set color
    // Note:
    //
    // Faces and Edges have a color attribute. The color does not have any 
    // meaning to the modeler, it is just an integer number (an enum).
    ///////////////////////////////////////////////////////////////////////////

    void setColor(Color);    // Set color of all faces and edges of the body


    ///////////////////////////////////////////////////////////////////////////
    //                          Linking bodies
    // Note: 
    //
    // Linear list of bodies, currently used only when bodies are linked for 
    // display.
    ///////////////////////////////////////////////////////////////////////////

    Body*    next   () const     { return mpNext; }
    void     setNext(Body* nxt)  { mpNext = nxt;  }


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

    bool     isNull   () const     { return mpFaceList == NULL; }
    bool     isNegated() const     { return isFlagOn(NEGBF);    } 

    // The validity checking level means:
    //
    // 0 ... No checking.
    //
    // 1 ... Simpler topology and geometry checking, such as that faces are
    //       planar, have at least three edges, the edges are partners of 
    //       other edges, partner edges are antiparallel and point to the 
    //       correct vertices, etc.
    //
    // 2 ... Extensive topology and geometry checking, involving such complex
    //       operations as checking the face selfintersections, illegal face
    //       touching, illegal shell nesting, etc. These tests involve 
    //       performing algorithms similar to the Boolean operations algorithm.
    //
    // If the validity checking level is not given or is -1, the current default
    // level set by setValidityCheckingLevel() is used.
    //
    bool     isValid(int validityCheckingLevel = -1) const; 

    // Non-manifold edges, even if perfectly legal, may sometimes be an 
    // unintended result of some wrong operation, so we have a predicate to 
    // easily check for them
    //
    bool     containsNonManifoldEdges() const; 


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

    // Physical edges are, loosely said, what looks like individual linear edges
    // on the body when the body is displayed. This means edges marked with the 
    // "bridge" flag are skipped and also some sequences of collinear edges are 
    // returned as a single physical edge.
    // 
    // In particular, if there are several collinear connected visible (i.e. not
    // marked as bridge) AModeler edges, they are returned as a single physical 
    // edge (such split edges usually happen when, during a Boolean operation, 
    // a hole in a face is connected to the outer loop of the face via a pair of
    // bridge edges and these bridge edges split the edge of the outer loop).
    //
    // Physical vertices are such vertices that are at the ends of physical edges.
    //
    // The physicalEdges vector contains pointers to the first AModeler edges in
    // the sequences of AModeler edges that form the physical edges. 
    //
    // The following code accesses all AModeler edges of a physical edge and
    // also obtains the start and the end vertex of the physical edge:
    //
    //
    //     for (unsigned i = 0; i < physicalEdges.size(); i++)
    //     {
    //         Edge* const pPhysicalEdge = physicalEdges[i];
    //
    //         Vertex* pPhysicalEdgeStartVertex = pPhysicalEdge->vertex();
    //         Vertex* pPhysicalEdgeEndVertex;
    //
    //         Edge* e = pPhysicalEdge;
    //         do {
    //             // Process the AModeler edge e of the physical edge
    //
    //             if (e->eptr == NULL)
    //             {
    //                 pPhysicalEdgeEndVertex = e->next()->vertex();
    //             }
    //         } while ((e = e->eptr) != NULL);
    //     } // for
    //
    void getPhysicalEdgesAndVertices(bool                  wantPhysicalEdges, 
                                     bool                  wantPhysicalVertices,
                                     std::vector<Edge*>&   physicalEdges,
                                     std::vector<Vertex*>& physicalVertices);

    const Interval3d& interval(double enlargeBy = 10*epsAbs()) const;  // Obtain body interval (bounding box) 

    void evaluateVertexSurfaceData  () const;
    void deleteVertexSurfaceData    () const;

    void setAEFAndBEFFlags          (bool markEdgesBetweenCoplanarFacesAsBridge);
    void setAEFAndBEFFlags          (); // For DLL compatibility, equalvalent to setAEFAndBEFFlags(true)
    void deleteFaceIntervals        () const;
    void deleteFaceIntervalsAndPlanes() const;

    void removeFace                 (Face*); // Removes the face from the face list
    void deleteFace                 (Face*); // ... and also deletes it

    void deleteMarkedFaces          (Flag);
    void deleteMarkedSurfaces       (Flag); // Also deletes VertexSurfaceData pointing to them
    void deleteMarkedCurves         (Flag);
    void deleteMarkedVertices       (Flag);

    void deleteEmptyFaces           ();
    void deleteUnusedVerticesSurfacesCurves(); // Note: Reuses FLAG(31)

    void setFaceFlags               (OnOff, Flag) const;
    void setSurfaceFlags            (OnOff, Flag) const;
    void setCurveFlags              (OnOff, Flag) const;
    void setEdgeFlags               (OnOff, Flag) const;
    void setVertexFlags             (OnOff, Flag) const;

    // Merges distinct vertices with the same coordinates. Returns true if some 
    // vertices were merged or false if not
    //
    bool mergeCoincidentVertices();

    // Cleans up the body that was created by operations such as extrusion and
    // skin that simply process the data and generate a mesh. If the profile(s) 
    // being extruded or skinned contain non-manifold vertices, the resulting 
    // mesh will contain non-manifold edges that are not properly linked via 
    // the partner pointer. These edges need to be linked. Moreover, if the 
    // profile(s) being extruded contain bridge edges, the resulting mesh will 
    // contain pairs of exactly coincident faces. These pairs of faces need to 
    // be removed
    // 
    void cleanUpNonManifoldEdgesAndCoincidentFaces();

    // Utility method that simply collects all edges whose e->vertex() == v
    //
    void getAllEdgesReferencingVertex(const Vertex* v, std::vector<Edge*>&) const;

    void setInterval(const Interval3d&); // For internal use only

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


// Sets the default level of checking done by Body::isValid() predicate:
//
// 0 ... No checking.
//
// 1 ... Simpler topology and geometry checking, such as that faces are
//       planar, have at least three edges, the edges are partners of 
//       other edges, partner edges are antiparallel and point to the 
//       correct vertices, etc.
//
// 2 ... Extensive topology and geometry checking, involving such complex
//       operations as checking the face selfintersections, illegal face
//       touching, illegal shell nesting, etc. These tests involve 
//       performing algorithms similar to the Boolean operations algorithm.
//
// Returns the previous validity checking level value.
//
DllImpExp int setValidityCheckingLevel(int newLevel);

DllImpExp int getValidityCheckingLevel();

// NOTE Jiri Kripac: All AModeler method and function names start with lowercase 
// but Spatial added this function starting with uppercase. For DLL 
// compatibility reasons, I allow the old name also
//
#define SetValidityCheckingLevel setValidityCheckingLevel


AMODELER_NAMESPACE_END
#endif

