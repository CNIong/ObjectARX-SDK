This example is a simple custom entity defining a square. It supports the
'AsdkSquareWrap' ATL COM sample in the adjacent subdirectory.

Build the 'AsdkSquareWrap' project first.  It will fail with an error that it
cannot open square.lib (which comes from this square sample).  But, it will
successfully generate the AsdkSquareLib_i.c, AsdkSquareLib_i.h, and
AsdkSquareLib.tlb files that are needed by this square sample.

Once the AsdkSquareLib_i.c, AsdkSquareLib_i.h, and AsdkSquareLib.tlb files are
generated, then build this square sample.  Once that is completed, go back to
the 'AsdkSquareWrap' project and build it again to complete generating the
AsdkSquareLib.dll file.

1- The Square sample is an ObjectDBX Object Enabler Application which defines
   a custom entity derived from AcDbCurve. The class name for this custom entity
   is: AsdkSquare

2- The SquareUI sample defines two commands which create an AsdkSquare entity 
   defined in the Square module. These commands are: 'ASDKSQUARE' (or 'SQ')
   and 'ASDKADDSQUARE' (or 'ADDSQ')


Command 'ASDKSQUARE' adds a square to model space using only the command line

Command 'ASDKADDSQUARE' adds a square to the current space using both the
command line and OPM. In order to use this command you must first compile and
register the 'AsdkSquareWrap' COM server on your system. Otherwise, the command
will refuse to run. To register this server, open and modify the
'AsdkSquareLib.reg' file with your local path. When done run this file on your
system to register the COM server.

Since this project defines both a custom entity / object enabler module
(square.dbx) and a UI support module (squareui.arx), they must first both be
loaded (in that order) before the ASDKSQUARE command can be run.