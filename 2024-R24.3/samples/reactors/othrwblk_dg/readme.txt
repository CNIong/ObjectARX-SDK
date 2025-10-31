Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   

Description:
	Example showing correct and incorrect ways to use
	AcEditorReactor::otherWblock to get the destination database's
	Model Space BTR and its ObjectId

1.  Load the arx application.  This will attach an editor reactor
	which overrides the otherWblock() method to monitor WBLOCK
	operations.
2.  Create some entities.
3.  Use the WBLOCK command to wblock out the entities just created.
	The editor reactor's otherWblock method will be called at the
	appropriate time.  This reactor method will use ads_printf to
	display the objectId of the destination Model Space BTR obtained
	correctly and the result of obtaining the destination Model Space
	BTR ObjectId incorrectly (you end up with the Id of the source
	Model Space BTR	instead), so that you can see that the incorrect
	method did indeed obtain the source Model Space BTR Id instead of
	the desired destination Model Space BTR Id.
