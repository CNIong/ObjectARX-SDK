
 (C) Copyright 1998 by Autodesk, Inc.
Command Counter Sample ARX Application

README.TXT Updated January 20, 1999

The Command Counter
application records the number of times each AutoCAD command,
AcEd-registered command, or AutoLISP expression evaluation
is invoked, plus the cumulative time spent with the command
or expression evaluation active. 
 
This information is accumulated across edit sessions in a separate ASCII
file, one for each login name used in an AutoCAD edit session. For
a single user installation, one login name, and thus one file, is
typically created and maintained.

The application was created for use in the R14 Alpha and Beta programs to
monitor site usage of AutoCAD features. It has since been used by
product marketing for researching AutoCAD feature use in R13c4
and c4a installations.  It has now been upgraded to operate with
AutoCAD Tahoe, although it is no longer used by the original clients.
It has been considered useful by other developers, as evidenced by the
number of suggested improvements to it.  However, it wasn't intended as
a feature to be supported for the multitudes.  So if you really want
it done right, You are going to have to do it yourself.

Take the source file, an ARX app development environment, and
do whatever you want with it, subject to all the legal disclaimers
listed in the source file header.  In summary, Autodesk isn't
responsible for any damage that comes from running the program
or interpreting the results.

To Install
----------

Build the CMDCOUNT sample application, and place the resultant
"CMDCOUNT.ARX" DLL on an accessible file system then do the following,
based on Release.

AutoCAD 2000 Installation
-------------------------

From the tools pulldown menu, select Load Application.  Pick the
"Contents" button in the "Startup Suite" box.  From that subdialog,
pick the "Add..." button.  Enter your file, click "Add", then close
out of all the dialog boxes.  CMDCOUNT will now load every time
AutoCAD is executed, until you remove it from the Startup Suite.

To Use
------

If you registered the program to load as described above, the program will
automatically  load every time you start AutoCAD (if AutoCAD is running
when you install the stuff in, either quit and restart it, or load the
ARX app manually), and accumulate statistics in an output file.

To take a peek at the statistics, either for the current session or the 
cumulative statistics, enter the CMDSTAT command, which has two options. 
Entering CR, or "S" will list the usage stats for the current AutoCAD invocation.  
Or, enter "C" to examine cumulative statistics, after the current session stats 
are merged in and reset.  Switching edit sessions doesn't reset session 
statistics, however examining cumulative stats causes 
the session stats to be merged to the cumulative stats then cleared.

The session statistics are also merged into the cumulative statistics
set whenever a drawing SAVE or WBLOCK is performed, and whenever AutoCAD
terminates.

CMDCOUNT may not be unloaded once it is loaded into an AutoCAD session.
It remains active until AutoCAD terminates.

After exiting AutoCAD, the output file can be examined with the ASCII editor 
of your choosing.  The marketing groups will give Alpha and Beta site
instructions on how to install it, and what to do with the accumulated 
information according to their needs.

It has already been successfully used in a few marketing research projects
for both released and pre-release software.

The Accumulated Statistics File
-------------------------------

Looking at the file in an ASCII editor should be quite obvious.  But
here's what can be said about it, and more importantly, what the file
will be named and what directory it will be located in, which is entirely
automatic, but not entirely simple.

The information is accumulated in a file named <userid>.txt, where <userid> 
is the login name for the current AutoCAD session (which is typically set 
during AutoCAD configuration). To derive the filename from the <userid>, the 
Command Counter strips out white space, and truncates after 8 characters. So 
<userid>="James Strzelec" would generate an output file called "JamesStr.txt". 
The output file lists the number of times each command and LISP expression has 
been invoked since the creation of the file, along with the total elapsed time, 
to the 1/100 of a second. In its header, it lists the version of the output file 
format (currently v1.2), CreateDate of the file, LastModifiedDate of the file, 
USERID, AutoCAD serial number, and AutoCAD version.

