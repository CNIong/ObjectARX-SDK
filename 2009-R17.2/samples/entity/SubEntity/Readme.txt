Sub Entity Readme.txt
(C) Copyright 2006 by Autodesk, Inc.

SliderCrank
------

The SliderCrank application demonstrates the sub-entity selection manipulation feature available in the AutoCAD. The sub-entity selection manipulation feature is demonstrated by using a custom entity "AsdkSliderCrank". 

The AsdkSliderCrank custom entity consists of a Crank and Piston which is connected by a link with a connecting pin at both the ends. The Crank, Piston, Connecting Link and Pin are drawn as sub-entities in the AsdkSliderCrank custom entity.

The SilderCrank sample demonstrates the following sub-entity selection manipulation feature:

1) Supports sub-entity selection and extracting the sub-entity information from the selection sets.
2) Provide right-click menu support on selected sub-entities.
3) Sub-entity grips on selected sub-entities.
4) Implements COM wrapper for the sub-entities.

****
Testing the application:

1) Load AsdkSliderCrankDb.dbx and AsdkSliderCrankUi.arx directly into AutoCAD.

2) Type the command "AddSliderCrank":
	a) This command creates a default AsdkSliderCrank in the model space. By clicking on the AsdkSliderCrank, the default grips are visible. To select the individual sub-entity i.e. Crank, Piston or Connecting Rod, hold the "ctrl" key pressed and select the sub-entity.

	b) On selecting the sub-entity, the sub-entity grips will appear on the screen. For example, if the connecting rod is selected, two grip points along the rod will be enabled. Using these grip points, the position of the connecting rod can be modified at both ends.

3) Type the command "MoveSliderCrank":
	a) This command will allow users to select the sub-entities of AsdkSliderCrank and the selected sub-entity will be translated by 10 units. To allow the user to select the sub-entity in a command, acedSSGet() method is used with “:U” mode.

4) Context menus: 
	a) The color of the sub-entity can be modified using the context menu. By right clicking on the sub-entity on the slider crank, the context menu will list the menu items to change the color of the selected sub-entity.

5) Property Palette:
	a) Property Palette will display the properties of the sub-entity selected. For example, if the piston sub-entity is selected the size and the skirt-length of the piston will be displayed.
