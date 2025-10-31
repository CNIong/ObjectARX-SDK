//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef ARXDBGCMDADESKLOGO_H
#define ARXDBGCMDADESKLOGO_H

#include "ArxDbgCmd.h"

/****************************************************************************
**
**  CLASS ArxDbgCmdAdeskLogo:
**
**  **jma
**
*************************************/

class ArxDbgCmdAdeskLogo : public ArxDbgCmd {

public:
					ArxDbgCmdAdeskLogo()	{}
    virtual			~ArxDbgCmdAdeskLogo()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

		// static command functions
	static void	cmdLineMain();
	static void	add();
	static void modify();
	static void	styles();
	static void hardwire();
	static void hardwire2();
	static void	styleAdd();
	static void	styleModify();

	static bool	getLogoStyle(AcDbObjectId& styleId);
};


#endif    // ARXDBGCMDADESKLOGO_H
