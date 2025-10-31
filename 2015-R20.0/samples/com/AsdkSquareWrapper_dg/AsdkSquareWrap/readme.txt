This example is an ATL COM wrapper for an ObjectARX custom entity. This project
builds a DLL that will be loaded when COM access to the custom entity is
requested (for example, by the Property Palette).

It works with the square sample application found in the adjacent subdirectory.

Build this project first.  It will fail with an error that it cannot open
square.lib (which comes from the square sample).  But, it will successfully
generate the AsdkSquareLib_i.c, AsdkSquareLib_i.h, and AsdkSquareLib.tlb files
that are needed by the square sample in order to build the square.lib file that
this project requires. 

Once the AsdkSquareLib_i.c, AsdkSquareLib_i.h, and AsdkSquareLib.tlb files are
generated, then build the square sample.  Once that is completed, come back to
this project and build it again to complete generating the AsdkSquareLib.dll file.

This sample demonstrates the use of the DllRegisterServer() to perform
self-registration for the COM server defined. This is demonstrated for simplicity
only. Generally registration of these keys should be performed by an MSI installer.