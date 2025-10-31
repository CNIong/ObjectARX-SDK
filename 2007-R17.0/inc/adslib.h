#ifndef _adslib_h
#define _adslib_h 1
//
// (C) Copyright 1989-2006 by Autodesk, Inc. 
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
// 
//   DESCRIPTION:
//   ADS definitions and system dependent controls.
//   This also contains a substitute for stdlib.h on some systems.
//   If we know the system has stdlib.h, just include it.



// Not clear that WIN needs to be defined anymore.
// Let's remove it next release.
//
#ifdef _WINDOWS
#define WIN 1
#endif

#ifdef WINVER
#define WIN 1
#endif

#ifdef _MSC_VER
#define MICROSOFT 1
#endif

#include "ads.h"
#include "adscodes.h"
#pragma pack (push, 8)

// The bool type isn't known in .c files.
#ifdef __cplusplus


/* Unlocks an application to enable it from being unloaded in mid-session.
   The default is that applications are locked, and hence unloadable in
   mid-session. The appId argument is the Id passed in as a void* during
   the AcRx::kInitAppMsg call back when the application is loaded. Return
   of non-zero means success.
*/
bool acrxUnlockApplication(void* appId);

/* Returns non-zero if the specified app is locked.
 */
bool acrxApplicationIsLocked(const ACHAR* modulename);

/* Symmetric to acrxUnlockApplication. Locks it, and hence prevents it from
   being unloaded in mid-session. Return of non-zero means success.
 */
bool acrxLockApplication(void* appId);


#endif // __cplusplus

#pragma pack (pop)

#endif // ndef _adslib_h

