// (C) Copyright 2005-2006 by Autodesk, Inc. 
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

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#ifndef WINVER
#define WINVER 0x500
#endif

#include <math.h>
#include <TCHAR.H>

// TODO: reference additional headers your program requires here
#include "rxregsvc.h"
#include "AcString.h"
#include "acutads.h"
#include "accmd.h"
#include "dbmain.h"
#include "dbsol3d.h"
#include "dbobjptr.h"
#include "dbapserv.h"
#include "dbsymutl.h"
#include "dbxutil.h"
#include "aced.h"

// Headers of Render API
#include "dblight.h"
#include "dbSun.h"
#include "dbRender.h"
#include "dbmaterial.h"

// Headers of Render API sample 
#include "Utilities.h"