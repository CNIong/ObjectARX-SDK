This sample app shows how to add menu items to AutoCAD context menus
in command, default and edit mode menus.
 (C) Copyright 1998 by Autodesk, Inc.

For the command mode it registers the command "sample" and adds menu
items for the command. Since this command does not has any options, the
sysvar SHORTCUTMENU has to be set to 7 for the menu to appear.

For the default mode, the app tries to add two menus, but since each
app is restricted to adding just one menu, the secon menu is ignored.
The default mode menus are cascaded of the AutoCAD context menus. The
name to be used for cascading menu label canbe supplied. If no name
is given we use the name of the app minus the extension.

For edit mode, menu items are added to AcDbEntity, AcDbLine and AcDbCircle.
The menu items for AcDbEntity will show up for all type of entity selections.
Those for AcDbLine and AcDbCircle will show up only when all lines or
all circles are selected respectively.

This sample uses MFC dll. It expects to have the same MFC DLL
as AutoCAD. 
The consequences of this for Production AutoCAD, which uses non-debug MFC, 
is the following:
- Debug target.
  The makefile will build debug version of this sample with _non-debug_ 
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

Above code section is used to turn off _DEBUG symbol for all MFC headers 
when we're building debug version. When _DEBUG is not defined for MFC headers,
it will pull in non-debug MFC library. Because debug code in MFC is turned off,
your MFC code should not contain MFC debugging facility, such as CDump, 
AssertValid, etc. However, it's still possible to debug into MFC source code.

DEBUG_AUTOCAD symbol is for Autodesk internal use only.