///////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form. 
//
// DESCRIPTION:
//
// The base class of all topological entities. It just contains a set of flags
// and per class new/delete.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef AMODELER_INC_ENTITY_H
#define AMODELER_INC_ENTITY_H

#include "global.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp Entity
{
public:

    Entity() : mFlags(0) {}
    virtual ~Entity()    {}

    Flag flags     ()           const { return mFlags;               }
    void setFlags  (Flag flags)       { mFlags = flags;              }
    bool isFlagOn  (Flag flag)  const { return (mFlags & flag) != 0; }
    bool isFlagOff (Flag flag)  const { return (mFlags & flag) == 0; }
    void setFlagOn (Flag flag)        { mFlags |=  flag;             }
    void setFlagOff(Flag flag)        { mFlags &= ~flag;             }
    void flipFlag  (Flag flag)        { mFlags ^=  flag;             }

#undef new
#undef delete

    // Per class new/delete. They are needed in case a client application 
    // (e.g. ARX) redefines global new/delete, then it creates AModeler 
    // entities and these entities are deleted on the AModeler side. 
    // Providing per class new/delete avoids calling the client redefined
    // new/delete.
    //
    void* operator new   (size_t); 
    void  operator delete(void*); 

#ifdef _DEBUG
	// Unicode OK
	// lpszFileName for both new and delete need to be "const char*", not "const wchar_t*"
    void* operator new   (size_t, const char* lpszFileName, int nLine);
    void operator  delete(void*,  const char* lpszFileName, int nLine);
#endif

private:
    Flag mFlags;  // Set of flags (unsigned int)

}; // class Entity


AMODELER_NAMESPACE_END
#endif
