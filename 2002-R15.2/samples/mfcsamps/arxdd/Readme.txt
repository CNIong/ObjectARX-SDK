This sample display a window with four simple shapes. Users can drag a shape 
into AutoCAD drawing window by clicking and holding left mouse on the
window and drag it into AutoCAD window. When the mouse button is released,
the shape is inserted based on the parameter choosen.

Command:
- arxdd - to bring up the drag-drop window.

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


ARX CUSTOM DRAG AND DROP:
-------------------------

The fundamental of OLE/COM drag and drop is the IDropTarget and IDropSource
interfaces. In order for a window to become a drop target, it must have an 
IDroptarget associated with it. The AutoCAD dwg window has its own IDropTarget
registered to it at startup time.  However, when 3rd party applications want to
implement new behaviour of Drag&Drop operation, like pallette dragging 
(Visio's style), they need to somehow get involved in receiving Drag&Drop
events. 
The only way to recieve these events it to register their own IDropTarget
interface to the AutoCAD dwg window. By doing this, the 3rd apps have to write
their own IDropTarget and implement what kind of behaviors they want. They lose
the default Drag&Drop behaviors of AutoCAD dwg window, since only one IDropTarget
can be associated/registerd with a window. The registration of new IDropTarget
should be done before the 3rd party's DoDragDrop call and immediately switch it
back to default AutoCAD IDropTarget after the call.


The API:
--------
Only two functions provided:
BOOL acedRegisterCustomDropTarget(IDroptarget*);
BOOL acedRevokeCustomDropTarget();


The Pseudo Code:

Usually in Drag&Drop operation, a call is made to DoDragDrop(). This function 
basically takes care the whole process of Drag&Drop events. Before calling this 
function, IDropSource & IDataObject are prepared and sent as an argument to that function.
* Prepare an IDropSource
* Call DoDragDrop()


For custom drag drop, before we call DoDragDrop, we need to set the Acad Dwg
Window IDropTarget and immediately reset it afterwards.
* Prepare an IDropSource
* Call acedRegisterCustomDropTarget(IDroptarget*);
* Call DoDragDrop()
* Call acedRevokeCustomDropTarget();


The Sample:
The sample is a very simple one. basically it replaces AutoCAD IDropTarget with
its own. The new IDroptarget basically inserts a geometry based on size stored in
the IDataObject.

RoadMap:

Files that really matter:
- ArxDrawView.cpp
  In this file, at the OnLButtonDown event, an IDataObject is created and pass it
  to DoDragDrop call. Notice that it registers its own IDroptarget before the call
  and immediately revokes it. 
  
  Notice that the CArxdrawView register a dummy IDroptarget to its window during 
  OnInitialUpdate so that no Drop event can be done on its window.

- droptarget.cpp
  This is the implementation of IDroptarget that replaces the one from Acad Dwg view.
  Nothing fancy here, basically it reads IDataObject, figure out the geometry size
  and insert it if there's a drop event. During drag over, a tracker is drown using
  MFC facility. 
  Points to ponder:
  - converting Screen coordinate to AutoCAD World coordinate. A function called
    acedCoordFromScreenToWorld().
  - Need to find out in paper space based on tilemode etc. 
  - measurement, need to use standard one. In ArxDrawView window, a circle of
    radius 3 is different that that one from AutoCAD dwg window. 






