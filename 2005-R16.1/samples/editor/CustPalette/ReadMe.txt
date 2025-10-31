
CustPalette sample Readme.txt

 (C) Copyright 2002-2003 by Autodesk, Inc.

This sample demonstrates deriving from CAdUiPalette and CAdUiPaletteSet. 
It explains how to persist palette data into an XML file, and to re-establish
the palette set when newly created.

Procedure:
 . Load AsDkPalette.arx
 . The palette set now shows up
 . Select item 1 and item 2 and enter data into the string, integer, and
   real edit fields
 . Reposition / Resize the palette
 . Close AutoCAD
 . Reopen AutoCAD and reload AsDkPalette.arx
 . The palette set is re-established at same position with the same size, 
   and the palette data is persisted

 The xml files that persist data are stored in the roamable profile directories.  e.g.
 
...\R16.1\enu\TestPaletteSet.xml
  for the palette set and,
...\R16.1\enu\TestPalette.xml
  for the palette

