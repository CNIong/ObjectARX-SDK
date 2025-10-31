Copyright 2013 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


This application implements a command called ellipsejig. It will help you 
create an ellipse from scratch by doing a jig. The user is first asked to
enter the ellipse major axis followed by ellipse minor axis. 

To use JigSample.dll:
1. Start AutoCAD and open a new drawing.
2. Type netload and select JigSample.dll from the \bin subfolder.
3. Execute the ellipsejig command, defined by JigSample.dll.

Please add the References acdbmgd.dll,acmgd.dll from your acad installation directory before trying to build this project.