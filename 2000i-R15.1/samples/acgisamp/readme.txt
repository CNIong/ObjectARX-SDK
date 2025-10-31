
 (C) Copyright 1998 by Autodesk, Inc.
This sample application demonstrates how to trap the shell data
when models are being shaded.  The sample makes use of the 
information passed onto the worldDraw function whenever an object
is regenerated.  This information is trapped and stored as part
of the custom entity (AsdkCustomDrawEntity) whose only purpose
is the retain the trapped data and display it on a regen or shade
operation.  Users can also translate the custom entity's data
to a format compatible with Stereo Lithography software for rapid
prototyping purposes.


 COMMANDS:  The application supports the following commands:
 1.  FacetFaces:	Command which allows users to select faces/regions and
 then facets them.  Users can enter the shade command after this and see a
 shaded representation of the selected faces.  The overlay of the parent model
 may obscure the display in some cases, hence it is a good idea to move the
 base model before shading the window.
 An other possibility is to call the SHADE command before calling FacetFaces.
 2.  SetColorIndex:  Command to set the color to be assigned to the
 facets.
 3.  SetDeviation:   Command to set the facet deviation.  A smaller value
 of deviation will create more facets and a more true representation of
 the surface data.
 All these commands are implemented in acgisamp.cpp

 CLASSES IMPLEMENTED IN THIS SAMPLE:

 1.  AsdkCustomWorldDraw - This is a custom class derived from 
 AcGiWorldDraw.  It has default implementations for all its methods
 and contains a member data called AsdkShellData.  File: custacgi.cpp

 2.  AsdkCustomWorldGeometry -  This object will be used when worldDraw
 method of an entity is called.  This class stores a backpointer to the
 AsdkWorldDraw class.  All methods of this object are stubbed
 out except the ::shell method.  The shell method will trap the
 incomming data and assign it to the AsdkShellData class.
 ex.  AsdkCustomWorldGeometry->AsdkCustomWorldDraw->AsdkShellData->storeData.
 The line above indicates that the worldGeometry class has a back pointer
 to the worldDraw class whose member class AsdkShellData is used to
 store the information coming into the AsdkCustomWorldGeometry::shell function
 File:  custacgi.cpp

 3.  AsdkCustomSubEntityTraits -  Object derived off AcGiSubEntityTraits.
     File: custacgi.cpp

 4.  AsdkShellData -  Class to store the trapped shellData.
     File:  custacgi.cpp

 5.  AsdkCustomDrawEntity -  A custom entity to draw the trapped shellData.
     File:  drawent.cpp

 6.  The class AsdkPerDocData holds the per document used global variables 
     colorIndex and deviation 

 7.  The class AsdkDocGlobals is responsable for setting the correct global
     variables when a Document-switch occures
     The actual global variables can be accessed through the global pointer
     named gpActualData

A high level description of the implementation is given below:

The "facetFaces" command will create a body/Region out of the face that was selected.
This object's worldDraw() method is called by passing in the AsdkCustomWorldDraw
object.  Since by default the AsdkCustomWorldDraw object is always set to shade mode,
the data of the body/region will get faceted and be trapped during the call the the
AsdkCustomWorldGeometry::shell method.  

This trapped data is used to create a AsdkCustomDrawEntity which will display the 
facets.  The original body/region is then deleted.  The code that does this can be
found in file acgisamp.cpp in the facetFaces() function.
