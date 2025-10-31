
Description:
 (C) Copyright 2003 by Autodesk, Inc.

	Table sample would help the developer understand the new AcDbTable entity and the AcDbTableStyle object. 
	The sample shows how these new classes can be used to create a Table object as well as TableStyle object in AutoCAD 
	and populate it with data. 


1. Load Asdktable.arx
2. Type Command: BLKTBL
	a. A modal dialog will be shown. It will list all the block definitions that have attribute definitions.
	   Also, a new table style "BlockAttList" will be added to the drawing.
	
	b. Select a block definition from the list and click "Create Table" button. This will create a new AcDbTable entity with the selected table style.
	   The number of columns are added depending on the number of attribute definitions available in the block definition. 
	   Then, for each block reference a new row is added to the table and attribute values of the block reference are filled in the row cells.
	
	c. To create a new table style, select "<New Table Style>" from the drop-down list box and type the table style name in the edit box.
	
	d. Select the check box "link to attributes" to use field expressions instead of actual attribute values in the table. 
	
	e. To update an existing table, select the block definition from the list and click "Update Table". 
	   It will prompt to select a table entity in the drawing and will update the selected table with new columns, rows and cell values.
 
