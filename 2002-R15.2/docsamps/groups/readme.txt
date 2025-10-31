
 (C) Copyright 1998 by Autodesk, Inc.
Description:
    This program demonstrates the use of some of the
    AcDbGroup protocol. It first prompts the user to 
    select some entities that are placed into a group 
    called "ASDK_GROUPTEST". Then it calls the function 
    removeAllButLines() to iterate over the group and 
    remove all the entities that are not lines. Finally, 
    it changes the remaining entities in the group to red. 


To use groups.arx:

1. Start AutoCAD and open a new drawing.

2. Create a number of entities making sure to include some lines, circles and arcs.

3. Type the ARX command and load groups.arx.

4. Type the GROUPTST command, defined by groups.arx. Make a selection set including
   selecting at least one line.

5. Verify the contents of the group by typing the GROUP command. In
the "Object Grouping" dialog click on the name of the group, ASDK_GROUPTEST,
in the "Group_Name" listbox at the top of the dialog. Then click on the 
"Highlight" button. The items included in the group will be shown with a
different linetype, usually DASHED. Click on the "Continue" button then
exit the "Object Grouping" dialog by clicking on "Cancel".
