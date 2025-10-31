The oemployapp application demonstrates a simple technique in which the ObjectARX application implements a very thin wrapper on top of the AutoCAD ActiveX objects.

The sample illustrates how to create subsets of and extend the AutoCAD ActiveX object model implemented by the AutoCAD OEM engine.

To minimize the amount of work to be done, the oemployapp sample reuses the
AutoCAD ActiveX Automation objects as often as possible to implement its
own ActiveX interface. 

---------
WARNING! AutoCAD OEM developers cannot export an ActiveX Automation
API that offers functionality equivalent in breadth to the ActiveX Automation
API supplied by the AutoCAD product. The API supplied by the AutoCAD product
offers access to all significant elements of the AutoCAD database and directly
corresponds to the logical structure of DWG and DXF files. The interface that you
provide must be specific to your product, and must include only the functionality
necessary for your product. As part of the product validation process,
Autodesk, Inc. will explicitly review and approve ActiveX Automation APIs
offered by OEM developers. If you have any doubt whether your ActiveX Automation
plans are appropriate, please contact your ADC Sales representative.
---------

The oempolyapp sample application gives an example of this, exporting the
following object model:
    AutoCAD Application
          |  
          |-- Prefences
          |       |
          |       |---- PreferencesDisplay
          |       |---- PreferencesDrafting
          |       |---- PreferencesFiles
          |       |---- PreferencesOpenSave
          |       |---- PreferencesOutput
          |       |---- PreferencesSelection
          |       |---- PreferencesSystem
          |       |---- PerefencesUser
          |
          |
          |-- Documents
          |       |
          |       |
          |   Document
          |       |
          |       |---- SelectionSets --- SelectionSet
          |       |---- Plot
          |       |---- Utility
          |
          |-- MenuBar
          |
          |-- MenuGroups
                  |
                  |---- PopMenus
                  |        | 
                  |     PopMenu
                  |        |
                  |     PopMenuItem
                  |        
                  |---- Toolbars
                           |
                        Toolbar
                           |
                        ToolBarItem
                                               
See AutoCAD OEM developer guide, using COM and ActiveX Automation chapter, for more information about this sample, including steps by steps how to create this project.