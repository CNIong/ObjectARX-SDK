// (C) Copyright 2005-2006 by Autodesk, Inc. 
//
This readme describes the commands implemented in the Surfaces and Helix sample, "SurfaceHelix" that illustrate the APIs available within AutoCAD to create and manipulate the different surface and helix objects. The commands described below creates surfaces that, when added together represents a table on a floor with items such as shade lamps, bowl, a helix that represents a spring, a pen holder and a pen. 

ADDPLANESURF: This command uses the PlaneSurface object to create the floor and bowl base surface.

ADDEXTRUDSURF: This command adds the table (4 legs and table top). It uses the ExtrudedSurface objects for this purpose.

ADDREVSURF: This command uses the RevolvedSurface class to create a pen holder.

ADDSWEPTSURF: This command uses the SweptSurface class to create the pen and the stand for the shaded lamp on the table.

ADDLOFTSURF: This command uses LoftedSurface class to create the shade surface of the shaded lamp and bowl surface.

ADDHELIX: This command uses the Helix class that adds a spring that acts a prop for the bowl.

ADDALL: This command is a utility command that internally calls the code for all the above ADDxxx commands.