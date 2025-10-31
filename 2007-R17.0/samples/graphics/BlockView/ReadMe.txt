------------------------
Block View Sample Readme
------------------------

- Compile and load the AsdkBlockView.arx.
- Run command BView at the AutoCAD command line.
- Default operation is to display the current drawing using the current view settings of the current drawing.

Function Descriptions
---------------------

File->Open	Opens an existing drawing into the Block View dialog (by clearing the AcGsView).
File->Output	Allows you to output a JPG;BMP;Tiff;Png files as a snaphot of the current view shown in the BlockView dialog.
		This feature requires the ATIL SDK.
		To enable the feature, follow the instructions in CBlockViewDlg::OnFilePrint().
File->AcGsDevice Config
		View or edit the current AcGsDevice configuration settings.
View->Zoom  Allows Zoom Extents/Zoom Window functionality
View->Settings->Show  Allows the toggling of various GSView settings such as Linetype/Material and Sectioning
View->Settings->Renderer Type  Allows you to switch the Renderer type.

ViewModes	This dropdown allows the user to change the View mode of the AcGsView.
		It has the same options as the SHADEMODE command.
ReMap Colors	Button to remap the color palette.
		This is particularily useful if you want to show an AcGsView as a Paper Space layout, with
		a white background. In this case you will need to remap white entities to appear in a different color.
Standard Colors
		Restores the Color Palette back to the original one.
Add Entity	Adds an entity to the Model Space and adds to the AcGsView.
Add Temp Entity
		Adds an entity just to the AcGsView.

------------------------------------------------------------------------------

 


