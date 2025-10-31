 (C) Copyright 2004 by Autodesk, Inc.

		VBNetArx - .NET API Sample

This sample demonstrates some extra basics of using the .NET API with AutoCAD.  It defines three commands:

COMINTEROP - Demonstrates the basics of accessing objects exposed in the ActiveX COM object model.  The function accesses the AcadApplication property in the COM object model, and proceeds to iterate the documents in the AcadDocuments collection.  Using the static FromAcadDocument() method, each COM AcadDocument is converted to a managed document.  The function then goes on to modify the "Description" field of each layer listed in the the document's layer table.  After running the command, open the Layer Properties Manager dialog, and note that each layer name's "Description" field contains the string "Changed by the cominterop command".

HYPER - Demonstrates how to add HyperLink objects to a Line which has been added to Model Space.  The command adds a Line object to Model Space, and then adds two hyperlinks to the Line: "www.autodesk.com" and "www.gotdotnet.com".  After running the command, move your mouse over the Line entity.  Notice that a hyperlink icon is displayed for "www.autodesk.com".

XRECORD - Demonstrates how to create an XRecord, and populate it using the .NET equivalent of resbufs, called 'ResultBuffer'.

To run the sample.  Build the application, and load it into AutoCAD using the NETLOAD command.  You will find the VBNetArx.dll module in the \bin subfolder.




