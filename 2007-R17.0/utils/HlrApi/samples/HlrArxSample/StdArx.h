//
//
// (C) Copyright 1990-2002 by Autodesk, Inc. 
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
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__EA061219_3F44_11D3_8D68_0060B0CDE437__INCLUDED_)
#define AFX_STDARX_H__EA061219_3F44_11D3_8D68_0060B0CDE437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//{{AFX_ARX_INC_SELECTED
#include "dbsymtb.h"          // symboltables
#include "actrans.h"          // transaction manager
#include "dbents.h"           // 'old' 2D polyline
#include "dbsol3d.h"          // Acis solids
#include "dbbody.h"           // Acis bodies
#include "dbcurve.h"          // Curve base class
#include "dbdim.h"            // dimension classes
#include "dbelipse.h"         // ellipse
#include "dbmain.h"           // Entity base class
#include "dbfcf.h"            // geometric tolerance
#include "graph.h"            // graph classes
#include "dbgroup.h"          // group classes
#include "dbhandle.h"         // handle class
#include "dbhatch.h"          // hatch
#include "dblead.h"           // leader
#include "dbmline.h"          // multi line
#include "dbmtext.h"          // mtext
#include "dbole.h"            // OLE2 container
#include "dbpl.h"             // polyline
#include "dbray.h"            // ray
#include "dbregion.h"         // Acis region
#include "dbspline.h"         // spline
#include "dbxline.h"          // xline
#include "gemat2d.h"          // AcGeMatrix2d
#include "gemat3d.h"          // AcGeMatrix3d
#include "gepnt2d.h"          // AcGePoint2d
#include "gept2dar.h"         // AcGePoint2dArray
#include "gepnt3d.h"          // AcGePoint3d
#include "gept3dar.h"         // AcGePoint3dArray
#include "gevec2d.h"          // AcGeVector2d
#include "gevc2dar.h"         // AcGeVector2dArray
#include "gevec3d.h"          // AcGeVector3d
#include "gevc3dar.h"         // AcGeVector3dArray
#include "gevptar.h"          // AcGeVoidPointerArray
//}}AFX_ARX_INC_SELECTED

//{{AFX_ARX_INC_OTHERS
//}}AFX_ARX_INC_OTHERS

#include "AdskDMgr.h"         // Utility class for document data
#include "docdata.h"          // Your document specific data

// Declare it as an extern here so that it
// becomes available in all modules
extern AsdkDataManager<CDocData> DocVars;

//{{AFX_ARX_FUNC
void asdktest1();
void asdktest2();
void asdktest3();
void asdktest4();
void asdktest5();
void asdktest6();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#include "../../Inc/Hlr.h"

#endif 
