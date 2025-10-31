Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


This sample demonstrates how to use the AcadToolImpl class to create a rudimentary Tool Palette client application. To run the sample, load the ARX file in AutoCAD and type the CREATESIMPLE command. This command creates a new tool palette named SimplePalette in the Tool Palettes window. 

SimplePalette demonstrates a flyout tool, a command tool, and a plain tool. The flyout tool uses a standard AutoCAD shape package to allow the user to exchange the default line tool for a variety of other entity tools. The command tool starts the LINE command and lets the user choose the start and end points. The plain tool behaves like a macro that creates a line with hard-coded points, with no user input.

This sample also demonstrates a custom tool palette context menu. When the user right-clicks on the SimplePalette, the context menu displays three extra items: Menu1, Menu2, and Menu3. Each of these menu items launches an alert box that displays the name of the chosen item. When the user right-clicks on any palette other than the SimplePalette, the three custom menu items do not appear.



