
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
 


==============================================================================

This sample was enhanced to support some features of Table Enhancement API.

A few more commands were added.

#1 DatLnk: creates a data link of excel type and sets it to cell (2,2).

Steps:

1. Make an EXCEL spread sheet ready before running this command. The file Test4Table.xls can be used for this purpose.

2. Create a table entity with minimum 4 colums and 4 rows.

2. Run the command DatLnk.

3. Select the table entity.

4. Select an .XLS file from the file open dialog.

You will find the data from the source Excel file has been embedded into the table from the top left cell (2,2). If the table does not have sufficient cells, it will be extended automatically.

The data link created here is bidirectional. We can write the changes made inside AutoCAD back to its source file, and we can update the table from the external source file. The following additional steps show how to do so:

5. Unlock a cell by highlighting the cell, clicking right mouse button, and choosing the Content item from the Locking sub menu.

6. When finish editing the cell, highlight it again and click right mouse button to make the context menu appear. Choose Data Links and then Upload User Changes to Source File menu item. Or highlight the whole table, click right mouse button, and choose Write Data Links to External Source menu item from the context menu.

7. Check the external source file. You will notice it has been synchronized.

8. At this time, with Excel file still open, modify a cell and save the changes in the Excel application window.

9. Return to AutoCAD.

10. Highlight any cell containing data from the Data Link, click right mouse button to make the context menu appear, and choose Data Links menu item and then Download Changes From Source File to make the data link in the table reflect the changes. 


#2 BrkTbl: breaks a table at the 1/3 of its height.


#3 TblTpl: creates a table template from the selected table and creates a table style 'MyTableStyle' to hold the table template.

Steps:

0. Check the Table Style dialog first (with TableStyle command) and confirm that no table style with the name 'MyTableStyle' is there.

1. Run the command TblTpl.

2. Select a table. A table style 'MyTableStyle' will be created. It contains a table template captured from the selected table.

3. Check the Table Style dialog again and confirm that the table style 'MyTableStyle' is there.

4. Run the Table command to create a table with the newly created table style.

You will notice the newly created table has the same looking as the old one.


#4 MltCnt: creates multiple contents, two blocks and a text, in cell (3, 0).

Before running the command, please create two blocks named 'test1' and 'test2' respectively.


#5 RstTbl: restores a table if it is broken.

