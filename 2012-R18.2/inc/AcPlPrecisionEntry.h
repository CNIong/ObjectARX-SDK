#ifndef ACPLPRECISIONENTRY_H
#define ACPLPRECISIONENTRY_H
//
//  (C) Copyright 2003-2009 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  Header for AcPlPrecisionEntry.h
//

#pragma once

#include "AcPl.h"
#include "AcPlObject.h"

/////////////////////////////////////////////////////////////////////////////
// AcPlPrecisionEntry

class AcPlPrecisionEntry  : public AcPlObject
{
    ACPL_DECLARE_MEMBERS(AcPlPrecisionEntry)
public:
    ACPL_PORT AcPlPrecisionEntry();

    ACPL_PORT virtual ~AcPlPrecisionEntry();

    ACPL_PORT AcPlPrecisionEntry(const AcPlPrecisionEntry & src);

    ACPL_PORT AcPlPrecisionEntry& operator= (const AcPlPrecisionEntry &src);

    ACPL_PORT const ACHAR *     title() const;
    ACPL_PORT void              setTitle(const ACHAR * pTitle);

    ACPL_PORT const ACHAR *     description() const;
    ACPL_PORT void              setDescription(const ACHAR * pDescription);

    ACPL_PORT const ACHAR *     unitType() const;
    ACPL_PORT void              setUnitType(const ACHAR * pUnitType);

    ACPL_PORT const ACHAR *     unitScale() const;
    ACPL_PORT void              setUnitScale(const ACHAR * pUnitScale);

    ACPL_PORT const double      desiredPrecision() const;
    ACPL_PORT void              setDesiredPrecision(double dDesiredPrecision);

    ACPL_PORT const int         gradientResolution() const;
    ACPL_PORT void              setGradientResolution(int nGradientResolution);

    ACPL_PORT const int         colorResolution() const;
    ACPL_PORT void              setColorResolution(int nColorResolution);

    ACPL_PORT const int         monoResolution() const;
    ACPL_PORT void              setMonoResolution(int nMonoResolution);
};

#endif // ACPLPRECISIONENTRY_H
