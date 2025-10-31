
Description:
 (C) Copyright 2002,2004 by Autodesk, Inc.

	Grip sample would help the developer understand the grip enhancement and 
Dynamic dimension. Two custom entity (Circle and rectangle) help the user understand 
the Grip enhancement and dynamic dimension functionality.


1. Load AcGrip,arx
2. Command: CIRCLEGRIP
3. Draw a custom circle
   As you drag the entity you could see that the circle displays the current radius. This
   could be implemented by using the new dynamic dimension methods in the AcEdJig class.
   Click on the entity for the grips to be enabled. 

4. Command: RECTJIG
5. Draw a Rectangle 
   As you drag the entity you could see that the rectangle displays the current radius. 
   Click on the entity for the grips to be enabled. 
   Hover over a grip in the rectangle and see aligned dimension getting displayed for the rectangle.

6. Command: SETDYNDIMMODES
   You can control the individual dynamic dimensions using the SETDYNDIMMODES AutoCAD command. This allows you to set each of the new DYNDIMMODEs    supported in AutoCAD for:

	RECTJIG (horizontal dimension)
	RECTJIG (vertical dimension)
	CIRCLEGRIP (radius dimension)

