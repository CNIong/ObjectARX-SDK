This sample demonstrated how to add an additional content
for the Autodesk Design Center, such as a DWF file.

It is basically a in-proc COM server that will be loaded into Acad
memory space. It is necessary to load the DesignCtrSample.arx manually into 
Acad the very first time so it is registered.

Here are the steps to create the project:

1. Use Atl Com AppWizard to create a dll, choose "Support MFC" and
   include "ISupportErrorInfo";
2. Manually delete CWinApp derived class and its implementation;
3. Add acrxEntryPoint() and DllMain() and appropriate headers; Note that 
   DllMain will alway be called first whether the app is loaded as a COM 
   DLL or an ARX app. acrxEntryPoint() will be called after DllMain() is 
   called when the user loads the app as an ARX app;
4. Change project settings to ObjectARX 3.0 standards. Need to export 
   acrxGetApiVersion function in the DEF file;
5. Add an Interface Object called IDesignCtrSampleObject.
   Add CWindowImplBase and IAcCeContentView to the base class list;
   Override some base class methods;
6. Insert app_registry.rgs as a new "REGISTRY" resource and setup a
   runtime swappable module called "%AUTH%". This rgs file will be 
   explicitly loaded;
7. Insert the Whip component into the project and the CWhip wrapper class
   is generated;
8. Add a class that is derived from CMDIChildWnd. Add some code to hook the 
   window creation up with the DesignCtrSampleObject actions.

Note: It is required that Whip 3.x is installed on the computer where
this sample is going to be used.
You can download it from:
http://www.autodesk.com/cgi-bin/whipreg.pl