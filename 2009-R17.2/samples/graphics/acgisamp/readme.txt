Acgisamp sample Readme.txt

 (C) Copyright 2001 by Autodesk, Inc.

This sample application demonstrates how to trap the shell data
when models are being shaded.  The sample makes use of the 
information passed onto the worldDraw function whenever an object
is regenerated.  This information is trapped and stored as part
of the custom entity (AsdkCustomDrawEntity), whose only purpose
is to retain the trapped data and display it on a regen or shade
operation.  Users can also translate the custom entity's data
to a format compatible with Stereo Lithography software for rapid
prototyping purposes.


COMMANDS: The application supports the following commands:

1. FACETFACES: A command that allows users to select faces or regions
   and then facets them.  Users can enter the SHADE command after this
   and see a shaded representation of the selected faces.  The overlay
   of the parent model may obscure the display in some cases, so it is
   a good idea to move the base model before shading the window.
   Another possibility is to use the SHADE command before FACETFACES.
 
2. SETCOLORINDEX: A command that sets the facet color.

3. SETDEVIATION: A command that sets the facet deviation. A lesser value
   of deviation creates more facets and a more true representation of
   the surface data.

All these commands are implemented in the file - ACGISAMP.CPP

CLASSES IMPLEMENTED IN THIS SAMPLE:

1. AsdkCustomWorldDraw - This is a custom class derived from 
   AcGiWorldDraw.  It has default implementations for all its methods
   and contains a member data of type AsdkShellData called mpShellData.
   See file - CUSTACGI.cpp

2. AsdkCustomWorldGeometry - This object is used when the worldDraw()
   method of an entity is called.  This class stores a backpointer to
   the AsdkWorldDraw class.  All methods of this object are stubbed
   out except the ::shell() method.  The shell method traps the
   incoming data and assigns it to the AsdkShellData class.
   
   Example
   
   AsdkCustomWorldGeometry->AsdkCustomWorldDraw->AsdkShellData->storeData.

   The line above indicates that the worldGeometry class has a back pointer
   to the worldDraw class whose member class AsdkShellData is used to
   store the information coming into the AsdkCustomWorldGeometry::shell()
   function
   See file - custacgi.cpp

3. AsdkCustomSubEntityTraits - An object derived from AcGiSubEntityTraits.
   See file - custacgi.cpp

4. AsdkShellData - A class to store the trapped shellData.
   See file - custacgi.cpp

5. AsdkCustomDrawEntity - A custom entity to draw the trapped shell data.
   See file - drawent.cpp

6. The class AsdkPerDocData holds the per document global variables 
   'colorIndex' and 'deviation'.

7. The class AsdkDocGlobals is responsable for setting the correct global
   variables when a document-switch occurs. The actual global variables
   can be accessed through the application wide global pointer named
   'gpActualData'.

A high level description of the implementation follows:

The FACEFACETS command will create a "Body/Region" out of the face that
was selected. This object's worldDraw() method is called by passing in
the AsdkCustomWorldDraw object.  Since the AsdkCustomWorldDraw
object is set by default to shade mode, the data of the "Body/Region"
is faceted and trapped during the call the the
AsdkCustomWorldGeometry::shell() method.  

This trapped data is used to create an AsdkCustomDrawEntity, which will
display the facets. The original "Body/Region" is then deleted. The code
that does this can be found in file acgisamp.cpp in the facetFaces()
function.
