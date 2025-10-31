(C) Copyright 2007-2008 by Autodesk, Inc. 

QuickProperties/Rollover Tooltips ObjectARX API Sample

This sample demonstrates how to implement Static Properties using the OPM_ENTRY() macros, Dynamic Properties
using the per-instance IPropertySource interface and the QuickProperty/Rollover API's IFilterableProperty and 
IFilterableSubtypePropertySource.
 
API's used in this sample are as follows:

IPropertySource - per-instance Dynamic Property interface
IDynamicProperty2 - Dynamic Property interface
IFilterableProperty - allows the developer to control which properties appear in the QuickProperties/Rollover
IFilterableSubtypePropertySource - allows developer to provide subtypes for his properties in QuickProperties
 
The commands implemented are:
 
addEnt - Creates an asdkMyEntity, Zooms to it, then PICKFIRST select it for editing with the Properties Palette


USEAGE:
------

1) Run the command addEnt, it will create an asdkMyEntity, it then zooms to its extents, then pickfirst selects.
2) Notice the properties in the Property Palette - the per-instance Dynamic Property will create an extra
    string input on selection if the "My Type" option is set to "With Text" or "Thickness with Text" making a 
    total of 3 Dynamic Properties.
3) Now run the CUI and Navigate to the QuickProperties entry and select to add Properties.
4) Notice the "My Entity" entry in the QuickProperties, select Properties as desired.

NOTES:

The QuickProperties/Rollover feature allows the user, via the CUI, to specify which commonly used properties he wants
to appear on the QuickProperties ribbon panel. 
The QuickProperties/Rollover configuration which is done via the CUI simply creates a temporary instance of all the registered
AcDbEntity derived classes in a drawing and then polls the Properties so that it presents these to the user 
for his preferred property filter.

There are 2 types of Properties in AutoCAD, Static and Dynamic; of these 2, Dynamic has 2 subtypes - 
per-class and per-instance. 

  NOTE: All of the QuickProperty/Rollover interfaces that are described below are only required when there are special 
  rules that govern the display of your properties. If your set/number of properties is always the same then ie
  no instance specific rules governing their display then you do not need to implement IFilerterable* interfaces as
  QuickProperties/Rollover handles it automatically for you - but please read this whole document to be sure.

  For Static properties, only one interface is possibly required by QP/RO - this is the 
IFilterableProperty; the same occurs for Per-class registered Dynamic properties. The main work is required 
if the developer implements per-instance properties, for this type of property there are 4 interfaces
IFilterableProperty, IFilterablePropertySource, IFilterableMultiplePropertySource and IFilterableSubtypePropertySource.
  The reason that there are so many interfaces for per-instance properties is because when the QuickProperties/Rollover 
CUI configuration feature creates an Object temporarily (see below item on AcDbPropertyFilterCustomizationPE)
to poll the properties from it your rules that govern the "per-instance" Dynamic Properties display may 
not be properly adhered to, therefore these interfaces exist to allow the developer to specify what 
properties are availble.      

This sample is intended to show in the simplest way:

1) Static Property implementation, using the simplest form of property registration - OPM_ENTRY() - see MyEntityWrapper.h/.cpp
  QP/RO interface - IFilterableProperty
    The IFilterableProperty in this example simply shows all properties regardless, there are no rules built in - 
    it's just to show how to implement it.
    
2) Per-Instance Dynamic Property implementation - see MyEntityDynProp1,2,3.h/.cpp
  QP/RO interface - IFilterableProperty
    The IFilterableProperty used in each of the 3 Dynamic Properties, this implementation simply shows all 
    properties, there are no rules built in - it's just to show how to implement it.

  QP/RO interface - IFilterableSubtypePropertySource
    This is the most complex interface that you can use on per-instance Dynamic Properties. It has 
    been implemented to show the subtypes of asdkMyEntity of "Normal", "With Text" and "Thickness with Text". 
    "With Text" and "Thickness with Text" both show an extra String input.
    

AcDbPropertyFilterCustomizationPE - this Protocol extension allows the developer to override the creation method
that the QuickProperties/Rollover uses to create the temporary Object which it polls the properties from. This is useful
where you may need special initialisation for complex entities or maybe interlinked entities which rely on each
other. 