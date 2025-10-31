//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#pragma once

// define GCC_NO_VTABLE to empty for Windows build
#define GCC_NO_VTABLE

#ifdef  ACDB_API
    #define   ACDB_PORT _declspec(dllexport)
#else
    #define   ACDB_PORT
#endif

#ifdef _ADESK_MAC_
#if defined(ACDB_API) || defined(ACDB_EXT)
// Why check ACDB_API?
// ACDB_API is defined when compile acdb. But not when compile Gelib.dylib.
// Gelib.dylib would try to link to virtual functions declared by AcRxObject. However,
// there is no implementation Gelib project can see. Unless they are pure virtual function, there would be
// linker error.
// On the other hand, when compiling acdb, these virtual function can't be pure virtual, otherwise,
// they will prevent from instantialize subclass objects. And the implementation of
// the virtual functions are in rxinit.cpp which is compiled into acdb.
// So we will leave GCC_NO_VTABLE to empty when compile acdb.

#else

// Why define GCC_NO_VTABLE to =0?
// define GCC_NO_VTABLE since there isn't equivalence of __declspec(novtable) on GCC
// Given virtual functions in AcRxObject has no implementation, there would be linker error
// if they are not pure virtual function when linking with GCC
#undef GCC_NO_VTABLE
#define GCC_NO_VTABLE =0    

#endif //ACDB_API
#endif //_ADESK_MAC_