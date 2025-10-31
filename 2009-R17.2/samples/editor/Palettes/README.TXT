Build the sample with Microsoft Visual C++ 8 Compiler.

Load (or demand load, in the startup suite) the build arx and dbx modules.  The build order is set to:

asdkBoltObject.dbx	-	Custom Entity
asdkBoltWrapper.arx	-	Custom Entity Wrapper
asdkBoltUI.arx		-	UI module defining Running Object Command and Custom Tool Palette support.

ARX Load all three.  Use the BOLTJIG command to demonstrate how to instantiate the custom bolt (defined in askdBoltObject).  When the property palette is open, you can simultaneously enter parameters for the BOLT *as the command is running*.  The second phase of the command will actively JIG the bolt onscreen.

Run the 'CREATETOOLS' command to create tool instances in the Tool Palette (run the TP command to load the Tool Palette in AutoCAD). Several tools are created in a custom palette including:

	1 Standard Bolt tool
	1 Command Tool which runs the BOLTJIG command
	1 Flyout Tool containing three standard tools, and one BOLTJIG command tool
	
Drag and drop is fully supported in the tool palettes in AutoCAD.  This sample demonstrates how to drag bolt entities from the AutoCAD screen to dynamically create tools on the palette, and accept their parameters for the tool.


This sample demonstrates the 'AsdkPromptBase.h' and 'AcadToolImpl.h' headers which aid in adding Running Object Command support, and custom tool implementations.  These files are included in the SDK include folder, and can be used freely to create other implementations.


NOTE: This sample is self-registering. AutoCAD must be run as administrator on Windows Vista for self-registration to be successful.