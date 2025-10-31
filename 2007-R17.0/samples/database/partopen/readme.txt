PartOpen sample Readme.txt

 (C) Copyright 2001-2006 by Autodesk, Inc.

This sample demonstrates how applications can filter large drawings
based on layer (AcDbLayerFilter) or spatial (AcDbSpatialFilter) criteria.
The sample also shows the usage of new notifications fired during various
phases of a partial open operation.

Defines the following commands:

PIMPORT
	Imports LINE entities from an external file into the current drawing
	using partial open to filter the
	database based upon the layers and area selected

PLOAD
	Simplified version of the PARTIALOAD command.  Only works if the
	active drawing is partially opened.

ISPOPEN
	Displays whether or not the active drawing is partially opened.

PVETO
	Toggle the state of the editor reactor to between vetoing and
	no vetoing partial open attempts.