//  Copyright 2017 Autodesk, Inc.  All rights reserved.
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

// AcPal [defined(ACPAL_API)] will implement some non cross platform
//      API for vertical [!defined(_ADESK_CROSS_PLATFORM_)] convenience.
// Cross platform code or Fabric [defined(_ADESK_CROSS_PLATFORM_) in
//      .cmake by default] should not use these APIs.
// AcPal unit test [defined(ACPAL_TEST)] need test these APIs.
#if defined(ACPAL_API) || !defined(_ADESK_CROSS_PLATFORM_) || defined(ACPAL_TEST)
#define AC_NON_CROSS_PLATFORM_API
#endif



#endif
