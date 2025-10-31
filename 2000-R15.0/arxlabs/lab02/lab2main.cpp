//
// (C) Copyright 1999 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//
#include <adslib.h>
#include <rxdlinkr.h>
#include <aced.h>
#include <dbents.h>
#include <geassign.h>
#include "lab2utils.h"
/*
In this lab we learn to append a line to the Model Space record, use acedGetPoint() 
to get user input, and change the line's color attribute while it is still open.  
When finished we close the pointer, rather than deleting it.
*/

Acad::ErrorStatus newLine()
{
//Mark the leftmost cubicle as unusable by putting a red diagonal
//line from the lower left to upper right corners
//Use the first parameter of acedGetPoint to rubberband to the second point
//Prompt the user to select the line's endpoints
	ads_point pt1, pt2;
	int retval;
//{{BEGIN_LEVEL_ADVANCED
	
	try 
	{
		//get the first point from the user.  Do not specify a base point.
		//...
//{{BEGIN_LEVEL_INTERMEDIATE
		if ((retval = acedGetPoint(NULL, "\nSelect lower left:  ", pt1)) != RTNORM) 
			throw retval;
//{{END_LEVEL_INTERMEDIATE
		//get the second point from the user, using the first point as a base point.
		//...
//{{BEGIN_LEVEL_INTERMEDIATE
		if ((retval = acedGetPoint(pt1, "\nSelect upper right:  ", pt2)) != RTNORM)
			throw retval;
//{{END_LEVEL_INTERMEDIATE
	}
	catch (int e)
	{
		if (e == RTCAN)
			return Acad::eUserBreak;
		if (e == RTERROR)
			return Acad::eInvalidInput;
	}
//{{END_LEVEL_ADVANCED
	
//Instantiate an AcDbLine pointer.  Use the two user-chosen 
//points as endpoints.
//Since AcDbLine's constructor uses AcGePoint2d, but acedGetPoint returns ads_point,
//you must find a way to translate old style to new style.  This can be done either by
//assigning each array member individually, or by calling asPnt3d() from geassign.h
//{{BEGIN_LEVEL_ADVANCED
//...
//{{BEGIN_LEVEL_INTERMEDIATE

	AcDbLine* pLine = new AcDbLine(asPnt3d(pt1), asPnt3d(pt2));
//{{END_LEVEL_INTERMEDIATE
//Make sure you created the line...
	if (!pLine)
	{
		acedAlert("Not enough memory to create a Line!");
		return Acad::eOutOfMemory;
	}
//{{END_LEVEL_ADVANCED
//Prompt the user to enter a new color
//Then change the color property of the new line to this value.
//{{BEGIN_LEVEL_ADVANCED
//...
//{{BEGIN_LEVEL_INTERMEDIATE
	int color;
	acedGetInt("\nEnter AutoCAD color number:  ", &color);
	if (pLine->setColorIndex(color) != Acad::eOk)
	{
		acutPrintf("\nInvalid color chosen.\n");
	}
//{{END_LEVEL_INTERMEDIATE
//{{END_LEVEL_ADVANCED

//Post the new entity to the database
//{{BEGIN_LEVEL_ADVANCED
	AcDbObjectId id;
	return postToDatabase(pLine, id);
//{{END_LEVEL_ADVANCED
}

//Call newLine() to create the line.
//Rebuild your application, load it in AutoCAD and run it.
void addLineCommand()
{
//{{BEGIN_LEVEL_ADVANCED
    if (newLine()==Acad::eOk)
        acutPrintf("Success\n");
    else
        acutPrintf("Failed\n");
//{{END_LEVEL_ADVANCED
}

//This is the entry point that makes a simple DLL an ARX.
//This entry point must be exported either by means of a def file
//or by the means of _declspec

//In the kInitAppMsg callback of acrxEntryPoint add a new command named "ADDLINE".
//Link it to the template file function arxmain(), which should be renamed as addLineCommand().
//Also don't forget to register the application as MDI aware.
extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
    switch (msg) {
    case AcRx::kInitAppMsg:
//{{BEGIN_LEVEL_ADVANCED
        //An ARX application is locked to memory by default.
        //You must make the following function call to unlock
        //it.
        acrxDynamicLinker->unlockApplication(pkt); 
		//You must also request that the AcRx dynamic linker make
		//your application MDI aware
		//...
//{{BEGIN_LEVEL_INTERMEDIATE
		acrxDynamicLinker->registerAppMDIAware(pkt);
//{{END_LEVEL_INTERMEDIATE
        //register the command
		//...
//{{BEGIN_LEVEL_INTERMEDIATE
        acedRegCmds->addCommand("OARX_LAB2","_addline","addline",ACRX_CMD_MODAL,addLineCommand);
//{{END_LEVEL_INTERMEDIATE
//{{END_LEVEL_ADVANCED
        break;
    case AcRx::kUnloadAppMsg:
        //remove the command group so that AutoCAD won't call us
        //when we are not here.
//{{BEGIN_LEVEL_ADVANCED
        acedRegCmds->removeGroup("OARX_LAB2");
//{{END_LEVEL_ADVANCED
        break;
    }
    return AcRx::kRetOK;
}