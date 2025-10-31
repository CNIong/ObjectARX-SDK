//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef ARXDBGCMDREACTORS_H
#define ARXDBGCMDREACTORS_H

#include "ArxDbgCmd.h"

/****************************************************************************
**
**  CLASS ArxDbgCmdReactors:
**
**  **jma
**
*************************************/

class ArxDbgCmdReactors : public ArxDbgCmd {

public:
					ArxDbgCmdReactors()		{}
    virtual			~ArxDbgCmdReactors()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

		// static command functions
	static void	reactors();
};


#endif    // ARXDBGCMDREACTORS_H
