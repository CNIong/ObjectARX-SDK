Curvetext Readme.txt

 (C) Copyright 2001 by Autodesk, Inc.

Curvetext is an ObjectARX application that allows the user to display text along
curves in the drawing. Such curves can be of any type except ray, xlines, and old
style polylines.

To use the application, build the dbx and arx components, and move them to the
acad.exe directory (or some directory in AutoCAD's search path). Then, for the
first time only, manually load the .dbx module and then the .arx modulee in
AutoCAD using the "APPLOAD" command.

Make sure you have a curve in the drawing (say a circle), and then type "CT"
on the command line, or select the circle, right click and select "Curvetext..."

The next time AutoCAD will be loaded, it will not be necessary to load the .dbx
module or .arx module manually since Curvetext implements demand loading, typing
"ct" at the command prompt, will load the required components automatically.

This sample uses the techniques of custom object with an embedded object, object
enabler (dbx), demand loading, context menu, AcUi dialogs, Input point API, and more.
