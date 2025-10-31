//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//      arxsdk/acui_port.h
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// Note: _ACUI_BUILD should be defined only when building the DLL.

#ifdef  _ACUI_BUILD
#  define   ACUI_PORT  __declspec(dllexport)
#else
#  define   ACUI_PORT
#endif

