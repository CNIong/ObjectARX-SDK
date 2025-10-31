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
#pragma once

#ifndef  ACBASEDEFS_H
#define ACBASEDEFS_H

//API exported by ac1stXX.dll

#ifndef _ADESK_MAC_
#ifndef ACBASE_PORT
#ifdef ACBASE_API
    #define ACBASE_PORT _declspec(dllexport)
#else
    #define ACBASE_PORT _declspec(dllimport)
#endif
#endif
#else
// On OS X, we will export all symbols by default and will use GCC
// attributes to exclude symbols we don't want to export.
#define ACBASE_PORT
#endif // _ADESK_MAC_


#endif //ACBASEDEFS_H