The search as to where to put <userid>.txt, goes like this:
First, it looks for acadnt.cfg, in the location indicated in the 
AutoCAD environment variable %ACADCFG%. If acadnt.cfg actually exists, and if 
it finds the output file, it updates the old accumulation data to reflect 
the latest AutoCAD session. If it doesn't find the output file, it creates 
the output file in this directory. 
Second, it looks for acad.exe along the %ACAD% path. Again, on finding the 
output file, it appends the new data, or else creates a new output file.
Failing these options, it puts the output file in the current working directory.
If file creation fails, the program gives up.

If you edit the file and mess up the format,
the command counter will either bail, or fail, depending on what was done.
Checking is minimal, you are on your honor.

Internal Logic Notes
--------------------

Internally, the app is quite simple.  It defines an AcEditorReactor with 
callbacks for all events related to commands and lisp expression evaluations, 
and accumulates statistics in an AcRxDictionary.  It has functions to load and 
store a dictionary of statistics to/from an ASCII file format.  It has a 
function to merge one dictionaries statitistics into another.  That's about it.  
It's capability for measurement are essentially defined by the available event 
callbacks available in the ARX libraries.

This application only accounts for actions invoked 
through the main AutoCAD Command Processor and LISP interpreter.  This means 
actions directly invoked via Windows events via toolbar, or direct windows 
tiles, etc, or OLE Automation, in particular, will NOT be counted by this 
application.  Then again, such actions aren't being properly accounted for 
by AutoCAD's UNDO/REDO mechanism either!  AutoCAD needs to deal with
this issue, someday.

To be clear on the definition of what is being measured,

The time recorded is elapsed time between the start and end of the command,
as measured by corresponding AcEditorReactor notification callbacks. The
relevant member functions are:

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

The time measured
includes time elapsed while waiting for input, from the user or whatever.

A command is an operation which can be entered in via the AutoCAD command line,
does not typically utilize AutoLISP in its execution.  It can be a builtin
command, or a command registered from an ARX application via the
acedRegCmds object (details in the ARX documentation). Virtually all AutoCAD
actions, especially those typically invoked from menu or toolbar picks, are
invoked by passing a string to the command processor, which in turn invokes
the command line form of the command.

A LISP expression is defined in the AutoLISP section in the customization
guide and most importantly, includes
functions registered in a call to ads_defun() in ARX and ADS applications.

Statistics are kept for each unique global command name and each
initial string in the AutoLISP expression
up to the first white space character, after folding the case. 

Whenever a LISP expression invokes the command 
facility to pump commands into AutoCAD, the commands so invoked will be counted 
as if they were invoked in any other context.  The LISP expression will also
continue to be timed, so "double-timing" occurs.

Also, if the transparent command facility is used (by prefixing supported
commands with an apostrophe ('), now, only the active command accumulates
time, as of July 16, 1998.

When documents are switched in MDI, only the active command in the active
document accumulates time, but the state in the suspended documents is tracked.

When the builtin command processor is idle, awaiting a next command, and
AutoLISP is not currently evaluating an expression, time is not 
accumlated in any statistics by this application.

To secure more reliable data during Alpha and Beta testing, and secure
more data in the event of AutoCAD crashes, 
cumulative statistics are updated during all  operations that lead to
internal DWG file save or wblock operations.  Time automatic saves are included.
These commands will definitely cause an update: SAVE, SAVEAS, AUTOSAVE,
and WBLOCK.  Other commands and custom ARX applications can also cause these
operations, especially wblock, in their course of execution.

Hopefully, the lack of ARX app notification in some AutoCAD
exit paths will be fixed by ship time, in which case the application would
always have an oppurtunity to save the command statistics up to the end of
the session, barring a full disk, memory corruption or whatever in an
abort situation.

The application is not intended to affect system actions in any way, it 
merely measures them.  If anything goes wrong while using the command counter, 
the best advice is to uninstall it.  The application has been benchmarked, 
and found to not significantly affect system performance.  It consumes 
relatively little memory, perhaps 250 bytes per cumulative command invoked, 
plus a few K overhead.

Beyond this, the one source module, CMDCOUNT.CPP, defines everything else.

