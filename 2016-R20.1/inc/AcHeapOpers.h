
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
// AcHeapOpers.h - Provides the AcHeapOperators base class.  Use this
//              base class as a simple way to give your class local
//              new and delete operators.  It guarantees that the
//              objects will be created and destroyed on the same
//              heap (the acad heap) at all times.
//
#pragma once
#include "adesk.h"
#if !defined(_ADESK_WINDOWS_)

#ifndef __has_builtin                                   // The Clang compiler has the builtin __assume, that is __has_builtin told us, however, we get the compile error
#define __has_builtin(x) 0                              // "Cannot compile this builtin function yet" if we use this builtin implementation, we filed the bug 11945
#endif                                                  // for LLVM, now, we just workaround this issue by define the __assume as macro.
#if !__has_builtin(__assume)                                                       
inline void __assume(bool exp)
{
    exp;
}
#else
#define __assume adsk__assume
inline void adsk__assume(bool exp)
{
    (void)exp;
}
#endif

#endif
#ifndef ACHEAPEXPORT
#ifdef _ACHEAP_INTERNAL
#define ACHEAPEXPORT __declspec(dllexport)
#else
#define ACHEAPEXPORT __declspec(dllimport)
#endif
#endif

class AcHeapOperators {
    private:
        ACHEAPEXPORT static void * __stdcall allocRawMem(size_t size);
        // Unicode: leaving pFName as char for now
        ACHEAPEXPORT static void * __stdcall allocRawMem(size_t size, const char *pFName,
                                             int nLine);
        ACHEAPEXPORT static void   __stdcall freeRawMem(void *p);
        ACHEAPEXPORT static void   __stdcall freeRawMem(void *p, const char *pFName,
                                            int nLine);
    public:

#undef new
#undef delete
        static void* operator new(size_t size) {
            void *p = allocRawMem(size);
            __assume(p != NULL);
            return p;
        }

        static void* operator new[](size_t size) {
            void *p = allocRawMem(size);
            __assume(p != NULL);
            return p;
        }

        // Unicode: leaving pFName as char for now
        static void* operator new(size_t size, const char *pFName,
                                  int nLine)
        {
            void * p = allocRawMem(size, pFName, nLine);
            __assume(p != NULL);
            return p;
        }

        static void* operator new[](size_t size,
                                    const char *pFName, int nLine)
        {
            void *p = allocRawMem(size, pFName, nLine);
            __assume(p != NULL);
            return p;
        }

        static void operator delete(void *p) {   
            if(p != NULL)
                freeRawMem(p);
        }

        static void operator delete[](void *p) {   
            if(p != NULL)
                freeRawMem(p);
        }

        // Unicode: leaving pFName as char for now
        static void operator delete(void *p, const char *pFName,
                                    int nLine)
        {
            if (p != NULL)
                freeRawMem(p, pFName, nLine);
        }

        static void operator delete[](void *p,
                                      const char *pFName, int nLine)
        {
            if (p != NULL)
                freeRawMem(p, pFName, nLine);
        }

};  // AcHeapOperators

#ifdef MEM_DEBUG
// Acad-specific re-definition of new and delete operators, used to
// insert filename and line number info into memory blocks
//
#define new DEBUG_NEW
#define delete DEBUG_DELETE
#endif

