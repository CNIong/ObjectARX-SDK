
This example is an ATL COM wrapper for an ObjectARX custom entity. This project builds a DLL that will be loaded when COM access to the custom entity is requested (for example, by the Property Palette).

It works with the square sample application found in the adjacent subdirectory.

Build the square sample first, then build this project. This project uses the square.lib file produced by building the square sample.

This sample demonstrates the use of the DllRegisterServer() to perform self-registration
for the COM server defined. This is demonstrated for simplicity only.
Generally registration of these keys should be performed by an MSI installer.