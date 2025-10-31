///////////////////////////////////////////////////////////////////////////////
//
// © Autodesk, Inc. 1998-2010. All rights reserved.
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
