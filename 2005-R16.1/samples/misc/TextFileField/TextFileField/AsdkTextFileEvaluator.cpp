//
//
// (C) Copyright 1990-2003 by Autodesk, Inc. 
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

#include "stdafx.h"
#include "AsdkTextFileEvaluator.h"
#include "assert.h"
#include "io.h"
#include "stdio.h"
#include <fcntl.h>



const char*
AsdkTextFileEvaluator::getEvaluatorId(void)const
{
	return TFEVALID;
}

Acad::ErrorStatus
AsdkTextFileEvaluator::compile(AcDbField * pField, AcDbDatabase * pDb, AcFdFieldResult * pResult)
{
	Acad::ErrorStatus es;
	assert(pField != NULL);
    
    if ( pField == NULL )
        return Acad::eInvalidInput;

    if ( pDb == NULL )
        pDb = pField->database();

    // Get the field code after stripping all the options
    int nFlag = AcDbField::kEvaluatedChildren | AcDbField::kStripOptions;
	const char* sFieldCode = pField->getFieldCode((AcDbField::FieldCodeFlag) nFlag);

	if ( strcmp( sFieldCode, "" ) == 0 )
	{
        // Invalid field
        es = pResult->setEvaluationStatus(AcDbField::kInvalidCode);
        return Acad::eInvalidInput;
    }
    AcFdFieldValue val( sFieldCode );
    es = pField->setData(TFDATAID, &val);

    return Acad::eOk;
}

Acad::ErrorStatus
AsdkTextFileEvaluator::evaluate(AcDbField * pField, int nContext, AcDbDatabase* pDb, AcFdFieldResult* pResult)
{
	Acad::ErrorStatus es;
	assert(pField != NULL);
   
    if (pField == NULL )
        return Acad::eInvalidInput;

    if (pDb == NULL)
        pDb = pField->database();

	AcFdFieldValue evalValue;
	AcDbField::EvalStatus evalStatus = format(pField,pDb,evalValue);
	
	if ( evalStatus == AcDbField::kSuccess )
	{
		es = pResult->setFieldValue( &evalValue );
	}
	else
		es=eInvalidInput;

	pResult->setEvaluationStatus( evalStatus );

	return es;
}

AcDbField::EvalStatus
AsdkTextFileEvaluator::format(AcDbField* pField, AcDbDatabase* pDb, AcFdFieldValue & pfValue)
{
	Acad::ErrorStatus es;
	assert( pField != NULL );

    if ( pDb == NULL )
        pDb = pField->database();

    AcFdFieldValue val;
    es = pField->getData(TFDATAID, &val);
	if(Acad::eOk!=es)
		return AcDbField::EvalStatus::kOtherError;;

   	const char *sValue;
	
	if( val.dataType() != AcFdFieldValue::kString )
		return AcDbField::kInvalidCode;
	else
	{
		val.get(sValue);
		
		// Multi-line text must include both CR & LF characters to be maintained
		// as a field by the MText IPE. We will read the text file as a binary
		// stream in order to keep the original CR & LF characters.
		
		int fp = _open(sValue,_O_BINARY | _O_RDONLY);
		
		if(-1 == fp)
			return AcDbField::kInvalidCode;
		
		// Read the file contents
		long nFileLen = _filelength(fp) + 1;
		char *sTextOrg = new char[nFileLen];
		
		memset(sTextOrg,0,nFileLen);
		if(0 == _read(fp,sTextOrg,nFileLen - 1))
		{
			delete[] sTextOrg;
			return AcDbField::kInvalidCode;
		}
		
		pfValue.set(sTextOrg);
		
		// Cleanup
		delete[] sTextOrg;
		_close(fp);
		
	}
	return AcDbField::kSuccess;
}