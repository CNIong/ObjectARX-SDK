//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ERRORMSG_H__
#define __ERRORMSG_H__


///////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
// Facet Modeler Error Passing Interface
//
///////////////////////////////////////////////////////////////////////////////
#include "AdAChar.h"

#if _MSC_VER >= 1000
using namespace AModeler;
#endif

ACHAR* getErrorMsg(ErrorCode err);

#endif
