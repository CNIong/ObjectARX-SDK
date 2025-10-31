(C) Copyright 1998 by Autodesk, Inc.

Description:

This program demonstrates creating a symbol table record (specifically a layer table record), filling in the required data, and then adding it to the layer table.

One command is defined, ADDLAYER, which calls the function addLayer().

1. Start AutoCAD and open a new drawing.
2. Type the ARX command and load tablerec.arx.
3. Type the ADDLAYER command, defined by tablerec.arx.

tablerec.arx will make a new layer, name it ADSK_TESTLAYER, give attributes
of thawed, unlocked, on, color red, and a linetype. The linetype will be 
CONTINUOUS unless you load the DASHED linetype before running tablerec.arx.
