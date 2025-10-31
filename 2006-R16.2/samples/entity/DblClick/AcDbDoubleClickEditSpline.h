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
// AcDbDoubleClickEditSpline.h: interface for the AcDbDoubleClickEditSpline class.

#if !defined(AFX_ACDBDOUBLECLICKEDITSPLINE_H__A84A7A99_DE1E_4D39_A32B_F7E202132BBC__INCLUDED_)
#define AFX_ACDBDOUBLECLICKEDITSPLINE_H__A84A7A99_DE1E_4D39_A32B_F7E202132BBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AcDbDoubleClickEditSpline : public AcDbDoubleClickEdit
{
public:
	void finishEdit(void);
	void startEdit(AcDbEntity *pEnt, AcGePoint3d pt);
	AcDbDoubleClickEditSpline();
	virtual ~AcDbDoubleClickEditSpline();

};

#endif // !defined(AFX_ACDBDOUBLECLICKEDITSPLINE_H__A84A7A99_DE1E_4D39_A32B_F7E202132BBC__INCLUDED_)
