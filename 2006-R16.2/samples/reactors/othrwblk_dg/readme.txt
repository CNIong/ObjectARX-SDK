
 (C) Copyright 1998 by Autodesk, Inc.
Description:
	Example showing correct and incorrect ways to use
	AcEditorReactor::otherWblock to get the destination database's
	Model Space BTR ObjectId

1.  Load the arx application.  This will attach an editor reactor
	which overrides the otherWblock() method to monitor WBLOCK
	operations.
2.  Create some entities.
3.  Use the WBLOCK command to wblock out the entities just created.
	The editor reactor's otherWblock method will be called at the
	appropriate time.  This reactor method will use ads_printf to
	display the objectId of the destination database obtained correctly
	the result of obtaining the destination database incorrectly (you
	end up with the Id of the source database instead),  and the Id
	of the source database (so that you can see that the incorrect
	method did indeed obtain the source database Id instead of the
	desired destination database Id.
