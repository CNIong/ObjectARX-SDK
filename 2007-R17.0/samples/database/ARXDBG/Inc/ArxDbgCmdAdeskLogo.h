//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
