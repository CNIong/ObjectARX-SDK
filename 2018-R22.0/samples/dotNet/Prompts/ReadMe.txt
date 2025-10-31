Copyright 2017 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


This application demonstrates how to use Prompts in .NET API.
It demonstrates the usage of.NET API's version of the user input functions like
acedGetInt, acedGetReal,acedGetDist,acedGetAngle,acedGetOrient,acedGetpoint,
acedGetCorner,acedGetKWord,acedGetString,acedNEntSel and acedNEntSelP.

To build the application:
Please add references acdbmgd.dll and acmgd.dll from you acad install directory.

To use this application:

1. Start AutoCAD and open a new drawing.
2. Type netload and select prompts.dll from the \bin subfolder.
3. Execute the commands defined by prompts.dll.

Please add the References acdbmgd.dll,acmgd.dll,
Autodesk.AutoCAD.Interop.dll and Autodesk.AutoCAD.Interop.Common.dll
before trying to build this project.

The following commands are part of this project:

1)GetInteger - A small function that shows how to prompt for an integer

2)GetDouble - This method prompts for a double value.
	      Pi,Two-pi  are valid keywords that can be entered
	      by the user at the prompt.

3)GetDistance - Gets the radius of the circle from the user using GetDistance 
                command and draws the circle.

4)GetAngle - The user is prompted to enter the start angle and end angle at the
	     command prompt.  Using which an arc is created.
             Also attached to this function is the input context reactor event
	     PromptingForAngle and PromptedForAngle. During ed.GetAngle(), these
             events gets fired. The call back function just remembers the prompt 
             option that the user has set initially and also the prompt result that 
             the user sees after he calls GetAngle() method.

5)useAngle - Demonstrates how the input context reactors PromptAngleOption and              PromptAngleResult works.

6)GetPoint - Draws a line using the points entered by the user.
     	     Prompt the user for the start point and end point of the line.

7)usepoint - Demonstrates how the input context reactors PromptPointOption and              PromptPointResult works.

8)GetKW - Here the user is prompted for a string that could be used as a keyword.
	  We then test to see if the user entered string has been taken as a valid 
	  keyword or not by asking the user to enter that string as a keyword in 
          the command prompt.

9)Getentity - Try to draw a few entities in the drawing for the user to select.
	      It prompts the user to select some entities and finally types
	      the name of the selected entity at the command prompt.
	      Also added the two input context reactor events:
	      PromptingForEntity and PromptedForEntity

10)GetNestentity - Try to draw a few nested entities like blocks and xrefs in the drawing for the user to select. If the user selects a nested entity then the name of the nested entity is displayed. Finally after the user is done selecting the entities, a non interactive selection is made at the point 30.4,11.6,0 and the name of the nested entity if any is displayed.