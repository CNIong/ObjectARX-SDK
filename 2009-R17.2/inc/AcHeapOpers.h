
//
// (C) Copyright 2002-2006 by Autodesk, Inc.
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
// AcHeapOpers.h - Provides the AcHeapOperators base class.  Use this
//              base class as a simple way to give your class local
//              new and delete operators.  It guarantees that the
//              objects will be created and destroyed on the same
//              heap (the acad heap) at all times.
//
#pragma once

class AcHeapOperators {
    private:
        static void * __stdcall allocRawMem(size_t size);
        // Unicode: leaving pFName as char for now
        static void * __stdcall allocRawMem(size_t size, const char *pFName,
                                             int nLine);
        static void   __stdcall freeRawMem(void *p);
        static void   __stdcall freeRawMem(void *p, const char *pFName,
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

