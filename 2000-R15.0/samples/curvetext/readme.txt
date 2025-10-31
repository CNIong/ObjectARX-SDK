Curvetext readme


Curvetext is an ObjectARX application that allows the user to display text along curves in the drawing. Such curves can be of any type except ray, xlines and old style polylines.

To use the application, build the dbx and arx components, and move them to the acad.exe directory. Then, for the first time only, manually load the .dbx and then the .arx file in AutoCAD using the "APPLOAD" command.

Make sure you have a curve on the drawing (say a circle), and them type "CT" on the command line, or select the circle, right click and select "Curvetext..."

Next time AutoCAD will be loaded, it will not be necessary to load the .dbx or .arx files manually since curvetext implements demand loading, type ing "ct" will load the components automatically.

This sample uses the techniques of custom object with an embedded object, object enabler (dbx), demand loading, context menu, AcUi dialogs, Input point API and more.
