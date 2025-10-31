//
// (C) Copyright 1999 by Autodesk, Inc. 
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
//
#include <dbapserv.h>
#include "Lab7PerDocData.h"
#include "Lab7Utils.h"


AsdkLab7DataManager::AsdkLab7DataManager()
{
    acDocManager->addReactor(this);
}

AsdkLab7DataManager::~AsdkLab7DataManager()
{
	acDocManager->removeReactor(this);
}

void AsdkLab7DataManager::documentToBeActivated(AcApDocument* pDoc)
{
	if ( chEmployeesInfo.m_pDbReactor == NULL ) { 
		chEmployeesInfo.m_pDbReactor = new AsdkLab7DbReactor();
		acdbHostApplicationServices()->workingDatabase()->addReactor(chEmployeesInfo.m_pDbReactor);
		attachReactorToAllEmployee(true);
	}

}

void AsdkLab7DataManager::documentToBeDestroyed( AcApDocument *pDoc )
{
	if ( chEmployeesInfo.m_pDbReactor != NULL) { //it should always happen
		curDoc()->database()->removeReactor( chEmployeesInfo.m_pDbReactor); 
		delete chEmployeesInfo.m_pDbReactor;
		attachReactorToAllEmployee(false);
	} 
    m_dataMap.erase(pDoc);
}
    
AsdkLab7DataManager lab7DataMgr; // MDI Safe


// ----------------------------------------------------------------------------
// Constructor.
//

AsdkChangedEmployees::AsdkChangedEmployees()
{
	EditCommand = false;
	NoObjReactor = false;
	m_pDbReactor = NULL;
}

