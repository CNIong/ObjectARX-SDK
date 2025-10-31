Mfcsamps\contextmenu sample Readme.txt

 (C) Copyright 2001 by Autodesk, Inc.

This sample application shows how to add menu items to AutoCAD context menus
in command, default, and edit mode menus.

For the command mode, it registers the command "sample" and adds menu
items for the command. Since this command does not have any options, the
sysvar SHORTCUTMENU has to be set to 7 for the menu to appear.

For the default mode, the application tries to add two menus, but since each
application is restricted to adding just one menu, the second menu is ignored.
The default mode menus are cascaded off the AutoCAD context menus. The
name to be used as the cascading menu label can be supplied. If no name
is given, we use the name of the application minus the extension.

For edit mode, menu items are added to AcDbEntity, AcDbLine and AcDbCircle.
The menu items for AcDbEntity show up for all type of entity selections.
Those for AcDbLine and AcDbCircle show up only when all lines or
all circles are selected respectively.

This sample uses MFC dll. It expects to have the same MFC DLL
as AutoCAD. 
The consequences of this for Production AutoCAD, which uses non-debug MFC, 
are as follows:

- Debug target.
  The makefile will a build debug version of this sample with _non-debug_ 
  MFC & C Runtime libraries.

If you browse the codes, you'll notice the following:

// Turn off the _DEBUG symbol if it's defined, before including
// MFC header files.
#if defined(_DEBUG) && !defined(DEBUG_THIS_ONLY)
    #define DEBUG_THIS_ONLY
    #undef _DEBUG
#endif

#include <MFC_HEADER_FILES>

// Turn on the _DEBUG symbol if it was defined, before including
// non-MFC header files.
//
#ifdef DEBUG_THIS_ONLY
    #define _DEBUG
    #undef DEBUG_THIS_ONLY
#endif

#include <other header files here>

this code section is used to turn off _DEBUG symbol for all MFC headers 
when we're building a debug version. When _DEBUG is not defined for MFC headers,
it will pull in a non-debug MFC library. Because debug code in MFC is turned off,
your MFC code should not contain MFC debugging facility, such as CDump, 
AssertValid, etc. However, it's still possible to debug into MFC source code.

The DEBUG_AUTOCAD symbol is for Autodesk internal use only.