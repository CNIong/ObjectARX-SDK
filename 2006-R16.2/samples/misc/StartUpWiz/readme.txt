
This sample demonstrates how to create a very basic Start-up wizard for AutoCAD or OEM.

The StartWiz.arx application has two commands: StartWiz and ShowWiz.

StartWiz:  This brings up the start-up dialog.  The buttons are self-explanatory; there is also
a Help button that users can click on to get more information on each button.

ShowWiz:  If the Hide option was checked in the dialog, then the StartWiz command will not bring 
the dialog back up.  In such cases, the ShowWiz command should be used.

To hook this application into the startup dialog, you will need to add the appropriate registry
entries.  The AcadStartWiz.reg file contains the registry entries necessary for use with acad.exe.
The AoemStartWiz.reg file contains the entries necessary for OEM.  You will need to edit whichever
file you use to set the correct path to the location of startwiz.arx file.  You might also need
to change the AutoCAD cookie (the "ACAD-301:409") in the registry keys in the .reg file to match
the language version of your AutoCAD.  Look at the existing AutoCAD entries in the registry to
see if this change is necessary.

For more information about hooking custom wizards into the startup dialog, please see the "Adding
Custom Wizards" topic in the ObjectARX Developer's Guide.
