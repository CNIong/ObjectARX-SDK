
ArxWizards.msi Readme.txt

 (C) Copyright 2007-2008 by Autodesk, Inc.


How to install on Vista
=======================

The ObjectARX wizards will install successfully on Vista, if you either :

   1) disable 'User Account Control' before installing the wizard,

   2) launch the wizard installer from a command prompt launched with administrator privileges,


NB : if you are still having a problem, verify your antivirus do not prevent VBscripting to execute
     while installing the wizards. This is also



Known limitations
=================

A) Microsoft ATL wizards not working properly with ObjectARX COM wrappers.
--------------------------------------------------------------------------

Visual Studio is unable to add Method/Property elements to an ObjectARX 
COM wrapper class because ObjectARX COM wrappers derive from either: 

IAcadEntityDispatchImpl<>, or 
IAcadObjectDispatchImpl<> 

The scripts in the Microsoft Visual Studio Wizard checks first-level base classes 
only while searching for ATL::IDispatchImpl; as such, the wizard cannot find it 
in the ObjectARX COM Wrapper class and refuses to implement the members. 
(See <VSINSTALLDIR>\VC\VCWizards\1033\common.js line # 1913)

In previous releases of Visual Studio, a text search was performed in the class 
definition file. ObjectARX could work around this issue by adding code like the 
one below into the header file:

Previous workaround: 

   #ifdef NEVER
     //- Please do not remove the following line. It is here to make .NET ATL Wizards
     //- running properly. The parent class will not compile but is required by .NET to recognize
     //- this class as being an ATL coclass
         ,public IDispatchImpl
   #endif

However, since Visual Studio 2005, intellisense code and scripts are now based 
on a more intelligent code parser interpreting preprocessor symbols and this 
workaround does not work anymore.

Ideally, this Microsoft script should search recursively. However this may have 
a performance impact. A quick workaround is to change this script to also test 
for 'IAcadEntityDispatchImpl' and 'IAcadObjectDispatchImpl'. We are not permitted 
to ship modified versions of Microsoft's copyrighted scripts with our installer. 
However, if you would like further details of the required modifications, then 
please contact us at oarxwiz-feedback@autodesk.com, or via DevHelp Online for 
ADN members.
