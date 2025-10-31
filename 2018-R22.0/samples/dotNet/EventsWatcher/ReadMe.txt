Copyright 2017 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


This sample is to demonstrate how to use the functionalities of AutoCAD .NET Reactors API. It is written in C#.

The following AutoCAD .NET events are showed in the sample:

Application Events
Database Events
Document Events
Document Collection (Manager) Events
Dynamic Linker Events
Editor Events
Layout Manager Events
Plot Manager Events

In addition, it also shows how to use model form and modeless form in a .NET assembly. The model form named EventsWatcher is the main UI to plant various events and remove them. The modeless dialog named Output is the output window for all the information of events selected in the former dialog. It also supports a context menu which contains two items, Save and Clean. When the Save item is pressed, a Save As dialog will pop up for you to save all the output in the form to a file with RTF or TXT format. The Clean command is to clear all the texts in the form, actually a rich text control embedded in it.

Steps to run the sample:

1. Compile it with VS.NET 4.5 or later. Please remove and add the two AutoCAD managed DLLs again.
2. NetLoad the assembly DLL EventsWatcher into AutoCAD. 
3. Click right mouse button to pop up the default application context menu.
4. Choose the Watcher -> Events Watcher ... menu item.
5. Choose any options you like.
6. Click OK button to exit the dialog.
7. If you want the Output form appear, please choose the Watcher -> Events Output Window menu item in the default application context menu.
8. Here you go. Enjoy it!
