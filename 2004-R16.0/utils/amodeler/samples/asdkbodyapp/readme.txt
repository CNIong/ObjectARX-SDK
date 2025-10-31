AsdkBodyApp Sample

 (C) Copyright 1998,2000 by Autodesk, Inc.
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
 

To use these applications, amodeler.arx must be in the AutoCAD directory.
This is because of the simple way the modeler gets loaded. First the OS
must find it and second AutoCAD must find it for the acrxLoadModule("AModeler.arx",1); 
call to succeed.


 

