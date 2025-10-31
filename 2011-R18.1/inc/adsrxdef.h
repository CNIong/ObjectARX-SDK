#ifndef   _ADSRXDEF_H_
#define   _ADSRXDEF_H_ 1
//
// (C) Copyright 1992-2007 by Autodesk, Inc.  All rights reserved.
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
// DESCRIPTION:C ADS definitions supported in Arx environment, plus
//             a few acrxXX function definitions.
//
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
    int    lflag;
    ACHAR* appname;
    LONG_PTR  apphandle;
    int    ads_fcode;
    int    ads_invkcnt;
    struct resbuf* ads_argl;
    FunHandList* ads_fhdl;
    AcRxGenHand * modhandle;
    resbuf *ads_ret;
    int    ads_rettype;
};

#pragma pack (pop)
#endif
