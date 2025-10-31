DWFMetaData ReadMe

(C) Copyright 2004-2006 by Autodesk, Inc.

This application is to provide help in developing and understanding the API related to 
DWF meta data manager. There is no built-in command to to run this application. 
This application is purely related DWF meta data manager reactors. 
Its main focus is to show : 
	- How to plant the reactors and trap the event(s) during PUBLISH operation 
	- How a third party application can customize the metadata published along with DWF file.

This application load AcPublish.arx and AcEPlotX.arx ate loaded at runtime.

This application defines two classes.
	- AcTestPublishReactor derived from AcPublishReactor
	- AcTestDMMEntReactor derived from AcDMMReactor


AcTestPublishReactor: 
Clients who desire notifications of the key publish events will derive
from AcPublishReactor and instantiate this class. These reactors are called only during Publish to 
DWF operations. Clients are responsible for obtaining configuration data for their metadata publication 
from the AcPublishReactor

AcTestDMMEntReactor:
Is the entity level reactor which we trap during publishing of entity to DWF file


Hooking up: 
Requirements for hooking up to publish:
-   Make sure AcPublish.arx is loaded
-   Hook up derived AcPublishReactor
-   Hook up derived AcPublishUiReactor and expose UI for controlling the publication of your metadata 
	by adding controls to PublishOptions dialog. (not showed in this sample)
-   In AboutToBeginPublishing, hook up AcDMMReactor derived object. 
	Note the AcDMMReactorManager only exists while AcPublish is running
-   In OnEndPublishing and in OnCancelledOrFailedPublishing, unhook AcDMMReactor
-   When application exits, be sure to unhook Publish reactors

Steps to run the application:
Launch AutoCAD 2006, Load the arx application. 
set BACKGROUNDPLOT to zero (optional)
Open any dwg file, run the command PUBLISH.
Using 'Autodesk DWF Viewer' open the resultant DWF file.

In sheet tab following properties are added:

DMMAPI		"Description"		"Description through API"
DMMAPI		"Sheet Number"		"Sheet Number through API"
DMMAPI		"Name"				"Value"

For individual entities following properties are added:

DMMAPI				color				colorValue
DMMAPI				Entitytpe			Entity type
DMMAPI				Handle				Handle of entity
DMMAPI				Layer				Layer name
DMMAPI				Linetype			Linetype
DMMAPI				Lineytype Scale		Linetype Scale used

In case of MPOLYGON which is a custom entity it following properties are added:

DMMAPI_CUSTOMENT	MPoly Area				Area of the Mpolygon
DMMAPI_CUSTOMENT	MPoly Perimeter			Perimeter of the Mpolygon object
		
Note: In current sample AcDbBlockReference are not processed. 
It will be included in the later builds.
