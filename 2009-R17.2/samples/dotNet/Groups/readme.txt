(c) Copyright 2004 by Autodesk, Inc.

Description: This application implements a command called GROUPTEST. This command first prompts the user to select some entities that are placed into a group called ASDK_GROUPTEST. Then it calls the function removeAllButLines() to iterate over the group and remove all the entities that are not lines. Finally, it changes the remaining entities in the group to red. 

To use Groups.dll:

1. Start AutoCAD and open a new drawing.
2. Type netload and select Groups.dll.
3. Execute the GROUPTEST command.

Autodesk references added to this project are the acdbmgd.dll and acmgd.dll .NET components, and the AutoCAD Type Library COM component.