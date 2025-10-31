
                                AModeler
                                ======== 
               
                          Faceted Solid Modeler


                              Revision 5.0


Installation
============
 
- Add the directory containing aecmodeler.dbx (normally the SDK's "redistrib"
  subdirectory) to your host app search path.

- The modeler has been compiled with Microsoft VC++ 8.0 compiler and is
  using Multithreaded DLL runtime library.


Overview
========

AModeler is a faceted solid modeling system. It provides the following 
functionality:

-  B-Rep data structure for the faceted representation of solid bodies.

-  Combination of bodies using the regularized Boolean operations -- union,
   intersection, and difference -- and sectioning bodies with a plane.

-  Perspective or parallel projection with hidden lines removed.

-  Box, cylinder, cone, sphere, torus, pipe, rectangleToCircleReducer, 
   convex hull and other primitives.

-  Set of sweep operations including general extrusion along the path, 
   allowing one profile to morph to another profile while being extruded. 
   Importing and sweeping 2D polylines from a DXF files.

-  Geometric transformations translation, rotation, scaling, stretching, and
   mirroring; general alignment of bodies in space.

-  Calculation of area, volume, centroid, moments of inertia and products of
   inertia for bodies; calculation of area, perimeter, and centroid for faces.

-  Checking interference of bodies; testing location of a point with respect
   to a body.

-  Picking entities (vertices, edges, faces, and bodies) in projected views.

-  Storing bodies in a native format; storing projected or triangulated bodies
   in DXF files.

-  Modern object-oriented software architecture.


File Structure
==============

The modeler is located in the "utils\amodeler" directory which contains the
following subdirectories:

inc            ... All the header files of the modeler. 

lib            ... File "aecmodeler.lib".

samples        ... Sample code asdkbodyapp demonstrating the
                            usage of the modeler.

docs           ... Picture of the B-Rep topological data structure
                            "topology.dwg" and this file "readme.txt".

The modeler's dbx "aecmodeler.dbx" is located in the SDK's redistrib directory.

The modeler is documented in the header files located in the "amodeler\inc"
subdirectory. To begin studying the system, start with the
"samples\asdkbodyapp\asdkbody.cpp" and "inc\body.h" files. These files contain
examples of the usage of the modeler and an overall description of the B-Rep
data structure. 

