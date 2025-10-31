Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   

Input Point API Sample Readme.txt
=================================

This sample applications show how to define three classes which provide
you with information from the Input Point complex.

1. An AcEdInputPointMonitor   - for watching point input events
2. An AcEdInputPointFilter    - which can also make modifications to the selected point
3. An AcEdInputContextReactor - for getting notification on acedGetXXX (and similar) calls

The Files
---------
Main.cpp         acrxEntryPoint and command definition
Filter.h         AsdkInputPointFilter declaration
Filter.cpp       AsdkInputPointFilter definition
Monitor.h        AsdkInputPointMonitor declaration
Monitor.cpp      AsdkInputPointMonitor definition
Reactor.h        AsdkInputContextReactor declaration
Reactor.cpp      AsdkInputContextReactor definition
InputPoint.def   Library definition file
ReadMe.txt       This file

The Commands
------------

The following commands are implemented by the application:

Global name     Local Name      Action
-------------------------------------------------------------------
AddMonitor      ADDMON          Adds our custom monitor
RemoveMonitor   REMMON          Removes our custom monitor
AddFilter       ADDFIL          Adds our custom filter
RemoveFilter    REMFIL          Removes our custom filter
ChangesOff      CHOFF           Tells the filter to perform changes
ChangesOn       CHON            Stops the filter making changes
AddReactor      ADDREAC         Adds our custom reactor
RemoveReactor   REMREAC         Removes our custom reactor
CursorOff       CUROFF          Turns the system graphics on
CursorOn        CURON           Turns the system graphics off
ForcedPickoff   FPOFF           Turns on the forced pick mode
ForcedPickon    FPON            Turns off the forced pick mode


Typical usage after loading the application:

ADDMON to add the monitor
Move the cursor to see the feedback in the reactor
Try some standard commands (such as LINE)
REMMON to remove the monitor

ADDFIL to add a filter
CHON to allow the filter to make changes
Try some standard commands (such as LINE)
REMFIL to remove the filter

ADDREAC to add a reactor
Try some standard commands (such as LINE)
REMREAC to remove the filter
