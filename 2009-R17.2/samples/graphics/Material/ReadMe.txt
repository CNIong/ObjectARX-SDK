Material Sample Readme.txt

(C) Copyright 2002-2006 by Autodesk, Inc.

This sample demonstrates the following:

1) How to use the AcDbMaterial API to create materials and assign
   them to custom entities. (MaterialUi project).
   
2) How to use the material dictionary to query, add, and remove 
   materials. (MaterialUi project).
   
3) How to implement a custom entity ObjectDBX enabler 
   (MaterialDb project).
   
4) How to implement an ObjectARX command (MaterialUi project).

5) How to use the AcadAppInfo class to perform self-registration
   for demand loading keys in the registry.  This is demonstrated for 
   simplicity only.  Generally registration of these keys should be 
   performed by an MSI installer.

6) How to apply the procedural materials, like speckle, tile, noise, 
   wave etc.  Also describes how to use the AcGiVariant class to set 
   the subtexture.

The project has two components:

1) AsdkMaterialDb.dbx - Defines the custom entity AsdkMaterial,
   which is a multi-polygon entity with materials applied to subentities.
   
2) AsdkMaterialUi.arx - Defines commands which allow the user to 
   manipulate materials and custom entities with materials applied to 
   them:

  Custom entity commands:
  
    MATENTADD  - Adds a custom entity with the current material assigned to it
    LSENTADD   - Adds a custom entity with the current landscape materail assigned to it
    
  Material commands:
                 
    MATLIST    - Lists the database materials.  Also lists the subtexture 
                 information with their properties.
    MATADD     - Adds a database material
    TEXMATADD  - Adds a database texture material (diffuse map)
    LSMATADD   - Adds a database material with these attributes:
                 - Diffuse map
                 - Opacity map
                 - Normal map
                 - Global illumination and final gathering disabled
                 - Advanced material mode
                               
    MATDELETE  - Removes a database material
    MATMODIFY  - Demonstrates modification of materials, cycling through several 
                 presets
    MATREPLACE - Replaces a given material or all materials in the database

    MATSPECKLE - Adds a database material with the Speckle map type.
    MATWAVE    - Adds a database material with the Wave map type.
    MATCHECKER - Adds a database material with the Checker map type.
    MATTILE    - Adds a database material with these attributes:
                 - Diffuse map with sub texture of procedural material type tile,
                   noise and speckle
                 - Bump map 

    Note: Sample diffuse, opacity, and normal map files are provided in the 
          Textures directory.  These files must be copied to a directory in the 
          AutoCAD Textures search path in order to be displayed.
