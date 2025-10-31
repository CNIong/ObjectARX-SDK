//
// (C) Copyright 2002 by Autodesk, Inc. 
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
//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__7DC1101A_C827_11D2_B89C_080009DCA551__INCLUDED_)
#define AFX_STDARX_H__7DC1101A_C827_11D2_B89C_080009DCA551__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//{{AFX_ARX_INC_SELECTED
#include "geassign.h"         // AcGe assign macros
#include "acgiutil.h"         // graphical definitions
//}}AFX_ARX_INC_SELECTED

// AutoCAD MFC Extensions:
#include "adui.h"
#include "acui.h"
#include "acuiComboBox.h"
#include "acuiDialog.h"

#include "imgdef.h"
#include "imgent.h"
//{{AFX_ARX_INC_OTHERS
//}}AFX_ARX_INC_OTHERS

#include "axlock.h"

//{{AFX_ARX_FUNC
void AsdkBlockView();
void AsdkConfigGS();
//}}AFX_ARX_FUNC

#include "resource.h"
#include "BlockViewDlg.h"
#include "dbsymtb.h"
#include <math.h>

#endif 
