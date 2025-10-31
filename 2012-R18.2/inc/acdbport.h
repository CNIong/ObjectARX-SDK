//
// (C) Copyright 2009-2011 by Autodesk, Inc.
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
#pragma once

// define GCC_NO_VTABLE to empty for Windows build
#define GCC_NO_VTABLE

#if defined _ADESK_WINDOWS_
#ifdef  ACDB_API
    #  define   ACDB_PORT _declspec(dllexport)
#else
    #  define   ACDB_PORT
#endif
#else // GCC port - Still need to sort out the right ACDB_PORT definition for exporting symbols

#define ACDB_PORT
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

#endif //_ADESK_WINDOWS_
