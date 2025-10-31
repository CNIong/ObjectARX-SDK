ISM Sample Readme.txt

 (C) Copyright 2001-2002 by Autodesk, Inc.

ABOUT
=====

This example creates two image entities of one image definition object.
It transforms and clips one of the image entities.


START
=====

First load acIsmui.arx. ISM stands for Image Support Module.

Then load IsmExample.arx. 
If this does not exist, you need to build it. Please see the Build section.

In order for the arx application to load the image, add the image directory to 
the preferences project directories (command PREFERENCES), and set this 
project as the current project (Set Current).
		
Start the example executing the command ISMEXAMPLE from the command line.

This command shows one clipped image on top of on image. 

You can zoom out to see that the clipped image is placed on a large image.


CLASSES
=======

EXAMPLE

CustomApplication

The single class of this example is called CustomApplication.

Purpose:   Example class of using the Image Support Module (ISM).
           It can attach an image by creating an entity, definition, and reactor.
           It can also add the object to the model or paper space.

Problems:  The image path has to be updated in the newImageAttach method.

If the path of the image atoll.jpg changes and you run into problems executing 
the example, please see the section "Problems: Cannot load the image:."


ISM
---

The classes that uses the example from the ISM library are:
AcDbRasterImage
AcDbRasterImageDef
AcDbRasterImageDefReactor
AcDbRasterVariables

For information about this classes and additional classes of the ISM API 
please see ARX Reference Help.



FILES
=====

IsmExample.dsp and IsmExample.dsw 
    IDE files of the example.

access.h
    Prototypes of the access function.
access.cpp
    Manages the access from AutoCAD to the CustomApplication class.

CustomApplication.h 
    Definition of the CustomApplication class.
CustomApplication.cpp
    Definition of its methods.

atoll.jpg
	Image file that the example uses.



BUILD
=====

The makefile has relative paths and works from the location:
samples\misc\ism.

You can add the image directory to the preferences project directories 
(command PREFERENCES) and set this project as the current one (Set Current).


PROBLEMS
========

ATTACHING THE SAME IMAGE DEFINITION AGAIN:

Running the example for a second time causes an error message.
This is because you tried to attach an image definition object with a name 
that already exists in the dictionary.


SOLUTIONS:

Detaching the definition object manually:
You can detach the definition object manually. Use the command IMAGE, 
select the definition object of the image "atoll", and press the "DETACH" button.


Change of code:
You can use the API method suggestName of the class AcDbRasterImageDef 
to get an unused image name. See ARX Reference Help for further information
about the ISM API.


Change of code:
In the method createAcDbRasterImageDef, there is a check for the image name: 	
        // Check if image name already in use.
It returns the value Acad::eHandleInUse, if the state is "name in use".
You need to get the object Id of this image definition object and allow
the error status Acad::eHandleInUse in the method newImageAttach after:
        // Create image definition object.
This solution has the advantage over the previous solution that it does not create
an additional definition object. This saves a lot of memory.



CANNOT LOAD THE IMAGE:

The error occurs because the path could not be found.
In this example in the method newImageAttach of the class CustomApplication, 
the name and the path of the image are defined.
        // definition
	ImageName = "atoll";
	ImagePath = "atoll.jpg";

In this case the path is the active directory.  


SOLUTIONS:

Manually:
Set in Preferences (command: PREFERENCES), Files, Project Files the path of the image atoll.jpg,
and set this project to your active one (Set Current). 


Change of the code:
Change the variable value of ImagePath. Be sure to use double backslashes "\\". 
The image path also includes the filename and extension itself.

Example:
         ImagePath = "C:\\PROGRAM FILES\\ObjectARX 2002\\samples\\misc\\ism\\atoll.jpg";

