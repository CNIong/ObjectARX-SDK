//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

/////////////////////////////////////////////////////////////////////////////
// Note: _ADUI_BUILD should be defined only when building the DLL.

#ifdef  _ADUI_BUILD
#  define   ADUI_PORT  __declspec(dllexport)
#else
#  define   ADUI_PORT
#endif
