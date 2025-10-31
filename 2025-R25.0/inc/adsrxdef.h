//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:C ADS definitions supported in Arx environment, plus
//             a few acrxXX function definitions.
//

#ifndef   _ADSRXDEF_H_
#define   _ADSRXDEF_H_ 1

#pragma pack (push, 8)
typedef struct fchnd {                /* ads function handler struct */
        struct fchnd *next;           /* linked */
        int fcode;                    /* function code */
        int (*fhdl)();                /* registered function pointer */
} FunHandList;
 
class AcRxGenHand;

/* The following typedef is used for maintaining a connection between
 * AutoLISP and an RXADS application.  It is for internal use only
 */
class RxADSAppTableEntryType {
  public:
    int    lflag = 0;
    const ACHAR* appname = nullptr;
    Adesk::LongPtr  apphandle = 0;
    int    ads_fcode = 0;
    int    ads_invkcnt = 0;
    struct resbuf* ads_argl = nullptr;
    FunHandList* ads_fhdl = nullptr;
    AcRxGenHand * modhandle = nullptr;
    resbuf *ads_ret = nullptr;
    int    ads_rettype = 0;
};

#pragma pack (pop)
#endif
