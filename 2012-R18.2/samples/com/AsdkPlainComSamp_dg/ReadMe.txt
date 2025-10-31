 (C) Copyright 2005-2006 by Autodesk, Inc. 

This sample demonstrates some of the many uses of COM access using Win32 API.


1. Start AutoCAD and open a new drawing.

2. Type the ARX command and load AsdkPlainComDocSamp.arx.

3. Type ComMenu command.
Notice that the AutoCAD menu now has an asdkcomaccess pulldown menu. 

4. From askdcomaccess menu, use add a com circle and/or autolisp example.

5. Type ComCircle command.
Notice that the a circle has added to the AutoCAD Modelspace. 

Note: If you are using this sample in an AutoCAD OEM Product you will need to add a command named AsdkComCircle to the product. (not just ComCircle). AsdkComCircle is the command called from the menu macro. 
