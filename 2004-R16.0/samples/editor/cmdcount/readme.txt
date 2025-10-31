Cmdcount sample Readme.txt

 (C) Copyright 2001 - 2002 by Autodesk, Inc.

Command Counter Sample ARX Application

README.TXT updated January 10 2003.

The Command Counter
application records the number of times each AutoCAD command,
AcEd-registered command, or AutoLISP expression evaluation
is invoked, plus the cumulative time spent with the command
or expression evaluation active. 
 
This information is accumulated across edit sessions in a
separate ASCII file, only one for each login name used in an AutoCAD
edit session. For a single user installation, only one login name,
and thus one file, is typically created and maintained.

The application was created for use in the R14 Alpha and Beta
programs to monitor site usage of AutoCAD features. It has since
been used by product marketing for researching AutoCAD feature use
in R13c4 and c4a installations.  It has now been upgraded to operate
with AutoCAD 2004, although it is no longer used by the original
clients. It has been considered useful by other developers, as
evidenced by the number of suggested improvements to it.  However,
it wasn't intended as a feature to be supported for the majority
of AutoCAD users.  So if you really want it done right, you should
do it yourself.

Take the source file, an ARX app development environment, and
do whatever you want with it, subject to all the legal disclaimers
listed in the source file header.  In summary, Autodesk isn't
responsible for any damage that comes from running the program
or interpreting the results.


AutoCAD 2004 Installation
-------------------------

Build the CMDCOUNT sample application, and place the resultant
"CMDCOUNT.ARX" module on an accessible file system folder.  
Next, use the ARX AutoCAD command to manually load "CMDCOUNT.ARX".
Once loaded, the sample registers itself for demand loading on
command invocation (i.e.loads when any CMDCOUNT commands are issued)
and optionally demand loads on startup.  Use the 'CMDCOUNT' command 
itself to control whether the sample autoloads on startup 
(by responding to "Load CmdCount on start up?").

To Use CMDCOUNT
---------------

If you responded 'Y" to the CMDCOUNT command as described above, it will
automatically load every time you start AutoCAD. Either way, at this point
the sample is recording command usage, and is writing the statistics to
an output file.

To view the statistics, either for the current session or the 
cumulative statistics, enter the CMDSTAT command, which has two
options.  Enter the <CR>, or "S" option to list the usage
statsistics for the current AutoCAD invocation.  
Or, enter "C" to examine cumulative statistics, after the current
session stats are merged in and reset.  Switching edit sessions
doesn't reset session statistics, but examining cumulative
statistics causes the session statistics to be merged with the
cumulative statsistics and then cleared.

The session statistics are also merged with the cumulative statistics
set whenever a drawing SAVE or WBLOCK command is performed, and
whenever AutoCAD terminates.

CMDCOUNT cannot be unloaded once it is loaded into an AutoCAD session.
It remains active until AutoCAD terminates.

After exiting AutoCAD, you can examine the output file with an ASCII
text editor of your choice.


The Accumulated Statistics File
-------------------------------

Looking at the file in an ASCII editor should tell you the results
of the operation quite clearly. But here is some further information,
including name and the directory it will be located in.

The information is accumulated in a file named <userid>.txt, where
<userid> is the login name for the current AutoCAD session (which
is typically set during AutoCAD configuration). To derive the
filename from the <userid>, the Command Counter strips out white
space, and truncates the name after 8 characters. So
<userid>="James Strzelec" would generate an output file called
"JamesStr.txt". The output file lists the number of times each
command and LISP expression has been invoked since the creation
of the file, along with the total elapsed time, to the 1/100 of
a second. In its header, it lists the version of the output file 
format (currently v1.2), CreateDate of the file, LastModifiedDate
of the file, USERID, AutoCAD serial number, and AutoCAD version.

The decision of where to store <userid>.txt is made by CMDCOUNT
as follows:

