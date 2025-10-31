AsdkBodyApp Sample

//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

This sample demonstrates the use of AsdkAmodeler. The sample has two parts:

1. AsdkBodyObj.dbx
This defines a custom object AsdkBody and is loadable into any ObjectDBX host
application, including AutoCAD. The custom object provide wrappers around the
basic Amodeler body creation functions.

2. AsdkBodyApp.arx
This defines some custom commands to create and modify the AsdkBody objects.

    "AHELP",                &printHelp,                 "Display this command table",
    "ABOX",                 &createBox,                 "Create a Box", 
    "ASPHERE",              &createSphere,              "Create a Sphere", 
    "ACYLINDER",            &createCylinder,            "Create a Cylinder",
    "ACONE",                &createCone,                "Create a Cone",
    "APIPE",                &createPipe,                "Create a Pipe",
    "APIPECONIC",           &createPipeConic,           "Create a Pipe Conic",
    "ATETRAHEDRON",         &createTetrahedron,         "Create a Tetrahedron",
    "ATORUS",               &createTorus,               "Create a Torus",
    "AREDUCINGELBOW",       &createReducingElbow,       "Create a Reducing Elbow",
    "ARECTTOCIRCLEREDUCER", &createRectToCircleReducer, "Create a Circle Reducer",
    "ACONVEXHULL",          &createConvexHull,          "Create a Convex Hull",
    "AFACE",	            &createFace,                "Create a Face",
    "APYRAMID",             &createPyramid,             "Create a Pyramid",
    "AEXTRUDE",             &createExtrusion,           "Sweep along a straight line",
    "AAXISREVOLVE",         &createAxisRevolution,      "Sweep around an axis",
    "APATHEXTRUDE",         &createExtrusionAlongPath,  "Sweep along a path",
    "AUNION",               &aUnion,                    "Unite Two AsdkBodys", 
    "ASUBTRACT",            &aSubtract,                 "Subtract Two AsdkBodys",
    "AINTERSECT",           &aIntersect,                "Intersects AsdkBodys",
    "DOARRAY",              &doArray,                   "Do an Array operation",

Note: Some of these routines require an old style polyline to work properly.
 

To use these applications, aecmodeler60.dbx must be in the AutoCAD directory.
This is because of the simple way the modeler gets loaded. First the OS
must find it and second AutoCAD must find it for the acrxLoadModule("AecModeler60.dbx",1); 
call to succeed.

3. Additional Notes about input for the commands.

APYRAMID - This command creates a pyramid. When you run this command it first prompts to
select a profile to extrude. The profile is used for the base of the pyramid. This needs
to be a polyline with at least two segments. At the Fillet Radius <0.0> 
prompt you can enter a value to fillet the edges of the pyramid. The prompt "Enter the # of
lines to approximate are circle" is not used for the pyramid so just accept the default. The 
Apex point is the top point of the pyramid so this needs to be a 3D point above the polyline
profile.   

ATETRAHEDRON - This command creates a tetrahedron. When you run this command it prompts for 4
corners. At each prompt select a point. At least one of the points needs to be in a different
plane.

AREDUCINGELBOW - This command creates a 90 degree elbow. The "Elbow center:" prompt gets a point 
that defines the center of the arc that forms the elbow. (not on the elbow) The End one center 
and the End two center get points that need to be the same distance from the Elbow center. Also 
these points need to form a 90 degree triangle. The radius is used to control the shape of the
elbow. When first using this command it may help to use the grid to select the points. 

ARECTTOCIRCLEREDUCER - This command will create a shape that is similar to a pyramid. The base is 
a rectangular shape and the top is a circle shape instead of a point. At the "Base Corner" prompt
enter a corner of the base rectangle shape. At the "Base sizes" prompt enter a point that would form
the opposite corner that would create a rectangular shape. At the "Circle center" prompt enter a 
3d point that is above the rectangle area selected with the first two prompts.     

ACONVEXHULL - This command creates a shape that is controlled by at least 3 points. One of these points
needs to be in a different plane. When you first use this command it may help to draw a BOX and 
snap to points on the box to see how it works.  

AEXTRUDE - This command will create a body that use a polyline as the base. The polyline needs to
have at least two segments. The fillet radius is used to fillet the edges of the extrusion. 
The command gets an extrusion vector by selecting two points. To extrude in the Z direction 
enter 0,0,0 at the "Extrusion vector: Select point:" prompt and at the next "Select point" prompt
enter 0,0,1. The other user input is used to control the result of the extrusion. 
