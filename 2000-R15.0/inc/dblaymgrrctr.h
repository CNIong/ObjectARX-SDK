#ifndef   _ACDB_LAYOUT_MANAGER_REACTOR_H
#define   _ACDB_LAYOUT_MANAGER_REACTOR_H
//
//  (C) Copyright 1998 by Autodesk, Inc.  All rights reserved.
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

#include "rxobject.h"
#include "dbid.h"
#pragma pack (push, 8)

class AcDbLayoutManagerReactor : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbLayoutManagerReactor);

    virtual void layoutCreated(const char* newLayoutName,
        const AcDbObjectId& layoutId);
    virtual void layoutToBeRemoved(const char* layoutName,
        const AcDbObjectId& layoutId);
    virtual void layoutRemoved(const char* layoutName,
        const AcDbObjectId& layoutId);
    virtual void abortLayoutRemoved(const char* layoutName,
        const AcDbObjectId& layoutId);
    virtual void layoutToBeCopied(const char* layoutName,
        const AcDbObjectId& oldLayoutId);
    virtual void layoutCopied(const char* oldLayoutName,
        const AcDbObjectId& oldLayoutId,
        const char* newLayoutname,
        const AcDbObjectId& newLayoutId);
    virtual void abortLayoutCopied(const char* layoutName,
        const AcDbObjectId& layoutId);
    virtual void layoutToBeRenamed(const char* oldName,
        const char* newName, const AcDbObjectId& layoutId);
    virtual void layoutRenamed(const char* oldName,
        const char* newName, const AcDbObjectId& layoutId);
    virtual void abortLayoutRename(const char* oldName,
        const char* newName, const AcDbObjectId& layoutId);
    virtual void layoutSwitched(const char* newLayoutname,
        const AcDbObjectId& newLayoutId);
    virtual void plotStyleTableChanged(const char* newTableName,
        const AcDbObjectId& layoutId);
};

#pragma pack (pop)
#endif // _ACDB_LAYOUT_MANAGER_REACTOR_H
