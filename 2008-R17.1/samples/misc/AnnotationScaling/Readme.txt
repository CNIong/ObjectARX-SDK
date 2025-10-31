(C) Copyright 2006 by Autodesk, Inc. 

Annotation Scaling ObjectARX API Sample

This sample demonstrates the how to control Annotation Scaling in AutoCAD via the ObjectARX API.
 
API's used in this sample are as follows:

AcDbObjectContext
AcDbAnnotationScale
AcDbAnnotativeObjectPE
AcDbPaperOrientationPE
AcDbObjectContextInterface
AcDbObjectContextCollection
AcDbObjectContextCollectionIterator
AcDbObjectContextManager
 
The commands implemented are:
 
listAnno - lists the Annotation Scales context setups from the current drawing. 
checkAnno - allows a user to select an entity on screen and then check its Annotation Scale settings (see what scales it supports)
addAnnoEnt - creates a Custom entity derived from AcDbText and sets its supported Annotation Scales to include 1:22


NOTES:

The Annotation Scaling framework is derived from a generic Object Context framework. The Framework is implemented using
Protocol extension (AcDbObjectContextInterface) for Entities and a Context Manager (AcDbObjectContextManager) 
at the AcDbDatabase level. The Protocol extensions were implemented to keep dwg compatibility.
The specific Annotation Scaling Context is hooked into the framework via the AcDbObjectContext, and it is through this object that you can 
interrogate/edit the Scale settings of an Entity via a derived AcDbAnnotationScale class.

With regards the custom entity: it has been derived from AcDbText showing 2 pieces of Text. The top line text
is the normal AcDbText drawn text, which needs no extra code to display as Annotative. The bottom line of text is drawn
by hand and shows how to fully support the Annotative Scaling feature.
  AcDbText is already an Annotative Entity in AutoCAD, and as such already supports the Annotative Scale 
context framework; deriving from an Annotative Entity automatically inherits the Context framework. 
If you derive from a class which is not Annotative by default, such as AcDbPolyline, then you must implement 
the framework protocols yourself (AcDbAnnotativeObjectPE, AcDbPaperOrientationPE and AcDbObjectContextInterface).  

The Custom Entity Supports these features

  1) Annotation Scaling
  2) View dependant Annotation Scaling
  3) Object Selection/Highlighting which shows the Scales that it supports
  4) Is Automatically loaded by the ARX, so no need to appload the DBX.

EXTRA INFORMATION:

  At time of posting, standard Built-in Annotative Entities are

    AcDbText
    AcDbMText
    AcDbHatch
    AcDbBlockReference
    AcDbDimension
    AcDbLeader
    AcDbFcf
    
    You can of course check which ones are annotative by trying to access the PEX for the entity e.g.
    
              AcDbObjectContextInterface *objectContextInterface = ACRX_PE_PTR(ent, AcDbObjectContextInterface);