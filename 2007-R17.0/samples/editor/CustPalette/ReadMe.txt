
CustPalette sample Readme.txt

 (C) Copyright 2002-2006 by Autodesk, Inc.

This sample demonstrates 
- deriving from CAdUiPalette and CAdUiPaletteSet. 
- explains how to persist palette data into an XML file, and to re-establish
the palette set when newly created.
- How to embed a property inspector control into a palette
- How to create a custom property editor activeX control (CDWGPreview)


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
 
...\R17.0\enu\TestPaletteSet.xml
  for the palette set and,
...\R17.0\enu\TestPalette.xml
  for the palette

*NOTE*:
*********************************************************************************
This sample code directly references the path to the 'Stadium North Elevation.dwg' file within the 'Sample' subfolder of the AutoCAD
installation directory.  You may receive a runtime error if AutoCAD was installed to a location other than
the default installation folder.