1. It checks the following registry value
HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\AutoCAD\R16.0\ACAD-1:409\Applications\AcadCmdCount\StatPath = <path>
   If this value is present then <path> is used. 

2. If the registry entry listed in #1 does not exist then CMDCOUNT
   looks in the MyDocuments folder of the currently logged on user.

3. If both #2 and #3 fail then CMDCOUNT tries to find <userid>.txt
   on the AutoCAD search path.

If CMDCOUNT doesn't find the output file, it creates the output
file in #1 if the registry entry is present otherwise it creates
it in MyDocuments.

If you edit the file and change the format,
the command counter will either terminate, or fail, depending on what was done.
Checking is minimal.


Internal Logic Notes
--------------------

Internally, the application is quite simple.  It defines an AcEditorReactor with 
callbacks for all events related to commands and lisp expression evaluations, 
and accumulates statistics in an AcRxDictionary.  It has functions to load and 
store a dictionary of statistics to and from an ASCII file format.  It has a 
function to merge one dictionary's statitistics with another. Its capabilities
measurement are essentially defined by the event callbacks available in the ARX
libraries.

This application only accounts for actions invoked through the main AutoCAD
Command Processor and LISP interpreter. It does not count actions directly
invoked via Windows events using the toolbar, or direct Windows 
tiles, or OLE Automation.

Command count measures the following:

The time between the start and end of the command,as measured by corresponding
AcEditorReactor notification callbacks. The relevant member functions are:

    // Command Events
    //
    // Begin timing
    virtual void commandWillStart(const char* cmdStr);

    // End timing
    virtual void commandEnded    (const char* cmdStr);
    virtual void commandCancelled(const char* cmdStr);
    virtual void commandFailed   (const char* cmdStr);
 
    // Lisp Events
    //
    // Begin timing
    virtual void lispWillStart   (const char* firstLine);

    // End timing
    virtual void lispEnded       ();
    virtual void lispCancelled   ();

The time measured includes time elapsed while waiting for input
from the user.

A command is an operation that can be entered at the AutoCAD command line
and does not typically use AutoLISP in its execution.  It can be a built in
command, or a command registered from an ARX application via the
acedRegCmds object. Virtually all AutoCAD actions, especially those typically
invoked from menu or toolbar picks, are invoked by passing a string to the
command processor, which in turn invokes the command line form of the command.

A LISP expression is defined in the AutoLISP section of the Customization
Guide and, most importantly, includes functions registered in a call to
ads_defun()/acedDefun() in ARX applications.

Statistics are kept for each unique global command name and each
initial string in the AutoLISP expression up to the first white space
character, after folding the case. 

Whenever a LISP expression invokes the command facility to pump commands into
AutoCAD, the commands so invoked are counted as if they were invoked in any
other context.  The LISP expression will also continue to be timed, so
"double-timing" occurs.

Also, as of July 16, 1998, if the transparent command facility is used (by
prefixing supported commands with an apostrophe ('), only the active command
accumulates time.

When documents are switched in MDI, only the active command in the active
document accumulates time, but the state in the suspended documents is tracked.

When the built in command processor is idle awaiting a next command, and
AutoLISP is not currently evaluating an expression, time is not 
accumulated in any statistics.
 
Cumulative statistics are updated during all operations that lead to
internal DWG file save or wblock operations. Time automatic saves are included.
The following commands cause an update: SAVE, SAVEAS, AUTOSAVE,
and WBLOCK. Please be aware, other commands and custom ARX applications can also
cause these operations, especially wblock() as they are executed.

The application is not intended to affect system actions in any way, it 
merely measures them.  If anything goes wrong while using the command counter, 
the best advice is to uninstall it.  The application has been benchmarked, 
and found not to significantly affect system performance.  It consumes 
relatively little memory, perhaps 250 bytes per cumulative command invoked, 
plus a few K overhead.

Apart from this, the one source module, CMDCOUNT.CPP which defines everything
else.

