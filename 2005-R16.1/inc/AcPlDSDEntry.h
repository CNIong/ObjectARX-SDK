#ifndef ACPLDSDENTRY_H
#define ACPLDSDENTRY_H
//
//  (C) Copyright 2003 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  Header for AcPlDSDEntry.h
//

#pragma once

#include "AcPl.h"
#include "AcPlObject.h"

/////////////////////////////////////////////////////////////////////////////
// AcPlDSDEntry

class AcPlDSDEntry  : public AcPlObject
{
    ACPL_DECLARE_MEMBERS(AcPlDSDEntry)
public:

    enum SheetType {
        kSingleDWF  = 0,
        kMultiDWF = 1,
        kOriginalDevice = 2
    };

    ACPL_PORT AcPlDSDEntry();

    ACPL_PORT virtual ~AcPlDSDEntry();

    ACPL_PORT AcPlDSDEntry(const AcPlDSDEntry & src);

    ACPL_PORT AcPlDSDEntry& operator= (const AcPlDSDEntry &src);

    ACPL_PORT const char *      dwgName() const;
    ACPL_PORT void              setDwgName(const char * pName);

    ACPL_PORT const char *      layout() const;
    ACPL_PORT void              setLayout(const char * pLayoutName);
    
    ACPL_PORT const char *      title() const;
    ACPL_PORT void              setTitle(const char * pTitle);
    
    ACPL_PORT const char *      NPS() const;
    ACPL_PORT void              setNPS(const char * pNPSName);
    
    ACPL_PORT const char *      NPSSourceDWG() const;
    ACPL_PORT void              setNPSSourceDWG(const char * pNPWDWGName);
};

#endif // ACPLDSDENTRY_H
