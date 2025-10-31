#ifndef ACPLPLOTERRORHANDLERLOCK_H
#define ACPLPLOTERRORHANDLERLOCK_H
//
//  (C) Copyright 2003-2006 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  Header for Plot Error Handler Lock.
//

#include "AdAChar.h"
#include "AcPlObject.h"

class AcPlPlotErrorHandler;

class AcPlPlotErrorHandlerLock : public AcPlObject
{
    ACPL_DECLARE_MEMBERS(AcPlPlotErrorHandlerLock);
public:
    enum LockStatus {
        kLocked,
        kUnLocked
    };

    ACPL_PORT AcPlPlotErrorHandlerLock();
    ACPL_PORT AcPlPlotErrorHandlerLock(AcPlPlotErrorHandler* pAppErrHandler, 
                             const ACHAR * pAppName);

    ACPL_PORT LockStatus status() const;
    ACPL_PORT bool lock(AcPlPlotErrorHandler* pAppErrHandler, const ACHAR * pAppName);
    ACPL_PORT bool unLock(AcPlPlotErrorHandler* pAppErrHandler);
    ACPL_PORT void getErrorHandler(AcPlPlotErrorHandler*& pAppErrHandler) const;
    ACPL_PORT const ACHAR * appName() const;
};

#endif // ACPLPLOTERRORHANDLERLOCK_H
