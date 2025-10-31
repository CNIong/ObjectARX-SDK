

			AsdkPlotApi ObjectARX SDK Sample

This sample demonstrates how to leverage the updated PLOT API for ObjectARX 2005.  The sample project
defines a simple PLOT dialog which contains a few specific plot parameters to chose from, including:

	Plot Device
	Plot Media
	Plot Scale
	Plot to Fit option
	Plot to File option
	Landscape option
	Background Plot option
	Preview Button
	Plot Button

When the asdkPlotApi.arx module is loaded, the PLOT dialog can be launched with the 'PLOTAPI' command.
The current layout is plotted with the parameters set on the dialog by pressing the 'PLOT' button.  
A plot preview can be generated with the 'PREVIEW' button.


New in AutoCAD 2005 is the ability to send a plot job to a background plot process.  This option is controlled by the BACKGROUNDPLOT system variable.  

The sample supports this background plot feature with the 'Background' option.  Additionally, the sample defines a custom plot reactor to receive notifications sent from the background plot process.  when the asdkPlotApi.arx module is demand loaded in AutoCAD at startup (required for this feature to work), a reactor
is planted for each background plot process (which is just another hidden acad.exe session), and sends 
notifications via COM back to the spawning process.  A separate 'Background Plot Notification' dialog is launched with the first instance of the Plot API Dialog.  whenever any background plots send notifications (via the reactor instance loaded at startup), they will be received in this dialog regardless of where the plot was initiated (such as from another session of AutoCAD).  This notification dialog will be closed automatically when the refcount for the server drops to zero (i.e. all the reactor instances are deleted).

Note:  Background plots take considerably longer to process...be patient for the notifications.

The sample demonstrates the use of the following PLOT-Specific API classes:

AcDbPlotSettings
AcDbPlotSettingsValidator
AcPlPlotConfigManager
AcPlPlotProgressDialog
AcPlPlotFactory
AcPlPlotEngine
AcPlPlotInfoValidator
AcPlPlotPageInfo
AcPlPlotInfo




	