This sample extends the "third" sample, showing how to implement snapping to divisions along
curves with a set of template classes.

The standard application sets up object snap modes to snap to divisions of 3, 4, 5.

Some useful boilerplate macros have been defined to reduce the effort in adding a new mode.
See DivOsnap.h for the implementation of these macros.


To add a new mode:
==================

At file scope:
--------------
1. Instantiate an object describing your osnap mode, passing in parameters for mode string,
   tooltips etc.

AsdkDivOsnapMode<6> sixthMode( "SIXth","_SIXth","Sixth of length", "1/6" );

2. Use the standard ObjectARX macro call to define the class's members. This cannot be in the
header (as would normally be done), as we need one per class, not per template definition.

ACRX_NO_CONS_DEFINE_MEMBERS( AsdkDivOsnapInfo<6>, AcDbCustomOsnapInfo );

In your initialization function:
--------------------------------
3. Initialize your class description object etc. to be added into the RX class hierarchy.

AsdkDivOsnapInfo<6>::rxInit();

4. Use a macro to register the protocol

ASDK_DEFINE_DIVISOR_OSNAP(6,sixthMode,"_sixth");

In your termination function:
-----------------------------
5. Delete the class description object from the RX class hierarchy.

deleteAcRxClass( AsdkDivOsnapInfo<6>::desc() );

In the command code:
--------------------
6. Optionally tell your class when the "snap2seg" and "snap2pline" commands are called.

ASDK_DIVISOR_SNAP_TO_SEG(6);

and

ASDK_DIVISOR_SNAP_TO_PLINE(6);


Commands:
=========
SNAP2PLINE      Chooses to snap to a third of each polyline segment
SNAP2SEG        Chooses to snap to a third of the whole polyline


Classes:
========
AsdkDivOsnapInfo          abstract base class for the protocol extension
AsdkDivOsnapEntityInfo    generic definition providing no functionality
AsdkDivOsnapCurveInfo     generic function for all curves, except AcDbPolylines
AsdkDivOsnapPolylineInfo  specialised function for AcDbPolylines and derived classes

AsdkDivOsnapMode          object snap mode describing the third object snap
AsdkDivGlyph              glyph definition


Notes:
======
Due to a compiler bug in MSVC with nested template classes (see Microsoft Knowledge Base Q128789), each
of the template methods have been defined inline. For this reason there is only one .cpp
file.