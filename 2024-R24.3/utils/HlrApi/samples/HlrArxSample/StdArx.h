//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
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
