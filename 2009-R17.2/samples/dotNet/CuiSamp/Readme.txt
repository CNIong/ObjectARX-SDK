// (C) Copyright 2005-2006 by Autodesk, Inc. 
//

This readme describes the commands implemented in the CUI sample "CuiSamp" that
illustrate the APIs available within AutoCAD to manipulate the CUI elements.

The sample also demonstrates a class (CUIStartup) that populates CUI with a custom 
Workspace called 'Acme Workspace' which in-turn contains a custom menu, toolbar and 
Dashboard entry.

The class is designed so that when loaded (either via NETLOAD or demand loaded from 
the registry) the Workspace is created and populated Automatically the first time
it is run.  Subsequent loads will not modify any CUI or Workspace settings, including
WSCURRENT.

The class also defines two commands which can be used as well:

FORCEWS - Forces the state of the Workspace.  Basically removes and completely
rebuilds the workspace, restoring the default settings.

REMOVEALL - Removes all the the UI components.

The purpose of this class is to demonstrate one method of UI deployment.  You can
generate all your UI components at first-run AutoCAD using this method.  

UI cleanup can be performed at uninstall without AutoCAD running (The RemoveAllComponents
Code can be moved into an executible spawned during uninstall so that cleanup could 
be performed without AutoCAD running).  This is left as a simple exercise for the developer.

The sample also demonstrates within the 'CuiSamp' class the following commands which
may be used as a guide toward general CUI development:


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

DOCKR: This command docks the "Properties palette" to the right. 

DOCKL: This command docks the "Properties palette" to the left.

DOCKF: This command sets the docking mode of the "Properties Palette" to
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
toolbar, dock the "Properties Palette" on the right, and add a shortcut (CTRL+B) to
the CUI dialog. This command is equavalent to calling ADDMENU, ADDTOOLBAR, DOCKR
and CUISHORTCUT.

*NOTE*:
*********************************************************************************
1) Except for ADDWS, REMWS and CUIALL, SAVECUI command needs to be run after 
running any of the above mentioned commands (Leaving out SAVECUI itself ofcourse). 
This is necessary to save the changes and reload the changed CUI. 

2) After running DOCKR, DOCKL or DOCKF command, Run the SAVECUI command and then
Reload the "AutoCAD Classic" workspace (Select it in the combobox in the 
"Workspaces" toolbar). 

3) Lisp wrapper functions have also been implemented for each of the commands. 
These functions are callable from a lisp routine or expression. The functions 
have the same name as that of the commands.
*********************************************************************************

*NOTE*:
*********************************************************************************
This code references the AcCui.dll managed component in the inc folder.
The AcCui.dll in the inc folder is for compile purposes only. 
*********************************************************************************