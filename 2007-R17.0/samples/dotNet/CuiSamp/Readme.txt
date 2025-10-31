// (C) Copyright 2005-2006 by Autodesk, Inc. 
//

This readme describes the commands implemented in the CUI sample "CuiSamp" that
illustrate the APIs available within AutoCAD to manipulate the CUI elements.

SAVECUI: This command saves the changes made in all the CUIs (main and partial). 
One can call this command after running other commands that modify the CUI. 
(See the note below) 

ADDMENU: This command adds a menu "Custom Menu" with two menu items to all 
workspaces.

REMMENU: This command removes the menu added using the "ADDMENU" command 
described above.

ADDWS: This command adds a workspace given the workspace name.

REMWS: This command removes a workspace given the workspace name.

CUISHORTCUT: This command adds a shortcut "CTRL+B" that toggles the snap
mode.

DOCKR: This command docks the "Info palette" to the right. 

DOCKL: This command docks the "Info palette" to the left.

DOCKF: This command sets the docking mode of the "Info Palette" to
floating.

REMTOOLBAR: This command removes the toolbar created with 
"ADDTOOLBAR" command.

ADDTOOLBAR: This command creates a new tool bar called "New Toolbar". 
This toolbar contains a Toolbar control for named view, button for drawing 
a pline, and a flyout that uses the "Draw" tool bar.

TEMPKEY: This command adds a temporary key override "SHIFT+Y". Specifically, 
this key provides temporary override for OSnap to endpoint functionality.

DBLCLICK: This command adds a double click action for polylines 
(Non-LWpolylines like 2D polylines). When a polyine is double clicked the 
properties window is launched.

CUIALL: This command creates a new menu called “Custom Menu”, add a new floating
toolbar, dock the "Info Palette" on the right, and add a shortcut (CTRL+B) to
the CUI dialog. This command is equavalent to calling ADDMENU, ADDTOOLBAR, DOCKR
and CUISHORTCUT.

*NOTE*:
*********************************************************************************
1) Except for ADDWS, REMWS and CUIALL, SAVECUI command needs to be run after 
running any of the above mentioned commands (Leaving out SAVECUI itself ofcourse). 
This is necessary to save the changes and reload the changed CUI. 

2) After running DOCKR, DOCKL or DOCKF command, Run the SAVECUI command and then
Reload the "AutoCAD Default" workspace (Select it in the combobox in the 
"Workspaces" toolbar). 

3) Lisp wrapper functions have also been implemented for each of the commands. 
These functions are callable from a lisp routine or expression. The functions 
have the same name as that of the commands.
*********************************************************************************

*NOTE*:
*********************************************************************************
This code references the AcCui.dll managed component for the functionality of the sample.
Since the location of AcCui.dll is fixed with the AutoCAD installation folder, you will
receive a build error if you installed AutoCAD into a folder other than C:\Program Files\AutoCAD 2007.

If the AcCui reference is missing in the project, you will need to manually remove it
from the project, and re-add it by adding the reference from the 'Project' menu, browsing to the
AutoCAD installation directory, where AcCui.dll resides.
*********************************************************************************