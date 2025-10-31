This sample is a CAD Standard Plugin. It adds a circle standard to CAD Standards framework. The logic 
of this Circle Standard is that a problem occurs when the color of a circle in the current drawing 
doesn't match any color of those circles in all standard files specified. All the colors of the standard
circles are considered as fix candidates for the problematic circle and the recommended fix object is 
the standard circle with the nearest radius as the bad one.

How to run it:

1. Compile and link the project with VC7;
2. Register the plugin, CircleStandard.DLL with RegSvr32.exe;
3. Run the file CircleStandard.reg to add one entry to Windows registry;
4. Startup AutoCAD; (You can find this plugin in the Plug-ins property page from Configure Standards tabbed dialog)
5. Check the plugin or any other standard plugins in the dialog;
6. Open a test drawing containing a few circles or StandardTest.dwg in the project;
7. Add one or more standard files into the Standards property page; (E.g. CircleStandard.dws in the project)
8. Change Settings if you like;
9. Click Check Standards button.
