Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////////////
Description:

This program demonstrates the use of some of the AcDbGroup protocol. It first prompts the user to select some entities that are placed into a group called "ASDK_GROUPTEST". Then it calls the function removeAllButLines() to iterate over the group and remove all the entities that are not lines. Finally, it changes the remaining entities in the group to red. 

To use groups.arx:
1. Start AutoCAD and open a new drawing.
2. Create a number of entities, making sure to include some lines, circles, and arcs.
3. Type the ARX command and load groups.arx.
4. Type the GROUPTST command, defined by groups.arx. Make a selection set that includes at least one line.
5. Verify the contents of the group by executing the GROUP command. In the 'Object Grouping' dialog click on the name of the group ASDK_GROUPTEST in the Group_Name listbox at the top of the dialog. Next, click the 'Highlight' button to highlight the members of the group (this will be a standard dashed-linetype highlight).  Notice that only the red lines in the group are highlighted.  Click the Continue button, then exit the Object Grouping dialog by clicking Cancel.
