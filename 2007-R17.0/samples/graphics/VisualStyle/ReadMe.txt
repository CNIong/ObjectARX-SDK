Visual Style Sample Readme.txt

(C) Copyright 2005-2006 by Autodesk, Inc.

This sample demonstrates several things:

1) How to use the AcDbVisualStyle API to create visual styles and assign
them to viewports and custom entities. (VisualStyleUi project).
2) How to use the visual style dictionary to query, rename, and delete 
visual styles. (VisualStyleUi project).
3) How to implement a custom entity ObjectDBX enabler 
(VisualStyleDb project).
4) How to implement an ObjectARX command (VisualStyleUi project).

The project has two components:

1) AsdkVisualStyleDb.dbx - Defines the custom entity AsdkVisualStyle,
which is an entity consisting of multiple spheres with visual styles
applied to each subentity.
2) AsdkVisualStyleUi.arx - Defines the command VSTYLE that lets the user
create AsdkVisualStyle entities.  Other supported commands include:

VSLIST = lists all visual styles in the visual style dictionary
VSCURRENT = sets the specified visual style on the current viewport
VSCURRENTINFO = displays visual style info for the current viewport
VSRENAME = renames an existing visual style
VSDELETE = deletes an existing visual style


Notes on Demand Loading Registration:

This sample demonstrates the use of the AcadAppInfo class to perform self-registration
for demand loading keys in the registry.  This is demonstrated for simplicity only.
Generally registration of these keys should be performed by an MSI installer.