//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// ********************************************************************************
// MODULE:      AcGiLineAttrUtils.h
// PURPOSE:     Utility functions to convert between different
//                line attributes tables
// HISTORY:     03/17/2002
// ********************************************************************************

#pragma once

#include "acdb.h"

class AcGiLineAttrUtils
{
public:
    // Unicode: leave as char for now
    static char __stdcall acgiLineWeightToIndex(AcDb::LineWeight lw);
    static AcDb::LineWeight __stdcall acgiIndexToLineWeight(char index);
};
