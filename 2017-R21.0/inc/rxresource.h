//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2016 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license
//  agreement provided at the time of installation or download, or which
//  otherwise accompanies this software in either electronic or hard copy form.
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _RXRESOURCE_H_
#define _RXRESOURCE_H_
#pragma once

#include "acbasedefs.h"
#include "PAL/api/def.h"
#include "adesk.h"
#include "pimplapi.h"
#include "AcHeapOpers.h"
class AcString;

#undef PAL
namespace Autodesk { namespace AutoCAD {namespace PAL { class AcRxResourceInstanceImp; } } }

class AcRxResourceInstance 
    : public Pimpl::ApiPart<AcHeapOperators, Autodesk::AutoCAD::PAL::AcRxResourceInstanceImp>
{
public:
    ACBASE_PORT explicit AcRxResourceInstance(const wchar_t* path);
    //for compatibility with existing code, do not use in new code
    ACPAL_PORT AcRxResourceInstance(void* hInst);

    ACBASE_PORT ~AcRxResourceInstance();
    ACBASE_PORT bool tryLoadString(Adesk::Int32 id, AcString& out) const noexcept;
    ACBASE_PORT bool isLoaded() const noexcept;
    
    ACBASE_PORT bool loadDataResource(Adesk::Int32 id, unsigned long& resourceSize, const void*& data) const noexcept;
};
#endif 