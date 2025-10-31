#ifndef _rxkernel_h
#define _rxkernel_h 1
//
// (C) Copyright 1992-2002 by Autodesk, Inc.
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

#include "rxsrvice.h"
#pragma pack (push, 8)

class AcRxClass;
class AcRxDictionary;

class ADESK_NO_VTABLE AcRxKernel : public AcRxService
{
public:
    ACRX_DECLARE_MEMBERS(AcRxKernel);
    AcRxKernel();
    virtual ~AcRxKernel();

    virtual
    AcRxDictionary* newAcRxDictionary(Adesk::Boolean sorted = Adesk::kTrue,
                                      Adesk::Boolean ignoreCase
                                                           = Adesk::kFalse) = 0;

    virtual
    AcRxDictionary* newAcRxDictionary(unsigned long length,
                                      Adesk::Boolean delObjects,
                                      Adesk::Boolean sorted = Adesk::kTrue,
                                      Adesk::Boolean ignoreCase
                                                           = Adesk::kFalse) = 0;

    virtual
    AcRxDictionary* newAcRxDictionary(const AcRxClass * filter) = 0;
};

#define acrxKernel \
    AcRxKernel::cast(AcRxDictionary::cast(\
    acrxSysRegistry()->at(ACRX_SERVICE_DICTIONARY))->at(ACRX_KERNEL_SERVICES))

#pragma pack (pop)
#endif
