//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1994-2002 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////

#ifndef _acuiListCtrl_h
#define _acuiListCtrl_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAcUiListCtrl window

/*
class ACUI_PORT CAcUiListCtrl : public CAdUiListCtrl {
//    DECLARE_DYNAMIC(CAcUiListCtrl);

public:
	            CAcUiListCtrl ();
virtual         ~CAcUiListCtrl ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAcUiListCtrl)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAcUiListCtrl)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
*/
//typedef CAdUiListCtrl   CAcUiListCtrl;
//The first release (2/2002) of the VC7 compiler has
//a bug that causes the above typedef not to work
//properly in certain situations.
//Here's some minimal code that demonstrates the problem.
//If/when they fix the problem we can go back using
//the typedef.
/*
class A 
{
protected:
    static void f() {}
};

typedef A B;

class C : public B
{
    static void* p;
};
void * C::p = &B::f;  //error C2248: 'A::f' : cannot access protected member declared in class 'A'

void main()
{
}
*/

#define  CAcUiListCtrl CAdUiListCtrl

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
