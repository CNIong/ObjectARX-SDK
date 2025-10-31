#ifndef   _ACTRANS_H
#define   _ACTRANS_H
//
//  (C) Copyright 1993-2008 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION: Header for Transaction Modeler.

#include "rxnames.h"
#include "aced.h"
#include "dbptrar.h"
#include "dbtrans.h"
#include "acdocman.h"
#pragma pack (push, 8)


class AcTransactionManager: public AcDbTransactionManager 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcTransactionManager);

    virtual Acad::ErrorStatus   enableGraphicsFlush(bool doEnable) = 0;
    virtual void                flushGraphics() = 0; 
};

inline AcTransactionManager* acTransactionManagerPtr()
{
    AcApDocument* pDoc = acDocManager->curDocument();
    return pDoc ? pDoc->transactionManager() : NULL;
}

#define actrTransactionManager  acTransactionManagerPtr()

#pragma pack (pop)
#endif
