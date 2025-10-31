//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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
#pragma once

#include "VisualStyleJig.h"
#include "AcCmd.h"

#include <string>

class VisualStyleCmd
{
public:
    enum Action { 
        kSetCurrent, 
        kDelete, 
        kRename, 
        kCurrentInfo, 
        kList,
        kCreate,
        kCreateWithAsk,
        kCmdCt};

    VisualStyleCmd();

    static const ACHAR *cmdName(int cmd);
    static const AcRxFunctionPtr cmdHandler(int cmd);

    static void unload(void);

private:
    static void setCurrentCmd(void);
    static void currentInfoCmd(void);
    static void deleteCmd(void);
    static void renameCmd(void);
    static void listCmd(void);
    static void createCmd(void);
    static void createWithAskCmd(void);

    void invokeCmd(Action cmd);

    void addVisualStyleEntity(AcDbObjectId visualStyleObjId = AcDbObjectId::kNull);
    void listAllVisualStyles(void);
    void displayViewportVStyleInfo(void);
    
    bool visualStyleCmd(Action cmd, ACHAR *result);

    void setVisualStyleCurrent(ACHAR *name, 
                               AcDbObjectId visualStyleId = AcDbObjectId::kNull);
    void deleteVisualStyle(ACHAR *name);
    void renameVisualStyle(ACHAR *name);

    bool visualStyleExists(ACHAR *name, AcDbObjectId *pVisualStyleId = NULL);

    void addVisualStyle(ACHAR *name);
    AcDbObjectId getCurrentVisualStyle(void);
    AcDbObjectId mCurrVisualStyleId;

    static const ACHAR *kCmdNames[kCmdCt];
    static const AcRxFunctionPtr kCmdHandlers[kCmdCt];
    static const ACHAR *kCmdPrompts[kCmdCt];
};

// Return the command name
inline const ACHAR *VisualStyleCmd::cmdName(int cmd)
{
    return kCmdNames[cmd];
}

// Return the command handler
inline const AcRxFunctionPtr VisualStyleCmd::cmdHandler(int cmd)
{
    return kCmdHandlers[cmd];
}

