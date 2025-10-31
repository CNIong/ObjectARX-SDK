mfcsamps\modeless sample Readme.txt

Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   

MODELESS:

This sample application displays a modeless dialog implemented with MFC.  
It also plants a database reactor on the current database and a document 
manager reactor on the active document in the MDI environment.  When
modifications are made to the database, the modeless dialog is updated to 
indicate which action was performed (that is, append, erase, or modify), and
what were the affected object's handle, AcDbObjectId, and AcRxClass.  Additionally, 
UNDO capability is provided from the context of the modeless dialog immediately 
following an alteration in a database entity.

The ARX command to be invoked is MODELESS.

This sample uses the MFC extension dll. It expects to have the same MFC DLL
as AutoCAD. 

The consequences of this for Production AutoCAD, which uses non-debug MFC, 
are the following:
- Debug target.
  The makefile will a build debug version of this sample with _non-debug_ 
  MFC & C Runtime libraries.

If you browse the codes, you will notice the following:

// Turn off the _DEBUG symbol if it's defined, before including
// MFC header files.
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
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

The above code section is used to turn off _DEBUG symbol for all MFC headers 
when we're building a debug version. When _DEBUG is not defined for MFC headers,
it will pull in non-debug MFC library. Because debug code in MFC is turned off,
your MFC code should not contain MFC debugging facility, such as CDump, 
AssertValid, and so on. However, it's still possible to debug into MFC source code.

The DEBUG_AUTOCAD symbol is for Autodesk internal use only.

There is another new key: document switching.
Since we are in the MDI environment, the user can switch from one document view 
window to another during a command execution context. This may cause 
problems if it is not handled properly.

That's why an AcApDocManagerReactor is implemented. However, there 
are some events such as bring to foreground, or minimizing, maximizing, restoring
the frame window, that are not handled yet from the point of using the ObjectARX
API.
