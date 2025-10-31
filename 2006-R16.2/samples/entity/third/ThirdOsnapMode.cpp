//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
#include <dbmain.h>
#include <dbosnap.h>

#include "ThirdOsnapInfo.h"
#include "ThirdOsnapMode.h"

AsdkThirdOsnapMode::AsdkThirdOsnapMode()
{
    m_pGlyph = new AsdkThirdGlyph;
}

AsdkThirdOsnapMode::~AsdkThirdOsnapMode()
{
    delete m_pGlyph;
    m_pGlyph = NULL;
}

const char*
AsdkThirdOsnapMode::localModeString() const
{
    return "THIrd";
}

const char*
AsdkThirdOsnapMode::globalModeString() const
{
    return "_THIrd";
}

const AcRxClass*
AsdkThirdOsnapMode::entityOsnapClass() const
{
    return AsdkThirdOsnapInfo::desc();
}

AcGiGlyph*
AsdkThirdOsnapMode::glyph() const
{
    return m_pGlyph;
}

const char*
AsdkThirdOsnapMode::tooltipString() const
{
    return "Third of length";
}
