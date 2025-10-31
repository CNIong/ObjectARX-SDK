Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   

Description:

	This program demonstrates the use of persistent reactors
	by attaching two reactors one to each of two lines.  Each
	reactor stores the objectId of the line it is not
	attached to so that when the line it is attached to is
	lengthened or shortened, the reactor opens the other line
	and modifies it's length to be the same as the new length
	of the line just changed.

1.	Load the arx application.
2.	Command: ALINES
        What this does is create two lines and connect them to two
        persistent reactors.  Each reactor has the objectId of the line
        it is *not* attahced to.  When one of the lines' length is changed,
        the reactor attached to it will open the other line (using the
        objectId it contains) and will change the length of the other line
        to match the length of the line the reactor is attached to.

        So, for example, if we call the two lines lineA and lineB,  then
        the reactor attached to lineA will store the objectId of lineB
        and the reactor attached to lineB will store the objectId of
        lineA.

        If we then change the length of lineA,  the reactor attached to
        lineA will open lineB and change the length of lineB to match
        the new length of lineA.