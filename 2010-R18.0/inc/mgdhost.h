//
// (C) Copyright 2003-2007 by Autodesk, Inc. 
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
