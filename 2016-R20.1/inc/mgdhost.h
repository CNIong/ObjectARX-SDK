//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#include "AdAChar.h"
#ifndef MGDHOST_H
#define MGDHOST_H 1
#pragma once

class AcDbManagedHost
{
public:
    virtual int version() { return 1;}
    virtual Acad::ErrorStatus load(const ACHAR * fname)=0;
};

AcDbManagedHost* ADESK_STDCALL acdbGetManagedHost();
Acad::ErrorStatus ADESK_STDCALL acdbSetManagedHost(AcDbManagedHost* pHost);
ACDB_PORT HRESULT ADESK_STDCALL acdbInitializeManagedLayer();
ACDB_PORT HRESULT ADESK_STDCALL acdbTerminateManagedLayer();


#endif /* MGDHOST_H */
