Build the sample with Microsoft Visual C++ 7 Compiler.

Load (or demand load, in the startup suite) the build arx and dbx modules in the following order:

asdkBoltObject.dbx
asdkBoltUI.arx

Manually load the modules asdkBoltWrapper.arx and asdkBoltTool.arx only once initially for self (COM) registration.  When the asdkBoltTool module is loaded,the ATC (XML) files and images for the tools are created within the your Windows system profile folders.  Next, restart AutoCAD (and issue the TP command if necessary) to display the new palette tabs on the tool palette window.  

The sample creates the "Stainless" and "Galvanized" tabs on the palette window.  Each has 3 tools representing stock bolt sizes.  Press each to create an instance of these bolts in the editor.  The "Stainless" tab has an extra 'command' tool which simply executes the BOLTJIG command.  This command (defined in asdkBoltUI.arx) accepts several parameters to create a custom bolt.  When the property palette is open, this command demonstrates how the property palette can now be used to respond to commandline queries, and vice versa.

The parameters of each sample tool in the palettes can be viewed and edited in a special property inspector window.  

Drag and drop is fully supported in the tool palettes in AutoCAD.  This sample demonstrates how to drag bolt entities from the AutoCAD screen to dynamically create tools on the palette, and accept their parameters for the tool.
