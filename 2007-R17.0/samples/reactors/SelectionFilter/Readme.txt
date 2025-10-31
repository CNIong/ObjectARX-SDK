// (C) Copyright 2005-2006 by Autodesk, Inc. 
//

Description:

 	This sample shows how to use the ehanced SelectionSet API to ...
        (1) highlight a nested entity inside of an XRef (largely as implemented in the  AutoCAD 2004 ARX  API). This is referred
            to as subentity selection in the project. It makes use of a subentity selection filter. 
        (2) select in space within an entity
        (3) subselect an (already selected) entity.
         Functionalities (2) and (3) make use of a  subselection filter.


Because the demonstration of functionality (3) requires using a custom entity, there are two projects within the sample solution -
a DBX and an ARX project. The corresponding ARX & DBX modules (AsdkSelectionFilterUI.arx & AsdkSelectionFilterDb.dbx) must be loaded
for this sample to run.
 
To test functionality (1)..

a. Open a drawing with an XRef attached
b. Load AsdkSelectionFilterUI.arx & AsdkSelectionFilterDb.dbx
c. Command: ADDSUBENTFILTER to add  the subentity selection filter
d. Command: SUBENTSEL to do subentity selection
e. Select entities that belong to the XRef
f. The selected nested entities will be highlighted
g. Hit enter to complete the selection. The ObjectId of the each selected entity is printed on the command line.
h. Command: DELSUBENTFILTER to delete the subentity selection filter. 
   You may also do this later using command DELFILTERS to delete all filters.



To test functionality (2) ....

a. Load AsdkSelectionFilterUI.arx & AsdkSelectionFilterDb.dbx, if not already loaded
b. Command: ADDSUBSELFILTER to add  the subselection filter
c. Draw a circle, an ellipse or a rectangle 
d. Click anywhere inside the ellipse, circle or rectangle. Notice that the entity is selected
e. Command: DELSUBSELFILTER to delete the subselection filter or DELFILTERS to delete all filters.
f. Repeat step (d) again. Notice that no selection takes place.


 
To test functionalities (3) and (2)....

a. Load AsdkSelectionFilterUI.arx & AsdkSelectionFilterDb.dbx, if not already loaded
b. Command: ADDSUBSELFILTER to add  the subentity selection filter
c. Command: RINGS to create a custom entity - AsdkRings, comprising of three concentric red, green and blue circles
d. Click anywhere inside the Rings entity. Notice that the entity is selected. 
e. Click inside the red (or green or blue) circle. Notice that only the red (or green or blue) circle is now selected. 
f. Command: DELSUBSELFILTER to delete the subselection filter
g. Repeat steps (d) & (e) again. Notice that no selection takes place.
h. Command DELFILTERS to delete all filters.
