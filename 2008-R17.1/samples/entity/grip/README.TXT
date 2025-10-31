
Description:
 (C) Copyright 2002-2006 by Autodesk, Inc.

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
   You can control the individual dynamic dimensions using the SETDYNDIMMODES AutoCAD command. This 
   allows you to set each of the new DYNDIMMODEs supported in AutoCAD for:

	RECTJIG (horizontal dimension)
	RECTJIG (vertical dimension)
	CIRCLEGRIP (radius dimension)

The SETDYNDIMMODES is similar to the settings one can make in the dynamic dimension system variables 
such as DYNDIGRIP. Specifically,the SETDYNDIMMODES allows us the change the parameters such as 
Editable, Invisible, Focal and Hideifzero (Equavalent of the flags in the AcDbDimData::DimDataFlags 
enum). We can change these values for each of the dimensionsions we are interested in namely 
horizontal dimension (RECTJIG), vertical dimension (RECTJIG) and radius dimension (CIRCLEGRIP).
Please check up the help on "Use Dynamic Input" in the "AutoCAD 2006 Help files" for more information 
on commands and System variables for dynamic dimensions.


NOTE: The CIRCLEGRIP command and RECTJIG command will work properly only when "DYNMODE" system variable is set
to 0. If it is set to any other value (1,2,3) the dynamic input functionality in AutoCAD 2006 and later will 
superimpose over the dynamic dimensions of AutoCAD.