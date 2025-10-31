//
// StdArx.h : include file for ObjectARX/DBX include files
// this file is only included once by your stdafx.h

#if !defined(AFX_STDARX_H__A5458F18_1F33_11D3_8D63_0060B0CDE437__INCLUDED_)
#define AFX_STDARX_H__A5458F18_1F33_11D3_8D63_0060B0CDE437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//{{AFX_ARX_INC_SELECTED
#include "dbsymtb.h"          // symboltables
#include "dbents.h"           // arc
#include "dbxrecrd.h"         // XRecord class
//}}AFX_ARX_INC_SELECTED

//{{AFX_ARX_INC_OTHERS
//}}AFX_ARX_INC_OTHERS

#include "AdskDMgr.h"         // Utility class for document data
#include "docdata.h"          // Your document specific data

// Declare it as an extern here so that it
// becomes available in all modules
extern AsdkDataManager<CDocData> DocVars;

//{{AFX_ARX_FUNC
void asdkmyinput();
void asdkmyselect();
void asdkcreate();
void asdksetlayer();
void asdkaddentry();
void asdkremoveentry();
void asdklistentries();
//}}AFX_ARX_FUNC

// TODO: Here you can add your own includes / declarations
#endif 
