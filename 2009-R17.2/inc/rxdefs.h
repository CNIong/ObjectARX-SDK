#ifndef   _RXDEFS_H_
#define   _RXDEFS_H_
//
// (C) Copyright 1992-2008 by Autodesk, Inc.  All rights reserved.
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

#include "adesk.h"
#pragma pack (push, 8)

#define NULLFCN static_cast<Adesk::IntPtr>(0)  // A NULL function pointer

#define ACRX_ULONG_MAX 0xFFFFFFFF

#define ACRX_ASCII_MAX 255  /* Same as UCHAR_MAX in <limits.h> */
#define ACRX_EOS 0          /* End of String Indicator */

// AcRx:  typedef and enum namespace scoping struct.

struct AcRx {

    typedef void (*FcnPtr) ();

    enum         DictIterType { kDictSorted   = 0,
                                kDictCollated = 1 };

    enum         Ordering     { kLessThan     = -1,
                                kEqual        = 0,
                                kGreaterThan  = 1,
                                kNotOrderable = 2 };

    enum         AppMsgCode   { kNullMsg         = 0,
                                kInitAppMsg      = 1,
                                kUnloadAppMsg    = 2,
                                kLoadDwgMsg      = 3,
                                kUnloadDwgMsg    = 4,
                                kInvkSubrMsg     = 5,
                                kCfgMsg          = 6,
                                kEndMsg          = 7,
                                kQuitMsg         = 8,
                                kSaveMsg         = 9,
                                kDependencyMsg   = 10,
                                kNoDependencyMsg = 11,
                                kOleUnloadAppMsg = 12,
                                kPreQuitMsg      = 13,
                                kInitDialogMsg   = 14,
                                kEndDialogMsg    = 15,                                
                                kSuspendMsg      = 16,
                                kInitTabGroupMsg = 17,
                                kEndTabGroupMsg  = 18};                                
        

    enum        AppRetCode   { kRetOK          = 0,
                                kRetError       = 3 };
};

/* These messages are replaced by kLoadDwgMsg, and kUnloadDgwMsg.
 */
#ifndef kLoadADSMsg
#define kLoadADSMsg kLoadDwgMsg
#define kUnloadADSMsg kUnloadDwgMsg
#endif

class AcRxClass;
typedef void (*AppNameChangeFuncPtr)(const AcRxClass* classObj,
                ACHAR *& newAppName, int saveVer);

#pragma pack (pop)

#endif
