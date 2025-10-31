//  Copyright 2004-2006 by Autodesk, Inc.
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
// DWFEntReactor.h
///<summary> 
/// classes defined here include:
/// AcadEntGeneralProps :To hold the AcDbEntity base properties which will be published as metadata in to dwf file
/// AcTestDMMEntReactor: Implements AcDMMReactor to handle entity level events which we trap during
/// publishing of entity to DWF file. This class makes use of general purpose class AcadEntGeneralProps 
/// </summary>

#ifndef _DWFENTREACTOR_H
#define _DWFENTREACTOR_H

#include "StdAfx.h"
#include "acpublishreactors.h"
#include "acdmmapi.h"

class AcadEntGeneralProps
{
public:
	AcadEntGeneralProps();
	virtual ~AcadEntGeneralProps();

public:
	Adesk :: UInt16 m_nColorIndex;
	CString m_strLayer;
	CString m_strLineType;
	double m_dLineTypeScale;
	CString	m_strHyperLinkLocation;

	TCHAR m_chHandle[20];
	TCHAR m_chEntityType[20];
	bool mIsBlockRef;
};


class AcTestDMMEntReactor:public AcDMMReactor
{

public:
	AcTestDMMEntReactor();
	virtual ~AcTestDMMEntReactor();
	void OnBeginSheet(AcDMMSheetReactorInfo * pInfo);
	void OnBeginEntity(AcDMMEntityReactorInfo * pInfo);
	void OnEndEntity(AcDMMEntityReactorInfo * pInfo);
	void OnEndSheet(AcDMMSheetReactorInfo * pInfo);	
	//TODO: will come back and implement logic for processing Block references
	//void ProcessBlocks (AcDMMEntityReactorInfo * pInfo);

private :
	AcadEntGeneralProps m_EntGenralPorps;
	void GetEntityInfo(AcDbEntity* pEntity);

};
#endif _DWFENTREACTOR_H