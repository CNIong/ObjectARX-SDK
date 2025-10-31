//  Copyright 2016 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form

#pragma once

#ifndef ACPAL_DEF_H
#define ACPAL_DEF_H

//We suppress import/export directives by default
//when statically linking
#ifdef _ADESK_STATIC_LINKING_
#define ACPAL_SUPPRESS_IMPEXP_DIRECTIVES 1
#endif


#if ACPAL_SUPPRESS_IMPEXP_DIRECTIVES 
    #define   ACPAL_PORT
#else
    #if defined(_MSC_VER) 
        #ifdef  ACPAL_API
            #define   ACPAL_PORT _declspec(dllexport)
        #else
            #define   ACPAL_PORT _declspec(dllimport)
            #pragma comment(lib, "acpal.lib")
        #endif
    #elif defined(__clang__)
        #ifdef  ACPAL_API
            #define   ACPAL_PORT
        #else
            #define   ACPAL_PORT
            #pragma comment(lib, "acpal.lib")
        #endif
    #else
        #error Visual C++ or Clang compiler is required.
    #endif
#endif

#endif
