
Copyright (C) 2003-2006 by Autodesk, Inc.

Permission to use, copy, modify, and distribute this software in 
object code form for any purpose and without fee is hereby granted, 
provided that the above copyright notice appears in all copies and 
that both that copyright notice and the limited warranty and 
restricted rights notice below appear in all supporting 
documentation.

AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF 
MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC. 
DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE 
UNINTERRUPTED OR ERROR FREE.

Use, duplication, or disclosure by the U.S. Government is subject 
to restrictions set forth in FAR 52.227-19 (Commercial Computer    
Software -- Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)    
(Rights in Technical Data and Computer Software), as applicable.


Trademarks

AutoCAD Map and ObjectARX are trademarks of Autodesk, Inc., in the 
USA and/or other countries.

All other brand names, product names or trademarks belong to 
their respective holders.


======================================================================
SAMPLE CODE for AutoCAD ObjectARX API
======================================================================

September 2003

These ObjectARX(TM) source code samples are designed to demonstrate 
the ObjectARX API for AutoCAD. They are not polished, and 
they do not constitute full tutorials, but they will give you some 
ideas about using this API to customize and extend AutoCAD.

Installation steps
------------------

1. Load the project into Developer Studio.

2. In the Project Settings, make sure the path is set up correctly in the C/C++ tab
   to have the Additional include directories pointing to where you installed ObjectARX
   (For example C:\ObjectARX\inc)

3. In the Project Settings, make sure the path is set up correctly in the Link tab
   to have the Additional library path pointing to where you installed ObjectARX
    (For example C:\ObjectARX\lib)


Loading the ObjectARX sample application
----------------------------------------

To load the sample application
1. Enter "ARX" on the Command Line of AutoCAD Map.
2. Choose Load, and then choose drawordersamp.arx in the file browser.


Using the sample
------------------

This sample demonstrates the use of  draw order API.

1. Create or open a drawing with multiple layers.


2. Type "sortbylayer" command. A dialog should show up. 
  	a. The listbox should list all the layers in the order that they are stored in the layer table.
	b. Click "List By Entity Order" button, layers in the listbox will be reordered based on the draw order of
	  the entities on each layer. The "*" around a layer name, indicates the draw orders of entities on that layer
	  are not continuous. At least one entity in that layer appears above the lowest entity on the following layer.
	  For example, "0,*L1*,L2" means all the entities on layer 0 are at the bottom of the drawing, i.e.,below entities of L1 and 
	  L2. However, At least one entity on Layer L1 is above the lowest entity in layer L2.
        c. You can drag and drop the layers in the list box to reorder the layers 
	d. Click "List Layer table" button. The list box will again list all the layers in the order that they are stored in the layer table.
	f. Click "apply" button, All the entities should be redrawn  based on the order of their layers in the list box.	

3. Type "draworderbylayer" command. 
   	a. Enter yes or just click enter key after the prompt "Order the draworder of all new entities based on the draw order of their layers? <Yes>/No"
	b. Draw an entity above the topmost entiy on a layer different from the topmost entity. The entity should be drawn behind the topmost entiy.
	c. type "draworderbylayer" command again.
	d. Enter no after above prompt
	e. Draw an entity above the topmost entity on a layer different from the topmost entiy. The entity is drawn above the topmost entity.
4. Type "reverseInLayer" command.
	a. A prompt shows up with the names of all the layers in the dawing.
	b. Choose one layer name.
	c. All the entities on that layer will be redraw in a reverse order.


 	
	
 




