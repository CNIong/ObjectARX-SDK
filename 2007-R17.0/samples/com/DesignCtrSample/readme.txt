DesignCtrSample sample Readme.txt

(C) Copyright 2006 by Autodesk, Inc.

This sample demonstrates how to add additional content, (such as
a DWG file), to the Autodesk Design Center.

The application is basically a in-proc COM server that will be loaded into
AutoCAD's memory space. Please note that you must load the DesignCtrSample.arx 
manually into AutoCAD the first time to run it so that registers COM CLSID's correctly.

Here are the steps to create the project manually: 
  (alternatively, you can install the ObjectARX Wizard Visual Studio Addin)

1. Use Atl Com AppWizard to create a dll, choose "Support MFC" and
   include "ISupportErrorInfo".
2. Manually delete the CWinApp derived class and its implementation.
3. Add acrxEntryPoint() and DllMain() and appropriate headers; Note that 
   DllMain will alway be called first whether the app is loaded as a COM 
   DLL or an ARX application. acrxEntryPoint() will be called after DllMain() is 
   called when the user loads the application as an ARX application.
4. Change project settings to ObjectARX standards.  
      Then either: 
              create your own .def file and export the acrxEntryPoint and acrxGetApiVersion functions.
        or 
              define the following text in your main cpp
                #pragma comment(linker, "/export:_acrxGetApiVersion,PRIVATE")
                #pragma comment(linker, "/export:_acrxEntryPoint,PRIVATE")
        or    use the AcRxDefault.def file found in the ObjectARX/inc folder
                
5. Add an Interface Object called IDesignCtrSampleObject.
   Add CWindowImplBase and IAcCeContentView to the base class list.
   Override some base class methods.
6. Insert app_registry.rgs as a new "REGISTRY" resource and setup a
   runtime swappable module called "%AUTH%". This rgs file will be 
   explicitly loaded.
7. Insert the Whip component into the project and the CWhip wrapper class
   is generated.
8. Add a class that is derived from CMDIChildWnd. Add some code to hook the 
   window creation up with the DesignCtrSampleObject actions.

Note: The whip control is available from
      http://www.autodesk.com


This sample demonstrates the use of the DllRegisterServer() to perform self-registration
for demand the COM server defined. This is demonstrated for simplicity only.
Generally registration of these keys should be performed by an MSI installer.