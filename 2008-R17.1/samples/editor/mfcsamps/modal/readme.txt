mfcsamps\modal sample Readme.txt

 (C) Copyright 2001 by Autodesk, Inc.

This sample ARX application demonstrates how to use MFC in an ObjectARX 
application to put up a modal dialog with just two buttons: OK and Cancel.

The ARX command to be invoked is 'modal'

This sample uses MFC extension dll. It expects to have the same MFC DLL
as AutoCAD. The consequences of this for Production AutoCAD, which uses 
non-debug MFC, as follows:

- Debug target.
  The makefile will build a debug version of this sample with _non-debug_ 
  MFC & C Runtime libraries.

If you browse the codes, you'll notice the following:

// Turn off the _DEBUG symbol if it's defined, before including
// MFC header files.
#if defined(_DEBUG) && !defined(DEBUG_THIS_APP_ONLY)
    #define DEBUG_THIS_APP_ONLY
    #undef _DEBUG
#endif

#include <MFC_HEADER_FILES>

// Turn on the _DEBUG symbol if it was defined, before including
// non-MFC header files.
//
#ifdef DEBUG_THIS_APP_ONLY
    #define _DEBUG
    #undef DEBUG_THIS_APP_ONLY
#endif

#include <other header files here>

This code section is used to turn off _DEBUG symbol for all MFC headers 
when we're building a debug version. When _DEBUG is not defined for MFC headers,
it will pull in a non-debug MFC library. Because debug code in MFC is turned off,
your MFC code should not contain MFC debugging facility, such as CDump, 
AssertValid, and so on. However, it's still possible to debug into MFC source code.


