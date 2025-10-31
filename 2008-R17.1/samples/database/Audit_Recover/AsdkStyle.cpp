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
//----- AsdkStyle.cpp : Implementation of AsdkStyle
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "AsdkStyle.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 AsdkStyle::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	AsdkStyle, AcDbObject,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, ASDKSTYLE,
	"ASDKAUDITRECOVERAPP"
	"|Product Desc:     A description for your object"
	"|Company:          Your company name"
	"|WEB Address:      Your company WEB site address"
)

//-----------------------------------------------------------------------------
AsdkStyle::AsdkStyle () : AcDbObject () 
{
	mpStyleName = NULL;
}

AsdkStyle::AsdkStyle (ACHAR* pStyleName) : AcDbObject () 
{
	mpStyleName = NULL;
	setStyleName(pStyleName);
}


AsdkStyle::~AsdkStyle () {
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus AsdkStyle::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbObject::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (AsdkStyle::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	pFiler->writeString(mpStyleName);
	pFiler->writeBool(m_bCorrupt2Flag);

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus AsdkStyle::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbObject::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > AsdkStyle::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < AsdkStyle::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	
	pFiler->readString(&mpStyleName);
	pFiler->readBool(&m_bCorrupt2Flag);

	return (pFiler->filerStatus ()) ;
}


AcDbObjectId AsdkStyle::AddToNOD(ACHAR* pStyleName)
{
	AcDbObjectId newId;
	AcDbDatabase *pDb=acdbHostApplicationServices()->workingDatabase();
	AcTransaction *pTrans=pDb->transactionManager()->startTransaction();
	try
	{
		AcDbDictionary *pNOD=NULL;
		if(Acad::eOk!=pTrans->getObject((AcDbObject*&)pNOD,pDb->namedObjectsDictionaryId(),AcDb::kForRead))
			throw "Couldn't get the NOD";

		AcDbObjectId dictId;
		AcDbDictionary *pStyleDict=NULL;
		if(Acad::eOk!=pNOD->getAt(_T("ASDK_STYLE"),dictId))
		{
			pNOD->upgradeOpen();
			pStyleDict=new AcDbDictionary;
			if(Acad::eOk!=pNOD->setAt(_T("ASDK_STYLE"),pStyleDict,dictId))
			{
				delete pStyleDict;
				throw _T("Couldn't add ASDK_STYLE to the NOD");
			}
			pDb->transactionManager()->addNewlyCreatedDBRObject(pStyleDict);
		}
		else
			if(Acad::eOk!=pTrans->getObject((AcDbObject*&)pStyleDict,dictId,AcDb::kForWrite))
				throw _T("Couldn't get the ASDK_STYLE Object");
		
		AsdkStyle *pStyle = NULL;
		if(Acad::eOk!=pStyleDict->getAt(_T("ASDK_STYLE_OBJECT"),newId))
		{
			pStyle = new AsdkStyle(pStyleName);
			if(!pStyle)
				throw _T("Couldn't create style object");

			if(Acad::eOk != pStyleDict->setAt(_T("ASDK_STYLE_OBJECT"),pStyle,newId))
			{
				delete pStyle;
				throw _T("Couldn't set new style object to ASDK_STYLE Dictionary");
			}
			if(Acad::eOk!=pDb->transactionManager()->addNewlyCreatedDBRObject(pStyle))
			{
				delete pStyle;
				throw _T("Couldn't set new style object to ASDK_STYLE Dictionary");
			}
		}
		pDb->transactionManager()->endTransaction();

	}
	catch(LPCTSTR pMessage)
	{
		pDb->transactionManager()->abortTransaction();
		throw pMessage;
	}
	return newId;
}


ACHAR* AsdkStyle::getStyleName(void)
{
	return mpStyleName;
}

void AsdkStyle::setStyleName(ACHAR* styleName)
{
	if(mpStyleName)
		acutDelString(mpStyleName);
	
	if(Acad::eOk != acutNewString(styleName,mpStyleName))
		mpStyleName=NULL;
}

void AsdkStyle::setCorruption(bool bCorrupt)
{
	m_bCorrupt2Flag = bCorrupt;
}


