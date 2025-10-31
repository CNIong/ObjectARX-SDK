
 (C) Copyright 1998 by Autodesk, Inc.
This sample application puts up a modeless dialog implemented with MFC.  
It also plants a database reactor on the current database and a document 
manager reactor on the active document in the MDI environment.  When any 
modifications are made to the database, the modeless dialog is updated to 
indicate what action was performed (i.e. append, erase, or modify), and what 
were the affected object's handle, AcDbObjectId, and AcRxClass.

The ARX command to be invoked is 'modeless'

This sample uses MFC extension dll. It expects to have the same MFC DLL
as AutoCAD. 

The consequences of this for Production AutoCAD, which uses non-debug MFC, 
is the following:
- Debug target.
  The makefile will build debug version of this sample with _non-debug_ 
  MFC & C Runtime libraries.

If you browse the codes, you'll notice the following:

// Turn off the _DEBUG symbol if it's defined, before including
// MFC header files.
#if defined(_DEBUG) && !defined(DEBUG_AUTOCAD)
    #define _DEBUG_WAS_DEFINED
    #undef _DEBUG
#endif

#include <MFC_HEADER_FILES>

// Turn on the _DEBUG symbol if it was defined, before including
// non-MFC header files.
//
#ifdef _DEBUG_WAS_DEFINED
    #define _DEBUG
    #undef _DEBUG_WAS_DEFINED
#endif

#include <other header files here>

Above code section is used to turn off _DEBUG symbol for all MFC headers 
when we're building debug version. When _DEBUG is not defined for MFC headers,
it will pull in non-debug MFC library. Because debug code in MFC is turned off,
your MFC code should not contain MFC debugging facility, such as CDump, 
AssertValid, etc. However, it's still possible to debug into MFC source code.

DEBUG_AUTOCAD symbol is for Autodesk internal use only.

There is another key area which is new. It is in regards to document switching.
Since we are in the MDI environment, the user can switch from one document view 
window to another during the middle of a command execution context. This may cause 
problems if it is not handled properly.

That's why an AcApDocManagerReactor is implemented to handle such cases. However, there 
are some events such as bring to foreground, min/max/restore the frame window, are not
handles yet from the point of using ObjectARX API.
