// (C) Copyright 2005-2006 by Autodesk, Inc. 
//

========================================================================
						Render API Sample
========================================================================

Five commands are defined in this sample.

ObjsToRender
	Create a wood material and a cube and attach the material to the cube.
AddLights
	Add both a spot light and a point light.
AddSunAndBackground
	Add a sun and set background object.
SetRenderSettings
	Set some render settings.
ListRenderSettings
	Output current render settings.


Before testing the sample, please set testing environment as:

1. The current workspace is 3D Modeling.
2. The current visual style is Conceptual.
3. This folder exists: 
	C:/Temp
4. This file exists:
	C:/Temp/background.jpg
   You may copy the background.jpg file in the Render sample folder to the C:/Temp folder.
 
 
Steps to run:

0. Load the Render.ARX into AutoCAD.

1. The following command sequence is recommended:
	1.1  Run ObjsToRender command.
	1.2	 Check the cube properties especially the Material proprty
	1.3  Run AddLights command.
	1.4  Run Zoom Extents command.
	1.5  Use Sun Properties palette to check the sun of the current view.
	1.6  Run AddSunAndBackground command.
	1.7  Use Sun Properties palette to check the sun of the current view again.
	1.8  Run ListRenderSettings command.
	1.9  Run SetRenderSettings command.
	1.10 Run ListRenderSettings command again.
	1.11 Run Render command.
	