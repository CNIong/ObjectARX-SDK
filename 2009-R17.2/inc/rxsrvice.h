//
// Copyright (C) 1992-1999 by Autodesk, Inc.
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

#ifndef _rxsrvice_h
#define _rxsrvice_h 1

#include "rxobject.h"
#pragma pack (push, 8)

extern "C" {
    typedef AcRx::AppRetCode (*DepFuncPtr)(AcRx::AppMsgCode, void*);
}

class AcRxServicePrototype;
class AcRxService;

class AcRxService: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxService);
    AcRxService();
    virtual ~AcRxService();

    AcRxObject* getSysInfo() const;
    void        setSysInfo(AcRxObject* sysInfoObj);

    void        addDependency();
    void        removeDependency();

    Adesk::Boolean unloadable() const;

    // The following functions are not currently implemented
    // They are present as place holders so that they can be
    // implemented in the future without breaking binary
    // compatibility
    //
    DepFuncPtr dependencyFunctionPtr();
    void setDependencyFunctionPtr(DepFuncPtr);

private:
    AcRxServicePrototype* mpImpService;
};

#pragma pack (pop)
#endif
