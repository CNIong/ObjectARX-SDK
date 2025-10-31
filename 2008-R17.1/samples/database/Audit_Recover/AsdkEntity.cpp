// (C) Copyright 2002-2006 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
//----- AsdkEntity.cpp : Implementation of AsdkEntity
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "AsdkEntity.h"
#include "asdkstyle.h"

//temp
#include "asdkentityrecreator.h"


//-----------------------------------------------------------------------------
Adesk::UInt32 AsdkEntity::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	AsdkEntity, AcDbCircle,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, ASDKENTITY,
	"ASDKAUDITRECOVERAPP"
	"|Product Desc:     A description for your object"
	"|Company:          Your company name"
	"|WEB Address:      Your company WEB site address"
)

//-----------------------------------------------------------------------------
AsdkEntity::AsdkEntity () : AcDbCircle () 
{
	m_bCorrupt2Flag = false;
}

AsdkEntity::~AsdkEntity () {
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus AsdkEntity::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	Acad::ErrorStatus es;
	es =AcDbCircle::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;

	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (AsdkEntity::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	pFiler->writeHardPointerId(m_styleId);
	pFiler->writeBool(m_bCorrupt2Flag);

	//----- Save parent class information first.

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus AsdkEntity::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	Acad::ErrorStatus es;
	//----- Read parent class information first.
	es =AcDbCircle::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;

	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > AsdkEntity::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < AsdkEntity::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....

	pFiler->readHardPointerId(&m_styleId);
	pFiler->readBool(&m_bCorrupt2Flag);

	return (pFiler->filerStatus ()) ;
}

//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean AsdkEntity::worldDraw (AcGiWorldDraw *mode) {
	assertReadEnabled () ;

	AcDbCircle::worldDraw (mode);
	
	mode->subEntityTraits().setColor(1);
	mode->geometry().circle(center(),radius()/2,normal());

	return Acad::eOk;
}

AcDbObjectId AsdkEntity::style()
{
	return m_styleId;
}

void AsdkEntity::setStyle(AcDbObjectId styleId)
{
	m_styleId = styleId;
}

void AsdkEntity::setCorruption(bool bCorrupt)
{
	m_bCorrupt2Flag = bCorrupt;
}


Acad::ErrorStatus AsdkEntity::audit(AcDbAuditInfo* pAuditInfo)
{
	Acad::ErrorStatus baseEs = AcDbEntity::audit(pAuditInfo);
	Acad::ErrorStatus localEs = Acad::eOk;
	AcDbObjectId fetchedId = AcDbObjectId::kNull;
	
	switch(pAuditInfo->auditPass())
	{
	case AcDbAuditInfo::PASS1:
				
		// Check self
		if(radius()<0.01f)
		{
			pAuditInfo->errorsFound(1);
			if(pAuditInfo->fixErrors())
			{
				assertWriteEnabled();
				pAuditInfo->printError(_T("AsdkEntity"),_T("0.0"),_T(">0.01"),_T("2.0"));
				if(Acad::eOk == setRadius(2.0f))
				{
					pAuditInfo->errorsFixed(1);
					localEs = Acad::eOk;
				}
				else
					localEs = Acad::eUnrecoverableErrors;
			}
		}
		break;

	case AcDbAuditInfo::PASS2:
		
		// Check references
		localEs = pAuditInfo->fetchObject(m_styleId,fetchedId,AsdkStyle::desc(),true);
		if((m_styleId == AcDbObjectId::kNull) || ((Acad::eOk == localEs) && (fetchedId != m_styleId)))
		{
			pAuditInfo->errorsFound(1);
			pAuditInfo->printError(_T("AsdkEntity"),_T("AsdkStyle Style Object"),_T("Bad or missing Style"),_T(""));
			// Errors found in the style
			if(pAuditInfo->fixErrors())
			{
				assertWriteEnabled();
				setStyle(fetchedId);
				pAuditInfo->errorsFixed(1);
			}
		}
		localEs = Acad::eOk;
		break;
	}

	ACDB_AUDIT_RETURN(pAuditInfo,baseEs,localEs,true)
}

