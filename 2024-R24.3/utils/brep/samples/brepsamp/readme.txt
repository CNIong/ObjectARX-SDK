The Autodesk Boundary Representation Library Sample Application
---------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

Building brsample.arx:

An ObjectARX sample application for the Autodesk Boundary
Representation Library (brepsamp) is contained in the
ObjectARX\utils\brep\samples tree. The makefile
brsample.dsp is used to build the sample application.


Running brsample.arx:

The sample application is called brsample.arx, and is loaded
in the standard way using the "arx" command in AutoCAD. It
implements several commands:

BRDUMP exemplifies both upwards and downwards topological
traversal as well as extraction and evaluation of geometric
data from a solid model. In addition, the face-level dump shows
how to extract meaningful data from elliptic cones and cylinders
(which are not yet supported as valid AcGe objects and therefore
must be evaluated in order to infer defining data). All results
are annotated on the screen.

BRTRMSRF displays trimmed surface data, based on a face pick in
AutoCAD. This command generates informational error messages on
unbounded surfaces (planes, spheres, tori) and at the apex of a
cone, where no trimmed data exists. The trimmed surface may be
generated either as a true trimmed surface (which may be a
collection of faces, each mapped to AcGeExternalBoundedSurface),
or as a collection of nurb curves defining the boundary of a
nurb surface. All results are annotated on the screen.

BRBBLOCK returns the model space coordinates of the lower left
and upper right corners of the bounding box for the selected
subentity in the solid model. The results are annotated on the
screen.

BRPTCNT returns the containment of a selected point with respect
to the selected subentity in the solid model. The returned
containment type is annotated on the screen.

BRLNCNT returns the containment of a selected line with respect
to the selected subentity in the solid model. The information
from the returned array of AcBrHits is annotated on the screen.

BRMESH exemplifies mesh generation and queries the user for a
brep-level or face-level mesh. If a face-level mesh is chosen,
default mesh controls are chosen by the sample app based on
surface type. If a brep-level mesh is chosen, the user is
queried to provide the mesh controls themselves. The mesh is
displayed on the screen as a set of closed AutoCAD polylines,
or alternatively is annotated as coordinate data on enumerated
mesh elements and nodes.


The user is queried for local vs. database context. If database
context is selected (the default), standard AutoCAD entity
selection is used in all of the commands. Any selected entity
which is not an AcDb3dSolid, AcDbBody or AcDbRegion is rejected.

If local context is sslected, the user is next queried for
solid primitive type. An AcDb3dSolid is set to a unit size
primitive of the selected type, and is used without being
added to the database.

Points and lines may either be selected from the screen or
entered directly as coordinates. The latter will give more
accurate and predictable results.


The purpose of these registered commands is to familiarise people
with the behaviour of various functions within acbr24.dll, and
to exemplify proper usage of the functions in an integrated
environment.  Please note that if you wish to use acbr24.dll in
your own application you must load it by using acrxDynamicLinker
as in the sample app because acbr24.dll is an ARX application
with a .dll extension.

Particular attention is paid to how the library interacts with
libacge.dll to provide useful boundary data and definition data
for external curves and surfaces. The sample app is often used
to exemplify temporary workarounds for known problems in the
various modeling libraries that it interacts with.

The sample app should be thought of as a template for any serious
application requiring boundary information of a model. It is not
guaranteed to be perfect.  To submit questions, bug reports, or 
any feedback, please contact your normal development support 
channels.  For enhancement requests, suggestions or comments, 
feel free to contact mcad_api_enhance@autodesk.com.discussing 
problems or requesting additional examples or workarounds.
 

The Structure of the sample application code is as follows:

brsample.cpp
This is the main entry module for the sample application.

brdump.cpp
This is the top level code for the brdump command, which dumps
topological and geometric data associated with the selected solid
or subentity.

brbdump.cpp
This module contains the code for enumerating all the topological
elements of a solid object.

brfdump.cpp
This module contains the code for dumping the surface data
associated with a selected face subentity.

bredump.cpp
This module contains the code for dumping the curve data
associated with a selected edge subentity. It should also now
be possible to select a degenerate edge (such as the apex of a
cone) for purposes of displaying its vertex coordinate data.

brvdump.cpp
This module contains the code for dumping the point data
associated with a selected vertex subentity. Note that it is not
currently possible to select a vertex in AutoCAD as it is not
part of the display list, but it is possible to write a function
which takes a known vertex and feeds it into the vertex dump.

brtrmsrf.cpp
This is the top level code for the brtrmsrf command, which dumps
a collection of external bounded surfaces corresponding to the
trimmed representation of the selected face as split along its
seams; or alternatively a list of 3d nurb curves and 2d parameter
space nurb curves corresponding to the boundary of the selected
face. If the selected face has no loops (such as a full sphere or
torus), eDegenerateTopology is returned.

brbblock.cpp
This is the top level code for the brbblock command, which
computes a 3d model space bounding block for the selected solid
or subentity.

brptcnt.cpp
This is the top level code for the brptcnt command, which
determines the containment of a selected point with respect to
a selected subentity.

brlncnt.cpp
This is the top level code for the brlncnt command, which
determines the containment of a selected line with respect to
a selected subentity.

brmmesh.cpp
This is the top level code for the brmesh command, which generates
a 2d mesh over the selected solid or face. The file name was
chosen to avoid potential conflicts with the existing brmesh.h
file in the api header suite.

brbmesh.cpp
This module contains the code for meshing an entire solid.

brfmesh.cpp
This module contains the code for meshing a specific face.

brmdump.cpp
This module contains the code for dumping the generated 2d mesh
elements to the screen.

brndump.cpp
This module contains the code for appending individual nodes to
an AutoCAD polyline display list for purposes of displaying a
generated mesh.

brdbutl.cpp
This module contains the AutoCAD/ObjectARX/ADS interface for the
application: primarily the processing of picks and the return of
a full subentity path.

brgeutl.cpp
This module contains the AcGe object conversion utilities. This
code serves as a reference for how to turn an external curve or
surface returned by an AcBr method into an AcGe native curve or
surface to query for definition data.

brreport.cpp
This module contains the utilities that dump AcBr error codes as
well as specialised functions that annotate the results of more
complex analysis (such as line containment).
