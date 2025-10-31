//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "dbmain.h"
#include "acdocman.h"
#include "dbapserv.h"

#include "DocReactor.h"



AsdkDocGlobals *gpAsdkDocGlobals = NULL; 
AsdkPerDocData * gpActualData = NULL;


// Document swapping functions 
void 
AsdkDocReactor::documentToBeActivated(AcApDocument *pDoc) 
{ 
    gpAsdkDocGlobals->setGlobals(pDoc); 
} 

void 
AsdkDocReactor::documentCreated(AcApDocument *pDoc) 
{ 
    gpAsdkDocGlobals->setGlobals(pDoc); 
} 

void 
AsdkDocReactor::documentToBeDestroyed(AcApDocument *pDoc) 
{ 
    gpAsdkDocGlobals->removeDocGlobals(pDoc); 
} 


AsdkPerDocData::AsdkPerDocData(AcApDocument *pDoc) 
{ 
    m_pDoc = pDoc; 
    m_pNext = NULL; 

	colorIndex = 1;		
	deviation = 0.1;  

} 

/////////////////////////////////////////////////////////
//   AsdkDocGlobals implementation
//
AsdkDocGlobals::AsdkDocGlobals(AcApDocument *pDoc) 
{ 
    m_pData = m_pHead = NULL; 
    m_pDocReactor = new AsdkDocReactor(); 
    acDocManager->addReactor(m_pDocReactor); 
} 

// Iterate through the list until we find the doc's global data. 
// If it's not found, create a new set of doc globals. 
// 
void 
AsdkDocGlobals::setGlobals(AcApDocument *pDoc) 
{ 
    AsdkPerDocData *p_data = m_pHead, *prev_data = m_pHead; 
    while (p_data != NULL)  
    { 
        if (p_data->m_pDoc == pDoc)  
        { 
            m_pData = p_data; 
            break; 

        } 
        prev_data = p_data; 
        p_data = p_data->m_pNext; 
    } 
    if (p_data == NULL)  
    { 
		gpActualData = m_pData = new AsdkPerDocData(pDoc);
        if (m_pHead == NULL) 
            m_pHead = m_pData;
        else 
            prev_data->m_pNext = m_pData; 
    }
	else
		gpActualData = m_pData;
} 

// Delete the globals associated with pDoc. 
// 
void 
AsdkDocGlobals::removeDocGlobals(AcApDocument *pDoc) 
{ 
    AsdkPerDocData  *p_data = m_pHead, *prev_data = m_pHead; 
    while (p_data != NULL)  
    { 
        if (p_data->m_pDoc == pDoc)  
        { 
            if (p_data == m_pHead) 
                m_pHead = p_data->m_pNext; 
            else 
                prev_data->m_pNext = p_data->m_pNext; 

            if (m_pData == p_data) 
                m_pData = m_pHead; 
	        delete p_data; 
            break; 
        } 
        prev_data = p_data; 
        p_data = p_data->m_pNext; 
    } 
} 

// Delete all the doc globals in the list (recursively). 
// 
void 
AsdkDocGlobals::removeAllDocGlobals(AsdkPerDocData *p_target) 
{ 
    if (p_target == NULL) 
        return; 
    if (p_target->m_pNext != NULL) 
        removeAllDocGlobals(p_target->m_pNext); 
    delete p_target; 
} 

// Application was unloaded - delete everything associated with this 
// 
void AsdkDocGlobals::unload() 
{ 
    acDocManager->removeReactor(m_pDocReactor); 
    delete m_pDocReactor; 
    removeAllDocGlobals(m_pHead); 
    m_pHead = m_pData = NULL; 
} 

/////////////////////////////////////////////////////////////////
//  Global functions to Setup/Delete the AcApDocManagerReactor
//  required by the MDI environment
/////////////////////////////////////////////////////////////////
void InitializeMDIManagement()
{
	gpAsdkDocGlobals = new AsdkDocGlobals( curDoc() ); 
	// Create all the document specific data		
	gpAsdkDocGlobals->setGlobals(curDoc());
}

void ShutDownMDIManagement()
{
	if (gpAsdkDocGlobals != NULL) 
	{   
		gpAsdkDocGlobals->unload(); 
		delete gpAsdkDocGlobals; 
		gpAsdkDocGlobals = NULL; 
	} 
}

