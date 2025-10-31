
This sample demonstrates how to use static MFC in an ARX application.
It is recommended to use dynamically linked MFC. Dynamically linked,
extension DLLs are the only method supported for using the AdUi and 
AcUi MFC extensions.
 
To use static.arx:
 
 1. Start AutoCAD
 
 2. Type the ARX command and load static.arx.
 
 4. Type the staticmfc command, defined by static.arx.
 
 5. A simple modal dialog box will be shown.
 
This sample uses static MFC lib that requires static runtime lib.
In order to use static MFC correctly, you must separate your MFC UI
code to link with the static library, but your database code should 
be using AutoCAD's runtime library.

