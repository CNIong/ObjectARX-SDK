 (C) Copyright 2007-2008 by Autodesk, Inc.

This application demonstrates the usage of the AcCtrl ActiveX control that is distributed with AutoCAD (it is available as AcCtrl.dll in the AutoCAD install folder).

The application is a stand alone .NET application that references the necessary .NET wrappers (generated automatically by Visual Studio using TLBIMP) for the control. The application consists of a dialog box with the embedded instance of the control and a few other .NET common controls (buttons and edit control)

To use this application:

1. Make sure AutoCAD is installed on the machine.
2. Build and launch the application. This displays a form. All the buttons on the form except the "Select Drawing" button are disabled.
3. Click on the "Select Drawing" button to nagivate to the desired AutoCAD drawing (*.dwg) and select it. If a valid drawing is selected, it will be loaded into the embedded control and displayed. This also enables the other buttons on the form. 

The usage of the other buttons on the form is self explanatory.
