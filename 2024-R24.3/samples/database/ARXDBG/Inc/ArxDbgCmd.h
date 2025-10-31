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

#ifndef ARXDBGCMD_H
#define ARXDBGCMD_H

/****************************************************************************
**
**  CLASS ArxDbgCmd:
**
**  **jma
**
*************************************/

class ArxDbgCmd {

public:
					ArxDbgCmd()	    {}
    virtual			~ArxDbgCmd()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)   {}

};


#endif    // ARXDBGCMD_H
