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

//-----------------------------------------------------------------------------
//----- DocData.h : include file for document specific data. An instance of this
//----- class is automatically created and managed by the AsdkDataManager class.
//----- See the AsdkDmgr.h / DocData.cpp for more datails
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//----- Here you can store the document / database related data.
class CDocData {
public:
	CDocData () ;
	CDocData (const CDocData &data) ;
	~CDocData () ;

	//{{AFX_ARX_DATA(CDocData)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_ARX_DATA

	//----- TODO: here you can add your variables
} ;
