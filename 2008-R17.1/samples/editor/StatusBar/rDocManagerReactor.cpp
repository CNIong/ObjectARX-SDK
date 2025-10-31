//
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

/////////////////////////////////////////////
// AcApDocManagerReactor reactors.
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "StdArx.h"

#include "acstatusbar.h"


void BubbleWindowCallback(void*,int);
void CreateDocumentWorkspace(AcApDocument* pDoc);
void DestroyDocumentWorkspace(AcApDocument* pDoc);

asdkDocManagerReactor::asdkDocManagerReactor(const bool autoInitAndRelease)
{
	m_autoInitAndRelease = autoInitAndRelease;
	if (m_autoInitAndRelease)
		if (NULL != acDocManager)
			acDocManager->addReactor(this);
		else
			m_autoInitAndRelease = false;
}

asdkDocManagerReactor::~asdkDocManagerReactor()
{
	if (m_autoInitAndRelease)
		if (NULL != acDocManager)
			acDocManager->removeReactor(this);
}

void asdkDocManagerReactor::documentToBeDestroyed(AcApDocument* pDocToDestroy)
{
	// Destroy the workspace pointers for this document.
	DestroyDocumentWorkspace(pDocToDestroy);
}

void asdkDocManagerReactor::documentCreated(AcApDocument* pDocCreating)
{
	// Create a workspace for the newly opened document.
	CreateDocumentWorkspace(pDocCreating);
}
