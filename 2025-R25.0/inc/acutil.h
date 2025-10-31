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
//  acutil.h - General-purpose AcUtil functions
//
//
//
//  DESCRIPTION:
//
//  This header file contains declarations of general-purpose utility
//  functions provided with the AcUtil library and DLL.
//
#ifndef _ACUTIL_H
#define _ACUTIL_H

#include "AcDbCore2dDefs.h"     // ACDBCORE2D_PORT

ACDBCORE2D_PORT bool acutSplitString(size_t & numLeftBytes, const ACHAR *& pRight,
                                     const ACHAR  * source, unsigned int  delimiter);

ACDBCORE2D_PORT bool acutWcMatchEx(const ACHAR * string, const ACHAR * pattern,
                                   bool ignoreCase);

#endif // _ACUTIL_H

