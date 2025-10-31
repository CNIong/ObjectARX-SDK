DynamicBlock .NET API Sample Readme.txt

(C) Copyright 2004 by Autodesk, Inc.

This sample demonstrates listing and manipulating the property values of a dynamic block 
reference.

There are three commands:

DynList - Lists at the command line all the properties of dynamic block references in the drawing.

DynEdit - Displays the properties of a dynamic block in a DataGrid. The grid shows four columns. 
          
          1. Name - Name of the parameter or property (ReadOnly)
          2. Type - The data type for the property value. See the Enum PropTypeCode for a list of types (ReadOnly)
          3. Value - The value of the parameter. Editable. Any
			 erroneous input will notify the user.
          4. Description - The description of the property (ReadOnly)

Once done editing, press the OK button to dismiss the form. The changes made to the 
properties can now be seen in the drawing.

DynFreeze - Converts a dynamic block reference to a regular (or static) block reference 

Demo:

 Load DynamicBlock.dll from the \bin folder into AutoCAD using NETLOAD command. 
 Play with the above commands. Rereferencing acmgd.dll and acdbmgd.dll may be necessary to build the project.
 
 
