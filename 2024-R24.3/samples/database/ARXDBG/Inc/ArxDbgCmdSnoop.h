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

#ifndef ARXDBGCMDSNOOP_H
#define ARXDBGCMDSNOOP_H

#include "ArxDbgCmd.h"

/****************************************************************************
**
**  CLASS ArxDbgCmdSnoop:
**
**  **jma
**
*************************************/

class ArxDbgCmdSnoop : public ArxDbgCmd {

public:
					ArxDbgCmdSnoop()	{}
    virtual			~ArxDbgCmdSnoop()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

		// static command functions
	static void	cmdLineMain();
	static void	editor();
	static void entities();
	static void	entitiesNested();
	static void database();
	static void services();
	static void sysRegistry();
};


#endif    // ARXDBGCMDSNOOP_H
