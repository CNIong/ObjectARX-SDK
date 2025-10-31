Description:
(C) Copyright 2002-2006 by Autodesk, Inc.

This program demonstrates the use of AcDbDataTable. It defines the following commands,"LISTTABLES","ADDTABLE","DELETETABLE","LISTCOLUMNS","ADDCOLUMN","LISTROWS","ADDROW","DELETEROW"

1. Load the arx application.
2.Command "LISTTABLES"
	Lists the names of all the tables in the current drawing. A
3.command "ADDTABLE"
 	This command prompts you to input a table name and the names and types of the columns that you want to put in that table. It then add a AcDbDataTable in the database with that name if a table with the same name isn't already exist.
4.Command "DLETETABLE"
	This command prompts you to input a table name, and delete that table from the database if it exist.
5.Command "LISTCOLUMNS"
	This command prompts you for a table name, and then list the number of total columns, and the names and types of each column.
6.Command "ADDCOLUMN"
	This command prompts you for the name of a table that already exist in the database. It also prompts you the name and type of the column you want to add. It then add the newly defined column to the existing table.
7.Command "LISTROWS"