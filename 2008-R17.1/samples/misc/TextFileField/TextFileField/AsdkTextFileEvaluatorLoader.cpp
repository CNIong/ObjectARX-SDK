//
//
// (C) Copyright 1990-2006 by Autodesk, Inc. 
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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "AsdkTextFileEvaluatorLoader.h"
#include "tchar.h"



AsdkTextFileEvaluatorLoader::AsdkTextFileEvaluatorLoader(void)
{
	m_pEvaluator = new AsdkTextFileEvaluator();
}

AsdkTextFileEvaluatorLoader::~AsdkTextFileEvaluatorLoader(void)
{
	delete m_pEvaluator;
	m_pEvaluator = NULL;
}

AcFdFieldEvaluator * AsdkTextFileEvaluatorLoader::getEvaluator(LPCTSTR pszEvalId)
{
	if ( _tcscmp( pszEvalId, TFFIELDCODE ) == 0 )
        return m_pEvaluator;
	else
		return NULL;
}

AcFdFieldEvaluator * AsdkTextFileEvaluatorLoader::findEvaluator(AcDbField * pField, const TCHAR*& pszEvalId)
{
	const TCHAR *sEvalId = m_pEvaluator->getEvaluatorId();
	if ( _tcscmp( pszEvalId, sEvalId ) == 0 )
        return m_pEvaluator;
	else
		return NULL;
}

Acad::ErrorStatus AsdkTextFileEvaluatorLoader::registerLoader(void)
{
	Acad::ErrorStatus es;

	AcFdFieldEngine * pfEngine = acdbGetFieldEngine();
	if ( pfEngine != NULL )
		es = pfEngine->registerEvaluatorLoader( this );

	return es;
}

Acad::ErrorStatus AsdkTextFileEvaluatorLoader::unregisterLoader(void)
{
	Acad::ErrorStatus es = Acad::eOk;

	AcFdFieldEngine * pfEngine = acdbGetFieldEngine();
	if ( pfEngine != NULL )
		es = pfEngine->unregisterEvaluatorLoader( this );

	return es;
}
