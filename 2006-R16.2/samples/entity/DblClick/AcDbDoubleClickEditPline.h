//
// (C) Copyright 2001 by Autodesk, Inc. 
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
// AcDbDoubleClickEditPline.h: interface for the AcDbDoubleClickEditPline class.

#include "AcDblClkEdit.h"

#if !defined(AFX_ACDBDOUBLECLICKEDITPLINE_H__A78199F5_6A01_4851_A8D0_4E828FF9E6F0__INCLUDED_)
#define AFX_ACDBDOUBLECLICKEDITPLINE_H__A78199F5_6A01_4851_A8D0_4E828FF9E6F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AcDbDoubleClickEditPline : public AcDbDoubleClickEdit
{
public:
	AcDbDoubleClickEditPline();
	virtual ~AcDbDoubleClickEditPline();
	void finishEdit(void);
	void startEdit(AcDbEntity *pEnt, AcGePoint3d clickpt);
};

#endif // !defined(AFX_ACDBDOUBLECLICKEDITPLINE_H__A78199F5_6A01_4851_A8D0_4E828FF9E6F0__INCLUDED_)
