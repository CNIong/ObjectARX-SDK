HlrArxSample Sample

 Copyright 2023 Autodesk, Inc.  All rights reserved.

This sample demonstrates the use of AsdkHlrApi24.

The AsdkHlrApi24 module is there to help to calculate hidden lines 
from an AutoCAD drawing. It returns the resulting curve entities
in memory, and the application can decide to add them to the same
drawing or another.

The AsdkHlrArxSample.arx sample defines some custom commands to 
use AsdkHlrApi24 engine.

- Command 'TEST1' ask you to select entities in an AutoCAD DWG file,
and use the current viewport settings to calculate hidden lines.
All visible curves will be returned with the Red color, all 
non-visible returned curves will be returned in Blue.


- Command TEST2 ask you to select entities in an AutoCAD DWG file,
for a virtual viewport, and for HLR controls you want to apply to 
the HLR engine. Then the color of each resulting entities will depend 
of the originator entity. The function is going throw block definition
to find the original entity which produced the edges, and assign its 
color to the edges.


- Command 'TEST3' demonstrates the same thing as command 'TEST1' except
that it works on memory only entities. Memory only entities, and database 
resident entity can be mixed together in the collector object.


- Command 'TEST4' demonstrates the use of kCleanup / kReuse flags


- Command TEST5 ask you to select entities on the AutoCAD DWG file,
for a virtual viewport, and for HLR controls you want to apply to 
the HLR engine. Then the color of each resulting entities will depend 
of the originator entity. The function is going throw block definition
to find the original entity which produced the edges, and assign its 
color to the edges. Its like 'TEST2', but works with clipping.


- Command 'TEST6' is a command which creates an ACIS BODY from triangles.



Note:
 
To use these applications, AsdkHlrApi24.dbx should be copied into the 
AutoCAD folder. First the OS must find it and second AutoCAD must find 
it for the acrxLoadModule("AsdkHlrApi24.dbx",0) call to succeed.
