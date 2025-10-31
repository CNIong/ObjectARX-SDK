// (C) Copyright 2005-2006 by Autodesk, Inc. 
//
This readme describes the commands implemented in the Sectionplane sample that illustrate the APIs available within AutoCAD to create and manipulate AcDbSection entities. 

DYNAMICSECTION: This command prompts for two points to define the beginning plane for a section. (AcDbSection) After selecting the two points a section is created. You can then change the location of the section. You can translate the section forward, backward or rotate it. Entering a positive value for the Translation will move the section forward. A negative value will move the section backwards. The Rotate option will also accept positive or negative values to rotate the section. The Snapshot option will prompt to select a 3dSolid and the name to give to a block. A block reference is placed at the same location as the geometry it was generated from.

GETSECTION: This command prompts the user to select a section. (SECTIONOBJECT) It then prints the properties of the section on the command line.

ITERSECTIONS: This command gets the section manager and then iterates through the sections in the drawing. Properties of each section are printed on the command line.

  
