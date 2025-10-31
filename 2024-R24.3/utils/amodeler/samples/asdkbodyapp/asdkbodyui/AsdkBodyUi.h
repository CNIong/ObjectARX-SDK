//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ABodyApp_H__
#define __ABodyApp_H__


///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//
// Stubs for functions implemented below
//
///////////////////////////////////////////////////////////////////////////////

struct CommandInfo
{
    ACHAR * commandName;
    AcRxFunctionPtr fn;
    ACHAR * desc;
};

// -----------------------------------------------
extern CommandInfo commandInfo[];

#endif  //  __ABodyApp_H__
