/////////////////////////////////////////////////////////////////////////////
//
//
// (C) Copyright 2008-2009 Autodesk, Inc. All rights reserved.
//
// **** CONFIDENTIAL MATERIAL ****
//
// The information contained herein is confidential, proprietary to
// Autodesk, Inc., and considered a trade secret. Use of this information
// by anyone other than authorized employees of Autodesk, Inc. is granted
// only under a written nondisclosure agreement, expressly prescribing
// the scope and manner of such use.
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef  _ADAF_BUILD
#  define   ADAF_PORT  __declspec(dllexport)
#else
#  define   ADAF_PORT  __declspec(dllimport)
#endif